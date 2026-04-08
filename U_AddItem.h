/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/
#ifndef U_AddItemH
#define U_AddItemH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
class TfrmGroup;

class TfrmAddItem : public TForm
{
__published:	
    TEdit *fldPath;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *fldTitle;
    TButton *btnCancel;
    TButton *btnSave;
    TSpeedButton *btnOpenFileDialog;
    TOpenDialog *openDialog;
    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall btnSaveClick(TObject *Sender);
    void __fastcall btnOpenFileDialogClick(TObject *Sender);
private:	
    AnsiString __fastcall FormatTitle(AnsiString FileName);
    AnsiString __fastcall GetWinDir();
public:		
    __fastcall TfrmAddItem(TComponent* Owner);
    TfrmGroup *CallerGroup;
};
extern PACKAGE TfrmAddItem *frmAddItem;

#endif
