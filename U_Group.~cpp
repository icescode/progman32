//---------------------------------------------------------------------------

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
    imgIcons->Clear(); // WAJIB: Kosongkan ImageList agar icon sinkron dengan item

    try {
        ini->ReadSectionValues("Items", Lines);

        for (int i = 0; i < Lines->Count; i++) {
            AnsiString RawValue = Lines->Values[Lines->Names[i]];
            if (RawValue.Trim() == "") continue;

            // Parsing: Nama, Path, IconIndex
            int p1 = RawValue.Pos(",");
            AnsiString Title = RawValue.SubString(1, p1 - 1);
            AnsiString Remainder = RawValue.SubString(p1 + 1, RawValue.Length());
            int p2 = Remainder.LastDelimiter(",");
            
            AnsiString FullPath = (p2 > 0) ? Remainder.SubString(1, p2 - 1).Trim() : Remainder.Trim();

            // --- EKSTRAK ICON DARI FILE EXE KE IMAGELIST ---
            HICON hIcon = ExtractIcon(HInstance, FullPath.c_str(), 0);
            int NewIconIndex = -1;
            
            if ((int)hIcon > 1) {
                TIcon *ico = new TIcon();
                ico->Handle = hIcon;
                NewIconIndex = imgIcons->AddIcon(ico); // Tambah ke ImageList
                delete ico;
            }

            // Masukkan ke ListView
            TListItem *Item = lvIcons->Items->Add();
            Item->Caption = Title;
            Item->ImageIndex = NewIconIndex; // Pakai index baru hasil ekstrasi
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
        // Cara khusus menjalankan Control Panel Applet
        // Format: control.exe filename.cpl
        ShellExecute(Handle, "open", "control.exe", FilePath.c_str(), NULL, SW_SHOWNORMAL);
    }
    else
    {
        // Cara standar untuk .exe
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
    
    if (Application->MessageBox("Hapus Group dan File Fisik?", "Konfirmasi", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
        // --- BUG 2: HAPUS FILE .GRP DARI DISK ---
        if (FileExists(FullGrpPath)) {
            DeleteFile(FullGrpPath); 
        }

        // --- BUG 1: HAPUS ENTRY DI OLDCAT.INI ---
        AnsiString IniPath = GetWinDirLocal() + "oldcat.ini";
        if (FileExists(IniPath))
        {
            TIniFile *ini = new TIniFile(IniPath);
            TStringList *TempList = new TStringList();
            try {
                ini->ReadSectionValues("Groups", TempList);
                ini->EraseSection("Groups"); // Bersihkan dulu agar urutan rapi

                int newIdx = 1;
                for (int i = 0; i < TempList->Count; i++) {
                    AnsiString Val = TempList->Values[TempList->Names[i]];
                    // Tulis ulang semua KECUALI yang sedang dihapus
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
        this->Close(); // Tutup jendela setelah dihapus
    }
}
void __fastcall TfrmGroup::AddItemClick(TObject *Sender)
{
    TfrmAddItem *dlg = new TfrmAddItem(this);
    try {
        // Berikan alamat memory jendela ini (this) ke form AddItem
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

    if (Application->MessageBox(("Hapus item '" + ItemName + "'?").c_str(), "Konfirmasi", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
        TIniFile *ini = new TIniFile(FullGrpPath);
        TStringList *Lines = new TStringList();
        try {
            // Baca semua item, hapus yang dipilih, lalu tulis ulang agar index item1, item2 urut
            ini->ReadSectionValues("Items", Lines);
            ini->EraseSection("Items");

            int newIdx = 1;
            for (int i = 0; i < Lines->Count; i++) {
                AnsiString Key = Lines->Names[i];
                AnsiString Val = Lines->Values[Key];
                
                // Jika caption (Nama) tidak sama dengan yang dihapus, simpan kembali
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
        // Refresh tampilan
        LoadItemsFromGrp(FullGrpPath);
    }
}

void __fastcall TfrmGroup::lvIconsContextPopup(TObject *Sender, const TPoint &MousePos, bool &Handled)
{
    // Cari tahu apakah ada item di bawah posisi mouse
    TListItem *HitItem = lvIcons->GetItemAt(MousePos.x, MousePos.y);

    if (HitItem != NULL) 
    {
        // KONDISI 1: Klik pada Item (Focus)
        HitItem->Selected = true; // Pastikan item terpilih
        
        AddItem->Visible = false;
        DeleteThisGroup->Visible = false;
        DeleteItem->Visible = true; // Munculkan hanya Delete Item
    }
    else 
    {
        // KONDISI 2: Klik di area kosong
        AddItem->Visible = true;
        DeleteThisGroup->Visible = true;
        DeleteItem->Visible = false; // Sembunyikan Delete Item
    }

    // Munculkan menu secara manual di posisi mouse
    TPoint ScreenPos = lvIcons->ClientToScreen(MousePos);
    PopUpMenu->Popup(ScreenPos.x, ScreenPos.y);

    // Beritahu sistem bahwa kita sudah menangani popup ini
    Handled = true;
}

