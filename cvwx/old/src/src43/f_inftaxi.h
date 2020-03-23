//---------------------------------------------------------------------------
#ifndef f_inftaxiH
#define f_inftaxiH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#endif

#ifdef CV_WINDOWS
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#endif

#ifdef CV_LINUX
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#endif

#include "simul.h"
//---------------------------------------------------------------------------
class TfrmInfosTaxi : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonOk;
    TLabel *Label0;
    TLabel *LabelCoordonnees;
        TRadioButton *RadioButtonAucunTaxi;
        TGroupBox *GroupBoxTaxi;
        TRadioButton *RadioButtonTaxiNumero;
        TLabel *Label4;
  TLabel *LabelTeteFileOrigine;
        TLabel *Label6;
    TLabel *LabelParcours;
        TLabel *Label2;
    TLabel *LabelDirection;
        TLabel *Label9;
    TLabel *LabelVitesse;
    TButton *ButtonAide;
        TLabel *Label3;
        TLabel *LabelNumeroFile;
        TLabel *Label5;
    TLabel *LabelNbPersonnes;
        TLabel *Label8;
        TLabel *LabelParcoursDepuisDepart;
        TLabel *Label7;
        TLabel *LabelToursDepuisDepart;
        TLabel *Label1;
  TLabel *LabelSituation;
  TLabel *Label10;
  TLabel *LabelToursDepuisDepot;
  TLabel *Label11;
  TLabel *LabelToursDepuisRetour;
  TLabel *Label12;
  TLabel *LabelDistanceTeteFileDepart;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
    voie *v;
    taxi *Taxi;
    int x, y;
    void RendreVisibleInfos(bool Visible);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmInfosTaxi(TComponent* Owner);
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInfosTaxi *frmInfosTaxi;
//---------------------------------------------------------------------------
#endif
  