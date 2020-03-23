//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_inftaxi.h"
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
TfrmInfosTaxi *frmInfosTaxi;
//---------------------------------------------------------------------------
const AnsiString asDebutTitreCadreTaxi="                           ",
                 asFrmNumeroCoordonnees="%d (%2.2d, %2.2d)",
                 asFrmCoordonnees="%2.2d, %2.2d",
                 asFrmPourcentage="%.3f%%",
                 asFrmVitesse="%d/%d",
                 asSituation[NBSITUATIONSTAXI]={"En attente","Départ d'une course","Dépôt de client(s)","Retour d'une course"};
//---------------------------------------------------------------------------
__fastcall TfrmInfosTaxi::TfrmInfosTaxi(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmInfosTaxi::RendreVisibleInfos(bool ARendreVisible)
 {
  int i;
  GroupBoxTaxi->Caption=asDebutTitreCadreTaxi;
  if (ARendreVisible)
   {
    RadioButtonTaxiNumero->Checked=true;
    GroupBoxTaxi->Caption= GroupBoxTaxi->Caption+
                               Format( asFrmNumeroCoordonnees,
                                       ARRAYOFCONST((v->NumTaxi, Taxi->x, Taxi->y)))+
                               " ";
   }
  else
   RadioButtonAucunTaxi->Checked=true;
  RadioButtonTaxiNumero->Enabled=ARendreVisible;
  RadioButtonAucunTaxi->Enabled=!ARendreVisible;
  for(i=1; i<13; i++)
   ((TLabel*)FindComponent("Label"+IntToStr(i)))->Enabled=ARendreVisible;
  LabelSituation->Visible=ARendreVisible;
  LabelDirection->Visible=ARendreVisible;
  LabelNumeroFile->Visible=ARendreVisible;
  LabelTeteFileOrigine->Visible=ARendreVisible;
  LabelNbPersonnes->Visible=ARendreVisible;
  LabelParcours->Visible=ARendreVisible;
  LabelToursDepuisDepart->Visible=ARendreVisible;
  LabelToursDepuisDepot->Visible=ARendreVisible;
  LabelToursDepuisRetour->Visible=ARendreVisible;
  LabelParcoursDepuisDepart->Visible=ARendreVisible;
  LabelDistanceTeteFileDepart->Visible=ARendreVisible;
  LabelVitesse->Visible=ARendreVisible;
 }
//---------------------------------------------------------------------------
void TfrmInfosTaxi::RafraichitInfos()
 {
  int i,
      NumPlaceTeteFile,
      NbDirPoss,
      MinDistFile=0x7FFFFFFF,
      ResteAParcourir,
      DistMin;
  bool Afficher;
  x=frmSimulation->DrawGridSimul->Col;
  y=frmSimulation->DrawGridSimul->Row;
  v=&(cv->v[x][y]);
  Taxi=NULL;
  LabelCoordonnees->Caption=Format(asFrmCoordonnees, ARRAYOFCONST((x, y)));
  if (Afficher=(v->NumTaxi>0))
   {
    Taxi=cv->Taxi+v->NumTaxi-1;
    LabelSituation->Caption=asSituation[Taxi->Situation];
    LabelDirection->Caption=asDir[Taxi->Dir];
    LabelNumeroFile->Caption=IntToStr(Taxi->NumFile+1);
    NumPlaceTeteFile=cv->PlaceTaxi[cv->FileTaxi[Taxi->NumFile].NumPlaceQueue].PlaceTeteFile();
    LabelTeteFileOrigine->Caption=Format(asFrmNumeroCoordonnees, ARRAYOFCONST((NumPlaceTeteFile, cv->PlaceTaxi[NumPlaceTeteFile-1].x, cv->PlaceTaxi[NumPlaceTeteFile-1].y)));
    LabelNbPersonnes->Caption=IntToStr(Taxi->NbPersonnes);
    LabelParcours->Caption=IntToStr(Taxi->NbCasesParcourues);
    LabelToursDepuisDepart->Caption=IntToStr(cv->TourCrt-Taxi->TourDepartDrnCourse);
    LabelToursDepuisDepot->Caption=IntToStr(cv->TourCrt-Taxi->TourDepotDrnCourse);
    LabelToursDepuisRetour->Caption=IntToStr(cv->TourCrt-Taxi->TourRetourDrnCourse);
    LabelParcoursDepuisDepart->Caption=IntToStr(Taxi->NbCasesParcouruesDrnCourse);
    for(i=0; i<NbDir[v->DirPoss]; i++)
     if (v->DistFileTaxi[i][Taxi->NumFile]<MinDistFile) MinDistFile=v->DistFileTaxi[i][Taxi->NumFile];
    LabelDistanceTeteFileDepart->Caption=IntToStr(MinDistFile);
    LabelVitesse->Caption=Format(asFrmVitesse, ARRAYOFCONST((1, cv->NbVitesses)));
   }
  RendreVisibleInfos(Afficher);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmInfosTaxi::FormShow(TObject *Sender)
{
 frmSimulation->ActionDetailTaxi->Checked=true;
#ifdef CV_LINUX
 FormResize(this);
#endif
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosTaxi::FormHide(TObject *Sender)
{
 frmSimulation->ActionDetailTaxi->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosTaxi::ButtonOkClick(TObject *Sender)
{
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosTaxi::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosTaxi::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=XMAX(GroupBoxTaxi)+LH_ESPACE,
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

