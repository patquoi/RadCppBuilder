//---------------------------------------------------------------------------
#ifndef f_statsvH
#define f_statsvH
//---------------------------------------------------------------------------
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TfrmStatsVehicules : public TForm
{
__published:	// Composants gérés par l'EDI
    TButton *ButtonFermer;
    TTabControl *TabControl;
    TStringGrid *StringGridStatsVehicules;
    TStringGrid *StringGridCoordParkings;
    TButton *ButtonAide;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonFermerClick(TObject *Sender);
    void __fastcall TabControlChange(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    __fastcall TfrmStatsVehicules(TComponent* Owner);
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStatsVehicules *frmStatsVehicules;
//---------------------------------------------------------------------------
#endif
