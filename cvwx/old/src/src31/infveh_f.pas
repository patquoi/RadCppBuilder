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

unit infveh_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls, simul;

type
  TfrmInfosVehicule = class(TForm)
    Label1: TLabel;
    LabelCoordonnees: TLabel;
    RadioButtonAucunVehicule: TRadioButton;
    RadioButtonVehiculeNumero: TRadioButton;
    GroupBoxVehicule: TGroupBox;
    Label2: TLabel;
    LabelDirection: TLabel;
    Label3: TLabel;
    LabelNivPriorite: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    LabelEtapeDepart: TLabel;
    LabelEtapeArrivee: TLabel;
    LabelTourSortie: TLabel;
    LabelTours: TLabel;
    LabelParcours: TLabel;
    LabelDistance: TLabel;
    LabelDistanceMin: TLabel;
    LabelParcoursEffectue: TLabel;
    LabelDetour: TLabel;
    LabelAttente: TLabel;
    LabelVitesse: TLabel;
    ButtonOk: TButton;
    procedure FormShow(Sender: TObject);
    procedure FormHide(Sender: TObject);
    procedure ButtonOkClick(Sender: TObject);
    procedure FormResize(Sender: TObject);
  private
    v : pVoie;
    Veh : pVehicule;
    x, y : Integer;
    procedure RendreVisibleInfos(ARendreVisible : Boolean);
  public
    procedure RafraichitInfos;
  end;

var
  frmInfosVehicule: TfrmInfosVehicule;

implementation

uses Math, simul_f;

{$R *.xfm}

const stDebutTitreCadreVehicule='                         ';
      stFrmNumeroCoordonnees='%d (%2.2d, %2.2d)';
      stFrmCoordonnees='%2.2d, %2.2d';
      stFrmPourcentage='%.3f%%'; // v3.0
      stFrmVitesse='%d/%d';

      stNiveauPriorite : array [0..NBNIVEAUXPRIORITE-1] of String = ('Normal', 'Urgences', 'Police');
      CouleurNiveauPriorite : array [0..NBNIVEAUXPRIORITE-1] of TColor = (clBlack, clRed, clBlue);

procedure TfrmInfosVehicule.FormShow(Sender: TObject);
begin
 FormResize(self);
 frmSimulation.ToolButtonInfosVehicule.Down:=true;
 frmSimulation.RubriqueInfosVehicule.Checked:=true;
 RafraichitInfos;
end;

procedure TfrmInfosVehicule.FormHide(Sender: TObject);
begin
 frmSimulation.ToolButtonInfosVehicule.Down:=false;
 frmSimulation.RubriqueInfosVehicule.Checked:=false;
end;

procedure TfrmInfosVehicule.ButtonOkClick(Sender: TObject);
begin
 Hide;
end;

procedure TfrmInfosVehicule.RendreVisibleInfos(ARendreVisible : Boolean);
var i : Integer;
 begin
  GroupBoxVehicule.Caption:=stDebutTitreCadreVehicule;
  if ARendreVisible then
   begin
    RadioButtonVehiculeNumero.Checked:=true;
    GroupBoxVehicule.Caption:= GroupBoxVehicule.Caption+
                               Format( stFrmNumeroCoordonnees,
                                       [v.NumVehicule, Veh.x, Veh.y]);
   end
  else
   RadioButtonAucunVehicule.Checked:=true;
  RadioButtonVehiculeNumero.Enabled:=ARendreVisible;
  RadioButtonAucunVehicule.Enabled:=not ARendreVisible;
  for i:=2 to 14 do
   (FindComponent('Label'+IntToStr(i)) as TLabel).Enabled:=ARendreVisible;
  LabelDirection.Visible:=ARendreVisible;
  LabelNivPriorite.Visible:=ARendreVisible;
  LabelEtapeDepart.Visible:=ARendreVisible;
  LabelEtapeArrivee.Visible:=ARendreVisible;
  LabelTourSortie.Visible:=ARendreVisible;
  LabelTours.Visible:=ARendreVisible;
  LabelParcours.Visible:=ARendreVisible;
  LabelDistance.Visible:=ARendreVisible;
  LabelDistanceMin.Visible:=ARendreVisible;
  LabelParcoursEffectue.Visible:=ARendreVisible;
  LabelDetour.Visible:=ARendreVisible;
  LabelAttente.Visible:=ARendreVisible;
  LabelVitesse.Visible:=ARendreVisible;
 end;

procedure TfrmInfosVehicule.RafraichitInfos;
var i,
    NbTours,
    NumEtapeDepart,
    NumEtapeArrivee,
    NbDirPoss,
    DejaParcouru,
    ResteAParcourir,
    DistMin : Integer;
    EtapeDepart : pVoie;
    Afficher : Boolean;
 begin
  x:=frmSimulation.DrawGridSimul.Col;
  y:=frmSimulation.DrawGridSimul.Row;
  v:=@(cv.v[x][y]);
  Veh:=nil;
  LabelCoordonnees.Caption:=Format(stFrmCoordonnees, [x, y]);
  Afficher:=(v.NumVehicule>0);
  if Afficher then
   begin
    Veh:=@(cv.Vehicules[v.NumVehicule-1]);
    NumEtapeDepart:=Veh.NumEtapeDepart;
    NumEtapeArrivee:=Veh.NumEtapeArrivee;
    NbTours:=cv.TourCrt-Veh.TourDepart;
    DejaParcouru:=Veh.NbCasesParcourues;
    ResteAParcourir:=v.DistEtape[NumEtapeArrivee-1, NumDirdp[Veh.Dir, v.DirPoss]];
    LabelDirection.Caption:=stDir[Veh.Dir];

    LabelNivPriorite.Caption:=stNiveauPriorite[Integer(Veh.NivPriorite)];
    LabelNivPriorite.Font.Color:=CouleurNiveauPriorite[Integer(Veh.NivPriorite)];

    LabelEtapeDepart.Caption:=Format( stFrmNumeroCoordonnees,
                                      [ NumEtapeDepart,
                                        cv.Etapes[NumEtapeDepart-1].x,
                                        cv.Etapes[NumEtapeDepart-1].y]);
    LabelEtapeArrivee.Caption:=Format( stFrmNumeroCoordonnees,
                                       [ NumEtapeArrivee,
                                         cv.Etapes[NumEtapeArrivee-1].x,
                                         cv.Etapes[NumEtapeArrivee-1].y]);
    LabelTourSortie.Caption:=IntToStr(Veh.TourDepart);
    LabelTours.Caption:=IntToStr(NbTours);
    LabelParcours.Caption:=IntToStr(DejaParcouru);
    LabelDistance.Caption:=IntToStr(ResteAParcourir);
    EtapeDepart:=@(cv.v[cv.Etapes[NumEtapeDepart-1].x, cv.Etapes[NumEtapeDepart-1].y]);
    NbDirPoss:=NbDir[EtapeDepart.DirPoss];
    DistMin:=DIST_INDEFINIE;
    for i:=0 to NbDirPoss-1 do
     DistMin:=min(DistMin, EtapeDepart.DistEtape[NumEtapeArrivee-1, i]);
    LabelDistanceMin.Caption:=IntToStr(DistMin);
    LabelParcoursEffectue.Caption:=Format(stFrmPourcentage, [(100.0*DejaParcouru)/(DejaParcouru+ResteAParcourir)]);
    LabelDetour.Caption:=Format(stFrmPourcentage, [(100.0*(DejaParcouru+ResteAParcourir))/DistMin-100.0]);
    if NbTours>0 then
     LabelAttente.Caption:=Format(stFrmPourcentage, [(100.0*(NbTours-DejaParcouru))/NbTours])
    else
     LabelAttente.Caption:='0,00%';
    LabelVitesse.Caption:=Format(stFrmVitesse, [1+(v.NumVehicule-1) mod cv.NbVitesses, cv.NbVitesses]);
   end;
  RendreVisibleInfos(Afficher);
 end;


procedure TfrmInfosVehicule.FormResize(Sender: TObject);
var h, w : Integer;
begin
 LabelCoordonnees.Left:=Label1.Width+Label1.Left+7;
 w:=2*GroupBoxVehicule.Left+GroupBoxVehicule.Width;
 h:=ButtonOk.Height+ButtonOk.Top+9;
 if Height<>h then Height:=h;
 if Width<>w then Width:=w;
end;

end.
