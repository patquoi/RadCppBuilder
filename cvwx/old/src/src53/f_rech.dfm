object frmRecherche: TfrmRecherche
  Left = 0
  Top = 0
  HelpContext = 65
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsToolWindow
  Caption = 'Recherche'
  ClientHeight = 408
  ClientWidth = 223
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = True
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 161
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
    Left = 109
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
    Left = 167
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
  object RadioButtonParking: TRadioButton
    Left = 8
    Top = 30
    Width = 73
    Height = 17
    Caption = '&Parking n'#176
    TabOrder = 3
    OnClick = RadioButtonClick
  end
  object CSpinEditParking: TCSpinEdit
    Left = 109
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
    OnChange = CSpinEditParkingChange
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
    Left = 109
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
    Left = 167
    Top = 109
    Width = 51
    Height = 29
    Cancel = True
    Caption = '&Vu'
    Default = True
    TabOrder = 29
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
    Left = 109
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
    Left = 109
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
    Caption = 'Pi'#233't&on n'#176
    TabOrder = 9
    OnClick = RadioButtonClick
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 389
    Width = 223
    Height = 19
    Panels = <>
    SimplePanel = True
    SizeGrip = False
  end
  object ButtonAide: TButton
    Left = 167
    Top = 181
    Width = 50
    Height = 29
    Caption = '&Aide'
    TabOrder = 30
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
    Left = 109
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
    Left = 109
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
    Left = 109
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
    Left = 109
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
    Width = 97
    Height = 17
    Caption = 'Ta&xi n'#176
    TabOrder = 19
    OnClick = RadioButtonClick
  end
  object CSpinEditTaxi: TCSpinEdit
    Left = 109
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
    Left = 109
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
    Left = 109
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
  object RadioButtonPlacePark: TRadioButton
    Left = 8
    Top = 294
    Width = 97
    Height = 17
    Caption = 'Place par&king n'#176
    TabOrder = 25
    OnClick = RadioButtonClick
  end
  object CSpinEditPlacePark: TCSpinEdit
    Left = 109
    Top = 292
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
    TabOrder = 26
    Value = 1
    OnChange = CSpinEditPlaceParkChange
  end
  object RadioButtonFilePark: TRadioButton
    Left = 8
    Top = 318
    Width = 97
    Height = 17
    Caption = 'File parkin&g n'#176
    TabOrder = 27
    OnClick = RadioButtonClick
  end
  object CSpinEditFilePark: TCSpinEdit
    Left = 109
    Top = 316
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
    TabOrder = 28
    Value = 1
    OnChange = CSpinEditFileParkChange
  end
  object RadioButtonVehlib: TRadioButton
    Left = 8
    Top = 342
    Width = 97
    Height = 17
    Caption = 'Vehlib n'#176
    TabOrder = 32
    OnClick = RadioButtonClick
  end
  object CSpinEditVehlib: TCSpinEdit
    Left = 109
    Top = 340
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
    TabOrder = 33
    Value = 1
    OnChange = CSpinEditVehlibChange
  end
  object RadioButtonPlaceVehlib: TRadioButton
    Left = 8
    Top = 366
    Width = 97
    Height = 17
    Caption = 'Place Vehlib n'#176
    TabOrder = 34
    OnClick = RadioButtonClick
  end
  object CSpinEditPlaceVehlib: TCSpinEdit
    Left = 109
    Top = 364
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
    TabOrder = 35
    Value = 1
    OnChange = CSpinEditPlaceVehlibChange
  end
end
