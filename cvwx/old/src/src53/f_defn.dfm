object frmDefNature: TfrmDefNature
  Left = 0
  Top = 20
  Width = 247
  Height = 154
  HelpContext = 45
  HorzScrollBar.Range = 178
  VertScrollBar.Range = 93
  ActiveControl = ButtonFermer
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Nature de la zone s'#233'lectionn'#233'e'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = 11
  Font.Name = 'MS Sans Serif'
  Font.Pitch = fpVariable
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = True
  Position = poDefault
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object LabelRq: TLabel
    Left = 0
    Top = 108
    Width = 233
    Height = 13
    AutoSize = False
    Caption = '(*) des cases non utilis'#233'es par les voies de circulation'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Pitch = fpVariable
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object RadioGroupNature: TRadioGroup
    Left = 6
    Top = 6
    Width = 147
    Height = 75
    Caption = ' Nature* '
    Items.Strings = (
      '&Voies de circulation'
      '&Trottoirs'
      '&Immeubles')
    TabOrder = 0
    OnClick = RadioGroupNatureClick
  end
  object CheckBoxEcraser: TCheckBox
    Left = 15
    Top = 89
    Width = 141
    Height = 13
    Caption = '&Ecraser si autre nature'
    TabOrder = 1
  end
  object ButtonAppliquer: TButton
    Left = 164
    Top = 37
    Width = 69
    Height = 25
    Caption = 'A&ppliquer'
    Default = True
    Enabled = False
    TabOrder = 3
    OnClick = ButtonAppliquerClick
  end
  object ButtonFermer: TButton
    Left = 164
    Top = 6
    Width = 69
    Height = 25
    Cancel = True
    Caption = 'Fermer'
    TabOrder = 2
    OnClick = ButtonFermerClick
  end
  object ButtonAide: TButton
    Left = 164
    Top = 68
    Width = 69
    Height = 25
    Cancel = True
    Caption = 'Aide'
    TabOrder = 4
    OnClick = ButtonAideClick
  end
  object CheckBoxPelouse: TCheckBox
    Left = 80
    Top = 40
    Width = 66
    Height = 17
    Caption = 'Pelouse'
    Enabled = False
    TabOrder = 5
  end
end
