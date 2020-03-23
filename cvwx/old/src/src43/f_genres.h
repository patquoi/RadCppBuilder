//---------------------------------------------------------------------------
#ifndef f_genresH
#define f_genresH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#include <QForms.hpp>
#include <QComCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#include <QForms.hpp>
#include <QComCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#include "winlinux.h"
//---------------------------------------------------------------------------
class TfrmGeneration : public TForm
{
__published:	// Composants gérés par l'EDI
  TGroupBox *GroupBox;
  TTrackBar *TrackBarTailleMinSegments;
  TLabel *Label1;
  TLabel *Label2;
  TTrackBar *TrackBarProbaSortieIntersection;
  TTrackBar *TrackBarTailleMaxSegments;
  TLabel *Label3;
  TLabel *Label4;
  TButton *ButtonAnnuler;
  TButton *ButtonOk;
  TLabel *Label5;
  TTrackBar *TrackBarProbaEntreeIntersection;
  TLabel *Label6;
  TTrackBar *TrackBarProbaTraverseeRoute;
  TLabel *LabelRq;
  TButton *ButtonAide;
  void __fastcall ButtonOkClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall ButtonAideClick(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
  __fastcall TfrmGeneration(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmGeneration *frmGeneration;
extern void GenereReseau();
//---------------------------------------------------------------------------
#endif
