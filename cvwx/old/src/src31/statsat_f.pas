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

unit statsat_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls, QExtCtrls, QComCtrls;

type
  TfrmStatsAttenteTrafic = class(TForm)
    RadioGroupType: TRadioGroup;
    GroupBox1: TGroupBox;
    CheckBoxEtapeDepart: TCheckBox;
    CheckBoxEtapeArrivee: TCheckBox;
    SpinEditEtapeDepart: TSpinEdit;
    SpinEditEtapeArrivee: TSpinEdit;
    GroupBoxLegende: TGroupBox;
    Label1: TLabel;
    LabelMax: TLabel;
    PaintBox: TPaintBox;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    LabelVehicules: TLabel;
    LabelAttenteCumulee: TLabel;
    LabelAttenteMoyenne: TLabel;
    LabelAttenteMaximale: TLabel;
    LabelTours: TLabel;
    LabelTraficCumule: TLabel;
    LabelTraficMoyen: TLabel;
    LabelTraficMaximal: TLabel;
    procedure FormResize(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure PaintBoxPaint(Sender: TObject);
    procedure RadioGroupTypeClick(Sender: TObject);
    procedure ParametresEtapeClick(Sender: TObject);
    procedure SpinEditEtapeChanged(Sender: TObject;
      NewValue: Integer);
  private
    m : Array[0..1] of Integer;
    procedure RecalculeEtVisualise;
  public
    function CouleurCase(x, y : Integer) : TColor;
    function stMsgDetailCase(x, y : Integer) : string;
  end;

var
  frmStatsAttenteTrafic: TfrmStatsAttenteTrafic;

implementation

uses Math, simul, simul_f;

{$R *.xfm}

const ATTENTE = 0;
      TRAFIC = 1;
      
procedure TfrmStatsAttenteTrafic.FormResize(Sender: TObject);
var h, w : Integer;
begin
 h:=GroupBoxLegende.Top+GroupBoxLegende.Height+5;
 w:=Max( LabelTours.Left+LabelTours.Width+9,
         LabelVehicules.Left+LabelVehicules.Width+9);
 if Height<>h then Height:=h;
 if Width<>w then Width:=w;
end;

procedure TfrmStatsAttenteTrafic.FormShow(Sender: TObject);
begin
 FormResize(Self);
 if cv.TourCrt>0 then
  Caption:='Statistiques de fluidité et de trafic au tour n°'+IntToStr(cv.TourCrt);
 SpinEditEtapeDepart.Max:=cv.NbEtapes;
 SpinEditEtapeArrivee.Max:=cv.NbEtapes;
 RecalculeEtVisualise;
end;


procedure TfrmStatsAttenteTrafic.PaintBoxPaint(Sender: TObject);
var i : Integer;
begin
for i:=0 to 127 do
 begin
 if i<64 then
  PaintBox.Canvas.Pen.Color:=4*i+256*252
 else
  PaintBox.Canvas.Pen.Color:=252+256*(252-4*(i-64));
 PaintBox.Canvas.MoveTo(i, 0);
 PaintBox.Canvas.LineTo(i, PaintBox.Height-1);
 end;
end;

function TfrmStatsAttenteTrafic.CouleurCase(x, y : Integer) : TColor;
var s, ed, ea, ts : Integer;
begin
 if CheckBoxEtapeDepart.Checked then ed:=SpinEditEtapeDepart.Value else ed:=0;
 if CheckBoxEtapeArrivee.Checked then ea:=SpinEditEtapeArrivee.Value else ea:=0;
 ts:=RadioGroupType.ItemIndex;
 if (m[ts]>0) and
    (cv.v[x, y].Trafic<>nil) and
    (cv.v[x, y].Attente<>nil) then // v3.0
  begin
  if ts>0 then
   s:=(127*cv.v[x,y].Trafic[ed,ea]) div m[ts]
  else
   s:=(127*cv.v[x,y].Attente[ed,ea]) div m[ts];
  if s<64 then
   Result:=4*s+256*252
  else
   Result:=252+256*(252-4*(s-64));
  end
 else Result:=0;
end;

function TfrmStatsAttenteTrafic.stMsgDetailCase(x, y : Integer) : string;
var stMsg : string;
    ed, ea, ts : Integer;
begin // v3.0
 if CheckBoxEtapeDepart.Checked then ed:=SpinEditEtapeDepart.Value else ed:=0;
 if CheckBoxEtapeArrivee.Checked then ea:=SpinEditEtapeArrivee.Value else ea:=0;
 ts:=RadioGroupType.ItemIndex;
 if (m[ts]>0) and
    (cv.v[x, y].Trafic<>nil) and   // v3.0
    (cv.v[x, y].Attente<>nil) then // v3.0
  if ts>0 then
   stMsg:=Format( 'Trafic en (%d, %d) au tour %d : %d véhicules (Max. %d) soit %.3f%%',
                  [x, y, cv.TourCrt, cv.v[x, y].Trafic[ed, ea], m[ts], (100.0*cv.v[x, y].Trafic[ed, ea])/m[ts]])
  else
   stMsg:=Format( 'Attente en (%d, %d) au tour %d : %d véhicules (Max. %d) soit %.3f%%',
                  [x, y, cv.TourCrt, cv.v[x, y].Attente[ed, ea], m[ts], (100.0*cv.v[x, y].Attente[ed, ea])/m[ts]]);
 Result:=stMsg;
end;

procedure TfrmStatsAttenteTrafic.RecalculeEtVisualise;
var x, y, n, ed, ea : Integer;
    t : Array [0..1] of Integer;
    v : pVoie;
begin
 n:=0; t[0]:=0; t[1]:=0;
 if CheckBoxEtapeDepart.Checked then ed:=SpinEditEtapeDepart.Value else ed:=0;
 if CheckBoxEtapeArrivee.Checked then ea:=SpinEditEtapeArrivee.Value else ea:=0;
 if (ed<0) or (ed>cv.NbEtapes) or (ea<0) or (ea>cv.NbEtapes) then
  begin
  Application.MessageBox('Le n° d''étape est incorrect !', 'Valeur incorrecte', [smbOk], smsWarning);
  Exit;
  end;
 m[0]:=0; m[1]:=0;
 for x:=0 to NBX-1 do
  for y:=0 to NBY-1 do
   begin
   v:=@(cv.v[x,y]);
   if (v.DirPoss>aucune) and (v.NumEtape=0) then
    begin
    Inc(n);
    if v.Attente[ed,ea]>m[ATTENTE] then m[ATTENTE]:=v.Attente[ed,ea];
    Inc(t[ATTENTE], v.Attente[ed,ea]);
    if v.Trafic[ed,ea]>m[TRAFIC] then m[TRAFIC]:=v.Trafic[ed,ea];
    Inc(t[TRAFIC], v.Trafic[ed,ea]);
    end;
   end;
 LabelMax.Caption:=IntToStr(m[RadioGroupType.ItemIndex]);
 LabelAttenteCumulee.Caption:=IntToStr(t[ATTENTE]);
 if n>0 then
  LabelAttenteMoyenne.Caption:=Format('%.1f', [t[ATTENTE]/n])
 else
  LabelAttenteMoyenne.Caption:='N/D';
 LabelAttenteMaximale.Caption:=IntToStr(m[ATTENTE]);
 LabelTraficCumule.Caption:=IntToStr(t[TRAFIC]);
 if n>0 then
  LabelTraficMoyen.Caption:=Format('%.1f', [t[TRAFIC]/n])
 else
  LabelTraficMoyen.Caption:='N/D';
 LabelTraficMaximal.Caption:=IntToStr(m[TRAFIC]);
 frmSimulation.DrawGridSimul.Repaint;
end;


procedure TfrmStatsAttenteTrafic.RadioGroupTypeClick(
  Sender: TObject);
begin
 LabelMax.Caption:=IntToStr(m[RadioGroupType.ItemIndex]);
 frmSimulation.DrawGridSimul.Repaint;
end;

procedure TfrmStatsAttenteTrafic.ParametresEtapeClick(
  Sender: TObject);
begin
 case (Sender as TComponent).Tag of
  1: begin
     SpinEditEtapeDepart.Enabled:=CheckBoxEtapeDepart.Checked;
     if SpinEditEtapeDepart.Enabled then SpinEditEtapeDepart.SetFocus;
     end;
  2: begin
     SpinEditEtapeArrivee.Enabled:=CheckBoxEtapeArrivee.Checked;
     if SpinEditEtapeArrivee.Enabled then SpinEditEtapeArrivee.SetFocus;
     end;
  end{case of};
  RecalculeEtVisualise;
end;

procedure TfrmStatsAttenteTrafic.SpinEditEtapeChanged(
  Sender: TObject; NewValue: Integer);
begin
 case (Sender as TComponent).Tag of
  1: begin
     SpinEditEtapeDepart.Enabled:=CheckBoxEtapeDepart.Checked;
     if SpinEditEtapeDepart.Enabled then SpinEditEtapeDepart.SetFocus;
     end;
  2: begin
     SpinEditEtapeArrivee.Enabled:=CheckBoxEtapeArrivee.Checked;
     if SpinEditEtapeArrivee.Enabled then SpinEditEtapeArrivee.SetFocus;
     end;
  end{case of};
  RecalculeEtVisualise;
end;

end.
