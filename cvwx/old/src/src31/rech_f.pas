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

unit rech_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls, QComCtrls, QExtCtrls;

type
  TfrmRecherche = class(TForm)
    RadioButtonCoordonnees: TRadioButton;
    RadioButtonEtape: TRadioButton;
    RadioButtonFeu: TRadioButton;
    RadioButtonVehicule: TRadioButton;
    RadioButtonPieton: TRadioButton;
    ButtonAnnuler: TButton;
    SpinEditX: TSpinEdit;
    SpinEditY: TSpinEdit;
    SpinEditEtape: TSpinEdit;
    SpinEditFeu: TSpinEdit;
    SpinEditVehicule: TSpinEdit;
    SpinEditPieton: TSpinEdit;
    StatusBar: TStatusBar;
    RadioButtonBus: TRadioButton;
    SpinEditBus: TSpinEdit;
    RadioButtonArretBus: TRadioButton;
    SpinEditArretBus: TSpinEdit;
    procedure ButtonAnnulerClick(Sender: TObject);
    procedure RadioButtonClick(Sender: TObject);
    procedure FormHide(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure SpinEditXChanged(Sender: TObject; NewValue: Integer);
    procedure SpinEditYChanged(Sender: TObject; NewValue: Integer);
    procedure SpinEditEtapeChanged(Sender: TObject; NewValue: Integer);
    procedure SpinEditFeuChanged(Sender: TObject; NewValue: Integer);
    procedure SpinEditVehiculeChanged(Sender: TObject; NewValue: Integer);
    procedure SpinEditPietonChanged(Sender: TObject; NewValue: Integer);
    procedure FormResize(Sender: TObject);
    procedure SpinEditBusChanged(Sender: TObject; NewValue: Integer);
    procedure SpinEditArretBusChanged(Sender: TObject; NewValue: Integer);
  private
    xPrc, yPrc : Integer;
    procedure RafraichitAffichage;
  public
    { Public declarations }
  end;

var
  frmRecherche: TfrmRecherche;

implementation

uses math, simul_f, simul;

{$R *.xfm}

const stValeurIncorrecte = 'Valeur incorrecte';
      stMsgNombreEntier = 'Vous devez entrer un nombre entier.';

procedure TfrmRecherche.ButtonAnnulerClick(Sender: TObject);
begin
 Close;
end;

procedure TfrmRecherche.RafraichitAffichage;
 begin
  SpinEditX.Enabled:=RadioButtonCoordonnees.Checked;
  SpinEditY.Enabled:=RadioButtonCoordonnees.Checked;
  SpinEditEtape.Enabled:=RadioButtonEtape.Checked;
  SpinEditFeu.Enabled:=RadioButtonFeu.Checked;
  SpinEditVehicule.Enabled:=RadioButtonVehicule.Checked;
  SpinEditPieton.Enabled:=RadioButtonPieton.Checked;
  SpinEditBus.Enabled:=RadioButtonBus.Checked; // v3.0
  SpinEditArretBus.Enabled:=RadioButtonArretBus.Checked; // v3.0
  case   Ord(RadioButtonCoordonnees.Checked)+
       2*Ord(RadioButtonEtape.Checked)+
       3*Ord(RadioButtonFeu.Checked)+
       4*Ord(RadioButtonVehicule.Checked)+
       5*Ord(RadioButtonPieton.Checked)+
       6*Ord(RadioButtonBus.Checked)+// v3.0
       7*Ord(RadioButtonArretBus.Checked) of // v3.0
    1: begin
       SpinEditX.SetFocus;
       SpinEditXChanged(SpinEditX, SpinEditX.Value);
       SpinEditYChanged(SpinEditY, SpinEditY.Value);
       end;
    2: begin
       SpinEditEtape.SetFocus;
       SpinEditEtapeChanged(SpinEditEtape, SpinEditEtape.Value);
       end;
    3: begin
       SpinEditFeu.SetFocus;
       SpinEditFeuChanged(SpinEditFeu, SpinEditFeu.Value);
       end;
    4: begin
       SpinEditVehicule.SetFocus;
       SpinEditVehiculeChanged(SpinEditVehicule, SpinEditVehicule.Value);
       end;
    5: begin
       SpinEditPieton.SetFocus;
       SpinEditPietonChanged(SpinEditPieton, SpinEditPieton.Value);
       end;
    6: begin // v3.0
       SpinEditBus.SetFocus;
       SpinEditBusChanged(SpinEditBus, SpinEditBus.Value);
       end;
    7: begin // v3.0
       SpinEditArretBus.SetFocus;
       SpinEditArretBusChanged(SpinEditArretBus, SpinEditArretBus.Value);
       end;
  end{case of};
 end;

procedure TfrmRecherche.FormHide(Sender: TObject);
begin
 frmSimulation.ToolButtonRecherche.Down:=false;
 frmSimulation.RubriqueRecherche.Checked:=false;
end;

procedure TfrmRecherche.RadioButtonClick(Sender: TObject);
begin
 RafraichitAffichage;
end;


procedure TfrmRecherche.FormShow(Sender: TObject);
var i, x, y : Integer;
    v : pVoie;
begin
 FormResize(Self);
 x:=frmSimulation.DrawGridSimul.Col;
 y:=frmSimulation.DrawGridSimul.Row;
 v:=@(cv.v[x, y]);
 frmSimulation.ToolButtonRecherche.Down:=true;
 frmSimulation.RubriqueRecherche.Checked:=true;
 xPrc:=x;
 yPrc:=y;
 SpinEditX.Value:=x;
 SpinEditY.Value:=y;
 if v.NumEtape>0 then SpinEditEtape.Value:=v.NumEtape;
 i:=0; while (v.NumFeu[i]=0) and (i<NBDIRS) do Inc(i);
 if i<NBDIRS then SpinEditFeu.Value:=v.NumFeu[i];
 if v.NumVehicule>0 then SpinEditVehicule.Value:=v.NumVehicule;
 if v.NbPietons>0 then
  if v.NumPieton[0]>0 then
   SpinEditPieton.Value:=v.NumPieton[0]
  else
   SpinEditPieton.Value:=v.NumPieton[1];
 if v.NumBus>0 then SpinEditBus.Value:=v.NumBus; // v3.0
 if v.NumArretBus>0 then SpinEditArretBus.Value:=v.NumArretBus; // v3.0
 SpinEditEtape.Max:=cv.NbEtapes;
 RadioButtonFeu.Enabled:=(cv.NbFeux>0); // v3.0.4
 if cv.NbFeux>0 then SpinEditFeu.Max:=cv.NbFeux; // v3.0.4
 SpinEditVehicule.Max:=cv.NbVehicules;
 RadioButtonPieton.Enabled:=(cv.NbPietons>0); // v3.0.4
 if cv.NbPietons>0 then SpinEditPieton.Max:=cv.NbPietons; // v3.0.4
 RadioButtonBus.Enabled:=(cv.NbBus>0); // v3.0.4
 if cv.NbBus>0 then SpinEditBus.Max:=cv.NbBus; // v3.0.4
 RadioButtonArretBus.Enabled:=(cv.NbArretsBus>0); // v3.0.4
 if cv.NbArretsBus>0 then SpinEditArretBus.Max:=cv.NbArretsBus; // v3.0.4
end;

procedure TfrmRecherche.SpinEditXChanged(Sender: TObject;
  NewValue: Integer);
begin
 frmSimulation.DrawGridSimul.Col:=SpinEditX.Value;
end;

procedure TfrmRecherche.SpinEditYChanged(Sender: TObject;
  NewValue: Integer);
begin
 frmSimulation.DrawGridSimul.Row:=SpinEditY.Value;
end;

procedure TfrmRecherche.SpinEditEtapeChanged(Sender: TObject;
  NewValue: Integer);
var e : pEtape;
begin
if (cv=nil) or (NewValue<1) or (NewValue>cv.NbEtapes) then
 begin
 StatusBar.SimpleText:='Aucune étape définie ou numéro incorrect';
 Exit;
 end;
e:=@(cv.Etapes[NewValue-1]);
if e.Definie then
 begin
 frmSimulation.DrawGridSimul.Col:=e.x;
 frmSimulation.DrawGridSimul.Row:=e.y;
 StatusBar.SimpleText:=Format('Etape n°%d trouvée en (%d, %d)', [NewValue, e.x, e.y]);
 end
else
 StatusBar.SimpleText:=Format('Etape n°%d non utilisée', [NewValue, e.x, e.y]);
end;

procedure TfrmRecherche.SpinEditFeuChanged(Sender: TObject;
  NewValue: Integer);
var f : pFeu;
begin
if (cv=nil) or (NewValue<1) or (NewValue>cv.NbFeux) then
 begin
 StatusBar.SimpleText:='Aucun feu défini ou numéro incorrect';
 Exit;
 end;
f:=@(cv.Feux[NewValue-1]);
if f.Defini then
 begin
 frmSimulation.DrawGridSimul.Col:=f.x;
 frmSimulation.DrawGridSimul.Row:=f.y;
 StatusBar.SimpleText:=Format('Feu n°%d trouvé en (%d, %d)', [NewValue, f.x, f.y]);
 end
else
 StatusBar.SimpleText:=Format('Feu n°%d non utilisé', [NewValue]);
end;


procedure TfrmRecherche.SpinEditVehiculeChanged(Sender: TObject;
  NewValue: Integer);
var veh : pVehicule;
begin
if (cv=nil) or (NewValue<1) or (NewValue>cv.NbVehicules) then
 begin
 StatusBar.SimpleText:='Aucun véhicule défini ou numéro incorrect';
 Exit;
 end;
veh:=@(cv.Vehicules[NewValue-1]);
if veh.Defini then
 begin
 frmSimulation.DrawGridSimul.Col:=veh.x;
 frmSimulation.DrawGridSimul.Row:=veh.y;
 StatusBar.SimpleText:=Format('Véhicule n°%d trouvé en (%d, %d)', [NewValue, veh.x, veh.y]);
 end
else
 StatusBar.SimpleText:=Format('Véhicule n°%d non utilisé', [NewValue]);
end;

procedure TfrmRecherche.SpinEditPietonChanged(Sender: TObject;
  NewValue: Integer);
var p : pPieton;
begin
if (cv=nil) or (NewValue<1) or (NewValue>cv.NbPietons) then
 begin
 StatusBar.SimpleText:='Aucun piéton défini ou numéro incorrect';
 Exit;
 end;
p:=@(cv.Pietons[NewValue-1]);
if p.Defini then
 begin
 frmSimulation.DrawGridSimul.Col:=p.x;
 frmSimulation.DrawGridSimul.Row:=p.y;
 StatusBar.SimpleText:=Format('Piéton n°%d trouvé en (%d, %d)', [NewValue, p.x, p.y]);
 end
else
 if p.NumBus>0 then
  begin
   frmSimulation.DrawGridSimul.Col:=cv.Autobus[p.NumBus-1].x;
   frmSimulation.DrawGridSimul.Row:=cv.Autobus[p.NumBus-1].y;
   StatusBar.SimpleText:=Format( 'Piéton n°%d trouvé dans le bus n°%d (%d, %d)',
                                 [ NewValue,
                                   p.Numbus,
                                   cv.Autobus[p.NumBus-1].x,
                                   cv.Autobus[p.NumBus-1].y]);
  end
 else
  StatusBar.SimpleText:=Format('Piéton n°%d non utilisé', [NewValue]);
end;

procedure TfrmRecherche.FormResize(Sender: TObject);
var h, w : Integer;
begin
 h:=StatusBar.Height+
    Max( ButtonAnnuler.Top+ButtonAnnuler.Height+5,
    Max( SpinEditArretBus.Top+SpinEditArretBus.Height+7,
         RadioButtonArretBus.Top+RadioButtonArretBus.Height+9));
 w:=Max( SpinEditY.Left+SpinEditY.Width+4,
         ButtonAnnuler.Left+ButtonAnnuler.Width+5);

 if Height<>h then Height:=h;
 if Width<>w then Width:=w;
end;

procedure TfrmRecherche.SpinEditBusChanged(Sender: TObject;
  NewValue: Integer);
var b : pBus;
begin // v3.0
if (cv=nil) or (NewValue<1) or (NewValue>cv.NbBus) then
 begin
 StatusBar.SimpleText:='Aucun bus défini ou numéro incorrect';
 Exit;
 end;
b:=@(cv.Autobus[NewValue-1]);
if b.Defini then
 begin
 frmSimulation.DrawGridSimul.Col:=b.x;
 frmSimulation.DrawGridSimul.Row:=b.y;
 StatusBar.SimpleText:=Format('Bus n°%d trouvé en (%d, %d)', [NewValue, b.x, b.y]);
 end
else
 StatusBar.SimpleText:=Format('Bus n°%d au dépôt', [NewValue]);
end;

procedure TfrmRecherche.SpinEditArretBusChanged(Sender: TObject;
  NewValue: Integer);
var ab : pArretBus;
begin // v3.0
if (cv=nil) or (NewValue<1) or (NewValue>cv.NbArretsBus) then
 begin
 StatusBar.SimpleText:='Aucun arrêt de bus défini ou numéro incorrect';
 Exit;
 end;
ab:=@(cv.ArretsBus[NewValue-1]);
if ab.Defini then
 begin
 frmSimulation.DrawGridSimul.Col:=ab.x;
 frmSimulation.DrawGridSimul.Row:=ab.y;
 StatusBar.SimpleText:=Format('Arrêt de bus n°%d trouvé en (%d, %d)', [NewValue, ab.x, ab.y]);
 end
else // Normalement pas possible car TOUS les arrêts de bus doivent être définis avant de lancer la simulation
 StatusBar.SimpleText:=Format('Arrêt de bus %n°d non utilisé', [NewValue]);
end;

end.


