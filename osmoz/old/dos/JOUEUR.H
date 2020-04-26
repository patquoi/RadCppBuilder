#include <stdio.h>

class joueur
 {
  int Rang;
  public:
  unsigned char Nom[8];
  unsigned CoordDeb[2], Nombre[27];
  int Automate, Score;
  double TpsEcoule;
  joueur(unsigned);
  void Reinitialise(unsigned char[8], int);
  void SaisitNom();
  void DefPrmCase(unsigned, unsigned);
  void AfficheLettresDisp();
  unsigned ChoixLettre();
  void IncrementeScore(int);
  int Sauve(FILE*);
  int Charge(FILE*);
 };