object frmParamVehlib: TfrmParamVehlib
  Left = 766
  Top = 422
  HelpContext = 3124
  ActiveControl = CSpinEditNbMaxPersonnesVehlib
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'Param'#232'tres des vehlibs'
  ClientHeight = 194
  ClientWidth = 295
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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label21: TLabel
    Left = 19
    Top = 13
    Width = 105
    Height = 13
    Caption = 'Capacit'#233' d'#39'un ve&hlib...'
    FocusControl = CSpinEditNbMaxPersonnesVehlib
  end
  object Label22: TLabel
    Left = 239
    Top = 13
    Width = 49
    Height = 13
    Caption = 'personnes'
  end
  object Label3: TLabel
    Left = 8
    Top = 136
    Width = 274
    Height = 11
    Caption = 
      '(*) '#224' 100%, les vehlibs ne peuvent pas '#234'tre emprunt'#233's faute de p' +
      'lace.'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object CSpinEditNbMaxPersonnesVehlib: TCSpinEdit
    Left = 203
    Top = 10
    Width = 31
    Height = 22
    MaxValue = 9
    MinValue = 1
    TabOrder = 0
    Value = 3
    OnChange = CSpinEditParametresChange
  end
  object GroupBox: TGroupBox
    Left = 8
    Top = 38
    Width = 281
    Height = 96
    Caption = ' Param'#232'tres des pi'#233'tons '
    TabOrder = 1
    object LabelNbCasesMaxPsgPtn: TLabel
      Left = 10
      Top = 22
      Width = 176
      Height = 13
      Caption = '&D'#233'tecte une place de vehlib jusqu'#39#224' :'
      FocusControl = CSpinEditNbCasesMaxPlaceVehlib
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label23: TLabel
      Left = 240
      Top = 22
      Width = 28
      Height = 13
      Caption = 'cases'
    end
    object LabelProbaVehlib: TLabel
      Left = 10
      Top = 44
      Width = 116
      Height = 13
      Caption = 'Probabilit'#233' de s'#39'&y diriger :'
      FocusControl = CSpinEditProbaDirPlaceVehlib
    end
    object Label25: TLabel
      Left = 240
      Top = 44
      Width = 8
      Height = 13
      Caption = '%'
    end
    object Label1: TLabel
      Left = 10
      Top = 66
      Width = 161
      Height = 13
      Caption = 'Tau&x* de remplissage des places :'
      FocusControl = CSpinEditTauxRemplissage
    end
    object Label2: TLabel
      Left = 240
      Top = 66
      Width = 8
      Height = 13
      Caption = '%'
    end
    object CSpinEditNbCasesMaxPlaceVehlib: TCSpinEdit
      Left = 195
      Top = 19
      Width = 42
      Height = 22
      MaxValue = 10
      TabOrder = 0
      Value = 3
      OnChange = CSpinEditParametresChange
    end
    object CSpinEditProbaDirPlaceVehlib: TCSpinEdit
      Left = 195
      Top = 41
      Width = 42
      Height = 22
      Increment = 5
      MaxValue = 100
      TabOrder = 1
      Value = 50
      OnChange = CSpinEditParametresChange
    end
    object CSpinEditTauxRemplissage: TCSpinEdit
      Left = 195
      Top = 63
      Width = 42
      Height = 22
      Increment = 5
      MaxValue = 100
      TabOrder = 2
      Value = 88
      OnChange = CSpinEditParametresChange
    end
  end
  object ButtonOk: TButton
    Left = 8
    Top = 156
    Width = 57
    Height = 26
    Caption = '&Vu'
    Default = True
    TabOrder = 2
    OnClick = ButtonOkClick
  end
  object ButtonAnnuler: TButton
    Left = 72
    Top = 156
    Width = 57
    Height = 26
    Cancel = True
    Caption = 'Annuler'
    ModalResult = 2
    TabOrder = 3
  end
  object ButtonAppliquer: TButton
    Left = 136
    Top = 156
    Width = 65
    Height = 26
    Caption = 'A&ppliquer'
    Enabled = False
    TabOrder = 4
    OnClick = ButtonAppliquerClick
  end
  object ButtonAide: TButton
    Left = 208
    Top = 156
    Width = 54
    Height = 26
    Caption = 'Aide'
    TabOrder = 5
    OnClick = ButtonAideClick
  end
end
