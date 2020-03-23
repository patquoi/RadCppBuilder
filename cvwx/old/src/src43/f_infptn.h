//---------------------------------------------------------------------------
#ifndef f_infptnH
#define f_infptnH
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
class TfrmInfosPieton : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonOk;
    TLabel *Label0;
    TLabel *LabelCoordonnees;
    TRadioButton *RadioButtonAucunPieton;
    TGroupBox *GroupBoxPieton;
    TRadioButton *RadioButtonPietonNumero;
    TLabel *Label3;
    TLabel *LabelSituation;
    TLabel *Label4;
    TLabel *LabelParcours;
    TLabel *Label1;
    TLabel *LabelDirection;
    TLabel *Label2;
    TLabel *LabelPosition;
    TButton *ButtonAide;
    TLabel *Label5;
  TLabel *LabelBusTramTaxi;
    TLabel *Label6;
  TLabel *LabelArretBusTramFileTaxi;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
    
private:	// Déclarations de l'utilisateur
    voie *v;
    pieton *p;
    int x, y, NumPieton;
    void RendreVisibleInfos(bool Visible);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmInfosPieton(TComponent* Owner);
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInfosPieton *frmInfosPieton;
//---------------------------------------------------------------------------
#endif
  