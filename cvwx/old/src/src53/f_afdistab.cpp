//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_afdistab.h"
#include "f_simul.h"
#include "simul.h"
#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmAffDistArretsBus *frmAffDistArretsBus;
//---------------------------------------------------------------------------
const AnsiString asDir1[NBDIR+1]={"", "   ­", "   ®", "   ¯", "   ¬"};
//---------------------------------------------------------------------------
__fastcall TfrmAffDistArretsBus::TfrmAffDistArretsBus(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void TfrmAffDistArretsBus::EffaceInfos()
 {
  int i,
      NbCol=StringGridDistances->ColCount,
      NbLig=StringGridDistances->RowCount,
      NbCases=NbCol*NbLig;
  for(i=0; i<NbCases; i++) StringGridDistances->Cells[i%NbCol][i/NbCol]="";
 }
//---------------------------------------------------------------------------
void TfrmAffDistArretsBus::RafraichitInfos()
 {
  int i, NbCases, NbX, de,
      x=frmSimulation->DrawGridSimul->Col,
      y=frmSimulation->DrawGridSimul->Row;
  voie *v=&(cv->v[x][y]);
  EffaceInfos();
  if (!v->DistArretBus) return;
  NbCases=(NbX=1+NbDir[v->DirPoss])*(1+cv->NbArretsBus);
  Caption="Arrêts bus "+Format(asFormatCoord, ARRAYOFCONST((x, y)));
  for(i=0; i<NbCases; i++)
   {
    if (i)
     {
      if (!(i%NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=Format("%5d", ARRAYOFCONST((i/NbX)));
      if (i&&(i<NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=asDir1[Dirdp[i%NbX-1][v->DirPoss]];
      if ((i%NbX)&&(i>=NbX))
       StringGridDistances->Cells[i%NbX][i/NbX]=((de=v->DistArretBus[i/NbX-1][i%NbX-1])==DIST_INDEFINIE)?AnsiString("     "):Format("%5d", ARRAYOFCONST((de)));
     }
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistArretsBus::FormShow(TObject *Sender)
{
 frmSimulation->ActionDistancesArretsBus->Checked=true;
 StringGridDistances->RowCount=1+cv->NbArretsBus;
 Height=(cv->NbArretsBus>10)?283:(26+21*StringGridDistances->RowCount);
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistArretsBus::FormHide(TObject *Sender)
{
 frmSimulation->ActionDistancesArretsBus->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAffDistArretsBus::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

