(******************************************************************************
CENTRE-VILLE pour Linux

Copyright (C) 2001 Patrice FOUQUET

Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le
modifier conformément aux dispositions de la Licence Publique Générale GNU,
telle que publiée par la Free Software Foundation ; version 2 de la licence,
ou encore toute version ultérieure.

Ce programme est distribué dans l'espoir qu'il sera utile,
mais SANS AUCUNE GARANTIE ; sans même la garantie implicite de COMMERCIALISATION
ou D'ADAPTATION A UN OBJET PARTICULIER. Pour plus de détail,
voir la Licence Publique Générale GNU.

Vous devez avoir reçu un exemplaire de la Licence Publique Générale GNU en même
temps que ce programme ; si ce n'est pas le cas,
écrivez à la Free Software Foundation Inc.,
675 Mass Ave, Cambridge, MA 02139, Etats-Unis.

Pour toutes informations:
mailto:fouquetp@francenet.fr
http://persoweb.francenet.fr/~fouquetp

-------------------------------------------------------------------------------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************)

unit propos_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QImgList, QButtons, QExtCtrls, QStdCtrls, QTypes;

type
  TfrmAPropos = class(TForm)
    SpeedButtonOk: TSpeedButton;
    ImageList: TImageList;
    ImageVersion: TImage;
    LabelTexte: TLabel;
    LabelURL: TLabel;
    LabelEMail: TLabel;
    LabelCV2: TLabel;
    LabelCV1: TLabel;
    Timer: TTimer;
    LabelAuteur2: TLabel;
    LabelAuteur1: TLabel;
    LabelSousVersion: TLabel;
    procedure TimerTimer(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormHide(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure SpeedButtonOkClick(Sender: TObject);
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure FormResize(Sender: TObject);
  private
    TempsEcoule : Integer;
    BitMap : TBitMap;
  public
    FermetureAutomatique : Boolean;
  end;

var
  frmAPropos: TfrmAPropos;

implementation

{$R *.xfm}

procedure TfrmAPropos.TimerTimer(Sender: TObject);
begin
 Inc(TempsEcoule);
 case TempsEcoule mod 10 of
  0: begin
     ImageList.GetBitmap(0, BitMap);
     LabelTexte.Font.Color:=clLime;
     end;
  4: begin
     ImageList.GetBitmap(1, BitMap);
     LabelTexte.Font.Color:=clYellow;
     end;
  6: begin
     ImageList.GetBitmap(2, BitMap);
     LabelTexte.Font.Color:=clMaroon;
     end;
 end{case of};
 SpeedButtonOk.Glyph:=BitMap;
 if FermetureAutomatique and (TempsEcoule = 2) then
  begin
  FermetureAutomatique:=false;
  Close;
  end;
end;

procedure TfrmAPropos.FormShow(Sender: TObject);
begin
 TempsEcoule:=0;
 Bitmap:=TBitMap.Create;
 ImageList.GetBitmap(0, Bitmap);             
 SpeedButtonOk.Glyph:=Bitmap;
 Timer.Enabled:=true;
 FormResize(self);
end;

procedure TfrmAPropos.FormHide(Sender: TObject);
begin
 Timer.Enabled:=false;
 Bitmap.Destroy;
end;

procedure TfrmAPropos.FormCreate(Sender: TObject);
begin
 FermetureAutomatique:=false;
end;

procedure TfrmAPropos.SpeedButtonOkClick(Sender: TObject);
begin
 Close;
end;

procedure TfrmAPropos.FormKeyPress(Sender: TObject; var Key: Char);
begin
 if (Key=#13) or (Key=#27) then SpeedButtonOk.Click;
end;

procedure TfrmAPropos.FormResize(Sender: TObject);
var h, w : Integer;
begin
 w:=LabelEMail.Left+LabelEMail.Width+13;
 h:=LabelEMail.Top+LabelEMail.Height+11;
 if Height<>h then
  begin
  Top:=Top+(Height-h) div 2;
  Height:=h;
  end;
 if Width<>w then
  begin
  Left:=Left+(Width-w) div 2;
  Width:=w;
  end;
end;

end.




