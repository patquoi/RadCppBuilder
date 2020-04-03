//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "base.h"
#include "simul.h"
#include "f_simul.h"
#include "f_epidemie.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmEpidemie *frmEpidemie;
//---------------------------------------------------------------------------
__fastcall TfrmEpidemie::TfrmEpidemie(TComponent* Owner)
	: TForm(Owner)
{ // v5.4.2 : Tout est fait dans FormShow
}
//---------------------------------------------------------------------------
void __fastcall TfrmEpidemie::ButtonOkClick(TObject *Sender)
{
 // On enregistre les paramètres
 cv->EpidemieInfectiosite = CSpinEditInfectiosite->Value;
 cv->EpidemieIterationPatientZero = CSpinEditPatientZero->Value;
 cv->EpidemieChargeFatale = CSpinEditChargeViraleFatale->Value;
 cv->EpidemieReinfections = CheckBoxReinfections->Checked; // v5.4.2
}
//---------------------------------------------------------------------------

void __fastcall TfrmEpidemie::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

void __fastcall TfrmEpidemie::FormShow(TObject *Sender)
{
 // On charge les paramètres
 CSpinEditInfectiosite->Value = cv->EpidemieInfectiosite; // Nb tours (100 par défaut)
 CSpinEditPatientZero->Value = cv->EpidemieIterationPatientZero; // Nb piétons (100 par défaut)
 CSpinEditChargeViraleFatale->Value = cv->EpidemieChargeFatale; // en % piétons infectés au bout de la période d'infectiosité (5 par défaut)
 CheckBoxReinfections->Checked = cv->EpidemieReinfections; // v5.4.2 : Si vrai, alors même guéri, un piéton peut être réinfecté, si faux, il ne peut plus l'être (faux par défaut)

 // On rafraîchit les accès. v5.4.2 : on ne teste plus CheckBoxActiver->Enabled
 CheckBoxActiver->Checked = frmSimulation->ActionEpidemie->Checked;
 GroupBox->Enabled = CheckBoxActiver->Checked;
 CSpinEditInfectiosite->Enabled = CheckBoxActiver->Checked;
 CSpinEditPatientZero->Enabled = CheckBoxActiver->Checked;
 CSpinEditChargeViraleFatale->Enabled = CheckBoxActiver->Checked;
 CheckBoxReinfections->Enabled = CheckBoxActiver->Checked; // v5.4.2
}
//---------------------------------------------------------------------------

