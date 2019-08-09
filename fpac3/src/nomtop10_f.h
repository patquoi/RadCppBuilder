//---------------------------------------------------------------------------

#ifndef nomtop10_fH
#define nomtop10_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormNomTop10 : public TForm
{
__published:	// Composants gérés par l'EDI
  TLabel *Label1;
  TEdit *EditNom;
  TButton *ButtonOK;
  TButton *ButtonAnnuler;
  void __fastcall EditNomChange(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
  __fastcall TFormNomTop10(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNomTop10 *FormNomTop10;
//---------------------------------------------------------------------------
#endif
