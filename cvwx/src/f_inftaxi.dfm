object frmInfosTaxi: TfrmInfosTaxi
  Left = -3
  Top = 673
  HelpContext = 673
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Propri'#233't'#233's du taxi'
  ClientHeight = 337
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
    Left = 59
    Top = 300
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Vu'
    Default = True
    TabOrder = 3
    OnClick = ButtonOkClick
  end
  object RadioButtonAucunTaxi: TRadioButton
    Left = 19
    Top = 32
    Width = 97
    Height = 17
    Caption = 'Aucun taxi'
    Checked = True
    Enabled = False
    TabOrder = 0
    TabStop = True
  end
  object GroupBoxTaxi: TGroupBox
    Left = 8
    Top = 56
    Width = 273
    Height = 233
    Caption = '                           '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Label2: TLabel
      Left = 13
      Top = 44
      Width = 48
      Height = 13
      Caption = 'Direction :'
    end
    object Label4: TLabel
      Left = 13
      Top = 76
      Width = 121
      Height = 13
      Caption = 'Num'#233'ro de la t'#234'te de file :'
    end
    object Label6: TLabel
      Left = 13
      Top = 108
      Width = 128
      Height = 13
      Caption = 'Distance totale parcourue :'
    end
    object LabelTeteFileOrigine: TLabel
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
    object LabelParcours: TLabel
      Left = 248
      Top = 108
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
      Top = 45
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
    object Label9: TLabel
      Left = 13
      Top = 204
      Width = 127
      Height = 13
      Caption = 'Vitesse max.(cases/tours) :'
    end
    object LabelVitesse: TLabel
      Left = 235
      Top = 204
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
    object Label3: TLabel
      Left = 13
      Top = 60
      Width = 74
      Height = 13
      Caption = 'Num'#233'ro de file :'
    end
    object LabelNumeroFile: TLabel
      Left = 248
      Top = 60
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
    object Label5: TLabel
      Left = 13
      Top = 92
      Width = 110
      Height = 13
      Caption = 'Nombre de personnes :'
    end
    object LabelNbPersonnes: TLabel
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
    object Label8: TLabel
      Left = 13
      Top = 172
      Width = 212
      Height = 13
      Caption = 'Distance parcourue depuis le dernier d'#233'part :'
    end
    object LabelParcoursDepuisDepart: TLabel
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
    object Label7: TLabel
      Left = 13
      Top = 124
      Width = 186
      Height = 13
      Caption = 'Tours effectifs depuis le dernier d'#233'part :'
    end
    object LabelToursDepuisDepart: TLabel
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
    object Label1: TLabel
      Left = 13
      Top = 28
      Width = 47
      Height = 13
      Caption = 'Situation :'
    end
    object LabelSituation: TLabel
      Left = 251
      Top = 28
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
    object Label10: TLabel
      Left = 13
      Top = 140
      Width = 183
      Height = 13
      Caption = 'Tours effectifs depuis le dernier d'#233'p'#244't :'
    end
    object LabelToursDepuisDepot: TLabel
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
    object Label11: TLabel
      Left = 13
      Top = 156
      Width = 183
      Height = 13
      Caption = 'Tours effectifs depuis le dernier retour :'
    end
    object LabelToursDepuisRetour: TLabel
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
    object Label12: TLabel
      Left = 13
      Top = 188
      Width = 168
      Height = 13
      Caption = 'Distance '#224' la t'#234'te de file de d'#233'part :'
    end
    object LabelDistanceTeteFileDepart: TLabel
      Left = 248
      Top = 188
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
  end
  object RadioButtonTaxiNumero: TRadioButton
    Left = 19
    Top = 55
    Width = 77
    Height = 17
    Caption = 'Taxi n'#176
    Enabled = False
    TabOrder = 1
  end
  object ButtonAide: TButton
    Left = 144
    Top = 300
    Width = 75
    Height = 25
    Caption = '&Aide'
    TabOrder = 4
    OnClick = ButtonAideClick
  end
end
