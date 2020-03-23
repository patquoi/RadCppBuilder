//---------------------------------------------------------------------------
#ifndef f_rechH
#define f_rechH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include "CSPIN.h"
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include "CSPIN.h"
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#include "winlinux.h"
//---------------------------------------------------------------------------
class TfrmRecherche : public TForm
{
__published:	// Composants gérés par l'EDI
    TRadioButton *RadioButtonCoordonnees;
    TSPINEDIT *CSpinEditX;
    TSPINEDIT *CSpinEditY;
    TRadioButton *RadioButtonEtape;
    TLabel *Label1;
    TSPINEDIT *CSpinEditEtape;
    TRadioButton *RadioButtonFeu;
    TSPINEDIT *CSpinEditFeu;
    TButton *ButtonAnnuler;
    TRadioButton *RadioButtonVehicule;
    TSPINEDIT *CSpinEditVehicule;
    TSPINEDIT *CSpinEditPieton;
    TRadioButton *RadioButtonPieton;
    TStatusBar *StatusBar;
    TButton *ButtonAide;
    TRadioButton *RadioButtonArretBus;
    TSPINEDIT *CSpinEditArretBus;
    TSPINEDIT *CSpinEditBus;
    TRadioButton *RadioButtonBus;
    TRadioButton *RadioButtonArretTram;
    TSPINEDIT *CSpinEditArretTram;
    TRadioButton *RadioButtonTram;
    TSPINEDIT *CSpinEditTram;
    TRadioButton *RadioButtonTaxi;
    TSPINEDIT *CSpinEditTaxi;
    TRadioButton *RadioButtonPlaceTaxi;
    TSPINEDIT *CSpinEditPlaceTaxi;
    TRadioButton *RadioButtonFileTaxi;
    TSPINEDIT *CSpinEditFileTaxi;
    void __fastcall RadioButtonClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall CSpinEditXChange(TObject *Sender);
    void __fastcall CSpinEditYChange(TObject *Sender);
    void __fastcall CSpinEditEtapeChange(TObject *Sender);
    void __fastcall CSpinEditFeuChange(TObject *Sender);
    
    void __fastcall CSpinEditVehiculeChange(TObject *Sender);
    void __fastcall ButtonAnnulerClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall CSpinEditPietonChange(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
    void __fastcall CSpinEditArretBusChange(TObject *Sender);
    void __fastcall CSpinEditBusChange(TObject *Sender);
    void __fastcall CSpinEditArretTramChange(TObject *Sender);
    void __fastcall CSpinEditTramChange(TObject *Sender);
    void __fastcall CSpinEditTaxiChange(TObject *Sender);
    void __fastcall CSpinEditPlaceTaxiChange(TObject *Sender);
    void __fastcall CSpinEditFileTaxiChange(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
    int xPrc, yPrc;
    void RafraichitAffichage();
public:		// Déclarations de l'utilisateur
    __fastcall TfrmRecherche(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRecherche *frmRecherche;
//---------------------------------------------------------------------------
#endif
