//---------------------------------------------------------------------------
#ifndef f_infbusH
#define f_infbusH
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
class TfrmInfosBus : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonOk;
    TLabel *Label0;
    TLabel *LabelCoordonnees;
    TRadioButton *RadioButtonAucunBus;
    TGroupBox *GroupBoxBus;
    TRadioButton *RadioButtonBusNumero;
    TLabel *Label3;
    TLabel *Label5;
    TLabel *LabelDernierArret;
    TLabel *LabelTourSortie;
    TLabel *Label7;
    TLabel *LabelParcours;
    TLabel *Label1;
    TLabel *LabelDirection;
    TLabel *Label10;
    TLabel *LabelParcoursEffectue;
    TLabel *Label11;
    TLabel *LabelDetour;
    TLabel *Label12;
    TLabel *Label6;
    TLabel *LabelTours;
    TLabel *Label13;
    TLabel *LabelAttente;
    TLabel *LabelVitesse;
    TButton *ButtonAide;
    TLabel *Label2;
    TLabel *LabelNumeroLigne;
    TLabel *Label8;
    TLabel *LabelDistance;
    TLabel *LabelDistanceMin;
    TLabel *Label4;
    TLabel *LabelProchainArret;
    TLabel *Label9;
    TLabel *Label14;
    TLabel *LabelNbPersonnes;
    TLabel *Label17;
    TLabel *Label18;
    TLabel *Label15;
    TLabel *LabelParcoursEntreArrets;
    TLabel *Label16;
    TLabel *LabelToursEntreArrets;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
    voie *v;
    bus *Bus;
    int x, y;
    void RendreVisibleInfos(bool Visible);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmInfosBus(TComponent* Owner);
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInfosBus *frmInfosBus;
//---------------------------------------------------------------------------
#endif
  