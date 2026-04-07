object frmMain: TfrmMain
  Left = 457
  Top = 345
  Width = 523
  Height = 323
  Caption = 'Program Manager'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  WindowMenu = Window1
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object MainMenu1: TMainMenu
    Left = 120
    Top = 120
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Caption = '&New Group'
        OnClick = Open1Click
      end
      object Delete1: TMenuItem
        Caption = '&Delete'
      end
      object Run1: TMenuItem
        Caption = '&Run'
      end
      object ExitWindows1: TMenuItem
        Caption = 'E&xit Windows'
      end
    end
    object Option1: TMenuItem
      Caption = '&Option'
      object AutoArrange1: TMenuItem
        Caption = '&Auto Arrange'
      end
      object MinimizeonUse1: TMenuItem
        Caption = '&Minimize on Use'
      end
      object SaveSettingonExit1: TMenuItem
        Caption = '&Save Setting on Exit'
      end
    end
    object Window1: TMenuItem
      Caption = '&Window'
      object Cascade1: TMenuItem
        Caption = '&Cascade'
        OnClick = Cascade1Click
      end
      object TileHorixzontally1: TMenuItem
        Caption = 'Tile &Horixzontally'
        OnClick = TileHorixzontally1Click
      end
      object TileVertically1: TMenuItem
        Caption = 'Tile &Vertically'
        OnClick = TileVertically1Click
      end
      object AranggeIcons1: TMenuItem
        Caption = '&Arangge Icons'
      end
      object Reload1: TMenuItem
        Caption = '&Reload'
        ShortCut = 8308
        OnClick = Reload1Click
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object AboutOldcat1: TMenuItem
        Caption = 'About Oldcat'
      end
    end
  end
end
