object frmInfosTram: TfrmInfosTram
  Left = 297
  Top = 432
  HelpContext = 672
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Propri'#233't'#233's du tram'
  ClientHeight = 380
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
  object Label17: TLabel
    Left = 10
    Top = 330
    Width = 54
    Height = 11
    Caption = '(*) 0 = Aucun.'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label18: TLabel
    Left = 70
    Top = 330
    Width = 150
    Height = 11
    Caption = '(**) Du dernier arr'#234't au prochain arr'#234't.'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object ButtonOk: TButton
    Left = 59
    Top = 348
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Vu'
    Default = True
    TabOrder = 3
    OnClick = ButtonOkClick
  end
  object RadioButtonAucunTram: TRadioButton
    Left = 19
    Top = 32
    Width = 97
    Height = 17
    Caption = 'Aucun tram'
    Checked = True
    Enabled = False
    TabOrder = 0
    TabStop = True
  end
  object GroupBoxTram: TGroupBox
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
    object Label3: TLabel
      Left = 13
      Top = 60
      Width = 68
      Height = 13
      Caption = 'Dernier arr'#234't* :'
    end
    object Label5: TLabel
      Left = 13
      Top = 108
      Width = 73
      Height = 13
      Caption = 'Tours effectifs :'
    end
    object Label6: TLabel
      Left = 13
      Top = 124
      Width = 128
      Height = 13
      Caption = 'Distance totale parcourue :'
    end
    object Label9: TLabel
      Left = 13
      Top = 204
      Width = 90
      Height = 13
      Caption = 'Parcours effectu'#233' :'
    end
    object Label10: TLabel
      Left = 13
      Top = 220
      Width = 80
      Height = 13
      Caption = 'D'#233'tour effectu'#233' :'
    end
    object Label11: TLabel
      Left = 13
      Top = 236
      Width = 88
      Height = 13
      Caption = 'Attente effectu'#233'e :'
    end
    object LabelDernierArret: TLabel
      Left = 108
      Top = 60
      Width = 148
      Height = 13
      Alignment = taRightJustify
      Caption = '0 (00, 00)  jusqu'#39'au tour 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelParcours: TLabel
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
    object LabelTours: TLabel
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
    object LabelParcoursEffectue: TLabel
      Left = 214
      Top = 204
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
      Top = 220
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
      Top = 236
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
    object Label2: TLabel
      Left = 13
      Top = 44
      Width = 121
      Height = 13
      Caption = 'Num'#233'ro de ligne de tram :'
    end
    object LabelNumeroLigne: TLabel
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
    object Label7: TLabel
      Left = 13
      Top = 172
      Width = 218
      Height = 13
      Caption = 'Distance/Temps minimal restant '#224' parcourir** :'
    end
    object LabelDistance: TLabel
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
    object LabelDistanceMin: TLabel
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
    object Label8: TLabel
      Left = 13
      Top = 188
      Width = 206
      Height = 13
      Caption = 'Distance/Temps minimal total '#224' parcourir** :'
    end
    object Label4: TLabel
      Left = 13
      Top = 76
      Width = 72
      Height = 13
      Caption = 'Prochain arr'#234't :'
    end
    object LabelProchainArret: TLabel
      Left = 108
      Top = 76
      Width = 148
      Height = 13
      Alignment = taRightJustify
      Caption = '0 (00, 00) depuis le tour 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label13: TLabel
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
    object Label14: TLabel
      Left = 13
      Top = 156
      Width = 203
      Height = 13
      Caption = 'Distance parcourue depuis le dernier arr'#234't :'
    end
    object LabelParcoursEntreArrets: TLabel
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
    object Label15: TLabel
      Left = 13
      Top = 140
      Width = 177
      Height = 13
      Caption = 'Tours effectifs depuis le dernier arr'#234't :'
    end
    object LabelToursEntreArrets: TLabel
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
  end
  object RadioButtonTramNumero: TRadioButton
    Left = 19
    Top = 55
    Width = 77
    Height = 17
    Caption = 'Tram n'#176
    Enabled = False
    TabOrder = 1
  end
  object ButtonAide: TButton
    Left = 144
    Top = 348
    Width = 75
    Height = 25
    Caption = '&Aide'
    TabOrder = 4
    OnClick = ButtonAideClick
  end
end
