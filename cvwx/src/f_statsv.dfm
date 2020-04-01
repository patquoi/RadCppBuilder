object frmStatsVehicules: TfrmStatsVehicules
  Left = 192
  Top = 108
  HelpContext = 62
  ActiveControl = ButtonFermer
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  ClientHeight = 351
  ClientWidth = 490
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StringGridCoordParkings: TStringGrid
    Left = 8
    Top = 8
    Width = 98
    Height = 235
    Hint = 'Coordonn'#233'es des '#233'tapes'
    ColCount = 2
    DefaultColWidth = 26
    DefaultRowHeight = 20
    RowCount = 2
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Courier New'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
    ParentFont = False
    ParentShowHint = False
    ScrollBars = ssVertical
    ShowHint = True
    TabOrder = 0
    ColWidths = (
      26
      52)
  end
  object ButtonFermer: TButton
    Left = 20
    Top = 264
    Width = 75
    Height = 25
    Caption = '&Vu'
    Default = True
    TabOrder = 1
    OnClick = ButtonFermerClick
  end
  object TabControl: TTabControl
    Left = 112
    Top = 8
    Width = 372
    Height = 336
    TabOrder = 2
    Tabs.Strings = (
      'Nb.cases entre le + long et le + court'
      'Nb.tours entre le + lent et le + rapide')
    TabIndex = 0
    OnChange = TabControlChange
    object StringGridStatsVehicules: TStringGrid
      Left = 2
      Top = 22
      Width = 367
      Height = 311
      Hint = 'Etape de d'#233'part en abscisse et '#233'tape d'#39'arriv'#233'e en ordonn'#233'e'
      ColCount = 2
      DefaultColWidth = 28
      DefaultRowHeight = 20
      RowCount = 2
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Courier New'
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
    end
  end
  object ButtonAide: TButton
    Left = 20
    Top = 296
    Width = 75
    Height = 25
    Caption = '&Aide'
    TabOrder = 3
    OnClick = ButtonAideClick
  end
end
