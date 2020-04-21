//---------------------------------------------------------------------------
#ifndef prmniv_fH
#define prmniv_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cspin.h"
#include <ExtCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TfrmPrmNiveau : public TForm
{
__published:	// Composants gérés par l'EDI
    TPanel *Panel1;
    TCSpinEdit *CSpinEditNumNiv;
    TLabel *LabelNumNiv;
    TLabel *LabelNbMaxBetes;
    TCSpinEdit *CSpinEditNbMaxBetes;
    TPanel *Panel2;
    TLabel *LabelTitreNbCrtBetes;
    TLabel *LabelNbCrtBetes;
    TLabel *LabelBarre;
    TLabel *LabelDelai;
    TLabel *LabelEffet;
    TButton *ButtonOk;
    TButton *ButtonAnnuler;
    TCSpinEdit *CSpinEditBarre;
    TCSpinEdit *CSpinEditDelai;
    TCSpinEdit *CSpinEditEffet;
    TLabel *Label1;
    TEdit *EditNomSerie;
    TCSpinEdit *CSpinEditNbBetesAImmobiliser;
    TLabel *LabelNbBetesACapturer;
    TLabel *LabelNbMaxTours;
    TCSpinEdit *CSpinEditNbMaxTours;
    TCheckBox *CheckBoxBordure;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    
    void __fastcall CSpinEditNbMaxBetesChange(TObject *Sender);
    
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    __fastcall TfrmPrmNiveau(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrmNiveau *frmPrmNiveau;
//---------------------------------------------------------------------------
#endif
