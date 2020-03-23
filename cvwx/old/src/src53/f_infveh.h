//---------------------------------------------------------------------------
#ifndef f_infvehH
#define f_infvehH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "simul.h"
//v5.0 ----------------------------------------------------------------------
#define DEPART   0
#define ARRIVEE  1
#define PARKING  0
#define FILEPARK 1
//---------------------------------------------------------------------------
class TfrmInfosVehicule : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonOk;
    TLabel *Label0;
    TLabel *LabelCoordonnees;
    TRadioButton *RadioButtonAucunVehicule;
    TGroupBox *GroupBoxVehicule;
    TRadioButton *RadioButtonVehiculeNumero;
  TLabel *LabelDepart;
  TLabel *LabelArrivee;
    TLabel *Label4;
    TLabel *Label7;
  TLabel *LabelParkingDepart;
  TLabel *LabelParkingArrivee;
    TLabel *LabelTourSortie;
    TLabel *LabelDistance;
    TLabel *Label6;
    TLabel *LabelParcours;
  TLabel *Label3;
    TLabel *LabelDirection;
    TLabel *Label8;
    TLabel *LabelDistanceMin;
    TLabel *Label9;
    TLabel *LabelParcoursEffectue;
    TLabel *Label10;
    TLabel *LabelDetour;
    TLabel *Label11;
    TLabel *Label5;
    TLabel *LabelTours;
    TLabel *Label12;
    TLabel *LabelAttente;
    TLabel *LabelVitesse;
    TLabel *Label13;
    TLabel *LabelNivPriorite;
    TButton *ButtonAide;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Déclarations de l'utilisateur
    voie *v;
    vehicule *Veh;
    int x, y;
    void RendreVisibleInfos(bool Visible);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmInfosVehicule(TComponent* Owner);
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInfosVehicule *frmInfosVehicule;
//---------------------------------------------------------------------------
#endif
  