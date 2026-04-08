/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/
#ifndef U_MainH
#define U_MainH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include "U_Group.h"

class TfrmMain : public TForm
{
__published:
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Open1;
        TMenuItem *Delete1;
        TMenuItem *Run1;
        TMenuItem *ExitWindows1;
        TMenuItem *Option1;
        TMenuItem *AutoArrange1;
        TMenuItem *MinimizeonUse1;
        TMenuItem *SaveSettingonExit1;
        TMenuItem *Window1;
        TMenuItem *Cascade1;
        TMenuItem *TileHorixzontally1;
        TMenuItem *TileVertically1;
        TMenuItem *AranggeIcons1;
        TMenuItem *Help1;
        TMenuItem *AboutOldcat1;
    TMenuItem *Reload1;
    void __fastcall Cascade1Click(TObject *Sender);
    void __fastcall TileVertically1Click(TObject *Sender);
    void __fastcall TileHorixzontally1Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Reload1Click(TObject *Sender);
    void __fastcall Open1Click(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);

private:

    int LastLayoutMode; // 0: None, 1: Cascade, 2: TileV, 3: TileH
    void __fastcall LoadItemsFromGrp(AnsiString FileName);
    TfrmGroup* __fastcall FindGroupWindow(AnsiString Caption);
    AnsiString __fastcall GetWinDir();
    void __fastcall LoadGroupsFromIni();
    void __fastcall WMExitSizeMove(TMessage &Message);
    void __fastcall ApplyMBoxLayout();

public:
    __fastcall TfrmMain(TComponent* Owner);

    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_EXITSIZEMOVE, TMessage, WMExitSizeMove)
    END_MESSAGE_MAP(TForm)
};
extern PACKAGE TfrmMain *frmMain;

#endif
