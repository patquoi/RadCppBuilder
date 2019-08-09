object frmParamTaxi: TfrmParamTaxi
  Left = 405
  Top = 330
  HelpContext = 3123
  ActiveControl = CSpinEditNbMaxPersonnesTaxi
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'Param'#232'tres des taxis'
  ClientHeight = 198
  ClientWidth = 269
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
    Width = 93
    Height = 13
    Caption = 'Capacit'#233' d'#39'un &taxi...'
    FocusControl = CSpinEditNbMaxPersonnesTaxi
  end
  object Label22: TLabel
    Left = 215
    Top = 13
    Width = 49
    Height = 13
    Caption = 'personnes'
  end
  object GroupBox: TGroupBox
    Left = 8
    Top = 38
    Width = 255
    Height = 116
    Caption = ' Param'#232'tres des pi'#233'tons '
    TabOrder = 1
    object LabelNbCasesMaxPsgPtn: TLabel
      Left = 10
      Top = 22
      Width = 156
      Height = 13
      Caption = '&D'#233'tecte une file de taxis jusqu'#39#224' :'
      FocusControl = CSpinEditNbCasesMaxPlaceTaxi
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label23: TLabel
      Left = 216
      Top = 22
      Width = 28
      Height = 13
      Caption = 'cases'
    end
    object Label24: TLabel
      Left = 217
      Top = 66
      Width = 23
      Height = 13
      Caption = 'tours'
    end
    object Label17: TLabel
      Left = 10
      Top = 66
      Width = 110
      Height = 13
      Caption = '&Attend un taxi jusqu'#39#224'...'
      FocusControl = CSpinEditNbMaxToursAttente
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabelProbaPsgPt: TLabel
      Left = 10
      Top = 44
      Width = 116
      Height = 13
      Caption = '&Probabilit'#233' de s'#39'y diriger :'
      FocusControl = CSpinEditProbaDirPlaceTaxi
    end
    object Label25: TLabel
      Left = 216
      Top = 44
      Width = 8
      Height = 13
      Caption = '%'
    end
    object Label26: TLabel
      Left = 10
      Top = 88
      Width = 155
      Height = 13
      Caption = 'Pro&babilit'#233' descente demand'#233'e :'
      FocusControl = CSpinEditProbaArretDmd
    end
    object Label27: TLabel
      Left = 216
      Top = 88
      Width = 8
      Height = 13
      Caption = '%'
    end
    object CSpinEditNbCasesMaxPlaceTaxi: TCSpinEdit
      Left = 171
      Top = 19
      Width = 42
      Height = 22
      MaxValue = 10
      TabOrder = 0
      Value = 3
      OnChange = CSpinEditParametresChange
    end
    object CSpinEditNbMaxToursAttente: TCSpinEdit
      Left = 171
      Top = 63
      Width = 42
      Height = 22
      MaxValue = 50
      TabOrder = 2
      Value = 10
      OnChange = CSpinEditParametresChange
    end
    object CSpinEditProbaDirPlaceTaxi: TCSpinEdit
      Left = 171
      Top = 41
      Width = 42
      Height = 22
      Increment = 5
      MaxValue = 100
      TabOrder = 1
      Value = 50
      OnChange = CSpinEditParametresChange
    end
    object CSpinEditProbaArretDmd: TCSpinEdit
      Left = 171
      Top = 85
      Width = 42
      Height = 22
      Increment = 5
      MaxValue = 100
      TabOrder = 3
      Value = 10
      OnChange = CSpinEditParametresChange
    end
  end
  object ButtonOk: TButton
    Left = 8
    Top = 164
    Width = 57
    Height = 26
    Caption = '&Vu'
    Default = True
    TabOrder = 2
    OnClick = ButtonOkClick
  end
  object ButtonAnnuler: TButton
    Left = 72
    Top = 164
    Width = 57
    Height = 26
    Cancel = True
    Caption = 'Annuler'
    ModalResult = 2
    TabOrder = 3
  end
  object ButtonAppliquer: TButton
    Left = 136
    Top = 164
    Width = 65
    Height = 26
    Caption = 'A&ppliquer'
    Enabled = False
    TabOrder = 4
    OnClick = ButtonAppliquerClick
  end
  object ButtonAide: TButton
    Left = 208
    Top = 164
    Width = 54
    Height = 26
    Caption = 'Aide'
    TabOrder = 5
    OnClick = ButtonAideClick
  end
  object CSpinEditNbMaxPersonnesTaxi: TCSpinEdit
    Left = 179
    Top = 10
    Width = 31
    Height = 22
    MaxValue = 9
    MinValue = 1
    TabOrder = 0
    Value = 3
    OnChange = CSpinEditParametresChange
  end
end
