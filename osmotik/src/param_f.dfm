object FormParametres: TFormParametres
  Left = 470
  Top = 265
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Param'#232'tres'
  ClientHeight = 224
  ClientWidth = 297
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object RadioGroupNbCamps: TRadioGroup
    Left = 8
    Top = 8
    Width = 105
    Height = 49
    Hint = 'Nombre de camps dirig'#233's par des joueurs et par l'#39'ordinateur.'
    Caption = ' Nombre de camps '
    Columns = 3
    Items.Strings = (
      '2'
      '3'
      '6')
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
  end
  object RadioGroupNbMaxLettresAPlacer: TRadioGroup
    Left = 120
    Top = 8
    Width = 169
    Height = 49
    Hint = 
      'Nombre maximum de lettres '#224' placer par camp et par tour sur le p' +
      'lateau de jeu.'
    Caption = ' Nombre max. de lettres '#224' placer '
    Columns = 3
    Items.Strings = (
      '6'
      '7'
      '8'
      '9'
      '10'
      '11')
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = RadioGroupNbMaxLettresAPlacerClick
  end
  object ButtonVu: TButton
    Left = 55
    Top = 183
    Width = 81
    Height = 25
    Caption = '&Vu && appliqu'#233
    Default = True
    TabOrder = 2
    OnClick = ButtonVuClick
  end
  object ButtonAnnuler: TButton
    Left = 168
    Top = 184
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Annuler'
    ModalResult = 2
    TabOrder = 3
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 64
    Width = 281
    Height = 105
    Caption = ' Taille du plateau de jeu (hexagones de c'#244't'#233') '
    TabOrder = 4
    object RadioButton7: TRadioButton
      Tag = 7
      Left = 8
      Top = 24
      Width = 113
      Height = 17
      Caption = '7 (127 hexagones)'
      TabOrder = 0
      OnClick = RadioButton7Click
    end
    object RadioButton8: TRadioButton
      Tag = 8
      Left = 8
      Top = 48
      Width = 113
      Height = 17
      Caption = '8 (169 hexagones)'
      TabOrder = 1
      OnClick = RadioButton7Click
    end
    object RadioButton9: TRadioButton
      Tag = 9
      Left = 8
      Top = 72
      Width = 113
      Height = 17
      Caption = '9 (217 hexagones)'
      TabOrder = 2
      OnClick = RadioButton7Click
    end
    object RadioButton10: TRadioButton
      Tag = 10
      Left = 128
      Top = 24
      Width = 113
      Height = 17
      Caption = '10 (271 hexagones)'
      TabOrder = 3
      OnClick = RadioButton7Click
    end
    object RadioButton11: TRadioButton
      Tag = 11
      Left = 128
      Top = 48
      Width = 113
      Height = 17
      Caption = '11 (331 hexagones)'
      TabOrder = 4
      OnClick = RadioButton7Click
    end
    object RadioButton12: TRadioButton
      Tag = 12
      Left = 128
      Top = 72
      Width = 113
      Height = 17
      Caption = '12 (397 hexagones)'
      TabOrder = 5
      OnClick = RadioButton7Click
    end
  end
end
