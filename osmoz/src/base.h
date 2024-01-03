//---------------------------------------------------------------------------
#ifndef baseH
#define baseH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
#define NUM_LETTRE(x) ((int)((x)-'A'+1))
#define ABS(x) (((x)<0)?(-(x)):(x))
//---------------------------------------------------------------------------
// v4.5 : prise en charge HDPI
#define HDPI(x) ((int)(0.5+((x)*Screen->PixelsPerInch)/96))
#define _HDPI(x) ((int)(0.5+((x)*96)/Screen->PixelsPerInch))
//---------------------------------------------------------------------------
#define NBLMIN           2  // v4.0
#define NBLMAX          15  // v4.0. Avant : 9
#define NBPRMLTR       114
#define NTL       4080472L  // v.4.7 (ODS9) // v4.4 = ODS8:  4031818L // v.4.3 = ODS7: 3867567L // v4.2 : ODS6 (v4.1.1, ODS5 : 3791166L. ODS4 : 3688194L)
#define NBCASES        169  // v4.0. Avant : 91
#define NBXY            15  // v4.0. Avant : 11
#define NBDIR            6
//---------------------------------------------------------------------------
#define INDEFINI -1
//---------------------------------------------------------------------------
// Paramètre InitialisePartie()
#define AVEC_JOUEURS true
#define SANS_JOUEURS false
// Contextes pour GereES()
#define CHOIX_LETTRE 0
#define PLCMT_LETTRE 1
//---------------------------------------------------------------------------
#define NB_CASES_ASSEZ_GRAND 32767
//---------------------------------------------------------------------------
typedef struct
 {
  bool DejaPasse; // Utilisé en interne par par NbCasesDeplacements(x,y)
  int NbCases;    // Utilisé en interne par NbCasesDeplacements(x,y)
  int Lettre, // 0=aucune ; 'A', 'B' etc...
      Valeur, // 0=aucune ; 1...=valeur de lettre
      Joueur; // 0=personne ; 1..6=joueur
 } cases;
//---------------------------------------------------------------------------
class plateau
 {
  bool Recherche;
  unsigned long PtsGagnes, PtsPris, LtrPrises, TotCoefs; // pour l'automate
  public:
  bool JeuEnCours, CalculNbCasesEnCours;
  time_t TopTour;
  unsigned NbPasseTour, NbCasesLibres, ValNaiss[27];
  cases c[NBXY][NBXY];
  int xDestDepl, yDestDepl, // Utilisés par NbCasesDeplacement(x,y)
      dx[NBDIR], dy[NBDIR];
  int XYMin[NBXY], XYMax[NBXY];
  plateau();
  void Reinitialise();
  void AffichePlateau();
  void AfficheCase(int, int, TColor);
  void AfficheValNaiss();
  bool NouvelleLettrePossible(int x, int y);
  bool LettreDeplacable(int x, int y);
  bool CaseIsolee(int x, int y);
  void PrepareCalculNbCasesDeplacement(int x, int y);
  int NbCasesDeplacement(int x, int y);
  bool FormeMotsApresDeplacement(int x0, int y0, int x1, int y1);
  void DeplaceLettre(int x0, int y0, int x1, int y1, int NbCases);
  bool LettreUtiliseeAuDepart(char Lettre);
  void PoseLettre(int x, int y, char Lettre);
  void EnleveLettre(int x, int y);
  void PlaceLettreAuto();
  int ChercheMotsFormes(int, int);
  void AjouteLettre(int x, int y);
  void DepartChrono();
  void FinChrono();
  int Sauve(int);
  int Charge(int);
 };
//---------------------------------------------------------------------------
class joueur
 {
  int Rang;
  public:
  String stNom;
  int CoordDeb[2];
  unsigned Nombre[27];
  bool Automate, RechercheDeplacements;
  int Score, NbMaxLettres;
  double TpsEcoule;
  joueur(unsigned);
  void Reinitialise(String stNvNom, bool Auto, bool RechDepl, int NbMaxL);
  void IncrementeScore(int Points);
  void DefPrmCase(int, int);
  void AfficheLettresDisp();
  void PrendLettre(char Lettre);
  void RemetLettre(char Lettre);
  int Sauve(int);
  int Charge(int);
 };
//---------------------------------------------------------------------------
class dico
 {
  public:
  unsigned long nbl[NBLMAX-1];
  unsigned long Indice[NBLMAX];
  char Dico[NTL];
  dico();
  int Existe(char *, unsigned);
 };
//---------------------------------------------------------------------------
extern dico Dico;
extern plateau p;
extern joueur J[NBDIR];
extern unsigned nbj, Jo, Tour;
//---------------------------------------------------------------------------
extern const String stCouleur[NBDIR], stRien, stFrmJoueur, stFrmTour;
//---------------------------------------------------------------------------
extern const unsigned ChxPrmLtr[114];
extern const int PrmCase[NBDIR][2];
//---------------------------------------------------------------------------
extern String stRepLocalAppData();
extern bool Sauvegarde(String stNomFichier);
extern bool Chargement(String stNomFichier);
extern void InitialisePartie(bool JoueursCompris);
extern void JoueurSuivant();
//---------------------------------------------------------------------------
#endif
