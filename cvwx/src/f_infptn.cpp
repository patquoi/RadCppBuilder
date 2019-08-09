//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_infptn.h"
#include "f_simul.h"
#include "f_rech.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#define NBSITUATIONS 16 // v5.3 (+3)
#define NBPOSITIONS  6  // v5.3 (+1)
//---------------------------------------------------------------------------
// Positions
#define DANSUNBUS  2
#define DANSUNTRAM 3
#define DANSUNTAXI 4
#define DANSVEHLIB 5 // v5.3
//---------------------------------------------------------------------------
// Situations
#define SEPROMENE      0
#define PSGPTTRV       1
#define ARRETBUSTRV    2
#define ARRETTRAMTRV   3
#define FILETAXITRV    4
#define PLACEVEHLIBTRV 5
#define ATTENDUNBUS    6
#define ATTENDDSLEBUS  7
#define ATTENDUNTRAM   8
#define ATTENDDSLETRAM 9
#define ATTENDUNTAXI   10
#define ATTENDDSLETAXI 11
#define ATTENDUNVEHLIB 12 // v5.3
#define ATTENDDSVEHLIB 13 // v5.3
#define VEUTDESCENDRE  14
#define ECRASE         15
//---------------------------------------------------------------------------
TfrmInfosPieton *frmInfosPieton;
//---------------------------------------------------------------------------
const AnsiString asDebutTitreCadrePieton="                           ",
                 asFrmNumeroCoordonnees="%d (%2.2d, %2.2d)",
                 asFrmCoordonnees="%2.2d, %2.2d",
                 asFrmPourcentage="%.3f%%",
                 asFrmDemiCase="%.1f",
                 asPosition[NBPOSITIONS]={"Entrée de la case", "Sortie de la case", "Dans un bus", "Dans un tram", "Dans un taxi", "ans un vehlib"}, // v5.3 (vehlib)
                 asSituation[NBSITUATIONS]={ "Se promène",
                                             "Se dirige vers un passage piéton",
                                             "Se dirige vers un arrêt de bus",
                                             "Se dirige vers un arrêt de trams",
                                             "Se dirige vers une file de taxis",
                                             "Se dirige vers une file de vehlibs", // v5.3
                                             "Attend un bus à l'arrêt",
                                             "Attend dans le bus",
                                             "Attend un tram à l'arrêt",
                                             "Attend dans le tram",
                                             "Attend un taxi en tête de file",
                                             "Attend dans le taxi",
                                             "Attend un vehlib", // v5.3
                                             "Attend dans le vehlib", // v5.3
                                             "Descend au prochain arrêt",
                                             "Ecrasé"};
//---------------------------------------------------------------------------
__fastcall TfrmInfosPieton::TfrmInfosPieton(TComponent* Owner)
    : TForm(Owner)
{
 NumPieton=0;
}
//---------------------------------------------------------------------------
void TfrmInfosPieton::RendreVisibleInfos(bool ARendreVisible)
 {
  int i;
  GroupBoxPieton->Caption=asDebutTitreCadrePieton;
  if (ARendreVisible)
   {
    if (!p->NumBus)
     GroupBoxPieton->Caption= GroupBoxPieton->Caption+
                              Format( asFrmNumeroCoordonnees,
                                      ARRAYOFCONST((NumPieton, p->x, p->y)))+" ";
    else
     GroupBoxPieton->Caption= GroupBoxPieton->Caption+
                              Format( asFrmNumeroCoordonnees,
                                      ARRAYOFCONST(( NumPieton,
                                                     cv->Bus[p->NumBus-1].x,
                                                     cv->Bus[p->NumBus-1].y)))+" ";
   }
  RadioButtonAucunPieton->Enabled=!ARendreVisible;
  RadioButtonAucunPieton->Checked=!ARendreVisible;
  RadioButtonPietonNumero->Checked=ARendreVisible;
  RadioButtonPietonNumero->Enabled=ARendreVisible;
  for(i=1; i<7; i++)
   ((TLabel*)FindComponent("Label"+IntToStr(i)))->Enabled=ARendreVisible;
  LabelDirection->Visible=ARendreVisible;
  LabelPosition->Visible=ARendreVisible;
  LabelSituation->Visible=ARendreVisible;
  LabelParcours->Visible=ARendreVisible;
  LabelBusTramTaxiVehlib->Visible=ARendreVisible;  // v5.3 ajout de Vehlib dans le nom
  LabelArretBusTramFileTaxiVehlib->Visible=ARendreVisible; // v5.3 ajout de Vehlib dans le nom
 }
//---------------------------------------------------------------------------
void TfrmInfosPieton::RafraichitInfos()
 {
  int Situation=0;
  x=frmSimulation->DrawGridSimul->Col;
  y=frmSimulation->DrawGridSimul->Row;
  v=&(cv->v[x][y]);
  p=NULL;
  NumPieton=0;
  LabelCoordonnees->Caption=Format(asFrmCoordonnees, ARRAYOFCONST((x, y)));
  if (frmRecherche&&
      frmRecherche->Visible&&
      frmRecherche->RadioButtonPieton->Checked)
   NumPieton=frmRecherche->CSpinEditPieton->Value;
  if (!NumPieton) // Si pas de piéton suivi, on cherche parmi ceux de la case courante
   {
    if (v->NumPieton[0])
     NumPieton=v->NumPieton[0];
    else
     if (v->NumPieton[1])
      NumPieton=v->NumPieton[1];
   }
  else
   {
    if ((v->NumPieton[0]!=NumPieton)&& // Si pas trouvé de piéton
        (v->NumPieton[1]!=NumPieton)&& // sur la case courante ET
        (v->NumBus!=cv->Pieton[NumPieton-1].NumBus)&&
        (v->NumTram!=cv->Pieton[NumPieton-1].NumTram)&&
        (v->NumTaxi!=cv->Pieton[NumPieton-1].NumTaxi)&&
        (v->NumVehlib!=cv->Pieton[NumPieton-1].NumVehlib)) // qu'il n'y en a pas dans un bus/tram/taxi/vehlib qui se trouverait sur la case. v3.6. v5.3 (vehlib)
     { // On cherche un autre piéton
      if (v->NumPieton[0])
       NumPieton=v->NumPieton[0];
      else
       if (v->NumPieton[1])
        NumPieton=v->NumPieton[1];
     }
   }
  if (NumPieton)
   {
    p=&(cv->Pieton[NumPieton-1]);
    LabelDirection->Caption=asDir[p->Dir];
    if (p->PsgPtTrv)
     Situation=PSGPTTRV;
    if (p->ArretBusTrv)
     Situation=ARRETBUSTRV;
    if (p->ArretTramTrv)
     Situation=ARRETTRAMTRV;
    if (p->FileTaxiTrv)
     Situation=FILETAXITRV;
    if (p->FileTaxiTrv) // v5.3
     Situation=PLACEVEHLIBTRV;

    if (p->AttendBus)
     Situation=ATTENDUNBUS;
    if (p->NumBus)
     Situation=ATTENDDSLEBUS;

    if (p->AttendTram)
     Situation=ATTENDUNTRAM;
    if (p->NumTram)
     Situation=ATTENDDSLETRAM;

    if (p->AttendTaxi)
     Situation=ATTENDUNTAXI;
    if (p->NumTaxi)
     Situation=ATTENDDSLETAXI;

    if (p->AttendVehlib) // v5.3
     Situation=ATTENDUNVEHLIB;
    if (p->NumVehlib) // v5.3
     Situation=ATTENDDSVEHLIB;

    if (p->VeutDescendre)
     Situation=VEUTDESCENDRE;

    if (p->Ecrase)
     Situation=ECRASE; // v4.3

	LabelSituation->Caption=asSituation[Situation];
	// v1.8.4 : FormatFloat au lieu de Format
    LabelParcours->Caption=FormatFloat(asFrmDemiCase, p->DemiCasesParcourues/2.0);
    // v5.3 ajout de Vehlib dans les noms de TLabel communs (LabelBusTramTaxiVehlib et LabelArretBusTramFileTaxiVehlib)
    if (p->NumBus)
     {
      LabelBusTramTaxiVehlib->Caption=Format( asFrmNumeroCoordonnees,
                                ARRAYOFCONST(( p->NumBus,
                                               cv->Bus[p->NumBus-1].x,
                                               cv->Bus[p->NumBus-1].y)));
      LabelPosition->Caption=asPosition[DANSUNBUS];
     }
    else
     if (p->NumTram)
      {
       LabelBusTramTaxiVehlib->Caption=Format( asFrmNumeroCoordonnees,
                                 ARRAYOFCONST(( p->NumTram,
                                                cv->Tram[p->NumTram-1].x,
                                                cv->Tram[p->NumTram-1].y)));
       LabelPosition->Caption=asPosition[DANSUNTRAM];
      }
     else
      if (p->NumTaxi) // v3.6
       {
        LabelBusTramTaxiVehlib->Caption=Format( asFrmNumeroCoordonnees,
                                  ARRAYOFCONST(( p->NumTaxi,
                                                 cv->Taxi[p->NumTaxi-1].x,
                                                 cv->Taxi[p->NumTaxi-1].y)));
        LabelPosition->Caption=asPosition[DANSUNTAXI];
       }
      else
       if (p->NumVehlib) // v5.3
        {
         LabelBusTramTaxiVehlib->Caption=Format( asFrmNumeroCoordonnees,
                                   ARRAYOFCONST(( p->NumVehlib,
                                                  cv->Vehlib[p->NumVehlib-1].x,
                                                  cv->Vehlib[p->NumVehlib-1].y)));
         LabelPosition->Caption=asPosition[DANSVEHLIB];
       }
      else
       {
        LabelBusTramTaxiVehlib->Caption="Aucun";
        LabelPosition->Caption=asPosition[!!p->DemiCase];
       }
    if (p->NumArretBus)
     LabelArretBusTramFileTaxiVehlib->Caption=Format( asFrmNumeroCoordonnees,
                                    ARRAYOFCONST(( p->NumArretBus,
                                                   cv->ArretBus[p->NumArretBus-1].x,
                                                   cv->ArretBus[p->NumArretBus-1].y)));
    else
     if (p->NumArretTram)
      LabelArretBusTramFileTaxiVehlib->Caption=Format( asFrmNumeroCoordonnees,
                                     ARRAYOFCONST(( p->NumArretTram,
                                                    cv->ArretTram[p->NumArretTram-1].x,
                                                    cv->ArretTram[p->NumArretTram-1].y)));
     else
      if (p->NumFileTaxi)
       LabelArretBusTramFileTaxiVehlib->Caption=Format( asFrmNumeroCoordonnees,
                                      ARRAYOFCONST(( p->NumFileTaxi,
                                                     cv->PlaceTaxi[cv->PlaceTaxi[cv->FileTaxi[p->NumFileTaxi-1].NumPlaceQueue].PlaceTeteFile()].x,
                                                     cv->PlaceTaxi[cv->PlaceTaxi[cv->FileTaxi[p->NumFileTaxi-1].NumPlaceQueue].PlaceTeteFile()].y)));
      else
       LabelArretBusTramFileTaxiVehlib->Caption="Aucun";
   }
  RendreVisibleInfos(NumPieton>0);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmInfosPieton::FormShow(TObject *Sender)
{
 frmSimulation->ActionDetailPieton->Checked=true;
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosPieton::FormHide(TObject *Sender)
{
 frmSimulation->ActionDetailPieton->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosPieton::ButtonOkClick(TObject *Sender)
{
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosPieton::ButtonAideClick(TObject *Sender)
{ // v3.0
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------

void __fastcall TfrmInfosPieton::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

