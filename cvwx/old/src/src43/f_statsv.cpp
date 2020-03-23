//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_statsv.h"
#include "simul.h"
#include "f_simul.h"
#include "winlinux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
TfrmStatsVehicules *frmStatsVehicules;
//---------------------------------------------------------------------------
const AnsiString asTitre = "Statistique des véhicules d'une étape à l'autre [Tour %d]";
//---------------------------------------------------------------------------
__fastcall TfrmStatsVehicules::TfrmStatsVehicules(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsVehicules::FormShow(TObject *Sender)
{
 int i, ne=cv->NbEtapes;
#ifdef CV_LINUX
 FormResize(this);
#endif
 frmSimulation->ActionStatsEtapes->Checked=true;
 frmStatsVehicules->Caption=Format(asTitre, ARRAYOFCONST(((int)cv->TourCrt)));
 StringGridCoordEtapes->RowCount=1+ne;
 StringGridStatsVehicules->Cells[0][0]="A\\D";
 StringGridStatsVehicules->RowCount=1+ne;
 StringGridStatsVehicules->ColCount=1+ne;
 StringGridCoordEtapes->Cells[0][0]="N°";
 StringGridCoordEtapes->Cells[1][0]="Position";
 for(i=0; i<ne; i++)
  {
   StringGridCoordEtapes->Cells[0][1+i]=Format("%3d", ARRAYOFCONST((1+i)));
   StringGridStatsVehicules->Cells[0][1+i]=Format("%3d", ARRAYOFCONST((1+i)));
   StringGridStatsVehicules->Cells[1+i][0]=Format("%3d", ARRAYOFCONST((1+i)));
   StringGridCoordEtapes->Cells[1][1+i]=Format("%d,%d",
                                               ARRAYOFCONST((cv->Etape[i].x,
                                                             cv->Etape[i].y)));
  }

}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsVehicules::FormHide(TObject *Sender)
{
 frmSimulation->ActionStatsEtapes->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsVehicules::ButtonFermerClick(TObject *Sender)
{
 Hide();
}
//---------------------------------------------------------------------------
void TfrmStatsVehicules::RafraichitInfos()
{
 int i, ed, ea,
     n=StringGridStatsVehicules->ColCount-1,
     Record, Minimum, Maximum;
 vehicule *v;
 frmStatsVehicules->Caption=Format(asTitre, ARRAYOFCONST(((int)cv->TourCrt)));
 for(i=0; i<n*n; i++)
  if ((i%n)!=(i/n))
   StringGridStatsVehicules->Cells[1+(i%n)][1+(i/n)]="   0";
 switch(TabControl->TabIndex)
  {
   case 0: for(ed=1; ed<=n; ed++)
            for(ea=1; ea<=n; ea++)
             if (ed!=ea)
              {
               Maximum=0; Minimum=32768;
               for(i=0; i<cv->NbVehicules; i++)
                {
                 v=&(cv->Vehicule[i]);
                 if ((v->NumEtapeDepart==ed)&&
                     (v->NumEtapeArrivee==ea)&&
                     (!v->Defini())&&
                     v->NbCasesParcourues) // Vehicule venant de l'étape ed et arrivé à l'étape ea
                  { // On lit les infos et on regarde le record en cours
                   if (v->NbCasesParcourues>Maximum) Maximum=v->NbCasesParcourues;
                   if (v->NbCasesParcourues<Minimum) Minimum=v->NbCasesParcourues;
                    Record=StrToInt(AnsiString(StringGridStatsVehicules->Cells[ed][ea]));
                   if (Maximum-Minimum>Record) // Si record battu on écrit
                    StringGridStatsVehicules->Cells[ed][ea]=Format("%4d", ARRAYOFCONST((Maximum-Minimum)));
                  }
                }
              }
           break;
   case 1: for(ed=1; ed<=n; ed++)
            for(ea=1; ea<=n; ea++)
             if (ed!=ea)
              {
               Maximum=0; Minimum=32768;
               for(i=0; i<cv->NbVehicules; i++)
                {
                 v=&(cv->Vehicule[i]);
                 if ((v->NumEtapeDepart==ed)&&
                     (v->NumEtapeArrivee==ea)&&
                     (!v->Defini())&&
                     v->TourDrnDepl) // Vehicule venant de l'étape ed et arrivé à l'étape ea
                  { // On lit les infos et on regarde le record en cours
                   if (v->TourDrnDepl>Maximum) Maximum=v->TourDrnDepl;
                   if (v->TourDrnDepl<Minimum) Minimum=v->TourDrnDepl;
                    Record=StrToInt(AnsiString(StringGridStatsVehicules->Cells[ed][ea]));
                   if (Maximum-Minimum>Record) // Si record battu on écrit
                    StringGridStatsVehicules->Cells[ed][ea]=Format("%4d", ARRAYOFCONST((Maximum-Minimum)));
                  }
                }
              }
           break;
  }
 StringGridStatsVehicules->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsVehicules::TabControlChange(TObject *Sender)
{
 RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsVehicules::ButtonAideClick(TObject *Sender)
{ // v3.0
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsVehicules::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=XMAX(TabControl)+LH_ESPACE,
     h=HMAX(ButtonAide,TabControl)+LH_ESPACE;
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

