//---------------------------------------------------------------------------
#ifndef f_afdisteH
#define f_afdisteH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QGrids.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QGrids.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
class TfrmAffDistEtapes : public TForm
{
__published:	// Composants gérés par l'EDI
  TStringGrid *StringGridDistances;
  TCheckBox *CheckBoxCouloirsBus;
  TPanel *Panel;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall CheckBoxCouloirsBusClick(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
  __fastcall TfrmAffDistEtapes(TComponent* Owner);
  void EffaceInfos();
  void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAffDistEtapes *frmAffDistEtapes;
//---------------------------------------------------------------------------
#endif
