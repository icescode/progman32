#ifndef U_GroupH
#define U_GroupH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>

class TFormGroup : public TForm {
__published:
    TListView *ListViewItem;
    TImageList *ImageIcons;
    TPopupMenu *PopUpMenu;
    TMenuItem *AddItem;
    TMenuItem *DeleteThisGroup;
    TMenuItem *DeleteItem;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ListViewItemDblClick(TObject *Sender);
    void __fastcall ListViewItemDeletion(TObject *Sender, TListItem *Item);
    void __fastcall DeleteThisGroupClick(TObject *Sender);
    void __fastcall AddItemClick(TObject *Sender);
    void __fastcall ListViewItemContextPopup(TObject *Sender, const TPoint &MousePos, bool &Handled);
    void __fastcall DeleteItemClick(TObject *Sender);
private:
    AnsiString __fastcall GetCurAppDir();
public:
    void __fastcall LoadItemsFromGrp(AnsiString FileName);
    __fastcall TFormGroup(TComponent* Owner);
};
extern PACKAGE TFormGroup *FormGroup;
#endif
