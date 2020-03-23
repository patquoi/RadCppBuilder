object frmInfosPieton: TfrmInfosPieton
  Left = 5
  Top = 187
  HelpContext = 68
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Propri'#233't'#233's du pi'#233'ton'
  ClientHeight = 228
  ClientWidth = 289
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
  object Label0: TLabel
    Left = 8
    Top = 8
    Width = 69
    Height = 13
    Caption = 'Coordonn'#233'es :'
  end
  object LabelCoordonnees: TLabel
    Left = 80
    Top = 8
    Width = 37
    Height = 13
    Caption = '00, 00'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object ButtonOk: TButton
    Left = 59
    Top = 196
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Vu'
    Default = True
    TabOrder = 3
    OnClick = ButtonOkClick
  end
  object RadioButtonAucunPieton: TRadioButton
    Left = 19
    Top = 32
    Width = 97
    Height = 17
    Caption = 'Aucun pi'#233'ton'
    Checked = True
    Enabled = False
    TabOrder = 0
    TabStop = True
  end
  object GroupBoxPieton: TGroupBox
    Left = 8
    Top = 56
    Width = 273
    Height = 129
    Caption = '                           '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Label1: TLabel
      Left = 13
      Top = 28
      Width = 48
      Height = 13
      Caption = 'Direction :'
    end
    object Label3: TLabel
      Left = 13
      Top = 60
      Width = 47
      Height = 13
      Caption = 'Situation :'
    end
    object Label4: TLabel
      Left = 13
      Top = 76
      Width = 99
      Height = 13
      Caption = 'Distance parcourue :'
    end
    object LabelSituation: TLabel
      Left = 251
      Top = 60
      Width = 5
      Height = 13
      Alignment = taRightJustify
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelParcours: TLabel
      Left = 237
      Top = 76
      Width = 19
      Height = 13
      Alignment = taRightJustify
      Caption = '0,0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelDirection: TLabel
      Left = 251
      Top = 29
      Width = 5
      Height = 13
      Alignment = taRightJustify
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 13
      Top = 44
      Width = 43
      Height = 13
      Caption = 'Position :'
    end
    object LabelPosition: TLabel
      Left = 251
      Top = 44
      Width = 5
      Height = 13
      Alignment = taRightJustify
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 13
      Top = 92
      Width = 78
      Height = 13
      Caption = 'Bus/Tram/Taxi :'
    end
    object LabelBusTramTaxi: TLabel
      Left = 200
      Top = 92
      Width = 56
      Height = 13
      Alignment = taRightJustify
      Caption = '0 (00, 00)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 13
      Top = 108
      Width = 156
      Height = 13
      Caption = 'Arr'#234't de bus ou tram/File de taxi :'
    end
    object LabelArretBusTramFileTaxi: TLabel
      Left = 200
      Top = 108
      Width = 56
      Height = 13
      Alignment = taRightJustify
      Caption = '0 (00, 00)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object RadioButtonPietonNumero: TRadioButton
    Left = 19
    Top = 55
    Width = 77
    Height = 17
    Caption = 'Pi'#233'ton n'#176
    Enabled = False
    TabOrder = 1
  end
  object ButtonAide: TButton
    Left = 144
    Top = 196
    Width = 75
    Height = 25
    Caption = '&Aide'
    TabOrder = 4
    OnClick = ButtonAideClick
  end
end
