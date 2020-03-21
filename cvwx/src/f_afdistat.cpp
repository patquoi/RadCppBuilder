//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "base.h"
#include "simul.h"
#include "f_afdistat.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmAffDistArretsTram *frmAffDistArretsTram;
//---------------------------------------------------------------------------
const AnsiString asDir1[NBDIR+1]={"", "   ­", "   ®", "   ¯", "   ¬"};
//---------------------------------------------------------------------------
__fastcall TfrmAffDistArretsTram::TfrmAffDistArretsTram(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void TfrmAffDistArretsTram::EffaceInfos()
 {
  int i,
      NbCol=StringGridDistances->ColCount,
      NbLig=StringGridDistances->RowCount,
      NbCases=NbCol*NbLig;
  for(i=0; i<NbCases; i++) StringGridDistances->Cells[i%NbCol][i/NbCol]="";
 }
//---------------------------------------------------------------------------
void TfrmAffDistArretsTram::RafraichitInfos()
 {
  int i, NbCases, NbX, de,
      x=frmSimulation->DrawGridSimul->Col,
      y=frmSimulation->DrawGridSimul->Row;
  voie *v=&(cv->v[x][y]);
  EffaceInfos();
  if (!v->DistArretTram) return;
  NbCases=(NbX=1+v->NbDirPossSensVoieTram(indefinie))*(1+cv->NbArretsTram);
  Caption="Arrêts tram "+Format(asFormatCoord, ARRAYOFCONST((x, y)));
  for(i=0; i<NbCases; i++)
   {
    if (i)
     {
      if (!(i%NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=Format("%5d", ARRAYOFCONST((i/NbX)));
      if (i&&(i<NbX)) StringGridDistances->Cells[i%NbX][i/NbX]=asDir1[v->DirSensVoieTram(indefinie, i%NbX-1)];
	  if ((i%NbX)&&(i>=NbX)) // v5.4 : conversion BCB6>BCBX (AnsiString>String)
	   StringGridDistances->Cells[i%NbX][i/NbX]=((de=v->DistArretTram[i/NbX-1][i%NbX-1])==DIST_INDEFINIE)?String("     "):Format("%5d", ARRAYOFCONST((de)));
	 }
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistArretsTram::FormShow(TObject *Sender)
{
 frmSimulation->ActionDistancesArretsTram->Checked=true;
 StringGridDistances->RowCount=1+cv->NbArretsTram;
 Height=(cv->NbArretsTram>10)?283:(26+21*StringGridDistances->RowCount);
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAffDistArretsTram::FormHide(TObject *Sender)
{
 frmSimulation->ActionDistancesArretsTram->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAffDistArretsTram::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

