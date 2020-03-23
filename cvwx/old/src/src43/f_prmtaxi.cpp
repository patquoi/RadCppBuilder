//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "simul.h"
#include "f_simul.h"
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
#ifdef CV_LINUX
 FormResize(this);
#endif
 InitialisationEnCours=true;
 CSpinEditNbMaxPersonnesTaxi->Value=cv->NbMaxPersonnesTaxi;
 CSpinEditNbCasesMaxPlaceTaxi->Value=cv->NbMaxCasesDetectFileTaxi;
 CSpinEditProbaDirPlaceTaxi->Value=cv->ProbaDirFileTaxi;
 CSpinEditNbMaxToursAttenteBus->Value=cv->NbMaxToursAttenteTaxi;
 CSpinEditProbaArretDmd->Value=cv->ProbaArretTaxiDmd;
 InitialisationEnCours=false;
}
//---------------------------------------------------------------------------
void TfrmParamTaxi::AppliqueChoix()
 {
  cv->NbMaxPersonnesTaxi=CSpinEditNbMaxPersonnesTaxi->Value;
  cv->NbMaxCasesDetectFileTaxi=CSpinEditNbCasesMaxPlaceTaxi->Value;
  cv->ProbaDirFileTaxi=CSpinEditProbaDirPlaceTaxi->Value;
  cv->NbMaxToursAttenteTaxi=CSpinEditNbMaxToursAttenteBus->Value;
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
void __fastcall TfrmParamTaxi::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=LMAX(Label22,GroupBox)+LH_ESPACE,
     h=max( HMAX(ButtonOk,ButtonAnnuler),
            HMAX(ButtonAppliquer,ButtonAide))+LH_ESPACE;
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

