//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_infveh.h"
#include "f_simul.h"
#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmInfosVehicule *frmInfosVehicule;
//---------------------------------------------------------------------------
const AnsiString asDebutTitreCadreVehicule="                           ",
                 asFrmNumeroCoordonnees="%d (%2.2d, %2.2d)",
                 asFrmCoordonnees="%2.2d, %2.2d",
                 asFrmPourcentage="%.3f%%", // v3.0
                 asFrmVitesse="%d/%d",
                 asNiveauPriorite[NBNIVEAUXPRIORITE]={"Normal", "Urgences", "Police"},
                 asDepartArrivee[2]={"de départ","d'arrivée"}, // v5.0
                 asFrmFileParking[2]={"Parking %s :","File Parking %s"}; // v5.0
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
  for(i=3; i<14; i++) // v5.0 : i=3 au lieu de i=1
   ((TLabel*)FindComponent("Label"+IntToStr(i)))->Enabled=ARendreVisible;
  LabelDepart->Visible=ARendreVisible; // v5.0
  LabelArrivee->Visible=ARendreVisible;// v5.0
  LabelDirection->Visible=ARendreVisible;
  LabelNivPriorite->Visible=ARendreVisible;
  LabelParkingDepart->Visible=ARendreVisible;
  LabelParkingArrivee->Visible=ARendreVisible;
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
      NumParkingDepart, NumParkingArrivee,
      NumFileParkDepart, NumFileParkArrivee, // v5.0
      NbDirPoss;
  bool Prioritaire;
  int DejaParcouru,
      ResteAParcourir,
      DistMin;
  voie *CaseDepart; // v5.0 : ATTENTION, le type de parking peut être souterrain ou extérieur !
  bool Afficher;
  x=frmSimulation->DrawGridSimul->Col;
  y=frmSimulation->DrawGridSimul->Row;
  v=&(cv->v[x][y]);
  Veh=NULL;
  LabelCoordonnees->Caption=Format(asFrmCoordonnees, ARRAYOFCONST((x, y)));
  if (Afficher=(v->NumVehicule>0))
   {
    Veh=cv->Vehicule+v->NumVehicule-1;
    NumParkingDepart=Veh->NumParkingDepart;     // v5.0
    NumParkingArrivee=Veh->NumParkingArrivee;   // v5.0
    NumFileParkDepart=Veh->NumFileParkDepart;   // v5.0
    NumFileParkArrivee=Veh->NumFileParkArrivee; // v5.0
    Prioritaire=(Veh->NivPriorite>normal);
    LabelDirection->Caption=asDir[Veh->Dir];

    LabelNivPriorite->Caption=asNiveauPriorite[Veh->NivPriorite];
    LabelNivPriorite->Font->Color=CouleurNiveauPriorite[Veh->NivPriorite];

    if (NumFileParkDepart) // v5.0
     {
      LabelDepart->Caption=Format( asFrmFileParking[FILEPARK], ARRAYOFCONST((asDepartArrivee[DEPART])));
      LabelParkingDepart->Caption=Format( asFrmNumeroCoordonnees,
                                          ARRAYOFCONST(( NumFileParkDepart,
                                                         cv->PlacePark[cv->FilePark[NumFileParkDepart-1].NumPlaceQueue].x,
                                                         cv->PlacePark[cv->FilePark[NumFileParkDepart-1].NumPlaceQueue].y)));
     }
    else
     {
      LabelDepart->Caption=Format( asFrmFileParking[PARKING], ARRAYOFCONST((asDepartArrivee[DEPART])));
      LabelParkingDepart->Caption=Format( asFrmNumeroCoordonnees,
                                          ARRAYOFCONST(( NumParkingDepart,
                                                         cv->Parking[NumParkingDepart-1].x,
                                                         cv->Parking[NumParkingDepart-1].y)));
     }

    if (NumFileParkArrivee) // v5.0
     {
      LabelArrivee->Caption=Format( asFrmFileParking[FILEPARK], ARRAYOFCONST((asDepartArrivee[ARRIVEE])));
      LabelParkingArrivee->Caption=Format( asFrmNumeroCoordonnees,
                                          ARRAYOFCONST(( NumFileParkArrivee,
                                                         cv->PlacePark[cv->FilePark[NumFileParkArrivee-1].NumPlaceQueue].x,
                                                         cv->PlacePark[cv->FilePark[NumFileParkArrivee-1].NumPlaceQueue].y)));
     }
    else
     {
      LabelArrivee->Caption=Format( asFrmFileParking[PARKING], ARRAYOFCONST((asDepartArrivee[ARRIVEE])));
      LabelParkingArrivee->Caption=Format( asFrmNumeroCoordonnees,
                                          ARRAYOFCONST(( NumParkingArrivee,
                                                         cv->Parking[NumParkingArrivee-1].x,
                                                         cv->Parking[NumParkingArrivee-1].y)));
     }

    LabelTourSortie->Caption=IntToStr(Veh->TourDepart);
    LabelTours->Caption=IntToStr(NbTours=cv->TourCrt-Veh->TourDepart);
    LabelParcours->Caption=IntToStr(DejaParcouru=Veh->NbCasesParcourues);
    if (NumParkingArrivee) // v5.0
     LabelDistance->Caption=IntToStr(ResteAParcourir=v->DistParking[NumParkingArrivee-1][NumDirdp[Veh->Dir][v->DirPoss]][Prioritaire]); // v3.5
    if (NumParkingDepart) // v5.0
      CaseDepart=&(cv->v[cv->Parking[NumParkingDepart-1].x][cv->Parking[NumParkingDepart-1].y]);
    if (NumFileParkArrivee) // v5.0
      LabelDistance->Caption=IntToStr(ResteAParcourir=v->DistFilePark[NumFileParkArrivee-1][NumDirdp[Veh->Dir][v->DirPoss]][Prioritaire]); // v3.5
    if (NumFileParkDepart) // v5.0
      CaseDepart=&(cv->v[cv->PlacePark[cv->FilePark[NumFileParkDepart-1].NumPlaceQueue].x]
                           [cv->PlacePark[cv->FilePark[NumFileParkDepart-1].NumPlaceQueue].y]);
    NbDirPoss=NbDir[CaseDepart->DirPoss];
    if (NumFileParkArrivee) // v5.0
     for(i=0, DistMin=DIST_INDEFINIE; i<NbDirPoss; i++)
      DistMin=min(DistMin, CaseDepart->DistFilePark[NumFileParkArrivee-1][i][Prioritaire]); // v5.0
    if (NumParkingArrivee)
     for(i=0, DistMin=DIST_INDEFINIE; i<NbDirPoss; i++)
      DistMin=min(DistMin, CaseDepart->DistParking[NumParkingArrivee-1][i][Prioritaire]); // v3.5
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

void __fastcall TfrmInfosVehicule::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

