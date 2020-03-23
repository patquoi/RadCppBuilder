object frmParamSimul: TfrmParamSimul
  Left = 318
  Top = 143
  HelpContext = 311
  ActiveControl = CSpinEditNbFeux
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Param'#232'tres'
  ClientHeight = 541
  ClientWidth = 280
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  HelpFile = 'cvw.hlp'
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 205
    Top = 201
    Width = 69
    Height = 11
    Caption = '(*) des v'#233'hicules.'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object GroupBoxFonctionnement: TGroupBox
    Left = 8
    Top = 216
    Width = 265
    Height = 318
    Caption = ' Param'#232'tres de fonctionnement '
    TabOrder = 4
    object LabelTours: TLabel
      Left = 213
      Top = 11
      Width = 33
      Height = 13
      Caption = 'Tour(s)'
    end
    object LabelAttenteAvChx: TLabel
      Left = 11
      Top = 101
      Width = 182
      Height = 13
      Caption = '&Attente avant choix d'#39'un autre trajet** :'
    end
    object LabelNbToursParSeconde: TLabel
      Left = 11
      Top = 125
      Width = 146
      Height = 13
      Caption = '&Nombre de tours par seconde :'
    end
    object LabelDureeOrange: TLabel
      Left = 11
      Top = 54
      Width = 106
      Height = 13
      Caption = 'Dur'#233'e du feu &Orange :'
    end
    object LabelDureeRouge: TLabel
      Left = 11
      Top = 78
      Width = 160
      Height = 13
      Caption = 'Dur'#233'e du feu &Rouge (par d'#233'faut) :'
    end
    object LabelDureeVert: TLabel
      Left = 11
      Top = 30
      Width = 147
      Height = 13
      Caption = 'Dur'#233'e du feu &Vert (par d'#233'faut) :'
    end
    object Label7: TLabel
      Left = 7
      Top = 290
      Width = 250
      Height = 24
      AutoSize = False
      Caption = 
        '(**) pour les v'#233'hicules (taxis compris). 2 fois moins de tours p' +
        'our les pi'#233'tons et  5 fois plus de tours pour les bus.'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Small Fonts'
      Font.Style = []
      ParentFont = False
      WordWrap = True
    end
    object CSpinEditAttenteAvChx: TCSpinEdit
      Left = 213
      Top = 98
      Width = 36
      Height = 22
      AutoSize = False
      MaxValue = 99
      TabOrder = 3
      Value = 10
      OnChange = Change
    end
    object CSpinEditNbToursParSeconde: TCSpinEdit
      Left = 213
      Top = 122
      Width = 36
      Height = 22
      MaxValue = 99
      MinValue = 1
      TabOrder = 4
      Value = 10
      OnChange = Change
    end
    object CSpinEditDureeOrange: TCSpinEdit
      Left = 213
      Top = 50
      Width = 36
      Height = 22
      AutoSize = False
      MaxValue = 10
      TabOrder = 1
      Value = 1
      OnChange = Change
    end
    object CSpinEditDureeRouge: TCSpinEdit
      Left = 213
      Top = 74
      Width = 36
      Height = 22
      AutoSize = False
      MaxValue = 10
      TabOrder = 2
      Value = 5
      OnChange = CSpinEditDureeRougeChange
    end
    object CSpinEditDureeVert: TCSpinEdit
      Left = 213
      Top = 26
      Width = 36
      Height = 22
      AutoSize = False
      MaxValue = 10
      TabOrder = 0
      Value = 5
      OnChange = CSpinEditDureeVertChange
    end
    object BitBtnAppliqueDureeFeuVert: TBitBtn
      Left = 189
      Top = 26
      Width = 22
      Height = 22
      Hint = 'Applique la dur'#233'e du vert '#224' tous les feux'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      OnClick = BitBtnAppliqueDureeFeuVertClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00000000000000
        000000000000000000000000000000000AA20000000000000FF8000000000000
        AA22000000000000FF88000000000830AA22000000000880FF88000000088332
        2A220000000888888F8800000883333222200000088888888880000082A33300
        0BB3000088F888000FF800082A2A3300BB3300088F8F8800FF880082A2AA3000
        BB330088F8FF8000FF88082A2AA230033B33088F8FF880088F8882A2AA880033
        333088F8FF88008888802A2AA280000009918F8FF88000000FF8A2AA28000000
        9911F8FF88000000FF882AA28000000099118FF880000000FF88AA2800000001
        1911FF88000000088F88A280000000111110F880000000888880}
      NumGlyphs = 2
    end
    object BitBtnAppliqueDureeFeuRouge: TBitBtn
      Left = 189
      Top = 74
      Width = 22
      Height = 22
      Hint = 'Applique la dur'#233'e du rouge '#224' tous les feux'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
      OnClick = BitBtnAppliqueDureeFeuRougeClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00000000000000
        000000000000000000000000000000000AA20000000000000FF8000000000000
        AA22000000000000FF88000000000830AA22000000000880FF88000000088332
        2A220000000888888F8800000883333222200000088888888880000082A33300
        0BB3000088F888000FF800082A2A3300BB3300088F8F8800FF880082A2AA3000
        BB330088F8FF8000FF88082A2AA230033B33088F8FF880088F8882A2AA880033
        333088F8FF88008888802A2AA280000009918F8FF88000000FF8A2AA28000000
        9911F8FF88000000FF882AA28000000099118FF880000000FF88AA2800000001
        1911FF88000000088F88A280000000111110F880000000888880}
      NumGlyphs = 2
    end
    object RadioGroupVitesses: TRadioGroup
      Left = 8
      Top = 148
      Width = 249
      Height = 64
      Caption = ' Simulation '#224'... '
      ItemIndex = 0
      Items.Strings = (
        '&1 vitesse (1 case par tour)'
        '&2 vitesses (1 case tous les 2 tours minimum)'
        '&3 vitesses (1 case tous les 3 tours minimum)')
      TabOrder = 7
      OnClick = Change
    end
    object GroupBoxPietons: TGroupBox
      Left = 8
      Top = 213
      Width = 249
      Height = 74
      Caption = ' Pi'#233'ton '
      TabOrder = 8
      object LabelNbCasesMaxPsgPtn: TLabel
        Left = 11
        Top = 23
        Width = 163
        Height = 13
        Caption = 'D'#233'tecte 1 passage pi'#233'tons jusqu'#39#224
        FocusControl = CSpinEditNbCasesMaxPsgPtn
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 215
        Top = 23
        Width = 28
        Height = 13
        Caption = 'cases'
      end
      object LabelProbaPsgPt: TLabel
        Left = 11
        Top = 48
        Width = 165
        Height = 13
        Caption = 'Probabilit'#233' de s'#39'&y diriger si d'#233'tect'#233' :'
        FocusControl = CSpinEditProbaPsgPt
      end
      object Label6: TLabel
        Left = 227
        Top = 48
        Width = 8
        Height = 13
        Caption = '%'
      end
      object CSpinEditNbCasesMaxPsgPtn: TCSpinEdit
        Left = 177
        Top = 20
        Width = 36
        Height = 22
        MaxValue = 10
        TabOrder = 0
        Value = 5
        OnChange = Change
      end
      object CSpinEditProbaPsgPt: TCSpinEdit
        Left = 178
        Top = 45
        Width = 44
        Height = 22
        Increment = 5
        MaxValue = 100
        TabOrder = 1
        Value = 50
        OnChange = Change
      end
    end
  end
  object ButtonOk: TButton
    Left = 210
    Top = 52
    Width = 56
    Height = 25
    Caption = 'Vu'
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = ButtonOkClick
  end
  object ButtonAnnuler: TButton
    Left = 210
    Top = 87
    Width = 56
    Height = 25
    Cancel = True
    Caption = 'Annuler'
    ModalResult = 2
    TabOrder = 1
  end
  object GroupBoxNbElements: TGroupBox
    Left = 8
    Top = 0
    Width = 185
    Height = 209
    Caption = ' El'#233'ments de la simulation '
    TabOrder = 3
    object LabelNbFeux: TLabel
      Left = 6
      Top = 24
      Width = 60
      Height = 13
      Caption = '&Feux (max.) :'
      FocusControl = CSpinEditNbFeux
    end
    object LabelNbVehicules: TLabel
      Left = 6
      Top = 72
      Width = 52
      Height = 13
      Caption = 'V'#233'&hicules :'
      FocusControl = CSpinEditNbVehicules
    end
    object LabelNbEtapes: TLabel
      Left = 6
      Top = 48
      Width = 39
      Height = 13
      Caption = '&Etapes :'
    end
    object LabelNbPietons: TLabel
      Left = 6
      Top = 96
      Width = 41
      Height = 13
      Caption = 'Pi'#233'&tons :'
      FocusControl = CSpinEditNbPietons
    end
    object Label1: TLabel
      Left = 147
      Top = 96
      Width = 12
      Height = 13
      Caption = '%*'
    end
    object LabelNbArretsBus: TLabel
      Left = 6
      Top = 120
      Width = 69
      Height = 13
      Caption = 'Arr'#234'ts de &Bus :'
      FocusControl = CSpinEditNbArretsBus
    end
    object LabelNbArretsTram: TLabel
      Left = 6
      Top = 144
      Width = 75
      Height = 13
      Caption = 'Arr'#234'ts de &Tram :'
      FocusControl = CSpinEditNbArretsTram
    end
    object LabelNbPlacesTaxi: TLabel
      Left = 6
      Top = 168
      Width = 71
      Height = 13
      Caption = 'Taxis (places) :'
      FocusControl = CSpinEditNbPlacesTaxi
    end
    object CSpinEditNbFeux: TCSpinEdit
      Left = 109
      Top = 21
      Width = 48
      Height = 22
      MaxValue = 100
      TabOrder = 0
      Value = 30
      OnChange = CSpinEditNbFeuxChange
    end
    object CSpinEditNbVehicules: TCSpinEdit
      Left = 109
      Top = 69
      Width = 48
      Height = 22
      AutoSize = False
      EditorEnabled = False
      Increment = 120
      MaxValue = 1000
      MinValue = 120
      TabOrder = 2
      Value = 120
      OnChange = CSpinEditNbVehiculesChange
    end
    object CSpinEditNbEtapes: TCSpinEdit
      Left = 109
      Top = 45
      Width = 48
      Height = 22
      EditorEnabled = False
      MaxValue = 32
      MinValue = 2
      TabOrder = 1
      Value = 4
      OnChange = CSpinEditNbEtapesChange
    end
    object CheckBoxMaintenus: TCheckBox
      Left = 7
      Top = 189
      Width = 137
      Height = 17
      Caption = '&Maintenus '#224' l'#39'ouverture'
      TabOrder = 10
      OnClick = Change
    end
    object CSpinEditNbPietons: TCSpinEdit
      Left = 109
      Top = 93
      Width = 36
      Height = 22
      AutoSize = False
      EditorEnabled = False
      Increment = 5
      MaxValue = 50
      TabOrder = 3
      Value = 25
      OnChange = CSpinEditNbPietonsChange
    end
    object CSpinEditNbArretsBus: TCSpinEdit
      Left = 109
      Top = 117
      Width = 36
      Height = 22
      MaxValue = 81
      TabOrder = 4
      OnChange = CSpinEditNbArretsBusChange
    end
    object BitBtnDefLignesBus: TBitBtn
      Left = 149
      Top = 117
      Width = 24
      Height = 24
      Hint = 'Param'#233'trer le r'#233'seau de bus'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      OnClick = BitBtnDefLignesBusClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0066666DDDDDD6
        66666666688888866666666DDDDDDDDDD666666888888888866666DDDDDDDDDD
        DD6666888888888888666D00DDD00DDD00D6680088800888008660000D0000D0
        00066000080000800006D0DD0D0DD0D0DD0D8088080880808808D0DD0D0DD0DD
        DD0D8088080880888808D000DD0DD0DD000D8000880880880008D000DD0DD0D0
        00DD8000880880800088D0DD0D0DD0D0DDDD8088080880808888D0DD0D0DD0D0
        DD0D808808088080880860000D0DD0D0000660000808808000066D00DD0DD0DD
        00D6680088088088008666DDDDDDDDDDDD666688888888888866666DDDDDDDDD
        D666666888888888866666666DDDDDD666666666688888866666}
      NumGlyphs = 2
    end
    object CSpinEditNbArretsTram: TCSpinEdit
      Left = 109
      Top = 141
      Width = 36
      Height = 22
      MaxValue = 81
      TabOrder = 6
      OnChange = CSpinEditNbArretsTramChange
    end
    object BitBtnDefLignesTram: TBitBtn
      Left = 149
      Top = 141
      Width = 24
      Height = 24
      Hint = 'Param'#233'trer le r'#233'seau de bus'
      Enabled = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
      OnClick = BitBtnDefLignesTramClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0066666EEEEEE6
        66666666688888866666666EEEEEEEEEE666666888888888866666EEEEEEEEEE
        EE6666888888888888666E0E0E0E0E0E0E0668080808080808066E0E0E0E0E0E
        0E066808080808080806EE0E0E0E0E0E0E0E8808080808080808EE0E0E0E0E0E
        0E0E8808080808080808EE0E00EE000E0E0E8808008800080808EE0E000E000E
        0E0E8808000800080808EE0E0E0E0E0E0E0E8808080808080808EE0E0E0E0E0E
        000E88080808080800086000000E000E000660000008000800066000E0EEE0EE
        0E06600080888088080666EEEEEEEEEEEE666688888888888866666EEEEEEEEE
        E666666888888888866666666EEEEEE666666666688888866666}
      NumGlyphs = 2
    end
    object CSpinEditNbPlacesTaxi: TCSpinEdit
      Left = 109
      Top = 165
      Width = 36
      Height = 22
      MaxValue = 99
      TabOrder = 8
      OnChange = CSpinEditNbPlacesTaxiChange
    end
    object BitBtnDefTaxis: TBitBtn
      Left = 149
      Top = 165
      Width = 24
      Height = 24
      Enabled = False
      TabOrder = 9
      OnClick = BitBtnDefTaxisClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0066666BBBBBB6
        66666666688888866666666BBBBBBBBBB666666888888888866666BBBBBBBBBB
        BB6666888888888888666BB0B0B0B0B0B0B668808080808080866BB0B0B0B0B0
        B0B66880808080808086BBB0B0B0B0B0B0BB8880808080808088BBB0B0B0B0B0
        B0BB8880808080808088BBB0B000BB0BB0BB8880800088088088BBB0B000BB0B
        B0BB8880800088088088BBB0B0B0B0B0B0BB8880808080808088BBB0B0B0B0B0
        B0BB88808080808080886B000000B0B0B0B668000000808080866B000B0BB0B0
        B0B6680008088080808666BBBBBBBBBBBB666688888888888866666BBBBBBBBB
        B666666888888888866666666BBBBBB666666666688888866666}
      NumGlyphs = 2
    end
  end
  object ButtonAppliquer: TButton
    Left = 210
    Top = 124
    Width = 56
    Height = 25
    Caption = 'A&ppliquer'
    Enabled = False
    TabOrder = 2
    OnClick = ButtonAppliquerClick
  end
  object ButtonAide: TButton
    Left = 208
    Top = 160
    Width = 58
    Height = 25
    Hint = 'Pour avoir de l'#39'aide (F1)'
    Caption = 'Aide'
    TabOrder = 5
    OnClick = ButtonAideClick
  end
end
