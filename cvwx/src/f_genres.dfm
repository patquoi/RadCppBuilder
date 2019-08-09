object frmGeneration: TfrmGeneration
  Left = 218
  Top = 147
  HelpContext = 3112
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'G'#233'n'#233'ration al'#233'atoire d'#39'un r'#233'seau'
  ClientHeight = 183
  ClientWidth = 687
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object LabelRq: TLabel
    Left = 8
    Top = 158
    Width = 414
    Height = 13
    Caption = 
      'ATTENTION : Seules les voies de circulation automobile sont g'#233'n'#233 +
      'r'#233'es !'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object GroupBox: TGroupBox
    Left = 8
    Top = 8
    Width = 673
    Height = 137
    Caption = ' Param'#232'tres '
    TabOrder = 0
    object Label1: TLabel
      Left = 11
      Top = 26
      Width = 350
      Height = 13
      Caption = 
        'Proportion des segments de routes par rapport aux dimensions de ' +
        'la zone :'
    end
    object Label2: TLabel
      Left = 11
      Top = 52
      Width = 360
      Height = 13
      Caption = 
        'Probabilit'#233' d'#39'aller dans une nouvelle direction (nouvelle sortie' +
        ' d'#39'intersection) :'
    end
    object Label3: TLabel
      Left = 411
      Top = 26
      Width = 20
      Height = 13
      Caption = 'Min.'
    end
    object Label4: TLabel
      Left = 536
      Top = 26
      Width = 23
      Height = 13
      Caption = 'Max.'
    end
    object Label5: TLabel
      Left = 11
      Top = 76
      Width = 390
      Height = 13
      Caption = 
        'Probabilit'#233' qu'#39'un segment d'#233'bouche sur une route (nouvelle entr'#233 +
        'e d'#39'intersection) :'
    end
    object Label6: TLabel
      Left = 11
      Top = 100
      Width = 393
      Height = 13
      Caption = 
        'Probabilit'#233' qu'#39'un segment traverse une route (nouvelle entr'#233'e/so' +
        'rtie d'#39'intersection) :'
    end
    object TrackBarTailleMinSegments: TTrackBar
      Left = 431
      Top = 18
      Width = 100
      Height = 29
      TabOrder = 0
      ThumbLength = 10
      TickMarks = tmBoth
    end
    object TrackBarProbaSortieIntersection: TTrackBar
      Left = 431
      Top = 45
      Width = 228
      Height = 29
      Position = 8
      TabOrder = 2
      ThumbLength = 10
      TickMarks = tmBoth
    end
    object TrackBarTailleMaxSegments: TTrackBar
      Left = 559
      Top = 18
      Width = 100
      Height = 29
      Position = 3
      TabOrder = 1
      ThumbLength = 10
      TickMarks = tmBoth
    end
    object TrackBarProbaEntreeIntersection: TTrackBar
      Left = 431
      Top = 69
      Width = 228
      Height = 29
      Position = 8
      TabOrder = 3
      ThumbLength = 10
      TickMarks = tmBoth
    end
    object TrackBarProbaTraverseeRoute: TTrackBar
      Left = 431
      Top = 93
      Width = 228
      Height = 29
      Position = 8
      TabOrder = 4
      ThumbLength = 10
      TickMarks = tmBoth
    end
  end
  object ButtonAnnuler: TButton
    Left = 517
    Top = 152
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Annuler'
    ModalResult = 2
    TabOrder = 2
  end
  object ButtonOk: TButton
    Left = 432
    Top = 152
    Width = 75
    Height = 25
    Caption = 'G'#233'n'#233'rer'
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = ButtonOkClick
  end
  object ButtonAide: TButton
    Left = 605
    Top = 152
    Width = 75
    Height = 25
    Caption = 'Aide'
    TabOrder = 3
    OnClick = ButtonAideClick
  end
end
