#include <vcl.h>
#include <IniFiles.hpp>
#pragma hdrstop

#include "U_Main.h"
#include "U_Group.h"
#include "U_CreateGroup.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmMain *frmMain;

__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TForm(Owner){

}

TfrmGroup* __fastcall TfrmMain::FindGroupWindow(AnsiString Caption) {
    for (int i = 0; i < MDIChildCount; i++) {
        if (MDIChildren[i]->Caption == Caption) {
            return (TfrmGroup*)MDIChildren[i];
        }
    }
    return NULL;
}

AnsiString __fastcall TfrmMain::GetWinDir()
{
    char buffer[MAX_PATH];
    ::GetWindowsDirectory(buffer, MAX_PATH);

    AnsiString path = AnsiString(buffer);
    if (path.LastDelimiter("\\") != path.Length()) {
        path = path + "\\";
    }
    return path;
}

void __fastcall TfrmMain::LoadGroupsFromIni()
{
    AnsiString IniPath = GetWinDir() + "oldcat.ini";
    if (!FileExists(IniPath)) {
        IniPath = ExtractFilePath(Application->ExeName) + "oldcat.ini";
    }

    if (!FileExists(IniPath)) return;

    TIniFile *ini = new TIniFile(IniPath);
    TStringList *GroupList = new TStringList();

    try {
        ini->ReadSectionValues("Groups", GroupList);

        for (int i = 0; i < GroupList->Count; i++) {
            AnsiString GroupFileName = GroupList->Values[GroupList->Names[i]];
            AnsiString FullGroupPath = "";

            // Cari lokasi file .GRP
            if (GroupFileName.Pos(":") == 0) {
                AnsiString PathInWin = GetWinDir() + GroupFileName;
                AnsiString PathInExe = ExtractFilePath(Application->ExeName) + GroupFileName;

                if (FileExists(PathInWin)) {
                    FullGroupPath = PathInWin;
                } else if (FileExists(PathInExe)) {
                    FullGroupPath = PathInExe;
                }
            } else {
                FullGroupPath = GroupFileName;
            }

            if (FullGroupPath != "" && FileExists(FullGroupPath)) {
                AnsiString GRPTitle = ExtractFileName(FullGroupPath);

                // --- PROSES VALIDASI AGAR TIDAK DOUBLE ---
                TfrmGroup *ExistingChild = FindGroupWindow(GRPTitle);

                if (ExistingChild) {
                    // Jika sudah ada, tampilkan ke depan saja
                    ExistingChild->BringToFront();
                    if (ExistingChild->WindowState == wsMinimized) {
                        ExistingChild->WindowState = wsNormal;
                    }
                } else {
                    // Jika belum ada, baru buat instance baru
                    TfrmGroup *Child = new TfrmGroup(this);
                    Child->Caption = GRPTitle;
                    Child->LoadItemsFromGrp(FullGroupPath);
                    Child->Show();
                }
            }
        }
    }
    __finally {
        delete ini;
        delete GroupList;
    }
}

void __fastcall TfrmMain::Cascade1Click(TObject *Sender)
{
    this->Cascade();
}

void __fastcall TfrmMain::TileVertically1Click(TObject *Sender)
{
    this->TileMode = tbVertical;
    this->Tile();
}

void __fastcall TfrmMain::TileHorixzontally1Click(TObject *Sender)
{
    this->TileMode = tbHorizontal;
    this->Tile();
}

void __fastcall TfrmMain::Reload1Click(TObject *Sender)
{
    LoadGroupsFromIni();
}

void __fastcall TfrmMain::FormShow(TObject *Sender)
{
    LoadGroupsFromIni();
}

void __fastcall TfrmMain::Open1Click(TObject *Sender)
{
    TfrmCreateGroup *CreateForm = new TfrmCreateGroup(this);
        try {
            if (CreateForm->ShowModal() == mrOk) {
            // Jika sukses membuat group, reload daftar di Main Form
                LoadGroupsFromIni();
            }
        }
        __finally {
            delete CreateForm;
        }
}
//---------------------------------------------------------------------------

