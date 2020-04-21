object frmNomJoueur: TfrmNomJoueur
  Left = 181
  Top = 270
  ActiveControl = EditNomJoueur
  BorderIcons = []
  BorderStyle = bsToolWindow
  Caption = 'Entrez votre nom'
  ClientHeight = 35
  ClientWidth = 173
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object EditNomJoueur: TEdit
    Left = 8
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 0
    OnChange = EditNomJoueurChange
  end
  object ButtonOk: TButton
    Left = 136
    Top = 8
    Width = 33
    Height = 22
    Caption = '&Vu'
    Default = True
    Enabled = False
    ModalResult = 1
    TabOrder = 1
  end
end
