//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "prmniv_f.h"
#include "base.h"
#include "plt_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma link "CSPIN"
#pragma resource "*.dfm"
TfrmPrmNiveau *frmPrmNiveau;
//---------------------------------------------------------------------------
__fastcall TfrmPrmNiveau::TfrmPrmNiveau(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrmNiveau::FormShow(TObject *Sender)
{
 EditNomSerie->Text=frmPlateau->stNomSerieNiveau;
 CSpinEditNumNiv->Value=Niv->Num;
 CSpinEditNbMaxBetes->Value=Niv->NbBetes;
 CSpinEditNbMaxBetes->ReadOnly=(Niv->NbCrtBetes>0);
 LabelNbCrtBetes->Caption=IntToStr(Niv->NbCrtBetes);
 CSpinEditDelai->Value=Niv->Delai;
 CSpinEditNbMaxTours->Value=Niv->Temps;
 CSpinEditBarre->Value=Niv->Barre;
 CSpinEditNbBetesAImmobiliser->Value=Niv->NbBetesAFaire;
 CSpinEditEffet->Value=Niv->Effet0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrmNiveau::ButtonOkClick(TObject *Sender)
{
 if (frmPlateau->stNomSerieNiveau!=EditNomSerie->Text) frmPlateau->stNomSerieNiveau=EditNomSerie->Text;
 if (Niv->Num!=CSpinEditNumNiv->Value) Niv->Num=CSpinEditNumNiv->Value;
 if (Niv->NbBetes!=CSpinEditNbMaxBetes->Value)
  {
   frmPlateau->AffichageAutorise=false;
   if (Niv->Bete) delete[] Niv->Bete;
   Niv->NbBetes=CSpinEditNbMaxBetes->Value;
   Niv->CreeBetes(Niv->NbBetes);
   frmPlateau->AffichageAutorise=true;
  }
 Niv->Delai=CSpinEditDelai->Value;
 Niv->TpsRestant=Niv->Temps=CSpinEditNbMaxTours->Value;
 Niv->Barre=CSpinEditBarre->Value;
 Niv->NbBetesAFaire=CSpinEditNbBetesAImmobiliser->Value;
 Niv->Effet=5*Niv->NbBetesAFaire;
 Niv->NbBetesCoincees=0;
 Niv->Effet0=CSpinEditEffet->Value;
 frmPlateau->RafraichitParametres(aff_tout);
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrmNiveau::CSpinEditNbMaxBetesChange(TObject *Sender)
{
 CSpinEditNbBetesAImmobiliser->MaxValue=CSpinEditNbMaxBetes->Value;
 if (CSpinEditNbBetesAImmobiliser->Value>CSpinEditNbMaxBetes->Value)
  CSpinEditNbBetesAImmobiliser->Value=CSpinEditNbMaxBetes->Value;
 
}
//---------------------------------------------------------------------------


