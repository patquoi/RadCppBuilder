//---------------------------------------------------------------------------
// Voir les notes A VOIR
//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include <stdlib.h>
#include <time.h>
//---------------------------------------------------------------------------
#include "simul.h"
#include "f_simul.h"
#include "f_stats.h"
#include "f_statsv.h"
#include "f_infveh.h"
#include "f_infptn.h"
#include "f_infbus.h"
#include "f_inftram.h"
#include "f_inftaxi.h"
#include "f_rech.h"
#include "winlinux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define PEUT_ETRE_INDEFINI true
#define DOIT_ETRE_DEFINI   false
//---------------------------------------------------------------------------
// Pour DistEtape
#define NORMAL      0
#define PRIORITAIRE 1
//---------------------------------------------------------------------------
#define AUCUN_FEU ((x==-1)&&(y==-1)&&(Dir==indefinie))
#define REMET_A_ZERO Definit(-1, -1, 0)
//---------------------------------------------------------------------------
// pour dxg/dyg
#define ZOOMX1 0
#define ZOOMX2 1
//---------------------------------------------------------------------------
// v3.5 : remplacement des [5] par [NBDIR+1] et des [4] par [NBDIR]
const dirposs PossDir[NBDIR+1]={aucune, N, E, S, O},
              InvPossDir[NBDIR+1]={aucune, S, O, N, E},
              // 1=90�droite, 2=180�, 3=90�gauche
              RotPossDir[NBDIR][16]={{aucune, N, E, NE, S, NS, SE, NES, O, NO, EO, NEO, SO, NSO, ESO, NESO},
                                     {aucune, E, S, SE, O, EO, SO, ESO, N, NE, NS, NES, NO, NEO, NSO, NESO},
                                     {aucune, S, O, SO, N, NS, NO, NSO, E, SE, EO, ESO, NE, NES, NEO, NESO},
                                     {aucune, O, N, NO, E, EO, NE, NEO, S, SO, NS, NSO, SE, ESO, NES, NESO}};
//---------------------------------------------------------------------------
const int dxr[NBDIR+1]={0, 0, 1, 0, -1},
          dyr[NBDIR+1]={0, -1, 0, 1, 0},
          NbDir[16]={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4},
          // NumDirdp[direction][dirposs] = Ordre de direction dans dirposs
          // 0 <= NumDirdp[direction][dirposs] < NbDir[direction][dirposs]
          NumDirdp[NBDIR+1][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // indefinie
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // nord
                                 {0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1}, // est
                                 {0,0,0,0,0,1,1,2,0,0,0,0,0,1,1,2}, // sud
                                 {0,0,0,0,0,0,0,0,0,1,1,2,1,2,2,3}};// ouest
//---------------------------------------------------------------------------
// SensPsgPt[dirposs] = indefini|horizontal|vertical. v2.0
const sens SensPsgPt[16]={indefini,   horizontal, vertical, indefini,
                          horizontal, horizontal, indefini, indefini,
                          vertical, indefini, vertical, indefini,
                          indefini, indefini, indefini, indefini};
//---------------------------------------------------------------------------
// (Dirdp[x][y] = (x+1)�me direction pour DirPoss=y
const direction Dirdp[NBDIR][16]={{indefinie,  nord,   est,  nord,   sud,  nord,   est,  nord,
                                   ouest,  nord,   est,  nord,   sud,  nord,   est,  nord},
                                  {indefinie,indefinie,indefinie,   est,indefinie,   sud,   sud,   est,
                                   indefinie, ouest, ouest,   est, ouest,   sud,   sud,   est},
                                  {indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,   sud,
                                   indefinie,indefinie,indefinie, ouest,indefinie, ouest, ouest,   sud},
                                  {indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,
                                   indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,indefinie, ouest}},
                InvDir[NBDIR+1]={indefinie, sud, ouest, nord, est},
                AGaucheDe[NBDIR+1]={indefinie, ouest, nord, est, sud},
                ADroiteDe[NBDIR+1]={indefinie, est, sud, ouest, nord};
//---------------------------------------------------------------------------
// v3.5                                  DirDest:        indefinie,   nord,       est,       sud,       ouest         // DirOrig:
const sens_voie_tram SensVoieTramDir[NBDIR+1][NBDIR+1]={{aucune_voie, nord_sud,   est_ouest, nord_sud,  est_ouest  }, // indefinie
                                                        {aucune_voie, nord_sud,   nord_est,  nord_sud,  nord_ouest }, // nord
                                                        {aucune_voie, nord_est,   est_ouest, sud_est,   est_ouest  }, // est
                                                        {aucune_voie, nord_sud,   sud_est,   nord_sud,  sud_ouest  }, // sud
                                                        {aucune_voie, nord_ouest, est_ouest, sud_ouest, est_ouest  }};// ouest
//---------------------------------------------------------------------------
const sens_voie_tram_base SensVoieTramBase[NBSENSVOIETRAM]={ aucune_voie_base, ne, ns, aucune_voie_base, no,
                                                             aucune_voie_base, aucune_voie_base, aucune_voie_base, se,
                                                             aucune_voie_base, aucune_voie_base, aucune_voie_base, aucune_voie_base,
                                                             aucune_voie_base, aucune_voie_base, aucune_voie_base, eo,
                                                             aucune_voie_base, aucune_voie_base, aucune_voie_base, aucune_voie_base,
                                                             aucune_voie_base, aucune_voie_base, aucune_voie_base, aucune_voie_base,
                                                             aucune_voie_base, aucune_voie_base, aucune_voie_base, aucune_voie_base,
                                                             aucune_voie_base, aucune_voie_base, aucune_voie_base, so};
//---------------------------------------------------------------------------
// v3.5                                                           DirDest:  indef, nord,  est,  sud,ouest  // DirOrig
const bool DirPossSensVoieTramBase[NBSENSVOIETRAMBASE][NBDIR+1][NBDIR+1]={{{false,false,false,false,false},// indef.// aucune_voie_base
                                                                           {false,false,false,false,false},// nord
                                                                           {false,false,false,false,false},// est
                                                                           {false,false,false,false,false},// sud
                                                                           {false,false,false,false,false}},//ouest
                                                                          {{false, true, true,false,false},// indef.// ne
                                                                           {false,false, true,false,false},// nord
                                                                           {false, true,false,false,false},// est
                                                                           {false,false,false,false,false},// sud
                                                                           {false,false,false,false,false}},//ouest
                                                                          {{false, true,false, true,false},// indef.// ns
                                                                           {false,false,false, true,false},// nord
                                                                           {false,false,false,false,false},// est
                                                                           {false, true,false,false,false},// sud
                                                                           {false,false,false,false,false}},//ouest
                                                                          {{false, true,false,false, true},// indef.// no
                                                                           {false,false,false,false, true},// nord
                                                                           {false,false,false,false,false},// est
                                                                           {false,false,false,false,false},// sud
                                                                           {false, true,false,false,false}},//ouest
                                                                          {{false,false, true, true,false},// indef.// se
                                                                           {false,false,false,false,false},// nord
                                                                           {false,false,false, true,false},// est
                                                                           {false,false, true,false,false},// sud
                                                                           {false,false,false,false,false}},//ouest
                                                                          {{false,false, true,false, true},// indef.// eo
                                                                           {false,false,false,false,false},// nord
                                                                           {false,false,false,false, true},// est
                                                                           {false,false,false,false,false},// sud
                                                                           {false,false, true,false,false}},//ouest
                                                                          {{false,false,false, true, true},// indef.// so
                                                                           {false,false,false,false,false},// nord
                                                                           {false,false,false,false,false},// est
                                                                           {false,false,false,false, true},// sud
                                                                           {false,false,false, true,false}}};//ouest
//---------------------------------------------------------------------------
const coin CoinDir[NBDIR+1]={aucun_coin, haut_droite, bas_droite, bas_gauche, haut_gauche}; // v3.8
//---------------------------------------------------------------------------
const AnsiString asDir[NBDIR+1]={"", "Nord", "Est", "Sud", "Ouest"},
                 asDirPoss[16]={"", "Nord", "Est", "Nord+Est",
                                "Sud", "Nord+Sud", "Est+Sud", "Nord+Est+Sud",
                                "Ouest", "Nord+Ouest", "Est+Ouest", "Nord+Est+Ouest",
                                "Sud+Ouest", "Nord+Sud+Ouest", "Est+Sud+Ouest", "Nord+Est+Sud+Ouest"};
//---------------------------------------------------------------------------
bool ParamsInchanges=false,
     VerifierApresOuverture=false,
     VerifierAvantSimulation=false;
//---------------------------------------------------------------------------
int dx[NBDIR+1]={0, 0, 1, 0, NBXDEF-1}, // v4.0 (const int->int, DEF)
    dy[NBDIR+1]={0, NBYDEF-1, 0, 1, 0}, // v4.0 (const int->int, DEF)
    VersionFichier=0, // v3.0
    SvgNbFeux=0,
    SvgNbEtapes=0,
    SvgNbVehicules=0,
    SvgNbPietons=0, // v2.0
    SvgNbArretsBus=0, // v3.0
    SvgNbArretsTram=0, // v3.5
    SvgNbPlacesTaxi=0; // v3.6
//---------------------------------------------------------------------------
centre_ville *cv=NULL;
//---------------------------------------------------------------------------
void AppelleAuChaos()
 {
  time_t t;
  srand((unsigned)time(&t));
 }
//-----------------------------------------------------------------------------
// Routines priv�es
//-----------------------------------------------------------------------------
void VerifiePosition(AnsiString asMsgErr, AnsiString asSource, int x, int y);
void VerifieDirection(AnsiString asMsgErr, AnsiString asSource, direction d, bool PeutEtreIndefinie);
void VerifiePriorite(AnsiString asMsgErr, AnsiString asSource, priorite p);
void VerifieDirPoss(AnsiString asMsgErr, AnsiString asSource, dirposs dp);
void VerifieEtat(AnsiString asMsgErr, AnsiString asSource, etat_feu e);
void VerifieDmdVert(AnsiString asMsgErr, AnsiString asSource, dmd_vert dv);
void VerifiePsgRouge(AnsiString asMsgErr, AnsiString asSource, psg_rouge pr);
//-----------------------------------------------------------------------------
void VerifiePosition(AnsiString asMsgErr, AnsiString asSource, int x, int y, bool PeutEtreIndefinie)
 {
  if (((x<-1)&&(PeutEtreIndefinie))||
      ((x<0)&&(!PeutEtreIndefinie))||
      (x>=cv->NbX))
   asMsgErr+=asSource+Format(": abscisse incorrecte (%d)\n", ARRAYOFCONST((x)));
  if (((y<-1)&&(PeutEtreIndefinie))||
      ((y<0)&&(!PeutEtreIndefinie))||
      (y>=cv->NbY))
   asMsgErr+=asSource+Format(": ordonn�e incorrecte (%d)\n", ARRAYOFCONST((y)));
 }
//-----------------------------------------------------------------------------
void VerifieDirection(AnsiString asMsgErr, AnsiString asSource, direction d, bool PeutEtreIndefinie)
 {
  if (((d<indefinie)&&(PeutEtreIndefinie))||
      ((d<=indefinie)&&(!PeutEtreIndefinie))||
      (d>ouest))
   asMsgErr+=asSource+Format(": direction incorrecte (%d)\n", ARRAYOFCONST((d)));
 }
//-----------------------------------------------------------------------------
void VerifiePriorite(AnsiString asMsgErr, AnsiString asSource, priorite p)
 {
  if ((p<a_droite)||(p>feux))
   asMsgErr+=asSource+Format(": priorit� incorrecte (%d)\n", ARRAYOFCONST((p)));
 }
//-----------------------------------------------------------------------------
void VerifieDirPoss(AnsiString asMsgErr, AnsiString asSource, dirposs dp)
 {
  if ((dp<aucune)||(dp>NESO))
   asMsgErr+=asSource+Format(": directions possibles incorrectes (%d)\n", ARRAYOFCONST((dp)));
 }
//-----------------------------------------------------------------------------
void VerifieEtat(AnsiString asMsgErr, AnsiString asSource, etat_feu e)
 {
  if ((e<inactif)||(e>rouge))
   asMsgErr+=asSource+Format(": �tat incorrect (%d)\n", ARRAYOFCONST((e)));
 }
//-----------------------------------------------------------------------------
void VerifieDmdVert(AnsiString asMsgErr, AnsiString asSource, dmd_vert dv)
 {
  if ((dv<arrivee_vehicule)||(dv>immediate))
   asMsgErr+=asSource+Format(": type de demande du vert incorrect (%d)\n", ARRAYOFCONST((dv)));
 }
//-----------------------------------------------------------------------------
void VerifiePsgRouge(AnsiString asMsgErr, AnsiString asSource, psg_rouge pr)
 {
  if ((pr<prm_dmd)||(pr>immediat))
   asMsgErr+=asSource+Format(": type de passage au rouge incorrect (%d)\n", ARRAYOFCONST((pr)));
 }
//-----------------------------------------------------------------------------
// M�thodes des classes
//-----------------------------------------------------------------------------
void pieton::Verifie(AnsiString &asMsgErr)
 {
  AnsiString asSource=Format("Pi�ton n�%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, DOIT_ETRE_DEFINI);
  VerifieDirection(asMsgErr, asSource, (direction)Dir, DOIT_ETRE_DEFINI);
  if ((DemiCase<0)||(DemiCase>1))
   asMsgErr+=asSource+Format(": valeur � case incorrecte (%d)\n", ARRAYOFCONST((DemiCase)));
 }
//-----------------------------------------------------------------------------
void pieton::ChercheFileTaxis() // v3.6
 {
  voie *v;
  int NumPlaceTaxi=0;
  direction DirPlace=indefinie,
            ProchDir=indefinie;
  if (!NumFileTaxi) // Cas improbable mais on ne sait jamais
   { // On abandonne la recherche de file de taxi
    FileTaxiTrv=false;
    return; // Num�ro de file de taxi obligatoire pour que l'on puisse trouver la t�te !
   }
  for(int d=nord; (!NumPlaceTaxi)&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    if (v->NumPlaceTaxi&&
       (cv->PlaceTaxi[v->NumPlaceTaxi-1].NumFile==NumFileTaxi-1))
     {
      NumPlaceTaxi=v->NumPlaceTaxi;
      DirPlace=(direction)d;
     }
   }
  if (!NumPlaceTaxi) // Pas trouv� de place de taxi aux allentours...
   { // On abandonne la recherche de file de taxi
    FileTaxiTrv=false;
    NumFileTaxi=0;
    return;
   }
  else
   if ((!cv->v[x][y].PassagePietons)&&(cv->PlaceTaxi[NumPlaceTaxi-1].EstTeteFile()))
    { // On a finalement trouv� la t�te : il attend le taxi (bloque le pi�ton)
     FileTaxiTrv=false;
     AttendTaxi=true;
     TourAttTaxi=cv->TourCrt;
     Dir=DirPlace;
     return;
    }
  if ((ProchDir=cv->PlaceTaxi[NumPlaceTaxi-1].DirPlaceSvtMemeFile())!=DirPlace)
   {
    if (cv->V(x,y,ProchDir).PietonPeutAller(ProchDir))
     {
      Dir=ProchDir; // Cas ou on longe simplement la file
      return;
     }
   }
  else // M�me direction : il faut contourner la case !
   {
    ProchDir=ADroiteDe[DirPlace];
    if (cv->V(x,y,ProchDir).PietonPeutAller(ProchDir)&&
        v->v(ProchDir)->PietonPeutAller(ProchDir))
     {
      Dir=ProchDir;
      return;
     }
    ProchDir=AGaucheDe[DirPlace]; // v3.6.1. Erreur de direction
    if (cv->V(x,y,ProchDir).PietonPeutAller(ProchDir)&&
        v->v(ProchDir)->PietonPeutAller(ProchDir))
     {
      Dir=ProchDir;
      return;
     }
    // On a pas trouv� de direction, on abandonne la recherche
    FileTaxiTrv=false;
    NumFileTaxi=0;
   }
 }
//-----------------------------------------------------------------------------
int feu::DefinitNbFeuxDmd(int n)
 {
  int i;
  if (NbFeuxDmd)
   {
    delete[] NumFeuxDmd;
    NumFeuxDmd=NULL;
   }
  NbFeuxDmd=0;
  if (NumFeuxDmd=new int[n])
   {
    for(i=0; i<n; i++) NumFeuxDmd[i]=0;
    NbFeuxDmd=n;
   }
  return NbFeuxDmd;
 }
//-----------------------------------------------------------------------------
int feu::DefinitNbFeuxAtt(int n)
 {
  int i;
  if (NbFeuxAtt)
   {
    delete[] NumFeuxAtt;
    NumFeuxAtt=NULL;
   }
  NbFeuxAtt=0;
  if (NumFeuxAtt=new int[n])
   {
    for(i=0; i<n; i++) NumFeuxAtt[i]=0;
    NbFeuxAtt=n;
   }
  return NbFeuxAtt;
 }
//-----------------------------------------------------------------------------
void feu::AjouteFeuDmd(int NumNvFeu)
 {
  int i, *NvNumFeuxDmd;
  NbFeuxDmd++;
  NvNumFeuxDmd=new int[NbFeuxDmd];
  for(i=0; i<NbFeuxDmd-1; i++)
   NvNumFeuxDmd[i]=NumFeuxDmd[i];
  NvNumFeuxDmd[NbFeuxDmd-1]=NumNvFeu;
  if (NumFeuxDmd) delete[] NumFeuxDmd;
  NumFeuxDmd=NvNumFeuxDmd;
 }
//-----------------------------------------------------------------------------
void feu::AjouteFeuAtt(int NumNvFeu)
 {
  int i, *NvNumFeuxAtt;
  NbFeuxAtt++;
  NvNumFeuxAtt=new int[NbFeuxAtt];
  for(i=0; i<NbFeuxAtt-1; i++)
   NvNumFeuxAtt[i]=NumFeuxAtt[i];
  NvNumFeuxAtt[NbFeuxAtt-1]=NumNvFeu;
  if (NumFeuxAtt) delete[] NumFeuxAtt;
  NumFeuxAtt=NvNumFeuxAtt;
 }
//-----------------------------------------------------------------------------
void feu::RetireFeuDmd(int NumFeu) // NumFeu(>0) doit �tre dans NumFeuxDmd[]
 {
  int i, Trv=0, *NvNumFeuxDmd=NULL;
  if (--NbFeuxDmd)
   {
    NvNumFeuxDmd=new int[NbFeuxDmd];
    for(i=0; i<NbFeuxDmd; i++)
     NvNumFeuxDmd[i]=NumFeuxDmd[i+(Trv|=(NumFeuxDmd[i]==NumFeu))];
   }
  delete[] NumFeuxDmd;
  NumFeuxDmd=NvNumFeuxDmd;
 }
//-----------------------------------------------------------------------------
void feu::RetireFeuAtt(int NumFeu) // NumFeu(>0) doit �tre dans NumFeuxAtt[]
 {
  int i, Trv=0, *NvNumFeuxAtt=NULL;
  if (--NbFeuxAtt)
   {
    NvNumFeuxAtt=new int[NbFeuxAtt];
    for(i=0; i<NbFeuxAtt; i++)
     NvNumFeuxAtt[i]=NumFeuxAtt[i+(Trv|=(NumFeuxAtt[i]==NumFeu))];
   }
  delete[] NumFeuxAtt;
  NumFeuxAtt=NvNumFeuxAtt;
 }
//-----------------------------------------------------------------------------
void feu::ChangeEtat()
 {
  bool ChgEtat=(Etat!=ProchainEtat);
  Etat=ProchainEtat;
  if (ChgEtat) frmSimulation->RedessineCase(x, y, false);
 }
//-----------------------------------------------------------------------------
void feu::DefinitProchainEtat()
 {
  int i;
  TourDrnChgEtat=cv->TourCrt;
  if (Etat) ProchainEtat=(etat_feu)(1+(Etat)%3);
  switch(ProchainEtat)
   {
    case vert:  DemandeVert=false;
                FeuxTousRouges=false;
                ProchainVert=false;
                break;
    case rouge: RougeDemande=false;
                // On informe quels sont les prochains feux � se mettre au vert
                for(i=0; i<NbFeuxDmd; i++)
                 if ((cv->Feu[NumFeuxDmd[i]-1].Etat==rouge)&&
                     (!cv->Feu[NumFeuxDmd[i]-1].ProchainVert)&&
                     (cv->Feu[NumFeuxDmd[i]-1].DemandeVert||
                      (cv->Feu[NumFeuxDmd[i]-1].TourDrnChgEtat<cv->TourCrt)))
                  {
                   cv->Feu[NumFeuxDmd[i]-1].ProchainVert=true;
                   cv->Feu[NumFeuxDmd[i]-1].TourDrnChgEtat=cv->TourCrt;
                  }
                break;
    default:    break;
   }
 }
//-----------------------------------------------------------------------------
void feu::Evolue()
 {
  int i,
      NumVeh,
      NumBus, // v3.0 
      NumTram, // v3.5
      NumTaxi; // v3.6
  ProchainEtat=Etat; // Par d�faut
  switch(Etat)
   {
    case inactif : break;
    case vert:     // Si (rouge demand� ou passage immediat) et dur�e vert �coul�e -> Orange
                   if (((RougeDemande&&(TourDrnChgEtat<cv->TourCrt))||
                        (TypePsgRouge==immediat))&&
                       (cv->TourCrt-TourDrnChgEtat>DureeVert))
                    DefinitProchainEtat();
                   break;
    case orange:   if (cv->TourCrt-TourDrnChgEtat>cv->DureeOrange)
                    DefinitProchainEtat();
                   break;
    case rouge:    // Le vert n'est pas encore demand�
                   if (!DemandeVert)
                    {
                     if ((cv->TourCrt-TourDrnChgEtat>DureeRouge)&& // la dur�e du rouge est �coul�e ET
                         ((TypeDmdVert==immediate)|| // La demande est imm�diate Ou
                          ((NumVeh=cv->v[x][y].NumVehicule)&& // un v�hicule est sur la case et
                           (cv->Vehicule[NumVeh-1].Dir==Dir))|| // dans la direction du feu... Ou
                          ((NumBus=cv->v[x][y].NumBus)&& // un bus est sur la case et
                           (cv->Bus[NumBus-1].Dir==Dir))||
                          ((NumTram=cv->v[x][y].NumTram)&& // un tram est sur la case et
                           (cv->Tram[NumTram-1].Dir==Dir))|| // dans la direction du feu... (v3.5)
                          ((NumTaxi=cv->v[x][y].NumTaxi)&& // un taxi est sur la case et
                           (cv->Taxi[NumTaxi-1].Dir==Dir)))) // dans la direction du feu... (v3.6)
                      { // Alors...On demande le vert DES QU'UN DES FEUX (devant �tre rouge) EST VERT
                       for(i=0;
                           (i<NbFeuxAtt)&&
                           ((cv->Feu[NumFeuxAtt[i]-1].Etat!=vert)||
                            ((cv->Feu[NumFeuxAtt[i]-1].TourDrnChgEtat==cv->TourCrt)&&
                             (!cv->Feu[NumFeuxAtt[i]-1].RougeDemande)));
                           i++);
                       if (DemandeVert=(i<NbFeuxAtt)) TourDrnChgEtat=cv->TourCrt;
                      }
                    }
                   // Le vert est demand�...
                   if (DemandeVert)
                    {
                     // On le fait toujours savoir (si jamais un feu devient vert entre-temps)
                     for(i=0; i<NbFeuxAtt; i++) // On parcours les feux devant �tre rouge
                      if ((cv->Feu[NumFeuxAtt[i]-1].Etat==vert)&& // feu oppos� vert et
                          (cv->Feu[NumFeuxAtt[i]-1].TourDrnChgEtat<cv->TourCrt)&&
                          (!cv->Feu[NumFeuxAtt[i]-1].RougeDemande)) // le rouge n'a pas encore �t� demand�)
                       {
                        cv->Feu[NumFeuxAtt[i]-1].RougeDemande=true; // Ben maintenant...
                        cv->Feu[NumFeuxAtt[i]-1].TourDrnChgEtat=cv->TourCrt; //  c'est fait !
                       }
                    }
                   // On v�rifie que les feux oppos�s ne sont pas d�j� tous rouges (vert demand� ou non)
                   if (!FeuxTousRouges)
                    {
                     for(i=0;
                         (i<NbFeuxAtt)&&
                         (cv->Feu[NumFeuxAtt[i]-1].Etat==rouge)&&
                         (cv->Feu[NumFeuxAtt[i]-1].DemandeVert||
                          cv->Feu[NumFeuxAtt[i]-1].ProchainVert||
                          (cv->Feu[NumFeuxAtt[i]-1].TourDrnChgEtat<cv->TourCrt));
                         i++);
                     if (FeuxTousRouges=(i==NbFeuxAtt)) TourDrnChgEtat=cv->TourCrt;
                    }
                   // On passe au vert si on le demande ou on l'autorise (vert demand� ou non)
                   if (FeuxTousRouges&&ProchainVert&&(TourDrnChgEtat<cv->TourCrt))
                    DefinitProchainEtat();
                   break;
   }
 }
//-----------------------------------------------------------------------------
bool feu::Charge(int hfile)
 {
  int i;
  bool Ok;
  Ok=FileRead(hfile, &Numero, sizeof(Numero))&&
     FileRead(hfile, &x, sizeof(x))&&
     FileRead(hfile, &y, sizeof(y))&&
     FileRead(hfile, &Dir, sizeof(Dir))&&
     FileRead(hfile, &Etat, sizeof(Etat))&&
     FileRead(hfile, &NbFeuxDmd, sizeof(NbFeuxDmd))&&
     FileRead(hfile, &NbFeuxAtt, sizeof(NbFeuxAtt))&&
     FileRead(hfile, &TypeDmdVert, sizeof(TypeDmdVert))&&
     FileRead(hfile, &TypePsgRouge, sizeof(TypePsgRouge))&&
     FileRead(hfile, &DureeRouge, sizeof(DureeRouge))&&
     FileRead(hfile, &DureeVert, sizeof(DureeVert))&&
     FileRead(hfile, &DemandeVert, sizeof(DemandeVert))&&
     FileRead(hfile, &RougeDemande, sizeof(RougeDemande));

  if (Ok)
   {
    if (NbFeuxDmd) Ok=!!(NumFeuxDmd=new int[NbFeuxDmd]);
    if (NbFeuxAtt) Ok=!!(NumFeuxAtt=new int[NbFeuxAtt]);
   }
  for(i=0; Ok&&(i<NbFeuxDmd); i++) Ok=FileRead(hfile, &(NumFeuxDmd[i]), sizeof(NumFeuxDmd[i]));
  for(i=0; Ok&&(i<NbFeuxAtt); i++) Ok=FileRead(hfile, &(NumFeuxAtt[i]), sizeof(NumFeuxAtt[i]));
  return Ok;
 }
//-----------------------------------------------------------------------------
bool feu::Sauve(int hfile)
 {
  int i, Ok,
      xc=x-cv->Xc, yc=y-cv->Yc; // v4.0.1
  Ok=FileWrite(hfile, &Numero, sizeof(Numero))&&
     FileWrite(hfile, cv->CopieEnCours?&xc:&x, sizeof(x))&& // v4.0.1
     FileWrite(hfile, cv->CopieEnCours?&yc:&y, sizeof(y))&& // v4.0.1
     FileWrite(hfile, &Dir, sizeof(Dir))&&
     FileWrite(hfile, &Etat, sizeof(Etat))&&
     FileWrite(hfile, &NbFeuxDmd, sizeof(NbFeuxDmd))&&
     FileWrite(hfile, &NbFeuxAtt, sizeof(NbFeuxAtt))&&
     FileWrite(hfile, &TypeDmdVert, sizeof(TypeDmdVert))&&
     FileWrite(hfile, &TypePsgRouge, sizeof(TypePsgRouge))&&
     FileWrite(hfile, &DureeRouge, sizeof(DureeRouge))&&
     FileWrite(hfile, &DureeVert, sizeof(DureeVert))&&
     FileWrite(hfile, &DemandeVert, sizeof(DemandeVert))&&
     FileWrite(hfile, &RougeDemande, sizeof(RougeDemande));

  for(i=0; Ok&&(i<NbFeuxDmd); i++) Ok=FileWrite(hfile, &(NumFeuxDmd[i]), sizeof(NumFeuxDmd[i]));
  for(i=0; Ok&&(i<NbFeuxAtt); i++) Ok=FileWrite(hfile, &(NumFeuxAtt[i]), sizeof(NumFeuxAtt[i]));
  return Ok;
 }
//-----------------------------------------------------------------------------
void feu::Verifie(AnsiString &asMsgErr, AnsiString asSource)
 {
  int i;
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, DOIT_ETRE_DEFINI);
  VerifieDirection(asMsgErr, asSource, (direction)Dir, DOIT_ETRE_DEFINI);
  VerifieEtat(asMsgErr, asSource, Etat);
  VerifieEtat(asMsgErr, asSource, ProchainEtat);

  VerifEnCours=true; // Evite les boucles infinies dues aux pointages mutuels de r�f�rences

  if ((NbFeuxDmd<0)||(NbFeuxDmd>cv->NbFeux))
   asMsgErr+=asSource+Format(": nombre des prochains feux verts incorrect (%d)\n", ARRAYOFCONST((NbFeuxDmd)));
  else
   for(i=0; i<NbFeuxDmd; i++)
    if ((NumFeuxDmd[i]<1)||(NumFeuxDmd[i]>cv->NbFeux)) // v3.7.2 : > strict
     asMsgErr+=asSource+Format(": num�ro du %d� prochain feu vert incorrect (%d)\n", ARRAYOFCONST((i+1, NumFeuxDmd[i])));
    else
     if (!cv->Feu[NumFeuxDmd[i]-1].VerifEnCours)
      cv->Feu[NumFeuxDmd[i]-1].Verifie(asMsgErr, Format("%d� prochain feu vert [n�%d, (%d,%d)]\n",
                                                        ARRAYOFCONST((i+1, NumFeuxDmd[i],
                                                                      cv->Feu[NumFeuxDmd[i]-1].x,
                                                                      cv->Feu[NumFeuxDmd[i]-1].y
                                                                     ))));

  if ((NbFeuxAtt<0)||(NbFeuxAtt>cv->NbFeux))
   asMsgErr+=asSource+Format(": nombre des feux devant �tre rouge incorrect (%d)\n", ARRAYOFCONST((NbFeuxAtt)));
  else
   for(i=0; i<NbFeuxAtt; i++)
    if ((NumFeuxAtt[i]<1)||(NumFeuxAtt[i]>cv->NbFeux)) // v3.7.2 : > strict
     asMsgErr+=asSource+Format(": num�ro du %d� feu devant �tre rouge incorrect (%d)\n", ARRAYOFCONST((i+1, NumFeuxAtt[i])));
    else
     if (!cv->Feu[NumFeuxAtt[i]-1].VerifEnCours)
      cv->Feu[NumFeuxAtt[i]-1].Verifie(asMsgErr, Format("%d� feu devant �tre rouge [n�%d, (%d,%d)]\n",
                                                        ARRAYOFCONST((i+1, NumFeuxAtt[i],
                                                                      cv->Feu[NumFeuxAtt[i]-1].x,
                                                                      cv->Feu[NumFeuxAtt[i]-1].y
                                                                     ))));

  VerifEnCours=false;

  VerifieDmdVert(asMsgErr, asSource, TypeDmdVert);
  VerifiePsgRouge(asMsgErr, asSource, TypePsgRouge);

  if (DemandeVert&&(Etat!=rouge))
   asMsgErr+=asSource+": demande le vert alors qu'il n'est pas rouge\n";
  if (RougeDemande&&(Etat!=vert))
   asMsgErr+=asSource+": le rouge est demand� alors qu'il n'est pas vert\n";
 }
//-----------------------------------------------------------------------------
void etape::PlaceProchainVehicule()
 {
  int i, NumVehicule=0;
  if (!cv->v[x][y].NumVehicule)
   {
    for(i=0; (!NumVehicule)&&(i<cv->NbVehicules); i++)
     NumVehicule=((cv->Vehicule[i].NumEtapeDepart==Numero)&&
                  (cv->Vehicule[i].x==x)&&
                  (cv->Vehicule[i].y==y))*(i+1);
    if (NumVehicule) // Il y a encore un v�hicule � sortir
     {
      cv->v[x][y].NumVehicule=NumVehicule;
      cv->PlaceVehicule(x, y, NumVehicule); // v2.2.7. Inclut les stats d'Attente/Trafic
      cv->Vehicule[NumVehicule-1].TourDepart=cv->TourCrt;
      cv->NbVehiculesSortis++;
     }
   }
 }
//-----------------------------------------------------------------------------
bool etape::Charge(int hfile)
 {
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &x, sizeof(x))&&
         FileRead(hfile, &y, sizeof(y));
 }
//-----------------------------------------------------------------------------
bool etape::Sauve(int hfile)
 {
  int xc=x-cv->Xc, yc=y-cv->Yc; // v4.0.1
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, cv->CopieEnCours?&xc:&x, sizeof(x))&& // v4.0.1
         FileWrite(hfile, cv->CopieEnCours?&yc:&y, sizeof(y));  // v4.0.1
 }
//-----------------------------------------------------------------------------
void etape::Verifie(AnsiString &asMsgErr)
 {
  AnsiString asSource=Format("Etape n�%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, DOIT_ETRE_DEFINI);
 }
//-----------------------------------------------------------------------------
void vehicule::CalculeProchaineDirection()
 {
  voie *v=&(cv->v[x][y]), *Voie;
  direction AncDir=Dir; // v2.2.4
  bool Prioritaire=(NivPriorite>normal); // v3.5 (pour DistEtape)
  int OrdreDir[NBDIR]={0,0,0,0},
      i, j, ndp=NbDir[v->DirPoss];
  Dir=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux �tapes.
  // En cas d'�galit�, c'est le hasard : (N�Veh.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if (i!=j) // On d�gringole si distance sup�rieure.
     OrdreDir[i]+=((v->DistEtape[NumEtapeArrivee-1][i][Prioritaire]>v->DistEtape[NumEtapeArrivee-1][j][Prioritaire])||
                   ((v->DistEtape[NumEtapeArrivee-1][i][Prioritaire]==v->DistEtape[NumEtapeArrivee-1][j][Prioritaire])&&
                    ((Dirdp[i][v->DirPoss]!=AncDir)|| // En cas d'�galit�, pr�f�re garder la direction courante : v2.2.4.  // v3.5 : || par && !
                     ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)
  for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
   for(j=0; (!Dir)&&(j<ndp); j++)
    {
     Voie=&(cv->V(x,y,Dirdp[j][v->DirPoss]));
     if ((OrdreDir[j]==i)&&
         ((!v->ToutDroit)||    // Direction interdite si : - Obligation d'aller tout droit ET
          Prioritaire|| //                                   V�hicule NON prioritaire (v3.9.1) ET
          (DirDrnDepl==Dirdp[j][v->DirPoss]))&& //           pas m�me direction que lors du dernier d�placement // v3.7.1 : Erreur !
         (!Voie->NumPlaceTaxi)&& //                        - Place de taxi. v3.6
         ((!Voie->PassageBus)||  //                        - Passage bus dans cette direction sauf v�hicules prioritaires (police, urgence)
          Prioritaire)&&
         (((!Voie->NumVehicule)&&
           (!Voie->NumBus)&& // v3.0
           (!Voie->NumTram)&& // v3.5
           (!Voie->NumTaxi))|| // v3.6
          (Voie->NumEtape&&(Voie->NumEtape==NumEtapeArrivee))||
          (cv->TourCrt<=1+TourDrnDepl+(!NivPriorite)*cv->AttenteMaxVeh*(1+OrdreDir[j])))) // v2.2
      Dir=Dirdp[j][v->DirPoss];
    }

   // Si la direction est toujours ind�finie : on prend la meilleure direction possible
   if (!Dir)
    for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
     for(j=0; (!Dir)&&(j<ndp); j++)
      if (OrdreDir[j]==i)
       Dir=Dirdp[j][v->DirPoss];
 }
//-----------------------------------------------------------------------------
direction vehicule::ProchaineDirectionAuCarrefour() // ATTENTION : DIR DOIT ETRE DEFINIE
 {
  voie *v=&(cv->V(x,y,Dir)); // Ici v est la prochaine case
  bool Prioritaire=(NivPriorite>normal); // v3.5 (pour DistEtape)
  int OrdreDir[NBDIR]={0,0,0,0},
      i, j, ndp=NbDir[v->DirPoss];
  direction DirAuCarrefour=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux �tapes si la case est libre.
  // En cas d'�galit�, c'est le hasard : (N�Veh.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if (i!=j)
     OrdreDir[i]+=((v->DistEtape[NumEtapeArrivee-1][i][Prioritaire]>v->DistEtape[NumEtapeArrivee-1][j][Prioritaire])||
                   ((v->DistEtape[NumEtapeArrivee-1][i][Prioritaire]==v->DistEtape[NumEtapeArrivee-1][j][Prioritaire])&&
                    ((Dirdp[i][v->DirPoss]!=Dir)|| // En cas d'�galit�, pr�f�re garder la direction courante : v2.2.4.  // v3.5 : || par && !
                     ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // tirage au hasard en cas d'�galit� (Ici TourCrt+1)
  for(i=0; (!DirAuCarrefour)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
   for(j=0; (!DirAuCarrefour)&&(j<ndp); j++)
    if ((OrdreDir[j]==i)&&
        (!v->NumPlaceTaxi)&& // Direction interdite si :     - Place de Taxi. v3.6
        ((!v->ToutDroit)||   //                              - Obligation d'aller tout droit ET
         Prioritaire|| //                                      V�hicule NON Prioritaire (v3.9.1) ET
         (DirDrnDepl==(DirDrnDepl==Dirdp[j][v->DirPoss])))) // pas m�me direction que lors du dernier d�placement. v3.7.1 : Erreur !
    DirAuCarrefour=Dirdp[j][v->DirPoss];
  return DirAuCarrefour;
 }
//-----------------------------------------------------------------------------
bool vehicule::PeutPasser()
 {
  voie *v=&(cv->v[x][y]);
  int NumFeuVeh;
  return Dir&&
         (NivPriorite||
          (((v->Priorite[Dir-1]!=stop)||
            (cv->TourCrt-TourDrnDepl>=2))&&
           ((!(NumFeuVeh=v->NumFeu[Dir-1]))||
            (cv->Feu[NumFeuVeh-1].Etat<orange))));
 }
//-----------------------------------------------------------------------------
void vehicule::Verifie(AnsiString &asMsgErr)
 {
  AnsiString asSource=Format("V�hicule n�%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  VerifieDirection(asMsgErr, asSource, Dir, PEUT_ETRE_INDEFINI);
  if (NumEtapeDepart<1)
   asMsgErr+=asSource+Format(": num�ro d'�tape de d�part incorrect (%d)\n", ARRAYOFCONST((NumEtapeDepart)));
  if (NumEtapeArrivee<1)
   asMsgErr+=asSource+Format(": num�ro d'�tape d'arriv�e incorrect (%d)\n", ARRAYOFCONST((NumEtapeArrivee)));
 }
//-----------------------------------------------------------------------------
void depot_bus::PlaceProchainBus() // v3.0
 {
  int NumProchBus;
  if (Defini()&&
      (!cv->v[x][y].NumBus)&& // Pas de bus
      (!cv->v[x][y].NumTram)&& // Pas de tram
      (!cv->v[x][y].NumVehicule)&& // pas de v�hicule
      (!cv->v[x][y].NumTaxi)&& // Pas de taxi (v3.6)... sur la case d�p�t
      (NumDrnBusSorti<cv->NbBus)) // ET Encore au moins un bus � sortir
   {
    NumProchBus=++NumDrnBusSorti;
    cv->PlaceBus(x, y, NumProchBus);
    cv->Bus[NumProchBus-1].TourDepart=cv->TourCrt; // v3.5 : un oubli !
   }
 }
//-----------------------------------------------------------------------------
bool depot_bus::Charge(int hfile) // v3.0
 {
  return FileRead(hfile, &x, sizeof(x))&&
         FileRead(hfile, &y, sizeof(y));
 }
//-----------------------------------------------------------------------------
bool depot_bus::Sauve(int hfile) // v3.0
 {
  int xc=x-cv->Xc, yc=y-cv->Yc; // v4.0.1
  return FileWrite(hfile, cv->CopieEnCours?&xc:&x, sizeof(x))&& // v4.0.1
         FileWrite(hfile, cv->CopieEnCours?&yc:&y, sizeof(y)); // v4.0.1
 }
//-----------------------------------------------------------------------------
void depot_bus::Verifie(AnsiString &asMsgErr) // v3.03
 {
  AnsiString asSource=Format("D�pot bus : ", ARRAYOFCONST((x, y)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
 }
//-----------------------------------------------------------------------------
void bus::FaitMonterPieton(int NumPietonAFaireMonter) // v3.0
 {
  pieton *p=cv->Pieton+NumPietonAFaireMonter;
  int xp=p->x, yp=p->y;
  if (NbPersonnes<cv->NbMaxPersonnesBus)
   {
    NbPersonnes++;
    cv->v[xp][yp].RetirePieton(NumPietonAFaireMonter);
    p->MonteDansBus(Numero); // v3.6
    frmSimulation->RedessineCase(xp, yp, false);
   }
 }
//-----------------------------------------------------------------------------
void bus::FaitMonterEtDescendre() // v3.0
 {
  int i;
  direction d=ADroiteDe[Dir];
  voie *v=&cv->V(x,y,d);
  pieton *p;
  for(i=0; i<cv->NbPietons; i++)
   {
    p=cv->Pieton+i;
    if ((p->NumBus==Numero)&&
        (p->VeutDescendre||
         (p->VeutDescendre=(cv->ProbaArretBusDmd>(rand()%100)))))
     v->FaitDescendrePieton(d, i); // Si on peut pas faire descendre, il descendra au prochain arr�t
    if ((p->NumArretBus==NumDrnArret)&&
        p->AttendBus)
     FaitMonterPieton(i); // Si on ne peut pas faire monter, il montera dans le prochain bus
   }
 }
//-----------------------------------------------------------------------------
void bus::CalculeProchaineDirection() // v3.0
 {
  voie *v=&(cv->v[x][y]), *Voie;
  direction AncDir=Dir;
  int OrdreDir[NBDIR]={0,0,0,0},
      i, j, ndp=NbDir[v->DirPoss];
  Dir=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux arr�ts de bus
  // En cas d'�galit�, c'est le hasard : (N�Bus.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if (i!=j) // On d�gringole si distance sup�rieure.
     OrdreDir[i]+=((v->DistArretBus[NumArretSvt-1][i]>v->DistArretBus[NumArretSvt-1][j])||
                   ((v->DistArretBus[NumArretSvt-1][i]==v->DistArretBus[NumArretSvt-1][j])&&
                    ((Dirdp[i][v->DirPoss]!=AncDir)|| // En cas d'�galit�, pr�f�re garder la direction courante : v2.2.4
                     ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)
  for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
   for(j=0; (!Dir)&&(j<ndp); j++)
    {
     Voie=&(cv->V(x,y,Dirdp[j][v->DirPoss]));
     if ((OrdreDir[j]==i)&&
         (!v->NumPlaceTaxi)&&  // Direction interdite si       - Place de taxi. v3.6
         ((!v->ToutDroit)||    //                              - Obligation d'aller tout droit ET
          (DirDrnDepl==(DirDrnDepl==Dirdp[j][v->DirPoss])))&& // pas m�me direction que lors du dernier d�placement. v3.7.1 : Erreur !
         (((!Voie->NumVehicule)&&(!Voie->NumBus)&&(!Voie->NumTram)&&(!Voie->NumTaxi))||
          (Voie->NumArretBus&&(Voie->NumArretBus==NumArretSvt))||
          (cv->TourCrt<=1+TourDrnDepl+5*cv->AttenteMaxVeh*(1+OrdreDir[j])))) // AttentMaxBus = 5*AttenteMaxVeh
      Dir=Dirdp[j][v->DirPoss];
    }

   // Si la direction est toujours ind�finie : on prend la meilleure direction possible
   if (!Dir)
    for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
     for(j=0; (!Dir)&&(j<ndp); j++)
      if (OrdreDir[j]==i) Dir=Dirdp[j][v->DirPoss];
  if (!DirDrnDepl) DirDrnDepl=Dir;
  if (!DirAvtDrnDepl) DirAvtDrnDepl=Dir;
 }
//-----------------------------------------------------------------------------
direction bus::ProchaineDirectionAuCarrefour() // ATTENTION : DIR DOIT ETRE DEFINIE. v3.0
 {
  voie *v=&(cv->V(x,y,Dir)); // Ici v est la prochaine case
  int OrdreDir[NBDIR]={0,0,0,0},
      i, j, ndp=NbDir[v->DirPoss];
  direction DirAuCarrefour=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux �tapes si la case est libre.
  // En cas d'�galit�, c'est le hasard : (N�Bus.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if (i!=j)
     OrdreDir[i]+=((v->DistArretBus[NumArretSvt-1][i]>v->DistArretBus[NumArretSvt-1][j])||
                   ((v->DistArretBus[NumArretSvt-1][i]==v->DistArretBus[NumArretSvt-1][j])&&
                    ((Dirdp[i][v->DirPoss]!=Dir)|| // En cas d'�galit�, pr�f�re garder la direction courante : // v3.5 : || par && !
                     ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // tirage au hasard en cas d'�galit� (Ici TourCrt+1)
  for(i=0; (!DirAuCarrefour)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
   for(j=0; (!DirAuCarrefour)&&(j<ndp); j++)
    if ((OrdreDir[j]==i)&&
        (!v->NumPlaceTaxi)&& // Direction interdite si :    - Place de taxi
        ((!v->ToutDroit)||   //                             - Obligation d'aller tout droit ET
         (DirDrnDepl==(DirDrnDepl==Dirdp[j][v->DirPoss])))) // pas m�me direction que lors du dernier d�placement. v3.7.1 : Erreur !
    DirAuCarrefour=Dirdp[j][v->DirPoss];
  return DirAuCarrefour;
 }
//-----------------------------------------------------------------------------
bool bus::PeutPasser() // v3.0
 {
  voie *v=&(cv->v[x][y]);
  int NumFeuBus;
  return Dir&&
         ((v->Priorite[Dir-1]!=stop)||
          (cv->TourCrt-TourDrnDepl>=2))&&
         ((!(NumFeuBus=v->NumFeu[Dir-1]))||
          (cv->Feu[NumFeuBus-1].Etat<orange));
 }
//-----------------------------------------------------------------------------
int bus::NumeroArretSuivant() // v3.0
 {
  int i;
  for( i=0;
       (NumArretSvt!=cv->LigneBus[NumLigne-1].NumArret[i])&&
       (i<cv->LigneBus[NumLigne-1].NbArrets);
       i++);
  if (i<cv->LigneBus[NumLigne-1].NbArrets)
   return cv->LigneBus[NumLigne-1].NumArret[(i+1)%cv->LigneBus[NumLigne-1].NbArrets];
  else
   return cv->LigneBus[NumLigne-1].NumArret[0];
 }
//-----------------------------------------------------------------------------
void bus::Verifie(AnsiString &asMsgErr) // v3.03
 {
  AnsiString asSource=Format("Bus n�%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  VerifieDirection(asMsgErr, asSource, Dir, PEUT_ETRE_INDEFINI);
  if ((NumLigne<0)||(NumLigne>=NBMAXLIGNESBUSTRAM))
   asMsgErr+=asSource+Format(": num�ro de ligne de bus incorrect (%d)\n", ARRAYOFCONST((NumLigne)));
 }
//-----------------------------------------------------------------------------
void arret_bus::Initialise() // v3.0
 {
  int i;
  x=-1; y=-1;
  NbLignes=0;
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++)
   {
    Ligne[i]=false;
    NumLigne[i]=0;
   }
 }
//-----------------------------------------------------------------------------
void arret_bus::InitialiseInfosLignesBus() // v3.0
 {
  int i;
  NbLignes=0;
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++)
   {
    Ligne[i]=false;
    NumLigne[i]=0;
   }
 }
//-----------------------------------------------------------------------------
void arret_bus::AjouteLigneBus(int n) // v3.0
 {
  NumLigne[NbLignes++]=n; // v3.0.5
  Ligne[n-1]=true;
 }
//-----------------------------------------------------------------------------
AnsiString arret_bus::asListeLignesBus() // v3.0.5
 {
  int i;
  AnsiString asListe="";
  for(i=0; i<NbLignes; i++)
   if (asListe.IsEmpty())
    asListe=IntToStr(NumLigne[i]);
   else
    asListe=asListe+","+IntToStr(NumLigne[i]);
  return asListe;
 }
//-----------------------------------------------------------------------------
bool arret_bus::Charge(int hfile) // v3.0
 {
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &x, sizeof(x))&&
         FileRead(hfile, &y, sizeof(y))&&
         FileRead(hfile, Ligne, NBMAXLIGNESBUSTRAM*sizeof(Ligne[0]))&&
         FileRead(hfile, &NbLignes, sizeof(NbLignes))&&
         FileRead(hfile, NumLigne, NBMAXLIGNESBUSTRAM*sizeof(NumLigne[0]));
 }
//-----------------------------------------------------------------------------
bool arret_bus::Sauve(int hfile) // v3.0
 {
  int xc=x-cv->Xc, yc=y-cv->Yc; // v4.0.1
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, cv->CopieEnCours?&xc:&x, sizeof(x))&&
         FileWrite(hfile, cv->CopieEnCours?&yc:&y, sizeof(y))&&
         FileWrite(hfile, Ligne, NBMAXLIGNESBUSTRAM*sizeof(Ligne[0]))&&
         FileWrite(hfile, &NbLignes, sizeof(NbLignes))&&
         FileWrite(hfile, NumLigne, NBMAXLIGNESBUSTRAM*sizeof(NumLigne[0]));
 }
//-----------------------------------------------------------------------------
void arret_bus::Verifie(AnsiString &asMsgErr) // v3.0
 {
  int i;
  AnsiString asSource=Format("Arr�t de bus n�%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  if ((NbLignes<0)||(NbLignes>NBMAXLIGNESBUSTRAM))
   asMsgErr+=asSource+Format(": nombre de lignes de bus incorrect (%d)\n", ARRAYOFCONST((NbLignes)));
  for(i=0; i<NbLignes; i++)
   if (Ligne[i]&&
       ((NumLigne[i]<0)||(NumLigne[i]>NBMAXLIGNESBUSTRAM)))
    asMsgErr+=asSource+Format(": num�ro de la %d� ligne de bus incorrect (%d)\n", ARRAYOFCONST((i+1, NumLigne[i]))); // v3.03
 }
//-----------------------------------------------------------------------------
void ligne_bus::Initialise() // v3.0
 {
  int i;
  NbBus=NbArrets=0;
  for(i=0; i<NBMAXARRETSBUSTRAMPARLIGNE; i++) NumArret[i]=0;
  for(i=0; i<NBMAXBUSTRAMPARLIGNE; i++) NumBus[i]=0;
 }
//-----------------------------------------------------------------------------
void ligne_bus::AjouteBus(int NumeroBus) // v3.0
 {
  NumBus[NbBus++]=NumeroBus;
 }
//-----------------------------------------------------------------------------
bool ligne_bus::Charge(int hfile) // v3.0
 { // Attention : On ne stocke pas le nombre et les n� de bus (calcul�s avant simul)
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &NbArrets, sizeof(NbArrets))&&
         FileRead(hfile, NumArret, NBMAXARRETSBUSTRAMPARLIGNE*sizeof(NumArret[0]));
 }
//-----------------------------------------------------------------------------
bool ligne_bus::Sauve(int hfile) // v3.0
 { // Attention : On ne stocke pas le nombre et les n� de bus (calcul�s avant simul)
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, &NbArrets, sizeof(NbArrets))&&
         FileWrite(hfile, NumArret, NBMAXARRETSBUSTRAMPARLIGNE*sizeof(NumArret[0]));
 }
//-----------------------------------------------------------------------------
void ligne_bus::Verifie(AnsiString &asMsgErr) // v3.0
 {
  int i;
  AnsiString asSource=Format("Ligne de bus n�%d", ARRAYOFCONST((Numero)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  if ((NbArrets<0)||(NbArrets>NBMAXARRETSBUSTRAMPARLIGNE))
   asMsgErr+=asSource+Format(": nombre d'arr�ts de bus incorrect (%d)\n", ARRAYOFCONST((NbArrets)));
  for(i=0; i<NbArrets; i++)
   if ((NumArret[i]<0)||(NumArret[i]>cv->NbArretsBus))
    asMsgErr+=asSource+Format(": num�ro du %d� arr�t de bus incorrect (%d)\n", ARRAYOFCONST((i+1, NumArret[i]))); // v3.03
 }
//-----------------------------------------------------------------------------
//////////// ICI COMMENCENT LES METHODES DES CLASSES LIEES AU RESEAU DE TRAM //
//-----------------------------------------------------------------------------
void tram::FaitMonterPieton(int NumPietonAFaireMonter) // v3.5
 {
  pieton *p=cv->Pieton+NumPietonAFaireMonter;
  int xp=p->x, yp=p->y;
  if (NbPersonnes<cv->NbMaxPersonnesTram)
   {
    NbPersonnes++;
    cv->v[xp][yp].RetirePieton(NumPietonAFaireMonter);
    p->MonteDansTram(Numero); // v3.6
    frmSimulation->RedessineCase(xp, yp, false);
   }
 }
//-----------------------------------------------------------------------------
void tram::FaitMonterEtDescendre() // v3.5
 {
  int i;
  direction d=ADroiteDe[Dir];
  voie *v=&cv->V(x,y,d);
  pieton *p;
  for(i=0; i<cv->NbPietons; i++)
   {
    p=cv->Pieton+i;
    if ((p->NumTram==Numero)&&
        (p->VeutDescendre||
         (p->VeutDescendre=(cv->ProbaArretTramDmd>(rand()%100)))))
     v->FaitDescendrePieton(d, i); // Si on peut pas faire descendre, il descendra au prochain arr�t
    if ((p->NumArretTram==NumDrnArret)&&
        p->AttendTram)
     FaitMonterPieton(i); // Si on ne peut pas faire monter, il montera dans le prochain tram
   }
 }
//-----------------------------------------------------------------------------
void tram::CalculeProchaineDirection() // v3.5
 {
  voie *v=&(cv->v[x][y]), *Voie;
  direction AncDir=DirDrnDepl;
  int OrdreDir[NBDIR]={0,0,0,0},
      d, i, j,
      nd=v->NbDirPossSensVoieTram(indefinie), // Nombre total de directions (pour DistArretTram)
      ndp=v->NbDirPossSensVoieTram(InvDir[AncDir]); // Nombre de directions possibles
  Dir=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux arr�ts de tram
  // En cas d'�galit�, c'est le hasard : (N�Tram.+Tour) Modulo Directions Possibles
  for(i=0; i<nd; i++)
   for(j=0; j<nd; j++)
    if ((i!=j)&&  // Direction possible
        (v->EstDirPossSensVoieTram(InvDir[AncDir], (direction)(d=v->DirSensVoieTram(indefinie, i)))))
     // On d�gringole si distance sup�rieure.
     OrdreDir[d-1]+=((v->DistArretTram[NumArretSvt-1][i]>v->DistArretTram[NumArretSvt-1][j])||
                   ((v->DistArretTram[NumArretSvt-1][i]==v->DistArretTram[NumArretSvt-1][j])&&
                    ((d!=AncDir)|| // En cas d'�galit�, pr�f�re garder la direction courante // v3.5 : || par && !
                     ((i+Numero+cv->TourCrt)%nd>(j+Numero+cv->TourCrt)%nd)))); // sinon tirage au hasard (Ici TourCrt+1)
  for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
   for(j=0; (!Dir)&&(j<ndp); j++)
    {
     Voie=&(cv->V(x,y,d=v->DirSensVoieTram(InvDir[AncDir], j)));
     if ((OrdreDir[d-1]==i)&&
         ((!v->ToutDroit)||    // Direction interdite si : - Obligation d'aller tout droit ET
          (DirDrnDepl==d))&&   //                            pas m�me direction que lors du dernier d�placement
         (!v->NumPlaceTaxi)&&  //                          - Place taxi. v3.6
         (((!Voie->NumVehicule)&&(!Voie->NumBus)&&(!Voie->NumTram)&&(!Voie->NumTaxi))||
          (Voie->NumArretTram&&(Voie->NumArretTram==NumArretSvt))||
          (cv->TourCrt<=1+TourDrnDepl+5*cv->AttenteMaxVeh*(1+OrdreDir[d-1])))) // AttentMaxTram = 5*AttenteMaxVeh
      Dir=(direction)d;
    }

   // Si la direction est toujours ind�finie : on prend la meilleure direction possible
   if (!Dir)
    for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
     for(j=0; (!Dir)&&(j<ndp); j++)
      if (OrdreDir[(d=v->DirSensVoieTram(InvDir[AncDir], j))-1]==i)
       Dir=(direction)d;
  if (!DirDrnDepl) DirDrnDepl=Dir;
  if (!DirAvtDrnDepl) DirAvtDrnDepl=Dir;
 }
//-----------------------------------------------------------------------------
direction tram::ProchaineDirectionAuCarrefour() // ATTENTION : DIR DOIT ETRE DEFINIE. v3.0
 {
  voie *v=&(cv->V(x,y,Dir)); // Ici v est la prochaine case
  int OrdreDir[NBDIR]={0,0,0,0},
      d, i, j,
      ndp=v->NbDirPossSensVoieTram(InvDir[Dir]); // Nombre de directions possibles
  direction DirAuCarrefour=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux �tapes si la case est libre.
  // En cas d'�galit�, c'est le hasard : (N�Tram.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if ((i!=j)&&  // Direction possible
        (v->EstDirPossSensVoieTram(InvDir[Dir], (direction)(d=v->DirSensVoieTram(indefinie, i)))))
     // On d�gringole si distance sup�rieure.
     OrdreDir[d-1]+=((v->DistArretTram[NumArretSvt-1][i]>v->DistArretTram[NumArretSvt-1][j])||
                   ((v->DistArretTram[NumArretSvt-1][i]==v->DistArretTram[NumArretSvt-1][j])&&
                    ((d!=Dir)|| // En cas d'�galit�, pr�f�re garder la direction courante. // v3.5 : || par && !
                     ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // tirage au hasard en cas d'�galit� (Ici TourCrt+1)
  for(i=0; (!DirAuCarrefour)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
   for(j=0; (!DirAuCarrefour)&&(j<ndp); j++)
    if ((OrdreDir[(d=v->DirSensVoieTram(InvDir[Dir], j))-1]==i)&&
        (!v->NumPlaceTaxi)&&  // Direction interdite si : - Place taxi. v3.6
        ((!v->ToutDroit)||    //                          - Obligation d'aller tout droit ET
         (DirDrnDepl==d)))    //                            pas m�me direction que lors du dernier d�placement
    DirAuCarrefour=(direction)d;
  return DirAuCarrefour;
 }
//-----------------------------------------------------------------------------
bool tram::PeutPasser() // v3.0
 {
  voie *v=&(cv->v[x][y]);
  int NumFeuTram;
  return Dir&&
         ((v->Priorite[Dir-1]!=stop)||
          (cv->TourCrt-TourDrnDepl>=2))&&
         ((!(NumFeuTram=v->NumFeu[Dir-1]))||
          (cv->Feu[NumFeuTram-1].Etat<orange));
 }
//-----------------------------------------------------------------------------
int tram::NumeroArretSuivant() // v3.0
 {
  int i;
  for( i=0;
       (NumArretSvt!=cv->LigneTram[NumLigne-1].NumArret[i])&&
       (i<cv->LigneTram[NumLigne-1].NbArrets);
       i++);
  if (i<cv->LigneTram[NumLigne-1].NbArrets)
   return cv->LigneTram[NumLigne-1].NumArret[(i+1)%cv->LigneTram[NumLigne-1].NbArrets];
  else
   return cv->LigneTram[NumLigne-1].NumArret[0];
 }
//-----------------------------------------------------------------------------
void tram::Verifie(AnsiString &asMsgErr) // v3.03
 {
  AnsiString asSource=Format("Tram n�%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  VerifieDirection(asMsgErr, asSource, Dir, PEUT_ETRE_INDEFINI);
  if ((NumLigne<0)||(NumLigne>=NBMAXLIGNESBUSTRAM))
   asMsgErr+=asSource+Format(": num�ro de ligne de tram incorrect (%d)\n", ARRAYOFCONST((NumLigne)));
 }
//-----------------------------------------------------------------------------
void arret_tram::Initialise() // v3.0
 {
  int i;
  x=-1; y=-1;
  NbLignes=0;
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++)
   {
    Ligne[i]=false;
    NumLigne[i]=0;
   }
 }
//-----------------------------------------------------------------------------
void arret_tram::InitialiseInfosLignesTram() // v3.5
 {
  int i;
  NbLignes=0;
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++)
   {
    Ligne[i]=false;
    NumLigne[i]=0;
   }
 }
//-----------------------------------------------------------------------------
void arret_tram::AjouteLigneTram(int n) // v3.0
 {
  NumLigne[NbLignes++]=n; // v3.0.5
  Ligne[n-1]=true;
 }
//-----------------------------------------------------------------------------
AnsiString arret_tram::asListeLignesTram() // v3.0.5
 {
  int i;
  AnsiString asListe="";
  for(i=0; i<NbLignes; i++)
   if (asListe.IsEmpty())
    asListe=AnsiString((char)('A'+NumLigne[i]-1));
   else
    asListe=asListe+","+AnsiString((char)('A'+NumLigne[i]-1));
  return asListe;
 }
//-----------------------------------------------------------------------------
bool arret_tram::Charge(int hfile) // v3.0
 {
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &x, sizeof(x))&&
         FileRead(hfile, &y, sizeof(y))&&
         FileRead(hfile, Ligne, NBMAXLIGNESBUSTRAM*sizeof(Ligne[0]))&&
         FileRead(hfile, &NbLignes, sizeof(NbLignes))&&
         FileRead(hfile, NumLigne, NBMAXLIGNESBUSTRAM*sizeof(NumLigne[0]));
 }
//-----------------------------------------------------------------------------
bool arret_tram::Sauve(int hfile) // v3.0
 {
  int xc=x-cv->Xc, yc=y-cv->Yc; // v4.0.1
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, cv->CopieEnCours?&xc:&x, sizeof(x))&& // v4.0.1
         FileWrite(hfile, cv->CopieEnCours?&yc:&y, sizeof(y))&& // v4.0.1
         FileWrite(hfile, Ligne, NBMAXLIGNESBUSTRAM*sizeof(Ligne[0]))&&
         FileWrite(hfile, &NbLignes, sizeof(NbLignes))&&
         FileWrite(hfile, NumLigne, NBMAXLIGNESBUSTRAM*sizeof(NumLigne[0]));
 }
//-----------------------------------------------------------------------------
void arret_tram::Verifie(AnsiString &asMsgErr) // v3.0
 {
  int i;
  AnsiString asSource=Format("Arr�t de tram n�%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  if ((NbLignes<0)||(NbLignes>NBMAXLIGNESBUSTRAM))
   asMsgErr+=asSource+Format(": nombre de lignes de tram incorrect (%d)\n", ARRAYOFCONST((NbLignes)));
  for(i=0; i<NbLignes; i++)
   if (Ligne[i]&&
       ((NumLigne[i]<0)||(NumLigne[i]>NBMAXLIGNESBUSTRAM)))
    asMsgErr+=asSource+Format(": num�ro de la %d� ligne de tram incorrect (%d)\n", ARRAYOFCONST((i+1, NumLigne[i]))); // v3.03
 }
//-----------------------------------------------------------------------------
void ligne_tram::Initialise() // v3.0
 {
  int i;
  NbTrams=NbArrets=0;
  for(i=0; i<NBMAXARRETSBUSTRAMPARLIGNE; i++) NumArret[i]=0;
  for(i=0; i<NBMAXBUSTRAMPARLIGNE; i++) NumTram[i]=0;
 }
//-----------------------------------------------------------------------------
void ligne_tram::AjouteTram(int NumeroTram) // v3.0
 {
  NumTram[NbTrams++]=NumeroTram;
 }
//-----------------------------------------------------------------------------
bool ligne_tram::Charge(int hfile) // v3.0
 { // Attention : On ne stocke pas le nombre et les n� de tram (calcul�s avant simul)
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &NbArrets, sizeof(NbArrets))&&
         FileRead(hfile, NumArret, NBMAXARRETSBUSTRAMPARLIGNE*sizeof(NumArret[0]));
 }
//-----------------------------------------------------------------------------
bool ligne_tram::Sauve(int hfile) // v3.0
 { // Attention : On ne stocke pas le nombre et les n� de tram (calcul�s avant simul)
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, &NbArrets, sizeof(NbArrets))&&
         FileWrite(hfile, NumArret, NBMAXARRETSBUSTRAMPARLIGNE*sizeof(NumArret[0]));
 }
//-----------------------------------------------------------------------------
void ligne_tram::Verifie(AnsiString &asMsgErr) // v3.0
 {
  int i;
  AnsiString asSource=Format("Ligne de tram n�%d", ARRAYOFCONST((Numero)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  if ((NbArrets<0)||(NbArrets>NBMAXARRETSBUSTRAMPARLIGNE))
   asMsgErr+=asSource+Format(": nombre d'arr�ts de tram incorrect (%d)\n", ARRAYOFCONST((NbArrets)));
  for(i=0; i<NbArrets; i++)
   if ((NumArret[i]<0)||(NumArret[i]>cv->NbArretsTram))
    asMsgErr+=asSource+Format(": num�ro du %d� arr�t de tram incorrect (%d)\n", ARRAYOFCONST((i+1, NumArret[i]))); // v3.03
 }
//-----------------------------------------------------------------------------
///////////// ICI FINISSENT LES METHODES DES CLASSES LIEES AU RESEAU DE TRAM //
//-----------------------------------------------------------------------------

bool place_taxi::Charge(int hfile)
 {
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &x, sizeof(x))&&
         FileRead(hfile, &y, sizeof(y));
 }
//-----------------------------------------------------------------------------
bool place_taxi::Sauve(int hfile)
 {
  int xc=x-cv->Xc, yc=y-cv->Yc; // v4.0.1
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, cv->CopieEnCours?&xc:&x, sizeof(x))&& // v4.0.1
         FileWrite(hfile, cv->CopieEnCours?&yc:&y, sizeof(y));  // v4.0.1
 }
//-----------------------------------------------------------------------------
void place_taxi::Verifie(AnsiString &asMsgErr)
 {
  AnsiString asSource=Format("Place Taxi n�%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
 }
//-----------------------------------------------------------------------------
bool place_taxi::EstQueueFile()
 {
  return cv->v[x][y].EstQueueFileTaxis();
 }
//-----------------------------------------------------------------------------
bool place_taxi::EstTeteFile()
 {
  return cv->v[x][y].EstTeteFileTaxis();
 }
//-----------------------------------------------------------------------------
int place_taxi::PlaceQueueFile() // Retourne 1+NumPlace si elle existe sinon 0
 {
  return cv->v[x][y].PlaceQueueFileTaxi();
 }
//-----------------------------------------------------------------------------
int place_taxi::PlaceTeteFile() // Retourne 1+NumPlace si elle existe sinon 0
 {
  return cv->v[x][y].PlaceTeteFileTaxi();
 }
//-----------------------------------------------------------------------------
direction place_taxi::DirPlaceSvtMemeFile()
 {
  int NumPlaceSvt;
  direction DirSvt=indefinie;
  for(int d=nord; (!DirSvt)&&(d<=ouest); d++)
   if ((NumPlaceSvt=cv->V(x,y,d).NumPlaceTaxi)&&
       (cv->PlaceTaxi[NumPlaceSvt-1].NumFile==NumFile))
    DirSvt=(direction)d;
  return DirSvt; // Si indefinie, il s'agit de la t�te de file !
 }
//-----------------------------------------------------------------------------
void taxi::Place(int p) // 0 <= p < NbPlacesTaxi
 {
  x=cv->PlaceTaxi[p].x;
  y=cv->PlaceTaxi[p].y;
  cv->v[x][y].NumTaxi=Numero;
  voie *v=&(cv->v[x][y]);
  if (cv->PlaceTaxi[p].EstTeteFile())
   {
    Situation=stAttente;
    for(int d=nord; (!Dir)&&(d<=ouest); d++)
     if (v->DirPoss&PossDir[(direction)d]) Dir=(direction)d;
   }
  else
   {
    Situation=stRetour;
    for(int d=nord; (!Dir)&&(d<=ouest); d++)
     if ((v->DirPoss&PossDir[(direction)d])&&
         (cv->V(x,y,d).NumPlaceTaxi)) Dir=(direction)d;
   }
 }
//-----------------------------------------------------------------------------
void taxi::CalculeProchaineDirection()
 {
  voie *v=&(cv->v[x][y]), *Voie;
  direction AncDir=Dir; // v2.2.4
  int OrdreDir[NBDIR]={0,0,0,0},
      i, j, ndp=NbDir[v->DirPoss];

  if ((Situation==stAttente)&&  // Si le taxi attend,
      (NbPietonsQuiSontMontes())) // On regarde d�j� s'il y a des pi�tons qui veulent monter...
   { // pour pouvoir partir...
    Situation=stDepart;
    TourDepartDrnCourse=cv->TourCrt;
   }
  Dir=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux files.
  // En cas d'�galit�, c'est le hasard : (N�Veh.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if (i!=j) // On d�gringole si distance sup�rieure.
     switch(Situation)
      {
       case stDepart: OrdreDir[i]+=(rand()%2); break; // Le hasard dans toute sa splendeur (en fait le taxi prom�ne le client)
       case stRetour: OrdreDir[i]+=((cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceTaxi&& // 1. File recherch�e
                                     (cv->PlaceTaxi[cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceTaxi-1].NumFile==NumFile))>
                                    (cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceTaxi&&
                                     (cv->PlaceTaxi[cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceTaxi-1].NumFile==NumFile)))||
                                   ((v->DistFileTaxi[NumFile][i]>v->DistFileTaxi[NumFile][j])|| // 2. Distance � la file
                                    ((v->DistFileTaxi[NumFile][i]==v->DistFileTaxi[NumFile][j])&&
                                     ((Dirdp[i][v->DirPoss]!=AncDir)|| // 3. En cas d'�galit�, pr�f�re garder la direction courante : v2.2.4. // v3.5 : || par && !
                                      ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)
                      break;
      }
  for(i=0; (!Dir)&&(i<5); i++)
   for(j=0; (!Dir)&&(j<ndp); j++)
    {
     Voie=&(cv->V(x,y,Dirdp[j][v->DirPoss]));
     if ((OrdreDir[j]==i)&&
         ((!v->ToutDroit)||    // Direction interdite si :     - obligation d'aller tout droit ET
          (DirDrnDepl==(DirDrnDepl==Dirdp[j][v->DirPoss])))&& // pas m�me direction que lors du dernier d�placement. v3.7.1 : Erreur !
         (((!Voie->NumVehicule)&&(!Voie->NumBus)&& // Sinon...
           (!Voie->NumTram)&&(!Voie->NumTaxi))|| //   - Il n'y a rien sur la route OU
          ((Situation==stRetour)&&               //   - Il est de retour et c'est la file du retour OU
           (Voie->NumPlaceTaxi&&(cv->PlaceTaxi[Voie->NumPlaceTaxi-1].NumFile==NumFile)))||
          (cv->TourCrt<=1+TourDrnDepl+cv->AttenteMaxVeh*(1+OrdreDir[j])))) // - Il est encore dans sa phase d'attente
      Dir=Dirdp[j][v->DirPoss];
    }

   // Si la direction est toujours ind�finie : on prend la meilleure direction possible
   if (!Dir)
    for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
     for(j=0; (!Dir)&&(j<ndp); j++)
      if (OrdreDir[j]==i)
       Dir=Dirdp[j][v->DirPoss];
 }
//-----------------------------------------------------------------------------
direction taxi::ProchaineDirectionAuCarrefour() // ATTENTION : DIR DOIT ETRE DEFINIE
 {
  voie *v=&(cv->V(x,y,Dir)); // Ici v est la prochaine case
  int OrdreDir[NBDIR]={0,0,0,0},
      i, j, ndp=NbDir[v->DirPoss];
  direction DirAuCarrefour=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux �tapes si la case est libre.
  // En cas d'�galit�, c'est le hasard : (N�Veh.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if (i!=j)
     switch(Situation)
      {
       case stDepart: OrdreDir[i]+=(rand()%2); break; // Le hasard dans toute sa splendeur (en fait le taxi prom�ne le client)
       case stRetour: OrdreDir[i]+=((cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceTaxi&& // 1. File recherch�e
                                     (cv->PlaceTaxi[cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceTaxi-1].NumFile==NumFile))>
                                    (cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceTaxi&&
                                     (cv->PlaceTaxi[cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceTaxi-1].NumFile==NumFile)))||
                                   ((v->DistFileTaxi[NumFile][i]>v->DistFileTaxi[NumFile][j])||
                                    ((v->DistFileTaxi[NumFile][i]==v->DistFileTaxi[NumFile][j])&&
                                     ((Dirdp[i][v->DirPoss]!=Dir)|| // En cas d'�galit�, pr�f�re garder la direction courante : v2.2.4.  // v3.5 : || par && !
                                      ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)
                      break;
      }
  for(i=0; (!DirAuCarrefour)&&(i<5); i++) // v3.5 : possibilit� de blocage si test n'est pas large (i<5)
   for(j=0; (!DirAuCarrefour)&&(j<ndp); j++)
    if ((OrdreDir[j]==i)&&
        ((!v->ToutDroit)||    // Direction interdite si :    - obligation d'aller tout droit ET
         (DirDrnDepl==(DirDrnDepl==Dirdp[j][v->DirPoss])))) // pas m�me direction que lors du dernier d�placement. v3.7.1 : Erreur !
    DirAuCarrefour=Dirdp[j][v->DirPoss];
  return DirAuCarrefour;
 }
//-----------------------------------------------------------------------------
bool taxi::PeutPasser()
 {
  voie *v=&(cv->v[x][y]);
  int NumFeuTaxi;
  return Dir&&
         ((v->Priorite[Dir-1]!=stop)||
          (cv->TourCrt-TourDrnDepl>=2))&&
         ((!(NumFeuTaxi=v->NumFeu[Dir-1]))||
          (cv->Feu[NumFeuTaxi-1].Etat<orange));
 }
//-----------------------------------------------------------------------------
void taxi::FaitDescendrePietons()
 {
  int i;
  direction d=ADroiteDe[Dir];
  voie *v=&cv->V(x,y,d);
  pieton *p;
  for(i=0; i<cv->NbPietons; i++)
   {
    p=cv->Pieton+i;
    if ((p->NumTaxi==Numero)&&
        (p->VeutDescendre||
         (p->VeutDescendre=(cv->ProbaArretTaxiDmd>(rand()%100)))))
     v->FaitDescendrePieton(d, i); // Si on peut pas faire descendre, il descendra une prochaine fois
   }
 }
//-----------------------------------------------------------------------------
void taxi::FaitMonterPieton(int NumPietonAFaireMonter)
 {
  pieton *p=cv->Pieton+NumPietonAFaireMonter;
  int xp=p->x, yp=p->y;
  if (NbPersonnes<cv->NbMaxPersonnesTaxi)
   {
    NbPersonnes++;
    cv->v[xp][yp].RetirePieton(NumPietonAFaireMonter);
    p->MonteDansTaxi(Numero); // v3.6
    frmSimulation->RedessineCase(xp, yp, false);
   }
 }
//-----------------------------------------------------------------------------
int taxi::NbPietonsQuiSontMontes() // retourne le nombre de pi�tons qui attendaient et qui sont mont�s
 {
  voie *v;
  pieton *p;
  for(int d=nord; (NbPersonnes<=cv->NbMaxPersonnesTaxi)&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    for(int i=0; (NbPersonnes<=cv->NbMaxPersonnesTaxi)&&(i<NBMAXPIETONSPARCASE); i++)
     {
      if (v->NumPieton[i]&&
          (p=cv->Pieton+v->NumPieton[i]-1)->AttendTaxi&&
          (p->NumFileTaxi-1==NumFile))
       FaitMonterPieton(v->NumPieton[i]-1);
     }
   }
  return NbPersonnes;
 }
//-----------------------------------------------------------------------------
void taxi::Verifie(AnsiString &asMsgErr)
 {
  AnsiString asSource=Format("Taxi n�%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": num�ro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  if (NumFile<=0)
   asMsgErr+=asSource+Format(": num�ro de file ind�fini ou incorrect (%d)\n", ARRAYOFCONST((NumFile)));
  VerifiePosition(asMsgErr, asSource, x, y, DOIT_ETRE_DEFINI);
 }
//-----------------------------------------------------------------------------

voie::voie()
 {
  int i;
  x=-1; y=-1;
  Initialise();
  DistEtape=NULL;
  Attente=NULL;
  Trafic=NULL;
  DistArretBus=NULL; // v3.0
  DistArretTram=NULL; // v3.5
  DistFileTaxi=NULL; // v3.6
 }
//-----------------------------------------------------------------------------
voie::~voie()
 {
  int i, j,
      nd=NbDir[DirPoss],
      ne=cv->NbEtapes,
      nab=cv->NbArretsBus, // v3.0
      nat=cv->NbArretsTram, // v3.5
      nft=cv->NbFilesTaxi; // v3.6
  if (DistEtape)
   {
    for(i=0; i<ne; i++)
     {
      for(j=0; j<nd; j++)
       delete[] DistEtape[i][j];
      delete[] DistEtape[i];
     }
    delete[] DistEtape;
   }
  DistEtape=NULL;
  if (DistArretBus)  // v3.0
   {
    for(i=0; i<nab; i++)
     delete[] DistArretBus[i];
    delete[] DistArretBus;
   }
  DistArretBus=NULL;
  if (DistArretTram)  // v3.5
   {
    for(i=0; i<nat; i++)
     delete[] DistArretTram[i];
    delete[] DistArretTram;
   }
  DistArretTram=NULL;
  if (DistFileTaxi)  // v3.6
   {
    for(i=0; i<nft; i++)
     delete[] DistFileTaxi[i];
    delete[] DistFileTaxi;
   }
  DistFileTaxi=NULL;
  if (Attente)
   {
    for(i=0; i<=ne; i++)
     delete[] Attente[i];
    delete[] Attente;
   }
  Attente=NULL;
  if (Trafic)
   {
    for(i=0; i<=ne; i++)
     delete[] Trafic[i];
    delete[] Trafic;
   }
  Trafic=NULL;
 }
//-----------------------------------------------------------------------------
void voie::Initialise()
 {
  int i;
  ToutDroit=false;
  PassagePietons=false;
  PassageBus=false; // v3.0
  for(i=0; i<4; i++)
   {
    Priorite[i]=a_droite;
    NumFeu[i]=0;
   }
  for(i=0; i<NBMAXPIETONSPARCASE; i++) NumPieton[i]=0; // v3.5 (sorti de la boucle pr�c�dente)
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++) LigneTram[i]=LigneBus[i]=false; // v3.5
  DirPoss=aucune;
  NbPietons=NumTaxi=NumPlaceTaxi=NumArretBus=NumArretTram=NumProchTaxi=NumProchTram=NumProchBus=NumProchVeh=NumEtape=NumTram=NumBus=NumVehicule=0; // v3.8 (Nature)
  Nature=voies;
  SensVoieTram=aucune_voie;
 }
//-----------------------------------------------------------------------------
void voie::Initialise(type_voie TypeVoie) // v3.5
 {
  if (TypeVoie&tvRoute)
   {
    for(int i=nord; i<=ouest; i++) // v3.7.2
     if ((DirPoss&PossDir[i])&&(!EstDirPossSensVoieTram(indefinie, (direction)(i-1))))
      Priorite[i-1]=a_droite;
    DirPoss=aucune;
    ToutDroit=PassageBus=false;
    for(int i=0; i<NBMAXLIGNESBUSTRAM; i++) LigneBus[i]=false;
    NumPlaceTaxi=NumArretBus=NumProchTaxi=NumProchBus=NumProchVeh=NumTaxi=NumBus=NumVehicule=0; // v3.7.2 : Pas l'�tape !
   }
  if (TypeVoie&tvVoieTram)
   {
    for(int i=nord; i<=ouest; i++) // v3.7.2
     if (EstDirPossSensVoieTram(indefinie, (direction)(i-1)))
      Priorite[i-1]=a_droite;
    SensVoieTram=aucune_voie;
    for(int i=0; i<NBMAXLIGNESBUSTRAM; i++) LigneTram[i]=false;
    NumArretTram=NumProchTram=NumTram=0;
   }
  SupprimePassagePietonsInvalide();
  for(int i=0; i<4; i++)
   if (ExisteVoieDansDirection(TypeVoie, direction(i+1)))
    {
     Priorite[i]=a_droite;
     NumFeu[i]=0;
    }
  NbPietons=0;
 }
//-----------------------------------------------------------------------------
voie *voie::v(direction d)
 { // v3.0
  return &cv->V(x,y,d);
 }
//-----------------------------------------------------------------------------
bool voie::PrepareCalculDistances() // v3.0 : inclut �galement la pr�paration des distances aux arr�ts de bus. v3.5... Et des trams ! v3.6...Et des taxis !
 {
  bool Ok=true;
  int i, j,
      nd=NbDir[DirPoss],
      ne=cv->NbEtapes,
      nab=cv->NbArretsBus,  // v3.0
      nat=cv->NbArretsTram, // v3.5
      nft=cv->NbFilesTaxi; // v3.6
  if (DistEtape)
   {
    for(i=0; i<ne; i++)
     {
      for(j=0; j<nd; j++)
       delete[] DistEtape[i][j];
      delete[] DistEtape[i];
     }
    delete[] DistEtape;
    DistEtape=NULL;
   }
  if (DistArretBus) // v3.0
   {
    for(i=0; i<nab; i++)
     delete[] DistArretBus[i];
    delete[] DistArretBus;
    DistArretBus=NULL;
   }
  if (DistArretTram) // v3.5
   {
    for(i=0; i<nat; i++)
     delete[] DistArretTram[i];
    delete[] DistArretTram;
    DistArretTram=NULL;
   }
  if (DistFileTaxi) // v3.6
   {
    for(i=0; i<nft; i++)
     delete[] DistFileTaxi[i];
    delete[] DistFileTaxi;
    DistFileTaxi=NULL;
   }
  if (nd>0)
   {
    if (ne>0)
     {
      if (Ok=(!!(DistEtape=new int**[ne]))) // D'abord le nombre d'�tapes
       for(i=0; Ok&&(i<ne); i++) // Puis le nombre de directions possibles
        {
         DistEtape[i]=NULL;
         if (Ok=(!!(DistEtape[i]=new int*[nd])))
          for(j=0; Ok&&(j<nd); j++) // v3.5
           if (Ok=(!!(DistEtape[i][j]=new int[2])))
            DistEtape[i][j][0]=DistEtape[i][j][1]=DIST_INDEFINIE;
        }
     }
    if (nab>0) // v3.0
     {
      if (Ok=(!!(DistArretBus=new int*[nab]))) // D'abord le nombre d'arr�ts de bus
       for(i=0; Ok&&(i<nab); i++) // Puis le nombre de directions possibles
        {
         DistArretBus[i]=NULL;
         if (Ok=(!!(DistArretBus[i]=new int[nd])))
          for(j=0; j<nd; j++) DistArretBus[i][j]=DIST_INDEFINIE;
        }
     }
    if (nft>0) // v3.6
     {
      if (Ok=(!!(DistFileTaxi=new int*[nft]))) // D'abord le nombre de files de taxi
       for(i=0; Ok&&(i<nft); i++) // Puis le nombre de directions possibles
        {
         DistFileTaxi[i]=NULL;
         if (Ok=(!!(DistFileTaxi[i]=new int[nd])))
          for(j=0; j<nd; j++) DistFileTaxi[i][j]=DIST_INDEFINIE;
        }
     }
   }
  nd=NbDirPossSensVoieTram(indefinie); // v3.5
  if ((nd>0)&&(nat>0)) // v3.5
   {
    if (Ok=(!!(DistArretTram=new int*[nat]))) // D'abord le nombre d'arr�ts de tram
     for(i=0; Ok&&(i<nat); i++) // Puis le nombre de directions possibles
      {
       DistArretTram[i]=NULL;
       if (Ok=(!!(DistArretTram[i]=new int[nd])))
        for(j=0; j<nd; j++) DistArretTram[i][j]=DIST_INDEFINIE;
      }
   }
  return Ok;
 }
//-----------------------------------------------------------------------------
bool voie::PrepareCalculAttenteTrafic()
 {
  bool Ok=true;
  int i, j, ne=cv->NbEtapes;
  if (Attente)
   {
    for(i=0; i<=ne; i++)
     delete[] Attente[i];
    delete[] Attente;
    Attente=NULL;
   }
  if (Trafic)
   {
    for(i=0; i<=ne; i++)
     delete[] Trafic[i];
    delete[] Trafic;
    Trafic=NULL;
   }
  if (ne>0)
   {
    if (Ok=(!!(Attente=new int*[ne+1])))
     for(i=0; Ok&&(i<=ne); i++)
      {
       Attente[i]=NULL;
       if (Ok=(!!(Attente[i]=new int[ne+1])))
        for(j=0; j<=ne; j++) Attente[i][j]=0;
      }
    if (Ok=Ok&&(!!(Trafic=new int*[ne+1])))
     for(i=0; Ok&&(i<=ne); i++)
      {
       Trafic[i]=NULL;
       if (Ok=(!!(Trafic[i]=new int[ne+1])))
        for(j=0; j<=ne; j++) Trafic[i][j]=0;
      }
   }
  return Ok;
 }
//-----------------------------------------------------------------------------
void voie::CalculeProchainVehiculeOuBusOuTramOuTaxi() // v3.6. Rq : N�cessite de conna�tre les 2 prochaines directions de chaque V�hicule/Bus/Tram
 {
  int d, MaxNivP=0,
      NumVV, // NUM�ro du V�hicule Voisin. v3.0
      NumBV, // NUM�ro du Bus Voisin. v3.0
      NumTV, // NUM�ro du Tram Voisin. v3.5
      NumXV, // NUM�ro du taXi Voisin. v3.6
      NivPriorite[5]={0,0,0,0,0};
  direction DirCrt, DirAuCarrefour;
  voie *v;

  NumProchTaxi=NumProchTram=NumProchBus=NumProchVeh=0; // Aucun par d�faut
  // 1. S'il y a un pi�ton, aucun ne peut arriver SAUF (v4.3) :
  if ((!frmSimulation->SimulationSanglante)&& // Mode Sanglant OU
      NbPietons&&                             // NbPietons=NbPi�tonsEcrases ALORS on peut rouler dessus (v4.3)
      (NbPietons!=(NumPieton[0]&&
                   (cv->Pieton[NumPieton[0]-1].Ecrase))+
                  (NumPieton[1]&&
                   (cv->Pieton[NumPieton[1]-1].Ecrase))))
   return;
  // 1bis. S'il y a d�j� un v�hicule et que ce n'est pas une �tape, aucun ne peut arriver
  if (NumVehicule&&(!NumEtape)) return;
  // 1ter. S'il y a un bus ou un tram ou un taxi, aucun ne peut arriver. v3.5
  if (NumBus||NumTram||NumTaxi) return;
  for(d=nord; d<=ouest; d++)
   {
    v=&(cv->V(x,y,d));
    NumVV=v->NumVehicule;
    NumXV=v->NumTaxi; // v3.6
    if (v->EstTeteBus()) NumBV=v->NumBus; else NumBV=0; // v3.0
    if (v->EstTeteTram()) NumTV=v->NumTram; else NumTV=0; // v3.5
    if (NumVV&& // 1. SOIT 1 Vehicule voisin arrivant sur la case ? Priorit� 1
        ((!PassageBus)|| // v3.1. Passage Bus interdit sauf...
         (cv->Vehicule[NumVV-1].NivPriorite>normal))) // pour les urgences
     {
      if (NivPriorite[d]=((cv->Vehicule[NumVV-1].Dir==InvDir[d])&& // 1 VEHICULE Qui arrive sur la case...
                          cv->TourDeDeplacementVehicule(NumVV-1)&& // Et que c'est son tour de d�placement... (multivitesse : version 1.5). v3.0.4 (chgtde nom)
                          ((!NumVehicule)|| // alors... Soit y a pas de v�hicule sur la case,
                           (NumEtape&&  // soit y en a une mais c'est une �tape...
                            (cv->Vehicule[NumVV-1].NumEtapeArrivee==NumEtape))))) // et c'est l'arriv�e
       {
        if (!cv->Vehicule[NumVV-1].NivPriorite)
         {
          // 2. Sont-elles oblig�es de s'arr�ter (stop non marqu� ou feu non vert) ? Priorit� 2
          NivPriorite[d]+=(((v->Priorite[InvDir[d]-1]==stop)&&(cv->Vehicule[NumVV-1].TourDrnDepl>cv->TourCrt-2L))||
                           ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat>vert)));
          // 3. Doivent-elles c�der le passage (clp ou stop marqu�) ? Priorit� 3
          NivPriorite[d]+=2*((v->Priorite[InvDir[d]-1]==cedez_le_passage)||
                             ((v->Priorite[InvDir[d]-1]==stop)&&(cv->TourCrt-cv->Vehicule[NumVV-1].TourDrnDepl>=2L)));
          // 4. V�hicules sur voie � priorit� � droite (ou feu inactif/vert) ? Priorit� 4
          NivPriorite[d]+=3*((v->Priorite[InvDir[d]-1]==a_droite)||
                             ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat<orange)));
         }
        else // 5. V�hicule prioritaire ? Urgence : Priorit� 6 ; Police : Priorit� 7
         NivPriorite[d]+=5+cv->Vehicule[NumVV-1].NivPriorite; // v2.2
       }
     }
    else // 1bis. SOIT 1 Bus voisin arrivant sur la case ? Priorit� 1. v3.0
     if (NumBV&&(!NumVehicule))
      {
       if (NivPriorite[d]=((cv->Bus[NumBV-1].Dir==InvDir[d])&& // 1 BUS Qui arrive sur la case...
                           cv->TourDeDeplacementBus(NumBV-1)&& // ET que c'est son tour de d�placement... (multivitesse)
                           (cv->TourCrt>=cv->Bus[NumBV-1].TourDepartArretSvt)&& // ET que c'est son tour de d�part vers le prochain arr�t
                           (!NumBus))) // et qu'y a pas de bus sur la case
        {
         // 2. Sont-ils oblig�s de s'arr�ter (stop non marqu� ou feu non vert) ? Priorit� 2
         NivPriorite[d]+=(((v->Priorite[InvDir[d]-1]==stop)&&(cv->Bus[NumBV-1].TourDrnDepl>cv->TourCrt-2L))||
                          ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat>vert)));
         // 3. Doivent-ils c�der le passage (clp ou stop marqu�) ? Priorit� 3
         NivPriorite[d]+=2*((v->Priorite[InvDir[d]-1]==cedez_le_passage)||
                            ((v->Priorite[InvDir[d]-1]==stop)&&(cv->TourCrt-cv->Bus[NumBV-1].TourDrnDepl>=2L)));
         // 4. Bus sur voie � priorit� � droite (ou feu inactif/vert) ? Priorit� 4
         NivPriorite[d]+=3*((v->Priorite[InvDir[d]-1]==a_droite)||
                            ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat<orange)));
        }
      }
     else // 1ter. SOIT 1 Tram voisin arrivant sur la case ? Priorit� 1. v3.5
      if (NumTV&&(!NumVehicule))
       {
        if (NivPriorite[d]=((cv->Tram[NumTV-1].Dir==InvDir[d])&& // 1 TRAM Qui arrive sur la case...
                            cv->TourDeDeplacementTram(NumTV-1)&& // ET que c'est son tour de d�placement... (multivitesse)
                            (cv->TourCrt>=cv->Tram[NumTV-1].TourDepartArretSvt)&& // ET que c'est son tour de d�part vers le prochain arr�t
                            (!NumTram))) // et qu'y a pas de tram sur la case
         {
          // 2. Sont-ils oblig�s de s'arr�ter (stop non marqu� ou feu non vert) ? Priorit� 2
          NivPriorite[d]+=(((v->Priorite[InvDir[d]-1]==stop)&&(cv->Tram[NumTV-1].TourDrnDepl>cv->TourCrt-2L))||
                           ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat>vert)));
          // 3. Doivent-ils c�der le passage (clp ou stop marqu�) ? Priorit� 3
          NivPriorite[d]+=2*((v->Priorite[InvDir[d]-1]==cedez_le_passage)||
                             ((v->Priorite[InvDir[d]-1]==stop)&&(cv->TourCrt-cv->Tram[NumTV-1].TourDrnDepl>=2L)));
          // 4. Tram sur voie � priorit� � droite (ou feu inactif/vert) ? Priorit� 4
          NivPriorite[d]+=3*((v->Priorite[InvDir[d]-1]==a_droite)||
                             ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat<orange)));
         }
       }
      else // 1ter. SOIT 1 Taxi voisin arrivant sur la case ? Priorit� 1. v3.5
       if (NumXV&&(!NumVehicule))
        {
         if (NivPriorite[d]=((cv->Taxi[NumXV-1].Dir==InvDir[d])&& // 1 TAXI Qui arrive sur la case...
                             cv->TourDeDeplacementTaxi(NumXV-1)&& // ET que c'est son tour de d�placement... (multivitesse)
                             (cv->Taxi[NumXV-1].Situation%2)&& // ET qu'il est sur le d�part ou le retour
                             (!NumTaxi))) // et qu'y a pas de taxi sur la case
          {
           // 2. Sont-ils oblig�s de s'arr�ter (stop non marqu� ou feu non vert) ? Priorit� 2
           NivPriorite[d]+=(((v->Priorite[InvDir[d]-1]==stop)&&(cv->Taxi[NumXV-1].TourDrnDepl>cv->TourCrt-2L))||
                            ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat>vert)));
           // 3. Doivent-ils c�der le passage (clp ou stop marqu�) ? Priorit� 3
           NivPriorite[d]+=2*((v->Priorite[InvDir[d]-1]==cedez_le_passage)||
                              ((v->Priorite[InvDir[d]-1]==stop)&&(cv->TourCrt-cv->Taxi[NumXV-1].TourDrnDepl>=2L)));
           // 4. Taxi sur voie � priorit� � droite (ou feu inactif/vert) ? Priorit� 4
           NivPriorite[d]+=3*((v->Priorite[InvDir[d]-1]==a_droite)||
                              ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat<orange)));
          }
        }
   }
  // 5. Entre v�hicules prioritaires (V.P.) :
  //    V.P. tournant � droite ? Priorit� 5
  //    V.P. allant tout droit et pas de V.P. venant de droite ? Priorit� 5
  //    V.P. tournant � gauche et pas de V.P. venant de la droite ou de devant ? Priorit� 5
  for(d=nord; d<=ouest; d++)
   if (NivPriorite[d]==4)
    {
     v=&(cv->V(x,y,d));
     NumVV=v->NumVehicule;
     NumXV=v->NumTaxi; // v3.6
     if (v->EstTeteBus()) NumBV=v->NumBus; else NumBV=0; // v3.0
     if (v->EstTeteTram()) NumTV=v->NumTram; else NumTV=0; // v3.5
     if (NumVV)
      {
       DirCrt=cv->Vehicule[NumVV-1].Dir;
       DirAuCarrefour=cv->Vehicule[NumVV-1].ProchaineDirectionAuCarrefour();
      }
     else
      if (NumBV) // v3.0
       {
        DirCrt=cv->Bus[NumBV-1].Dir;
        DirAuCarrefour=cv->Bus[NumBV-1].ProchaineDirectionAuCarrefour();
       }
      else
       if (NumTV) // v3.5
        {
         DirCrt=cv->Tram[NumTV-1].Dir;
         DirAuCarrefour=cv->Tram[NumTV-1].ProchaineDirectionAuCarrefour();
        }
       else
        if (NumXV) // v3.6
         {
          DirCrt=cv->Taxi[NumXV-1].Dir;
          DirAuCarrefour=cv->Taxi[NumXV-1].ProchaineDirectionAuCarrefour();
         }
        else
         {
          DirCrt=indefinie;
          DirAuCarrefour=indefinie;
         }
     NivPriorite[d]+=((DirAuCarrefour==ADroiteDe[DirCrt])||
                     ((DirAuCarrefour==DirCrt)&&
                      (NivPriorite[ADroiteDe[DirCrt]]<4))||
                     ((DirAuCarrefour==AGaucheDe[DirCrt])&&
                      (NivPriorite[ADroiteDe[DirCrt]]<4)&&
                      (NivPriorite[DirCrt]<4)));
    }
  for(d=nord; d<=ouest; d++)
   if (NivPriorite[d]>MaxNivP)
    {
     MaxNivP=NivPriorite[d];
     NumProchVeh=cv->V(x,y,d).NumVehicule;
     NumProchBus=cv->V(x,y,d).NumBus; // v3.0
     NumProchTram=cv->V(x,y,d).NumTram; // v3.5
     NumProchTaxi=cv->V(x,y,d).NumTaxi; // v3.6
    }
 }
//-----------------------------------------------------------------------------
void voie::DeplaceVehiculeOuBusOuTramOuTaxi() // v3.6 (Taxis)
 {
  if (NumProchVeh&&cv->Vehicule[NumProchVeh-1].PeutPasser())
   {  // Si le prochain v�hicule peut arriver sur la case...
    cv->v[cv->Vehicule[NumProchVeh-1].x][cv->Vehicule[NumProchVeh-1].y].NumVehicule=0; // Effac�e de la case d'origine
    frmSimulation->RedessineCase(cv->Vehicule[NumProchVeh-1].x, cv->Vehicule[NumProchVeh-1].y, false);
    if ((!NumEtape)||(NumEtape!=cv->Vehicule[NumProchVeh-1].NumEtapeArrivee))
     {
      cv->PlaceVehicule(x, y, NumProchVeh); // v2.2.7. Inclut les stats d'Attente/Trafic
      NumVehicule=NumProchVeh;
     }
    else // Etape : NumVehicule est r�serv� pour les v�hicules qui partent de l'�tape uniquement
     {
      cv->NbToursParcourus+= cv->TourCrt-
                             cv->Vehicule[NumProchVeh-1].TourDepart-
                             cv->Vehicule[NumProchVeh-1].NbToursRepos- // v2.2.4
                             1;
      cv->NbCasesParcourues+=cv->Vehicule[NumProchVeh-1].NbCasesParcourues+1;
      cv->PlaceVehicule(-1, -1, NumProchVeh); // v2.2.7. Inclut les stats d'Attente/Trafic
      cv->NbVehiculesArrives++;
     }
    cv->NbVehiculesDeplaces++;
    cv->Vehicule[NumProchVeh-1].NbCasesParcourues++;
    cv->Vehicule[NumProchVeh-1].TourDrnDepl=cv->TourCrt;
    frmSimulation->RedessineCase(x, y, false);
    cv->Vehicule[NumProchVeh-1].DirDrnDepl=cv->Vehicule[NumProchVeh-1].Dir;
    NumProchVeh=0;
   }
  if (NumProchBus&&cv->Bus[NumProchBus-1].PeutPasser()) // v3.0
   {  // Si le prochain bus peut arriver sur la case...
    cv->PlaceBus(x, y, NumProchBus);
    NumProchBus=0;
   }
  if (NumProchTram&&cv->Tram[NumProchTram-1].PeutPasser()) // v3.5
   {  // Si le prochain tram peut arriver sur la case...
    cv->PlaceTram(x, y, NumProchTram);
    NumProchTram=0;
   }
  if (NumProchTaxi&&cv->Taxi[NumProchTaxi-1].PeutPasser()) // v3.6
   {  // Si le prochain taxi peut arriver sur la case...
    cv->v[cv->Taxi[NumProchTaxi-1].x][cv->Taxi[NumProchTaxi-1].y].NumTaxi=0; // Effac�e de la case d'origine
    frmSimulation->RedessineCase(cv->Taxi[NumProchTaxi-1].x, cv->Taxi[NumProchTaxi-1].y, false);
    cv->PlaceVehiculeTaxi(x, y, NumProchTaxi);
    NumProchTaxi=0;
   }
 }
//-----------------------------------------------------------------------------
bool voie::PietonPeutAller(direction DirPieton) // v2.0
 {
  return (NbPietons<NBMAXPIETONSPARCASE)&&
         (!NumVehicule)&&
         (!NumBus)&& // v3.0
         (!NumTram)&& // v3.5
         (!NumTaxi)&& // v3.6
         (PassagePietons||
          ((NATURE(this)==trottoirs)&& // v3.8
           (Nature!=arbre)&&(Nature!=pelouse)&& // v3.9
           (!DirPoss)&&
           (!SensVoieTram)))&& // v3.5
         ((!NumPieton[0])||
          ((cv->Pieton[NumPieton[0]-1].DemiCase||
            (cv->Pieton[NumPieton[0]-1].Dir!=DirPieton))&&
           ((!cv->Pieton[NumPieton[0]-1].DemiCase)||
            (InvDir[cv->Pieton[NumPieton[0]-1].Dir]!=DirPieton))))&&
         ((!NumPieton[1])||
          ((cv->Pieton[NumPieton[1]-1].DemiCase||
            (cv->Pieton[NumPieton[1]-1].Dir!=DirPieton))&&
           ((!cv->Pieton[NumPieton[1]-1].DemiCase)||
            (InvDir[cv->Pieton[NumPieton[1]-1].Dir]!=DirPieton))));
 }
//-----------------------------------------------------------------------------
bool voie::FaitDescendrePieton(direction DirDescente, int NumPietonAFaireDescendre) // v3.6 (taxis)
 {
  int d;
  voie *Voie;
  pieton *p;
  bool APuDescendre;
  if ((NbPietons<NBMAXPIETONSPARCASE)&&PietonPeutAller(DirDescente))
   {
    AjoutePieton(NumPietonAFaireDescendre);
    p=cv->Pieton+NumPietonAFaireDescendre;
    if (p->NumBus) // v3.5
     {
      cv->Bus[p->NumBus-1].NbPersonnes--;
      p->NumBus=0;
     }
    if (p->NumTram) // v3.5
     {
      cv->Tram[p->NumTram-1].NbPersonnes--;
      p->NumTram=0;
     }
    if (p->NumTaxi) // v3.6
     {
      cv->Taxi[p->NumTaxi-1].NbPersonnes--;
      p->NumTaxi=0;
     }
    p->x=x; p->y=y; p->VeutDescendre=false;
    RedessineCase(false);
    return true;
   }
  else
   {
    for( APuDescendre=false,d=nord;
         (!APuDescendre)&&(d<=ouest);
         d++)
     {
      Voie=v((direction)d);
      if (Voie->PietonPeutAller((direction)d)) // v3.6
       APuDescendre=Voie->FaitDescendrePieton((direction)d, NumPietonAFaireDescendre);
     }
    return APuDescendre; 
   }
 }
//-----------------------------------------------------------------------------
bool voie::AjoutePieton(int NumPietonAAjouter) //v2.0
 {
  int i;
  if (NbPietons<NBMAXPIETONSPARCASE)
   {
    for(i=0; NumPieton[i]&&(i<NBMAXPIETONSPARCASE); i++);
    NumPieton[i]=NumPietonAAjouter+1;
    NbPietons++;
    return true;
   }
  else
   return false;
 }
//-----------------------------------------------------------------------------
bool voie::RetirePieton(int NumPietonARetirer) //v2.0
 {
  int i;
  if (NbPietons)
   {
    for(i=0; (NumPieton[i]!=NumPietonARetirer+1)&&(i<NBMAXPIETONSPARCASE); i++);
    if (i<NBMAXPIETONSPARCASE)
     {
      NumPieton[i]=0;
      NbPietons--;
      return true;
     }
    else
     return false;
   }
  else
   return false;
 }
//-----------------------------------------------------------------------------
void voie::DeplacePietons() //v3.5 : Inclut l'attente aux arr�ts de bus/tram, la mont�e et la descente du bus/tram 
 {
  bool DirTrv;
  int i, d, dd, n;
  pieton *p, *pv;
  direction NvDir;
  for(i=0; i<NBMAXPIETONSPARCASE; i++)
   if (NumPieton[i]&&
       (!cv->Pieton[NumPieton[i]-1].NumBus)&& // Ne doit pas �tre dans un bus, v3.0
       (!cv->Pieton[NumPieton[i]-1].NumTram)&& //             ni dans un tram, v3.5
       (!cv->Pieton[NumPieton[i]-1].NumTaxi)&& //             ni dans un taxi, v3.6
       (!cv->Pieton[NumPieton[i]-1].Ecrase)&& //              ni �cras�.       v4.3
       (cv->Pieton[NumPieton[i]-1].TourDrnDepl<cv->TourCrt))
    {
     p=&(cv->Pieton[NumPieton[i]-1]);
     NvDir=indefinie;
     if (p->ArretBusTrv&&(!PassagePietons)&&(n=cv->V(x,y,p->Dir).NumArretBus)) // Pas d'attente sur un passage pi�ton (v3.6)
      { // Si Arr�t de bus trouv� et qu'il arrive dessus alors on attend le bus (bloque le pi�ton)
       p->ArretBusTrv=false;
       p->NumArretBus=n;
       p->AttendBus=true;
       p->TourAttBus=cv->TourCrt;
      }
     if (p->ArretTramTrv&&(!PassagePietons)&&(n=cv->V(x,y,p->Dir).NumArretTram))// Pas d'attente sur un passage pi�ton (v3.6)
      { // Si Arr�t de tram trouv� et qu'il arrive dessus alors on attend le tram (bloque le pi�ton)
       p->ArretTramTrv=false;
       p->NumArretTram=n;
       p->AttendTram=true;
       p->TourAttTram=cv->TourCrt;
      }
     if (p->FileTaxiTrv)
      if (n=cv->V(x,y,p->Dir).NumPlaceTaxi)
       {
        if ((!PassagePietons)&&(cv->PlaceTaxi[n-1].EstTeteFile())) // v3.6.
         { // Phase 2 : Si File de taxi trouv�e ET qu'il arrive dessus et que c'est la t�te de la file ALORS il attend le taxi (bloque le pi�ton)
          p->NumFileTaxi=cv->PlaceTaxi[n-1].NumFile+1;
          p->FileTaxiTrv=false;
          p->AttendTaxi=true;
          p->TourAttTaxi=cv->TourCrt;
         }
        else
         { // Phase 1 : Recherche de la t�te de la file de taxi. ATTENTION ! p->NumFileTaxi>0 n'implique pas que le pi�ton attend un taxi comme les bus ou les trams.
          if (!p->NumFileTaxi) p->NumFileTaxi=cv->PlaceTaxi[n-1].NumFile+1; // On fixe la file � chercher
          p->ChercheFileTaxis(); // Change p->Dir pour se diriger vers la t�te de file
         }
       }
     if (p->AttendBus&&(p->TourAttBus+cv->NbMaxToursAttenteBus<cv->TourCrt)) // v3.0.
      { // Si attente de bus trop longue (param�tre), le pi�ton abandonne
       p->ArretBusTrv=false;
       p->NumArretBus=0;
       p->AttendBus=false;
       p->TourAttBus=0;
      }
     if (p->AttendTram&&(p->TourAttTram+cv->NbMaxToursAttenteTram<cv->TourCrt)) // v3.5.
      { // Si attente de tram trop longue (param�tre), le pi�ton abandonne
       p->ArretTramTrv=false;
       p->NumArretTram=0;
       p->AttendTram=false;
       p->TourAttTram=0;
      }
     if (p->AttendTaxi&&(p->TourAttTaxi+cv->NbMaxToursAttenteTaxi<cv->TourCrt)) // v3.6.
      { // Si attente de taxi trop longue (param�tre), le pi�ton abandonne
       p->FileTaxiTrv=false;
       p->NumFileTaxi=0;
       p->AttendTaxi=false;
       p->TourAttTaxi=0;
      }
     if ((!p->AttendBus)&& // Le pieton n'attend pas de bus
         (!p->AttendTram)&& // Le pieton n'attend pas de tram (v3.5)
         (!p->AttendTaxi)&& // Le pi�ton n'attend pas de taxi (v3.6)
         (!p->PsgPtTrv)&& // Le pi�ton ne se dirige pas d�j� vers un passage pi�tons ET
         (!p->ArretBusTrv)&& // Le pi�ton ne se dirige pas d�j� vers un arr�t de bus ET
         (!p->ArretTramTrv)&& // Le pi�ton ne se dirige pas d�j� vers un arr�t de tram (v3.5)
         (!p->FileTaxiTrv)) // Le pi�ton ne se dirige pas d�j� vers une t�te de file de taxi (v3.6)
      { // 1. Recherche de passage pi�tons
       if (cv->ProbaDirPsgPt&& // Si recherche de passage pi�tons il y a ET
           (NvDir=cv->CherchePassagePietons(x, y, (sens)(2-p->Dir%2)))&& // Passage pi�ton trouv� ET
           ((rand()%100)<cv->ProbaDirPsgPt)) // Probabilit� d'y aller (param�tre)
        { // Il va vers le passage pi�ton trouv�
         p->Dir=NvDir;
         p->PsgPtTrv=true; // Indique qu'il est en train d'aller vers un passage pi�ton (inhibe les futures recherches)
        }
       else // 2. Recherche d'arr�t de bus. v3.0
        if (cv->ProbaDirArretBus&& // Si recherche d'arret de bus il y a ET
            (NvDir=cv->ChercheArretBus(x, y, (sens)(2-p->Dir%2)))&& // Arret bus trouv� ET
            ((rand()%100)<cv->ProbaDirArretBus)) // Probabilit� d'y aller (param�tre)
         { // Il va vers l'arr�t de bus
          p->Dir=NvDir;
          p->ArretBusTrv=true; // Indique qu'il est en train d'aller vers un arr�t de bus (inhibe les futures recherches)
         }
        else // 3. Recherche d'arr�t de tram. v3.5
         if (cv->ProbaDirArretTram&& // Si recherche d'arret de tram il y a ET
             (NvDir=cv->ChercheArretTram(x, y, (sens)(2-p->Dir%2)))&& // Arret tram trouv� ET
             ((rand()%100)<cv->ProbaDirArretTram)) // Probabilit� d'y aller (param�tre)
          { // Il va vers l'arr�t de tram
           p->Dir=NvDir;
           p->ArretTramTrv=true; // Indique qu'il est en train d'aller vers un arr�t de tram (inhibe les futures recherches)
          }
         else // 4. Recherche de file de taxi. v3.6
          if (cv->ProbaDirFileTaxi&& // Si recherche de file de taxi il y a ET
              (NvDir=cv->CherchePlaceTaxi(x, y, (sens)(2-p->Dir%2)))&& // Place de taxi trouv�e ET
              ((rand()%100)<cv->ProbaDirFileTaxi)) // Probabilit� d'y aller (param�tre)
           { // Il va vers le t�te de file de taxi
            p->Dir=NvDir;
            p->FileTaxiTrv=true; // Indique qu'il est en train d'aller vers une t�te de file de taxi (inhibe les futures recherches)
           }
      }
     if ((!NvDir)&&(!p->AttendBus)&&(!p->AttendTram)&&(!p->AttendTaxi)) // La direction n'a pas chang� et aucun bus/tram/taxi attendu (il marche tranquillement) v3.6 (taxi)
      if (p->DemiCase) // Demi-case et m�me direction : il sort de la case
       if (cv->V(x,y,p->Dir).PietonPeutAller((direction)p->Dir))
        cv->DeplacePieton(NumPieton[i]-1, (x+dx[p->Dir])%cv->NbX, (y+dy[p->Dir])%cv->NbY, (direction)p->Dir);
       else // Peut pas sortir : on cherche une autre direction � gauche ou � droite (au sort)
        {
         if (cv->TourCrt-cv->Pieton[NumPieton[i]-1].TourDrnDepl>1+cv->AttenteMaxVeh/2)
          { // S'il a assez attendu (Param�tre AttenteV�hicule/2)
           for(DirTrv=false,dd=1-2*(rand()%2),d=2-dd; (!DirTrv)&&(d&&(d<NBDIR)); d+=dd)
            {
             NvDir=(direction)(1+(p->Dir+d-1)%NBDIR); // � Gauche ou � droite
             if (DirTrv=cv->V(x,y,NvDir).PietonPeutAller(NvDir))
              {
               p->AnnuleRechercheEnCours(); // Toute recherche est annul�e car la direction a chang� !
               cv->DeplacePieton(NumPieton[i]-1, (x+dx[NvDir])%cv->NbX, (y+dy[NvDir])%cv->NbY, NvDir);
              }
            }
          }
        }
      else // Ben c'est la demi-case...
       {// On regarde si on peut passer la demi-case !
        if (NumPieton[1-i])
         {
          pv=&(cv->Pieton[NumPieton[1-i]-1]); // pv comme pi�ton voisin
          if ((((pv->Dir==p->Dir)&&
                pv->DemiCase)||
               ((pv->Dir==InvDir[p->Dir])&&
                (!pv->DemiCase)))&&
              (cv->TourCrt-cv->Pieton[NumPieton[i]-1].TourDrnDepl>1+cv->AttenteMaxVeh/2))
            // On choisit une direction � gauche ou � droite (s�re) s'il a assez attendu
           {
            p->AnnuleRechercheEnCours(); // Toute recherche est annul�e car la direction a chang� !
            p->Dir=(direction)(1+(p->Dir+1+2*(rand()%2))%NBDIR);
           }
         }
        p->DemiCase++;
        p->DemiCasesParcourues++; // v3.0
        p->TourDrnDepl=cv->TourCrt;
       }
    }
  frmSimulation->RedessineCase(x, y, false);
 }
//-----------------------------------------------------------------------------
void voie::RetireArretBus() // v3.0
 {
  int Numero=NumArretBus,
      d;
  NumArretBus=0;
  if (frmSimulation) frmSimulation->RedessineCase(x,y,true);
  for(d=nord; d<=ouest; d++)
   if (cv->V(x,y,d).NumArretBus==Numero)
    cv->V(x,y,d).RetireArretBus();
 }
//-----------------------------------------------------------------------------
void voie::RetireArretTram() // v3.5
 {
  int Numero=NumArretTram,
      d;
  NumArretTram=0;
  if (frmSimulation) frmSimulation->RedessineCase(x,y,true);
  for(d=nord; d<=ouest; d++)
   if (cv->V(x,y,d).NumArretTram==Numero)
    cv->V(x,y,d).RetireArretTram();
 }
//-----------------------------------------------------------------------------
void voie::RetirePlaceTaxi() // v3.6
 {
  NumPlaceTaxi=0;
  if (frmSimulation) frmSimulation->RedessineCase(x,y,true);
 }
//-----------------------------------------------------------------------------

bool voie::EstTeteArretBus() // v3.0
 {
  return NumArretBus&&
         (cv->ArretBus[NumArretBus-1].x==x)&&
         (cv->ArretBus[NumArretBus-1].y==y);
 }
//-----------------------------------------------------------------------------
bool voie::EstTeteArretTram() // v3.5
 {
  return NumArretTram&&
         (cv->ArretTram[NumArretTram-1].x==x)&&
         (cv->ArretTram[NumArretTram-1].y==y);
 }
//-----------------------------------------------------------------------------
bool voie::EstTeteArretBus(int NumeroArretBus) // v3.0
 {
  return (NumArretBus==NumeroArretBus)&&
         (cv->ArretBus[NumeroArretBus-1].x==x)&&
         (cv->ArretBus[NumeroArretBus-1].y==y);
 }
//-----------------------------------------------------------------------------
bool voie::EstTeteArretTram(int NumeroArretTram) // v3.5
 {
  return (NumArretTram==NumeroArretTram)&&
         (cv->ArretTram[NumeroArretTram-1].x==x)&&
         (cv->ArretTram[NumeroArretTram-1].y==y);
 }
//-----------------------------------------------------------------------------
bool voie::EstTeteBus() // v3.0
 {
  return NumBus&&
         (cv->Bus[NumBus-1].x==x)&&
         (cv->Bus[NumBus-1].y==y);
 }
//-----------------------------------------------------------------------------
bool voie::EstTeteTram() // v3.5
 {
  return NumTram&&
         (cv->Tram[NumTram-1].x==x)&&
         (cv->Tram[NumTram-1].y==y);
 }
//-----------------------------------------------------------------------------
bool voie::EstQueueFileTaxis() // v3.6
 {
  bool EstQueueFile=(NumPlaceTaxi>0);
  voie *v;
  for(int d=nord; EstQueueFile&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    EstQueueFile=((v->DirPoss&InvPossDir[d])==aucune)||(!v->NumPlaceTaxi);
   }
  return EstQueueFile;
 }
//-----------------------------------------------------------------------------
bool voie::EstTeteFileTaxis() // v3.6
 {
  bool EstTeteFile=(NumPlaceTaxi>0);
  voie *v;
  for(int d=nord; EstTeteFile&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    EstTeteFile=(((DirPoss&PossDir[d])==aucune)||(!v->NumPlaceTaxi));
   }
  return EstTeteFile;
 }
//-----------------------------------------------------------------------------
int voie::PlaceQueueFileTaxi() // v3.6. Retourne 1+NumPlace si elle existe sinon 0
 {
  int NumPlaceQueue=0;
  voie *v;
  if (!NumPlaceTaxi) return 0; // N'est pas une place de taxi
  for(int d=nord; (!NumPlaceQueue)&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    if ((v->DirPoss&InvPossDir[d])&&v->NumPlaceTaxi)
     NumPlaceQueue=v->PlaceQueueFileTaxi();
   }
  if (!NumPlaceQueue)
   return NumPlaceTaxi; // Pas d'autre place trouv�e alors c'est la queue
  else
   return NumPlaceQueue; // Sinon c'est celle qui a �t� trouv�e
 }
//-----------------------------------------------------------------------------
int voie::PlaceTeteFileTaxi() // v3.6. Retourne 1+NumPlace si elle existe sinon 0
 {
  int NumPlaceTete=0;
  voie *v;
  if (!NumPlaceTaxi) return 0; // N'est pas une place de taxi
  if (EstTeteFileTaxis()) return NumPlaceTaxi;
  for(int d=nord; (!NumPlaceTete)&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    if ((DirPoss&PossDir[d])&&v->NumPlaceTaxi)
     NumPlaceTete=v->PlaceTeteFileTaxi();
   }
  if (!NumPlaceTete)
   return NumPlaceTaxi; // Pas d'autre place trouv�e alors c'est la t�te
  else
   return NumPlaceTete; // Sinon c'est celle qui a �t� trouv�e
 }
//-----------------------------------------------------------------------------
bool voie::ExistePlusieursQueuesFileTaxis() // v3.6
 {
  int NbQueues=0;
  voie *v;
  if (NumPlaceTaxi)
   for(int d=nord; d<=ouest; d++)
    {
     v=&(cv->V(x,y,d));
     NbQueues+=((v->DirPoss&InvPossDir[d])&&v->NumPlaceTaxi);
    } 
  return NbQueues>1;
 }
//-----------------------------------------------------------------------------
bool voie::ExistePlusieursTetesFileTaxis() // v3.6
 {
  int NbTetes=0;
  voie *v;
  if (NumPlaceTaxi)
   for(int d=nord; d<=ouest; d++)
    {
     v=&(cv->V(x,y,d));
     NbTetes+=((v->DirPoss&PossDir[d])&&v->NumPlaceTaxi);
    }
  return NbTetes>1;
 }
//-----------------------------------------------------------------------------
void voie::DefinitArretBus(int n) // v3.0
 {
  cv->DefinitArretBus(n, x, y);
 }
//-----------------------------------------------------------------------------
void voie::DefinitArretTram(int n) // v3.5
 {
  cv->DefinitArretTram(n, x, y);
 }
//-----------------------------------------------------------------------------
void voie::RedessineCasesArretBus(direction d0) // v3.0
 {
  if (frmSimulation) frmSimulation->RedessineCase(x,y,false);
  if (d0)
   {
    if (cv->V(x,y,d0).NumArretBus==NumArretBus)
     cv->V(x,y,d0).RedessineCasesArretBus(d0);
   }
  else
   for(int d=nord; d<=ouest; d++)
    if (cv->V(x,y,d).NumArretBus==NumArretBus)
     cv->V(x,y,d).RedessineCasesArretBus((direction)d);
 }
//-----------------------------------------------------------------------------
void voie::RedessineCasesArretTram(direction d0) // v3.5
 {
  if (frmSimulation) frmSimulation->RedessineCase(x,y,false);
  if (d0)
   {
    if (cv->V(x,y,d0).NumArretTram==NumArretTram)
     cv->V(x,y,d0).RedessineCasesArretTram(d0);
   }
  else
   for(int d=nord; d<=ouest; d++)
    if (cv->V(x,y,d).NumArretTram==NumArretTram)
     cv->V(x,y,d).RedessineCasesArretTram((direction)d);
 }
//-----------------------------------------------------------------------------
bool voie::EstDepotBus() // v3.0
 {
  return (x==cv->DepotBus.x)&&(y==cv->DepotBus.y);
 }
//-----------------------------------------------------------------------------
void voie::CalculeDistanceEtape(int e, int DistSansPsgBus, int DistAvecPsgBus, direction DirOrig) // 0 <= e < NbEtapes
 {
  if (DirOrig)
   { // v3.5
    if (DistEtape[e][NumDirdp[DirOrig][DirPoss]][SANSPSGBUS]>DistSansPsgBus)
     DistEtape[e][NumDirdp[DirOrig][DirPoss]][SANSPSGBUS]=DistSansPsgBus;
    if (DistEtape[e][NumDirdp[DirOrig][DirPoss]][AVECPSGBUS]>DistAvecPsgBus)
     DistEtape[e][NumDirdp[DirOrig][DirPoss]][AVECPSGBUS]=DistAvecPsgBus;
   }
  for(int d=nord; d<=ouest; d++)
   { // ATTENTION, faire un saut � v(x,y,d,2) si obligation d'aller tout droit car risque qu'il ne soit pas d�fini plus tard par isolation (on ne passe pas deux fois sur une m�me case)
    int DistCrtAvecPsgBus=DistAvecPsgBus,
        DistCrtSansPsgBus=DistSansPsgBus; // Distances par d�faut (v3.9.1)
    voie *VoieCrt=v((direction)d), *Voie2Cases=&(cv->V_(x,y,2,d));
    if (ToutDroit&&((DirPoss&InvPossDir[d])==InvPossDir[d])) // SI ToutDroit ET d est une direction possible (Tout Droit) ALORS on ne prend que la distance de la case d'en face (v3.9.1)
     {
      voie *VoieOpposee=v(InvDir[d]);
      DistCrtAvecPsgBus=VoieOpposee->DistEtape[e][NumDirdp[InvDir[d]][VoieOpposee->DirPoss]][AVECPSGBUS]; // distance depuis la case d'en face (avec passage bus)
      DistCrtSansPsgBus=VoieOpposee->DistEtape[e][NumDirdp[InvDir[d]][VoieOpposee->DirPoss]][SANSPSGBUS]; // distance depuis la case d'en face (sans passage bus)
      if (DistCrtAvecPsgBus!=DIST_INDEFINIE) DistCrtAvecPsgBus++; // Si distance d�finie, on l'incr�mente de 1
      if (DistCrtSansPsgBus!=DIST_INDEFINIE) DistCrtSansPsgBus++; // Si distance d�finie, on l'incr�mente de 1
     }
    if (VoieCrt->PassageBus)
     {
      if (((VoieCrt->DirPoss&InvPossDir[d])==InvPossDir[d])&& // Si VoieCrt pointe sur l'�tape ET
          (VoieCrt->DistEtape[e][NumDirdp[InvDir[d]][VoieCrt->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+1))
       VoieCrt->CalculeDistanceEtape( e,
                                      DIST_INDEFINIE,
                                      DistCrtAvecPsgBus+1,
                                      InvDir[d]);
      if ((VoieCrt->ToutDroit&& // v3.9.1 (On traite le ToutDroit : 2 cases)
          ((Voie2Cases->DirPoss&InvPossDir[d])==InvPossDir[d])&&
          (Voie2Cases->DistEtape[e][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+2)))
       Voie2Cases->CalculeDistanceEtape( e,
                                         DIST_INDEFINIE,
                                         DistCrtAvecPsgBus+2,
                                         InvDir[d]);
     }
    else
     {
      if (((VoieCrt->DirPoss&InvPossDir[d])==InvPossDir[d])&&
          ((VoieCrt->DistEtape[e][NumDirdp[InvDir[d]][VoieCrt->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+1)||
           (VoieCrt->DistEtape[e][NumDirdp[InvDir[d]][VoieCrt->DirPoss]][SANSPSGBUS]>DistCrtSansPsgBus+1)))
       VoieCrt->CalculeDistanceEtape( e,
                                      (DistCrtSansPsgBus==DIST_INDEFINIE)?DIST_INDEFINIE:DistCrtSansPsgBus+1,
                                      DistCrtAvecPsgBus+1,
                                      InvDir[d]);
      if (VoieCrt->ToutDroit&& // v3.9.1 (On traite le ToutDroit : 2 cases)
          ((Voie2Cases->DirPoss&InvPossDir[d])==InvPossDir[d])&&
          ((Voie2Cases->DistEtape[e][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+2)||
           (Voie2Cases->DistEtape[e][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]][SANSPSGBUS]>DistCrtSansPsgBus+2)))
       Voie2Cases->CalculeDistanceEtape( e,
                                         (DistCrtSansPsgBus==DIST_INDEFINIE)?DIST_INDEFINIE:DistCrtSansPsgBus+2,
                                         DistCrtAvecPsgBus+2,
                                         InvDir[d]);
     }
   }
 }
//-----------------------------------------------------------------------------
void voie::CalculeDistanceArretBus(int ab, int Distance, direction DirOrig) // 0 <= ab < NbArretBus. v3.0
 {
  if (DirOrig) DistArretBus[ab][NumDirdp[DirOrig][DirPoss]]=Distance;
  for(int d=nord; d<=ouest; d++)
   {
    voie *VoieCrt=v((direction)d), *Voie2Cases=&(cv->V_(x,y,2,d));
    if (((VoieCrt->DirPoss&InvPossDir[d])==InvPossDir[d])&& // Si VoieCrt pointe sur l'arr�t de bus ET
        (VoieCrt->DistArretBus[ab][NumDirdp[InvDir[d]][VoieCrt->DirPoss]]>Distance+1)) // Distance ind�finie
     VoieCrt->CalculeDistanceArretBus(ab, Distance+1, InvDir[d]); // On lance le calcul de distance
    if ((VoieCrt->ToutDroit&& // v3.9.1 (On traite le ToutDroit : 2 cases)
        ((Voie2Cases->DirPoss&InvPossDir[d])==InvPossDir[d])&&
        (Voie2Cases->DistArretBus[ab][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]]>Distance+2)))
     Voie2Cases->CalculeDistanceArretBus(ab, Distance+2, InvDir[d]);
   }
 }
//-----------------------------------------------------------------------------
void voie::CalculeDistanceArretTram(int at, int Distance, direction DirOrig) // 0 <= at < NbArretTram. v3.5
 {
  if (DirOrig) DistArretTram[at][NumDirPossSensVoieTram(indefinie, DirOrig)]=Distance;
  for(int d=nord; d<=ouest; d++)
   {
    if ((DirOrig&&EstDirPossSensVoieTram((direction)d, DirOrig))|| // Si une voie va vers DirOrig (d�finie) depuis d OU
        (!DirOrig)&&EstDirPossSensVoieTram(indefinie, (direction)d)) // on part d'un arr�t de tram (DirOrig==indefinie) et on regarde toutes les directions
     {
      voie *VoieCrt=v((direction)d);
      if (VoieCrt->DistArretTram[at][VoieCrt->NumDirPossSensVoieTram(indefinie, InvDir[d])]>Distance+1) // Distance ind�finie
       VoieCrt->CalculeDistanceArretTram(at, Distance+1, InvDir[d]); // On lance le calcul de distance
     }
   }
 }
//-----------------------------------------------------------------------------
void voie::CalculeDistanceFileTaxi(int ft, int Distance, direction DirOrig) // 0 <= ft < NbFilesTaxi. v3.6
 {
  if (DirOrig) DistFileTaxi[ft][NumDirdp[DirOrig][DirPoss]]=Distance;
  for(int d=nord; d<=ouest; d++)
   {
    voie *VoieCrt=v((direction)d), *Voie2Cases=&(cv->V_(x,y,2,d));
    if (((VoieCrt->DirPoss&InvPossDir[d])==InvPossDir[d])&& // Si VoieCrt pointe sur la file de taxi ET
        (VoieCrt->DistFileTaxi[ft][NumDirdp[InvDir[d]][VoieCrt->DirPoss]]>Distance+1)) // Distance ind�finie
     VoieCrt->CalculeDistanceFileTaxi(ft, Distance+1, InvDir[d]); // On lance le calcul de distance
    if ((VoieCrt->ToutDroit&& // v3.9.1 (On traite le ToutDroit : 2 cases)
        ((Voie2Cases->DirPoss&InvPossDir[d])==InvPossDir[d])&&
        (Voie2Cases->DistFileTaxi[ft][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]]>Distance+2)))
     Voie2Cases->CalculeDistanceFileTaxi(ft, Distance+2, InvDir[d]);
   }
 }
//-----------------------------------------------------------------------------
void voie::InitialiseInfosLignesBus()
 {
  for(int i=0; i<NBMAXLIGNESBUSTRAM; i++)
   LigneBus[i]=false; // v3.0.3
 }
//-----------------------------------------------------------------------------
void voie::InitialiseInfosLignesTram()
 {
  for(int i=0; i<NBMAXLIGNESBUSTRAM; i++)
   LigneTram[i]=false;
 }
//-----------------------------------------------------------------------------
void voie::ModifieSensVoieTram(direction DirOrig, direction DirDest) // v3.5
 {
  SensVoieTram^=SensVoieTramDir[DirOrig][DirDest];
  RedessineCase(true);
 }
//-----------------------------------------------------------------------------
direction voie::DirSensVoieTram(direction DirOrigine, int iDir) // v3.5
 { // ATTENTION : 0<=iDir<=3 (0 = premi�re, etc.)
  int n=0;
  direction DirTrv=indefinie;
  for(int DirCrt=nord; (!DirTrv)&&(DirCrt<=ouest); DirCrt++)
   if ((EstDirPossSensVoieTram(DirOrigine, (direction)DirCrt))&&(iDir==n++))
    DirTrv=(direction)DirCrt;
  return DirTrv;
 }
//-----------------------------------------------------------------------------
bool voie::EstDirPossSensVoieTram(direction DirOrigine, direction DirDestination) // v3.5
 {
  int i;
  for(i=32;
      i&&(!DirPossSensVoieTramBase[SensVoieTramBase[SensVoieTram&i]][DirOrigine][DirDestination]);
      i/=2);
  return i>0;
 }
//-----------------------------------------------------------------------------
int voie::NumDirPossSensVoieTram(direction DirOrigine, direction DirDestination) // v3.5
 { // Attention : SUPPOSE DEJA que DirDestination est une direction possible de voie::SensVoieTram
  int i=0;
  for(int DirCrt=nord; (DirDestination!=DirCrt)&&(DirCrt<=ouest); DirCrt++)
   if (EstDirPossSensVoieTram(DirOrigine, (direction)DirCrt)) i++;
  return i;
 }
//-----------------------------------------------------------------------------
int voie::NbDirPossSensVoieTram(direction DirOrigine) // v3.5
 {
  int n=0;
  for(int DirDestination=nord; DirDestination<=ouest; DirDestination++)
   if (EstDirPossSensVoieTram(DirOrigine, (direction)DirDestination)) n++;
  return n;
 }
//-----------------------------------------------------------------------------
bool voie::SupprimePassagePietonsInvalide() // v3.5
 {
  if (PassagePietons&&(!cv->SensPassagePietonsPossible(x,y)))
   {
    PassagePietons=false;
    return true;
   }
  else return false;
 }
//-----------------------------------------------------------------------------
inline bool voie::ExisteVoieDansDirection(type_voie TypeVoie, direction d) // v3.5 // condition n�cessaire d>indefinie
 {
  return ((TypeVoie&tvRoute)&&(DirPoss&PossDir[d]))||
         ((TypeVoie&tvVoieTram)&&EstDirPossSensVoieTram(indefinie, d));
 }
//-----------------------------------------------------------------------------
void voie::DefinitNature(nature NvNature, bool Ecraser) // v3.8
 {
  int d;
  if ((!Ecraser)&&(Nature>voies)) return;
  for( d=nord;
       ((!(DirPoss&PossDir[d]))&&
        (!(v((direction)d)->DirPoss&InvPossDir[d])))&&
       (d<=ouest); d++);
  if ((d>ouest)&&(!SensVoieTram))
   {
    Nature=NvNature;
    RedessineCase(true);
    frmSimulation->SimulationModifiee=true;
   }
 }
//-----------------------------------------------------------------------------
void voie::TuePietons() // v4.3
 {
  int NbPietonsEcrases=0;
  for(int i=0; i<NBMAXPIETONSPARCASE; i++)
   if (NumPieton[i])
    {
     NbPietonsEcrases++;
     cv->Pieton[NumPieton[i]-1].SeFaitEcraser();
    }
  if (NbPietonsEcrases) RedessineCase(false);
 }
//-----------------------------------------------------------------------------
void voie::RedessineCase(bool EffaceFond) // v3.0
 {
  frmSimulation->RedessineCase(x, y, EffaceFond);
 }
//-----------------------------------------------------------------------------
bool voie::Charge(int hfile)
 {
  int i;
  bool Ok;
  Ok=FileRead(hfile, &x, sizeof(x))&&
     FileRead(hfile, &y, sizeof(y))&&
     FileRead(hfile, &DirPoss, sizeof(DirPoss))&&
     ((VersionFichier<0x350)|| // v3.5
      (FileRead(hfile, &SensVoieTram, sizeof(SensVoieTram))))&&
     ((VersionFichier<0x380)|| // v3.8
      (FileRead(hfile, &Nature, sizeof(Nature))))&&
     FileRead(hfile, &NumEtape, sizeof(NumEtape))&&
     FileRead(hfile, &ToutDroit, sizeof(ToutDroit))&&
     FileRead(hfile, &PassagePietons, sizeof(PassagePietons))&& // v2.0
     ((VersionFichier<0x300)|| // v3.0
      (FileRead(hfile, &PassageBus, sizeof(PassageBus))&&
       FileRead(hfile, &NumArretBus, sizeof(NumArretBus))))&&
     ((VersionFichier<0x350)|| // v3.5
      (FileRead(hfile, &NumArretTram, sizeof(NumArretTram))));
     ((VersionFichier<0x360)|| // v3.6
      (FileRead(hfile, &NumPlaceTaxi, sizeof(NumPlaceTaxi))));
  for(i=0; Ok&&(i<4); i++)
   Ok=FileRead(hfile, &(Priorite[i]), sizeof(Priorite[i]))&&
      FileRead(hfile, &(NumFeu[i]), sizeof(NumFeu[i]));
  return Ok;
 }
//-----------------------------------------------------------------------------
bool voie::Sauve(int hfile)
 {
  int i,
      xc=x-cv->Xc, yc=y-cv->Yc; // v4.0.1
  bool Ok;
  Ok=FileWrite(hfile, cv->CopieEnCours?&xc:&x, sizeof(x))&&
     FileWrite(hfile, cv->CopieEnCours?&yc:&y, sizeof(y))&&
     FileWrite(hfile, &DirPoss, sizeof(DirPoss))&&
     FileWrite(hfile, &SensVoieTram, sizeof(SensVoieTram))&&
     FileWrite(hfile, &Nature, sizeof(Nature))&&
     FileWrite(hfile, &NumEtape, sizeof(NumEtape))&&
     FileWrite(hfile, &ToutDroit, sizeof(ToutDroit))&&
     FileWrite(hfile, &PassagePietons, sizeof(PassagePietons)); // v2.0
     FileWrite(hfile, &PassageBus, sizeof(PassageBus))&& // v3.0
     FileWrite(hfile, &NumArretBus, sizeof(NumArretBus))&& // v3.0
     FileWrite(hfile, &NumArretTram, sizeof(NumArretTram)); // v3.5
     FileWrite(hfile, &NumPlaceTaxi, sizeof(NumPlaceTaxi)); // v3.6
  for(i=0; Ok&&(i<4); i++)
   Ok=FileWrite(hfile, &(Priorite[i]), sizeof(Priorite[i]))&&
      FileWrite(hfile, &(NumFeu[i]), sizeof(NumFeu[i]));
  return Ok;
 }
//-----------------------------------------------------------------------------
void voie::Verifie(AnsiString &asMsgErr)
 {
  int i, xx, yy;
  AnsiString asSource=Format("Case (%d,%d)", ARRAYOFCONST((x, y)));
  VerifiePosition(asMsgErr, asSource, x, y, DOIT_ETRE_DEFINI);
  VerifieDirPoss(asMsgErr, asSource, DirPoss);
  for(i=0; i<4; i++)
   {
    VerifiePriorite(asMsgErr, asSource+" ("+asDir[i+1]+")", Priorite[i]);
    if (NumFeu[i]&&(Priorite[i]!=feux))
     asMsgErr+=asSource+Format(": num�ro de feu %s mais priorit� diff�rente de Feu (%d)\n", ARRAYOFCONST((asDir[i+1], Priorite[i])));
    if ((NumFeu[i]<0)||(NumFeu[i]>cv->NbFeux))
     asMsgErr+=asSource+Format(": num�ro de feu %s incorrect (%d)\n", ARRAYOFCONST((asDir[i+1], NumFeu[i])));
    else
     if (NumFeu[i])
      {
       cv->Feu[NumFeu[i]-1].Verifie(asMsgErr, asSource+Format(" Feu %s", ARRAYOFCONST((asDir[i+1]))));
       if ((x!=(xx=cv->Feu[NumFeu[i]-1].x))||(y!=(yy=cv->Feu[NumFeu[i]-1].y)))
        asMsgErr+=asSource+Format(": coordonn�es du feu %s (%d,%d) diff�rentes des coordonn�es de la case\n", ARRAYOFCONST((asDir[i+1], xx, yy)));
      }
   }
  // Compl�ment des contr�les (v3.6)
  if ((NumEtape<0)||(NumEtape>cv->NbEtapes))
   asMsgErr+=asSource+Format(": num�ro de place de taxi incorrect (%d)\n", ARRAYOFCONST((NumPlaceTaxi)));
  if ((NumArretBus<0)||(NumArretBus>cv->NbArretsBus))
   asMsgErr+=asSource+Format(": num�ro d'arr�t de bus incorrect (%d)\n", ARRAYOFCONST((NumArretBus)));
  if ((NumArretTram<0)||(NumArretTram>cv->NbArretsTram))
   asMsgErr+=asSource+Format(": num�ro d'arr�t de tram incorrect (%d)\n", ARRAYOFCONST((NumArretTram)));
  if ((NumPlaceTaxi<0)||(NumPlaceTaxi>cv->NbPlacesTaxi))
   asMsgErr+=asSource+Format(": num�ro de place de taxi incorrect (%d)\n", ARRAYOFCONST((NumPlaceTaxi)));
 }
//-----------------------------------------------------------------------------
void stats::Definit()
 {
  NbVehiculesDeplaces=cv->NbVehiculesDeplaces;
  NbVehiculesArrives=cv->NbVehiculesArrives;
  NbVehiculesSortis=cv->NbVehiculesSortis;
 }
//-----------------------------------------------------------------------------
void centre_ville::CreeZone() // v4.0 (allocation dynamique)
 {
  if ((NbX>0)&&(NbY>0))
   {
    v=new voie*[NbX];
    for(int i=0; i<NbX; i++) v[i]=new voie[NbY];
    for(int i=0; i<NbX; i++)
     for(int j=0; j<NbY; j++)
      if (v+i+j) v[i][j].Definit(i, j);
   }
  else v=NULL;
  dx[(int)ouest]=NbX-1; dy[(int)nord]=NbY-1;
 }
//-----------------------------------------------------------------------------
centre_ville::centre_ville(bool NbElementsParDefaut, int NbX, int NbY)  // v4.0 (NbX, NbY)
 {
  this->NbX=NbX; this->NbY=NbY; // v4.0
  CreeZone();
  CopieEnCours=TourEnCours=false; // v4.0.1 (CopieEnCours)
  Xc=Yc=NbXc=NbYc=0; // v4.0.1
  dtTop=dtTemps=0; // v3.9.2
  NbToursParcourus=NbCasesParcourues=TourCrt=0L; NbToursParSeconde=10L; // v4.2 (NbToursParSeconde=10L au lieu de 2L)
  NbVehiculesSortis=NbVehiculesDeplaces=NbVehiculesArrives=DureeOrange=NbEtapes=NbTrams=NbBus=NbVehicules=NbFeux=0; // v3.0 (NbBus) v3.5 (NbTrams)
  AttenteMaxVeh=10L;
  NbVitesses=1;
  NbToursStats=100;
  TypeStats=par_pourcentage; // v3.5
  NbMaxCasesDetectPsgPt=5; // v3.0.5
  ProbaDirPsgPt=50;
  NbMaxCasesDetectFileTaxi=NbMaxCasesDetectArretTram=NbMaxCasesDetectArretBus=3; // v3.6 (taxi)
  ProbaDirFileTaxi=ProbaDirArretTram=ProbaDirArretBus=50; // v3.6 (taxi)
  ProbaArretTaxiDmd=ProbaArretTramDmd=ProbaArretBusDmd=10; // v3.6 (taxi)
  NbMaxPersonnesTram=NbMaxPersonnesBus=100; // v3.5
  NbMaxPersonnesTaxi=3; // v3.6
  NbToursStopArretTram=NbToursStopArretBus=3; // v3.5
  NbMaxToursAttenteTaxi=NbMaxToursAttenteTram=NbMaxToursAttenteBus=25; // v3.6 (taxi)
  VerifOk=DistancesCalculees=QuadrillageStats=false;
  Feu=NULL;
  Etape=NULL;
  Vehicule=NULL;
  Bus=NULL; // v3.0
  Tram=NULL; // v3.5
  Pieton=NULL; // v2.0
  Stats=NULL;
  ArretBus=NULL; // v3.0
  NbLignesBus=0; // v3.0
  NbArretsBus=0; // v3.0
  ArretTram=NULL; // v3.5
  NbLignesTram=0; // v3.5
  NbArretsTram=0; // v3.5
  NbTaxis=0; // v3.6
  NbPlacesTaxi=0; // v3.6
  NbFilesTaxi=0; // v3.6
  Taxi=NULL; // v3.6
  PlaceTaxi=NULL; // v3.6
  FileTaxi=NULL; // v3.6
  for(int i=0; i<NBMAXLIGNESBUSTRAM; i++)
   {
    LigneBus[i].AffecteNumero(i+1); // v3.0
    LigneTram[i].AffecteNumero(i+1); // v3.5
   }
  // Tableaux avec nombre par d�faut
  if (NbElementsParDefaut)
   {
    DefinitNbFeux(NBFEUXDEFAUT);
    DefinitNbEtapes(NBETAPESDEFAUT);
    DefinitNbVehicules(NBVEHICULESDEFAUT);
    DefinitNbPietons(NBPIETONSDEFAUT); // v2.0
   }
  // Propri�t�s pour la g�n�ration al�atoire de r�seau (v4.2)
  LgrMinSgmtRoute=LgrMaxSgmtRoute=ProbaSortieIntersection=ProbaEntreeIntersection=ProbaTraverseeRoute=0;
 }
//-----------------------------------------------------------------------------
centre_ville::~centre_ville()
 {
  if (v)
   {
    for(int i=0; i<NbX; i++)
     if (v[i]) { delete[] v[i]; v[i]=NULL; }
    delete[] v; v=NULL;
   }
  if (Feu) { delete[] Feu; Feu=NULL; }
  if (Etape) { delete[] Etape; Etape=NULL; }
  if (Vehicule) { delete[] Vehicule; Vehicule=NULL; }
  if (Pieton) { delete[] Pieton; Pieton=NULL; }
  if (ArretBus) { delete[] ArretBus; ArretBus=NULL; } // v3.6
  if (ArretTram) { delete[] ArretTram; ArretTram=NULL; } // v3.6
  if (Taxi) { delete[] Taxi; Taxi=NULL; } // v3.6
  if (PlaceTaxi) { delete[] PlaceTaxi; PlaceTaxi=NULL; } // v3.6
  if (FileTaxi) { delete[] FileTaxi; FileTaxi=NULL; } // v3.6
  if (Stats) { delete[] Stats; Stats=NULL; }
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbFeux(int n)
 {
  int i;
  if (NbFeux) { delete[] Feu; Feu=NULL; }
  NbFeux=0;
  if (n&&(Feu=new feu[n]))
   {
    for(i=0; i<n; i++) Feu[i].AffecteNumero(i+1);
    NbFeux=n;
   }
  return NbFeux;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbEtapes(int n)
 {
  int i;
  if (NbEtapes) { delete[] Etape; Etape=NULL; }
  NbEtapes=0;
  if (Etape=new etape[n])
   {
    for(i=0; i<n; i++) Etape[i].AffecteNumero(i+1);
    NbEtapes=n;
   }
  return NbEtapes;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbVehicules(int n)
 {
  int i;
  if (NbVehicules) { delete[] Vehicule; Vehicule=NULL; }
  NbVehicules=0;
  if (Vehicule=new vehicule[n])
   {
    for(i=0; i<n; i++) Vehicule[i].AffecteNumero(i+1);
    NbVehicules=n;
   }
  return NbVehicules;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbBus(int n) // v3.0
 {
  int i;
  if (NbBus) { delete[] Bus; Bus=NULL; }
  NbBus=0;
  if (n&&(Bus=new bus[n]))
   {
    for(i=0; i<n; i++) Bus[i].AffecteNumero(i+1);
    NbBus=n;
   }
  return NbBus;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbTrams(int n) // v3.5
 {
  int i;
  if (NbTrams) { delete[] Tram; Tram=NULL; }
  NbTrams=0;
  if (n&&(Tram=new tram[n]))
   {
    for(i=0; i<n; i++) Tram[i].AffecteNumero(i+1);
    NbTrams=n;
   }
  return NbTrams;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbPietons(int n)
 {
  int i;
  if (NbPietons) { delete[] Pieton; Pieton=NULL; }
  NbPietons=0;
  if (n&&(Pieton=new pieton[n]))
   {
    for(i=0; i<n; i++) Pieton[i].AffecteNumero(i+1);
    NbPietons=n;
   }
  return NbPietons;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbLignesBus(int n) // v3.0
 {
  int i;
  if (n>NbLignesBus)
   for(i=NbLignesBus; i<n; i++) LigneBus[i].Initialise();
  else
   for(i=NbLignesBus-1; i>=n; i--) LigneBus[i].Initialise();
  NbLignesBus=n;
  return NbLignesBus;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbLignesTram(int n) // v3.5
 {
  int i;
  if (n>NbLignesTram)
   for(i=NbLignesTram; i<n; i++) LigneTram[i].Initialise();
  else
   for(i=NbLignesTram-1; i>=n; i--) LigneTram[i].Initialise();
  NbLignesTram=n;
  return NbLignesTram;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbArretsBus(int n) // v3.0
 {
  int i;
  if (NbArretsBus) { delete[] ArretBus; ArretBus=NULL; }
  NbArretsBus=0;
  if (ArretBus=new arret_bus[n])
   {
    for(i=0; i<n; i++) ArretBus[i].AffecteNumero(i+1);
    NbArretsBus=n;
   }
  return NbArretsBus;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbArretsTram(int n) // v3.5
 {
  int i;
  if (NbArretsTram) { delete[] ArretTram; ArretTram=NULL; }
  NbArretsTram=0;
  if (ArretTram=new arret_tram[n])
   {
    for(i=0; i<n; i++) ArretTram[i].AffecteNumero(i+1);
    NbArretsTram=n;
   }
  return NbArretsTram;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbPlacesTaxi(int n) // v3.0
 {
  int i;
  if (NbPlacesTaxi) { delete[] PlaceTaxi; PlaceTaxi=NULL; }
  NbPlacesTaxi=0;
  if (n&&(PlaceTaxi=new place_taxi[n]))
   {
    for(i=0; i<n; i++) { PlaceTaxi[i].AffecteNumero(i+1); }
    NbPlacesTaxi=n;
   }
  return NbPlacesTaxi;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbFilesTaxi(int n) // v3.0
 {
  int i;
  if (NbFilesTaxi) { delete[] FileTaxi; FileTaxi=NULL; }
  NbFilesTaxi=0;
  if (n&&(FileTaxi=new file_taxi[n]))
   {
    for(i=0; i<n; i++) { FileTaxi[i].AffecteNumero(i+1); }
    NbFilesTaxi=n;
   }
  return NbFilesTaxi;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbTaxis(int n) // v3.0
 {
  int i;
  if (NbTaxis) { delete[] Taxi; Taxi=NULL; }
  NbTaxis=0;
  if (n&&(Taxi=new taxi[n]))
   {
    for(i=0; i<n; i++) { Taxi[i].AffecteNumero(i+1); }
    NbTaxis=n;
   }
  return NbTaxis;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitFilesTaxi() // v3.6
 {
  int NumFile=0, NbFilesTrv=0;
  if (FileTaxi) { delete[] FileTaxi; FileTaxi=NULL; NbFilesTaxi=0; }
  if ((!NbPlacesTaxi)||(!PlaceTaxi)) return 0;
  for(int i=0; i<NbPlacesTaxi; i++)
   if (PlaceTaxi[i].Definie())
    NbFilesTrv+=PlaceTaxi[i].EstQueueFile();
  if (NbFilesTrv)
   {
    if (DefinitNbFilesTaxi(NbFilesTrv)!=NbFilesTrv) return 0;
    // D'abord on d�finit la file pour les queues de file
    for(int i=0; i<NbPlacesTaxi; i++)
     if (PlaceTaxi[i].Definie()&&
         PlaceTaxi[i].EstQueueFile())
      {
       FileTaxi[NumFile].Definit(i);
       PlaceTaxi[i].DefinitFile(NumFile);
       NumFile++;
      }
     // Ensuite pour toutes les autres places
    for(int i=0; i<NbPlacesTaxi; i++)
     if (PlaceTaxi[i].Definie())
      PlaceTaxi[i].DefinitFile(PlaceTaxi[PlaceTaxi[i].PlaceQueueFile()-1].NumFile);
   }
  return NbFilesTrv;
 }
//-----------------------------------------------------------------------------
int centre_ville::NbFeuxLibres()
 {
  int i, n=0;
  for(i=0; i<NbFeux; i++) n+=!Feu[i].Defini();
  return n;
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroFeuLibre()
 {
  int i;
  for(i=0; (i<NbFeux)&&Feu[i].Defini(); i++);
  return (i+1)*(i<NbFeux);
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroEtapeLibre()
 {
  int i;
  for(i=0; (i<NbEtapes)&&Etape[i].Definie(); i++);
  return (i+1)*(i<NbEtapes);
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroVehiculeLibre()
 {
  int i;
  for(i=0; (i<NbVehicules)&&Vehicule[i].Defini(); i++);
  return (i+1)*(i<NbVehicules);
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroPietonLibre()
 {
  int i;
  for(i=0; (i<NbPietons)&&Pieton[i].Defini(); i++);
  return (i+1)*(i<NbPietons);
 }
//-----------------------------------------------------------------------------
int centre_ville::ArretBusExistant(int x, int y) // v3.0
 {
  int d, i=0;
  voie *Voie;
  for(d=nord; d<=ouest; d++)
   {
    Voie=&_V(x,y,d);
    if (Voie->NumArretBus&&
        ((v[x][y].DirPoss&PossDir[d])||  // on peut aller sur la case Voie OU
         (Voie->DirPoss&InvPossDir[d]))) // on peut venir de la case Voie
     {
      if (!i)
       i=Voie->NumArretBus;
      if ((Voie->NumArretBus==i)&& // Si case contigu� est arr�t de bus
          (!Voie->v(AGaucheDe[d])->DirPoss)&& // ET qu'il y a un trottoir � sa gauche (en regardant vers l'arri�re de l'arr�t)
          (Voie->DirPoss&InvPossDir[d])) // Si d est dans la bonne direction (sens bus)
       ArretBus[i-1].Definit(x, y); // (x,y) devient la t�te d'arr�t de bus Voie->NumArretBus
     }
   }
  return i;
 }
//-----------------------------------------------------------------------------
int centre_ville::ArretTramExistant(int x, int y) // v3.5
 { // Pour les trams on ne change pas la t�te de l'arr�t car il peut y avoir un double sens sur la voie
  int d, i=0;
  voie *Voie;
  for(d=nord; (!i)&&(d<=ouest); d++)
   {
    Voie=&_V(x,y,d);
    if (Voie->NumArretTram&& // Un arr�t contigu existe ET
        (v[x][y].SensVoieTram==SensVoieTramDir[d][d])&& // M�me sens de la voie
        (Voie->SensVoieTram==SensVoieTramDir[d][d])) // Dans le prolongement
     i=Voie->NumArretTram;
   }
  return i;
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroArretBusLibre(int x, int y) // v3.0
 {
  int i;
  if (i=ArretBusExistant(x, y))
   return i; // L'arr�t existe d�j� (case contigu� qui communique : va ou vient)
  else
   { // C'est un nouvel arr�t de bus
    for(i=0; (i<NbArretsBus)&&ArretBus[i].Defini(); i++);
    return (i+1)*(i<NbArretsBus);
   }
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroArretTramLibre(int x, int y) // v3.5
 {
  int i;
  if (i=ArretTramExistant(x, y))
   return i; // L'arr�t existe d�j� (case contigu� qui communique : va ou vient)
  else
   { // C'est un nouvel arr�t de tram
    for(i=0; (i<NbArretsTram)&&ArretTram[i].Defini(); i++);
    return (i+1)*(i<NbArretsTram);
   }
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroPlaceTaxiLibre() // v3.6
 {
  int i;
  for(i=0; (i<NbPlacesTaxi)&&PlaceTaxi[i].Definie(); i++);
  return (i+1)*(i<NbPlacesTaxi);
 }
//-----------------------------------------------------------------------------
int centre_ville::AjouteFeu(int x, int y, direction d)
 {
  int i=NumeroFeuLibre();
  if (i)
   {
    Feu[i-1].Definit(x, y, d);
    v[x][y].NumFeu[d-1]=i;
    // D�finition des dur�es par d�faut
    Feu[i-1].DureeVert=DureeVert;
    Feu[i-1].DureeRouge=DureeRouge;
   }
  return i;
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeFeu(int n)
 {
  if ((n>-1)&&(n<NbFeux))
   {
    v[Feu[n].x][Feu[n].y].NumFeu[Feu[n].Dir-1]=0;
    Feu[n].Initialise();
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeFeuxVoie(int x, int y, type_voie TypeVoie) // v3.5 (TypeVoie)
 {
  voie *Voie=&(v[x][y]);
  int i;
  for(i=0; i<4; i++)
   if (Voie->ExisteVoieDansDirection(TypeVoie, (direction(i+1)))&& // v3.5
       Voie->NumFeu[i])
    SupprimeFeu(Voie->NumFeu[i]-1);
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeEtapeVoie(int x, int y) // v3.6
 {
  voie *Voie=&(v[x][y]);
  if (Voie->NumEtape) cv->SupprimeEtape(Voie->NumEtape-1);
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeArretBusVoie(int x, int y) // v3.6
 {
  voie *Voie=&(v[x][y]);
  if (Voie->NumArretBus) Voie->RetireArretBus();
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeDepotBusVoie(int x, int y) // v3.6
 {
  voie *Voie=&(v[x][y]);
  if (Voie->EstDepotBus()) DepotBus.Initialise();
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeArretTramVoie(int x, int y) // v3.6
 {
  voie *Voie=&(v[x][y]);
  if (Voie->NumArretTram) Voie->RetireArretTram();
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimePlaceTaxiVoie(int x, int y) // v3.6
 {
  voie *Voie=&(v[x][y]);
  if (Voie->NumPlaceTaxi) Voie->RetirePlaceTaxi();
 }
//-----------------------------------------------------------------------------

int centre_ville::AjouteEtape(int x, int y)
 {
  int i=NumeroEtapeLibre();
  if (i)
   {
    Etape[i-1].Definit(x, y);
    v[x][y].NumEtape=i;
   }
  return i;
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeEtape(int n)
 {
  if ((n>-1)&&(n<NbEtapes))
   {
    v[Etape[n].x][Etape[n].y].NumEtape=0;
    Etape[n].Initialise();
   }
 }
//-----------------------------------------------------------------------------
int centre_ville::AjouteArretBus(int x, int y) // v3.0
 {
  int i=NumeroArretBusLibre(x, y);
  if (i)
   {
    if (!ArretBus[i-1].Defini())
     ArretBus[i-1].Definit(x, y);
    v[x][y].NumArretBus=i;
   }
  return i;
 }
//-----------------------------------------------------------------------------
int centre_ville::AjouteArretTram(int x, int y) // v3.5
 {
  int i=NumeroArretTramLibre(x, y);
  if (i)
   {
    if (!ArretTram[i-1].Defini())
     ArretTram[i-1].Definit(x, y);
    v[x][y].NumArretTram=i;
   }
  return i;
 }
//-----------------------------------------------------------------------------
int centre_ville::AjoutePlaceTaxi(int x, int y) // v3.6
 {
  int i=NumeroPlaceTaxiLibre();
  if (i)
   {
    if (!PlaceTaxi[i-1].Definie())
     PlaceTaxi[i-1].Definit(x, y);
    v[x][y].NumPlaceTaxi=i;
   }
  return i;
 }
//-----------------------------------------------------------------------------

bool centre_ville::ExisteCaseArretBus(int x, int y) // v3.0
 {
  bool Existe=false;
  int d, i=v[x][y].NumArretBus;
  voie *Voie;
  for(d=nord; d<=ouest; d++)
   {
    Voie=&_V(x,y,d);
    if (Voie->NumArretBus==i)
     { // On profite pour regarder si on change de t�te d'arr�t de bus
      Existe=true;
      if (v[x][y].EstTeteArretBus()) // Si c'�tait une t�te d'arr�t de bus,
       Voie->DefinitArretBus(i);// sa voisine prend la place. v3.0.3
     }
   }
  return Existe;
 }
//-----------------------------------------------------------------------------
bool centre_ville::ExisteCaseArretTram(int x, int y) // v3.5
 {
  bool Existe=false;
  int d, i=v[x][y].NumArretTram;
  voie *Voie;
  for(d=nord; d<=ouest; d++)
   {
    Voie=&_V(x,y,d);
    if (Voie->NumArretTram==i)
     { // On profite pour regarder si on change de t�te d'arr�t de tram
      Existe=true;
      if (v[x][y].EstTeteArretTram()) // Si c'�tait une t�te d'arr�t de tram,
       Voie->DefinitArretTram(i);// sa voisine prend la place. v3.0.3
     }
   }
  return Existe;
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeArretBus(int x, int y) // v3.0. Supprime sur une case seulement
 {
  int i=v[x][y].NumArretBus;
  if ((i>0)&&(i<=NbArretsBus))
   {
    if (!ExisteCaseArretBus(x, y))
     ArretBus[i-1].Initialise(); // Si l'arr�t n'a pas d'autre case
    v[x][y].NumArretBus=0;
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeArretTram(int x, int y) // v3.5. Supprime sur une case seulement
 {
  int i=v[x][y].NumArretTram;
  if ((i>0)&&(i<=NbArretsTram))
   {
    if (!ExisteCaseArretTram(x, y))
     ArretTram[i-1].Initialise(); // Si l'arr�t n'a pas d'autre case
    v[x][y].NumArretTram=0;
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeArretBus(int n) // v3.0. Supprime compl�tement l'arr�t (sur TOUTES les cases)
 {
  v[ArretBus[n].x][ArretBus[n].y].RetireArretBus(); // Retire le n� d'arr�t de bus r�cursivement sur toutes les cases
  ArretBus[n].Initialise();
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeArretTram(int n) // v3.5. Supprime compl�tement l'arr�t (sur TOUTES les cases)
 {
  v[ArretTram[n].x][ArretTram[n].y].RetireArretTram(); // Retire le n� d'arr�t de tram r�cursivement sur toutes les cases
  ArretTram[n].Initialise();
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimePlaceTaxi(int n) // v3.6
 {
  v[PlaceTaxi[n].x][PlaceTaxi[n].y].RetirePlaceTaxi();
  PlaceTaxi[n].Initialise();
 }
//-----------------------------------------------------------------------------
sens centre_ville::SensPassagePietonsPossible(int x, int y)
 { // v2.0
  // 1. Sens suivant DirPoss (Directions de l'int�rieur vers l'ext�rieur)
  sens Sens=SensPsgPt[v[x][y].DirPoss];
  // 2. Test des cases voisines (Directions de l'ext�rieur vers l'int�rieur)
  switch(Sens)
   {
    case vertical:   if ((_V(x,y,nord).DirPoss&S)||
                         (_V(x,y,sud).DirPoss&N))
                      Sens=indefini;
                     break;
    case horizontal: if ((_V(x,y,est).DirPoss&O)||
                         (_V(x,y,ouest).DirPoss&E))
                      Sens=indefini;
                     break;
    default: Sens=indefini;
   }
  // v3.5 : S'il n'y a pas de route, on regarde les voies de tram...
  if (!v[x][y].DirPoss)
   {
    if (!v[x][y].SensVoieTram) // Si pas de voie de tram alors
     Sens=indefini; // Pas de sens possible (case noire)
    else
     { // Sinon deux cas de voies de tram permettent le passage pi�tons
      if (v[x][y].SensVoieTram==est_ouest) Sens=vertical;
      if (v[x][y].SensVoieTram==nord_sud) Sens=horizontal;
     }
   }
  else // Sinon, s'il y a une route,
   if (v[x][y].SensVoieTram) // il ne faut pas qu'il y ait une voie de tram
    Sens=indefini;
  return Sens;
 }
//-----------------------------------------------------------------------------
direction centre_ville::CherchePassagePietons(int x, int y, sens SensRecherche) // v2.0
 {
  bool Trv;
  int i, d, Dist[2]={0,0};
  direction Dir[2]={(direction)(3-SensRecherche),(direction)(5-SensRecherche)};
  if ((!NbMaxCasesDetectPsgPt)|| // NbMaxCasesDetectPsgPt et
      (!SensRecherche)) // SensRecherche
   return indefinie; //  doivent �tre d�finis (horizontal|vertical ; >0)
  for(d=0; d<2; d++)
   {
    for(Trv=false,i=1;
        (!(Trv=V_(x,y,i,3-SensRecherche+2*d).PassagePietons)&&
        (!V_(x,y,i,3-SensRecherche+2*d).DirPoss)&&
        (i<=NbMaxCasesDetectPsgPt));
        i++);
    if (Trv) Dist[d]=i;
   }
  switch(!!Dist[0]+2*!!Dist[1])
   {
    case 0: return indefinie;
    case 1: return Dir[0];
    case 2: return Dir[1];
    case 3: if (Dist[0]==Dist[1])
             return Dir[rand()%2];
            else
             return (Dist[0]<Dist[1]?Dir[0]:Dir[1]);
    default:return indefinie;
   }
 }
//-----------------------------------------------------------------------------
direction centre_ville::ChercheArretBus(int x, int y, sens SensRecherche) // v3.0
 {
  bool Trv;
  int i, d, Dist[2]={0,0};
  direction Dir[2]={(direction)(3-SensRecherche),(direction)(5-SensRecherche)};
  if ((!NbMaxCasesDetectArretBus)|| // NbMaxCasesDetectArretBus et
      (!SensRecherche)) // SensRecherche
   return indefinie; //  doivent �tre d�finis (horizontal|vertical ; >0)
  for(d=0; d<2; d++)
   {
    for(Trv=false,i=1;
        (!(Trv=V_(x,y,i,3-SensRecherche+2*d).NumArretBus)&&
        (!V_(x,y,i,3-SensRecherche+2*d).DirPoss)&&
        (i<=NbMaxCasesDetectArretBus));
        i++);
    if (i<=NbMaxCasesDetectArretBus) // Si toujours dans les distances on v�rifie la derni�re case (l'arr�t EST sur une route)
     Trv|=V_(x,y,i,3-SensRecherche+2*d).NumArretBus;
    if (Trv) Dist[d]=i;
   }
  switch(!!Dist[0]+2*!!Dist[1])
   {
    case 0: return indefinie;
    case 1: return Dir[0];
    case 2: return Dir[1];
    case 3: if (Dist[0]==Dist[1])
             return Dir[rand()%2];
            else
             return (Dist[0]<Dist[1]?Dir[0]:Dir[1]);
    default:return indefinie;
   }
 }
//-----------------------------------------------------------------------------
direction centre_ville::ChercheArretTram(int x, int y, sens SensRecherche) // v3.0
 {
  bool Trv;
  int i, d, Dist[2]={0,0};
  direction Dir[2]={(direction)(3-SensRecherche),(direction)(5-SensRecherche)};
  if ((!NbMaxCasesDetectArretTram)|| // NbMaxCasesDetectArretTram et
      (!SensRecherche)) // SensRecherche
   return indefinie; //  doivent �tre d�finis (horizontal|vertical ; >0)
  for(d=0; d<2; d++)
   {
    for(Trv=false,i=1;
        (!(Trv=V_(x,y,i,3-SensRecherche+2*d).NumArretTram)&&
        (!V_(x,y,i,3-SensRecherche+2*d).DirPoss)&&
        (i<=NbMaxCasesDetectArretTram));
        i++);
    if (i<=NbMaxCasesDetectArretTram) // Si toujours dans les distances on v�rifie la derni�re case (l'arr�t EST sur une route)
     Trv|=V_(x,y,i,3-SensRecherche+2*d).NumArretTram;
    if (Trv) Dist[d]=i;
   }
  switch(!!Dist[0]+2*!!Dist[1])
   {
    case 0: return indefinie;
    case 1: return Dir[0];
    case 2: return Dir[1];
    case 3: if (Dist[0]==Dist[1])
             return Dir[rand()%2];
            else
             return (Dist[0]<Dist[1]?Dir[0]:Dir[1]);
    default:return indefinie;
   }
 }
//-----------------------------------------------------------------------------
direction centre_ville::CherchePlaceTaxi(int x, int y, sens SensRecherche) // v3.6
 {
  bool Trv;
  int i, d, Dist[2]={0,0};
  direction Dir[2]={(direction)(3-SensRecherche),(direction)(5-SensRecherche)};
  if ((!NbMaxCasesDetectFileTaxi)|| // NbMaxCasesDetectFileTaxi et
      (!SensRecherche)) // SensRecherche
   return indefinie; //  doivent �tre d�finis (horizontal|vertical ; >0)
  for(d=0; d<2; d++)
   {
    for(Trv=false,i=1;
        (!(Trv=V_(x,y,i,3-SensRecherche+2*d).NumPlaceTaxi)&&
        (!V_(x,y,i,3-SensRecherche+2*d).DirPoss)&&
        (i<=NbMaxCasesDetectFileTaxi));
        i++);
    if (i<=NbMaxCasesDetectFileTaxi) // Si toujours dans les distances on v�rifie la derni�re case (le place de taxi EST sur une route)
     Trv|=V_(x,y,i,3-SensRecherche+2*d).NumPlaceTaxi;
    if (Trv) Dist[d]=i;
   }
  switch(!!Dist[0]+2*!!Dist[1])
   {
    case 0: return indefinie;
    case 1: return Dir[0];
    case 2: return Dir[1];
    case 3: if (Dist[0]==Dist[1])
             return Dir[rand()%2];
            else
             return (Dist[0]<Dist[1]?Dir[0]:Dir[1]);
    default:return indefinie;
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::DefinitArretBus(int n, int x, int y) // v3.0
 {
  if ((n>0)&&(n<=NbArretsBus))
   ArretBus[n-1].Definit(x, y);
 }
//-----------------------------------------------------------------------------
void centre_ville::DefinitArretTram(int n, int x, int y) // v3.5
 {
  if ((n>0)&&(n<=NbArretsTram))
   ArretTram[n-1].Definit(x, y);
 }
//-----------------------------------------------------------------------------
direction centre_ville::DirectionArretBus(int x, int y) // v3.0
 {
  bool Ambiguite=false;
  int d;
  direction Dir=indefinie;
  for(d=nord; d<=ouest; d++) // On prend la derni�re possibilit� en cas de litige
   if ((!(v[x][y].DirPoss&PossDir[d]))&& // Si pas de d�placement vers d ET
       (!_V(x,y,d).DirPoss)&& // Mur vers d ET
       (v[x][y].DirPoss&PossDir[AGaucheDe[d]])) // Direction possible � gauche (sens de la circulation de la voie)
    {
     Ambiguite=!!Dir;
     Dir=(direction)d;
    }
  return (direction)((!Ambiguite)*Dir);
 }
//-----------------------------------------------------------------------------
direction centre_ville::DirectionArretTram(int x, int y) // v3.5
 {
  bool Ambiguite=false;
  int d;
  direction Dir=indefinie;
  for(d=nord; d<=ouest; d++) // On prend la derni�re possibilit� en cas de litige
   if ((!(v[x][y].DirPoss&PossDir[d]))&& // Si pas de d�placement vers d ET
       (!_V(x,y,d).DirPoss)&& // Mur vers d ET
       (v[x][y].DirPoss&PossDir[AGaucheDe[d]])) // Direction possible � gauche (sens de la circulation de la voie)
    {
     Ambiguite=!!Dir;
     Dir=(direction)d;
    }
  return (direction)((!Ambiguite)*Dir);
 }
//-----------------------------------------------------------------------------
position_arret_bus_tram centre_ville::PositionArretBus(int x, int y, direction d) // v3.0
 {
  switch(  (_V(x,y,AGaucheDe[d]).NumArretBus==v[x][y].NumArretBus)+
         2*(_V(x,y,ADroiteDe[d]).NumArretBus==v[x][y].NumArretBus))
   {
    case 1: return queue;
    case 2: return tete;
    case 3: return milieu;
    default: return tete;
   }
 }
//-----------------------------------------------------------------------------
position_arret_bus_tram centre_ville::PositionArretTram(int x, int y, direction d) // v3.5
 {
  switch(  (_V(x,y,AGaucheDe[d]).NumArretTram==v[x][y].NumArretTram)+
         2*(_V(x,y,ADroiteDe[d]).NumArretTram==v[x][y].NumArretTram))
   {
    case 1: return queue;
    case 2: return tete;
    case 3: return milieu;
    default: return tete;
   }
 }
//-----------------------------------------------------------------------------
bool centre_ville::ArretsBusVoisinsDifferents(int x, int y) // v3.0
 {
  voie *Voie;
  bool DiffTrv=false;
  int d, n, i=0;
  for(d=nord; (!DiffTrv)&&(d<=ouest); d++)
   {
    Voie=&_V(x,y,d);
    if ((n=Voie->NumArretBus)&&
        ((v[x][y].DirPoss&PossDir[d])||  // on peut aller sur la case Voie OU
         (Voie->DirPoss&InvPossDir[d]))) // on peut venir de la case Voie
     if (!i) i=n; else DiffTrv=(i!=n);
   }
  return DiffTrv;
 }
//-----------------------------------------------------------------------------
bool centre_ville::ArretsTramVoisinsDifferents(int x, int y) // v3.5
 {
  voie *Voie;
  bool DiffTrv=false;
  int d, n, i=0;
  for(d=nord; (!DiffTrv)&&(d<=ouest); d++)
   {
    Voie=&_V(x,y,d);
    if ((n=Voie->NumArretTram)&&
        ((v[x][y].DirPoss&PossDir[d])||  // on peut aller sur la case Voie OU
         (Voie->DirPoss&InvPossDir[d]))) // on peut venir de la case Voie
     if (!i) i=n; else DiffTrv=(i!=n);
   }
  return DiffTrv;
 }
//-----------------------------------------------------------------------------
direction centre_ville::DirArretBusVoisin(int x, int y) // v3.0
 {
  voie *Voie;
  int d, DirArretBusVoisin=indefinie;
  for(d=nord; (!DirArretBusVoisin)&&(d<=ouest); d++)
   {
    Voie=&_V(x,y,d);
    if (Voie->NumArretBus&& // Arr�t de bus voisin ET
        ((v[x][y].DirPoss&PossDir[d])|| // on peut y aller ou
         (Voie->DirPoss&InvPossDir[d]))) // on peut en venir
     DirArretBusVoisin=d;
   }
  return (direction)DirArretBusVoisin;
 }
//-----------------------------------------------------------------------------
direction centre_ville::DirArretTramVoisin(int x, int y) // v3.5
 {
  voie *Voie;
  int d, DirArretTramVoisin=indefinie;
  for(d=nord; (!DirArretTramVoisin)&&(d<=ouest); d++)
   {
    Voie=&_V(x,y,d);
    if (Voie->NumArretTram&& // Arr�t de tram voisin ET
        ((v[x][y].DirPoss&PossDir[d])|| // on peut y aller ou
         (Voie->DirPoss&InvPossDir[d]))) // on peut en venir
     DirArretTramVoisin=d;
   }
  return (direction)DirArretTramVoisin;
 }
//-----------------------------------------------------------------------------
bool centre_ville::AjoutArretBusPossible(int x, int y) // v3.0
 {
  int d;
  direction DirArretVoisin;
  bool Possible=false;
  if (v[x][y].DirPoss&&(!ArretsBusVoisinsDifferents(x, y))) // C'est de la route ET il n'y a pas deux arr�ts diff�rents voisins
   {
    DirArretVoisin=DirArretBusVoisin(x,y);
    for(d=nord; (!Possible)&&(d<=ouest); d++)
     if ((!(v[x][y].DirPoss&PossDir[d]))&& // Si pas de direction possible vers d et dans cette direction il y a un mur ALORS
         (!_V(x,y,d).DirPoss)) // Soit 1 arr�t d'un c�t� ou de l'autre soit c'est le m�me n� (ou nul les 2)
      Possible=((!DirArretVoisin)|| // Si arr�t voisin il y a, ALORS
                (DirArretVoisin==ADroiteDe[d])||  // il doit �tre dans le m�me
                (DirArretVoisin==AGaucheDe[d]))&& // sens que le futur arr�t
               ((!!_V(x,y,AGaucheDe[d]).NumArretBus+!!_V(x,y,ADroiteDe[d]).NumArretBus==1)||
                (_V(x,y,AGaucheDe[d]).NumArretBus==_V(x,y,ADroiteDe[d]).NumArretBus));
    return Possible;
   }
  else return false;
 }
//-----------------------------------------------------------------------------
bool centre_ville::AjoutArretTramPossible(int x, int y) // v3.5
 {
  int d;
  direction DirArretVoisin;
  bool Possible=false;
  if (v[x][y].SensVoieTram&&(!ArretsTramVoisinsDifferents(x, y))) // C'est de la route ET il n'y a pas deux arr�ts diff�rents voisins
   {
    DirArretVoisin=DirArretTramVoisin(x,y);
    for(d=nord; (!Possible)&&(d<=ouest); d++)
     if ((!(v[x][y].DirPoss&PossDir[d]))&& // Si pas de direction possible vers d et dans cette direction il y a un mur ALORS
         (!_V(x,y,d).DirPoss)) // Soit 1 arr�t d'un c�t� ou de l'autre soit c'est le m�me n� (ou nul les 2)
      Possible=((!DirArretVoisin)|| // Si arr�t voisin il y a, ALORS
                (DirArretVoisin==ADroiteDe[d])||  // il doit �tre dans le m�me
                (DirArretVoisin==AGaucheDe[d]))&& // sens que le futur arr�t
               ((!!_V(x,y,AGaucheDe[d]).NumArretTram+!!_V(x,y,ADroiteDe[d]).NumArretTram==1)||
                (_V(x,y,AGaucheDe[d]).NumArretTram==_V(x,y,ADroiteDe[d]).NumArretTram));
    return Possible;
   }
  else return false;
 }
//-----------------------------------------------------------------------------
bool centre_ville::SuppressionArretBusPossible(int x, int y) // v3.0
 {
  int d, i=v[x][y].NumArretBus, n=0;
  for(d=nord; d<=ouest; d++)
   n+=(_V(x,y,d).NumArretBus==i);
  return (n<2);
 }
//-----------------------------------------------------------------------------
bool centre_ville::SuppressionArretTramPossible(int x, int y) // v3.5
 {
  int d, i=v[x][y].NumArretTram, n=0;
  for(d=nord; d<=ouest; d++)
   n+=(_V(x,y,d).NumArretTram==i);
  return (n<2);
 }
//-----------------------------------------------------------------------------
void centre_ville::InitialiseInfosLignesBus() // v3.0
 {
  int i;
  NbLignesBus=0;
  for(i=0; i<NbArretsBus; i++)
   ArretBus[i].InitialiseInfosLignesBus();
 }
//-----------------------------------------------------------------------------
void centre_ville::InitialiseInfosLignesTram() // v3.5
 {
  int i;
  NbLignesTram=0;
  for(i=0; i<NbArretsTram; i++)
   ArretTram[i].InitialiseInfosLignesTram();
 }
//-----------------------------------------------------------------------------
void centre_ville::InitialiseInfosTrajetLignesBus()
 {
  int i, j;
  for(i=0; i<NbX; i++)
   for(j=0; j<NbY; j++)
    v[i][j].InitialiseInfosLignesBus();
 }
//-----------------------------------------------------------------------------
void centre_ville::InitialiseInfosTrajetLignesTram()
 {
  int i, j;
  for(i=0; i<NbX; i++)
   for(j=0; j<NbY; j++)
    v[i][j].InitialiseInfosLignesTram();
 }
//-----------------------------------------------------------------------------
void centre_ville::CalculeTrajetLignesBus() // v3.0.3
 { // InitialiseInfosTrajetLignesBus doit avoir �t� lanc� avant pour mettre les voie::LigneBus[i] � false
  int i, j, dp, ndp, DistArretBus, DistCrt, NumArretSvt;
  direction DirSvt;
  voie *Voie;
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++)
   if (LigneBus[i].NbArrets)
    for(j=0; j<LigneBus[i].NbArrets; j++)
     {
      Voie=&(v[ArretBus[LigneBus[i].NumArret[j]-1].x][ArretBus[LigneBus[i].NumArret[j]-1].y]);
      Voie->LigneBus[i]=true;
      NumArretSvt=LigneBus[i].NumArret[(j+1)%LigneBus[i].NbArrets];
      do
       {
        DistArretBus=0x7FFFFFFF;
        DirSvt=indefinie;
        ndp=NbDir[Voie->DirPoss];
        for(dp=0; dp<ndp; dp++) // v3.5
         {
          DistCrt=Voie->DistArretBus[NumArretSvt-1][dp];
          if (DistArretBus>DistCrt)
           {
            DistArretBus=DistCrt;
            DirSvt=Dirdp[dp][Voie->DirPoss];
           }
         }
        Voie=Voie->v(DirSvt); // 1. On va dans la direction ayant la distance la plus petite vers le prochain arr�t
        Voie->LigneBus[i]=true; // 2. On marque la ligne sur cette case
       }
      while(!Voie->EstTeteArretBus(NumArretSvt));
     }
 }
//-----------------------------------------------------------------------------
void centre_ville::CalculeTrajetLignesTram() // v3.5. Correction : v3.8
 { // InitialiseInfosTrajetLignesTram doit avoir �t� lanc� avant pour mettre les voie::LigneTram[i] � false
  int i, j, dp, ndp, DistArretTram, DistCrt, NumArretSvt;
  direction DirCrt, DirPrc, // v3.8
            DirSvt;
  voie *Voie;
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++)
   if (LigneTram[i].NbArrets)
    for(j=0; j<LigneTram[i].NbArrets; j++)
     {
      DirPrc=DirSvt=indefinie; // v3.8
      Voie=&(v[ArretTram[LigneTram[i].NumArret[j]-1].x][ArretTram[LigneTram[i].NumArret[j]-1].y]);
      Voie->LigneTram[i]=true;
      NumArretSvt=LigneTram[i].NumArret[(j+1)%LigneTram[i].NbArrets];
      do
       {
        DistArretTram=0x7FFFFFFF;
        DirSvt=indefinie;
        ndp=Voie->NbDirPossSensVoieTram(indefinie); // v3.8. DistArretTram travaille dans toutes les directions !
        for(dp=0; dp<ndp; dp++)  // donc il faut alors regarder si la direction courante est accessible depuis d'o� l'on vient !
         if (Voie->EstDirPossSensVoieTram(InvDir[DirPrc], DirCrt=Voie->DirSensVoieTram(indefinie, dp)))
          {
           DistCrt=Voie->DistArretTram[NumArretSvt-1][dp];
           if (DistArretTram>DistCrt)
            {
             DistArretTram=DistCrt;
             DirSvt=DirCrt; // v3.8
            }
          }
        Voie=Voie->v(DirPrc=DirSvt); // 1. On va dans la direction ayant la distance la plus petite vers le prochain arr�t. v3.8 (DirPrc)
        Voie->LigneTram[i]=true; // 2. On marque la ligne sur cette case
       }
      while(!Voie->EstTeteArretTram(NumArretSvt));
     }
 }
//-----------------------------------------------------------------------------
bool centre_ville::VerifieCalculDistances(type_distance &TypeDistance) // v3.5 : inclut �galement celui des arr�ts de bus et tram. v3.6... Et des files de taxi
 {
  bool Ok=true;
  int i, j, k, d, ndp;
  for(i=0; Ok&&(i<NbX); i++)
   for(j=0; Ok&&(j<NbY); j++)
    {
     ndp=NbDir[v[i][j].DirPoss];
     for(d=0; Ok&&(d<ndp); d++)
      {
       for(k=0; Ok&&(k<NbEtapes); k++)
        if (v[i][j].PassageBus|| // Si passage de bus OU
            _V(i,j,Dirdp[d][v[i][j].DirPoss]).PassageBus) // pointe sur un passage de bus
         { // On ne teste que la distance AVEC passage de bus
          if (!(Ok=(v[i][j].DistEtape[k][d][AVECPSGBUS]<DIST_INDEFINIE)))
           {
            xErr=i; yErr=j;
            TypeDistance=etapes;
           } // v3.5
         }
        else
         {
          if (!(Ok=(v[i][j].DistEtape[k][d][AVECPSGBUS]<DIST_INDEFINIE)&&
                   (v[i][j].DistEtape[k][d][SANSPSGBUS]<DIST_INDEFINIE)))
           {
            xErr=i; yErr=j;
            TypeDistance=etapes;
           } // v3.5
         }
       for(k=0; Ok&&(k<NbArretsBus); k++) // v3.0
        if (ArretBus[k].Defini()&& // v3.5
            (!(Ok=(v[i][j].DistArretBus[k][d]<DIST_INDEFINIE))))
         {
          xErr=i; yErr=j;
          TypeDistance=arrets_bus;
         } // v3.5
       for(k=0; Ok&&(k<NbFilesTaxi); k++) // v3.6
        if (!(Ok=(v[i][j].DistFileTaxi[k][d]<DIST_INDEFINIE)))
         {
          xErr=i; yErr=j;
          TypeDistance=files_taxi;
         } // v3.6
      }
     // v3.5
     ndp=v[i][j].NbDirPossSensVoieTram(indefinie);
     for(d=0; Ok&&(d<ndp); d++)
      for(k=0; Ok&&(k<NbArretsTram); k++)
       if (ArretTram[k].Defini()&&
           (!(Ok=(v[i][j].DistArretTram[k][d]<DIST_INDEFINIE))))
        {
         xErr=i; yErr=j;
         TypeDistance=arrets_tram;
        }
    }
  return Ok;
 }
//-----------------------------------------------------------------------------
bool centre_ville::PrepareCalculDistances() // v3.0 : inclut �galement celui des arr�ts de bus/tram. v3.6 ...Et des files de taxis
 {
  bool Ok=true;
  int i, j;
  for(i=0; Ok&&(i<NbX); i++)
   for(j=0; Ok&&(j<NbY); j++)
    Ok=v[i][j].PrepareCalculDistances();
  return Ok;
 }
//-----------------------------------------------------------------------------
bool centre_ville::PrepareCalculAttenteTrafic()
 {
  bool Ok=true;
  int i, j;
  for(i=0; Ok&&(i<NbX); i++)
   for(j=0; Ok&&(j<NbY); j++)
    Ok=v[i][j].PrepareCalculAttenteTrafic();
  return Ok;
 }
//-----------------------------------------------------------------------------
void centre_ville::IncrementeTrafic(int NumVehicule)
 {
  vehicule *veh=Vehicule+(NumVehicule-1);
  v[veh->x][veh->y].Trafic[veh->NumEtapeDepart][veh->NumEtapeArrivee]++;
  v[veh->x][veh->y].Trafic[0][veh->NumEtapeArrivee]++;
  v[veh->x][veh->y].Trafic[veh->NumEtapeDepart][0]++;
  v[veh->x][veh->y].Trafic[0][0]++;
 }
//-----------------------------------------------------------------------------
void centre_ville::IncrementeAttente(int NumVehicule)
 {
  vehicule *veh=Vehicule+(NumVehicule-1);
  int n=TourCrt-veh->TourDrnDepl-1;
  if (n>0)
   {
    v[veh->x][veh->y].Attente[veh->NumEtapeDepart][veh->NumEtapeArrivee]+=n;
    v[veh->x][veh->y].Attente[0][veh->NumEtapeArrivee]+=n;
    v[veh->x][veh->y].Attente[veh->NumEtapeDepart][0]+=n;
    v[veh->x][veh->y].Attente[0][0]+=n;
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::PlaceVehicule(int x, int y, int NumVehicule)
 {
  IncrementeAttente(NumVehicule);
  if (frmSimulation->SimulationSanglante&&
      (x>-1)&&(y>-1)&&
      cv->v[x][y].NbPietons) // v4.3
   cv->v[x][y].TuePietons();
  Vehicule[NumVehicule-1].Place(x, y);
  if ((x>-1)&&(y>-1))
   IncrementeTrafic(NumVehicule);
 }
//-----------------------------------------------------------------------------
bool centre_ville::PrepareVehicules()
 {
  int i,
      NumEtapeDepart=1,
      NumEtapeArrivee=2,
      NbVehiculesAvantCreation=NbVehicules;
  if (DefinitNbVehicules(NbVehiculesAvantCreation)!=NbVehiculesAvantCreation)
   return false;
  for(i=0; i<NbVehicules; i++)
   {
    Vehicule[i].Definit(Etape[NumEtapeDepart-1].x, Etape[NumEtapeDepart-1].y,
                        indefinie,
                        NumEtapeDepart, NumEtapeArrivee,
                        (i%(NbVehicules/(2*NbEtapes)))?
                         normal:
                         ((i%(NbVehicules/NbEtapes))?police:urgence));
    do
     {
      NumEtapeArrivee=1+NumEtapeArrivee%NbEtapes;
      if (NumEtapeArrivee==1)
       {
        NumEtapeDepart=1+NumEtapeDepart%NbEtapes;
        if (NumEtapeDepart==1) { NumEtapeDepart=1; NumEtapeArrivee=2; }
       }
     } while(NumEtapeDepart==NumEtapeArrivee);
   }
  return true;
 }
//-----------------------------------------------------------------------------
void centre_ville::PlaceBus(int x, int y, int NumBus) // v3.0
 {
  bus *b=Bus+NumBus-1;
  if (b->Defini()&&b->DirDrnDepl)
   {
    _V(b->x,b->y,InvDir[b->DirDrnDepl]).NumBus=0; // Effac� de la case d'origine (arri�re du bus)
    _V(b->x,b->y,InvDir[b->DirDrnDepl]).RedessineCase(false);
   }
  b->DirAvtDrnDepl=b->DirDrnDepl;
  b->DirDrnDepl=b->Dir;
  if (frmSimulation->SimulationSanglante&&cv->v[x][y].NbPietons) // v4.3
   cv->v[x][y].TuePietons();
  b->Place(x,y);
  if (v[x][y].NumArretBus&&
      v[x][y].EstTeteArretBus()&&
      (v[x][y].NumArretBus==b->NumArretSvt))
   { // C'est ici que l'on change d'ARRET
    b->NumDrnArret=b->NumArretSvt;
    b->NbCasesParcouruesDepuisDrnArret=0;
    b->TourArriveDrnArret=TourCrt;
    b->NumArretSvt=b->NumeroArretSuivant();
    b->TourDepartArretSvt=TourCrt+NbToursStopArretBus;
    b->FaitMonterEtDescendre();
   }
  else
   b->NbCasesParcouruesDepuisDrnArret++;
  b->NbCasesParcourues++;
  b->TourDrnDepl=TourCrt;
  // On ne dessine pas l'arri�re du bus car ils peuvent sortir du d�p�t (contrairement aux trams).
  v[x][y].NumBus=NumBus;
  _V(x,y,InvDir[b->DirDrnDepl]).RedessineCase(false);
  v[x][y].RedessineCase(false);
 }
//-----------------------------------------------------------------------------
void centre_ville::PlaceTram(int x, int y, int NumTram) // v3.5
 {
  tram *t=Tram+NumTram-1;
  if (t->Defini()&&t->DirDrnDepl)
   {
    _V(t->x,t->y,InvDir[t->DirDrnDepl]).NumTram=0; // Effac� de la case d'origine (arri�re du tram)
    _V(t->x,t->y,InvDir[t->DirDrnDepl]).RedessineCase(false);
   }
  t->DirAvtDrnDepl=t->DirDrnDepl;
  t->DirDrnDepl=t->Dir;
  if (frmSimulation->SimulationSanglante&&cv->v[x][y].NbPietons) // v4.3
   cv->v[x][y].TuePietons();
  t->Place(x,y);
  if (v[x][y].NumArretTram&&
      v[x][y].EstTeteArretTram()&&
      (v[x][y].NumArretTram==t->NumArretSvt))
   { // C'est ici que l'on change d'ARRET
    t->NumDrnArret=t->NumArretSvt;
    t->NbCasesParcouruesDepuisDrnArret=0;
    t->TourArriveDrnArret=TourCrt;
    t->NumArretSvt=t->NumeroArretSuivant();
    t->TourDepartArretSvt=TourCrt+NbToursStopArretTram;
    if (t->TourArriveDrnArret) t->FaitMonterEtDescendre();
   }
  else
   t->NbCasesParcouruesDepuisDrnArret++;
  t->NbCasesParcourues++;
  t->TourDrnDepl=TourCrt;
  _V(x,y,InvDir[t->DirDrnDepl]).NumTram=NumTram;
  v[x][y].NumTram=NumTram;
  _V(x,y,InvDir[t->DirDrnDepl]).RedessineCase(false);
  v[x][y].RedessineCase(false);
 }
//-----------------------------------------------------------------------------
void centre_ville::PlaceVehiculeTaxi(int x, int y, int NumTaxi) // v3.6
 {
  taxi *t=Taxi+NumTaxi-1;
  int NumPlace;
  t->DirDrnDepl=t->Dir;
  if (frmSimulation->SimulationSanglante&&cv->v[x][y].NbPietons) // v4.3
   cv->v[x][y].TuePietons();
  t->Place(x,y);
  t->NbCasesParcouruesDrnCourse++;
  t->NbCasesParcourues++;
  t->TourDrnDepl=TourCrt;
  t->DirDrnDepl=t->Dir;
  v[x][y].NumTaxi=NumTaxi;
  v[x][y].RedessineCase(false);
  switch(t->Situation)
   {
    case stDepart: t->FaitDescendrePietons();
                   if (!t->NbPersonnes)
                    {
                     t->Situation=stRetour;
                     t->TourDepotDrnCourse=TourCrt;
                    }
                   break;
    case stRetour:  if ((NumPlace=v[x][y].NumPlaceTaxi)&& // Si c'est une place de taxi
                        (PlaceTaxi[NumPlace-1].NumFile==t->NumFile)&& // de la file du taxi ET
                        PlaceTaxi[NumPlace-1].EstTeteFile()) // c'est la t�te de file ALORS
                     {
                      t->Situation=stAttente;
                      t->TourRetourDrnCourse=TourCrt;
                     }
                    break;
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::DefinitBus(int NumBus, int NumLigne) // v3.0
 {
  Bus[NumBus-1].Definit(NumLigne, LigneBus[NumLigne-1].NumArret[0]);
  LigneBus[NumLigne-1].AjouteBus(NumBus);
 }
//-----------------------------------------------------------------------------
void centre_ville::DefinitTram(int NumTram, int NumLigne) // v3.5
 {
  Tram[NumTram-1].Definit(NumLigne, LigneTram[NumLigne-1].NumArret[0]);
  LigneTram[NumLigne-1].AjouteTram(NumTram);
 }
//-----------------------------------------------------------------------------
bool centre_ville::PrepareBus() // v3.0
 {
  int i, NbBusADefinir=0, NumLigneCrt=0;
  // On d�finit 1 bus de 1 � 3 arr�ts. 2 bus de 4 � 6 arr�ts et 3 bus de 7 � 9 arr�ts
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++)
   if (LigneBus[i].NbArrets)
    NbBusADefinir+=1+(LigneBus[i].NbArrets-1)/3;
  if (DefinitNbBus(NbBusADefinir)!=NbBusADefinir)
   return false;
  for(i=0; i<NbBus; i++)
   {
    while((!LigneBus[NumLigneCrt].NbArrets)||
          (LigneBus[NumLigneCrt].NbBus==(1+(LigneBus[NumLigneCrt].NbArrets-1)/3)))
     NumLigneCrt=(NumLigneCrt+1)%NBMAXLIGNESBUSTRAM;
    DefinitBus(i+1, NumLigneCrt+1);
    NumLigneCrt=(NumLigneCrt+1)%NBMAXLIGNESBUSTRAM;
   }
  return true;
 }
//-----------------------------------------------------------------------------
bool centre_ville::PrepareTrams() // v3.5
 {
  int i, j, x, y, NbTramsADefinir=0, NumLigneCrt=0, NumArret, NumProchArret, dp, DistProchArret;
  bool ArretTrv;
  voie *Voie;
  // On d�finit 1 tram de 1 � 3 arr�ts. 2 tram de 4 � 6 arr�ts et 3 tram de 7 � 9 arr�ts
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++)
   if (LigneTram[i].NbArrets)
    NbTramsADefinir+=1+(LigneTram[i].NbArrets-1)/3;
  if (DefinitNbTrams(NbTramsADefinir)!=NbTramsADefinir)
   return false;
  for(i=0; i<NbTrams; i++)
   {
    while((!LigneTram[NumLigneCrt].NbArrets)||
          (LigneTram[NumLigneCrt].NbTrams==(1+(LigneTram[NumLigneCrt].NbArrets-1)/3)))
     NumLigneCrt=(NumLigneCrt+1)%NBMAXLIGNESBUSTRAM;
    DefinitTram(i+1, NumLigneCrt+1);
    NumLigneCrt=(NumLigneCrt+1)%NBMAXLIGNESBUSTRAM;
   }
  // On place les trams sur les arr�ts...
  for(ArretTrv=true,i=0; (ArretTrv)&&(i<NbTrams); i++)
   {
    for(ArretTrv=false,j=0; (!ArretTrv)&&(j<LigneTram[Tram[i].NumLigne-1].NbArrets); j++)
     { // Pour chaque tram, on cherche le premier arr�t libre dans l'ordre de leur ligne respective
      NumArret=LigneTram[Tram[i].NumLigne-1].NumArret[j];
      NumProchArret=LigneTram[Tram[i].NumLigne-1].NumArret[(j+1)%LigneTram[Tram[i].NumLigne-1].NbArrets];
      ArretTrv= ArretTram[NumArret-1].Defini()&&
                (!v[x=ArretTram[NumArret-1].x][y=ArretTram[NumArret-1].y].NumTram);
     }
    if (ArretTrv)
     {
      Voie=&(v[x][y]);
      // On trouve dans quel sens on va
      for(DistProchArret=DIST_INDEFINIE,dp=0; dp<Voie->NbDirPossSensVoieTram(indefinie); dp++)
       {
        if (Voie->DistArretTram[NumProchArret-1][dp]<DistProchArret)
         {
          DistProchArret=Voie->DistArretTram[NumProchArret-1][dp];
          Tram[i].Dir=Tram[i].DirDrnDepl=Tram[i].DirAvtDrnDepl=Voie->DirSensVoieTram(indefinie, dp);
          Tram[i].NumArretSvt=NumArret;
         }
       }
      // Et ENFIN on place le tram
      PlaceTram(x, y, i+1);
     }
   }
  if (!ArretTrv)
   {
    AfficheMessage( "\n\
Il n'est pas possible de placer tous les trams sur un arr�t de leur ligne respective !\n\
R�organisez votre r�seau de trams (les lignes ou les arr�ts) pour que le r�seau puisse d�marrer, puis r�essayez !",
                    "Impossible de placer les trams", tmAvertissement, 0, 0);
    return false;
   }
  else return true;
 }
//-----------------------------------------------------------------------------
bool centre_ville::PrepareTaxis() // v3.6. Les taxis ainsi que leurs places et leurs files
 {
  int NbTaxisADefinir=0, NumTaxi=0;
  for(int i=0; i<NbPlacesTaxi; i++) NbTaxisADefinir+=PlaceTaxi[i].Definie();
  if (DefinitNbTaxis(NbTaxisADefinir)!=NbTaxisADefinir) return false;
  for(int i=0; i<NbPlacesTaxi; i++)
   if (PlaceTaxi[i].Definie())
    {
     Taxi[NumTaxi].DefinitEtPlace(PlaceTaxi[i].NumFile, i);
     NumTaxi++;
    }
  return true;
 }
//-----------------------------------------------------------------------------
bool centre_ville::PreparePietons() // v2.0
 {
  int x,y,i,
      NbPietonsAvantCreation=NbPietons;
  direction Dir;
  if (DefinitNbPietons(NbPietonsAvantCreation)!=NbPietonsAvantCreation)
   return false;
  for(i=0; i<NbPietons; i++)
   {
    do { x=rand()%NbX; y=rand()%NbY; Dir=(direction)(1+rand()%4); }
    while(!v[x][y].PietonPeutAller(Dir));
    Pieton[i].Definit(x,y,Dir,0);
    v[x][y].AjoutePieton(i);
   }
  return true;
 }
//-----------------------------------------------------------------------------
void centre_ville::DeplacePieton(int NumPieton, int x, int y, direction d) // v2.0
 {
  v[Pieton[NumPieton].x][Pieton[NumPieton].y].RetirePieton(NumPieton);
  Pieton[NumPieton].Place(x,y);
  Pieton[NumPieton].DemiCasesParcourues++; // v3.0
  if (Pieton[NumPieton].Dir!=d) Pieton[NumPieton].Dir=d;
  Pieton[NumPieton].TourDrnDepl=TourCrt;
  if (Pieton[NumPieton].PsgPtTrv&&   // Si le pi�ton se dirige vers un passage pi�ton ET
      v[x][y].PassagePietons)        // Si le passage pi�ton est trouv� ALORS
   Pieton[NumPieton].PsgPtTrv=false; // On r�active les recherches de passages pi�tons
  v[x][y].AjoutePieton(NumPieton);
  frmSimulation->RedessineCase(x, y, false);
 }

//-----------------------------------------------------------------------------
bool centre_ville::ChangeDirectionSiPossible(int x, int y, dirposs dp) // ATTENTION : dp = N|E|S|O
 { // On change si...
  voie *vv=&(v[x][y]);
  if ((!vv->PassagePietons)&& // v3.5
      (!vv->NumArretBus)&&
      (!TourCrt)&&
      ((vv->DirPoss!=dp)||(!vv->PassageBus))&&
      ((!(vv->DirPoss&dp))||(!vv->Priorite[Dirdp[0][dp]-1])))
   {
    vv->DirPoss=(dirposs)(vv->DirPoss^dp);
    frmSimulation->RedessineCase(x, y, true);
    return true;
   }
  else return false;
 }
//-----------------------------------------------------------------------------
void centre_ville::CalculeDistances() // v3.0 : inclut �galement celles des arr�ts de bus. v3.5... Et des trams ! v3.6... Et des files de taxis !
 {
  int i;
  frmSimulation->StatusBar->Panels->Items[0]->Text="Calcul des distances aux �tapes...";
  frmSimulation->StatusBar->Repaint();
  for(i=0; i<NbEtapes; i++)
   {
    frmSimulation->StatusBar->Panels->Items[3]->Text=Format("%d/%d", ARRAYOFCONST((i+1, NbEtapes)));
    frmSimulation->StatusBar->Repaint();
    if (Etape[i].Definie())
     v[Etape[i].x][Etape[i].y].CalculeDistanceEtape(i, 0, 0, indefinie);
   }
  // v3.0
  frmSimulation->StatusBar->Panels->Items[0]->Text="Calcul des distances aux arr�ts de bus...";
  frmSimulation->StatusBar->Repaint();
  for(i=0; i<NbArretsBus; i++)
   {
    frmSimulation->StatusBar->Panels->Items[3]->Text=Format("%d/%d", ARRAYOFCONST((i+1, NbArretsBus)));
    frmSimulation->StatusBar->Repaint();
    if (ArretBus[i].Defini())
     v[ArretBus[i].x][ArretBus[i].y].CalculeDistanceArretBus(i, 0, indefinie);
   }
  // v3.5
  frmSimulation->StatusBar->Panels->Items[0]->Text="Calcul des distances aux arr�ts de tram...";
  frmSimulation->StatusBar->Repaint();
  for(i=0; i<NbArretsTram; i++)
   {
    frmSimulation->StatusBar->Panels->Items[3]->Text=Format("%d/%d", ARRAYOFCONST((i+1, NbArretsTram)));
    frmSimulation->StatusBar->Repaint();
    if (ArretTram[i].Defini())
     v[ArretTram[i].x][ArretTram[i].y].CalculeDistanceArretTram(i, 0, indefinie);
   }
  // v3.6
  frmSimulation->StatusBar->Panels->Items[0]->Text="Calcul des distances aux files de taxi...";
  frmSimulation->StatusBar->Repaint();
  for(i=0; i<NbFilesTaxi; i++)
   {
    frmSimulation->StatusBar->Panels->Items[3]->Text=Format("%d/%d", ARRAYOFCONST((i+1, NbFilesTaxi)));
    frmSimulation->StatusBar->Repaint();
    v[PlaceTaxi[FileTaxi[i].NumPlaceQueue].x][PlaceTaxi[FileTaxi[i].NumPlaceQueue].y].CalculeDistanceFileTaxi(i, 0, indefinie);
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::RessuscitePietons() // v4.3.1
 {
  for(int i=0; i<NbPietons; i++)
   {
    pieton *p=Pieton+i;
    if (p->Ecrase)
     {
      p->Ecrase=false;
      frmSimulation->RedessineCase(p->x, p->y, true);
     }
   }
 }
//-----------------------------------------------------------------------------
void __fastcall centre_ville::EffectueTourSimulation()
 {
  int i, j;
  TourEnCours=true;
  NbVehiculesDeplaces=0;
  if (frmSimulation->ResurrectionDemandee) // v4.3.1
   {
    RessuscitePietons();
    frmSimulation->ResurrectionDemandee=false;
   }
  // 0. On d�place les pi�tons
  for(i=0; i<NbX; i++)
   for(j=0; j<NbY; j++)
    if (v[i][j].NbPietons)
     v[i][j].DeplacePietons();

  // 1. On calcule les priorit�s de passage sur chaque case de la voie
  for(i=0; i<NbX; i++)
   for(j=0; j<NbY; j++)
    v[i][j].CalculeProchainVehiculeOuBusOuTramOuTaxi();

  // 2. On d�place les v�hicules
  for(i=0; i<NbX; i++)
   for(j=0; j<NbY; j++)
    v[i][j].DeplaceVehiculeOuBusOuTramOuTaxi();

  // 3. On fait tourner les feux...
  for(i=0; i<NbFeux; i++) Feu[i].Evolue();
  for(i=0; i<NbFeux; i++) Feu[i].ChangeEtat();

  // 4. On sort les voitures des �tapes sur la voie
  for(i=0; i<NbEtapes; i++)
   Etape[i].PlaceProchainVehicule();
  // 4bis. Ainsi que les bus du d�p�t. v3.0
  DepotBus.PlaceProchainBus();

  // 5a. On calcule la prochaine direction de chaque v�hicule
  for(i=0; i<NbVehicules; i++)
   if (Vehicule[i].Defini())
    Vehicule[i].CalculeProchaineDirection(); // Vehicule[i].Dir d�fini
  // 5b. Ainsi que celle des bus. v3.0
  for(i=0; i<NbBus; i++)
   if (Bus[i].Defini())
    Bus[i].CalculeProchaineDirection(); // Bus[i].Dir d�fini
  // 5c. Ainsi que celle des trams. v3.5
  for(i=0; i<NbTrams; i++)
   if (Tram[i].Defini())
    Tram[i].CalculeProchaineDirection(); // Tram[i].Dir d�fini
  // 5d. Ainsi que celle des taxis. v3.6
  for(i=0; i<NbTaxis; i++)
   Taxi[i].CalculeProchaineDirection(); // Taxi[i].Dir d�fini

  // 6a. On rafra�chit les v�hicules (la direction a pu chang�)
  for(i=0; i<2*NbEtapes; i++)
   if (Vehicule[i*(NbVehicules/NbEtapes/2)].Defini())
    frmSimulation->RedessineCase( Vehicule[i*(NbVehicules/NbEtapes/2)].x,
                                  Vehicule[i*(NbVehicules/NbEtapes/2)].y,
                                  false);
  // 6b. Et les bus (la direction a pu chang�). v3.0
  for(i=0; i<NbBus; i++)
   if (Bus[i].Defini())
    frmSimulation->RedessineCase( Bus[i].x, Bus[i].y, false);
  // 6c. Et les trams (la direction a pu chang�). v3.5
  for(i=0; i<NbTrams; i++)
   if (Tram[i].Defini())
    frmSimulation->RedessineCase( Tram[i].x, Tram[i].y, false);
  // 6d. Et les taxis (la direction a pu chang�). v3.6
  for(i=0; i<NbTaxis; i++)
   frmSimulation->RedessineCase( Taxi[i].x, Taxi[i].y, false);

  // 7. On affiche les stats...
  Stats[TourCrt%NbToursStats].Definit();
  if (frmStatistiques->Visible) frmStatistiques->PaintBoxStats->Repaint();
  if (frmStatsVehicules->Visible) frmStatsVehicules->RafraichitInfos();
  if (frmInfosVehicule->Visible) frmInfosVehicule->RafraichitInfos();
  if (frmInfosBus->Visible) frmInfosBus->RafraichitInfos(); // v3.0
  if (frmInfosTram->Visible) frmInfosTram->RafraichitInfos(); // v3.5
  if (frmInfosTaxi->Visible) frmInfosTaxi->RafraichitInfos(); // v3.6
  if (frmInfosPieton->Visible) frmInfosPieton->RafraichitInfos(); // v3.0
  if (frmRecherche&&frmRecherche->Visible)
   {
    if (frmRecherche->RadioButtonVehicule->Checked)
     frmRecherche->CSpinEditVehiculeChange(frmRecherche->CSpinEditVehicule);
    if (frmRecherche->RadioButtonPieton->Checked)
     frmRecherche->CSpinEditPietonChange(frmRecherche->CSpinEditPieton);
    if (frmRecherche->RadioButtonBus->Checked) // v3.0
     frmRecherche->CSpinEditBusChange(frmRecherche->CSpinEditBus);
    if (frmRecherche->RadioButtonTram->Checked) // v3.5
     frmRecherche->CSpinEditTramChange(frmRecherche->CSpinEditTram);
    if (frmRecherche->RadioButtonTaxi->Checked) // v3.6
     frmRecherche->CSpinEditTaxiChange(frmRecherche->CSpinEditTaxi);
   }

  TourCrt+=(NbVehiculesArrives<NbVehicules);
  TourEnCours=false;
 }
//-----------------------------------------------------------------------------
bool centre_ville::Charge(int hfile)
 {
  int i, j;
  bool Ok;
  NbPietons=-1;
  Ok=FileRead(hfile, &NbFeux, sizeof(NbFeux));
  if (NbFeux>=VERSIONMIN) // v3.0
   { // Version stock�e
    VersionFichier=NbFeux;
    Ok=FileRead(hfile, &NbFeux, sizeof(NbFeux)); // On relit le nombre de feux
   }
  else // Version non stock�e compatible (2.0 <= version < 3.0)
   VersionFichier=VERSIONANC;
  if (VersionFichier>VERSION) return false; // v3.5 : n'ouvre pas les fichier de simulation g�n�r�s par une version ult�rieure de la version actuelle (format de fichier)
  if (VersionFichier<0x400) // On charge les dimensions de la zone
   {
    NbX=NBXDEF;
    NbY=NBYDEF;
   }
  else
   Ok=FileRead(hfile, &NbX, sizeof(NbX))&&
      FileRead(hfile, &NbY, sizeof(NbY));
  CreeZone();
  if (Ok&&(Ok=FileRead(hfile, &NbEtapes, sizeof(NbEtapes))&&
              FileRead(hfile, &NbVehicules, sizeof(NbVehicules))&&
              FileRead(hfile, &NbPietons, sizeof(NbPietons))&&
              ((VersionFichier<0x300)|| // v3.0
               (FileRead(hfile, &NbArretsBus, sizeof(NbArretsBus))&&
                FileRead(hfile, &NbLignesBus, sizeof(NbLignesBus))))&&
              ((VersionFichier<0x350)|| // v3.5
               (FileRead(hfile, &NbArretsTram, sizeof(NbArretsTram))&&
                FileRead(hfile, &NbLignesTram, sizeof(NbLignesTram))))&&
              ((VersionFichier<0x360)|| // v3.6
               (FileRead(hfile, &NbPlacesTaxi, sizeof(NbPlacesTaxi))&&
                FileRead(hfile, &NbTaxis, sizeof(NbTaxis))))&&
              FileRead(hfile, &DureeVert, sizeof(DureeVert))&&
              FileRead(hfile, &DureeOrange, sizeof(DureeOrange))&&
              FileRead(hfile, &DureeRouge, sizeof(DureeRouge))&&
              FileRead(hfile, &AttenteMaxVeh, sizeof(AttenteMaxVeh))&&
              FileRead(hfile, &NbToursParSeconde, sizeof(NbToursParSeconde))&&
              FileRead(hfile, &NbToursStats, sizeof(NbToursStats))&&
              FileRead(hfile, &QuadrillageStats, sizeof(QuadrillageStats))&&
              FileRead(hfile, &TypeStats, sizeof(TypeStats))&&
              FileRead(hfile, &NbVitesses, sizeof(NbVitesses))&&
              FileRead(hfile, &NbMaxCasesDetectPsgPt, sizeof(NbMaxCasesDetectPsgPt))&&
              FileRead(hfile, &ProbaDirPsgPt, sizeof(ProbaDirPsgPt))&&
              ((VersionFichier<0x300)|| // v3.0
               (FileRead(hfile, &NbMaxCasesDetectArretBus, sizeof(NbMaxCasesDetectArretBus))&&
                FileRead(hfile, &ProbaDirArretBus, sizeof(ProbaDirArretBus))&&
                FileRead(hfile, &ProbaArretBusDmd, sizeof(ProbaArretBusDmd))&&
                FileRead(hfile, &NbMaxPersonnesBus, sizeof(NbMaxPersonnesBus))&&
                FileRead(hfile, &NbToursStopArretBus, sizeof(NbToursStopArretBus))&&
                FileRead(hfile, &NbMaxToursAttenteBus, sizeof(NbMaxToursAttenteBus))))&&
              ((VersionFichier<0x350)|| // v3.5
               (FileRead(hfile, &NbMaxCasesDetectArretTram, sizeof(NbMaxCasesDetectArretTram))&&
                FileRead(hfile, &ProbaDirArretTram, sizeof(ProbaDirArretTram))&&
                FileRead(hfile, &ProbaArretTramDmd, sizeof(ProbaArretTramDmd))&&
                FileRead(hfile, &NbMaxPersonnesTram, sizeof(NbMaxPersonnesTram))&&
                FileRead(hfile, &NbToursStopArretTram, sizeof(NbToursStopArretTram))&&
                FileRead(hfile, &NbMaxToursAttenteTram, sizeof(NbMaxToursAttenteTram))))&&
              ((VersionFichier<0x360)|| // v3.6
               (FileRead(hfile, &NbMaxCasesDetectFileTaxi, sizeof(NbMaxCasesDetectFileTaxi))&& // v3.6
                FileRead(hfile, &ProbaDirFileTaxi, sizeof(ProbaDirFileTaxi))&&
                FileRead(hfile, &ProbaArretTaxiDmd, sizeof(ProbaArretTaxiDmd))&&
                FileRead(hfile, &NbMaxPersonnesTaxi, sizeof(NbMaxPersonnesTaxi))&&
                FileRead(hfile, &NbMaxToursAttenteTaxi, sizeof(NbMaxToursAttenteTaxi))))));
  if (Ok&&NbFeux&&(Ok=!!(Feu=new feu[(ParamsInchanges&&(SvgNbFeux>NbFeux))?SvgNbFeux:NbFeux])))
   for(i=0; Ok&&(i<NbFeux); i++)
    {
     Ok=Feu[i].Charge(hfile);
     Feu[i].AffecteNumero(i+1);
    }
  if (Ok&&NbEtapes&&(Ok=!!(Etape=new etape[(ParamsInchanges&&(SvgNbEtapes>NbEtapes))?SvgNbEtapes:NbEtapes])))
   for(i=0; Ok&&(i<NbEtapes); i++)
    {
     Ok=Etape[i].Charge(hfile);
     Etape[i].AffecteNumero(i+1);
    }
  if (Vehicule) { delete[] Vehicule; Vehicule=NULL; }
  if (Pieton) { delete[] Pieton; Pieton=NULL; }
  if (VersionFichier>=0x300) // v3.0
   { // D�pot, arr�ts et lignes de bus
    Ok=DepotBus.Charge(hfile);
    if (Ok&&NbArretsBus&&(Ok=!!(ArretBus=new arret_bus[(ParamsInchanges&&(SvgNbArretsBus>NbArretsBus))?SvgNbArretsBus:NbArretsBus])))
     for(i=0; Ok&&(i<NbArretsBus); i++)
      {
       Ok=ArretBus[i].Charge(hfile);
       ArretBus[i].AffecteNumero(i+1);
      }
    if (Ok)
     for(i=0; Ok&&(i<NBMAXLIGNESBUSTRAM); i++)
      {
       Ok=LigneBus[i].Charge(hfile);
       LigneBus[i].AffecteNumero(i+1);
      }
   }
  if (VersionFichier>=0x350) // v3.5
   { // Arr�ts et lignes de tram
    if (Ok&&NbArretsTram&&(Ok=!!(ArretTram=new arret_tram[(ParamsInchanges&&(SvgNbArretsTram>NbArretsTram))?SvgNbArretsTram:NbArretsTram])))
     for(i=0; Ok&&(i<NbArretsTram); i++)
      {
       Ok=ArretTram[i].Charge(hfile);
       ArretTram[i].AffecteNumero(i+1);
      }
    if (Ok)
     for(i=0; Ok&&(i<NBMAXLIGNESBUSTRAM); i++)
      {
       Ok=LigneTram[i].Charge(hfile);
       LigneTram[i].AffecteNumero(i+1);
      }
   }
  if (VersionFichier>=0x360) // v3.6
   { // Places de Taxis
    if (Ok&&NbPlacesTaxi&&(Ok=!!(PlaceTaxi=new place_taxi[(ParamsInchanges&&(SvgNbPlacesTaxi>NbPlacesTaxi))?SvgNbPlacesTaxi:NbPlacesTaxi])))
     for(i=0; Ok&&(i<NbPlacesTaxi); i++)
      {
       Ok=PlaceTaxi[i].Charge(hfile);
       PlaceTaxi[i].AffecteNumero(i+1);
      }
   }
  for(i=0; Ok&&(i<NbX); i++)
   for(j=0; Ok&&(j<NbY); j++)
    Ok=v[i][j].Charge(hfile);
  if (NbPietons==-1) NbPietons=0; // Si version sans pi�tons alors pas de pi�ton !
  if (ParamsInchanges)
   {
    if (SvgNbFeux>NbFeux) NbFeux=SvgNbFeux;
    if (SvgNbEtapes>NbEtapes) NbEtapes=SvgNbEtapes;
    if (SvgNbVehicules>NbVehicules) NbVehicules=SvgNbVehicules;
    if (SvgNbPietons>NbPietons) NbPietons=SvgNbPietons;
    if (SvgNbArretsBus>NbArretsBus) NbArretsBus=SvgNbArretsBus; // v3.0
    if (SvgNbArretsTram>NbArretsTram) NbArretsTram=SvgNbArretsTram; // v3.5
    if (SvgNbPlacesTaxi>NbPlacesTaxi) NbPlacesTaxi=SvgNbPlacesTaxi; // v3.6
   }
  return Ok;
 }
//-----------------------------------------------------------------------------
bool centre_ville::Sauve(int hfile)
 {
  int i, j, VersionCourante=VERSION;
  bool Ok;
  Ok=FileWrite(hfile, &VersionCourante, sizeof(VersionCourante))&& // v3.0
     FileWrite(hfile, &NbFeux, sizeof(NbFeux))&&
     FileWrite(hfile, CopieEnCours?&NbXc:&NbX, sizeof(NbX))&& // v4.0.1 (CopieEnCours)
     FileWrite(hfile, CopieEnCours?&NbYc:&NbY, sizeof(NbY))&& // v4.0.1 (CopieEnCours)
     FileWrite(hfile, &NbEtapes, sizeof(NbEtapes))&&
     FileWrite(hfile, &NbVehicules, sizeof(NbVehicules))&&
     FileWrite(hfile, &NbPietons, sizeof(NbPietons))&& // v2.0
     FileWrite(hfile, &NbArretsBus, sizeof(NbArretsBus))&& // v3.0
     FileWrite(hfile, &NbLignesBus, sizeof(NbLignesBus))&& // v3.0
     FileWrite(hfile, &NbArretsTram, sizeof(NbArretsTram))&& // v3.5
     FileWrite(hfile, &NbLignesTram, sizeof(NbLignesTram))&& // v3.5
     FileWrite(hfile, &NbPlacesTaxi, sizeof(NbPlacesTaxi))&& // v3.6
     FileWrite(hfile, &NbTaxis, sizeof(NbTaxis))&& // v3.6
     FileWrite(hfile, &DureeVert, sizeof(DureeVert))&&
     FileWrite(hfile, &DureeOrange, sizeof(DureeOrange))&&
     FileWrite(hfile, &DureeRouge, sizeof(DureeRouge))&&
     FileWrite(hfile, &AttenteMaxVeh, sizeof(AttenteMaxVeh))&&
     FileWrite(hfile, &NbToursParSeconde, sizeof(NbToursParSeconde))&&
     FileWrite(hfile, &NbToursStats, sizeof(NbToursStats))&&
     FileWrite(hfile, &QuadrillageStats, sizeof(QuadrillageStats))&&
     FileWrite(hfile, &TypeStats, sizeof(TypeStats))&&
     FileWrite(hfile, &NbVitesses, sizeof(NbVitesses))&&
     FileWrite(hfile, &NbMaxCasesDetectPsgPt, sizeof(NbMaxCasesDetectPsgPt))&&
     FileWrite(hfile, &ProbaDirPsgPt, sizeof(ProbaDirPsgPt))&&
     FileWrite(hfile, &NbMaxCasesDetectArretBus, sizeof(NbMaxCasesDetectArretBus))&& // v3.0
     FileWrite(hfile, &ProbaDirArretBus, sizeof(ProbaDirArretBus))&& // v3.0
     FileWrite(hfile, &ProbaArretBusDmd, sizeof(ProbaArretBusDmd))&& // v3.0
     FileWrite(hfile, &NbMaxPersonnesBus, sizeof(NbMaxPersonnesBus))&& // v3.0
     FileWrite(hfile, &NbToursStopArretBus, sizeof(NbToursStopArretBus))&& // v3.0
     FileWrite(hfile, &NbMaxToursAttenteBus, sizeof(NbMaxToursAttenteBus))&& // v3.0
     FileWrite(hfile, &NbMaxCasesDetectArretTram, sizeof(NbMaxCasesDetectArretTram))&& // v3.5
     FileWrite(hfile, &ProbaDirArretTram, sizeof(ProbaDirArretTram))&& // v3.5
     FileWrite(hfile, &ProbaArretTramDmd, sizeof(ProbaArretTramDmd))&& // v3.5
     FileWrite(hfile, &NbMaxPersonnesTram, sizeof(NbMaxPersonnesTram))&& // v3.5
     FileWrite(hfile, &NbToursStopArretTram, sizeof(NbToursStopArretTram))&& // v3.5
     FileWrite(hfile, &NbMaxToursAttenteTram, sizeof(NbMaxToursAttenteTram))&& // v3.5
     FileWrite(hfile, &NbMaxCasesDetectFileTaxi, sizeof(NbMaxCasesDetectFileTaxi))&& // v3.5
     FileWrite(hfile, &ProbaDirFileTaxi, sizeof(ProbaDirFileTaxi))&& // v3.5
     FileWrite(hfile, &ProbaArretTaxiDmd, sizeof(ProbaArretTaxiDmd))&& // v3.5
     FileWrite(hfile, &NbMaxPersonnesTaxi, sizeof(NbMaxPersonnesTaxi))&& // v3.5
     FileWrite(hfile, &NbMaxToursAttenteTaxi, sizeof(NbMaxToursAttenteTaxi)); // v3.5

  for(i=0; Ok&&(i<NbFeux); i++) Ok=Feu[i].Sauve(hfile);
  for(i=0; Ok&&(i<NbEtapes); i++) Ok=Etape[i].Sauve(hfile);
  Ok=DepotBus.Sauve(hfile);
  for(i=0; Ok&&(i<NbArretsBus); i++) Ok=ArretBus[i].Sauve(hfile); // v3.0
  for(i=0; Ok&&(i<NBMAXLIGNESBUSTRAM); i++) Ok=LigneBus[i].Sauve(hfile); // v3.0. Attention : tableau statique
  for(i=0; Ok&&(i<NbArretsTram); i++) Ok=ArretTram[i].Sauve(hfile); // v3.5
  for(i=0; Ok&&(i<NBMAXLIGNESBUSTRAM); i++) Ok=LigneTram[i].Sauve(hfile); // v3.5. Attention : tableau statique
  for(i=0; Ok&&(i<NbPlacesTaxi); i++) Ok=PlaceTaxi[i].Sauve(hfile); // v3.6
  if (CopieEnCours) // v4.0.1
   for(i=Xc; Ok&&(i<Xc+NbXc); i++)
    for(j=Yc; Ok&&(j<Yc+NbYc); j++)
     Ok=v[i][j].Sauve(hfile);
  else
   for(i=0; Ok&&(i<NbX); i++)
    for(j=0; Ok&&(j<NbY); j++)
     Ok=v[i][j].Sauve(hfile);
  return Ok;
 }
//-----------------------------------------------------------------------------
void centre_ville::Verifie(AnsiString &asMsgErr)
 {
  int i, j;
  asMsgErr="";
  if (NbFeux<0)
   asMsgErr+=Format("Le nombre de feux est incorrect (%d)\n", ARRAYOFCONST((NbFeux)));
  if (NbEtapes<2)
   asMsgErr+=Format("Le nombre d'�tapes est incorrect (%d)\n", ARRAYOFCONST((NbEtapes)));
  if (NbVehicules<=0)
   asMsgErr+=Format("Le nombre de v�hicules est incorrect (%d)\n", ARRAYOFCONST((NbVehicules)));
  else
   if ((NbVehicules<NBMAXVEHICULES)&&
       ((!NbEtapes)||
        (NbEtapes==1)||
        (NbVehicules%(NbEtapes*(NbEtapes-1)))))
    asMsgErr+=Format("Le nombre de v�hicules ne permet pas une simulation �quilibr�e (%d)\n", ARRAYOFCONST((NbVehicules)));
  if (NbPietons<0)
   asMsgErr+=Format("Le nombre de pi�tons est incorrect (%d)\n", ARRAYOFCONST((NbPietons)));
  if (DureeVert<0)
   asMsgErr+=Format("La dur�e du feu vert par d�faut est incorrecte (%d)\n", ARRAYOFCONST((DureeOrange)));
  if (DureeOrange<0)
   asMsgErr+=Format("La dur�e du feu orange est incorrecte (%d)\n", ARRAYOFCONST((DureeOrange)));
  if (DureeRouge<0)
   asMsgErr+=Format("La dur�e du feu rouge par d�faut est incorrecte (%d)\n", ARRAYOFCONST((DureeOrange)));
  if (AttenteMaxVeh<0)
   asMsgErr+=AnsiString("La dur�e d'attente maximale d'un v�hicule est incorrecte\n");
  if (NbToursParSeconde<0)
   asMsgErr+=AnsiString("Le nombre de tours par seconde est incorrect\n");
  if (NbToursStats<0)
   asMsgErr+=Format("Le nombre de tours soumis aux statistiques est incorrect (%d)\n", ARRAYOFCONST((NbToursStats)));
  if ((TypeStats<par_nombre)||(TypeStats>par_pourcentage))
   asMsgErr+=Format("Le type de statistique est incorrect (%d)\n", ARRAYOFCONST((TypeStats)));
  if ((NbVitesses<1)||(NbVitesses>3))
   asMsgErr+=Format("Le nombre de vitesses est incorrecte (%d)\n", ARRAYOFCONST((NbVitesses)));
  if ((NbMaxCasesDetectPsgPt<0)||(NbMaxCasesDetectPsgPt>5))
   asMsgErr+=Format("Le nombre de case maximum pour la d�tection de passage pi�tons est incorrect (%d)\n", ARRAYOFCONST((NbMaxCasesDetectPsgPt)));
  if ((ProbaDirPsgPt<0)||(ProbaDirPsgPt>100))
   asMsgErr+=Format("La probabilit� qu'un pi�ton se dirige vers un passage pi�tons d�tect� est incorrecte (%d)\n", ARRAYOFCONST((ProbaDirPsgPt)));
  if (NbArretsBus<0)
   asMsgErr+=Format("Le nombre d'arr�ts de bus est incorrect (%d)\n", ARRAYOFCONST((NbArretsBus)));
  if (NbLignesBus<0)
   asMsgErr+=Format("Le nombre de lignes de bus est incorrect (%d)\n", ARRAYOFCONST((NbLignesBus)));
  if (NbArretsTram<0)
   asMsgErr+=Format("Le nombre d'arr�ts de tram est incorrect (%d)\n", ARRAYOFCONST((NbArretsTram)));
  if (NbLignesTram<0)
   asMsgErr+=Format("Le nombre de lignes de tram est incorrect (%d)\n", ARRAYOFCONST((NbLignesTram)));
  if (NbPlacesTaxi<0)
   asMsgErr+=Format("Le nombre de places de taxi est incorrect (%d)\n", ARRAYOFCONST((NbPlacesTaxi)));
  if (NbTaxis<0)
   asMsgErr+=Format("Le nombre de taxis est incorrect (%d)\n", ARRAYOFCONST((NbTaxis)));

  for(i=0; i<NbX; i++)
   for(j=0; j<NbY; j++)
    v[i][j].Verifie(asMsgErr);
  for(i=0; i<NbFeux; i++)
   Feu[i].Verifie(asMsgErr, Format("Feu n�%d", ARRAYOFCONST((i+1))));
  for(i=0; i<NbEtapes; i++)
   Etape[i].Verifie(asMsgErr);
  if (Vehicule)
   for(i=0; i<NbVehicules; i++)
    Vehicule[i].Verifie(asMsgErr);
  if (Pieton)
   for(i=0; i<NbPietons; i++)
    Pieton[i].Verifie(asMsgErr);
  if (Bus) // v3.0.4 (un oubli)
   for(i=0; i<NbBus; i++)
    Bus[i].Verifie(asMsgErr);
  if (ArretBus) // v3.0
   for(i=0; i<NbArretsBus; i++)
    ArretBus[i].Verifie(asMsgErr);
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++) // v3.0
    LigneBus[i].Verifie(asMsgErr);
  if (Tram) // v3.5
   for(i=0; i<NbTrams; i++)
    Tram[i].Verifie(asMsgErr);
  if (ArretTram) // v3.5
   for(i=0; i<NbArretsTram; i++)
    ArretTram[i].Verifie(asMsgErr);
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++) // v3.5
    LigneTram[i].Verifie(asMsgErr);
  for(i=0; i<NbPlacesTaxi; i++)
   PlaceTaxi[i].Verifie(asMsgErr);
  DepotBus.Verifie(asMsgErr); // v3.03
 }
//-----------------------------------------------------------------------------
inline bool centre_ville::TourDeDeplacementVehicule(int NumeroVehicule) // v3.0.4
 {
  if ((TourCrt-Vehicule[NumeroVehicule].TourDepart)%NbVitesses <=
      (Vehicule[NumeroVehicule].NivPriorite?NbVitesses-1:NumeroVehicule%NbVitesses))
   return true;
  else
   {
    Vehicule[NumeroVehicule].NbToursRepos++; // v2.2.4
    return false;
   }
 }
//-----------------------------------------------------------------------------
inline bool centre_ville::TourDeDeplacementBus(int NumeroBus) // v3.0
 {
  if (!((TourCrt-Bus[NumeroBus].TourDepart)%NbVitesses))
   return true;
  else
   {
    Bus[NumeroBus].NbToursRepos++;
    return false;
   }
 }
//-----------------------------------------------------------------------------
inline bool centre_ville::TourDeDeplacementTram(int NumeroTram) // v3.5
 {
  if (!(TourCrt%NbVitesses))
   return true;
  else
   {
    Tram[NumeroTram].NbToursRepos++;
    return false;
   }
 }
//-----------------------------------------------------------------------------
inline bool centre_ville::TourDeDeplacementTaxi(int NumeroTaxi) // v3.6
 {
  if (!(TourCrt%NbVitesses))
   return true;
  else
   {
    Taxi[NumeroTaxi].NbToursRepos++;
    return false;
   }
 }
//-----------------------------------------------------------------------------
bool centre_ville::CopieValide() // v4.2.1
 {
  AnsiString asMsg;
  for(int i=0; i<NbEtapes; i++)
   if (Etape[i].Definie()&&(!DansSelectionEnCours(Etape+i)))
    asMsg=asMsg+"l'�tape n�"+IntToStr(i+1)+" "+asCoordonnees(Etape+i)+", ";
  if (DepotBus.Defini()&&(!DansSelectionEnCours(&DepotBus)))
   asMsg=asMsg+"le d�p�t de bus n�"+asCoordonnees(&DepotBus)+", ";
  for(int i=0; i<NbFeux; i++)
   if (Feu[i].Defini()&&(!DansSelectionEnCours(Feu+i)))
    asMsg=asMsg+"le feu n�"+IntToStr(i+1)+" "+asCoordonnees(Feu+i)+", ";
  for(int i=0; i<NbArretsBus; i++)
   if (ArretBus[i].Defini()&&(!DansSelectionEnCours(ArretBus+i)))
    asMsg=asMsg+"l'arr�t de bus n�"+IntToStr(i+1)+" "+asCoordonnees(ArretBus+i)+", ";
  for(int i=0; i<NbPlacesTaxi; i++)
   if (PlaceTaxi[i].Definie()&&(!DansSelectionEnCours(PlaceTaxi+i)))
    asMsg=asMsg+"la place de taxi n�"+IntToStr(i+1)+" "+asCoordonnees(PlaceTaxi+i)+", ";
  if (!asMsg.IsEmpty())
   {
    AfficheMessage("Les �l�ments suivants DOIVENT �TRE dans la s�lection :\n"+asMsg+"\n\nVeuillez soit les supprimer, soit les inclure dans la s�lection avant de r�essayer.", "Commande de copie impossible", tmAvertissement, 0, 0);
    return false;
   }
  else
   return true;
 }
//-----------------------------------------------------------------------------
void centre_ville::Genere(int x, int y, int d) // v4.2
 { // ATTENTION : d peut changer � l'int�rieur de Genere(...)
  int k=0;
  bool Ok=true,
       DejaFait[NBDIR+1]={false,false,false,false,false},
       AutreDirection=false;
  do
   { /* LE CODE EN COMMENTAIRE sert pour le d�bogage
    frmSimulation->DrawGridSimul->Col=x;
    frmSimulation->DrawGridSimul->Row=y;
    frmSimulation->RedessineCase(x,y,true); */
    int l=1+(LgrMinSgmtRoute*((d-1)%2?NbX:NbY))/10+ // Longueur du nouveau segment de route
          rand()%(1+((LgrMaxSgmtRoute-LgrMinSgmtRoute)*((d-1)%2?NbX:NbY))/10);
    //AfficheMessage("D�part du segment","("+IntToStr(x)+","+IntToStr(y)+"),"+asDir[d], tmInformation,0,0);
    bool //MemeDir=false, // pour d�bogage
         //TraverseeRoute=true, // pour d�bogage
         DirOpposee=false,
         EntreeIntersection=true;
    for(k=0,Ok=true,AutreDirection=false; Ok&&(k<=l); k++)
     {
      voie *vc=&(_V_(x,y,k,d)); // Case suivante
      Ok=(!(/*MemeDir=*/vc->DirPoss&PossDir[d]))&& // S'il s'agit d'une direction possible = d
         (!(DirOpposee=vc->DirPoss&InvPossDir[d]))&& // OU une direction oppos�e � d
         ((!vc->DirPoss)||
          (/*TraverseeRoute=*/(ProbaTraverseeRoute>rand()%10))|| // OU une travers�e de route refus�e, ALORS on NE TRACE pas le segment de route sur la case.
          (EntreeIntersection=(ProbaEntreeIntersection>rand()%10))); // OU une entr�e d'intersection ?
      if (Ok)
       {
        vc->DirPoss+=PossDir[d]; // On trace la route jusqu'� la case courante
        //frmSimulation->RedessineCase((x+k*dx[d])%NbX, (y+k*dy[d])%NbY, true);
        //AfficheMessage("Trac� de segment","("+IntToStr((x+k*dx[d])%NbX)+","+IntToStr((y+k*dy[d])%NbY)+"),"+IntToStr(k)+"/"+IntToStr(l)+","+asDir[d], tmInformation,0,0);
       }
     }
    if (!Ok) // Le segment N'a PAS �t� trac� jusqu'au bout
     {
      k--; // On revient sur la case pr�c�dente TRAC�E
      if (DirOpposee|| // SI direction OPPOSEE,
          (!EntreeIntersection)) // OU SI arriv�e sur une route refus�e
       { // ALORS on part A GAUCHE OU A DROITE (on �vite les deux probl�mes)
        //AfficheMessage("DirOppos�e||(!EntreeIntersection)","("+IntToStr((x+k*dx[d])%NbX)+","+IntToStr((y+k*dy[d])%NbY)+"),Pas Ok,"+IntToStr(k)+"/"+IntToStr(l)+","+asDir[d], tmInformation,0,0);
        int dd=1+(d+2*(rand()%2))%NBDIR;
        if (!k)
         DejaFait[dd]=true;
        else
         for(int i=0; i<NBDIR+1; i++) DejaFait[i]=false;
        if (k||(!DejaFait[dd])) // On teste si on n'a pas d�j� fait cette direction sur la m�me case...
         {
          x=(x+k*dx[d])%NbX;
          y=(y+k*dy[d])%NbY;
          d=dd;
          AutreDirection=true;
         }
       }
/*    else
       AfficheMessage("M�meDir||(!Travers�eRoute)","("+IntToStr((x+k*dx[d])%NbX)+","+IntToStr((y+k*dy[d])%NbY)+"),Pas Ok,"+IntToStr(k)+"/"+IntToStr(l)+","+asDir[d], tmInformation,0,0);
*/   }
    else // Le segment a �t� trac� jusqu'au bout : MAIS ATTENTION V(x,y,k,d) N'EST PAS TRAC� !!!
     {
      if ((_V_(x,y,k,d).DirPoss&(NESO-InvPossDir[d]))!=NESO-InvPossDir[d]) // peut-on continuer � cr�er des segments ?
       {
        if (ProbaSortieIntersection>rand()%10) // Cr�e-t-on une sortie d'intersection ?
         {
          //AfficheMessage("SortieIntersection","("+IntToStr((x+k*dx[d])%NbX)+","+IntToStr((y+k*dy[d])%NbY)+"),Ok,"+IntToStr(k)+"/"+IntToStr(l)+","+asDir[d], tmInformation,0,0);
          int dd;
          do { dd=1+rand()%NBDIR; } while((_V_(x,y,k,d).DirPoss&PossDir[dd])||(abs(d-dd)==2));
          Genere((x+k*dx[d])%NbX, (y+k*dy[d])%NbY, dd);
          //frmSimulation->DrawGridSimul->Col=x;
          //frmSimulation->DrawGridSimul->Row=y;
          //frmSimulation->RedessineCase(x,y,true);
          //AfficheMessage("RetourCreationNvBranche","("+IntToStr((x+k*dx[d])%NbX)+","+IntToStr((y+k*dy[d])%NbY)+"),Ok,"+IntToStr(k)+"/"+IntToStr(l)+","+asDir[d], tmInformation,0,0);
         }
        int dd;
        //AfficheMessage("PoursuiteSegment","("+IntToStr((x+k*dx[d])%NbX)+","+IntToStr((y+k*dy[d])%NbY)+"),Ok,"+IntToStr(k)+"/"+IntToStr(l)+","+asDir[d], tmInformation,0,0);
        do { dd=1+rand()%NBDIR; } while((_V_(x,y,k,d).DirPoss&PossDir[dd])||(abs(d-dd)==2));
        x=(x+k*dx[d])%NbX;
        y=(y+k*dy[d])%NbY;
        d=dd;
        AutreDirection=true;
       }
     }
   }
  while(AutreDirection);
 }
