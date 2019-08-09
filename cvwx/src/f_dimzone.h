//---------------------------------------------------------------------------
#ifndef f_dimzoneH
#define f_dimzoneH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
#include "base.h"
//---------------------------------------------------------------------------
class TfrmDimensionsZone : public TForm
{
__published:	// Composants g�r�s par l'EDI
  TCSpinEdit *CSpinEditNbX;
  TCSpinEdit *CSpinEditNbY;
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
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
  int NbX, NbY;
  __fastcall TfrmDimensionsZone(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDimensionsZone *frmDimensionsZone;
extern bool DefinitDimensionsZone(int &NbX, int &NbY, bool &GenereReseau);
//---------------------------------------------------------------------------
#endif
