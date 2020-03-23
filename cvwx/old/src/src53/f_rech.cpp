//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_rech.h"
#include "f_simul.h"
#include "simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
#pragma link "cspin"
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
  CSpinEditParking->Enabled=RadioButtonParking->Checked;
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
  CSpinEditPlacePark->Enabled=RadioButtonPlacePark->Checked; // v5.0
  CSpinEditFilePark->Enabled=RadioButtonFilePark->Checked; // v5.0
  CSpinEditVehlib->Enabled=RadioButtonVehlib->Checked; // v5.3
  CSpinEditPlaceVehlib->Enabled=RadioButtonPlaceVehlib->Checked; // v5.3

  switch(   RadioButtonCoordonnees->Checked+
          2*RadioButtonParking->Checked+
          3*RadioButtonFeu->Checked+
          4*RadioButtonVehicule->Checked+
          5*RadioButtonPieton->Checked+
          6*RadioButtonBus->Checked+ // v3.0
          7*RadioButtonArretBus->Checked+ // v3.0
          8*RadioButtonTram->Checked+ // v3.5
          9*RadioButtonArretTram->Checked+ // v3.5
         10*RadioButtonTaxi->Checked+ // v3.6
         11*RadioButtonPlaceTaxi->Checked+ // v3.6
         12*RadioButtonFileTaxi->Checked+ // v3.6
         13*RadioButtonPlacePark->Checked+ // v5.0
         14*RadioButtonFilePark->Checked+ // v5.0
         15*RadioButtonVehlib->Checked+ // v5.3
         16*RadioButtonPlaceVehlib->Checked) // v5.3
   {
    case 1: CSpinEditX->SetFocus();
            CSpinEditXChange(CSpinEditX);
            CSpinEditYChange(CSpinEditY);
            StatusBar->SimpleText="";
            break;
    case 2: CSpinEditParking->SetFocus();
            CSpinEditParkingChange(CSpinEditParking);
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
    case 13:CSpinEditPlacePark->SetFocus(); // v5.0
            CSpinEditPlaceParkChange(CSpinEditPlacePark);
            break;
    case 14:CSpinEditFilePark->SetFocus(); // v5.0
            CSpinEditFileParkChange(CSpinEditFilePark);
            break;
    case 15:CSpinEditVehlib->SetFocus(); // v5.3
            CSpinEditVehlibChange(CSpinEditVehlib);
            break;
    case 16:CSpinEditPlaceVehlib->SetFocus(); // v5.3
            CSpinEditPlaceVehlibChange(CSpinEditPlaceVehlib);
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
 frmSimulation->ActionRechercher->Checked=true;
 CSpinEditParking->MAXVALUE=cv->NbParkings;
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
 CSpinEditPlacePark->MAXVALUE=cv->NbPlacesPark; // v5.0
 CSpinEditFilePark->MAXVALUE=cv->NbFilesPark; // v5.0
 CSpinEditVehlib->MAXVALUE=cv->NbVehlibs; // v5.3
 CSpinEditPlaceVehlib->MAXVALUE=cv->NbPlacesVehlib; // v5.3
 CSpinEditX->Value=x;
 CSpinEditY->Value=y;
 if (v->NumParking) CSpinEditParking->Value=v->NumParking;
 for(i=0; (!v->NumFeu[i])&&(i<NBDIR); i++);
 if (i<NBDIR) CSpinEditFeu->Value=v->NumFeu[i];
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
 if (v->NumPlacePark) // v5.0
  {
   CSpinEditPlacePark->Value=v->NumPlacePark;
   CSpinEditFilePark->Value=cv->PlacePark[v->NumPlacePark-1].NumFile+1;
  }
 if (v->NumVehlib) CSpinEditVehlib->Value=v->NumVehlib; // v5.3
 if (v->NumPlaceVehlib) // v5.3
  CSpinEditPlaceVehlib->Value=v->NumPlaceVehlib;
 frmSimulation->TimerClignotementLocalisation->Enabled=true; // v4.4.1 : on fait à présent clignoter le curseur
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
void __fastcall TfrmRecherche::CSpinEditParkingChange(TObject *Sender)
{
 if ((!cv)||
     (!cv->Parking)||
     (CSpinEditParking->Value<1)||
     (CSpinEditParking->Value>cv->NbParkings))
  {
   StatusBar->SimpleText="Aucune parking défini ou n° incorrect";
   return;
  }
 parking *p=cv->Parking+CSpinEditParking->Value-1;
 if (p&&p->Defini())
  {
   frmSimulation->DrawGridSimul->Col=p->x;
   frmSimulation->DrawGridSimul->Row=p->y;
   StatusBar->SimpleText=Format("Parking n°%d trouvé en (%d, %d)", ARRAYOFCONST(((int)CSpinEditParking->Value, p->x, p->y)));
  }
 else
  StatusBar->SimpleText=Format("Parking n°%d non utilisé", ARRAYOFCONST(((int)CSpinEditParking->Value)));
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
 frmSimulation->TimerClignotementLocalisation->Enabled=false; // v4.4.1 : on arrête le clignotement
 cv->v[frmSimulation->DrawGridSimul->Col][frmSimulation->DrawGridSimul->Row].RedessineCase(false); // v4.4.1 : on réaffiche le curseur
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
   StatusBar->SimpleText="Aucune place de taxi définie ou n° incorrect";
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
   StatusBar->SimpleText="Aucune file de taxis définie ou n° incorrect";
   return;
  }
 file_taxi *ft=cv->FileTaxi+CSpinEditFileTaxi->Value-1;
 frmSimulation->DrawGridSimul->Col=cv->PlaceTaxi[ft->NumPlaceQueue].x;
 frmSimulation->DrawGridSimul->Row=cv->PlaceTaxi[ft->NumPlaceQueue].y;
 StatusBar->SimpleText=Format( "file de taxis n°%d trouvée en (%d, %d)",
                               ARRAYOFCONST(( (int)CSpinEditFileTaxi->Value,
                                              cv->PlaceTaxi[ft->NumPlaceQueue].x,
                                              cv->PlaceTaxi[ft->NumPlaceQueue].y)));
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecherche::CSpinEditPlaceParkChange(TObject *Sender)
{
 if ((!cv)||
     (!cv->PlacePark)||
     (CSpinEditPlacePark->Value<1)||
     (CSpinEditPlacePark->Value>cv->NbPlacesPark))
  {
   StatusBar->SimpleText="Aucune place de parking définie ou n° incorrect";
   return;
  }
 place_park *pp=cv->PlacePark+CSpinEditPlacePark->Value-1;
 if (pp&&pp->Definie())
  {
   frmSimulation->DrawGridSimul->Col=pp->x;
   frmSimulation->DrawGridSimul->Row=pp->y;
   StatusBar->SimpleText=Format("Place de parking n°%d trouvée en (%d, %d)", ARRAYOFCONST(((int)CSpinEditPlacePark->Value, pp->x, pp->y)));
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecherche::CSpinEditFileParkChange(TObject *Sender)
{
 if ((!cv)||
     (!cv->FilePark)||
     (CSpinEditFilePark->Value<1)||
     (CSpinEditFilePark->Value>cv->NbFilesPark))
  {
   StatusBar->SimpleText="Aucune file de parkings définie ou n° incorrect";
   return;
  }
 file_park *fp=cv->FilePark+CSpinEditFilePark->Value-1;
 frmSimulation->DrawGridSimul->Col=cv->PlacePark[fp->NumPlaceQueue].x;
 frmSimulation->DrawGridSimul->Row=cv->PlacePark[fp->NumPlaceQueue].y;
 StatusBar->SimpleText=Format( "file de parkings n°%d trouvée en (%d, %d)",
                               ARRAYOFCONST(( (int)CSpinEditFilePark->Value,
                                              cv->PlacePark[fp->NumPlaceQueue].x,
                                              cv->PlacePark[fp->NumPlaceQueue].y)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditVehlibChange(TObject *Sender)
{ // v5.3
 if ((!cv)||
     (!cv->Vehlib)||
     (CSpinEditVehlib->Value<1)||
     (CSpinEditVehlib->Value>cv->NbVehlibs))
  {
   StatusBar->SimpleText="Aucun vehlib défini ou n° incorrect";
   return;
  }
 vehlib *vl=cv->Vehlib+CSpinEditVehlib->Value-1;
 frmSimulation->DrawGridSimul->Col=vl->x;
 frmSimulation->DrawGridSimul->Row=vl->y;
 StatusBar->SimpleText=Format("Vehlib n°%d trouvé en (%d, %d)", ARRAYOFCONST(((int)CSpinEditVehlib->Value, vl->x, vl->y)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::CSpinEditPlaceVehlibChange(TObject *Sender)
{ // v5.3
 if ((!cv)||
     (!cv->PlaceVehlib)||
     (CSpinEditPlaceVehlib->Value<1)||
     (CSpinEditPlaceVehlib->Value>cv->NbPlacesVehlib))
  {
   StatusBar->SimpleText="Aucune place de vehlib définie ou n° incorrect";
   return;
  }
 place_vehlib *pv=cv->PlaceVehlib+CSpinEditPlaceVehlib->Value-1;
 if (pv&&pv->Definie())
  {
   frmSimulation->DrawGridSimul->Col=pv->x;
   frmSimulation->DrawGridSimul->Row=pv->y;
   StatusBar->SimpleText=Format("Place de vehlib n°%d trouvée en (%d, %d)", ARRAYOFCONST(((int)CSpinEditPlaceVehlib->Value, pv->x, pv->y)));
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecherche::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

