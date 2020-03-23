//---------------------------------------------------------------------------
#ifndef F_deffH
#define F_deffH
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
class TfrmDefFeux : public TForm
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
    TLabel *Label6;
    TLabel *LabelNbFeuxDmd;
    TSpeedButton *SpeedButtonSelFeuxDmd;
    TLabel *Label7;
    TLabel *LabelNbFeuxAtt;
    TSpeedButton *SpeedButtonSelFeuxAtt;
    TButton *ButtonAide;
    TLabel *Label8;
    TLabel *LabelFeuxPietons;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    
    void __fastcall RadioGroupEtatClick(TObject *Sender);
    void __fastcall RadioGroupTypeDmdVertClick(TObject *Sender);
    
    void __fastcall CSpinEditDureeVertChange(TObject *Sender);
    void __fastcall ButtonAppliquerClick(TObject *Sender);
    void __fastcall ButtonAnnulerClick(TObject *Sender);
    
    void __fastcall SpeedButtonSelFeuxDmdClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall SpeedButtonSelFeuxAttClick(TObject *Sender);
    void __fastcall RadioGroupTypePsgRougeClick(TObject *Sender);
    
    
    void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:
    int Numero;
    feu *f;
    voie *v;
public:
    int x, y;
    int NbFeuxDmd, // Nbre de feux demandant le rouge
        NbFeuxAtt,// Nbre de feux devant être rouge pour que Numero passe au vert
        *NumFeuxDmd, // Liste des feux demandant le rouge
        *NumFeuxAtt; // Liste des feux devant être rouge pour que Numero passe au vert
    direction Direction;
    __fastcall TfrmDefFeux(TComponent* Owner);
    bool RafraichitInfos(); // retourne faux quand il n'a pas pu ajouter le feu
    bool AppliqueChoix();
    void RafraichitInfosFeuxDmd();
    void RafraichitInfosFeuxAtt();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDefFeux *frmDefFeux;
//---------------------------------------------------------------------------
#endif
 