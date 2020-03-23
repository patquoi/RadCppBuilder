//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_statsc.h"
#include "simul.h"
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
#define SURROUTE  0
#define SURVOIE   1
//---------------------------------------------------------------------------
TfrmStatsComposition *frmStatsComposition;
//---------------------------------------------------------------------------
const AnsiString asFrmPC="%6.2f";
//---------------------------------------------------------------------------
void Composition()
 {
  if (frmStatsComposition=new TfrmStatsComposition(Application))
   try
    {
     frmStatsComposition->ShowModal();
    }
   __finally
    {
     frmStatsComposition->Release();
     frmStatsComposition=NULL;
    }
 }
//---------------------------------------------------------------------------
__fastcall TfrmStatsComposition::TfrmStatsComposition(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsComposition::FormShow(TObject *Sender)
{
 voie *vv;
 int i, x, y,
     Total=0,
     Routes=0,
     VoiesTram=0, // v3.5
     Priorites[2]={0,0},
     Etapes=0,
     CasesArretsBus=0, // v3.0
     ArretsBus=0, // v3.0
     CasesArretsTram=0, // v3.5
     ArretsTram=0, // v3.5
     PlacesTaxi=0, // v3.6
     Feux[2]={0,0}, //v3.5
     Clp[2]={0,0}, //v3.5
     Stops[2]={0,0}, //v3.5
     Dir=0,
     Nord=0,
     Est=0,
     Sud=0,
     Ouest=0;
#ifdef CV_LINUX
 FormResize(this);
#endif
 for(i=0; i<cv->NbArretsBus; i++) // v3.0
  ArretsBus+=cv->ArretBus[i].Defini();
 for(i=0; i<cv->NbArretsTram; i++) // v3.5
  ArretsTram+=cv->ArretTram[i].Defini();
 for(i=0; i<cv->NbPlacesTaxi; i++) // v3.6
  PlacesTaxi+=cv->PlaceTaxi[i].Definie();
 for(x=0; x<cv->NbX; x++)
  for(y=0; y<cv->NbY; y++)
   {
    vv=&(cv->v[x][y]);
    Total++;
    Etapes+=(vv->NumEtape>0);
    CasesArretsBus+=(vv->NumArretBus>0); // v3.0
    if (vv->DirPoss) // Route
     {
      Routes++;
      Dir+=NbDir[vv->DirPoss];
      Nord+=((vv->DirPoss&N)>0);
      Est+=((vv->DirPoss&E)>0);
      Sud+=((vv->DirPoss&S)>0);
      Ouest+=((vv->DirPoss&O)>0);
      for(i=0; i<4; i++)
       if (vv->DirPoss&PossDir[(direction)(i+1)]) // v3.5
        switch(vv->Priorite[i])
         {
          case feux:             Priorites[SURROUTE]++; Feux[SURROUTE]++; break;
          case cedez_le_passage: Priorites[SURROUTE]++; Clp[SURROUTE]++; break;
          case stop:             Priorites[SURROUTE]++; Stops[SURROUTE]++; break;
          default: break;
         }
     }
    if (vv->SensVoieTram) // v3.5
     {
      VoiesTram++;
      CasesArretsTram+=(vv->NumArretTram>0);
      for(i=0; i<4; i++)
       if (vv->EstDirPossSensVoieTram(indefinie, (direction)(i+1)))
        switch(vv->Priorite[i])
         {
          case feux:             Priorites[SURVOIE]++; Feux[SURVOIE]++; break;
          case cedez_le_passage: Priorites[SURVOIE]++; Clp[SURVOIE]++; break;
          case stop:             Priorites[SURVOIE]++; Stops[SURVOIE]++; break;
          default: break;
         }
     }
   }
 LabelTotal->Caption=IntToStr(Total);
 LabelRoutes->Caption=IntToStr(Routes);
 LabelRoutesPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Routes/Total)));
 if (Routes)
  {
   LabelPrioritesR->Caption=IntToStr(Priorites[SURROUTE]);
   LabelPrioritesRPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Priorites[SURROUTE]/Routes)));
   if (Priorites[SURROUTE])
    {
     LabelFeuxR->Caption=IntToStr(Feux[SURROUTE]);
     LabelFeuxRPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Feux[SURROUTE]/Priorites[SURROUTE])));
     LabelFeuxRMax->Caption=IntToStr(cv->NbFeux);
     LabelFeuxRReste->Caption=IntToStr(cv->NbFeux-Feux[SURVOIE]-Feux[SURROUTE]);
     LabelClpR->Caption=IntToStr(Clp[SURROUTE]);
     LabelClpRPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Clp[SURROUTE]/Priorites[SURROUTE])));
     LabelStopsR->Caption=IntToStr(Stops[SURROUTE]);  // v3.8 : oubli de [SURROUTE] !
     LabelStopsRPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Stops[SURROUTE]/Priorites[SURROUTE])));
    }
   LabelEtapes->Caption=IntToStr(Etapes);
   LabelEtapesPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Etapes/Routes)));
   LabelEtapesMax->Caption=IntToStr(cv->NbEtapes);
   LabelEtapesReste->Caption=IntToStr(cv->NbEtapes-Etapes);
   LabelDir->Caption=IntToStr(Dir);
   LabelDirPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Dir/Routes)));
   if (Dir)
    {
     LabelNord->Caption=IntToStr(Nord);
     LabelNordPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Nord/Dir)));
     LabelEst->Caption=IntToStr(Est);
     LabelEstPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Est/Dir)));
     LabelSud->Caption=IntToStr(Sud);
     LabelSudPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Sud/Dir)));
     LabelOuest->Caption=IntToStr(Ouest);
     LabelOuestPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Ouest/Dir)));
    }
  }
 if (ArretsBus) // v3.0
  {
   LabelArretsBus->Caption=IntToStr(ArretsBus);
   if (Routes) LabelArretsBusPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*CasesArretsBus/Routes)));
   LabelArretsBusMax->Caption=IntToStr(cv->NbArretsBus);
   LabelArretsBusReste->Caption=IntToStr(cv->NbArretsBus-ArretsBus);
  }
 // v3.5
 LabelVoiesTram->Caption=IntToStr(VoiesTram);
 LabelVoiesTramPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*VoiesTram/Total)));
 if (ArretsTram)
  {
   LabelArretsTram->Caption=IntToStr(ArretsTram);
   if (VoiesTram) LabelArretsTramPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*CasesArretsTram/VoiesTram)));
   LabelArretsTramMax->Caption=IntToStr(cv->NbArretsTram);
   LabelArretsTramReste->Caption=IntToStr(cv->NbArretsTram-ArretsTram);
  }
 LabelPlacesTaxi->Caption=IntToStr(PlacesTaxi);
 if (Routes) LabelPlacesTaxiPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*PlacesTaxi/Routes)));
 LabelPlacesTaxiMax->Caption=IntToStr(cv->NbPlacesTaxi);
 LabelPlacesTaxiReste->Caption=IntToStr(cv->NbPlacesTaxi-PlacesTaxi);
 LabelPrioritesV->Caption=IntToStr(Priorites[SURVOIE]);
 if (VoiesTram) LabelPrioritesVPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Priorites[SURVOIE]/VoiesTram)));
 if (Priorites[SURVOIE])
  {
   LabelFeuxV->Caption=IntToStr(Feux[SURVOIE]);
   LabelFeuxVPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Feux[SURVOIE]/Priorites[SURVOIE])));
   LabelFeuxVMax->Caption=IntToStr(cv->NbFeux);
   LabelFeuxVReste->Caption=IntToStr(cv->NbFeux-Feux[SURVOIE]-Feux[SURROUTE]);
   LabelClpV->Caption=IntToStr(Clp[SURVOIE]);
   LabelClpVPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Clp[SURVOIE]/Priorites[SURVOIE])));
   LabelStopsV->Caption=IntToStr(Stops[SURVOIE]); // v3.8 : oubli de [SURVOIE] !
   LabelStopsVPC->Caption=Format(asFrmPC, ARRAYOFCONST((100.0*Stops[SURVOIE]/Priorites[SURVOIE])));
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsComposition::ButtonAideClick(TObject *Sender)
{ // v3.0
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmStatsComposition::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=max( max( LMAX(Label42,Label43),
                 LMAX(Bevel1,Bevel2)),
            max( LMAX(Label11,Label37),
                 XMAX(Label31)))+LH_ESPACE,
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

