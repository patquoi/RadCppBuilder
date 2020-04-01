//---------------------------------------------------------------------------
#ifndef f_statsH
#define f_statsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmStatistiques : public TForm
{
__published:	// Composants gérés par l'EDI
    TPaintBox *PaintBoxStats;
    void __fastcall PaintBoxStatsPaint(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    bool AffichageEpidemique; // v5.4.1. Définit avant l'appel à FormShow par frmSimulation
    __fastcall TfrmStatistiques(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStatistiques *frmStatistiques;
//---------------------------------------------------------------------------
#endif
