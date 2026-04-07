//---------------------------------------------------------------------------

#ifndef U_AddItemH
#define U_AddItemH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmGroup;

class TfrmAddItem : public TForm
{
__published:	// IDE-managed Components
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
private:	// User declarations
    AnsiString __fastcall FormatTitle(AnsiString FileName);
    AnsiString __fastcall GetWinDir();
public:		// User declarations
    __fastcall TfrmAddItem(TComponent* Owner);
    TfrmGroup *CallerGroup;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAddItem *frmAddItem;
//---------------------------------------------------------------------------
#endif
