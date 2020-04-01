//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "simul.h"
#include "f_prmtram.h"
#include "f_prmsim.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmParamTram *frmParamTram;
//---------------------------------------------------------------------------
const AnsiString asOrdre[2]={"ème","er"};
//---------------------------------------------------------------------------
__fastcall TfrmParamTram::TfrmParamTram(TComponent* Owner)
    : TForm(Owner)
{
 // v5.4 on charge les glyphes manuellement pour prendre en compte le HDPI
 for(int i=0; i<9; i++)
  if (i!=4) // v5.4 : plus de zoom !
   frmSimulation->AffecteGlyphe(GLYPHE_DIR+i, ((TBitBtn*)(FindComponent((UnicodeString)("BitBtn"+IntToStr(1+i%3)+IntToStr(1+i/3)))))->Glyph);
}
//---------------------------------------------------------------------------
void TfrmParamTram::RafraichitNbTrams()
 {
  int i, NbTrams=0;
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++)
   if (cv->LigneTram[i].NbArrets)
    NbTrams+=1+(cv->LigneTram[i].NbArrets-1)/3; // On définit 1 tram de 1 à 3 arrêts. 2 trams de 4 à 6 arrêts et 3 trams de 7 à 9 arrêts
  LabelNbTrams->Caption=IntToStr(NbTrams);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmParamTram::FormShow(TObject *Sender)
{
 int i, j;
 AnsiString asNumLigne;
 TShape* Shape;
 NumArretTramAMontrer=0;
 InitialisationEnCours=true;
 for(NbArretsTram=i=0; i<cv->NbArretsTram; i++) NbArretsTram+=cv->ArretTram[i].Defini();
 LabelNbArretsTram->Caption=IntToStr(NbArretsTram);
 LabelNbMaxArretsTram->Caption=IntToStr(cv->NbArretsTram);
 RafraichitNbTrams();
 if (NbArretsTram)
  {
   CheckBoxTout->Visible=(cv->TourCrt>0);
   LabelT->Visible=(cv->TourCrt>0);
   ShapeT->Visible=(cv->TourCrt>0);
   if (!cv->TourCrt)
    {
     LabelLigne->Caption="Ligne";
     LabelLigne->Left=LabelLigne->Left+8;
    }
   LabelRqCochesLignesTram->Visible=(cv->TourCrt>0);
   for(i=1; i<=NBMAXLIGNESBUSTRAM; i++)
    {
     if (cv->NbArretsTram<NBMAXARRETSBUSTRAMPARLIGNE)
      ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(i)))->MAXVALUE=cv->NbArretsTram;
     ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(i)))->Value=cv->LigneTram[i-1].NbArrets;
     ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(i)))->Enabled=!cv->TourCrt;
     ((TCheckBox*)FindComponent("CheckBox"+IntToStr(i)))->Visible=(cv->TourCrt>0)&&(cv->LigneTram[i-1].NbArrets>0);
     for(j=1; j<=NBMAXARRETSBUSTRAMPARLIGNE; j++)
      {
       ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(10*i+j)))->MAXVALUE=cv->NbArretsTram;
       ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(10*i+j)))->Value=cv->LigneTram[i-1].NumArret[j-1];
       ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(10*i+j)))->Enabled=!cv->TourCrt;
      }
     asNumLigne=IntToStr(i);
     Shape=(TShape*)FindComponent("Shape"+asNumLigne);
     Shape->Brush->Color=CoulLigneBusTram[i-1];
     Shape->Pen->Color=CoulLigneBusTram[i-1];
     ((TLabel*)FindComponent("LabelL"+asNumLigne))->Font->Color=CoulTLigneBusTram[i-1];
    }
  }
 else
  {
   for(i=1; i<=NBMAXLIGNESBUSTRAM; i++)
    ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(i)))->Visible=false;
   AfficheMessage( "Vous devez poser au moins un arrêt de tram sur le réseau pour pouvoir définir le réseau de lignes de tram.",
                   "Impossible de paramétrer le réseau de lignes de tram", tmAvertissement, 0, 0);
  }
 CSpinEditNbMaxPersonnesTram->Value=cv->NbMaxPersonnesTram;
 CSpinEditNbToursStopArretTram->Value=cv->NbToursStopArretTram;
 CSpinEditNbCasesMaxArretTram->Value=cv->NbMaxCasesDetectArretTram;
 CSpinEditProbaDirArretTram->Value=cv->ProbaDirArretTram;
 CSpinEditNbMaxToursAttenteTram->Value=cv->NbMaxToursAttenteTram;
 CSpinEditProbaArretDmd->Value=cv->ProbaArretTramDmd;
 InitialisationEnCours=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamTram::CSpinEditChange(TObject *Sender)
{
 TCSpinEdit *CSpinEdit=(TCSpinEdit*)Sender;
 int i,
     k=StrToInt(CSpinEdit->Name.SubString(10, CSpinEdit->Name.Length()-9)),
     n=CSpinEdit->Value,
     AncNumArretTramAMontrer;
 switch(k/10)
  {
   case 0: // Nombre d'arrêts
           for(i=1; i<=NBMAXARRETSBUSTRAMPARLIGNE; i++)
            ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(10*k+i)))->Visible=(i<=n);
           break;
   default:// N°d'arrêt de tram
           if ((!n)||(n>cv->NbArretsTram))
            CSpinEdit->Value=0;
           else
            if (!cv->ArretTram[n-1].Defini())
             CSpinEdit->Value=1+CSpinEdit->Value%cv->NbArretsTram;
            else
             if (!InitialisationEnCours)
              {
			   if ((AncNumArretTramAMontrer=NumArretTramAMontrer))
                {
                 NumArretTramAMontrer=0;
                 cv->v[cv->ArretTram[AncNumArretTramAMontrer-1].x]
                      [cv->ArretTram[AncNumArretTramAMontrer-1].y].RedessineCasesArretTram(indefinie);
                }
               NumArretTramAMontrer=CSpinEdit->Value;
               // On bouge le curseur pour être sûr de voir l'arrêt
               frmSimulation->DrawGridSimul->Col=cv->ArretTram[NumArretTramAMontrer-1].x;
               frmSimulation->DrawGridSimul->Row=cv->ArretTram[NumArretTramAMontrer-1].y;
              }
           break;
  }
 if (!InitialisationEnCours) ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamTram::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this); // v5.4 (oubli v3.8)
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamTram::MenuItemClick(TObject *Sender)
{
 ((TBitBtn*)FindComponent("BitBtn"+IntToStr(((TComponent*)Sender)->Tag)))->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamTram::BitBtnDirClick(TObject *Sender)
{
 int n=StrToInt(((TComponent*)Sender)->Name.SubString(7, ((TComponent*)Sender)->Name.Length()-6)),
     dx=n/10-2, dy=n%10-2;
 if (CheckBoxCoins->Checked)
  {
   switch(dx)
    {
     case -1: frmSimulation->DrawGridSimul->Col=0; break;
     case +1: frmSimulation->DrawGridSimul->Col=frmSimulation->DrawGridSimul->ColCount-1; break;
    }
   switch(dy)
    {
     case -1: frmSimulation->DrawGridSimul->Row=0; break;
     case +1: frmSimulation->DrawGridSimul->Row=frmSimulation->DrawGridSimul->RowCount-1; break;
    }
  }
 else
  {
   if ((frmSimulation->DrawGridSimul->Col+dx>=0)&&
       (frmSimulation->DrawGridSimul->Col+dx<frmSimulation->DrawGridSimul->ColCount))
    frmSimulation->DrawGridSimul->Col+=dx;
   if ((frmSimulation->DrawGridSimul->Row+dy>=0)&&
       (frmSimulation->DrawGridSimul->Row+dy<frmSimulation->DrawGridSimul->RowCount))
    frmSimulation->DrawGridSimul->Row+=dy;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamTram::TimerClignotementTimer(TObject *Sender)
{
 TimerClignotement->Tag^=1;
 if (NumArretTramAMontrer)
  cv->v[cv->ArretTram[NumArretTramAMontrer-1].x]
       [cv->ArretTram[NumArretTramAMontrer-1].y].RedessineCasesArretTram(indefinie);
}
//---------------------------------------------------------------------------
bool TfrmParamTram::AppliqueChoix()
 {
  AnsiString asMsg;
  int i, j;
  TCSpinEdit *CSpinEditNb, *CSpinEditNum;
  // 1. On vérifie que tous les arrêts sont définis
  for(i=1; i<=NBMAXLIGNESBUSTRAM; i++)
   {
    CSpinEditNb=(TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(i));
    if (CSpinEditNb->Value)
     {
      for(j=1; j<=CSpinEditNb->Value; j++)
       {
        CSpinEditNum=(TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(10*i+j));
        if (!CSpinEditNum->Value)
         asMsg= asMsg+
                Format( " - Le %d%s arrêt de la ligne n°%d n'est pas défini.\n",
                        ARRAYOFCONST(( j, asOrdre[!(j-1)], i)));
       }
     }
   }
  if (!asMsg.IsEmpty())
   {
    AfficheMessage( Format("Le réseau de trams n'est pas correct :\n%s\nCorrigez avant de continuer.", ARRAYOFCONST((asMsg))),
                    "Impossible de continuer", tmAvertissement, 0, 0);
    return false;
   }
  // 2. On valide les lignes de tram
  frmSimulation->SimulationModifiee=true;
  cv->InitialiseInfosLignesTram();
  for(i=1; i<=NBMAXLIGNESBUSTRAM; i++)
   {
    CSpinEditNb=(TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(i));
    if ((cv->LigneTram[i-1].NbArrets=CSpinEditNb->Value))
     {
      cv->NbLignesTram++;
      for(j=1; j<=CSpinEditNb->Value; j++)
       {
        CSpinEditNum=(TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(10*i+j));
        cv->LigneTram[i-1].NumArret[j-1]=CSpinEditNum->Value;
        cv->ArretTram[CSpinEditNum->Value-1].AjouteLigneTram(i); // v3.0.5
       }
     }
   }
  // 3. On valide les autres paramètres
  cv->NbMaxPersonnesTram=CSpinEditNbMaxPersonnesTram->Value;
  cv->NbToursStopArretTram=CSpinEditNbToursStopArretTram->Value;
  cv->NbMaxCasesDetectArretTram=CSpinEditNbCasesMaxArretTram->Value;
  cv->ProbaDirArretTram=CSpinEditProbaDirArretTram->Value;
  cv->NbMaxToursAttenteTram=CSpinEditNbMaxToursAttenteTram->Value;
  cv->ProbaArretTramDmd=CSpinEditProbaArretDmd->Value;
  ButtonAppliquer->Enabled=false;
  RafraichitNbTrams();
  return true;
 }
//---------------------------------------------------------------------------
void __fastcall TfrmParamTram::ButtonOkClick(TObject *Sender)
{
 if (AppliqueChoix()) ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamTram::ButtonAppliquerClick(TObject *Sender)
{
 AppliqueChoix();
}
//---------------------------------------------------------------------------


void __fastcall TfrmParamTram::CSpinEditParametresChange(
      TObject *Sender)
{
 if (!InitialisationEnCours) ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamTram::CheckBoxClick(TObject *Sender)
{
 if (!CheckBoxTout->Tag)
  {
   if (((TCheckBox*)Sender)->Checked) // v5.3
     WindowState=wsMinimized;
   frmSimulation->DrawGridSimul->Repaint();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamTram::CheckBoxToutClick(TObject *Sender)
{
 CheckBoxTout->Tag=1;
 for(int i=0; i<NBMAXLIGNESBUSTRAM; i++)
   ((TCheckBox*)FindComponent("CheckBox"+IntToStr(i+1)))->Checked=(cv->LigneTram[i].NbArrets>0)?CheckBoxTout->Checked:false;
 CheckBoxTout->Tag=0;
 if (CheckBoxTout->Checked) // v5.3
   WindowState=wsMinimized;
 frmSimulation->DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamTram::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

