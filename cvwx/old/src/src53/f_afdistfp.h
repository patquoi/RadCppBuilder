//---------------------------------------------------------------------------
#ifndef f_afdistfpH
#define f_afdistfpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmAffDistFilesPark : public TForm
{
__published:	// Composants g�r�s par l'EDI
  TStringGrid *StringGridDistances;
  TPanel *Panel;
  TCheckBox *CheckBoxCouloirsBus;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
  void __fastcall CheckBoxCouloirsBusClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);


private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    __fastcall TfrmAffDistFilesPark(TComponent* Owner);
    void EffaceInfos();
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAffDistFilesPark *frmAffDistFilesPark;
//---------------------------------------------------------------------------
#endif
