/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/

#include <vcl.h>
#include <IniFiles.hpp>
#pragma hdrstop

#include "U_Main.h"
#include "U_Group.h"
#include "U_CreateGroup.h"
#include "U_ProcessMonitor.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TFormMain *FormMain;

__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner){
    LastLayoutMode = 0;
}

TFormGroup* __fastcall TFormMain::FindGroupWindow(AnsiString Caption) {
    for (int i = 0; i < MDIChildCount; i++) {
        if (MDIChildren[i]->Caption == Caption) {
            return (TFormGroup*)MDIChildren[i];
        }
    }
    return NULL;
}

AnsiString __fastcall TFormMain::GetCurAppDir()
{
    AnsiString path = ExtractFilePath(Application->ExeName);

    if (path.LastDelimiter("\\") != path.Length()) {
        path = path + "\\";
    }
    return path;
}
AnsiString __fastcall GetCurWinDir()
{
    char buffer[MAX_PATH];
    ::GetWindowsDirectory(buffer, MAX_PATH);

    AnsiString path = AnsiString(buffer);
    if (path.LastDelimiter("\\") != path.Length()) {
        path = path + "\\";
    }
    return path;
}

void __fastcall TFormMain::LoadGroupsFromIni()
{
    AnsiString IniPath = GetCurAppDir() + "progmanx.ini";

    if (!FileExists(IniPath))
    {
        TStringList *NewIni = new TStringList();
        try {
            NewIni->Add("[Settings]");
            NewIni->Add("Window=0,0,640,480,1");
            NewIni->Add("");
            NewIni->Add("[Groups]");
            NewIni->SaveToFile(IniPath);
        }
        __finally {
            delete NewIni;
        }
    }


    TIniFile *ini = new TIniFile(IniPath);
    TStringList *GroupList = new TStringList();
    try 
    {
        ini->ReadSectionValues("Groups", GroupList);

        for (int i = 0; i < GroupList->Count; i++) 
        {
            AnsiString GroupFileName = GroupList->Values[GroupList->Names[i]];
            AnsiString FullGroupPath = GetCurAppDir() + GroupFileName;

            AnsiString GRPTitle = ExtractFileName(GroupFileName);
            int dotPos = GRPTitle.Pos(".");
            if (dotPos > 0) GRPTitle = GRPTitle.SubString(1, dotPos - 1);

            if (FileExists(FullGroupPath))
            {
                TFormGroup *ExistingChild = FindGroupWindow(GRPTitle);
                if (!ExistingChild)
                {
                    TFormGroup *Child = new TFormGroup(this);
                    Child->Caption = GRPTitle;
                    Child->LoadItemsFromGrp(FullGroupPath);
                    Child->Show();
                }
            }
        }
    }
    __finally
    {
        delete ini;
        delete GroupList;
    }
}
void __fastcall TFormMain::Cascade1Click(TObject *Sender)
{
    LastLayoutMode = 1;
    this->Cascade();
}

void __fastcall TFormMain::TileVertically1Click(TObject *Sender)
{
    LastLayoutMode = 2;
    this->TileMode = tbVertical;
    this->Tile();
}

void __fastcall TFormMain::TileHorixzontally1Click(TObject *Sender)
{
    LastLayoutMode = 3;
    this->TileMode = tbHorizontal;
    this->Tile();
}

void __fastcall TFormMain::Reload1Click(TObject *Sender)
{
    LoadGroupsFromIni();
}

void __fastcall TFormMain::FormShow(TObject *Sender)
{
    this->Constraints->MinWidth = 0;
    this->Constraints->MinHeight = 0;
    this->Constraints->MaxWidth = 0;
    this->Constraints->MaxHeight = 0;
    
    this->BorderStyle = bsSizeable;
    LoadGroupsFromIni();
}

void __fastcall TFormMain::Open1Click(TObject *Sender)
{
    TFormCreateGroup *CreateForm = new TFormCreateGroup(this);
        try {
            if (CreateForm->ShowModal() == mrOk) {
                LoadGroupsFromIni();
            }
        }
        __finally {
            delete CreateForm;
        }
}

void __fastcall TFormMain::WMExitSizeMove(TMessage &Message)
{
    if (MDIChildCount > 0 && LastLayoutMode > 0)
    {
        ApplyMBoxLayout();
    }
    TForm::Dispatch(&Message);
}

void __fastcall TFormMain::FormResize(TObject *Sender)
{
    static TWindowState LastState = wsNormal;

    if (WindowState != LastState)
    {
        if (MDIChildCount > 0 && LastLayoutMode > 0)
        {
            ApplyMBoxLayout();
        }
        LastState = WindowState;
    }
}


void __fastcall TFormMain::ApplyMBoxLayout()
{
    if (MDIChildCount <= 0) return;

    LockWindowUpdate(ClientHandle);
    try {
        switch(LastLayoutMode)
        {
            case 1:
                this->Cascade();
                break;
            case 2: // Tile Vertical
                ::SendMessage(ClientHandle, WM_MDITILE, 0x0004 | 0x0002, 0);
                break;
            case 3:
                ::SendMessage(ClientHandle, WM_MDITILE, 0x0001 | 0x0002, 0);
                break;
        }
    }
    __finally {
        LockWindowUpdate(NULL);
    }
}
void __fastcall TFormMain::AppMonitor1Click(TObject *Sender)
{
    TFormProcessMonitor *f = (TFormProcessMonitor*)FindGroupWindow("Process Monitor");

    if (!f) {
        f = new TFormProcessMonitor(this);
        f->Caption = "Process Monitor";
        f->Show();
    } else {
        f->BringToFront();
    }
}
