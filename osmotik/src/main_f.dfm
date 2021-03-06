object FormMain: TFormMain
  Left = 223
  Top = 110
  ActiveControl = RichEdit
  Caption = 'Osmotik'
  ClientHeight = 541
  ClientWidth = 832
  Color = clSilver
  ParentFont = True
  KeyPreview = True
  Menu = MainMenu
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox: TPaintBox
    Left = 0
    Top = 0
    Width = 632
    Height = 522
    Align = alClient
    Color = clSilver
    ParentColor = False
    OnClick = PaintBoxClick
    OnMouseMove = PaintBoxMouseMove
    OnPaint = PaintBoxPaint
    ExplicitWidth = 640
    ExplicitHeight = 527
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 522
    Width = 832
    Height = 19
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Panels = <
      item
        Width = 542
      end
      item
        Alignment = taCenter
        Width = 50
      end
      item
        Alignment = taRightJustify
        Style = psOwnerDraw
        Width = 33
      end
      item
        Alignment = taRightJustify
        Style = psOwnerDraw
        Width = 33
      end
      item
        Alignment = taRightJustify
        Style = psOwnerDraw
        Width = 33
      end
      item
        Alignment = taRightJustify
        Style = psOwnerDraw
        Width = 33
      end
      item
        Alignment = taRightJustify
        Style = psOwnerDraw
        Width = 33
      end
      item
        Alignment = taRightJustify
        Style = psOwnerDraw
        Width = 33
      end>
    SizeGrip = False
    UseSystemFont = False
    OnDrawPanel = StatusBarDrawPanel
  end
  object PanelDroite: TPanel
    Left = 632
    Top = 0
    Width = 200
    Height = 522
    Align = alRight
    ParentColor = True
    TabOrder = 1
    object RichEdit: TRichEdit
      Left = 1
      Top = 30
      Width = 198
      Height = 491
      Hint = 'Evolution du jeu et scores'
      TabStop = False
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      Color = clSilver
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      Lines.Strings = (
        '')
      ParentFont = False
      ParentShowHint = False
      ReadOnly = True
      ShowHint = True
      TabOrder = 0
      WordWrap = False
      Zoom = 100
    end
    object PanelMilieu: TPanel
      Left = 1
      Top = 1
      Width = 198
      Height = 29
      Align = alTop
      BevelInner = bvLowered
      Color = clSilver
      TabOrder = 1
      object LabelLettresAPlacer: TLabel
        Left = 2
        Top = 2
        Width = 194
        Height = 25
        Hint = 'Lettres '#224' placer sur le plateau de jeu'
        Align = alClient
        AutoSize = False
        Color = clWhite
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Comic Sans MS'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
      end
    end
  end
  object MainMenu: TMainMenu
    Left = 8
    Top = 8
    object MenuItemPartie: TMenuItem
      Caption = '&Partie'
      object MenuItemNouvellePartie: TMenuItem
        Caption = '&Nouvelle...'
        ShortCut = 115
        OnClick = MenuItemNouvellePartieClick
      end
      object MenuItemOuvrir: TMenuItem
        Caption = '&Ouvrir...'
        ShortCut = 114
        OnClick = MenuItemOuvrirClick
      end
      object MenuItemEnregistrer: TMenuItem
        Caption = '&Enregistrer'
        ShortCut = 113
        OnClick = MenuItemEnregistrerClick
      end
      object MenuItemEnregistrerSous: TMenuItem
        Tag = 1
        Caption = 'Enregistrer &sous...'
        ShortCut = 8305
        OnClick = MenuItemEnregistrerClick
      end
      object MenuItemQuitter: TMenuItem
        Caption = '&Quitter'
        ShortCut = 32883
        OnClick = MenuItemQuitterClick
      end
    end
    object MenuItemOptions: TMenuItem
      Caption = '&Options'
      object MenuItemOptionsPolice: TMenuItem
        Caption = '&Police...'
        OnClick = MenuItemOptionsPoliceClick
      end
      object MenuItemOptionsCouleurFond: TMenuItem
        Caption = '&Couleur de fond...'
        OnClick = MenuItemOptionsCouleurFondClick
      end
    end
    object MenuItemAction: TMenuItem
      Caption = '&Action'
      object MenuItemPasserSonTour: TMenuItem
        Caption = '&Passer son tour'
        ShortCut = 16464
        OnClick = MenuItemPasserSonTourClick
      end
    end
    object MenuItemInformations: TMenuItem
      Caption = '&?'
      object MenuItemAide: TMenuItem
        Caption = '&R'#232'gle du jeu et utilisation'
        ShortCut = 112
        OnClick = MenuItemAideClick
      end
      object MenuItemAPropos: TMenuItem
        Caption = #192' &propos d'#39'Osmotik'
        ShortCut = 8304
        OnClick = MenuItemAProposClick
      end
    end
  end
  object PopupMenuPlacer: TPopupMenu
    BiDiMode = bdLeftToRight
    Images = VirtualImageList
    ParentBiDiMode = False
    Left = 40
    Top = 8
    object MenuItemPlacer10h: TMenuItem
      Tag = 6
      Caption = '10h'
      ImageIndex = 5
      OnClick = MenuItemPlacerClick
    end
    object MenuItemPlacer8h: TMenuItem
      Tag = 5
      Caption = '  8h'
      ImageIndex = 4
      OnClick = MenuItemPlacerClick
    end
    object MenuItemPlacer0h: TMenuItem
      Tag = 1
      Break = mbBreak
      Caption = '  0h'
      ImageIndex = 0
      OnClick = MenuItemPlacerClick
    end
    object MenuItemPlacer6h: TMenuItem
      Tag = 4
      Caption = '  6h'
      ImageIndex = 3
      OnClick = MenuItemPlacerClick
    end
    object MenuItemPlacer2h: TMenuItem
      Tag = 2
      Break = mbBreak
      Caption = '  2h'
      ImageIndex = 1
      OnClick = MenuItemPlacerClick
    end
    object MenuItemPlacer4h: TMenuItem
      Tag = 3
      Caption = '  4h'
      ImageIndex = 2
      OnClick = MenuItemPlacerClick
    end
  end
  object TimerAfficheMotsTrouves: TTimer
    Enabled = False
    OnTimer = TimerAfficheMotsTrouvesTimer
    Left = 104
    Top = 8
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'smt'
    Filter = 'Parties d'#39'Osmotik (*.smt)|*.smt|Tous fichiers (*.*)|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = 'Ouvrir une partie d'#39'Osmotik'
    Left = 136
    Top = 8
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'smt'
    Filter = 'Parties d'#39'Osmotik (*.smt)|*.smt|Tous fichiers (*.*)|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = 'Enregistrer la partie d'#39'Osmotik sous...'
    Left = 168
    Top = 8
  end
  object FontDialog: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    Options = [fdTrueTypeOnly, fdScalableOnly]
    Left = 200
    Top = 8
  end
  object ColorDialog: TColorDialog
    Left = 232
    Top = 8
  end
  object TimerReflexion: TTimer
    Interval = 100
    OnTimer = TimerReflexionTimer
    Left = 104
    Top = 40
  end
  object ImageCollection: TImageCollection
    Images = <
      item
        Name = 'Directions\1N'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F400000006624B474400CC00CC00CCDFC15F1A000000097048597300002E2300
              002E230178A53F760000000774494D4507E4040B072A0C001244730000026D49
              44415458C3ED96CD6AEA4014C7FF638A1D124C34D650ABE0228BAEF200EE7D0B
              573E805BE9ABF411742F087D01377755105CA8F85945D0BA4834623C5D55AE5F
              ED24B6F76EFCC3C0909939E777CECC9C098808415AAD56A3582C46B1588CAAD5
              2A05B51368D1DBDB1B65B359024000C8B22C6AB55AF44F005CD745B15824C6D8
              0E0000150A05B26DFBF701CAE532C9B2BCE71C0085C3617A7E7EA65F0568369B
              6459D691F3CF96C964A85EAFFB820841509EE7A152A98088108FC7A128CA6E8C
              738E482482E17088A7A7278CC76312B5CB8884E7C2B66D789E87D16844AFAFAF
              28140AB06D1BA55209F97C1EDD6E17B3D90CB95C0EA9548A89D8BC810FADD7EB
              9CEBBA2FD16814CBE512AEEB020086C3210CC3806118E09C9BD168B42D6AF3C6
              4FF4CD66F3E5D369A3D1C066B30100743A1D341A0D48920445515A9665B1DBDB
              5B21BBC267603C1ED3A7F3434D26935D366CDBC6743A15DED79068F4D3E974EF
              5BBFDFDFF51DC7C172B9FC1B16E76003019C8A7E3E9FEFFA8BC502EFEFEF87C0
              F42300A7A23F94EBBA984C2687D042590805897EBD5EEF39F43C0FB3D9EC1438
              5D04702EFAED760B5555619A26EEEEEE20CB320683C129F86FB3F06521EAF57A
              D4E9744E8EAD562B6CB75B2C160B388E0355559148248EE63D3E3EE2FEFE9E05
              AA03AAAA9A9224B53CCF3B1AE39C030064593EBB5E922470CECDC05BA0695A5B
              D7750495AEEBD034AD1D18803186878707539224DFCEC3E130D2E934638C5D76
              0B8266C1300CA8AA7AF9350C9205CE3992C924FBB14AE8370BA954EACBC3E91B
              C04F16144541229160A2B0C2CFB1A669ED4C2603C771BE3BF97F449F62DF7F44
              BFA110FEB3AE0057802BC0073862A8104AE9BCE10000000049454E44AE426082}
          end>
      end
      item
        Name = 'Directions\2NE'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F400000006624B474400CC00CC00CCDFC15F1A000000097048597300002E2300
              002E230178A53F760000000774494D4507E4040B072916D65DEECA000002C949
              44415458C3ED974F4822511CC7BF6F266C706804C5A80C26B62E1675AF638CD0
              A5A0904ED1C120ECDA65BD75DEABA73A0742DDEC6AA081C7F6A01DA209078A50
              2B4B105EF987FCED61B145AC716C733BAC3F78B7DFCCF7F37EFFDE7B8C88F095
              26E08BEDCB01FAFEA518E71CA55289EEEFEF0100636363AC6B00A55209A7A7A7
              747575055DD791CD66A1EB3A6E6F6F512814E0F178108D460944DD59BAAED3CC
              CC0C0178736D6C6C50BD5E47D7008808070707343030D022AE280A25120922A2
              CE001E1F1FB55C2E4766AB582C7E6BF8572A15ACAEAEB600689A469C731091F5
              22E49CE3E2E22256A9544CFD6459CE4C4F4FB342A140E17018B158ACB9EAFBFA
              10080460B7DB0100CCEA20CA6432747373D3D6AF56ABE1F2F2127B7B7B48A7D3
              20224C4C4CE0FAFA1AD56A15535353383E3EC6D0D010B33C0738E768B48E9965
              B35984C3616C6F6F23954A8188303F3F8FC3C343CCCDCD0100D6D6D65EC52DCF
              817C3E4F66A12F97CB482693884422300C0300208A22D6D7D7B1B3B303555559
              2814A2BBBB3B2C2E2E367DDB36059C739C9D9DBD0B601806F6F7F7914C2651AB
              D57E8F5741C0CACA0A7677777FB85CAE100054AB559C9C9C90A6698C31667D14
              9BEDBE5EAFE3E8E808F178BC497C696909814000CFCFCFDF1BBE369B0D3E9FAF
              49BC2D40BBDC0B82009FCF07A7D30900902409CBCBCBD8DCDC84DD6E473E9F47
              BBAE3105787878A0763F989C9C84DFEF872CCBD8DADA4230187C6D31CE398AC5
              227DF8305214655C14C5CCCBCBCBBB3E8C312C2C2C405555CCCECE4210FEEC49
              14454892346EA6615A844484F3F373B2D2826F99DBED86D7EB6DC9BBE51430C6
              303232322E8A62C7E2369B0DA3A3A3A6E296BAC0E170188D22EBC4060707A128
              CADFDF883E12054992303C3CCC3EED4AD669143C1ECF6B277C0A402751906519
              6EB79B5985B57C1C3B1C0E4355553C3D3D99FA399DCE9FFDFDFD96A3C57AEF82
              1E400FE0BF07F805199B03A1AC104F7E0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Directions\3SE'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F400000006624B474400CC00CC00CCDFC15F1A000000097048597300002E2300
              002E230178A53F760000000774494D4507E4040B072B081E64B12B0000029E49
              44415458C3ED974D4B2A5118C7FF63373224F10561A04522ED8436F77E0161B6
              B974E942BF41E0BA4D44F713F4B2A85D5008A1222806B5A89D17C185E0948231
              29694CCCC4C83432F3DCD5C40DC999F11A6DFCC3B399F3C0F93D6F67CE618808
              DF2917BE59738039C01CE0875D4722822008341C0E27FA0502813FA150E8D7CC
              0124498A743A1DE8BA3ED1EFF5F5F5A7D7EBC5D2D2D2EC4A4044E876BB2DABCD
              014051140C06039A690F4892141145D1765D1F1F1F61552ADB004EA237A5AA2A
              7ABD1ECD04C069F4A6FAFD3E6459FE3F8069A237A5691A044120ABBFAD6B16D1
              8BA288DBDB5B188631F65D92A4C8D400B22C5B464F4428954AD8DDDD45A150C0
              68347A5FD3751DAAAAB6A6060806838CD53C371A0D64B359288A82FDFD7D1C1C
              1CBC4F80C7E381DFEF67A606F0783C0885429FAE1B86814AA502B34CAAAAE2E2
              E202474747180E876059D6F240B29C0296653FCD82CBE5423C1E472C16C3E2E2
              E23B543E9FC7F1F1319697977FFFDB94954A65AC29193B77C256AB4582204C9C
              FB9B9B1B9C9E9EA2DD6E0300161616904C26B1BDBD8DB5B535A65C2ED3D6D616
              CECFCF118D46194727E1A42C0080DBED06C771D8D9D9C1E6E626DC6E37745DC7
              C9C90952A9146AB51AEDEDEDA1D168A0502838CF809D2C981A8D46B8BBBBC3E1
              E121EAF53A8808EBEBEB78787880A6698846A3B8BCBC04CBB28CA3FB8055164C
              F97C3EA45229A6582C2293C9C0EFF7E3FEFE1E9AA601009ACD26AEAEAE3ECEB1
              5D134591EBF57A34C95E5E5E22A6FFDBDB1B12890401F8601CC791A228202267
              004EEDECEC8C565656C600BC5E2F5D5F5FD39702F03C4F1B1B1B639B9B964EA7
              C9300CFB4DE854B22CA35AAD52A7D301CFF3E876BBE0791E4F4F4F787E7EC6EA
              EA2A72B9DCD7017C765B92659906830100201C0E33CCFC71FADD007F01767C50
              168103B1DF0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Directions\4S'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F400000006624B474400CC00CC00CCDFC15F1A000000097048597300002E2300
              002E230178A53F760000000774494D4507E4040B072A22DCC449BC0000026C49
              44415458C3ED96CF6AE25014C6BF68306A501B252868293A8B42D1D5CCA6BB2E
              3A5BDFC19D1B9FA29BBE421FC1071084990770330FE0228B604C402190142529
              B1DF6CC680D5A9496AE9C603176EC2C939BFEF9CFB2702497CA5A5F0C5760638
              039C01C4A88E24611806D7EBF5BB7EE572F98FAAAA3F4E0EE0384E4BD7756C36
              9B77FD9E9F9FBF178B45489274BA169084699ADAB1E400B05AADB05C2E79D235
              E0384ECBB6EDC87D9DCFE738D6AAC80071D46FCDF33C5896C59300C455BFB5C5
              6201D7753F069044FDD65E5E5E6018068FDDB6A9CF50BF35DBB6E1384E2BF136
              745DF7BFEA3DCFC3EBEB2B1CC7C17ABD46B15884AAAA3B3E9BCD069EE7690084
              4400954A45304D93BEEFEF257F7C7CC46C360B01BADD2EFAFDFE8E9F2CCB5014
              45485C015996A1AA2A0CC3D8ED5B2A05D775A1695AF8AED168EC7D5FABD58E1E
              48477741AD5613DE06C96432A856ABE1733A9D46B95C3E042F7C781B6EABF09E
              4992B40314557DE493F05015144509E7A55209171717B1D54706385485CBCBCB
              709ECFE791CBE562AB8FF53F70A80A5BAB56AB61C238EA635DC7B22CE3FAFAFA
              A7EFFBBF0040D77588A2882008D06C367173730300C866B3DFA2AA8F05F06FF5
              FF4EA7D382699ACCE5729024094110A05EAF63B15840D775D8B6ADDDDFDFA35E
              AF47AB02C9482308023C3C3CB0DD6EB352A950966502200066B359160A058AA2
              C8BBBB3B5A96C5A871230390C4743A65A7D30913BF1D5757579C4C268C133316
              00490C8743E6F3F9BDE4994C864F4F4F8C1B2F3680EFFB180C0614046107A0D7
              EB71B55AE1D30148C2B22CDEDEDE86C93B9D0E354D639258890048623C1E5351
              142A8AC2D168C4A471FE029A93CD6B515EEB860000000049454E44AE426082}
          end>
      end
      item
        Name = 'Directions\5SO'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F400000006624B474400CC00CC00CCDFC15F1A000000097048597300002E2300
              002E230178A53F760000000774494D4507E4040B072A33B674694E000002A749
              44415458C3ED97BB4BEB5018C07FA7DA874A8AC56AA51485563B767175112C6E
              EEBA8AB88983FF8008E25D5C1587EE8250B08B50A82EDDEE2606D4F662C11716
              022934C46A72EED442AFDC34F5814B0F7C434EBE9CEFF73D0F11524A7E7279F8
              E1D503E801F400FABB51AE56ABBF354D9B71D2191C1C24168B0921C4D702BCBC
              BC50A95466EAF5BAA35E5F5F1F8AA2C4878787FF7C690AAAD5AAEC641CC0B22C
              1E1E1ECA6E27AC2B00C330B8BFBF779D2A4DD3D0753DFE65008F8F8FD2344DD7
              00DD44A12340AD56E3F9F9B9EBEA761B0547002925777777B2D168740DE0360A
              8E00BAAEC7354D6BDBB36D9B62B1C8BFFB1F8D822380699A65CBB25ACFAFAFAF
              E47239767676383D3DA59377966551ABD5CA1F06088542626868A8D509070707
              ECEFEF53AFD7393E3E4655554700BFDFCFC8C888F83080DFEF677C7C1CC33038
              3C3C249BCDD2EC064DD3C8E7F3D8B6FDDFEF474747693AE00A404A493E9F6F2B
              BA8181815F994C869393939631AFD7CBDCDC1C8B8B8B783C1E27F88EF3B86D14
              ABAA2A373636D8DBDB930B0B0BA252A9C8ADAD2DB2D96CCB783C1E67797999D9
              D9590281C0A7BC7F0790CBE5505595DDDD5DC6C6C6E4E6E62685420180402040
              3A9D6669698968348A8BD4B9BA8D44B3929F9E9EE4FCFC3C979797F87C3E2626
              2628954A082148A552ACADAD313D3D8DD7EBED78682C16239148B8026845E0EC
              EC8CABAB2B001A8D06A552895028C4EAEA2AEBEBEB84C361717171D1F142EAC6
              FB16806118643219DEDEDEDA5EA6D369B6B7B785CFE703606A6A2A619A66B903
              40DA4DEEDB2AFFFCFC5C06834109B489A228F2E8E8484A29F92EC1B66D565656
              DE196F4A2A9592D7D7D7DF06D17F7373238BC5228AA2100E87894422249349A2
              D128C96492C9C949229188E09B96D0759DDBDB5BD9ECDD603028BACAE167017A
              3FA73F0DF0170354CCB5F7F656C50000000049454E44AE426082}
          end>
      end
      item
        Name = 'Directions\6NO'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F400000006624B474400CC00CC00CCDFC15F1A000000097048597300002E2300
              002E230178A53F760000000774494D4507E4040B07292AF932924D000002D549
              44415458C3ED973D4B235114869FEB981826389230E3471C14120C246040562D
              4410C414161105C1460515353616365AF803B6F607D88A1616DA0EE80FD84644
              04D1C54619085111C41135770BD780BB6E2671CD0A8B07A618EE70EE73DEF371
              EF0829251F69157CB07D3840E5F5F535A7A7A712C0300C344D137EBFFFDF01D8
              B62D474646383B3B43D775EAEAEA64341A25140A118D46696E6EA6BDBD5D689A
              561E825C2EC7D4D494045E7D1289843C3A3A92524ACAF120A5647777576A9AF6
              DBE6D5D5D5727D7DBD6C9B4B29A904E8E8E8109D9D9DD2B2AC17EAF4F7F73338
              38289EDFAFAEAEC28EE39C1452B4AAAA2A190804AC6233209EE7C0DADA9A1C1F
              1FE7E1E121BF180804989E9E667E7E1E5DD7C5FEFEBEBCB9B9C10580D6D6D6A2
              0B390F60DBB6ECEBEBE3E0E000AFD74B535313C7C7C70821482412CCCECED2D2
              D282C7E371756A9A26914844943407EAEBEBC5E8E828005D5D5D6C6C6CD0DBDB
              8B9492BDBD3D161616585959E1FCFCDCD5692693C14DA95707512A95221E8FB3
              B4B4445B5B9B585D5D656262024551701C87EDED6D969797B12C0BC771FEE8F4
              EEEE0EDBB665492980A78EB02C4BF6F4F408AFD70B40369BFD9A4EA717373737
              C9E57200783C1EBABBBB191B1B231C0EFF552DBC504008413299CC6F0E707B7B
              BB383939C9C0C00015154F9FDFDFDFB3B3B3C3D6D6561EEAAD2A143C0B7E3A41
              5555666666181A1AC2E7F301100C0649269379A8B7D6424180CBCBCB7CDBA9AA
              4A3A9D666E6E0EBFDFCFF0F030F1781CB700B2D96C41152A0B2DFA7CBE88A228
              278F8F8FF9DCA75229745D27168B2144E14E5314054DD3224517E1AF26A5E4F0
              F050663299379D338661108BC54421D082291042609AE68BA22CD6144521140A
              45DC5472BD90689A466D6D6DC900C160909A9A9AEFEF72236A686810CFD5FF9E
              D1170DA0AA2A8D8D8DEF1E7D497742C3308A3AE14A89DEB50B5E192CDF2E2E2E
              BEB8A9659AA6280BC0E77FC127C027C07F09F003D26890A66402558100000000
              49454E44AE426082}
          end>
      end>
    Left = 56
    Top = 96
  end
  object VirtualImageList: TVirtualImageList
    DisabledGrayscale = False
    DisabledSuffix = '_Disabled'
    Images = <
      item
        CollectionIndex = 0
        CollectionName = 'Directions\1N'
        Disabled = False
        Name = '1N'
      end
      item
        CollectionIndex = 1
        CollectionName = 'Directions\2NE'
        Disabled = False
        Name = '2NE'
      end
      item
        CollectionIndex = 2
        CollectionName = 'Directions\3SE'
        Disabled = False
        Name = '3SE'
      end
      item
        CollectionIndex = 3
        CollectionName = 'Directions\4S'
        Disabled = False
        Name = '4S'
      end
      item
        CollectionIndex = 4
        CollectionName = 'Directions\5SO'
        Disabled = False
        Name = '5SO'
      end
      item
        CollectionIndex = 5
        CollectionName = 'Directions\6NO'
        Disabled = False
        Name = '6NO'
      end>
    ImageCollection = ImageCollection
    Width = 32
    Height = 32
    Left = 56
    Top = 144
  end
end
