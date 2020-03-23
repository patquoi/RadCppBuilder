//---------------------------------------------------------------------------
#ifndef f_defnH
#define f_defnH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
class TfrmDefNature : public TForm
{
__published:	// Composants gérés par l'EDI
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
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall ButtonFermerClick(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
  __fastcall TfrmDefNature(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDefNature *frmDefNature;
//---------------------------------------------------------------------------
#endif
