//---------------------------------------------------------------------------

#ifndef f_epidemieH
#define f_epidemieH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "cspin.h"
//---------------------------------------------------------------------------
class TfrmEpidemie : public TForm
{
__published:	// Composants gérés par l'EDI
	TGroupBox *GroupBox;
	TCSpinEdit *CSpinEditInfectiosite;
	TLabel *Label1;
	TCSpinEdit *CSpinEditPatientZero;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TCSpinEdit *CSpinEditChargeViraleFatale;
	TLabel *Label5;
	TButton *ButtonOk;
	TButton *ButtonAnnuler;
	TButton *ButtonAide;
	TLabel *Label6;
	TCheckBox *CheckBoxActiver;
	TLabel *Label7;
	TLabel *Label8;
	TCheckBox *CheckBoxReinfections;
	void __fastcall ButtonOkClick(TObject *Sender);
	void __fastcall ButtonAideClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
	__fastcall TfrmEpidemie(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEpidemie *frmEpidemie;
//---------------------------------------------------------------------------
#endif
