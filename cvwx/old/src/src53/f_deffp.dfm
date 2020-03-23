object frmDefFeuxPietons: TfrmDefFeuxPietons
  Left = 303
  Top = 187
  HelpContext = 425
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'D'#233'finition du feu de pi'#233'tons'
  ClientHeight = 349
  ClientWidth = 290
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
  object Label2: TLabel
    Left = 136
    Top = 8
    Width = 48
    Height = 13
    Caption = 'Direction :'
  end
  object LabelDirection: TLabel
    Left = 190
    Top = 8
    Width = 25
    Height = 13
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 243
    Top = 8
    Width = 12
    Height = 13
    Caption = 'N'#176
  end
  object LabelNumero: TLabel
    Left = 257
    Top = 8
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label7: TLabel
    Left = 11
    Top = 176
    Width = 107
    Height = 13
    Caption = 'Feux de circulation li'#233's'
  end
  object LabelNbFeux: TLabel
    Left = 127
    Top = 176
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
  object SpeedButtonSelFeux: TSpeedButton
    Left = 141
    Top = 171
    Width = 24
    Height = 24
    Hint = 'S'#233'lectionne les feux de circulation li'#233's'
    AllowAllUp = True
    GroupIndex = 1
    Glyph.Data = {
      06020000424D0602000000000000760000002800000028000000140000000100
      0400000000009001000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00666666666666
      6666666666FFFFFF66FF66FFFFFF6FFFFFF66AA66FFFFFF66888888F688FF888
      888F6FFFFFF6AAAA6FFFFFF6688888868888F888888F6FF6666AAAAAA6666FF6
      688F666888888666688F6FF6666AAAAAA6666FF6688F666888888666688F6FF6
      6666AAAA66666FF6688F666688886666688F6FF666666AA666666FF668866666
      688F66666886666666666BB66666666666666666688FF666666666666666BBBB
      66666666666666668888FF6666666666666BBBBBB66666666666666888888F66
      66666666666BBBBBB66666666666666888888666666666666666BBBB66666666
      66666666888866666666666666666BB66666666666FF6666688F666666FF6FF6
      6666699666666FF6688F6666688FF666688F6FF66666999966666FF6688F6666
      8888FF66688F6FF66669999996666FF6688F666888888F66688F6FF666699999
      96666FF6688FFFF888888666688F6FFFFFF699996FFFFFF66888888F88886888
      888F6FFFFFF669966FFFFFF66888888668866888888666666666666666666666
      66666666666666666666}
    NumGlyphs = 2
    ParentShowHint = False
    ShowHint = True
    OnClick = SpeedButtonSelFeuxClick
  end
  object Label6: TLabel
    Left = 11
    Top = 200
    Width = 114
    Height = 13
    Caption = 'Position du feu oppos'#233' :'
  end
  object LabelCoordonneesFeuPietonsOppose: TLabel
    Left = 130
    Top = 200
    Width = 45
    Height = 13
    Caption = '(00, 00)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label8: TLabel
    Left = 8
    Top = 280
    Width = 273
    Height = 25
    AutoSize = False
    Caption = 
      '(*) Le pi'#233'ton demande '#224' traverser. La demande n'#39'a pas d'#39'effet su' +
      'r les feux de circulation li'#233's '#224' d'#39'autres feux de circulation.'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object Label9: TLabel
    Left = 171
    Top = 176
    Width = 82
    Height = 13
    Caption = 'Dur'#233'e travers'#233'e :'
  end
  object LabelDureeTraversee: TLabel
    Left = 271
    Top = 176
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
  object RadioGroupTypeDmdVert: TRadioGroup
    Left = 8
    Top = 72
    Width = 273
    Height = 41
    Caption = ' Demande le feu vert d'#232's... '
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      '...qu'#39'un pi'#233'ton attend*'
      '...que le feu est rouge')
    TabOrder = 1
    OnClick = RadioGroupTypeDmdVertClick
  end
  object RadioGroupEtat: TRadioGroup
    Left = 8
    Top = 24
    Width = 273
    Height = 41
    Caption = ' Etat initial '
    Columns = 4
    ItemIndex = 0
    Items.Strings = (
      '&Inactif'
      '&Vert'
      '&Rouge')
    TabOrder = 0
    OnClick = RadioGroupEtatClick
  end
  object GroupBoxDureeFeu: TGroupBox
    Left = 8
    Top = 224
    Width = 273
    Height = 49
    Caption = ' Dur'#233'es apr'#232's demande de &changement (en tours)'
    TabOrder = 3
    object Label5: TLabel
      Left = 137
      Top = 21
      Width = 80
      Height = 13
      Caption = 'Dur'#233'e du rouge :'
      FocusControl = CSpinEditDureeRouge
    end
    object Label4: TLabel
      Left = 11
      Top = 21
      Width = 71
      Height = 13
      Caption = 'Dur'#233'e du vert :'
      FocusControl = CSpinEditDureeVert
    end
    object CSpinEditDureeRouge: TCSpinEdit
      Left = 221
      Top = 18
      Width = 41
      Height = 22
      MaxValue = 100
      TabOrder = 1
      OnChange = CSpinEditDureeVertChange
    end
    object CSpinEditDureeVert: TCSpinEdit
      Left = 86
      Top = 18
      Width = 41
      Height = 22
      MaxValue = 100
      TabOrder = 0
      OnChange = CSpinEditDureeVertChange
    end
  end
  object ButtonOk: TButton
    Left = 16
    Top = 312
    Width = 49
    Height = 25
    Caption = 'Vu'
    Default = True
    TabOrder = 4
    OnClick = ButtonOkClick
  end
  object ButtonAnnuler: TButton
    Left = 80
    Top = 312
    Width = 49
    Height = 25
    Cancel = True
    Caption = 'Annuler'
    TabOrder = 5
    OnClick = ButtonAnnulerClick
  end
  object ButtonAppliquer: TButton
    Left = 144
    Top = 312
    Width = 57
    Height = 25
    Caption = '&Appliquer'
    Enabled = False
    TabOrder = 6
    OnClick = ButtonAppliquerClick
  end
  object RadioGroupTypePsgRouge: TRadioGroup
    Left = 8
    Top = 120
    Width = 273
    Height = 41
    Caption = ' Passe au rouge d'#232's... '
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      '...qu'#39'un feu le demande'
      '...que le feu est vert')
    TabOrder = 2
    OnClick = RadioGroupTypePsgRougeClick
  end
  object ButtonAide: TButton
    Left = 216
    Top = 312
    Width = 57
    Height = 25
    Caption = '&Aide'
    TabOrder = 7
    OnClick = ButtonAideClick
  end
end
