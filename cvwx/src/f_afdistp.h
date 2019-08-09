//---------------------------------------------------------------------------
#ifndef f_afdistpH
#define f_afdistpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmAffDistParkings : public TForm
{
__published:	// Composants gérés par l'EDI
  TStringGrid *StringGridDistances;
  TCheckBox *CheckBoxCouloirsBus;
  TPanel *Panel;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall CheckBoxCouloirsBusClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
  __fastcall TfrmAffDistParkings(TComponent* Owner);
  void EffaceInfos();
  void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAffDistParkings *frmAffDistParkings;
//---------------------------------------------------------------------------
#endif
