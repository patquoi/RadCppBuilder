//---------------------------------------------------------------------------
#ifndef messages_fH
#define messages_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>

#define TOUT_EFFACER true
#define RIEN_EFFACER false

//---------------------------------------------------------------------------
class TfrmMessages : public TForm
{
__published:	// Composants gérés par l'EDI
    TMemo *Memo;
    TStatusBar *StatusBar;
    TPanel *Panel;
    TButton *Button;
    TTimer *Timer;
    TSaveDialog *SaveDialog;
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall ButtonClick(TObject *Sender);
private:	// Déclarations de l'utilisateur
    AnsiString asMessage;
    bool ToutEffacer;
public:		// Déclarations de l'utilisateur
    __fastcall TfrmMessages(TComponent* Owner);
    void AfficheMessage(AnsiString asMessage, bool ToutEffacer);
    void AjouteMessage(AnsiString asMessage, bool ToutEffacer);
    void RetireMessages(int Nombre);
    void ChargeMessages(AnsiString asNomFichier);
    void SauveMessages(AnsiString asNomFichier);
    void SauvegardeFin();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMessages *frmMessages;
//---------------------------------------------------------------------------
#endif
