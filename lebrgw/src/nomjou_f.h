//---------------------------------------------------------------------------
#ifndef nomjou_fH
#define nomjou_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmNomJoueur : public TForm
{
__published:	// Composants g�r�s par l'EDI
    TEdit *EditNomJoueur;
    TButton *ButtonOk;
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall EditNomJoueurChange(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormShow(TObject *Sender);
private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    __fastcall TfrmNomJoueur(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNomJoueur *frmNomJoueur;
//---------------------------------------------------------------------------
#endif
