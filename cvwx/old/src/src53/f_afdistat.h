//---------------------------------------------------------------------------
#ifndef f_afdistatH
#define f_afdistatH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmAffDistArretsTram : public TForm
{
__published:	// Composants g�r�s par l'EDI
    TStringGrid *StringGridDistances;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);


private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    __fastcall TfrmAffDistArretsTram(TComponent* Owner);
    void EffaceInfos();
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAffDistArretsTram *frmAffDistArretsTram;
//---------------------------------------------------------------------------
#endif
