object frmDefVoie: TfrmDefVoie
  Left = 5
  Top = 187
  HelpContext = 41
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Priorit'#233's de la case'
  ClientHeight = 368
  ClientWidth = 290
  Color = clBtnFace
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
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 69
    Height = 13
    Caption = 'Coordonn'#233'es :'
  end
  object LabelCoordonnees: TLabel
    Left = 80
    Top = 8
    Width = 37
    Height = 13
    Caption = '00, 00'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object RadioGroupPrioriteNord: TRadioGroup
    Left = 80
    Top = 40
    Width = 130
    Height = 89
    Caption = ' Priorit'#233' &Nord '
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      #192' droite'
      'C'#233'dez-le-passage'
      'Stop'
      'Feu...')
    ParentFont = False
    TabOrder = 0
    OnClick = RadioGroupPrioriteClick
  end
  object RadioGroupPrioriteOuest: TRadioGroup
    Tag = 3
    Left = 8
    Top = 136
    Width = 130
    Height = 89
    Caption = ' Priorit'#233' &Ouest '
    Enabled = False
    ItemIndex = 0
    Items.Strings = (
      #192' droite'
      'C'#233'dez-le-passage'
      'Stop'
      'Feu...')
    TabOrder = 2
    OnClick = RadioGroupPrioriteClick
  end
  object RadioGroupPrioriteEst: TRadioGroup
    Tag = 1
    Left = 152
    Top = 136
    Width = 130
    Height = 89
    Caption = ' Priorit'#233' &Est '
    Enabled = False
    ItemIndex = 0
    Items.Strings = (
      #192' droite'
      'C'#233'dez-le-passage'
      'Stop'
      'Feu...')
    TabOrder = 4
    OnClick = RadioGroupPrioriteClick
  end
  object RadioGroupPrioriteSud: TRadioGroup
    Tag = 2
    Left = 80
    Top = 232
    Width = 130
    Height = 89
    Caption = ' Priorit'#233' &Sud'
    Enabled = False
    ItemIndex = 0
    Items.Strings = (
      #192' droite'
      'C'#233'dez-le-passage'
      'Stop'
      'Feu...')
    TabOrder = 6
    OnClick = RadioGroupPrioriteClick
  end
  object ButtonOk: TButton
    Left = 14
    Top = 334
    Width = 49
    Height = 25
    Caption = '&Vu'
    Default = True
    TabOrder = 8
    OnClick = ButtonOkClick
  end
  object ButtonAnnuler: TButton
    Left = 78
    Top = 334
    Width = 49
    Height = 25
    Cancel = True
    Caption = 'Annuler'
    TabOrder = 9
    OnClick = ButtonAnnulerClick
  end
  object BitBtnDefFeuN: TBitBtn
    Tag = 1
    Left = 136
    Top = 102
    Width = 22
    Height = 22
    Hint = 'D'#233'finit le feu Nord'
    Enabled = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = BitBtnDefFeuClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      0400000000000001000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00000000000000
      000000000000000000000000000000000AA20000000000000FF8000000000000
      AA22000000000000FF88000000000830AA22000000000880FF88000000088332
      2A220000000888888F8800000883333222200000088888888880000082A33300
      0BB3000088F888000FF800082A2A3300BB3300088F8F8800FF880082A2AA3000
      BB330088F8FF8000FF88082A2AA230033B33088F8FF880088F8882A2AA880033
      333088F8FF88008888802A2AA280000009918F8FF88000000FF8A2AA28000000
      9911F8FF88000000FF882AA28000000099118FF880000000FF88AA2800000001
      1911FF88000000088F88A280000000111110F880000000888880}
    NumGlyphs = 2
  end
  object BitBtnDefFeuO: TBitBtn
    Tag = 4
    Left = 64
    Top = 198
    Width = 22
    Height = 22
    Hint = 'D'#233'finit le feu Ouest'
    Enabled = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    OnClick = BitBtnDefFeuClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      0400000000000001000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00000000000000
      000000000000000000000000000000000AA20000000000000FF8000000000000
      AA22000000000000FF88000000000830AA22000000000880FF88000000088332
      2A220000000888888F8800000883333222200000088888888880000082A33300
      0BB3000088F888000FF800082A2A3300BB3300088F8F8800FF880082A2AA3000
      BB330088F8FF8000FF88082A2AA230033B33088F8FF880088F8882A2AA880033
      333088F8FF88008888802A2AA280000009918F8FF88000000FF8A2AA28000000
      9911F8FF88000000FF882AA28000000099118FF880000000FF88AA2800000001
      1911FF88000000088F88A280000000111110F880000000888880}
    NumGlyphs = 2
  end
  object BitBtnDefFeuE: TBitBtn
    Tag = 2
    Left = 208
    Top = 198
    Width = 22
    Height = 22
    Hint = 'D'#233'finit le feu Est'
    Enabled = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 5
    OnClick = BitBtnDefFeuClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      0400000000000001000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00000000000000
      000000000000000000000000000000000AA20000000000000FF8000000000000
      AA22000000000000FF88000000000830AA22000000000880FF88000000088332
      2A220000000888888F8800000883333222200000088888888880000082A33300
      0BB3000088F888000FF800082A2A3300BB3300088F8F8800FF880082A2AA3000
      BB330088F8FF8000FF88082A2AA230033B33088F8FF880088F8882A2AA880033
      333088F8FF88008888802A2AA280000009918F8FF88000000FF8A2AA28000000
      9911F8FF88000000FF882AA28000000099118FF880000000FF88AA2800000001
      1911FF88000000088F88A280000000111110F880000000888880}
    NumGlyphs = 2
  end
  object BitBtnDefFeuS: TBitBtn
    Tag = 3
    Left = 136
    Top = 294
    Width = 22
    Height = 22
    Hint = 'D'#233'finit le feu Sud'
    Enabled = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 7
    OnClick = BitBtnDefFeuClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      0400000000000001000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00000000000000
      000000000000000000000000000000000AA20000000000000FF8000000000000
      AA22000000000000FF88000000000830AA22000000000880FF88000000088332
      2A220000000888888F8800000883333222200000088888888880000082A33300
      0BB3000088F888000FF800082A2A3300BB3300088F8F8800FF880082A2AA3000
      BB330088F8FF8000FF88082A2AA230033B33088F8FF880088F8882A2AA880033
      333088F8FF88008888802A2AA280000009918F8FF88000000FF8A2AA28000000
      9911F8FF88000000FF882AA28000000099118FF880000000FF88AA2800000001
      1911FF88000000088F88A280000000111110F880000000888880}
    NumGlyphs = 2
  end
  object ButtonAppliquer: TButton
    Left = 142
    Top = 334
    Width = 57
    Height = 25
    Caption = '&Appliquer'
    Enabled = False
    TabOrder = 10
    OnClick = ButtonAppliquerClick
  end
  object ButtonAide: TButton
    Left = 214
    Top = 334
    Width = 57
    Height = 25
    Caption = '&Aide'
    TabOrder = 11
    OnClick = ButtonAideClick
  end
end
