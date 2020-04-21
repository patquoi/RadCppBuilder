//---------------------------------------------------------------------------
#ifndef score_fH
#define score_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>

#define L_BETES 0
#define L_EFFET 1
#define L_TEMPS 2
#define L_SCORE 3

//---------------------------------------------------------------------------
class TfrmScore : public TForm
{
__published:	// Composants gérés par l'EDI
    TPanel *PanelScores;
    TLabel *LabelScBetes;
    TLabel *Label1;
    TPanel *PanelNombres;
    TLabel *LabelNbBetes;
    TPanel *PanelCoefs;
    TLabel *Label2;
    TLabel *LabelNbTemps;
    TLabel *LabelScTemps;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *LabelNbEffet;
    TLabel *LabelScEffet;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TButton *ButtonOk;
    TLabel *Label13;
    TLabel *LabelBarre;
    TLabel *Label15;
    TLabel *LabelScNiv;
    TLabel *Label3;
    TLabel *LabelScore;
    TTimer *TimerDefil;
    TStatusBar *StatusBar;
    TLabel *Label7;
    TLabel *Label4;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label14;
    TLabel *LabelBarreAtteinte;
    TStatusBar *StatusBarSuiteOuFin;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall TimerDefilTimer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    
private:	// Déclarations de l'utilisateur
    int LigneCrt, Effet, NbBetes;
    wchar_t wsChiffres[32];
    long TpsRestant;
    bool CalculEnCours; 
public:		// Déclarations de l'utilisateur
    __fastcall TfrmScore(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmScore *frmScore;
//---------------------------------------------------------------------------
#endif
