#include <stdio.h>
#include <time.h>

typedef struct
 {
  int Lettre, // 0=aucune ; 1,2,...=A,B,...
      Valeur, // 0=aucune ; 1...=valeur de lettre
      Joueur; // 0=personne ; 1..6=joueur
 } cases;

class plateau
 {
  int SauvePos,
      Recherche;
  unsigned long PtsGagnes, PtsPris, LtrPrises, TotCoefs; // pour l'automate
  time_t TopTour;
  public:
  cases c[11][11];
  unsigned NbPasseTour, NbCasesLibres, ValNaiss[27];
  int dx[6], dy[6];
  unsigned XYMin[11], XYMax[11];
  plateau();
  void Reinitialise();
  void AffichePlateau();
  void ChoixCase(unsigned *, unsigned *, unsigned *);
  void AfficheCase(unsigned, unsigned, unsigned);
  void AfficheValNaiss();
  void PlaceLettre();
  void PlaceLettreAuto();
  int ChercheMotsFormes(int, int);
  void TesteTemps();
  void DepartChrono();
  void FinChrono();
  int Sauve(FILE*);
  int Charge(FILE*);
 };