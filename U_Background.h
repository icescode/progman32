/*
  Replication progman 3.11 to windows 32 bit
  CopyLeft MIT License Hardiyanto April 2026
*/

#ifndef U_BackgroundH
#define U_BackgroundH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>

class TFormBackground : public TForm
{
__published:
    TToolBar *ToolBar1;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TImageList *ImageList1;
    TToolButton *ToolButton3;
    TPanel *PanelDateTime;
    TTimer *Timer1;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ToolButton2Click(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
private:
    void __fastcall CreateParams(Controls::TCreateParams &Params);
    void __fastcall WMMouseActivate(TMessage &Message);
public:		
    __fastcall TFormBackground(TComponent* Owner);

    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_MOUSEACTIVATE, TMessage, WMMouseActivate)
    END_MESSAGE_MAP(TForm)
};

extern PACKAGE TFormBackground *FormBackground;

#endif
