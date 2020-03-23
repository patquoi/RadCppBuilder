object frmRecherche: TfrmRecherche
  Left = 0
  Top = 0
  HelpContext = 65
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsToolWindow
  Caption = 'Recherche'
  ClientHeight = 316
  ClientWidth = 208
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  HelpFile = 'cvw.hlp'
  OldCreateOrder = True
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 145
    Top = 7
    Width = 3
    Height = 13
    Caption = ','
  end
  object RadioButtonCoordonnees: TRadioButton
    Left = 8
    Top = 6
    Width = 84
    Height = 17
    Caption = '&Coordonn'#233'es'
    TabOrder = 0
    OnClick = RadioButtonClick
  end
  object CSpinEditX: TCSpinEdit
    Left = 93
    Top = 4
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 98
    ParentFont = False
    TabOrder = 1
    OnChange = CSpinEditXChange
  end
  object CSpinEditY: TCSpinEdit
    Left = 151
    Top = 4
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 62
    ParentFont = False
    TabOrder = 2
    OnChange = CSpinEditYChange
  end
  object RadioButtonEtape: TRadioButton
    Left = 8
    Top = 30
    Width = 65
    Height = 17
    Caption = '&Etape n'#176
    TabOrder = 3
    OnClick = RadioButtonClick
  end
  object CSpinEditEtape: TCSpinEdit
    Left = 93
    Top = 28
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 32
    MinValue = 1
    ParentFont = False
    TabOrder = 4
    Value = 1
    OnChange = CSpinEditEtapeChange
  end
  object RadioButtonFeu: TRadioButton
    Left = 8
    Top = 54
    Width = 54
    Height = 17
    Caption = '&Feu n'#176
    TabOrder = 5
    OnClick = RadioButtonClick
  end
  object CSpinEditFeu: TCSpinEdit
    Left = 93
    Top = 52
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 100
    MinValue = 1
    ParentFont = False
    TabOrder = 6
    Value = 1
    OnChange = CSpinEditFeuChange
  end
  object ButtonAnnuler: TButton
    Left = 151
    Top = 109
    Width = 51
    Height = 29
    Cancel = True
    Caption = '&Vu'
    Default = True
    TabOrder = 25
    OnClick = ButtonAnnulerClick
  end
  object RadioButtonVehicule: TRadioButton
    Left = 8
    Top = 78
    Width = 76
    Height = 17
    Caption = '&V'#233'hicule n'#176
    TabOrder = 7
    OnClick = RadioButtonClick
  end
  object CSpinEditVehicule: TCSpinEdit
    Left = 93
    Top = 76
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 1000
    MinValue = 1
    ParentFont = False
    TabOrder = 8
    Value = 1
    OnChange = CSpinEditVehiculeChange
  end
  object CSpinEditPieton: TCSpinEdit
    Left = 93
    Top = 100
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 500
    MinValue = 1
    ParentFont = False
    TabOrder = 10
    Value = 1
    OnChange = CSpinEditPietonChange
  end
  object RadioButtonPieton: TRadioButton
    Left = 8
    Top = 102
    Width = 76
    Height = 17
    Caption = '&Pi'#233'ton n'#176
    TabOrder = 9
    OnClick = RadioButtonClick
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 297
    Width = 208
    Height = 19
    Panels = <>
    SimplePanel = True
    SizeGrip = False
  end
  object ButtonAide: TButton
    Left = 151
    Top = 181
    Width = 50
    Height = 29
    Caption = '&Aide'
    TabOrder = 26
    OnClick = ButtonAideClick
  end
  object RadioButtonArretBus: TRadioButton
    Left = 8
    Top = 150
    Width = 76
    Height = 17
    Caption = '&Arr'#234't Bus n'#176
    TabOrder = 13
    OnClick = RadioButtonClick
  end
  object CSpinEditArretBus: TCSpinEdit
    Left = 93
    Top = 148
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 9
    MinValue = 1
    ParentFont = False
    TabOrder = 14
    Value = 1
    OnChange = CSpinEditArretBusChange
  end
  object CSpinEditBus: TCSpinEdit
    Left = 93
    Top = 124
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 1000
    MinValue = 1
    ParentFont = False
    TabOrder = 12
    Value = 1
    OnChange = CSpinEditBusChange
  end
  object RadioButtonBus: TRadioButton
    Left = 8
    Top = 126
    Width = 76
    Height = 17
    Caption = '&Bus n'#176
    TabOrder = 11
    OnClick = RadioButtonClick
  end
  object RadioButtonArretTram: TRadioButton
    Left = 8
    Top = 198
    Width = 82
    Height = 17
    Caption = 'A&rr'#234't Tram n'#176
    TabOrder = 17
    OnClick = RadioButtonClick
  end
  object CSpinEditArretTram: TCSpinEdit
    Left = 93
    Top = 196
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 9
    MinValue = 1
    ParentFont = False
    TabOrder = 18
    Value = 1
    OnChange = CSpinEditArretTramChange
  end
  object RadioButtonTram: TRadioButton
    Left = 8
    Top = 174
    Width = 76
    Height = 17
    Caption = '&Tram n'#176
    TabOrder = 15
    OnClick = RadioButtonClick
  end
  object CSpinEditTram: TCSpinEdit
    Left = 93
    Top = 172
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 1000
    MinValue = 1
    ParentFont = False
    TabOrder = 16
    Value = 1
    OnChange = CSpinEditTramChange
  end
  object RadioButtonTaxi: TRadioButton
    Left = 8
    Top = 222
    Width = 82
    Height = 17
    Caption = 'V'#233'h. Ta&xi n'#176
    TabOrder = 19
    OnClick = RadioButtonClick
  end
  object CSpinEditTaxi: TCSpinEdit
    Left = 93
    Top = 220
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 9
    MinValue = 1
    ParentFont = False
    TabOrder = 20
    Value = 1
    OnChange = CSpinEditTaxiChange
  end
  object RadioButtonPlaceTaxi: TRadioButton
    Left = 8
    Top = 246
    Width = 82
    Height = 17
    Caption = 'P&lace Taxi n'#176
    TabOrder = 21
    OnClick = RadioButtonClick
  end
  object CSpinEditPlaceTaxi: TCSpinEdit
    Left = 93
    Top = 244
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 9
    MinValue = 1
    ParentFont = False
    TabOrder = 22
    Value = 1
    OnChange = CSpinEditPlaceTaxiChange
  end
  object RadioButtonFileTaxi: TRadioButton
    Left = 8
    Top = 270
    Width = 82
    Height = 17
    Caption = 'F&ile Taxi n'#176
    TabOrder = 23
    OnClick = RadioButtonClick
  end
  object CSpinEditFileTaxi: TCSpinEdit
    Left = 93
    Top = 268
    Width = 52
    Height = 22
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 9
    MinValue = 1
    ParentFont = False
    TabOrder = 24
    Value = 1
    OnChange = CSpinEditFileTaxiChange
  end
end
