/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/

#include <vcl.h>
#include <windows.h>
#include <shellapi.h>
#pragma hdrstop

#include "U_Background.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBackground *FormBackground;

extern "C" __stdcall void SHShutDownDialog(HWND hwnd);

__fastcall TFormBackground::TFormBackground(TComponent* Owner): TForm(Owner)
{
    BorderStyle = bsNone;
    Left = 0;
    Top = 0;
    Width = Screen->Width;
    Height = Screen->Height;
}
void __fastcall TFormBackground::WMMouseActivate(TMessage &Message)
{
    // MA_NOACTIVATE: Terima klik mouse, tapi jangan aktifkan/bawa jendela ke depan
    Message.Result = MA_NOACTIVATE;
}
void __fastcall TFormBackground::CreateParams(Controls::TCreateParams &Params)
{
    TForm::CreateParams(Params);
    
    // Hilangkan caption dan border
    Params.Style &= ~WS_CAPTION;
    Params.Style &= ~WS_THICKFRAME;
    
    // Sembunyikan dari taskbar
    Params.ExStyle |= WS_EX_TOOLWINDOW;
    
    // Gunakan FindWindow untuk mendapatkan Handle Desktop Shell
    HWND hShell = FindWindow("Progman", NULL);
    if (hShell != NULL)
    {
        Params.WndParent = hShell;
    }
    else 
    {
        // Fallback jika Progman tidak ditemukan
        Params.WndParent = GetDesktopWindow();
    }
}
void __fastcall TFormBackground::FormShow(TObject *Sender)
{
    SetWindowPos(Handle, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

}

void __fastcall TFormBackground::ToolButton2Click(TObject *Sender)
{
    typedef void (__stdcall *PSHShutDownDialog)(HWND);

    HINSTANCE hShell = LoadLibrary("shell32.dll");
    if (hShell) {
        // Ordinal 60 adalah SHShutDownDialog
        PSHShutDownDialog SHShutDownDialog = (PSHShutDownDialog)GetProcAddress(hShell, (LPCSTR)60);
        if (SHShutDownDialog) {
            SHShutDownDialog(Handle);
        }
        FreeLibrary(hShell);
    }
}


void __fastcall TFormBackground::Timer1Timer(TObject *Sender)
{
    AnsiString TimeStr = FormatDateTime("dd-m-yy hh:mm:ss", Now());
    PanelDateTime->Caption = TimeStr;

}


