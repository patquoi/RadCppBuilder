//---------------------------------------------------------------------------

#ifndef param_fH
#define param_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormParametres : public TForm
{
__published:	// Composants gérés par l'EDI
  TRadioGroup *RadioGroupNbCamps;
  TRadioGroup *RadioGroupNbMaxLettresAPlacer;
  TButton *ButtonVu;
  TButton *ButtonAnnuler;
  TGroupBox *GroupBox1;
  TRadioButton *RadioButton7;
  TRadioButton *RadioButton8;
  TRadioButton *RadioButton9;
  TRadioButton *RadioButton10;
  TRadioButton *RadioButton11;
  TRadioButton *RadioButton12;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ButtonVuClick(TObject *Sender);
  void __fastcall RadioButton7Click(TObject *Sender);
  void __fastcall RadioGroupNbMaxLettresAPlacerClick(TObject *Sender);
private:	// Déclarations de l'utilisateur
  int NbHexagonesDeCote;
public:		// Déclarations de l'utilisateur
  __fastcall TFormParametres(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormParametres *FormParametres;
//---------------------------------------------------------------------------
#endif
