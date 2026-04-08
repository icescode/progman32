/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/
#include <vcl.h>
#include <IniFiles.hpp>
#pragma hdrstop

#include "U_AddItem.h"
#include "U_Group.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAddItem *frmAddItem;

__fastcall TfrmAddItem::TfrmAddItem(TComponent* Owner): TForm(Owner)
{
}
AnsiString __fastcall TfrmAddItem::GetWinDir()
{
    char buffer[MAX_PATH];
    ::GetWindowsDirectory(buffer, MAX_PATH);

    AnsiString path = AnsiString(buffer);
    if (path.LastDelimiter("\\") != path.Length()) {
        path = path + "\\";
    }
    return path;
}

AnsiString __fastcall TfrmAddItem::FormatTitle(AnsiString FileName)
{

    int dotPos = FileName.Pos(".");
    if (dotPos > 0) {
        FileName = FileName.SubString(1, dotPos - 1);
    }

    if (FileName.Length() > 0) {
        AnsiString FirstLetter = FileName.SubString(1, 1).UpperCase();
        AnsiString Rest = FileName.SubString(2, FileName.Length() - 1).LowerCase();
        FileName = FirstLetter + Rest;
    }

    return FileName;
}

void __fastcall TfrmAddItem::btnCancelClick(TObject *Sender)
{
    Close();
}

void __fastcall TfrmAddItem::btnSaveClick(TObject *Sender)
{
    if (!CallerGroup) {
        return;
    }

    AnsiString FullPath = fldPath->Text.Trim();
    AnsiString Title = fldTitle->Text.Trim();

    if (Title.Length() == 0 || FullPath.Length() == 0) {
        Application->MessageBox("Title and Path cannot be empty!", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    if (FullPath.Pos(":\\") == 0) {
        FullPath = GetWinDir() + FullPath;
    }

    if (!FileExists(FullPath)) {
        Application->MessageBox(("File not found: " + FullPath).c_str(), "Error", MB_OK | MB_ICONERROR);
        return;
    }

    AnsiString WinDir = GetWinDir();
    AnsiString GrpFileName = CallerGroup->Caption;
    AnsiString FullGrpPath = WinDir + GrpFileName;

    if (!FileExists(FullGrpPath)) {
        FullGrpPath = ExtractFilePath(Application->ExeName) + GrpFileName;
    }


    TIniFile *ini = new TIniFile(FullGrpPath);
    TStringList *ItemList = new TStringList();

    try {

        ini->ReadSection("Items", ItemList);

        int NextIndex = ItemList->Count + 1;
        AnsiString NewKey = "item" + IntToStr(NextIndex);

        ini->WriteString("Items", NewKey, Title + "," + FullPath + ",0");


        delete ini;
        ini = NULL;

        CallerGroup->LoadItemsFromGrp(FullGrpPath);

        Application->MessageBox("Item added successfully!", "Success", MB_OK | MB_ICONINFORMATION);


        ModalResult = mrOk;
    }
    __finally {
        if (ini) delete ini;
        if (ItemList) delete ItemList;
    }
}

void __fastcall TfrmAddItem::btnOpenFileDialogClick(TObject *Sender)
{

    openDialog->Filter = "Programs & Control Panel (*.exe;*.cpl)|*.exe;*.cpl|Executable Files (*.exe)|*.exe|Control Panel Files (*.cpl)|*.cpl";

    if (openDialog->Execute())
    {
        fldPath->Text = openDialog->FileName;
        AnsiString OnlyName = ExtractFileName(openDialog->FileName);
        fldTitle->Text = FormatTitle(OnlyName);
    }
}
