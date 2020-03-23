object frmInfosVehicule: TfrmInfosVehicule
  Left = 5
  Top = 187
  HelpContext = 66
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Propri'#233't'#233's du v'#233'hicule'
  ClientHeight = 371
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
    Top = 340
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Vu'
    Default = True
    TabOrder = 3
    OnClick = ButtonOkClick
  end
  object RadioButtonAucunVehicule: TRadioButton
    Left = 19
    Top = 32
    Width = 97
    Height = 17
    Caption = 'Aucun v'#233'hicule'
    Checked = True
    Enabled = False
    TabOrder = 0
    TabStop = True
  end
  object GroupBoxVehicule: TGroupBox
    Left = 8
    Top = 56
    Width = 273
    Height = 273
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
    object Label2: TLabel
      Left = 13
      Top = 60
      Width = 82
      Height = 13
      Caption = 'Etape de d'#233'part :'
    end
    object Label3: TLabel
      Left = 13
      Top = 76
      Width = 77
      Height = 13
      Caption = 'Etape d'#39'arriv'#233'e :'
    end
    object Label4: TLabel
      Left = 13
      Top = 92
      Width = 63
      Height = 13
      Caption = 'Sorti au tour :'
    end
    object Label5: TLabel
      Left = 13
      Top = 124
      Width = 73
      Height = 13
      Caption = 'Tours effectifs :'
    end
    object Label6: TLabel
      Left = 13
      Top = 140
      Width = 99
      Height = 13
      Caption = 'Distance parcourue :'
    end
    object Label7: TLabel
      Left = 13
      Top = 156
      Width = 210
      Height = 13
      Caption = 'Distance/Temps minimal restant '#224' parcourir :'
    end
    object Label8: TLabel
      Left = 13
      Top = 172
      Width = 198
      Height = 13
      Caption = 'Distance/Temps minimal total '#224' parcourir :'
    end
    object Label9: TLabel
      Left = 13
      Top = 196
      Width = 90
      Height = 13
      Caption = 'Parcours effectu'#233' :'
    end
    object Label10: TLabel
      Left = 13
      Top = 212
      Width = 80
      Height = 13
      Caption = 'D'#233'tour effectu'#233' :'
    end
    object Label11: TLabel
      Left = 13
      Top = 228
      Width = 88
      Height = 13
      Caption = 'Attente effectu'#233'e :'
    end
    object LabelEtapeDepart: TLabel
      Left = 200
      Top = 60
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
    object LabelEtapeArrivee: TLabel
      Left = 200
      Top = 76
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
    object LabelTourSortie: TLabel
      Left = 248
      Top = 92
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
    object LabelDistance: TLabel
      Left = 248
      Top = 156
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
    object LabelParcours: TLabel
      Left = 248
      Top = 140
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
    object LabelDistanceMin: TLabel
      Left = 248
      Top = 172
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
    object LabelTours: TLabel
      Left = 248
      Top = 124
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
    object LabelParcoursEffectue: TLabel
      Left = 214
      Top = 196
      Width = 42
      Height = 13
      Alignment = taRightJustify
      Caption = '0,000%'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelDetour: TLabel
      Left = 214
      Top = 212
      Width = 42
      Height = 13
      Alignment = taRightJustify
      Caption = '0,000%'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Left = 13
      Top = 252
      Width = 127
      Height = 13
      Caption = 'Vitesse max.(cases/tours) :'
    end
    object LabelAttente: TLabel
      Left = 214
      Top = 228
      Width = 42
      Height = 13
      Alignment = taRightJustify
      Caption = '0,000%'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelVitesse: TLabel
      Left = 235
      Top = 252
      Width = 21
      Height = 13
      Alignment = taRightJustify
      Caption = '0/0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label13: TLabel
      Left = 13
      Top = 44
      Width = 89
      Height = 13
      Caption = 'Niveau de priorit'#233' :'
    end
    object LabelNivPriorite: TLabel
      Left = 216
      Top = 44
      Width = 40
      Height = 13
      Alignment = taRightJustify
      Caption = 'Normal'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object RadioButtonVehiculeNumero: TRadioButton
    Left = 19
    Top = 55
    Width = 77
    Height = 17
    Caption = 'V'#233'hicule n'#176
    Enabled = False
    TabOrder = 1
  end
  object ButtonAide: TButton
    Left = 144
    Top = 340
    Width = 75
    Height = 25
    Caption = '&Aide'
    TabOrder = 4
    OnClick = ButtonAideClick
  end
end
