//---------------------------------------------------------------------------
#ifndef f_prmsimH
#define f_prmsimH
//---------------------------------------------------------------------------
#include "CSPIN.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include "base.h"
//---------------------------------------------------------------------------
class TfrmParamSimul : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonOk;
    TButton *ButtonAnnuler;
    TGroupBox *GroupBoxNbElements;
    TLabel *LabelNbVehicules;
 TCSpinEdit *CSpinEditNbVehicules;
    TGroupBox *GroupBoxFonctionnement;
 TCSpinEdit *CSpinEditAttenteAvChx;
    TLabel *LabelTours;
    TLabel *LabelAttenteAvChx;
    TButton *ButtonAppliquer;
    TLabel *LabelNbToursParSeconde;
 TCSpinEdit *CSpinEditNbToursParSeconde;
    TLabel *LabelDureeOrange;
 TCSpinEdit *CSpinEditDureeOrange;
    TLabel *LabelDureeRouge;
 TCSpinEdit *CSpinEditDureeRouge;
    TLabel *LabelDureeVert;
 TCSpinEdit *CSpinEditDureeVert;
    TBitBtn *BitBtnAppliqueDureeFeuVert;
    TBitBtn *BitBtnAppliqueDureeFeuRouge;
    TRadioGroup *RadioGroupVitesses;
    TLabel *LabelNbPietons;
 TCSpinEdit *CSpinEditNbPietons;
    TLabel *Label1;
    TGroupBox *GroupBoxPietons;
    TLabel *LabelNbCasesMaxPsgPtn;
 TCSpinEdit *CSpinEditNbCasesMaxPsgPtn;
    TLabel *Label4;
    TLabel *LabelProbaPsgPt;
 TCSpinEdit *CSpinEditProbaPsgPt;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *LabelNbArretsBus;
    TBitBtn *BitBtnDefLignesBus;
    TButton *ButtonAide;
    TLabel *LabelNbArretsTram;
    TBitBtn *BitBtnDefLignesTram;
    TLabel *LabelNbPlacesTaxi;
    TBitBtn *BitBtnDefTaxis;
  TLabel *Label2;
        TBitBtn *BitBtnDefVehlibs;
    void __fastcall CSpinEditNbVehiculesChange(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);

    void __fastcall ButtonAppliquerClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);

    void __fastcall BitBtnAppliqueDureeFeuVertClick(TObject *Sender);
    void __fastcall BitBtnAppliqueDureeFeuRougeClick(TObject *Sender);
    void __fastcall CSpinEditDureeVertChange(TObject *Sender);
    void __fastcall CSpinEditDureeRougeChange(TObject *Sender);
    void __fastcall CSpinEditNbPietonsChange(TObject *Sender);
    void __fastcall Change(TObject *Sender);
    void __fastcall BitBtnDefLignesBusClick(TObject *Sender);
    
    void __fastcall ButtonAideClick(TObject *Sender);
    void __fastcall BitBtnDefLignesTramClick(TObject *Sender);
    void __fastcall BitBtnDefTaxisClick(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BitBtnDefVehlibsClick(TObject *Sender);
private:	// Déclarations de l'utilisateur
    bool NbVehiculesChange,
         NbPietonsChange, // v2.0
         NbFeuxChange,
         NbParkingsChange,
         NbArretsBusChange, // v3.0
         NbArretsTramChange, // v3.5
         NbPlacesTaxiChange, // v3.6
         NbPlacesParkChange, // v5.0
         Initialisation;
    bool AppliqueChoix();
    void CalculeChoixPossiblesNbVehicules(); // v5.0
public:		// Déclarations de l'utilisateur
    __fastcall TfrmParamSimul(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmParamSimul *frmParamSimul;
extern void Parametres();
//---------------------------------------------------------------------------
#endif
