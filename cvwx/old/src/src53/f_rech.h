//---------------------------------------------------------------------------
#ifndef f_rechH
#define f_rechH
//---------------------------------------------------------------------------
#include "CSPIN.h"
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "base.h"
//---------------------------------------------------------------------------
class TfrmRecherche : public TForm
{
__published:	// Composants gérés par l'EDI
  TRadioButton *RadioButtonCoordonnees;
  TCSpinEdit *CSpinEditX;
  TCSpinEdit *CSpinEditY;
  TRadioButton *RadioButtonParking;
  TLabel *Label1;
  TCSpinEdit *CSpinEditParking;
  TRadioButton *RadioButtonFeu;
  TCSpinEdit *CSpinEditFeu;
  TButton *ButtonAnnuler;
  TRadioButton *RadioButtonVehicule;
  TCSpinEdit *CSpinEditVehicule;
  TCSpinEdit *CSpinEditPieton;
  TRadioButton *RadioButtonPieton;
  TStatusBar *StatusBar;
  TButton *ButtonAide;
  TRadioButton *RadioButtonArretBus;
  TCSpinEdit *CSpinEditArretBus;
  TCSpinEdit *CSpinEditBus;
  TRadioButton *RadioButtonBus;
  TRadioButton *RadioButtonArretTram;
  TCSpinEdit *CSpinEditArretTram;
  TRadioButton *RadioButtonTram;
  TCSpinEdit *CSpinEditTram;
  TRadioButton *RadioButtonTaxi;
  TCSpinEdit *CSpinEditTaxi;
  TRadioButton *RadioButtonPlaceTaxi;
  TCSpinEdit *CSpinEditPlaceTaxi;
  TRadioButton *RadioButtonFileTaxi;
  TCSpinEdit *CSpinEditFileTaxi;
  TRadioButton *RadioButtonPlacePark;
  TCSpinEdit *CSpinEditPlacePark;
  TRadioButton *RadioButtonFilePark;
  TCSpinEdit *CSpinEditFilePark;
  TRadioButton *RadioButtonVehlib;
  TCSpinEdit *CSpinEditVehlib;
  TRadioButton *RadioButtonPlaceVehlib;
  TCSpinEdit *CSpinEditPlaceVehlib;
  void __fastcall RadioButtonClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall CSpinEditXChange(TObject *Sender);
  void __fastcall CSpinEditYChange(TObject *Sender);
  void __fastcall CSpinEditParkingChange(TObject *Sender);
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
  void __fastcall CSpinEditPlaceParkChange(TObject *Sender);
  void __fastcall CSpinEditFileParkChange(TObject *Sender);
  void __fastcall CSpinEditVehlibChange(TObject *Sender);
  void __fastcall CSpinEditPlaceVehlibChange(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
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
