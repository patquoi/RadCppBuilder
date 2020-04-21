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
__published:	// Composants gérés par l'EDI
    TImage *Image;
    TTimer *Timer;
    TButton *ButtonOk;
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ButtonOkClick(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    __fastcall TfrmAvertissement(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAvertissement *frmAvertissement;
//---------------------------------------------------------------------------
#endif
