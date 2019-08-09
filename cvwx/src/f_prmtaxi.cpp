//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "simul.h"
#include "f_simul.h"
#include "f_prmtaxi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "cspin"
//---------------------------------------------------------------------------
TfrmParamTaxi *frmParamTaxi;
//---------------------------------------------------------------------------
__fastcall TfrmParamTaxi::TfrmParamTaxi(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamTaxi::ButtonOkClick(TObject *Sender)
{
 AppliqueChoix();
 ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamTaxi::ButtonAppliquerClick(TObject *Sender)
{
 AppliqueChoix();
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamTaxi::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamTaxi::FormShow(TObject *Sender)
{
 InitialisationEnCours=true;
 CSpinEditNbMaxPersonnesTaxi->Value=cv->NbMaxPersonnesTaxi;
 CSpinEditNbCasesMaxPlaceTaxi->Value=cv->NbMaxCasesDetectFileTaxi;
 CSpinEditProbaDirPlaceTaxi->Value=cv->ProbaDirFileTaxi;
 CSpinEditNbMaxToursAttente->Value=cv->NbMaxToursAttenteTaxi;
 CSpinEditProbaArretDmd->Value=cv->ProbaArretTaxiDmd;
 InitialisationEnCours=false;
}
//---------------------------------------------------------------------------
void TfrmParamTaxi::AppliqueChoix()
 {
  cv->NbMaxPersonnesTaxi=CSpinEditNbMaxPersonnesTaxi->Value;
  cv->NbMaxCasesDetectFileTaxi=CSpinEditNbCasesMaxPlaceTaxi->Value;
  cv->ProbaDirFileTaxi=CSpinEditProbaDirPlaceTaxi->Value;
  cv->NbMaxToursAttenteTaxi=CSpinEditNbMaxToursAttente->Value;
  cv->ProbaArretTaxiDmd=CSpinEditProbaArretDmd->Value;
  frmSimulation->SimulationModifiee=true;
  ButtonAppliquer->Enabled=false;
 }
//---------------------------------------------------------------------------
void __fastcall TfrmParamTaxi::CSpinEditParametresChange(
      TObject *Sender)
{
 if (!InitialisationEnCours) ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamTaxi::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

