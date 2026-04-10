/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/


#ifndef U_ProcessMonitorH
#define U_ProcessMonitorH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>

class TFormProcessMonitor : public TForm
{
__published:	// IDE-managed Components
    TListView *ProcessListView;
    TTimer *TimerRefresh;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ProcessListViewDblClick(TObject *Sender);
    void __fastcall TimerRefreshTimer(TObject *Sender);

private:
    void __fastcall RefreshProcessList();
public:
    __fastcall TFormProcessMonitor(TComponent* Owner);
};

extern PACKAGE TFormProcessMonitor *FormProcessMonitor;

#endif
