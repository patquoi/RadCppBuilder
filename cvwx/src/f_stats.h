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
__published:	// Composants g�r�s par l'EDI
    TPaintBox *PaintBoxStats;
    void __fastcall PaintBoxStatsPaint(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    bool AffichageEpidemique; // v5.4.1. D�finit avant l'appel � FormShow par frmSimulation
    __fastcall TfrmStatistiques(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStatistiques *frmStatistiques;
//---------------------------------------------------------------------------
#endif
