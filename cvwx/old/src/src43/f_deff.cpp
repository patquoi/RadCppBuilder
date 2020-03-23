//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_deff.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
 #pragma link "cspin"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
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
  int i;
  v=&(cv->v[x][y]);
  Numero=v->NumFeu[Direction-1];
  if (!Numero)
   if (!(Numero=cv->AjouteFeu(x, y, Direction)))
    {
     AfficheMessage( "Vous ne pouvez plus ajouter de feu :\nvous avez déjà atteint le nombre maximum !",
                     "Modifications impossibles", tmAvertissement, 0, 0);
     return false;
    }
   else
    v->NumFeu[Direction-1]=Numero;
  f=&(cv->Feu[Numero-1]);
  LabelCoordonnees->Caption=Format("%2.2d, %2.2d", ARRAYOFCONST((x, y)));
  LabelDirection->Caption=asDir[Direction];
  if (Numero) LabelNumero->Caption=IntToStr(Numero);
  RadioGroupEtat->ItemIndex=f->Etat;
  RadioGroupTypeDmdVert->ItemIndex=f->TypeDmdVert;
  CheckBoxDemandeVert->Checked=f->DemandeVert;
  RadioGroupTypePsgRouge->ItemIndex=f->TypePsgRouge;
  CheckBoxRougeDemande->Checked=f->RougeDemande;
  CheckBoxDemandeVert->Enabled=(f->Etat==rouge);
  CheckBoxRougeDemande->Enabled=(f->Etat==vert);
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
  return true;
 }
//---------------------------------------------------------------------------
bool TfrmDefFeux::AppliqueChoix()
 {
  int i;
  frmSimulation->SimulationModifiee=true;
  ControleDemandeEtPassage();
  f->Etat=(etat_feu)RadioGroupEtat->ItemIndex;
  f->TypeDmdVert=(dmd_vert)RadioGroupTypeDmdVert->ItemIndex;
  f->DemandeVert=CheckBoxDemandeVert->Checked;
  f->TypePsgRouge=(psg_rouge)RadioGroupTypePsgRouge->ItemIndex;
  f->RougeDemande=CheckBoxRougeDemande->Checked;
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
#ifdef CV_LINUX
 FormResize(this);
#endif
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
 frmSimulation->RedessineCase(x, y, true);
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
void TfrmDefFeux::ControleDemandeEtPassage()
 {
  if (RadioGroupEtat->ItemIndex!=f->Etat)
   ButtonAppliquer->Enabled=true;
  switch(RadioGroupEtat->ItemIndex)
   {
    case vert: CheckBoxDemandeVert->Checked=false;
               CheckBoxDemandeVert->Enabled=false;
               CheckBoxRougeDemande->Enabled=true;
               break;
    case rouge:CheckBoxRougeDemande->Checked=false;
               CheckBoxRougeDemande->Enabled=false;
               CheckBoxDemandeVert->Enabled=true;
               break;
    default:   CheckBoxDemandeVert->Enabled=false;
               CheckBoxRougeDemande->Enabled=false;
               break;
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::RadioGroupEtatClick(TObject *Sender)
{
 ControleDemandeEtPassage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::RadioGroupTypeDmdVertClick(TObject *Sender)
{
 if (RadioGroupTypeDmdVert->ItemIndex!=f->TypeDmdVert)
 ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefFeux::CheckBoxDemandeVertClick(TObject *Sender)
{
 if (CheckBoxDemandeVert->Checked!=f->DemandeVert)
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
void __fastcall TfrmDefFeux::CheckBoxRougeDemandeClick(TObject *Sender)
{
 if (CheckBoxRougeDemande->Checked!=f->RougeDemande)
  ButtonAppliquer->Enabled=true;
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
void __fastcall TfrmDefFeux::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=max( max( LMAX(LabelNumero,GroupBoxDureeFeu),
                 LMAX(RadioGroupTypeDmdVert,RadioGroupTypePsgRouge)),
            LMAX(CheckBoxDemandeVert,CheckBoxRougeDemande))+LH_ESPACE,
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
