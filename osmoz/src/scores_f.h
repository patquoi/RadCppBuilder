//---------------------------------------------------------------------------
#ifndef scores_fH
#define scores_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmScores : public TForm
{
__published:	// Composants gérés par l'EDI
    TStringGrid *StringGrid;
    TTimer *Timer;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall StringGridDrawCell(TObject *Sender, int Col, int Row,
          TRect &Rect, TGridDrawState State);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall TimerTimer(TObject *Sender);
private:	// Déclarations de l'utilisateur
    bool RafraichirTempsUniquement;
public:		// Déclarations de l'utilisateur
    int cljo[6], jocl[6], nj[6], np[6], NbjSvt;
    __fastcall TfrmScores(TComponent* Owner);
    void Initialise();
    void MajScores();
    void MajTemps();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmScores *frmScores;
//---------------------------------------------------------------------------
#endif
