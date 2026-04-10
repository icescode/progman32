object FormProcessMonitor: TFormProcessMonitor
  Left = 676
  Top = 319
  Width = 385
  Height = 302
  Caption = 'Process Monitor'
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
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object ProcessListView: TListView
    Left = 0
    Top = 0
    Width = 377
    Height = 274
    Align = alClient
    Columns = <>
    TabOrder = 0
    ViewStyle = vsReport
    OnDblClick = ProcessListViewDblClick
  end
  object TimerRefresh: TTimer
    OnTimer = TimerRefreshTimer
    Left = 136
    Top = 40
  end
end
