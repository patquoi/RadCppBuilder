//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "f_prmbus.h"
#include "simul.h"
#include "f_prmsim.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "cspin"
//---------------------------------------------------------------------------
TfrmParamBus *frmParamBus;
//---------------------------------------------------------------------------
const AnsiString asOrdre[2]={"ème","er"};
//---------------------------------------------------------------------------
__fastcall TfrmParamBus::TfrmParamBus(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmParamBus::RafraichitNbBus()
 {
  int i, NbBus=0;
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++)
   if (cv->LigneBus[i].NbArrets)
    NbBus+=1+(cv->LigneBus[i].NbArrets-1)/3; // On définit 1 bus de 1 à 3 arrêts. 2 bus de 4 à 6 arrêts et 3 bus de 7 à 9 arrêts
  LabelNbBus->Caption=IntToStr(NbBus);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmParamBus::FormShow(TObject *Sender)
{
 int i, j;
 AnsiString asNumLigne;
 TShape* Shape;
 NumArretBusAMontrer=0;
 InitialisationEnCours=true;
 for(NbArretsBus=i=0; i<cv->NbArretsBus; i++) NbArretsBus+=cv->ArretBus[i].Defini();
 LabelNbArretsBus->Caption=IntToStr(NbArretsBus);
 LabelNbMaxArretsBus->Caption=IntToStr(cv->NbArretsBus);
 RafraichitNbBus();
 if (NbArretsBus)
  {
   CheckBoxTout->Visible=(cv->TourCrt>0);
   LabelT->Visible=(cv->TourCrt>0);
   ShapeT->Visible=(cv->TourCrt>0);
   if (!cv->TourCrt)
    {
     LabelLigne->Caption="Ligne";
     LabelLigne->Left=LabelLigne->Left+8;
    }
   LabelRqCochesLignesBus->Visible=(cv->TourCrt>0);
   for(i=1; i<=NBMAXLIGNESBUSTRAM; i++)
    {
     if (cv->NbArretsBus<NBMAXARRETSBUSTRAMPARLIGNE)
      ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(i)))->MAXVALUE=cv->NbArretsBus;
     ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(i)))->Value=cv->LigneBus[i-1].NbArrets;
     ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(i)))->Enabled=!cv->TourCrt;
     ((TCheckBox*)FindComponent("CheckBox"+IntToStr(i)))->Visible=(cv->TourCrt>0)&&(cv->LigneBus[i-1].NbArrets>0);
     for(j=1; j<=NBMAXARRETSBUSTRAMPARLIGNE; j++)
      {
       ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(10*i+j)))->MAXVALUE=cv->NbArretsBus;
       ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(10*i+j)))->Value=cv->LigneBus[i-1].NumArret[j-1];
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
   AfficheMessage( "Vous devez poser au moins un arrêt de bus sur le réseau pour pouvoir définir le réseau de lignes de bus.",
                   "Impossible de paramétrer le réseau de lignes de bus", tmAvertissement, 0, 0);
  }
 CSpinEditNbMaxPersonnesBus->Value=cv->NbMaxPersonnesBus;
 CSpinEditNbToursStopArretBus->Value=cv->NbToursStopArretBus;
 CSpinEditNbCasesMaxArretBus->Value=cv->NbMaxCasesDetectArretBus;
 CSpinEditProbaDirArretBus->Value=cv->ProbaDirArretBus;
 CSpinEditNbMaxToursAttenteBus->Value=cv->NbMaxToursAttenteBus;
 CSpinEditProbaArretDmd->Value=cv->ProbaArretBusDmd;
 InitialisationEnCours=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamBus::CSpinEditChange(TObject *Sender)
{
 TCSpinEdit *CSpinEdit=(TCSpinEdit*)Sender;
 int i,
     k=StrToInt(CSpinEdit->Name.SubString(10, CSpinEdit->Name.Length()-9)),
     n=CSpinEdit->Value,
     AncNumArretBusAMontrer;
 switch(k/10)
  {
   case 0: // Nombre d'arrêts
           for(i=1; i<=NBMAXARRETSBUSTRAMPARLIGNE; i++)
            ((TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(10*k+i)))->Visible=(i<=n);
           break;
   default:// N°d'arrêt de bus
           if ((!n)||(n>cv->NbArretsBus))
            CSpinEdit->Value=0;
           else
            if (!cv->ArretBus[n-1].Defini())
             CSpinEdit->Value=1+CSpinEdit->Value%cv->NbArretsBus;
            else
             if (!InitialisationEnCours)
              {
               if (AncNumArretBusAMontrer=NumArretBusAMontrer)
                {
                 NumArretBusAMontrer=0;
                 cv->v[cv->ArretBus[AncNumArretBusAMontrer-1].x]
                      [cv->ArretBus[AncNumArretBusAMontrer-1].y].RedessineCasesArretBus(indefinie);
                }
               NumArretBusAMontrer=CSpinEdit->Value;
               // On bouge le curseur pour être sûr de voir l'arrêt
               frmSimulation->DrawGridSimul->Col=cv->ArretBus[NumArretBusAMontrer-1].x;
               frmSimulation->DrawGridSimul->Row=cv->ArretBus[NumArretBusAMontrer-1].y;
              }
           break;
  }
 if (!InitialisationEnCours) ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamBus::ButtonAideClick(TObject *Sender)
{ // v3.0
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamBus::MenuItemClick(TObject *Sender)
{
 ((TBitBtn*)FindComponent("BitBtn"+IntToStr(((TComponent*)Sender)->Tag)))->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamBus::BitBtnDirClick(TObject *Sender)
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

void __fastcall TfrmParamBus::BitBtn22Click(TObject *Sender)
{
 frmSimulation->ActionZoom->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamBus::TimerClignotementTimer(TObject *Sender)
{
 TimerClignotement->Tag^=1;
 if (NumArretBusAMontrer)
  cv->v[cv->ArretBus[NumArretBusAMontrer-1].x]
       [cv->ArretBus[NumArretBusAMontrer-1].y].RedessineCasesArretBus(indefinie);
}
//---------------------------------------------------------------------------
bool TfrmParamBus::AppliqueChoix()
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
    AfficheMessage( Format("Le réseau de bus n'est pas correct :\n%s\nCorrigez avant de continuer.", ARRAYOFCONST((asMsg))),
                    "Impossible de continuer", tmAvertissement, 0, 0);
    return false;
   }
  // 2. On valide les lignes de bus
  frmSimulation->SimulationModifiee=true;
  cv->InitialiseInfosLignesBus();
  for(i=1; i<=NBMAXLIGNESBUSTRAM; i++)
   {
    CSpinEditNb=(TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(i));
    if (cv->LigneBus[i-1].NbArrets=CSpinEditNb->Value)
     {
      cv->NbLignesBus++;
      for(j=1; j<=CSpinEditNb->Value; j++)
       {
        CSpinEditNum=(TCSpinEdit*)FindComponent(asDebutNomSpinEdit+IntToStr(10*i+j));
        cv->LigneBus[i-1].NumArret[j-1]=CSpinEditNum->Value;
        cv->ArretBus[CSpinEditNum->Value-1].AjouteLigneBus(i); // v3.0.5
       }
     }
   }
  // 3. On valide les autres paramètres
  cv->NbMaxPersonnesBus=CSpinEditNbMaxPersonnesBus->Value;
  cv->NbToursStopArretBus=CSpinEditNbToursStopArretBus->Value;
  cv->NbMaxCasesDetectArretBus=CSpinEditNbCasesMaxArretBus->Value;
  cv->ProbaDirArretBus=CSpinEditProbaDirArretBus->Value;
  cv->NbMaxToursAttenteBus=CSpinEditNbMaxToursAttenteBus->Value;
  cv->ProbaArretBusDmd=CSpinEditProbaArretDmd->Value;
  ButtonAppliquer->Enabled=false;
  RafraichitNbBus();
  return true;
 }
//---------------------------------------------------------------------------
void __fastcall TfrmParamBus::ButtonOkClick(TObject *Sender)
{
 if (AppliqueChoix()) ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmParamBus::ButtonAppliquerClick(TObject *Sender)
{
 AppliqueChoix();
}
//---------------------------------------------------------------------------


void __fastcall TfrmParamBus::CSpinEditParametresChange(
      TObject *Sender)
{
 if (!InitialisationEnCours) ButtonAppliquer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamBus::CheckBoxClick(TObject *Sender)
{
 if (!CheckBoxTout->Tag)
  {
   if (((TCheckBox*)Sender)->Checked) // v5.3
     WindowState=wsMinimized;
   frmSimulation->DrawGridSimul->Repaint();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamBus::CheckBoxToutClick(TObject *Sender)
{
 CheckBoxTout->Tag=1;
 for(int i=0; i<NBMAXLIGNESBUSTRAM; i++)
   ((TCheckBox*)FindComponent("CheckBox"+IntToStr(i+1)))->Checked=(cv->LigneBus[i].NbArrets>0)?CheckBoxTout->Checked:false;
 CheckBoxTout->Tag=0;
 if (CheckBoxTout->Checked) // v5.3
   WindowState=wsMinimized;
 frmSimulation->DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmParamBus::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

