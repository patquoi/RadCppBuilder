//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_deff.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "cspin"
//---------------------------------------------------------------------------
TfrmDefFeux *frmDefFeux=NULL;
//---------------------------------------------------------------------------
__fastcall TfrmDefFeux::TfrmDefFeux(TComponent* Owner) : TForm(Owner)
 {
  NbFeuxDmd=0;
  NbFeuxAtt=0;
  NumFeuxDmd=NULL;
  NumFeuxAtt=NULL;
 }
//---------------------------------------------------------------------------
bool TfrmDefFeux::RafraichitInfos()
 {
  int i, NbFeuxP;
  v=&(cv->v[x][y]);
  Numero=v->NumFeu[Direction-1];
  if (!Numero)
   Numero=cv->AjouteFeu(x, y, Direction); // v5.2 : plus de message de limite.
  v->NumFeu[Direction-1]=Numero;
  f=&(cv->Feu[Numero-1]);
  LabelCoordonnees->Caption=Format("%2.2d, %2.2d", ARRAYOFCONST((x, y)));
  LabelDirection->Caption=asDir[Direction];
  if (Numero) LabelNumero->Caption=IntToStr(Numero);
  RadioGroupEtat->ItemIndex=f->Etat;
  RadioGroupTypeDmdVert->ItemIndex=f->TypeDmdVert;
  RadioGroupTypePsgRouge->ItemIndex=f->TypePsgRouge;
  CSpinEditDureeVert->Value=f->DureeVert;
  CSpinEditDureeRouge->Value=f->DureeRouge;

  // Copie des listes de feux
  NbFeuxDmd=f->NbFeuxDmd;
  NbFeuxAtt=f->NbFeuxAtt;
  if (NumFeuxDmd) { delete[] NumFeuxDmd; NumFeuxDmd=NULL; }
  if (NumFeuxAtt) { delete[] NumFeuxAtt; NumFeuxAtt=NULL; }
  if (((NbFeuxDmd)&&(!(NumFeuxDmd=new int[NbFeuxDmd])))||
      ((NbFeuxAtt)&&(!(NumFeuxAtt=new int[NbFeuxAtt]))))
    {
     AfficheMessage(asMemInsuff,asErrInattendue, tmErreur, 0, 0);
     return false;
    }
  for(i=0; i<NbFeuxDmd; i++) NumFeuxDmd[i]=f->NumFeuxDmd[i];
  for(i=0; i<NbFeuxAtt; i++) NumFeuxAtt[i]=f->NumFeuxAtt[i];

  // Affichage du nombre de feux de chaque liste
  LabelNbFeuxDmd->Caption=IntToStr(NbFeuxDmd);
  LabelNbFeuxAtt->Caption=IntToStr(NbFeuxAtt);

  // Affichage des numéros de feux piétons liés (v5.2)
  LabelFeuxPietons->Caption="";

  for(i=0,NbFeuxP=0; i<cv->NbFeuxPieton; i++)
   if (cv->FeuP[i].Defini()&&cv->FeuP[i].NbFeux)
    for(int j=0; j<cv->FeuP[i].NbFeux; j++)
     if (cv->FeuP[i].NumFeux[j]==Numero)
      {
       LabelFeuxPietons->Caption=LabelFeuxPietons->Caption+Format((LabelFeuxPietons->Caption=="")?"%d":", %d", ARRAYOFCONST((i+1)));
       NbFeuxP++;
      }
  if (LabelFeuxPietons->Caption=="")
   LabelFeuxPietons->Caption="Aucun";
  else
   LabelFeuxPietons->Caption=IntToStr(NbFeuxP)+" ("+LabelFeuxPietons->Caption+")";

  ButtonAppliquer->Enabled=false; // v5.2 : En cas de changement de coordonnées (boîte non modale) => Annulation implicite donc Appliquer ne peut être actif.
  return true;
 }
//---------------------------------------------------------------------------
bool TfrmDefFeux::AppliqueChoix()
 {
  int i;
  frmSimulation->SimulationModifiee=true;
  f->Etat=(etat_feu)RadioGroupEtat->ItemIndex;
  f->TypeDmdVert=(dmd_vert)RadioGroupTypeDmdVert->ItemIndex;
  f->TypePsgRouge=(psg_rouge)RadioGroupTypePsgRouge->ItemIndex;
  f->DureeVert=CSpinEditDureeVert->Value;
  f->DureeRouge=CSpinEditDureeRouge->Value;

  // Copie des listes de feux
  f->NbFeuxDmd=0;
  f->NbFeuxAtt=0;
  if (f->NumFeuxDmd) { delete[] f->NumFeuxDmd; f->NumFeuxDmd=NULL; }
  if (f->NumFeuxAtt) { delete[] f->NumFeuxAtt; f->NumFeuxAtt=NULL; }
  if (((NbFeuxDmd)&&(!(f->NumFeuxDmd=new int[NbFeuxDmd])))||
      ((NbFeuxAtt)&&(!(f->NumFeuxAtt=new int[NbFeuxAtt]))))
   {
    AfficheMessage(asMemInsuff,asErrInattendue, tmErreur, 0, 0);
    return false;
   }
  f->NbFeuxDmd=NbFeuxDmd;
  f->NbFeuxAtt=NbFeuxAtt;
  for(i=0; i<NbFeuxDmd; i++) f->NumFeuxDmd[i]=NumFeuxDmd[i];
  for(i=0; i<NbFeuxAtt; i++) f->NumFeuxAtt[i]=NumFeuxAtt[i];
  ButtonAppliquer->Enabled=false;
  frmSimulation->RedessineCase(x, y, true);
  return true;
 }
//---------------------------------------------------------------------------
void TfrmDefFeux::RafraichitInfosFeuxDmd()
 {
  ButtonAppliquer->Enabled=true;
  LabelNbFeuxDmd->Caption=IntToStr(NbFeuxDmd);
 }
//---------------------------------------------------------------------------
void TfrmDefFeux::RafraichitInfosFeuxAtt()
 {
  ButtonAppliquer->Enabled=true;
  LabelNbFeuxAtt->Caption=IntToStr(NbFeuxAtt);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::FormShow(TObject *Sender)
{
 if (!RafraichitInfos()) Hide(); else frmSimulation->RedessineCase(x, y, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::FormHide(TObject *Sender)
{
 int i;
 frmSimulation->ActionPriorites->Enabled=true;
 SpeedButtonSelFeuxDmd->Down=false;
 SpeedButtonSelFeuxAtt->Down=false;
 if (frmSimulation->SelectionFeuxDmd)
  for(i=0; i<NbFeuxDmd; i++)
   frmSimulation->RedessineCase(cv->Feu[NumFeuxDmd[i]-1].x, cv->Feu[NumFeuxDmd[i]-1].y, true);
 if (frmSimulation->SelectionFeuxAtt)
  for(i=0; i<NbFeuxAtt; i++)
   frmSimulation->RedessineCase(cv->Feu[NumFeuxAtt[i]-1].x, cv->Feu[NumFeuxAtt[i]-1].y, true);
 frmSimulation->SelectionFeuxDmd=false;
 frmSimulation->SelectionFeuxAtt=false;
 // v5.2 : En cas de dfinition de feux, on revient à la case initiale.
 frmSimulation->DrawGridSimul->Col=x;
 frmSimulation->DrawGridSimul->Row=y;
 frmSimulation->DrawGridSimulClick(frmSimulation);

}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::ButtonOkClick(TObject *Sender)
{
 AppliqueChoix();
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::ButtonAnnulerClick(TObject *Sender)
{
 ButtonAppliquer->Enabled=false;
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::ButtonAppliquerClick(TObject *Sender)
{
 if (!AppliqueChoix()) Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::RadioGroupEtatClick(TObject *Sender)
{
 if (RadioGroupEtat->ItemIndex!=f->Etat)
  ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::RadioGroupTypeDmdVertClick(TObject *Sender)
{
 if (RadioGroupTypeDmdVert->ItemIndex!=f->TypeDmdVert)
 ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::CSpinEditDureeVertChange(TObject *Sender)
{
 ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::SpeedButtonSelFeuxDmdClick(TObject *Sender)
{
 int i;
 if (SpeedButtonSelFeuxDmd->Down&&(!SpeedButtonSelFeuxAtt->Down))
  SpeedButtonSelFeuxAtt->Click();
 frmSimulation->SelectionFeuxDmd=SpeedButtonSelFeuxDmd->Down;
 for(i=0; i<NbFeuxDmd; i++) frmSimulation->RedessineCase(cv->Feu[NumFeuxDmd[i]-1].x, cv->Feu[NumFeuxDmd[i]-1].y, true);
 frmSimulation->RedessineCase(frmSimulation->DrawGridSimul->Col, frmSimulation->DrawGridSimul->Row, true);
 frmSimulation->ActionPriorites->Enabled=!((frmSimulation->SelectionFeuxDmd||frmSimulation->SelectionFeuxAtt));
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::SpeedButtonSelFeuxAttClick(TObject *Sender)
{
 int i;
 if (SpeedButtonSelFeuxAtt->Down&&(!SpeedButtonSelFeuxDmd->Down))
  SpeedButtonSelFeuxDmd->Click();
 frmSimulation->SelectionFeuxAtt=SpeedButtonSelFeuxAtt->Down;
 for(i=0; i<NbFeuxAtt; i++) frmSimulation->RedessineCase(cv->Feu[NumFeuxAtt[i]-1].x, cv->Feu[NumFeuxAtt[i]-1].y, true);
 frmSimulation->RedessineCase(frmSimulation->DrawGridSimul->Col, frmSimulation->DrawGridSimul->Row, true);
 frmSimulation->ActionPriorites->Enabled=!((frmSimulation->SelectionFeuxDmd||frmSimulation->SelectionFeuxAtt));
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::RadioGroupTypePsgRougeClick(TObject *Sender)
{
 if (RadioGroupTypePsgRouge->ItemIndex!=f->TypePsgRouge)
  ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::ButtonAideClick(TObject *Sender)
{ // v3.0
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

