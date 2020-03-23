//---------------------------------------------------------------------------
#ifndef f_infvehH
#define f_infvehH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#include "simul.h"
//---------------------------------------------------------------------------
class TfrmInfosVehicule : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonOk;
    TLabel *Label0;
    TLabel *LabelCoordonnees;
    TRadioButton *RadioButtonAucunVehicule;
    TGroupBox *GroupBoxVehicule;
    TRadioButton *RadioButtonVehiculeNumero;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label7;
    TLabel *LabelEtapeDepart;
    TLabel *LabelEtapeArrivee;
    TLabel *LabelTourSortie;
    TLabel *LabelDistance;
    TLabel *Label6;
    TLabel *LabelParcours;
    TLabel *Label1;
    TLabel *LabelDirection;
    TLabel *Label8;
    TLabel *LabelDistanceMin;
    TLabel *Label9;
    TLabel *LabelParcoursEffectue;
    TLabel *Label10;
    TLabel *LabelDetour;
    TLabel *Label11;
    TLabel *Label5;
    TLabel *LabelTours;
    TLabel *Label12;
    TLabel *LabelAttente;
    TLabel *LabelVitesse;
    TLabel *Label13;
    TLabel *LabelNivPriorite;
    TButton *ButtonAide;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
    voie *v;
    vehicule *Veh;
    int x, y;
    void RendreVisibleInfos(bool Visible);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmInfosVehicule(TComponent* Owner);
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInfosVehicule *frmInfosVehicule;
//---------------------------------------------------------------------------
#endif
  