//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_afdiste.h"
#include "f_simul.h"
#include "simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
TfrmAffDistEtapes *frmAffDistEtapes;
//---------------------------------------------------------------------------
#ifdef CV_LINUX
const AnsiString asDir1[NBDIR+1]={"", "   N", "   E", "   S", "   O"};
#endif
#ifdef CV_WINDOWS
const AnsiString asDir1[NBDIR+1]={"", "   ­", "   ®", "   ¯", "   ¬"};
#endif
//---------------------------------------------------------------------------
__fastcall TfrmAffDistEtapes::TfrmAffDistEtapes(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void TfrmAffDistEtapes::EffaceInfos()
 {
  int i,
      NbCol=StringGridDistances->ColCount,
      NbLig=StringGridDistances->RowCount,
      NbCases=NbCol*NbLig;
  for(i=0; i<NbCases; i++) StringGridDistances->Cells[i%NbCol][i/NbCol]="";
 }
//---------------------------------------------------------------------------
void TfrmAffDistEtapes::RafraichitInfos()
 {
  int i, NbCases, NbX, de,
      x=frmSimulation->DrawGridSimul->Col,
      y=frmSimulation->DrawGridSimul->Row;
  voie *v=&(cv->v[x][y]);
  EffaceInfos();
  if (!v->DistEtape) return;
  NbCases=(NbX=1+NbDir[v->DirPoss])*(1+cv->NbEtapes);
  Caption="Etapes "+Format(asFormatCoord, ARRAYOFCONST((x, y)));
  for(i=0; i<NbCases; i++)
   {
    if (i)
     {
      if (!(i%NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=Format("%5d", ARRAYOFCONST((i/NbX)));
      if (i&&(i<NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=asDir1[Dirdp[i%NbX-1][v->DirPoss]];
      if ((i%NbX)&&(i>=NbX)) // v3.5
       StringGridDistances->Cells[i%NbX][i/NbX]=((de=v->DistEtape[i/NbX-1][i%NbX-1][CheckBoxCouloirsBus->Checked])==DIST_INDEFINIE)?AnsiString("     "):Format("%5d", ARRAYOFCONST((de)));
     }
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistEtapes::FormShow(TObject *Sender)
{
 frmSimulation->ActionDistancesEtapes->Checked=true;
 StringGridDistances->RowCount=1+cv->NbEtapes;
 Height=(cv->NbEtapes>10)?300:(43+21*StringGridDistances->RowCount);
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistEtapes::FormHide(TObject *Sender)
{
 frmSimulation->ActionDistancesEtapes->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistEtapes::CheckBoxCouloirsBusClick(
      TObject *Sender)
{
 RafraichitInfos();
}
//---------------------------------------------------------------------------

