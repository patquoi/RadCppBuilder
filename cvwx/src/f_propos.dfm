object frmAPropos: TfrmAPropos
  Left = 617
  Top = 254
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #192' propos de Centre-Ville'
  ClientHeight = 169
  ClientWidth = 259
  Color = clBlack
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Arial'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = True
  Position = poScreenCenter
  OnClick = LabelClick
  OnCreate = FormCreate
  OnHide = FormHide
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object LabelAuteur2: TLabel
    Left = 70
    Top = 28
    Width = 104
    Height = 26
    Alignment = taCenter
    Caption = 'Id'#233'e && Programme de Patrice FOUQUET'
    Font.Charset = ANSI_CHARSET
    Font.Color = clOlive
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = True
    WordWrap = True
  end
  object LabelCV2: TLabel
    Left = 70
    Top = 4
    Width = 104
    Height = 23
    Alignment = taCenter
    AutoSize = False
    Caption = 'Centre-Ville'
    Font.Charset = ANSI_CHARSET
    Font.Color = clMaroon
    Font.Height = -19
    Font.Name = 'Impact'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object LabelCV1: TLabel
    Left = 69
    Top = 3
    Width = 104
    Height = 23
    Alignment = taCenter
    AutoSize = False
    Caption = 'Centre-Ville'
    Font.Charset = ANSI_CHARSET
    Font.Color = 33023
    Font.Height = -19
    Font.Name = 'Impact'
    Font.Style = []
    ParentFont = False
    Transparent = True
    OnClick = LabelClick
  end
  object LabelAuteur1: TLabel
    Left = 69
    Top = 27
    Width = 104
    Height = 26
    Alignment = taCenter
    Caption = 'Id'#233'e && Programme de Patrice FOUQUET'
    Font.Charset = ANSI_CHARSET
    Font.Color = clYellow
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = True
    WordWrap = True
    OnClick = LabelClick
  end
  object LabelEMail: TLabel
    Left = 0
    Top = 152
    Width = 259
    Height = 17
    Cursor = crHandPoint
    Align = alBottom
    Alignment = taCenter
    AutoSize = False
    Caption = 'centre-ville@patquoi.fr'
    Font.Charset = ANSI_CHARSET
    Font.Color = clAqua
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = LabelEMailClick
  end
  object LabelURL: TLabel
    Left = 0
    Top = 138
    Width = 259
    Height = 14
    Cursor = crHandPoint
    Align = alBottom
    Alignment = taCenter
    Caption = 'http://patquoi.fr/#cvw'
    Font.Charset = ANSI_CHARSET
    Font.Color = clAqua
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = LabelURLClick
    ExplicitWidth = 104
  end
  object LabelTexte: TLabel
    Left = 24
    Top = 68
    Width = 212
    Height = 61
    Hint = 
      'Voyons les humains comme des fourmis. Hormis que les fourmis n'#39'o' +
      'nt pas de voitures.'
    Alignment = taCenter
    AutoSize = False
    Caption = 
      'Cette simulation est n'#233'e le jour o'#249' j'#39'ai constat'#233' comme la circu' +
      'lation des '#234'tres humains est impr'#233'visible. Etant impuissants, d'#233 +
      'tendons-nous et comtemplons ce ph'#233'nom'#232'ne. Le chaos ne peut '#234'tre ' +
      'que comtempl'#233'.'
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clLime
    Font.Height = -9
    Font.Name = 'Small Fonts'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    WordWrap = True
    OnClick = LabelClick
  end
  object SpeedButtonOk: TSpeedButton
    Left = 8
    Top = 8
    Width = 48
    Height = 48
    Hint = 'Cliquer sur le feu tricolore pour fermer'
    Flat = True
    ParentShowHint = False
    ShowHint = True
    OnClick = LabelClick
  end
  object LabelSousVersion: TLabel
    Left = 239
    Top = 34
    Width = 9
    Height = 14
    Caption = ',0'
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clLime
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    OnClick = LabelClick
  end
  object LabelGPL1: TLabel
    Left = 185
    Top = 46
    Width = 57
    Height = 23
    Caption = 'GPL 2.0'
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlue
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Transparent = True
  end
  object LabelGPL2: TLabel
    Left = 184
    Top = 45
    Width = 57
    Height = 23
    Hint = 'Cliquer ici pour plus d'#39'infos...'
    Caption = 'GPL 2.0'
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clSkyBlue
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    Transparent = True
    OnClick = LabelClick
  end
  object ImageVersion: TImage
    Left = 183
    Top = 3
    Width = 56
    Height = 44
    Picture.Data = {
      0954506E67496D61676589504E470D0A1A0A0000000D494844520000001C0000
      00160806000000D396FCF2000000017352474200AECE1CE90000000467414D41
      0000B18F0BFC6105000000097048597300001D8600001D86015DA21381000000
      DE4944415478DABD95C10902410C459336042FF660150A96B4DB8395085AC836
      E045B08DD1110F8BE4FFFCAC622E0393993CE691306E66CDFE18DE8197FB5ABE
      B05BDD602EAAF379DE37A77D3B6EA7AF81CF3A16D509812AEC7A38C35C072AE7
      43A54C1B0AB546A8B40A8C7452A0AA8D01D51A5297662F463AA37DA94B1910E9
      44FB6997668A914EB4FF52BA4497920F953260D67D2C0F956640A697E5A9D2AA
      16A69405ECD24C0B532A01AB5A509EC5CF94B290075F55CA421EFC8AD20C0895
      320DD1ABDAFB86FB02A573A0F26B8FA3D930E44069F0955FBB03E76B55E90378
      4BD0010FABC1650000000049454E44AE426082}
    Stretch = True
    OnClick = LabelClick
  end
  object Timer: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 32
    Top = 120
  end
  object ImageCollection: TImageCollection
    Images = <
      item
        Name = 'cv1'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200403000000815467
              C700000030504C5445000000800000008000808000000080800080008080C0C0
              C0808080FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF4F132649000000
              097048597300002E2300002E230178A53F760000000774494D4507E403120B31
              240ABA1A720000008B4944415428CF63E0A8674005640AFC2F6F4053C1D1812C
              D0D02028802250D02028C8812CF0015D8081415010CD1646411A38CCD800CD61
              C6C6680E43136060303646B385D9985C87ED2E407518F7EEED3087692D0009EC
              EE002B01396CD52AA03BB877FCEFDE0E7518586077FFFF1F20252033B45631A0
              0A302931206B8139006E284C006E2DDC8D6005008E7C4435412A0FFE00000000
              49454E44AE426082}
          end>
      end
      item
        Name = 'cv2'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200403000000815467
              C700000030504C5445000000800000008000808000000080800080008080C0C0
              C0808080FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF4F132649000000
              097048597300002E2300002E230178A53F760000000774494D4507E403120B31
              1ACBDB07D90000008D4944415428CF63E0A8674005640AFC2F6F4053C1D1812C
              D0D02028802250D02028C8812CF0015D8081415010CD1646904007083420B963
              260814E010003B8C73FEFF9FD3911D86106868B0DE0072D8CCFF201D6087EDDE
              CD812CF0012AC039733ACC1DD6BB195005988D211617A005108640070921A6A4
              8016624A4A68218626C0C0A0A48416624C4A14C52D00506045E7B52F98A30000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'cv3'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200403000000815467
              C700000030504C5445000000800000008000808000000080800080008080C0C0
              C0808080FF000000FF00FFFF000000FFFF00FF00FFFFFFFFFF4F132649000000
              097048597300002E2300002E230178A53F760000000774494D4507E403120B31
              115C09DE510000009C4944415428CF9DCE2B0EC3300C80616F25091C2CAB7C82
              49B958D8600D0BC726A35CB134288BDD87126F6433A9F2C9957F7033ECC3CCAF
              FA39C157E0D880BC65E5009FE65C528E0AE541E07392D900DC02BEC85B3788C6
              67055D608148CC4E7FC91BAC0ADD95914DC7E5F6ADB49E5AA883C3F7B00E24AC
              01A270EF205208AE85D5024008E6CA60E1A3E38F309C4C18A20933008068AE5C
              F1E7B076DEBE6956162F58FAAC0000000049454E44AE426082}
          end>
      end>
    Left = 8
    Top = 64
  end
  object VirtualImageList: TVirtualImageList
    DisabledGrayscale = False
    DisabledSuffix = '_Disabled'
    Images = <
      item
        CollectionIndex = 0
        CollectionName = 'cv1'
        Disabled = False
        Name = 'cv1'
      end
      item
        CollectionIndex = 1
        CollectionName = 'cv2'
        Disabled = False
        Name = 'cv2'
      end
      item
        CollectionIndex = 2
        CollectionName = 'cv3'
        Disabled = False
        Name = 'cv3'
      end>
    ImageCollection = ImageCollection
    Width = 32
    Height = 32
    Top = 120
  end
end
