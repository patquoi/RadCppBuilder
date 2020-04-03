//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <stdlib.h>
#include <time.h>
//---------------------------------------------------------------------------
#include "base.h"
#include "simul.h"
#include "f_simul.h"
#include "f_stats.h"
#include "f_statsv.h"
#include "f_infveh.h"
#include "f_infptn.h"
#include "f_infbus.h"
#include "f_inftram.h"
#include "f_inftaxi.h"
#include "f_infvehlib.h"
#include "f_rech.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define PEUT_ETRE_INDEFINI true
#define DOIT_ETRE_DEFINI   false
//---------------------------------------------------------------------------
// Pour DistParking
#define NORMAL      0
#define PRIORITAIRE 1
//---------------------------------------------------------------------------
#define AUCUN_FEU ((x==-1)&&(y==-1)&&(Dir==indefinie))
#define REMET_A_ZERO Definit(-1, -1, 0)
#define NUMVEHLIBPLACE(x) ((int)(0.5+(x)*(TauxRemplissageVehlib/100.0)))
//---------------------------------------------------------------------------

// v3.5 : remplacement des [5] par [NBDIR+1] et des [4] par [NBDIR]
const dirposs PossDir[NBDIR+1]={aucune, N, E, S, O},
              InvPossDir[NBDIR+1]={aucune, S, O, N, E},
              // 1=90°droite, 2=180°, 3=90°gauche
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
// (Dirdp[x][y] = (x+1)ème direction pour DirPoss=y
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
bool VerifierApresOuverture=false,
     VerifierAvantSimulation=false;
//---------------------------------------------------------------------------
int dx[NBDIR+1]={0, 0, 1, 0, NBXDEF-1}, // v4.0 (const int->int, DEF)
    dy[NBDIR+1]={0, NBYDEF-1, 0, 1, 0}, // v4.0 (const int->int, DEF)
    VersionFichier=0, // v3.0
    SvgNbFeux=0,
    SvgNbFeuxPieton=0, // v5.2
    SvgNbParkings=0,
    SvgNbVehicules=0,
    SvgNbVehlibs=0, // v5.3
    SvgNbPietons=0, // v2.0
    SvgNbArretsBus=0, // v3.0
    SvgNbArretsTram=0, // v3.5
    SvgNbPlacesTaxi=0, // v3.6
    SvgNbPlacesPark=0, // v5.0
    SvgNbPlacesVehlib=0; // v5.3
//---------------------------------------------------------------------------
centre_ville *cv=NULL;
//-----------------------------------------------------------------------------
template <class E> int IncrementeNombre(E **e, int &n) // v5.1
 {
  E *ee=new E[n+1];
  for(int i=0; i<n; i++)
   ee[i].Copie((*e)+i); // Effectue la copie des membres et affecte CopieEnCours=true pour
  ee[n].AffecteNumero(n+1); // v5.2 (oubli)
  ee[n].Initialise(); // v5.2 (oubli)
  delete[] *e; // ...empêcher de désallouer les instances membres lors de l'appel à delete[] e
  *e=ee;
  return ++n;
 };
//-----------------------------------------------------------------------------
/* Conditions d'utilisation
1. Exemple d'appel :  IncrementeNombre(&Feu, NbFeux)
2. La classe E doit avoir les définitions suivantes :

class E
 {
  bool CopieEnCours; // v5.1 (Si des propriétés sont des références)
  [...]
  E()
   {
    [..]
    CopieEnCours=false; // v5.1 (Si des propriétés sont des références)
   };
  void Copie(E *e) // v5.1
   {
    Numero=n;
    e->CopieEnCours=true; // (Si des propriétés sont des références)
    p1=f->p1;
    [...]
    pn=f->pn;
   };
  ~E()
   {
    if (!CopieEnCours) // v5.1 (Si des propriétés sont des références)
     {
      if (pa) delete[] pa;
      [...]
      if (pz) delete[] pz;
     }
   }
*/
//---------------------------------------------------------------------------
void AppelleAuChaos()
 {
  time_t t;
  srand((unsigned)time(&t)); 
 }
//-----------------------------------------------------------------------------
// Routines privées
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
   asMsgErr+=asSource+Format(": ordonnée incorrecte (%d)\n", ARRAYOFCONST((y)));
 }
//-----------------------------------------------------------------------------
void VerifieDirection(AnsiString asMsgErr, AnsiString asSource, direction d, bool PeutEtreIndefinie)
 {
  if (((d<indefinie)&&(PeutEtreIndefinie))||
      ((d<=indefinie)&&(!PeutEtreIndefinie))||
      (d>ouest))
   asMsgErr+=asSource+Format(": direction incorrecte (%d)\n", ARRAYOFCONST(((int)d))); // v5.4 enum as char type (cast int)
 }
//-----------------------------------------------------------------------------
void VerifiePriorite(AnsiString asMsgErr, AnsiString asSource, priorite p)
 {
  if ((p<a_droite)||(p>feux))
   asMsgErr+=asSource+Format(": priorité incorrecte (%d)\n", ARRAYOFCONST(((int)p))); // v5.4 enum as char type (cast int)
 }
//-----------------------------------------------------------------------------
void VerifieDirPoss(AnsiString asMsgErr, AnsiString asSource, dirposs dp)
 {
  if ((dp<aucune)||(dp>NESO))
   asMsgErr+=asSource+Format(": directions possibles incorrectes (%d)\n", ARRAYOFCONST(((int)dp))); // v5.4 enum as char type (cast int)
 }
//-----------------------------------------------------------------------------
void VerifieEtat(AnsiString asMsgErr, AnsiString asSource, etat_feu e)
 {
  if ((e<inactif)||(e>rouge))
   asMsgErr+=asSource+Format(": état incorrect (%d)\n", ARRAYOFCONST(((int)e))); // v5.4 enum as char type (cast int)
 }
//-----------------------------------------------------------------------------
void VerifieDmdVert(AnsiString asMsgErr, AnsiString asSource, dmd_vert dv)
 {
  if ((dv<arrivee_vehicule)||(dv>immediate))
   asMsgErr+=asSource+Format(": type de demande du vert incorrect (%d)\n", ARRAYOFCONST(((int)dv))); // v5.4 enum as char type (cast int)
 }
//-----------------------------------------------------------------------------
void VerifiePsgRouge(AnsiString asMsgErr, AnsiString asSource, psg_rouge pr)
 {
  if ((pr<prm_dmd)||(pr>immediat))
   asMsgErr+=asSource+Format(": type de passage au rouge incorrect (%d)\n", ARRAYOFCONST(((int)pr))); // v5.4 enum as char type (cast int)
 }
//-----------------------------------------------------------------------------
// Méthodes des classes
//-----------------------------------------------------------------------------
infection::infection(const centre_ville *cv) // Patient zéro initialisé à la création (centre_ville *cv) ou au démarrage de la simulation
 {
  TourDeb = 0;
  TourFin = cv->EpidemieInfectiosite; // au tour TourFin, le piéton n'est plus contagieux
  TourFatal = 0; // Permet de savoir le tour fatal (TourFatal + cv->EpidemieInfectiosite)
  NumDrnPieton = NumPrmPieton = 0; // Pas de patient source car patient zéro donc... vaut zéro !
  DrnRang = PrmRang = 0; // Patient zéro ben... vaut zéro !
  ChargeVirale = 1; // Incrémenté à chaque (ré)infection sur la période de contagion
  Svt = NULL;
 };
//-----------------------------------------------------------------------------
infection::infection(int Tour, int NumPieton, int Rang) // v5.4.1. NumPieton>0 (pieton::Numero+1)
 {
  TourDeb = Tour + 1; // Le piéton est contagieux à partir du tour suivant
  TourFin = Tour + 1 + cv->EpidemieInfectiosite;
  TourFatal = 0;
  NumDrnPieton = NumPrmPieton = NumPieton;
  DrnRang = PrmRang = Rang;
  ChargeVirale = 1;
  Svt = NULL;
 }
//-----------------------------------------------------------------------------
bool infection::Reinfecte(int Tour, int NumPieton, int Rang) // comme le constructeur mais pour une personne qui a déjà été infectée
 { // retourne vrai si la réinfection a bien eu lieu
  if ((Tour+1>=TourDeb)&&(Tour+1<=TourFin))
   {
	if (NumDrnPieton==NumPieton)
	  return false; // Un même piéton ne contamine pas deux fois de suite la même personne
	else
	 {
	  if (!TourFatal)
		TourFin = Tour + cv->EpidemieInfectiosite;
	  TourFin = Tour + cv->EpidemieInfectiosite;
	  NumDrnPieton = NumPieton;
	  DrnRang = Rang;
	  ChargeVirale++;
	  if (ChargeVirale==cv->EpidemieChargeFatale)
		TourFatal=Tour; // Mort programmée
	  return true;
	 }
   }
  else
   {
	if (Svt)
	  return Svt->Reinfecte(Tour, NumPieton, Rang);
	else
	 {
	  Svt = new infection(Tour, NumPieton, Rang);
	  return true;
	 }
   }
};
//-----------------------------------------------------------------------------
bool infection::DoitSuccomber(int Tour)
 {
  if (TourFatal)
	return (Tour >= TourFatal + cv->EpidemieInfectiosite);
  else
	if (Svt)
	  return Svt->DoitSuccomber(Tour);
	else
      return false;
 }
//-----------------------------------------------------------------------------
void pieton::Verifie(AnsiString &asMsgErr)
 {
  AnsiString asSource=Format("Piéton n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, DOIT_ETRE_DEFINI);
  VerifieDirection(asMsgErr, asSource, (direction)Dir, DOIT_ETRE_DEFINI);
  if ((DemiCase<0)||(DemiCase>1))
   asMsgErr+=asSource+Format(": valeur ½ case incorrecte (%d)\n", ARRAYOFCONST((DemiCase)));
 }
//-----------------------------------------------------------------------------
void pieton::ChercheFileTaxi() // v3.6
 {
  voie *v;
  int NumPlaceTaxi=0;
  direction DirPlace=indefinie,
			ProchDir=indefinie;
  if (!NumFileTaxi) // Cas improbable mais on ne sait jamais
   { // On abandonne la recherche de file de taxi
	FileTaxiTrv=false;
	return; // Numéro de file de taxi obligatoire pour que l'on puisse trouver la tête !
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
  if (!NumPlaceTaxi) // Pas trouvé de place de taxi aux allentours...
   { // On abandonne la recherche de file de taxi
	FileTaxiTrv=false;
	NumFileTaxi=0;
	return;
   }
  else
   if ((!cv->v[x][y].PassagePietons)&&(cv->PlaceTaxi[NumPlaceTaxi-1].EstTeteFile()))
    { // On a finalement trouvé la tête : il attend le taxi (bloque le piéton)
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
  else // Même direction : il faut contourner la case !
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
    // On a pas trouvé de direction, on abandonne la recherche
    FileTaxiTrv=false;
    NumFileTaxi=0;
   }
 }
//-----------------------------------------------------------------------------
bool pieton::EstContagieux()
 {
  if (EstVivant()&&Infection)
	return Infection->EstContagieux(cv->TourCrt);
  else
	return false;
 }
//-----------------------------------------------------------------------------
void pieton::EstContaminePar(int NumPieton, int Rang) // v5.4.1. NumPieton>0 (pieton::Numero+1)
 {// Utilisation : UnPieton->EstContaminePar(PietonContagieux->Numero, 1+PietonContagieux->DonneRang())
  if (Infection)
	Infection->Reinfecte(cv->TourCrt, NumPieton, Rang);
  else
	Infection = new infection(cv->TourCrt, NumPieton, Rang);
 }
//-----------------------------------------------------------------------------
int pieton::DonneRang()
 {
  if (Infection)
	return Infection->DonneRang(cv->TourCrt);
  else
	return -1;
 }
//-----------------------------------------------------------------------------
int pieton::DonneChargeVirale()
 {
  if (Infection)
	return Infection->DonneChargeVirale(cv->TourCrt);
  else
	return 0;
 }
//-----------------------------------------------------------------------------
bool pieton::DoitSuccomber()
 {
  if (Infection)
	return Infection->DoitSuccomber(cv->TourCrt);
  else
    return false;
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
void feu::AjouteFeuPtn(int NumNvFeu) // v5.2
 {
  int i, *NvNumFeuxPtn;
  NbFeuxPtn++;
  NvNumFeuxPtn=new int[NbFeuxPtn];
  for(i=0; i<NbFeuxPtn-1; i++)
   NvNumFeuxPtn[i]=NumFeuxPtn[i];
  NvNumFeuxPtn[NbFeuxPtn-1]=NumNvFeu;
  if (NumFeuxPtn) delete[] NumFeuxPtn;
  NumFeuxPtn=NvNumFeuxPtn;
 }
//-----------------------------------------------------------------------------
void feu::RetireFeuDmd(int NumFeu) // NumFeu(>0) doit être dans NumFeuxDmd[]
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
void feu::RetireFeuAtt(int NumFeu) // NumFeu(>0) doit être dans NumFeuxAtt[]
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
                // On informe quels sont les prochains feux à se mettre au vert
                for(i=0; i<NbFeuxDmd; i++)
                 if ((cv->Feu[NumFeuxDmd[i]-1].Etat==rouge)&&
                     (!cv->Feu[NumFeuxDmd[i]-1].ProchainVert)&&
                     (cv->Feu[NumFeuxDmd[i]-1].DemandeVert||
                      (cv->Feu[NumFeuxDmd[i]-1].TourDrnChgEtat<cv->TourCrt)))
                  {
                   cv->Feu[NumFeuxDmd[i]-1].ProchainVert=true;
                   cv->Feu[NumFeuxDmd[i]-1].TourDrnChgEtat=cv->TourCrt;
                  }
                // v5.2 : ...Et les feux piétons liés...  
                for(i=0; i<NbFeuxPtn; i++)
                 if ((cv->FeuP[NumFeuxPtn[i]-1].Etat==rouge)&& // ETAT=Etat pour les feux adverses et non l'état pour les piétons (compte le temps de traversée
                     (!cv->FeuP[NumFeuxPtn[i]-1].ProchainVert)&&
                     (cv->FeuP[NumFeuxPtn[i]-1].DemandeVert||
                      (cv->FeuP[NumFeuxPtn[i]-1].TourDrnChgEtat<cv->TourCrt)))
                  {
                   cv->FeuP[NumFeuxPtn[i]-1].ProchainVert=true;
                   cv->FeuP[NumFeuxPtn[i]-1].TourDrnChgEtat=cv->TourCrt;
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
      NumVL, // v5.3
      NumBus, // v3.0
      NumTram, // v3.5
      NumTaxi; // v3.6
  ProchainEtat=Etat; // Par défaut
  switch(Etat)
   {
    case inactif : break;
    case vert:     // Si (rouge demandé ou passage immediat) et durée vert écoulée -> Orange
                   if (((RougeDemande&&(TourDrnChgEtat<cv->TourCrt))||
                        (TypePsgRouge==immediat))&&
                       (cv->TourCrt-TourDrnChgEtat>DureeVert))
                    DefinitProchainEtat();
                   break;
    case orange:   if (cv->TourCrt-TourDrnChgEtat>cv->DureeOrange)
                    DefinitProchainEtat();
                   break;
    case rouge:    // Le vert n'est pas encore demandé
                   if (!DemandeVert)
                    {
                     if ((cv->TourCrt-TourDrnChgEtat>DureeRouge)&& // la durée du rouge est écoulée ET
                         ((TypeDmdVert==immediate)|| // La demande est immédiate Ou
                          ((NumVeh=cv->v[x][y].NumVehicule)&& // un véhicule est sur la case et
                           (cv->Vehicule[NumVeh-1].Dir==Dir))|| // dans la direction du feu... Ou
                          ((NumVL=cv->v[x][y].NumVehlib)&& // (v5.3) un vehlib est sur la case et
                           (cv->Vehlib[NumVL-1].Dir==Dir))|| // dans la direction du feu... Ou
                          ((NumBus=cv->v[x][y].NumBus)&& // un bus est sur la case et
                           (cv->Bus[NumBus-1].Dir==Dir))||
                          ((NumTram=cv->v[x][y].NumTram)&& // un tram est sur la case et
                           (cv->Tram[NumTram-1].Dir==Dir))|| // dans la direction du feu... (v3.5)
                          ((NumTaxi=cv->v[x][y].NumTaxi)&& // un taxi est sur la case et
                           (cv->Taxi[NumTaxi-1].Dir==Dir)))) // dans la direction du feu... (v3.6)
                      { // Alors...On demande le vert DES QU'UN DES FEUX (devant être rouge) EST VERT
                       for(i=0;
                           (i<NbFeuxAtt)&&
                           ((cv->Feu[NumFeuxAtt[i]-1].Etat!=vert)||
                            ((cv->Feu[NumFeuxAtt[i]-1].TourDrnChgEtat==cv->TourCrt)&&
                             (!cv->Feu[NumFeuxAtt[i]-1].RougeDemande)));
                           i++);
                       // v5.2 : on vérifie les feux piétons (comme ci-dessus)
                       if (!(DemandeVert=(i<NbFeuxAtt))) // Si pas de demande de vert dans les feux de circulation
                        {
                         for(i=0;
                             (i<NbFeuxPtn)&&
                             ((cv->FeuP[NumFeuxPtn[i]-1].Etat!=vert)|| // ETAT=Etat pour les feux adverses et non l'état pour les piétons (compte le temps de traversée
                              ((cv->FeuP[NumFeuxPtn[i]-1].TourDrnChgEtat==cv->TourCrt)&&
                               (!cv->FeuP[NumFeuxPtn[i]-1].RougeDemande)));
                             i++);
                         DemandeVert=(i<NbFeuxPtn);
                        }
                       if (DemandeVert) TourDrnChgEtat=cv->TourCrt; // v5.2: DemandeVert est défini ci-dessus
                      }
                    }
                   // Le vert est demandé...
                   if (DemandeVert)
                    {
                     // On le fait toujours savoir (si jamais un feu devient vert entre-temps)
                     for(i=0; i<NbFeuxAtt; i++) // On parcours les feux devant être rouge
                      if ((cv->Feu[NumFeuxAtt[i]-1].Etat==vert)&& // feu opposé vert et
                          (cv->Feu[NumFeuxAtt[i]-1].TourDrnChgEtat<cv->TourCrt)&&
                          (!cv->Feu[NumFeuxAtt[i]-1].RougeDemande)) // le rouge n'a pas encore été demandé)
                       {
                        cv->Feu[NumFeuxAtt[i]-1].RougeDemande=true; // Ben maintenant...
                        cv->Feu[NumFeuxAtt[i]-1].TourDrnChgEtat=cv->TourCrt; //  c'est fait !
                       }
                     // v5.2 : Idem pour les feux de piétons
                     for(i=0; i<NbFeuxPtn; i++) // On parcours les feux piétons devant être rouge
                      if ((cv->FeuP[NumFeuxPtn[i]-1].Etat==vert)&& // feu opposé vert et (ETAT=Etat pour les feux adverses et non l'état pour les piétons (compte le temps de traversée)
                          (cv->FeuP[NumFeuxPtn[i]-1].TourDrnChgEtat<cv->TourCrt)&&
                          (!cv->FeuP[NumFeuxPtn[i]-1].RougeDemande)) // le rouge n'a pas encore été demandé)
                       {
                        cv->FeuP[NumFeuxPtn[i]-1].RougeDemande=true; // Ben maintenant...
                        cv->FeuP[NumFeuxPtn[i]-1].TourDrnChgEtat=cv->TourCrt; //  c'est fait !
                       }
                    }
                   // On vérifie que les feux opposés ne sont pas déjà tous rouges (vert demandé ou non)
                   if (!FeuxTousRouges)
                    {
                     for(i=0;
                         (i<NbFeuxAtt)&&
                         (cv->Feu[NumFeuxAtt[i]-1].Etat==rouge)&&
                         (cv->Feu[NumFeuxAtt[i]-1].DemandeVert||
                          cv->Feu[NumFeuxAtt[i]-1].ProchainVert||
                          (cv->Feu[NumFeuxAtt[i]-1].TourDrnChgEtat<cv->TourCrt));
                         i++);
                     // v5.2 : Idem pour les feux piétons
					 if ((FeuxTousRouges=(i==NbFeuxAtt))) // Si Feux de circulation tous Rouges
                      {
                       for(i=0;
                           (i<NbFeuxPtn)&&
                           (cv->FeuP[NumFeuxPtn[i]-1].Etat==rouge)&&
                           (cv->FeuP[NumFeuxPtn[i]-1].DemandeVert||
                            cv->FeuP[NumFeuxPtn[i]-1].ProchainVert||
                            (cv->FeuP[NumFeuxPtn[i]-1].TourDrnChgEtat<cv->TourCrt));
                           i++);
                       FeuxTousRouges=(i==NbFeuxPtn);
                      }
                     if (FeuxTousRouges) TourDrnChgEtat=cv->TourCrt; // v5.2 : FeuxTousRouges défini ci-dessus
                    }
                   // On passe au vert si on le demande ou on l'autorise (vert demandé ou non)
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
	 // v5.2 : /!\ On ne charge pas les feux de piétons
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
	// v5.2 : /!\ On ne charge pas les feux de piétons
   }
  for(i=0; Ok&&(i<NbFeuxDmd); i++) Ok=FileRead(hfile, &(NumFeuxDmd[i]), sizeof(NumFeuxDmd[i]));
  for(i=0; Ok&&(i<NbFeuxAtt); i++) Ok=FileRead(hfile, &(NumFeuxAtt[i]), sizeof(NumFeuxAtt[i]));
	// v5.2 : /!\ On ne charge pas les feux de piétons
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
	// v5.2 : /!\ On ne sauve pas les feux de piétons
	 FileWrite(hfile, &TypeDmdVert, sizeof(TypeDmdVert))&&
	 FileWrite(hfile, &TypePsgRouge, sizeof(TypePsgRouge))&&
	 FileWrite(hfile, &DureeRouge, sizeof(DureeRouge))&&
	 FileWrite(hfile, &DureeVert, sizeof(DureeVert))&&
	 FileWrite(hfile, &DemandeVert, sizeof(DemandeVert))&&
	 FileWrite(hfile, &RougeDemande, sizeof(RougeDemande));

  for(i=0; Ok&&(i<NbFeuxDmd); i++) Ok=FileWrite(hfile, &(NumFeuxDmd[i]), sizeof(NumFeuxDmd[i]));
  for(i=0; Ok&&(i<NbFeuxAtt); i++) Ok=FileWrite(hfile, &(NumFeuxAtt[i]), sizeof(NumFeuxAtt[i]));
    // v5.2 : /!\ On ne sauve pas les feux de piétons
  return Ok;
 }
//-----------------------------------------------------------------------------
void feu::Verifie(AnsiString &asMsgErr, AnsiString asSource)
 {
  int i;
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, DOIT_ETRE_DEFINI);
  VerifieDirection(asMsgErr, asSource, (direction)Dir, DOIT_ETRE_DEFINI);
  VerifieEtat(asMsgErr, asSource, Etat);
  VerifieEtat(asMsgErr, asSource, ProchainEtat);

  VerifEnCours=true; // Evite les boucles infinies dues aux pointages mutuels de références

  if ((NbFeuxDmd<0)||(NbFeuxDmd>cv->NbFeux))
   asMsgErr+=asSource+Format(": nombre des prochains feux verts incorrect (%d)\n", ARRAYOFCONST((NbFeuxDmd)));
  else
   for(i=0; i<NbFeuxDmd; i++)
    if ((NumFeuxDmd[i]<1)||(NumFeuxDmd[i]>cv->NbFeux)) // v3.7.2 : > strict
     asMsgErr+=asSource+Format(": numéro du %d° prochain feu vert incorrect (%d)\n", ARRAYOFCONST((i+1, NumFeuxDmd[i])));
    else
     if (!cv->Feu[NumFeuxDmd[i]-1].VerifEnCours)
      cv->Feu[NumFeuxDmd[i]-1].Verifie(asMsgErr, Format("%d° prochain feu vert [n°%d, (%d,%d)]\n",
                                                        ARRAYOFCONST((i+1, NumFeuxDmd[i],
                                                                      cv->Feu[NumFeuxDmd[i]-1].x,
                                                                      cv->Feu[NumFeuxDmd[i]-1].y
                                                                     ))));

  if ((NbFeuxAtt<0)||(NbFeuxAtt>cv->NbFeux))
   asMsgErr+=asSource+Format(": nombre des feux devant être rouge incorrect (%d)\n", ARRAYOFCONST((NbFeuxAtt)));
  else
   for(i=0; i<NbFeuxAtt; i++)
    if ((NumFeuxAtt[i]<1)||(NumFeuxAtt[i]>cv->NbFeux)) // v3.7.2 : > strict
     asMsgErr+=asSource+Format(": numéro du %d° feu devant être rouge incorrect (%d)\n", ARRAYOFCONST((i+1, NumFeuxAtt[i])));
    else
     if (!cv->Feu[NumFeuxAtt[i]-1].VerifEnCours)
      cv->Feu[NumFeuxAtt[i]-1].Verifie(asMsgErr, Format("%d° feu devant être rouge [n°%d, (%d,%d)]\n",
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
   asMsgErr+=asSource+": le rouge est demandé alors qu'il n'est pas vert\n";
 }
//-----------------------------------------------------------------------------
void feu_pieton::Initialise() // v5.2
 {
  for(int i=0; i<NBFEUXPIETONSPARNUMERO; i++)
   {
    x[i]=y[i]=-1;
    Dir[i]=indefinie;
   }
  for(int i=0; i<NBDIR; i++)
   iFeuDir[i]=0;
  ProchainEtat=Etat=inactif;
  TypeDmdVert=arrivee_vehicule;
  TypePsgRouge=prm_dmd;
  DureeTraversee=DureeVert=DureeRouge=NbFeux=0;
  TourDrnChgEtat=0L;
  ProchainVert=RougeDemande=FeuxTousRouges=DemandeVert=false;
  VerifEnCours=false;
 };
//-----------------------------------------------------------------------------
void feu_pieton::Copie(feu_pieton *f) // v5.2
 {
  f->CopieEnCours=true;
  Numero=f->Numero;
  for(int i=0; i<NBFEUXPIETONSPARNUMERO; i++)
   {
    x[i]=f->x[i];
    y[i]=f->y[i];
    Dir[i]=f->Dir[i];
   }
  for(int i=0; i<NBDIR; i++)
   iFeuDir[i]=f->iFeuDir[i];
  Etat=f->Etat;
  ProchainEtat=f->ProchainEtat;
  NbFeux=f->NbFeux;
  NumFeux=f->NumFeux;
  DureeRouge=f->DureeRouge;
  DureeVert=f->DureeVert;
  DureeTraversee=f->DureeTraversee;
  TourDrnChgEtat=f->TourDrnChgEtat;
  TypeDmdVert=f->TypeDmdVert;
  TypePsgRouge=f->TypePsgRouge;
  DemandeVert=f->DemandeVert;
  FeuxTousRouges=f->FeuxTousRouges;
  RougeDemande=f->RougeDemande;
  ProchainVert=f->ProchainVert;
  VerifEnCours=f->VerifEnCours;
 };
//-----------------------------------------------------------------------------
void feu_pieton::DefinitFeuOppose()
 { // On suppose ici que :
   //  - x[0],y[0],Dir[0] sont définis
   //  - On peut poser le feu opposé (contrôle déjà effectué)
   //  - v[x[0]][y[0]].NumFeuP[Dir[0]-1]=Numero
  int k;
  for(k=1; cv->V_(x[0],y[0],k,Dir[0]).PassagePietons; k++);
  int xx=(x[0]+k*dx[Dir[0]])%cv->NbX,
      yy=(y[0]+k*dy[Dir[0]])%cv->NbY;
  direction dd=InvDir[Dir[0]];
  x[1]=xx;
  y[1]=yy;
  Dir[1]=dd;
  iFeuDir[Dir[1]-1]=1;
  cv->v[xx][yy].NumFeuP[dd-1]=Numero;
  DureeTraversee=2*(k-1)+1;
 }
//-----------------------------------------------------------------------------
void feu_pieton::AjouteFeu(int NumNvFeu) // v5.2
 {
  int i, *NvNumFeux;
  NbFeux++;
  NvNumFeux=new int[NbFeux];
  for(i=0; i<NbFeux-1; i++)
   NvNumFeux[i]=NumFeux[i];
  NvNumFeux[NbFeux-1]=NumNvFeu;
  if (NumFeux) delete[] NumFeux;
  NumFeux=NvNumFeux;
 }
//-----------------------------------------------------------------------------
void feu_pieton::RetireFeu(int NumFeu) // //v5.2
 {
  int i, Trv=0, *NvNumFeux=NULL;
  if (--NbFeux)
   {
    NvNumFeux=new int[NbFeux];
    for(i=0; i<NbFeux; i++)
     NvNumFeux[i]=NumFeux[i+(Trv|=(NumFeux[i]==NumFeu))];
   }
  delete[] NumFeux;
  NumFeux=NvNumFeux;
 }
//-----------------------------------------------------------------------------
void feu_pieton::ChangeEtat()
 {
  bool ChgEtat=(Etat!=ProchainEtat);
  Etat=ProchainEtat;
  if (ChgEtat)
   for(int i=0; i<NBFEUXPIETONSPARNUMERO; i++)
    frmSimulation->RedessineCase(x[i], y[i], false);
 }
//-----------------------------------------------------------------------------
void feu_pieton::DefinitProchainEtat()
 {
  int i;
  TourDrnChgEtat=cv->TourCrt;
  if (Etat) ProchainEtat=(etat_feu)(4-Etat);
  switch(ProchainEtat)
   {
    case vert:  DemandeVert=false;
                FeuxTousRouges=false;
                ProchainVert=false;
                break;
    case rouge: RougeDemande=false;
                break;
    default:    break;
   }
 }
//-----------------------------------------------------------------------------
bool feu_pieton::PietonAttend()
 {
  int NumPieton;
  bool Attend=false; // Pessimiste
  for(int i=0; (!Attend)&&(i<NBFEUXPIETONSPARNUMERO); i++)
   for(int j=0; (!Attend)&&(j<NBMAXPIETONSPARCASE); j++)
	if ((NumPieton=cv->v[x[i]][y[i]].NumPieton[j]))
     {
      pieton *p=cv->Pieton+(NumPieton-1);
      Attend=p->PsgPtTrv&&(p->Dir==Dir[i]); // Le piéton attend dans le sens du feu piéton.
     }
  return Attend;
 }
//-----------------------------------------------------------------------------
void feu_pieton::Evolue()
 {
  int i;
  ProchainEtat=Etat; // Par défaut
//  pieton *p;
  switch(Etat)
   {
    case inactif : break;
    case vert:     if (cv->TourCrt-TourDrnChgEtat<=DureeTraversee) break; // On attend que la traversée se passe avant d'agir
                   // Si (rouge demandé ou passage immediat) et durée vert écoulée -> Rouge
                   if (((RougeDemande&&(TourDrnChgEtat<cv->TourCrt))||
                        (TypePsgRouge==immediat))&&
                       (cv->TourCrt-TourDrnChgEtat>DureeVert))
                    DefinitProchainEtat();
                   break;
    case rouge:    if (cv->TourCrt-TourDrnChgEtat==DureeTraversee) // On attend que le temps minimum de traversée se termine
                   // Le bloc for ci-dessous a été déplacé de DefinitProchainEtat jusqu'ici car il y a un décalage de DureeTraversee
                   // On informe quels sont les prochains feux à se mettre au vert
                    for(i=0; i<NbFeux; i++)
                     if ((cv->Feu[NumFeux[i]-1].Etat==rouge)&&
                         (!cv->Feu[NumFeux[i]-1].ProchainVert)&&
                         (cv->Feu[NumFeux[i]-1].DemandeVert||
                          (cv->Feu[NumFeux[i]-1].TourDrnChgEtat<cv->TourCrt)))
                      {
                       cv->Feu[NumFeux[i]-1].ProchainVert=true;
                       cv->Feu[NumFeux[i]-1].TourDrnChgEtat=cv->TourCrt;
                      }
                   if (!DemandeVert) // Le vert n'est pas encore demandé
                    {
                     if ((cv->TourCrt-TourDrnChgEtat>DureeRouge)&& // la durée du rouge est écoulée ET
                         ((TypeDmdVert==immediate)|| // La demande est immédiate Ou
                          PietonAttend())) // un pieton attend au pied d'un des feux de piétons
                      { // Alors...On demande le vert DES QU'UN DES FEUX (devant être rouge) EST VERT
                       for(i=0;
                           (i<NbFeux)&&
                           ((cv->Feu[NumFeux[i]-1].Etat!=vert)||
                            ((cv->Feu[NumFeux[i]-1].TourDrnChgEtat==cv->TourCrt)&&
                             (!cv->Feu[NumFeux[i]-1].RougeDemande)));
                           i++);
					   if ((DemandeVert=(i<NbFeux))) TourDrnChgEtat=cv->TourCrt;
                      }
                    }
                   // Le vert est demandé...
                   if (DemandeVert)
                    {
                     // On le fait toujours savoir (si jamais un feu devient vert entre-temps)
                     for(i=0; i<NbFeux; i++) // On parcours les feux devant être rouge
                      if ((cv->Feu[NumFeux[i]-1].Etat==vert)&& // feu opposé vert et
                          (cv->Feu[NumFeux[i]-1].TourDrnChgEtat<cv->TourCrt)&&
                          (!cv->Feu[NumFeux[i]-1].RougeDemande)) // le rouge n'a pas encore été demandé)
                       {
                        cv->Feu[NumFeux[i]-1].RougeDemande=true; // Ben maintenant...
                        cv->Feu[NumFeux[i]-1].TourDrnChgEtat=cv->TourCrt; //  c'est fait !
                       }
                    }
                   // On vérifie que les feux opposés ne sont pas déjà tous rouges (vert demandé ou non)
                   if (!FeuxTousRouges)
                    {
                     for(i=0;
                         (i<NbFeux)&&
                         (cv->Feu[NumFeux[i]-1].Etat==rouge)&&
                         (cv->Feu[NumFeux[i]-1].DemandeVert||
                          cv->Feu[NumFeux[i]-1].ProchainVert||
                          (cv->Feu[NumFeux[i]-1].TourDrnChgEtat<cv->TourCrt));
                         i++);
					 if ((FeuxTousRouges=(i==NbFeux))) TourDrnChgEtat=cv->TourCrt;
                    }
                   // On passe au vert si on le demande ou on l'autorise (vert demandé ou non)
                   if (FeuxTousRouges&&ProchainVert&&(TourDrnChgEtat<cv->TourCrt))
                    DefinitProchainEtat();
				   break;
    default : break; // v5.4 : évite l'avertissement
   }
 }
//-----------------------------------------------------------------------------
bool feu_pieton::Charge(int hfile)
 {
  int i;
  bool Ok;
  Ok=FileRead(hfile, &Numero, sizeof(Numero))&&
     FileRead(hfile, x, NBFEUXPIETONSPARNUMERO*sizeof(x[0]))&&
     FileRead(hfile, y, NBFEUXPIETONSPARNUMERO*sizeof(y[0]))&&
     FileRead(hfile, Dir, NBFEUXPIETONSPARNUMERO*sizeof(Dir[0]))&&
     FileRead(hfile, iFeuDir, NBDIR*sizeof(iFeuDir[0]))&&
     FileRead(hfile, &Etat, sizeof(Etat))&&
     FileRead(hfile, &NbFeux, sizeof(NbFeux))&&
     FileRead(hfile, &TypeDmdVert, sizeof(TypeDmdVert))&&
     FileRead(hfile, &TypePsgRouge, sizeof(TypePsgRouge))&&
     FileRead(hfile, &DureeRouge, sizeof(DureeRouge))&&
     FileRead(hfile, &DureeVert, sizeof(DureeVert))&&
     FileRead(hfile, &DemandeVert, sizeof(DemandeVert))&&
     FileRead(hfile, &RougeDemande, sizeof(RougeDemande));
  if (Ok)
   if (NbFeux) Ok=!!(NumFeux=new int[NbFeux]);
  for(i=0; Ok&&(i<NbFeux); i++) Ok=FileRead(hfile, &(NumFeux[i]), sizeof(NumFeux[i]));
  if (Ok) DureeTraversee=2*(abs(x[1]-x[0])+abs(y[1]-y[0])-1)+1;
  return Ok;
 }
//-----------------------------------------------------------------------------
bool feu_pieton::Sauve(int hfile)
 {
  int i, Ok, // xc,yc : gestion copie vers fichier (v4.0.1)
      xc[NBFEUXPIETONSPARNUMERO]={x[0]-cv->Xc, x[1]-cv->Xc},
      yc[NBFEUXPIETONSPARNUMERO]={y[0]-cv->Yc, y[1]-cv->Yc};
  Ok=FileWrite(hfile, &Numero, sizeof(Numero))&&
     FileWrite(hfile, cv->CopieEnCours?xc:x, NBFEUXPIETONSPARNUMERO*sizeof(x[0]))&&
     FileWrite(hfile, cv->CopieEnCours?yc:y, NBFEUXPIETONSPARNUMERO*sizeof(y[0]))&&
     FileWrite(hfile, Dir, NBFEUXPIETONSPARNUMERO*sizeof(Dir[0]))&&
     FileWrite(hfile, iFeuDir, NBDIR*sizeof(iFeuDir[0]))&&
     FileWrite(hfile, &Etat, sizeof(Etat))&&
     FileWrite(hfile, &NbFeux, sizeof(NbFeux))&&
     FileWrite(hfile, &TypeDmdVert, sizeof(TypeDmdVert))&&
     FileWrite(hfile, &TypePsgRouge, sizeof(TypePsgRouge))&&
     FileWrite(hfile, &DureeRouge, sizeof(DureeRouge))&&
     FileWrite(hfile, &DureeVert, sizeof(DureeVert))&&
     FileWrite(hfile, &DemandeVert, sizeof(DemandeVert))&&
     FileWrite(hfile, &RougeDemande, sizeof(RougeDemande));
  for(i=0; Ok&&(i<NbFeux); i++) Ok=FileWrite(hfile, &(NumFeux[i]), sizeof(NumFeux[i]));
  return Ok;
 }
//-----------------------------------------------------------------------------
void parking::PlaceProchainVehicule()
 {
  int i, NumVehicule=0;
  if (!cv->v[x][y].NumVehicule)
   {
    for(i=0; (!NumVehicule)&&(i<cv->NbVehicules); i++)
     NumVehicule=((cv->Vehicule[i].NumParkingDepart==Numero)&&
                  (cv->Vehicule[i].x==x)&&
                  (cv->Vehicule[i].y==y))*(i+1);
    if (NumVehicule) // Il y a encore un véhicule à sortir
     {
      cv->v[x][y].NumVehicule=NumVehicule;
      cv->PlaceVehicule(x, y, NumVehicule); // v2.2.7. Inclut les stats d'Attente/Trafic
      cv->Vehicule[NumVehicule-1].TourDepart=cv->TourCrt;
      cv->NbVehiculesSortis++;
     }
   }
 }
//-----------------------------------------------------------------------------
bool parking::Charge(int hfile)
 {
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &x, sizeof(x))&&
         FileRead(hfile, &y, sizeof(y));
 }
//-----------------------------------------------------------------------------
bool parking::Sauve(int hfile)
 {
  int xc=x-cv->Xc, yc=y-cv->Yc; // v4.0.1
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, cv->CopieEnCours?&xc:&x, sizeof(x))&& // v4.0.1
         FileWrite(hfile, cv->CopieEnCours?&yc:&y, sizeof(y));  // v4.0.1
 }
//-----------------------------------------------------------------------------
void parking::Verifie(AnsiString &asMsgErr)
 {
  AnsiString asSource=Format("Parking n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, DOIT_ETRE_DEFINI);
 }
//-----------------------------------------------------------------------------
void vehicule::Definit(int x0, int y0, direction Dir0,
                       int NumDepart, int NumArrivee,
                       int NumFileDepart, int NumFileArrivee, // v5.0
                       niveau_priorite NivPriorite0) // v2.2
 {
  x=x0; y=y0; Dir=Dir0;
  NumParkingDepart=NumDepart; NumParkingArrivee=NumArrivee;
  NumFileParkDepart=NumFileDepart; NumFileParkArrivee=NumFileArrivee;
  NivPriorite=NivPriorite0;
 }
//-----------------------------------------------------------------------------
bool vehicule::EstDestination(const voie *v) // v5.0 : inclut les parkings extérieurs
 {
  if (NumParkingArrivee)
   return (NumParkingArrivee==v->NumParking);
  if (NumFileParkArrivee&&v->NumPlacePark)
   return (NumFileParkArrivee==cv->PlacePark[v->NumPlacePark-1].NumFile+1); // v5.2.3 : NumFile+1 et non NumFile
  return false;
 }
//-----------------------------------------------------------------------------
void vehicule::CalculeProchaineDirection()
 {
  voie *v=&(cv->v[x][y]), *Voie;
  direction AncDir=Dir; // v2.2.4
  bool Prioritaire=(NivPriorite>normal); // v3.5 (pour DistParking)
  int OrdreDir[NBDIR]={0,0,0,0},
      i, j, ndp=NbDir[v->DirPoss];
  Dir=indefinie;

  // On classe les dir.poss. dans l'ordre < des distances aux parkings.
  // En cas d'égalité, c'est le hasard : (N°Veh.+Tour) Modulo Directions Possibles
  if (NumFileParkArrivee) // v5.0 : recopie du calcul d'OrdreDir puis remplacement des occurrences "Parking" par "FilePark"
   for(i=0; i<ndp; i++)
    for(j=0; j<ndp; j++)
     if (i!=j) // On dégringole si distance supérieure.
      OrdreDir[i]+=((cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlacePark&& // 1. File recherchée
                     (cv->PlacePark[cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlacePark-1].NumFile+1==NumFileParkArrivee))> // v5.2.3 : NumFile+1 et non NumFile
                    (cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlacePark&&
                     (cv->PlacePark[cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlacePark-1].NumFile+1==NumFileParkArrivee)))|| // 2. Distance à la file. v5.2.3 : NumFile+1 et non NumFile
                   ((v->DistFilePark[NumFileParkArrivee-1][i][Prioritaire]>v->DistFilePark[NumFileParkArrivee-1][j][Prioritaire])||
                    ((v->DistFilePark[NumFileParkArrivee-1][i][Prioritaire]==v->DistFilePark[NumFileParkArrivee-1][j][Prioritaire])&&
                     ((Dirdp[i][v->DirPoss]!=AncDir)|| // En cas d'égalité, préfère garder la direction courante : v2.2.4.  // v3.5 : || par && !
                      ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)
  if (NumParkingArrivee)
   for(i=0; i<ndp; i++)
    for(j=0; j<ndp; j++)
     if (i!=j) // On dégringole si distance supérieure.
      OrdreDir[i]+=((v->DistParking[NumParkingArrivee-1][i][Prioritaire]>v->DistParking[NumParkingArrivee-1][j][Prioritaire])||
                    ((v->DistParking[NumParkingArrivee-1][i][Prioritaire]==v->DistParking[NumParkingArrivee-1][j][Prioritaire])&&
                     ((Dirdp[i][v->DirPoss]!=AncDir)|| // En cas d'égalité, préfère garder la direction courante : v2.2.4.  // v3.5 : || par && !
                      ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)

  for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
   for(j=0; (!Dir)&&(j<ndp); j++)
    {
     Voie=&(cv->V(x,y,Dirdp[j][v->DirPoss]));
     if ((OrdreDir[j]==i)&&
         ((!v->ToutDroit)||    // Direction interdite si : - Obligation d'aller tout droit ET
          Prioritaire|| //                                   Véhicule NON prioritaire (v3.9.1) ET
          (DirDrnDepl==Dirdp[j][v->DirPoss]))&& //           pas même direction que lors du dernier déplacement // v3.7.1 : Erreur !
         (!Voie->NumPlaceTaxi)&& //                        - Place de taxi. v3.6
         (!Voie->NumPlaceVehlib)&& //                      - Place de vehlib v5.3        
         ((!Voie->PassageBus)||  //                        - Passage bus dans cette direction sauf véhicules prioritaires (police, urgence)
          Prioritaire)&&
         (((!Voie->NumVehicule)&&
           (!Voie->NumVehlib)&& // v5.3
           (!Voie->NumBus)&& // v3.0
           (!Voie->NumTram)&& // v3.5
           (!Voie->NumTaxi))|| // v3.6
          ((Voie->NumParking||Voie->NumPlacePark)&& // v5.0 Voie->NumPlacePark
           EstDestination(Voie))|| // v5.0 EstDestination
          (cv->TourCrt<=1+TourDrnDepl+(!NivPriorite)*cv->AttenteMaxVeh*(1+OrdreDir[j])))) // v2.2
      Dir=Dirdp[j][v->DirPoss];
    }

   // Si la direction est toujours indéfinie : on prend la meilleure direction possible
   if (!Dir)
    for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
     for(j=0; (!Dir)&&(j<ndp); j++)
      {
       Voie=&(cv->V(x,y,Dirdp[j][v->DirPoss]));
       if (((!NumFileParkArrivee)|| // v5.0 : Empêcher le véhicule arrivé à la file de place de continuer
            (!Voie->NumPlacePark)|| // v5.0 (suite)
            (cv->PlacePark[Voie->NumPlacePark-1].NumFile+1==NumFileParkArrivee))&& // v5.0 (suite). v5.2.3 : NumFile+1 et non NumFile
           (OrdreDir[j]==i))
        Dir=Dirdp[j][v->DirPoss];
      }
 }
//-----------------------------------------------------------------------------
direction vehicule::ProchaineDirectionAuCarrefour() // ATTENTION : DIR DOIT ETRE DEFINIE
 {
  voie *v=&(cv->V(x,y,Dir)); // Ici v est la prochaine case
  bool Prioritaire=(NivPriorite>normal); // v3.5 (pour DistParking)
  int OrdreDir[NBDIR]={0,0,0,0},
      i, j, ndp=NbDir[v->DirPoss];
  direction DirAuCarrefour=indefinie;

  // On classe les dir.poss. dans l'ordre < des distances aux parkings si la case est libre.
  // En cas d'égalité, c'est le hasard : (N°Veh.+Tour) Modulo Directions Possibles
  if (NumFileParkArrivee) // v5.0 : recopie du calcul d'OrdreDir puis remplacement des occurrences "Parking" par "FilePark"
   for(i=0; i<ndp; i++)
    for(j=0; j<ndp; j++)
     if (i!=j)
      OrdreDir[i]+=((cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlacePark&& // 1. File recherchée
                     (cv->PlacePark[cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlacePark-1].NumFile+1==NumFileParkArrivee))> // v5.2.3 : NumFile+1 et non NumFile
                    (cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlacePark&&
                     (cv->PlacePark[cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlacePark-1].NumFile+1==NumFileParkArrivee)))|| // 2. Distance à la file. v5.2.3 : NumFile+1 et non NumFile
                   ((v->DistFilePark[NumFileParkArrivee-1][i][Prioritaire]>v->DistFilePark[NumFileParkArrivee-1][j][Prioritaire])||
                    ((v->DistFilePark[NumFileParkArrivee-1][i][Prioritaire]==v->DistFilePark[NumFileParkArrivee-1][j][Prioritaire])&&
                     ((Dirdp[i][v->DirPoss]!=Dir)|| // En cas d'égalité, préfère garder la direction courante : v2.2.4.  // v3.5 : || par && !
                      ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // tirage au hasard en cas d'égalité (Ici TourCrt+1)
  if (NumParkingArrivee) // v5.0 : if (NumParkingArrivee)
   for(i=0; i<ndp; i++)
    for(j=0; j<ndp; j++)
     if (i!=j)
      OrdreDir[i]+=((v->DistParking[NumParkingArrivee-1][i][Prioritaire]>v->DistParking[NumParkingArrivee-1][j][Prioritaire])||
                    ((v->DistParking[NumParkingArrivee-1][i][Prioritaire]==v->DistParking[NumParkingArrivee-1][j][Prioritaire])&&
                     ((Dirdp[i][v->DirPoss]!=Dir)|| // En cas d'égalité, préfère garder la direction courante : v2.2.4.  // v3.5 : || par && !
                      ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // tirage au hasard en cas d'égalité (Ici TourCrt+1)

  for(i=0; (!DirAuCarrefour)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
   for(j=0; (!DirAuCarrefour)&&(j<ndp); j++)
    if ((OrdreDir[j]==i)&&
        (!v->NumPlaceTaxi)&& // Direction interdite si :     - Place de Taxi. v3.6
        (!v->NumPlaceVehlib)&& //                            - Place de vehlib v5.3        
        ((!v->ToutDroit)||   //                              - Obligation d'aller tout droit ET
         Prioritaire|| //                                      Véhicule NON Prioritaire (v3.9.1) ET
         (DirDrnDepl==Dirdp[j][v->DirPoss]))) // pas même direction que lors du dernier déplacement. v3.7.1 : Erreur ! v5.2.3 : Erreur sur Test même direction
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
  AnsiString asSource=Format("Véhicule n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  VerifieDirection(asMsgErr, asSource, Dir, PEUT_ETRE_INDEFINI);

  if (NumFileParkDepart) // v5.0
   {
    if (NumFileParkDepart<1)
     asMsgErr+=asSource+Format(": numéro de file de parking de départ incorrect (%d)\n", ARRAYOFCONST((NumFileParkDepart)));
   }
  else
   if (NumParkingDepart<1)
    asMsgErr+=asSource+Format(": numéro de parking de départ incorrect (%d)\n", ARRAYOFCONST((NumParkingDepart)));

  if (NumFileParkArrivee) // v5.0
   {
    if (NumFileParkArrivee<1)
     asMsgErr+=asSource+Format(": numéro de file de parking d'arrivée incorrect (%d)\n", ARRAYOFCONST((NumFileParkArrivee)));
   }
  else
   if (NumParkingArrivee<1)
    asMsgErr+=asSource+Format(": numéro de parking d'arrivée incorrect (%d)\n", ARRAYOFCONST((NumParkingArrivee)));
 }
//-----------------------------------------------------------------------------
// CLASSES du réseau de VEHLIB (v5.3)
//-----------------------------------------------------------------------------
bool place_vehlib::Charge(int hfile)
 {
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &x, sizeof(x))&&
         FileRead(hfile, &y, sizeof(y));
 }
//-----------------------------------------------------------------------------
bool place_vehlib::Sauve(int hfile)
 {
  int xc=x-cv->Xc, yc=y-cv->Yc; // v4.0.1
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, cv->CopieEnCours?&xc:&x, sizeof(x))&& // v4.0.1
         FileWrite(hfile, cv->CopieEnCours?&yc:&y, sizeof(y));  // v4.0.1
 }
//-----------------------------------------------------------------------------
void place_vehlib::Verifie(AnsiString &asMsgErr)
 {
  AnsiString asSource=Format("Place Vehlib n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
 }
//-----------------------------------------------------------------------------
bool place_vehlib::EstLibre()
 {
  return (!NumVehlibReserve)&&
         (!cv->v[x][y].NumVehlib);
 }
//-----------------------------------------------------------------------------
void vehlib::Place(int p) // ATTENTION: 0 <= p < NbPlacesVehlib
 {
  x=cv->PlaceVehlib[p].x;
  y=cv->PlaceVehlib[p].y;
  cv->v[x][y].NumVehlib=Numero;
  voie *v=&(cv->v[x][y]);
  Situation=svAttente;
  for(int d=nord; (!Dir)&&(d<=ouest); d++)
   if (v->DirPoss&PossDir[(direction)d]) Dir=(direction)d;
  //DebugEcrit(Format("Vehlib(%d)::Place(%d): (x,y)=(%d,%d); cv->v[x][y].NumVehlib=%d; Situation=svAttente; Dir=%d", ARRAYOFCONST((Numero,p,x,y,Numero,(int)Dir))));
 }
//-----------------------------------------------------------------------------
bool vehlib::EstDestination(const voie *v)
 {
  if (NumPlaceArrivee)
   return (NumPlaceArrivee==v->NumPlaceVehlib);
  else
   return false;
 }
//-----------------------------------------------------------------------------
void vehlib::CalculeProchaineDirection()
 {
  voie *v=&(cv->v[x][y]), *Voie;
  direction AncDir=Dir; // v2.2.4
  int OrdreDir[NBDIR]={0,0,0,0},
      i, j, ndp=NbDir[v->DirPoss];

  if ((Situation==svAttente)&&  // Si le vehlib attend,
      (NbPietonsQuiSontMontes())) // On regarde déjà s'il y a des piétons qui veulent monter...
   { // pour pouvoir partir...
    if (!NumPlaceArrivee) // Des fois les piétons restent dans le vehlib...
     ReservePlaceVehlibCible();
    Situation=svDepart;
    TourDepart=cv->TourCrt;
	//DebugEcrit(Format("Vehlib(%d)::CalculeProchaineDirection(): Situation=svDepart; TourDepart=%d", ARRAYOFCONST((Numero,cv->TourCrt))));
   }
  Dir=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux files.
  // En cas d'égalité, c'est le hasard : (N°Veh.+Tour) Modulo Directions Possibles
  if (NumPlaceArrivee&&(Situation==svDepart))
   for(i=0; i<ndp; i++)
    for(j=0; j<ndp; j++)
     if (i!=j) // On dégringole si distance supérieure.
      {
       OrdreDir[i]+=((cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceVehlib==NumPlaceArrivee)> // 1. Place arrivée
                     (cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceVehlib==NumPlaceArrivee))||
                    ((v->DistPlaceVehlib[NumPlaceArrivee-1][i]>v->DistPlaceVehlib[NumPlaceArrivee-1][j])|| // 2. Distance à la place.
                     ((v->DistPlaceVehlib[NumPlaceArrivee-1][i]==v->DistPlaceVehlib[NumPlaceArrivee-1][j])&&
                      ((Dirdp[i][v->DirPoss]!=AncDir)|| // En cas d'égalité, préfère garder la direction courante
                       ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)
	   //DebugEcrit(Format("Vehlib(%d)::CalculeProchaineDirection(): NumPlaceArrivee>0 (%d) -> for(i,j)=(%d,%d) OrdreDir[i]=%d [V(i,j).NumPlaceVehlib=(%d,%d),V(i,j).DistPlaceVehlib=(%d,%d)]", ARRAYOFCONST((Numero,NumPlaceArrivee,i,j,OrdreDir[i],cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceVehlib,cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceVehlib,v->DistPlaceVehlib[NumPlaceArrivee-1][i],v->DistPlaceVehlib[NumPlaceArrivee-1][j]))));
      }
  for(i=0; (!Dir)&&(i<5); i++)
   for(j=0; (!Dir)&&(j<ndp); j++)
    {
     Voie=&(cv->V(x,y,Dirdp[j][v->DirPoss]));
     if ((OrdreDir[j]==i)&&
         ((!v->ToutDroit)||    // Direction interdite si : - Obligation d'aller tout droit ET
          (DirDrnDepl==Dirdp[j][v->DirPoss]))&& //           pas même direction que lors du dernier déplacement
         (!Voie->NumPlaceTaxi)&& //                        - Place de taxi.
         ((!Voie->NumPlaceVehlib)|| //                     - Place de vehlib (v5.3)
          (Voie->NumPlaceVehlib==NumPlaceArrivee))&& //      SAUF place d'arrivée (v5.3)
         (!Voie->PassageBus)&&   //                        - Passage bus
         (((!Voie->NumVehicule)&& //                       - Véhicule de tout type
           (!Voie->NumVehlib)&&
           (!Voie->NumBus)&&
           (!Voie->NumTram)&&
           (!Voie->NumTaxi))||
          ((Voie->NumParking||Voie->NumPlacePark||Voie->NumPlaceVehlib)&&
           EstDestination(Voie))||
          (cv->TourCrt<=1+TourDrnDepl+cv->AttenteMaxVeh*(1+OrdreDir[j]))))
      {
       Dir=Dirdp[j][v->DirPoss];
       //if (NumPlaceArrivee) DebugEcrit(Format("Vehlib(%d)::CalculeProchaineDirection(): for(i,j)=(%d,%d) OrdreDir[j]==i -> Dir=Dirdp[j][v->DirPoss] (%d)", ARRAYOFCONST((Numero,i,j,(int)Dir))));
      }
    }

   // Si la direction est toujours indéfinie : on prend la meilleure direction possible
   if (!Dir)
    for(i=0; (!Dir)&&(i<5); i++) // possibilité de blocage si test n'est pas large (i<5)
     for(j=0; (!Dir)&&(j<ndp); j++)
      {
       Voie=&(cv->V(x,y,Dirdp[j][v->DirPoss]));
       if (((!NumPlaceArrivee)|| // Empêcher le véhicule arrivé à la place de continuer
            (!Voie->NumPlaceVehlib)||
            (Voie->NumPlaceVehlib==NumPlaceArrivee))&&
            (OrdreDir[j]==i))
        Dir=Dirdp[j][v->DirPoss];
      }
 }
//-----------------------------------------------------------------------------
direction vehlib::ProchaineDirectionAuCarrefour() // ATTENTION : DIR DOIT ETRE DEFINIE
 {
  voie *v=&(cv->V(x,y,Dir)); // Ici v est la prochaine case
  int OrdreDir[NBDIR]={0,0,0,0},
      i, j, ndp=NbDir[v->DirPoss];
  direction DirAuCarrefour=indefinie;

  // On classe les dir.poss. dans l'ordre < des distances aux parkings si la case est libre.
  // En cas d'égalité, c'est le hasard : (N°Veh.+Tour) Modulo Directions Possibles
  if (NumPlaceArrivee) // v5.0 : recopie du calcul d'OrdreDir puis remplacement des occurrences "Parking" par "FilePark"
   for(i=0; i<ndp; i++)
    for(j=0; j<ndp; j++)
     if (i!=j)
      OrdreDir[i]+=((cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceVehlib==NumPlaceArrivee)> // 1. Place arrivée
                    (cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceVehlib==NumPlaceArrivee))||
                   ((v->DistPlaceVehlib[NumPlaceArrivee-1][i]>v->DistPlaceVehlib[NumPlaceArrivee-1][j])|| // 2. Distance à la place.
                    ((v->DistPlaceVehlib[NumPlaceArrivee-1][i]==v->DistPlaceVehlib[NumPlaceArrivee-1][j])&&
                     ((Dirdp[i][v->DirPoss]!=Dir)|| // En cas d'égalité, préfère garder la direction courante
                      ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)
  for(i=0; (!DirAuCarrefour)&&(i<5); i++) // possibilité de blocage si test n'est pas large (i<5)
   for(j=0; (!DirAuCarrefour)&&(j<ndp); j++)
    if ((OrdreDir[j]==i)&&
        (!v->NumPlaceTaxi)&& // Direction interdite si :     - Place de Taxi. v3.6
        ((!v->ToutDroit)||   //                              - Obligation d'aller tout droit ET
         (DirDrnDepl==Dirdp[j][v->DirPoss]))) // pas même direction que lors du dernier déplacement
    DirAuCarrefour=Dirdp[j][v->DirPoss];
  return DirAuCarrefour;
 }
//-----------------------------------------------------------------------------
bool vehlib::PeutPasser()
 {
  voie *v=&(cv->v[x][y]);
  int NumFeuVeh;
  return Dir&&
         (((v->Priorite[Dir-1]!=stop)||
           (cv->TourCrt-TourDrnDepl>=2))&&
          ((!(NumFeuVeh=v->NumFeu[Dir-1]))||
           (cv->Feu[NumFeuVeh-1].Etat<orange)));
 }
//-----------------------------------------------------------------------------
void vehlib::FaitDescendrePietons()
 {
  int i, d;
  voie *vl=&(cv->v[x][y]);
  for(d=nord; (!vl->PietonPeutAller((direction)d))&&(d<=ouest); d++); // direction où sortent les piétons et pas forcément à droite comme les taxis !
  if (vl->PietonPeutAller((direction)d)) // On s'assure que l'on trouve un trottoir quand même !
   {
    voie *v=&cv->V(x,y,d);
    pieton *p;
    for(i=0; i<cv->NbPietons; i++)
     {
      p=cv->Pieton+i;
      if (p->NumVehlib==Numero)
       v->FaitDescendrePieton((direction)d, i);
     }
   }
 }
//-----------------------------------------------------------------------------
void vehlib::ReservePlaceVehlibCible()
 {
  int NumPlace; // 0 < NumPlace <= NbPlacesVehlib
  do // On choisit une place libre
   {
    NumPlace=rand()%cv->NbPlacesVehlib;
   }
  while((NumPlace+1==NumPlaceDepart)||(!cv->PlaceVehlib[NumPlace].EstLibre()));
  place_vehlib *pv=cv->PlaceVehlib+NumPlace;
  int xp=pv->x, yp=pv->y;
  pv->NumVehlibReserve=Numero;
  NumPlaceArrivee=NumPlace+1;
  frmSimulation->RedessineCase(xp, yp, false);
 }
//-----------------------------------------------------------------------------
void vehlib::FaitMonterPieton(int NumPietonAFaireMonter)
 {
  pieton *p=cv->Pieton+NumPietonAFaireMonter;
  int xp=p->x, yp=p->y;
  if (NbPersonnes<cv->NbMaxPersonnesVehlib)
   {
    NbPersonnes++;
    cv->v[xp][yp].RetirePieton(NumPietonAFaireMonter);
    p->MonteDansVehlib(Numero);
    if (!NumPlaceArrivee)
     ReservePlaceVehlibCible();
    frmSimulation->RedessineCase(xp, yp, false);
   }
 }
//-----------------------------------------------------------------------------
int vehlib::NbPietonsQuiSontMontes() // retourne le nombre de piétons qui attendaient et qui sont montés
 {
  voie *v;
  pieton *p;
  if (cv->NbVehlibs<cv->NbPlacesVehlib) // S'il y a des places libres dans la simulation
   for(int d=nord; (NbPersonnes<=cv->NbMaxPersonnesVehlib)&&(d<=ouest); d++)
    {
     v=&(cv->V(x,y,d));
     for(int i=0; (NbPersonnes<=cv->NbMaxPersonnesVehlib)&&(i<NBMAXPIETONSPARCASE); i++)
      if (v->NumPieton[i]&&
          (p=cv->Pieton+v->NumPieton[i]-1)->AttendVehlib&&
          (p->NumPlaceVehlib==NumPlaceDepart))
       FaitMonterPieton(v->NumPieton[i]-1);
    }
  return NbPersonnes;
 }
//-----------------------------------------------------------------------------
void vehlib::Verifie(AnsiString &asMsgErr)
 {
  AnsiString asSource=Format("Vehlib n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  VerifieDirection(asMsgErr, asSource, Dir, PEUT_ETRE_INDEFINI);

  if (NumPlaceDepart)
   {
    if (NumPlaceDepart<1)
     asMsgErr+=asSource+Format(": numéro de place de départ incorrect (%d)\n", ARRAYOFCONST((NumPlaceDepart)));
   }
  if (NumPlaceArrivee)
   {
    if (NumPlaceArrivee<1)
     asMsgErr+=asSource+Format(": numéro de place d'arrivée incorrect (%d)\n", ARRAYOFCONST((NumPlaceArrivee)));
   }
 }
//-----------------------------------------------------------------------------
// FIN CLASSE VEHLIB (v5.3)
//-----------------------------------------------------------------------------
void depot_bus::PlaceProchainBus() // v3.0
 {
  int NumProchBus;
  if (Defini()&&
      (!cv->v[x][y].NumBus)&& // Pas de bus
      (!cv->v[x][y].NumTram)&& // Pas de tram
      (!cv->v[x][y].NumVehicule)&& // Pas de véhicule
      (!cv->v[x][y].NumTaxi)&& // Pas de taxi (v3.6)... sur la case dépôt
      (!cv->v[x][y].NumVehlib)&& // Pas de vehlib (v5.3)
      (NumDrnBusSorti<cv->NbBus)) // ET Encore au moins un bus à sortir
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
  AnsiString asSource=Format("Dépot bus : ", ARRAYOFCONST((x, y)));
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
     v->FaitDescendrePieton(d, i); // Si on peut pas faire descendre, il descendra au prochain arrêt
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
  // On classe les dir.poss. dans l'ordre < des distances aux arrêts de bus
  // En cas d'égalité, c'est le hasard : (N°Bus.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if (i!=j) // On dégringole si distance supérieure.
     OrdreDir[i]+=((v->DistArretBus[NumArretSvt-1][i]>v->DistArretBus[NumArretSvt-1][j])||
                   ((v->DistArretBus[NumArretSvt-1][i]==v->DistArretBus[NumArretSvt-1][j])&&
                    ((Dirdp[i][v->DirPoss]!=AncDir)|| // En cas d'égalité, préfère garder la direction courante : v2.2.4
                     ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)
  for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
   for(j=0; (!Dir)&&(j<ndp); j++)
    {
     Voie=&(cv->V(x,y,Dirdp[j][v->DirPoss]));
     if ((OrdreDir[j]==i)&&
         (!v->NumPlaceTaxi)&&  // Direction interdite si       - Place de taxi. v3.6
         (!v->NumPlacePark)&&  //                              - Place de parking. v5.0
         (!v->NumPlaceVehlib)&&//                              - Place de vehlib. v5.3
         ((!v->ToutDroit)||    //                              - Obligation d'aller tout droit ET
          (DirDrnDepl==Dirdp[j][v->DirPoss]))&& // pas même direction que lors du dernier déplacement. v3.7.1 : Erreur ! v5.2.3 : Erreur sur Test même direction
         (((!Voie->NumVehicule)&&(!Voie->NumBus)&&(!Voie->NumTram)&&(!Voie->NumTaxi)&&(!Voie->NumVehlib))|| // v5.3 (vehlib)
          (Voie->NumArretBus&&(Voie->NumArretBus==NumArretSvt))||
          (cv->TourCrt<=1+TourDrnDepl+5*cv->AttenteMaxVeh*(1+OrdreDir[j])))) // AttentMaxBus = 5*AttenteMaxVeh
      Dir=Dirdp[j][v->DirPoss];
    }

   // Si la direction est toujours indéfinie : on prend la meilleure direction possible
   if (!Dir)
    for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
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
  // On classe les dir.poss. dans l'ordre < des distances aux parkings si la case est libre.
  // En cas d'égalité, c'est le hasard : (N°Bus.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if (i!=j)
     OrdreDir[i]+=((v->DistArretBus[NumArretSvt-1][i]>v->DistArretBus[NumArretSvt-1][j])||
                   ((v->DistArretBus[NumArretSvt-1][i]==v->DistArretBus[NumArretSvt-1][j])&&
                    ((Dirdp[i][v->DirPoss]!=Dir)|| // En cas d'égalité, préfère garder la direction courante : // v3.5 : || par && !
                     ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // tirage au hasard en cas d'égalité (Ici TourCrt+1)
  for(i=0; (!DirAuCarrefour)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
   for(j=0; (!DirAuCarrefour)&&(j<ndp); j++)
    if ((OrdreDir[j]==i)&&
        (!v->NumPlaceTaxi)&&  // Direction interdite si :    - Place de taxi
        (!v->NumPlacePark)&&  //                             - Place de parking. v5.0
        (!v->NumPlaceVehlib)&&//                             - Place de vehlib. v5.3
        ((!v->ToutDroit)||    //                             - Obligation d'aller tout droit ET
         (DirDrnDepl==Dirdp[j][v->DirPoss]))) // pas même direction que lors du dernier déplacement. v3.7.1 : Erreur !
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
  AnsiString asSource=Format("Bus n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  VerifieDirection(asMsgErr, asSource, Dir, PEUT_ETRE_INDEFINI);
  if ((NumLigne<0)||(NumLigne>=NBMAXLIGNESBUSTRAM))
   asMsgErr+=asSource+Format(": numéro de ligne de bus incorrect (%d)\n", ARRAYOFCONST((NumLigne)));
 }
//-----------------------------------------------------------------------------
void arret_bus::Copie(arret_bus *a) // v5.1
 {
  Numero=a->Numero;
  x=a->x; y=a->y;
  for(int i=0; i<NBMAXLIGNESBUSTRAM; i++)
   {
    Ligne[i]=a->Ligne[i];
    NumLigne[i]=a->NumLigne[i];
   }
  NbLignes=a->NbLignes;
 };
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
  AnsiString asSource=Format("Arrêt de bus n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  if ((NbLignes<0)||(NbLignes>NBMAXLIGNESBUSTRAM))
   asMsgErr+=asSource+Format(": nombre de lignes de bus incorrect (%d)\n", ARRAYOFCONST((NbLignes)));
  for(i=0; i<NbLignes; i++)
   if (Ligne[i]&&
       ((NumLigne[i]<0)||(NumLigne[i]>NBMAXLIGNESBUSTRAM)))
    asMsgErr+=asSource+Format(": numéro de la %d° ligne de bus incorrect (%d)\n", ARRAYOFCONST((i+1, NumLigne[i]))); // v3.03
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
 { // Attention : On ne stocke pas le nombre et les n° de bus (calculés avant simul)
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &NbArrets, sizeof(NbArrets))&&
         FileRead(hfile, NumArret, NBMAXARRETSBUSTRAMPARLIGNE*sizeof(NumArret[0]));
 }
//-----------------------------------------------------------------------------
bool ligne_bus::Sauve(int hfile) // v3.0
 { // Attention : On ne stocke pas le nombre et les n° de bus (calculés avant simul)
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, &NbArrets, sizeof(NbArrets))&&
         FileWrite(hfile, NumArret, NBMAXARRETSBUSTRAMPARLIGNE*sizeof(NumArret[0]));
 }
//-----------------------------------------------------------------------------
void ligne_bus::Verifie(AnsiString &asMsgErr) // v3.0
 {
  int i;
  AnsiString asSource=Format("Ligne de bus n°%d", ARRAYOFCONST((Numero)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  if ((NbArrets<0)||(NbArrets>NBMAXARRETSBUSTRAMPARLIGNE))
   asMsgErr+=asSource+Format(": nombre d'arrêts de bus incorrect (%d)\n", ARRAYOFCONST((NbArrets)));
  for(i=0; i<NbArrets; i++)
   if ((NumArret[i]<0)||(NumArret[i]>cv->NbArretsBus))
    asMsgErr+=asSource+Format(": numéro du %d° arrêt de bus incorrect (%d)\n", ARRAYOFCONST((i+1, NumArret[i]))); // v3.03
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
     v->FaitDescendrePieton(d, i); // Si on peut pas faire descendre, il descendra au prochain arrêt
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
  // On classe les dir.poss. dans l'ordre < des distances aux arrêts de tram
  // En cas d'égalité, c'est le hasard : (N°Tram.+Tour) Modulo Directions Possibles
  for(i=0; i<nd; i++)
   for(j=0; j<nd; j++)
    if ((i!=j)&&  // Direction possible
        (v->EstDirPossSensVoieTram(InvDir[AncDir], (direction)(d=v->DirSensVoieTram(indefinie, i)))))
     // On dégringole si distance supérieure.
     OrdreDir[d-1]+=((v->DistArretTram[NumArretSvt-1][i]>v->DistArretTram[NumArretSvt-1][j])||
                   ((v->DistArretTram[NumArretSvt-1][i]==v->DistArretTram[NumArretSvt-1][j])&&
                    ((d!=AncDir)|| // En cas d'égalité, préfère garder la direction courante // v3.5 : || par && !
                     ((i+Numero+cv->TourCrt)%nd>(j+Numero+cv->TourCrt)%nd)))); // sinon tirage au hasard (Ici TourCrt+1)
  for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
   for(j=0; (!Dir)&&(j<ndp); j++)
	{
     d=v->DirSensVoieTram(InvDir[AncDir], j);
	 Voie=&(cv->V(x,y,d));
	 if ((OrdreDir[d-1]==i)&&
         ((!v->ToutDroit)||    // Direction interdite si : - Obligation d'aller tout droit ET
          (DirDrnDepl==d))&&   //                            pas même direction que lors du dernier déplacement
         (!v->NumPlaceTaxi)&&  //                          - Place taxi. v3.6
         (!v->NumPlaceVehlib)&& //                         - Place de vehlib v5.3        
         (((!Voie->NumVehicule)&&(!Voie->NumBus)&&(!Voie->NumTram)&&(!Voie->NumTaxi)&&(!Voie->NumVehlib))|| // v5.3 (vehlib)
          (Voie->NumArretTram&&(Voie->NumArretTram==NumArretSvt))||
          (cv->TourCrt<=1+TourDrnDepl+5*cv->AttenteMaxVeh*(1+OrdreDir[d-1])))) // AttentMaxTram = 5*AttenteMaxVeh
      Dir=(direction)d;
    }

   // Si la direction est toujours indéfinie : on prend la meilleure direction possible
   if (!Dir)
    for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
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
  // On classe les dir.poss. dans l'ordre < des distances aux parkings si la case est libre.
  // En cas d'égalité, c'est le hasard : (N°Tram.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if ((i!=j)&&  // Direction possible
        (v->EstDirPossSensVoieTram(InvDir[Dir], (direction)(d=v->DirSensVoieTram(indefinie, i)))))
     // On dégringole si distance supérieure.
     OrdreDir[d-1]+=((v->DistArretTram[NumArretSvt-1][i]>v->DistArretTram[NumArretSvt-1][j])||
                   ((v->DistArretTram[NumArretSvt-1][i]==v->DistArretTram[NumArretSvt-1][j])&&
                    ((d!=Dir)|| // En cas d'égalité, préfère garder la direction courante. // v3.5 : || par && !
                     ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // tirage au hasard en cas d'égalité (Ici TourCrt+1)
  for(i=0; (!DirAuCarrefour)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
   for(j=0; (!DirAuCarrefour)&&(j<ndp); j++)
    if ((OrdreDir[(d=v->DirSensVoieTram(InvDir[Dir], j))-1]==i)&&
        (!v->NumPlaceTaxi)&&  // Direction interdite si : - Place taxi. v3.6
        (!v->NumPlaceVehlib)&& //                         - Place de vehlib v5.3        
        ((!v->ToutDroit)||    //                          - Obligation d'aller tout droit ET
         (DirDrnDepl==d)))    //                            pas même direction que lors du dernier déplacement
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
  AnsiString asSource=Format("Tram n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  VerifieDirection(asMsgErr, asSource, Dir, PEUT_ETRE_INDEFINI);
  if ((NumLigne<0)||(NumLigne>=NBMAXLIGNESBUSTRAM))
   asMsgErr+=asSource+Format(": numéro de ligne de tram incorrect (%d)\n", ARRAYOFCONST((NumLigne)));
 }
//-----------------------------------------------------------------------------
void arret_tram::Copie(arret_tram *a) // v5.1
 {
  Numero=a->Numero;
  x=a->x; y=a->y;
  for(int i=0; i<NBMAXLIGNESBUSTRAM; i++)
   {
    Ligne[i]=a->Ligne[i];
    NumLigne[i]=a->NumLigne[i];
   }
  NbLignes=a->NbLignes;
 };
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
  AnsiString asSource=Format("Arrêt de tram n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
  if ((NbLignes<0)||(NbLignes>NBMAXLIGNESBUSTRAM))
   asMsgErr+=asSource+Format(": nombre de lignes de tram incorrect (%d)\n", ARRAYOFCONST((NbLignes)));
  for(i=0; i<NbLignes; i++)
   if (Ligne[i]&&
       ((NumLigne[i]<0)||(NumLigne[i]>NBMAXLIGNESBUSTRAM)))
    asMsgErr+=asSource+Format(": numéro de la %d° ligne de tram incorrect (%d)\n", ARRAYOFCONST((i+1, NumLigne[i]))); // v3.03
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
 { // Attention : On ne stocke pas le nombre et les n° de tram (calculés avant simul)
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &NbArrets, sizeof(NbArrets))&&
         FileRead(hfile, NumArret, NBMAXARRETSBUSTRAMPARLIGNE*sizeof(NumArret[0]));
 }
//-----------------------------------------------------------------------------
bool ligne_tram::Sauve(int hfile) // v3.0
 { // Attention : On ne stocke pas le nombre et les n° de tram (calculés avant simul)
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, &NbArrets, sizeof(NbArrets))&&
         FileWrite(hfile, NumArret, NBMAXARRETSBUSTRAMPARLIGNE*sizeof(NumArret[0]));
 }
//-----------------------------------------------------------------------------
void ligne_tram::Verifie(AnsiString &asMsgErr) // v3.0
 {
  int i;
  AnsiString asSource=Format("Ligne de tram n°%d", ARRAYOFCONST((Numero)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  if ((NbArrets<0)||(NbArrets>NBMAXARRETSBUSTRAMPARLIGNE))
   asMsgErr+=asSource+Format(": nombre d'arrêts de tram incorrect (%d)\n", ARRAYOFCONST((NbArrets)));
  for(i=0; i<NbArrets; i++)
   if ((NumArret[i]<0)||(NumArret[i]>cv->NbArretsTram))
    asMsgErr+=asSource+Format(": numéro du %d° arrêt de tram incorrect (%d)\n", ARRAYOFCONST((i+1, NumArret[i]))); // v3.03
 }
//-----------------------------------------------------------------------------
///////////// ICI FINISSENT LES METHODES DES CLASSES LIEES AU RESEAU DE TRAM //
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
///////////// ICI COMENCENT LES METHODES DES CLASSES LIEES AU RESEAU DE TAXI //
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
  AnsiString asSource=Format("Place Taxi n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  if (cv->DistancesCalculees) // Vérification avant simulation seulement
   if (Definie()&&(NumFile<0))
    asMsgErr+=asSource+Format(": numéro de file indéfini ou incorrect (%d)\n", ARRAYOFCONST((NumFile)));
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
  return DirSvt; // Si indefinie, il s'agit de la tête de file !
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
      (NbPietonsQuiSontMontes())) // On regarde déjà s'il y a des piétons qui veulent monter...
   { // pour pouvoir partir...
    Situation=stDepart;
    TourDepartDrnCourse=cv->TourCrt;
   }
  Dir=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux files.
  // En cas d'égalité, c'est le hasard : (N°Veh.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if (i!=j) // On dégringole si distance supérieure.
     switch(Situation)
      {
       case stDepart: OrdreDir[i]+=(rand()%2); break; // Le hasard dans toute sa splendeur (en fait le taxi promène le client)
       case stRetour: OrdreDir[i]+=((cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceTaxi&& // 1. File recherchée
                                     (cv->PlaceTaxi[cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceTaxi-1].NumFile==NumFile))>
                                    (cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceTaxi&&
                                     (cv->PlaceTaxi[cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceTaxi-1].NumFile==NumFile)))||
                                   ((v->DistFileTaxi[NumFile][i]>v->DistFileTaxi[NumFile][j])|| // 2. Distance à la file
                                    ((v->DistFileTaxi[NumFile][i]==v->DistFileTaxi[NumFile][j])&&
                                     ((Dirdp[i][v->DirPoss]!=AncDir)|| // 3. En cas d'égalité, préfère garder la direction courante : v2.2.4. // v3.5 : || par && !
                                      ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)
					  break;
       default: break; // v5.4 : évite l'avertissement
      }
  for(i=0; (!Dir)&&(i<5); i++)
   for(j=0; (!Dir)&&(j<ndp); j++)
    {
     Voie=&(cv->V(x,y,Dirdp[j][v->DirPoss]));
     if ((OrdreDir[j]==i)&&
         ((!v->ToutDroit)||    // Direction interdite si :     - obligation d'aller tout droit ET
          (DirDrnDepl==Dirdp[j][v->DirPoss]))&& // pas même direction que lors du dernier déplacement. v3.7.1 : Erreur ! v5.2.3 : Erreur sur Test même direction
         (((!Voie->NumVehicule)&&(!Voie->NumVehlib)&&(!Voie->NumBus)&&    // Sinon... v5.3 (vehlib)
           (!Voie->NumTram)&&(!Voie->NumTaxi)&&(!Voie->NumPlaceVehlib))|| //   - Il n'y a rien sur la route (y compris place vehlib v5.3) OU
          ((Situation==stRetour)&&                                        //   - Il est de retour et c'est la file du retour OU
           (Voie->NumPlaceTaxi&&(cv->PlaceTaxi[Voie->NumPlaceTaxi-1].NumFile==NumFile)))||
          (cv->TourCrt<=1+TourDrnDepl+cv->AttenteMaxVeh*(1+OrdreDir[j])))) // - Il est encore dans sa phase d'attente
      Dir=Dirdp[j][v->DirPoss];
    }

   // Si la direction est toujours indéfinie : on prend la meilleure direction possible
   if (!Dir)
    for(i=0; (!Dir)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
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
  // On classe les dir.poss. dans l'ordre < des distances aux parkings si la case est libre.
  // En cas d'égalité, c'est le hasard : (N°Veh.+Tour) Modulo Directions Possibles
  for(i=0; i<ndp; i++)
   for(j=0; j<ndp; j++)
    if (i!=j)
     switch(Situation)
      {
       case stDepart: OrdreDir[i]+=(rand()%2); break; // Le hasard dans toute sa splendeur (en fait le taxi promène le client)
       case stRetour: OrdreDir[i]+=((cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceTaxi&& // 1. File recherchée
                                     (cv->PlaceTaxi[cv->V(x,y,Dirdp[j][v->DirPoss]).NumPlaceTaxi-1].NumFile==NumFile))>
                                    (cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceTaxi&&
                                     (cv->PlaceTaxi[cv->V(x,y,Dirdp[i][v->DirPoss]).NumPlaceTaxi-1].NumFile==NumFile)))||
                                   ((v->DistFileTaxi[NumFile][i]>v->DistFileTaxi[NumFile][j])||
                                    ((v->DistFileTaxi[NumFile][i]==v->DistFileTaxi[NumFile][j])&&
                                     ((Dirdp[i][v->DirPoss]!=Dir)|| // En cas d'égalité, préfère garder la direction courante : v2.2.4.  // v3.5 : || par && !
                                      ((i+Numero+cv->TourCrt)%ndp>(j+Numero+cv->TourCrt)%ndp)))); // sinon tirage au hasard (Ici TourCrt+1)
                      break;
       default: break; // v5.4 : évite l'avertissement
      }
  for(i=0; (!DirAuCarrefour)&&(i<5); i++) // v3.5 : possibilité de blocage si test n'est pas large (i<5)
   for(j=0; (!DirAuCarrefour)&&(j<ndp); j++)
    if ((OrdreDir[j]==i)&&    // Direction interdite si :
        (!v->NumPlaceVehlib)&&//   - pas de place vehlib (v5.3)
        ((!v->ToutDroit)||    //   - obligation d'aller tout droit ET
         (DirDrnDepl==Dirdp[j][v->DirPoss]))) // pas même direction que lors du dernier déplacement. v3.7.1 : Erreur ! v5.2.3 : Erreur sur Test même direction
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
int taxi::NbPietonsQuiSontMontes() // retourne le nombre de piétons qui attendaient et qui sont montés
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
  AnsiString asSource=Format("Taxi n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  if (NumFile<0)
   asMsgErr+=asSource+Format(": numéro de file indéfini ou incorrect (%d)\n", ARRAYOFCONST((NumFile)));
  VerifiePosition(asMsgErr, asSource, x, y, DOIT_ETRE_DEFINI);
 }
//-----------------------------------------------------------------------------
// Places de parking : v5.0
//-----------------------------------------------------------------------------

bool place_park::Charge(int hfile)
 {
  return FileRead(hfile, &Numero, sizeof(Numero))&&
         FileRead(hfile, &x, sizeof(x))&&
         FileRead(hfile, &y, sizeof(y));
 }
//-----------------------------------------------------------------------------
bool place_park::Sauve(int hfile)
 {
  int xc=x-cv->Xc, yc=y-cv->Yc;
  return FileWrite(hfile, &Numero, sizeof(Numero))&&
         FileWrite(hfile, cv->CopieEnCours?&xc:&x, sizeof(x))&&
         FileWrite(hfile, cv->CopieEnCours?&yc:&y, sizeof(y));
 }
//-----------------------------------------------------------------------------
void place_park::Verifie(AnsiString &asMsgErr)
 {
  AnsiString asSource=Format("Place prkg n°%d (%d,%d)", ARRAYOFCONST((Numero, x, y)));
  if (Numero<0)
   asMsgErr+=asSource+Format(": numéro incorrect (%d)\n", ARRAYOFCONST((Numero)));
  if (cv->DistancesCalculees) // Vérification avant simulation seulement
   if (NumFile<0)
    asMsgErr+=asSource+Format(": numéro de file indéfini ou incorrect (%d)\n", ARRAYOFCONST((NumFile)));
  VerifiePosition(asMsgErr, asSource, x, y, PEUT_ETRE_INDEFINI);
 }
//-----------------------------------------------------------------------------
bool place_park::EstQueueFile()
 {
  return cv->v[x][y].EstQueueFilePark();
 }
//-----------------------------------------------------------------------------
int place_park::PlaceQueueFile() // Retourne 1+NumPlace si elle existe sinon 0
 {
  return cv->v[x][y].PlaceQueueFilePark();
 }
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

voie::voie()
 {
  int i;
  x=-1; y=-1;
  Initialise();
  DistParking=NULL;
  Attente=NULL;
  Trafic=NULL;
  DistArretBus=NULL; // v3.0
  DistArretTram=NULL; // v3.5
  DistFileTaxi=NULL; // v3.6
  DistFilePark=NULL; // v5.0
  DistPlaceVehlib=NULL; // v5.3
 }
//-----------------------------------------------------------------------------
voie::~voie()
 {
  int i, j,
      nd=NbDir[DirPoss],
      ne=cv->NbParkings,
      nab=cv->NbArretsBus, // v3.0
      nat=cv->NbArretsTram, // v3.5
      nft=cv->NbFilesTaxi, // v3.6
      nfp=cv->NbFilesPark, // v5.0
      npv=cv->NbPlacesVehlib; // v5.3
  if (DistParking)
   {
    for(i=0; i<ne; i++)
     {
      for(j=0; j<nd; j++)
       delete[] DistParking[i][j];
      delete[] DistParking[i];
     }
    delete[] DistParking;
   }
  DistParking=NULL;
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
  if (DistFilePark) // v5.0
   {
    for(i=0; i<nfp; i++)
     {
      for(j=0; j<nd; j++)
       delete[] DistFilePark[i][j];
      delete[] DistFilePark[i];
     }
    delete[] DistFilePark;
   }
  DistFilePark=NULL;
  if (DistPlaceVehlib) // v5.3
   {
    for(i=0; i<npv; i++)
     delete[] DistPlaceVehlib[i];
    delete[] DistPlaceVehlib;
   }
  DistPlaceVehlib=NULL;
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
  for(i=0; i<NBDIR; i++)
   {
    Priorite[i]=a_droite;
    NumFeu[i]=0;
    NumFeuP[i]=0; // v5.2
   }
  for(i=0; i<NBMAXPIETONSPARCASE; i++) NumPieton[i]=0; // v3.5 (sorti de la boucle précédente)
  for(i=0; i<NBMAXLIGNESBUSTRAM; i++) LigneTram[i]=LigneBus[i]=false; // v3.5
  DirPoss=aucune;
  NumSpotVehlib=NumPlaceVehlib=NumProchVL=NumVehlib=NbPietons=NumPlacePark=NumTaxi=NumPlaceTaxi=NumArretBus=NumArretTram=NumProchTaxi=NumProchTram=NumProchBus=NumProchVeh=NumParking=NumTram=NumBus=NumVehicule=0; // v3.8 (Nature) v5.0 (Place) v5.3 (vehlib)
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
    NumPlaceVehlib=NumVehlib=NumPlacePark=NumPlaceTaxi=NumArretBus=NumProchTaxi=NumProchBus=NumProchVeh=NumTaxi=NumBus=NumVehicule=0; // v3.7.2 : Pas le parking ! v5.0 (NumPlace) v5.3 (vehlib)
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
  for(int i=0; i<NBDIR; i++)
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
bool voie::PrepareCalculDistances() // v3.0 : inclut également la préparation des distances aux arrêts de bus.
 { // v3.5... Et des trams ! v3.6...Et des taxis ! v5.0...Et des places de parking
  bool Ok=true;
  int i, j,
      nd=NbDir[DirPoss],
      ne=cv->NbParkings,
      nab=cv->NbArretsBus,  // v3.0
      nat=cv->NbArretsTram, // v3.5
      nft=cv->NbFilesTaxi, // v3.6
      nfp=cv->NbFilesPark, // v5.0
      npv=cv->NbPlacesVehlib; // v5.3
  if (DistParking)
   {
    for(i=0; i<ne; i++)
     {
      for(j=0; j<nd; j++)
       delete[] DistParking[i][j];
      delete[] DistParking[i];
     }
    delete[] DistParking;
    DistParking=NULL;
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
  if (DistFilePark) // v5.0
   {
    for(i=0; i<nfp; i++)
     {
      for(j=0; j<nd; j++)
       delete[] DistFilePark[i][j];
      delete[] DistFilePark[i];
     }
    delete[] DistFilePark;
    DistFilePark=NULL;
   }
  if (DistPlaceVehlib) // v5.3
   {
    for(i=0; i<npv; i++)
     delete[] DistPlaceVehlib[i];
    delete[] DistPlaceVehlib;
    DistPlaceVehlib=NULL;
   }
  if (nd>0)
   {
    if (ne>0)
	 {
	  if ((Ok=(!!(DistParking=new int**[ne])))) // D'abord le nombre de parkings
	   for(i=0; Ok&&(i<ne); i++) // Puis le nombre de directions possibles
		{
		 DistParking[i]=NULL;
		 if ((Ok=(!!(DistParking[i]=new int*[nd]))))
		  for(j=0; Ok&&(j<nd); j++) // v3.5
		   if ((Ok=(!!(DistParking[i][j]=new int[2]))))
			DistParking[i][j][0]=DistParking[i][j][1]=DIST_INDEFINIE;
		}
	 }
	if (nab>0) // v3.0
	 {
	  if ((Ok=(!!(DistArretBus=new int*[nab])))) // D'abord le nombre d'arrêts de bus
	   for(i=0; Ok&&(i<nab); i++) // Puis le nombre de directions possibles
		{
		 DistArretBus[i]=NULL;
		 if ((Ok=(!!(DistArretBus[i]=new int[nd]))))
		  for(j=0; j<nd; j++) DistArretBus[i][j]=DIST_INDEFINIE;
		}
	 }
	if (nft>0) // v3.6
	 {
	  if ((Ok=(!!(DistFileTaxi=new int*[nft])))) // D'abord le nombre de files de taxi
	   for(i=0; Ok&&(i<nft); i++) // Puis le nombre de directions possibles
		{
		 DistFileTaxi[i]=NULL;
		 if ((Ok=(!!(DistFileTaxi[i]=new int[nd]))))
		  for(j=0; j<nd; j++) DistFileTaxi[i][j]=DIST_INDEFINIE;
		}
	 }
	if (nfp>0) // v5.0
	 {
	  if ((Ok=(!!(DistFilePark=new int**[nfp])))) // D'abord le nombre de files de parkings
	   for(i=0; Ok&&(i<nfp); i++) // Puis le nombre de directions possibles
		{
		 DistFilePark[i]=NULL;
		 if ((Ok=(!!(DistFilePark[i]=new int*[nd]))))
		  for(j=0; j<nd; j++)
		   if ((Ok=(!!(DistFilePark[i][j]=new int[2]))))
            DistFilePark[i][j][0]=DistFilePark[i][j][1]=DIST_INDEFINIE;
        }
     }
    if (npv>0) // v5.3
     {
	  if ((Ok=(!!(DistPlaceVehlib=new int*[npv])))) // D'abord le nombre de places de vehlib
       for(i=0; Ok&&(i<npv); i++) // Puis le nombre de directions possibles
        {
         DistPlaceVehlib[i]=NULL;
		 if ((Ok=(!!(DistPlaceVehlib[i]=new int[nd]))))
		  for(j=0; j<nd; j++) DistPlaceVehlib[i][j]=DIST_INDEFINIE;
		}
	 }
   }
  nd=NbDirPossSensVoieTram(indefinie); // v3.5
  if ((nd>0)&&(nat>0)) // v3.5
   {
	if ((Ok=(!!(DistArretTram=new int*[nat])))) // D'abord le nombre d'arrêts de tram
	 for(i=0; Ok&&(i<nat); i++) // Puis le nombre de directions possibles
	  {
	   DistArretTram[i]=NULL;
	   if ((Ok=(!!(DistArretTram[i]=new int[nd]))))
        for(j=0; j<nd; j++) DistArretTram[i][j]=DIST_INDEFINIE;
      }
   }
  return Ok;
 }
//-----------------------------------------------------------------------------
bool voie::PrepareCalculAttenteTrafic()
 {
  bool Ok=true;
  int i, j, ne=cv->NbParkings;
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
	if ((Ok=(!!(Attente=new int*[ne+1]))))
	 for(i=0; Ok&&(i<=ne); i++)
	  {
	   Attente[i]=NULL;
	   if ((Ok=(!!(Attente[i]=new int[ne+1]))))
		for(j=0; j<=ne; j++) Attente[i][j]=0;
	  }
	if ((Ok=Ok&&(!!(Trafic=new int*[ne+1]))))
     for(i=0; Ok&&(i<=ne); i++)
      {
       Trafic[i]=NULL;
	   if ((Ok=(!!(Trafic[i]=new int[ne+1]))))
        for(j=0; j<=ne; j++) Trafic[i][j]=0;
      }
   }
  return Ok;
 }
//-----------------------------------------------------------------------------
void voie::CalculeProchainVehiculeOuBusOuTramOuTaxiOuVehlib() // v3.6. Rq : Nécessite de connaître les 2 prochaines directions de chaque Véhicule/Bus/Tram/ (v5.3) Vehlib
 {
  int d, MaxNivP=0,
      NumVV, // NUMéro du Véhicule Voisin. v3.0
      NumLV, // NUMéro du vehLib Voisin. v5.3
      NumBV, // NUMéro du Bus Voisin. v3.0
      NumTV, // NUMéro du Tram Voisin. v3.5
      NumXV, // NUMéro du taXi Voisin. v3.6
      NivPriorite[5]={0,0,0,0,0};
  direction DirCrt, DirAuCarrefour;
  voie *v;

  NumProchVL=NumProchTaxi=NumProchTram=NumProchBus=NumProchVeh=0; // Aucun par défaut. v5.3 (vehlib)
  // 1. S'il y a un piéton, aucun ne peut arriver SAUF (v4.3) :
  if ((!frmSimulation->SimulationSanglante)&& // Mode Sanglant OU
      NbPietons&&                             // NbPietons=NbPiétonsEcrases ALORS on peut rouler dessus (v4.3)
      (NbPietons!=(NumPieton[0]&&
				   (!cv->Pieton[NumPieton[0]-1].EstVivant()))+ // v5.4.1 : !EstVivant() au lieu de Ecrase
				  (NumPieton[1]&&
                   (!cv->Pieton[NumPieton[1]-1].EstVivant()))))   // v5.4.1 : !EstVivant() au lieu de Ecrase
   return;
  // 1bis. S'il y a déjà un véhicule et que ce n'est pas un parking, aucun ne peut arriver
  if (NumVehicule&&(!NumParking)) return;
  // 1ter. S'il y a un bus ou un tram ou un taxi, aucun ne peut arriver. v3.5
  if (NumVehlib||NumBus||NumTram||NumTaxi) return; // v5.3 (ajout vehlib)
  for(d=nord; d<=ouest; d++)
   {
    v=&(cv->V(x,y,d));
    NumVV=v->NumVehicule;
    NumXV=v->NumTaxi; // v3.6
    NumLV=v->NumVehlib; // v5.3
    if (v->EstTeteBus()) NumBV=v->NumBus; else NumBV=0; // v3.0
    if (v->EstTeteTram()) NumTV=v->NumTram; else NumTV=0; // v3.5
    if (NumPlaceVehlib&&(!NumLV)) continue; // v5.3 : on n'accepte que les vehlibs sur la places de vehlib !
    if (NumVV&& // 1. SOIT 1 Vehicule voisin arrivant sur la case ? Priorité 1
        ((!PassageBus)|| // v3.1. Passage Bus interdit sauf...
         (cv->Vehicule[NumVV-1].NivPriorite>normal))) // pour les urgences
     {
	  if ((NivPriorite[d]=((cv->Vehicule[NumVV-1].Dir==InvDir[d])&& // 1 VEHICULE Qui arrive sur la case...
						   cv->TourDeDeplacementVehicule(NumVV-1)&& // Et que c'est son tour de déplacement... (multivitesse : version 1.5). v3.0.4 (chgtde nom)
						   ((!NumVehicule)|| // alors... Soit y a pas de véhicule sur la case,
							((NumParking||NumPlacePark)&&  // soit y en a une mais c'est un parking (v5.0) ou place de parking...
							 cv->Vehicule[NumVV-1].EstDestination(this)))))) // et c'est l'arrivée
       {
        if (!cv->Vehicule[NumVV-1].NivPriorite)
         {
          // 2. Sont-elles obligées de s'arrêter (stop non marqué ou feu non vert) ? Priorité 2
          NivPriorite[d]+=(((v->Priorite[InvDir[d]-1]==stop)&&(cv->Vehicule[NumVV-1].TourDrnDepl>cv->TourCrt-2L))||
                           ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat>vert)));
          // 3. Doivent-elles céder le passage (clp ou stop marqué) ? Priorité 3
          NivPriorite[d]+=2*((v->Priorite[InvDir[d]-1]==cedez_le_passage)||
                             ((v->Priorite[InvDir[d]-1]==stop)&&(cv->TourCrt-cv->Vehicule[NumVV-1].TourDrnDepl>=2L)));
          // 4. Véhicules sur voie à priorité à droite (ou feu inactif/vert) ? Priorité 4
          NivPriorite[d]+=3*((v->Priorite[InvDir[d]-1]==a_droite)||
                             ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat<orange)));
         }
        else // 5. Véhicule prioritaire ? Urgence : Priorité 6 ; Police : Priorité 7
         NivPriorite[d]+=5+cv->Vehicule[NumVV-1].NivPriorite; // v2.2
       }
     }
    else // 1bis. SOIT 1 Bus voisin arrivant sur la case ? Priorité 1. v3.0
     if (NumBV&&(!NumVehicule))
      {
	   if ((NivPriorite[d]=((cv->Bus[NumBV-1].Dir==InvDir[d])&& // 1 BUS Qui arrive sur la case...
							cv->TourDeDeplacementBus(NumBV-1)&& // ET que c'est son tour de déplacement... (multivitesse)
							(cv->TourCrt>=cv->Bus[NumBV-1].TourDepartArretSvt)&& // ET que c'est son tour de départ vers le prochain arrêt
							(!NumBus)))) // et qu'y a pas de bus sur la case
        {
         // 2. Sont-ils obligés de s'arrêter (stop non marqué ou feu non vert) ? Priorité 2
         NivPriorite[d]+=(((v->Priorite[InvDir[d]-1]==stop)&&(cv->Bus[NumBV-1].TourDrnDepl>cv->TourCrt-2L))||
                          ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat>vert)));
         // 3. Doivent-ils céder le passage (clp ou stop marqué) ? Priorité 3
         NivPriorite[d]+=2*((v->Priorite[InvDir[d]-1]==cedez_le_passage)||
                            ((v->Priorite[InvDir[d]-1]==stop)&&(cv->TourCrt-cv->Bus[NumBV-1].TourDrnDepl>=2L)));
         // 4. Bus sur voie à priorité à droite (ou feu inactif/vert) ? Priorité 4
         NivPriorite[d]+=3*((v->Priorite[InvDir[d]-1]==a_droite)||
                            ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat<orange)));
        }
      }
     else // 1ter. SOIT 1 Tram voisin arrivant sur la case ? Priorité 1. v3.5
      if (NumTV&&(!NumVehicule))
       {
		if ((NivPriorite[d]=((cv->Tram[NumTV-1].Dir==InvDir[d])&& // 1 TRAM Qui arrive sur la case...
							 cv->TourDeDeplacementTram(NumTV-1)&& // ET que c'est son tour de déplacement... (multivitesse)
							 (cv->TourCrt>=cv->Tram[NumTV-1].TourDepartArretSvt)&& // ET que c'est son tour de départ vers le prochain arrêt
							 (!NumTram)))) // et qu'y a pas de tram sur la case
         {
          // 2. Sont-ils obligés de s'arrêter (stop non marqué ou feu non vert) ? Priorité 2
          NivPriorite[d]+=(((v->Priorite[InvDir[d]-1]==stop)&&(cv->Tram[NumTV-1].TourDrnDepl>cv->TourCrt-2L))||
                           ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat>vert)));
          // 3. Doivent-ils céder le passage (clp ou stop marqué) ? Priorité 3
          NivPriorite[d]+=2*((v->Priorite[InvDir[d]-1]==cedez_le_passage)||
                             ((v->Priorite[InvDir[d]-1]==stop)&&(cv->TourCrt-cv->Tram[NumTV-1].TourDrnDepl>=2L)));
          // 4. Tram sur voie à priorité à droite (ou feu inactif/vert) ? Priorité 4
          NivPriorite[d]+=3*((v->Priorite[InvDir[d]-1]==a_droite)||
                             ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat<orange)));
         }
       }
      else // 1ter. SOIT 1 Taxi voisin arrivant sur la case ? Priorité 1. v3.5
       if (NumXV&&(!NumVehicule))
        {
		 if ((NivPriorite[d]=((cv->Taxi[NumXV-1].Dir==InvDir[d])&& // 1 TAXI Qui arrive sur la case...
							  cv->TourDeDeplacementTaxi(NumXV-1)&& // ET que c'est son tour de déplacement... (multivitesse)
							  (cv->Taxi[NumXV-1].Situation%2)&& // ET qu'il est sur le départ ou le retour
							  (!NumTaxi)))) // et qu'y a pas de taxi sur la case
          {
           // 2. Sont-ils obligés de s'arrêter (stop non marqué ou feu non vert) ? Priorité 2
           NivPriorite[d]+=(((v->Priorite[InvDir[d]-1]==stop)&&(cv->Taxi[NumXV-1].TourDrnDepl>cv->TourCrt-2L))||
                            ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat>vert)));
           // 3. Doivent-ils céder le passage (clp ou stop marqué) ? Priorité 3
           NivPriorite[d]+=2*((v->Priorite[InvDir[d]-1]==cedez_le_passage)||
                              ((v->Priorite[InvDir[d]-1]==stop)&&(cv->TourCrt-cv->Taxi[NumXV-1].TourDrnDepl>=2L)));
           // 4. Taxi sur voie à priorité à droite (ou feu inactif/vert) ? Priorité 4
           NivPriorite[d]+=3*((v->Priorite[InvDir[d]-1]==a_droite)||
                              ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat<orange)));
          }
        }
       else // 1ter. SOIT 1 vehLib voisin arrivant sur la case ? Priorité 1. v5.3
        if (NumLV&&(!NumVehicule))
         {
		  if ((NivPriorite[d]=((cv->Vehlib[NumLV-1].Dir==InvDir[d])&& // 1 VEHLIB Qui arrive sur la case...
							   cv->TourDeDeplacementVehlib(NumLV-1)&& // ET que c'est son tour de déplacement... (multivitesse)
							   (cv->Vehlib[NumLV-1].Situation==svDepart)&& // ET qu'il est sur le départ
							   (!NumVehlib)))) // et qu'y a pas de taxi sur la case
           {
            // 2. Sont-ils obligés de s'arrêter (stop non marqué ou feu non vert) ? Priorité 2
            NivPriorite[d]+=(((v->Priorite[InvDir[d]-1]==stop)&&(cv->Vehlib[NumLV-1].TourDrnDepl>cv->TourCrt-2L))||
                             ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat>vert)));
            // 3. Doivent-ils céder le passage (clp ou stop marqué) ? Priorité 3
            NivPriorite[d]+=2*((v->Priorite[InvDir[d]-1]==cedez_le_passage)||
                               ((v->Priorite[InvDir[d]-1]==stop)&&(cv->TourCrt-cv->Vehlib[NumLV-1].TourDrnDepl>=2L)));
            // 4. Taxi sur voie à priorité à droite (ou feu inactif/vert) ? Priorité 4
            NivPriorite[d]+=3*((v->Priorite[InvDir[d]-1]==a_droite)||
                               ((v->Priorite[InvDir[d]-1]==feux)&&(cv->Feu[v->NumFeu[InvDir[d]-1]-1].Etat<orange)));
           }
         }
   }
  // 5. Entre véhicules prioritaires (V.P.) :
  //    V.P. tournant à droite ? Priorité 5
  //    V.P. allant tout droit et pas de V.P. venant de droite ? Priorité 5
  //    V.P. tournant à gauche et pas de V.P. venant de la droite ou de devant ? Priorité 5
  for(d=nord; d<=ouest; d++)
   if (NivPriorite[d]==4)
    {
     v=&(cv->V(x,y,d));
     NumVV=v->NumVehicule;
     NumXV=v->NumTaxi; // v3.6
     NumLV=v->NumVehlib; // v5.3
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
         if (NumLV) // v5.3
          {
           DirCrt=cv->Vehlib[NumLV-1].Dir;
           DirAuCarrefour=cv->Vehlib[NumLV-1].ProchaineDirectionAuCarrefour();
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
     NumProchVL=cv->V(x,y,d).NumVehlib; // v5.3
    }
 }
//-----------------------------------------------------------------------------
void voie::DeplaceVehiculeOuBusOuTramOuTaxi() // v3.6 (Taxis)
 {
  if (NumProchVeh&&cv->Vehicule[NumProchVeh-1].PeutPasser())
   {  // Si le prochain véhicule peut arriver sur la case...
    cv->v[cv->Vehicule[NumProchVeh-1].x][cv->Vehicule[NumProchVeh-1].y].NumVehicule=0; // Effacée de la case d'origine
    frmSimulation->RedessineCase(cv->Vehicule[NumProchVeh-1].x, cv->Vehicule[NumProchVeh-1].y, false);
    if (!cv->Vehicule[NumProchVeh-1].EstDestination(this)) // v5.0
     {
      cv->PlaceVehicule(x, y, NumProchVeh); // v2.2.7. Inclut les stats d'Attente/Trafic
      NumVehicule=NumProchVeh;
     }
    else // Parking : NumVehicule est réservé pour les véhicules qui partent du parking uniquement
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
    cv->v[cv->Taxi[NumProchTaxi-1].x][cv->Taxi[NumProchTaxi-1].y].NumTaxi=0; // Effacée de la case d'origine
    frmSimulation->RedessineCase(cv->Taxi[NumProchTaxi-1].x, cv->Taxi[NumProchTaxi-1].y, false);
    cv->PlaceVehiculeTaxi(x, y, NumProchTaxi);
    NumProchTaxi=0;
   }
  if (NumProchVL&&cv->Vehlib[NumProchVL-1].PeutPasser()) // v5.3
   {  // Si le prochain vehlib peut arriver sur la case...
    cv->v[cv->Vehlib[NumProchVL-1].x][cv->Vehlib[NumProchVL-1].y].NumVehlib=0; // Effacée de la case d'origine
    frmSimulation->RedessineCase(cv->Vehlib[NumProchVL-1].x, cv->Vehlib[NumProchVL-1].y, false);
    cv->PlaceVehiculeVehlib(x, y, NumProchVL);
    NumProchVL=0;
   }
 }
//-----------------------------------------------------------------------------
bool voie::PietonPeutAller(direction DirPieton) // v2.0
 {
  return (NbPietons<NBMAXPIETONSPARCASE)&&
         (!NumVehicule)&&
         (!NumVehlib)&& // v5.3
         (!NumBus)&& // v3.0
         (!NumTram)&& // v3.5
         (!NumTaxi)&& // v3.6
         ((PassagePietons&&
           cv->PassagePietonFranchissable(x, y, DirPieton))|| // v5.2
          ((Nature==trottoirs)&& // v5.2
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
void voie::DeplacePietons() //v3.5 : Inclut l'attente aux arrêts de bus/tram, la montée et la descente du bus/tram 
 {
  bool DirTrv;
  int i, d, dd, n,
      NbPietonsDehors=0,
	  NumPietonDehors[NBMAXPIETONSPARCASE]={0,0}; // v5.4.1 : pour savoir si l'on peut effectuer la contamination
  pieton *p, *pv;
  direction NvDir;
  for(i=0; i<NBMAXPIETONSPARCASE; i++)
   if (NumPieton[i]&&
	   (!cv->Pieton[NumPieton[i]-1].NumBus)&& // Ne doit pas être dans un bus,    v3.0
	   (!cv->Pieton[NumPieton[i]-1].NumTram)&&  //             ni dans un tram,   v3.5
	   (!cv->Pieton[NumPieton[i]-1].NumTaxi)&&  //             ni dans un taxi,   v3.6
	   (!cv->Pieton[NumPieton[i]-1].NumVehlib)&&//             ni dans un vehlib  v5.3
	   cv->Pieton[NumPieton[i]-1].EstVivant()&& //             ni mort            v4.3. v5.4.1 : !Ecrase remplacé par EstVivant pour prendre en compte Mort d'épidémie
	   (cv->Pieton[NumPieton[i]-1].TourDrnDepl<cv->TourCrt))
	{
     NbPietonsDehors++;
	 NumPietonDehors[i]=NumPieton[i]; // v5.4.1 : pour savoir si l'on peut effectuer la contamination après déplacement
	 p=&(cv->Pieton[NumPieton[i]-1]);
	 NvDir=indefinie;
	 if (p->ArretBusTrv&&(!PassagePietons)&&(n=cv->V(x,y,p->Dir).NumArretBus)) // Pas d'attente sur un passage piéton (v3.6)
	  { // Si Arrêt de bus trouvé et qu'il arrive dessus alors on attend le bus (bloque le piéton)
	   p->ArretBusTrv=false;
	   p->NumArretBus=n;
	   p->AttendBus=true;
	   p->TourAttBus=cv->TourCrt;
	  }
	 if (p->ArretTramTrv&&(!PassagePietons)&&(n=cv->V(x,y,p->Dir).NumArretTram))// Pas d'attente sur un passage piéton (v3.6)
	  { // Si Arrêt de tram trouvé et qu'il arrive dessus alors on attend le tram (bloque le piéton)
       p->ArretTramTrv=false;
       p->NumArretTram=n;
       p->AttendTram=true;
       p->TourAttTram=cv->TourCrt;
      }
	 if (p->FileTaxiTrv)
	  if ((n=cv->V(x,y,p->Dir).NumPlaceTaxi))
       { // Si file de taxis trouvée
        if ((!PassagePietons)&&(cv->PlaceTaxi[n-1].EstTeteFile())) // v3.6. Pas sur passage piétons
         { // Phase 2 : Si File de taxi trouvée ET qu'il arrive dessus et que c'est la tête de la file ALORS il attend le taxi (bloque le piéton)
          p->NumFileTaxi=cv->PlaceTaxi[n-1].NumFile+1;
          p->FileTaxiTrv=false;
          p->AttendTaxi=true;
          p->TourAttTaxi=cv->TourCrt;
         }
        else
         { // Phase 1 : Recherche de la tête de la file de taxi. ATTENTION ! p->NumFileTaxi>0 n'implique pas que le piéton attend un taxi comme les bus ou les trams.
		  if (!p->NumFileTaxi) p->NumFileTaxi=cv->PlaceTaxi[n-1].NumFile+1; // On fixe la file à chercher
          p->ChercheFileTaxi(); // Change p->Dir pour se diriger vers la tête de file
         }
       }
     if (p->PlaceVehlibTrv) // v5.3
	  if ((n=cv->V(x,y,p->Dir).NumPlaceVehlib))
       { // Si la place est occupé par un vehlib
        if (cv->V(x,y,p->Dir).NumVehlib)
         {  // Phase 2 : Si Place de vehlib trouvée avec vehlib ET qu'il arrive dessus ALORS il attend de prendre le vehlib sans tour d'attente (phase suivante dans le code)
          p->NumPlaceVehlib=n;
          p->PlaceVehlibTrv=false;
          p->AttendVehlib=true; // En fait on attend pas car contrairement aux taxis, il y a forcément un vehlib donc pas de p->TourAttVehlib
         }
       }
     if (p->AttendBus&&(p->TourAttBus+cv->NbMaxToursAttenteBus<cv->TourCrt)) // v3.0.
	  { // Si attente de bus trop longue (paramètre), le piéton abandonne
       p->ArretBusTrv=false;
       p->NumArretBus=0;
       p->AttendBus=false;
       p->TourAttBus=0;
      }
     if (p->AttendTram&&(p->TourAttTram+cv->NbMaxToursAttenteTram<cv->TourCrt)) // v3.5.
      { // Si attente de tram trop longue (paramètre), le piéton abandonne
       p->ArretTramTrv=false;
	   p->NumArretTram=0;
       p->AttendTram=false;
       p->TourAttTram=0;
      }
     if (p->AttendTaxi&&(p->TourAttTaxi+cv->NbMaxToursAttenteTaxi<cv->TourCrt)) // v3.6.
	  { // Si attente de taxi trop longue (paramètre), le piéton abandonne
       p->FileTaxiTrv=false;
       p->NumFileTaxi=0;
       p->AttendTaxi=false;
       p->TourAttTaxi=0;
      }
     if ((!p->AttendBus)&& // Le pieton n'attend ni bus
         (!p->AttendTram)&& //                   ni tram (v3.5)
         (!p->AttendTaxi)&& //                   ni taxi (v3.6)
         (!p->AttendVehlib)&& //                 ni vehlib (v5.3)
         (!p->PsgPtTrv)&& // Le piéton ne se dirige pas déjà vers un passage piéton OU
         (!p->ArretBusTrv)&& //                              vers un arrêt de bus OU
         (!p->ArretTramTrv)&& //                             vers un arrêt de tram OU (v3.5)
		 (!p->FileTaxiTrv)&& //                              vers une tête de file de taxis OU (v3.6)
         (!p->PlaceVehlibTrv)) //                            vers une place de vehlibs (v5.3)
      { // 1. Recherche de passage piéton
       if (cv->ProbaDirPsgPt&& // Si recherche de passage piéton il y a ET
           (NvDir=cv->CherchePassagePietons(x, y, (sens)(2-p->Dir%2)))&& // Passage piéton trouvé ET
		   ((rand()%100)<cv->ProbaDirPsgPt)) // Probabilité d'y aller (paramètre)
        { // Il va vers le passage piéton trouvé
		 p->Dir=NvDir;
		 p->PsgPtTrv=true; // Indique qu'il est en train d'aller vers un passage piéton (inhibe les futures recherches)
		}
	   else // 2. Recherche d'arrêt de bus. v3.0
		if (cv->ProbaDirArretBus&& // Si recherche d'arret de bus il y a ET
			(NvDir=cv->ChercheArretBus(x, y, (sens)(2-p->Dir%2)))&& // Arret bus trouvé ET
			((rand()%100)<cv->ProbaDirArretBus)) // Probabilité d'y aller (paramètre)
		 { // Il va vers l'arrêt de bus
		  p->Dir=NvDir;
		  p->ArretBusTrv=true; // Indique qu'il est en train d'aller vers un arrêt de bus (inhibe les futures recherches)
		 }
		else // 3. Recherche d'arrêt de tram. v3.5
		 if (cv->ProbaDirArretTram&& // Si recherche d'arret de tram il y a ET
			 (NvDir=cv->ChercheArretTram(x, y, (sens)(2-p->Dir%2)))&& // Arret tram trouvé ET
			 ((rand()%100)<cv->ProbaDirArretTram)) // Probabilité d'y aller (paramètre)
		  { // Il va vers l'arrêt de tram
		   p->Dir=NvDir;
		   p->ArretTramTrv=true; // Indique qu'il est en train d'aller vers un arrêt de tram (inhibe les futures recherches)
		  }
		 else // 4. Recherche de file de taxi. v3.6
		  if (cv->ProbaDirFileTaxi&& // Si recherche de file de taxi il y a ET
			  (NvDir=cv->CherchePlaceTaxi(x, y, (sens)(2-p->Dir%2)))&& // Place de taxi trouvée ET
			  ((rand()%100)<cv->ProbaDirFileTaxi)) // Probabilité d'y aller (paramètre)
		   { // Il va vers le tête de file de taxi
			p->Dir=NvDir;
			p->FileTaxiTrv=true; // Indique qu'il est en train d'aller vers une tête de file de taxi (inhibe les futures recherches)
		   }
		 else // 5. Recherche de file de vehlib. v5.3
		  if (cv->ProbaDirFileVehlib&& // Si recherche de file de vehlib il y a ET
			  (NvDir=cv->CherchePlaceVehlib(x, y, (sens)(2-p->Dir%2)))&& // Place de vehlib trouvée ET
			  ((rand()%100)<cv->ProbaDirFileVehlib)) // Probabilité d'y aller (paramètre)
		   { // Il va vers le tête de file de taxi
			p->Dir=NvDir;
			p->PlaceVehlibTrv=true; // Indique qu'il est en train d'aller vers une place de vehlib (inhibe les futures recherches)
		   }
	  }
	 if ((!NvDir)&&(!p->AttendBus)&&(!p->AttendTram)&&(!p->AttendTaxi)&&(!p->AttendVehlib)) // La direction n'a pas changé et aucun bus/tram/taxi/vehlib attendu (il marche tranquillement) v3.6 (taxi) v5.3 (vehlib)
	  {
	   if (p->DemiCase) // Demi-case et même direction : il sort de la case
		{
		 if (cv->V(x,y,p->Dir).PietonPeutAller((direction)p->Dir))
		  {
		   cv->DeplacePieton(NumPieton[i]-1, (x+dx[p->Dir])%cv->NbX, (y+dy[p->Dir])%cv->NbY, (direction)p->Dir);
		  }
		 else // Peut pas sortir : on cherche une autre direction à gauche ou à droite (au sort)
		  {
		   if (cv->TourCrt-cv->Pieton[NumPieton[i]-1].TourDrnDepl>1+cv->AttenteMaxVeh/2)
			{ // S'il a assez attendu (Paramètre AttenteVéhicule/2)
			 for(DirTrv=false,dd=1-2*(rand()%2),d=2-dd; (!DirTrv)&&(d&&(d<NBDIR)); d+=dd)
			  {
			   NvDir=(direction)(1+(p->Dir+d-1)%NBDIR); // à Gauche ou à droite
			   if ((DirTrv=cv->V(x,y,NvDir).PietonPeutAller(NvDir)))
				{
				 p->AnnuleRechercheEnCours(); // Toute recherche est annulée car la direction a changé !
				 cv->DeplacePieton(NumPieton[i]-1, (x+dx[NvDir])%cv->NbX, (y+dy[NvDir])%cv->NbY, NvDir);
				}
			  }
			}
		  }
		}
	  else // Ben c'est la demi-case...
		{ // On regarde si on peut passer la demi-case !
		 if (NumPieton[1-i])
		  {
		   pv=&(cv->Pieton[NumPieton[1-i]-1]); // pv comme piéton voisin
		   if ((((pv->Dir==p->Dir)&&
				 pv->DemiCase)||
				((pv->Dir==InvDir[p->Dir])&&
				 (!pv->DemiCase)))&&
			  (cv->TourCrt-cv->Pieton[NumPieton[i]-1].TourDrnDepl>1+cv->AttenteMaxVeh/2))
			// On choisit une direction à gauche ou à droite (sûre) s'il a assez attendu
			{
			 p->AnnuleRechercheEnCours(); // Toute recherche est annulée car la direction a changé !
			 p->Dir=(direction)(1+(p->Dir+1+2*(rand()%2))%NBDIR);
			}
		  }
		 p->DemiCase++;
		 p->DemiCasesParcourues++; // v3.0
		 p->TourDrnDepl=cv->TourCrt;
		}
	  }
	}
  // v5.4.1 Contamination si mode épidémique
  if (frmSimulation->EpidemieActivee)
   {
	// 1. Infection par contact
	if (NbPietonsDehors==2)
	 {
	  int np1=NumPietonDehors[0],
		  np2=NumPietonDehors[1];
	  pieton *p1=&(cv->Pieton[np1-1]),
			 *p2=&(cv->Pieton[np2-1]);
	  if (p1->EstContagieux()&&
		  (cv->EpidemieReinfections||(!p2->EstGueri()))) // v5.4.2 : Si réinfections possibles (nouveau paramètre) alors un guéri peut être réinfecté
		p2->EstContaminePar(np1, p1->DonneRang()+1);
	  if (p2->EstContagieux()&&
		  (cv->EpidemieReinfections||(!p1->EstGueri()))) // v5.4.2 : Si réinfections possibles (nouveau paramètre) alors un guéri peut être réinfecté
		p1->EstContaminePar(np2, p2->DonneRang()+1);
	 }

	// 2. Infection fatale
	for(i=0; i<NBMAXPIETONSPARCASE; i++)
	  if (NumPietonDehors[i])
	   {
		p=&(cv->Pieton[NumPietonDehors[i]-1]);
		if ((!p->Mort)&&p->DoitSuccomber())
		 {
		  p->SuccombeInfection();
		  if (p->Defini())
			cv->v[p->x][p->y].RedessineCase(false);
		 }
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
void voie::RetirePlacePark() // v5.0
 {
  NumPlacePark=0;
  if (frmSimulation) frmSimulation->RedessineCase(x,y,true);
 }
//-----------------------------------------------------------------------------
void voie::RetirePlaceVehlib() // v5.3
 {
  NumPlaceVehlib=0;
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
   return NumPlaceTaxi; // Pas d'autre place trouvée alors c'est la queue
  else
   return NumPlaceQueue; // Sinon c'est celle qui a été trouvée
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
   return NumPlaceTaxi; // Pas d'autre place trouvée alors c'est la tête
  else
   return NumPlaceTete; // Sinon c'est celle qui a été trouvée
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
bool voie::EstQueueFilePark() // v5.0
 {
  bool EstQueueFile=(NumPlacePark>0);
  voie *v;
  for(int d=nord; EstQueueFile&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    EstQueueFile=((v->DirPoss&InvPossDir[d])==aucune)||(!v->NumPlacePark);
   }
  return EstQueueFile;
 }
//-----------------------------------------------------------------------------
bool voie::EstTeteFilePark() // v5.0
 {
  bool EstTeteFile=(NumPlacePark>0);
  voie *v;
  for(int d=nord; EstTeteFile&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    EstTeteFile=(((DirPoss&PossDir[d])==aucune)||(!v->NumPlacePark));
   }
  return EstTeteFile;
 }
//-----------------------------------------------------------------------------
int voie::PlaceQueueFilePark() // v5.0. Retourne 1+NumPlace si elle existe sinon 0
 {
  int NumPlaceQueue=0;
  voie *v;
  if (!NumPlacePark) return 0; // N'est pas une place de parking
  for(int d=nord; (!NumPlaceQueue)&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    if ((v->DirPoss&InvPossDir[d])&&v->NumPlacePark)
     NumPlaceQueue=v->PlaceQueueFilePark();
   }
  if (!NumPlaceQueue)
   return NumPlacePark; // Pas d'autre place trouvée alors c'est la queue
  else
   return NumPlaceQueue; // Sinon c'est celle qui a été trouvée
 }
//-----------------------------------------------------------------------------
int voie::PlaceTeteFilePark() // v5.0. Retourne 1+NumPlace si elle existe sinon 0
 {
  int NumPlaceTete=0;
  voie *v;
  if (!NumPlacePark) return 0; // N'est pas une place de taxi
  if (EstTeteFilePark()) return NumPlacePark;
  for(int d=nord; (!NumPlaceTete)&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    if ((DirPoss&PossDir[d])&&v->NumPlacePark)
     NumPlaceTete=v->PlaceTeteFilePark();
   }
  if (!NumPlaceTete)
   return NumPlacePark; // Pas d'autre place trouvée alors c'est la tête
  else
   return NumPlaceTete; // Sinon c'est celle qui a été trouvée
 }
//-----------------------------------------------------------------------------
bool voie::ExistePlusieursQueuesFilePark() // v5.0
 {
  int NbQueues=0;
  voie *v;
  if (NumPlacePark)
   for(int d=nord; d<=ouest; d++)
    {
     v=&(cv->V(x,y,d));
     NbQueues+=((v->DirPoss&InvPossDir[d])&&v->NumPlacePark);
    }
  return NbQueues>1;
 }
//-----------------------------------------------------------------------------
bool voie::ExistePlusieursTetesFilePark() // v5.0
 {
  int NbTetes=0;
  voie *v;
  if (NumPlacePark)
   for(int d=nord; d<=ouest; d++)
    {
     v=&(cv->V(x,y,d));
     NbTetes+=((v->DirPoss&PossDir[d])&&v->NumPlacePark);
    }
  return NbTetes>1;
 }
//-----------------------------------------------------------------------------
bool voie::EstQueueFileVehlibs() // v5.3
 {
  bool EstQueueFile=(NumPlaceVehlib>0);
  voie *v;
  for(int d=nord; EstQueueFile&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    EstQueueFile=((v->DirPoss&InvPossDir[d])==aucune)||(!v->NumPlaceVehlib);
   }
  return EstQueueFile;
 }
//-----------------------------------------------------------------------------
bool voie::EstTeteFileVehlibs() // v5.3
 {
  bool EstTeteFile=(NumPlaceVehlib>0);
  voie *v;
  for(int d=nord; EstTeteFile&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    EstTeteFile=(((DirPoss&PossDir[d])==aucune)||(!v->NumPlaceVehlib));
   }
  return EstTeteFile;
 }
//-----------------------------------------------------------------------------
int voie::PlaceQueueFileVehlib() // v5.3. Retourne 1+NumPlace si elle existe sinon 0
 {
  int NumPlaceQueue=0;
  voie *v;
  if (!NumPlaceVehlib) return 0; // N'est pas une place de vehlib
  for(int d=nord; (!NumPlaceQueue)&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    if ((v->DirPoss&InvPossDir[d])&&v->NumPlaceVehlib)
     NumPlaceQueue=v->PlaceQueueFileVehlib();
   }
  if (!NumPlaceQueue)
   return NumPlaceVehlib; // Pas d'autre place trouvée alors c'est la queue
  else
   return NumPlaceQueue; // Sinon c'est celle qui a été trouvée
 }
//-----------------------------------------------------------------------------
int voie::PlaceTeteFileVehlib() // v5.3. Retourne 1+NumPlace si elle existe sinon 0
 {
  int NumPlaceTete=0;
  voie *v;
  if (!NumPlaceVehlib) return 0; // N'est pas une place de vehlib
  if (EstTeteFileVehlibs()) return NumPlaceVehlib;
  for(int d=nord; (!NumPlaceTete)&&(d<=ouest); d++)
   {
    v=&(cv->V(x,y,d));
    if ((DirPoss&PossDir[d])&&v->NumPlaceVehlib)
     NumPlaceTete=v->PlaceTeteFileVehlib();
   }
  if (!NumPlaceTete)
   return NumPlaceVehlib; // Pas d'autre place trouvée alors c'est la tête
  else
   return NumPlaceTete; // Sinon c'est celle qui a été trouvée
 }
//-----------------------------------------------------------------------------
bool voie::ExistePlusieursQueuesFileVehlibs() // v5.3
 {
  int NbQueues=0;
  voie *v;
  if (NumPlaceVehlib)
   for(int d=nord; d<=ouest; d++)
    {
     v=&(cv->V(x,y,d));
     NbQueues+=((v->DirPoss&InvPossDir[d])&&v->NumPlaceVehlib);
    }
  return NbQueues>1;
 }
//-----------------------------------------------------------------------------
bool voie::ExistePlusieursTetesFileVehlibs() // v5.3
 {
  int NbTetes=0;
  voie *v;
  if (NumPlaceVehlib)
   for(int d=nord; d<=ouest; d++)
    {
     v=&(cv->V(x,y,d));
     NbTetes+=((v->DirPoss&PossDir[d])&&v->NumPlaceVehlib);
    }
  return NbTetes>1;
 }
//-----------------------------------------------------------------------------
int voie::OrientationPlaceVehlib() // v5.3 : Permet d'orienter l'image de la place selon l'orientation de la file !
 {
  int Orientation=0;
  if (NumPlaceVehlib)
   for(int d=nord; (!Orientation)&&(d<=ouest); d++)
    if (DirPoss&PossDir[(direction)d])
     Orientation=d-1;
   return Orientation;
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
void voie::CalculeDistanceParking(int e, int DistSansPsgBus, int DistAvecPsgBus, direction DirOrig) // 0 <= e < NbParkings
 {
  if (DirOrig)
   { // v3.5
    if (DistParking[e][NumDirdp[DirOrig][DirPoss]][SANSPSGBUS]>DistSansPsgBus)
     DistParking[e][NumDirdp[DirOrig][DirPoss]][SANSPSGBUS]=DistSansPsgBus;
    if (DistParking[e][NumDirdp[DirOrig][DirPoss]][AVECPSGBUS]>DistAvecPsgBus)
     DistParking[e][NumDirdp[DirOrig][DirPoss]][AVECPSGBUS]=DistAvecPsgBus;
   }
  for(int d=nord; d<=ouest; d++)
   { // ATTENTION, faire un saut à v(x,y,d,2) si obligation d'aller tout droit car risque qu'il ne soit pas défini plus tard par isolation (on ne passe pas deux fois sur une même case)
    int DistCrtAvecPsgBus=DistAvecPsgBus,
        DistCrtSansPsgBus=DistSansPsgBus; // Distances par défaut (v3.9.1)
    voie *VoieCrt=v((direction)d), *Voie2Cases=&(cv->V_(x,y,2,d));
    if (ToutDroit&&((DirPoss&InvPossDir[d])==InvPossDir[d])) // SI ToutDroit ET d est une direction possible (Tout Droit) ALORS on ne prend que la distance de la case d'en face (v3.9.1)
     {
      voie *VoieOpposee=v(InvDir[d]);
      DistCrtAvecPsgBus=VoieOpposee->DistParking[e][NumDirdp[InvDir[d]][VoieOpposee->DirPoss]][AVECPSGBUS]; // distance depuis la case d'en face (avec passage bus)
      DistCrtSansPsgBus=VoieOpposee->DistParking[e][NumDirdp[InvDir[d]][VoieOpposee->DirPoss]][SANSPSGBUS]; // distance depuis la case d'en face (sans passage bus)
      if (DistCrtAvecPsgBus!=DIST_INDEFINIE) DistCrtAvecPsgBus++; // Si distance définie, on l'incrémente de 1
      if (DistCrtSansPsgBus!=DIST_INDEFINIE) DistCrtSansPsgBus++; // Si distance définie, on l'incrémente de 1
     }
    if (VoieCrt->PassageBus)
     {
      if (((VoieCrt->DirPoss&InvPossDir[d])==InvPossDir[d])&& // Si VoieCrt pointe sur le parking ET
          (VoieCrt->DistParking[e][NumDirdp[InvDir[d]][VoieCrt->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+1))
       VoieCrt->CalculeDistanceParking( e,
                                      DIST_INDEFINIE,
                                      DistCrtAvecPsgBus+1,
                                      InvDir[d]);
      if ((VoieCrt->ToutDroit&& // v3.9.1 (On traite le ToutDroit : 2 cases)
          ((Voie2Cases->DirPoss&InvPossDir[d])==InvPossDir[d])&&
          (Voie2Cases->DistParking[e][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+2)))
       Voie2Cases->CalculeDistanceParking( e,
                                         DIST_INDEFINIE,
                                         DistCrtAvecPsgBus+2,
                                         InvDir[d]);
     }
    else
     {
      if (((VoieCrt->DirPoss&InvPossDir[d])==InvPossDir[d])&&
          ((VoieCrt->DistParking[e][NumDirdp[InvDir[d]][VoieCrt->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+1)||
           (VoieCrt->DistParking[e][NumDirdp[InvDir[d]][VoieCrt->DirPoss]][SANSPSGBUS]>DistCrtSansPsgBus+1)))
       VoieCrt->CalculeDistanceParking( e,
                                      (DistCrtSansPsgBus==DIST_INDEFINIE)?DIST_INDEFINIE:DistCrtSansPsgBus+1,
                                      DistCrtAvecPsgBus+1,
                                      InvDir[d]);
      if (VoieCrt->ToutDroit&& // v3.9.1 (On traite le ToutDroit : 2 cases)
          ((Voie2Cases->DirPoss&InvPossDir[d])==InvPossDir[d])&&
          ((Voie2Cases->DistParking[e][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+2)||
           (Voie2Cases->DistParking[e][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]][SANSPSGBUS]>DistCrtSansPsgBus+2)))
       Voie2Cases->CalculeDistanceParking( e,
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
    if (((VoieCrt->DirPoss&InvPossDir[d])==InvPossDir[d])&& // Si VoieCrt pointe sur l'arrêt de bus ET
        (VoieCrt->DistArretBus[ab][NumDirdp[InvDir[d]][VoieCrt->DirPoss]]>Distance+1)) // Distance indéfinie
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
   { // v5.4 : manquait parenthèses autour de b&&c (a||(b&&c))
	if ((DirOrig&&EstDirPossSensVoieTram((direction)d, DirOrig))|| // Si une voie va vers DirOrig (définie) depuis d OU
		((!DirOrig)&&EstDirPossSensVoieTram(indefinie, (direction)d))) // on part d'un arrêt de tram (DirOrig==indefinie) et on regarde toutes les directions
     {
      voie *VoieCrt=v((direction)d);
      if (VoieCrt->DistArretTram[at][VoieCrt->NumDirPossSensVoieTram(indefinie, InvDir[d])]>Distance+1) // Distance indéfinie
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
        (VoieCrt->DistFileTaxi[ft][NumDirdp[InvDir[d]][VoieCrt->DirPoss]]>Distance+1)) // Distance indéfinie
     VoieCrt->CalculeDistanceFileTaxi(ft, Distance+1, InvDir[d]); // On lance le calcul de distance
    if ((VoieCrt->ToutDroit&& // v3.9.1 (On traite le ToutDroit : 2 cases)
        ((Voie2Cases->DirPoss&InvPossDir[d])==InvPossDir[d])&&
        (Voie2Cases->DistFileTaxi[ft][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]]>Distance+2)))
     Voie2Cases->CalculeDistanceFileTaxi(ft, Distance+2, InvDir[d]);
   }
 }
//-----------------------------------------------------------------------------
void voie::CalculeDistanceFilePark(int fp, int DistSansPsgBus, int DistAvecPsgBus, direction DirOrig) // 0 <= fp < NbFilesPark. v5.0
 {
  if (DirOrig)
   { // v3.5
    if (DistFilePark[fp][NumDirdp[DirOrig][DirPoss]][SANSPSGBUS]>DistSansPsgBus)
     DistFilePark[fp][NumDirdp[DirOrig][DirPoss]][SANSPSGBUS]=DistSansPsgBus;
    if (DistFilePark[fp][NumDirdp[DirOrig][DirPoss]][AVECPSGBUS]>DistAvecPsgBus)
     DistFilePark[fp][NumDirdp[DirOrig][DirPoss]][AVECPSGBUS]=DistAvecPsgBus;
   }
  for(int d=nord; d<=ouest; d++)
   { // ATTENTION, faire un saut à v(x,y,d,2) si obligation d'aller tout droit car risque qu'il ne soit pas défini plus tard par isolation (on ne passe pas deux fois sur une même case)
    int DistCrtAvecPsgBus=DistAvecPsgBus,
        DistCrtSansPsgBus=DistSansPsgBus; // Distances par défaut (v3.9.1)
    voie *VoieCrt=v((direction)d), *Voie2Cases=&(cv->V_(x,y,2,d));
    if (ToutDroit&&((DirPoss&InvPossDir[d])==InvPossDir[d])) // SI ToutDroit ET d est une direction possible (Tout Droit) ALORS on ne prend que la distance de la case d'en face (v3.9.1)
     {
      voie *VoieOpposee=v(InvDir[d]);
      DistCrtAvecPsgBus=VoieOpposee->DistFilePark[fp][NumDirdp[InvDir[d]][VoieOpposee->DirPoss]][AVECPSGBUS]; // distance depuis la case d'en face (avec passage bus)
      DistCrtSansPsgBus=VoieOpposee->DistFilePark[fp][NumDirdp[InvDir[d]][VoieOpposee->DirPoss]][SANSPSGBUS]; // distance depuis la case d'en face (sans passage bus)
      if (DistCrtAvecPsgBus!=DIST_INDEFINIE) DistCrtAvecPsgBus++; // Si distance définie, on l'incrémente de 1
      if (DistCrtSansPsgBus!=DIST_INDEFINIE) DistCrtSansPsgBus++; // Si distance définie, on l'incrémente de 1
     }
    if (VoieCrt->PassageBus)
     {
      if (((VoieCrt->DirPoss&InvPossDir[d])==InvPossDir[d])&& // Si VoieCrt pointe sur le parking ET
          (VoieCrt->DistFilePark[fp][NumDirdp[InvDir[d]][VoieCrt->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+1))
       VoieCrt->CalculeDistanceFilePark( fp,
                                      DIST_INDEFINIE,
                                      DistCrtAvecPsgBus+1,
                                      InvDir[d]);
      if ((VoieCrt->ToutDroit&& // v3.9.1 (On traite le ToutDroit : 2 cases)
          ((Voie2Cases->DirPoss&InvPossDir[d])==InvPossDir[d])&&
          (Voie2Cases->DistFilePark[fp][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+2)))
       Voie2Cases->CalculeDistanceFilePark( fp,
                                         DIST_INDEFINIE,
                                         DistCrtAvecPsgBus+2,
                                         InvDir[d]);
     }
    else
     {
      if (((VoieCrt->DirPoss&InvPossDir[d])==InvPossDir[d])&&
          ((VoieCrt->DistFilePark[fp][NumDirdp[InvDir[d]][VoieCrt->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+1)||
           (VoieCrt->DistFilePark[fp][NumDirdp[InvDir[d]][VoieCrt->DirPoss]][SANSPSGBUS]>DistCrtSansPsgBus+1)))
       VoieCrt->CalculeDistanceFilePark( fp,
                                      (DistCrtSansPsgBus==DIST_INDEFINIE)?DIST_INDEFINIE:DistCrtSansPsgBus+1,
                                      DistCrtAvecPsgBus+1,
                                      InvDir[d]);
      if (VoieCrt->ToutDroit&& // v3.9.1 (On traite le ToutDroit : 2 cases)
          ((Voie2Cases->DirPoss&InvPossDir[d])==InvPossDir[d])&&
          ((Voie2Cases->DistFilePark[fp][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]][AVECPSGBUS]>DistCrtAvecPsgBus+2)||
           (Voie2Cases->DistFilePark[fp][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]][SANSPSGBUS]>DistCrtSansPsgBus+2)))
       Voie2Cases->CalculeDistanceFilePark( fp,
                                         (DistCrtSansPsgBus==DIST_INDEFINIE)?DIST_INDEFINIE:DistCrtSansPsgBus+2,
                                         DistCrtAvecPsgBus+2,
                                         InvDir[d]);
     }
   }
 }
//-----------------------------------------------------------------------------
void voie::CalculeDistancePlaceVehlib(int pv, int Distance, direction DirOrig) // v5.3. 0 <= pv < NbPlacesVehlib
 {
  if (DirOrig) DistPlaceVehlib[pv][NumDirdp[DirOrig][DirPoss]]=Distance;
  for(int d=nord; d<=ouest; d++)
   {
    voie *VoieCrt=v((direction)d), *Voie2Cases=&(cv->V_(x,y,2,d));
    if (((VoieCrt->DirPoss&InvPossDir[d])==InvPossDir[d])&& // Si VoieCrt pointe sur la place de vehlib ET
        (VoieCrt->DistPlaceVehlib[pv][NumDirdp[InvDir[d]][VoieCrt->DirPoss]]>Distance+1)) // Distance indéfinie
     VoieCrt->CalculeDistancePlaceVehlib(pv, Distance+1, InvDir[d]); // On lance le calcul de distance
    if ((VoieCrt->ToutDroit&& // On traite le ToutDroit : 2 cases
        ((Voie2Cases->DirPoss&InvPossDir[d])==InvPossDir[d])&&
        (Voie2Cases->DistPlaceVehlib[pv][NumDirdp[InvDir[d]][Voie2Cases->DirPoss]]>Distance+2)))
     Voie2Cases->CalculeDistancePlaceVehlib(pv, Distance+2, InvDir[d]);
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
  SensVoieTram=(sens_voie_tram)(((int)SensVoieTram)^((int)SensVoieTramDir[DirOrig][DirDest])); // v5.4 : conversion BCB6>BCBX pas de a^=b sur énumérés.
  RedessineCase(true);
 }
//-----------------------------------------------------------------------------
direction voie::DirSensVoieTram(direction DirOrigine, int iDir) // v3.5
 { // ATTENTION : 0<=iDir<=3 (0 = première, etc.)
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
bool voie::ExisteVoieDansDirection(type_voie TypeVoie, direction d) // v5.4 : pas de inline pour éviter avertissement "non trouvé"
 { // v3.5 // condition nécessaire d>indefinie
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
    if ((Nature!=trottoirs)||
        (NvNature==trottoirs)||
        !_FEUXPIETONS) // v5.2 : on empêche la suppression des trottoirs libres (sans décors) si des feux de piétons existent
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
bool voie::FeuPietonsPossible() //v5.2
 {
  return (Nature==trottoirs)&& // Trottoirs sans décors  : les piétons peuvent passer
         (!DirPoss)&&(!SensVoieTram); // ET Pas de voies de circulation
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
     FileRead(hfile, &NumParking, sizeof(NumParking))&&
     FileRead(hfile, &ToutDroit, sizeof(ToutDroit))&&
     FileRead(hfile, &PassagePietons, sizeof(PassagePietons))&& // v2.0
     ((VersionFichier<0x300)|| // v3.0
      (FileRead(hfile, &PassageBus, sizeof(PassageBus))&&
       FileRead(hfile, &NumArretBus, sizeof(NumArretBus))))&&
     ((VersionFichier<0x350)|| // v3.5
      (FileRead(hfile, &NumArretTram, sizeof(NumArretTram))))&&
     ((VersionFichier<0x360)|| // v3.6
      (FileRead(hfile, &NumPlaceTaxi, sizeof(NumPlaceTaxi))))&&
     ((VersionFichier<0x500)|| // v5.0
      (FileRead(hfile, &NumPlacePark, sizeof(NumPlacePark))))&&
     ((VersionFichier<0x530)|| // v5.3
      (FileRead(hfile, &NumPlaceVehlib, sizeof(NumPlaceVehlib))&&
       FileRead(hfile, &NumSpotVehlib, sizeof(NumSpotVehlib))));
  for(i=0; Ok&&(i<NBFEUXPARCASE); i++) // v5.2: NBFEUXPARCASE
   Ok=FileRead(hfile, &(Priorite[i]), sizeof(Priorite[i]))&&
      FileRead(hfile, &(NumFeu[i]), sizeof(NumFeu[i]));
  if (Ok)   // v5.1.1 : élimination automatique des feux fantômes !
   for(i=0; i<NBFEUXPARCASE; i++)
    if (NumFeu[i]&&
        ((cv->Feu[NumFeu[i]-1].x!=x)||
         (cv->Feu[NumFeu[i]-1].y!=y)))
     NumFeu[i]=0; // Feu fantôme effacé !
  if (VersionFichier>=0x520) // v5.2 : feux piétons
   for(i=0; Ok&&(i<NBFEUXPARCASE); i++)
    Ok=FileRead(hfile, &(NumFeuP[i]), sizeof(NumFeuP[i]));
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
     FileWrite(hfile, &NumParking, sizeof(NumParking))&&
     FileWrite(hfile, &ToutDroit, sizeof(ToutDroit))&&
     FileWrite(hfile, &PassagePietons, sizeof(PassagePietons)); // v2.0
     FileWrite(hfile, &PassageBus, sizeof(PassageBus))&& // v3.0
     FileWrite(hfile, &NumArretBus, sizeof(NumArretBus))&& // v3.0
     FileWrite(hfile, &NumArretTram, sizeof(NumArretTram))&& // v3.5
     FileWrite(hfile, &NumPlaceTaxi, sizeof(NumPlaceTaxi))&& // v3.6
     FileWrite(hfile, &NumPlacePark, sizeof(NumPlacePark))&& // v5.0
     FileWrite(hfile, &NumPlaceVehlib, sizeof(NumPlaceVehlib))&& // v5.3
     FileWrite(hfile, &NumSpotVehlib, sizeof(NumSpotVehlib)); // v5.3
  for(i=0; Ok&&(i<NBFEUXPARCASE); i++)
   Ok=FileWrite(hfile, &(Priorite[i]), sizeof(Priorite[i]))&&
      FileWrite(hfile, &(NumFeu[i]), sizeof(NumFeu[i]));
  for(i=0; Ok&&(i<NBFEUXPARCASE); i++)
   Ok=FileWrite(hfile, &(NumFeuP[i]), sizeof(NumFeuP[i]));
  return Ok;
 }
//-----------------------------------------------------------------------------
void voie::Verifie(AnsiString &asMsgErr)
 {
  int i, xx, yy;
  AnsiString asSource=Format("Case (%d,%d)", ARRAYOFCONST((x, y)));
  VerifiePosition(asMsgErr, asSource, x, y, DOIT_ETRE_DEFINI);
  VerifieDirPoss(asMsgErr, asSource, DirPoss);
  for(i=0; i<NBDIR; i++)
   {
    VerifiePriorite(asMsgErr, asSource+" ("+asDir[i+1]+")", Priorite[i]);
    if (NumFeu[i]&&(Priorite[i]!=feux))
     asMsgErr+=asSource+Format(": numéro de feu %s mais priorité différente de Feu (%d)\n", ARRAYOFCONST((asDir[i+1], (int)Priorite[i]))); // v5.4 enum as char type (cast int)
    if ((NumFeu[i]<0)||(NumFeu[i]>cv->NbFeux))
     asMsgErr+=asSource+Format(": numéro de feu %s incorrect (%d)\n", ARRAYOFCONST((asDir[i+1], NumFeu[i])));
    else
     if (NumFeu[i])
      {
       cv->Feu[NumFeu[i]-1].Verifie(asMsgErr, asSource+Format(" Feu %s", ARRAYOFCONST((asDir[i+1]))));
       if ((x!=(xx=cv->Feu[NumFeu[i]-1].x))||(y!=(yy=cv->Feu[NumFeu[i]-1].y)))
        asMsgErr+=asSource+Format(": coordonnées du feu %s (%d,%d) différentes des coordonnées de la case\n", ARRAYOFCONST((asDir[i+1], xx, yy)));
      }
   }
  // Complément des contrôles (v3.6)
  if ((NumParking<0)||(NumParking>cv->NbParkings))
   asMsgErr+=asSource+Format(": numéro de parking incorrect (%d)\n", ARRAYOFCONST((NumParking))); // v5.0 (correction message erroné)
  if ((NumArretBus<0)||(NumArretBus>cv->NbArretsBus))
   asMsgErr+=asSource+Format(": numéro d'arrêt de bus incorrect (%d)\n", ARRAYOFCONST((NumArretBus)));
  if ((NumArretTram<0)||(NumArretTram>cv->NbArretsTram))
   asMsgErr+=asSource+Format(": numéro d'arrêt de tram incorrect (%d)\n", ARRAYOFCONST((NumArretTram)));
  if ((NumPlaceTaxi<0)||(NumPlaceTaxi>cv->NbPlacesTaxi))
   asMsgErr+=asSource+Format(": numéro de place de taxi incorrect (%d)\n", ARRAYOFCONST((NumPlaceTaxi)));
  if ((NumPlacePark<0)||(NumPlacePark>cv->NbPlacesPark)) // v5.0
   asMsgErr+=asSource+Format(": numéro de place de parking incorrect (%d)\n", ARRAYOFCONST((NumPlacePark)));
 }
//-----------------------------------------------------------------------------
void stats::Definit()
 {
  NbVehiculesDeplaces=cv->NbVehiculesDeplaces;
  NbVehiculesArrives=cv->NbVehiculesArrives;
  NbVehiculesSortis=cv->NbVehiculesSortis;
  // v5.4.1 : stats épidémiques des piétons
  NbPietonsGueris=cv->NbPietonsGueris;
  NbPietonsInfectes=cv->NbPietonsInfectes;
  NbPietonsMorts=cv->NbPietonsMorts;
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
  NbVehiculesSortis=NbVehiculesDeplaces=NbVehiculesArrives=0L;
  NbPietonsGueris=NbPietonsInfectes=NbPietonsMorts=0L; // v5.4.1 : stats épidémiques des piétons
  DureeOrange=NbParkings=NbTrams=NbBus=NbVehicules=NbFeux=NbFeuxPieton=0L; // v3.0 (NbBus) v3.5 (NbTrams), v5.2 (NbFeuxPieton)
  AttenteMaxVeh=10L;
  NbVitesses=1;
  NbToursStats=100;
  TypeStats=par_pourcentage; // v3.5
  NbMaxCasesDetectPsgPt=5; // v3.0.5
  ProbaDirPsgPt=50;
  NbMaxCasesDetectFileVehlib=NbMaxCasesDetectFileTaxi=NbMaxCasesDetectArretTram=NbMaxCasesDetectArretBus=3; // v3.6 (taxi) v5.3 (vehlib)
  ProbaDirFileVehlib=ProbaDirFileTaxi=ProbaDirArretTram=ProbaDirArretBus=50; // v3.6 (taxi) v5.3 (vehlib)
  ProbaArretTaxiDmd=ProbaArretTramDmd=ProbaArretBusDmd=10; // v3.6 (taxi)
  TauxRemplissageVehlib=80; // v5.3. 80% par défaut pour avoir 4/5 pour que des places soient libres au moment des premiers vehlibs pris... 
  NbMaxPersonnesTram=NbMaxPersonnesBus=100; // v3.5
  NbMaxPersonnesVehlib=NbMaxPersonnesTaxi=3; // v3.6 (taxi) v5.3 (vehlib)
  NbToursStopArretTram=NbToursStopArretBus=3; // v3.5
  NbMaxToursAttenteTaxi=NbMaxToursAttenteTram=NbMaxToursAttenteBus=25; // v3.6 (taxi) v5.3 (vehlib)
  VerifOk=DistancesCalculees=QuadrillageStats=false;
  NbFilesPark=NbPlacesPark=0L; // v5.0
  NbPlacesVehlib=0L; // v5.3
  Feu=NULL;
  Parking=NULL;
  Vehicule=NULL;
  Vehlib=NULL; // v5.3
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
  PlacePark=NULL; // v5.0
  FilePark=NULL; // v5.0
  PlaceVehlib=NULL; // v5.3
  for(int i=0; i<NBMAXLIGNESBUSTRAM; i++)
   {
    LigneBus[i].AffecteNumero(i+1); // v3.0
    LigneTram[i].AffecteNumero(i+1); // v3.5
   }
  // Tableaux avec nombre par défaut
  if (NbElementsParDefaut)
   {
    DefinitNbFeux(NBFEUXDEFAUT);
    DefinitNbFeuxPietons(NBFEUXPIETONDEFAUT); // v5.2
    DefinitNbParkings(NBETAPESDEFAUT);
    DefinitNbVehicules(NBVEHICULESDEFAUT);
    DefinitNbPietons(NBPIETONSDEFAUT); // v2.0
   }
  // Propriétés pour la génération aléatoire de réseau (v4.2)
  LgrMinSgmtRoute=LgrMaxSgmtRoute=ProbaSortieIntersection=ProbaEntreeIntersection=ProbaTraverseeRoute=0;
  // v5.4.1 paramètres par défaut de l'épidémie (si activée)
  EpidemieInfectiosite=100; // Nb tours
  EpidemieIterationPatientZero=100; // Nb piétons
  EpidemieChargeFatale=10; // Charge virale à partir de laquelle le piéton succombera au bout de la période d'infectiosité
  EpidemieReinfections = false; // v5.4.2
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
  if (Parking) { delete[] Parking; Parking=NULL; }
  if (Vehicule) { delete[] Vehicule; Vehicule=NULL; }
  if (Vehlib) { delete[] Vehlib; Vehlib=NULL; } // v5.3
  if (Pieton) { delete[] Pieton; Pieton=NULL; }
  if (ArretBus) { delete[] ArretBus; ArretBus=NULL; } // v3.6
  if (ArretTram) { delete[] ArretTram; ArretTram=NULL; } // v3.6
  if (Taxi) { delete[] Taxi; Taxi=NULL; } // v3.6
  if (PlaceTaxi) { delete[] PlaceTaxi; PlaceTaxi=NULL; } // v3.6
  if (FileTaxi) { delete[] FileTaxi; FileTaxi=NULL; } // v3.6
  if (PlacePark) { delete[] PlacePark; PlacePark=NULL; } // v5.0
  if (FilePark) { delete[] FilePark; FilePark=NULL; } // v5.0
  if (PlaceVehlib) { delete[] PlaceVehlib; PlaceVehlib=NULL; } // v5.3
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
int centre_ville::DefinitNbFeuxPietons(int n) // v5.2
 {
  int i;
  if (NbFeuxPieton) { delete[] FeuP; FeuP=NULL; }
  NbFeuxPieton=0;
  if (n&&(FeuP=new feu_pieton[n]))
   {
    for(i=0; i<n; i++) FeuP[i].AffecteNumero(i+1);
    NbFeuxPieton=n;
   }
  return NbFeuxPieton;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbParkings(int n)
 {
  int i;
  if (NbParkings) { delete[] Parking; Parking=NULL; }
  NbParkings=0;
  if ((Parking=new parking[n]))
   {
    for(i=0; i<n; i++) Parking[i].AffecteNumero(i+1);
    NbParkings=n;
   }
  return NbParkings;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbVehicules(int n)
 {
  int i;
  if (NbVehicules) { delete[] Vehicule; Vehicule=NULL; }
  NbVehicules=0;
  if ((Vehicule=new vehicule[n]))
   {
    for(i=0; i<n; i++) Vehicule[i].AffecteNumero(i+1);
    NbVehicules=n;
   }
  return NbVehicules;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbVehlibs(int n) // v5.3
 {
  int i;
  if (NbVehlibs) { delete[] Vehlib; Vehlib=NULL; }
  NbVehlibs=0;
  if ((Vehlib=new vehlib[n]))
   {
    for(i=0; i<n; i++) Vehlib[i].AffecteNumero(i+1);
    NbVehlibs=n;
   }
  return NbVehlibs;
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
	for(i=0; i<n; i++)
	 {
	  Pieton[i].AffecteNumero(i+1);
	  if ((frmSimulation->EpidemieActivee)&& // Si épidémie activée ET
		  EpidemieIterationPatientZero&& // Si patients zéro à définir ALORS
		  (!((i+1)%EpidemieIterationPatientZero))) // On définit les patients zéro
		Pieton[i].Infection = new infection(this);
	 }
    NbPietons=n;
   }
  return NbPietons;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbArretsBus(int n) // v3.0
 {
  int i;
  if (NbArretsBus) { delete[] ArretBus; ArretBus=NULL; }
  NbArretsBus=0;
  if ((ArretBus=new arret_bus[n]))
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
  if ((ArretTram=new arret_tram[n]))
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
    // D'abord on définit la file pour les queues de file
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
int centre_ville::DefinitNbPlacesPark(int n) // v5.0
 {
  int i;
  if (NbPlacesPark) { delete[] PlacePark; PlacePark=NULL; }
  NbPlacesPark=0;
  if (n&&(PlacePark=new place_park[n]))
   {
    for(i=0; i<n; i++) { PlacePark[i].AffecteNumero(i+1); }
    NbPlacesPark=n;
   }
  return NbPlacesPark;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbFilesPark(int n) // v5.0
 {
  int i;
  if (NbFilesPark) { delete[] FilePark; FilePark=NULL; }
  NbFilesPark=0;
  if (n&&(FilePark=new file_park[n]))
   {
    for(i=0; i<n; i++) { FilePark[i].AffecteNumero(i+1); }
    NbFilesPark=n;
   }
  return NbFilesPark;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitFilesPark() // v5.0
 {
  int NumFilePark=0, NbFilesTrv=0;
  if (FilePark) { delete[] FilePark; FilePark=NULL; NbFilesPark=0; }
  if ((!NbPlacesPark)||(!PlacePark)) return 0;
  for(int i=0; i<NbPlacesPark; i++)
   if (PlacePark[i].Definie())
    NbFilesTrv+=PlacePark[i].EstQueueFile();
  if (NbFilesTrv)
   {
    if (DefinitNbFilesPark(NbFilesTrv)!=NbFilesTrv) return 0;
    // D'abord on définit la file pour les queues de file
    for(int i=0; i<NbPlacesPark; i++)
     if (PlacePark[i].Definie()&&
         PlacePark[i].EstQueueFile())
      {
       FilePark[NumFilePark].Definit(i);
       PlacePark[i].DefinitFile(NumFilePark);
       NumFilePark++;
      }
     // Ensuite pour toutes les autres places
    for(int i=0; i<NbPlacesPark; i++)
     if (PlacePark[i].Definie())
      PlacePark[i].DefinitFile(PlacePark[PlacePark[i].PlaceQueueFile()-1].NumFile);
   }
  return NbFilesTrv;
 }
//-----------------------------------------------------------------------------
int centre_ville::DefinitNbPlacesVehlib(int n) // v5.3
 {
  int i;
  if (NbPlacesVehlib) { delete[] PlaceVehlib; PlaceVehlib=NULL; }
  NbPlacesVehlib=0;
  if (n&&(PlaceVehlib=new place_vehlib[n]))
   {
    for(i=0; i<n; i++) { PlaceVehlib[i].AffecteNumero(i+1); }
    NbPlacesVehlib=n;
   }
  return NbPlacesVehlib;
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
int centre_ville::NumeroFeuPietonsLibre() // v5.2
 {
  int i;
  for(i=0; (i<NbFeuxPieton)&&FeuP[i].Defini(); i++);
  return (i+1)*(i<NbFeuxPieton);
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroParkingLibre()
 {
  int i;
  for(i=0; (i<NbParkings)&&Parking[i].Defini(); i++);
  return (i+1)*(i<NbParkings);
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroVehiculeLibre()
 {
  int i;
  for(i=0; (i<NbVehicules)&&Vehicule[i].Defini(); i++);
  return (i+1)*(i<NbVehicules);
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroVehlibLibre() // v5.3
 {
  int i;
  for(i=0; (i<NbVehlibs)&&Vehlib[i].Defini(); i++);
  return (i+1)*(i<NbVehlibs);
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
      if ((Voie->NumArretBus==i)&& // Si case contiguë est arrêt de bus
          (!Voie->v(AGaucheDe[d])->DirPoss)&& // ET qu'il y a un trottoir à sa gauche (en regardant vers l'arrière de l'arrêt)
          (Voie->DirPoss&InvPossDir[d])) // Si d est dans la bonne direction (sens bus)
       ArretBus[i-1].Definit(x, y); // (x,y) devient la tête d'arrêt de bus Voie->NumArretBus
     }
   }
  return i;
 }
//-----------------------------------------------------------------------------
int centre_ville::ArretTramExistant(int x, int y) // v3.5
 { // Pour les trams on ne change pas la tête de l'arrêt car il peut y avoir un double sens sur la voie
  int d, i=0;
  voie *Voie;
  for(d=nord; (!i)&&(d<=ouest); d++)
   {
    Voie=&_V(x,y,d);
    if (Voie->NumArretTram&& // Un arrêt contigu existe ET
        (v[x][y].SensVoieTram==SensVoieTramDir[d][d])&& // Même sens de la voie
        (Voie->SensVoieTram==SensVoieTramDir[d][d])) // Dans le prolongement
     i=Voie->NumArretTram;
   }
  return i;
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroArretBusLibre(int x, int y) // v3.0
 {
  int i;
  if ((i=ArretBusExistant(x, y)))
   return i; // L'arrêt existe déjà (case contiguë qui communique : va ou vient)
  else
   { // C'est un nouvel arrêt de bus
    for(i=0; (i<NbArretsBus)&&ArretBus[i].Defini(); i++);
    return (i+1)*(i<NbArretsBus);
   }
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroArretTramLibre(int x, int y) // v3.5
 {
  int i;
  if ((i=ArretTramExistant(x, y)))
   return i; // L'arrêt existe déjà (case contiguë qui communique : va ou vient)
  else
   { // C'est un nouvel arrêt de tram
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
int centre_ville::NumeroPlaceParkLibre() // v5.0. v5.3 renommée de NumeroPlaceLibre pour ne pas confondre avec NumeroPlaceVehlibLibre()
 {
  int i;
  for(i=0; (i<NbPlacesPark)&&PlacePark[i].Definie(); i++);
  return (i+1)*(i<NbPlacesPark);
 }
//-----------------------------------------------------------------------------
int centre_ville::NumeroPlaceVehlibLibre() // v5.3
 {
  int i;
  for(i=0; (i<NbPlacesVehlib)&&PlaceVehlib[i].Definie(); i++);
  return (i+1)*(i<NbPlacesVehlib);
 }
//-----------------------------------------------------------------------------
int centre_ville::AjouteFeu(int x, int y, direction d)
 {
  int i=NumeroFeuLibre();
  if (!i) // v5.1
   i=IncrementeNombre(&Feu, NbFeux);
  if (i)
   {
    Feu[i-1].Definit(x, y, d);
    v[x][y].NumFeu[d-1]=i;
    // Définition des durées par défaut
    Feu[i-1].DureeVert=DureeVert;
    Feu[i-1].DureeRouge=DureeRouge;
   }
  return i;
 }
//-----------------------------------------------------------------------------
int centre_ville::AjouteFeuPietons(int x, int y, direction d) // v5.2
 { // Inclut l'ajout du feu opposé de même numéro
  int j, i=NumeroFeuPietonsLibre();
  if (!i) // v5.1
   i=IncrementeNombre(&FeuP, NbFeuxPieton);
  if (i)
   {
    FeuP[i-1].Definit(x, y, d);
    v[x][y].NumFeuP[d-1]=i;
    // Définition des durées par défaut
    FeuP[i-1].DureeVert=DureeVert;
    FeuP[i-1].DureeRouge=DureeRouge;
    FeuP[i-1].DefinitFeuOppose(); // Recherche et affecte les coordonnées et NumFeuP de la case opposée
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
void centre_ville::SupprimeFeuPietons(int n) // v5.2
 {
  if ((n>-1)&&(n<NbFeuxPieton))
   {
    for(int i=0; i<NBFEUXPIETONSPARNUMERO; i++)
     v[FeuP[n].x[i]][FeuP[n].y[i]].NumFeuP[FeuP[n].Dir[i]-1]=0;
    FeuP[n].Initialise();
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeFeuxVoie(int x, int y, type_voie TypeVoie) // v3.5 (TypeVoie)
 {
  voie *Voie=&(v[x][y]);
  int i;
  for(i=0; i<NBDIR; i++)
   if (Voie->ExisteVoieDansDirection(TypeVoie, (direction(i+1)))&& // v3.5
       Voie->NumFeu[i])
    SupprimeFeu(Voie->NumFeu[i]-1);
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeParkingVoie(int x, int y) // v3.6
 {
  voie *Voie=&(v[x][y]);
  if (Voie->NumParking) cv->SupprimeParking(Voie->NumParking-1);
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
void centre_ville::SupprimePlaceParkVoie(int x, int y) // v5.0. v5.3 : Renommée de SupprimePlaceVoie pour ne pas confondre avec SupprimePlaceVehlibVoie(x, y)
 {
  voie *Voie=&(v[x][y]);
  if (Voie->NumPlacePark) Voie->RetirePlacePark();
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimePlaceVehlibVoie(int x, int y) // v5.3
 {
  voie *Voie=&(v[x][y]);
  if (Voie->NumPlaceVehlib) Voie->RetirePlaceVehlib();
 }
//-----------------------------------------------------------------------------

int centre_ville::AjouteParking(int x, int y)
 {
  int i=NumeroParkingLibre();
  if (!i) // v5.1
   i=IncrementeNombre(&Parking, NbParkings);
  if (i)
   {
    Parking[i-1].Definit(x, y);
    v[x][y].NumParking=i;
   }
  return i;
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeParking(int n)
 {
  if ((n>-1)&&(n<NbParkings))
   {
    v[Parking[n].x][Parking[n].y].NumParking=0;
    Parking[n].Initialise();
   }
 }
//-----------------------------------------------------------------------------
int centre_ville::AjouteArretBus(int x, int y) // v3.0
 {
  int i=NumeroArretBusLibre(x, y);
  if (!i) // v5.1
   i=IncrementeNombre(&ArretBus, NbArretsBus);
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
  if (!i) // v5.1
   i=IncrementeNombre(&ArretTram, NbArretsTram);
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
  if (!i) // v5.1
   i=IncrementeNombre(&PlaceTaxi, NbPlacesTaxi);
  if (i)
   {
    if (!PlaceTaxi[i-1].Definie())
     PlaceTaxi[i-1].Definit(x, y);
    v[x][y].NumPlaceTaxi=i;
   }
  return i;
 }
//-----------------------------------------------------------------------------
int centre_ville::AjoutePlacePark(int x, int y) // v5.0, v5.1 : ancien nom AjoutePlace
 {
  int i=NumeroPlaceParkLibre(); // v5.3 renommée de NumeroPlaceLibre pour ne pas confondre avec NumeroPlaceVehlibLibre()
  if (!i) // v5.1
   i=IncrementeNombre(&PlacePark, NbPlacesPark);
  if (i)
   {
    if (!PlacePark[i-1].Definie())
     PlacePark[i-1].Definit(x, y);
    v[x][y].NumPlacePark=i;
   }
  return i;
 }
//-----------------------------------------------------------------------------
int centre_ville::AjoutePlaceVehlib(int x, int y) // v5.3
 {
  int i=NumeroPlaceVehlibLibre();
  if (!i) // v5.1
   i=IncrementeNombre(&PlaceVehlib, NbPlacesVehlib);
  if (i)
   {
    if (!PlaceVehlib[i-1].Definie())
     PlaceVehlib[i-1].Definit(x, y);
    v[x][y].NumPlaceVehlib=i;
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
     { // On profite pour regarder si on change de tête d'arrêt de bus
      Existe=true;
      if (v[x][y].EstTeteArretBus()) // Si c'était une tête d'arrêt de bus,
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
     { // On profite pour regarder si on change de tête d'arrêt de tram
      Existe=true;
      if (v[x][y].EstTeteArretTram()) // Si c'était une tête d'arrêt de tram,
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
     ArretBus[i-1].Initialise(); // Si l'arrêt n'a pas d'autre case
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
     ArretTram[i-1].Initialise(); // Si l'arrêt n'a pas d'autre case
    v[x][y].NumArretTram=0;
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeArretBus(int n) // v3.0. Supprime complètement l'arrêt (sur TOUTES les cases)
 {
  v[ArretBus[n].x][ArretBus[n].y].RetireArretBus(); // Retire le n° d'arrêt de bus récursivement sur toutes les cases
  ArretBus[n].Initialise();
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimeArretTram(int n) // v3.5. Supprime complètement l'arrêt (sur TOUTES les cases)
 {
  v[ArretTram[n].x][ArretTram[n].y].RetireArretTram(); // Retire le n° d'arrêt de tram récursivement sur toutes les cases
  ArretTram[n].Initialise();
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimePlaceTaxi(int n) // v3.6
 {
  v[PlaceTaxi[n].x][PlaceTaxi[n].y].RetirePlaceTaxi();
  PlaceTaxi[n].Initialise();
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimePlacePark(int n) // v5.0. v5.3 : renommée de SupprimePlace(n) pour distinguer avec SupprimePlaceVehlib(n)
 {
  v[PlacePark[n].x][PlacePark[n].y].RetirePlacePark();
  PlacePark[n].Initialise();
 }
//-----------------------------------------------------------------------------
void centre_ville::SupprimePlaceVehlib(int n) // v5.3
 {
  v[PlaceVehlib[n].x][PlaceVehlib[n].y].RetirePlaceVehlib();
  PlaceVehlib[n].Initialise();
 }
//-----------------------------------------------------------------------------
sens centre_ville::SensPassagePietonsPossible(int x, int y)
 { // v2.0
  // 1. Sens suivant DirPoss (Directions de l'intérieur vers l'extérieur)
  sens Sens=SensPsgPt[v[x][y].DirPoss];
  // 2. Test des cases voisines (Directions de l'extérieur vers l'intérieur)
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
     { // Sinon deux cas de voies de tram permettent le passage piéton
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
   return indefinie; //  doivent être définis (horizontal|vertical ; >0)
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
   return indefinie; //  doivent être définis (horizontal|vertical ; >0)
  for(d=0; d<2; d++)
   {
    for(Trv=false,i=1;
        (!(Trv=V_(x,y,i,3-SensRecherche+2*d).NumArretBus)&&
        (!V_(x,y,i,3-SensRecherche+2*d).DirPoss)&&
        (i<=NbMaxCasesDetectArretBus));
        i++);
    if (i<=NbMaxCasesDetectArretBus) // Si toujours dans les distances on vérifie la dernière case (l'arrêt EST sur une route)
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
   return indefinie; //  doivent être définis (horizontal|vertical ; >0)
  for(d=0; d<2; d++)
   {
    for(Trv=false,i=1;
        (!(Trv=V_(x,y,i,3-SensRecherche+2*d).NumArretTram)&&
        (!V_(x,y,i,3-SensRecherche+2*d).DirPoss)&&
        (i<=NbMaxCasesDetectArretTram));
        i++);
    if (i<=NbMaxCasesDetectArretTram) // Si toujours dans les distances on vérifie la dernière case (l'arrêt EST sur une route)
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
   return indefinie; //  doivent être définis (horizontal|vertical ; >0)
  for(d=0; d<2; d++)
   {
    for(Trv=false,i=1;
        (!(Trv=V_(x,y,i,3-SensRecherche+2*d).NumPlaceTaxi)&&
        (!V_(x,y,i,3-SensRecherche+2*d).DirPoss)&&
        (i<=NbMaxCasesDetectFileTaxi));
        i++);
    if (i<=NbMaxCasesDetectFileTaxi) // Si toujours dans les distances on vérifie la dernière case (le place de taxi EST sur une route)
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
direction centre_ville::CherchePlaceVehlib(int x, int y, sens SensRecherche) // v5.3
 {
  bool Trv;
  int i, d, Dist[2]={0,0};
  direction Dir[2]={(direction)(3-SensRecherche),(direction)(5-SensRecherche)};
  if ((!NbMaxCasesDetectFileVehlib)|| // NbMaxCasesDetectFileVehlib et
      (!SensRecherche)) // SensRecherche
   return indefinie; //  doivent être définis (horizontal|vertical ; >0)
  for(d=0; d<2; d++)
   {
    for(Trv=false,i=1;
        (!(Trv=V_(x,y,i,3-SensRecherche+2*d).NumPlaceVehlib)&&
        (!V_(x,y,i,3-SensRecherche+2*d).DirPoss)&&
        (i<=NbMaxCasesDetectFileVehlib));
        i++);
    if (i<=NbMaxCasesDetectFileVehlib) // Si toujours dans les distances on vérifie la dernière case (le place de vehlib EST sur une route)
     Trv|=V_(x,y,i,3-SensRecherche+2*d).NumPlaceVehlib;
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
  for(d=nord; d<=ouest; d++) // On prend la dernière possibilité en cas de litige
   if ((!(v[x][y].DirPoss&PossDir[d]))&& // Si pas de déplacement vers d ET
       (!_V(x,y,d).DirPoss)&& // Mur vers d ET
       (v[x][y].DirPoss&PossDir[AGaucheDe[d]])) // Direction possible à gauche (sens de la circulation de la voie)
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
  for(d=nord; d<=ouest; d++) // On prend la dernière possibilité en cas de litige
   if ((!(v[x][y].DirPoss&PossDir[d]))&& // Si pas de déplacement vers d ET
       (!_V(x,y,d).DirPoss)&& // Mur vers d ET
       (v[x][y].DirPoss&PossDir[AGaucheDe[d]])) // Direction possible à gauche (sens de la circulation de la voie)
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
	 {
	  if (!i) i=n; else DiffTrv=(i!=n);
     }
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
	 {
	  if (!i) i=n; else DiffTrv=(i!=n);
     }
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
    if (Voie->NumArretBus&& // Arrêt de bus voisin ET
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
    if (Voie->NumArretTram&& // Arrêt de tram voisin ET
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
  if (v[x][y].DirPoss&&(!ArretsBusVoisinsDifferents(x, y))) // C'est de la route ET il n'y a pas deux arrêts différents voisins
   {
    DirArretVoisin=DirArretBusVoisin(x,y);
    for(d=nord; (!Possible)&&(d<=ouest); d++)
     if ((!(v[x][y].DirPoss&PossDir[d]))&& // Si pas de direction possible vers d et dans cette direction il y a un mur ALORS
         (!_V(x,y,d).DirPoss)) // Soit 1 arrêt d'un côté ou de l'autre soit c'est le même n° (ou nul les 2)
      Possible=((!DirArretVoisin)|| // Si arrêt voisin il y a, ALORS
                (DirArretVoisin==ADroiteDe[d])||  // il doit être dans le même
                (DirArretVoisin==AGaucheDe[d]))&& // sens que le futur arrêt
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
  if (v[x][y].SensVoieTram&&(!ArretsTramVoisinsDifferents(x, y))) // C'est de la route ET il n'y a pas deux arrêts différents voisins
   {
    DirArretVoisin=DirArretTramVoisin(x,y);
    for(d=nord; (!Possible)&&(d<=ouest); d++)
     if ((!(v[x][y].DirPoss&PossDir[d]))&& // Si pas de direction possible vers d et dans cette direction il y a un mur ALORS
         (!_V(x,y,d).DirPoss)) // Soit 1 arrêt d'un côté ou de l'autre soit c'est le même n° (ou nul les 2)
      Possible=((!DirArretVoisin)|| // Si arrêt voisin il y a, ALORS
                (DirArretVoisin==ADroiteDe[d])||  // il doit être dans le même
                (DirArretVoisin==AGaucheDe[d]))&& // sens que le futur arrêt
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
 { // InitialiseInfosTrajetLignesBus doit avoir été lancé avant pour mettre les voie::LigneBus[i] à false
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
        Voie=Voie->v(DirSvt); // 1. On va dans la direction ayant la distance la plus petite vers le prochain arrêt
        Voie->LigneBus[i]=true; // 2. On marque la ligne sur cette case
       }
      while(!Voie->EstTeteArretBus(NumArretSvt));
     }
 }
//-----------------------------------------------------------------------------
void centre_ville::CalculeTrajetLignesTram() // v3.5. Correction : v3.8
 { // InitialiseInfosTrajetLignesTram doit avoir été lancé avant pour mettre les voie::LigneTram[i] à false
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
        for(dp=0; dp<ndp; dp++)  // donc il faut alors regarder si la direction courante est accessible depuis d'où l'on vient !
         if (Voie->EstDirPossSensVoieTram(InvDir[DirPrc], DirCrt=Voie->DirSensVoieTram(indefinie, dp)))
          {
           DistCrt=Voie->DistArretTram[NumArretSvt-1][dp];
           if (DistArretTram>DistCrt)
            {
             DistArretTram=DistCrt;
             DirSvt=DirCrt; // v3.8
            }
          }
        Voie=Voie->v(DirPrc=DirSvt); // 1. On va dans la direction ayant la distance la plus petite vers le prochain arrêt. v3.8 (DirPrc)
        Voie->LigneTram[i]=true; // 2. On marque la ligne sur cette case
       }
      while(!Voie->EstTeteArretTram(NumArretSvt));
     }
 }
//-----------------------------------------------------------------------------
bool centre_ville::VerifieCalculDistances(type_distance &TypeDistance) // v3.5 : inclut également celui des arrêts de bus et tram. v3.6... Et des files de taxi
 {
  bool Ok=true;
  int i, j, k, d, ndp;
  for(i=0; Ok&&(i<NbX); i++)
   for(j=0; Ok&&(j<NbY); j++)
    {
     ndp=NbDir[v[i][j].DirPoss];
     for(d=0; Ok&&(d<ndp); d++)
      {
       for(k=0; Ok&&(k<NbParkings); k++)
        if (v[i][j].PassageBus|| // Si passage de bus OU
            _V(i,j,Dirdp[d][v[i][j].DirPoss]).PassageBus) // pointe sur un passage de bus
         { // On ne teste que la distance AVEC passage de bus
          if (!(Ok=(v[i][j].DistParking[k][d][AVECPSGBUS]<DIST_INDEFINIE)))
           {
            xErr=i; yErr=j;
            TypeDistance=parkings;
           } // v3.5
         }
        else
         {
          if (!(Ok=(v[i][j].DistParking[k][d][AVECPSGBUS]<DIST_INDEFINIE)&&
                   (v[i][j].DistParking[k][d][SANSPSGBUS]<DIST_INDEFINIE)))
           {
            xErr=i; yErr=j;
            TypeDistance=parkings;
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
bool centre_ville::PrepareCalculDistances() // v3.0 : inclut également celui des arrêts de bus/tram. v3.6 ...Et des files de taxi
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
 { // A VOIR : créer infos trafic pour les parkings extérieurs.
  vehicule *veh=Vehicule+(NumVehicule-1);
  if (veh->NumParkingDepart&&veh->NumParkingArrivee)
   v[veh->x][veh->y].Trafic[veh->NumParkingDepart][veh->NumParkingArrivee]++;
  if (veh->NumParkingArrivee)
   v[veh->x][veh->y].Trafic[0][veh->NumParkingArrivee]++;
  if (veh->NumParkingDepart)
   v[veh->x][veh->y].Trafic[veh->NumParkingDepart][0]++;
  v[veh->x][veh->y].Trafic[0][0]++;
 }
//-----------------------------------------------------------------------------
void centre_ville::IncrementeAttente(int NumVehicule)
 { // A VOIR : créer infos trafic pour les parkings extérieurs.
  vehicule *veh=Vehicule+(NumVehicule-1);
  int n=TourCrt-veh->TourDrnDepl-1;
  if (n>0)
   {
    if (veh->NumParkingDepart&&veh->NumParkingArrivee)
     v[veh->x][veh->y].Attente[veh->NumParkingDepart][veh->NumParkingArrivee]+=n;
    if (veh->NumParkingArrivee)
     v[veh->x][veh->y].Attente[0][veh->NumParkingArrivee]+=n;
    if (veh->NumParkingDepart)
     v[veh->x][veh->y].Attente[veh->NumParkingDepart][0]+=n;
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
  int NumParkingDepart=1,
      NumParkingArrivee=2,
      NumFileParkDepart,  // v5.0
      NumFileParkArrivee, // v5.0
      NumPlaceParkDepart, // v5.0
      NumPlaceParkArrivee,// v5.0
      NumPrmVehiculePlacePark=NbVehicules-2*NbPlacesPark, // v5.0
      NbVehiculesAvantCreation=NbVehicules;
  if (DefinitNbVehicules(NbVehiculesAvantCreation)!=NbVehiculesAvantCreation)
   return false;
  for(int i=0; i<NumPrmVehiculePlacePark; i++)
   {
    Vehicule[i].Definit(Parking[NumParkingDepart-1].x, Parking[NumParkingDepart-1].y,
                        indefinie,
                        NumParkingDepart, NumParkingArrivee,
                        0, 0, // v5.0 : On ne traite ici que les départs/arrivées parkings souterrains
                        (i%(NbVehicules/(2*NbParkings)))?
                         normal:
                         ((i%(NbVehicules/NbParkings))?police:urgence));
    do
     {
      NumParkingArrivee=1+NumParkingArrivee%NbParkings;
      if (NumParkingArrivee==1)
       {
        NumParkingDepart=1+NumParkingDepart%NbParkings;
        if (NumParkingDepart==1) { NumParkingDepart=1; NumParkingArrivee=2; }
       }
     } while(NumParkingDepart==NumParkingArrivee);
   }

  // v5.0 : On s'occupe des véhicules partant/arrivant de/sur une place de parking
  for(int i=NumPrmVehiculePlacePark; i<NbVehicules; i++)
   {
    NumParkingDepart =(  (i-NumPrmVehiculePlacePark)/NbPlacesPark)*(1+(i-NumPrmVehiculePlacePark)%NbParkings); // Parking au départ pour les dernières
    NumParkingArrivee=(1-(i-NumPrmVehiculePlacePark)/NbPlacesPark)*(1+(i-NumPrmVehiculePlacePark)%NbParkings); // Parking à l'arrivée pour les premières
    NumPlaceParkDepart= (1-(i-NumPrmVehiculePlacePark)/NbPlacesPark)*(1+(i-NumPrmVehiculePlacePark)%NbPlacesPark); // Place au départ pour les premières
    NumPlaceParkArrivee=(  (i-NumPrmVehiculePlacePark)/NbPlacesPark)*(1+(i-NumPrmVehiculePlacePark)%NbPlacesPark); // Place à l'arrivée pour les dernières
    NumFileParkDepart=NumPlaceParkDepart?(1+PlacePark[NumPlaceParkDepart-1].NumFile):0;
    NumFileParkArrivee=NumPlaceParkArrivee?(1+PlacePark[NumPlaceParkArrivee-1].NumFile):0;
    Vehicule[i].Definit((NumPlaceParkDepart?PlacePark[NumPlaceParkDepart-1].x:Parking[NumParkingDepart-1].x),
                        (NumPlaceParkDepart?PlacePark[NumPlaceParkDepart-1].y:Parking[NumParkingDepart-1].y),
                        indefinie,
                        NumParkingDepart, NumParkingArrivee,
                        NumFileParkDepart, NumFileParkArrivee,
                        (i%(NbVehicules/(2*NbParkings)))?
                         normal:
                         ((i%(NbVehicules/NbParkings))?police:urgence));
   }
  return true;
 }
//-----------------------------------------------------------------------------
void centre_ville::PlaceBus(int x, int y, int NumBus) // v3.0
 {
  bus *b=Bus+NumBus-1;
  if (b->Defini()&&b->DirDrnDepl)
   {
    _V(b->x,b->y,InvDir[b->DirDrnDepl]).NumBus=0; // Effacé de la case d'origine (arrière du bus)
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
  // On ne dessine pas l'arrière du bus car ils peuvent sortir du dépôt (contrairement aux trams).
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
    _V(t->x,t->y,InvDir[t->DirDrnDepl]).NumTram=0; // Effacé de la case d'origine (arrière du tram)
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
                        PlaceTaxi[NumPlace-1].EstTeteFile()) // c'est la tête de file ALORS
                     {
                      t->Situation=stAttente;
                      t->TourRetourDrnCourse=TourCrt;
                     }
					break;
    default : break; // v5.4 : évite l'avertissement
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::PlaceVehiculeVehlib(int x, int y, int NumVehlib) // v5.3
 {
  vehlib *vl=Vehlib+NumVehlib-1;
  int NumPlace;
  vl->DirDrnDepl=vl->Dir;
  if (frmSimulation->SimulationSanglante&&cv->v[x][y].NbPietons)
   cv->v[x][y].TuePietons();
  vl->Place(x,y);
  vl->NbCasesParcourues++;
  vl->TourDrnDepl=TourCrt;
  vl->DirDrnDepl=vl->Dir;
  v[x][y].NumVehlib=NumVehlib;
  v[x][y].RedessineCase(false);
  switch(vl->Situation)
   {
    case svDepart: if ((NumPlace=v[x][y].NumPlaceVehlib)&& // Si c'est une place de vehlib ET
                       (NumPlace==vl->NumPlaceArrivee)&& // c'est la place d'arrivée ET
                       (PlaceVehlib[NumPlace-1].NumVehlibReserve==NumVehlib)) // elle a été réservée pour ce vehlib
                    {
                     vl->FaitDescendrePietons();
                     vl->NumPlaceDepart=NumPlace;
                     vl->NumPlaceArrivee=0;
                     vl->Situation=svAttente;
                     PlaceVehlib[NumPlace-1].NumVehlibReserve=0;
                    }
                   break;
    default: break;               
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
  // On définit 1 bus de 1 à 3 arrêts. 2 bus de 4 à 6 arrêts et 3 bus de 7 à 9 arrêts
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
  // On définit 1 tram de 1 à 3 arrêts. 2 tram de 4 à 6 arrêts et 3 tram de 7 à 9 arrêts
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
  // On place les trams sur les arrêts...
  for(ArretTrv=true,i=0; (ArretTrv)&&(i<NbTrams); i++)
   {
    for(ArretTrv=false,j=0; (!ArretTrv)&&(j<LigneTram[Tram[i].NumLigne-1].NbArrets); j++)
     { // Pour chaque tram, on cherche le premier arrêt libre dans l'ordre de leur ligne respective
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
Il n'est pas possible de placer tous les trams sur un arrêt de leur ligne respective !\n\
Réorganisez votre réseau de trams (les lignes ou les arrêts) pour que le réseau puisse démarrer, puis réessayez !",
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
bool centre_ville::PrepareVehlibs() // v5.3. Les vehlibs ainsi que leurs places
 {
  if (!NbPlacesVehlib)
   {
    NbVehlibs=0;
    return true;
   }
  int NbVehlibsADefinir=1+NUMVEHLIBPLACE(NbPlacesVehlib-1), // On calcule le n° de vehlib pour la dernière place (NbPlacesVehlib-1) auquel on rajoute 1 pour avoir le nombre de vehlibs à créer.
      NumVehlib=0;

  // On alloue les vehlibs...
  if (DefinitNbVehlibs(NbVehlibsADefinir)!=NbVehlibsADefinir) return false;

  // On détermine la place de chaque vehlib pour répartir les places libres
  int *NumPlace=new int[NbVehlibsADefinir];
  for(int i=0; i<NbVehlibsADefinir; i++) NumPlace[i]=0;
  for(int i=0; i<NbPlacesVehlib; i++)
   if (!NumPlace[NUMVEHLIBPLACE(i)])
     NumPlace[NUMVEHLIBPLACE(i)]=i;

  // On définit et place les vehlibs.
  for(int i=0; i<NbVehlibsADefinir; i++)
   {
    Vehlib[NumVehlib].DefinitEtPlace(NumPlace[i]);
    NumVehlib++;
   }
  if (NumPlace) delete [] NumPlace;
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
  if (Pieton[NumPieton].PsgPtTrv&&   // Si le piéton se dirige vers un passage piéton ET
      v[x][y].PassagePietons)        // Si le passage piéton est trouvé ALORS
   Pieton[NumPieton].PsgPtTrv=false; // On réactive les recherches de passages piétons
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
void centre_ville::CalculeDistances() // v3.0 : inclut également celles des arrêts de bus. v3.5... Et des trams ! v3.6... Et des files de taxi !
 {
  int i;
  frmSimulation->StatusBar->Panels->Items[0]->Text="Calcul des distances aux parkings...";
  frmSimulation->StatusBar->Repaint();
  for(i=0; i<NbParkings; i++)
   {
    frmSimulation->StatusBar->Panels->Items[3]->Text=Format("%d/%d", ARRAYOFCONST((i+1, NbParkings)));
    frmSimulation->StatusBar->Repaint();
    if (Parking[i].Defini())
     v[Parking[i].x][Parking[i].y].CalculeDistanceParking(i, 0, 0, indefinie);
   }
  // v3.0
  frmSimulation->StatusBar->Panels->Items[0]->Text="Calcul des distances aux arrêts de bus...";
  frmSimulation->StatusBar->Repaint();
  for(i=0; i<NbArretsBus; i++)
   {
    frmSimulation->StatusBar->Panels->Items[3]->Text=Format("%d/%d", ARRAYOFCONST((i+1, NbArretsBus)));
    frmSimulation->StatusBar->Repaint();
    if (ArretBus[i].Defini())
     v[ArretBus[i].x][ArretBus[i].y].CalculeDistanceArretBus(i, 0, indefinie);
   }
  // v3.5
  frmSimulation->StatusBar->Panels->Items[0]->Text="Calcul des distances aux arrêts de tram...";
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
  // v5.0
  frmSimulation->StatusBar->Panels->Items[0]->Text="Calcul des distances aux files de parkings...";
  frmSimulation->StatusBar->Repaint();
  for(i=0; i<NbFilesPark; i++)
   {
    frmSimulation->StatusBar->Panels->Items[3]->Text=Format("%d/%d", ARRAYOFCONST((i+1, NbFilesPark)));
    frmSimulation->StatusBar->Repaint();
    v[PlacePark[FilePark[i].NumPlaceQueue].x][PlacePark[FilePark[i].NumPlaceQueue].y].CalculeDistanceFilePark(i, 0, 0, indefinie);
   }
  // v5.3
  frmSimulation->StatusBar->Panels->Items[0]->Text="Calcul des distances aux places de vehlib...";
  frmSimulation->StatusBar->Repaint();
  for(i=0; i<NbPlacesVehlib; i++)
   {
    frmSimulation->StatusBar->Panels->Items[3]->Text=Format("%d/%d", ARRAYOFCONST((i+1, NbPlacesVehlib)));
    frmSimulation->StatusBar->Repaint();
    v[PlaceVehlib[i].x][PlaceVehlib[i].y].CalculeDistancePlaceVehlib(i, 0, indefinie);
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
	if (p->Mort) // v5.4.1
	 {
	  p->SupprimeInfection();
	  frmSimulation->RedessineCase(p->x, p->y, true);
	 }
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::PlaceVehiculesSurPlacesPark() // v5.0
 {
  for(int i=0; i<NbVehicules; i++)
   {
    vehicule *Veh=Vehicule+i;
    if (Veh->NumFileParkDepart)
     {
      v[Veh->x][Veh->y].NumVehicule=i+1;
      PlaceVehicule(Veh->x, Veh->y, i+1); // v2.2.7. Inclut les stats d'Attente/Trafic
      frmSimulation->RedessineCase(Veh->x, Veh->y, false);
      Vehicule[i].TourDepart=cv->TourCrt;
      NbVehiculesSortis++;
     }
   }
 }
//-----------------------------------------------------------------------------
void centre_ville::PlaceVehlibsSurPlaces() // v5.3
 {
  for(int i=0; i<NbVehlibs; i++)
   {
    vehlib *VL=Vehlib+i;
    if (VL->NumPlaceDepart)
     {
      v[VL->x][VL->y].NumVehlib=i+1;
      PlaceVehiculeVehlib(VL->x, VL->y, i+1); // Inclut les stats d'Attente/Trafic
      frmSimulation->RedessineCase(VL->x, VL->y, false);
     }
   }
 }
//-----------------------------------------------------------------------------
bool centre_ville::ExisteFeuPietons(int x, int y) //v5.2
 { // Utilisé pour empêcher de supprimer un passage piéton si des feux de piétons existent (à supprimer avant le passage piéton)
  bool Existe=false;
  int k;
  for(int d=nord; (!Existe)&&(d<=ouest); d++)
   {
    for(k=1; _V_(x,y,k,d).PassagePietons; k++);
    Existe=(_V_(x,y,k,d).NumFeuP[InvDir[d]-1]>0);
   }
  return Existe; 
 }
//-----------------------------------------------------------------------------
void centre_ville::PrepareFeuxPietons() // v5.2
 {
  // On réinitialise d'abord
  for(int i=0; i<NbFeux; i++)
   if (Feu[i].NbFeuxPtn)
    {
     delete[] Feu[i].NumFeuxPtn;
     Feu[i].NbFeuxPtn=0;
    }
  // On charge les feux de piétons
  for(int i=0; i<NbFeuxPieton; i++)
   for(int j=0; j<FeuP[i].NbFeux; j++)
    Feu[FeuP[i].NumFeux[j]-1].AjouteFeuPtn(i+1);
 }
//-----------------------------------------------------------------------------
bool centre_ville::FeuPietonsPossible(int x, int y, direction d) //v5.2
 { // Utilisé pour savoir si l'on peut poser un feu piéton opposé (à l'extrémité du passage piétons)
  bool Possible=true; // Optimiste !
  int k;
  for(k=1; _V_(x,y,k,d).PassagePietons; k++);
  Possible=(k>1)&&_V_(x,y,k,d).FeuPietonsPossible(); // Au moins un passage piétons et il mène sur un trottoir libre pour les piétons (sans décors ni voies de circulation)
  return Possible;
 }
//-----------------------------------------------------------------------------
bool centre_ville::PassagePietonFranchissable(int x, int y, direction d) // v5.2
 { // Permet de savoir si un feu piéton n'est pas au rouge dans le cas où en (x,y) il y a un passage piéton
  if (_V(x,y,InvDir[d]).PassagePietons)  // Si le piéton n'était pas au bord du passage piétons alors 
   return true; // il a déjà commencé à traverser.
  bool Possible=true; // Optimiste
  int k, NumFeuP;
  for(k=1; _V_(x,y,k,d).PassagePietons; k++);
  if ((NumFeuP=_V_(x,y,k,d).NumFeuP[InvDir[d]-1]))
   Possible=(FeuP[NumFeuP-1].Etat!=rouge);
  return Possible;
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
  // 0. On déplace les piétons
  for(i=0; i<NbX; i++)
   for(j=0; j<NbY; j++)
    if (v[i][j].NbPietons)
     v[i][j].DeplacePietons();
  NbPietonsGueris=NbPietonsInfectes=NbPietonsMorts=0L;
  // 0bis. v5.4.1 : On calcule les stats épidémiques de piétons si mode épidémie
  if (frmSimulation->ActionEpidemie->Checked)
	for(i=0; i<NbPietons; i++)
	 {
	  if (Pieton[i].Mort)
		NbPietonsMorts++;
	  else
	   {
		if (Pieton[i].EstContagieux())
		  NbPietonsInfectes++;
		else
		  if (Pieton[i].NbInfections()>0)
		  NbPietonsGueris++;
	   }
	 }
  // 1. On calcule les priorités de passage sur chaque case de la voie
  for(i=0; i<NbX; i++)
   for(j=0; j<NbY; j++)
	v[i][j].CalculeProchainVehiculeOuBusOuTramOuTaxiOuVehlib();

  // 2. On déplace les véhicules
  for(i=0; i<NbX; i++)
   for(j=0; j<NbY; j++)
	v[i][j].DeplaceVehiculeOuBusOuTramOuTaxi();

  // 3. On fait tourner les feux...
  for(i=0; i<NbFeuxPieton; i++) FeuP[i].Evolue(); // v5.2
  for(i=0; i<NbFeux; i++) Feu[i].Evolue();
  for(i=0; i<NbFeuxPieton; i++) FeuP[i].ChangeEtat(); // v5.2
  for(i=0; i<NbFeux; i++) Feu[i].ChangeEtat();

  // 4. On sort les voitures des parkings sur la voie
  for(i=0; i<NbParkings; i++)
   Parking[i].PlaceProchainVehicule();
  // 4bis. Ainsi que les bus du dépôt. v3.0
  DepotBus.PlaceProchainBus();
  // 4ter. v5.0 : On place les véhicules sur les places de parkings
  if (!TourCrt)
   PlaceVehiculesSurPlacesPark();
  // 5a. On calcule la prochaine direction de chaque véhicule
  for(i=0; i<NbVehicules; i++)
   if (Vehicule[i].Defini())
    Vehicule[i].CalculeProchaineDirection(); // Vehicule[i].Dir défini
  // 5b. Ainsi que celle des bus. v3.0
  for(i=0; i<NbBus; i++)
   if (Bus[i].Defini())
    Bus[i].CalculeProchaineDirection(); // Bus[i].Dir défini
  // 5c. Ainsi que celle des trams. v3.5
  for(i=0; i<NbTrams; i++)
   if (Tram[i].Defini())
    Tram[i].CalculeProchaineDirection(); // Tram[i].Dir défini
  // 5d. Ainsi que celle des taxis. v3.6
  for(i=0; i<NbTaxis; i++)
   Taxi[i].CalculeProchaineDirection(); // Taxi[i].Dir défini
  // 5e. Ainsi que celle des vehlibs. v5.3
  for(i=0; i<NbVehlibs; i++)
   Vehlib[i].CalculeProchaineDirection(); // Vehlib[i].Dir défini

  // 6a. On rafraîchit les véhicules (la direction a pu changé)
  for(i=0; i<2*NbParkings; i++)
   if (Vehicule[i*(NbVehicules/NbParkings/2)].Defini())
    frmSimulation->RedessineCase( Vehicule[i*(NbVehicules/NbParkings/2)].x,
                                  Vehicule[i*(NbVehicules/NbParkings/2)].y,
                                  false);
  // 6b. Et les bus (la direction a pu changé). v3.0
  for(i=0; i<NbBus; i++)
   if (Bus[i].Defini())
    frmSimulation->RedessineCase( Bus[i].x, Bus[i].y, false);
  // 6c. Et les trams (la direction a pu changé). v3.5
  for(i=0; i<NbTrams; i++)
   if (Tram[i].Defini())
    frmSimulation->RedessineCase( Tram[i].x, Tram[i].y, false);
  // 6d. Et les taxis (la direction a pu changé). v3.6
  for(i=0; i<NbTaxis; i++)
   frmSimulation->RedessineCase( Taxi[i].x, Taxi[i].y, false);
  // 6e. Et les vehlibs (la direction a pu changé). v5.3
  for(i=0; i<NbVehlibs; i++)
   frmSimulation->RedessineCase( Vehlib[i].x, Vehlib[i].y, false);

  // 7. On affiche les stats...
  Stats[TourCrt%NbToursStats].Definit();
  if (frmStatistiques->Visible) frmStatistiques->PaintBoxStats->Repaint();
  if (frmStatsVehicules->Visible) frmStatsVehicules->RafraichitInfos();
  if (frmInfosVehicule->Visible) frmInfosVehicule->RafraichitInfos();
  if (frmInfosBus->Visible) frmInfosBus->RafraichitInfos(); // v3.0
  if (frmInfosTram->Visible) frmInfosTram->RafraichitInfos(); // v3.5
  if (frmInfosTaxi->Visible) frmInfosTaxi->RafraichitInfos(); // v3.6
  if (frmInfosVehlib->Visible) frmInfosVehlib->RafraichitInfos(); // v5.3
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
    if (frmRecherche->RadioButtonVehlib->Checked) // v5.3
     frmRecherche->CSpinEditVehlibChange(frmRecherche->CSpinEditVehlib);
   }

  TourCrt+=(NbVehiculesArrives<NbVehicules);
  TourEnCours=false;
 }
//-----------------------------------------------------------------------------
bool centre_ville::Charge(int hfile)
 {
  int i, j,
      NvNbParkings=0, // v5.1
      NvNbPlacesPark=0, // v5.1
	  NvNbPlacesVehlib=0; // v5.3
  bool Ok;
  NbPietons=-1;
  Ok=FileRead(hfile, &NbFeux, sizeof(NbFeux));
  if (NbFeux>=VERSIONMIN) // v3.0
   { // Version stockée
	VersionFichier=NbFeux;
	Ok=FileRead(hfile, &NbFeux, sizeof(NbFeux)); // On relit le nombre de feux
   }
  else // Version non stockée compatible (2.0 <= version < 3.0)
   VersionFichier=VERSIONANC;
  if (VersionFichier>VERSION) return false; // v3.5 : n'ouvre pas les fichier de simulation générés par une version ultérieure de la version actuelle (format de fichier)
  if (VersionFichier<0x400) // On charge les dimensions de la zone
   {
	NbX=NBXDEF;
	NbY=NBYDEF;
   }
  else
   Ok=FileRead(hfile, &NbX, sizeof(NbX))&&
	  FileRead(hfile, &NbY, sizeof(NbY));
  CreeZone();
  if (Ok) Ok= ((VersionFichier<0x520)|| // v5.2
			   (FileRead(hfile, &NbFeuxPieton, sizeof(NbFeuxPieton))))&&
			  FileRead(hfile, &NbParkings, sizeof(NbParkings))&&
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
			  ((VersionFichier<0x500)|| // v5.0
			   (FileRead(hfile, &NbPlacesPark, sizeof(NbPlacesPark))))&&
			  ((VersionFichier<0x530)|| // v5.3
			   (FileRead(hfile, &NbPlacesVehlib, sizeof(NbPlacesVehlib))&&
				FileRead(hfile, &NbVehlibs, sizeof(NbVehlibs))))&&
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
			   (FileRead(hfile, &NbMaxCasesDetectFileTaxi, sizeof(NbMaxCasesDetectFileTaxi))&&
				FileRead(hfile, &ProbaDirFileTaxi, sizeof(ProbaDirFileTaxi))&&
				FileRead(hfile, &ProbaArretTaxiDmd, sizeof(ProbaArretTaxiDmd))&&
				FileRead(hfile, &NbMaxPersonnesTaxi, sizeof(NbMaxPersonnesTaxi))&&
				FileRead(hfile, &NbMaxToursAttenteTaxi, sizeof(NbMaxToursAttenteTaxi))))&&
			  ((VersionFichier<0x530)|| // v5.3
			   (FileRead(hfile, &NbMaxPersonnesVehlib, sizeof(NbMaxPersonnesVehlib))&&
				FileRead(hfile, &NbMaxCasesDetectFileVehlib, sizeof(NbMaxCasesDetectFileVehlib))&&
				FileRead(hfile, &ProbaDirFileVehlib, sizeof(ProbaDirFileVehlib))&&
				FileRead(hfile, &TauxRemplissageVehlib, sizeof(TauxRemplissageVehlib))));
  if (Ok&&NbFeux&&(Ok=!!(Feu=new feu[NbFeux])))
   for(i=0; Ok&&(i<NbFeux); i++)
    {
     Ok=Feu[i].Charge(hfile);
     Feu[i].AffecteNumero(i+1);
    }
  if (VersionFichier>=0x520) // v5.2
   {
    if (Ok&&NbFeuxPieton&&(Ok=!!(FeuP=new feu_pieton[NbFeuxPieton])))
     for(i=0; Ok&&(i<NbFeuxPieton); i++)
      {
       Ok=FeuP[i].Charge(hfile);
       FeuP[i].AffecteNumero(i+1);
      }
   }
  if (Ok&&NbParkings&&(Ok=!!(Parking=new parking[NbParkings])))
   for(i=0; Ok&&(i<NbParkings); i++)
    {
     Ok=Parking[i].Charge(hfile);
     Parking[i].AffecteNumero(i+1);
     if (Parking[i].Defini()) NvNbParkings++; // v5.1 : on teste s'il manque des parkings souterrains par rapport à NbParkings
    }
  if (Vehicule) { delete[] Vehicule; Vehicule=NULL; }
  if (Vehlib) { delete[] Vehlib; Vehlib=NULL; } // v5.3
  if (Pieton) { delete[] Pieton; Pieton=NULL; }
  if (VersionFichier>=0x300) // v3.0
   { // Dépot, arrêts et lignes de bus
    Ok=Ok&&DepotBus.Charge(hfile); // v5.2 : Manquait Ok&&
    if (Ok&&NbArretsBus&&(Ok=!!(ArretBus=new arret_bus[NbArretsBus])))
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
   { // Arrêts et lignes de tram
    if (Ok&&NbArretsTram&&(Ok=!!(ArretTram=new arret_tram[NbArretsTram])))
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
    if (Ok&&NbPlacesTaxi&&(Ok=!!(PlaceTaxi=new place_taxi[NbPlacesTaxi])))
     for(i=0; Ok&&(i<NbPlacesTaxi); i++)
      {
       Ok=PlaceTaxi[i].Charge(hfile);
       PlaceTaxi[i].AffecteNumero(i+1);
      }
   }

  if (VersionFichier>=0x500) // v5.0
   { // Places de parkings
    if (Ok&&NbPlacesPark&&(Ok=!!(PlacePark=new place_park[NbPlacesPark])))
     for(i=0; Ok&&(i<NbPlacesPark); i++)
      {
       Ok=PlacePark[i].Charge(hfile);
       PlacePark[i].AffecteNumero(i+1);
       if (PlacePark[i].Definie()) NvNbPlacesPark++; // v5.1 : on teste s'il manque des places de parkings par rapport à NbPlacesPark
      }
   }

  if (VersionFichier>=0x530) // v5.3
   {
    // Places de vehlib
    if (Ok&&NbPlacesVehlib&&(Ok=!!(PlaceVehlib=new place_vehlib[NbPlacesVehlib])))
     for(i=0; Ok&&(i<NbPlacesVehlib); i++)
      {
       Ok=PlaceVehlib[i].Charge(hfile);
       PlaceVehlib[i].AffecteNumero(i+1);
       if (PlaceVehlib[i].Definie()) NvNbPlacesVehlib++; // on teste s'il manque des places de vehlib par rapport à NbPlacesVehlib
      }
   }
  for(i=0; Ok&&(i<NbX); i++)
   for(j=0; Ok&&(j<NbY); j++)
    Ok=v[i][j].Charge(hfile);

  // v5.1 : on retire les parkings indéfinis
  if (Ok&&(NvNbParkings<NbParkings))
   {
    parking *NvParking=NULL;
    Ok=!!(NvParking=new parking[NvNbParkings]);
    if (Ok)
     {
      NvNbParkings=0;
      for(i=0; i<NbParkings; i++)
       {
        if (Parking[i].Defini())
         {
          NvParking[NvNbParkings].Copie(Parking+i); // NvNbParkings++
          NvParking[NvNbParkings].AffecteNumero(NvNbParkings+1); // On renumérote
          cv->v[NvParking[NvNbParkings].x][NvParking[NvNbParkings].y].NumParking=NvNbParkings+1;
          NvNbParkings++;
         }
       }
      NbParkings=NvNbParkings;
      delete[] Parking;
      Parking=NvParking;
     }
   }

  // v5.1 : on retire les places de parkings indéfinies
  if (Ok&&
      (VersionFichier>=0x500)&&
      (NvNbPlacesPark<NbPlacesPark))
   {
    place_park *NvPlacePark=NULL;
    Ok=!!(NvPlacePark=new place_park[NvNbPlacesPark]);
    if (Ok)
     {
      NvNbPlacesPark=0;
      for(i=0; i<NbPlacesPark; i++)
       {
        if (PlacePark[i].Definie())
         {
          NvPlacePark[NvNbPlacesPark].Copie(PlacePark+i);
          NvPlacePark[NvNbPlacesPark].AffecteNumero(NvNbPlacesPark+1); // On renumérote
          cv->v[NvPlacePark[NvNbPlacesPark].x][NvPlacePark[NvNbPlacesPark].y].NumPlacePark=NvNbPlacesPark+1;
          NvNbPlacesPark++;
         }
       }
      NbPlacesPark=NvNbPlacesPark;
      delete[] PlacePark;
      PlacePark=NvPlacePark;
     }
   }

  // v5.3 : on retire les places de vehlib indéfinies
  if (Ok&&
      (VersionFichier>=0x530)&&
      (NvNbPlacesVehlib<NbPlacesVehlib))
   {
    place_vehlib *NvPlaceVehlib=NULL;
    Ok=!!(NvPlaceVehlib=new place_vehlib[NvNbPlacesVehlib]);
    if (Ok)
     {
      NvNbPlacesVehlib=0;
      for(i=0; i<NbPlacesVehlib; i++)
       {
        if (PlaceVehlib[i].Definie())
         {
          NvPlaceVehlib[NvNbPlacesVehlib].Copie(PlaceVehlib+i);
          NvPlaceVehlib[NvNbPlacesVehlib].AffecteNumero(NvNbPlacesVehlib+1); // On renumérote
          cv->v[NvPlaceVehlib[NvNbPlacesVehlib].x][NvPlaceVehlib[NvNbPlacesVehlib].y].NumPlaceVehlib=NvNbPlacesVehlib+1;
          NvNbPlacesVehlib++;
         }
       }
      NbPlacesVehlib=NvNbPlacesVehlib;
      delete[] PlaceVehlib;
      PlaceVehlib=NvPlaceVehlib;
     }
   }

  if (NbPietons==-1) NbPietons=0; // Si version sans piétons alors pas de piéton !
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
     FileWrite(hfile, &NbFeuxPieton, sizeof(NbFeuxPieton))&& // v5.2
     FileWrite(hfile, &NbParkings, sizeof(NbParkings))&&
     FileWrite(hfile, &NbVehicules, sizeof(NbVehicules))&&
     FileWrite(hfile, &NbPietons, sizeof(NbPietons))&& // v2.0
     FileWrite(hfile, &NbArretsBus, sizeof(NbArretsBus))&& // v3.0
     FileWrite(hfile, &NbLignesBus, sizeof(NbLignesBus))&& // v3.0
     FileWrite(hfile, &NbArretsTram, sizeof(NbArretsTram))&& // v3.5
     FileWrite(hfile, &NbLignesTram, sizeof(NbLignesTram))&& // v3.5
     FileWrite(hfile, &NbPlacesTaxi, sizeof(NbPlacesTaxi))&& // v3.6
     FileWrite(hfile, &NbTaxis, sizeof(NbTaxis))&& // v3.6
     FileWrite(hfile, &NbPlacesPark, sizeof(NbPlacesPark))&& // v5.0
     FileWrite(hfile, &NbPlacesVehlib, sizeof(NbPlacesVehlib))&& // v5.3
     FileWrite(hfile, &NbVehlibs, sizeof(NbVehlibs))&& // v5.3
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
     FileWrite(hfile, &NbMaxToursAttenteTaxi, sizeof(NbMaxToursAttenteTaxi))&& // v3.5
     FileWrite(hfile, &NbMaxPersonnesVehlib, sizeof(NbMaxPersonnesVehlib))&& // v5.3
     FileWrite(hfile, &NbMaxCasesDetectFileVehlib, sizeof(NbMaxCasesDetectFileVehlib))&& // v5.3
     FileWrite(hfile, &ProbaDirFileVehlib, sizeof(ProbaDirFileVehlib))&& // v5.3
     FileWrite(hfile, &TauxRemplissageVehlib, sizeof(TauxRemplissageVehlib)); // v5.3

  for(i=0; Ok&&(i<NbFeux); i++) Ok=Feu[i].Sauve(hfile);
  for(i=0; Ok&&(i<NbFeuxPieton); i++) Ok=FeuP[i].Sauve(hfile); // v5.2
  for(i=0; Ok&&(i<NbParkings); i++) Ok=Parking[i].Sauve(hfile);
  Ok=DepotBus.Sauve(hfile);
  for(i=0; Ok&&(i<NbArretsBus); i++) Ok=ArretBus[i].Sauve(hfile); // v3.0
  for(i=0; Ok&&(i<NBMAXLIGNESBUSTRAM); i++) Ok=LigneBus[i].Sauve(hfile); // v3.0. Attention : tableau statique
  for(i=0; Ok&&(i<NbArretsTram); i++) Ok=ArretTram[i].Sauve(hfile); // v3.5
  for(i=0; Ok&&(i<NBMAXLIGNESBUSTRAM); i++) Ok=LigneTram[i].Sauve(hfile); // v3.5. Attention : tableau statique
  for(i=0; Ok&&(i<NbPlacesTaxi); i++) Ok=PlaceTaxi[i].Sauve(hfile); // v3.6
  for(i=0; Ok&&(i<NbPlacesPark); i++) Ok=PlacePark[i].Sauve(hfile); // v5.0
  for(i=0; Ok&&(i<NbPlacesVehlib); i++) Ok=PlaceVehlib[i].Sauve(hfile); // v5.3
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
 { // v5.0 : Calcul préalable pour le NbVehicules
  int NbMinVehicules= NbParkings*(NbParkings-1)
                     +2*NbPlacesPark, // v5.0 : 1 véh départ + 1 véh arrivée par place de parking
      NbMaxVehicules= (NBMAXVEHICULES/(NbParkings*(NbParkings-1)))*NbParkings*(NbParkings-1)
                     +2*NbPlacesPark; // v5.0 : 1 véh départ + 1 véh arrivée par place de parking
  int i, j;
  asMsgErr="";
  if (NbFeux<0)
   asMsgErr+=Format("Le nombre de feux est incorrect (%d)\n", ARRAYOFCONST((NbFeux)));
  if (NbParkings<2)
   asMsgErr+=Format("Le nombre de parkings est incorrect (%d)\n", ARRAYOFCONST((NbParkings)));
  if (NbVehicules<=0)
   asMsgErr+=Format("Le nombre de véhicules est incorrect (%d)\n", ARRAYOFCONST((NbVehicules)));
  else
   if ((!NbParkings)||
       (NbParkings==1)||
       (NbVehicules%NbMinVehicules)|| // Incrément incorrect
       (NbVehicules<NbMinVehicules)||
       (NbVehicules>NbMaxVehicules))
    asMsgErr+=Format("Le nombre de véhicules ne permet pas une simulation équilibrée (%d)\n", ARRAYOFCONST((NbVehicules)));
  if (NbPietons<0)
   asMsgErr+=Format("Le nombre de piétons est incorrect (%d)\n", ARRAYOFCONST((NbPietons)));
  if (DureeVert<0)
   asMsgErr+=Format("La durée du feu vert par défaut est incorrecte (%d)\n", ARRAYOFCONST((DureeOrange)));
  if (DureeOrange<0)
   asMsgErr+=Format("La durée du feu orange est incorrecte (%d)\n", ARRAYOFCONST((DureeOrange)));
  if (DureeRouge<0)
   asMsgErr+=Format("La durée du feu rouge par défaut est incorrecte (%d)\n", ARRAYOFCONST((DureeOrange)));
  if (AttenteMaxVeh<0)
   asMsgErr+=AnsiString("La durée d'attente maximale d'un véhicule est incorrecte\n");
  if (NbToursParSeconde<0)
   asMsgErr+=AnsiString("Le nombre de tours par seconde est incorrect\n");
  if (NbToursStats<0)
   asMsgErr+=Format("Le nombre de tours soumis aux statistiques est incorrect (%d)\n", ARRAYOFCONST((NbToursStats)));
  if ((TypeStats<par_nombre)||(TypeStats>par_pourcentage))
   asMsgErr+=Format("Le type de statistique est incorrect (%d)\n", ARRAYOFCONST(((int)TypeStats)));
  if ((NbVitesses<1)||(NbVitesses>3))
   asMsgErr+=Format("Le nombre de vitesses est incorrect (%d)\n", ARRAYOFCONST((NbVitesses)));
  if ((NbMaxCasesDetectPsgPt<0)||(NbMaxCasesDetectPsgPt>5))
   asMsgErr+=Format("Le nombre de case maximum pour la détection de passage piéton est incorrect (%d)\n", ARRAYOFCONST((NbMaxCasesDetectPsgPt)));
  if ((ProbaDirPsgPt<0)||(ProbaDirPsgPt>100))
   asMsgErr+=Format("La probabilité qu'un piéton se dirige vers un passage piéton détecté est incorrecte (%d)\n", ARRAYOFCONST((ProbaDirPsgPt)));
  if (NbArretsBus<0)
   asMsgErr+=Format("Le nombre d'arrêts de bus est incorrect (%d)\n", ARRAYOFCONST((NbArretsBus)));
  if (NbLignesBus<0)
   asMsgErr+=Format("Le nombre de lignes de bus est incorrect (%d)\n", ARRAYOFCONST((NbLignesBus)));
  if (NbArretsTram<0)
   asMsgErr+=Format("Le nombre d'arrêts de tram est incorrect (%d)\n", ARRAYOFCONST((NbArretsTram)));
  if (NbLignesTram<0)
   asMsgErr+=Format("Le nombre de lignes de tram est incorrect (%d)\n", ARRAYOFCONST((NbLignesTram)));
  if (NbPlacesTaxi<0)
   asMsgErr+=Format("Le nombre de places de taxi est incorrect (%d)\n", ARRAYOFCONST((NbPlacesTaxi)));
  if (NbTaxis<0)
   asMsgErr+=Format("Le nombre de taxis est incorrect (%d)\n", ARRAYOFCONST((NbTaxis)));
  if (NbPlacesVehlib<0) // v5.3
   asMsgErr+=Format("Le nombre de places de vehlib est incorrect (%d)\n", ARRAYOFCONST((NbPlacesVehlib)));
  if (NbVehlibs<0) // v5.3
   asMsgErr+=Format("Le nombre de vehlibs est incorrect (%d)\n", ARRAYOFCONST((NbVehlibs)));
  for(i=0; i<NbX; i++)
   for(j=0; j<NbY; j++)
    v[i][j].Verifie(asMsgErr);
  for(i=0; i<NbFeux; i++)
   Feu[i].Verifie(asMsgErr, Format("Feu n°%d", ARRAYOFCONST((i+1))));
  for(i=0; i<NbParkings; i++)
   Parking[i].Verifie(asMsgErr);
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
  if (Taxi) // v5.0 (oubli)
   for(i=0; i<NbTaxis; i++)
    Taxi[i].Verifie(asMsgErr);
  if (PlaceTaxi)
   for(i=0; i<NbPlacesTaxi; i++)
    PlaceTaxi[i].Verifie(asMsgErr);
  for(i=0; i<NbPlacesPark; i++) //v5.0
   PlacePark[i].Verifie(asMsgErr);
  if (Vehlib) // v5.3
   for(i=0; i<NbVehlibs; i++)
    Vehlib[i].Verifie(asMsgErr);
  if (PlaceVehlib) // v5.3
   for(i=0; i<NbPlacesVehlib; i++)
    PlaceVehlib[i].Verifie(asMsgErr);
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
inline bool centre_ville::TourDeDeplacementVehlib(int NumeroVehlib) // v5.3
 {
  if ((TourCrt-Vehlib[NumeroVehlib].TourDepart)%NbVitesses <= NbVitesses-1)
   return true;
  else
   {
    Vehlib[NumeroVehlib].NbToursRepos++; 
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
  for(int i=0; i<NbParkings; i++)
   if (Parking[i].Defini()&&(!DansSelectionEnCours(Parking+i)))
    asMsg=asMsg+"le parking n°"+IntToStr(i+1)+" "+asCoordonnees(Parking+i)+", ";
  if (DepotBus.Defini()&&(!DansSelectionEnCours(&DepotBus)))
   asMsg=asMsg+"le dépôt de bus n°"+asCoordonnees(&DepotBus)+", ";
  for(int i=0; i<NbFeux; i++)
   if (Feu[i].Defini()&&(!DansSelectionEnCours(Feu+i)))
    asMsg=asMsg+"le feu n°"+IntToStr(i+1)+" "+asCoordonnees(Feu+i)+", ";
  for(int i=0; i<NbArretsBus; i++)
   if (ArretBus[i].Defini()&&(!DansSelectionEnCours(ArretBus+i)))
    asMsg=asMsg+"l'arrêt de bus n°"+IntToStr(i+1)+" "+asCoordonnees(ArretBus+i)+", ";
  for(int i=0; i<NbPlacesTaxi; i++)
   if (PlaceTaxi[i].Definie()&&(!DansSelectionEnCours(PlaceTaxi+i)))
    asMsg=asMsg+"la place de taxi n°"+IntToStr(i+1)+" "+asCoordonnees(PlaceTaxi+i)+", ";
  for(int i=0; i<NbPlacesPark; i++) // v5.0
   if (PlacePark[i].Definie()&&(!DansSelectionEnCours(PlacePark+i)))
    asMsg=asMsg+"la place de parking n°"+IntToStr(i+1)+" "+asCoordonnees(PlacePark+i)+", ";
  for(int i=0; i<NbPlacesVehlib; i++) // v5.3
   if (PlaceVehlib[i].Definie()&&(!DansSelectionEnCours(PlaceVehlib+i)))
    asMsg=asMsg+"la place de vehlib n°"+IntToStr(i+1)+" "+asCoordonnees(PlaceVehlib+i)+", ";
  if (!asMsg.IsEmpty())
   {
    AfficheMessage("Les éléments suivants DOIVENT ÊTRE dans la sélection :\n"+asMsg+"\n\nVeuillez soit les supprimer, soit les inclure dans la sélection avant de réessayer.", "Commande de copie impossible", tmAvertissement, 0, 0);
    return false;
   }
  else
   return true;
 }
//-----------------------------------------------------------------------------
void centre_ville::Genere(int x, int y, int d) // v4.2
 { // ATTENTION : d peut changer à l'intérieur de Genere(...)
  int k=0;
  bool Ok=true,
       DejaFait[NBDIR+1]={false,false,false,false,false},
       AutreDirection=false;
  do
   { /* LE CODE EN COMMENTAIRE sert pour le débogage
    frmSimulation->DrawGridSimul->Col=x;
    frmSimulation->DrawGridSimul->Row=y;
    frmSimulation->RedessineCase(x,y,true); */
    int l=1+(LgrMinSgmtRoute*((d-1)%2?NbX:NbY))/10+ // Longueur du nouveau segment de route
          rand()%(1+((LgrMaxSgmtRoute-LgrMinSgmtRoute)*((d-1)%2?NbX:NbY))/10);
    //AfficheMessage("Départ du segment","("+IntToStr(x)+","+IntToStr(y)+"),"+asDir[d], tmInformation,0,0);
    bool //MemeDir=false, // pour débogage
         //TraverseeRoute=true, // pour débogage
         DirOpposee=false,
         EntreeIntersection=true;
    for(k=0,Ok=true,AutreDirection=false; Ok&&(k<=l); k++)
     {
      voie *vc=&(_V_(x,y,k,d)); // Case suivante
      Ok=(!(/*MemeDir=*/vc->DirPoss&PossDir[d]))&& // S'il s'agit d'une direction possible = d
         (!(DirOpposee=vc->DirPoss&InvPossDir[d]))&& // OU une direction opposée à d
         ((!vc->DirPoss)||
          (/*TraverseeRoute=*/(ProbaTraverseeRoute>rand()%10))|| // OU une traversée de route refusée, ALORS on NE TRACE pas le segment de route sur la case.
          (EntreeIntersection=(ProbaEntreeIntersection>rand()%10))); // OU une entrée d'intersection ?
      if (Ok)
	   { // v5.4 : Conversion BCB6>BCBX pas de a+=b sur énumérés
        vc->DirPoss=(dirposs)(((int)vc->DirPoss)+((int)(PossDir[d]))); // On trace la route jusqu'à la case courante
        //frmSimulation->RedessineCase((x+k*dx[d])%NbX, (y+k*dy[d])%NbY, true);
        //AfficheMessage("Tracé de segment","("+IntToStr((x+k*dx[d])%NbX)+","+IntToStr((y+k*dy[d])%NbY)+"),"+IntToStr(k)+"/"+IntToStr(l)+","+asDir[d], tmInformation,0,0);
       }
     }
    if (!Ok) // Le segment N'a PAS été tracé jusqu'au bout
     {
      k--; // On revient sur la case précédente TRACÉE
      if (DirOpposee|| // SI direction OPPOSEE,
          (!EntreeIntersection)) // OU SI arrivée sur une route refusée
       { // ALORS on part A GAUCHE OU A DROITE (on évite les deux problèmes)
        //AfficheMessage("DirOpposée||(!EntreeIntersection)","("+IntToStr((x+k*dx[d])%NbX)+","+IntToStr((y+k*dy[d])%NbY)+"),Pas Ok,"+IntToStr(k)+"/"+IntToStr(l)+","+asDir[d], tmInformation,0,0);
        int dd=1+(d+2*(rand()%2))%NBDIR;
        if (!k)
         DejaFait[dd]=true;
        else
         for(int i=0; i<NBDIR+1; i++) DejaFait[i]=false;
        if (k||(!DejaFait[dd])) // On teste si on n'a pas déjà fait cette direction sur la même case...
         {
          x=(x+k*dx[d])%NbX;
          y=(y+k*dy[d])%NbY;
          d=dd;
          AutreDirection=true;
         }
       }
/*    else
       AfficheMessage("MêmeDir||(!TraverséeRoute)","("+IntToStr((x+k*dx[d])%NbX)+","+IntToStr((y+k*dy[d])%NbY)+"),Pas Ok,"+IntToStr(k)+"/"+IntToStr(l)+","+asDir[d], tmInformation,0,0);
*/   }
    else // Le segment a été tracé jusqu'au bout : MAIS ATTENTION V(x,y,k,d) N'EST PAS TRACÉ !!!
     {
      if ((_V_(x,y,k,d).DirPoss&(NESO-InvPossDir[d]))!=NESO-InvPossDir[d]) // peut-on continuer à créer des segments ?
       {
        if (ProbaSortieIntersection>rand()%10) // Crée-t-on une sortie d'intersection ?
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
//-----------------------------------------------------------------------------

