//---------------------------------------------------------------------------
#ifndef f_infvehlibH
#define f_infvehlibH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "simul.h"
//---------------------------------------------------------------------------
class TfrmInfosVehlib : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonOk;
    TLabel *Label0;
    TLabel *LabelCoordonnees;
    TRadioButton *RadioButtonAucunVehlib;
    TGroupBox *GroupBoxVehlib;
    TRadioButton *RadioButtonVehlibNumero;
    TLabel *Label6;
    TLabel *LabelParcours;
    TLabel *Label2;
    TLabel *LabelDirection;
        TLabel *Label10;
    TLabel *LabelVitesse;
    TButton *ButtonAide;
    TLabel *Label3;
        TLabel *LabelNumeroPlaceDepart;
    TLabel *Label8;
    TLabel *LabelParcoursDepuisDepart;
    TLabel *Label7;
    TLabel *LabelToursDepuisDepart;
    TLabel *Label1;
    TLabel *LabelSituation;
        TLabel *Label9;
        TLabel *LabelDistancePlaceArrivee;
        TLabel *Label4;
        TLabel *LabelNumeroPlaceArrivee;
        TLabel *Label5;
    TLabel *LabelNbPersonnes;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Déclarations de l'utilisateur
    voie *v;
    vehlib *Vehlib;
    int x, y;
    void RendreVisibleInfos(bool Visible);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmInfosVehlib(TComponent* Owner);
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInfosVehlib *frmInfosVehlib;
//---------------------------------------------------------------------------
#endif

