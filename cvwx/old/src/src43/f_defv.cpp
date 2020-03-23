//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_defv.h"
#include "f_simul.h"
#include "f_deff.h"
#include "winlinux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
TfrmDefVoie *frmDefVoie=NULL;
//---------------------------------------------------------------------------
const AnsiString asFrmMsgSuppr="\
Le feu %s (à supprimer) est référencé par le feu n°%d (%d,%d).\n\
Si vous choisissez de supprimer le feu, TOUTES les références seront supprimées.\n\n\
Voulez-vous néanmoins le supprimer ?",
                 asFrmMsgAjout="Le feu %s ne peut être ajouté : il y a déjà %d feux.\n",
                 asMAJIgnoree="Modifications de priorité ignorées";
//---------------------------------------------------------------------------
__fastcall TfrmDefVoie::TfrmDefVoie(TComponent* Owner) : TForm(Owner) {}

void TfrmDefVoie::DefinitFeu(direction Dir)
 {
  frmDefFeux->Direction=Dir;
  frmDefFeux->x=x;
  frmDefFeux->y=y;
  frmDefFeux->Show();
 }
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::RadioGroupPrioriteNordClick(TObject *Sender)
{
 if (RadioGroupPrioriteNord->ItemIndex!=v->Priorite[nord-1])
  {
   ButtonAppliquer->Enabled=true;
   BitBtnDefFeuN->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::RadioGroupPrioriteEstClick(TObject *Sender)
{
 if (RadioGroupPrioriteEst->ItemIndex!=v->Priorite[est-1])
  {
   ButtonAppliquer->Enabled=true;
   BitBtnDefFeuE->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::RadioGroupPrioriteSudClick(TObject *Sender)
{
 if (RadioGroupPrioriteSud->ItemIndex!=v->Priorite[sud-1])
  {
   ButtonAppliquer->Enabled=true;
   BitBtnDefFeuS->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::RadioGroupPrioriteOuestClick(TObject *Sender)
{
 if (RadioGroupPrioriteOuest->ItemIndex!=v->Priorite[ouest-1])
  {
   ButtonAppliquer->Enabled=true;
   BitBtnDefFeuO->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void TfrmDefVoie::AppliqueChoix()
 {
  AnsiString asMsg;
  TRadioGroup *RadioGroupPriorite[NBDIR]={ RadioGroupPrioriteNord,
                                           RadioGroupPrioriteEst,
                                           RadioGroupPrioriteSud,
                                           RadioGroupPrioriteOuest};
  TBitBtn *BitBtnDefFeu[NBDIR]={ BitBtnDefFeuN, // v3.8.3
                                 BitBtnDefFeuE,
                                 BitBtnDefFeuS,
                                 BitBtnDefFeuO};
  frmSimulation->SimulationModifiee=true;
  // 1. On supprime les feux si on change de priorité (et on ferme la fiche DefFeux)
  for(int d=nord; d<=ouest; d++) // v3.8.3
   {
    int RefTrv, NumRef;
    if ((v->Priorite[d-1]==feux)&&
        (RadioGroupPriorite[d-1]->ItemIndex!=feux))
     {
      RefTrv=0;
      for(NumRef=0; (!RefTrv)&&(NumRef<cv->NbFeux); NumRef++)
       if (cv->Feu[NumRef].Defini())
        {
         for(int j=0; (!RefTrv)&&(j<cv->Feu[NumRef].NbFeuxAtt); j++)
          RefTrv=(cv->Feu[NumRef].NumFeuxAtt[j]==v->NumFeu[d-1]);
         for(int j=0; (!RefTrv)&&(j<cv->Feu[NumRef].NbFeuxDmd); j++)
          RefTrv=(cv->Feu[NumRef].NumFeuxDmd[j]==v->NumFeu[d-1]);
        }
      if (RefTrv)
       { // A. On a trouvé des références au feu à supprimer
        if (AfficheMessage( Format( asFrmMsgSuppr,
                                    ARRAYOFCONST(( asDir[d], NumRef+1, cv->Feu[NumRef].x, cv->Feu[NumRef].y))),
                            "Suppression de feu",
                            tmQuestionNecessaire, 1, 1)==trOui)
         {
          // A.1.a On supprime les références au feu à supprimer
          for(int i=0; i<cv->NbFeux; i++)
           {
            for(int j=0; j<cv->Feu[i].NbFeuxDmd; j++)
             if (cv->Feu[i].NumFeuxDmd[j]==v->NumFeu[d-1])
              cv->Feu[i].RetireFeuDmd(v->NumFeu[d-1]);
            for(int j=0; j<cv->Feu[i].NbFeuxAtt; j++)
             if (cv->Feu[i].NumFeuxAtt[j]==v->NumFeu[d-1])
              cv->Feu[i].RetireFeuAtt(v->NumFeu[d-1]);
           }
          // A.1.b On peut maintenant supprimer le feu
          cv->SupprimeFeu(v->NumFeu[d-1]-1);
          if (frmDefFeux->Visible) frmDefFeux->Hide();
         }
        else // A.2. On ne supprime pas le feu : on revient à la définition de priorité Feu.
         RadioGroupPriorite[d-1]->ItemIndex=feux;
       }
      else
       { // B. On n'a pas trouvé de référence : on peut supprimer directement le feu
        cv->SupprimeFeu(v->NumFeu[d-1]-1);
        if (frmDefFeux->Visible) frmDefFeux->Hide();
       }
     }
   }
  // 2. On ajoute les feux
  for(int d=nord; d<=ouest; d++)
   if ((v->Priorite[d-1]!=feux)&&
       (RadioGroupPriorite[d-1]->ItemIndex==feux)&&
       (!cv->AjouteFeu(x, y, (direction)d)))
    {
     asMsg=asMsg+Format(asFrmMsgAjout, ARRAYOFCONST((asDir[d], cv->NbFeux)));
     RadioGroupPriorite[d-1]->ItemIndex=v->Priorite[d-1];
    }
  if (!asMsg.IsEmpty()) AfficheMessage(asMsg, asMAJIgnoree, tmAvertissement, 0, 0);

  // 3. On change les priorités
  for(int d=nord; d<=ouest; d++)
   v->Priorite[d-1]=(priorite)RadioGroupPriorite[d-1]->ItemIndex;

  // 4. On met à jour l'accessibilité des boutons et groupes
  ButtonAppliquer->Enabled=false;
  for(int d=nord; d<=ouest; d++)
   BitBtnDefFeu[d-1]->Enabled=(RadioGroupPriorite[d-1]->ItemIndex==3);

  // 5. On rafraîchit la scène
  frmSimulation->RedessineCase(x, y, true);
 }
//---------------------------------------------------------------------------
void TfrmDefVoie::RafraichitInfos()
 {
  if (frmDefFeux->Visible) frmDefFeux->Hide();
  x=frmSimulation->DrawGridSimul->Col;
  y=frmSimulation->DrawGridSimul->Row;
  v=&(cv->v[x][y]);
  bool VoiesTramEtRoutes=v->SensVoieTram&&v->DirPoss,
       VoieTram[NBDIR]={ v->EstDirPossSensVoieTram(indefinie, nord),
                         v->EstDirPossSensVoieTram(indefinie, est),
                         v->EstDirPossSensVoieTram(indefinie, sud),
                         v->EstDirPossSensVoieTram(indefinie, ouest)};
  int NbDirVoiesTram= VoieTram[nord-1]+
                      VoieTram[est-1]+
                      VoieTram[sud-1]+
                      VoieTram[ouest-1];
  LabelCoordonnees->Caption=Format("%2.2d, %2.2d", ARRAYOFCONST((x, y)));
  RadioGroupPrioriteNord->Enabled= (!VoiesTramEtRoutes)&&
                                   (!v->NumEtape)&&(!v->EstDepotBus())&&
                                   (NbDirVoiesTram<3)&&
                                   (((v->DirPoss&N)==N)||VoieTram[nord-1]);
  RadioGroupPrioriteNord->Font->Color=VoieTram[nord-1]?clNavy:clBlack;
  RadioGroupPrioriteNord->ItemIndex=v->Priorite[nord-1];
  RadioGroupPrioriteEst->Enabled= (!VoiesTramEtRoutes)&&
                                  (!v->NumEtape)&&(!v->EstDepotBus())&&
                                  (NbDirVoiesTram<3)&&
                                  (((v->DirPoss&E)==E)||VoieTram[est-1]);
  RadioGroupPrioriteEst->Font->Color=VoieTram[est-1]?clNavy:clBlack;
  RadioGroupPrioriteEst->ItemIndex=v->Priorite[est-1];
  RadioGroupPrioriteSud->Enabled= (!VoiesTramEtRoutes)&&
                                  (!v->NumEtape)&&(!v->EstDepotBus())&&
                                  (NbDirVoiesTram<3)&&
                                  (((v->DirPoss&S)==S)||VoieTram[sud-1]);
  RadioGroupPrioriteSud->Font->Color=VoieTram[sud-1]?clNavy:clBlack;
  RadioGroupPrioriteSud->ItemIndex=v->Priorite[sud-1];
  RadioGroupPrioriteOuest->Enabled= (!VoiesTramEtRoutes)&&
                                    (!v->NumEtape)&&(!v->EstDepotBus())&&
                                    (NbDirVoiesTram<3)&&
                                    (((v->DirPoss&O)==O)||VoieTram[ouest-1]);
  RadioGroupPrioriteOuest->Font->Color=VoieTram[ouest-1]?clNavy:clBlack;
  RadioGroupPrioriteOuest->ItemIndex=v->Priorite[ouest-1];
  BitBtnDefFeuN->Enabled=(RadioGroupPrioriteNord->ItemIndex==3);
  BitBtnDefFeuE->Enabled=(RadioGroupPrioriteEst->ItemIndex==3);
  BitBtnDefFeuS->Enabled=(RadioGroupPrioriteSud->ItemIndex==3);
  BitBtnDefFeuO->Enabled=(RadioGroupPrioriteOuest->ItemIndex==3);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::FormShow(TObject *Sender)
{
#ifdef CV_LINUX
 FormResize(this);
#endif
 frmSimulation->ActionPriorites->Checked=true;
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::ButtonOkClick(TObject *Sender)
{
 AppliqueChoix();
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::ButtonAppliquerClick(TObject *Sender)
{
 AppliqueChoix();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::BitBtnDefFeuNClick(TObject *Sender)
{
 DefinitFeu(nord);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::BitBtnDefFeuEClick(TObject *Sender)
{
 DefinitFeu(est);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::BitBtnDefFeuSClick(TObject *Sender)
{
 DefinitFeu(sud);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::BitBtnDefFeuOClick(TObject *Sender)
{
 DefinitFeu(ouest);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::ButtonAnnulerClick(TObject *Sender)
{
 ButtonAppliquer->Enabled=false;
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::FormHide(TObject *Sender)
{
 if (frmDefFeux->Visible) frmDefFeux->Hide();
 frmSimulation->ActionPriorites->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::ButtonAideClick(TObject *Sender)
{ // v3.0
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=XMAX(RadioGroupPrioriteEst)+LH_ESPACE,
     h=max( HMAX(ButtonOk,ButtonAnnuler),
            HMAX(ButtonAppliquer,ButtonAide))+LH_ESPACE;
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
