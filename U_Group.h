#ifndef U_GroupH
#define U_GroupH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>

class TfrmGroup : public TForm {
__published:
    TListView *lvIcons;
    TImageList *imgIcons;
    TPopupMenu *PopUpMenu;
    TMenuItem *AddItem;
    TMenuItem *DeleteThisGroup;
    TMenuItem *DeleteItem;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall lvIconsDblClick(TObject *Sender);
    void __fastcall lvIconsDeletion(TObject *Sender, TListItem *Item);
    void __fastcall DeleteThisGroupClick(TObject *Sender);
    void __fastcall AddItemClick(TObject *Sender);
    void __fastcall lvIconsContextPopup(TObject *Sender, const TPoint &MousePos, bool &Handled);
    void __fastcall DeleteItemClick(TObject *Sender);
private:
    AnsiString __fastcall GetWinDirLocal();
public:
    void __fastcall LoadItemsFromGrp(AnsiString FileName);
    __fastcall TfrmGroup(TComponent* Owner);
};
extern PACKAGE TfrmGroup *frmGroup;
#endif
