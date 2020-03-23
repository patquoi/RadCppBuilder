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

unit infbus_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls, simul;

const NXY = 0;
      DRN = 1;
      SVT = 2;

      stDebutTitreCadreBus = '                 ';
      stFrmNumeroCoordonnees : array[0..2] of String = ( '%d (%2.2d, %2.2d)',
                                                         '%d (%2.2d, %2.2d)  jusqu''au tour %d',
                                                         '%d (%2.2d, %2.2d) depuis le tour %d');
     stFrmCoordonnees = '%2.2d, %2.2d';
     stFrmPourcentage = '%.3f%%';
     stFrmVitesse = '%d/%d';

type
  TfrmInfosBus = class(TForm)
    Label1: TLabel;
    LabelCoordonnees: TLabel;
    RadioButtonAucunBus: TRadioButton;
    GroupBoxBus: TGroupBox;
    Label2: TLabel;
    LabelDirection: TLabel;
    Label3: TLabel;
    LabelNumeroLigne: TLabel;
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
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    LabelDernierArret: TLabel;
    LabelProchainArret: TLabel;
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
    RadioButtonBusNumero: TRadioButton;
    Label21: TLabel;
    Label20: TLabel;
    LabelNbPersonnes: TLabel;
    LabelToursEntreArrets: TLabel;
    LabelParcoursEntreArrets: TLabel;
    procedure FormShow(Sender: TObject);
    procedure FormHide(Sender: TObject);
    procedure ButtonOkClick(Sender: TObject);
    procedure FormResize(Sender: TObject);
  private
    x, y : Integer;
    v : pVoie;
    b : pBus;
    procedure RendreVisibleInfos(ARendreVisible : Boolean);
  public
    procedure RafraichitInfos;
  end;

var
  frmInfosBus: TfrmInfosBus;

implementation

uses Math, simul_f;

{$R *.xfm}

procedure TfrmInfosBus.RendreVisibleInfos(ARendreVisible : Boolean);
var i : Integer;
 begin
  GroupBoxBus.Caption:=stDebutTitreCadreBus;
  if ARendreVisible then
   begin
    RadioButtonBusNumero.Checked:=true;
    GroupBoxBus.Caption:= GroupBoxBus.Caption+
                               Format( stFrmNumeroCoordonnees[NXY],
                                       [v.NumBus, b.x, b.y]);
   end
  else
   RadioButtonAucunBus.Checked:=true;
  RadioButtonBusNumero.Enabled:=ARendreVisible;
  RadioButtonAucunBus.Enabled:=not ARendreVisible;
  for i:=2 to 17 do
   (FindComponent('Label'+IntToStr(i)) as TLabel).Enabled:=ARendreVisible;
  LabelDirection.Visible:=ARendreVisible;
  LabelNumeroLigne.Visible:=ARendreVisible;
  LabelTourSortie.Visible:=ARendreVisible;
  LabelNbPersonnes.Visible:=ARendreVisible;
  LabelDernierArret.Visible:=ARendreVisible;
  LabelProchainArret.Visible:=ARendreVisible;
  LabelTours.Visible:=ARendreVisible;
  LabelParcours.Visible:=ARendreVisible;
  LabelToursEntreArrets.Visible:=ARendreVisible;
  LabelParcoursEntreArrets.Visible:=ARendreVisible;
  LabelDistance.Visible:=ARendreVisible;
  LabelDistanceMin.Visible:=ARendreVisible;
  LabelParcoursEffectue.Visible:=ARendreVisible;
  LabelDetour.Visible:=ARendreVisible;
  LabelAttente.Visible:=ARendreVisible;
  LabelVitesse.Visible:=ARendreVisible;
 end;

procedure TfrmInfosBus.RafraichitInfos;
var i,
    NbTours,
    NumDrnArret,
    NumArretSvt,
    NbDirPoss,
    DejaParcouru,
    ResteAParcourir,
    DistMin : Integer;
    DrnArret : pVoie;
    Afficher : Boolean;
 begin
  x:=frmSimulation.DrawGridSimul.Col;
  y:=frmSimulation.DrawGridSimul.Row;
  v:=@(cv.v[x][y]);
  b:=nil;
  LabelCoordonnees.Caption:=Format(stFrmCoordonnees, [x, y]);
  Afficher:=(v.NumBus>0);
  if Afficher then
   begin
    b:=@(cv.Autobus[v.NumBus-1]);
    LabelDirection.Caption:=stDir[b.Dir];
    NumDrnArret:=b.NumDrnArret;
    if NumDrnArret>0 then
     begin
      LabelDernierArret.Caption:=Format( stFrmNumeroCoordonnees[DRN],
                                         [ NumDrnArret,
                                           cv.ArretsBus[NumDrnArret-1].x,
                                           cv.ArretsBus[NumDrnArret-1].y,
                                           b.TourArriveDrnArret]);
      DrnArret:=@(cv.v[cv.ArretsBus[NumDrnArret-1].x, cv.ArretsBus[NumDrnArret-1].y]);
     end
    else
     begin // Si pas encore d'arrêt, on prend le dépôt comme dernier arrêt
      LabelDernierArret.Caption:=Format( stFrmNumeroCoordonnees[DRN],
                                         [ 0,
                                           cv.DepotBus.x,
                                           cv.DepotBus.y,
                                           b.TourDepart]);
      DrnArret:=@(cv.v[cv.DepotBus.x, cv.DepotBus.y]);
     end;
    NumArretSvt:=b.NumArretSvt; 
    LabelProchainArret.Caption:=Format( stFrmNumeroCoordonnees[SVT],
                                         [ NumArretSvt,
                                           cv.ArretsBus[NumArretSvt-1].x,
                                           cv.ArretsBus[NumArretSvt-1].y,
                                           b.TourDepartArretSvt]);

    NbTours:=cv.TourCrt-b.TourArriveDrnArret;
    DejaParcouru:=b.NbCasesParcouruesDepuisDrnArret;
    ResteAParcourir:=v.DistArretBus[NumArretSvt-1, NumDirdp[b.Dir, v.DirPoss]];
    LabelTourSortie.Caption:=IntToStr(b.TourDepart);
    LabelNbPersonnes.Caption:=IntToStr(b.NbPersonnes);
    LabelTours.Caption:=IntToStr(b.NbCasesParcourues);
    LabelParcours.Caption:=IntToStr(DejaParcouru);
    LabelToursEntreArrets.Caption:=IntToStr(NbTours);
    LabelParcoursEntreArrets.Caption:=IntToStr(DejaParcouru);
    LabelDistance.Caption:=IntToStr(ResteAParcourir);
    NbDirPoss:=NbDir[DrnArret.DirPoss];
    DistMin:=DIST_INDEFINIE;
    for i:=0 to NbDirPoss-1 do
     DistMin:=min(DistMin, DrnArret.DistArretBus[NumArretSvt-1, i]);
    LabelDistanceMin.Caption:=IntToStr(DistMin);
    LabelParcoursEffectue.Caption:=Format(stFrmPourcentage, [(100.0*DejaParcouru)/(DejaParcouru+ResteAParcourir)]);
    LabelDetour.Caption:=Format(stFrmPourcentage, [(100.0*(DejaParcouru+ResteAParcourir))/DistMin-100.0]);
    if NbTours>0 then
     LabelAttente.Caption:=Format(stFrmPourcentage, [(100.0*(NbTours-DejaParcouru))/NbTours])
    else
     LabelAttente.Caption:='0,000%';
    LabelVitesse.Caption:=Format(stFrmVitesse, [1, cv.NbVitesses]);
   end{if Afficher};
  RendreVisibleInfos(Afficher);
 end;

procedure TfrmInfosBus.FormShow(Sender: TObject);
begin
 FormResize(self);
 frmSimulation.ToolButtonInfosBus.Down:=true;
 frmSimulation.RubriqueInfosBus.Checked:=true;
 RafraichitInfos;
end;

procedure TfrmInfosBus.FormHide(Sender: TObject);
begin
 frmSimulation.ToolButtonInfosBus.Down:=false;
 frmSimulation.RubriqueInfosBus.Checked:=false;
end;

procedure TfrmInfosBus.ButtonOkClick(Sender: TObject);
begin
 Hide;
end;

procedure TfrmInfosBus.FormResize(Sender: TObject);
var h, w : Integer;
begin
 LabelCoordonnees.Left:=Label1.Width+Label1.Left+7;
 w:=2*GroupBoxBus.Left+GroupBoxBus.Width;
 h:=ButtonOk.Height+ButtonOk.Top+9;
 if Height<>h then Height:=h;
 if Width<>w then Width:=w;
end;

end.
