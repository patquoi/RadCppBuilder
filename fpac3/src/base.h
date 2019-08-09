//---------------------------------------------------------------------------
#ifndef baseH
#define baseH
//---------------------------------------------------------------------------
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#define PRMPARDEFPILULEPARPACGUM 100
#define PRMPARDEFVULNERABILITE   100
#define PRMPARDEFFANTOMESDEPART    4
#define PRMPARDEFPORTESPARCASE    75
#define PRMPARDEFAGRESSIVITE      25
//---------------------------------------------------------------------------
#define INFINI              MaxInt
#define INDEFINIE           -1 // Coordonnées x et y
#define ENVMIN              3
#define NBPLANS             4
#define NBDIRECTIONS        4
#define SANS              255
#define TAILLEMAXCOULOIR  (NbY/10)
#define NBCOTESMANOIR       5
#define NBANIMATIONSPORTE   5
#define NBANIMATIONSMORT    4
#define RAPPORTAIREDISTMIN 20
#define NBBONUS             4
#define TEMPSBONUS        100 // Avant changement d'endroit et de nature
#define DISTMINPACBONUS   100
#define NBMAXFANTOMES      10
#define NBVIESDEPART        5
#define NBMAXPORTESFILE    50
#define NBMAXPRIMES        10
#define DELAIPRIME         16
#define PRIMEFANTOME      100
#define SCOREPILULE         1
#define SCOREPACGUM        10
#define SCOREBONUS         50 // 4x50=200 au total pour les 4 as
#define SCOREQUARTVIDE   1000
#define RAPPORTVULNTRANS   10
#define MAXDETERMINISME   100
#define TPSAVANTLANCERFTM  10
#define INACTIVITEPARDETERMINISME 25
#define DETERMINISMEMAX    99
#define NBMAXLETTRESNOM     8
#define NBENTREESTOP       10
// paramètres concernant le fichier INI
#define SECTIONTOP10       "Top10"
#define ENTREESCORE        "Score%d"
#define ENTREENOM          "Nom%d"
#define ENTREENIV          "Niveau%d"
#define SECTIONPARAM       "Paramètres"
#define ENTREEDIM     "Dimensions"
#define ENTREEAGR     "Agressivité"
#define ENTREERPP     "RapportPilulesPacGums"
#define ENTREEDVF     "DuréeVulnerabilité"
#define ENTREENFD     "NombreFantomesDepart"
#define ENTREENBP     "NombrePortes"
#define NOMVIDE       ";;;;;;;;"




//---------------------------------------------------------------------------
#define  C(x,y,d)            c[x+dx[d]][y+dy[d]]
#define _C(x,y,d)            Jeu.c[x+dx[d]][y+dy[d]]
#define  DM(x,y,d)           dm[x+dx[d]][y+dy[d]]
#define _DM(x,y,d)           Jeu.dm[x+dx[d]][y+dy[d]]
#define OAD(x,y,d)           oad[x+dx[d]][y+dy[d]]
#define  VALIDE(x,y)         (((x)>=0)&&((x)<NbX)&&((y)>=0)&&((y)<NbY))
#define _VALIDE(x,y)         (((x)>=0)&&((x)<Jeu.NbX)&&((y)>=0)&&((y)<Jeu.NbY))
#define DIST(x,y)            ((x)*(x)+(y)*(y))
#define RANDOM(X)            RandomRange(0, X)
#define NBX                  NbX
#define NBY                  NbY
#define XMAX                 (NbX-1)
#define YMAX                 (NbY-1)
#define _XMAX                (Jeu.NbX-1)
#define _YMAX                (Jeu.NbY-1)
#define CXYKD(x,y,k,d)       (((x+k*dx[d]<0)||(x+k*dx[d]>NbX-1)||(y+k*dy[d]<0)||(y+k*dy[d]>NbY-1))?vide:c[x+k*dx[d]][y+k*dy[d]])
#define PORTE(x, y)          (Table[x][y]<SANS)
#define _PORTE(x, y)         (Jeu.Table[x][y]<SANS)
#define  TRANSPOSITION(x, y) ((((!(x))||((x)==NbX-1))&&((y)==NbY/2))||(((!(y))||((y)==NbY-1))&&((x)==NbX/2)))
#define _TRANSPOSITION(x, y) ((((!(x))||((x)==Jeu.NbX-1))&&((y)==Jeu.NbY/2))||(((!(y))||((y)==Jeu.NbY-1))&&((x)==Jeu.NbX/2)))
#define  DEPLACABLE(x,y,d)   ( VALIDE(x+dx[d],y+dy[d])&&(( C(x,y,d)<mur)|| TRANSPOSITION(x+dx[d], y+dy[d])))
#define _DEPLACABLE(x,y,d)   (_VALIDE(x+dx[d],y+dy[d])&&((_C(x,y,d)<mur)||_TRANSPOSITION(x+dx[d], y+dy[d])))
#define  NUMQUART(x,y)       (((x)>    NbX/2)+2*((y)>    NbY/2))
#define _NUMQUART(x,y)       (((x)>Jeu.NbX/2)+2*((y)>Jeu.NbY/2))
#define DEMITOUR(d1,d2)      ((NBDIRECTIONS+(d1)-(d2))%NBDIRECTIONS==NBDIRECTIONS/2) // v1.2
#define ABS(x)               (((x)>=0)?(x):(-(x)))
//---------------------------------------------------------------------------
enum direction {nord, est, sud, ouest, indefinie};
enum plan      {nord_ouest, nord_est, sud_ouest, sud_est};
enum element {vide, pilule, pacgum, mur};
enum etat_ftm {mange, en_fuite, transition, en_chasse};
             // yeux, gris,     gris/couleur, couleur
enum prise_bonus {aucun=0,
                  pique=1,
                  coeur=2, pique_coeur=3,
                  trefle=4, pique_trefle=5, coeur_trefle=6, pique_coeur_trefle=7,
                  carreau=8, pique_carreau=9, coeur_carreau=10, pique_coeur_carreau=11, trefle_carreau=12, pique_trefle_carreau=13, coeur_trefle_carreau=14, tous=15};
enum blocage {non=0, par_fantome=1, par_pacman=2, par_bonus=4, zone=8, tout=255}; // zone = cas où les 4 as ont été pris et que pacman est passé à 5 cases de la porte.
enum fin_jeu {sans_vie, sans_pilule};
//---------------------------------------------------------------------------
const int dx[NBDIRECTIONS+1]={0, 1, 0, -1, 0},
          dy[NBDIRECTIONS+1]={-1, 0, 1, 0, 0};
const prise_bonus CouleurBonus[NBBONUS]={pique,coeur,trefle,carreau};
//---------------------------------------------------------------------------
class top10
 {
  private:
  TIniFile *IniFile;
  public:
  int Col0, Row0, l, h, PosDrnEntree;
  void Reinitialise();
  top10();
  ~top10() { if (IniFile) delete IniFile; };
  AnsiString asNom[NBENTREESTOP];
  int Score[NBENTREESTOP], Niveau[NBENTREESTOP];
  void Lit();
  void Ecrit();
  void InitialiseDepart(int Col0, int Row0);
  void TesteTop();
  void Affecte(int Rang, int Score, int Niveau, const AnsiString asNom);
  void AjouteAuTop(const AnsiString asNouveauNom);
  void LitParametres();
  void EnregistreParametres();
  void RestaureParametres();
  bool EstMieuxQueLeRang(int Rang);
 };
//---------------------------------------------------------------------------
class primes
 {
  public:
  int x[NBMAXPRIMES], y[NBMAXPRIMES],
      Delai[NBMAXPRIMES], Valeur[NBMAXPRIMES],
      Nouvelle, Courante;
  void Initialise();
  primes() { Initialise(); };
  void Affiche();
  void Ajoute(int Num, int xp, int yp);
 };
//---------------------------------------------------------------------------
class bonus
 {
  public:
  int x, y, Temps;
  prise_bonus APrendre, Pris;
  void Initialise() { x=y=INDEFINIE; APrendre=Pris=aucun; Temps=0; };
  bonus() { Initialise(); }
  void Gere();
  void Mange();
 };
//---------------------------------------------------------------------------
class fantome
 {
  private:
  int FNum;
  public:
  int x, y,
      xp, yp, // Coordonnées précédentes
      TpsRestantVulnerable; // Temps de vulnerabilité
  direction d;
  etat_ftm Etat;
  void Initialise() { x=y=xp=yp=INDEFINIE; d=indefinie; Etat=mange; TpsRestantVulnerable=0; };
  fantome() { Initialise(); };
  void Numerote(int Num) { FNum = Num; };
  void Lance();
  void CalculeNouvelleDirection();
  void EvalueSituation();
  void Deplace();
  void RendVulnerable();
  __property int Num = {read=FNum};
 };
//---------------------------------------------------------------------------
class pacman
 {
  public:
  bool AMange;
  int TempsMort, // Si >0 Moment où pacman a été bouffé (Jeu.Temps)
      x, y,
      xp, yp; // Coordonnées précédentes
  direction d,
            ds; // Direction demandée lorsque PacMan est à cheval ou la direction n'est pas encore possible ! On réserve la demande
  void Initialise() { xp=yp=x=y=INDEFINIE; d=ds=indefinie; AMange=false; TempsMort=0; };
  pacman() { Initialise(); };
  void Positionne(const int x, const int y, const direction d)
   {
    xp=yp=INDEFINIE;
    ds=indefinie;
    this->x=x; this->y=y;
    this->d=d;
    TempsMort=0;
    AMange=false;
   };
  void Deplace();
  void MangePilule();
  void MangePacGum();
  void Meurt();
 };
//---------------------------------------------------------------------------
class porte
 {
  public:
  int x, y, Pos;
  bool Ouverte;
  unsigned char Bloquee, BlqEnr;
  porte() {x=y=INDEFINIE; Bloquee=BlqEnr=Pos=0; Ouverte=false; };
  ~porte() {};
  void Positionne(const int x, const int y, const bool Ouverte, const int Position)
   {
    this->x=x; this->y=y;
    this->Pos=Position;
    this->Ouverte=Ouverte;
   };
 };
//---------------------------------------------------------------------------
struct bord
 {
  int x, y;
  direction d;
 };
//---------------------------------------------------------------------------
class ouvadist;
//---------------------------------------------------------------------------
class jeu
 {
  private:
  public:
  bool ACheval,
       QuartNettoye; // Sert à renvoyer les fantômes au manoir
  int Temps, NbCases, NbPilules[NBPLANS],
      Agressivite, FrqPil, Vulnerabilite, FantomesDepart, PortesParCase, // Paramètres
      NbX, NbY, NbPortes,
      XManoir, YManoir,
      Determinisme,
      NbVies, Niveau,
      Score, NbBords,
      NbFantomes, NbFantomesManges,
      Inactivite;
  bonus Bonus;
  bord Bord[NBDIRECTIONS*NBCOTESMANOIR];
  fantome Fantome[NBMAXFANTOMES];
  pacman PacMan;
  primes Primes;
  element **c;
  int **dm; // Distance en cases au manoir (XManoir,YManoir)
  ouvadist **oad; // Précalcul des positions d'ouverture/fermeture de portes à distance dans la phase Sésame
  unsigned char **Table; // Si Table[x][y]<SANS => Porte[Table[x][y]] existe
  porte *Porte;

  void Detruit();
  int Environnement(const int x, const int y, const direction d);
  int EnvMinimum(const int x, const int y);
  jeu();
  ~jeu() { Detruit(); };
  void Initialise();
  void PosePortes();
  void AnimePortes();
  void FermePortes(); // Juste après la mort de Pacman et si Sésame est actif
  void InitialiseLaby();
  void CreeLaby(const int x, const int y, const int Plan);
  void CreeLaby();
  void CalculeDistanceAuManoir(int x, int y);
  int DifficulteEvaluee();
  void LanceFantome(const int i) { Fantome[i].Lance(); };
  void DeplaceFantomes();
  void Deplace();
  void IncrementeScore(int Points);
  void IncrementeDeterminisme();
  void AjouteVie();
  void RetireVie();
  void AjouteFantome() { LanceFantome(NbFantomes++); } // A FAIRE : Réinitialiser les fantômes
  void MangePacMan()
   {
    if (PacMan.d<indefinie)
     PacMan.Meurt();
   };
  void MangeFantome(int Num);
  void TermineJeu(fin_jeu Fin);
  int PositionPorte(int NumPorte, int x, int y);
  void CalculeOuvADistCase(int Num, int x, int y, int Pos);
  void CalculeOuverturesADistance();
  void GenereTraceOAD();
  void DebloquePorte(int x, int y, blocage Blocage);
  void BloquePorte(int x, int y, blocage Blocage);
 };
//---------------------------------------------------------------------------
// Classe jeu d'instance statique et unique Jeu : accès à l'instance depuis les méthodes de classes des instances filles de jeu
extern jeu Jeu;
//---------------------------------------------------------------------------
class ouvadist
 {
  public:
  int *PosPorte;
  void Initialise();
  ouvadist() { PosPorte=new int[Jeu.NbPortes]; Initialise(); };
  ~ouvadist() { if (PosPorte) delete[] PosPorte; };
 };
//---------------------------------------------------------------------------
#endif

