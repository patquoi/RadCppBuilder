//---------------------------------------------------------------------------
#ifndef f_afdistftH
#define f_afdistftH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmAffDistFilesTaxi : public TForm
{
__published:	// Composants g�r�s par l'EDI
    TStringGrid *StringGridDistances;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);


private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    __fastcall TfrmAffDistFilesTaxi(TComponent* Owner);
    void EffaceInfos();
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAffDistFilesTaxi *frmAffDistFilesTaxi;
//---------------------------------------------------------------------------
#endif
