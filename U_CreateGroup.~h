#ifndef U_CreateGroupH
#define U_CreateGroupH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

class TfrmCreateGroup : public TForm
{
__published:	
    TEdit *fldTitle;
    TButton *btnCancel;
    TButton *btnSave;

    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall btnSaveClick(TObject *Sender);

private:
    AnsiString __fastcall GetWinDir(); // Helper untuk cari folder Windows

public:		
    __fastcall TfrmCreateGroup(TComponent* Owner);
};
extern PACKAGE TfrmCreateGroup *frmCreateGroup;
#endif
