object FormNomTop10: TFormNomTop10
  Left = 777
  Top = 652
  BorderStyle = bsDialog
  Caption = 'Vous '#234'tes dans le Top 10'
  ClientHeight = 73
  ClientWidth = 241
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 11
    Width = 86
    Height = 13
    Caption = 'Entrez votre nom :'
  end
  object EditNom: TEdit
    Left = 104
    Top = 7
    Width = 121
    Height = 24
    CharCase = ecUpperCase
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    MaxLength = 8
    ParentFont = False
    TabOrder = 0
    OnChange = EditNomChange
  end
  object ButtonOK: TButton
    Left = 32
    Top = 40
    Width = 75
    Height = 25
    Caption = 'Accepter'
    Default = True
    Enabled = False
    ModalResult = 1
    TabOrder = 1
  end
  object ButtonAnnuler: TButton
    Left = 136
    Top = 40
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Annuler'
    ModalResult = 2
    TabOrder = 2
  end
end
