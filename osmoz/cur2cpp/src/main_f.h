//---------------------------------------------------------------------------

#ifndef main_fH
#define main_fH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// Composants gérés par l'EDI
	TMemo *Memo;
	TPanel *Panel1;
	void __fastcall FormShow(TObject *Sender);
private:	// Déclarations utilisateur
	void GenereCodeAND(const String stNomFichierCur, const bool Suivant);
	void GenereCodeXOR(const String stNomFichierCur, const bool Suivant);
public:		// Déclarations utilisateur
	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
