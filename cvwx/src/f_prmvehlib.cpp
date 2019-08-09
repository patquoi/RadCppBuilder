//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "simul.h"
#include "f_simul.h"
#include "f_prmvehlib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "cspin"
//---------------------------------------------------------------------------
TfrmParamVehlib *frmParamVehlib;
//---------------------------------------------------------------------------
__fastcall TfrmParamVehlib::TfrmParamVehlib(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamVehlib::ButtonOkClick(TObject *Sender)
{
 AppliqueChoix();
 ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamVehlib::ButtonAppliquerClick(TObject *Sender)
{
 AppliqueChoix();
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamVehlib::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamVehlib::FormShow(TObject *Sender)
{
 InitialisationEnCours=true;
 CSpinEditNbMaxPersonnesVehlib->Value=cv->NbMaxPersonnesVehlib;
 CSpinEditNbCasesMaxPlaceVehlib->Value=cv->NbMaxCasesDetectFileVehlib;
 CSpinEditProbaDirPlaceVehlib->Value=cv->ProbaDirFileVehlib;
 CSpinEditTauxRemplissage->Value=cv->TauxRemplissageVehlib;
 InitialisationEnCours=false;
}
//---------------------------------------------------------------------------
void TfrmParamVehlib::AppliqueChoix()
 {
  cv->NbMaxPersonnesVehlib=CSpinEditNbMaxPersonnesVehlib->Value;
  cv->NbMaxCasesDetectFileVehlib=CSpinEditNbCasesMaxPlaceVehlib->Value;
  cv->ProbaDirFileVehlib=CSpinEditProbaDirPlaceVehlib->Value;
  cv->TauxRemplissageVehlib=CSpinEditTauxRemplissage->Value;
  frmSimulation->SimulationModifiee=true;
  ButtonAppliquer->Enabled=false;
 }
//---------------------------------------------------------------------------
void __fastcall TfrmParamVehlib::CSpinEditParametresChange(
      TObject *Sender)
{
 if (!InitialisationEnCours) ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamVehlib::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

