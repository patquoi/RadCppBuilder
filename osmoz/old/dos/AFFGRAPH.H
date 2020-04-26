#define AFFICHAGE ((AffMsgPartie==1)||((AffMsgPartie==2)&&(!J[Jo].Automate)))

class graphmode
 {
  int pg, mg;
  void OuvreFenetre(int);
  void FermeFenetre();
  void AfficheTexte(char*, int, int);
  public:
  int Horloge;
  unsigned char BufCurs[686];
  graphmode();
  void Palette(int);
  void SaisitChaine(char*, char[], int, int);
  void DessineHexagone(int, int, int);
  void DessinePlateau();
  void AfficheValeur(unsigned, unsigned, unsigned, unsigned, unsigned);
  void AfficheMessage(unsigned char *, unsigned, unsigned);
  char PoseQuestion(unsigned char *, unsigned char *, unsigned);
  void AfficheScore(int, int);
  void AfficheTemps(int, int, int);
  void AfficheClassement(int, int, int);
  char GereES(int);
  int Relancement(int);
  void ReinitialiseEcran();
 };
