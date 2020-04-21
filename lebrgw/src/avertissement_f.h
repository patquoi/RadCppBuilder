//---------------------------------------------------------------------------
#ifndef avertissement_fH
#define avertissement_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmAvertissement : public TForm
{
__published:	// Composants g�r�s par l'EDI
    TImage *Image;
    TTimer *Timer;
    TButton *ButtonOk;
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ButtonOkClick(TObject *Sender);
private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    __fastcall TfrmAvertissement(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAvertissement *frmAvertissement;
//---------------------------------------------------------------------------
#endif
