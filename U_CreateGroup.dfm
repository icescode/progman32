object frmCreateGroup: TfrmCreateGroup
  Left = 141
  Top = 597
  BorderStyle = bsDialog
  Caption = 'New Group'
  ClientHeight = 96
  ClientWidth = 317
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 120
  TextHeight = 16
  object fldTitle: TEdit
    Left = 8
    Top = 16
    Width = 297
    Height = 24
    TabOrder = 0
  end
  object btnCancel: TButton
    Left = 147
    Top = 57
    Width = 75
    Height = 25
    Caption = '&Cancel'
    TabOrder = 1
    OnClick = btnCancelClick
  end
  object btnSave: TButton
    Left = 232
    Top = 56
    Width = 75
    Height = 25
    Caption = '&Sa&ve'
    TabOrder = 2
    OnClick = btnSaveClick
  end
end
