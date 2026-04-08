/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/
#include <vcl.h>
#include <IniFiles.hpp>
#include <shellapi.h>
#pragma hdrstop

#include "U_Group.h"
#include "U_AddItem.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmGroup *frmGroup;

__fastcall TfrmGroup::TfrmGroup(TComponent* Owner): TForm(Owner){

}
AnsiString __fastcall TfrmGroup::GetWinDirLocal()
{
    char buffer[MAX_PATH];
    ::GetWindowsDirectory(buffer, MAX_PATH);
    AnsiString path = AnsiString(buffer);
    if (path.LastDelimiter("\\") != path.Length()) {
        path = path + "\\";
    }
    return path;
}

void __fastcall TfrmGroup::LoadItemsFromGrp(AnsiString FullGrpPath)
{
    if (!FileExists(FullGrpPath)) return;

    TIniFile *ini = new TIniFile(FullGrpPath);
    TStringList *Lines = new TStringList();

    lvIcons->Items->Clear();
    imgIcons->Clear();

    try {
        ini->ReadSectionValues("Items", Lines);

        for (int i = 0; i < Lines->Count; i++) {
            AnsiString RawValue = Lines->Values[Lines->Names[i]];
            if (RawValue.Trim() == "") continue;

            int p1 = RawValue.Pos(",");
            AnsiString Title = RawValue.SubString(1, p1 - 1);
            AnsiString Remainder = RawValue.SubString(p1 + 1, RawValue.Length());
            int p2 = Remainder.LastDelimiter(",");

            AnsiString FullPath = (p2 > 0) ? Remainder.SubString(1, p2 - 1).Trim() : Remainder.Trim();

            HICON hIcon = ExtractIcon(HInstance, FullPath.c_str(), 0);
            int NewIconIndex = -1;

            if ((int)hIcon > 1) {
                TIcon *ico = new TIcon();
                ico->Handle = hIcon;
                NewIconIndex = imgIcons->AddIcon(ico);
                delete ico;
            }

            TListItem *Item = lvIcons->Items->Add();
            Item->Caption = Title;
            Item->ImageIndex = NewIconIndex;
            Item->SubItems->Add(FullPath);
        }
    }
    __finally {
        delete Lines;
        delete ini;
    }
}
void __fastcall TfrmGroup::FormClose(TObject *Sender, TCloseAction &Action) {

    Action = caFree;
}

void __fastcall TfrmGroup::lvIconsDblClick(TObject *Sender)
{
    if (lvIcons->Selected == NULL || lvIcons->Selected->SubItems->Count == 0) return;

    AnsiString FilePath = lvIcons->Selected->SubItems->Strings[0];
    AnsiString Ext = ExtractFileExt(FilePath).LowerCase();

    if (Ext == ".cpl")
    {
        ShellExecute(Handle, "open", "control.exe", FilePath.c_str(), NULL, SW_SHOWNORMAL);
    }
    else
    {
        ShellExecute(Handle, "open", FilePath.c_str(), NULL,
                     ExtractFilePath(FilePath).c_str(), SW_SHOWNORMAL);
    }
}

void __fastcall TfrmGroup::lvIconsDeletion(TObject *Sender,
      TListItem *Item)
{
    if (Item->Data != NULL) {
        delete (AnsiString*)Item->Data;
        Item->Data = NULL;
    }
}

void __fastcall TfrmGroup::DeleteThisGroupClick(TObject *Sender)
{
    AnsiString GroupFileName = this->Caption;
    AnsiString FullGrpPath = GetWinDirLocal() + GroupFileName;

    if (Application->MessageBox("Delete this Group ?", "Confirmation", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
        if (FileExists(FullGrpPath)) {
            DeleteFile(FullGrpPath);
        }

        AnsiString IniPath = GetWinDirLocal() + "oldcat.ini";
        if (FileExists(IniPath))
        {
            TIniFile *ini = new TIniFile(IniPath);
            TStringList *TempList = new TStringList();
            try {
                ini->ReadSectionValues("Groups", TempList);
                ini->EraseSection("Groups");

                int newIdx = 1;
                for (int i = 0; i < TempList->Count; i++) {
                    AnsiString Val = TempList->Values[TempList->Names[i]];

                    if (Val != GroupFileName) {
                        ini->WriteString("Groups", "Group" + IntToStr(newIdx), Val);
                        newIdx++;
                    }
                }
            }
            __finally {
                delete ini;
                delete TempList;
            }
        }
        this->Close();
    }
}
void __fastcall TfrmGroup::AddItemClick(TObject *Sender)
{
    TfrmAddItem *dlg = new TfrmAddItem(this);
    try {

        dlg->CallerGroup = this;
        dlg->ShowModal();
    }
    __finally {
        delete dlg;
    }
}

void __fastcall TfrmGroup::DeleteItemClick(TObject *Sender)
{
    if (lvIcons->Selected == NULL) return;

    AnsiString ItemName = lvIcons->Selected->Caption;
    AnsiString FullGrpPath = GetWinDirLocal() + this->Caption;

    if (Application->MessageBox(("Delete this item '" + ItemName + "'?").c_str(), "Confirmation", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
        TIniFile *ini = new TIniFile(FullGrpPath);
        TStringList *Lines = new TStringList();
        try {
            ini->ReadSectionValues("Items", Lines);
            ini->EraseSection("Items");

            int newIdx = 1;
            for (int i = 0; i < Lines->Count; i++) {
                AnsiString Key = Lines->Names[i];
                AnsiString Val = Lines->Values[Key];

                if (Val.Pos(ItemName + ",") != 1) {
                    ini->WriteString("Items", "item" + IntToStr(newIdx), Val);
                    newIdx++;
                }
            }
        }
        __finally {
            delete ini;
            delete Lines;
        }
        LoadItemsFromGrp(FullGrpPath);
    }
}

void __fastcall TfrmGroup::lvIconsContextPopup(TObject *Sender, const TPoint &MousePos, bool &Handled)
{

    TListItem *HitItem = lvIcons->GetItemAt(MousePos.x, MousePos.y);

    if (HitItem != NULL)
    {
        HitItem->Selected = true;

        AddItem->Visible = false;
        DeleteThisGroup->Visible = false;
        DeleteItem->Visible = true;
    }
    else
    {
        AddItem->Visible = true;
        DeleteThisGroup->Visible = true;
        DeleteItem->Visible = false;
    }

    TPoint ScreenPos = lvIcons->ClientToScreen(MousePos);
    PopUpMenu->Popup(ScreenPos.x, ScreenPos.y);

    Handled = true;
}

