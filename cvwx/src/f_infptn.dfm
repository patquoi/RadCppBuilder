object frmInfosPieton: TfrmInfosPieton
  Left = 1
  Top = 3
  HelpContext = 68
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Propri'#233't'#233's du pi'#233'ton'
  ClientHeight = 401
  ClientWidth = 289
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
    Left = 58
    Top = 364
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
    Height = 296
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
      Left = 64
      Top = 60
      Width = 192
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
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
      Left = 64
      Top = 29
      Width = 192
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
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
      Left = 64
      Top = 44
      Width = 192
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
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
      Width = 112
      Height = 13
      Caption = 'Bus/Tram/Taxi/Vehlib :'
    end
    object LabelBusTramTaxiVehlib: TLabel
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
      Width = 174
      Height = 13
      Caption = 'Arr'#234't de bus ou tram/File taxi/vehlib :'
    end
    object LabelArretBusTramFileTaxiVehlib: TLabel
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
    object GroupBoxEpidemie: TGroupBox
      Left = 13
      Top = 134
      Width = 243
      Height = 147
      Caption = '  '
      TabOrder = 0
      object Label7: TLabel
        Left = 16
        Top = 24
        Width = 36
        Height = 13
        Caption = 'Infect'#233' '
      end
      object LabelInfecte: TLabel
        Left = 203
        Top = 24
        Width = 24
        Height = 13
        Alignment = taRightJustify
        Caption = 'Non'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label8: TLabel
        Left = 16
        Top = 56
        Width = 107
        Height = 13
        Caption = 'Rang (premier, dernier)'
      end
      object LabelRangs: TLabel
        Left = 204
        Top = 56
        Width = 23
        Height = 13
        Alignment = taRightJustify
        Caption = '0, 0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label9: TLabel
        Left = 16
        Top = 72
        Width = 159
        Height = 13
        Caption = 'Tours d'#39'infection (premier, dernier)'
      end
      object LabelTours: TLabel
        Left = 204
        Top = 72
        Width = 23
        Height = 13
        Alignment = taRightJustify
        Caption = '0, 0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label10: TLabel
        Left = 16
        Top = 40
        Width = 157
        Height = 13
        Caption = 'Infections (p'#233'riodes discontinues)'
      end
      object LabelInfections: TLabel
        Left = 219
        Top = 40
        Width = 8
        Height = 13
        Alignment = taRightJustify
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label11: TLabel
        Left = 16
        Top = 88
        Width = 141
        Height = 13
        Caption = 'P'#233'riode d'#39'infectiosit'#233' entam'#233'e'
      end
      object LabelPeriodeInfectiosite: TLabel
        Left = 210
        Top = 88
        Width = 17
        Height = 13
        Alignment = taRightJustify
        Caption = '0%'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label13: TLabel
        Left = 16
        Top = 104
        Width = 62
        Height = 13
        Caption = 'Charge virale'
      end
      object LabelChargeVirale: TLabel
        Left = 219
        Top = 104
        Width = 8
        Height = 13
        Alignment = taRightJustify
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label12: TLabel
        Left = 16
        Top = 120
        Width = 129
        Height = 13
        Caption = 'Etat '#224' l'#39'issue de la p'#233'riode :'
      end
      object LabelEtatFinal: TLabel
        Left = 170
        Top = 120
        Width = 57
        Height = 13
        Alignment = taRightJustify
        Caption = 'Sain/Mort'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object CheckBoxEpidemie: TCheckBox
      Left = 28
      Top = 134
      Width = 102
      Height = 17
      Caption = 'Epid'#233'mie activ'#233'e '
      Enabled = False
      TabOrder = 1
    end
  end
  object RadioButtonPietonNumero: TRadioButton
    Left = 19
    Top = 55
    Width = 60
    Height = 17
    Caption = 'Pi'#233'ton n'#176
    Enabled = False
    TabOrder = 1
  end
  object ButtonAide: TButton
    Left = 160
    Top = 364
    Width = 75
    Height = 25
    Caption = '&Aide'
    TabOrder = 4
    OnClick = ButtonAideClick
  end
end
