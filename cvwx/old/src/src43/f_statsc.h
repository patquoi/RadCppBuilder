//---------------------------------------------------------------------------
#ifndef f_statscH
#define f_statscH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
class TfrmStatsComposition : public TForm
{
__published:	// Composants gérés par l'EDI
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TLabel *LabelTotal;
  TLabel *LabelTotalPC;
  TLabel *LabelRoutes;
  TLabel *LabelRoutesPC;
  TLabel *LabelPrioritesR;
  TLabel *LabelPrioritesRPC;
  TLabel *Label6;
  TLabel *Label8;
  TLabel *Label9;
  TLabel *Label10;
  TLabel *Label11;
  TLabel *LabelFeuxRMax;
  TLabel *LabelFeuxRReste;
  TLabel *LabelFeuxR;
  TLabel *LabelFeuxRPC;
  TLabel *LabelClpR;
  TLabel *LabelClpRPC;
  TLabel *LabelStopsR;
  TLabel *LabelStopsRPC;
  TLabel *Label24;
  TLabel *LabelDir;
  TLabel *LabelDirPC;
  TLabel *Label27;
  TLabel *Label28;
  TLabel *Label29;
  TLabel *LabelNord;
  TLabel *LabelEst;
  TLabel *LabelSud;
  TLabel *LabelSudPC;
  TLabel *LabelEstPC;
  TLabel *LabelNordPC;
  TLabel *Label36;
  TLabel *LabelOuest;
  TLabel *LabelOuestPC;
  TButton *ButtonOk;
  TLabel *Label12;
  TLabel *LabelEtapes;
  TLabel *LabelEtapesPC;
  TLabel *LabelEtapesMax;
  TLabel *LabelEtapesReste;
  TLabel *Label7;
  TLabel *Label14;
  TLabel *Label15;
  TLabel *Label16;
  TLabel *Label17;
  TLabel *Label18;
  TLabel *Label19;
  TLabel *Label20;
  TLabel *Label21;
  TLabel *Label22;
  TLabel *Label23;
  TButton *ButtonAide;
  TLabel *Label13;
  TLabel *LabelArretsBus;
  TLabel *LabelArretsBusPC;
  TLabel *Label30;
  TLabel *LabelArretsBusMax;
  TLabel *LabelArretsBusReste;
  TLabel *Label25;
  TLabel *LabelArretsTram;
  TLabel *LabelArretsTramPC;
  TLabel *Label32;
  TLabel *LabelArretsTramMax;
  TLabel *LabelArretsTramReste;
  TLabel *Label26;
  TLabel *LabelVoiesTram;
  TLabel *LabelVoiesTramPC;
  TLabel *Label31;
  TLabel *Label33;
  TLabel *Label34;
  TBevel *Bevel1;
  TBevel *Bevel2;
  TLabel *Label35;
  TLabel *LabelPrioritesV;
  TLabel *LabelPrioritesVPC;
  TLabel *Label39;
  TLabel *Label40;
  TLabel *Label41;
  TLabel *LabelFeuxVMax;
  TLabel *LabelFeuxVReste;
  TLabel *LabelFeuxV;
  TLabel *LabelFeuxVPC;
  TLabel *LabelClpV;
  TLabel *LabelClpVPC;
  TLabel *LabelStopsV;
  TLabel *LabelStopsVPC;
  TLabel *Label50;
  TLabel *Label51;
  TLabel *Label52;
  TLabel *Label53;
  TLabel *Label37;
  TLabel *Label38;
  TLabel *Label42;
  TLabel *Label43;
  TLabel *Label44;
  TLabel *Label45;
  TLabel *LabelPlacesTaxi;
  TLabel *Label47;
  TLabel *LabelPlacesTaxiPC;
  TLabel *LabelPlacesTaxiMax;
  TLabel *LabelPlacesTaxiReste;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
  __fastcall TfrmStatsComposition(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern void Composition();
//extern PACKAGE TfrmStatsComposition *frmStatsComposition;
//---------------------------------------------------------------------------
#endif
