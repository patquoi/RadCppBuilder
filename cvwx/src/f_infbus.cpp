//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_infbus.h"
#include "f_simul.h"
#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
// Pour asFrmNumeroCoordonnees
#define NXY 0
#define DRN 1
#define SVT 2
//---------------------------------------------------------------------------
TfrmInfosBus *frmInfosBus;
//---------------------------------------------------------------------------
const AnsiString asDebutTitreCadreBus="                           ",
                 asFrmNumeroCoordonnees[3]={ "%d (%2.2d, %2.2d)",
                                             "%d (%2.2d, %2.2d)  jusqu'au tour %d",
                                             "%d (%2.2d, %2.2d) depuis le tour %d"},
                 asFrmCoordonnees="%2.2d, %2.2d",
                 asFrmPourcentage="%.3f%%",
                 asFrmVitesse="%d/%d";
//---------------------------------------------------------------------------
__fastcall TfrmInfosBus::TfrmInfosBus(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmInfosBus::RendreVisibleInfos(bool ARendreVisible)
 {
  int i;
  GroupBoxBus->Caption=asDebutTitreCadreBus;
  if (ARendreVisible)
   {
    RadioButtonBusNumero->Checked=true;
    GroupBoxBus->Caption= GroupBoxBus->Caption+
                               Format( asFrmNumeroCoordonnees[NXY],
                                       ARRAYOFCONST((v->NumBus, Bus->x, Bus->y)))+
                               " ";
   }
  else
   RadioButtonAucunBus->Checked=true;
  RadioButtonBusNumero->Enabled=ARendreVisible;
  RadioButtonAucunBus->Enabled=!ARendreVisible;
  for(i=1; i<17; i++)
   ((TLabel*)FindComponent("Label"+IntToStr(i)))->Enabled=ARendreVisible;
  LabelDirection->Visible=ARendreVisible;
  LabelNumeroLigne->Visible=ARendreVisible;
  LabelTourSortie->Visible=ARendreVisible;
  LabelNbPersonnes->Visible=ARendreVisible;
  LabelDernierArret->Visible=ARendreVisible;
  LabelProchainArret->Visible=ARendreVisible;
  LabelTours->Visible=ARendreVisible;
  LabelParcours->Visible=ARendreVisible;
  LabelToursEntreArrets->Visible=ARendreVisible;
  LabelParcoursEntreArrets->Visible=ARendreVisible;
  LabelDistance->Visible=ARendreVisible;
  LabelDistanceMin->Visible=ARendreVisible;
  LabelParcoursEffectue->Visible=ARendreVisible;
  LabelDetour->Visible=ARendreVisible;
  LabelAttente->Visible=ARendreVisible;
  LabelVitesse->Visible=ARendreVisible;
 }
//---------------------------------------------------------------------------
void TfrmInfosBus::RafraichitInfos()
 {
  int i,
      NbTours,
      NumDrnArret,
      NumArretSvt,
      NbDirPoss,
      DejaParcouru,
      ResteAParcourir,
      DistMin;
  voie *DrnArret;
  bool Afficher;
  x=frmSimulation->DrawGridSimul->Col;
  y=frmSimulation->DrawGridSimul->Row;
  v=&(cv->v[x][y]);
  Bus=NULL;
  LabelCoordonnees->Caption=Format(asFrmCoordonnees, ARRAYOFCONST((x, y)));
  if ((Afficher=(v->NumBus>0)))
   {
    Bus=cv->Bus+v->NumBus-1;
    LabelDirection->Caption=asDir[Bus->Dir];
    LabelNumeroLigne->Caption=IntToStr(Bus->NumLigne); // v3.5 : un oubli !!!
    if ((NumDrnArret=Bus->NumDrnArret))
     {
      LabelDernierArret->Caption=Format( asFrmNumeroCoordonnees[DRN],
                                         ARRAYOFCONST(( NumDrnArret,
                                                        cv->ArretBus[NumDrnArret-1].x,
                                                        cv->ArretBus[NumDrnArret-1].y,
                                                        (int)Bus->TourArriveDrnArret)));
      DrnArret=&(cv->v[cv->ArretBus[NumDrnArret-1].x][cv->ArretBus[NumDrnArret-1].y]);
     }
    else
     { // Si pas encore d'arrêt... On prend le dépôt comme dernier arrêt
      LabelDernierArret->Caption=Format( asFrmNumeroCoordonnees[DRN],
                                         ARRAYOFCONST(( 0,
                                                        cv->DepotBus.x,
                                                        cv->DepotBus.y,
                                                        (int)Bus->TourDepart)));
      DrnArret=&(cv->v[cv->DepotBus.x][cv->DepotBus.y]);
     }
    LabelProchainArret->Caption=Format( asFrmNumeroCoordonnees[SVT],
                                        ARRAYOFCONST(( NumArretSvt=Bus->NumArretSvt,
                                                       cv->ArretBus[NumArretSvt-1].x,
                                                       cv->ArretBus[NumArretSvt-1].y,
                                                       (int)cv->Bus->TourDepartArretSvt)));
    LabelTourSortie->Caption=IntToStr(Bus->TourDepart);
    LabelNbPersonnes->Caption=IntToStr(Bus->NbPersonnes);
    LabelTours->Caption=IntToStr(cv->TourCrt-Bus->TourDepart);
    LabelParcours->Caption=IntToStr(Bus->NbCasesParcourues);
    LabelToursEntreArrets->Caption=IntToStr(NbTours=cv->TourCrt-Bus->TourArriveDrnArret);
    LabelParcoursEntreArrets->Caption=IntToStr(DejaParcouru=Bus->NbCasesParcouruesDepuisDrnArret);
    LabelDistance->Caption=IntToStr(ResteAParcourir=v->DistArretBus[NumArretSvt-1][NumDirdp[Bus->Dir][v->DirPoss]]);
    NbDirPoss=NbDir[DrnArret->DirPoss];
    for(i=0, DistMin=DIST_INDEFINIE; i<NbDirPoss; i++)
     DistMin=min(DistMin, DrnArret->DistArretBus[NumArretSvt-1][i]);
	LabelDistanceMin->Caption=IntToStr(DistMin);
	// v1.8.4 : FormatFloat au lieu de Format
	LabelParcoursEffectue->Caption=FormatFloat(asFrmPourcentage, (100.0*DejaParcouru)/(DejaParcouru+ResteAParcourir));
	LabelDetour->Caption=FormatFloat(asFrmPourcentage, (100.0*(DejaParcouru+ResteAParcourir))/DistMin-100.0);
	if (NbTours)
	 LabelAttente->Caption=FormatFloat(asFrmPourcentage, (100.0*(NbTours-DejaParcouru))/NbTours);
    else
     LabelAttente->Caption="0,000%";
    LabelVitesse->Caption=Format(asFrmVitesse, ARRAYOFCONST((1, cv->NbVitesses)));
   }
  RendreVisibleInfos(Afficher);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmInfosBus::FormShow(TObject *Sender)
{
 frmSimulation->ActionDetailBus->Checked=true;
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosBus::FormHide(TObject *Sender)
{
 frmSimulation->ActionDetailBus->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosBus::ButtonOkClick(TObject *Sender)
{
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosBus::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------

void __fastcall TfrmInfosBus::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

