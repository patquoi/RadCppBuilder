//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_rech.h"
#include "f_simul.h"
#include "simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
 #pragma link "cspin"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
TfrmRecherche *frmRecherche;
//---------------------------------------------------------------------------
__fastcall TfrmRecherche::TfrmRecherche(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmRecherche::RafraichitAffichage()
 {
  CSpinEditX->Enabled=RadioButtonCoordonnees->Checked;
  CSpinEditY->Enabled=RadioButtonCoordonnees->Checked;
  CSpinEditEtape->Enabled=RadioButtonEtape->Checked;
  CSpinEditFeu->Enabled=RadioButtonFeu->Checked;
  CSpinEditVehicule->Enabled=RadioButtonVehicule->Checked;
  CSpinEditPieton->Enabled=RadioButtonPieton->Checked;
  CSpinEditBus->Enabled=RadioButtonBus->Checked; // v3.0
  CSpinEditArretBus->Enabled=RadioButtonArretBus->Checked; // v3.0
  CSpinEditTram->Enabled=RadioButtonTram->Checked; // v3.5
  CSpinEditArretTram->Enabled=RadioButtonArretTram->Checked; // v3.5
  CSpinEditTaxi->Enabled=RadioButtonTaxi->Checked; // v3.6
  CSpinEditPlaceTaxi->Enabled=RadioButtonPlaceTaxi->Checked; // v3.6
  CSpinEditFileTaxi->Enabled=RadioButtonFileTaxi->Checked; // v3.6
  switch(   RadioButtonCoordonnees->Checked+
          2*RadioButtonEtape->Checked+
          3*RadioButtonFeu->Checked+
          4*RadioButtonVehicule->Checked+
          5*RadioButtonPieton->Checked+
          6*RadioButtonBus->Checked+ // v3.0
          7*RadioButtonArretBus->Checked+ // v3.0
          8*RadioButtonTram->Checked+ // v3.5
          9*RadioButtonArretTram->Checked+ // v3.5
         10*RadioButtonTaxi->Checked+ // v3.6
         11*RadioButtonPlaceTaxi->Checked+ // v3.6
         12*RadioButtonFileTaxi->Checked) // v3.6
   {
    case 1: CSpinEditX->SetFocus();
            CSpinEditXChange(CSpinEditX);
            CSpinEditYChange(CSpinEditY);
            StatusBar->SimpleText="";
            break;
    case 2: CSpinEditEtape->SetFocus();
            CSpinEditEtapeChange(CSpinEditEtape);
            break;
    case 3: CSpinEditFeu->SetFocus();
            CSpinEditFeuChange(CSpinEditFeu);
            break;
    case 4: CSpinEditVehicule->SetFocus();
            CSpinEditVehiculeChange(CSpinEditVehicule);
            break;
    case 5: CSpinEditPieton->SetFocus();
            CSpinEditPietonChange(CSpinEditPieton);
            break;
    case 6: CSpinEditBus->SetFocus(); // v3.0
            CSpinEditBusChange(CSpinEditBus);
            break;
    case 7: CSpinEditArretBus->SetFocus(); // v3.0
            CSpinEditArretBusChange(CSpinEditArretBus);
            break;
    case 8: CSpinEditTram->SetFocus(); // v3.5
            CSpinEditTramChange(CSpinEditTram);
            break;
    case 9: CSpinEditArretTram->SetFocus(); // v3.5
            CSpinEditArretTramChange(CSpinEditArretTram);
            break;
    case 10:CSpinEditTaxi->SetFocus(); // v3.6
            CSpinEditTaxiChange(CSpinEditTaxi);
            break;
    case 11:CSpinEditPlaceTaxi->SetFocus(); // v3.6
            CSpinEditPlaceTaxiChange(CSpinEditPlaceTaxi);
            break;
    case 12:CSpinEditFileTaxi->SetFocus(); // v3.6
            CSpinEditFileTaxiChange(CSpinEditFileTaxi);
            break;
    default: break;
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::RadioButtonClick(TObject *Sender)
{
 RafraichitAffichage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::FormShow(TObject *Sender)
{
 int i,
     x=frmSimulation->DrawGridSimul->Col,
     y=frmSimulation->DrawGridSimul->Row;
 voie *v=&(cv->v[x][y]);
#ifdef CV_LINUX
 FormResize(this);
#endif
 frmSimulation->ActionRechercher->Checked=true;
 CSpinEditEtape->MAXVALUE=cv->NbEtapes;
 CSpinEditFeu->MAXVALUE=cv->NbFeux;
 CSpinEditVehicule->MAXVALUE=cv->NbVehicules;
 CSpinEditPieton->MAXVALUE=cv->NbPietons;
 CSpinEditBus->MAXVALUE=cv->NbBus; // v3.0
 CSpinEditArretBus->MAXVALUE=cv->NbArretsBus; // v3.0
 CSpinEditTram->MAXVALUE=cv->NbTrams; // v3.5
 CSpinEditArretTram->MAXVALUE=cv->NbArretsTram; // v3.5
 CSpinEditTaxi->MAXVALUE=cv->NbTaxis; // v3.6
 CSpinEditPlaceTaxi->MAXVALUE=cv->NbPlacesTaxi; // v3.6
 CSpinEditFileTaxi->MAXVALUE=cv->NbFilesTaxi; // v3.6
 CSpinEditX->Value=x;
 CSpinEditY->Value=y;
 if (v->NumEtape) CSpinEditEtape->Value=v->NumEtape;
 for(i=0; (!v->NumFeu[i])&&(i<4); i++);
 if (i<4) CSpinEditFeu->Value=v->NumFeu[i];
 if (v->NumVehicule) CSpinEditVehicule->Value=v->NumVehicule;
 if (v->NbPietons)
  if (v->NumPieton[0])
   CSpinEditPieton->Value=v->NumPieton[0];
  else
   CSpinEditPieton->Value=v->NumPieton[1];
 if (v->NumBus) CSpinEditBus->Value=v->NumBus; // v3.0
 if (v->NumArretBus) CSpinEditArretBus->Value=v->NumArretBus; // v3.0
 if (v->NumTram) CSpinEditTram->Value=v->NumTram; // v3.5
 if (v->NumArretTram) CSpinEditArretTram->Value=v->NumArretTram; // v3.5
 if (v->NumTaxi) CSpinEditTaxi->Value=v->NumTaxi; // v3.6
 if (v->NumPlaceTaxi)
  {
   CSpinEditPlaceTaxi->Value=v->NumPlaceTaxi; // v3.6
   CSpinEditFileTaxi->Value=cv->PlaceTaxi[v->NumPlaceTaxi-1].NumFile+1; // v3.6
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditXChange(TObject *Sender)
{
 frmSimulation->DrawGridSimul->Col=CSpinEditX->Value;
 StatusBar->SimpleText="";
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditYChange(TObject *Sender)
{
 frmSimulation->DrawGridSimul->Row=CSpinEditY->Value;
 StatusBar->SimpleText="";
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditEtapeChange(TObject *Sender)
{
 if ((!cv)||
     (!cv->Etape)||
     (CSpinEditEtape->Value<1)||
     (CSpinEditEtape->Value>cv->NbEtapes))
  {
   StatusBar->SimpleText="Aucune étape définie ou n° incorrect";
   return;
  }
 etape *e=cv->Etape+CSpinEditEtape->Value-1;
 if (e&&e->Definie())
  {
   frmSimulation->DrawGridSimul->Col=e->x;
   frmSimulation->DrawGridSimul->Row=e->y;
   StatusBar->SimpleText=Format("Etape n°%d trouvée en (%d, %d)", ARRAYOFCONST(((int)CSpinEditEtape->Value, e->x, e->y)));
  }
 else
  StatusBar->SimpleText=Format("Etape n°%d non utilisée", ARRAYOFCONST(((int)CSpinEditEtape->Value)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditFeuChange(TObject *Sender)
{
 if ((!cv)||
     (!cv->Feu)||
     (CSpinEditFeu->Value<1)||
     (CSpinEditFeu->Value>cv->NbFeux))
  {
   StatusBar->SimpleText="Aucun feu défini ou n° incorrect";
   return;
  }
 feu *f=cv->Feu+CSpinEditFeu->Value-1;
 if (f&&f->Defini())
  {
   frmSimulation->DrawGridSimul->Col=f->x;
   frmSimulation->DrawGridSimul->Row=f->y;
   StatusBar->SimpleText=Format("Feu n°%d trouvé en (%d, %d)", ARRAYOFCONST(((int)CSpinEditFeu->Value, f->x, f->y)));
  }
 else
  StatusBar->SimpleText=Format("Feu n°%d non utilisé", ARRAYOFCONST(((int)CSpinEditFeu->Value)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditVehiculeChange(TObject *Sender)
{
 if ((!cv)||
     (!cv->Vehicule)||
     (CSpinEditVehicule->Value<1)||
     (CSpinEditVehicule->Value>cv->NbVehicules))
  {
   StatusBar->SimpleText="Aucun véhicule défini ou n° incorrect";
   return;
  }
 vehicule *veh=cv->Vehicule+CSpinEditVehicule->Value-1;
 if (veh&&veh->Defini())
  {
   frmSimulation->DrawGridSimul->Col=veh->x;
   frmSimulation->DrawGridSimul->Row=veh->y;
   StatusBar->SimpleText=Format("Véhicule n°%d trouvé en (%d, %d)", ARRAYOFCONST(((int)CSpinEditVehicule->Value, veh->x, veh->y)));
  }
 else
  StatusBar->SimpleText=Format("Véhicule n°%d non utilisé", ARRAYOFCONST(((int)CSpinEditVehicule->Value)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditPietonChange(TObject *Sender)
{
 if ((!cv)||
     (!cv->Pieton)||
     (CSpinEditPieton->Value<1)||
     (CSpinEditPieton->Value>cv->NbPietons))
  {
   StatusBar->SimpleText="Aucun piéton défini ou n° incorrect";
   return;
  }
 pieton *p=cv->Pieton+CSpinEditPieton->Value-1;
 if (p&&p->Defini())
  {
   frmSimulation->DrawGridSimul->Col=p->x;
   frmSimulation->DrawGridSimul->Row=p->y;
   StatusBar->SimpleText=Format("Piéton n°%d trouvé en (%d, %d)", ARRAYOFCONST(((int)CSpinEditPieton->Value, p->x, p->y)));
  }
 else
  if (p->NumBus)
   {
    frmSimulation->DrawGridSimul->Col=cv->Bus[p->NumBus-1].x;
    frmSimulation->DrawGridSimul->Row=cv->Bus[p->NumBus-1].y;
    StatusBar->SimpleText=Format( "Piéton n°%d trouvé dans le bus n°%d (%d, %d)",
                                  ARRAYOFCONST(( (int)CSpinEditPieton->Value,
                                                 (int)p->NumBus,
                                                 cv->Bus[p->NumBus-1].x,
                                                 cv->Bus[p->NumBus-1].y)));
   }
  else
   StatusBar->SimpleText=Format("Piéton n°%d non utilisé", ARRAYOFCONST(((int)CSpinEditPieton->Value)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::ButtonAnnulerClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::FormHide(TObject *Sender)
{
 frmSimulation->ActionRechercher->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecherche::ButtonAideClick(TObject *Sender)
{ // v3.0
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditArretBusChange(TObject *Sender)
{ // v3.0
 if ((!cv)||
     (!cv->ArretBus)||
     (CSpinEditArretBus->Value<1)||
     (CSpinEditArretBus->Value>cv->NbArretsBus))
  {
   StatusBar->SimpleText="Aucun arrêt de bus défini ou n° incorrect";
   return;
  }
 arret_bus *ab=cv->ArretBus+CSpinEditArretBus->Value-1;
 if (ab&&ab->Defini())
  {
   frmSimulation->DrawGridSimul->Col=ab->x;
   frmSimulation->DrawGridSimul->Row=ab->y;
   StatusBar->SimpleText=Format("Arrêt de bus n°%d trouvé en (%d, %d)", ARRAYOFCONST(((int)CSpinEditArretBus->Value, ab->x, ab->y)));
  }
 else // Normalement impossible car tous les arrêts de bus doivent être définis avant de lancer la simulation
  StatusBar->SimpleText=Format("Arrêt de bus n°%d non utilisé", ARRAYOFCONST(((int)CSpinEditArretBus->Value)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditBusChange(TObject *Sender)
{ // v3.0
 if ((!cv)||
     (!cv->Bus)||
     (CSpinEditBus->Value<1)||
     (CSpinEditBus->Value>cv->NbBus))
  {
   StatusBar->SimpleText="Aucun bus défini ou n° incorrect";
   return;
  }
 bus *b=cv->Bus+CSpinEditBus->Value-1;
 if (b&&b->Defini())
  {
   frmSimulation->DrawGridSimul->Col=b->x;
   frmSimulation->DrawGridSimul->Row=b->y;
   StatusBar->SimpleText=Format("Bus n°%d trouvé en (%d, %d)", ARRAYOFCONST(((int)CSpinEditBus->Value, b->x, b->y)));
  }
 else  // Bus encore au dépôt
  StatusBar->SimpleText=Format("Bus n°%d au dépôt", ARRAYOFCONST(((int)CSpinEditBus->Value)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditArretTramChange(TObject *Sender)
{ // v3.5
 if ((!cv)||
     (!cv->ArretTram)||
     (CSpinEditArretTram->Value<1)||
     (CSpinEditArretTram->Value>cv->NbArretsTram))
  {
   StatusBar->SimpleText="Aucun arrêt de tram défini ou n° incorrect";
   return;
  }
 arret_tram *at=cv->ArretTram+CSpinEditArretTram->Value-1;
 if (at&&at->Defini())
  {
   frmSimulation->DrawGridSimul->Col=at->x;
   frmSimulation->DrawGridSimul->Row=at->y;
   StatusBar->SimpleText=Format("Arrêt de tram n°%d trouvé en (%d, %d)", ARRAYOFCONST(((int)CSpinEditArretTram->Value, at->x, at->y)));
  }
 else // Normalement impossible car tous les arrêts de Tram doivent être définis avant de lancer la simulation
  StatusBar->SimpleText=Format("Arrêt de tram n°%d non utilisé", ARRAYOFCONST(((int)CSpinEditArretTram->Value)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditTramChange(TObject *Sender)
{ // v3.5
 if ((!cv)||
     (!cv->Tram)||
     (CSpinEditTram->Value<1)||
     (CSpinEditTram->Value>cv->NbTrams))
  {
   StatusBar->SimpleText="Aucun tram défini ou n° incorrect";
   return;
  }
 tram *t=cv->Tram+CSpinEditTram->Value-1;
 if (t&&t->Defini())
  {
   frmSimulation->DrawGridSimul->Col=t->x;
   frmSimulation->DrawGridSimul->Row=t->y;
   StatusBar->SimpleText=Format("Tram n°%d trouvé en (%d, %d)", ARRAYOFCONST(((int)CSpinEditTram->Value, t->x, t->y)));
  }
 else  // Tram non encore utilisé
  StatusBar->SimpleText=Format("Tram n°%d non utilisé", ARRAYOFCONST(((int)CSpinEditTram->Value)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditTaxiChange(TObject *Sender)
{
 if ((!cv)||
     (!cv->Taxi)||
     (CSpinEditTaxi->Value<1)||
     (CSpinEditTaxi->Value>cv->NbTaxis))
  {
   StatusBar->SimpleText="Aucun taxi défini ou n° incorrect";
   return;
  }
 taxi *t=cv->Taxi+CSpinEditTaxi->Value-1;
 frmSimulation->DrawGridSimul->Col=t->x;
 frmSimulation->DrawGridSimul->Row=t->y;
 StatusBar->SimpleText=Format("Taxi n°%d trouvé en (%d, %d)", ARRAYOFCONST(((int)CSpinEditTaxi->Value, t->x, t->y)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditPlaceTaxiChange(TObject *Sender)
{
 if ((!cv)||
     (!cv->PlaceTaxi)||
     (CSpinEditPlaceTaxi->Value<1)||
     (CSpinEditPlaceTaxi->Value>cv->NbPlacesTaxi))
  {
   StatusBar->SimpleText="Aucune place taxi définie ou n° incorrect";
   return;
  }
 place_taxi *pt=cv->PlaceTaxi+CSpinEditPlaceTaxi->Value-1;
 if (pt&&pt->Definie())
  {
   frmSimulation->DrawGridSimul->Col=pt->x;
   frmSimulation->DrawGridSimul->Row=pt->y;
   StatusBar->SimpleText=Format("Place de taxi n°%d trouvée en (%d, %d)", ARRAYOFCONST(((int)CSpinEditPlaceTaxi->Value, pt->x, pt->y)));
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditFileTaxiChange(TObject *Sender)
{
 if ((!cv)||
     (!cv->FileTaxi)||
     (CSpinEditFileTaxi->Value<1)||
     (CSpinEditFileTaxi->Value>cv->NbFilesTaxi))
  {
   StatusBar->SimpleText="Aucune file taxi définie ou n° incorrect";
   return;
  }
 file_taxi *ft=cv->FileTaxi+CSpinEditFileTaxi->Value-1;
 frmSimulation->DrawGridSimul->Col=cv->PlaceTaxi[ft->NumPlaceQueue].x;
 frmSimulation->DrawGridSimul->Row=cv->PlaceTaxi[ft->NumPlaceQueue].y;
 StatusBar->SimpleText=Format( "file taxi n°%d trouvée en (%d, %d)",
                               ARRAYOFCONST(( (int)CSpinEditFileTaxi->Value,
                                              cv->PlaceTaxi[ft->NumPlaceQueue].x,
                                              cv->PlaceTaxi[ft->NumPlaceQueue].y)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=max( LMAX(ButtonAnnuler,ButtonAide),
            XMAX(CSpinEditY))+LH_ESPACE,
     h=HMAX(RadioButtonFileTaxi,CSpinEditFileTaxi)+LH_ESPACE+StatusBar->Height;
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

