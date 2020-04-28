//---------------------------------------------------------------------------
#ifndef param_fH
#define param_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <IniFiles.hpp>

//---------------------------------------------------------------------------
class TfrmParametresAutomates : public TForm
{
__published:	// Composants gérés par l'EDI
    TStatusBar *StatusBar;
    TTrackBar *TrackBar1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TCheckBox *CheckBoxInterruption;
    TGroupBox *GroupBox1;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TTrackBar *TrackBar2;
    TCheckBox *CheckBoxAutorisation;
    TButton *ButtonValider;
    TButton *ButtonAnnuler;
    void __fastcall ButtonValiderClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// Déclarations de l'utilisateur
    void LitParametres();
public:		// Déclarations de l'utilisateur
    TIniFile *IniFile;
    int TempsPause, TailleMax;
    bool Interruption, Autorisation;
    __fastcall TfrmParametresAutomates(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmParametresAutomates *frmParametresAutomates;
extern const String stSection,
					stEntreePause,
					stEntreeInterruption,
					stEntreeAutorisation,
					stSectionPartie,
					stEntreeEnregistrerMessages,
					stEntreeTailleMax,
                    stBool[2];

//---------------------------------------------------------------------------
#endif
