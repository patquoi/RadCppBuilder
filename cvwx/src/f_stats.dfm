object frmStatistiques: TfrmStatistiques
  Left = 594
  Top = 0
  HelpContext = 611
  BorderStyle = bsSizeToolWin
  Caption = #201'volution'
  ClientHeight = 188
  ClientWidth = 192
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = True
  OnCreate = FormCreate
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBoxStats: TPaintBox
    Left = 0
    Top = 0
    Width = 192
    Height = 188
    Align = alClient
    ParentShowHint = False
    ShowHint = True
    OnPaint = PaintBoxStatsPaint
    ExplicitWidth = 200
    ExplicitHeight = 193
  end
end
