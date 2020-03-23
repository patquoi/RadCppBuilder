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

unit infptn_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls, simul;

type
  TfrmInfosPieton = class(TForm)
    Label1: TLabel;
    LabelCoordonnees: TLabel;
    RadioButtonAucunPieton: TRadioButton;
    RadioButtonPietonNumero: TRadioButton;
    GroupBoxPieton: TGroupBox;
    Label2: TLabel;
    LabelDirection: TLabel;
    Label3: TLabel;
    LabelPosition: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    LabelSituation: TLabel;
    LabelParcours: TLabel;
    ButtonOk: TButton;
    LabelBus: TLabel;
    LabelArretBus: TLabel;
    procedure FormShow(Sender: TObject);
    procedure FormHide(Sender: TObject);
    procedure ButtonOkClick(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    v : pVoie;
    p : pPieton;
    x, y, NumPieton : Integer;
    procedure RendreVisibleInfos(ARendreVisible : Boolean);
  public
    procedure RafraichitInfos;
  end;

var
  frmInfosPieton: TfrmInfosPieton;

implementation

uses Math, simul_f, rech_f;

{$R *.xfm}

const stDebutTitreCadrePieton='                      ';
      stFrmNumeroCoordonnees='%d (%2.2d, %2.2d)';
      stFrmCoordonnees='%2.2d, %2.2d';
      stFrmPourcentage='%.3f%%'; // v3.0
      stFrmDemiCase='%.1f';

      NBPOSITIONS  = 3;
      NBSITUATIONS = 6;

      // Position
      DANSUNBUS    = 2;

      // Situations
      SEPROMENE    = 0;
      PSGPTTRV     = 1;
      ARRETBUSTRV  = 2;
      ATTENDUNBUS  = 3;
      ATTENDDSLEBUS= 4;
      DESCENDDUBUS = 5;

      stPosition : array [0..2] of String = ( 'Entrée dans la case',
                                              'Sortie de la case',
                                              'Dans un bus');
      stSituation: array [0..NBSITUATIONS-1] of String = ( 'Se promène',
                                                           'Se dirige vers un passage piétons',
                                                           'Se dirige vers un arrêt de bus',
                                                           'Attend un bus à l''arrêt de bus',
                                                           'Attend dans le bus',
                                                           'Descend au prochain arrêt');

procedure TfrmInfosPieton.FormShow(Sender: TObject);
begin
 FormResize(self);
 frmSimulation.ToolButtonInfosPieton.Down:=true;
 frmSimulation.RubriqueInfosPieton.Checked:=true;
 RafraichitInfos;
end;

procedure TfrmInfosPieton.FormHide(Sender: TObject);
begin
 frmSimulation.ToolButtonInfosPieton.Down:=false;
 frmSimulation.RubriqueInfosPieton.Checked:=false;
end;

procedure TfrmInfosPieton.ButtonOkClick(Sender: TObject);
begin
 Hide;
end;

procedure TfrmInfosPieton.RendreVisibleInfos(ARendreVisible : Boolean);
var i : Integer;
 begin
  GroupBoxPieton.Caption:=stDebutTitreCadrePieton;
  if ARendreVisible then
   begin
    RadioButtonPietonNumero.Checked:=true;
    if p.NumBus=0 then
     GroupBoxPieton.Caption:= GroupBoxPieton.Caption+
                              Format( stFrmNumeroCoordonnees,
                                      [NumPieton, p.x, p.y])
    else
     GroupBoxPieton.Caption:= GroupBoxPieton.Caption+
                              Format( stFrmNumeroCoordonnees,
                                      [NumPieton,
                                       cv.Autobus[p.NumBus-1].x,
                                       cv.Autobus[p.NumBus-1].y])
   end{if ARendreVisible}
  else
   RadioButtonAucunPieton.Checked:=true;
  RadioButtonPietonNumero.Enabled:=ARendreVisible;
  RadioButtonAucunPieton.Enabled:=not ARendreVisible;
  for i:=2 to 7 do
   (FindComponent('Label'+IntToStr(i)) as TLabel).Enabled:=ARendreVisible;
  LabelDirection.Visible:=ARendreVisible;
  LabelPosition.Visible:=ARendreVisible;
  LabelSituation.Visible:=ARendreVisible;
  LabelParcours.Visible:=ARendreVisible;
  LabelBus.Visible:=ARendreVisible;
  LabelArretBus.Visible:=ARendreVisible;
 end;

procedure TfrmInfosPieton.RafraichitInfos;
var Situation : Integer;
 begin
  Situation:=0;
  x:=frmSimulation.DrawGridSimul.Col;
  y:=frmSimulation.DrawGridSimul.Row;
  v:=@(cv.v[x][y]);
  p:=nil;
  NumPieton:=0;
  LabelCoordonnees.Caption:=Format(stFrmCoordonnees, [x, y]);
  if (frmRecherche<>nil) and
     frmRecherche.Visible and
     frmRecherche.RadioButtonPieton.Checked then
   NumPieton:=frmRecherche.SpinEditPieton.Value;
  if NumPieton=0 then // Si pas de piéton suivi, on cherche parmi ceux de la case courante
   begin
    if v.NumPieton[0]>0 then
     NumPieton:=v.NumPieton[0]
    else
     if v.NumPieton[1]>0 then
      NumPieton:=v.NumPieton[1];
   end
  else // Pieton suivi, on recherche s'il se trouve sur la case ou dans un bus
   if (v.NumPieton[0]<>NumPieton) and
      (v.NumPieton[1]<>NumPieton) and
      (v.NumBus<>cv.Pietons[NumPieton-1].NumBus) then
    begin
     if v.NumPieton[0]>0 then
      NumPieton:=v.NumPieton[0]
     else
      if v.NumPieton[1]>0 then
       NumPieton:=v.NumPieton[1];
    end;
  if NumPieton>0 then
   begin
    p:=@(cv.Pietons[NumPieton-1]);
    LabelDirection.Caption:=stDir[p.Dir];

    if p.PsgPtTrv then Situation:=PSGPTTRV;
    if p.ArretBusTrv then Situation:=ARRETBUSTRV;
    if p.AttendBus then Situation:=ATTENDUNBUS;
    if p.NumBus>0 then Situation:=ATTENDDSLEBUS;
    if p.VeutDescendre then Situation:=DESCENDDUBUS;

    LabelSituation.Caption:=stSituation[Situation];
    LabelParcours.Caption:=Format(stFrmDemiCase, [p.DemiCasesParcourues/2.0]);
    if p.NumBus>0 then
     begin
      LabelBus.Caption:=Format( stFrmNumeroCoordonnees,
                                [ p.NumBus,
                                  cv.Autobus[p.Numbus-1].x,
                                  cv.Autobus[p.Numbus-1].y]);
      LabelPosition.Caption:=stPosition[DANSUNBUS];
     end
    else
     begin
      LabelBus.Caption:='Aucun';
      LabelPosition.Caption:=stPosition[Ord(p.DemiCase>0)];
     end;
    if p.NumArretBus>0 then
     LabelArretBus.Caption:=Format( stFrmNumeroCoordonnees,
                                    [ p.NumArretBus,
                                      cv.ArretsBus[p.NumArretBus-1].x,
                                      cv.ArretsBus[p.NumArretBus-1].y])
    else
     LabelArretBus.Caption:='Aucun';
   end{if NumPieton>0};
  RendreVisibleInfos(NumPieton>0);
 end;


procedure TfrmInfosPieton.FormResize(Sender: TObject);
var h, w : Integer;
begin
 LabelCoordonnees.Left:=Label1.Width+Label1.Left+7;
 w:=2*GroupBoxPieton.Left+GroupBoxPieton.Width;
 h:=ButtonOk.Height+ButtonOk.Top+9;
 if Height<>h then Height:=h;
 if Width<>w then Width:=w;
end;

procedure TfrmInfosPieton.FormCreate(Sender: TObject);
begin
 NumPieton:=0;
end;

end.
