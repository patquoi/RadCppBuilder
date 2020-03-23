object frmStatsComposition: TfrmStatsComposition
  Left = 201
  Top = 108
  HelpContext = 315
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Statistiques sur la composition du r'#233'seau'
  ClientHeight = 440
  ClientWidth = 379
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  HelpFile = 'cvw.hlp'
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 56
    Width = 34
    Height = 13
    Caption = 'Routes'
  end
  object Label2: TLabel
    Left = 8
    Top = 120
    Width = 158
    Height = 13
    Caption = ' - Priorit'#233's (sauf priorit'#233's '#224' droite) :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 40
    Width = 24
    Height = 13
    Caption = 'Total'
  end
  object Label4: TLabel
    Left = 147
    Top = 16
    Width = 71
    Height = 13
    Caption = 'Nombre/Cases'
  end
  object Label5: TLabel
    Left = 252
    Top = 16
    Width = 12
    Height = 13
    Caption = '%*'
  end
  object LabelTotal: TLabel
    Left = 211
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
  object LabelTotalPC: TLabel
    Left = 237
    Top = 40
    Width = 40
    Height = 13
    Alignment = taRightJustify
    Caption = '100,00'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelRoutes: TLabel
    Left = 211
    Top = 56
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
  object LabelRoutesPC: TLabel
    Left = 251
    Top = 56
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0,00'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelPrioritesR: TLabel
    Left = 211
    Top = 120
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelPrioritesRPC: TLabel
    Left = 252
    Top = 120
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label6: TLabel
    Left = 16
    Top = 136
    Width = 29
    Height = 13
    Caption = #183' Feux'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label8: TLabel
    Left = 16
    Top = 152
    Width = 90
    Height = 13
    Caption = #183' C'#233'dez-le-passage'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label9: TLabel
    Left = 16
    Top = 168
    Width = 33
    Height = 13
    Caption = #183' Stops'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label10: TLabel
    Left = 300
    Top = 16
    Width = 23
    Height = 13
    Caption = 'Max.'
  end
  object Label11: TLabel
    Left = 343
    Top = 16
    Width = 30
    Height = 13
    Caption = 'Dispo.'
  end
  object LabelFeuxRMax: TLabel
    Left = 315
    Top = 136
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelFeuxRReste: TLabel
    Left = 363
    Top = 136
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelFeuxR: TLabel
    Left = 211
    Top = 136
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelFeuxRPC: TLabel
    Left = 252
    Top = 136
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelClpR: TLabel
    Left = 211
    Top = 152
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelClpRPC: TLabel
    Left = 252
    Top = 152
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelStopsR: TLabel
    Left = 211
    Top = 168
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelStopsRPC: TLabel
    Left = 252
    Top = 168
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label24: TLabel
    Left = 8
    Top = 184
    Width = 102
    Height = 13
    Caption = ' - Directions possibles'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabelDir: TLabel
    Left = 211
    Top = 184
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelDirPC: TLabel
    Left = 252
    Top = 184
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label27: TLabel
    Left = 16
    Top = 200
    Width = 29
    Height = 13
    Caption = #183' Nord'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label28: TLabel
    Left = 16
    Top = 216
    Width = 21
    Height = 13
    Caption = #183' Est'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label29: TLabel
    Left = 16
    Top = 232
    Width = 25
    Height = 13
    Caption = #183' Sud'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabelNord: TLabel
    Left = 211
    Top = 200
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelEst: TLabel
    Left = 211
    Top = 216
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelSud: TLabel
    Left = 211
    Top = 232
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelSudPC: TLabel
    Left = 252
    Top = 232
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelEstPC: TLabel
    Left = 252
    Top = 216
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelNordPC: TLabel
    Left = 252
    Top = 200
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label36: TLabel
    Left = 16
    Top = 248
    Width = 34
    Height = 13
    Caption = #183' Ouest'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabelOuest: TLabel
    Left = 211
    Top = 248
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelOuestPC: TLabel
    Left = 252
    Top = 248
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label12: TLabel
    Left = 8
    Top = 72
    Width = 42
    Height = 13
    Caption = ' - Etapes'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabelEtapes: TLabel
    Left = 211
    Top = 72
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelEtapesPC: TLabel
    Left = 252
    Top = 72
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelEtapesMax: TLabel
    Left = 315
    Top = 72
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelEtapesReste: TLabel
    Left = 363
    Top = 72
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label7: TLabel
    Left = 6
    Top = 373
    Width = 94
    Height = 11
    Caption = '(*) Pourcentage relatif :'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object Label14: TLabel
    Left = 277
    Top = 68
    Width = 3
    Height = 11
    Caption = '1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label15: TLabel
    Left = 277
    Top = 116
    Width = 3
    Height = 11
    Caption = '1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label16: TLabel
    Left = 277
    Top = 180
    Width = 3
    Height = 11
    Caption = '1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label17: TLabel
    Left = 277
    Top = 132
    Width = 5
    Height = 11
    Caption = '2'
    Font.Charset = ANSI_CHARSET
    Font.Color = clPurple
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label18: TLabel
    Left = 277
    Top = 148
    Width = 5
    Height = 11
    Caption = '2'
    Font.Charset = ANSI_CHARSET
    Font.Color = clPurple
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label19: TLabel
    Left = 277
    Top = 164
    Width = 5
    Height = 11
    Caption = '2'
    Font.Charset = ANSI_CHARSET
    Font.Color = clPurple
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label20: TLabel
    Left = 277
    Top = 196
    Width = 5
    Height = 11
    Caption = '3'
    Font.Charset = ANSI_CHARSET
    Font.Color = clMaroon
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label21: TLabel
    Left = 277
    Top = 212
    Width = 5
    Height = 11
    Caption = '3'
    Font.Charset = ANSI_CHARSET
    Font.Color = clMaroon
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label22: TLabel
    Left = 277
    Top = 228
    Width = 5
    Height = 11
    Caption = '3'
    Font.Charset = ANSI_CHARSET
    Font.Color = clMaroon
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label23: TLabel
    Left = 277
    Top = 244
    Width = 5
    Height = 11
    Caption = '3'
    Font.Charset = ANSI_CHARSET
    Font.Color = clMaroon
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label13: TLabel
    Left = 8
    Top = 88
    Width = 71
    Height = 13
    Caption = ' - Arr'#234'ts de bus'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabelArretsBus: TLabel
    Left = 211
    Top = 88
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelArretsBusPC: TLabel
    Left = 252
    Top = 88
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label30: TLabel
    Left = 277
    Top = 84
    Width = 3
    Height = 11
    Caption = '1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object LabelArretsBusMax: TLabel
    Left = 315
    Top = 88
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelArretsBusReste: TLabel
    Left = 363
    Top = 88
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label25: TLabel
    Left = 8
    Top = 280
    Width = 74
    Height = 13
    Caption = ' - Arr'#234'ts de tram'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabelArretsTram: TLabel
    Left = 211
    Top = 280
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelArretsTramPC: TLabel
    Left = 252
    Top = 280
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label32: TLabel
    Left = 277
    Top = 276
    Width = 5
    Height = 11
    Caption = '4'
    Font.Charset = ANSI_CHARSET
    Font.Color = clGreen
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object LabelArretsTramMax: TLabel
    Left = 315
    Top = 280
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelArretsTramReste: TLabel
    Left = 363
    Top = 280
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label26: TLabel
    Left = 8
    Top = 264
    Width = 64
    Height = 13
    Caption = 'Voies de tram'
  end
  object LabelVoiesTram: TLabel
    Left = 211
    Top = 264
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
  object LabelVoiesTramPC: TLabel
    Left = 251
    Top = 264
    Width = 26
    Height = 13
    Alignment = taRightJustify
    Caption = '0,00'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label31: TLabel
    Left = 6
    Top = 385
    Width = 358
    Height = 11
    Caption = 
      '(0) % des cases, (1) des routes, (2) des priorit'#233's, (3) des dire' +
      'ctions, (4) des voies de tram.'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label33: TLabel
    Left = 277
    Top = 52
    Width = 5
    Height = 11
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label34: TLabel
    Left = 277
    Top = 260
    Width = 5
    Height = 11
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Bevel1: TBevel
    Left = 3
    Top = 32
    Width = 374
    Height = 2
  end
  object Bevel2: TBevel
    Left = 5
    Top = 364
    Width = 374
    Height = 2
  end
  object Label35: TLabel
    Left = 8
    Top = 296
    Width = 158
    Height = 13
    Caption = ' - Priorit'#233's (sauf priorit'#233's '#224' droite) :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabelPrioritesV: TLabel
    Left = 211
    Top = 296
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelPrioritesVPC: TLabel
    Left = 252
    Top = 296
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label39: TLabel
    Left = 16
    Top = 312
    Width = 29
    Height = 13
    Caption = #183' Feux'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label40: TLabel
    Left = 16
    Top = 328
    Width = 90
    Height = 13
    Caption = #183' C'#233'dez-le-passage'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label41: TLabel
    Left = 16
    Top = 344
    Width = 33
    Height = 13
    Caption = #183' Stops'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabelFeuxVMax: TLabel
    Left = 315
    Top = 312
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelFeuxVReste: TLabel
    Left = 363
    Top = 312
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelFeuxV: TLabel
    Left = 211
    Top = 312
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelFeuxVPC: TLabel
    Left = 252
    Top = 312
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelClpV: TLabel
    Left = 211
    Top = 328
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelClpVPC: TLabel
    Left = 252
    Top = 328
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelStopsV: TLabel
    Left = 211
    Top = 344
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelStopsVPC: TLabel
    Left = 252
    Top = 344
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label50: TLabel
    Left = 277
    Top = 292
    Width = 5
    Height = 11
    Caption = '4'
    Font.Charset = ANSI_CHARSET
    Font.Color = clGreen
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label51: TLabel
    Left = 277
    Top = 308
    Width = 5
    Height = 11
    Caption = '2'
    Font.Charset = ANSI_CHARSET
    Font.Color = clPurple
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label52: TLabel
    Left = 277
    Top = 324
    Width = 5
    Height = 11
    Caption = '2'
    Font.Charset = ANSI_CHARSET
    Font.Color = clPurple
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label53: TLabel
    Left = 277
    Top = 340
    Width = 5
    Height = 11
    Caption = '2'
    Font.Charset = ANSI_CHARSET
    Font.Color = clPurple
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label37: TLabel
    Left = 177
    Top = 373
    Width = 189
    Height = 11
    Caption = '(**) Sur routes et sur voies de tram confondus.'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object Label38: TLabel
    Left = 323
    Top = 134
    Width = 8
    Height = 13
    Caption = '**'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label42: TLabel
    Left = 371
    Top = 134
    Width = 8
    Height = 13
    Caption = '**'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label43: TLabel
    Left = 371
    Top = 310
    Width = 8
    Height = 13
    Caption = '**'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label44: TLabel
    Left = 323
    Top = 310
    Width = 8
    Height = 13
    Caption = '**'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label45: TLabel
    Left = 8
    Top = 104
    Width = 75
    Height = 13
    Caption = ' - Places de taxi'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabelPlacesTaxi: TLabel
    Left = 211
    Top = 104
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label47: TLabel
    Left = 277
    Top = 100
    Width = 3
    Height = 11
    Caption = '1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentFont = False
  end
  object LabelPlacesTaxiPC: TLabel
    Left = 252
    Top = 104
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Caption = 'N/D'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelPlacesTaxiMax: TLabel
    Left = 315
    Top = 104
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelPlacesTaxiReste: TLabel
    Left = 363
    Top = 104
    Width = 8
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object ButtonOk: TButton
    Left = 112
    Top = 408
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Vu'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object ButtonAide: TButton
    Left = 200
    Top = 408
    Width = 75
    Height = 25
    Caption = '&Aide'
    TabOrder = 1
    OnClick = ButtonAideClick
  end
end
