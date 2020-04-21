//---------------------------------------------------------------------------
#ifndef comm_fH
#define comm_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#define DIR    0
#define PRT    1

#define HAUT   0
#define DROITE 1
#define BAS    2
#define GAUCHE 3

//---------------------------------------------------------------------------
class TfrmCommandes : public TForm
{
__published:	// Composants g�r�s par l'EDI
    TButton *ButtonOk;
    TButton *ButtonAnnuler;
    TRadioGroup *RadioGroup;
    TImage *Image;
    TLabel *Label1;
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    
private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    __fastcall TfrmCommandes(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCommandes *frmCommandes;
extern const int IdxComm[2][6];
//---------------------------------------------------------------------------
#endif
