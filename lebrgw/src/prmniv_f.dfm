object frmPrmNiveau: TfrmPrmNiveau
  Left = 192
  Top = 108
  ActiveControl = EditNomSerie
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Param'#232'tres du niveau'
  ClientHeight = 364
  ClientWidth = 208
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 79
    Height = 13
    Caption = 'Nom de la &s'#233'rie :'
  end
  object Panel1: TPanel
    Left = 8
    Top = 56
    Width = 193
    Height = 86
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 1
    object LabelNumNiv: TLabel
      Left = 8
      Top = 11
      Width = 93
      Height = 13
      Caption = '&Num'#233'ro du niveau :'
      FocusControl = CSpinEditNumNiv
    end
    object LabelNbMaxBetes: TLabel
      Left = 8
      Top = 35
      Width = 127
      Height = 13
      Caption = 'Nombre ma&ximal de b'#234'tes :'
      FocusControl = CSpinEditNbMaxBetes
    end
    object LabelTitreNbCrtBetes: TLabel
      Left = 8
      Top = 59
      Width = 127
      Height = 13
      Caption = 'Nombre de b'#234'tes plac'#233'es :'
    end
    object LabelNbCrtBetes: TLabel
      Left = 143
      Top = 59
      Width = 8
      Height = 13
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object CSpinEditNumNiv: TCSpinEdit
      Left = 140
      Top = 8
      Width = 45
      Height = 22
      MaxValue = 999
      TabOrder = 0
    end
    object CSpinEditNbMaxBetes: TCSpinEdit
      Left = 140
      Top = 32
      Width = 45
      Height = 22
      Hint = 
        'Vous ne pouvez changer le nombre maximal de b'#234'tes que si aucune ' +
        'n'#39'a '#233't'#233' plac'#233'e'
      MaxValue = 100
      MinValue = 1
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      Value = 10
      OnChange = CSpinEditNbMaxBetesChange
    end
  end
  object Panel2: TPanel
    Left = 8
    Top = 152
    Width = 193
    Height = 137
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 2
    object LabelBarre: TLabel
      Left = 8
      Top = 59
      Width = 68
      Height = 13
      Caption = '&Barre (points) :'
      FocusControl = CSpinEditBarre
    end
    object LabelDelai: TLabel
      Left = 8
      Top = 11
      Width = 98
      Height = 13
      Caption = '&D'#233'lai des tours (ms) :'
      FocusControl = CSpinEditDelai
    end
    object LabelEffet: TLabel
      Left = 8
      Top = 107
      Width = 107
      Height = 13
      Caption = '&Effet limite du curseur :'
      FocusControl = CSpinEditEffet
    end
    object LabelNbBetesACapturer: TLabel
      Left = 8
      Top = 83
      Width = 95
      Height = 13
      Caption = 'B'#234'tes '#224' &immobiliser :'
      FocusControl = CSpinEditNbBetesAImmobiliser
    end
    object LabelNbMaxTours: TLabel
      Left = 8
      Top = 35
      Width = 108
      Height = 13
      Caption = 'Nombre maxi de &tours :'
      FocusControl = CSpinEditNbMaxTours
    end
    object CSpinEditBarre: TCSpinEdit
      Left = 120
      Top = 56
      Width = 65
      Height = 22
      Increment = 100
      MaxValue = 999900
      TabOrder = 2
    end
    object CSpinEditDelai: TCSpinEdit
      Left = 120
      Top = 8
      Width = 65
      Height = 22
      Increment = 50
      MaxValue = 1000
      MinValue = 50
      TabOrder = 0
      Value = 500
    end
    object CSpinEditEffet: TCSpinEdit
      Left = 120
      Top = 104
      Width = 65
      Height = 22
      MaxValue = 500
      TabOrder = 4
      Value = 5
    end
    object CSpinEditNbBetesAImmobiliser: TCSpinEdit
      Left = 120
      Top = 80
      Width = 65
      Height = 22
      MaxValue = 99
      TabOrder = 3
      Value = 10
    end
    object CSpinEditNbMaxTours: TCSpinEdit
      Left = 120
      Top = 32
      Width = 65
      Height = 22
      Increment = 100
      MaxValue = 9999
      MinValue = 100
      TabOrder = 1
      Value = 1000
    end
  end
  object ButtonOk: TButton
    Left = 16
    Top = 329
    Width = 83
    Height = 25
    Caption = '&Vu && appliqu'#233
    Default = True
    ModalResult = 1
    TabOrder = 4
    OnClick = ButtonOkClick
  end
  object ButtonAnnuler: TButton
    Left = 110
    Top = 329
    Width = 83
    Height = 25
    Cancel = True
    Caption = 'Annuler'
    ModalResult = 2
    TabOrder = 5
  end
  object EditNomSerie: TEdit
    Left = 8
    Top = 24
    Width = 193
    Height = 21
    TabOrder = 0
  end
  object CheckBoxBordure: TCheckBox
    Left = 16
    Top = 296
    Width = 185
    Height = 17
    Caption = 'Ajouter une bordure de murs'
    Enabled = False
    TabOrder = 3
  end
end
