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

TfrmCreateGroup *frmCreateGroup;

__fastcall TfrmCreateGroup::TfrmCreateGroup(TComponent* Owner): TForm(Owner)
{
}

AnsiString __fastcall TfrmCreateGroup::GetWinDir()
{
    char buffer[MAX_PATH];
    ::GetWindowsDirectory(buffer, MAX_PATH);
    AnsiString path = AnsiString(buffer);
    if (path.LastDelimiter("\\") != path.Length()) {
        path = path + "\\";
    }
    return path;
}

void __fastcall TfrmCreateGroup::btnCancelClick(TObject *Sender)
{
    Close();
}

void __fastcall TfrmCreateGroup::btnSaveClick(TObject *Sender)
{
    AnsiString GroupName = fldTitle->Text.Trim();
    
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
            Application->MessageBox("Nama group hanya boleh berisi huruf, angka, dan spasi!", 
                                    "Invalid Name", MB_OK | MB_ICONERROR);
            return; // Gagalkan proses simpan
        }
    }

    AnsiString WinDir = GetWinDir();
    AnsiString GrpFileName = GroupName + ".grp";
    AnsiString FullGrpPath = WinDir + GrpFileName;
    AnsiString IniPath = WinDir + "oldcat.ini";

    if (FileExists(FullGrpPath)) {
        Application->MessageBox("Group already exist please create a new name..",
                                "Duplicate", MB_OK | MB_ICONWARNING);
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
