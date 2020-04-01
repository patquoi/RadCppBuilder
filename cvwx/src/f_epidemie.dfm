object frmEpidemie: TfrmEpidemie
  Left = 0
  Top = 0
  HelpContext = 317
  BorderStyle = bsDialog
  Caption = 'Param'#232'tres de l'#39#233'pid'#233'mie'
  ClientHeight = 176
  ClientWidth = 350
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label7: TLabel
    Left = 0
    Top = 154
    Width = 350
    Height = 22
    Align = alBottom
    AutoSize = False
    Caption = 
      '  Les param'#232'tres doivent '#234'tre modifi'#233's avant de lancer la simula' +
      'tion.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ExplicitTop = 144
    ExplicitWidth = 337
  end
  object Label8: TLabel
    Left = 0
    Top = 136
    Width = 350
    Height = 18
    Align = alBottom
    AutoSize = False
    Caption = '  (*) 0 si aucune charge virale fatale'
    ExplicitTop = 135
    ExplicitWidth = 337
  end
  object GroupBox: TGroupBox
    Left = 8
    Top = 24
    Width = 249
    Height = 105
    Caption = ' '
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 19
      Width = 106
      Height = 13
      Caption = '&P'#233'riode d'#39'infectiosit'#233' :'
      FocusControl = CSpinEditInfectiosite
    end
    object Label2: TLabel
      Left = 16
      Top = 47
      Width = 111
      Height = 13
      Caption = '&Un patient 0 tous les...'
      FocusControl = CSpinEditPatientZero
    end
    object Label3: TLabel
      Left = 195
      Top = 47
      Width = 35
      Height = 13
      Caption = 'pi'#233'tons'
    end
    object Label4: TLabel
      Left = 16
      Top = 75
      Width = 108
      Height = 13
      Caption = '&Charge virale fatale* :'
      FocusControl = CSpinEditChargeViraleFatale
    end
    object Label5: TLabel
      Left = 195
      Top = 75
      Width = 46
      Height = 13
      Caption = 'infections'
    end
    object Label6: TLabel
      Left = 195
      Top = 19
      Width = 25
      Height = 13
      Caption = 'tours'
    end
    object CSpinEditInfectiosite: TCSpinEdit
      Left = 140
      Top = 16
      Width = 49
      Height = 22
      MaxValue = 999
      MinValue = 10
      TabOrder = 0
      Value = 100
    end
    object CSpinEditPatientZero: TCSpinEdit
      Left = 140
      Top = 44
      Width = 49
      Height = 22
      MaxValue = 999
      MinValue = 10
      TabOrder = 1
      Value = 100
    end
    object CSpinEditChargeViraleFatale: TCSpinEdit
      Left = 140
      Top = 72
      Width = 49
      Height = 22
      MaxValue = 100
      TabOrder = 2
      Value = 10
    end
  end
  object ButtonOk: TButton
    Left = 274
    Top = 16
    Width = 56
    Height = 25
    Caption = 'Vu'
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = ButtonOkClick
  end
  object ButtonAnnuler: TButton
    Left = 274
    Top = 55
    Width = 56
    Height = 25
    Cancel = True
    Caption = 'Annuler'
    ModalResult = 2
    TabOrder = 2
  end
  object ButtonAide: TButton
    Left = 274
    Top = 94
    Width = 56
    Height = 25
    Hint = 'Pour avoir de l'#39'aide (F1)'
    Caption = 'Aide'
    TabOrder = 3
    OnClick = ButtonAideClick
  end
  object CheckBoxActiver: TCheckBox
    Left = 8
    Top = 6
    Width = 106
    Height = 17
    Caption = 'Activer l'#39#233'pid'#233'mie '
    TabOrder = 4
    OnClick = CheckBoxActiverClick
  end
end
