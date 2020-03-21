//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_simul.h"
#include "f_genres.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmGeneration *frmGeneration;
//---------------------------------------------------------------------------
void GenereReseau()
 {
  if ((frmGeneration=new TfrmGeneration(Application)))
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

void __fastcall TfrmGeneration::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

void __fastcall TfrmGeneration::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

