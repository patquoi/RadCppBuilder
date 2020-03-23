//---------------------------------------------------------------------------
#ifndef f_afdistabH
#define f_afdistabH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmAffDistArretsBus : public TForm
{
__published:	// Composants gérés par l'EDI
    TStringGrid *StringGridDistances;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    
    
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    __fastcall TfrmAffDistArretsBus(TComponent* Owner);
    void EffaceInfos();
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAffDistArretsBus *frmAffDistArretsBus;
//---------------------------------------------------------------------------
#endif
