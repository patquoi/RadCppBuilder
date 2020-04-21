//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "score_f.h"
#include "plt_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmScore *frmScore;
//---------------------------------------------------------------------------
__fastcall TfrmScore::TfrmScore(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmScore::FormShow(TObject *Sender)
{
 TimerDefil->Enabled=false;
 TimerDefil->Interval=100;
 CalculEnCours=false;
 Caption=Format("Score du niveau %3.3d", ARRAYOFCONST((Niv->Num)));
 LigneCrt=0;
 TpsRestant=Niv->TpsRestant;
 Effet=Niv->Effet;
 NbBetes=Niv->NbBetesCoincees;
 wsprintf(wsChiffres, L"%06ld", Niv->Barre);
          LabelBarre->Caption=AnsiString(wsChiffres);
 TimerDefil->Enabled=true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmScore::TimerDefilTimer(TObject *Sender)
{
 static long ScNivCrt=0L;
 long ScCalc;
 int NbCrt;
 if (CalculEnCours) return;

 CalculEnCours=true;
 TimerDefil->Tag++;
 if (TimerDefil->Interval>10) TimerDefil->Interval--;
 LabelBarreAtteinte->Font->Color=((TimerDefil->Tag/5)%2)?(LabelBarre->Font->Color):Color;
 switch(LigneCrt)
  {
   case L_BETES: if (Niv->NbBetesCoincees)
                  {
                   Niv->NbBetesCoincees--;
                   frmPlateau->RafraichitParametres(aff_reste);
                   wsprintf(wsChiffres, L"%2d", NbCrt=NbBetes-Niv->NbBetesCoincees);
                   LabelNbBetes->Caption=AnsiString(wsChiffres);
                   wsprintf(wsChiffres, L"%06ld", ScCalc=1000L*(long)NbCrt);
                   LabelScBetes->Caption=AnsiString(wsChiffres);
                   LabelScNiv->Caption=AnsiString(wsChiffres);
                   if ((!LabelBarreAtteinte->Visible)&&(ScCalc>=Niv->Barre))
                    LabelBarreAtteinte->Visible=true;
                   if (!Niv->NbBetesCoincees)
                    {
                     ScNivCrt=1000L*(long)NbCrt;
                     LigneCrt++;
                    }
                  }
                 else LigneCrt++;
                 break;
   case L_EFFET: if (Niv->Effet-Niv->Effet0)
                  {
                   Niv->Effet--;
                   frmPlateau->RafraichitParametres(aff_effet);
                   wsprintf(wsChiffres, L"%3d", NbCrt=Effet-Niv->Effet);
                   LabelNbEffet->Caption=AnsiString(wsChiffres);
                   wsprintf(wsChiffres, L"%06ld", 100L*(long)NbCrt);
                   LabelScEffet->Caption=AnsiString(wsChiffres);
                   wsprintf(wsChiffres, L"%06ld", ScCalc=ScNivCrt+100L*(long)NbCrt);
                   LabelScNiv->Caption=AnsiString(wsChiffres);
                   if ((!LabelBarreAtteinte->Visible)&&(ScCalc>=Niv->Barre))
                    LabelBarreAtteinte->Visible=true;
                   if (!(Niv->Effet-Niv->Effet0))
                    {
                     ScNivCrt+=100L*(long)NbCrt;
                     LigneCrt++;
                    }
                  }
                 else
                  {
                   if (Niv->Effet<5*Niv->NbBetesAFaire)
                    Niv->TpsRestant=0L;
                   LigneCrt++;
                  }
                 break;
   case L_TEMPS: if (Niv->TpsRestant)
                  {
                   if (Niv->TpsRestant>=10L)
                    Niv->TpsRestant-=10L;
                   else
                    Niv->TpsRestant=0L;
                   frmPlateau->RafraichitParametres(aff_temps);
                   wsprintf(wsChiffres, L"%4ld", NbCrt=TpsRestant-Niv->TpsRestant);
                   LabelNbTemps->Caption=AnsiString(wsChiffres);
                   wsprintf(wsChiffres, L"%06ld", 5L*(long)NbCrt);
                   LabelScTemps->Caption=AnsiString(wsChiffres);
                   wsprintf(wsChiffres, L"%06ld", ScCalc=ScNivCrt+5L*(long)NbCrt);
                   LabelScNiv->Caption=AnsiString(wsChiffres);
                   if ((!LabelBarreAtteinte->Visible)&&(ScCalc>=Niv->Barre))
                    LabelBarreAtteinte->Visible=true;
                   if (!Niv->TpsRestant)
                    {
                     ScNivCrt+=5L*(long)NbCrt;
                     LigneCrt++;
                    }
                  }
                 else LigneCrt++;
                 break;
   case L_SCORE: Niv->Score=ScNivCrt;
                 Niv->Cumul+=ScNivCrt;
                 ScNivCrt=0L; // v1.7 - Variable static donc à remettre à zéro !
                 frmPlateau->RafraichitParametres(aff_score);
                 wsprintf(wsChiffres, L"%06ld", Niv->Cumul);
                 LabelScore->Caption=AnsiString(wsChiffres);
                 ButtonOk->Enabled=true;
                 if (frmPlateau->Mode==jeu)
                  {
                   if (LabelBarreAtteinte->Visible)
                    StatusBarSuiteOuFin->SimpleText="Barre atteinte : NIVEAU SUIVANT.";
                   else
                    StatusBarSuiteOuFin->SimpleText="Barre non atteinte : FIN DE JEU.";
                  }
                 LigneCrt++;
                 break;
  }
 CalculEnCours=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmScore::FormClose(TObject *Sender, TCloseAction &Action)
{
 TimerDefil->Enabled=false;
}
//---------------------------------------------------------------------------


