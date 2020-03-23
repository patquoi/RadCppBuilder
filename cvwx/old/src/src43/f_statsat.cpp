//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_statsat.h"
#include "simul.h"
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
#define ATTENTE 0
#define TRAFIC  1
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#define RGB(r,g,b) ((TColor)(0x00000001*(TColor)(r)+0x00000100*(TColor)(g)+0x00010000*(TColor)(b)))
#endif
//---------------------------------------------------------------------------
TfrmStatsAttenteTrafic *frmStatsAttenteTrafic;
//---------------------------------------------------------------------------
__fastcall TfrmStatsAttenteTrafic::TfrmStatsAttenteTrafic(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsAttenteTrafic::PaintBoxPaint(
      TObject *Sender)
{
 for(int i=0; i<128; i++)
  {
   PaintBox->Canvas->Pen->Color=(TColor)RGB((i<64)?4*i:252,(i>=64)?252-4*(i-64):252,0);
   PaintBox->Canvas->MoveTo(i, 0);
   PaintBox->Canvas->LineTo(i, PaintBox->Height-1);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsAttenteTrafic::FormShow(TObject *Sender)
{
#ifdef CV_LINUX
 FormResize(this);
#endif
 if (cv->TourCrt)
  Caption="Statistiques de fluidité et de trafic au tour n°"+IntToStr(cv->TourCrt);
 CSpinEditEtapeDepart->MAXVALUE=cv->NbEtapes;
 CSpinEditEtapeArrivee->MAXVALUE=cv->NbEtapes;
 RecalculeEtVisualise();
}
//---------------------------------------------------------------------------
TColor TfrmStatsAttenteTrafic::CouleurCase(int x, int y)
 {
  int s,
      ed=CheckBoxEtapeDepart->Checked?CSpinEditEtapeDepart->Value:0,
      ea=CheckBoxEtapeArrivee->Checked?CSpinEditEtapeArrivee->Value:0,
      ts=RadioGroupType->ItemIndex;
  if (m[ts]&&cv->v[x][y].Trafic&&cv->v[x][y].Attente) // v3.0
   {
    if (ts)
     s=(127*cv->v[x][y].Trafic[ed][ea])/m[ts];
    else
     s=(127*cv->v[x][y].Attente[ed][ea])/m[ts];
    return (TColor)RGB((s<64)?4*s:252,(s>=64)?252-4*(s-64):252,0);
   }
  else
   return (TColor)0;
 }
//---------------------------------------------------------------------------
AnsiString TfrmStatsAttenteTrafic::asMsgDetailCase(int x, int y)
 {  // v3.0
  AnsiString asMsg;
  int ed=CheckBoxEtapeDepart->Checked?CSpinEditEtapeDepart->Value:0,
      ea=CheckBoxEtapeArrivee->Checked?CSpinEditEtapeArrivee->Value:0,
      ts=RadioGroupType->ItemIndex;
  if (m[ts]&&cv->v[x][y].Trafic&&cv->v[x][y].Attente)
   if (ts)
    asMsg=Format( "Trafic en (%d, %d) au tour %d : %d véhicules (Max. %d) soit %.3f%%",
                  ARRAYOFCONST(( x, y, (int)cv->TourCrt,
                                 cv->v[x][y].Trafic[ed][ea], m[ts],
                                 (100.0*cv->v[x][y].Trafic[ed][ea])/m[ts])));
   else
    asMsg=Format( "Attente en (%d, %d) au tour %d : %d tours (Max. %d) soit %.3f%%",
                  ARRAYOFCONST(( x, y, (int)cv->TourCrt,
                                 cv->v[x][y].Attente[ed][ea], m[ts],
                                 (100.0*cv->v[x][y].Attente[ed][ea])/m[ts])));
  return asMsg;
 }
//---------------------------------------------------------------------------
void TfrmStatsAttenteTrafic::RecalculeEtVisualise()
{
 int x, y, n=0, t[2]={0,0},
     ed=CheckBoxEtapeDepart->Checked?CSpinEditEtapeDepart->Value:0,
     ea=CheckBoxEtapeArrivee->Checked?CSpinEditEtapeArrivee->Value:0;
 if ((ed<0)||(ed>cv->NbEtapes)||(ea<0)||(ea>cv->NbEtapes))
  {
   AfficheMessage("Le n° d'étape est incorrect !", "Valeur incorrecte", tmAvertissement, 0, 0);
   return;
  }
 m[0]=0; m[1]=0;
 for(x=0; x<cv->NbX; x++)
  for(y=0; y<cv->NbY; y++)
   if ((cv->v[x][y].DirPoss>aucune)&&(!cv->v[x][y].NumEtape))
    {
     n++;
     if (cv->v[x][y].Attente&&cv->v[x][y].Trafic)
      {
       if (cv->v[x][y].Attente[ed][ea]>m[ATTENTE]) m[ATTENTE]=cv->v[x][y].Attente[ed][ea];
       t[ATTENTE]+=cv->v[x][y].Attente[ed][ea];
       if (cv->v[x][y].Trafic[ed][ea]>m[TRAFIC]) m[TRAFIC]=cv->v[x][y].Trafic[ed][ea];
       t[TRAFIC]+=cv->v[x][y].Trafic[ed][ea];
      }
    }
 LabelMax->Caption=IntToStr(m[RadioGroupType->ItemIndex]);
 LabelAttenteCumulee->Caption=IntToStr(t[ATTENTE]);
 if (n)
  LabelAttenteMoyenne->Caption=Format("%.1f", ARRAYOFCONST((1.0*t[ATTENTE]/n)));
 else
  LabelAttenteMoyenne->Caption="N/D";
 LabelAttenteMaximale->Caption=IntToStr(m[ATTENTE]);
 LabelTraficCumule->Caption=IntToStr(t[TRAFIC]);
 if (n)
  LabelTraficMoyen->Caption=Format("%.1f", ARRAYOFCONST((1.0*t[TRAFIC]/n)));
 else
  LabelTraficMoyen->Caption="N/D";
 LabelTraficMaximal->Caption=IntToStr(m[TRAFIC]);
 frmSimulation->DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsAttenteTrafic::ParametresEtapesClick(TObject *Sender)
{
 switch(((TComponent*)Sender)->Tag) // Comportements propres à certains objets
  {
   case 1: CSpinEditEtapeDepart->Enabled=CheckBoxEtapeDepart->Checked;
           if (CSpinEditEtapeDepart->Enabled) CSpinEditEtapeDepart->SetFocus();
           break;
   case 2: CSpinEditEtapeArrivee->Enabled=CheckBoxEtapeArrivee->Checked;
           if (CSpinEditEtapeArrivee->Enabled) CSpinEditEtapeArrivee->SetFocus();
           break;
  }
 RecalculeEtVisualise();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsAttenteTrafic::RadioGroupTypeClick(
      TObject *Sender)
{
 LabelMax->Caption=IntToStr(m[RadioGroupType->ItemIndex]);
 frmSimulation->DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsAttenteTrafic::BitBtn22Click(
      TObject *Sender)
{
 frmSimulation->ActionZoom->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsAttenteTrafic::BitBtnDirClick(
      TObject *Sender)
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
void __fastcall TfrmStatsAttenteTrafic::RubriqueClick(
      TObject *Sender)
{
 ((TBitBtn*)FindComponent("BitBtn"+IntToStr(((TComponent*)Sender)->Tag)))->Click();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsAttenteTrafic::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=LMAX(BitBtn32,LabelAttenteCumulee)+LH_ESPACE,
     h=max( YMAX(LabelTraficMaximal),
            HMAX(GroupBoxLegende,Label6))+LH_ESPACE;
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

