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
{
 CheckBoxActiver->Checked = false;
 GroupBox->Enabled = false;
 CSpinEditInfectiosite->Enabled = false;
 CSpinEditPatientZero->Enabled = false;
 CSpinEditChargeViraleFatale->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEpidemie::CheckBoxActiverClick(TObject *Sender)
{
 GroupBox->Enabled = CheckBoxActiver->Checked;
 CSpinEditInfectiosite->Enabled = CheckBoxActiver->Checked;
 CSpinEditPatientZero->Enabled = CheckBoxActiver->Checked;
 CSpinEditChargeViraleFatale->Enabled = CheckBoxActiver->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmEpidemie::ButtonOkClick(TObject *Sender)
{
 // On enregistre les param�tres
 cv->EpidemieInfectiosite = CSpinEditInfectiosite->Value;
 cv->EpidemieIterationPatientZero = CSpinEditPatientZero->Value;
 cv->EpidemieChargeFatale = CSpinEditChargeViraleFatale->Value;
 frmSimulation->ActionEpidemie->Checked = CheckBoxActiver->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmEpidemie::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

void __fastcall TfrmEpidemie::FormShow(TObject *Sender)
{
 // On charge les param�tres
 CSpinEditInfectiosite->Value = cv->EpidemieInfectiosite; // Nb tours (100 par d�faut)
 CSpinEditPatientZero->Value = cv->EpidemieIterationPatientZero; // Nb pi�tons (100 par d�faut)
 CSpinEditChargeViraleFatale->Value = cv->EpidemieChargeFatale; // en % pi�tons infect�s au bout de la p�riode d'infectiosit� (5 par d�faut)

 // On rafra�chit les acc�s
 CheckBoxActiver->Enabled = (!frmSimulation->SimulationEnCours);
 GroupBox->Enabled = CheckBoxActiver->Checked && CheckBoxActiver->Enabled;
 CSpinEditInfectiosite->Enabled = CheckBoxActiver->Checked && CheckBoxActiver->Enabled;
 CSpinEditPatientZero->Enabled = CheckBoxActiver->Checked && CheckBoxActiver->Enabled;
 CSpinEditChargeViraleFatale->Enabled = CheckBoxActiver->Checked && CheckBoxActiver->Enabled;
}
//---------------------------------------------------------------------------

