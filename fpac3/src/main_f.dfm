object FormMain: TFormMain
  Left = 261
  Top = -7
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'FPac III'
  ClientHeight = 341
  ClientWidth = 353
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object DrawGridJeu: TDrawGrid
    Left = 0
    Top = 0
    Width = 353
    Height = 293
    TabStop = False
    Align = alClient
    BorderStyle = bsNone
    Color = clBlack
    ColCount = 48
    DefaultColWidth = 16
    DefaultRowHeight = 16
    DefaultDrawing = False
    DoubleBuffered = True
    DrawingStyle = gdsClassic
    FixedColor = clBlack
    FixedCols = 0
    RowCount = 30
    FixedRows = 0
    GridLineWidth = 0
    Options = []
    ParentDoubleBuffered = False
    ScrollBars = ssNone
    TabOrder = 0
    OnDrawCell = DrawGridJeuDrawCell
  end
  object DrawGridMsg: TDrawGrid
    Left = 0
    Top = 309
    Width = 353
    Height = 32
    TabStop = False
    Align = alBottom
    BorderStyle = bsNone
    Color = clBlack
    ColCount = 48
    DefaultColWidth = 16
    DefaultRowHeight = 16
    DefaultDrawing = False
    DoubleBuffered = True
    DrawingStyle = gdsClassic
    FixedColor = clBlack
    FixedCols = 0
    RowCount = 2
    FixedRows = 0
    GridLineWidth = 0
    Options = []
    ParentDoubleBuffered = False
    ScrollBars = ssNone
    TabOrder = 1
    OnDrawCell = DrawGridMsgDrawCell
  end
  object DrawGridPts: TDrawGrid
    Left = 0
    Top = 293
    Width = 353
    Height = 16
    TabStop = False
    Align = alBottom
    BorderStyle = bsNone
    Color = clBlack
    ColCount = 48
    DefaultColWidth = 16
    DefaultRowHeight = 16
    DefaultDrawing = False
    DoubleBuffered = True
    DrawingStyle = gdsClassic
    FixedColor = clBlack
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    GridLineWidth = 0
    Options = []
    ParentDoubleBuffered = False
    ScrollBars = ssNone
    TabOrder = 2
    OnDrawCell = DrawGridPtsDrawCell
  end
  object MainMenu: TMainMenu
    object MenuItemPartie: TMenuItem
      Caption = '&Partie'
      object MenuItemJouer: TMenuItem
        Action = ActionPartieJouer
      end
    end
    object MenuItemParametres: TMenuItem
      Caption = 'Pa&ram'#232'tres'
      object MenuItemDimensions: TMenuItem
        Caption = '&Dimensions'
        object MenuItemDimensions1: TMenuItem
          Action = ActionParamDimensions48x30
          GroupIndex = 1
          RadioItem = True
        end
        object MenuItemDimensions2: TMenuItem
          Action = ActionParamDimensions64x40
          GroupIndex = 1
          RadioItem = True
        end
        object MenuItemDimensions3: TMenuItem
          Action = ActionParamDimensions80x50
          GroupIndex = 1
          RadioItem = True
        end
        object MenuItemDimensions4: TMenuItem
          Action = ActionParamDimensions96x60
          GroupIndex = 1
          Hint = 'Dimensions pour une r'#233'solution minimale de 1600x1200'
          RadioItem = True
        end
        object MenuItemDimensions5: TMenuItem
          Action = ActionParamDimensions112x70
          GroupIndex = 1
          Hint = 'Dimensions pour une r'#233'solution minimale de 1800x1440'
          RadioItem = True
        end
      end
      object MenuItemAgressivite: TMenuItem
        Caption = '&Agressit'#233' des fant'#244'mes'
        object MenuItemVitesse1: TMenuItem
          Action = ActionParamAgressivite25
          GroupIndex = 2
          RadioItem = True
        end
        object MenuItemVitesse2: TMenuItem
          Action = ActionParamAgressivite33
          GroupIndex = 2
          RadioItem = True
        end
        object MenuItemVitesse3: TMenuItem
          Action = ActionParamAgressivite50
          GroupIndex = 2
          RadioItem = True
        end
      end
      object MenuItemNbPilules: TMenuItem
        Caption = 'Rapport &Pilules/Pacgums'
        object MenuItem50Pilules: TMenuItem
          Action = ActionParamPilulesParPacgum50
          AutoCheck = True
          GroupIndex = 3
          RadioItem = True
        end
        object MenuItem100Pilules: TMenuItem
          Action = ActionParamPilulesParPacgum100
          AutoCheck = True
          GroupIndex = 3
          RadioItem = True
        end
        object MenuItem200Pilules: TMenuItem
          Action = ActionParamPilulesParPacgum150
          AutoCheck = True
          GroupIndex = 3
          RadioItem = True
        end
      end
      object MenuItemVulnerabilite: TMenuItem
        Caption = 'Dur'#233'e &Vuln'#233'rabilit'#233' Fant'#244'mes'
        object MenuItemVulnerabilite1: TMenuItem
          Action = ActionParamVulnerabilite100Cases
          GroupIndex = 4
          RadioItem = True
        end
        object MenuItemVulnerabilite2: TMenuItem
          Action = ActionParamVulnerabilite50Cases
          GroupIndex = 4
          RadioItem = True
        end
        object MenuItemVulnerabilite3: TMenuItem
          Action = ActionParamVulnerabilite25Cases
          GroupIndex = 4
          RadioItem = True
        end
      end
      object MenuItemFantomesDepart: TMenuItem
        Caption = 'Nombre de &Fant'#244'mes au d'#233'part'
        object MenuItemFantomesDepart3: TMenuItem
          Action = ActionParamDepartFantomes3
          GroupIndex = 5
          RadioItem = True
        end
        object MenuItemFantomesDepart4: TMenuItem
          Action = ActionParamDepartFantomes4
          GroupIndex = 5
          RadioItem = True
        end
        object MenuItemFantomesDepart5: TMenuItem
          Action = ActionParamDepartFantomes5
          GroupIndex = 5
          RadioItem = True
        end
        object MenuItemFantomesDepart6: TMenuItem
          Action = ActionParamDepartFantomes6
          GroupIndex = 5
          RadioItem = True
        end
      end
      object MenuItemNbPortes: TMenuItem
        Caption = '&Nombre de portes'
        object MenuItem1PortesPour2lignes: TMenuItem
          Action = ActionParamPortes1Pour150Cases
          GroupIndex = 6
          RadioItem = True
        end
        object MenuItem2PortesPour2lignes: TMenuItem
          Action = ActionParamPortes1Pour75Cases
          GroupIndex = 6
          RadioItem = True
        end
        object MenuItem3PortesPour2lignes: TMenuItem
          Action = ActionParamPortes1Pour50Cases
          GroupIndex = 6
          RadioItem = True
        end
      end
      object MenuItemSeparatorA: TMenuItem
        Caption = '-'
      end
      object ActionParamEnregistrer1: TMenuItem
        Action = ActionParamEnregistrer
      end
      object Restaurerlesparamtrespardfaut1: TMenuItem
        Action = ActionParamRestaurer
      end
      object RinitialiserleTop101: TMenuItem
        Action = ActionParamReinitialiserTop10
      end
    end
    object MenuItemInfo: TMenuItem
      Caption = '&?'
      object MenuItemAPropos: TMenuItem
        Action = ActionInfosAPropos
      end
      object MenuItemCommandes: TMenuItem
        Action = ActionInfosCommandes
      end
      object Rgledujeu1: TMenuItem
        Action = ActionInfosRegleDuJeu
      end
      object Lgende1: TMenuItem
        Action = ActionInfosLegende
      end
      object Top101: TMenuItem
        Action = ActionInfosTop10
      end
    end
  end
  object ActionList: TActionList
    Left = 32
    object ActionParamDimensions48x30: TAction
      Category = 'Param'#232'tres'
      Caption = '48 x 30'
      Checked = True
      GroupIndex = 1
      Hint = 'Dimensions pour une r'#233'solution minimale de 800x600'
      ShortCut = 112
      OnExecute = ActionDimensionsExecute
    end
    object ActionParamDimensions64x40: TAction
      Tag = 1
      Category = 'Param'#232'tres'
      Caption = '64 x 40'
      Enabled = False
      GroupIndex = 1
      Hint = 'Dimensions pour une r'#233'solution minimale de 1024x768'
      ShortCut = 113
      OnExecute = ActionDimensionsExecute
    end
    object ActionParamDimensions80x50: TAction
      Tag = 2
      Category = 'Param'#232'tres'
      Caption = '80 x 50'
      Enabled = False
      GroupIndex = 1
      Hint = 'Dimensions pour une r'#233'solution minimale de 1280x1024'
      ShortCut = 114
      OnExecute = ActionDimensionsExecute
    end
    object ActionParamDimensions96x60: TAction
      Tag = 3
      Category = 'Param'#232'tres'
      Caption = '96 x 60'
      Enabled = False
      GroupIndex = 1
      Hint = 'Dimensions pour une r'#233'solution minimale de 1280x1024'
      OnExecute = ActionDimensionsExecute
    end
    object ActionParamDimensions112x70: TAction
      Tag = 4
      Category = 'Param'#232'tres'
      Caption = '112 x 70'
      Enabled = False
      GroupIndex = 1
      Hint = 'Dimensions pour une r'#233'solution minimale de 1600x1200'
      OnExecute = ActionDimensionsExecute
    end
    object ActionParamAgressivite25: TAction
      Category = 'Param'#232'tres'
      Caption = '&25%'
      Checked = True
      GroupIndex = 2
      ShortCut = 115
      OnExecute = ActionAgressiviteExecute
    end
    object ActionParamAgressivite33: TAction
      Tag = 1
      Category = 'Param'#232'tres'
      Caption = '&33%'
      GroupIndex = 2
      ShortCut = 116
      OnExecute = ActionAgressiviteExecute
    end
    object ActionParamAgressivite50: TAction
      Tag = 2
      Category = 'Param'#232'tres'
      Caption = '&50%'
      GroupIndex = 2
      ShortCut = 117
      OnExecute = ActionAgressiviteExecute
    end
    object ActionParamPilulesParPacgum50: TAction
      Category = 'Param'#232'tres'
      Caption = '1 Pacgum pour &50 pilules'
      GroupIndex = 3
      ShortCut = 118
      OnExecute = Action1PGxxxPExecute
    end
    object ActionParamPilulesParPacgum100: TAction
      Tag = 1
      Category = 'Param'#232'tres'
      Caption = '1 Pacgum pour 1&00 pilules'
      Checked = True
      GroupIndex = 3
      ShortCut = 119
      OnExecute = Action1PGxxxPExecute
    end
    object ActionInfosAPropos: TAction
      Category = 'Infos'
      Caption = #192' &propos...'
      ShortCut = 24656
      OnExecute = ActionInfosAProposExecute
    end
    object ActionParamPilulesParPacgum150: TAction
      Tag = 2
      Category = 'Param'#232'tres'
      Caption = '1 Pacgum pour 1&50 pilules'
      GroupIndex = 3
      ShortCut = 120
      OnExecute = Action1PGxxxPExecute
    end
    object ActionParamVulnerabilite100Cases: TAction
      Category = 'Param'#232'tres'
      Caption = '&100 cases'
      GroupIndex = 4
      ShortCut = 121
      OnExecute = ActionxxCasesExecute
    end
    object ActionParamVulnerabilite50Cases: TAction
      Tag = 1
      Category = 'Param'#232'tres'
      Caption = '&50 cases'
      Checked = True
      GroupIndex = 4
      ShortCut = 122
      OnExecute = ActionxxCasesExecute
    end
    object ActionParamVulnerabilite25Cases: TAction
      Tag = 2
      Category = 'Param'#232'tres'
      Caption = '&25 cases'
      GroupIndex = 4
      ShortCut = 123
      OnExecute = ActionxxCasesExecute
    end
    object ActionParamDepartFantomes3: TAction
      Category = 'Param'#232'tres'
      Caption = '&3 Fant'#244'mes'
      GroupIndex = 5
      ShortCut = 8306
      OnExecute = ActionDepartFantomesExecute
    end
    object ActionParamDepartFantomes4: TAction
      Tag = 1
      Category = 'Param'#232'tres'
      Caption = '&4 Fant'#244'mes'
      Checked = True
      GroupIndex = 5
      ShortCut = 8307
      OnExecute = ActionDepartFantomesExecute
    end
    object ActionParamDepartFantomes5: TAction
      Tag = 2
      Category = 'Param'#232'tres'
      Caption = '&5 Fant'#244'mes'
      GroupIndex = 5
      ShortCut = 8308
      OnExecute = ActionDepartFantomesExecute
    end
    object ActionParamDepartFantomes6: TAction
      Tag = 3
      Category = 'Param'#232'tres'
      Caption = '&6 Fant'#244'mes'
      GroupIndex = 5
      ShortCut = 8309
      OnExecute = ActionDepartFantomesExecute
    end
    object ActionPartieJouer: TAction
      Category = 'Partie'
      Caption = '&Jouer !'
      ShortCut = 16458
      OnExecute = ActionPartieJouerExecute
    end
    object ActionInfosCommandes: TAction
      Category = 'Infos'
      Caption = '&Commandes'
      ShortCut = 24643
      OnExecute = ActionInfosCommandesExecute
    end
    object ActionParamPortes1Pour150Cases: TAction
      Category = 'Param'#232'tres'
      Caption = '1 porte toutes les &150 cases'
      GroupIndex = 6
      ShortCut = 16496
      OnExecute = ActionParamPortesNPour2LignesExecute
    end
    object ActionParamPortes1Pour75Cases: TAction
      Tag = 1
      Category = 'Param'#232'tres'
      Caption = '1 porte toutes les &75 cases'
      Checked = True
      GroupIndex = 6
      ShortCut = 16497
      OnExecute = ActionParamPortesNPour2LignesExecute
    end
    object ActionParamPortes1Pour50Cases: TAction
      Tag = 2
      Category = 'Param'#232'tres'
      Caption = '1 porte toutes les &50 cases'
      GroupIndex = 6
      ShortCut = 16498
      OnExecute = ActionParamPortesNPour2LignesExecute
    end
    object ActionInfosRegleDuJeu: TAction
      Category = 'Infos'
      Caption = '&R'#232'gle du jeu'
      ShortCut = 24658
      OnExecute = ActionInfosRegleDuJeuExecute
    end
    object ActionInfosLegende: TAction
      Category = 'Infos'
      Caption = '&L'#233'gende'
      ShortCut = 24652
      OnExecute = ActionInfosLegendeExecute
    end
    object ActionInfosTop10: TAction
      Category = 'Infos'
      Caption = '&Top 10'
      ShortCut = 24660
      OnExecute = ActionInfosTop10Execute
    end
    object ActionParamEnregistrer: TAction
      Category = 'Param'#232'tres'
      Caption = '&Enregistrer les param'#232'tres'
      ShortCut = 16467
      OnExecute = ActionParamEnregistrerExecute
    end
    object ActionParamRestaurer: TAction
      Category = 'Param'#232'tres'
      Caption = '&Restaurer les param'#232'tres'
      ShortCut = 16466
      OnExecute = ActionParamRestaurerExecute
    end
    object ActionParamReinitialiserTop10: TAction
      Category = 'Param'#232'tres'
      Caption = 'R'#233'initialiser le &Top 10'
      ShortCut = 16468
      OnExecute = ActionParamReinitialiserTop10Execute
    end
  end
  object TimerMsg: TTimer
    Interval = 25
    OnTimer = TimerMsgTimer
    Top = 32
  end
  object TimerJeu: TTimer
    Enabled = False
    Interval = 150
    OnTimer = TimerJeuTimer
    Top = 64
  end
  object TimerDemo: TTimer
    Interval = 5000
    OnTimer = TimerDemoTimer
    Top = 96
  end
  object TimerTop10: TTimer
    Enabled = False
    Interval = 10
    OnTimer = TimerTop10Timer
    Top = 128
  end
  object VirtualImageListJeu: TVirtualImageList
    AutoFillMode = afmDisabled
    DisabledGrayscale = False
    DisabledSuffix = '_Disabled'
    Images = <
      item
        CollectionIndex = 140
        CollectionName = 'El'#233'ments\Pillule'
        Disabled = False
        Name = 'Pillule'
      end
      item
        CollectionIndex = 118
        CollectionName = 'El'#233'ments\PacGum'
        Disabled = False
        Name = 'PacGum'
      end
      item
        CollectionIndex = 117
        CollectionName = 'El'#233'ments\Mur'
        Disabled = False
        Name = 'Mur'
      end
      item
        CollectionIndex = 128
        CollectionName = 'Pacman\PacManEntierBFNord'
        Disabled = False
        Name = 'PacManEntierBFNord'
      end
      item
        CollectionIndex = 132
        CollectionName = 'Pacman\PacManEntierBONord'
        Disabled = False
        Name = 'PacManEntierBONord'
      end
      item
        CollectionIndex = 127
        CollectionName = 'Pacman\PacManEntierBFEst'
        Disabled = False
        Name = 'PacManEntierBFEst'
      end
      item
        CollectionIndex = 131
        CollectionName = 'Pacman\PacManEntierBOEst'
        Disabled = False
        Name = 'PacManEntierBOEst'
      end
      item
        CollectionIndex = 130
        CollectionName = 'Pacman\PacManEntierBFSud'
        Disabled = False
        Name = 'PacManEntierBFSud'
      end
      item
        CollectionIndex = 134
        CollectionName = 'Pacman\PacManEntierBOSud'
        Disabled = False
        Name = 'PacManEntierBOSud'
      end
      item
        CollectionIndex = 129
        CollectionName = 'Pacman\PacManEntierBFOuest'
        Disabled = False
        Name = 'PacManEntierBFOuest'
      end
      item
        CollectionIndex = 133
        CollectionName = 'Pacman\PacManEntierBOOuest'
        Disabled = False
        Name = 'PacManEntierBOOuest'
      end
      item
        CollectionIndex = 120
        CollectionName = 'Pacman\PacManArri'#232'reNord'
        Disabled = False
        Name = 'PacManArri'#232'reNord'
      end
      item
        CollectionIndex = 124
        CollectionName = 'Pacman\PacManAvantNord'
        Disabled = False
        Name = 'PacManAvantNord'
      end
      item
        CollectionIndex = 119
        CollectionName = 'Pacman\PacManArri'#232'reEst'
        Disabled = False
        Name = 'PacManArri'#232'reEst'
      end
      item
        CollectionIndex = 123
        CollectionName = 'Pacman\PacManAvantEst'
        Disabled = False
        Name = 'PacManAvantEst'
      end
      item
        CollectionIndex = 122
        CollectionName = 'Pacman\PacManArri'#232'reSud'
        Disabled = False
        Name = 'PacManArri'#232'reSud'
      end
      item
        CollectionIndex = 126
        CollectionName = 'Pacman\PacManAvantSud'
        Disabled = False
        Name = 'PacManAvantSud'
      end
      item
        CollectionIndex = 121
        CollectionName = 'Pacman\PacManArri'#232'reOuest'
        Disabled = False
        Name = 'PacManArri'#232'reOuest'
      end
      item
        CollectionIndex = 125
        CollectionName = 'Pacman\PacManAvantOuest'
        Disabled = False
        Name = 'PacManAvantOuest'
      end
      item
        CollectionIndex = 24
        CollectionName = 'Fantomes\FantomeBleuEntierNord'
        Disabled = False
        Name = 'FantomeBleuEntierNord'
      end
      item
        CollectionIndex = 23
        CollectionName = 'Fantomes\FantomeBleuEntierEst'
        Disabled = False
        Name = 'FantomeBleuEntierEst'
      end
      item
        CollectionIndex = 26
        CollectionName = 'Fantomes\FantomeBleuEntierSud'
        Disabled = False
        Name = 'FantomeBleuEntierSud'
      end
      item
        CollectionIndex = 25
        CollectionName = 'Fantomes\FantomeBleuEntierOuest'
        Disabled = False
        Name = 'FantomeBleuEntierOuest'
      end
      item
        CollectionIndex = 35
        CollectionName = 'Fantomes\FantomeCielEntierNord'
        Disabled = False
        Name = 'FantomeCielEntierNord'
      end
      item
        CollectionIndex = 34
        CollectionName = 'Fantomes\FantomeCielEntierEst'
        Disabled = False
        Name = 'FantomeCielEntierEst'
      end
      item
        CollectionIndex = 37
        CollectionName = 'Fantomes\FantomeCielEntierSud'
        Disabled = False
        Name = 'FantomeCielEntierSud'
      end
      item
        CollectionIndex = 36
        CollectionName = 'Fantomes\FantomeCielEntierOuest'
        Disabled = False
        Name = 'FantomeCielEntierOuest'
      end
      item
        CollectionIndex = 57
        CollectionName = 'Fantomes\FantomeMagentaEntierNord'
        Disabled = False
        Name = 'FantomeMagentaEntierNord'
      end
      item
        CollectionIndex = 56
        CollectionName = 'Fantomes\FantomeMagentaEntierEst'
        Disabled = False
        Name = 'FantomeMagentaEntierEst'
      end
      item
        CollectionIndex = 59
        CollectionName = 'Fantomes\FantomeMagentaEntierSud'
        Disabled = False
        Name = 'FantomeMagentaEntierSud'
      end
      item
        CollectionIndex = 58
        CollectionName = 'Fantomes\FantomeMagentaEntierOuest'
        Disabled = False
        Name = 'FantomeMagentaEntierOuest'
      end
      item
        CollectionIndex = 68
        CollectionName = 'Fantomes\FantomeRougeEntierNord'
        Disabled = False
        Name = 'FantomeRougeEntierNord'
      end
      item
        CollectionIndex = 67
        CollectionName = 'Fantomes\FantomeRougeEntierEst'
        Disabled = False
        Name = 'FantomeRougeEntierEst'
      end
      item
        CollectionIndex = 70
        CollectionName = 'Fantomes\FantomeRougeEntierSud'
        Disabled = False
        Name = 'FantomeRougeEntierSud'
      end
      item
        CollectionIndex = 69
        CollectionName = 'Fantomes\FantomeRougeEntierOuest'
        Disabled = False
        Name = 'FantomeRougeEntierOuest'
      end
      item
        CollectionIndex = 79
        CollectionName = 'Fantomes\FantomeVertEntierNord'
        Disabled = False
        Name = 'FantomeVertEntierNord'
      end
      item
        CollectionIndex = 78
        CollectionName = 'Fantomes\FantomeVertEntierEst'
        Disabled = False
        Name = 'FantomeVertEntierEst'
      end
      item
        CollectionIndex = 81
        CollectionName = 'Fantomes\FantomeVertEntierSud'
        Disabled = False
        Name = 'FantomeVertEntierSud'
      end
      item
        CollectionIndex = 80
        CollectionName = 'Fantomes\FantomeVertEntierOuest'
        Disabled = False
        Name = 'FantomeVertEntierOuest'
      end
      item
        CollectionIndex = 46
        CollectionName = 'Fantomes\FantomeGrisEntierNord'
        Disabled = False
        Name = 'FantomeGrisEntierNord'
      end
      item
        CollectionIndex = 45
        CollectionName = 'Fantomes\FantomeGrisEntierEst'
        Disabled = False
        Name = 'FantomeGrisEntierEst'
      end
      item
        CollectionIndex = 48
        CollectionName = 'Fantomes\FantomeGrisEntierSud'
        Disabled = False
        Name = 'FantomeGrisEntierSud'
      end
      item
        CollectionIndex = 47
        CollectionName = 'Fantomes\FantomeGrisEntierOuest'
        Disabled = False
        Name = 'FantomeGrisEntierOuest'
      end
      item
        CollectionIndex = 19
        CollectionName = 'Fantomes\FantomeBleuArrNAvtS'
        Disabled = False
        Name = 'FantomeBleuArrNAvtS'
      end
      item
        CollectionIndex = 16
        CollectionName = 'Fantomes\FantomeBleuArri'#232'reEst'
        Disabled = False
        Name = 'FantomeBleuArri'#232'reEst'
      end
      item
        CollectionIndex = 18
        CollectionName = 'Fantomes\FantomeBleuArri'#232'reSud'
        Disabled = False
        Name = 'FantomeBleuArri'#232'reSud'
      end
      item
        CollectionIndex = 17
        CollectionName = 'Fantomes\FantomeBleuArri'#232'reOuest'
        Disabled = False
        Name = 'FantomeBleuArri'#232'reOuest'
      end
      item
        CollectionIndex = 30
        CollectionName = 'Fantomes\FantomeCielArrNAvtS'
        Disabled = False
        Name = 'FantomeCielArrNAvtS'
      end
      item
        CollectionIndex = 27
        CollectionName = 'Fantomes\FantomeCielArri'#232'reEst'
        Disabled = False
        Name = 'FantomeCielArri'#232'reEst'
      end
      item
        CollectionIndex = 29
        CollectionName = 'Fantomes\FantomeCielArri'#232'reSud'
        Disabled = False
        Name = 'FantomeCielArri'#232'reSud'
      end
      item
        CollectionIndex = 28
        CollectionName = 'Fantomes\FantomeCielArri'#232'reOuest'
        Disabled = False
        Name = 'FantomeCielArri'#232'reOuest'
      end
      item
        CollectionIndex = 52
        CollectionName = 'Fantomes\FantomeMagentaArrNAvtS'
        Disabled = False
        Name = 'FantomeMagentaArrNAvtS'
      end
      item
        CollectionIndex = 49
        CollectionName = 'Fantomes\FantomeMagentaArri'#232'reEst'
        Disabled = False
        Name = 'FantomeMagentaArri'#232'reEst'
      end
      item
        CollectionIndex = 51
        CollectionName = 'Fantomes\FantomeMagentaArri'#232'reSud'
        Disabled = False
        Name = 'FantomeMagentaArri'#232'reSud'
      end
      item
        CollectionIndex = 50
        CollectionName = 'Fantomes\FantomeMagentaArri'#232'reOuest'
        Disabled = False
        Name = 'FantomeMagentaArri'#232'reOuest'
      end
      item
        CollectionIndex = 63
        CollectionName = 'Fantomes\FantomeRougeArrNAvtS'
        Disabled = False
        Name = 'FantomeRougeArrNAvtS'
      end
      item
        CollectionIndex = 60
        CollectionName = 'Fantomes\FantomeRougeArri'#232'reEst'
        Disabled = False
        Name = 'FantomeRougeArri'#232'reEst'
      end
      item
        CollectionIndex = 62
        CollectionName = 'Fantomes\FantomeRougeArri'#232'reSud'
        Disabled = False
        Name = 'FantomeRougeArri'#232'reSud'
      end
      item
        CollectionIndex = 61
        CollectionName = 'Fantomes\FantomeRougeArri'#232'reOuest'
        Disabled = False
        Name = 'FantomeRougeArri'#232'reOuest'
      end
      item
        CollectionIndex = 74
        CollectionName = 'Fantomes\FantomeVertArrNAvtS'
        Disabled = False
        Name = 'FantomeVertArrNAvtS'
      end
      item
        CollectionIndex = 71
        CollectionName = 'Fantomes\FantomeVertArri'#232'reEst'
        Disabled = False
        Name = 'FantomeVertArri'#232'reEst'
      end
      item
        CollectionIndex = 73
        CollectionName = 'Fantomes\FantomeVertArri'#232'reSud'
        Disabled = False
        Name = 'FantomeVertArri'#232'reSud'
      end
      item
        CollectionIndex = 72
        CollectionName = 'Fantomes\FantomeVertArri'#232'reOuest'
        Disabled = False
        Name = 'FantomeVertArri'#232'reOuest'
      end
      item
        CollectionIndex = 41
        CollectionName = 'Fantomes\FantomeGrisArrNAvtS'
        Disabled = False
        Name = 'FantomeGrisArrNAvtS'
      end
      item
        CollectionIndex = 38
        CollectionName = 'Fantomes\FantomeGrisArri'#232'reEst'
        Disabled = False
        Name = 'FantomeGrisArri'#232'reEst'
      end
      item
        CollectionIndex = 40
        CollectionName = 'Fantomes\FantomeGrisArri'#232'reSud'
        Disabled = False
        Name = 'FantomeGrisArri'#232'reSud'
      end
      item
        CollectionIndex = 39
        CollectionName = 'Fantomes\FantomeGrisArri'#232'reOuest'
        Disabled = False
        Name = 'FantomeGrisArri'#232'reOuest'
      end
      item
        CollectionIndex = 21
        CollectionName = 'Fantomes\FantomeBleuAvantNord'
        Disabled = False
        Name = 'FantomeBleuAvantNord'
      end
      item
        CollectionIndex = 20
        CollectionName = 'Fantomes\FantomeBleuAvantEst'
        Disabled = False
        Name = 'FantomeBleuAvantEst'
      end
      item
        CollectionIndex = 183
        CollectionName = 'Fantomes\FantomeBleuAvtSArrN'
        Disabled = False
        Name = 'FantomeBleuAvtSArrN'
      end
      item
        CollectionIndex = 22
        CollectionName = 'Fantomes\FantomeBleuAvantOuest'
        Disabled = False
        Name = 'FantomeBleuAvantOuest'
      end
      item
        CollectionIndex = 32
        CollectionName = 'Fantomes\FantomeCielAvantNord'
        Disabled = False
        Name = 'FantomeCielAvantNord'
      end
      item
        CollectionIndex = 31
        CollectionName = 'Fantomes\FantomeCielAvantEst'
        Disabled = False
        Name = 'FantomeCielAvantEst'
      end
      item
        CollectionIndex = 184
        CollectionName = 'Fantomes\FantomeCielAvtSArrN'
        Disabled = False
        Name = 'FantomeCielAvtSArrN'
      end
      item
        CollectionIndex = 33
        CollectionName = 'Fantomes\FantomeCielAvantOuest'
        Disabled = False
        Name = 'FantomeCielAvantOuest'
      end
      item
        CollectionIndex = 54
        CollectionName = 'Fantomes\FantomeMagentaAvantNord'
        Disabled = False
        Name = 'FantomeMagentaAvantNord'
      end
      item
        CollectionIndex = 53
        CollectionName = 'Fantomes\FantomeMagentaAvantEst'
        Disabled = False
        Name = 'FantomeMagentaAvantEst'
      end
      item
        CollectionIndex = 186
        CollectionName = 'Fantomes\FantomeMagentaAvtSArrN'
        Disabled = False
        Name = 'FantomeMagentaAvtSArrN'
      end
      item
        CollectionIndex = 55
        CollectionName = 'Fantomes\FantomeMagentaAvantOuest'
        Disabled = False
        Name = 'FantomeMagentaAvantOuest'
      end
      item
        CollectionIndex = 65
        CollectionName = 'Fantomes\FantomeRougeAvantNord'
        Disabled = False
        Name = 'FantomeRougeAvantNord'
      end
      item
        CollectionIndex = 64
        CollectionName = 'Fantomes\FantomeRougeAvantEst'
        Disabled = False
        Name = 'FantomeRougeAvantEst'
      end
      item
        CollectionIndex = 187
        CollectionName = 'Fantomes\FantomeRougeAvtSArrN'
        Disabled = False
        Name = 'FantomeRougeAvtSArrN'
      end
      item
        CollectionIndex = 66
        CollectionName = 'Fantomes\FantomeRougeAvantOuest'
        Disabled = False
        Name = 'FantomeRougeAvantOuest'
      end
      item
        CollectionIndex = 76
        CollectionName = 'Fantomes\FantomeVertAvantNord'
        Disabled = False
        Name = 'FantomeVertAvantNord'
      end
      item
        CollectionIndex = 75
        CollectionName = 'Fantomes\FantomeVertAvantEst'
        Disabled = False
        Name = 'FantomeVertAvantEst'
      end
      item
        CollectionIndex = 188
        CollectionName = 'Fantomes\FantomeVertAvtSArrN'
        Disabled = False
        Name = 'FantomeVertAvtSArrN'
      end
      item
        CollectionIndex = 77
        CollectionName = 'Fantomes\FantomeVertAvantOuest'
        Disabled = False
        Name = 'FantomeVertAvantOuest'
      end
      item
        CollectionIndex = 43
        CollectionName = 'Fantomes\FantomeGrisAvantNord'
        Disabled = False
        Name = 'FantomeGrisAvantNord'
      end
      item
        CollectionIndex = 42
        CollectionName = 'Fantomes\FantomeGrisAvantEst'
        Disabled = False
        Name = 'FantomeGrisAvantEst'
      end
      item
        CollectionIndex = 185
        CollectionName = 'Fantomes\FantomeGrisAvtSArrN'
        Disabled = False
        Name = 'FantomeGrisAvtSArrN'
      end
      item
        CollectionIndex = 44
        CollectionName = 'Fantomes\FantomeGrisAvantOuest'
        Disabled = False
        Name = 'FantomeGrisAvantOuest'
      end
      item
        CollectionIndex = 150
        CollectionName = 'Score\Score100'
        Disabled = False
        Name = 'Score100'
      end
      item
        CollectionIndex = 151
        CollectionName = 'Score\Score200'
        Disabled = False
        Name = 'Score200'
      end
      item
        CollectionIndex = 152
        CollectionName = 'Score\Score300'
        Disabled = False
        Name = 'Score300'
      end
      item
        CollectionIndex = 153
        CollectionName = 'Score\Score400'
        Disabled = False
        Name = 'Score400'
      end
      item
        CollectionIndex = 154
        CollectionName = 'Score\Score500'
        Disabled = False
        Name = 'Score500'
      end
      item
        CollectionIndex = 155
        CollectionName = 'Score\Score600'
        Disabled = False
        Name = 'Score600'
      end
      item
        CollectionIndex = 156
        CollectionName = 'Score\Score700'
        Disabled = False
        Name = 'Score700'
      end
      item
        CollectionIndex = 157
        CollectionName = 'Score\Score800'
        Disabled = False
        Name = 'Score800'
      end
      item
        CollectionIndex = 158
        CollectionName = 'Score\Score900'
        Disabled = False
        Name = 'Score900'
      end
      item
        CollectionIndex = 159
        CollectionName = 'Score\Score1000'
        Disabled = False
        Name = 'Score1000'
      end
      item
        CollectionIndex = 84
        CollectionName = 'El'#233'ments\FlecheHautBas'
        Disabled = False
        Name = 'FlecheHautBas'
      end
      item
        CollectionIndex = 83
        CollectionName = 'El'#233'ments\FlecheGaucheDroite'
        Disabled = False
        Name = 'FlecheGaucheDroite'
      end
      item
        CollectionIndex = 189
        CollectionName = 'Caract'#232'res\Espace'
        Disabled = False
        Name = 'Espace'
      end
      item
        CollectionIndex = 88
        CollectionName = 'Jokers\JokerPique'
        Disabled = False
        Name = 'JokerPique'
      end
      item
        CollectionIndex = 87
        CollectionName = 'Jokers\JokerCoeur'
        Disabled = False
        Name = 'JokerCoeur'
      end
      item
        CollectionIndex = 89
        CollectionName = 'Jokers\JokerTrefle'
        Disabled = False
        Name = 'JokerTrefle'
      end
      item
        CollectionIndex = 86
        CollectionName = 'Jokers\JokerCarreau'
        Disabled = False
        Name = 'JokerCarreau'
      end
      item
        CollectionIndex = 190
        CollectionName = 'Portes\EspacePorteH'
        Disabled = False
        Name = 'EspacePorteH'
      end
      item
        CollectionIndex = 141
        CollectionName = 'Portes\PorteH2'
        Disabled = False
        Name = 'PorteH2'
      end
      item
        CollectionIndex = 142
        CollectionName = 'Portes\PorteH3'
        Disabled = False
        Name = 'PorteH3'
      end
      item
        CollectionIndex = 143
        CollectionName = 'Portes\PorteH4'
        Disabled = False
        Name = 'PorteH4'
      end
      item
        CollectionIndex = 144
        CollectionName = 'Portes\PorteH5'
        Disabled = False
        Name = 'PorteH5'
      end
      item
        CollectionIndex = 191
        CollectionName = 'Portes\EspacePorteV'
        Disabled = False
        Name = 'EspacePorteV'
      end
      item
        CollectionIndex = 145
        CollectionName = 'Portes\PorteV2'
        Disabled = False
        Name = 'PorteV2'
      end
      item
        CollectionIndex = 146
        CollectionName = 'Portes\PorteV3'
        Disabled = False
        Name = 'PorteV3'
      end
      item
        CollectionIndex = 147
        CollectionName = 'Portes\PorteV4'
        Disabled = False
        Name = 'PorteV4'
      end
      item
        CollectionIndex = 148
        CollectionName = 'Portes\PorteV5'
        Disabled = False
        Name = 'PorteV5'
      end
      item
        CollectionIndex = 179
        CollectionName = 'Fantomes\YeuxEntiersNord'
        Disabled = False
        Name = 'YeuxEntiersNord'
      end
      item
        CollectionIndex = 178
        CollectionName = 'Fantomes\YeuxEntiersEst'
        Disabled = False
        Name = 'YeuxEntiersEst'
      end
      item
        CollectionIndex = 181
        CollectionName = 'Fantomes\YeuxEntiersSud'
        Disabled = False
        Name = 'YeuxEntiersSud'
      end
      item
        CollectionIndex = 180
        CollectionName = 'Fantomes\YeuxEntiersOuest'
        Disabled = False
        Name = 'YeuxEntiersOuest'
      end
      item
        CollectionIndex = 171
        CollectionName = 'Fantomes\YeuxArri'#232'reNord'
        Disabled = False
        Name = 'YeuxArri'#232'reNord'
      end
      item
        CollectionIndex = 170
        CollectionName = 'Fantomes\YeuxArri'#232'reEst'
        Disabled = False
        Name = 'YeuxArri'#232'reEst'
      end
      item
        CollectionIndex = 173
        CollectionName = 'Fantomes\YeuxArri'#232'reSud'
        Disabled = False
        Name = 'YeuxArri'#232'reSud'
      end
      item
        CollectionIndex = 172
        CollectionName = 'Fantomes\YeuxArri'#232'reOuest'
        Disabled = False
        Name = 'YeuxArri'#232'reOuest'
      end
      item
        CollectionIndex = 175
        CollectionName = 'Fantomes\YeuxAvantNord'
        Disabled = False
        Name = 'YeuxAvantNord'
      end
      item
        CollectionIndex = 174
        CollectionName = 'Fantomes\YeuxAvantEst'
        Disabled = False
        Name = 'YeuxAvantEst'
      end
      item
        CollectionIndex = 177
        CollectionName = 'Fantomes\YeuxAvantSud'
        Disabled = False
        Name = 'YeuxAvantSud'
      end
      item
        CollectionIndex = 176
        CollectionName = 'Fantomes\YeuxAvantOuest'
        Disabled = False
        Name = 'YeuxAvantOuest'
      end
      item
        CollectionIndex = 135
        CollectionName = 'Pacman\PacManVieMort1'
        Disabled = False
        Name = 'PacManVieMort1'
      end
      item
        CollectionIndex = 136
        CollectionName = 'Pacman\PacManVieMort2'
        Disabled = False
        Name = 'PacManVieMort2'
      end
      item
        CollectionIndex = 137
        CollectionName = 'Pacman\PacManVieMort3'
        Disabled = False
        Name = 'PacManVieMort3'
      end
      item
        CollectionIndex = 138
        CollectionName = 'Pacman\PacManVieMort4'
        Disabled = False
        Name = 'PacManVieMort4'
      end
      item
        CollectionIndex = 192
        CollectionName = 'El'#233'ments\FondNoir'
        Disabled = False
        Name = 'FondNoir'
      end>
    ImageCollection = ImageCollection
    PreserveItems = True
    Left = 144
  end
  object ImageCollection: TImageCollection
    Images = <
      item
        Name = 'Caract'#232'res\Apostrophe'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D35095068
              88F2000000224944415418D363600002161E1E1E0624C043221F5D3F033A9F01
              9DCF80CE1F2C0000FE380129590D8AF70000000049454E44AE426082}
          end>
      end
      item
        Name = 'Chiffres\Chiffre0'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B9B1FF0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFBA3D8E58
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D3413B411
              40C9000000374944415418D363600002262E30606280022E3840E74344B8B850
              459850059818D0F5E21480607C0278CCC0B016C361984EC7F41CAAF701B0BD06
              F1F5BD93460000000049454E44AE426082}
          end>
      end
      item
        Name = 'Chiffres\Chiffre1'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D333920EB
              1FD8000000364944415418D363600002262E106080032E2E54012E34012E3401
              26740184325A0A20AC0503262487C11D83CE47166140358709C4060040D804A9
              6E9B06BA0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Chiffres\Chiffre2'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B1716A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1615E3D7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D310AAD0D
              1C4C000000384944415418D363600002262E30606280022E3840E74344B8B850
              45985005E0E6C0D5620A70A1011C02784DC2B416DD61984EC7F41CAAF70170FD
              0679C1E94C830000000049454E44AE426082}
          end>
      end
      item
        Name = 'Chiffres\Chiffre3'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D33204480
              B718000000374944415418D363600002262E30606280022E3840E74344B8B850
              45985005E0E6C0D5E210E0C263111166605A8BEE304CA7637A0ED5FB00356B06
              156F8EA5B60000000049454E44AE426082}
          end>
      end
      item
        Name = 'Chiffres\Chiffre4'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544501097E0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF7F8C416D
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D31306B01
              C5FE000000334944415418D363600002262E30606280022E3840E74344B8D004
              98D005E02C4202084D18020C28AE6160A0BE0003AA00D8FB007615058B201DC7
              F70000000049454E44AE426082}
          end>
      end
      item
        Name = 'Chiffres\Chiffre5'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54456928B30000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF5366C23A
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D303BE5C8
              2D370000003B4944415418D363600002262E30606280022E3840E74344B8B850
              45985005981890F422998021806C08860041DD98D632601A816924A615C8DE07
              0070FD06795D9BD2FB0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Chiffres\Chiffre6'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445498E6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF87337A52
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D2F089742
              42BF0000003B4944415418D36D8F410A00201002C5A3FF7F7051119A79DB015D
              05A6A825E24857EFBD8994840908F35A42010FF9037717A8B755ACABF7B89C3F
              009AFB06DD367E3D7B0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Chiffres\Chiffre7'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D30206FAD
              E4DB000000374944415418D363600002262E30606280022E3840E74344B8B850
              45985005E0E6C0D55226C08426C0C4852A80EE7C262E540544F2C1FA01C53E04
              CBA83498390000000049454E44AE426082}
          end>
      end
      item
        Name = 'Chiffres\Chiffre8'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D2F29DB2B
              52E1000000384944415418D363600002262E30606280022E3840E74344B8B850
              459850059818D0F5E210403604BB005E3330ACC57018A6D3313D87EA7D00DB3D
              0741AC059AEB0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Chiffres\Chiffre9'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54457361760000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFE6EEBF35
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D2E34A136
              0F79000000394944415418D3758F410A00300CC2C4A3FF7FF0C63686AD34B706
              540A6CA803F1D0A7DFD748D5B00AA26707E125218C41C42CB2222B73C2DF5FB1
              3F06DDC9DD1B2F0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Caract'#232'res\DeuxPoints'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D2E11EA32
              DB3E0000001A4944415418D36360201BF0F3A3F3D144300430B40C1A5BE00000
              C0500169D62C892F0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Etoiles\Etoile'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445498E6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF87337A52
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300000EC400000EC401952B0E1B0000000774494D4507E306100D2B38D5F7
              B717000000394944415418D36360C00158D0F93C2C0404787878700BB0F02001
              16A82C1CA0A96141D5C6826A26AA3DE8022C200EB21E8824B253B07B1002009F
              0F033D81F69BAA0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Etoiles\EtoileAllum'#233'e'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544520B7F00000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF38DC0474
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300000EC400000EC401952B0E1B0000000774494D4507E306100D2B2A264E
              C65F000000394944415418D36360C00158D0F93C2C0404787878700BB0F02001
              16A82C1CA0A96141D5C6826A26AA3DE8022C200EB21E8824B253B07B1002009F
              0F033D81F69BAA0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Etoiles\EtoileEteinte'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445403C570000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFADC0EBB5
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300000EC400000EC401952B0E1B0000000774494D4507E306100D2A362B54
              AB51000000394944415418D36360C00138D0F99C1C0404383939710B70702201
              0EA82C1CA0A9E140D5C6816A26AA3DE8021C200EB21E8824B253B07B10020060
              A102B9BFED2F9C0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Etoiles\EtoileMiEteinteMiAllum'#233'e'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54451005C10000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFF05B3C41
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300000EC400000EC401952B0E1B0000000774494D4507E306100D2938E7C1
              D595000000464944415418D3758F310E00200803191CBC84FFBF5741A340B45B
              8F1682C847BDF8A685340A50A500087517AEBEE2C7133267BE51B2DE02F2D504
              E61291D8316FE426DE0F2E0D7E8102F47116529E0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuArri'#232'reEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445607ED40000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFB9C8958E
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D3B27123D
              A8B30000002F4944415418D363604000565E2040E2F3F2A20A00E50504900540
              7C5656FC02185AD00C254B008C4812600523C2020090BA04A6E126517A000000
              0049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuArri'#232'reOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D3B14ADED
              C9A5000000304944415418D363E00502560624C00B0628020202286A78595941
              22F804C05A78D10DA5500028C440AA002B18112F0000BACB04A65A1709BD0000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuArri'#232'reSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544520FC4E0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF755E2C02
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D3A2F05FD
              11C0000000364944415418D36360183C8095170A58217C5E2400951710007140
              242B58818000880D212102ACAC02301262042BD8583089662636010052880533
              911D43AD0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuArrNAvtS'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D3A125D95
              5DD10000001B4944415418D36360E045010C0CD80450105102AC28881881C101
              005A1D0401300FC6C50000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuAvantEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445C16B6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF7848BBC6
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D392E59D7
              7295000000334944415418D363E00502560624C00B0628020202286A807C5656
              64259802602DBCE8865228001462204D809581178C88170000B83B048EA0D81A
              EA0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuAvantNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54456B00000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF9C6D7E35
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D3820A774
              6ED3000000334944415418D36360183C8095170A58217C5E2400956705AB0191
              AC600502ACAC02301222000430126204880525D1CCC426000046D80533046D97
              DD0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuAvantOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54455854550000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF84F24634
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D380892C1
              C629000000324944415418D363604000565E2040E2F3F2A20A00E50504900578
              7959598122780530B4A0194A9600189122C0CA0B468405008E82048E37246865
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuEntierEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D372C295A
              3E37000000394944415418D36360606060E58502560630E045020C1079010110
              0744B282150808B0B2C248EC02485A78D1CC245F00051125C08A82080B000048
              B40933002B43F20000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuEntierNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54459852920000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFD9185A06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D3712E83B
              239C0000003D4944415418D36360606060E58502560630E045020C107956B01A
              10C90A5620C0CA2A00232102400023214680585012CD4CF20550105102AC2888
              B00000428409330A73D5570000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuEntierOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54451005C10000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFF05B3C41
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D36382A9B
              DB0B000000394944415418D36360606060E58502560630E045020C1079010110
              0744B28215B0B282D96012BB0092165E3433C9174041C408B0F2A220C2020047
              8C0933550475780000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuEntierSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544560F6C10000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFAE669EC8
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D361EF896
              5EF60000003F4944415418D39D8CC10A0020084377D951D8FF7F6D380BB24BD1
              180F9D3200604C11566C42DDA55C92F4839473B102528B5541D79A47E77FD0FC
              14B0F91E0C4E340933B49530380000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielArri'#232'reEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450015AC0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF50ADBEE9
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0120ABB6
              5D300000002F4944415418D363604000767E2040E2F3F3A30A00E50504900540
              7C7676FC02185AD00C254B008C4812600723C20200ED0205584EA485DE000000
              0049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielArri'#232'reOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E01108D6F
              6D9C000000304944415418D363E00702760624C00F0628020202286AF8D9D941
              22F804C05AF8D10DA5500028C440AA003B18112F00001D6C05582F0CD11A0000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielArri'#232'reSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E042238CF
              C859000000364944415418D36360183C809D1F0AD8217C7E2400951710007140
              243B58818000880D212102ECEC02301262043BD858308966263601007EC205E7
              00C89EB60000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielArrNAvtS'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445014FB30000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF0682A966
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E040B7A7D
              50350000001B4944415418D36360E047010C0CD80450105102EC28881881C101
              00E98D04B1178952BD0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielAvantEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445D17E6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFBAF67C96
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E002CBB1B
              205A000000334944415418D363E00702760624C00F0628020202286A807C7676
              64259802602DFCE8865228001462204D809D811F8C881700001ACC0540D36425
              C80000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielAvantNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E03331D3E
              7E6C000000334944415418D36360183C809D1F0AD8217C7E2400956707AB0191
              EC600502ECEC02301222000430126204880525D1CCC4260000753205E790AFAF
              860000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielAvantOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E001F04CB
              414C000000324944415418D363604000767E2040E2F3F3A30A00E505049005F8
              F9D9D98122780530B4A0194A9600189122C0CE0F46840500EADA0540EC0B34AC
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielEntierEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544580184B0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1D15EDD0
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E030DDC5F
              63C7000000394944415418D36360606060E78702760630E047020C1079010110
              0744B283150808B0B3C348EC02485AF8D1CC245F00051125C08E82080B000007
              8D0A97D29F6B860000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielEntierNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54455C67690000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFBC19C718
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E022E6723
              23F40000003D4944415418D36360606060E78702760630E047020C107976B01A
              10C90E5620C0CE2E00232102400023214680585012CD4CF20550105102EC2888
              B00000027D0A97AAC10DF00000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielEntierOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E021B3190
              E7D7000000394944415418D36360606060E78702760630E047020C1079010110
              0744B28315B0B383D96012BB0092167E3433C9174041C408B0F3A320C2020006
              850A97287899600000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielEntierSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445707ACB0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFF25989EA
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E013B21D3
              94DC0000003F4944415418D39D8CC10A00300842BD79CCFFFFDA916DB076D998
              C8A32C0400C61461C526D45DCA25493F4839172B20B5581574AD7974FE07CD4F
              019BEFC1000C0D0A9708BAF35B0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisArri'#232'reEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445498E6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF87337A52
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E062F7448
              D6660000002F4944415418D3636040000E4E2040E27372A20A00E50504900540
              7C0E0EFC02185AD00C254B008C4812E00023C20200FEA20396240ECE7F000000
              0049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisArri'#232'reOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544521706A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF2870F405
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E062193F0
              FB61000000304944415418D363E004020E0624C0090628020202286A38393840
              22F804C05A38D10DA5500028C440AA000718112F00001F1403965E3A71AC0000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisArri'#232'reSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54451000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF97D1EAFD
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0A22A64C
              E5D7000000364944415418D36360183C8083130A38207C4E2400951710007140
              240758818000880D2121021C1C023012620407D858308966263601001152041F
              1B8F4A9A0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisArrNAvtS'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544551726A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF92AFC447
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0A090AF0
              1C970000001B4944415418D36360E044010C0CD804501051021C28881881C101
              007D37030A8365E01F0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisAvantEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54454004F90000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFE5182C7F
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E05334B64
              D9EA000000334944415418D363E004020E0624C0090628020202286A807C0E0E
              64259802602D9CE8865228001462204D808381138C881700001EF70393F23C59
              500000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisAvantNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445F134670000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF7E5DAD3B
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E092A83BA
              3E26000000334944415418D36360183C8083130A38207C4E240095E700AB0191
              1C6005021C1C02301222000430126204880525D1CCC426000008D2041F9D298F
              340000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisAvantOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445A1816A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF63326916
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0528C101
              1006000000324944415418D3636040000E4E2040E27372A20A00E50504900538
              3939388022780530B4A0194A9600189122C0C10946840500FE260393FABB8BDD
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisEntierEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544521706A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF2870F405
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E091442DB
              238D000000394944415418D363606060E0E084020E0630E044020C1079010110
              074472801508087070C048EC02485A38D1CC245F00051125C08182080B00001C
              B007288E0776AC0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisEntierNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0902B60F
              96DC0000003D4944415418D363606060E0E084020E0630E044020C10790EB01A
              10C9015620C0C12100232102400023214680585012CD4CF205501051021C2888
              B00000183007288EE880050000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisEntierOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54457761730000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFA75CE467
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E082BEDA6
              3FF1000000394944415418D363606060E0E084020E0630E044020C1079010110
              0744728015707080D96012BB0092164E3433C9174041C4087070A220C202001C
              2107280FD66D940000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisEntierSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E08192571
              6E710000003F4944415418D39D8CC10A003008423DDACDFFFFDA916DB076D998
              C8A32C0400C61461C526D45DCA25493F4839172B20B5581574AD7974FE07CD4F
              019BEFC10020B00728B4CF11AF0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaArri'#232'reEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445203C570000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFD1F8EFAF
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0D1FB165
              3F010000002F4944415418D363604000363E2040E2F3F1A10A00E50504900540
              7C3636FC02185AD00C254B008C4812600323C20200BEDE04FFE45E32A3000000
              0049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaArri'#232'reOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445406ACC0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFF803F841
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0D1426B7
              E689000000304944415418D363E00302360624C0070628020202286AF8D8D840
              22F804C05AF8D00DA5500028C440AA001B18112F0000EC1404FF6F8127720000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaArri'#232'reSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E100CCAB7
              12C3000000364944415418D36360183C808D0F0AD8207C3E2400951710007140
              241B58818000880D2121026C6C02301262041BD8583089662636010068A5058D
              413163DB0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaArrNAvtS'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544551726A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF92AFC447
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0F342FEF
              A4C30000001B4944415418D36360E043010C0CD804501051026C28881881C101
              00A1D50459B931CBCD0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaAvantEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B1716A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1615E3D7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0C32EDA1
              5235000000334944415418D363E00302360624C0070628020202286A807C3636
              64259802602D7CE8865228001462204D808D810F8C88170000E97C04E75064CF
              850000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaAvantNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544551726A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF92AFC447
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0F1C1A5A
              0C39000000334944415418D36360183C808D0F0AD8207C3E2400956703AB0191
              6C6005026C6C02301222000430126204880525D1CCC42600005E05058DCCF1A5
              B40000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaAvantOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54451000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF97D1EAFD
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0C27807C
              B6DE000000324944415418D363604000363E2040E2F3F1A10A00E505049005F8
              F8D8D88022780530B4A0194A9600189122C0C60746840500BCAE04E7D03B9992
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaEntierEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0E2ACCFB
              A8E1000000394944415418D36360606060E38302360630E043020C1079010110
              0744B281150808B0B1C148EC02485AF8D0CC245F00051125C08682080B0000A8
              1909E5F205230F0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaEntierNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0F0AEE8E
              B9680000003D4944415418D36360606060E38302360630E043020C107936B01A
              10C9065620C0C62600232102400023214680585012CD4CF205501051026C2888
              B00000A27909E583CE06140000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaEntierOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445C16B6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF7848BBC6
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0E140D9A
              B54A000000394944415418D36360606060E38302360630E043020C1079010110
              0744B28115B0B181D96012BB0092163E3433C9174041C408B0F1A120C20200A7
              0109E522E3A8340000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaEntierSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54451600000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF46C4C954
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0D396368
              BAFC0000003F4944415418D39D8CC10A0020084377DA51F6FF5F1BCE82EC5234
              C643A70C00185384159B5077299724FD20E55CAC80D46255D0B5E6D1F91F343F
              056CBE0703AD1909E5361A67560000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeArri'#232'reEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E13136C92
              4CF50000002F4944415418D363604000262E2040E27371A10A00E50504900540
              7C2626FC02185AD00C254B008C4812600223C20200064E039B76EF2A0B000000
              0049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeArri'#232'reOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445C16B6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF7848BBC6
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1308E6F7
              8519000000304944415418D363E00202260624C0050628020202286AB8989840
              22F804C05AB8D00DA5500028C440AA001318112F000026F0039BC0434CB80000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeArri'#232'reSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445703D4A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFF11ED8B6
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1510A3C1
              BAC9000000364944415418D36360183C80890B0A98207C2E2400951710007140
              241358818000880D2121024C4C023012620413D8583089662636010010310425
              977788BC0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeArrNAvtS'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54452F41700000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF14FA7263
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E14326FBA
              CA6C0000001B4944415418D36360E042010C0CD804501051024C28881881C101
              0082E602F9A20E2B820000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeAvantEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445407D320000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFAB8A6720
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E122CC3EF
              5089000000334944415418D363E00202260624C0050628020202286A807C2626
              64259802602D5CE8865228001462204D8089810B8C88170000247803831BA5CB
              A30000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeAvantNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E141E5D62
              A68F000000334944415418D36360183C80890B0A98207C2E2400956702AB0191
              4C6005024C4C02301222000430126204880525D1CCC426000001510425314F33
              C00000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeAvantOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B1716A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1615E3D7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E121D9231
              50B3000000324944415418D363604000262E2040E27371A10A00E505049005B8
              B898988022780530B4A0194A9600189122C0C4054684050003FE038325B197F9
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeEntierEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1134FBAE
              9B1C000000394944415418D36360606060E28202260630E042020C1079010110
              074432811508083031C148EC02485AB8D0CC245F00051125C08482080B00002A
              76071DBB4C431B0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeEntierNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445906EF30000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFA1EC52AA
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1409DEB1
              23480000003D4944415418D36360606060E28202260630E042020C107926B01A
              10C9045620C0C42400232102400023214680585012CD4CF205501051024C2888
              B000002296071D31E60D490000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeEntierOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E112998A8
              F7C5000000394944415418D36360606060E28202260630E042020C1079010110
              0744328115303181D96012BB0092162E3433C9174041C4083071A120C2020029
              1E071DAD8BB78F0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeEntierSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445313B010000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF26A61530
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1330CEF5
              3D870000003F4944415418D39D8CC10A00200843C78E9EF6FF5F1BCE82EC5234
              C643A70C00185384159B5077299724FD20E55CAC80D46255D0B5E6D1F91F343F
              056CBE07033176071DD6D632CB0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertArri'#232'reEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445C16B6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF7848BBC6
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1628A0EE
              51940000002F4944415418D363604000666E2040E27373A30A00E50504900540
              7C6666FC02185AD00C254B008C4812600623C20200347203F47AC9A673000000
              0049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertArri'#232'reOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E16332A8B
              9878000000304944415418D363E00602660624C00D0628020202286AB8999941
              22F804C05AB8D10DA5500028C440AA003318112F0000583903F47DCCF3590000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertArri'#232'reSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445A1816A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF63326916
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E182ED70E
              D92F000000364944415418D36360183C80991B0A98217C6E2400951710007140
              243358818000880D212102CCCC023012620433D85830896626360100264E047F
              4250188B0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertArrNAvtS'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54458043110000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFD5F2F296
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E190AF216
              0CBF0000001B4944415418D36360E046010C0CD80450105102CC28881881C101
              00CA9E03515B3C84C30000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertAvantEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000090000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFAC9AA90B
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1715E19D
              2CC4000000334944415418D363E00602660624C00D0628020202286A807C6666
              64259802602DDCE8865228001462204D8099811B8C8817000055B903DC20BB16
              560000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertAvantNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445209E920000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF3AB93EDA
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E191EE8CC
              D8C2000000334944415418D36360183C80991B0A98217C6E2400956706AB0191
              CC600502CCCC02301222000430126204880525D1CCC4260000187E047F03DFCB
              BC0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertAvantOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445A82C340000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF18CD630F
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1721C029
              D871000000324944415418D363604000666E2040E27373A30A00E505049005B8
              B999998122780530B4A0194A9600189122C0CC0D46840500322A03DCCC75E372
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertEntierEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544511856A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8FD909C4
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E180392D1
              855A000000394944415418D36360606060E68602660630E046020C1079010110
              074432831508083033C348EC02485AB8D1CC245F00051125C08C82080B000089
              DB07CF07419A1E0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertEntierNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445F0B9C20000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF36C2B5B0
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1A0BAE3C
              6FEA0000003D4944415418D36360606060E68602660630E046020C107966B01A
              10C90C5620C0CC2C00232102400023214680585012CD4CF20550105102CC2888
              B00000828B07CFF6E56E790000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertEntierOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54457049470000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF38C25EA0
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E180EEC60
              F9E7000000394944415418D36360606060E68602660630E046020C1079010110
              0744328315303383D96012BB0092166E3433C9174041C4083073A320C2020088
              9307CF553A4D7F0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertEntierSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B1716A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1615E3D7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1A1EC3E1
              8B010000003F4944415418D39D8CC10A00200843073B7AD9FF7F6D380BB24BD1
              180F9D3200604C11566C42DDA55C92F4839473B102528B5541D79A47E77FD0FC
              14B0F91E0C905B07CF479BF67B0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Caract'#232'res\Fl'#232'cheDroite'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450002020000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF94F786C2
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1B3808F7
              3FBD0000003F4944415418D36D8F310E00300802DD6EF4FFBF6D9B0E502C93B9
              A060D5111522094D02231CB5C876F71566772287C8BB640EE20696EAB1B3D8BF
              FA784EE302A67E04ED13EA51BF0000000049454E44AE426082}
          end>
      end
      item
        Name = 'El'#233'ments\FlecheGaucheDroite'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544580B3810000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF334653BF
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1C13EB0A
              503A000000254944415418D36360A00EE04763F02304F8212492003F98400198
              02185A300DC5B496620000BF5F03497EFF45600000000049454E44AE426082}
          end>
      end
      item
        Name = 'El'#233'ments\FlecheHautBas'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B1716A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1615E3D7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1C2D2A6B
              4D910000002A4944415418D3636080007E7E0614C0CF8F2AC2CF8F2AC2CF8F2E
              8269C68008603A0C9B4331BD0B650000BF5F0349545B01FE0000000049454E44
              AE426082}
          end>
      end
      item
        Name = 'El'#233'ments\Fond'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54451400000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF09C82833
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1E02B38C
              124A000000224944415418D363E00001060E0E18CD80019065211441014C33D0
              6D212C3030EE0000BBEE0541EEE5DC060000000049454E44AE426082}
          end>
      end
      item
        Name = 'Jokers\JokerCarreau'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445E03A560000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF0894902C
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1E2C6F5A
              1F85000000344944415418D36360C001F8F8D0F9A8226C200136343E9208940F
              17E14302E87CB008860086164C4331ADC57418A6D3313D8700000F3D05C1E325
              FEE60000000049454E44AE426082}
          end>
      end
      item
        Name = 'Jokers\JokerCoeur'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B1716A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1615E3D7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1F03DD90
              139D000000384944415418D36360C002B8B8B890283003C4845250061C504980
              019D8F2C0273191384CB84EA582E14D733A1CA8395A07990898901070000104D
              04D16C67557B0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Jokers\JokerPique'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450500000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFD602DA5B
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1F17C74A
              C7E0000000364944415418D36360C001F8F90908F0F3A38AB08304D851E591D4
              F02301743E5884B000861960110630E2C7E35276147761713A1200001C300617
              A8E71CCB0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Jokers\JokerTrefle'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544521706A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF2870F405
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E1F2FEF48
              7F7E0000003D4944415418D36360C00A98B98180198D8F2CC20D05B80530B440
              D420CB83303303540D333712604632116E2E610188B3C108612AC806088DD51D
              A8000093440539BF67911F0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreA'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E22340FC5
              FE2C000000404944415418D363600002161E30606180021E3840E74344787850
              455850055818D0F5E210403604BB005E335860F6C39D8F2A805089AE17464200
              0B4400EC7D00936008493D1697740000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreB'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E291A30E7
              2A280000003B4944415418D363600002161E30606180021E3840E74344787850
              455850055818A0E2100C626208A0DB842940D80C0C6B311C86E9744CCFA17A1F
              007E180879CEA1D2470000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreC'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54455A54550000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFCBFEA753
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2202C07F
              6BB5000000384944415418D363600002161E30606180021E3840E74344787850
              455850055818D0F5E2154016C62E80C30C0C6B311C86E9744CCFA17A1F001DA0
              07B972BBCA5A0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreD'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B1716A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1615E3D7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E23094EB6
              837C0000003B4944415418D363600002161E30606180021E3840E74344787850
              455850055818A0E2100C626208C06DC22940D80C0C6B311C86E9744CCFA17A1F
              0064F80849FB4232F60000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreE'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445C16B6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF7848BBC6
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E24010F2C
              9D89000000394944415418D363600002161E30606180021E3840E74344787850
              455850055818D0F5E210400832E010C06B0686B5180EC3743AA6E750BD0F0051
              0008192A5422F00000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreF'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B1716A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1615E3D7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E293A0B89
              0AE00000003B4944415418D385CC390E0030080341172EFDFFF7E620220184B2
              158C04C08CDA112779793791A23002916F1BB88806F05480CAA4FF110AAC3F3E
              0FDCA9060D4CB219450000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreG'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445D001D10000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFEDC3850F
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2A2DA377
              DCE40000003C4944415418D363600002161E30606180021E3840E74344787850
              45585005581890F4229980450061082E0184620C010C6B311C86E9744CCFA17A
              1F0040500819E5ACC6C30000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreH'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54453732000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF0674DA75
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E251695E4
              290F0000003F4944415418D37D4F390E00200C6260E4FFEF55636B35A80C3D48
              0F003A2801121190263162F65A290A55E649B02673E94E6C7810DF1BF6D684B9
              743777DA6F27CC07D1572B22BF0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreI'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54455854550000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF84F24634
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2522B450
              DDBA0000003D4944415418D363600002161E30606180021E3840E74344787850
              455850055818A0E2100C626208C06D624005C85284CCC0B016C361984EC7F41C
              AAF70127CC07D1E3D789B60000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreJ'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54453001000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF3808F0FA
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E260FDAA2
              D20C000000394944415418D3636080021E1E1E160664C0030218023C18023C18
              022C848DC1144012265680850705B0C01D80E430743EB208CC012C48CE0600B4
              BA0625258CCDF30000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreK'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2B0A1F66
              58CE000000404944415418D37D8FC10E0020084239787CFFFFBDD5B25AB2E220
              CA9C82D41120412801531875CD6CCA86C3710B51377908507E98F0BD616FCD98
              5BF77077FC061CE007B92811D1420000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreL'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E26229F7D
              8E79000000394944415418D363600002161E1E1E0624C0C3832AC08326C08326
              C0822E806E0069021026610198B550C00277189273D0F9C82268CE6701B101C4
              AE0625659BFEE80000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreM'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2413FC95
              ECC1000000414944415418D39D8F490E002008037BE8B1FF7FAF4B1103DE9C04
              031308084CA80D1128E9B58D540DAB20C23B56FA2F72DF2BA81C8AF3ABB89D7D
              F6BC8616FBFB038040081949D8F7A10000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreN'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445206C610000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFA0E518A8
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2808DA45
              6A21000000444944415418D3658F3912002008035350EEFFDFAB8E68442808EC
              704AD3022408A5C106CB9F9C2B19608D0A22D5B50750819EB19E50815BBFF5F4
              B5EDB07E7A7FAEBE3F00414C0801F094FB990000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreO'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2B1D9CB5
              DD09000000324944415418D363600002161E30606180021E3840E74344787850
              455850055818D0F5D24600C35A0C87613A1DD373A8DE07005ACC08314EC70DE8
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreP'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544567656F0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFA6548F77
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2B31AE6D
              B1EA0000003E4944415418D3658FC10A003008423D78F4FFBFB76DC5A814827A
              112970443D11257DED3989340927208A67DDD6C0FEE4A09DB45507F6D68CB975
              0F37E30750DC08012565FACC0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreQ'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B1716A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1615E3D7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2C0CB944
              6B3C000000414944415418D3758E310A003008033364CCFFDFDB528B4D841E38
              782809B0A10EC445CDDCCB4869988298BF5F511342E3A5633C1E56DB9ACA8FC3
              5494193C6862016DB407F9E6E039220000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreR'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54456199B30000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFE8741A58
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2C2715F8
              927C000000444944415418D3658E4B0E00400443BBE8D2FDCF3B0CF16D227851
              002ACA171192D4EE9D884CC20988E01E561EB02F5D9096F145F773CEB2DC65EB
              A05FF05F507B3459FD00585007D1DBC72CB70000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreS'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E282A0F25
              2BC50000003E4944415418D3654F31120020086260E4FFEFADABCE4498944340
              60833A201E5498FB652467E80431B568D7CD177F4230A62F8F169FB1512CABE7
              73FEFE02414C0801E1268E070000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreT'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2D14B333
              C22B0000003B4944415418D363600002161E30606180021E3840E74344787850
              455850055818A0E2100C626208C06D624005A40860588BE1304CA7637A0ED5FB
              00C81D06E101F2E1E20000000049454E44AE426082}
          end>
      end
      item
        Name = 'Caract'#232'res\LettreTilde'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450907000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF852CDA1D
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2023BE20
              19690000001B4944415418D36360A013E0E141218024904610580430B4D00300
              00E69001B1F38BBE5E0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreU'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54451005C10000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFF05B3C41
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E221033C6
              1AFD000000414944415418D3B58F3116C03008421918FFFDCF9BA49198762F83
              284F9E284D1824B00AB085553373A81A9AFD16DC9B31FD22D4D9C0B91F7454BE
              DE6B3EF19FF707EF2907B9D3767D510000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreV'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2D3B18E2
              FF72000000434944415418D39D8F3702003008021918EFFFEF4D5353C63058B0
              A0528741022B008B183673CA45C0F6BE09EFCE1CFA254E396E155236E1AAF0CE
              F26E3FF23A7FBEDF000B1C0801208255F60000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreW'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E241FF523
              A0EA000000464944415418D39D8F3B0EC03008433D787CF73F6FDB1487365296
              78E0630136D20D830456015EE289E999A90A3AFB4FB827B3B423FAEC0151B281
              A31FB45556FD4F3FED8FF72F1BD80819A88CAC2C0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreX'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B1716A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1615E3D7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2E167610
              F0C4000000434944415418D3658F3912002008035350EEFFDFAB8E8868524020
              9CD2448004A104ECC4B227A65C12AE8F578914AA029539BC2F6AF8356F6F436D
              AD1DE6A7FB73EFFB03DB3D074170524C820000000049454E44AE426082}
          end>
      end
      item
        Name = 'Lettres\LettreY'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445498E6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF87337A52
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E2E2E5E12
              485A000000474944415418D3858F3912C030080355A8DCFFBF37718C39DC4405
              1282E1905E1824B002B08D154F4E52088A3D2B8E42767038A1E6B6455DFE1B9E
              33AD6B4D9D5A797734E77CEF3FE99507713E2E4CF40000000049454E44AE4260
              82}
          end>
      end
      item
        Name = 'Lettres\LettreZ'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445C16B6A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF7848BBC6
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E281A29FC
              1B690000003D4944415418D3658F3B0E003008421918B9FF79DB58638ABC0DFC
              2170A10AA2D1B0F5732477E806B13BC7F0BDA5F1E3259BC20E9067235846CFE7
              FCFD03414C08013A6184370000000049454E44AE426082}
          end>
      end
      item
        Name = 'El'#233'ments\Mur'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450090820000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFDD0463FB
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2F15F0C9
              52D40000002B4944415418D3636000014E0E0638CD89061838383920004AA32A
              C7D00FA631CC40D20FA2B16B1B04EE0000D9D60559552041C40000000049454E
              44AE426082}
          end>
      end
      item
        Name = 'El'#233'ments\PacGum'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445006C860000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF6ADDE947
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2E272105
              3215000000294944415418D363602013307171713121F1B92000459E0B590D17
              179A12C202186660D882E90E0A010063B102731E3A8FCA0000000049454E44AE
              426082}
          end>
      end
      item
        Name = 'Pacman\PacManArri'#232'reEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2D3267F5
              853D000000334944415418D3636040022C3C3C3CC87C2097871F8DCFC38BC647
              52C10211E04153406B010C6B193004183004183004C0E60000907804F839A122
              E00000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManArri'#232'reNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2D25E426
              00FA0000002C4944415418D363E0E1E7E5E741020C3C680053800595CFC280A6
              848101558481015584010A58E0FA070F000022EF04F83082E6B9000000004945
              4E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManArri'#232'reOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544570FDFC0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF1AE3FF2B
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2E031D06
              D6C4000000334944415418D363E0E1E161614006FC40111E64015E1E3411B00A
              6411081FC91CA8000F5D0430AC457718039A0003AA008AF701BD7104F82391D1
              290000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManArri'#232'reSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544500B6700000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF89DDE81D
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2D14B5F8
              00C00000002C4944415418D3636018448085070C58607C1E3840E74344787850
              4558500558D0140095600AF0F3F2230B0000263904F869DAAABC000000004945
              4E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManAvantEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445495EBF0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFED195D6A
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2C25FD3D
              31BB0000003B4944415418D363E0E1E161614006BCFC402114015E1E5411B00A
              64111E08604117E0411540369405D5522C02185AB01B8AC55A742D040C45B118
              0039750403B0CB23A30000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManAvantNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2C1642ED
              50AD000000374944415418D36360184480850744F2B0C0F83C3C3C481498C183
              4E8358309A055580054AC305781878F879F941322C70015E5E5E640100D5C704
              03123D2CFE0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManAvantOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2C34978D
              1149000000394944415418D3636040022C3C3C3CC87C20979F1795CFC3CB8BCA
              4756C1C20301A80A300D4515006964C12B40C0500C6B1930AD25C61D20730012
              5504037E0BE9390000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManAvantSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54454A4D0F0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF7D4C4539
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2C032F30
              B446000000344944415418D3CD88B91100200CC352B8B42FFB6FCB8179920D50
              239D8292480234C154F6B17D037DE0C4B3AB7A55D1041E888F186F14040387EF
              94000000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManEntierBFEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544548CEC30000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF2FD64A6D
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2B04FE15
              B722000000454944415418D3958F310E002008033B742CF1FFBF5510A3329878
              03492FED0030A00222F1D0AC8DBBB3CC4C69667D36DCE47E41A8F0120CBE2629
              58056ABECDF1CC91EFF73B379009CAE02E49660000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManEntierBFNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2A2DA5BC
              1E0F0000004A4944415418D3658F490A0030080373F038D2FFFFB60B5DD4060F
              668860A4218331A0ADB92FC0F31B70FD01ACFB084C648068DE0812EE9EC19728
              FA81656F2A91F72AB50CB1AEDD7BA90328E909CAFFF3DA720000000049454E44
              AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManEntierBFOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2B1CED79
              2F74000000454944415418D3958F310A00300803336454FCFF6F5B45455A28F4
              A6E450506043098864675373D55D5455CA44C80937B95F1072700B06AF896F41
              1CA64F1D7D9A7A77BEBF00363909CA7217EFE40000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManEntierBFSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54455854550000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF84F24634
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2A198408
              EABA000000454944415418D3858F310E002008C4183A42F8FF6F350A4670B0DB
              351772884CD00512E8A1E76D54ABA10A5A61565EE1E65598D9A711D78FA00A72
              187D2AFD19AEBCE69379003FB009CA7D14DC240000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManEntierBOEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B292F609F
              2CE00000003D4944415418D36D8F310E00200C021918F9FF7B356A1B116F2B0D
              018009B5200E6AAE9B642932DA5F10CFDF1C1E11999F120A614B111BC55CF98F
              F3F9036A780851DBA845330000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManEntierBONord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445C13BBF0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFB8760857
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B29022540
              7095000000424944415418D36D8F310E002008036FE8D8FFBF578C9100DAA5E5
              020120242806F6F41EEC1ED4818E6D7243C02F900648E1A117F481583B5AF2A0
              525772DF55CEC302ECC90851842D06FD0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManEntierBOOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445F1643B0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8E04AAC9
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B281A2F37
              D9820000003D4944415418D3858E490A003008033DCC31FF7F6F8B548B0AEDDC
              0C6631DB20073B28B937908A0AE90F183F3D56D1C44768961A3A6B355A5F2B5A
              A7CF5E5B980851D7B22FDC0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManEntierBOSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B271C41CC
              6078000000424944415418D36D8F310E003008021D6EF4FFEFAD692D29A62CE0
              C5448C28915B442BA5391F92E904078C855AF900BE0006D035B9025E8876810E
              FAE106F7AAFFD802E9B80851B59F27790000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManVieMort1'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445E113970000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF7E8066B0
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2614560C
              D90B000000334944415418D363600002161E30606180011E2880F15960022C68
              7C8808121722C48306682380612D86C3B0381DD37328DE0700D1CC09116B8428
              600000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManVieMort2'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54454022720000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFE2A3FC65
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B25313625
              5E8F000000384944415418D3636000031E20604006E8022C200116542E5C08CE
              8389F1A001220430CC40319605D55E163C2EC510805A80C6471241361400B8F9
              06C98596412A0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManVieMort3'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445B981540000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFD7E00A00
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B250289F5
              3F99000000394944415418D3636080001E1E0654802EC0C2C3C382C64788F0A0
              006C0210F510C0826C048AB12C687C884178DD4184D33104D00D45B892010043
              B603F1DAA6AD260000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\PacManVieMort4'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445DE00570000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFD44F240C
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B2423DC87
              1E860000002C4944415418D3636080001E1E0654405080858787059903032CD8
              0530B490692DA52E85284055027127980900760F02B131B823B9000000004945
              4E44AE426082}
          end>
      end
      item
        Name = 'Caract'#232'res\ParamPorte'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54455854550000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF84F24634
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B233AF7AD
              20810000002E4944415418D3636060E0E0E06084020630202CC0830038045840
              80074CE210E04088E0124088E01420D9E9040400FF6B03591C97363900000000
              49454E44AE426082}
          end>
      end
      item
        Name = 'El'#233'ments\Pillule'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450500000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFD602DA5B
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B222563BE
              1C35000000194944415418D36360A01DE0E1E141E7A38A1016C03083D600008F
              CC00FDEAE2D44A0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Portes\PorteH2'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B21097A4B
              2315000000224944415418D36360200878D0B9980228223C58045044C06CD205
              08DB42D8A5040100001F01E1193497610000000049454E44AE426082}
          end>
      end
      item
        Name = 'Portes\PorteH3'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445207B200000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF2488BF84
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B201EE083
              9793000000354944415418D36360200878D0B93C28223C20011E643E0F03B208
              94091741305820340B4C29BA00BA16744331ACC574185E9F600300551F028119
              6DCF3D0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Portes\PorteH4'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              530000035C7A5458745261772070726F66696C65207479706520657869660000
              78DAED965B96E3280C86DFB58A5E02921097E56030E7CC0E66F9F383892B49A5
              AAD2A93AD32F6D120BCB20097D8284F67FFFE9F40B973871E42DA6904370B87C
              F6590A3AC91DD721D9F9795F0FEED2B9D1D3F942A052483D1EC3BEC617E8ED6D
              42F44BBFDDEA29D665272D4317CBCBA00ECF82CE1A9796219543CFEB99F29A57
              FCD572D6B75799AF6D3B5EDD3FFB886434833D15925D591DEE61785144A0590B
              64C09D35C8D028FA0A39EEFE71EEE8ECDE25EFECDDE5CE95A5D7DB54900B6B40
              B8CBD1D2B33DCEDDCCD01DB58BE79B17753F5DBCCF5D6FA9F7FD585DF101990A
              B4167559CAEC6120D2E9754E0B68115F433FCE96D112965841AC81E686568933
              0BB2DDD973E3C29DF7292B5784E8659708295245A72E69942C7542F1A3719708
              3C8D3481550535F0503963E1E9374F7F95133C37C648611863CC78D7E891F295
              761AEA7D942EB34B67AE10978C9A461883DCB8631480705F39B599DFD9E8AA6E
              DC155805419B694E586071DB6162337EAB2D9D9C15E3CC7972C7D6E0D89601A4
              08BE0DC1B082800BACC6815D1489CCC863029F82C845BD6C20C066D2983AD828
              76429424C337E6449E63C5E450E3680108C3A68940830D0458DE1BEA27FA841A
              2AA6E6C9CC82454B96AD040D3E58082186714695A8D1478B21C698628E2569F2
              C9524831A59453C992154798E59023E594732E054E0B4C17CC2E1851CA269B6E
              7EB32D6C714B5BDE4A45F9545FAD861A6BAAB996264D1BB67F0B2D524B2DB7B2
              F38E52DAFD6E7BD8E39EF6BC978E5AEBDA7DB71E7AECA9E75E4E6A8BEA2D35BE
              23F739355ED406313FC7C5376A50C77831C1E338B1C10CC4C43388C74100052D
              83994BECBD0C728399CB824D61026A6C034EE3410C04FDCE629D4F766FE43EE5
              46E67F8B9B7C448E06BA9F204703DD22F79EDB036AADCC5F149D80C62E1C3975
              DA71B0615091840FCEE3D7257DD7C05F437FDA90BA3264E9557DF7752A5136AD
              CDF75B8FF8BDA91F58A36F87B3BCD3BDFBAFE447E1D14BEE1F78A727DC7D3CFB
              4AD293B9FCD21AFD0E99CFACD323F3DDED87D97D1C2BE7AC56C3312DE16F61BA
              9B442FC6F22E36FA7CE9CFC7464F94C8CF14E4B34CE9891279AABEE8BBB15C24
              BD5A803F5B905792BEB357AFBDD3EB35782BE9670EDABF86FE6F43DAF1AF27D3
              7F80EDD3CA25B8E35E00000033504C5445F114EE000000800000008000808000
              000080800080008080808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FF
              FFFFFFFF12637DE20000000174524E530040E6D86600000001624B4744008805
              1D48000000097048597300002E2300002E230178A53F760000000774494D4507
              E306100B1F250956548B0000002A4944415418D36360A002E0E141E3F1F02084
              A06C9810921490C5C282A4125D004D0B86A118D652010000551F0281EFFF3D68
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Portes\PorteH5'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              53000003017A5458745261772070726F66696C65207479706520657869660000
              78DAED976D6E23291086FF738A3D02F545C1716868A4B9C11E7F5F68ECC44E26
              D24C461AAD6413377475F102F514B813CE7F7F8CF00F3E54240535CFA9A414F1
              D1A2852B1A395E9FABA6A8EBBA6FE2ADF1600FF7070C93A096EB369DDBBFC26E
              6F1D5CB7FD78B4076F5B276FA19BF216943932A3B1FDF21612BEECB4EF43D9FD
              AABE5BCEFE8EC6EBB11DD7A3E77B7504A31BF484039F4212714D7314C10CA448
              459D7025493C2D82B6A09E16FD3C76E1DE7C0ADEBDF514BB58B75D1E431162DA
              0EE92946DB4EF679EC56849EA8DD467E78E0E53EC4C7D88D9EC738AFD5554D88
              540A7B51B7A5AC161C114E95D52DA138BE86B6AF52503296D840AC83E681D202
              1562447B9052A74A83CE55376A98A2F2C98E9AB9B12C5B16E7C26D41D15968B0
              034F0F92C1AA819AC0CCF7B9D01AB7ACF11A658CDC099E4C1023F4F850C267C6
              DF2977A13166EA12C57C8F15E6C533A7318D496E5EE1052034764C6DC57795F0
              2E6FE23BB00282B6C29CB1C01A8F4BE2307ACB2D599C057E1635C46B6B90F72D
              8010616CC3644840202612A344D1999D0871CCE053317316E50304C88C3B8501
              36829DE09C798E8D3E4ECB978D2F338E1680306C1A071A6C20C05235E48F6B46
              0E5513D36066C9DCB215AB4992264B29799A6754757175F3E4EED98BD72C59B3
              E5943DE75C722D5C04479895543C945C4AA91583564857F4AEF0A8F5E0430E3D
              EC48871FF928476D489FA6CD5A6ADE722BAD76EED2B1FD7BEA1E7AEEA5D7934E
              A4D2A9A79DE9F4339FE5AC03B93664E8B091868F3CCAA8776A9BEA23357A22F7
              3535DAD426315D7EFE460D66F79B04CDE3C4263310632510F7490009CD9359CC
              A4CA93DC64160B635318831AD984D3691203413D896DD09DDD1BB92FB905D35F
              E2C63F231726BA3F412E4C749BDC476E9F50EB75FDA2C8023477E18C69948183
              0D4E9533FE701EFF7E1DBE2BF0127A09FD75218975D67534D1A16D19439D2F6B
              D3FACDFA25F43F13EAFDCAA363385EB5DA37B332FC91B47E09BD84FE9A90E045
              02FF4786FF006F8496329C4E1D6500000033504C544540AC8100000080000000
              8000808000000080800080008080808080C0C0C0FF000000FF00FFFF000000FF
              FF00FF00FFFFFFFFFF35C1728D0000000174524E530040E6D86600000001624B
              47440088051D48000000097048597300002E2300002E230178A53F7600000007
              74494D4507E306100B1F105FE590A8000000134944415418D36360A00BE04103
              E408D0050000991F0301169252DC0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Portes\PorteV2'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54456765740000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFD5954960
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B203BAB87
              43D40000001F4944415418D3636060E001020606040D652271D164871AC0E213
              34BF226800001F01E106FCA7E10000000049454E44AE426082}
          end>
      end
      item
        Name = 'Portes\PorteV3'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54452F41700000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF14FA7263
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B200EFD34
              87F70000002E4944415418D3636060E0E1E161000374069C0F6522F1C11C143E
              50848505854F27806E2DBAC3D09D8EEE39540600551F0281045DF93A00000000
              49454E44AE426082}
          end>
      end
      item
        Name = 'Portes\PorteV4'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544570A10E0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFAD4084F3
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B1D3526D7
              266D0000002F4944415418D3636000021E1E04C9805500CC46E6630A0079A87C
              4C0106743E030B0B21014C2308D842D0A5787D0B00551F02813F13A6AB000000
              0049454E44AE426082}
          end>
      end
      item
        Name = 'Portes\PorteV5'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54451070D10000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF5B458B59
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B1D186308
              7A18000000134944415418D3636000031E2060400623550000991F030143708C
              950000000049454E44AE426082}
          end>
      end
      item
        Name = 'Caract'#232'res\Pourcent'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B1C2EB5A9
              DEC0000000414944415418D3854FB10D003008228CFC7F7007AB103BD441D188
              20D021D1B072D541EA892EEABA065C9426B9979506EE3E5653553ECE8F0F84E7
              E719588961E200B80E051D051568350000000049454E44AE426082}
          end>
      end
      item
        Name = 'Score\Score100'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445207B200000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF2488BF84
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B1B36E984
              D051000000234944415418D36360C004FCFC100C2140143F880925B009300C19
              017EA8DBE19E4303007DF90691B0BED5BF0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Score\Score200'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445207A7A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF534C3446
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B19096DD4
              9FEE0000002F4944415418D36360C004FCFC280488E44722B00880C40809F0A3
              09F0F3A31BCACF806E0B3504306CE147F11C1A0000762E06A04BC121C3000000
              0049454E44AE426082}
          end>
      end
      item
        Name = 'Score\Score300'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445803B870000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFF6CEF3F0
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B1823AF74
              6779000000274944415418D36360C004DCDC280488E44622B00880C448150099
              8D5F807443897029BAE7D0000069D3048F29A45F400000000049454E44AE4260
              82}
          end>
      end
      item
        Name = 'Score\Score400'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544589351B0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFF82BF096
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B180974CF
              AEAF000000244944415418D36360C000DCDC0CDC60124A40041004B504B80908
              80C4682380EC39340000B14804D156DD011C0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Score\Score500'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445F174230000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF9970A9F7
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B17265886
              8F390000002D4944415418D36360C0003C40002219A00488E4412210729409F0
              F0E0170089912880CDA5685A78785008740000E4120559C271DC960000000049
              454E44AE426082}
          end>
      end
      item
        Name = 'Score\Score600'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445A0B9C90000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF9F98A9CD
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B1705FAE1
              FE4B000000234944415418D36360C0043C3C280488E4412210729409F0600860
              D8427D010CCFA10100E18A057D877D18A50000000049454E44AE426082}
          end>
      end
      item
        Name = 'Score\Score700'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54452F00000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF55A4BB17
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B1625D894
              EFC2000000284944415418D36360C0005C40002219A00488E44222B00880C448
              16E0421380DA4A070164CFA101004CA4044324DE425F0000000049454E44AE42
              6082}
          end>
      end
      item
        Name = 'Score\Score800'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445F1941E0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFDB7206D4
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B143A67AA
              80B5000000214944415418D36360C0045C5C280488E44222A82300361BAF00ED
              AC45F61C1A00007454049D95D99AE80000000049454E44AE426082}
          end>
      end
      item
        Name = 'Score\Score900'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450300000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF0717F9F2
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B1412521F
              284F000000264944415418D36360C0040202280488144022A82520802AC08021
              C0C040AA00616B313C870600E23D073150B745550000000049454E44AE426082}
          end>
      end
      item
        Name = 'Score\Score1000'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450001010000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF894CDDE4
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B13274BED
              7AAB0000001D4944415418D36360C004026004C70C02020CC8102C3C8405503D
              8706001B7D05D1727E10BA0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Touches\ToucheCtrl'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54452140BF0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF0CA5EA5A
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B1234D648
              0A340000002B4944415418D363602017F0A351FCFCFC0C1008E58358FCFC0C70
              0130E667A0B1003FAA00948724801F00006B9502D19784FA630000000049454E
              44AE426082}
          end>
      end
      item
        Name = 'Touches\ToucheEchap'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544578DB4B0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF79BF15BB
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B1200F7FC
              FE810000002C4944415418D3636020070808A01020520089C02300D301A4400C
              18860B30C094C1C5510408D882E13092010084EE04B105018D9E000000004945
              4E44AE426082}
          end>
      end
      item
        Name = 'Touches\ToucheF1'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445D14EBF0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF9E2362C9
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B111B56B4
              64AE000000254944415418D363602002F0800094852A8026CE80A990014D05A6
              19780430B4502E40000000C553030DE00E58C50000000049454E44AE426082}
          end>
      end
      item
        Name = 'Touches\ToucheF3'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445F144550000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF03EA8809
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B10399ACF
              140B0000002C4944415418D363602002F0800084461180898358300A5500450A
              5D00BBA1C80284CDC06E2D86C31086120000F1030379E3E29807000000004945
              4E44AE426082}
          end>
      end
      item
        Name = 'Touches\ToucheF6'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54453032E90000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFC85A7BA0
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B100DBB7B
              E0BE0000002A4944415418D363602002F0800084461180898358300A43006E06
              8600DC0CD20D2528806606C2E904000016B603CDEB18BD650000000049454E44
              AE426082}
          end>
      end
      item
        Name = 'Touches\ToucheF12'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450100000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF481B1895
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B0F2144F9
              82C3000000384944415418D36360200C788000448259700128068B4009900003
              420099C42200339481074D80074D31948F2CC040508007D55A98002100007DA6
              048D8BDD96490000000049454E44AE426082}
          end>
      end
      item
        Name = 'Touches\ToucheMaj'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445F1241E0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF0313449A
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B0E303752
              9370000000294944415418D3636020167073A3F1C108858F22C28D426132B8B9
              2126C2686C665047801BD90A020000B9DF0177ACF886F90000000049454E44AE
              426082}
          end>
      end
      item
        Name = 'Touches\TouchesFl'#233'ch'#233'es'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54451400000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF09C82833
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B0E081F50
              2BEE000000354944415418D36360C0010404D0F9A8220202E822A85A04600202
              48920802AE1F6E0E860086164C43B1B914D361180EC5F01C020000652E0481A9
              C813700000000049454E44AE426082}
          end>
      end
      item
        Name = 'Caract'#232'res\UnQuart'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B0D1FB7AE
              FDEA000000364944415418D36360C004FCFCE8349A008C01E72309A048814874
              0114C39014C005506C816214E3F8C100C938840056D73310104006007F8F04DE
              F800760F0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Vie'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445C13BBF0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFB8760857
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100B0C17A06E
              44990000003D4944415418D36D8F310E00200C02D918F9FF6F356A1B116F2B0D
              018009B5200E6AAE9B642932DA5F10CFDF1C1E11999F120A614B111BC55CF98F
              F3F90394CE0A7F35E243BC0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxArri'#232'reEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C5445736176000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFFE6EEBF350000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A362ADC6DBCC6000000204944415418D36360A0
              35E0E444E30B0870A2F1393838F1096068C134946A00008A54010D628967E100
              00000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxArri'#232'reNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C5445B001B8000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF5A2606940000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A351C38FA7A9C0000001F4944415418D3636060
              E01400024E08C900069C6016279C0F647322C8610D002A7D012D98B07CBD0000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxArri'#232'reOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C5445010000000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF481B18950000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A361C13D7295F000000214944415418D36360A0
              0DE0E444E30B08A088707270A08A60086068C13494060000948C010D92A6DD41
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxArri'#232'reSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C5445B001B8000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF5A2606940000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A35082220AEE10000001D4944415418D3636018
              EE80931341825902029C3012CA07B221240303001672012DE3F9016300000000
              49454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxAvantEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C544560DD52000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF934D51490000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A3327DFAB343E000000204944415418D36360A0
              0DE0E444E30B0870A2F1393838F1096068C1349406000094CC010D4D46A3E100
              00000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxAvantNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C5445481EB8000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF85FFA6760000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A313860955B49000000204944415418D3636018
              EE8093134182591C1C9C3012CC17E0E010E084900C0C00123200ED071C72A200
              00000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxAvantOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C544556DF37000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF959E195E0000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A3313FE1FC08B000000214944415418D36360A0
              35E0E444E30B08A088707270A08A60086068C134946A00008A14010DBD39A8AC
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxAvantSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C5445F08FEA000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFFA11AE8560000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A3038798E6A08000000214944415418D3636060
              E014E0E010E084900C60C0C9C1C10923A1229C0872580300EAAE00ED74C68B12
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxEntiersEst'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C5445D00EB8000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFFF6C599D50000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A2F20A7B8FCC0000000254944415418D36360A0
              15E0E4449060968000278C84F2393838212476010C2D9886521D00001E1F0219
              D468CDD60000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxEntiersNord'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C5445690000000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFFD3619F520000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A2E026BC38C650000002F4944415418D36360A0
              15E0E4449060160707278C04F3053838043821245400083821244C0988C509E7
              631A4A750000199F0219E7C49E700000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxEntiersOuest'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C544520FE00000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF9DF4E1600000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A2F09E50A64AC000000254944415418D36360A0
              15E0E4449060968000278C04F33938806C08895D00430BA6A15407001D9F0219
              4159E7E30000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\YeuxEntiersSud'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C5445508AC4000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF02EFADC30000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A2C3678411A520000002D4944415418D36360A0
              15E0E4449060968000278C84F2816C080915E0E000098048A8120E0E4E1889DD
              50AA0300221F0219683000C00000000049454E44AE426082}
          end>
      end
      item
        Name = 'Pacman\ZBouleJaune'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5522A0A76107188529D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA2033D
              0862088332B38C59494AA0E5F8BA878FAF77519ED5FADC9FA34BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CAEACB4B5CA739803816B00809221494B181226C4469
              D549B190A4FD580B7FBFEB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC580F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E99586163902BAB7818BEB86A6EC01973B40DF93219BB22BF9690AB91C
              F07E46DF94017A6F81E0AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB015EEB729F8B39A70C00000033504C5445481EB8000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF85FFA6760000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E306100A2B35AE09DD2F000000334944415418D3636000
              02161E30606180021E3840E743447878504558500558D0140095D04400C35A0C
              87613A1DD373A8DE0700405B09E1A0010D240000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeBleuAvtSArrN'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54450000000000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF8225EB06
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100D3A125D95
              5DD10000001B4944415418D36360E045010C0CD80450105102AC28881881C101
              005A1D0401300FC6C50000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeCielAvtSArrN'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C5445014FB30000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF0682A966
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E040B7A7D
              50350000001B4944415418D36360E047010C0CD80450105102EC28881881C101
              00E98D04B1178952BD0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeGrisAvtSArrN'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544551726A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF92AFC447
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0A090AF0
              1C970000001B4944415418D36360E044010C0CD804501051021C28881881C101
              007D37030A8365E01F0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeMagentaAvtSArrN'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C544551726A0000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF92AFC447
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E0F342FEF
              A4C30000001B4944415418D36360E043010C0CD804501051026C28881881C101
              00A1D50459B931CBCD0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeRougeAvtSArrN'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54452F41700000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF14FA7263
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E14326FBA
              CA6C0000001B4944415418D36360E042010C0CD804501051024C28881881C101
              0082E602F9A20E2B820000000049454E44AE426082}
          end>
      end
      item
        Name = 'Fantomes\FantomeVertAvtSArrN'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000033504C54458043110000008000000080008080000000808000800080
              80808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFD5F2F296
              0000000174524E530040E6D86600000001624B47440088051D48000000097048
              597300002E2300002E230178A53F760000000774494D4507E306100E190AF216
              0CBF0000001B4944415418D36360E046010C0CD80450105102CC28881881C101
              00CA9E03515B3C84C30000000049454E44AE426082}
          end>
      end
      item
        Name = 'Caract'#232'res\Espace'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5221595561071C8509D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA203BD
              08A10FFD32B38C59494AA0E5F8BA878FAF77519ED5FADC9FA35BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CCEACB4B5CA739843816B00809221494B181226C4469
              D549B190A4FD580BFFA0EB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC680F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E995861639027AB6818BEB86A6EC01973BC0C093219BB22BF9690AB91C
              F07E46DF940142B740D7AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB012D29728B3D9C1C6900000033504C5445B0C193000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF49F0FF980000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E30610131300FCD23D080000000D4944415418D3636018
              05C8000001100001EC97E37A0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Portes\EspacePorteH'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5221595561071C8509D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA203BD
              08A10FFD32B38C59494AA0E5F8BA878FAF77519ED5FADC9FA35BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CCEACB4B5CA739843816B00809221494B181226C4469
              D549B190A4FD580BFFA0EB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC680F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E995861639027AB6818BEB86A6EC01973BC0C093219BB22BF9690AB91C
              F07E46DF940142B740D7AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB012D29728B3D9C1C6900000033504C5445B0C193000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF49F0FF980000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E30610131300FCD23D080000000D4944415418D3636018
              05C8000001100001EC97E37A0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Portes\EspacePorteV'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              5300000185694343504943432070726F66696C65000028917D913D48C3401CC5
              5F53B5221595561071C8509D2C888A386A158A5021D40AAD3A985CFA21346948
              525C1C05D782831F8B550717675D1D5C0541F003C4C5D549D1454AFC5F526811
              EBC1713FDEDD7BDCBD03846A916956DB18A0E9B6998CC7C47466450CBCA203BD
              08A10FFD32B38C59494AA0E5F8BA878FAF77519ED5FADC9FA35BCD5A0CF089C4
              33CC306DE275E2A94DDBE0BC4F1C660559253E271E35E982C48F5C573C7EE39C
              7759E0996133959C230E138BF926569A98154C8D789238A26A3AE50B698F55CE
              5B9CB56299D5EFC95F18CCEACB4B5CA739843816B00809221494B181226C4469
              D549B190A4FD580BFFA0EB97C8A5906B038C1CF3284183ECFAC1FFE077B7566E
              62DC4B0AC680F617C7F9180602BB40ADE238DFC78E533B01FCCFC095DEF097AA
              C0F427E995861639027AB6818BEB86A6EC01973BC0C093219BB22BF9690AB91C
              F07E46DF940142B740D7AAD75B7D1FA70F408ABA4ADC000787C0489EB2D75ABC
              BBB3B9B77FCFD4FBFB012D29728B3D9C1C6900000033504C5445B0C193000000
              800000008000808000000080800080008080808080C0C0C0FF000000FF00FFFF
              000000FFFF00FF00FFFFFFFFFF49F0FF980000000174524E530040E6D8660000
              0001624B47440088051D48000000097048597300002E2300002E230178A53F76
              0000000774494D4507E30610131300FCD23D080000000D4944415418D3636018
              05C8000001100001EC97E37A0000000049454E44AE426082}
          end>
      end
      item
        Name = 'El'#233'ments\FondNoir'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100803000000282D0F
              53000002E37A5458745261772070726F66696C65207479706520657869660000
              78DAED974D92E4280C85F79C628E802484C471B08188BEC11C7F1E98FCADEA89
              988A5ECC224DA4C14A5912EF03B22AF4BF7F8DF0172E2AC221A9792E39475CA9
              A4C215038FD775F514D3BAEF87781BBCD8C3FD0B8649D0CBF598FBF6AFB0EBE3
              054BDB7EBCDA839D3B8EEF40B7C83BA0CCCC8C41DB45EE40C2979DF673287C0D
              6A7E9ACEFE8C93CB34E9717DF5FE9C0C6234453C68C45D48E2BAF39549508514
              A9E80D7712E39B4560ABF0285FF50BF159C33701EFA337FDE2B9EDF290E30A74
              9B567ED369DB49BFD76FA9F45C11F13D333F5764724FF155BFD17C8C7ECDAEA6
              1C2057DE93BA4D658DE0084993ACD7329AE1A318DB6A05CD638D27A8354CF508
              F1C0432186E2831235AA34A8AFFEA4132526EE0CB999F964593687FC85CF0525
              CD46832D804613078913E40466BED7422B6F99F990CC91B9113C99100C8C5F5B
              7837FCB4BD041A632E73A2E877AD5017CFF5853226B979871780D0D89AEAD297
              C2D5C5F76B821510D425B36382351E578843E9B1B6647196A801AE295EFB85AC
              ED009008B915C5908040CC244A99A2311B117474F0A9A89C25F10102A441B9A1
              4A4E2219709C676EBC63B47C59F932E3780108958C6DE373BB00564A9A32F69B
              6309D5A0A24955B39ABA16AD5972CA9A73B63CCFA96A62C9D4B299B915AB2E9E
              5C3DBBB97BF15AB8088E310D25172B5E4AA915496BAA8855E15F6138F890231D
              7AE4C30E3FCA514F2C9F339D7AE6D34E3FCB591B3769380242CBCD9AB7D26AA7
              8EA5D453D79EBB75EFA5D781B53664A4A1230F1B3ECAA8776A9BEA2BB57772FF
              4E8D36355EA0A69F3DA8C16C760B41F338D1C90CC4381188DB248005CD935974
              4A8927B9C92C169620A28C2A75C26934898160EAC43AE8CEEE41EEB7DC02D4FD
              AFDCF83B7261A2FB13E4C244F744EE2BB76FA8B5BA8E5B5980E62E84A6382105
              DB0F0EDD2B7B9DBF4B3FEAC34F5FFC04FA04FA04FA04FA04FA04FA04FA7F061A
              F8E301FFF0857F009F1792DDCA7D357600000184694343504943432070726F66
              696C650000789C7D913D48C3401886DFA64A452A22661051C8509D2C888A386A
              158A5021D40AAD3A985CFA074D1A92161747C1B5E0E0CF62D5C1C55957075741
              10FC0171717552749112BF4B0A2D62BCE3B887F7BEF7E5EE3B40A897986E778C
              03BA51B192F19894CEAC4AA15784D0477318A2C26C734E9613F01D5FF708F0FD
              2ECAB3FCEBFE1C3D5AD6664040229E65A65521DE209EDEAC989CF78945565034
              E273E2318B2E48FCC875D5E337CE7997059E295AA9E43CB1482CE5DB586D6356
              B074E229E288A61B942FA43DD6386F71D64B55D6BC277F61386BAC2C739DD610
              E258C412644850514511255410A5DD20C54692CE633EFE41D72F934B2557118C
              1C0B284387E2FAC1FFE0776FEDDCE48497148E019D2F8EF3310284768146CD71
              BE8F1DA77102049F812BA3E52FD781994FD26B2D2D7204F46E0317D72D4DDD03
              2E7780812753B114570AD2127239E0FD8CBE2903F4DF02DD6B5EDF9AE7387D00
              52D4ABC40D7070088CE6297BDDE7DD5DED7DFBB7A6D9BF1F48A67296DB5DFC54
              00000033504C5445009082000000800000008000808000000080800080008080
              808080C0C0C0FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFFDD0463FB00
              0000097048597300002E2300002E230178A53F760000000774494D4507E30711
              111E24F3273D2F0000000F4944415418D3636044030C235B00008910010129A5
              1CC80000000049454E44AE426082}
          end>
      end>
    Left = 104
    Top = 16
  end
  object VirtualImageListMsg: TVirtualImageList
    AutoFillMode = afmDisabled
    DisabledGrayscale = False
    DisabledSuffix = '_Disabled'
    Images = <
      item
        CollectionIndex = 1
        CollectionName = 'Chiffres\Chiffre0'
        Disabled = False
        Name = 'Chiffre0'
      end
      item
        CollectionIndex = 2
        CollectionName = 'Chiffres\Chiffre1'
        Disabled = False
        Name = 'Chiffre1'
      end
      item
        CollectionIndex = 3
        CollectionName = 'Chiffres\Chiffre2'
        Disabled = False
        Name = 'Chiffre2'
      end
      item
        CollectionIndex = 4
        CollectionName = 'Chiffres\Chiffre3'
        Disabled = False
        Name = 'Chiffre3'
      end
      item
        CollectionIndex = 5
        CollectionName = 'Chiffres\Chiffre4'
        Disabled = False
        Name = 'Chiffre4'
      end
      item
        CollectionIndex = 6
        CollectionName = 'Chiffres\Chiffre5'
        Disabled = False
        Name = 'Chiffre5'
      end
      item
        CollectionIndex = 7
        CollectionName = 'Chiffres\Chiffre6'
        Disabled = False
        Name = 'Chiffre6'
      end
      item
        CollectionIndex = 8
        CollectionName = 'Chiffres\Chiffre7'
        Disabled = False
        Name = 'Chiffre7'
      end
      item
        CollectionIndex = 9
        CollectionName = 'Chiffres\Chiffre8'
        Disabled = False
        Name = 'Chiffre8'
      end
      item
        CollectionIndex = 10
        CollectionName = 'Chiffres\Chiffre9'
        Disabled = False
        Name = 'Chiffre9'
      end
      item
        CollectionIndex = 189
        CollectionName = 'Caract'#232'res\Espace'
        Disabled = False
        Name = 'Espace'
      end
      item
        CollectionIndex = 90
        CollectionName = 'Lettres\LettreA'
        Disabled = False
        Name = 'LettreA'
      end
      item
        CollectionIndex = 91
        CollectionName = 'Lettres\LettreB'
        Disabled = False
        Name = 'LettreB'
      end
      item
        CollectionIndex = 92
        CollectionName = 'Lettres\LettreC'
        Disabled = False
        Name = 'LettreC'
      end
      item
        CollectionIndex = 93
        CollectionName = 'Lettres\LettreD'
        Disabled = False
        Name = 'LettreD'
      end
      item
        CollectionIndex = 94
        CollectionName = 'Lettres\LettreE'
        Disabled = False
        Name = 'LettreE'
      end
      item
        CollectionIndex = 95
        CollectionName = 'Lettres\LettreF'
        Disabled = False
        Name = 'LettreF'
      end
      item
        CollectionIndex = 96
        CollectionName = 'Lettres\LettreG'
        Disabled = False
        Name = 'LettreG'
      end
      item
        CollectionIndex = 97
        CollectionName = 'Lettres\LettreH'
        Disabled = False
        Name = 'LettreH'
      end
      item
        CollectionIndex = 98
        CollectionName = 'Lettres\LettreI'
        Disabled = False
        Name = 'LettreI'
      end
      item
        CollectionIndex = 99
        CollectionName = 'Lettres\LettreJ'
        Disabled = False
        Name = 'LettreJ'
      end
      item
        CollectionIndex = 100
        CollectionName = 'Lettres\LettreK'
        Disabled = False
        Name = 'LettreK'
      end
      item
        CollectionIndex = 101
        CollectionName = 'Lettres\LettreL'
        Disabled = False
        Name = 'LettreL'
      end
      item
        CollectionIndex = 102
        CollectionName = 'Lettres\LettreM'
        Disabled = False
        Name = 'LettreM'
      end
      item
        CollectionIndex = 103
        CollectionName = 'Lettres\LettreN'
        Disabled = False
        Name = 'LettreN'
      end
      item
        CollectionIndex = 104
        CollectionName = 'Lettres\LettreO'
        Disabled = False
        Name = 'LettreO'
      end
      item
        CollectionIndex = 105
        CollectionName = 'Lettres\LettreP'
        Disabled = False
        Name = 'LettreP'
      end
      item
        CollectionIndex = 106
        CollectionName = 'Lettres\LettreQ'
        Disabled = False
        Name = 'LettreQ'
      end
      item
        CollectionIndex = 107
        CollectionName = 'Lettres\LettreR'
        Disabled = False
        Name = 'LettreR'
      end
      item
        CollectionIndex = 108
        CollectionName = 'Lettres\LettreS'
        Disabled = False
        Name = 'LettreS'
      end
      item
        CollectionIndex = 109
        CollectionName = 'Lettres\LettreT'
        Disabled = False
        Name = 'LettreT'
      end
      item
        CollectionIndex = 111
        CollectionName = 'Lettres\LettreU'
        Disabled = False
        Name = 'LettreU'
      end
      item
        CollectionIndex = 112
        CollectionName = 'Lettres\LettreV'
        Disabled = False
        Name = 'LettreV'
      end
      item
        CollectionIndex = 113
        CollectionName = 'Lettres\LettreW'
        Disabled = False
        Name = 'LettreW'
      end
      item
        CollectionIndex = 114
        CollectionName = 'Lettres\LettreX'
        Disabled = False
        Name = 'LettreX'
      end
      item
        CollectionIndex = 115
        CollectionName = 'Lettres\LettreY'
        Disabled = False
        Name = 'LettreY'
      end
      item
        CollectionIndex = 116
        CollectionName = 'Lettres\LettreZ'
        Disabled = False
        Name = 'LettreZ'
      end
      item
        CollectionIndex = 131
        CollectionName = 'Pacman\PacManEntierBOEst'
        Disabled = False
        Name = 'PacManEntierBOEst'
      end
      item
        CollectionIndex = 117
        CollectionName = 'El'#233'ments\Mur'
        Disabled = False
        Name = 'Mur'
      end
      item
        CollectionIndex = 118
        CollectionName = 'El'#233'ments\PacGum'
        Disabled = False
        Name = 'PacGum'
      end
      item
        CollectionIndex = 80
        CollectionName = 'Fantomes\FantomeVertEntierOuest'
        Disabled = False
        Name = 'FantomeVertEntierOuest'
      end
      item
        CollectionIndex = 160
        CollectionName = 'Touches\ToucheCtrl'
        Disabled = False
        Name = 'ToucheCtrl'
      end
      item
        CollectionIndex = 166
        CollectionName = 'Touches\ToucheMaj'
        Disabled = False
        Name = 'ToucheMaj'
      end
      item
        CollectionIndex = 162
        CollectionName = 'Touches\ToucheF1'
        Disabled = False
        Name = 'ToucheF1'
      end
      item
        CollectionIndex = 163
        CollectionName = 'Touches\ToucheF3'
        Disabled = False
        Name = 'ToucheF3'
      end
      item
        CollectionIndex = 164
        CollectionName = 'Touches\ToucheF6'
        Disabled = False
        Name = 'ToucheF6'
      end
      item
        CollectionIndex = 165
        CollectionName = 'Touches\ToucheF12'
        Disabled = False
        Name = 'ToucheF12'
      end
      item
        CollectionIndex = 167
        CollectionName = 'Touches\TouchesFl'#233'ch'#233'es'
        Disabled = False
        Name = 'TouchesFl'#233'ch'#233'es'
      end
      item
        CollectionIndex = 110
        CollectionName = 'Caract'#232'res\LettreTilde'
        Disabled = False
        Name = 'LettreTilde'
      end
      item
        CollectionIndex = 11
        CollectionName = 'Caract'#232'res\DeuxPoints'
        Disabled = False
        Name = 'DeuxPoints'
      end
      item
        CollectionIndex = 168
        CollectionName = 'Caract'#232'res\UnQuart'
        Disabled = False
        Name = 'UnQuart'
      end
      item
        CollectionIndex = 140
        CollectionName = 'El'#233'ments\Pillule'
        Disabled = False
        Name = 'Pillule'
      end
      item
        CollectionIndex = 0
        CollectionName = 'Caract'#232'res\Apostrophe'
        Disabled = False
        Name = 'Apostrophe'
      end
      item
        CollectionIndex = 85
        CollectionName = 'El'#233'ments\Fond'
        Disabled = False
        Name = 'Fond'
      end
      item
        CollectionIndex = 161
        CollectionName = 'Touches\ToucheEchap'
        Disabled = False
        Name = 'ToucheEchap'
      end
      item
        CollectionIndex = 149
        CollectionName = 'Caract'#232'res\Pourcent'
        Disabled = False
        Name = 'Pourcent'
      end
      item
        CollectionIndex = 13
        CollectionName = 'Etoiles\EtoileAllum'#233'e'
        Disabled = False
        Name = 'EtoileAllum'#233'e'
      end
      item
        CollectionIndex = 15
        CollectionName = 'Etoiles\EtoileMiEteinteMiAllum'#233'e'
        Disabled = False
        Name = 'EtoileMiEteinteMiAllum'#233'e'
      end
      item
        CollectionIndex = 14
        CollectionName = 'Etoiles\EtoileEteinte'
        Disabled = False
        Name = 'EtoileEteinte'
      end
      item
        CollectionIndex = 88
        CollectionName = 'Jokers\JokerPique'
        Disabled = False
        Name = 'JokerPique'
      end
      item
        CollectionIndex = 87
        CollectionName = 'Jokers\JokerCoeur'
        Disabled = False
        Name = 'JokerCoeur'
      end
      item
        CollectionIndex = 89
        CollectionName = 'Jokers\JokerTrefle'
        Disabled = False
        Name = 'JokerTrefle'
      end
      item
        CollectionIndex = 86
        CollectionName = 'Jokers\JokerCarreau'
        Disabled = False
        Name = 'JokerCarreau'
      end
      item
        CollectionIndex = 139
        CollectionName = 'Caract'#232'res\ParamPorte'
        Disabled = False
        Name = 'ParamPorte'
      end
      item
        CollectionIndex = 82
        CollectionName = 'Caract'#232'res\Fl'#232'cheDroite'
        Disabled = False
        Name = 'Fl'#232'cheDroite'
      end
      item
        CollectionIndex = 192
        CollectionName = 'El'#233'ments\FondNoir'
        Disabled = False
        Name = 'FondNoir'
      end>
    ImageCollection = ImageCollection
    PreserveItems = True
    Left = 144
    Top = 32
  end
end
