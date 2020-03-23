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

unit prmsim_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls, QButtons, QExtCtrls, QComCtrls;

type
  TfrmParamSimul = class(TForm)
    GroupBoxElements: TGroupBox;
    EditNbFeuxMax: TEdit;
    LabelNbFeuxMax: TLabel;
    LabelNbEtapesMax: TLabel;
    EditNbEtapesMax: TEdit;
    LabelNbVehicules: TLabel;
    EditNbVehicules: TEdit;
    LabelNbPietons: TLabel;
    EditNbPietons: TEdit;
    Label5: TLabel;
    Label6: TLabel;
    ButtonOk: TButton;
    ButtonAnnuler: TButton;
    ButtonAppliquer: TButton;
    GroupBox1: TGroupBox;
    LabelDureeVert: TLabel;
    EditDureeVert: TEdit;
    Label8: TLabel;
    LabelDureeOrange: TLabel;
    EditDureeOrange: TEdit;
    LabelDureeRouge: TLabel;
    EditDureeRouge: TEdit;
    BitBtnAppliqueDureeFeuVert: TBitBtn;
    BitBtnAppliqueDureeFeuRouge: TBitBtn;
    EditAttenteAvChx: TEdit;
    LabelAttenteAvChx: TLabel;
    EditNbToursParSeconde: TEdit;
    LabelNbToursParSeconde: TLabel;
    RadioGroupVitesses: TRadioGroup;
    GroupBoxPietons: TGroupBox;
    LabelNbCasesMaxPsgPtn: TLabel;
    EditNbCasesMaxPsgPtn: TEdit;
    Label14: TLabel;
    LabelProbaPsgPt: TLabel;
    EditProbaPsgPt: TEdit;
    Label16: TLabel;
    Label17: TLabel;
    LabelNbArretsBus: TLabel;
    EditNbArretsBus: TEdit;
    BitBtnDefLignesBus: TBitBtn;
    procedure FormCreate(Sender: TObject);
    procedure ButtonOkClick(Sender: TObject);
    procedure ButtonAppliquerClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure BitBtnDefLignesBusClick(Sender: TObject);
    procedure EditChange(Sender: TObject);
    procedure RadioGroupVitessesClick(Sender: TObject);
    procedure BitBtnAppliqueDureeFeuVertClick(Sender: TObject);
    procedure BitBtnAppliqueDureeFeuRougeClick(Sender: TObject);
    procedure EditDureeVertChange(Sender: TObject);
    procedure EditDureeRougeChange(Sender: TObject);
    procedure EditNbArretsBusChange(Sender: TObject);
  private
    IncrementVehicules : Integer;
    NbMin, NbMax : Array [0..10] of Integer;
    Initialisation : Boolean;
    Edit : array [0..4] of TEdit;
    function NbElementsCorrect : Boolean;
    function AppliqueChoix : Boolean;
  public
    { Public declarations }
  end;

var
  frmParamSimul: TfrmParamSimul;

procedure Parametres;

implementation

uses simul_f, simul, prmbus_f;

{$R *.xfm}

const NbElementsMinDef : array [0..11] of Integer = (  0,  2,  120,  0,  0,  0,  0,  0,  0,  1,  0,   0);
      NbElementsMaxDef : array [0..11] of Integer = (100, 32, 1000, 50, 81, 10, 10, 10, 99, 10, 10, 100);
      NbElementsDef    : array [0..11] of Integer = ( 30,  4,  120, 25,  0,  5,  1,  5, 10,  2,  5,  50);
      // v3.0.4
      stNbElements : array [0..4] of String = ('Nombre de feux', 'Nombre d''étapes', 'Nombre de véhicules', 'Nombre de piétons', 'Nombre d''arrêts de bus');
      stMsgValeurIncorrecte : array [0..2] of String = ( #13#10' - %s incorrect.'#13#10'Vous devez entrer un nombre entier compris entre %d et %d.',
                                                         #13#10' - %s incorrect.'#13#10'Vous devez entrer un nombre entier supérieur à %d.',
                                                         #13#10' - %s incorrect.'#13#10'Vous devez entrer un nombre entier inférieur à %d.');
//----------------------------------------------------------------------------
procedure Parametres;
 begin
  frmParamSimul:=TfrmParamSimul.Create(frmSimulation);
  try
   frmParamSimul.ShowModal;
  finally
   frmParamSimul.Release;
   frmParamSimul:=nil;
  end;
 end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.FormCreate(Sender: TObject);
var i : Integer;
begin
 IncrementVehicules:=1;
 for i:=0 to 10 do
  begin
  NbMin[i]:=NbElementsMinDef[i];
  NbMax[i]:=NbElementsMaxDef[i];
  end;
 Edit[0]:=EditNbFeuxMax;
 Edit[1]:=EditNbEtapesMax;
 Edit[2]:=EditNbVehicules;
 Edit[3]:=EditNbPietons;
 Edit[4]:=EditNbArretsBus;
end;
//----------------------------------------------------------------------------
function TfrmParamSimul.NbElementsCorrect : Boolean;
var Valeur,
    i,
    NbEtapes,
    NbMinVehicules,
    NbMaxVehicules,
    NbVehicules : Integer;
    stMsg : String;
 begin
 for i:=0 to 4 do
  try
   if not Initialisation and (i=1) then
    begin
     NbEtapes:=StrToInt(EditNbEtapesMax.Text);
     NbMinVehicules:=NbEtapes*(NbEtapes-1);
     NbMaxVehicules:=(1000 div (NbEtapes*(NbEtapes-1)))*NbEtapes*(NbEtapes-1);
     NbVehicules:=(NBMAXETAPES div NbEtapes)*NbMinVehicules;
     NbMin[2]:=NbMinVehicules;
     IncrementVehicules:=NbMinVehicules;
     NbMax[2]:=NbMaxVehicules;
     if NbMaxVehicules<NbVehicules then
      EditNbVehicules.Text:=IntToStr(NbMaxVehicules);
    end;
   Valeur:=StrToInt(Edit[i].Text);
   if (Valeur<NbMin[i]) then
    begin
    stMsg:=stMsg+Format( stMsgValeurIncorrecte[1],
                         [stNbElements[i], NbMin[i]]);
    Edit[i].Text:=IntToStr(NbMin[i]);
    end;
   if (Valeur>NbMax[i]) then
    begin
    stMsg:=stMsg+Format( stMsgValeurIncorrecte[2],
                         [stNbElements[i], NbMax[i]]);
    Edit[i].Text:=IntToStr(NbMax[i]);
    end;
   if (i=2) and // Si Véhicules ALORS
     (Valeur mod IncrementVehicules<>0) then // Le nombre doit être divisible par IncrementVehicules
    EditNbVehicules.Text:=IntToStr(IncrementVehicules*(Valeur div IncrementVehicules));
  except
   stMsg:=stMsg+Format( stMsgValeurIncorrecte[0],
                        [stNbElements[i], NbMin[i], NbMax[i]]);
   Edit[i].Text:=IntToStr(NbElementsDef[i]);
  end{try};
  if stMsg<>'' then
   begin
    Application.MessageBox(pChar('Une ou plusieurs erreurs ont été détectée(s) :'+stMsg), 'Paramètres incorrects', [smbOk], smsWarning);
    Result:=false;
   end
  else
   Result:=true;
 end;
//----------------------------------------------------------------------------
function TfrmParamSimul.AppliqueChoix : Boolean;
 begin
  if not NbElementsCorrect then
   begin
   Result:=false;
   Exit;
   end;
  frmSimulation.SimulModifiee:=true;
  // v3.0.4. On n'alloue pas maintenant les véhicules et les piétons
  cv.DefinitNbVehicules(StrToInt(EditNbVehicules.Text), DEFINIT_SEULEMENT);
  cv.DefinitNbPietons((StrToInt(EditNbPietons.Text)*StrToInt(EditNbVehicules.Text)) div 100, DEFINIT_SEULEMENT);
  cv.DefinitNbFeux(StrToInt(EditNbFeuxMax.Text));
  cv.DefinitNbEtapes(StrToInt(EditNbEtapesMax.Text));
  cv.DefinitNbArretsBus(StrToInt(EditNbArretsBus.Text)); // v3.0
  BitBtnDefLignesBus.Enabled:=(cv.NbArretsBus>0); // v3.0

  cv.DureeVert:=StrToInt(EditDureeVert.Text);
  cv.DureeOrange:=StrToInt(EditDureeOrange.Text);
  cv.DureeRouge:=StrToInt(EditDureeRouge.Text);
  cv.AttenteMaxVeh:=StrToInt(EditAttenteAvChx.Text);
  cv.NbToursParSeconde:=StrToInt(EditNbToursParSeconde.Text);
  cv.NbVitesses:=RadioGroupVitesses.ItemIndex+1;
  cv.NbMaxCasesDetectPsgPt:=StrToInt(EditNbCasesMaxPsgPtn.Text);
  cv.ProbaDirPsgPt:=StrToInt(EditProbaPsgPt.Text);

  frmSimulation.DrawGridSimul.Repaint;
  ButtonAppliquer.Enabled:=false;

  BitBtnAppliqueDureeFeuVert.Enabled:=true;
  BitBtnAppliqueDureeFeuRouge.Enabled:=true;
  Result:=true;
 end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.ButtonOkClick(Sender: TObject);
begin
 if AppliqueChoix then
  ButtonOk.ModalResult:=mrOk
 else
  ButtonOk.ModalResult:=mrNone;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.ButtonAppliquerClick(Sender: TObject);
begin
 AppliqueChoix;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.FormShow(Sender: TObject);
begin
 FormResize(self);
 Initialisation:=true;
 if cv.NbVehicules>0 then
  EditNbVehicules.Text:=IntToStr(cv.NbVehicules)
 else
  cv.DefinitNbVehicules(StrToInt(EditNbVehicules.Text), DEFINIT_SEULEMENT); // v3.0.4. On n'alloue pas maintenant

 EditNbPietons.Text:=IntToStr((100*cv.NbPietons) div cv.NbVehicules);
 EditNbFeuxMax.Text:=IntToStr(cv.NbFeux);
 if cv.NbEtapes>0 then
  EditNbEtapesMax.Text:=IntToStr(cv.NbEtapes)
 else
  cv.DefinitNbEtapes(StrToInt(EditNbEtapesMax.Text));

 if cv.NbArretsBus>0 then // v3.0
  EditNbArretsBus.Text:=IntToStr(cv.NbArretsBus)
 else
  if StrToInt(EditNbArretsBus.Text)>0 then
   cv.DefinitNbArretsBus(StrToInt(EditNbArretsBus.Text));

 BitBtnDefLignesBus.Enabled:=(cv.NbArretsBus>0); // v3.0

 if cv.DureeVert>0 then
  EditDureeVert.Text:=IntToStr(cv.DureeVert)
 else
  cv.DureeVert:=StrToInt(EditDureeVert.Text);
 if cv.DureeOrange>0 then
  EditDureeOrange.Text:=IntToStr(cv.DureeOrange)
 else
  cv.DureeOrange:=StrToInt(EditDureeOrange.Text);
 if cv.DureeRouge>0 then
  EditDureeRouge.Text:=IntToStr(cv.DureeRouge)
 else
  cv.DureeRouge:=StrToInt(EditDureeRouge.Text);

 EditAttenteAvChx.Text:=IntToStr(cv.AttenteMaxVeh);

 if cv.NbToursParSeconde>0 then
  EditNbToursParSeconde.Text:=IntToStr(cv.NbToursParSeconde)
 else
  cv.NbToursParSeconde:=StrToInt(EditNbToursParSeconde.Text);

 RadioGroupVitesses.ItemIndex:=cv.NbVitesses-1;
 EditNbCasesMaxPsgPtn.Text:=IntToStr(cv.NbMaxCasesDetectPsgPt);
 EditProbaPsgPt.Text:=IntToStr(cv.ProbaDirPsgPt);

 LabelNbFeuxMax.Enabled:=(cv.TourCrt=0);
 EditNbFeuxMax.Enabled:=(cv.TourCrt=0);
 LabelNbEtapesMax.Enabled:=not cv.DistancesCalculees and (cv.TourCrt=0);
 EditNbEtapesMax.Enabled:=not cv.DistancesCalculees and (cv.TourCrt=0);
 LabelNbVehicules.Enabled:=(cv.TourCrt=0);
 EditNbVehicules.Enabled:=(cv.TourCrt=0);
 LabelNbPietons.Enabled:=(cv.TourCrt=0);
 EditNbPietons.Enabled:=(cv.TourCrt=0);
 LabelNbArretsBus.Enabled:=not cv.DistancesCalculees and (cv.TourCrt=0); // v3.0
 EditNbArretsBus.Enabled:=not cv.DistancesCalculees and (cv.TourCrt=0); // v3.0
 LabelDureeVert.Enabled:=not frmSimulation.SimulationEnCours;
 LabelDureeOrange.Enabled:=not frmSimulation.SimulationEnCours;
 LabelDureeRouge.Enabled:=not frmSimulation.SimulationEnCours;
 EditDureeVert.Enabled:=not frmSimulation.SimulationEnCours;
 EditDureeOrange.Enabled:=not frmSimulation.SimulationEnCours;
 EditDureeRouge.Enabled:=not frmSimulation.SimulationEnCours;
 BitBtnAppliqueDureeFeuVert.Enabled:=not frmSimulation.SimulationEnCours;
 BitBtnAppliqueDureeFeuRouge.Enabled:=not frmSimulation.SimulationEnCours;
 LabelAttenteAvChx.Enabled:=not frmSimulation.SimulationEnCours;
 EditAttenteAvChx.Enabled:=not frmSimulation.SimulationEnCours;
 LabelNbToursParSeconde.Enabled:=not frmSimulation.SimulationEnCours;
 EditNbToursParSeconde.Enabled:=not frmSimulation.SimulationEnCours;
 RadioGroupVitesses.Enabled:=not frmSimulation.SimulationEnCours;
 LabelNbCasesMaxPsgPtn.Enabled:=not frmSimulation.SimulationEnCours;
 LabelProbaPsgPt.Enabled:=not frmSimulation.SimulationEnCours;
 EditNbCasesMaxPsgPtn.Enabled:=not frmSimulation.SimulationEnCours;
 EditProbaPsgPt.Enabled:=not frmSimulation.SimulationEnCours;
 Initialisation:=false;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.FormResize(Sender: TObject);
var h, w : Integer;
begin
h:=GroupBox1.Height+GroupBox1.Top+13;
w:=GroupBox1.Width+GroupBox1.Left+11;
if Height<>h then Height:=h;
if Width<>w then Width:=w;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.BitBtnDefLignesBusClick(Sender: TObject);
begin
 frmParamBus:=TfrmParamBus.Create(self);
 try
  frmParamSimul.Hide;
  frmParamBus.ShowModal;
 finally
  frmSimulation.DrawGridSimul.Repaint;
  frmParamSimul.Show;
  frmParamBus.Release;
  frmParamBus:=nil;
 end;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.EditChange(Sender: TObject);
begin
 if not Initialisation then
  ButtonAppliquer.Enabled:=true;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.RadioGroupVitessesClick(Sender: TObject);
begin
 if not Initialisation then
  ButtonAppliquer.Enabled:=true;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.BitBtnAppliqueDureeFeuVertClick(Sender: TObject);
var i : Integer;
begin
 for i:=0 to cv.NbFeux-1 do
  if cv.Feux[i].Defini then cv.Feux[i].DureeVert:=cv.DureeVert;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.BitBtnAppliqueDureeFeuRougeClick(Sender: TObject);
var i : Integer;
begin
 for i:=0 to cv.NbFeux-1 do
  if cv.Feux[i].Defini then cv.Feux[i].DureeRouge:=cv.DureeRouge;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.EditDureeVertChange(Sender: TObject);
begin
 if not Initialisation then
  ButtonAppliquer.Enabled:=true;
 BitBtnAppliqueDureeFeuVert.Enabled:=false;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.EditDureeRougeChange(Sender: TObject);
begin
 if not Initialisation then
  ButtonAppliquer.Enabled:=true;
 BitBtnAppliqueDureeFeuRouge.Enabled:=false;
end;
//----------------------------------------------------------------------------
procedure TfrmParamSimul.EditNbArretsBusChange(Sender: TObject);
begin
 if not Initialisation then
  begin
  ButtonAppliquer.Enabled:=true;
  BitBtnDefLignesBus.Enabled:=false;
  end;
end;

end.
