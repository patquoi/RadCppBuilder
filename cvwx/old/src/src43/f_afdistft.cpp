//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_afdistft.h"
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
TfrmAffDistFilesTaxi *frmAffDistFilesTaxi;
//---------------------------------------------------------------------------
#ifdef CV_LINUX
const AnsiString asDir1[NBDIR+1]={"", "   N", "   E", "   S", "   O"};
#endif
#ifdef CV_WINDOWS
const AnsiString asDir1[NBDIR+1]={"", "   ­", "   ®", "   ¯", "   ¬"};
#endif
//---------------------------------------------------------------------------
__fastcall TfrmAffDistFilesTaxi::TfrmAffDistFilesTaxi(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void TfrmAffDistFilesTaxi::EffaceInfos()
 {
  int i,
      NbCol=StringGridDistances->ColCount,
      NbLig=StringGridDistances->RowCount,
      NbCases=NbCol*NbLig;
  for(i=0; i<NbCases; i++) StringGridDistances->Cells[i%NbCol][i/NbCol]="";
 }
//---------------------------------------------------------------------------
void TfrmAffDistFilesTaxi::RafraichitInfos()
 {
  int i, NbCases, NbX, de,
      x=frmSimulation->DrawGridSimul->Col,
      y=frmSimulation->DrawGridSimul->Row;
  voie *v=&(cv->v[x][y]);
  EffaceInfos();
  if (!v->DistFileTaxi) return;
  NbCases=(NbX=1+NbDir[v->DirPoss])*(1+cv->NbFilesTaxi);
  Caption="Files de taxis "+Format(asFormatCoord, ARRAYOFCONST((x, y)));
  for(i=0; i<NbCases; i++)
   {
    if (i)
     {
      if (!(i%NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=Format("%5d", ARRAYOFCONST((i/NbX)));
      if (i&&(i<NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=asDir1[Dirdp[i%NbX-1][v->DirPoss]];
      if ((i%NbX)&&(i>=NbX))
       StringGridDistances->Cells[i%NbX][i/NbX]=((de=v->DistFileTaxi[i/NbX-1][i%NbX-1])==DIST_INDEFINIE)?AnsiString("     "):Format("%5d", ARRAYOFCONST((de)));
     }
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistFilesTaxi::FormShow(TObject *Sender)
{
 frmSimulation->ActionDistancesFilesTaxi->Checked=true;
 StringGridDistances->RowCount=1+cv->NbFilesTaxi;
 Height=(cv->NbFilesTaxi>10)?283:(26+21*StringGridDistances->RowCount);
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistFilesTaxi::FormHide(TObject *Sender)
{
 frmSimulation->ActionDistancesFilesTaxi->Checked=false;
}
//---------------------------------------------------------------------------

