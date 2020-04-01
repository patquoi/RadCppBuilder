//---------------------------------------------------------------------------
#ifndef f_infptnH
#define f_infptnH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "simul.h"
//---------------------------------------------------------------------------
class TfrmInfosPieton : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonOk;
    TLabel *Label0;
    TLabel *LabelCoordonnees;
    TRadioButton *RadioButtonAucunPieton;
    TGroupBox *GroupBoxPieton;
    TRadioButton *RadioButtonPietonNumero;
    TLabel *Label3;
    TLabel *LabelSituation;
    TLabel *Label4;
    TLabel *LabelParcours;
    TLabel *Label1;
    TLabel *LabelDirection;
    TLabel *Label2;
    TLabel *LabelPosition;
    TButton *ButtonAide;
    TLabel *Label5;
        TLabel *LabelBusTramTaxiVehlib;
    TLabel *Label6;
        TLabel *LabelArretBusTramFileTaxiVehlib;
	TGroupBox *GroupBoxEpidemie;
	TCheckBox *CheckBoxEpidemie;
	TLabel *Label7;
	TLabel *LabelInfecte;
	TLabel *Label8;
	TLabel *LabelRangs;
	TLabel *Label9;
	TLabel *LabelTours;
	TLabel *Label10;
	TLabel *LabelInfections;
	TLabel *Label11;
	TLabel *LabelPeriodeInfectiosite;
	TLabel *Label13;
	TLabel *LabelChargeVirale;
	TLabel *Label12;
	TLabel *LabelEtatFinal;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    
private:	// Déclarations de l'utilisateur
    voie *v;
    pieton *p;
    int x, y, NumPieton;
    void RendreVisibleInfos(bool Visible);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmInfosPieton(TComponent* Owner);
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInfosPieton *frmInfosPieton;
//---------------------------------------------------------------------------
#endif
  