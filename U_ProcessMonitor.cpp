/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/

#include <vcl.h>
#pragma hdrstop

#include "U_ProcessMonitor.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TFormProcessMonitor *FormProcessMonitor;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    TListView *lv = (TListView*)lParam;

    if (IsWindowVisible(hwnd) && GetWindowTextLength(hwnd) > 0)
    {
        if (GetWindow(hwnd, GW_OWNER) == NULL)
        {
            DWORD dwStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
            if (!(dwStyle & WS_EX_TOOLWINDOW))
            {
                char title[255];
                GetWindowText(hwnd, title, sizeof(title));

                AnsiString appTitle = title;
                if (appTitle != "Program Manager" && appTitle != "Default IME" && appTitle != "MSCTFIME UI")
                {
                    TListItem *Item = lv->Items->Add();
                    Item->Caption = appTitle;
                    Item->Data = (void*)hwnd;
                    Item->SubItems->Add("Running");
                }
            }
        }
    }
    return TRUE;
}
__fastcall TFormProcessMonitor::TFormProcessMonitor(TComponent* Owner): TForm(Owner)
{
}

void __fastcall TFormProcessMonitor::RefreshProcessList()
{
    ProcessListView->Items->BeginUpdate();
    try {
        int topIdx = SendMessage(ProcessListView->Handle, LVM_GETTOPINDEX, 0, 0);

        ProcessListView->Items->Clear();
        EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)ProcessListView);

        if (ProcessListView->Items->Count > topIdx)
        {
            ProcessListView->Items->Item[ProcessListView->Items->Count - 1]->MakeVisible(false);
            ProcessListView->Items->Item[topIdx]->MakeVisible(false);
        }
    }
    __finally {
        ProcessListView->Items->EndUpdate();
    }
}

void __fastcall TFormProcessMonitor::FormShow(TObject *Sender)
{
    ProcessListView->ViewStyle = vsReport;
    ProcessListView->ReadOnly = true;
    ProcessListView->RowSelect = true;

    ProcessListView->Columns->Clear();
    TListColumn *col = ProcessListView->Columns->Add();
    col->Caption = "Application Name";
    col->Width = 300;

    TListColumn *status = ProcessListView->Columns->Add();
    status->Caption = "Status";
    status->Width = 100;

    TimerRefresh->Interval = 2000;
    TimerRefresh->Enabled = true;

    RefreshProcessList();
}

void __fastcall TFormProcessMonitor::FormClose(TObject *Sender,TCloseAction &Action)
{
    Action = caFree;
}

void __fastcall TFormProcessMonitor::ProcessListViewDblClick(
      TObject *Sender)
{
    if (ProcessListView->Selected)
    {
        HWND targetHWnd = (HWND)ProcessListView->Selected->Data;

        if (IsWindow(targetHWnd))
        {
            if (IsIconic(targetHWnd)) {
                ShowWindow(targetHWnd, SW_RESTORE);
            }
            SetForegroundWindow(targetHWnd);
        }
        else {
            Application->MessageBox("Application is no longer running.", "Info", MB_OK);
            RefreshProcessList();
        }
    }
}

void __fastcall TFormProcessMonitor::TimerRefreshTimer(TObject *Sender)
{
    RefreshProcessList();
}

