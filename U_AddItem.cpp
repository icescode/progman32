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

TFormAddItem *FormAddItem;

__fastcall TFormAddItem::TFormAddItem(TComponent* Owner): TForm(Owner)
{
}

AnsiString __fastcall TFormAddItem::GetCurAppDir()
{
    AnsiString path = ExtractFilePath(Application->ExeName);

    if (path.LastDelimiter("\\") != path.Length()) {
        path = path + "\\";
    }
    return path;
}
AnsiString __fastcall TFormAddItem::FormatTitle(AnsiString FileName)
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

void __fastcall TFormAddItem::ButtonCancelClick(TObject *Sender)
{
    Close();
}

void __fastcall TFormAddItem::ButtonSaveClick(TObject *Sender)
{
    AnsiString Title = FieldTitle->Text.Trim();
    AnsiString FullPath = FieldPath->Text.Trim();

    if (Title.IsEmpty() || FullPath.IsEmpty()) return;

    if (!FileExists(FullPath)) {
        Application->MessageBox(("File not found: " + FullPath).c_str(), "Error", MB_OK | MB_ICONERROR);
        return;
    }


    AnsiString AppDir = GetCurAppDir();
    AnsiString GrpFileName = CallerGroup->Caption + ".grp";
    AnsiString FullGrpPath = AppDir + GrpFileName;

    if (!FileExists(FullGrpPath)) {
        FullGrpPath = ExtractFilePath(Application->ExeName) + GrpFileName;
    }

    if (!FileExists(FullGrpPath)) {
        Application->MessageBox(("Group file not found: " + GrpFileName).c_str(), "Error", MB_OK | MB_ICONERROR);
        return;
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
void __fastcall TFormAddItem::ButtonOpenFileDialogClick(TObject *Sender)
{

    OpenDialog->Filter = "Programs & Control Panel (*.exe;*.cpl)|*.exe;*.cpl|Executable Files (*.exe)|*.exe|Control Panel Files (*.cpl)|*.cpl";

    if (OpenDialog->Execute())
    {
        FieldPath->Text = OpenDialog->FileName;
        AnsiString OnlyName = ExtractFileName(OpenDialog->FileName);
        FieldTitle->Text = FormatTitle(OnlyName);
    }
}
