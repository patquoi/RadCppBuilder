object frmRecords: TfrmRecords
  Left = 158
  Top = 83
  ActiveControl = ButtonOk
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Records'
  ClientHeight = 463
  ClientWidth = 473
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 15
    Top = 17
    Width = 30
    Height = 13
    Caption = '&S'#233'rie :'
    FocusControl = ComboBoxSerie
  end
  object RadioGroupTypeRecord: TRadioGroup
    Left = 200
    Top = 1
    Width = 265
    Height = 38
    Caption = 'Score '
    Columns = 2
    ItemIndex = 1
    Items.Strings = (
      'de la &partie'
      'du &niveau')
    TabOrder = 1
    OnClick = RadioGroupTypeRecordClick
  end
  object RadioGroupReinitialisation: TRadioGroup
    Left = 8
    Top = 336
    Width = 457
    Height = 81
    Caption = ' &R'#233'initialiser les records '
    Color = clBtnFace
    ItemIndex = 0
    Items.Strings = (
      'Non'
      'Oui, les records de ce niveau'
      'Oui, les records de niveaux et de parties de cette s'#233'rie'
      'Oui, tous les records de toutes les s'#233'ries')
    ParentColor = False
    TabOrder = 5
    OnClick = RadioGroupReinitialisationClick
  end
  object StringGrid: TStringGrid
    Left = 8
    Top = 96
    Width = 457
    Height = 235
    DefaultColWidth = 20
    DefaultRowHeight = 20
    RowCount = 11
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
    ParentFont = False
    ScrollBars = ssNone
    TabOrder = 4
    OnClick = StringGridClick
    OnEnter = StringGridEnter
    ColWidths = (
      20
      234
      46
      33
      115)
  end
  object ButtonOk: TButton
    Left = 96
    Top = 428
    Width = 81
    Height = 25
    Hint = 
      'Applique les modifications demand'#233'es et ferme la fen'#234'tre des rec' +
      'ords'
    Caption = '&Vu && appliqu'#233
    Default = True
    ModalResult = 1
    ParentShowHint = False
    ShowHint = True
    TabOrder = 6
    OnClick = ButtonOkClick
  end
  object ButtonAnnuler: TButton
    Left = 272
    Top = 428
    Width = 75
    Height = 25
    Hint = 
      'N'#39'effectue pas les modifications demand'#233'es et ferme la fen'#234'tre d' +
      'es records'
    Cancel = True
    Caption = 'Annuler'
    Enabled = False
    ModalResult = 2
    ParentShowHint = False
    ShowHint = True
    TabOrder = 8
  end
  object ComboBoxSerie: TComboBox
    Left = 48
    Top = 14
    Width = 145
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Sorted = True
    TabOrder = 0
    OnChange = ComboBoxSerieChange
  end
  object ComboBoxNiveau: TComboBox
    Left = 409
    Top = 12
    Width = 45
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Sorted = True
    TabOrder = 2
    OnChange = ComboBoxNiveauChange
  end
  object ButtonAppliquer: TButton
    Left = 187
    Top = 428
    Width = 75
    Height = 25
    Hint = 'Applique les modifications demand'#233'es'
    Caption = 'Appli&quer'
    Enabled = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 7
    OnClick = ButtonOkClick
  end
  object PanelNvEntree: TPanel
    Left = 9
    Top = 40
    Width = 456
    Height = 53
    BevelOuter = bvNone
    TabOrder = 3
    Visible = False
    object LabelPos: TLabel
      Left = 4
      Top = 33
      Width = 14
      Height = 14
      Caption = ' 0'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelScore: TLabel
      Left = 259
      Top = 33
      Width = 42
      Height = 14
      Caption = '000000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelDateHeure: TLabel
      Left = 340
      Top = 33
      Width = 112
      Height = 14
      Caption = 'JJ/MM/AAAA hh:mm'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelNvEntree: TLabel
      Left = 5
      Top = 11
      Width = 5
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelDelaiOuNiv: TLabel
      Left = 307
      Top = 33
      Width = 28
      Height = 14
      Caption = '0000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object EditNom: TEdit
      Left = 22
      Top = 30
      Width = 234
      Height = 21
      Cursor = crIBeam
      TabOrder = 0
      OnChange = EditNomChange
    end
  end
  object Timer: TTimer
    Interval = 200
    OnTimer = TimerTimer
    Left = 432
    Top = 65512
  end
end
