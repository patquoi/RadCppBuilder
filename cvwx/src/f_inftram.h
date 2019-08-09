//---------------------------------------------------------------------------
#ifndef f_inftramH
#define f_inftramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "simul.h"
//---------------------------------------------------------------------------
class TfrmInfosTram : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonOk;
    TLabel *Label0;
    TLabel *LabelCoordonnees;
    TRadioButton *RadioButtonAucunTram;
    TGroupBox *GroupBoxTram;
    TRadioButton *RadioButtonTramNumero;
    TLabel *Label3;
    TLabel *LabelDernierArret;
  TLabel *Label6;
    TLabel *LabelParcours;
    TLabel *Label1;
    TLabel *LabelDirection;
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
    TButton *ButtonAide;
    TLabel *Label2;
    TLabel *LabelNumeroLigne;
  TLabel *Label7;
    TLabel *LabelDistance;
    TLabel *LabelDistanceMin;
    TLabel *Label4;
    TLabel *LabelProchainArret;
  TLabel *Label8;
  TLabel *Label13;
    TLabel *LabelNbPersonnes;
    TLabel *Label17;
    TLabel *Label18;
  TLabel *Label14;
    TLabel *LabelParcoursEntreArrets;
  TLabel *Label15;
    TLabel *LabelToursEntreArrets;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Déclarations de l'utilisateur
    voie *v;
    tram *Tram;
    int x, y;
    void RendreVisibleInfos(bool Visible);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmInfosTram(TComponent* Owner);
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInfosTram *frmInfosTram;
//---------------------------------------------------------------------------
#endif
