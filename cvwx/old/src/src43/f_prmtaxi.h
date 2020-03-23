//---------------------------------------------------------------------------
#ifndef f_prmtaxiH
#define f_prmtaxiH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include "CSPIN.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include "CSPIN.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#include "winlinux.h"
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
        TSPINEDIT *CSpinEditNbCasesMaxPlaceTaxi;
        TSPINEDIT *CSpinEditNbMaxToursAttenteBus;
        TSPINEDIT *CSpinEditProbaDirPlaceTaxi;
        TSPINEDIT *CSpinEditProbaArretDmd;
        TButton *ButtonOk;
        TButton *ButtonAnnuler;
        TButton *ButtonAppliquer;
        TButton *ButtonAide;
        TLabel *Label21;
        TSPINEDIT *CSpinEditNbMaxPersonnesTaxi;
        TLabel *Label22;
        void __fastcall ButtonOkClick(TObject *Sender);
        void __fastcall ButtonAppliquerClick(TObject *Sender);
        void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CSpinEditParametresChange(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
    bool InitialisationEnCours;
    void AppliqueChoix();
public:		// Déclarations de l'utilisateur
        __fastcall TfrmParamTaxi(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmParamTaxi *frmParamTaxi;
//---------------------------------------------------------------------------
#endif
