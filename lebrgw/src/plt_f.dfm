object frmPlateau: TfrmPlateau
  Left = 365
  Top = 142
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Le Berger'
  ClientHeight = 428
  ClientWidth = 683
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu
  OldCreateOrder = True
  Position = poScreenCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DrawGrid: TDrawGrid
    Left = 0
    Top = 0
    Width = 683
    Height = 386
    Align = alClient
    ColCount = 40
    DefaultColWidth = 16
    DefaultRowHeight = 16
    FixedCols = 0
    RowCount = 25
    FixedRows = 0
    Options = []
    ScrollBars = ssNone
    TabOrder = 0
    OnClick = DrawGridClick
    OnDrawCell = DrawGridDrawCell
    OnKeyDown = DrawGridKeyDown
    OnKeyPress = DrawGridKeyPress
    OnMouseDown = DrawGridMouseDown
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 409
    Width = 683
    Height = 19
    Font.Charset = ANSI_CHARSET
    Font.Color = clBtnText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Pitch = fpFixed
    Font.Style = []
    Panels = <
      item
        Width = 631
      end
      item
        Alignment = taCenter
        Text = '(-,-)'
        Width = 54
      end>
    SizeGrip = False
    UseSystemFont = False
  end
  object PanelScores: TPanel
    Left = 0
    Top = 386
    Width = 683
    Height = 23
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 2
    object Label3: TLabel
      Left = 5
      Top = 5
      Width = 24
      Height = 13
      Caption = 'S'#233'rie'
    end
    object LabelSerie: TLabel
      Left = 34
      Top = 5
      Width = 5
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelScore0: TLabel
      Left = 268
      Top = 5
      Width = 28
      Height = 13
      AutoSize = False
      Caption = 'Score'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabelScore: TLabel
      Left = 303
      Top = 4
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
    object LabelBarre0: TLabel
      Left = 368
      Top = 5
      Width = 25
      Height = 13
      AutoSize = False
      Caption = 'Barre'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clPurple
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabelBarre: TLabel
      Left = 401
      Top = 4
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
    object LabelNiveau0: TLabel
      Left = 189
      Top = 5
      Width = 34
      Height = 13
      AutoSize = False
      Caption = 'Niveau'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object LabelNiveau: TLabel
      Left = 230
      Top = 4
      Width = 27
      Height = 17
      Caption = '000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelTemps0: TLabel
      Left = 464
      Top = 5
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'Temps'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabelTemps: TLabel
      Left = 503
      Top = 4
      Width = 36
      Height = 17
      Caption = '0000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clMaroon
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelReste0: TLabel
      Left = 552
      Top = 5
      Width = 28
      Height = 13
      AutoSize = False
      Caption = 'Reste'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clOlive
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabelReste: TLabel
      Left = 587
      Top = 4
      Width = 18
      Height = 17
      Caption = '00'
      Font.Charset = ANSI_CHARSET
      Font.Color = clOlive
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelEffet0: TLabel
      Left = 621
      Top = 5
      Width = 22
      Height = 13
      AutoSize = False
      Caption = 'Effet'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabelEffet: TLabel
      Left = 650
      Top = 4
      Width = 27
      Height = 17
      Caption = '000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clGreen
      Font.Height = -15
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object MainMenu: TMainMenu
    Left = 656
    object MenuPartie: TMenuItem
      Caption = '&Partie'
      object RubriqueNouvelle: TMenuItem
        Caption = 'Nouvelle &Partie'
        Enabled = False
        ShortCut = 115
        OnClick = RubriqueNouvelleClick
      end
      object RubriqueOuvrir: TMenuItem
        Caption = '&Ouvrir'
        Enabled = False
        ShortCut = 114
        OnClick = RubriqueOuvrirClick
      end
      object RubriqueChangerSerie: TMenuItem
        Caption = '&Changer de s'#233'rie'
        Enabled = False
        ShortCut = 16499
        OnClick = RubriqueChangerSerieClick
      end
      object Sep1: TMenuItem
        Caption = '-'
      end
      object RubriqueInterrompre: TMenuItem
        Caption = '&Interrompre'
        Enabled = False
        ShortCut = 116
        OnClick = RubriqueInterrompreClick
      end
    end
    object MenuEditeur: TMenuItem
      Caption = '&Editeur'
      object RubriqueNouveauNiveau: TMenuItem
        Caption = '&Nouveau niveau'
        ShortCut = 8307
        OnClick = RubriqueNouveauNiveauClick
      end
      object Sep5: TMenuItem
        Caption = '-'
      end
      object RubriqueOuvrirNiveau: TMenuItem
        Caption = '&Ouvrir un niveau'
        ShortCut = 8306
        OnClick = RubriqueOuvrirNiveauClick
      end
      object RubriqueOuvrirNiveauPrecedent: TMenuItem
        Caption = 'Ouvrir le niveau &pr'#233'c'#233'dent'
        ShortCut = 8310
        OnClick = RubriqueOuvrirNiveauPrecedentClick
      end
      object RubriqueOuvrirNiveauSuivant: TMenuItem
        Caption = 'Ouvrir le niveau &suivant'
        ShortCut = 8311
        OnClick = RubriqueOuvrirNiveauSuivantClick
      end
      object Sep7: TMenuItem
        Caption = '-'
      end
      object RubriqueEnregistrerNiveau: TMenuItem
        Caption = '&Enregistrer le niveau'
        ShortCut = 8305
        OnClick = RubriqueEnregistrerNiveauClick
      end
      object Sep8: TMenuItem
        Caption = '-'
      end
      object RubriqueTesterNiveau: TMenuItem
        Caption = '&Tester le niveau'
        ShortCut = 8308
        OnClick = RubriqueTesterNiveauClick
      end
      object RubriqueInterrompreNiveau: TMenuItem
        Caption = '&Interrompre le niveau'
        Enabled = False
        ShortCut = 116
        OnClick = RubriqueInterrompreNiveauClick
      end
      object Sep2: TMenuItem
        Caption = '-'
      end
      object RubriqueParametresNiveau: TMenuItem
        Caption = '&Param'#232'tre du niveau'
        ShortCut = 8309
        OnClick = RubriqueParametresNiveauClick
      end
    end
    object MenuOptions: TMenuItem
      Caption = '&Options'
      object RubriqueCommandes: TMenuItem
        Caption = 'Commandes au cla&vier...'
        ShortCut = 16459
        OnClick = RubriqueCommandesClick
      end
      object RubriqueCouleurCurseur: TMenuItem
        Caption = '&Couleur du curseur...'
        ShortCut = 16451
        OnClick = RubriqueCouleurCurseurClick
      end
    end
    object MenuMode: TMenuItem
      Caption = '&Mode'
      object RubriqueJeu: TMenuItem
        Caption = '&Jeu'
        RadioItem = True
        ShortCut = 16458
        OnClick = RubriqueJeuClick
      end
      object RubriqueEditeur: TMenuItem
        Caption = '&Editeur'
        Checked = True
        RadioItem = True
        ShortCut = 16453
        OnClick = RubriqueEditeurClick
      end
    end
    object MenuAffichage: TMenuItem
      Caption = '&Affichage'
      object MenuMessages: TMenuItem
        Caption = '&Messages'
        object RubriqueMsgLigneStatut: TMenuItem
          Caption = 'Dans la ligne de &statut'
          RadioItem = True
          ShortCut = 16467
          OnClick = RubriqueMsgLigneStatutClick
        end
        object RubriqueMsgBoiteDialogue: TMenuItem
          Caption = 'Dans une bo'#238'te de &dialogue'
          Checked = True
          RadioItem = True
          ShortCut = 16452
          OnClick = RubriqueMsgBoiteDialogueClick
        end
      end
      object MenuAffEditeur: TMenuItem
        Caption = '&Editeur'
        object RubriqueQuadrillage: TMenuItem
          Caption = '&Quadrillage'
          Checked = True
          ShortCut = 16465
          OnClick = RubriqueQuadrillageClick
        end
        object Sep9: TMenuItem
          Caption = '-'
        end
        object RubriqueBetes: TMenuItem
          Caption = '&B'#234'tes'
          Checked = True
          ShortCut = 16450
          OnClick = RubriqueBetesClick
        end
        object RubriquePortes: TMenuItem
          Caption = '&Portes'
          Checked = True
          ShortCut = 16464
          OnClick = RubriquePortesClick
        end
        object RubriqueDeclencheurs: TMenuItem
          Caption = '&D'#233'clencheurs'
          Checked = True
          ShortCut = 16452
          OnClick = RubriqueDeclencheursClick
        end
        object SepF: TMenuItem
          Caption = '-'
        end
        object RubriqueTout: TMenuItem
          Caption = '&Rien'
          ShortCut = 16432
          OnClick = RubriqueToutClick
        end
      end
      object MenuItemDiplome: TMenuItem
        Caption = '&Dipl'#244'me...'
        Visible = False
        OnClick = MenuItemDiplomeClick
      end
    end
    object MenuInformations: TMenuItem
      Caption = '&Informations'
      object RubriquePartiesSauvegardees: TMenuItem
        Caption = 'Parties sauve&gard'#233'es...'
        ShortCut = 16455
        OnClick = RubriquePartiesSauvegardeesClick
      end
      object RubriqueRecords: TMenuItem
        Caption = '&Records...'
        ShortCut = 16466
        OnClick = RubriqueRecordsClick
      end
      object SepG: TMenuItem
        Caption = '-'
      end
      object RubriqueRDJetUTL: TMenuItem
        Caption = 'R'#232'gle du &jeu et utilisation'
        ShortCut = 112
        OnClick = RubriqueRDJetUTLClick
      end
      object RubriqueAPropos: TMenuItem
        Caption = #192' &propos...'
        ShortCut = 32880
        OnClick = RubriqueAProposClick
      end
    end
    object RubriqueQuitter: TMenuItem
      Caption = '&Quitter'
      ShortCut = 32883
      OnClick = RubriqueQuitterClick
    end
  end
  object PopupMenuEditeur: TPopupMenu
    Left = 624
    object RubriquePoserMur: TMenuItem
      Caption = 'Poser un mur'
      ShortCut = 13
      OnClick = RubriquePoserMurClick
    end
    object RubriqueLibererEspace: TMenuItem
      Caption = 'Lib'#233'rer l'#39'espace'
      ShortCut = 32
      OnClick = RubriqueLibererEspaceClick
    end
    object Sep3: TMenuItem
      Caption = '-'
    end
    object RubriquePoserPorteO: TMenuItem
      Caption = 'Poser une porte ouverte'
      ShortCut = 79
      OnClick = RubriquePoserPorteOClick
    end
    object RubriquePoserPorteF: TMenuItem
      Caption = 'Poser une porte ferm'#233'e'
      ShortCut = 70
      OnClick = RubriquePoserPorteFClick
    end
    object Sep4: TMenuItem
      Caption = '-'
    end
    object RubriquePoserDeclencheurB: TMenuItem
      Caption = 'Poser un d'#233'clencheur bleu'
      ShortCut = 66
      OnClick = RubriquePoserDeclencheurBClick
    end
    object RubriquePoserDeclencheurR: TMenuItem
      Caption = 'Poser un d'#233'clencheur rouge'
      ShortCut = 82
      OnClick = RubriquePoserDeclencheurRClick
    end
    object Sep6: TMenuItem
      Caption = '-'
    end
    object RubriquePoserRetirerBete: TMenuItem
      Caption = 'Poser/retirer une b'#234'te'
      ShortCut = 88
      OnClick = RubriquePoserRetirerBeteClick
    end
    object RubriqueOrienterBeteG: TMenuItem
      Caption = 'Orienter la b'#234'te '#224' gauche'
      Enabled = False
      ShortCut = 226
      OnClick = RubriqueOrienterBeteGClick
    end
    object RubriqueOrienterBeteD: TMenuItem
      Caption = 'Orienter la b'#234'te '#224' droite'
      Enabled = False
      ShortCut = 8418
      OnClick = RubriqueOrienterBeteDClick
    end
  end
  object OpenDialogNiveau: TOpenDialog
    DefaultExt = 'nlb'
    FileName = 'serie1'
    Filter = 'Niveaux Le berger (*.nlb)|*.NLB|Tous fichiers (*.*)|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist]
    Title = 'Ouvrir un niveau (nom de la s'#233'rie)'
    Left = 552
  end
  object SaveDialogNiveau: TSaveDialog
    DefaultExt = 'nlb'
    FileName = 'serie1'
    Filter = 'Niveaux Le berger (*.nlb)|*.NLB|Tous fichiers (*.*)|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofFileMustExist]
    Title = 'Enregistrer le niveau (nom de la s'#233'rie)'
    Left = 584
  end
  object TimerMsg: TTimer
    Interval = 100
    OnTimer = TimerMsgTimer
    Left = 520
  end
  object TimerJeu: TTimer
    Enabled = False
    OnTimer = TimerJeuTimer
    Left = 488
  end
  object PopupMenuJeu: TPopupMenu
    Left = 624
    Top = 28
    object TitreMenuAction: TMenuItem
      Caption = 'Menu Action'
      Default = True
    end
    object SepA: TMenuItem
      Caption = '-'
      ShortCut = 35
    end
    object RubriqueNord: TMenuItem
      Caption = '&Nord'
      ShortCut = 38
      OnClick = RubriqueNordClick
    end
    object RubriquePorteHaut: TMenuItem
      Caption = 'Actionner la porte en &Haut'
      ShortCut = 90
      OnClick = RubriquePorteHautClick
    end
    object SepB: TMenuItem
      Caption = '-'
      ShortCut = 36
    end
    object RubriqueEst: TMenuItem
      Caption = '&Est'
      ShortCut = 39
      OnClick = RubriqueEstClick
    end
    object RubriquePorteDroite: TMenuItem
      Caption = 'Actionner la porte '#224' &Droite'
      ShortCut = 83
      OnClick = RubriquePorteDroiteClick
    end
    object SepC: TMenuItem
      Caption = '-'
      ShortCut = 33
    end
    object RubriqueSud: TMenuItem
      Caption = '&Sud'
      ShortCut = 40
      OnClick = RubriqueSudClick
    end
    object RubriquePorteBas: TMenuItem
      Caption = 'Actionner la porte en &Bas'
      ShortCut = 87
      OnClick = RubriquePorteBasClick
    end
    object SepD: TMenuItem
      Caption = '-'
      ShortCut = 34
    end
    object RubriqueOuest: TMenuItem
      Caption = '&Ouest'
      ShortCut = 37
      OnClick = RubriqueOuestClick
    end
    object RubriquePorteGauche: TMenuItem
      Caption = 'Actionner la porte '#224' &Gauche'
      ShortCut = 81
      OnClick = RubriquePorteGaucheClick
    end
    object SepH: TMenuItem
      Caption = '-'
      ShortCut = 16419
      Visible = False
    end
    object SepI: TMenuItem
      Caption = '-'
      ShortCut = 16420
      Visible = False
    end
    object SepJ: TMenuItem
      Caption = '-'
      ShortCut = 16417
      Visible = False
    end
    object SepK: TMenuItem
      Caption = '-'
      ShortCut = 24610
      Visible = False
    end
    object SepL: TMenuItem
      Caption = '-'
      ShortCut = 16419
      Visible = False
    end
    object SepM: TMenuItem
      Caption = '-'
      ShortCut = 24612
      Visible = False
    end
    object SepN: TMenuItem
      Caption = '-'
      ShortCut = 24609
      Visible = False
    end
    object SepO: TMenuItem
      Caption = '-'
      ShortCut = 24610
      Visible = False
    end
    object SepP: TMenuItem
      Caption = '-'
      ShortCut = 8227
      Visible = False
    end
    object SepQ: TMenuItem
      Caption = '-'
      ShortCut = 8228
      Visible = False
    end
    object SepR: TMenuItem
      Caption = '-'
      ShortCut = 8225
      Visible = False
    end
    object SepS: TMenuItem
      Caption = '-'
      ShortCut = 8226
      Visible = False
    end
  end
  object ColorDialog: TColorDialog
    Color = clFuchsia
    CustomColors.Strings = (
      'ColorA=80'
      'ColorB=8000'
      'ColorC=8080'
      'ColorD=800000'
      'ColorE=800080'
      'ColorF=808000'
      'ColorG=C0C0C0'
      'ColorH=FF'
      'ColorI=FF00'
      'ColorJ=FFFF'
      'ColorK=FF0000'
      'ColorL=FF00FF'
      'ColorM=FFFF00'
      'ColorN=808080'
      'ColorO=0'
      'ColorP=FFFFFF')
    Options = [cdPreventFullOpen]
    Left = 456
  end
  object ImageCollection: TImageCollection
    Images = <
      item
        Name = '0\000'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102D
              0B473C65B5000000574944415408D7258DB10DC04008033D6D3AD6FA8E655250
              58BA5D62F205129CCE58D00507D15933826906ABBCC4A88942950218AF53E1F1
              2283E7A64E56F4E4CA3F87BCF9D97FBCD7DB8A39C96B851C56A2BEED5B10F601
              5DB36598ECC09EBA0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\001'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102D
              06398D1908000000634944415408D7358EB10900310C03BD64AAF4DF04AF95CE
              652A9135523868979779DE601042F2D9C87072D218925A234FF030CD93C04E5A
              7000703719AB612B33D03A10C62B6381253A9AC4735785520E2A54F5BF15B290
              8598BA2C448AF3D135FA235E45EA5DED7385C8FC0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\002'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1028
              125E203930000000684944415408D72D8EC109C0300C03B55367C9AB2394BCB3
              517E7EE625BA461F0EDAA532ADC12084E433A4E8D21414965E484FE851A2A7C8
              3B85D045B277D8588DB7302EB6931C38B68DC5A3C4C96631F6AAD080362B54F5
              BFA5B0C52CC4F46523D29C8FEEF11FF10240B25A579050F9E30000000049454E
              44AE426082}
          end>
      end
      item
        Name = '0\003'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1028
              0DD32834C5000000684944415408D72D8EB10DC0300804D989595C7984C8351B
              B9A374F5F21A29887E97BC952021BD9E87C3C81CE4A43125D546DEC99B65A308
              ECA2252F0063988CD5B06911681D11E62E63B91FD1D1242296421AF1C1099DF5
              7F8B290B751053978528713EBA4A7FE40B5C635717818529F70000000049454E
              44AE426082}
          end>
      end
      item
        Name = '0\004'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1028
              08A342C04A000000674944415408D72D8EB10DC0300804D9C9B3B8F208916B6F
              E48ED2D5CB6BB820FA5DF22441E2F57A048791DEC949A3CBAA8D3CCEC3B01E04
              76D09C1780DE4DC1AAD8B431466D122BA55448D2B4D728C5CA116FA036E4FABF
              45578448C4D46521429C8FAED21FFE00AE7254CB5BF0B2E50000000049454E44
              AE426082}
          end>
      end
      item
        Name = '0\005'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              2F6224B0250000005F4944415408D7458EC109C0300C03B55367C9AB2394BCBB
              517E7EF625B2461E2EDAA50A0DADC02064E433A4A8521314B61E48233494A829
              B2A7103A48D60A07576117CE256C4BBFF956BAC9B273D6574BE1883911CD978D
              48735EBAE53FE20144A0532D38A7F09D0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\006'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1028
              1DCE9F24A1000000654944415408D7358DBB0D80300C05BD1593A4A2A741A9D8
              89CE65AA27D648E1E876C196A03B9DDEC7C0AF8D1BC3B9362781E94CC27A203D
              8139A7A4DE2DC5687A3273AAED921B2BC51005BB5AC2B14685228D2A54F5BFE5
              A9147571E7725EC4E47BA7007F016BDD5AC0F3826B810000000049454E44AE42
              6082}
          end>
      end
      item
        Name = '0\007'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1028
              03349019C2000000674944415408D7358DB10DC4300C03B595277195FE9BC095
              774AA7D21591355CC8B85D5E02FEBB0341F20C7C361E0C673627813DDB266C44
              266F60CE2D690C0BB4BADEECDCEA97E4C6C96089824B3DE1735695221355A9E6
              FF959FD914A578F23915B1F9D929C0BF7D60577C59F80BA00000000049454E44
              AE426082}
          end>
      end
      item
        Name = '0\008'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1028
              18BEF5D02E000000664944415408D7358DAB0D00211044B72B2A41E1CF10143D
              E156A226B4815832BDDC90DCB99797F918E93D71D0E8ECC929E0EE6933AC85CC
              0A9AB3F684D62C08C152A62217C08D67664CF04241163C67422E64142EB8F5BF
              E54710F762685917B1F9BDF302FD05E463558A28795D2A0000000049454E44AE
              426082}
          end>
      end
      item
        Name = '0\009'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              34E84179C9000000644944415408D735CDA10DC4400C445177E54A0E1D3F122D
              724F61864156DA58E0E8F772B34AC29E461E8F4186B36324E189C00C9FB48D56
              7236966CE1358635259CBAD9162A8DEB083F8A1B1FE177A395E8E65BABFEB6F2
              127A4DECFAAC899E3CEB2C907F7B0953ECE24395880000000049454E44AE4260
              82}
          end>
      end
      item
        Name = '0\010'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              38E1F735E20000005F4944415408D7658DB109C0300C04950154A81578C18087
              7293C2F0BBD84D0AC1EF12D91052A43B0EFE4F4854F2A210EC1D4C60377384D4
              98661614C0C6980512ADA8AA25A448E50929F4F0CF9C3F8377C5FDE309D1D673
              48DCABB5EADC753C40EB426359AA949C0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\011'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102D
              01A7E98CAB0000005E4944415408D7658DB109C0300C0455A6D1A201EF21045E
              2318C3EFE22A18C1EF12D91052A43B0EFE4F4814F2A210EC1D4C603773849498
              661614C0C6981512ADAAAA25A448E50929F4F0CF9C3F8377C5FDE309D1D67348
              DCABB5EADC753CE7D7505589FF5A440000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_0000'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              21859C9D220000002A4944415408D763702F2F2F06610638C3050A188C8D9D8D
              41980122E15E8E60C0D54054181B3350C91C00329429E1F40CF3CE0000000049
              454E44AE426082}
          end>
      end
      item
        Name = '0\012_0001'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              261BF808810000002F4944415408D76360800117286030860220C3D9188419CA
              8BDDCB4118C1802B86A8002A8648941723184806126F0E0089D324D9F644BE8A
              0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_0010'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              174A2608BB000000314944415408D763702F2F2F762F2F766080335CC0C0D981
              C1D8D8D918881D184012E5C5C80CB81AB00A636324ED94990300AFA128392836
              3D5D0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_0011'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              123A4CFC34000000344944415408D7636080011708706030860010C319483B3B
              309417BB9797172333206A810CB00A906290847B79311203AE8614730045C923
              AD90E7D1560000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_0100'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              1DAAF3E1A5000000304944415408D763702F2F2F06610638C3050A188C8D9D8D
              41980122E15E8E60C0D54054181B3390648E311420D4C0000003D02671B3D287
              6B0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_0101'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              09B02935D8000000344944415408D76360800117286030860220C3D9188419CA
              8BDDCB4118C1802B86A8002A8648941723184806A29B03B702AE0606005B0F21
              6975345AA90000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_0110'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              3B37BFF29F0000003A4944415408D763702F2F2F762F2F766080335CC0C0D981
              C1D8D8D918881D184012E5C5C80CB81AB00A636324EDC498630C0130352E0E0C
              300000863725052F3DB0AF0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_0111'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              04CE9849650000003A4944415408D7636080011708706030860010C319483B3B
              309417BB9797172333206A810CB00A906290847B79311203AE06D31CB815704B
              6100001C5F2079A1403E870000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_1000'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102C
              0E2E4DA07B0000002F4944415408D76360312F2F762F2F2F6640304C5CC08081
              C5D8D9D81888810C90847B391203A1C618AC8A814AE600001D2222EDEEA6E566
              0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_1001'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              36490E8E22000000344944415408D763608001161708606031860020C3194839
              8318EEE5E5C5EEE5480C1324C5CE60C5E62089F2622406420DF1E60000F02D1E
              CCE7D9EC290000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_1010'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              30A06D2B17000000304944415408D76360312F2F762F2F766040304C5C80C019
              C830763636360633DCCBCB8B51180835C62055C8DA293207009A2F21453BCF3A
              500000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_1011'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              20BDDA3B73000000374944415408D76360800116173070606031060310C31948
              3B8318EEE5E5C5280C13905A67886267B062F3F262F7F2626406420DF1E60000
              AC231DA0288D3A9B0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_1100'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              2A5D0FD26D000000364944415408D76360312F2F762F2F2F6640304C5CC08081
              C5D8D9D81888810C90847B391203A1C618AC8A814473208081C505AA060600FE
              6F20500843EED30000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_1101'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              25CDB0CFFC000000394944415408D763608001161708606031860020C3194839
              8318EEE5E5C5EEE5480C1324C5CE60C5E62089F2622406420DA639302B6096C2
              0000D1891C2FB6D1A6350000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_1110'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              167260AEEA000000394944415408D76360312F2F762F2F766040304C5C80C019
              C830763636360633DCCBCB8B51180835C62055C8DA8932070C800C1730706080
              010080E51EE409788BDE0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\012_1111'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              1B0CD1D2570000003C4944415408D76360800116173070606031060310C31948
              3B8318EEE5E5C5280C13905A67886267B062F3F262F7F2626406420DA639302B
              6096C2000092D91B3F80E77CC50000000049454E44AE426082}
          end>
      end
      item
        Name = '0\028'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              3AEC0D8D05000000704944415408D74D8DBD09C33014844F6DE0815EA1C66B08
              0F22825648A79D5CB9D32E56E3E2C1ED92336972D5C7713F20E7204F8293C98D
              02AED29D8111E55DFB46CCABD4BAE781585D4E532675A9D93F14811B3E3F7881
              70ED6453DDA5ACD69104782E901C1688FB02F0BCCB82717E01DDAB335C9ECBEF
              D70000000049454E44AE426082}
          end>
      end
      item
        Name = '0\029'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              2F81D069EE0000006A4944415408D7458E3D0A80300C855F1707A16007474F21
              1E4424BB17E89D9CDC72974E1D02EF2EA6053510F2919FF7025233791354474F
              90151868C88690D248680969969461F02AB2A074D826F844E458F71FCEAFF3EE
              E87BC5ABEB348BA61C0D5609C4E6EEE17FE80375A0341D4337AE340000000049
              454E44AE426082}
          end>
      end
      item
        Name = '0\030'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              357CB29094000000724944415408D74D8DBB090341104335E9C1C229D8D0552C
              2EE430D382B3EDC991B3E9652F7130A05E3CE7C8911E421F4831A5B7A010D054
              A0054089993062136219494CE42AE55E19B03BF706597777FEC1D34AFDD8CAF9
              41439CFE187E54EBD5C7B85F75F5726E89FC9CB573BD4BC6A6F802B748335C7C
              21DEF80000000049454E44AE426082}
          end>
      end
      item
        Name = '0\031'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              2968B3CCDB000000694944415408D74D8EBD09803010859F8D85103045261107
              11B9011C2043D9D8DD2EA64971F076F122443C78F015EFE7406A262F82EAE802
              598191866C438C98082D499C322C89489C03EEB43600CABE886CF1074787CFA3
              3DC5F3ED6913AD3918AC12086DDDCFFFD0078609341D9483B295000000004945
              4E44AE426082}
          end>
      end
      item
        Name = '0\032'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              1FA70959420000005D4944415408D75DCAB109C0300C0440B93518E2C24DD630
              19C404AD90CE6BB9D32E712BF85D220502C15F1DFF4F80746080200839C18059
              3843A96B392BEF20B91D5B279D5CEBD1EC135E24874D7F5C812D2D7AE348241F
              B02092AED303F2FD3134F887968D0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\033'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              1AD763ADCD0000004F4944415408D763B87B776DEEDDBBCBEE32DC5D0B640231
              0318B0DDBDC52008065C771942C1403017CA089585308C4305C00C6363E3401C
              0CB81A84AE50C1BB5093796F41ECE205D90E044077AC0500D2942E1D169FF70D
              0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\034'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              1547DCB05C000000504944415408D763B8CB180A0481BC0CE80C2E865C98C85A
              18E3162EC56046B031889106617081448C8D4D41DA2F82197719EE2E10054A09
              001977410CD95B0CB7AE5D140D155C0612B9CB28C87B772D00980A2DBB43BDF5
              B50000000049454E44AE426082}
          end>
      end
      item
        Name = '0\035'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              241602B0660000005A4944415408D763B87B776DEEDDBBCBEE32DC5D0B640231
              C3DDBBD718C020F716A3200830ACBD281A0A020CB7207428C305D1605330E362
              B0B1B1290A2311C680AB590BD3757721D49CBB77A126DFBA761762D75D2000BA
              632D00C3CF34ED5256FABF0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\036'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              1037B644D3000000584944415408D775CB310AC0201044D16F2B086EE1C15278
              8574B953AA74DEC52A853077C94AB00964AAC7CC2E0AD5B325BE881CAB690BE3
              EF78A2382CB1BF88082BD5B2BF77F364A133387C9008461A8CBB03D76C0449ED
              01F24329273E32E4540000000049454E44AE426082}
          end>
      end
      item
        Name = '0\037'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              0BBDD38D3F000000574944415408D7558EC109C0300C03E511F2E868FE7781EC
              94577FDE25AF3C0CDAA522690215181FC6480219957C088650037260AA26AC48
              886EE5727724E676F40356FC0FF7B9EC9FD8C0F6F9286539E7E0CAA2A41EF102
              AC2F30E0681FA2B50000000049454E44AE426082}
          end>
      end
      item
        Name = '0\038'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              06C362F182000000594944415408D75DCAB109C0301043D17FADC1E02B32588A
              5B219DD74AE75D5C1BB44B8E4020B8D24312D2E8D22D340455094D408BBE30A7
              8831CDDDE9AC99E92D3FF811DE2AB22322FC87CB32E32CD9BCA88C0FDA5058FB
              F40032FA2CA08A55E00D0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\039'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1027
              015D0664210000004F4944415408D763B87B776DEEDDBBCBEE32DC5D0B640231
              0318B0DDBDC52008020C5C7719428100C8CA053342050578610C060823501027
              03AE06A60B68CE5DA8C9BCB72076F1826C0702A03BD60200CB0B2A104B647481
              0000000049454E44AE426082}
          end>
      end
      item
        Name = '0\040'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              25781EB1B10000006D4944415408D72D8B310AC3400C04E5265D202EAECC2B0E
              3FC484FB423AFDC9953B3DC68D0AC1FCC57B2402C130CC1A84C3891142BD4106
              4999D73485054A703709B266E3F2EA1443E56F750AB16FB2AC0FCDE16A638D39
              6F9F3EDE6A8ED6FBF6125C43662FAB65E8F6A7F1871B2F6651254608DAC40000
              000049454E44AE426082}
          end>
      end
      item
        Name = '0\041'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              155EC7811D0000006A4944415408D7258DC109C4300C04F53E08E43EF7731526
              85984365B82DFFDC8E1E82E925ABE42110CBECACC19EB030B65E9D19B109D2BE
              672589F968C09CE63E8814E3FFF1419C79BF5A4625FDFA413E4F932F8B39B6AC
              D59297C7134B7D9997D4624C3BEF7A0D28BB01B0F6506B50E84DFA0000000049
              454E44AE426082}
          end>
      end
      item
        Name = '0\042'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              200874453E0000006C4944415408D7458CB10D85400C43CD0048505CC9142706
              41E856A0CB5AD76597CF2F5244F22EF868701AFBC90E3835E998F199BB9DB51D
              09FB955AF785701691CD90BC4B5B49D07C5AE77050CA1884D165894B899D29F2
              A7EB34371F3D28448F1C65755D1D4D7384F78F893D576F51826F3CA5CC000000
              0049454E44AE426082}
          end>
      end
      item
        Name = '0\043'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              1ACE789C8C000000674944415408D73D8DB10D80400C03CD081499043109FA15
              E87E27AA74D9052852BCE45D70BE205224CBB12F20A3934E3024B520339804FA
              2867591154E4B106194C6B0DEC316EDB2534CFB195489FE2CCDF79795546F5E0
              6C4585AC4E2EB4C82329A66372F4243E9E7E52687D0324610000000049454E44
              AE426082}
          end>
      end
      item
        Name = '0\044'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              338CCA04E00000006C4944415408D7158C310AC4400C03B5CD1507816C91875D
              912FA4F39FAEDACE7F09295C2CCC5FA295C148626CD14EEBB78976D8741BF5E3
              ECFB5771776B4779371B85266A5D1B22FE922A05481F2FA80106AE7237986E1E
              D2A32492053AD4A8B960B36966964F1CD61FC2DD0BCA7B486D1A26823C000000
              0049454E44AE426082}
          end>
      end
      item
        Name = '0\045'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              2AE8A1AC200000005E4944415408D73D8DBB09C0300C442F23B8C86859219D77
              4AE54EBB98142A0C6F974832A4103C4EF711588781B0C038811B3EA5BE4279D4
              648445ED5408CCA35DA2DB5201F549F05170FBAFBC9427E2B653B64DCA41B279
              392BA97A62C43E63B649D90EF9E3210000000049454E44AE426082}
          end>
      end
      item
        Name = '0\046'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              381B18DD68000000684944415408D7258BB109C0301003E53660F017192CC5AF
              90EE774A95CEBBB8FAE241BB44268590384E2067902FC1A9A980CCC964216A93
              2226A5300202CCDA4E88CB934C56FE2FA04BBE7301D05DB019BAEEAB9919E43C
              6A1B1AB0D36D1CA876BABB75B0A9FDEA1FC0FF487B98EB1DD60000000049454E
              44AE426082}
          end>
      end
      item
        Name = '0\047'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252525252FF52FF5252FF
              FFA50000A500A5A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFF3F506A91000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              2F98CB58AF0000005F4944415408D72D8DB10DC02010035DA5430AA3A5600CD6
              A2FB75BE78C9BBE420291096DF67CB8E692FCB81E4492DC3E95257C329EBE9B2
              3DA746BF5B161904568606B7CAED9C50FD6281EF4CD07A28F8D3930B9EE68B31
              32FCF5ADEF01BC17800C48804C0F463C0000000049454E44AE426082}
          end>
      end
      item
        Name = '1\048'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              33207F4BEC0000004C4944415408D72D8DC10900410C022D2E205C3DFB4A4342
              AA5CB3E7D3C151A8288E88533D3DA7403A4B850A32714923777E844842247736
              1AE34563ECC66E6182B01BBB85277DFE8A4444EA0BBDFE3B877B5A671F000000
              0049454E44AE426082}
          end>
      end
      item
        Name = '1\049'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              11EC043B49000000654944415408D71D8EB10DC4300C03B993ABF40284ECE3E6
              B586D3300B10D6944FA7D4E1A02314A96C25665457CF40A66F291033C8B7A7C9
              4DB265876B18216E8E8B14E267B06867AF8BC3A4F63A52439B476A741DF01474
              1023E1923FBBE5F037000E7F03FE50243E77AB8132C40000000049454E44AE42
              6082}
          end>
      end
      item
        Name = '1\050'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              1D7B315AEC0000006A4944415408D71D8E310EC0200C03FD27A6EE91A27E8417
              B09417B0D3C5FD40445E59C3969C2C9F11E6E1198E663D7B3683BBFE08833523
              BF6C2237C90C65388B10C6CD729103F51198ACA86B5E2C3AC69A3B34108B3B94
              C8BEC1DB111BD11C32A9592E89CF00487C06FC58EB3E7A575974370000000049
              454E44AE426082}
          end>
      end
      item
        Name = '1\051'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              179BE4B3F2000000694944415408D71D8EB111C0300803B593ABF4DC7159C413
              B8F204F44EA32CC0852923BB1342F0429AA7573A86CD9A350CEE9A330D368C7C
              6BC8B949562AC3D5642182ED62047A97B17ADFE2629388580A69951F77A85073
              5F3D13B92D9A43247D164BE05300029F023F299B3DBAE663B62B000000004945
              4E44AE426082}
          end>
      end
      item
        Name = '1\052'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              11728716C7000000694944415408D71D8EBB11C0300843B513957BEEB82CE209
              5C7902F749A32CC0852923BBE184F83C213D322A03C367CD1A8E08F5990E1F4E
              BE35E45C242BB5C3DB6461AD654D05BD77A3CA16ED08B9BCF7283FD21A0B35F7
              D53391DBA20744D267B1043E0120F009F00314B93D8EE7FE4277000000004945
              4E44AE426082}
          end>
      end
      item
        Name = '1\053'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              01F1B32B2D000000624944415408D7458EBB0D80400C43BDD355F49122166182
              5437013D346681884C89EF84C055E27C9E91E6E9958EB05EBDC2E0AE3ED36061
              E45521672559A91D1E4D16F657D85EFDC537CA9B6C0B0BD5C7D5D991C3A23944
              D267B1049E0120F00CF00043E73E10166D995E0000000049454E44AE426082}
          end>
      end
      item
        Name = '1\054'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              0C11817A1E0000006A4944415408D715CDC109C0300C4351ED9453EF06D34D32
              402EF5005920BDA80B9878CA2A37F1107CA4F9EC958E61A1310CEE5E9969B061
              E457437293ACD487AB896037DB4526EC112CEAB3D7C52689BDCEA9909BE754A8
              38F006F210CD11227E6A293CBBABAEF0ECE21F35633E7A79FF959D0000000049
              454E44AE426082}
          end>
      end
      item
        Name = '1\055'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              06F15493000000006C4944415408D715CDB10905310C8361ED94EA7A83B94D32
              409AE701B2405EA32C60E2294FE9C487E0479ACF5EE918161AC3E02EC934D8B0
              D9770DC94BB2521FAEC65DB097ED2113F6132CEA73D6C32689B3EEA99087F754
              A8B8F00F649ED9698E28B5B65A0ACFEEAAD76D893FDA583D4BE143E917000000
              0049454E44AE426082}
          end>
      end
      item
        Name = '1\056'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              02F63957190000006C4944415408D7158DB10D04310CC3B453AAF4028CDB2403
              A4790F9005F28DB380114F79BA8E202410495BA3D230E9824998C964129C5CE3
              D49479D6884A6D42700A7CA2F588047FBBC50E6DEEEED164FCEE902BE4D5B80B
              CABFD7DF9179053478A975D452780D53BDBE96F40BDA2E3D79ACFA1CC5000000
              0049454E44AE426082}
          end>
      end
      item
        Name = '1\057'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              38B7AD9264000000694944415408D7258DB10904310C04B7A78B3E1788EB4405
              387915A006EE13BB81C5AAF2D75C360C03039A57341DC352300CEE32A4C18655
              AC1E3277C56CAA9982D5B0FBC024ECFB543C53CD165C32F942835BCD47D079E2
              5F82DC027364EBB5F4D2B8C275EFF392FE0309A73DFB6D37F09D000000004945
              4E44AE426082}
          end>
      end
      item
        Name = '1\058'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              066FD7BE8E000000624944415408D745CD410600310C85E137DBEEC2507A9B21
              E43C25849CA6B30A39E544A9D9C547DE8F6009C91028BB992B43C488BA31D81E
              220A45C15AEF30E81CAD3572484151AFA3A05DFD173B1247F27CC5DEB90D1EB3
              962B91B15B8254AE7AFA070AAF2B4DB8AAD64B0000000049454E44AE426082}
          end>
      end
      item
        Name = '1\059'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102B
              0B1166C233000000614944415408D745CD310AC0300885E13775C8B9A45EA418
              C82C113C4DA60A9EB21208DDE403DF8F200ECE6028B9992B81D944BA11C86E11
              0945C15AEF30E81CAD3571704151AFA3A05DFD173B1247F27CC5DE790C1EB396
              2B91B15B8C54AA7AFA07A67A35434697072D0000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_0000'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_0001'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_0010'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_0011'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_0100'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_0101'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_0110'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_0111'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_1000'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_1001'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_1010'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_1011'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_1100'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_1101'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_1110'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\060_1111'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              2E43792735000000344944415408D763D80D011B183629818102C32655251004
              32A2994010C85050024314354A30354A4A50354A186A089B0363C00000E57D1D
              42A3E921240000000049454E44AE426082}
          end>
      end
      item
        Name = '1\061'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              102EAD7592000000714944415408D7358D310A03310C04C770E7FA84210F705E
              70F107EE40EA5318D769A4FF3F218290A9862D767035B77063EA2A52A76276B7
              21AEE86CAF3E1E13BB5AEFCFC399F7C8E50CB48CE4DCFFB261A5A5C8CEFA49C5
              91FC392AF196E458F8A7A460ACA0089B127E01598F0C53637D013E3617C39876
              94E70000000049454E44AE426082}
          end>
      end
      item
        Name = '1\062'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              0AD3CF8CE8000000664944415408D7458EB10D80300C041F09A8899018002600
              2F40E1EF29ACD469ECFD4720448AA87C92DF7F862B9DE184698E1CA620094CAE
              50C390D26CE03DA45592C350A7C886BBC1B1A06E44AEFDFCE1E9507A26FA9597
              D643E4F89A47C527AE2EA28ADB032F1C881878787896EB0000000049454E44AE
              426082}
          end>
      end
      item
        Name = '1\063'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1026
              043477A1EF000000714944415408D7358DC10903310C04C790F3DBC2A9C0A9E0
              A2062E201510307EE723F55F420C21AF19E6B14B98876738D316D469B85F4018
              3629B2137E15112198D7A6B4C490AED20EAC7455951BFE93835536F5ACC45FF2
              ADCFA1E7223E7D8C477356F65DEE46C66BEFECF79C56A4E6FA028B2317C35863
              B1C50000000049454E44AE426082}
          end>
      end
      item
        Name = '1\064'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              37A08A933A000000684944415408D74D8EC109C430100315C8F91DE30E721524
              DB4002AB02028BDF778FDDFE4B881D30E4370F4923B8D2194E98D6A8610A92C0
              C7156A53CE48069E451A39AC88485E128EF2ED009CFB2AB2E5175C037E2313A3
              E5FF6787A8D1976745173717D1C4CF811B268918785A7436620000000049454E
              44AE426082}
          end>
      end
      item
        Name = '1\065'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              32D0E067B50000005F4944415408D75DCAD109C0201003D008EA7745E8007602
              EB0215EE3638DCE0DC7F846A4BFD68BE1E49A0C4CA5D1942CD042F04E61A4B50
              02493C53D9057C4D6C0AA925A523779079E026C6942DF885433365247BE887FE
              6BD6C77E935B9F1B641F1847398461380000000049454E44AE426082}
          end>
      end
      item
        Name = '1\066'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              2D5DE86A400000004D4944415408D7634875714D754D4B75650871094B0B4B0B
              71610003D65417064130600B61300603C15428C3580CC250321600339494940C
              7130E06A10BA8C055DA126B3C0ED7265005A0C7600000EFD17DBE3C4A3D30000
              000049454E44AE426082}
          end>
      end
      item
        Name = '1\067'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              27BD3D835E000000584944415408D763486534060243568610088385C115C670
              411381AB618349B1A2A8315202898441186C0C4093959494818CB44030238C21
              3541182825E0CA1096066288B830A4A53A0A1B0BA6BA32A485B8300AB2A58501
              001CAA174713C9D82D0000000049454E44AE426082}
          end>
      end
      item
        Name = '1\068'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1025
              22CD5777D1000000574944415408D7634875714D754D4B75650871094B0B4B0B
              71617075756500039710464110607075143606018610086DCCE0206CA40C6638
              1A292929A33002618C04989A3498AED444A8396169509341168301D062B00300
              825519FDB1EA358D0000000049454E44AE426082}
          end>
      end
      item
        Name = '1\069'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1024
              37B991A27B000000584944415408D75DCA310AC0201044D12FA8B58B27095E20
              85F629C43ACDEEFD8F10410C21533D66067565E608F4054FDBA8BFE6FDC43D85
              EF274F48602C4414C94552C42E994903BDDD048D6138C1574C4F401BD62B441B
              0FC32714A7CF338B870000000049454E44AE426082}
          end>
      end
      item
        Name = '1\070'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1024
              32C9FB56F4000000544944415408D7558EB10DC0300804DF23581985055CF07D
              0AE4DA0DEC3F421C6422E51AAE78FD03573AC309D319334C4112891A5ADF80A3
              F54B4460C82B189FB42E7FB94B5665A2C4D7E999719ADFE1640FE7030FDD1C17
              99B6CF67ED0000000049454E44AE426082}
          end>
      end
      item
        Name = '1\071'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1024
              2D44F35B010000005A4944415408D75D8AC109C0300CC46468FAAEC924C50BE4
              616F10BA81B3FF080D94E4D19784EE488F8C9141F707CEEE4434201DEF88CE44
              34515592DE26F51A385A4DAF824B35333D884F0A8F4CDA7D924BC6AFECCFB1A6
              B23F2F5DA415A7E95C9A810000000049454E44AE426082}
          end>
      end
      item
        Name = '1\072'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF52A5A5A5FFFF52FFFF
              FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF94984257000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1024
              214D45172A0000004D4944415408D7634875714D754D4B75650871094B0B4B0B
              71610003D6541706411060600B61300602202B15CC30161460833118200C4341
              9C0CB81A982EA039AE509359E076B932002D063B0000739C157742CB1D2A0000
              000049454E44AE426082}
          end>
      end
      item
        Name = '1\073'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1024
              1C152D5B3B000000664944415408D7358BC10985400C444710044FCAFE0AD60A
              745B08A4214FA9E67B1A48958EB8E694F778039AD3938ED322234F83BB983458
              57328A9854F32AF411D1476A1E948670584735E455DAEA898C72D4F60BF05F6A
              DD16475C4D6637E4D074FBF43DF30DC0C331913B3D78210000000049454E44AE
              426082}
          end>
      end
      item
        Name = '1\074'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1024
              1782FF82B3000000694944415408D7258E310A424110435308B65F10044B3DC1
              BA571808789EADF6428139A5C9B7CB84E44DA0A2D82256EDDEBD0AA06FA9703B
              FE16E63828B530E7382DCCCFB8BA64E7F57EBAB4221E6145DCC34AE642B3D272
              A27638228B261BFBCD2F3332007D267AFF00BB8F2EE36EF2C381000000004945
              4E44AE426082}
          end>
      end
      item
        Name = '1\075'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1024
              116B9C2786000000684944415408D72D8B410A8030100323085E95DE3CD617D4
              BE405808F81A853DF5430BFB4A97DA9C9221039B6AA42CD0BFCCE055CF5C8B40
              9E94F3B12AC8146437A8BCA96ECD21B4695B6890E6CD55E2E3460B8C3E03C32C
              36E9F08182C4894274E956C1908821B50F0BBF2ED0EBF1E6040000000049454E
              44AE426082}
          end>
      end
      item
        Name = '1\076'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1024
              0C089A4B5F000000664944415408D7258EC10980400C04D712241D6807A60185
              40C06E847B5D35DE2B902ADD9CBFCD329904611E9EE168D6B36733B8738E006C
              56CBCA86D01025C34A54514BAFEC0C24C6B129CA3143399E0A74D859CCD4D656
              04A14B8A6175D3CCB91E00B2FDD73EF5EF3191B0A5284D0000000049454E44AE
              426082}
          end>
      end
      item
        Name = '1\077'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1024
              079F4892D7000000684944415408D72D8CB10903410C04E7E0C0E0E8C55762BE
              01070281AB71A0E8AAF94CA02ABD86DB6835CC8A1A97F27A90E354B14960E765
              C7C4BFA61C49BC870A453AC378361E371085AF86E972BAA25C64757AFE7195EE
              88A6371291141E72843EFAB647C11EAD1F3B3A2A05A7E6D5FE0000000049454E
              44AE426082}
          end>
      end
      item
        Name = '1\078'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1024
              02EF2266580000005E4944415408D7254EB90D003108F38D10DD2859200512EB
              A4A0CA34D75962CA33A4B38D1F40737AD21176F26418DCC5F90156D2C6902213
              C62B4FD87EC64485D040215D26BAA34077142069EDA9DA5580BC26F4D252B3B8
              1ED05646AF9D1F88C02C668B823CA40000000049454E44AE426082}
          end>
      end
      item
        Name = '1\079'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1023
              39116819BB000000644944415408D72D8BC109C0300C03152804FAAAC924C52B
              18BC4E1E7D659AFE049EB282E6634967098C6416134FAC5AF5043295C9406C24
              A2128BEAFC087B44EC913A7AE3105935015D9068865EA8D9CC0C0B7CA576A5AC
              0DB7EB40B5E1EED665A47E9F1FF5D12CD59AB3D2C00000000049454E44AE4260
              82}
          end>
      end
      item
        Name = '1\080'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A5A55252FF52FF5252FFFFA50000A5A5
              A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4EDB5918000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1023
              346FD965060000005E4944415408D7258EC109C0300C03F50814FA6A46295DC1
              20E83C79652181A7ACADFE64D93A0B0A8A2962C5CE9D2B80A3662930316CE19E
              A094C2332F5B2D50A1726A57A165D12C8B66F986A4C588B29A233258E433D7FB
              FF720133BAC007BDB02ABC890593A70000000049454E44AE426082}
          end>
      end
      item
        Name = '2\081'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              28AA1A8200000000334944415408D7758CB111004008C21C9FC2D132D48B96BE
              56910B84EA92241238401A2BFCC1016375E2EC03DE686776ABB5E001FD1D55E9
              7C635A2E0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\082'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              21D3C63AA40000004E4944415408D7658DB109C0300C043D9C2A4FF6048DE1EA
              F024414345B21A43541DCFE97F28CFC3637844FC007682F4002761193BE1C526
              1464B01A26860A4A3A4E49D757F7482307BAB9972EF800F09251BDB119A7FD00
              00000049454E44AE426082}
          end>
      end
      item
        Name = '2\083'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1023
              2E92BB9C7C000000584944415408D7658DBB0DC0200C44BD022B300B153D3B59
              91C7A07A6212CB43C5840629573D9DEE239AB2B0108B881FC04A507D80CF6136
              5648755A872AC3D3988C0D9D96507CEE50117376E86A9D1D55C983B37C9E2E78
              01002D4E5BF799B9930000000049454E44AE426082}
          end>
      end
      item
        Name = '2\084'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1023
              287BD83949000000584944415408D7658DBB0DC03008445981159885CA3D3B21
              8B31A84E9E2462A8E0B8B194AB9E4EF7216F45455154D50F80D5E03E017C0E52
              B18A44A0032264D6469A6D18D006E6EC1033C5831DBA5A67C79DFAE02C9FA70B
              5EDA6A4A45CF8D96F30000000049454E44AE426082}
          end>
      end
      item
        Name = '2\085'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1023
              229B0DD057000000574944415408D7658DC109003108046DC116ACC5977F7B92
              C332F25A52C9615167924FE07C0CC382BB147D59599455F51360B6443C007682
              A1984522A2D62077573496D81666C66850BE801AAEAFD313413D709ACFD2251F
              11A34793DD22292E0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\086'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              1082183A9E0000004E4944415408D763E800829E333D67187ACE9C3983C158B5
              6A0D90D1D1D1B56AD52AB0C8AA252EABD69C61508202865028403004A180A1E7
              D4AA552E5EAB907441CCE9E860005A00311962131203008CDD458F728027A100
              00000049454E44AE426082}
          end>
      end
      item
        Name = '2\087'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1023
              1C5A6CCDFC000000544944415408D74DCDB10DC0300844512F934DA8DC65AB53
              E4315C7D799288A102468952F1840EAE493A4E1FDE86FB8718055801E902F686
              69ACC08D7548C462163A861219DA990CFDAEEA8FD4A2A03E07AAF4C50316AA4E
              79E8EF09EA0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\088'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1023
              1124DDB141000000514944415408D76DCCB10D00210C034096619354746C65BD
              320695C5242F0FF5496828BE3B59B61B803EE56A2EFD6107808764255CC61D78
              69834C44B00E068D4864A93A59BA56F1D3278126F9792EE8C2071A7D4AFD3963
              57270000000049454E44AE426082}
          end>
      end
      item
        Name = '2\089'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1023
              16BAB924E2000000514944415408D76DCCB10D00210C03C02CC326A9E8D8CA7A
              310695C5242F0FF5216928BE3B59B60D401B9AB229FD610780A70D66C2C00EBC
              F44E1E2CE72A743A71C0C8B2D346E7B5AA1FC0A459CF095DF8006C7048C3ED7C
              8DCA0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\090'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              0676CC8FCF0000004D4944415408D76DCCBB0900310C03502FE34DAE4AE7ADC4
              E13152994C7268A8737E9022DD434812006A748A9337B404F0AAC54822D1125F
              477454B5BAF1043656A7C4B19A3F80903E9F0778E007EDF746DDD0F194A10000
              000049454E44AE426082}
          end>
      end
      item
        Name = '2\091'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              1B15CAE316000000534944415408D7658DA10DC0300C045362FEA40AF070E928
              65065E2AFC87EAA7565450A3D349FE6BA14B265B92DC00F80B13802002635C2E
              334F338340622981841DBE4DFF19FFBE6AA74723EF5A56B25AD54E3EDD8B32EB
              5DCD62560000000049454E44AE426082}
          end>
      end
      item
        Name = '2\092'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              0C961966D1000000504944415408D7658D210EC0300C03CB46F25F17842F208F
              2A0BF1A3E635AA0616743A29BE11BA647224C903806F28008208AC552E536E66
              1048BC4A2061971F337FC6BFAFDE9931C8BB9795EC56B7930F280B471F50DE8A
              BC0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\093_0000'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F102A
              01E8A81A6C0000003C4944415408D76350AB3AA404C20C29E26B944098C151A9
              EA1808330829A9A780300350852308334054A488334054382A31A8AF01AA0062
              062A990300E76529B5008FAA5B0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\093_0001'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              2F1F534460000000654944415408D72DCCB10D80300C44D103210A4495262DBA
              2299C32B78064FE19932458ACC45202EBE74C5E9A178D7D33B61B9E9911B2174
              DDE80389557756436799A3081A4D6F5A860FD16B08515B7A66C47458C2A18533
              241C4BE1480FE77F613D96C3AF17F2AF2769F800618B0000000049454E44AE42
              6082}
          end>
      end
      item
        Name = '2\093_0010'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              389C80C1A7000000474944415408D76350AB3AA404C20C29E26B944098C151A9
              EA1808330829A9A780300350852308334054A48833805484020183FA1A215D25
              2060009B0102249B03C220739440180047B7276EEFE615510000000049454E44
              AE426082}
          end>
      end
      item
        Name = '2\093_0011'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              330B52182F0000006B4944415408D72DCCB10DC520100350274A7E958A863672
              0173DC0A27B1C14D71333105050364A2403E962CB9B01E9237FD79232C563D62
              2584AE1BBD2330EBCE6C684C632441A5E9458BF02E7A9652906B783882E1DC98
              190E6D395D96636139D296F3BDF07F08A7C3D9178F5425E7848062D300000000
              49454E44AE426082}
          end>
      end
      item
        Name = '2\093_0100'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              25FF86AD7E0000005D4944415408D76350AB3AA404C20C29E26B944098C151A9
              EA1808330829A9A780300350852308334054A488334054382A31A8AF11D20562
              2506A019416C50738258A0E6043142CD0962829A036440CC09E2819A13C40535
              27881D680E009BE72786D7A8B6920000000049454E44AE426082}
          end>
      end
      item
        Name = '2\093_0101'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              1F398A74CC000000554944415408D7A5CCB10D80300C04C007219010559AF45F
              247378859FC15378264F91220330113003DD558716437B0CC26B6AAB4918430B
              63A2B06B65770CB617CD90745DF48A98A6731AD1B3DC4716E2FFA3EF7900CFEC
              25C11F472A510000000049454E44AE426082}
          end>
      end
      item
        Name = '2\093_0110'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              2A6F39B0EF000000634944415408D76350AB3AA404C20C29E26B944098C151A9
              EA1808330829A9A780300350852308334054A488330055E886020183FA1AA14B
              4A40C0003423880104802A8258A0E6043142CD0962829A036440CC09E2819A13
              C405B40D644E10FB1A212500369D2604AECFF4410000000049454E44AE426082}
          end>
      end
      item
        Name = '2\093_0111'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              1B3EE7B0D50000005E4944415408D795CCBB0D80300C45D107E22321AA34E95F
              91CCE1152C65034FE1993C458A0CC0449011B8D5AD0E8A773DBC139643B71C84
              D075A10F24565D590D9DE59B22089ADEB40C1FA27B6B0D35D2C32F4C07B3DFCE
              3584D3D133125F496F23CF03637CA10000000049454E44AE426082}
          end>
      end
      item
        Name = '2\093_1000'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              11DE3259CB0000004A4944415408D76350AB3AA404C20C29E26B944098C151A9
              EA1808330829A9A780300350852308334054A488338486860681543128292929
              A8AF115262000226D2CD81A8009A03320384013A0C27601D608E3C0000000049
              454E44AE426082}
          end>
      end
      item
        Name = '2\093_1001'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              0CBD343512000000674944415408D72DCCB109C030100340258404422A37EE55
              D873FC0A0FDEE0A7F04C9EC285E78A9DBC40A0421C52ED7AD64E586C7AC44608
              AB6EAC038159776643679A23091A4D1F5A442945EF210467AE168895E40ECD9D
              21EE587047BA3BDF0BFF633A791AAB2F2C6224C65A8355C60000000049454E44
              AE426082}
          end>
      end
      item
        Name = '2\093_1010'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              164056CC68000000474944415408D76350AB3AA404C20C29E26B944098C151A9
              EA1808330829A9A780300350852308334054A48833848686C602712883121430
              C00149E64054382A31A8AF01AA0062009AC42519AAA474260000000049454E44
              AE426082}
          end>
      end
      item
        Name = '2\093_1011'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              072AE6EC9A000000644944415408D73D8CB10D803010030D022AAA34E95D2473
              FC0A2F65839F2233658A14998B17BCB064CBC5E950FAD4AB4FC2F2D0230F42D8
              75635F48ACBAB31A268B9F221834BD6919AD353D7DC008FEB887169E25E1B114
              1E99E179297C84107538E17D009D7622B4EDF9D21D0000000049454E44AE4260
              82}
          end>
      end
      item
        Name = '2\093_1100'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1029
              01C38549AF000000614944415408D72DCC310A80300C85E1A788823875E99EC1
              9EA357086474EB297AA69EC2C173994713F821C3E3C3DD5F616879084395FE31
              24298DC11795612E5A86993D5C41FC8E91047EBA87A35B38BA84A36B38FE4C47
              2F3A6EE849A78CA4747EEE7C253367C7B7D50000000049454E44AE426082}
          end>
      end
      item
        Name = '2\093_1101'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1028
              32654E19F80000005B4944415408D79DCCB10D80300C44D103219050AA34E9AF
              48E6F00A96B281A7F04C9E2245E622880DF8D5AF1EAA0F3D7D1056428F1284D0
              75A34F6436DDD90C83754D15044D13ADA0F7AEF71482AB2B32B1FAE1F894CF69
              91F5751EE68E22AEE8308C8B0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\093_1110'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1028
              38859BF0E6000000614944415408D72D8DB109C0300C043F211008A9DCB85711
              CFE115042ADD790ACFE4295264AEE8B11E4EA878EEF18C57087A9E4250657C04
              494A27F04625588D9E6166CD3148041EE5A1478FF0E8161EDDC3E3CFF2E84D8F
              2FE9E56B2833E93993FC5D5F23214CB9C4A40000000049454E44AE426082}
          end>
      end
      item
        Name = '2\093_1111'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1028
              2C9F41249B0000005D4944415408D7958CBB0DC02014C42E513E52948A86FE0A
              9883154E6203A67833BD2928982B44CA027161B93292751DD689165D5B74A2D0
              B4D00602B356E686CE342315389B6EB6885AABF629F00313BDFAF7B151748D42
              640F3A3DF001601120BCBA7C13FF0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\109'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1023
              0937B12917000000624944415408D74DCD310E80300C03406763E8D04819F945
              F940451EC6D8218FA27B1E85A98484A793071B83898C44648A968569AE0B7636
              DF13E3B2D68ECA663A9B4E8833BDFC61846E1FD840B953895B99FAEE0881814C
              88A22471013C2202E0FB0335E72AED2C2459430000000049454E44AE426082}
          end>
      end
      item
        Name = '2\110'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              3BE67D49D6000000544944415408D763E800829E333D67187ACE9C3903633030
              F080190C8C82823C67183A1A1805455C0481220C40DAC54586A101CC30116000
              CAB8B8381B3B6263C0D4C07541CDE960380333196825C42E88DD3D6700F41E2B
              E8F875CBF20000000049454E44AE426082}
          end>
      end
      item
        Name = '2\111'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1023
              04490055AA000000644944415408D74DCD310E80300C03407763E8504B1DF945
              F900220F83AD431E55F63C0A970191C5270F0EBACEC3031E01E41703C00B2422
              07FA994842CD50B2086035960C4FD5CCF8611194B6E71F6E3B9AED73A7B6B695
              8E88AA660DE1D28E4F78A2BE3F3D142AED0529F23F0000000049454E44AE4260
              82}
          end>
      end
      item
        Name = '2\112'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              3698CC356B000000534944415408D76D8DB10D80400C034D9F8248D904164064
              30BE4B91D13C1481E7BFC2D5C94A7C884A3289243900901716550811CDBCA81A
              73775D0597ED0F00EDDCDC0FFD837933BFBE9D00C77229BBABBB9337020E2BE8
              33BF14EA0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\113'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              01207190640000004F4944415408D763E800829E333D67187ACE9C6114E40133
              0E8AB808821922CEC62E3267183A1A400C01A0C8411763631347208311CCE001
              318052080607880104101134460784C1C170062682C10000433C28BF6CCFE0E7
              0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\114'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1021
              36B3E166A8000000444944415408D763E800829E333D67187ACE9C3903668001
              0F902108063C67185CC04010C6709181308C5D04C00C636363471C0CB81A842E
              17C10E84C970BB2076F79C0100B9E7275FA7ECB8B40000000049454E44AE4260
              82}
          end>
      end
      item
        Name = '2\115'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1021
              305A82C39D000000464944415408D763E860740102471E861EDC0C62D40019CE
              C62E8E1C300658C4D8D804C43808669C61E86810014A0974309C390362C89C01
              321A455C047B408C1E46419E9E33001E9F25153ACB8D880000000049454E44AE
              426082}
          end>
      end
      item
        Name = '2\116'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1021
              293EE96B5D000000494944415408D763E800829E333D67187ACE9C3903633080
              41CF1946411060E86814710101861E08EDC2D020E26C0266343A1B1B9B6067C0
              D5C075C1CD390333196825C42E88DD3D670000972BFBE8701615000000004945
              4E44AE426082}
          end>
      end
      item
        Name = '2\117'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1021
              213032E36F0000004A4944415408D78DCAA10DC0300C44D16F5660104B59A852
              060B34F0501DC043F50A0A2BF5A3A7D391B6D4E9D437FE7CCAA610C70B2DC45C
              31842BD468729B40D28D05DEC206EA418157DF90042125878536D50000000049
              454E44AE426082}
          end>
      end
      item
        Name = '2\118'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1021
              1BF63E3ADD000000454944415408D7758DB10D00310803CD08483F92074B99C2
              A379A84789A08B1BAE303EEC8A2C43B61B70521C59C15E911F4908E7126B2092
              2FE8CE7CCD8E7BB994D775DDF20F094F286504E74A990000000049454E44AE42
              6082}
          end>
      end
      item
        Name = '2\119'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1021
              13F8E5B2EF000000514944415408D76DC8B10D80300C44D19F2E458A9C948590
              3C18650A0F95013C1456103470CD7F3A66CEC3038F80B6B1800D8A68C13C8B24
              F25959F5041AA6DEF032CC4C2F6A226B47FBC1BC5189E7F9E002C1DA24CF4254
              91BD0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\120'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1021
              0C75EDBF1A000000434944415408D775CDB11100200803C00C40212379E77016
              8C96A18C726265AA2F20C154824104C98313137C07460C454A0C6F768144F72F
              EAE67EA967BEE6DACAEDE002D05723C9DAF9EB460000000049454E44AE426082}
          end>
      end
      item
        Name = '2\121'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              3071AF905E000000514944415408D763E800829E333D67187ACE9C398383D1D1
              0151C500E29D398383015105126114E4390312691471110433449C8D5D6480E6
              3488181B9B0874309C39E80214713CC37086D105081C79E00C001D12445D151D
              C3840000000049454E44AE426082}
          end>
      end
      item
        Name = '2\122'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              2BFBCA59B20000004F4944415408D735CDB115C02008045006B0D0CEC22D9205
              7861380B46BBA1A20750FD0707C83EE570880320A4307AC274322566CAA1D8A7
              2DF0BCAB70439B9D7B8B99C0D90AE80233A37BFD4A20F10359BD44887318A09D
              0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\123'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              251C7274B5000000524944415408D763E860740102471E861E38E3A08BB3B18B
              E319869E0322C6C6260267183A3A448022324091338D222E823D20460FA3200F
              8471E6CC1930A3030CC02220312C8C8E0E882A8633672062980C000354442991
              5836230000000049454E44AE426082}
          end>
      end
      item
        Name = '2\124'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              206C18803A000000514944415408D763E800829E333D67187ACE9C3983CC6080
              32180519406A3A1A455C1840F267445C208C03222610C64167631003A804C2E8
              39036734C0D4F48074816C029B03B10968328401B40BCA380300BDCF4518FE47
              B7050000000049454E44AE426082}
          end>
      end
      item
        Name = '2\125'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              1AAA1459880000004F4944415408D76DCAB10D00210C0340A7A720120BBDC460
              942932D40FE0A1DE8192779AB315844DE569481B820BF031BD0BAF2B9D886502
              8824CCD10A0BA89A4CA06DC44E2D3AF20711E70BE4D96E7C0D833C91542702E6
              0000000049454E44AE426082}
          end>
      end
      item
        Name = '2\126'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              13D3C8E12C0000004A4944415408D7558DC10D00200803EB08248EE4603E7D30
              940374282D2406795D68D3C3BAE774C249169848D830A8B3601DCA77B3118007
              D60551F93EA5330532C54E98B49CCAEB4A701E008E3E78D030FD0F0000000049
              454E44AE426082}
          end>
      end
      item
        Name = '2\127'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              0D29C7DC4F000000524944415408D775CCB109C030100340B94BE1C2822C14F8
              C15CAAF0501940434526B5BFD1E9791ECA2C2F63D93E40FAAFB09B7D80804B0A
              2600EF0D1AD183B79144FECC248742DEC5D1E17657153792F5F40FFC4C3D49C0
              496A020000000049454E44AE426082}
          end>
      end
      item
        Name = '2\128'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000010000000100403000000EDDDE2
              5200000030504C54450000000000A500A50000A5A55252FF52FF5252FFFFA500
              00A55200A5A5A5FF5252FF52FFFFFF52FFFFFFFFFFFFFFFFFF4A54AB1F000000
              097048597300000B1200000B1201D2DD7EFC0000000774494D4507E4040F1022
              07C9123551000000484944415408D73DCDC10DC0300C024006F0A31E295287EB
              83D1182A366EE2D749208CAF8EA2404906E247968C95700B6F3E0E1B185476D1
              5B466FB973104677DDB9CB080EE625B5015E803D59527F63010000000049454E
              44AE426082}
          end>
      end>
    Left = 40
    Top = 8
  end
  object VirtualImageList: TVirtualImageList
    DisabledGrayscale = False
    DisabledSuffix = '_Disabled'
    Images = <
      item
        CollectionIndex = 0
        CollectionName = '0\000'
        Disabled = False
        Name = '000'
      end
      item
        CollectionIndex = 1
        CollectionName = '0\001'
        Disabled = False
        Name = '001'
      end
      item
        CollectionIndex = 2
        CollectionName = '0\002'
        Disabled = False
        Name = '002'
      end
      item
        CollectionIndex = 3
        CollectionName = '0\003'
        Disabled = False
        Name = '003'
      end
      item
        CollectionIndex = 4
        CollectionName = '0\004'
        Disabled = False
        Name = '004'
      end
      item
        CollectionIndex = 5
        CollectionName = '0\005'
        Disabled = False
        Name = '005'
      end
      item
        CollectionIndex = 6
        CollectionName = '0\006'
        Disabled = False
        Name = '006'
      end
      item
        CollectionIndex = 7
        CollectionName = '0\007'
        Disabled = False
        Name = '007'
      end
      item
        CollectionIndex = 8
        CollectionName = '0\008'
        Disabled = False
        Name = '008'
      end
      item
        CollectionIndex = 9
        CollectionName = '0\009'
        Disabled = False
        Name = '009'
      end
      item
        CollectionIndex = 10
        CollectionName = '0\010'
        Disabled = False
        Name = '010'
      end
      item
        CollectionIndex = 11
        CollectionName = '0\011'
        Disabled = False
        Name = '011'
      end
      item
        CollectionIndex = 12
        CollectionName = '0\012_0000'
        Disabled = False
        Name = '012_0000'
      end
      item
        CollectionIndex = 13
        CollectionName = '0\012_0001'
        Disabled = False
        Name = '012_0001'
      end
      item
        CollectionIndex = 14
        CollectionName = '0\012_0010'
        Disabled = False
        Name = '012_0010'
      end
      item
        CollectionIndex = 15
        CollectionName = '0\012_0011'
        Disabled = False
        Name = '012_0011'
      end
      item
        CollectionIndex = 16
        CollectionName = '0\012_0100'
        Disabled = False
        Name = '012_0100'
      end
      item
        CollectionIndex = 17
        CollectionName = '0\012_0101'
        Disabled = False
        Name = '012_0101'
      end
      item
        CollectionIndex = 18
        CollectionName = '0\012_0110'
        Disabled = False
        Name = '012_0110'
      end
      item
        CollectionIndex = 19
        CollectionName = '0\012_0111'
        Disabled = False
        Name = '012_0111'
      end
      item
        CollectionIndex = 20
        CollectionName = '0\012_1000'
        Disabled = False
        Name = '012_1000'
      end
      item
        CollectionIndex = 21
        CollectionName = '0\012_1001'
        Disabled = False
        Name = '012_1001'
      end
      item
        CollectionIndex = 22
        CollectionName = '0\012_1010'
        Disabled = False
        Name = '012_1010'
      end
      item
        CollectionIndex = 23
        CollectionName = '0\012_1011'
        Disabled = False
        Name = '012_1011'
      end
      item
        CollectionIndex = 24
        CollectionName = '0\012_1100'
        Disabled = False
        Name = '012_1100'
      end
      item
        CollectionIndex = 25
        CollectionName = '0\012_1101'
        Disabled = False
        Name = '012_1101'
      end
      item
        CollectionIndex = 26
        CollectionName = '0\012_1110'
        Disabled = False
        Name = '012_1110'
      end
      item
        CollectionIndex = 27
        CollectionName = '0\012_1111'
        Disabled = False
        Name = '012_1111'
      end
      item
        CollectionIndex = 28
        CollectionName = '0\028'
        Disabled = False
        Name = '028'
      end
      item
        CollectionIndex = 29
        CollectionName = '0\029'
        Disabled = False
        Name = '029'
      end
      item
        CollectionIndex = 30
        CollectionName = '0\030'
        Disabled = False
        Name = '030'
      end
      item
        CollectionIndex = 31
        CollectionName = '0\031'
        Disabled = False
        Name = '031'
      end
      item
        CollectionIndex = 32
        CollectionName = '0\032'
        Disabled = False
        Name = '032'
      end
      item
        CollectionIndex = 33
        CollectionName = '0\033'
        Disabled = False
        Name = '033'
      end
      item
        CollectionIndex = 34
        CollectionName = '0\034'
        Disabled = False
        Name = '034'
      end
      item
        CollectionIndex = 35
        CollectionName = '0\035'
        Disabled = False
        Name = '035'
      end
      item
        CollectionIndex = 36
        CollectionName = '0\036'
        Disabled = False
        Name = '036'
      end
      item
        CollectionIndex = 37
        CollectionName = '0\037'
        Disabled = False
        Name = '037'
      end
      item
        CollectionIndex = 38
        CollectionName = '0\038'
        Disabled = False
        Name = '038'
      end
      item
        CollectionIndex = 39
        CollectionName = '0\039'
        Disabled = False
        Name = '039'
      end
      item
        CollectionIndex = 40
        CollectionName = '0\040'
        Disabled = False
        Name = '040'
      end
      item
        CollectionIndex = 41
        CollectionName = '0\041'
        Disabled = False
        Name = '041'
      end
      item
        CollectionIndex = 42
        CollectionName = '0\042'
        Disabled = False
        Name = '042'
      end
      item
        CollectionIndex = 43
        CollectionName = '0\043'
        Disabled = False
        Name = '043'
      end
      item
        CollectionIndex = 44
        CollectionName = '0\044'
        Disabled = False
        Name = '044'
      end
      item
        CollectionIndex = 45
        CollectionName = '0\045'
        Disabled = False
        Name = '045'
      end
      item
        CollectionIndex = 46
        CollectionName = '0\046'
        Disabled = False
        Name = '046'
      end
      item
        CollectionIndex = 47
        CollectionName = '0\047'
        Disabled = False
        Name = '047'
      end
      item
        CollectionIndex = 48
        CollectionName = '1\048'
        Disabled = False
        Name = '048'
      end
      item
        CollectionIndex = 49
        CollectionName = '1\049'
        Disabled = False
        Name = '049'
      end
      item
        CollectionIndex = 50
        CollectionName = '1\050'
        Disabled = False
        Name = '050'
      end
      item
        CollectionIndex = 51
        CollectionName = '1\051'
        Disabled = False
        Name = '051'
      end
      item
        CollectionIndex = 52
        CollectionName = '1\052'
        Disabled = False
        Name = '052'
      end
      item
        CollectionIndex = 53
        CollectionName = '1\053'
        Disabled = False
        Name = '053'
      end
      item
        CollectionIndex = 54
        CollectionName = '1\054'
        Disabled = False
        Name = '054'
      end
      item
        CollectionIndex = 55
        CollectionName = '1\055'
        Disabled = False
        Name = '055'
      end
      item
        CollectionIndex = 56
        CollectionName = '1\056'
        Disabled = False
        Name = '056'
      end
      item
        CollectionIndex = 57
        CollectionName = '1\057'
        Disabled = False
        Name = '057'
      end
      item
        CollectionIndex = 58
        CollectionName = '1\058'
        Disabled = False
        Name = '058'
      end
      item
        CollectionIndex = 59
        CollectionName = '1\059'
        Disabled = False
        Name = '059'
      end
      item
        CollectionIndex = 60
        CollectionName = '1\060_0000'
        Disabled = False
        Name = '060_0000'
      end
      item
        CollectionIndex = 61
        CollectionName = '1\060_0001'
        Disabled = False
        Name = '060_0001'
      end
      item
        CollectionIndex = 62
        CollectionName = '1\060_0010'
        Disabled = False
        Name = '060_0010'
      end
      item
        CollectionIndex = 63
        CollectionName = '1\060_0011'
        Disabled = False
        Name = '060_0011'
      end
      item
        CollectionIndex = 64
        CollectionName = '1\060_0100'
        Disabled = False
        Name = '060_0100'
      end
      item
        CollectionIndex = 65
        CollectionName = '1\060_0101'
        Disabled = False
        Name = '060_0101'
      end
      item
        CollectionIndex = 66
        CollectionName = '1\060_0110'
        Disabled = False
        Name = '060_0110'
      end
      item
        CollectionIndex = 67
        CollectionName = '1\060_0111'
        Disabled = False
        Name = '060_0111'
      end
      item
        CollectionIndex = 68
        CollectionName = '1\060_1000'
        Disabled = False
        Name = '060_1000'
      end
      item
        CollectionIndex = 69
        CollectionName = '1\060_1001'
        Disabled = False
        Name = '060_1001'
      end
      item
        CollectionIndex = 70
        CollectionName = '1\060_1010'
        Disabled = False
        Name = '060_1010'
      end
      item
        CollectionIndex = 71
        CollectionName = '1\060_1011'
        Disabled = False
        Name = '060_1011'
      end
      item
        CollectionIndex = 72
        CollectionName = '1\060_1100'
        Disabled = False
        Name = '060_1100'
      end
      item
        CollectionIndex = 73
        CollectionName = '1\060_1101'
        Disabled = False
        Name = '060_1101'
      end
      item
        CollectionIndex = 74
        CollectionName = '1\060_1110'
        Disabled = False
        Name = '060_1110'
      end
      item
        CollectionIndex = 75
        CollectionName = '1\060_1111'
        Disabled = False
        Name = '060_1111'
      end
      item
        CollectionIndex = 76
        CollectionName = '1\061'
        Disabled = False
        Name = '061'
      end
      item
        CollectionIndex = 77
        CollectionName = '1\062'
        Disabled = False
        Name = '062'
      end
      item
        CollectionIndex = 78
        CollectionName = '1\063'
        Disabled = False
        Name = '063'
      end
      item
        CollectionIndex = 79
        CollectionName = '1\064'
        Disabled = False
        Name = '064'
      end
      item
        CollectionIndex = 80
        CollectionName = '1\065'
        Disabled = False
        Name = '065'
      end
      item
        CollectionIndex = 81
        CollectionName = '1\066'
        Disabled = False
        Name = '066'
      end
      item
        CollectionIndex = 82
        CollectionName = '1\067'
        Disabled = False
        Name = '067'
      end
      item
        CollectionIndex = 83
        CollectionName = '1\068'
        Disabled = False
        Name = '068'
      end
      item
        CollectionIndex = 84
        CollectionName = '1\069'
        Disabled = False
        Name = '069'
      end
      item
        CollectionIndex = 85
        CollectionName = '1\070'
        Disabled = False
        Name = '070'
      end
      item
        CollectionIndex = 86
        CollectionName = '1\071'
        Disabled = False
        Name = '071'
      end
      item
        CollectionIndex = 87
        CollectionName = '1\072'
        Disabled = False
        Name = '072'
      end
      item
        CollectionIndex = 88
        CollectionName = '1\073'
        Disabled = False
        Name = '073'
      end
      item
        CollectionIndex = 89
        CollectionName = '1\074'
        Disabled = False
        Name = '074'
      end
      item
        CollectionIndex = 90
        CollectionName = '1\075'
        Disabled = False
        Name = '075'
      end
      item
        CollectionIndex = 91
        CollectionName = '1\076'
        Disabled = False
        Name = '076'
      end
      item
        CollectionIndex = 92
        CollectionName = '1\077'
        Disabled = False
        Name = '077'
      end
      item
        CollectionIndex = 93
        CollectionName = '1\078'
        Disabled = False
        Name = '078'
      end
      item
        CollectionIndex = 94
        CollectionName = '1\079'
        Disabled = False
        Name = '079'
      end
      item
        CollectionIndex = 95
        CollectionName = '1\080'
        Disabled = False
        Name = '080'
      end
      item
        CollectionIndex = 96
        CollectionName = '2\081'
        Disabled = False
        Name = '081'
      end
      item
        CollectionIndex = 97
        CollectionName = '2\082'
        Disabled = False
        Name = '082'
      end
      item
        CollectionIndex = 98
        CollectionName = '2\083'
        Disabled = False
        Name = '083'
      end
      item
        CollectionIndex = 99
        CollectionName = '2\084'
        Disabled = False
        Name = '084'
      end
      item
        CollectionIndex = 100
        CollectionName = '2\085'
        Disabled = False
        Name = '085'
      end
      item
        CollectionIndex = 101
        CollectionName = '2\086'
        Disabled = False
        Name = '086'
      end
      item
        CollectionIndex = 102
        CollectionName = '2\087'
        Disabled = False
        Name = '087'
      end
      item
        CollectionIndex = 103
        CollectionName = '2\088'
        Disabled = False
        Name = '088'
      end
      item
        CollectionIndex = 104
        CollectionName = '2\089'
        Disabled = False
        Name = '089'
      end
      item
        CollectionIndex = 105
        CollectionName = '2\090'
        Disabled = False
        Name = '090'
      end
      item
        CollectionIndex = 106
        CollectionName = '2\091'
        Disabled = False
        Name = '091'
      end
      item
        CollectionIndex = 107
        CollectionName = '2\092'
        Disabled = False
        Name = '092'
      end
      item
        CollectionIndex = 108
        CollectionName = '2\093_0000'
        Disabled = False
        Name = '093_0000'
      end
      item
        CollectionIndex = 109
        CollectionName = '2\093_0001'
        Disabled = False
        Name = '093_0001'
      end
      item
        CollectionIndex = 110
        CollectionName = '2\093_0010'
        Disabled = False
        Name = '093_0010'
      end
      item
        CollectionIndex = 111
        CollectionName = '2\093_0011'
        Disabled = False
        Name = '093_0011'
      end
      item
        CollectionIndex = 112
        CollectionName = '2\093_0100'
        Disabled = False
        Name = '093_0100'
      end
      item
        CollectionIndex = 113
        CollectionName = '2\093_0101'
        Disabled = False
        Name = '093_0101'
      end
      item
        CollectionIndex = 114
        CollectionName = '2\093_0110'
        Disabled = False
        Name = '093_0110'
      end
      item
        CollectionIndex = 115
        CollectionName = '2\093_0111'
        Disabled = False
        Name = '093_0111'
      end
      item
        CollectionIndex = 116
        CollectionName = '2\093_1000'
        Disabled = False
        Name = '093_1000'
      end
      item
        CollectionIndex = 117
        CollectionName = '2\093_1001'
        Disabled = False
        Name = '093_1001'
      end
      item
        CollectionIndex = 118
        CollectionName = '2\093_1010'
        Disabled = False
        Name = '093_1010'
      end
      item
        CollectionIndex = 119
        CollectionName = '2\093_1011'
        Disabled = False
        Name = '093_1011'
      end
      item
        CollectionIndex = 120
        CollectionName = '2\093_1100'
        Disabled = False
        Name = '093_1100'
      end
      item
        CollectionIndex = 121
        CollectionName = '2\093_1101'
        Disabled = False
        Name = '093_1101'
      end
      item
        CollectionIndex = 122
        CollectionName = '2\093_1110'
        Disabled = False
        Name = '093_1110'
      end
      item
        CollectionIndex = 123
        CollectionName = '2\093_1111'
        Disabled = False
        Name = '093_1111'
      end
      item
        CollectionIndex = 124
        CollectionName = '2\109'
        Disabled = False
        Name = '109'
      end
      item
        CollectionIndex = 125
        CollectionName = '2\110'
        Disabled = False
        Name = '110'
      end
      item
        CollectionIndex = 126
        CollectionName = '2\111'
        Disabled = False
        Name = '111'
      end
      item
        CollectionIndex = 127
        CollectionName = '2\112'
        Disabled = False
        Name = '112'
      end
      item
        CollectionIndex = 128
        CollectionName = '2\113'
        Disabled = False
        Name = '113'
      end
      item
        CollectionIndex = 129
        CollectionName = '2\114'
        Disabled = False
        Name = '114'
      end
      item
        CollectionIndex = 130
        CollectionName = '2\115'
        Disabled = False
        Name = '115'
      end
      item
        CollectionIndex = 131
        CollectionName = '2\116'
        Disabled = False
        Name = '116'
      end
      item
        CollectionIndex = 132
        CollectionName = '2\117'
        Disabled = False
        Name = '117'
      end
      item
        CollectionIndex = 133
        CollectionName = '2\118'
        Disabled = False
        Name = '118'
      end
      item
        CollectionIndex = 134
        CollectionName = '2\119'
        Disabled = False
        Name = '119'
      end
      item
        CollectionIndex = 135
        CollectionName = '2\120'
        Disabled = False
        Name = '120'
      end
      item
        CollectionIndex = 136
        CollectionName = '2\121'
        Disabled = False
        Name = '121'
      end
      item
        CollectionIndex = 137
        CollectionName = '2\122'
        Disabled = False
        Name = '122'
      end
      item
        CollectionIndex = 138
        CollectionName = '2\123'
        Disabled = False
        Name = '123'
      end
      item
        CollectionIndex = 139
        CollectionName = '2\124'
        Disabled = False
        Name = '124'
      end
      item
        CollectionIndex = 140
        CollectionName = '2\125'
        Disabled = False
        Name = '125'
      end
      item
        CollectionIndex = 141
        CollectionName = '2\126'
        Disabled = False
        Name = '126'
      end
      item
        CollectionIndex = 142
        CollectionName = '2\127'
        Disabled = False
        Name = '127'
      end
      item
        CollectionIndex = 143
        CollectionName = '2\128'
        Disabled = False
        Name = '128'
      end>
    ImageCollection = ImageCollection
    Left = 40
    Top = 56
  end
end
