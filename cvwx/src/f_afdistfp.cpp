//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "base.h"
#include "simul.h"
#include "f_afdistfp.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmAffDistFilesPark *frmAffDistFilesPark;
//---------------------------------------------------------------------------
const AnsiString asDir1[NBDIR+1]={"", "   �", "   �", "   �", "   �"};
//---------------------------------------------------------------------------
__fastcall TfrmAffDistFilesPark::TfrmAffDistFilesPark(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void TfrmAffDistFilesPark::EffaceInfos()
 {
  int i,
      NbCol=StringGridDistances->ColCount,
      NbLig=StringGridDistances->RowCount,
      NbCases=NbCol*NbLig;
  for(i=0; i<NbCases; i++) StringGridDistances->Cells[i%NbCol][i/NbCol]="";
 }
//---------------------------------------------------------------------------
void TfrmAffDistFilesPark::RafraichitInfos()
 {
  int i, NbCases, NbX, de,
      x=frmSimulation->DrawGridSimul->Col,
      y=frmSimulation->DrawGridSimul->Row;
  voie *v=&(cv->v[x][y]);
  EffaceInfos();
  if (!v->DistFilePark) return;
  NbCases=(NbX=1+NbDir[v->DirPoss])*(1+cv->NbFilesPark);
  Caption="Files parking "+Format(asFormatCoord, ARRAYOFCONST((x, y)));
  for(i=0; i<NbCases; i++)
   {
    if (i)
     {
      if (!(i%NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=Format("%5d", ARRAYOFCONST((i/NbX)));
	  if (i&&(i<NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=asDir1[Dirdp[i%NbX-1][v->DirPoss]];
	  if ((i%NbX)&&(i>=NbX)) // v5.4 : conversion BCB6>BCBX (AnsiString>String)
	   StringGridDistances->Cells[i%NbX][i/NbX]=((de=v->DistFilePark[i/NbX-1][i%NbX-1][CheckBoxCouloirsBus->Checked])==DIST_INDEFINIE)?String("     "):Format("%5d", ARRAYOFCONST((de)));
     }
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistFilesPark::FormShow(TObject *Sender)
{
 frmSimulation->ActionDistancesFilesPark->Checked=true;
 StringGridDistances->RowCount=1+cv->NbFilesPark;
 Height=(cv->NbFilesPark>10)?283:(26+21*StringGridDistances->RowCount);
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistFilesPark::FormHide(TObject *Sender)
{
 frmSimulation->ActionDistancesFilesPark->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistFilesPark::CheckBoxCouloirsBusClick(
      TObject *Sender)
{
 RafraichitInfos();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAffDistFilesPark::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{// v5.3 (n�cessite TForm:KeyPreview � true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

