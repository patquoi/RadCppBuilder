//---------------------------------------------------------------------------
#ifndef f_prmsimH
#define f_prmsimH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include "CSPIN.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QStdCtrls.hpp>
#include <QComCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include "CSPIN.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QStdCtrls.hpp>
#include <QComCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#include "winlinux.h"
//---------------------------------------------------------------------------
class TfrmParamSimul : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonOk;
    TButton *ButtonAnnuler;
    TGroupBox *GroupBoxNbElements;
    TLabel *LabelNbVehicules;
    TSPINEDIT *CSpinEditNbVehicules;
    TLabel *LabelNbFeux;
    TSPINEDIT *CSpinEditNbFeux;
    TLabel *LabelNbEtapes;
    TSPINEDIT *CSpinEditNbEtapes;
    TGroupBox *GroupBoxFonctionnement;
    TSPINEDIT *CSpinEditAttenteAvChx;
    TLabel *LabelTours;
    TLabel *LabelAttenteAvChx;
    TButton *ButtonAppliquer;
    TLabel *LabelNbToursParSeconde;
    TSPINEDIT *CSpinEditNbToursParSeconde;
    TLabel *LabelDureeOrange;
    TSPINEDIT *CSpinEditDureeOrange;
    TLabel *LabelDureeRouge;
    TSPINEDIT *CSpinEditDureeRouge;
    TLabel *LabelDureeVert;
    TSPINEDIT *CSpinEditDureeVert;
    TBitBtn *BitBtnAppliqueDureeFeuVert;
    TBitBtn *BitBtnAppliqueDureeFeuRouge;
    TCheckBox *CheckBoxMaintenus;
    TRadioGroup *RadioGroupVitesses;
    TLabel *LabelNbPietons;
    TSPINEDIT *CSpinEditNbPietons;
    TLabel *Label1;
    TGroupBox *GroupBoxPietons;
    TLabel *LabelNbCasesMaxPsgPtn;
    TSPINEDIT *CSpinEditNbCasesMaxPsgPtn;
    TLabel *Label4;
    TLabel *LabelProbaPsgPt;
    TSPINEDIT *CSpinEditProbaPsgPt;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *LabelNbArretsBus;
    TSPINEDIT *CSpinEditNbArretsBus;
    TBitBtn *BitBtnDefLignesBus;
    TButton *ButtonAide;
    TLabel *LabelNbArretsTram;
    TLabel *Label2;
    TSPINEDIT *CSpinEditNbArretsTram;
    TBitBtn *BitBtnDefLignesTram;
    TLabel *LabelNbPlacesTaxi;
    TSPINEDIT *CSpinEditNbPlacesTaxi;
    TBitBtn *BitBtnDefTaxis;
    void __fastcall CSpinEditNbVehiculesChange(TObject *Sender);
    void __fastcall CSpinEditNbFeuxChange(TObject *Sender);
    void __fastcall CSpinEditNbEtapesChange(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);

    void __fastcall ButtonAppliquerClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);

    void __fastcall BitBtnAppliqueDureeFeuVertClick(TObject *Sender);
    void __fastcall BitBtnAppliqueDureeFeuRougeClick(TObject *Sender);
    void __fastcall CSpinEditDureeVertChange(TObject *Sender);
    void __fastcall CSpinEditDureeRougeChange(TObject *Sender);
    void __fastcall CSpinEditNbPietonsChange(TObject *Sender);
    void __fastcall Change(TObject *Sender);
    void __fastcall CSpinEditNbArretsBusChange(TObject *Sender);
    void __fastcall BitBtnDefLignesBusClick(TObject *Sender);
    
    void __fastcall ButtonAideClick(TObject *Sender);
    void __fastcall CSpinEditNbArretsTramChange(TObject *Sender);
    void __fastcall BitBtnDefLignesTramClick(TObject *Sender);
  void __fastcall CSpinEditNbPlacesTaxiChange(TObject *Sender);
        void __fastcall BitBtnDefTaxisClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);

private:	// Déclarations de l'utilisateur
    bool NbVehiculesChange,
         NbPietonsChange, // v2.0
         NbFeuxChange,
         NbEtapesChange,
         NbArretsBusChange, // v3.0
         NbArretsTramChange, // v3.5
         NbPlacesTaxiChange, // v3.6
         Initialisation;
    bool AppliqueChoix();
public:		// Déclarations de l'utilisateur
    __fastcall TfrmParamSimul(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmParamSimul *frmParamSimul;
extern void Parametres();
//---------------------------------------------------------------------------
#endif
