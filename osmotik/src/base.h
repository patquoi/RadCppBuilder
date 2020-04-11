//---------------------------------------------------------------------------
#ifndef baseH
#define baseH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <classes.hpp>
#include <types.hpp>
#include <graphics.hpp>
//---------------------------------------------------------------------------
#define NBDIR               6
#define NBMAXCAMPS          6
#define NBCONFIGSDEPART     3 // (2,3 ou 6 joueurs)
#define NBLMINMOTDICO       2
#define NBLMAXMOTDICO      15
#define NBLDICO            4031818L // v1.3 (ODS8) // v.1.2 = ODS7: 3942512L // v1.1 = ODS6: 3867567L, v0.9.1 = ODS5 : 3791166L 
#define NBLALPHABET        26
//---------------------------------------------------------------------------
#define DRN_VERSION_SMT 0x0940 // Dernière version modifiée des fichiers .smt
//---------------------------------------------------------------------------
#define H(x,y,k,d) h[(x)+(k)*dx[(int)(d)]][(y)+(k)*dy[(int)(d)]]
#define X(x,k,d) ((x)+(k)*dx[(int)(d)])
#define Y(y,k,d) ((y)+(k)*dy[(int)(d)])
#define JCRT J[(int)CampCrt-1]
#define _JCRT J[(int)P->CampCrt-1]
#define JC(c) J[(int)(c)-1]
#define LIT(x)   FileRead(f, &(x), sizeof(x)) // v1.4 FileRead au lieu de fread
#define ECRIT(x) FileWrite(f, &(x), sizeof(x)) // v1.4 FileWrite au lieu de fwrite
//---------------------------------------------------------------------------
// v1.4 : taille enum forcée à 1 octet (char) car occupait 1 octet et maintenant par défaut en prend 2 voire 4.
enum direction : char {dAucune, d0h, d2h, d4h, d6h, d8h, d10h}; // 6 directions de puis un hexagone
enum camp : char {cNeutre, cBleu, cRouge, cJaune, cVert, cMagenta, cCiel}; // Camp d'un hexagone (vide, pion blanc, pion noir)
enum type_hexagone : char {thIndefini, thPlateau, thReference, thJeu}; // Type d'un hexagone qui déterminera l'endroit où il va être dessiné
enum config_depart : char {cdADeux, cdATrois, cdASix}; // Configuration de départ (nombres de camps)
//---------------------------------------------------------------------------
class joueur;
//---------------------------------------------------------------------------
class bilan
 { // Pour les int ?p?a[NBMAXCAMPS+1], ?p?a[0] est la somme des ?p?a[i], i de 1 à P->NbCamps.
  public:
  camp Camp; // Transmis à la construction de joueur
  int s, // Score (Points=NbLettres des mots formés. Ex. 3 mots de 2 lettres + 2 mots de 3 lettres = 3x2 + 2x3 = 12 points. s=p+ppaa
      p, // Points accumulés sur les lettres du camp courant.
      ppaa[NBMAXCAMPS+1], // Points Pris À l'Adversaire : Nombres de fois (points) qu'une lettre ennemie est décrémentée.
      lpaa[NBMAXCAMPS+1], // Lettres Prises À l'Adversaire : Nombres de lettres ennemies qui passent de 0 à 1 point en passant au camp courant.
      pppa[NBMAXCAMPS+1], // Points Pris Par l'Adversaire : contraire de ppaa
      lppa[NBMAXCAMPS+1]; // Points Pris Par l'Adversaire : contraire de lpaa
  void Initialise();
  bilan() { Initialise(); };
  ~bilan() {};
  void AccumulePoint() { s++; p++; };
  void AccumulePPAA(joueur *ja);
  void AccumuleLPAA(joueur *ja);
  void EnregistrePPPA(joueur *ja);
  void EnregistreLPPA(joueur *ja);
  bool Charge(int f) // v1.4 : int f au lieu de FILE *f et FileRead au lieu de fread
   {
	return FileRead(f, &s, sizeof(s))&&
		   FileRead(f, &p, sizeof(p))&&
		   LIT(ppaa[0])&&LIT(ppaa[1])&&LIT(ppaa[2])&&LIT(ppaa[3])&&LIT(ppaa[4])&&LIT(ppaa[5])&&LIT(ppaa[6])&&
		   LIT(lpaa[0])&&LIT(lpaa[1])&&LIT(lpaa[2])&&LIT(lpaa[3])&&LIT(lpaa[4])&&LIT(lpaa[5])&&LIT(lpaa[6])&&
		   LIT(pppa[0])&&LIT(pppa[1])&&LIT(pppa[2])&&LIT(pppa[3])&&LIT(pppa[4])&&LIT(pppa[5])&&LIT(pppa[6])&&
		   LIT(lppa[0])&&LIT(lppa[1])&&LIT(lppa[2])&&LIT(lppa[3])&&LIT(lppa[4])&&LIT(lppa[5])&&LIT(lppa[6]);
   };
  bool Sauve(int f) // v1.4 : int f au lieu de FILE *f et FileWrite au lieu de fwrite
   {
	return FileWrite(f, &s, sizeof(s))&&
		   FileWrite(f, &p, sizeof(p))&&
		   ECRIT(ppaa[0])&&ECRIT(ppaa[1])&&ECRIT(ppaa[2])&&ECRIT(ppaa[3])&&ECRIT(ppaa[4])&&ECRIT(ppaa[5])&&ECRIT(ppaa[6])&&
           ECRIT(lpaa[0])&&ECRIT(lpaa[1])&&ECRIT(lpaa[2])&&ECRIT(lpaa[3])&&ECRIT(lpaa[4])&&ECRIT(lpaa[5])&&ECRIT(lpaa[6])&&
           ECRIT(pppa[0])&&ECRIT(pppa[1])&&ECRIT(pppa[2])&&ECRIT(pppa[3])&&ECRIT(pppa[4])&&ECRIT(pppa[5])&&ECRIT(pppa[6])&&
           ECRIT(lppa[0])&&ECRIT(lppa[1])&&ECRIT(lppa[2])&&ECRIT(lppa[3])&&ECRIT(lppa[4])&&ECRIT(lppa[5])&&ECRIT(lppa[6]);
   };
 };
//---------------------------------------------------------------------------
class proprietes_mot : public TObject // Pour localiser un mot dans une TStringList associée grâce à TStringList::AddObject(...)
 {
  public:
  int x, y;
  direction d;
  bilan Bilan;
  proprietes_mot() { x=-1; y=-1; d=dAucune; };
  proprietes_mot(int x, int y, direction d) { this->x=x; this->y=y; this->d=d; };
  bool Charge(int f) // v1.4 : int f au lieu de FILE *f
   {
	return LIT(x)&&LIT(y)&&LIT(d)&&
		   Bilan.Charge(f);
   };
  bool Sauve(int f) // v1.4 : int f au lieu de FILE *f
   {
    return ECRIT(x)&&ECRIT(y)&&ECRIT(d)&&
           Bilan.Sauve(f);
   };
 };
//---------------------------------------------------------------------------
class hexagone
 {
  int X, Y; // Usage interne pour avoir la position sur le plateau [transmise par Initialise(x,y)]
  type_hexagone Type; // Usage interne pour l'affichage
  public:
  // propriétés principales de la case hexagonale
  camp Camp;
  int Valeur;
  char Lettre;
  int Tour; // Indique le tour lors duquel la lettre a été posée (si Lettre est définie, sinon -1)
  bool MotForme; // Indique si l'hexagone fait partie d'un mot formé
  // méthodes
  void Initialise() { Camp=cNeutre; Valeur=0; Lettre = '\0'; Tour=-1; MotForme=false; }; // Utilisé par le constructeur et par RetireLettre()
  hexagone() { Type=thIndefini; X=Y=-1; Initialise(); };
  void Initialise(int x, int y) { Type=thPlateau; X=x; Y=y; };
  void Initialise(int x, int y, int v, char l) { Type=thReference; Camp=cNeutre; X=x; Y=y; Valeur=v; Lettre=l; }; // Utilisé dans plateau::plateau
  void Initialise(type_hexagone t, int x, int y, camp c, int v, char l) { Type=t; X=x; Y=y; Camp=c; Valeur=v; Lettre=l; }; // Utilisé dans joueur::joueur
  int Xc(); // Renvoie l'abcisse du centre de l'hexagone
  int Yc(); // Renvoie l'ordonnée du centre de l'hexagone
  ~hexagone() {};
  void Dessine(TCanvas *Canvas);
  void RetireLettre(TCanvas *Canvas) { Initialise(); Dessine(Canvas); };
  void PoseLettre(TCanvas *Canvas, camp c, char l, int t);
  AnsiString asContenu();
  bool Charge(int f) // v1.4 : int f au lieu de FILE *f
   {
	return LIT(X)&&LIT(Y)&&
		   LIT(Camp)&&LIT(Valeur)&&LIT(Lettre)&&
		   LIT(Tour)&&LIT(MotForme);
   };
  bool Sauve(int f) // v1.4 : int f au lieu de FILE *f
   {
    return ECRIT(X)&&ECRIT(Y)&&
           ECRIT(Camp)&&ECRIT(Valeur)&&ECRIT(Lettre)&&
           ECRIT(Tour)&&ECRIT(MotForme);
   };
 };
//---------------------------------------------------------------------------
extern const int Score0[NBLALPHABET]; // Utilisé dans plateau & joueur
//---------------------------------------------------------------------------
class joueur
 {
  public:
  camp Camp; // Initialisé par construction
  hexagone h[NBLALPHABET]; // Capital lettres du joueur ('A'=0; 'B'=1, etc.)
  bilan BilanTour, BilanTotal;
  TDateTime TempsEcoule; // v0.9.4
  TStringList *slMotsFormes; // Mots formés lors du dernier coup
  void Initialise();
  joueur(camp c) { Camp=c; BilanTour.Camp=Camp; BilanTotal.Camp=Camp; Initialise(); TempsEcoule=0; }; // v0.9.4 (TempsEcoule)
  ~joueur() { delete slMotsFormes; };
  void InitialiseTour()
   {
    BilanTour.Initialise();
    if (slMotsFormes) slMotsFormes->Clear();
   };
  void CapitaliseLettre(hexagone *hp) // On Suppose qu'hp a assez de points et que c'est une lettre
   {
    hp->Valeur-=Score0[hp->Lettre-'A'];
    h[hp->Lettre-'A'].Valeur++;
   }
  // Méthode pour les bilans
  void AccumulePoint(int iMot)
   {
    ((proprietes_mot*)slMotsFormes->Objects[iMot])->Bilan.AccumulePoint();
    BilanTour.AccumulePoint();
    BilanTotal.AccumulePoint();
   };
  void AccumulePPAA(int iMot, joueur *ja)
   {
    ((proprietes_mot*)slMotsFormes->Objects[iMot])->Bilan.AccumulePPAA(ja);
    BilanTour.AccumulePPAA(ja);
    BilanTotal.AccumulePPAA(ja);
    ja->EnregistrePPPA(this);
   };
  void AccumuleLPAA(int iMot, joueur *ja)
   {
    ((proprietes_mot*)slMotsFormes->Objects[iMot])->Bilan.AccumuleLPAA(ja);
    BilanTour.AccumuleLPAA(ja);
    BilanTotal.AccumuleLPAA(ja);
    ja->EnregistreLPPA(this);
    ja->EnregistrePPPA(this);
   };
  void EnregistrePPPA(joueur *ja)
   {
    BilanTour.EnregistrePPPA(ja);
    BilanTotal.EnregistrePPPA(ja);
   };
  void EnregistreLPPA(joueur *ja)
   {
    BilanTour.EnregistreLPPA(ja);
    BilanTotal.EnregistreLPPA(ja);
   };
  bool Charge(int f); // v0.9.4 : code dépacée dans le cpp
  bool Sauve(int f);  // v0.9.4 : code dépacée dans le cpp
 };
//---------------------------------------------------------------------------
// Constantes utilisées dans la définition de classes (et méthodes déclarées inlines)
extern const int lq, hq;
extern const int NbCamps[NBCONFIGSDEPART];
extern joueur J[NBMAXCAMPS]; // Utilisé dans joueur, plateau (notion d'instance unique)
//---------------------------------------------------------------------------
class plateau // ATTENTION : Toutes les instances d'hexagones créées voient l'instance unique plateau *P
 {
  public:
  // Propriétéz visuelles
  int Xs, Ys; // Coordonnées de l'hexagone sur lequel est le pointeur de la souris (-1, -1) si aucun
  double K, Khp; // Echelle (Khp = K pour hexagone hors plateau : constante recalculée à partir de Nhp dans DefinitEchelle)
  int N, Nhp, // Nb Hexagones/Côté; 1h/c = 1h ; 2h/c = 7h ; Nh/c = (3N(N-1)+1)h. (Nhp = N pour hexagone hors plateau : constante)
      Xc, Yc; // (xy,yc) = Centre du plateau
  // Propriétés du jeu
  bool PartieEnCours,
       FormationMotEnCours;
  config_depart CfgDep;
  camp CampCrt; // Camp dont c'est le tour de jouer
  int TourCrt,
      NbMaxLettresAPlacer, // Nombre maximal de lettres pouvant être placées en un coup
      iMotForme, // Mot à mis en évidence en cours de comptabilisation
      NbCasesLibres,
      NbAbandons;
  TDateTime TopChrono; // v0.9.4 : Temps au moment du début du tour de jeu du joueur courant
  hexagone **h, hr[NBLALPHABET];
  void CreeHexagones();
  void DetruitHexagones();
  plateau() { h=NULL; TopChrono=0; }; // Pour l'ouverture d'une partie
  plateau(int n, config_depart cd, int nl);
  ~plateau() { DetruitHexagones(); };
  void Dessine(TCanvas *Canvas); // Au centre : le plateau
  void DessineReference(TCanvas *Canvas); // À gauche : la référence (score de régénération des lettres + capital initial)
  void DessineCapitalLettres(TCanvas *Canvas); // À droite : jeu du joueur courant (capital de lettres)
  void DessineTout(TCanvas *Canvas)
   {
    Dessine(Canvas);
    DessineReference(Canvas);
    if (CampCrt) DessineCapitalLettres(Canvas);
   };
  void DefinitEchelle(int Largeur, int Hauteur);
  inline int Xq(int X, int Y) { return (int)((X-Xc+(1-2*(X<Xc))*K*lq/2)/(K*lq)); };
  inline int Yq(int X, int Y) { return (int)((Y-Yc-(Y<Yc)*K*hq)/(K*hq)); };
  int Xh(int X, int Y); // Renvoie l'abcisse de l'hexagone que le point (X,Y) sélectionne (-1 si aucun)
  int Yh(int X, int Y); // Renvoie l'ordonnée de l'hexagone que le point (X,Y) sélectionne (-1 si aucun)
  void ChangeHexagoneCourant(TCanvas *Canvas, int X, int Y); // Change Xs et Ys et rafraîchit l'affichage
  bool CoordonneesValides(int x, int y)
   {
    return (x>=0)&&(y>=0)&&
           (x<=2*(N-1))&&(y<=2*(N-1))&&
           (x+y<=4*(N-1))&&(abs(x-y)<=N-1);
   }
  void InitialiseTourSuivant()
   {
    if (CampCrt)
     {
      CampCrt=(camp)(1+((int)(CampCrt)%NbCamps[CfgDep]));
      if (CampCrt==cBleu)
       {
        TourCrt++;
        NbAbandons=0;
       }
     }
    else
     {
      CampCrt=cBleu;
      PartieEnCours=true;
     }
    JCRT.InitialiseTour();
    TopChrono=Now(); // v0.9.4
   };
  inline bool LettrePosee(int x, int y) { return (h[x][y].Camp==CampCrt)&&(h[x][y].Tour==TourCrt); };
  inline bool LettreMemeCampDejaPosee(int x, int y) { return (h[x][y].Camp==CampCrt)&&(h[x][y].Tour<TourCrt); };
  inline bool LettreCapitalisable(int x, int y) { return h[x][y].Lettre&&(h[x][y].Valeur>=Score0[h[x][y].Lettre-'A']); };
  void ComptabiliseMotFormeLettre(int iMot, int x, int y); // +1 pt si même camp, sinon -1 pt. Si 0 alors chgt de camp et +1 pt
  void ComptabiliseMotForme(TCanvas *Canvas, int iMot);
  void DessineMot(TCanvas *Canvas, int iMot);
  void ComptabiliseMotsFormes();
  bool ChercheMots(int xd, int yd, direction d, int iFMin, int iD, int iF);
  bool LettresJouables(const AnsiString asLettresAPlacer, int xd, int yd, direction d, int &iFMin, int &iD, int &iF);
  void PoseLettre(TCanvas *Canvas, int x, int y, char l) { h[x][y].PoseLettre(Canvas, CampCrt, l, TourCrt); NbCasesLibres--; };
  void PoseLettres(TCanvas *Canvas, const AnsiString asLettresAPlacer, int xd, int yd, direction d);
  void RetireLettres(TCanvas *Canvas, int xd, int yd, int d, int iFMin);
  bool ChargePlateau(int f); // v1.4 : int f au lieu de FILE *f et FileRead au lieu de fread
  bool SauvePlateau(int f); // v1.4 : int f au lieu de FILE *f et FileRead au lieu de fread
  bool Charge(int f) // v1.4 : int f au lieu de FILE *f
   {
	return LIT(Xs)&&LIT(Ys)&&
		   LIT(K)&&LIT(Khp)&&
		   LIT(N)&&LIT(Nhp)&&
		   LIT(Xc)&&LIT(Yc)&&
		   LIT(PartieEnCours)&&LIT(FormationMotEnCours)&&
		   LIT(CfgDep)&&LIT(CampCrt)&&LIT(TourCrt)&&
		   LIT(NbMaxLettresAPlacer)&&
		   LIT(NbCasesLibres)&&
		   LIT(NbAbandons)&&
		   ChargePlateau(f);
   };
  bool Sauve(int f) // v1.4 : int f au lieu de FILE *f
   {
    return ECRIT(Xs)&&ECRIT(Ys)&&
           ECRIT(K)&&ECRIT(Khp)&&
           ECRIT(N)&&ECRIT(Nhp)&&
           ECRIT(Xc)&&ECRIT(Yc)&&
           ECRIT(PartieEnCours)&&ECRIT(FormationMotEnCours)&&
           ECRIT(CfgDep)&&ECRIT(CampCrt)&&ECRIT(TourCrt)&&
           ECRIT(NbMaxLettresAPlacer)&&
           ECRIT(NbCasesLibres)&&
           ECRIT(NbAbandons)&&
           SauvePlateau(f);
   };
 };
//---------------------------------------------------------------------------
class dico
 {
  public:
  unsigned long nbl[NBLMAXMOTDICO-1];
  unsigned long Indice[NBLMAXMOTDICO];
  char Dico[NBLDICO]; // v1.4 : char au lieu de unsigned char
  dico();
  bool Existe(const char [], unsigned); // v1.4 : char [] au lieu de unsigned char *
 };
//---------------------------------------------------------------------------
extern int Version;
extern dico Dico;
extern plateau *P;
extern const int dx[NBDIR+1], dy[NBDIR+1];
extern const TColor ch[2*(NBMAXCAMPS+1)];
extern const AnsiString asVide; // v0.8.5 (qu'une seule version pour tout le projet)
//---------------------------------------------------------------------------
extern String stRepLocalAppData(); // v1.4
//---------------------------------------------------------------------------
#endif

