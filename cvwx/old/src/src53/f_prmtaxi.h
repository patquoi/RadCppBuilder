//---------------------------------------------------------------------------
#ifndef f_prmtaxiH
#define f_prmtaxiH
//---------------------------------------------------------------------------
#include "CSPIN.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "base.h"
//---------------------------------------------------------------------------
class TfrmParamTaxi : public TForm
{
__published:	// Composants gérés par l'EDI
        TGroupBox *GroupBox;
        TLabel *LabelNbCasesMaxPsgPtn;
        TLabel *Label23;
        TLabel *Label24;
        TLabel *Label17;
        TLabel *LabelProbaPsgPt;
        TLabel *Label25;
        TLabel *Label26;
        TLabel *Label27;
        TCSpinEdit *CSpinEditNbCasesMaxPlaceTaxi;
        TCSpinEdit *CSpinEditNbMaxToursAttente;
        TCSpinEdit *CSpinEditProbaDirPlaceTaxi;
        TCSpinEdit *CSpinEditProbaArretDmd;
        TButton *ButtonOk;
        TButton *ButtonAnnuler;
        TButton *ButtonAppliquer;
        TButton *ButtonAide;
        TLabel *Label21;
        TCSpinEdit *CSpinEditNbMaxPersonnesTaxi;
        TLabel *Label22;
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
public:	// Déclarations de l'utilisateur
        __fastcall TfrmParamTaxi(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmParamTaxi *frmParamTaxi;
//---------------------------------------------------------------------------
#endif
