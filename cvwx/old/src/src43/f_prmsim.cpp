//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_prmsim.h"
#include "simul.h"
#include "f_simul.h"
#include "f_prmbus.h"
#include "f_prmtram.h"
#include "f_prmtaxi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
 #pragma link "cspin"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
TfrmParamSimul *frmParamSimul=NULL;
//---------------------------------------------------------------------------
void Parametres()
 {
  if (frmParamSimul=new TfrmParamSimul(frmSimulation))
   {
    frmParamSimul->ShowModal();
    delete frmParamSimul;
    frmParamSimul=NULL;
   }
 }
//---------------------------------------------------------------------------
__fastcall TfrmParamSimul::TfrmParamSimul(TComponent* Owner) : TForm(Owner)
 {
  NbFeuxChange=false;
  NbEtapesChange=false;
  NbVehiculesChange=false;
  NbPietonsChange=false; // v2.0
  NbArretsBusChange=false; // v3.0
  NbArretsTramChange=false; // v3.5
  NbPlacesTaxiChange=false; // v3.6
 }
//---------------------------------------------------------------------------
bool TfrmParamSimul::AppliqueChoix()
 {
  int i;
  frmSimulation->SimulationModifiee=true;
  if (NbVehiculesChange) cv->DefinitNbVehicules(CSpinEditNbVehicules->Value);
  if (NbPietonsChange) cv->DefinitNbPietons((CSpinEditNbPietons->Value*CSpinEditNbVehicules->Value)/100); // v2.0
  if (NbFeuxChange)
   {
    switch(AfficheMessage("\
Lorsque vous changez le nombre de feux,\n\
tous les feux sont SUPPRIMÉS !\n\
Êtes-vous sûr(e) de vouloir changer le nombre de feux ?", "Avertissement", tmQuestionFacultative, 2, 2)) // Défaut ET Echap = Annuler
     {
      case trOui:    NbFeuxChange=false;
                     if (!cv) break;
                     for(i=0; i<cv->NbFeux; i++)
                      if (cv->Feu[i].Defini())
                       cv->v[cv->Feu[i].x][cv->Feu[i].y].NumFeu[cv->Feu[i].Dir-1]=0;
                     if (cv->Feu) { delete[] cv->Feu; cv->Feu=NULL; }
                     cv->DefinitNbFeux(CSpinEditNbFeux->Value);
                     break;
      case trNon:    NbFeuxChange=false;
                     CSpinEditNbFeux->Value=cv->NbFeux; break;
      case trAnnuler:return false;
      default:  break;
     }
   }
  if (NbEtapesChange)
   {
    switch(AfficheMessage("\
Si vous changez le nombre d'étapes,\n\
toutes les étapes en cours vont être SUPPRIMÉES !\n\
Êtes-vous sûr(e) de vouloir changer le nombre d'étapes ?", "Avertissement", tmQuestionFacultative, 2, 2)) // Défaut ET Echap = Annuler
     {
      case trOui:    NbEtapesChange=false;
                     if (!cv) break;
                     for(i=0; i<cv->NbEtapes; i++)
                      if (cv->Etape[i].Definie())
                       cv->v[cv->Etape[i].x][cv->Etape[i].y].NumEtape=0;
                     if (cv->Etape) { delete[] cv->Etape; cv->Etape=NULL; }
                     cv->DefinitNbEtapes(CSpinEditNbEtapes->Value);
                     break;
      case trNon:    NbEtapesChange=false;
                     CSpinEditNbEtapes->Value=cv->NbEtapes; break;
      case trAnnuler:return false;
      default:  break;
     }
   }
  if (NbArretsBusChange) // v3.0
   {
    switch(AfficheMessage("\
Lorsque vous changez le nombre d'arrêts de bus,\n\
tous les arrêts de bus sont SUPPRIMÉS et\n\
toutes les définitions de lignes de bus sont PERDUES !\n\
Êtes-vous sûr(e) de vouloir changer le nombre d'arrêts de bus ?", "Avertissement", tmQuestionFacultative, 2, 2)) // Défaut ET Echap = Annuler
     {
      case trOui:    NbArretsBusChange=false;
                     if (!cv) break;
                     for(i=0; i<cv->NbArretsBus; i++)
                      if (cv->ArretBus[i].Defini())
                       cv->SupprimeArretBus(i);
                     if (cv->ArretBus) { delete[] cv->ArretBus; cv->ArretBus=NULL; }
                     cv->DefinitNbArretsBus(CSpinEditNbArretsBus->Value);
                     break;
      case trNon:    NbArretsBusChange=false;
                     CSpinEditNbArretsBus->Value=cv->NbArretsBus; break;
      case trAnnuler:return false;
      default:  break;
     }
   }
  BitBtnDefLignesBus->Enabled=(cv->NbArretsBus>0); // v3.0

  if (NbArretsTramChange) // v3.5
   {
    switch(AfficheMessage("\
Lorsque vous changez le nombre d'arrêts de tram,\n\
tous les arrêts de tram sont SUPPRIMÉS et\n\
toutes les définitions de lignes de tram sont PERDUES !\n\
Êtes-vous sûr(e) de vouloir changer le nombre d'arrêts de tram ?", "Avertissement", tmQuestionFacultative, 2, 2)) // Défaut ET Echap = Annuler
     {
      case trOui:    NbArretsTramChange=false;
                     if (!cv) break;
                     for(i=0; i<cv->NbArretsTram; i++)
                      if (cv->ArretTram[i].Defini())
                       cv->SupprimeArretTram(i);
                     if (cv->ArretTram) { delete[] cv->ArretTram; cv->ArretTram=NULL; }
                     cv->DefinitNbArretsTram(CSpinEditNbArretsTram->Value);
                     break;
      case trNon:    NbArretsTramChange=false;
                     CSpinEditNbArretsTram->Value=cv->NbArretsTram; break;
      case trAnnuler:return false;
      default:  break;
     }
   }
  BitBtnDefLignesTram->Enabled=(cv->NbArretsTram>0); // v3.5

  if (NbPlacesTaxiChange)
   {
    switch(AfficheMessage("\
Si vous changez le nombre de places de taxi,\n\
toutes les places de taxi en cours vont être SUPPRIMÉES !\n\
Êtes-vous sûr(e) de vouloir changer le nombre de places de taxi ?", "Avertissement", tmQuestionFacultative, 2, 2)) // Défaut ET Echap = Annuler
     {
      case trOui:    NbPlacesTaxiChange=false;
                     if (!cv) break;
                     for(i=0; i<cv->NbPlacesTaxi; i++)
                      if (cv->PlaceTaxi[i].Definie())
                       cv->v[cv->PlaceTaxi[i].x][cv->PlaceTaxi[i].y].NumPlaceTaxi=0;
                     if (cv->PlaceTaxi) { delete[] cv->PlaceTaxi; cv->PlaceTaxi=NULL; }
                     cv->DefinitNbPlacesTaxi(CSpinEditNbPlacesTaxi->Value);
                     break;
      case trNon:    NbPlacesTaxiChange=false;
                     CSpinEditNbPlacesTaxi->Value=cv->NbPlacesTaxi; break;
      case trAnnuler:return false;
      default:  break;
     }
   }
  BitBtnDefTaxis->Enabled=(cv->NbPlacesTaxi>0); // v3.6

  if (ParamsInchanges=CheckBoxMaintenus->Checked)
   {
    SvgNbFeux=cv->NbFeux;
    SvgNbEtapes=cv->NbEtapes;
    SvgNbVehicules=cv->NbVehicules;
    SvgNbPietons=cv->NbPietons; // v2.0
    SvgNbArretsBus=cv->NbArretsBus; // v3.0
    SvgNbArretsTram=cv->NbArretsTram; // v3.5
    SvgNbPlacesTaxi=cv->NbPlacesTaxi; // v3.6
   }
  cv->DureeVert=CSpinEditDureeVert->Value;
  cv->DureeOrange=CSpinEditDureeOrange->Value;
  cv->DureeRouge=CSpinEditDureeRouge->Value;
  cv->AttenteMaxVeh=CSpinEditAttenteAvChx->Value;
  cv->NbToursParSeconde=CSpinEditNbToursParSeconde->Value;
  cv->NbVitesses=RadioGroupVitesses->ItemIndex+1;
  cv->NbMaxCasesDetectPsgPt=CSpinEditNbCasesMaxPsgPtn->Value;
  cv->ProbaDirPsgPt=CSpinEditProbaPsgPt->Value;

  frmSimulation->DrawGridSimul->Repaint();
  ButtonAppliquer->Enabled=false;
  BitBtnAppliqueDureeFeuVert->Enabled=true;
  BitBtnAppliqueDureeFeuRouge->Enabled=true;
  return true;
 }
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::CSpinEditNbVehiculesChange(TObject *Sender)
 {
  if (!Initialisation)
   {
    NbVehiculesChange=true;
    ButtonAppliquer->Enabled=true;
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::CSpinEditNbPietonsChange(TObject *Sender)
{ // v2.0
  if (!Initialisation)
   {
    NbPietonsChange=true;
    ButtonAppliquer->Enabled=true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::CSpinEditNbFeuxChange(TObject *Sender)
 {
  if (!Initialisation)
   {
    NbFeuxChange=true;
    ButtonAppliquer->Enabled=true;
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::CSpinEditNbEtapesChange(TObject *Sender)
 {
  int NbEtapes=CSpinEditNbEtapes->Value,
      NbMinVehicules=NbEtapes*(NbEtapes-1),
      NbMaxVehicules=(1000/(NbEtapes*(NbEtapes-1)))*NbEtapes*(NbEtapes-1),
      NbVehicules=(NBMAXETAPES/NbEtapes)*NbMinVehicules;
  if (!Initialisation)
   {
    NbEtapesChange=true;
    CSpinEditNbVehicules->Increment=NbMinVehicules;
    CSpinEditNbVehicules->MINVALUE=NbMinVehicules;
    CSpinEditNbVehicules->MAXVALUE=NbMaxVehicules;
    CSpinEditNbVehicules->Value=(NbMaxVehicules<NbVehicules)?NbMaxVehicules:NbVehicules;
    ButtonAppliquer->Enabled=true;
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::ButtonOkClick(TObject *Sender)
{
 AppelleAuChaos();
 ButtonOk->ModalResult=AppliqueChoix()?mrOk:mrNone;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::ButtonAppliquerClick(TObject *Sender)
{
 AppliqueChoix();
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::FormShow(TObject *Sender)
{
#ifdef CV_LINUX
 FormResize(this);
#endif
 Initialisation=true;
 Caption=Caption+Format(" [%dx%d]", ARRAYOFCONST((cv->NbX, cv->NbY)));
 if (cv->NbVehicules) CSpinEditNbVehicules->Value=cv->NbVehicules;
 else cv->DefinitNbVehicules(CSpinEditNbVehicules->Value);

 CSpinEditNbPietons->Value=(100*cv->NbPietons)/cv->NbVehicules;
 CSpinEditNbFeux->Value=cv->NbFeux;

 CSpinEditNbArretsBus->Value=cv->NbArretsBus; // v3.0
 CSpinEditNbArretsTram->Value=cv->NbArretsTram; // v3.5
 CSpinEditNbPlacesTaxi->Value=cv->NbPlacesTaxi; // v3.6
 BitBtnDefLignesBus->Enabled=(cv->NbArretsBus>0); // v3.0
 BitBtnDefLignesTram->Enabled=(cv->NbArretsTram>0); // v3.5
 BitBtnDefTaxis->Enabled=(cv->NbPlacesTaxi>0); // v3.6

 if (cv->NbEtapes) CSpinEditNbEtapes->Value=cv->NbEtapes;
 else cv->DefinitNbEtapes(CSpinEditNbEtapes->Value);

 CheckBoxMaintenus->Checked=ParamsInchanges;

 if (cv->DureeVert) CSpinEditDureeVert->Value=cv->DureeVert;
 else cv->DureeVert=CSpinEditDureeVert->Value;
 if (cv->DureeOrange) CSpinEditDureeOrange->Value=cv->DureeOrange;
 else cv->DureeOrange=CSpinEditDureeOrange->Value;
 if (cv->DureeRouge) CSpinEditDureeRouge->Value=cv->DureeRouge;
 else cv->DureeRouge=CSpinEditDureeRouge->Value;

 CSpinEditAttenteAvChx->Value=cv->AttenteMaxVeh;

 if (cv->NbToursParSeconde) CSpinEditNbToursParSeconde->Value=cv->NbToursParSeconde;
 else cv->NbToursParSeconde=CSpinEditNbToursParSeconde->Value;

 RadioGroupVitesses->ItemIndex=cv->NbVitesses-1;
 CSpinEditNbCasesMaxPsgPtn->Value=cv->NbMaxCasesDetectPsgPt;
 CSpinEditProbaPsgPt->Value=cv->ProbaDirPsgPt;

 LabelNbFeux->Enabled=!cv->TourCrt;
 CSpinEditNbFeux->Enabled=!cv->TourCrt;
 LabelNbEtapes->Enabled=(!cv->DistancesCalculees)&&(!cv->TourCrt);
 CSpinEditNbEtapes->Enabled=(!cv->DistancesCalculees)&&(!cv->TourCrt);
 LabelNbVehicules->Enabled=!cv->TourCrt;
 CSpinEditNbVehicules->Enabled=!cv->TourCrt;
 LabelNbPietons->Enabled=!cv->TourCrt; // v2.0
 CSpinEditNbPietons->Enabled=!cv->TourCrt; // v2.0
 LabelNbArretsBus->Enabled=(!cv->DistancesCalculees)&&(!cv->TourCrt);; // v3.0
 CSpinEditNbArretsBus->Enabled=(!cv->DistancesCalculees)&&(!cv->TourCrt); // v3.0
 LabelNbArretsTram->Enabled=(!cv->DistancesCalculees)&&(!cv->TourCrt);; // v3.5
 CSpinEditNbArretsTram->Enabled=(!cv->DistancesCalculees)&&(!cv->TourCrt); // v3.5
 LabelNbPlacesTaxi->Enabled=(!cv->DistancesCalculees)&&(!cv->TourCrt);; // v3.7
 CSpinEditNbPlacesTaxi->Enabled=(!cv->DistancesCalculees)&&(!cv->TourCrt); // v3.7
 LabelDureeVert->Enabled=!frmSimulation->SimulationEnCours;
 LabelDureeOrange->Enabled=!frmSimulation->SimulationEnCours;
 LabelDureeRouge->Enabled=!frmSimulation->SimulationEnCours;
 CSpinEditDureeVert->Enabled=!frmSimulation->SimulationEnCours;
 CSpinEditDureeOrange->Enabled=!frmSimulation->SimulationEnCours;
 CSpinEditDureeRouge->Enabled=!frmSimulation->SimulationEnCours;
 BitBtnAppliqueDureeFeuVert->Enabled=!frmSimulation->SimulationEnCours;
 BitBtnAppliqueDureeFeuRouge->Enabled=!frmSimulation->SimulationEnCours;
 LabelAttenteAvChx->Enabled=!frmSimulation->SimulationEnCours;
 CSpinEditAttenteAvChx->Enabled=!frmSimulation->SimulationEnCours;
 LabelNbToursParSeconde->Enabled=!frmSimulation->SimulationEnCours;
 CSpinEditNbToursParSeconde->Enabled=!frmSimulation->SimulationEnCours;
 RadioGroupVitesses->Enabled=!frmSimulation->SimulationEnCours;
 LabelNbCasesMaxPsgPtn->Enabled=!frmSimulation->SimulationEnCours;
 LabelProbaPsgPt->Enabled=!frmSimulation->SimulationEnCours;
 CSpinEditNbCasesMaxPsgPtn->Enabled=!frmSimulation->SimulationEnCours;
 CSpinEditProbaPsgPt->Enabled=!frmSimulation->SimulationEnCours;
 Initialisation=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::BitBtnAppliqueDureeFeuVertClick(
      TObject *Sender)
{
 int i;
 for(i=0; i<cv->NbFeux; i++)
  if (cv->Feu[i].Defini()) cv->Feu[i].DureeVert=cv->DureeVert;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::BitBtnAppliqueDureeFeuRougeClick(
      TObject *Sender)
{
 int i;
 for(i=0; i<cv->NbFeux; i++)
  if (cv->Feu[i].Defini()) cv->Feu[i].DureeRouge=cv->DureeRouge;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::CSpinEditDureeVertChange(TObject *Sender)
{
 if (!Initialisation)
  {
   ButtonAppliquer->Enabled=true;
   BitBtnAppliqueDureeFeuVert->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::CSpinEditDureeRougeChange(TObject *Sender)
{
 if (!Initialisation)
  {
   ButtonAppliquer->Enabled=true;
   BitBtnAppliqueDureeFeuRouge->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::Change(TObject *Sender)
{
 if (!Initialisation) ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::CSpinEditNbArretsBusChange(TObject *Sender)
{
 if (!Initialisation)
  {
   NbArretsBusChange=true;
   BitBtnDefLignesBus->Enabled=false;
   ButtonAppliquer->Enabled=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::BitBtnDefLignesBusClick(TObject *Sender)
{
 if (frmParamBus=new TfrmParamBus(this))
  try
   {
    frmParamSimul->Hide();
    frmParamBus->ShowModal();
   }
  __finally
   {
    frmSimulation->DrawGridSimul->Repaint();
    frmParamSimul->Show();
    frmParamBus->Release();
    frmParamBus=NULL;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::ButtonAideClick(TObject *Sender)
{ // v3.0
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::CSpinEditNbArretsTramChange(
      TObject *Sender)
{ // v3.5
 if (!Initialisation)
  {
   NbArretsTramChange=true;
   BitBtnDefLignesTram->Enabled=false;
   ButtonAppliquer->Enabled=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::BitBtnDefLignesTramClick(TObject *Sender)
{ // v3.5
 if (frmParamTram=new TfrmParamTram(this))
  try
   {
    frmParamSimul->Hide();
    frmParamTram->ShowModal();
   }
  __finally
   {
    frmSimulation->DrawGridSimul->Repaint();
    frmParamSimul->Show();
    frmParamTram->Release();
    frmParamTram=NULL;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::CSpinEditNbPlacesTaxiChange(TObject *Sender)
{ // v3.6
  if (!Initialisation)
   {
    NbPlacesTaxiChange=true;
    BitBtnDefTaxis->Enabled=false;
    ButtonAppliquer->Enabled=true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::BitBtnDefTaxisClick(TObject *Sender)
{
 if (frmParamTaxi=new TfrmParamTaxi(this))
  try
   {
    frmParamSimul->Hide();
    frmParamTaxi->ShowModal();
   }
  __finally
   {
    frmSimulation->DrawGridSimul->Repaint();
    frmParamSimul->Show();
    frmParamTaxi->Release();
    frmParamTaxi=NULL;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamSimul::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=max( max( LMAX(ButtonOk,ButtonAnnuler),
                 LMAX(ButtonAppliquer,ButtonAide)),
            LMAX(Label2,GroupBoxFonctionnement))+LH_ESPACE,
     h=YMAX(GroupBoxFonctionnement)+LH_ESPACE;
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

