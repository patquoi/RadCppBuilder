//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_prmsim.h"
#include "simul.h"
#include "f_simul.h"
#include "f_prmbus.h"
#include "f_prmtram.h"
#include "f_prmtaxi.h"
#include "f_prmvehlib.h"
#include "f_dimzone.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
#pragma link "cspin"
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
  NbParkingsChange=false;
  NbVehiculesChange=false;
  NbPietonsChange=false; // v2.0
  NbArretsBusChange=false; // v3.0
  NbArretsTramChange=false; // v3.5
  NbPlacesTaxiChange=false; // v3.6
  NbPlacesParkChange=false; // v5.0
 }
//---------------------------------------------------------------------------
bool TfrmParamSimul::AppliqueChoix()
 {
  int i;
  frmSimulation->SimulationModifiee=true;
  if (NbVehiculesChange) cv->DefinitNbVehicules(CSpinEditNbVehicules->Value);
  if (NbPietonsChange) cv->DefinitNbPietons((CSpinEditNbPietons->Value*CSpinEditNbVehicules->Value)/100); // v2.0
  BitBtnDefLignesBus->Enabled=(cv->NbArretsBus>0); // v3.0
  BitBtnDefLignesTram->Enabled=(cv->NbArretsTram>0); // v3.5
  BitBtnDefTaxis->Enabled=(cv->NbPlacesTaxi>0); // v3.6
  BitBtnDefVehlibs->Enabled=(cv->NbPlacesVehlib>0); // v5.3
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
void TfrmParamSimul::CalculeChoixPossiblesNbVehicules() // v5.0 : Calcul des possibilités de véhicules déporté en fonction car utilisé dans FormShow
 {
  int NbMinVehicules= cv->NbParkings*(cv->NbParkings-1)
                     +2*cv->NbPlacesPark, // v5.0 : 1 véh départ + 1 véh arrivée par place de parking
      NbMaxVehicules= NbMinVehicules*(NBMAXVEHICULES/NbMinVehicules), // v5.0.3
      NbVehicules=NbMinVehicules*(CSpinEditNbVehicules->Value/NbMinVehicules); // v5.0.3
    CSpinEditNbVehicules->Increment=NbMinVehicules;
    CSpinEditNbVehicules->MINVALUE=NbMinVehicules;
    CSpinEditNbVehicules->MAXVALUE=NbMaxVehicules;
    // v5.0.3 : recalcul modulo NbVehicules
    if (CSpinEditNbVehicules->Value!=NbVehicules)
     {
      CSpinEditNbVehicules->Value=NbVehicules;
      NbVehiculesChange=true;
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
 Initialisation=true;
 if (!Caption.Pos("["))// v5.0
  if (frmDimensionsZone) // v4.4.0
   Caption=Caption+Format(" [%dx%d]", ARRAYOFCONST((frmDimensionsZone->NbX, frmDimensionsZone->NbY)));
  else
   Caption=Caption+Format(" [%dx%d]", ARRAYOFCONST((cv->NbX, cv->NbY)));
 if (cv->NbVehicules) CSpinEditNbVehicules->Value=cv->NbVehicules;
 else cv->DefinitNbVehicules(CSpinEditNbVehicules->Value);

 CSpinEditNbPietons->Value=(100*cv->NbPietons)/cv->NbVehicules;
 BitBtnDefLignesBus->Enabled=(cv->NbArretsBus>0); // v3.0
 BitBtnDefLignesTram->Enabled=(cv->NbArretsTram>0); // v3.5
 BitBtnDefTaxis->Enabled=(cv->NbPlacesTaxi>0); // v3.6
 BitBtnDefVehlibs->Enabled=(cv->NbPlacesVehlib>0); // v5.3

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

 LabelNbVehicules->Enabled=!cv->TourCrt;
 CSpinEditNbVehicules->Enabled=!cv->TourCrt;
 LabelNbPietons->Enabled=!cv->TourCrt; // v2.0
 CSpinEditNbPietons->Enabled=!cv->TourCrt; // v2.0
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
 CalculeChoixPossiblesNbVehicules(); // v5.0
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


void __fastcall TfrmParamSimul::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamSimul::BitBtnDefVehlibsClick(TObject *Sender)
{ // v5.3
 if (frmParamVehlib=new TfrmParamVehlib(this))
  try
   {
    frmParamSimul->Hide();
    frmParamVehlib->ShowModal();
   }
  __finally
   {
    frmSimulation->DrawGridSimul->Repaint();
    frmParamSimul->Show();
    frmParamVehlib->Release();
    frmParamVehlib=NULL;
   }
}
//---------------------------------------------------------------------------

