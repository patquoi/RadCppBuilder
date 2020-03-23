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

unit stats_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QExtCtrls;

type
  TfrmStatistiques = class(TForm)
    PaintBoxStats: TPaintBox;
    procedure PaintBoxStatsPaint(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormHide(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmStatistiques: TfrmStatistiques;

implementation

uses simul_f, simul;

{$R *.xfm}

procedure TfrmStatistiques.FormShow(Sender: TObject);
begin
 frmSimulation.ToolButtonAffStatsEvol.Down:=true;
 frmSimulation.RubriqueStatistiquesEvolution.Checked:=true;
end;

procedure TfrmStatistiques.FormHide(Sender: TObject);
begin
 frmSimulation.ToolButtonAffStatsEvol.Down:=false;
 frmSimulation.RubriqueStatistiquesEvolution.Checked:=false;
end;

procedure TfrmStatistiques.FormCreate(Sender: TObject);
begin
 PaintBoxStats.Canvas.Pen.Style:=psSolid;
 PaintBoxStats.Canvas.Pen.Mode:=pmCopy;
 PaintBoxStats.Canvas.Pen.Width:=1;
end;

procedure TfrmStatistiques.PaintBoxStatsPaint(Sender: TObject);
var ParNbVehicules : Boolean;
    i, j, x, y,
    NbTours, DrnTour, PrmTour,
    NbVehicules, NbMarques,
    dt, xMax, yMax, NbRestants : Integer;
begin
 if not frmSimulation.SimulationEnCours then Exit;
 ParNbVehicules:=(cv.TypeStats=par_nombre);
 NbTours:=cv.NbToursStats;
 DrnTour:=cv.TourCrt;
 if DrnTour<NbTours then
  PrmTour:=0
 else
  PrmTour:=(DrnTour-NbTours+1);
 NbVehicules:=cv.NbVehicules;
 if ParNbVehicules then
  NbMarques:=NbVehicules div 10
 else
  NbMarques:=10;
 dt:=1+9*Ord(NbTours>=100);
 xMax:=PaintBoxStats.Width;
 yMax:=PaintBoxStats.Height;

 // 1. Affichage du quadrillage
 if cv.QuadrillageStats then
  for i:=0  to NbTours div dt-1 do
   for j:=0 to NbMarques-1 do
    begin
     x:=dt*xMax*i div NbTours;
     if ParNbVehicules then
      y:=10*yMax*j div NbVehicules
     else
      y:=10*yMax*j div 100;
     if (i mod 10) and (j mod 10)>0 then
      PaintBoxStats.Canvas.Pen.Color:=clGray
     else
      PaintBoxStats.Canvas.Pen.Color:=clWhite;
     PaintBoxStats.Canvas.Rectangle(x-1, yMax-y-1, x+1, yMax-y+1);
    end;

 // 2. Affichage des véhicules
 if xMax and yMax>0 then
  begin
   PaintBoxStats.Canvas.Pen.Color:=clRed; // Arrivés = Rouges
   PaintBoxStats.Canvas.MoveTo(0, yMax-yMax*cv.StatsCV[PrmTour mod NbTours].NbVehiculesArrives div NbVehicules);
   for i:=0 to DrnTour-PrmTour do
    PaintBoxStats.Canvas.LineTo(xMax*i div NbTours, yMax-yMax*cv.StatsCV[(PrmTour+i) mod NbTours].NbVehiculesArrives div NbVehicules);

   PaintBoxStats.Canvas.Pen.Color:=clYellow; // Sortis = Jaunes
   PaintBoxStats.Canvas.MoveTo(0, yMax-yMax*cv.StatsCV[PrmTour mod NbTours].NbVehiculesSortis div NbVehicules);
   for i:=0 to DrnTour-PrmTour do
    PaintBoxStats.Canvas.LineTo(xMax*i div NbTours, yMax-yMax*cv.StatsCV[(PrmTour+i) mod NbTours].NbVehiculesSortis div NbVehicules);

   PaintBoxStats.Canvas.Pen.Color:=clGreen; // Deplaces = Verts
   if ParNbVehicules then
    NbRestants:=NbVehicules
   else
    NbRestants:=(cv.StatsCV[PrmTour mod NbTours].NbVehiculesSortis-cv.StatsCV[PrmTour mod NbTours].NbVehiculesArrives);
   if NbRestants=0 then NbRestants:=100;
   PaintBoxStats.Canvas.MoveTo(0, yMax-yMax*cv.StatsCV[PrmTour mod NbTours].NbVehiculesDeplaces div NbRestants);
   for i:=0 to DrnTour-PrmTour do
    begin
     if ParNbVehicules then
      NbRestants:=NbVehicules
     else
     NbRestants:=(cv.StatsCV[(PrmTour+i) mod NbTours].NbVehiculesSortis-cv.StatsCV[(PrmTour+i) mod NbTours].NbVehiculesArrives);
     if NbRestants=0 then NbRestants:=100;
     PaintBoxStats.Canvas.LineTo(xMax*i div NbTours, yMax-yMax*cv.StatsCV[(PrmTour+i) mod NbTours].NbVehiculesDeplaces div NbRestants);
    end;
  end;
end;


end.
