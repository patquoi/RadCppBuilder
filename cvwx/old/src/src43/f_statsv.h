//---------------------------------------------------------------------------
#ifndef f_statsvH
#define f_statsvH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QGrids.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QGrids.hpp>
#include <QStdCtrls.hpp>
#include <Classes.hpp>
#endif
//---------------------------------------------------------------------------
class TfrmStatsVehicules : public TForm
{
__published:	// Composants gérés par l'EDI
    TStringGrid *StringGridCoordEtapes;
    TButton *ButtonFermer;
    TTabControl *TabControl;
    TStringGrid *StringGridStatsVehicules;
    TButton *ButtonAide;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonFermerClick(TObject *Sender);
    void __fastcall TabControlChange(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    __fastcall TfrmStatsVehicules(TComponent* Owner);
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStatsVehicules *frmStatsVehicules;
//---------------------------------------------------------------------------
#endif
