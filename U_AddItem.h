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
class TFormGroup;

class TFormAddItem : public TForm
{
__published:
    TEdit *FieldPath;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *FieldTitle;
    TButton *ButtonCancel;
    TButton *ButtonSave;
    TSpeedButton *ButtonOpenFileDialog;
    TOpenDialog *OpenDialog;
    void __fastcall ButtonCancelClick(TObject *Sender);
    void __fastcall ButtonSaveClick(TObject *Sender);
    void __fastcall ButtonOpenFileDialogClick(TObject *Sender);
private:	
    AnsiString __fastcall FormatTitle(AnsiString FileName);
    AnsiString __fastcall GetCurAppDir();
public:
    __fastcall TFormAddItem(TComponent* Owner);
    TFormGroup *CallerGroup;
};
extern PACKAGE TFormAddItem *FormAddItem;

#endif
