object FormGroup: TFormGroup
  Left = 190
  Top = 287
  Width = 445
  Height = 294
  Caption = 'Group'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 120
  TextHeight = 16
  object ListViewItem: TListView
    Left = 0
    Top = 0
    Width = 437
    Height = 266
    Align = alClient
    Columns = <>
    IconOptions.AutoArrange = True
    LargeImages = ImageIcons
    ReadOnly = True
    TabOrder = 0
    OnContextPopup = ListViewItemContextPopup
    OnDblClick = ListViewItemDblClick
    OnDeletion = ListViewItemDeletion
  end
  object ImageIcons: TImageList
    Height = 32
    Width = 32
    Left = 128
    Top = 48
  end
  object PopUpMenu: TPopupMenu
    Left = 224
    Top = 112
    object DeleteItem: TMenuItem
      Caption = 'Delete Item'
      OnClick = DeleteItemClick
    end
    object AddItem: TMenuItem
      Caption = 'Add Item'
      OnClick = AddItemClick
    end
    object DeleteThisGroup: TMenuItem
      Caption = 'Delete This Group'
      OnClick = DeleteThisGroupClick
    end
  end
end
