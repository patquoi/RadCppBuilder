//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_genres.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
TfrmGeneration *frmGeneration;
//---------------------------------------------------------------------------
void GenereReseau()
 {
  if (frmGeneration=new TfrmGeneration(Application))
   try
    {
     frmGeneration->ShowModal();
    }
   __finally
    {
     delete frmGeneration;
     frmGeneration=NULL;
    }
 }
//---------------------------------------------------------------------------
__fastcall TfrmGeneration::TfrmGeneration(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGeneration::ButtonOkClick(TObject *Sender)
{
 cv->PrepareGenerationAleatoire( TrackBarTailleMinSegments->Position,
                                 TrackBarTailleMaxSegments->Position,
                                 TrackBarProbaSortieIntersection->Position,
                                 TrackBarProbaEntreeIntersection->Position,
                                 TrackBarProbaTraverseeRoute->Position);
 cv->Genere(rand()%cv->NbX, rand()%cv->NbY, (direction)(1+rand()%NBDIR));
 frmSimulation->DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmGeneration::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=LMAX(GroupBox,ButtonAnnuler)+LH_ESPACE,
     h=max( HMAX(ButtonAide,LabelRq),
            HMAX(ButtonOk,ButtonAnnuler))+LH_ESPACE;
 if (!RedimensionnementEnCours)
  if ((Width!=l)||(Height!=h))
   {
    RedimensionnementEnCours=true;
    if (Width!=l) Width=l;
    if (Height!=h) Height=h;
    RedimensionnementEnCours=false;
   }
#endif
}
//---------------------------------------------------------------------------

void __fastcall TfrmGeneration::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

