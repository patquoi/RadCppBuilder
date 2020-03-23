object frmStatistiques: TfrmStatistiques
  Left = 594
  Top = 0
  Width = 208
  Height = 227
  HelpContext = 611
  BorderStyle = bsSizeToolWin
  Caption = #201'volution'
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  HelpFile = 'cvw.hlp'
  OldCreateOrder = True
  OnCreate = FormCreate
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBoxStats: TPaintBox
    Left = 0
    Top = 0
    Width = 200
    Height = 200
    Hint = 'Sortis en jaune ; D'#233'plac'#233's en vert et Arriv'#233's en rouge'
    Align = alClient
    ParentShowHint = False
    ShowHint = True
    OnPaint = PaintBoxStatsPaint
  end
end
