//---------------------------------------------------------------------------
#ifndef f_genresH
#define f_genresH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "base.h"
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
  void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
  __fastcall TfrmGeneration(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmGeneration *frmGeneration;
extern void GenereReseau();
//---------------------------------------------------------------------------
#endif
