//---------------------------------------------------------------------------
#ifndef f_deffpH
#define f_deffpH
//---------------------------------------------------------------------------
#include "CSPIN.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "base.h"
#include "simul.h"
//---------------------------------------------------------------------------
class TfrmDefFeuxPietons : public TForm
{
__published:	// Composants gérés par l'EDI
    TLabel *Label1;
    TLabel *LabelCoordonnees;
    TLabel *Label2;
    TLabel *LabelDirection;
    TLabel *Label3;
    TLabel *LabelNumero;
    TRadioGroup *RadioGroupEtat;
    TRadioGroup *RadioGroupTypeDmdVert;
    TGroupBox *GroupBoxDureeFeu;
    TCSpinEdit *CSpinEditDureeRouge;
    TLabel *Label5;
    TCSpinEdit *CSpinEditDureeVert;
    TLabel *Label4;
    TButton *ButtonOk;
    TButton *ButtonAnnuler;
    TButton *ButtonAppliquer;
    TRadioGroup *RadioGroupTypePsgRouge;
    TLabel *Label7;
    TLabel *LabelNbFeux;
    TSpeedButton *SpeedButtonSelFeux;
    TButton *ButtonAide;
    TLabel *Label6;
    TLabel *LabelCoordonneesFeuPietonsOppose;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *LabelDureeTraversee;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    
    void __fastcall RadioGroupEtatClick(TObject *Sender);
    void __fastcall RadioGroupTypeDmdVertClick(TObject *Sender);
    
    void __fastcall CSpinEditDureeVertChange(TObject *Sender);
    void __fastcall ButtonAppliquerClick(TObject *Sender);
    void __fastcall ButtonAnnulerClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall SpeedButtonSelFeuxClick(TObject *Sender);
    void __fastcall RadioGroupTypePsgRougeClick(TObject *Sender);
    
    
    void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:
    int Numero;
    feu_pieton *f;
    voie *v;
public:
    int x, y;
    int NbFeux, // Nbre de feux liés
        *NumFeux; // Liste des feux liés
    direction Direction;
    __fastcall TfrmDefFeuxPietons(TComponent* Owner);
    bool RafraichitInfos(); // retourne faux quand il n'a pas pu ajouté le feu
    void RafraichitFeuxPietons();
    void AnalyseEtatFeux(); // v5.2.1
    bool AppliqueChoix();
    void RafraichitInfosFeux();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDefFeuxPietons *frmDefFeuxPietons;
//---------------------------------------------------------------------------
#endif
