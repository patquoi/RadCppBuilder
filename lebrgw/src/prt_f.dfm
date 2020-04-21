object frmParties: TfrmParties
  Left = 202
  Top = 80
  ActiveControl = ComboBoxNom
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Parties'
  ClientHeight = 400
  ClientWidth = 383
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object LabelNom: TLabel
    Left = 10
    Top = 8
    Width = 38
    Height = 13
    Caption = '&Joueur :'
    FocusControl = ComboBoxNom
  end
  object ComboBoxNom: TComboBox
    Left = 56
    Top = 5
    Width = 319
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnChange = ComboBoxNomChange
  end
  object StringGridParties: TStringGrid
    Left = 8
    Top = 32
    Width = 367
    Height = 235
    DefaultColWidth = 26
    DefaultRowHeight = 20
    RowCount = 11
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
    ParentFont = False
    ParentShowHint = False
    ScrollBars = ssVertical
    ShowHint = True
    TabOrder = 1
    OnDblClick = StringGridPartiesDblClick
    ColWidths = (
      26
      125
      26
      46
      119)
  end
  object ButtonOk: TButton
    Left = 65
    Top = 364
    Width = 81
    Height = 25
    Caption = '&Vu && appliqu'#233
    Default = True
    ModalResult = 1
    TabOrder = 2
    OnClick = ButtonOkClick
  end
  object ButtonAppliquer: TButton
    Left = 157
    Top = 364
    Width = 75
    Height = 25
    Caption = 'Appli&quer'
    Enabled = False
    TabOrder = 3
    OnClick = ButtonOkClick
  end
  object ButtonAnnuler: TButton
    Left = 243
    Top = 364
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Annuler'
    Enabled = False
    ModalResult = 2
    TabOrder = 4
  end
  object RadioGroupTypeSuppression: TRadioGroup
    Left = 8
    Top = 272
    Width = 368
    Height = 81
    Caption = ' Supprimer... '
    ItemIndex = 0
    Items.Strings = (
      'Aucune partie sauvegard'#233'e'
      'La partie sauvegard'#233'e s'#233'lectionn'#233'e'
      'Toutes les parties sauvegard'#233'es du joueur courant'
      'Toutes les parties sauvegard'#233'es de tous les joueurs')
    TabOrder = 5
    OnClick = RadioGroupTypeSuppressionClick
  end
end
