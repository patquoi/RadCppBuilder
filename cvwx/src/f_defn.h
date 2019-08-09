//---------------------------------------------------------------------------
#ifndef f_defnH
#define f_defnH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmDefNature : public TForm
{
__published:	// Composants g�r�s par l'EDI
  TRadioGroup *RadioGroupNature;
  TCheckBox *CheckBoxEcraser;
  TButton *ButtonAppliquer;
  TButton *ButtonFermer;
  TButton *ButtonAide;
  TLabel *LabelRq;
  TCheckBox *CheckBoxPelouse;
  void __fastcall RadioGroupNatureClick(TObject *Sender);
  void __fastcall ButtonAppliquerClick(TObject *Sender);
  void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall ButtonFermerClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
  __fastcall TfrmDefNature(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDefNature *frmDefNature;
//---------------------------------------------------------------------------
#endif
