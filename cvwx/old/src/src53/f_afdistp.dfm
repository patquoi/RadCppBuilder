object frmAffDistParkings: TfrmAffDistParkings
  Left = 591
  Top = 0
  Width = 141
  Height = 132
  HelpContext = 63
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSizeToolWin
  Caption = ' '
  Color = clBtnFace
  Constraints.MaxWidth = 141
  Constraints.MinWidth = 141
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = True
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StringGridDistances: TStringGrid
    Left = 0
    Top = 17
    Width = 133
    Height = 81
    Align = alClient
    ColCount = 4
    DefaultColWidth = 28
    DefaultRowHeight = 20
    RowCount = 4
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Symbol'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ScrollBars = ssVertical
    ShowHint = False
    TabOrder = 0
    RowHeights = (
      20
      20
      20
      20)
  end
  object Panel: TPanel
    Left = 0
    Top = 0
    Width = 133
    Height = 17
    Align = alTop
    BevelOuter = bvNone
    Caption = 'Panel'
    TabOrder = 1
    object CheckBoxCouloirsBus: TCheckBox
      Left = 1
      Top = 0
      Width = 122
      Height = 17
      Caption = 'Avec couloirs de bus'
      TabOrder = 0
      OnClick = CheckBoxCouloirsBusClick
    end
  end
end
