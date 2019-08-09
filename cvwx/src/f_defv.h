//---------------------------------------------------------------------------
#ifndef f_defvH
#define f_defvH
//---------------------------------------------------------------------------
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "simul.h"
//---------------------------------------------------------------------------
class TfrmDefVoie : public TForm
{
__published:	// Composants gérés par l'EDI
    TLabel *Label1;
    TLabel *LabelCoordonnees;
    TRadioGroup *RadioGroupPrioriteNord;
    TRadioGroup *RadioGroupPrioriteOuest;
    TRadioGroup *RadioGroupPrioriteEst;
    TRadioGroup *RadioGroupPrioriteSud;
    TButton *ButtonOk;
    TButton *ButtonAnnuler;
    TBitBtn *BitBtnDefFeuN;
    TBitBtn *BitBtnDefFeuO;
    TBitBtn *BitBtnDefFeuE;
    TBitBtn *BitBtnDefFeuS;
    TButton *ButtonAppliquer;
    TButton *ButtonAide;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAppliquerClick(TObject *Sender);
    void __fastcall ButtonAnnulerClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
    void __fastcall BitBtnDefFeuClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall RadioGroupPrioriteClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Déclarations de l'utilisateur
    voie *v;
    int x, y;
    TBitBtn *BitBtn[NBDIR]; // v5.2 
    void DefinitFeu(direction Dir);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmDefVoie(TComponent* Owner);
    void RafraichitInfos();
    void AppliqueChoix();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDefVoie *frmDefVoie;
//---------------------------------------------------------------------------
#endif
