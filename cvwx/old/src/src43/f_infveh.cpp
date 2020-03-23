//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_infveh.h"
#include "f_simul.h"
#include "winlinux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
TfrmInfosVehicule *frmInfosVehicule;
//---------------------------------------------------------------------------
const AnsiString asDebutTitreCadreVehicule="                           ",
                 asFrmNumeroCoordonnees="%d (%2.2d, %2.2d)",
                 asFrmCoordonnees="%2.2d, %2.2d",
                 asFrmPourcentage="%.3f%%", // v3.0
                 asFrmVitesse="%d/%d",
                 asNiveauPriorite[NBNIVEAUXPRIORITE]={"Normal", "Urgences", "Police"};
//---------------------------------------------------------------------------
const TColor CouleurNiveauPriorite[NBNIVEAUXPRIORITE]={clBlack, clRed, clBlue};
//---------------------------------------------------------------------------
__fastcall TfrmInfosVehicule::TfrmInfosVehicule(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmInfosVehicule::RendreVisibleInfos(bool ARendreVisible)
 {
  int i;
  GroupBoxVehicule->Caption=asDebutTitreCadreVehicule;
  if (ARendreVisible)
   {
    RadioButtonVehiculeNumero->Checked=true;
    GroupBoxVehicule->Caption= GroupBoxVehicule->Caption+
                               Format( asFrmNumeroCoordonnees,
                                       ARRAYOFCONST((v->NumVehicule, Veh->x, Veh->y)))+
                               " ";
   }
  else
   RadioButtonAucunVehicule->Checked=true;
  RadioButtonVehiculeNumero->Enabled=ARendreVisible;
  RadioButtonAucunVehicule->Enabled=!ARendreVisible;
  for(i=1; i<14; i++)
   ((TLabel*)FindComponent("Label"+IntToStr(i)))->Enabled=ARendreVisible;
  LabelDirection->Visible=ARendreVisible;
  LabelNivPriorite->Visible=ARendreVisible;
  LabelEtapeDepart->Visible=ARendreVisible;
  LabelEtapeArrivee->Visible=ARendreVisible;
  LabelTourSortie->Visible=ARendreVisible;
  LabelTours->Visible=ARendreVisible;
  LabelParcours->Visible=ARendreVisible;
  LabelDistance->Visible=ARendreVisible;
  LabelDistanceMin->Visible=ARendreVisible;
  LabelParcoursEffectue->Visible=ARendreVisible;
  LabelDetour->Visible=ARendreVisible;
  LabelAttente->Visible=ARendreVisible;
  LabelVitesse->Visible=ARendreVisible;
 }
//---------------------------------------------------------------------------
void TfrmInfosVehicule::RafraichitInfos()
 {
  int i,
      NbTours,
      NumEtapeDepart,
      NumEtapeArrivee,
      NbDirPoss;
  bool Prioritaire;
  int DejaParcouru,
      ResteAParcourir,
      DistMin;
  voie *EtapeDepart;
  bool Afficher;
  x=frmSimulation->DrawGridSimul->Col;
  y=frmSimulation->DrawGridSimul->Row;
  v=&(cv->v[x][y]);
  Veh=NULL;
  LabelCoordonnees->Caption=Format(asFrmCoordonnees, ARRAYOFCONST((x, y)));
  if (Afficher=(v->NumVehicule>0))
   {
    Veh=cv->Vehicule+v->NumVehicule-1;
    Prioritaire=(Veh->NivPriorite>normal);
    LabelDirection->Caption=asDir[Veh->Dir];

    LabelNivPriorite->Caption=asNiveauPriorite[Veh->NivPriorite];
    LabelNivPriorite->Font->Color=CouleurNiveauPriorite[Veh->NivPriorite];

    LabelEtapeDepart->Caption=Format( asFrmNumeroCoordonnees,
                                      ARRAYOFCONST(( NumEtapeDepart=Veh->NumEtapeDepart,
                                                     cv->Etape[NumEtapeDepart-1].x,
                                                     cv->Etape[NumEtapeDepart-1].y)));
    LabelEtapeArrivee->Caption=Format( asFrmNumeroCoordonnees,
                                       ARRAYOFCONST(( NumEtapeArrivee=Veh->NumEtapeArrivee,
                                                      cv->Etape[NumEtapeArrivee-1].x,
                                                      cv->Etape[NumEtapeArrivee-1].y)));
    LabelTourSortie->Caption=IntToStr(Veh->TourDepart);
    LabelTours->Caption=IntToStr(NbTours=cv->TourCrt-Veh->TourDepart);
    LabelParcours->Caption=IntToStr(DejaParcouru=Veh->NbCasesParcourues);
    LabelDistance->Caption=IntToStr(ResteAParcourir=v->DistEtape[NumEtapeArrivee-1][NumDirdp[Veh->Dir][v->DirPoss]][Prioritaire]); // v3.5
    EtapeDepart=&(cv->v[cv->Etape[NumEtapeDepart-1].x][cv->Etape[NumEtapeDepart-1].y]);
    NbDirPoss=NbDir[EtapeDepart->DirPoss];
    for(i=0, DistMin=DIST_INDEFINIE; i<NbDirPoss; i++)
     DistMin=min(DistMin, EtapeDepart->DistEtape[NumEtapeArrivee-1][i][Prioritaire]); // v3.5
    LabelDistanceMin->Caption=IntToStr(DistMin);
    LabelParcoursEffectue->Caption=Format(asFrmPourcentage, ARRAYOFCONST(((100.0*DejaParcouru)/(DejaParcouru+ResteAParcourir))));
    LabelDetour->Caption=Format(asFrmPourcentage, ARRAYOFCONST(((100.0*(DejaParcouru+ResteAParcourir))/DistMin-100.0)));
    if (NbTours)
     LabelAttente->Caption=Format(asFrmPourcentage, ARRAYOFCONST(((100.0*(NbTours-DejaParcouru))/NbTours)));
    else
     LabelAttente->Caption="0,000%";
    LabelVitesse->Caption=Format(asFrmVitesse, ARRAYOFCONST((1+(v->NumVehicule-1)%cv->NbVitesses, cv->NbVitesses)));
   }
  RendreVisibleInfos(Afficher);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmInfosVehicule::FormShow(TObject *Sender)
{
 frmSimulation->ActionDetailVehicule->Checked=true;
#ifdef CV_LINUX
 FormResize(this);
#endif
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosVehicule::FormHide(TObject *Sender)
{
 frmSimulation->ActionDetailVehicule->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosVehicule::ButtonOkClick(TObject *Sender)
{
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosVehicule::ButtonAideClick(TObject *Sender)
{ // v3.0
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosVehicule::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=XMAX(GroupBoxVehicule)+LH_ESPACE,
     h=HMAX(ButtonOk,ButtonAide)+LH_ESPACE;
 if (!RedimensionnementEnCours)
  if ((Width!=l)||(Height!=h))
   {
    RedimensionnementEnCours=true;
    if (Width!=l) Width=l;
    if (Height!=h) Height=h;
    RedimensionnementEnCours=false;
   }
#endif
}
//---------------------------------------------------------------------------

