object frmAffDistArretsTram: TfrmAffDistArretsTram
  Left = 591
  Top = 0
  HelpContext = 642
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSizeToolWin
  Caption = ' '
  ClientHeight = 76
  ClientWidth = 156
  Color = clBtnFace
  Constraints.MaxWidth = 172
  Constraints.MinWidth = 172
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
    Top = 0
    Width = 156
    Height = 76
    Align = alClient
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
    ExplicitWidth = 164
    ExplicitHeight = 81
    RowHeights = (
      20
      20
      20
      20)
  end
end
