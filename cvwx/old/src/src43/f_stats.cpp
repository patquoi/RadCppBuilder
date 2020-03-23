//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_stats.h"
#include "simul.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
TfrmStatistiques *frmStatistiques;
//---------------------------------------------------------------------------
__fastcall TfrmStatistiques::TfrmStatistiques(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TfrmStatistiques::PaintBoxStatsPaint(TObject *Sender)
{
 bool ParNbVehicules=(cv->TypeStats==par_nombre);
 int i, j, x, y,
     NbTours=cv->NbToursStats,
     DrnTour=cv->TourCrt,
     PrmTour=(DrnTour<NbTours)?0:(DrnTour-NbTours+1),
     NbVehicules=cv->NbVehicules,
     NbMarques=(ParNbVehicules)?(NbVehicules/10):10,
     dt=1+9*(NbTours>=100L),
     xMax=PaintBoxStats->Width,
     yMax=PaintBoxStats->Height,
     NbRestants;

 // 1. Affichage du quadrillage
 if (cv->QuadrillageStats)
  for(i=0; i<NbTours/dt; i++)
   for(j=0; j<NbMarques; j++)
    {
     x=dt*xMax*i/NbTours; y=(ParNbVehicules)?(10*yMax*j/NbVehicules):(10*yMax*j/100);
     PaintBoxStats->Canvas->Pen->Color=((i%10)&&(j%10))?clGray:clWhite;
     PaintBoxStats->Canvas->Rectangle(x-1, yMax-y-1, x+1, yMax-y+1);
    }

 if (!cv->Stats) return;

 // 2. Affichage des véhicules
 if (xMax&&yMax)
  {
   PaintBoxStats->Canvas->Pen->Color=clRed; // Arrivés = Rouges
   PaintBoxStats->Canvas->MoveTo(0, yMax-yMax*cv->Stats[PrmTour%NbTours].NbVehiculesArrives/NbVehicules);
   for(i=0; i<DrnTour-PrmTour+1; i++)
    PaintBoxStats->Canvas->LineTo(xMax*i/NbTours, yMax-yMax*cv->Stats[(PrmTour+i)%NbTours].NbVehiculesArrives/NbVehicules);

   PaintBoxStats->Canvas->Pen->Color=clYellow; // Sortis = Jaunes
   PaintBoxStats->Canvas->MoveTo(0, yMax-yMax*cv->Stats[PrmTour%NbTours].NbVehiculesSortis/NbVehicules);
   for(i=0; i<DrnTour-PrmTour+1; i++)
    PaintBoxStats->Canvas->LineTo(xMax*i/NbTours, yMax-yMax*cv->Stats[(PrmTour+i)%NbTours].NbVehiculesSortis/NbVehicules);

   PaintBoxStats->Canvas->Pen->Color=clGreen; // Deplaces = Verts
   NbRestants=ParNbVehicules?NbVehicules:(cv->Stats[PrmTour%NbTours].NbVehiculesSortis-cv->Stats[PrmTour%NbTours].NbVehiculesArrives);
   if (!NbRestants) NbRestants=100;
   PaintBoxStats->Canvas->MoveTo(0, yMax-yMax*cv->Stats[PrmTour%NbTours].NbVehiculesDeplaces/NbRestants);
   for(i=0; i<DrnTour-PrmTour+1; i++)
    {
     NbRestants=ParNbVehicules?NbVehicules:(cv->Stats[(PrmTour+i)%NbTours].NbVehiculesSortis-cv->Stats[(PrmTour+i)%NbTours].NbVehiculesArrives);
     if (!NbRestants) NbRestants=100;
     PaintBoxStats->Canvas->LineTo(xMax*i/NbTours, yMax-yMax*cv->Stats[(PrmTour+i)%NbTours].NbVehiculesDeplaces/NbRestants);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatistiques::FormShow(TObject *Sender)
{
 frmSimulation->ActionEvolution->Checked=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatistiques::FormHide(TObject *Sender)
{
 frmSimulation->ActionEvolution->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatistiques::FormCreate(TObject *Sender)
{
 PaintBoxStats->Canvas->Pen->Style=psSolid;
 PaintBoxStats->Canvas->Pen->Mode=pmCopy;
 PaintBoxStats->Canvas->Pen->Width=1;
}
//---------------------------------------------------------------------------

