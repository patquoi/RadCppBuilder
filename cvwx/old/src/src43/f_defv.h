//---------------------------------------------------------------------------
#ifndef f_defvH
#define f_defvH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX 
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
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
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
#endif
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
    void __fastcall RadioGroupPrioriteNordClick(TObject *Sender);
    void __fastcall RadioGroupPrioriteEstClick(TObject *Sender);
    void __fastcall RadioGroupPrioriteSudClick(TObject *Sender);
    void __fastcall RadioGroupPrioriteOuestClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);


    void __fastcall BitBtnDefFeuNClick(TObject *Sender);
    void __fastcall BitBtnDefFeuEClick(TObject *Sender);
    void __fastcall BitBtnDefFeuSClick(TObject *Sender);
    void __fastcall BitBtnDefFeuOClick(TObject *Sender);
    
    
    
    
    void __fastcall ButtonAppliquerClick(TObject *Sender);
    void __fastcall ButtonAnnulerClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
    voie *v;
    int x, y;
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
