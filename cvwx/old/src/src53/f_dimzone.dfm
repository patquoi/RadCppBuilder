object frmDimensionsZone: TfrmDimensionsZone
  Left = 375
  Top = 325
  HelpContext = 3111
  ActiveControl = CSpinEditNbX
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Dimensions de la zone'
  ClientHeight = 121
  ClientWidth = 276
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 66
    Height = 13
    Caption = 'Colonnes (X) :'
  end
  object Label2: TLabel
    Left = 144
    Top = 8
    Width = 57
    Height = 13
    Caption = 'x lignes (Y) :'
  end
  object CSpinEditNbX: TCSpinEdit
    Tag = 1
    Left = 76
    Top = 6
    Width = 65
    Height = 22
    TabOrder = 0
  end
  object CSpinEditNbY: TCSpinEdit
    Left = 204
    Top = 6
    Width = 65
    Height = 22
    TabOrder = 1
  end
  object ButtonCreer: TButton
    Left = 8
    Top = 85
    Width = 75
    Height = 25
    Caption = 'Cr'#233'er'
    Default = True
    TabOrder = 2
    OnClick = ButtonCreerClick
  end
  object ButtonAnnuler: TButton
    Left = 96
    Top = 85
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Annuler'
    ModalResult = 2
    TabOrder = 3
  end
  object ButtonAide: TButton
    Left = 192
    Top = 85
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Aide'
    TabOrder = 4
    OnClick = ButtonAideClick
  end
  object CheckBoxAfficherParametres: TCheckBox
    Left = 9
    Top = 36
    Width = 250
    Height = 17
    Caption = 'Afficher les param'#232'tres apr'#232's cr'#233'ation de la zone'
    Checked = True
    State = cbChecked
    TabOrder = 5
  end
  object CheckBoxGenererReseau: TCheckBox
    Left = 9
    Top = 57
    Width = 177
    Height = 17
    Caption = 'G'#233'n'#233'rer al'#233'atoirement un r'#233'seau'
    TabOrder = 6
  end
end
