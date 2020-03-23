//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_infvehlib.h"
#include "f_simul.h"
#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmInfosVehlib *frmInfosVehlib;
//---------------------------------------------------------------------------
const AnsiString asDebutTitreCadreVehlib="                           ",
                 asAucune="Aucune", asNA="N/A", asNonDemarre="Non démarré",
                 asFrmNumeroCoordonnees="%d (%2.2d, %2.2d)",
                 asFrmCoordonnees="%2.2d, %2.2d",
                 asFrmPourcentage="%.3f%%",
                 asFrmVitesse="%d/%d",
                 asSituation[NBSITUATIONSTAXI]={"En attente","Départ d'une course","Dépôt de client(s)","Retour d'une course"};
//---------------------------------------------------------------------------
__fastcall TfrmInfosVehlib::TfrmInfosVehlib(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmInfosVehlib::RendreVisibleInfos(bool ARendreVisible)
 {
  int i;
  GroupBoxVehlib->Caption=asDebutTitreCadreVehlib;
  if (ARendreVisible)
   {
    RadioButtonVehlibNumero->Checked=true;
    GroupBoxVehlib->Caption= GroupBoxVehlib->Caption+
                               Format( asFrmNumeroCoordonnees,
                                       ARRAYOFCONST((v->NumVehlib, Vehlib->x, Vehlib->y)))+
                               " ";
   }
  else
   RadioButtonAucunVehlib->Checked=true;
  RadioButtonVehlibNumero->Enabled=ARendreVisible;
  RadioButtonAucunVehlib->Enabled=!ARendreVisible;
  for(i=1; i<=10; i++)
   ((TLabel*)FindComponent("Label"+IntToStr(i)))->Enabled=ARendreVisible;
  LabelSituation->Visible=ARendreVisible;
  LabelDirection->Visible=ARendreVisible;
  LabelNumeroPlaceDepart->Visible=ARendreVisible;
  LabelNumeroPlaceArrivee->Visible=ARendreVisible;
  LabelNbPersonnes->Visible=ARendreVisible;
  LabelParcours->Visible=ARendreVisible;
  LabelToursDepuisDepart->Visible=ARendreVisible;
  LabelParcoursDepuisDepart->Visible=ARendreVisible;
  LabelDistancePlaceArrivee->Visible=ARendreVisible;
  LabelVitesse->Visible=ARendreVisible;
 }
//---------------------------------------------------------------------------
void TfrmInfosVehlib::RafraichitInfos()
 {
  int i,
      NbDirPoss,
      MinDistPlace=0x7FFFFFFF,
      ResteAParcourir,
      DistMin;
  bool Afficher;
  x=frmSimulation->DrawGridSimul->Col;
  y=frmSimulation->DrawGridSimul->Row;
  v=&(cv->v[x][y]);
  Vehlib=NULL;
  LabelCoordonnees->Caption=Format(asFrmCoordonnees, ARRAYOFCONST((x, y)));
  if (Afficher=(v->NumVehlib>0))
   {
    Vehlib=cv->Vehlib+v->NumVehlib-1;
    LabelSituation->Caption=asSituation[Vehlib->Situation];
    LabelDirection->Caption=asDir[Vehlib->Dir];
    LabelNumeroPlaceDepart->Caption=Format( asFrmNumeroCoordonnees,
                                            ARRAYOFCONST(( Vehlib->NumPlaceDepart,
                                                           cv->PlaceVehlib[Vehlib->NumPlaceDepart-1].x,
                                                           cv->PlaceVehlib[Vehlib->NumPlaceDepart-1].y)));
    if (Vehlib->NumPlaceArrivee)
      LabelNumeroPlaceArrivee->Caption=Format( asFrmNumeroCoordonnees,
                                               ARRAYOFCONST(( Vehlib->NumPlaceArrivee,
                                                              cv->PlaceVehlib[Vehlib->NumPlaceArrivee-1].x,
                                                              cv->PlaceVehlib[Vehlib->NumPlaceArrivee-1].y)));
    else
      LabelNumeroPlaceArrivee->Caption=asAucune;
    LabelNbPersonnes->Caption=IntToStr(Vehlib->NbPersonnes);
    LabelParcours->Caption=IntToStr(Vehlib->NbCasesParcourues);
    switch(Vehlib->Situation)
     {
      case svDepart:  LabelToursDepuisDepart->Caption=IntToStr(cv->TourCrt-Vehlib->TourDepart);
                      LabelParcoursDepuisDepart->Caption=IntToStr(Vehlib->NbCasesParcourues);
                      break;
      case svAttente: LabelToursDepuisDepart->Caption=asNonDemarre;
                      LabelParcoursDepuisDepart->Caption=asNonDemarre;
                      break;
     }
    if (Vehlib->NumPlaceArrivee)
     {
      for(i=0; i<NbDir[v->DirPoss]; i++)
       if (v->DistPlaceVehlib[Vehlib->NumPlaceArrivee-1][i]<MinDistPlace)
        MinDistPlace=v->DistPlaceVehlib[Vehlib->NumPlaceArrivee-1][i];
      LabelDistancePlaceArrivee->Caption=IntToStr(MinDistPlace);
     }
     else
      LabelDistancePlaceArrivee->Caption=asNA;
    LabelVitesse->Caption=Format(asFrmVitesse, ARRAYOFCONST((1, cv->NbVitesses)));
   }
  RendreVisibleInfos(Afficher);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmInfosVehlib::FormShow(TObject *Sender)
{
 frmSimulation->ActionDetailVehlib->Checked=true;
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosVehlib::FormHide(TObject *Sender)
{
 frmSimulation->ActionDetailVehlib->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosVehlib::ButtonOkClick(TObject *Sender)
{
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosVehlib::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosVehlib::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

