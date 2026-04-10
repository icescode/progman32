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

TFormGroup *FormGroup;

__fastcall TFormGroup::TFormGroup(TComponent* Owner): TForm(Owner){

}
AnsiString __fastcall TFormGroup::GetCurAppDir()
{
    AnsiString path = ExtractFilePath(Application->ExeName);

    if (path.LastDelimiter("\\") != path.Length()) {
        path = path + "\\";
    }
    return path;
}

void __fastcall TFormGroup::LoadItemsFromGrp(AnsiString FullGrpPath)
{
    if (!FileExists(FullGrpPath)) return;

    TIniFile *ini = new TIniFile(FullGrpPath);
    TStringList *Lines = new TStringList();

    ListViewItem->Items->Clear();
    ImageIcons->Clear();

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
                NewIconIndex = ImageIcons->AddIcon(ico);
                delete ico;
            }

            TListItem *Item = ListViewItem->Items->Add();
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
void __fastcall TFormGroup::FormClose(TObject *Sender, TCloseAction &Action) {

    Action = caFree;
}

void __fastcall TFormGroup::ListViewItemDblClick(TObject *Sender)
{
    if (ListViewItem->Selected == NULL || ListViewItem->Selected->SubItems->Count == 0) return;

    AnsiString FilePath = ListViewItem->Selected->SubItems->Strings[0];
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

void __fastcall TFormGroup::ListViewItemDeletion(TObject *Sender,TListItem *Item)
{
    if (Item->Data != NULL) {
        delete (AnsiString*)Item->Data;
        Item->Data = NULL;
    }
}

void __fastcall TFormGroup::DeleteThisGroupClick(TObject *Sender)
{

    AnsiString GroupFileName = this->Caption + ".grp";
    AnsiString FullGrpPath = GetCurAppDir() + GroupFileName;

    if (Application->MessageBox(("Delete the group '" + this->Caption + "' and all its items?").c_str(),
        "Confirmation", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {

        if (FileExists(FullGrpPath)) {
            if (!DeleteFile(FullGrpPath)) {
                Application->MessageBox("Could not delete physical .grp file. Check permissions.", "Error", MB_OK);
            }
        }


        AnsiString IniPath = GetCurAppDir() + "progmanx.ini";
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

                    if (Val.LowerCase() != GroupFileName.LowerCase()) {
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
void __fastcall TFormGroup::AddItemClick(TObject *Sender)
{
    TFormAddItem *dlg = new TFormAddItem(this);
    try {

        dlg->CallerGroup = this;
        dlg->ShowModal();
    }
    __finally {
        delete dlg;
    }
}

void __fastcall TFormGroup::DeleteItemClick(TObject *Sender)
{
    if (!ListViewItem->Selected) return;

    AnsiString ItemName = ListViewItem->Selected->Caption;


    AnsiString FullGrpPath = GetCurAppDir() + this->Caption + ".grp";

    if (Application->MessageBox(("Delete this item '" + ItemName + "'?").c_str(),
        "Confirmation", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
        if (!FileExists(FullGrpPath)) {
            Application->MessageBox("Group file not found!", "Error", MB_OK);
            return;
        }

        TIniFile *ini = new TIniFile(FullGrpPath);
        TStringList *Lines = new TStringList();
        try {
            ini->ReadSectionValues("Items", Lines);


            ini->EraseSection("Items");

            int newIdx = 1;
            for (int i = 0; i < Lines->Count; i++) {
                AnsiString FullLine = Lines->Strings[i];
                AnsiString Val = Lines->Values[Lines->Names[i]];

                int commaPos = Val.Pos(",");
                AnsiString NameInFile = Val.SubString(1, commaPos - 1);

                if (NameInFile != ItemName) {
                    ini->WriteString("Items", "item" + IntToStr(newIdx), Val);
                    newIdx++;
                }
            }


            delete ini;
            ini = NULL;


            LoadItemsFromGrp(FullGrpPath);
        }
        __finally {
            if (ini) delete ini;
            delete Lines;
        }
    }
}
void __fastcall TFormGroup::ListViewItemContextPopup(TObject *Sender, const TPoint &MousePos, bool &Handled)
{

    TListItem *HitItem = ListViewItem->GetItemAt(MousePos.x, MousePos.y);

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

    TPoint ScreenPos = ListViewItem->ClientToScreen(MousePos);
    PopUpMenu->Popup(ScreenPos.x, ScreenPos.y);

    Handled = true;
}

