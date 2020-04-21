object frmScore: TfrmScore
  Left = 185
  Top = 193
  BorderIcons = []
  BorderStyle = bsToolWindow
  Caption = 'Score du niveau'
  ClientHeight = 206
  ClientWidth = 304
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 5
    Top = 14
    Width = 79
    Height = 13
    Caption = 'B'#234'tes bloqu'#233'es :'
    Font.Charset = ANSI_CHARSET
    Font.Color = clOlive
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 5
    Top = 50
    Width = 73
    Height = 13
    Caption = 'Temps restant :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 5
    Top = 32
    Width = 63
    Height = 13
    Caption = 'Effet restant :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label10: TLabel
    Left = 215
    Top = 29
    Width = 11
    Height = 20
    Caption = '='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label13: TLabel
    Left = 5
    Top = 86
    Width = 84
    Height = 13
    Caption = 'Barre '#224' atteindre :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label15: TLabel
    Left = 5
    Top = 68
    Width = 84
    Height = 13
    Caption = 'Score du niveau :'
  end
  object Label3: TLabel
    Left = 5
    Top = 104
    Width = 75
    Height = 13
    Caption = 'Total Score :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label7: TLabel
    Left = 144
    Top = 29
    Width = 10
    Height = 20
    Caption = #180
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Symbol'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 144
    Top = 11
    Width = 10
    Height = 20
    Caption = #180
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Symbol'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label8: TLabel
    Left = 144
    Top = 47
    Width = 10
    Height = 20
    Caption = #180
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Symbol'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label9: TLabel
    Left = 215
    Top = 47
    Width = 11
    Height = 20
    Caption = '='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label14: TLabel
    Left = 215
    Top = 11
    Width = 11
    Height = 20
    Caption = '='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelBarreAtteinte: TLabel
    Left = 140
    Top = 86
    Width = 86
    Height = 13
    Caption = 'Barre atteinte !'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
  end
  object PanelScores: TPanel
    Left = 232
    Top = 8
    Width = 66
    Height = 113
    BevelOuter = bvLowered
    TabOrder = 0
    object LabelScBetes: TLabel
      Left = 6
      Top = 5
      Width = 54
      Height = 17
      Caption = '000000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clOlive
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelScTemps: TLabel
      Left = 6
      Top = 41
      Width = 54
      Height = 17
      Caption = '000000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clMaroon
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelScEffet: TLabel
      Left = 6
      Top = 23
      Width = 54
      Height = 17
      Caption = '000000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clGreen
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelBarre: TLabel
      Left = 6
      Top = 77
      Width = 54
      Height = 17
      Caption = '000000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clPurple
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelScNiv: TLabel
      Left = 6
      Top = 59
      Width = 54
      Height = 17
      Caption = '000000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelScore: TLabel
      Left = 6
      Top = 95
      Width = 54
      Height = 17
      Caption = '000000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object PanelNombres: TPanel
    Left = 88
    Top = 8
    Width = 49
    Height = 59
    BevelOuter = bvLowered
    TabOrder = 1
    object LabelNbBetes: TLabel
      Left = 34
      Top = 5
      Width = 9
      Height = 17
      Alignment = taRightJustify
      Caption = '0'
      Font.Charset = ANSI_CHARSET
      Font.Color = clOlive
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelNbTemps: TLabel
      Left = 34
      Top = 41
      Width = 9
      Height = 17
      Alignment = taRightJustify
      Caption = '0'
      Font.Charset = ANSI_CHARSET
      Font.Color = clMaroon
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelNbEffet: TLabel
      Left = 34
      Top = 23
      Width = 9
      Height = 17
      Alignment = taRightJustify
      Caption = '0'
      Font.Charset = ANSI_CHARSET
      Font.Color = clGreen
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object PanelCoefs: TPanel
    Left = 160
    Top = 8
    Width = 49
    Height = 59
    BevelOuter = bvLowered
    TabOrder = 2
    object Label5: TLabel
      Left = 8
      Top = 5
      Width = 36
      Height = 17
      Alignment = taRightJustify
      Caption = '1000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label11: TLabel
      Left = 35
      Top = 41
      Width = 9
      Height = 17
      Alignment = taRightJustify
      Caption = '5'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Left = 17
      Top = 23
      Width = 27
      Height = 17
      Alignment = taRightJustify
      Caption = '100'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object ButtonOk: TButton
    Left = 112
    Top = 136
    Width = 75
    Height = 25
    Caption = '&Vu'
    Default = True
    Enabled = False
    ModalResult = 1
    TabOrder = 3
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 168
    Width = 304
    Height = 19
    Panels = <>
    SimplePanel = True
    SizeGrip = False
  end
  object StatusBarSuiteOuFin: TStatusBar
    Left = 0
    Top = 187
    Width = 304
    Height = 19
    Panels = <>
    SimplePanel = True
    SizeGrip = False
  end
  object TimerDefil: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerDefilTimer
    Left = 104
    Top = 72
  end
end
