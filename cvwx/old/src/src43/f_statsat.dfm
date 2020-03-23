object frmStatsAttenteTrafic: TfrmStatsAttenteTrafic
  Left = 0
  Top = 0
  HelpContext = 612
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsToolWindow
  Caption = 'Statistiques de fluidit'#233' et de trafic'
  ClientHeight = 168
  ClientWidth = 368
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -9
  Font.Name = 'Small Fonts'
  Font.Style = []
  HelpFile = 'cvw.hlp'
  OldCreateOrder = True
  PopupMenu = PopupMenu
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 11
  object Label1: TLabel
    Left = 174
    Top = 81
    Width = 98
    Height = 11
    Caption = 'Attente totale cumul'#233'e :'
  end
  object Label2: TLabel
    Left = 174
    Top = 93
    Width = 112
    Height = 11
    Caption = 'Attente moyenne par case :'
  end
  object Label3: TLabel
    Left = 174
    Top = 105
    Width = 124
    Height = 11
    Caption = 'Attente maximale enregistr'#233'e :'
  end
  object Label4: TLabel
    Left = 174
    Top = 130
    Width = 81
    Height = 11
    Caption = 'Trafic total cumul'#233' :'
  end
  object Label5: TLabel
    Left = 174
    Top = 142
    Width = 95
    Height = 11
    Caption = 'Trafic moyen par case :'
  end
  object Label6: TLabel
    Left = 174
    Top = 154
    Width = 107
    Height = 11
    Caption = 'Trafic maximal enregistr'#233' :'
  end
  object Label7: TLabel
    Left = 330
    Top = 69
    Width = 31
    Height = 11
    Caption = 'Tours'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelAttenteCumulee: TLabel
    Left = 354
    Top = 81
    Width = 7
    Height = 11
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelAttenteMoyenne: TLabel
    Left = 354
    Top = 93
    Width = 7
    Height = 11
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelAttenteMaximale: TLabel
    Left = 354
    Top = 105
    Width = 7
    Height = 11
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelTraficCumule: TLabel
    Left = 354
    Top = 130
    Width = 7
    Height = 11
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelTraficMoyen: TLabel
    Left = 354
    Top = 142
    Width = 7
    Height = 11
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelTraficMaximal: TLabel
    Left = 354
    Top = 154
    Width = 7
    Height = 11
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label8: TLabel
    Left = 311
    Top = 118
    Width = 50
    Height = 11
    Caption = 'V'#233'hicules'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object RadioGroupType: TRadioGroup
    Left = 8
    Top = 3
    Width = 289
    Height = 42
    Caption = ' Choix des statistiques '#224' visualiser '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      
        '&Attente (tours pendant lesquels 1 v'#233'hicule est rest'#233' sur 1 case' +
        ')'
      '&Trafic (v'#233'hicules qui sont pass'#233's par 1 case)')
    ParentFont = False
    ParentShowHint = False
    ShowHint = False
    TabOrder = 0
    OnClick = RadioGroupTypeClick
  end
  object GroupBoxEtapes: TGroupBox
    Left = 8
    Top = 48
    Width = 153
    Height = 64
    Hint = 'Cocher les cases puis choisissez un n'#176' d'#39#233'tape'
    Caption = ' S'#233'lection de trajets '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    object CSpinEditEtapeArrivee: TCSpinEdit
      Left = 97
      Top = 35
      Width = 40
      Height = 19
      Enabled = False
      MaxValue = 1
      MinValue = 1
      TabOrder = 3
      Value = 1
      OnChange = ParametresEtapesClick
    end
    object CheckBoxEtapeArrivee: TCheckBox
      Tag = 2
      Left = 9
      Top = 37
      Width = 80
      Height = 17
      Caption = 'Etape Arri&v'#233'e'
      TabOrder = 2
      OnClick = ParametresEtapesClick
    end
    object CheckBoxEtapeDepart: TCheckBox
      Tag = 1
      Left = 9
      Top = 16
      Width = 80
      Height = 17
      Caption = 'Etape &D'#233'part'
      TabOrder = 0
      OnClick = ParametresEtapesClick
    end
    object CSpinEditEtapeDepart: TCSpinEdit
      Left = 97
      Top = 15
      Width = 40
      Height = 19
      Enabled = False
      MaxValue = 1
      MinValue = 1
      TabOrder = 1
      Value = 1
      OnChange = ParametresEtapesClick
    end
  end
  object GroupBoxLegende: TGroupBox
    Left = 8
    Top = 115
    Width = 153
    Height = 49
    Caption = ' L'#233'gende '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object LabelMax: TLabel
      Left = 121
      Top = 12
      Width = 18
      Height = 11
      Alignment = taRightJustify
      Caption = 'Max'
    end
    object Label10: TLabel
      Left = 11
      Top = 12
      Width = 5
      Height = 11
      Caption = '0'
    end
    object PaintBox: TPaintBox
      Left = 12
      Top = 24
      Width = 128
      Height = 17
      OnPaint = PaintBoxPaint
    end
  end
  object BitBtn21: TBitBtn
    Left = 328
    Top = 0
    Width = 20
    Height = 20
    Hint = 
      'D'#233'place dans les coins si option coch'#233'e (Pav'#233' num'#233'rique Verr.Num' +
      '. d'#233'sactiv'#233')'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 5
    OnClick = BitBtnDirClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333000333
      3333333333777F33333333333309033333333333337F7F333333333333090333
      33333333337F7F33333333333309033333333333337F7F333333333333090333
      33333333337F7F33333333333309033333333333FF7F7FFFF333333000090000
      3333333777737777F333333099999990333333373F3333373333333309999903
      333333337F33337F33333333099999033333333373F333733333333330999033
      3333333337F337F3333333333099903333333333373F37333333333333090333
      33333333337F7F33333333333309033333333333337373333333333333303333
      333333333337F333333333333330333333333333333733333333}
    NumGlyphs = 2
  end
  object BitBtn31: TBitBtn
    Left = 348
    Top = 0
    Width = 20
    Height = 20
    Hint = 
      'D'#233'place dans les coins si option coch'#233'e (Pav'#233' num'#233'rique Verr.Num' +
      '. d'#233'sactiv'#233')'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 6
    OnClick = BitBtnDirClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      33333333333333333333333333333333333333FF333333333333370733333333
      33333777F33333333333309073333333333337F77F3333F33333370907333733
      3333377F77F337F3333333709073003333333377F77F77F33333333709009033
      333333377F77373F33333333709999033333333377F3337F3333333330999903
      3333333337333373F333333309999990333333337FF33337F333333700999990
      33333337773FF3373F333333330099990333333333773FF37F33333333330099
      033333333333773F73F3333333333300903333333333337737F3333333333333
      0033333333333333773333333333333333333333333333333333}
    NumGlyphs = 2
  end
  object BitBtn11: TBitBtn
    Left = 307
    Top = 0
    Width = 20
    Height = 20
    Hint = 
      'D'#233'place dans les coins si option coch'#233'e (Pav'#233' num'#233'rique Verr.Num' +
      '. d'#233'sactiv'#233')'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 4
    OnClick = BitBtnDirClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      333333333333333FFF3333333333333707333333333333F777F3333333333370
      9033333333F33F7737F33333373337090733333337F3F7737733333330037090
      73333333377F7737733333333090090733333333373773773333333309999073
      333333337F333773333333330999903333333333733337F33333333099999903
      33333337F3333F7FF33333309999900733333337333FF7773333330999900333
      3333337F3FF7733333333309900333333333337FF77333333333309003333333
      333337F773333333333330033333333333333773333333333333333333333333
      3333333333333333333333333333333333333333333333333333}
    NumGlyphs = 2
  end
  object BitBtn13: TBitBtn
    Left = 307
    Top = 40
    Width = 20
    Height = 20
    Hint = 
      'D'#233'place dans les coins si option coch'#233'e (Pav'#233' num'#233'rique Verr.Num' +
      '. d'#233'sactiv'#233')'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 10
    OnClick = BitBtnDirClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      33333333333333333333333333333333333333FF333333333333300333333333
      33333773FF33333333333090033333333333373773FF33333333330990033333
      3333337F3773FF33333333099990033333333373F33773FFF333333099999007
      33333337F33337773333333099999903333333373F3333733333333309999033
      333333337F3337F333333333099990733333333373F3F77F3333333330900907
      3333333337F77F77F33333333003709073333333377377F77F33333337333709
      073333333733377F77F33333333333709033333333333377F7F3333333333337
      0733333333333337773333333333333333333333333333333333}
    NumGlyphs = 2
  end
  object BitBtn23: TBitBtn
    Left = 328
    Top = 40
    Width = 20
    Height = 20
    Hint = 
      'D'#233'place dans les coins si option coch'#233'e (Pav'#233' num'#233'rique Verr.Num' +
      '. d'#233'sactiv'#233')'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 11
    OnClick = BitBtnDirClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333303333
      333333333337F33333333333333033333333333333373F333333333333090333
      33333333337F7F33333333333309033333333333337373F33333333330999033
      3333333337F337F33333333330999033333333333733373F3333333309999903
      333333337F33337F33333333099999033333333373333373F333333099999990
      33333337FFFF3FF7F33333300009000033333337777F77773333333333090333
      33333333337F7F33333333333309033333333333337F7F333333333333090333
      33333333337F7F33333333333309033333333333337F7F333333333333090333
      33333333337F7F33333333333300033333333333337773333333}
    NumGlyphs = 2
  end
  object BitBtn33: TBitBtn
    Left = 348
    Top = 40
    Width = 20
    Height = 20
    Hint = 
      'D'#233'place dans les coins si option coch'#233'e (Pav'#233' num'#233'rique Verr.Num' +
      '. d'#233'sactiv'#233')'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 12
    OnClick = BitBtnDirClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      333333333333333333333333333333333333333333333333FFF3333333333333
      00333333333333FF77F3333333333300903333333333FF773733333333330099
      0333333333FF77337F3333333300999903333333FF7733337333333700999990
      3333333777333337F3333333099999903333333373F333373333333330999903
      33333333F7F3337F33333333709999033333333F773FF3733333333709009033
      333333F7737737F3333333709073003333333F77377377F33333370907333733
      33333773773337333333309073333333333337F7733333333333370733333333
      3333377733333333333333333333333333333333333333333333}
    NumGlyphs = 2
  end
  object BitBtn12: TBitBtn
    Left = 307
    Top = 20
    Width = 20
    Height = 20
    Hint = 
      'D'#233'place dans les coins si option coch'#233'e (Pav'#233' num'#233'rique Verr.Num' +
      '. d'#233'sactiv'#233')'
    TabOrder = 7
    OnClick = BitBtnDirClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333333333333333333333333333333333333333333333
      3333333333333FF3333333333333003333333333333F77F33333333333009033
      333333333F7737F333333333009990333333333F773337FFFFFF330099999000
      00003F773333377777770099999999999990773FF33333FFFFF7330099999000
      000033773FF33777777733330099903333333333773FF7F33333333333009033
      33333333337737F3333333333333003333333333333377333333333333333333
      3333333333333333333333333333333333333333333333333333333333333333
      3333333333333333333333333333333333333333333333333333}
    NumGlyphs = 2
  end
  object BitBtn32: TBitBtn
    Left = 348
    Top = 20
    Width = 20
    Height = 20
    Hint = 
      'D'#233'place dans les coins si option coch'#233'e (Pav'#233' num'#233'rique Verr.Num' +
      '. d'#233'sactiv'#233')'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 9
    OnClick = BitBtnDirClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333333333333333333333333333333333333333333333
      3333333333333333333333333333333333333333333FF3333333333333003333
      3333333333773FF3333333333309003333333333337F773FF333333333099900
      33333FFFFF7F33773FF30000000999990033777777733333773F099999999999
      99007FFFFFFF33333F7700000009999900337777777F333F7733333333099900
      33333333337F3F77333333333309003333333333337F77333333333333003333
      3333333333773333333333333333333333333333333333333333333333333333
      3333333333333333333333333333333333333333333333333333}
    NumGlyphs = 2
  end
  object BitBtn22: TBitBtn
    Left = 328
    Top = 20
    Width = 20
    Height = 20
    Hint = 'Zoom -/+ (touche Z)'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 8
    OnClick = BitBtn22Click
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000130B0000130B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      33033333333333333F7F3333333333333000333333333333F777333333333333
      000333333333333F777333333333333000333333333333F77733333333333300
      033333333FFF3F777333333700073B703333333F7773F77733333307777700B3
      33333377333777733333307F8F8F7033333337F333F337F3333377F8F9F8F773
      3333373337F3373F3333078F898F870333337F33F7FFF37F333307F99999F703
      33337F377777337F3333078F898F8703333373F337F33373333377F8F9F8F773
      333337F3373337F33333307F8F8F70333333373FF333F7333333330777770333
      333333773FF77333333333370007333333333333777333333333}
    NumGlyphs = 2
  end
  object CheckBoxCoins: TCheckBox
    Left = 199
    Top = 45
    Width = 97
    Height = 17
    Hint = 
      'Permettre d'#39'utiliser les touches fl'#233'ch'#233'es pour aller dans les co' +
      'ins'
    Caption = 'Aller dans les &coins'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
  end
  object PopupMenu: TPopupMenu
    Left = 272
    Top = 16
    object RubriqueHautGauche: TMenuItem
      Tag = 11
      Caption = 'Haut Gauche'
      ShortCut = 36
      OnClick = RubriqueClick
    end
    object RubriqueHaut: TMenuItem
      Tag = 21
      Caption = 'Haut'
      ShortCut = 38
      OnClick = RubriqueClick
    end
    object RubriqueHautDroite: TMenuItem
      Tag = 31
      Caption = 'Haut Droite'
      ShortCut = 33
      OnClick = RubriqueClick
    end
    object Sep1: TMenuItem
      Caption = '-'
    end
    object RubriqueGauche: TMenuItem
      Tag = 12
      Caption = 'Gauche'
      ShortCut = 37
      OnClick = RubriqueClick
    end
    object RubriqueDroite: TMenuItem
      Tag = 32
      Caption = 'Droite'
      ShortCut = 39
      OnClick = RubriqueClick
    end
    object RubriqueZoom: TMenuItem
      Tag = 22
      Caption = 'Zoom (-/+)'
      ShortCut = 90
      OnClick = RubriqueClick
    end
    object Sep2: TMenuItem
      Caption = '-'
    end
    object RubriqueBasGauche: TMenuItem
      Tag = 13
      Caption = 'Bas Gauche'
      ShortCut = 35
      OnClick = RubriqueClick
    end
    object RubriqueBas: TMenuItem
      Tag = 23
      Caption = 'Bas'
      ShortCut = 40
      OnClick = RubriqueClick
    end
    object RubriqueBasDroite: TMenuItem
      Tag = 33
      Caption = 'Bas Droite'
      ShortCut = 34
      OnClick = RubriqueClick
    end
  end
end
