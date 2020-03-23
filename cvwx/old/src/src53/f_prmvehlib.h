//---------------------------------------------------------------------------
#ifndef f_prmvehlibH
#define f_prmvehlibH
//---------------------------------------------------------------------------
#include "CSPIN.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "base.h"
//---------------------------------------------------------------------------
class TfrmParamVehlib : public TForm
{
__published:	// Composants gérés par l'EDI
        TLabel *Label21;
        TCSpinEdit *CSpinEditNbMaxPersonnesVehlib;
        TLabel *Label22;
        TGroupBox *GroupBox;
        TLabel *LabelNbCasesMaxPsgPtn;
        TLabel *Label23;
        TLabel *LabelProbaVehlib;
        TLabel *Label25;
        TCSpinEdit *CSpinEditNbCasesMaxPlaceVehlib;
        TCSpinEdit *CSpinEditProbaDirPlaceVehlib;
        TButton *ButtonOk;
        TButton *ButtonAnnuler;
        TButton *ButtonAppliquer;
        TButton *ButtonAide;
        TLabel *Label1;
        TCSpinEdit *CSpinEditTauxRemplissage;
        TLabel *Label2;
        TLabel *Label3;
        void __fastcall ButtonOkClick(TObject *Sender);
        void __fastcall ButtonAppliquerClick(TObject *Sender);
        void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CSpinEditParametresChange(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private: // Déclarations de l'utilisateur
        bool InitialisationEnCours;
        void AppliqueChoix();
public:	 // Déclarations de l'utilisateur
        __fastcall TfrmParamVehlib(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmParamVehlib *frmParamVehlib;
//---------------------------------------------------------------------------
#endif
