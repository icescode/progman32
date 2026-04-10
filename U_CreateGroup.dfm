object FormCreateGroup: TFormCreateGroup
  Left = 753
  Top = 710
  BorderStyle = bsDialog
  Caption = 'New Group'
  ClientHeight = 74
  ClientWidth = 248
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
  object Label1: TLabel
    Left = 8
    Top = 13
    Width = 26
    Height = 16
    Caption = 'Title'
  end
  object FieldTitle: TEdit
    Left = 40
    Top = 9
    Width = 201
    Height = 24
    TabOrder = 0
  end
  object ButtonCancel: TButton
    Left = 83
    Top = 42
    Width = 75
    Height = 25
    Caption = '&Cancel'
    TabOrder = 1
    OnClick = ButtonCancelClick
  end
  object ButtonSave: TButton
    Left = 168
    Top = 41
    Width = 75
    Height = 25
    Caption = '&Sa&ve'
    TabOrder = 2
    OnClick = ButtonSaveClick
  end
end
