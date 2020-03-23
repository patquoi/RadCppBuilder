//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_infptn.h"
#include "f_simul.h"
#include "f_rech.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
#define NBSITUATIONS 13
#define NBPOSITIONS  5
//---------------------------------------------------------------------------
// Positions
#define DANSUNBUS  2
#define DANSUNTRAM 3
#define DANSUNTAXI 4
//---------------------------------------------------------------------------
// Situations
#define SEPROMENE      0
#define PSGPTTRV       1
#define ARRETBUSTRV    2
#define ARRETTRAMTRV   3
#define FILETAXITRV    4
#define ATTENDUNBUS    5
#define ATTENDDSLEBUS  6
#define ATTENDUNTRAM   7
#define ATTENDDSLETRAM 8
#define ATTENDUNTAXI   9
#define ATTENDDSLETAXI 10
#define VEUTDESCENDRE  11
#define ECRASE         12
//---------------------------------------------------------------------------
TfrmInfosPieton *frmInfosPieton;
//---------------------------------------------------------------------------
const AnsiString asDebutTitreCadrePieton="                           ",
                 asFrmNumeroCoordonnees="%d (%2.2d, %2.2d)",
                 asFrmCoordonnees="%2.2d, %2.2d",
                 asFrmPourcentage="%.3f%%",
                 asFrmDemiCase="%.1f",
                 asPosition[NBPOSITIONS]={"Entrée de la case", "Sortie de la case", "Dans un bus", "Dans un tram", "Dans un taxi"},
                 asSituation[NBSITUATIONS]={ "Se promène",
                                             "Se dirige vers un passage piétons",
                                             "Se dirige vers un arrêt de bus",
                                             "Se dirige vers un arrêt de trams",
                                             "Se dirige vers une file de taxis",
                                             "Attend un bus à l'arrêt",
                                             "Attend dans le bus",
                                             "Attend un tram à l'arrêt",
                                             "Attend dans le tram",
                                             "Attend un taxi en tête de file",
                                             "Attend dans le taxi",
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
  LabelBusTramTaxi->Visible=ARendreVisible;
  LabelArretBusTramFileTaxi->Visible=ARendreVisible;
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
        (v->NumTaxi!=cv->Pieton[NumPieton-1].NumTaxi)) // qu'il n'y en a pas dans un bus/tram/taxi qui se trouverait sur la case. v3.6
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

    if (p->VeutDescendre)
     Situation=VEUTDESCENDRE;

    if (p->Ecrase)
     Situation=ECRASE; // v4.3

    LabelSituation->Caption=asSituation[Situation];
    LabelParcours->Caption=Format(asFrmDemiCase, ARRAYOFCONST(( p->DemiCasesParcourues/2.0 )));
    if (p->NumBus)
     {
      LabelBusTramTaxi->Caption=Format( asFrmNumeroCoordonnees,
                                ARRAYOFCONST(( p->NumBus,
                                               cv->Bus[p->NumBus-1].x,
                                               cv->Bus[p->NumBus-1].y)));
      LabelPosition->Caption=asPosition[DANSUNBUS];
     }
    else
     if (p->NumTram)
      {
       LabelBusTramTaxi->Caption=Format( asFrmNumeroCoordonnees,
                                 ARRAYOFCONST(( p->NumTram,
                                                cv->Tram[p->NumTram-1].x,
                                                cv->Tram[p->NumTram-1].y)));
       LabelPosition->Caption=asPosition[DANSUNTRAM];
      }
     else
      if (p->NumTaxi) // v3.6
       {
        LabelBusTramTaxi->Caption=Format( asFrmNumeroCoordonnees,
                                  ARRAYOFCONST(( p->NumTaxi,
                                                 cv->Taxi[p->NumTaxi-1].x,
                                                 cv->Taxi[p->NumTaxi-1].y)));
        LabelPosition->Caption=asPosition[DANSUNTAXI];
       }
      else
       {
        LabelBusTramTaxi->Caption="Aucun";
        LabelPosition->Caption=asPosition[!!p->DemiCase];
       }
    if (p->NumArretBus)
     LabelArretBusTramFileTaxi->Caption=Format( asFrmNumeroCoordonnees,
                                    ARRAYOFCONST(( p->NumArretBus,
                                                   cv->ArretBus[p->NumArretBus-1].x,
                                                   cv->ArretBus[p->NumArretBus-1].y)));
    else
     if (p->NumArretTram)
      LabelArretBusTramFileTaxi->Caption=Format( asFrmNumeroCoordonnees,
                                     ARRAYOFCONST(( p->NumArretTram,
                                                    cv->ArretTram[p->NumArretTram-1].x,
                                                    cv->ArretTram[p->NumArretTram-1].y)));
     else
      if (p->NumFileTaxi)
       LabelArretBusTramFileTaxi->Caption=Format( asFrmNumeroCoordonnees,
                                      ARRAYOFCONST(( p->NumFileTaxi,
                                                     cv->PlaceTaxi[cv->PlaceTaxi[cv->FileTaxi[p->NumFileTaxi-1].NumPlaceQueue].PlaceTeteFile()].x,
                                                     cv->PlaceTaxi[cv->PlaceTaxi[cv->FileTaxi[p->NumFileTaxi-1].NumPlaceQueue].PlaceTeteFile()].y)));
      else
       LabelArretBusTramFileTaxi->Caption="Aucun";
   }
  RendreVisibleInfos(NumPieton>0);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmInfosPieton::FormShow(TObject *Sender)
{
 frmSimulation->ActionDetailPieton->Checked=true;
#ifdef CV_LINUX
 FormResize(this);
#endif
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
void __fastcall TfrmInfosPieton::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=XMAX(GroupBoxPieton)+LH_ESPACE,
     h=HMAX(ButtonOk,ButtonAide)+LH_ESPACE;
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

