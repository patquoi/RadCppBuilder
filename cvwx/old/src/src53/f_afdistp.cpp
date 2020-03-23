//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_afdistp.h"
#include "f_simul.h"
#include "simul.h"
#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmAffDistParkings *frmAffDistParkings;
//---------------------------------------------------------------------------
const AnsiString asDir1[NBDIR+1]={"", "   ­", "   ®", "   ¯", "   ¬"};
//---------------------------------------------------------------------------
__fastcall TfrmAffDistParkings::TfrmAffDistParkings(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void TfrmAffDistParkings::EffaceInfos()
 {
  int i,
      NbCol=StringGridDistances->ColCount,
      NbLig=StringGridDistances->RowCount,
      NbCases=NbCol*NbLig;
  for(i=0; i<NbCases; i++) StringGridDistances->Cells[i%NbCol][i/NbCol]="";
 }
//---------------------------------------------------------------------------
void TfrmAffDistParkings::RafraichitInfos()
 {
  int i, NbCases, NbX, de,
      x=frmSimulation->DrawGridSimul->Col,
      y=frmSimulation->DrawGridSimul->Row;
  voie *v=&(cv->v[x][y]);
  EffaceInfos();
  if (!v->DistParking) return;
  NbCases=(NbX=1+NbDir[v->DirPoss])*(1+cv->NbParkings);
  Caption="Parkings "+Format(asFormatCoord, ARRAYOFCONST((x, y)));
  for(i=0; i<NbCases; i++)
   {
    if (i)
     {
      if (!(i%NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=Format("%5d", ARRAYOFCONST((i/NbX)));
      if (i&&(i<NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=asDir1[Dirdp[i%NbX-1][v->DirPoss]];
      if ((i%NbX)&&(i>=NbX)) // v3.5
       StringGridDistances->Cells[i%NbX][i/NbX]=((de=v->DistParking[i/NbX-1][i%NbX-1][CheckBoxCouloirsBus->Checked])==DIST_INDEFINIE)?AnsiString("     "):Format("%5d", ARRAYOFCONST((de)));
     }
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistParkings::FormShow(TObject *Sender)
{
 frmSimulation->ActionDistancesParkings->Checked=true;
 StringGridDistances->RowCount=1+cv->NbParkings;
 Height=(cv->NbParkings>10)?300:(43+21*StringGridDistances->RowCount);
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistParkings::FormHide(TObject *Sender)
{
 frmSimulation->ActionDistancesParkings->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistParkings::CheckBoxCouloirsBusClick(
      TObject *Sender)
{
 RafraichitInfos();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAffDistParkings::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

