/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/
#ifndef U_CreateGroupH
#define U_CreateGroupH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

class TFormCreateGroup : public TForm
{
__published:
    TEdit *FieldTitle;
    TButton *ButtonCancel;
    TButton *ButtonSave;
    TLabel *Label1;

    void __fastcall ButtonCancelClick(TObject *Sender);
    void __fastcall ButtonSaveClick(TObject *Sender);

private:
    AnsiString __fastcall TFormCreateGroup::GetCurAppDir();

public:		
    __fastcall TFormCreateGroup(TComponent* Owner);
};
extern PACKAGE TFormCreateGroup *FormCreateGroup;
#endif
