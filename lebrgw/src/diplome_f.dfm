object frmDiplome: TfrmDiplome
  Left = 192
  Top = 108
  BorderIcons = []
  BorderStyle = bsNone
  ClientHeight = 384
  ClientWidth = 512
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  PopupMenu = PopupMenu
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnPaint = FormPaint
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ShapeE: TShape
    Left = 56
    Top = 20
    Width = 400
    Height = 256
    Brush.Style = bsClear
    Pen.Color = 14737632
    Shape = stEllipse
  end
  object ShapeD: TShape
    Left = 52
    Top = 24
    Width = 408
    Height = 248
    Brush.Style = bsClear
    Pen.Color = 13684944
    Shape = stEllipse
  end
  object ShapeC: TShape
    Left = 48
    Top = 28
    Width = 416
    Height = 240
    Brush.Style = bsClear
    Pen.Color = clSilver
    Shape = stEllipse
  end
  object ShapeB: TShape
    Left = 44
    Top = 32
    Width = 424
    Height = 232
    Brush.Style = bsClear
    Pen.Color = 11579568
    Shape = stEllipse
  end
  object ShapeA: TShape
    Left = 40
    Top = 36
    Width = 432
    Height = 224
    Brush.Style = bsClear
    Pen.Color = 10526880
    Shape = stEllipse
  end
  object Shape9: TShape
    Left = 36
    Top = 40
    Width = 440
    Height = 216
    Brush.Style = bsClear
    Pen.Color = 9474192
    Shape = stEllipse
  end
  object Shape8: TShape
    Left = 32
    Top = 44
    Width = 448
    Height = 208
    Brush.Style = bsClear
    Pen.Color = clGray
    Shape = stEllipse
  end
  object Shape7: TShape
    Left = 28
    Top = 48
    Width = 456
    Height = 200
    Brush.Style = bsClear
    Pen.Color = 7368816
    Shape = stEllipse
  end
  object Shape6: TShape
    Left = 24
    Top = 52
    Width = 464
    Height = 192
    Brush.Style = bsClear
    Pen.Color = 6316128
    Shape = stEllipse
  end
  object Shape5: TShape
    Left = 20
    Top = 56
    Width = 472
    Height = 184
    Brush.Style = bsClear
    Pen.Color = 5263440
    Shape = stEllipse
  end
  object Shape4: TShape
    Left = 16
    Top = 60
    Width = 480
    Height = 176
    Brush.Style = bsClear
    Pen.Color = 4210752
    Shape = stEllipse
  end
  object Shape3: TShape
    Left = 12
    Top = 64
    Width = 488
    Height = 168
    Brush.Style = bsClear
    Pen.Color = 3158064
    Shape = stEllipse
  end
  object Shape2: TShape
    Left = 8
    Top = 68
    Width = 496
    Height = 160
    Brush.Style = bsClear
    Pen.Color = 2105376
    Shape = stEllipse
  end
  object Shape1: TShape
    Left = 4
    Top = 72
    Width = 504
    Height = 152
    Brush.Style = bsClear
    Pen.Color = 1052688
    Shape = stEllipse
  end
  object Shape0: TShape
    Left = 0
    Top = 76
    Width = 512
    Height = 144
    Brush.Style = bsClear
    Shape = stEllipse
  end
  object LabelDiplomeArriere: TLabel
    Left = 75
    Top = 120
    Width = 355
    Height = 55
    Alignment = taCenter
    Caption = 'Dipl'#244'me de berger'
    Font.Charset = ANSI_CHARSET
    Font.Color = clGray
    Font.Height = -48
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object LabelDiplomeAvant: TLabel
    Left = 73
    Top = 118
    Width = 355
    Height = 55
    Alignment = taCenter
    Caption = 'Dipl'#244'me de berger'
    Color = clWhite
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -48
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Transparent = True
  end
  object LabelNomJoueur: TLabel
    Left = 79
    Top = 288
    Width = 143
    Height = 22
    Caption = 'Nom du joueur'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Courier New'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
    Transparent = True
  end
  object Label1: TLabel
    Left = 0
    Top = 286
    Width = 73
    Height = 23
    Caption = 'D'#233'cern'#233' '#224
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object Label2: TLabel
    Left = 0
    Top = 310
    Width = 123
    Height = 23
    Caption = 'pour avoir r'#233'ussi'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object LabelNomSerie: TLabel
    Left = 296
    Top = 312
    Width = 165
    Height = 22
    Caption = 'Nom de la s'#233'rie'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Courier New'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
    Transparent = True
  end
  object LabelNbNiveaux: TLabel
    Left = 127
    Top = 312
    Width = 11
    Height = 22
    Caption = 'N'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Courier New'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
    Transparent = True
  end
  object Label3: TLabel
    Left = 144
    Top = 310
    Width = 147
    Height = 23
    Caption = 'niveau(x) de la s'#233'rie'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object Label4: TLabel
    Left = 0
    Top = 334
    Width = 124
    Height = 23
    Caption = 'avec un score de '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object LabelScore: TLabel
    Left = 124
    Top = 336
    Width = 55
    Height = 22
    Caption = 'Score'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Courier New'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
    Transparent = True
  end
  object Label5: TLabel
    Left = 0
    Top = 370
    Width = 513
    Height = 13
    Alignment = taCenter
    AutoSize = False
    Caption = 'Le berger - '#169' Patquoi.fr - 2020 '
    Transparent = True
  end
  object PopupMenu: TPopupMenu
    Left = 24
    Top = 16
    object RubriqueExporter: TMenuItem
      Caption = '&Exporter sous forme d'#39'image...'
      ShortCut = 16453
      OnClick = RubriqueExporterClick
    end
    object RubriqueCopier: TMenuItem
      Caption = '&Copier dans le presse-papier'
      ShortCut = 16451
      OnClick = RubriqueCopierClick
    end
    object RubriqueFermer: TMenuItem
      Caption = '&Fermer'
      OnClick = RubriqueFermerClick
    end
  end
  object ImageCollection: TImageCollection
    Images = <
      item
        Name = 'PatquoiFr'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D49484452000000400000002E080600000098971F
              F400000006624B474400FF00FF00FFA0BDA793000000097048597300002E2300
              002E230178A53F760000000774494D4507E4041114340D8290E1E80000001974
              455874436F6D6D656E74004372656174656420776974682047494D5057810E17
              000004444944415468DEED99DF739A5814C7BFC035F8031A54FC89DDE4A16AAB
              CD4C77A69DEEFFFFB47D4B33D304CC64B2A6713B6B5504A253A3401FB252D828
              55A8A293BD4FC0E5E2F1DC73EE399F7328DBB66D3CE141C22CEE76FFC1F5F535
              0080E338349BAF3DF3373737F8FAB58BD96C8662B184A3A3A3A5DF525515AD96
              E2DC330C8D58EC00D96C169254014551BBA700BF311A8DF0E5CBDF81D79BA605
              D3FC864EA703968D2397CBF9BE6F1806CECF3F01005896C59B37BF6F5E01F97C
              01F97C61E1DC6C3673AEEBF53A0421BDF277198641B3F91A67671F01009AA6FD
              5401812DE0C3873F0100A228229DCEE0F2B20500E0791E8D4613A3D108B7B79F
              6118060020994C4192CA383C147C5DE0F2F287392B8A8262B1844422EEBC2F8A
              22E2F10424495A285822917059C38332755D47A7D3C16874F7AF2C0994CB1508
              820045919DF72793091445C68B17555C5D5D41D3861004013CFF0CEDF65F0080
              743A835AAD06DA4F3BF7F7F7383FFF84E17008D334619A260C43872CCB8E4282
              0EC330707BFB792D9792E50BE8BAE692E50E8A22633C1E2D5CD3EFF7A1AA0358
              9685C160B0F0F77C15A0691A2CCB020064B359542A1567AED7EBF90A5CADD69C
              EB6432F5E8009C4C26BEEB27936F3F84A46968DA10F380757C7C8C4C26E352E6
              1DEAF597CE3DCBB2A8D75F623A9D3ACFB2D92C4AA5F27A6780FB030C434048EC
              915906F63D42F0EA5563C90168E2F4F4D4B98FC7E3304DD3230B4DD32BC8627B
              D6C462643D05D8B6E533172E7DE0380EC964F2A74A3A3C14502A954108812455
              A0AA2ABADD2E745D73DEB3ACE0B2848802E1E23245D1BE51E0EDDB779E67E3F1
              18B27C81E9740A42624826532EDF0FAE003AE89FDC5462B23C511A382E294965
              F03CFF4B3683B8E3B63B76CF4DD0ED67EEF945FED46AB5A0AA0388A20851147F
              A902E687F132BF776F88699AB06DDB63658BFE9F4701C3E110BAAE7B26054100
              4551B06D1BFD7E1F40DF75AA8A4BC3CF26C6C1C18173DD6EB73D87E07F15309B
              CD7076F611CF9FFFE63C1B0CFAD0B4E16317C8E572208480E33894CBDE30C1B2
              2CAAD51A388E034DD3208480E79FA156AB83E3B8ADBA8028E6200869D0340D41
              1050287833D0542A8542A10886613C1B98CBE5C1300C388E47A9547AECCA4F89
              06DD99EB3C13A4FEC7E18871346A1C2751E368D4384EA2C6D1A8717CA9056C0B
              47A3C671B28E49C9F2858701E6387A7272E28BA30F7178004DD3D6DAE1398EBB
              93A0071CD7D1683443E378AFD75B9E0A6F0B47A3C67112358E468DE3246A1C8D
              1AC749D4381A358ED351E368D438BEB2536E0A47A3C6F19515B0291C8D1AC757
              76814DE168D438BE551A5C84A3518F278FC3349EF8707A83FBDADE0EEB92242C
              4FEF7B3D81BC7FFF47289EDEF77AC25217D897F676D87A42E0437057DADBABD4
              13FCDAFB74589EDEF77A42E0E6E8AEB4B7C3D613022B6057DADB61EB098115B0
              2BEDEDB0A8BDB54C7057EB09242C4FEF7B3D816CCB0276B59EB03517D8D57AC2
              5EE1F026EA09DF0163E7FA0F112785630000000049454E44AE426082}
          end>
      end>
    Left = 408
    Top = 8
  end
  object VirtualImageList: TVirtualImageList
    DisabledGrayscale = False
    DisabledSuffix = '_Disabled'
    Images = <
      item
        CollectionIndex = 0
        CollectionName = 'PatquoiFr'
        Disabled = False
        Name = 'PatquoiFr'
      end>
    ImageCollection = ImageCollection
    Width = 64
    Height = 46
    Left = 408
    Top = 56
  end
  object SaveDialogImage: TSaveDialog
    DefaultExt = 'bmp'
    Filter = 'Image (*.bmp)|.bmp'
    Title = 'Enregistrer l'#39'image sous...'
    Left = 24
    Top = 72
  end
end
