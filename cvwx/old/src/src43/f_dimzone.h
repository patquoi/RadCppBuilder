//---------------------------------------------------------------------------
#ifndef f_dimzoneH
#define f_dimzoneH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#include <QForms.hpp>
#include <QComCtrls.hpp>
#include "CSPIN.h"
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#include <QForms.hpp>
#include <QComCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#include "winlinux.h"
//---------------------------------------------------------------------------
class TfrmDimensionsZone : public TForm
{
__published:	// Composants gérés par l'EDI
  TSPINEDIT *CSpinEditNbX;
  TSPINEDIT *CSpinEditNbY;
  TLabel *Label1;
  TLabel *Label2;
  TButton *ButtonCreer;
  TButton *ButtonAnnuler;
  TButton *ButtonAide;
  TCheckBox *CheckBoxAfficherParametres;
  TCheckBox *CheckBoxGenererReseau;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ButtonCreerClick(TObject *Sender);
  void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
 int NbX, NbY;
  __fastcall TfrmDimensionsZone(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmDimensionsZone *frmDimensionsZone;
extern bool DefinitDimensionsZone(int &NbX, int &NbY, bool &GenereReseau);
//---------------------------------------------------------------------------
#endif
