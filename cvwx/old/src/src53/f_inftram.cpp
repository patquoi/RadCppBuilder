//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_inftram.h"
#include "f_simul.h"
#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
// Pour asFrmNumeroCoordonnees
#define NXY 0
#define DRN 1
#define SVT 2
//---------------------------------------------------------------------------
TfrmInfosTram *frmInfosTram;
//---------------------------------------------------------------------------
const AnsiString asDebutTitreCadreTram="                           ",
                 asFrmNumeroCoordonnees[3]={ "%d (%2.2d, %2.2d)",
                                             "%d (%2.2d, %2.2d)  jusqu'au tour %d",
                                             "%d (%2.2d, %2.2d) depuis le tour %d"},
                 asFrmCoordonnees="%2.2d, %2.2d",
                 asFrmPourcentage="%.3f%%",
                 asFrmVitesse="%d/%d";
//---------------------------------------------------------------------------
__fastcall TfrmInfosTram::TfrmInfosTram(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmInfosTram::RendreVisibleInfos(bool ARendreVisible)
 {
  int i;
  GroupBoxTram->Caption=asDebutTitreCadreTram;
  if (ARendreVisible)
   {
    RadioButtonTramNumero->Checked=true;
    GroupBoxTram->Caption= GroupBoxTram->Caption+
                               Format( asFrmNumeroCoordonnees[NXY],
                                       ARRAYOFCONST((v->NumTram, Tram->x, Tram->y)))+
                               " ";
   }
  else
   RadioButtonAucunTram->Checked=true;
  RadioButtonTramNumero->Enabled=ARendreVisible;
  RadioButtonAucunTram->Enabled=!ARendreVisible;
  for(i=1; i<16; i++)
   ((TLabel*)FindComponent("Label"+IntToStr(i)))->Enabled=ARendreVisible;
  LabelDirection->Visible=ARendreVisible;
  LabelNumeroLigne->Visible=ARendreVisible;
  LabelNbPersonnes->Visible=ARendreVisible;
  LabelDernierArret->Visible=ARendreVisible;
  LabelProchainArret->Visible=ARendreVisible;
  LabelTours->Visible=ARendreVisible;
  LabelParcours->Visible=ARendreVisible;
  LabelToursEntreArrets->Visible=ARendreVisible;
  LabelParcoursEntreArrets->Visible=ARendreVisible;
  LabelDistance->Visible=ARendreVisible;
  LabelDistanceMin->Visible=ARendreVisible;
  LabelParcoursEffectue->Visible=ARendreVisible;
  LabelDetour->Visible=ARendreVisible;
  LabelAttente->Visible=ARendreVisible;
  LabelVitesse->Visible=ARendreVisible;
 }
//---------------------------------------------------------------------------
void TfrmInfosTram::RafraichitInfos()
 {
  int i,
      NbTours,
      NumDrnArret,
      NumArretSvt,
      NbDirPoss,
      DejaParcouru,
      ResteAParcourir,
      DistMin;
  voie *DrnArret;
  bool Afficher;
  x=frmSimulation->DrawGridSimul->Col;
  y=frmSimulation->DrawGridSimul->Row;
  v=&(cv->v[x][y]);
  Tram=NULL;
  LabelCoordonnees->Caption=Format(asFrmCoordonnees, ARRAYOFCONST((x, y)));
  if (Afficher=(v->NumTram>0))
   {
    Tram=cv->Tram+v->NumTram-1;
    LabelDirection->Caption=asDir[Tram->Dir];
    LabelNumeroLigne->Caption=AnsiString(char('A'+Tram->NumLigne-1));
    if (NumDrnArret=Tram->NumDrnArret)
     {
      LabelDernierArret->Caption=Format( asFrmNumeroCoordonnees[DRN],
                                         ARRAYOFCONST(( NumDrnArret,
                                                        cv->ArretTram[NumDrnArret-1].x,
                                                        cv->ArretTram[NumDrnArret-1].y,
                                                        (int)Tram->TourArriveDrnArret)));
      DrnArret=&(cv->v[cv->ArretTram[NumDrnArret-1].x][cv->ArretTram[NumDrnArret-1].y]);
     }
    else
     { // Si pas encore d'arrêt... On prend le premier arrêt de la ligne comme dernier arrêt
      LabelDernierArret->Caption=Format( asFrmNumeroCoordonnees[DRN],
                                         ARRAYOFCONST(( 0,
                                                        cv->ArretTram[0].x,
                                                        cv->ArretTram[0].y,
                                                        0)));
      DrnArret=&(cv->v[cv->ArretTram[0].x][cv->ArretTram[0].y]);
     }
    LabelProchainArret->Caption=Format( asFrmNumeroCoordonnees[SVT],
                                        ARRAYOFCONST(( NumArretSvt=Tram->NumArretSvt,
                                                       cv->ArretTram[NumArretSvt-1].x,
                                                       cv->ArretTram[NumArretSvt-1].y,
                                                       (int)cv->Tram->TourDepartArretSvt)));
    LabelNbPersonnes->Caption=IntToStr(Tram->NbPersonnes);
    LabelTours->Caption=IntToStr(cv->TourCrt);
    LabelParcours->Caption=IntToStr(Tram->NbCasesParcourues);
    LabelToursEntreArrets->Caption=IntToStr(NbTours=cv->TourCrt-Tram->TourArriveDrnArret);
    LabelParcoursEntreArrets->Caption=IntToStr(DejaParcouru=Tram->NbCasesParcouruesDepuisDrnArret);
    LabelDistance->Caption=IntToStr(ResteAParcourir=v->DistArretTram[NumArretSvt-1][v->NumDirPossSensVoieTram(indefinie, Tram->Dir)]);
    NbDirPoss=DrnArret->NbDirPossSensVoieTram(indefinie);
    for(i=0, DistMin=DIST_INDEFINIE; i<NbDirPoss; i++)
     DistMin=min(DistMin, DrnArret->DistArretTram[NumArretSvt-1][i]);
    LabelDistanceMin->Caption=IntToStr(DistMin);
    LabelParcoursEffectue->Caption=Format(asFrmPourcentage, ARRAYOFCONST(((100.0*DejaParcouru)/(DejaParcouru+ResteAParcourir))));
    LabelDetour->Caption=Format(asFrmPourcentage, ARRAYOFCONST(((100.0*(DejaParcouru+ResteAParcourir))/DistMin-100.0)));
    if (NbTours)
     LabelAttente->Caption=Format(asFrmPourcentage, ARRAYOFCONST(((100.0*(NbTours-DejaParcouru))/NbTours)));
    else
     LabelAttente->Caption="0,000%";
    LabelVitesse->Caption=Format(asFrmVitesse, ARRAYOFCONST((1, cv->NbVitesses)));
   }
  RendreVisibleInfos(Afficher);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmInfosTram::FormShow(TObject *Sender)
{
 frmSimulation->ActionDetailTram->Checked=true;
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosTram::FormHide(TObject *Sender)
{
 frmSimulation->ActionDetailTram->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosTram::ButtonOkClick(TObject *Sender)
{
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmInfosTram::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------

void __fastcall TfrmInfosTram::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

