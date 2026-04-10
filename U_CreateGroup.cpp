/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/
#include <vcl.h>
#include <IniFiles.hpp>
#pragma hdrstop

#include "U_CreateGroup.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormCreateGroup *FormCreateGroup;

__fastcall TFormCreateGroup::TFormCreateGroup(TComponent* Owner): TForm(Owner)
{
}

AnsiString __fastcall TFormCreateGroup::GetCurAppDir()
{
    AnsiString path = ExtractFilePath(Application->ExeName);

    if (path.LastDelimiter("\\") != path.Length()) {
        path = path + "\\";
    }
    return path;
}
void __fastcall TFormCreateGroup::ButtonCancelClick(TObject *Sender)
{
    Close();
}

void __fastcall TFormCreateGroup::ButtonSaveClick(TObject *Sender)
{
    AnsiString GroupName = FieldTitle->Text.Trim();

    if (GroupName.Length() == 0) {
        return;
    }

    for (int i = 1; i <= GroupName.Length(); i++) {
        char c = GroupName[i];
        bool isValid = (c >= 'A' && c <= 'Z') ||
                       (c >= 'a' && c <= 'z') ||
                       (c >= '0' && c <= '9') ||
                       (c == ' ');

        if (!isValid) {
            Application->MessageBox("Only A (a) to Z (z) and 0-9 for Group name !",
                                    "Invalid Name", MB_OK | MB_ICONERROR);
            return;
        }
    }

    AnsiString AppDir = GetCurAppDir();
    AnsiString GrpFileName = GroupName + ".grp";
    AnsiString FullGrpPath = AppDir + GrpFileName;
    AnsiString IniPath = AppDir + "progmanx.ini";

    if (FileExists(FullGrpPath)) {
        Application->MessageBox("Group already exist please create a new name..", "Duplicate", MB_OK | MB_ICONWARNING);
        return;
    }


    TStringList *NewGrp = new TStringList();
    try {
        NewGrp->Add("[Items]");
        NewGrp->SaveToFile(FullGrpPath);
    }
    catch (...) {
        Application->MessageBox("Error creating file!", "Error", MB_OK | MB_ICONERROR);
        delete NewGrp;
        return;
    }
    delete NewGrp;

    if (FileExists(IniPath)) {
        TIniFile *ini = new TIniFile(IniPath);
        TStringList *CurrentGroups = new TStringList();
        try {
            ini->ReadSection("Groups", CurrentGroups);
            int NextIndex = CurrentGroups->Count + 1;
            AnsiString NewKey = "Group" + IntToStr(NextIndex);
            ini->WriteString("Groups", NewKey, GrpFileName);
        }
        __finally {
            delete ini;
            delete CurrentGroups;
        }
    }

    Application->MessageBox("Group Created Successfully!", "Success", MB_OK | MB_ICONINFORMATION);
    ModalResult = mrOk;
}
