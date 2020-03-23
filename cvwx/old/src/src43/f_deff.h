//---------------------------------------------------------------------------
#ifndef F_deffH
#define F_deffH
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

#ifdef CV_WINDOWS
#include "CSPIN.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#endif

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
    TCheckBox *CheckBoxDemandeVert;
    TRadioGroup *RadioGroupTypeDmdVert;
    TGroupBox *GroupBoxDureeFeu;
    TSPINEDIT *CSpinEditDureeRouge;
    TLabel *Label5;
    TSPINEDIT *CSpinEditDureeVert;
    TLabel *Label4;
    TButton *ButtonOk;
    TButton *ButtonAnnuler;
    TButton *ButtonAppliquer;
    TRadioGroup *RadioGroupTypePsgRouge;
    TCheckBox *CheckBoxRougeDemande;
    TLabel *Label6;
    TLabel *LabelNbFeuxDmd;
    TSpeedButton *SpeedButtonSelFeuxDmd;
    TLabel *Label7;
    TLabel *LabelNbFeuxAtt;
    TSpeedButton *SpeedButtonSelFeuxAtt;
    TButton *ButtonAide;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    
    void __fastcall RadioGroupEtatClick(TObject *Sender);
    void __fastcall RadioGroupTypeDmdVertClick(TObject *Sender);
    void __fastcall CheckBoxDemandeVertClick(TObject *Sender);
    
    void __fastcall CSpinEditDureeVertChange(TObject *Sender);
    void __fastcall ButtonAppliquerClick(TObject *Sender);
    void __fastcall ButtonAnnulerClick(TObject *Sender);
    
    void __fastcall SpeedButtonSelFeuxDmdClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall SpeedButtonSelFeuxAttClick(TObject *Sender);
    void __fastcall CheckBoxRougeDemandeClick(TObject *Sender);
    void __fastcall RadioGroupTypePsgRougeClick(TObject *Sender);
    
    
    void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
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
    void ControleDemandeEtPassage();
    bool RafraichitInfos(); // retourne faux quand il n'a pas pu ajouté le feu
    bool AppliqueChoix();
    void RafraichitInfosFeuxDmd();
    void RafraichitInfosFeuxAtt();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDefFeux *frmDefFeux;
//---------------------------------------------------------------------------
#endif
 