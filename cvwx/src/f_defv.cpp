//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "base.h"
#include "f_defv.h"
#include "f_defvp.h"
#include "f_simul.h"
#include "f_deff.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmDefVoie *frmDefVoie=NULL;
//---------------------------------------------------------------------------
const AnsiString asFrmMsgSuppr="\
Le feu %s (à supprimer) est référencé par le feu %sn°%d (%d,%d).\n\
Si vous choisissez de supprimer le feu, TOUTES les références seront supprimées.\n\n\
Voulez-vous néanmoins le supprimer ?", // v5.2 : ajout d'un paramètre permettant d'indiquer si la référence est un feu de circulation ou de piéton
                 asVoieOuPieton[2]={" ","piéton "}, // v5.2 : Paramètre %s de la chaîne ci-dessus
                 asMAJIgnoree="Modifications de priorité ignorées";

//---------------------------------------------------------------------------
__fastcall TfrmDefVoie::TfrmDefVoie(TComponent* Owner) : TForm(Owner)
 {
  // v5.4 on charge les glyphes manuellement pour prendre en compte le HDPI
  frmSimulation->AffecteGlyphe(GLYPHE_DEFF, BitBtnDefFeuN->Glyph);
  frmSimulation->AffecteGlyphe(GLYPHE_DEFF, BitBtnDefFeuE->Glyph);
  frmSimulation->AffecteGlyphe(GLYPHE_DEFF, BitBtnDefFeuS->Glyph);
  frmSimulation->AffecteGlyphe(GLYPHE_DEFF, BitBtnDefFeuO->Glyph);
 }

void TfrmDefVoie::DefinitFeu(direction Dir)
 {
  frmDefFeux->Direction=Dir;
  frmDefFeux->x=x;
  frmDefFeux->y=y;
  frmDefFeux->Show();
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
    int RefTrv, NumRef,
        NumRefP; // v5.2
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
      // v5.2 : Référence dans les feux de piéton
      for(NumRefP=0; (!RefTrv)&&(NumRefP<cv->NbFeuxPieton); NumRefP++)
       if (cv->FeuP[NumRefP].Defini())
        for(int j=0; (!RefTrv)&&(j<cv->FeuP[NumRefP].NbFeux); j++)
         RefTrv=(cv->FeuP[NumRefP].NumFeux[j]==v->NumFeu[d-1]);
      if (RefTrv)
       { // A. On a trouvé des références au feu à supprimer
        if (AfficheMessage( Format( asFrmMsgSuppr,
                                    ARRAYOFCONST(( asDir[d],
                                                   asVoieOuPieton[!NumRef],
                                                   NumRef+1,
                                                   cv->Feu[NumRef].x,
                                                   cv->Feu[NumRef].y))),
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
          // A.1.b On supprime les références au feu à supprimer dans les feux de piéton (v5.2)
          for(int i=0; i<cv->NbFeuxPieton; i++)
           for(int j=0; j<cv->FeuP[i].NbFeux; j++)
            if (cv->FeuP[i].NumFeux[j]==v->NumFeuP[d-1])
             cv->FeuP[i].RetireFeu(v->NumFeuP[d-1]);
          // A.1.c On peut maintenant supprimer le feu
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
       (RadioGroupPriorite[d-1]->ItemIndex==feux))
    cv->AjouteFeu(x, y, (direction)d); // v5.2 : Message Ajout supprimé.
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
  if ((!v->SensVoieTram)&&(!v->DirPoss)) // v5.2: On teste si présence de voies. Si pas le cas on affiche les priorités Piétons !
   {
    frmDefVoie->Hide();
    frmDefVoiePietons->Show();
    return;
   }
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
                                   (!v->NumParking)&&(!v->EstDepotBus())&&
                                   (NbDirVoiesTram<3)&&
                                   (((v->DirPoss&N)==N)||VoieTram[nord-1]);
  RadioGroupPrioriteNord->Font->Color=VoieTram[nord-1]?clNavy:clBlack;
  RadioGroupPrioriteNord->ItemIndex=v->Priorite[nord-1];
  RadioGroupPrioriteEst->Enabled= (!VoiesTramEtRoutes)&&
                                  (!v->NumParking)&&(!v->EstDepotBus())&&
                                  (NbDirVoiesTram<3)&&
                                  (((v->DirPoss&E)==E)||VoieTram[est-1]);
  RadioGroupPrioriteEst->Font->Color=VoieTram[est-1]?clNavy:clBlack;
  RadioGroupPrioriteEst->ItemIndex=v->Priorite[est-1];
  RadioGroupPrioriteSud->Enabled= (!VoiesTramEtRoutes)&&
                                  (!v->NumParking)&&(!v->EstDepotBus())&&
                                  (NbDirVoiesTram<3)&&
                                  (((v->DirPoss&S)==S)||VoieTram[sud-1]);
  RadioGroupPrioriteSud->Font->Color=VoieTram[sud-1]?clNavy:clBlack;
  RadioGroupPrioriteSud->ItemIndex=v->Priorite[sud-1];
  RadioGroupPrioriteOuest->Enabled= (!VoiesTramEtRoutes)&&
                                    (!v->NumParking)&&(!v->EstDepotBus())&&
                                    (NbDirVoiesTram<3)&&
                                    (((v->DirPoss&O)==O)||VoieTram[ouest-1]);
  RadioGroupPrioriteOuest->Font->Color=VoieTram[ouest-1]?clNavy:clBlack;
  RadioGroupPrioriteOuest->ItemIndex=v->Priorite[ouest-1];
  BitBtnDefFeuN->Enabled=(RadioGroupPrioriteNord->ItemIndex==3);
  BitBtnDefFeuE->Enabled=(RadioGroupPrioriteEst->ItemIndex==3);
  BitBtnDefFeuS->Enabled=(RadioGroupPrioriteSud->ItemIndex==3);
  BitBtnDefFeuO->Enabled=(RadioGroupPrioriteOuest->ItemIndex==3);
  ButtonAppliquer->Enabled=false; // v5.2 : En cas de changement de coordonnées (boîte non modale) => Annulation implicite donc Appliquer ne peut être actif.
 }
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::FormShow(TObject *Sender)
{
 if (frmDefVoiePietons&&frmDefVoiePietons->Visible) frmDefVoiePietons->Hide(); // v5.2: fenêtres non modales exclusives.
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
void __fastcall TfrmDefVoie::ButtonAnnulerClick(TObject *Sender)
{
 ButtonAppliquer->Enabled=false;
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::FormHide(TObject *Sender)
{
 if (frmDefFeux&&frmDefFeux->Visible) frmDefFeux->Hide();
 frmSimulation->ActionPriorites->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::ButtonAideClick(TObject *Sender)
{ // v3.0
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::BitBtnDefFeuClick(TObject *Sender)
{
 DefinitFeu((direction)((TComponent*)Sender)->Tag); // v5.2 : Factorisation !
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefVoie::FormCreate(TObject *Sender)
{ // v5.2 : Pour factorisation
 BitBtn[0]=BitBtnDefFeuN;
 BitBtn[1]=BitBtnDefFeuE;
 BitBtn[2]=BitBtnDefFeuS;
 BitBtn[3]=BitBtnDefFeuO;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDefVoie::RadioGroupPrioriteClick(TObject *Sender)
{ // v5.2 : Factorisation
 TRadioGroup *RadioGroupPriorite=(TRadioGroup*)Sender;
 if (RadioGroupPriorite->ItemIndex!=v->Priorite[RadioGroupPriorite->Tag])
  {
   ButtonAppliquer->Enabled=true;
   BitBtn[RadioGroupPriorite->Tag]->Enabled=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmDefVoie::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

