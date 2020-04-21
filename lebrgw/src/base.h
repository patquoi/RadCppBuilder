//---------------------------------------------------------------------------
#ifndef baseH
#define baseH
//---------------------------------------------------------------------------
#define NBX 40
#define NBY 25
#define INDEFINI -1
#define NBDIR 5
#define NBDECAL 4
#define MAXDIR 4
#define NBMAXNIV 100
//---------------------------------------------------------------------------
#define I_CHEMIN   0
#define I_PORTEO   1
#define I_PORTEH   1
#define I_PORTEV   5
#define I_DECLB   10
#define I_DECLR   11
#define I_MUR     12
#define I_BETE    28 // Entière N,E,S,O
#define I_BETELAV 32 // Longue moitié AVant
#define I_BETELAR 36 // Longue moitié ARrière
#define I_BETECAV 40 // Courte moitié AVant
#define I_BETECAR 44 // Courte moitié ARrière
//---------------------------------------------------------------------------
#define AFF_BETES  1
#define AFF_PORTES 2
#define AFF_DECL   4
//---------------------------------------------------------------------------
// Paramètre Bordure de EstUnMur
#define AVEC_BORDS true
#define SANS_BORD false
//---------------------------------------------------------------------------
#define NIV (s->NivCrt)
//---------------------------------------------------------------------------
#define abs(x) ((x<0)?(-(x)):(x))
#define EST_DE_TYPE(x,y,d,t) (c[(x)+dx[d]][(y)+dy[d]].Type==(t))
#define EST_UN_DECL(x,y,d) (c[(x)+dx[d]][(y)+dy[d]].Type>porte)
#define SANS_CURSEUR(xb,yb,d) (((xb)+dx[d]!=x)||((yb)+dy[d]!=y))
//---------------------------------------------------------------------------
#define C(x,y,d) c[(x)+dx[d]][(y)+dy[d]]
#define READ(x) FileRead(hfile, &(x), sizeof(x))
#define WRITE(x) FileWrite(hfile, &(x), sizeof(x))
//---------------------------------------------------------------------------
// v1.7 : type enum forcé à char pour être sûr de lire/écrire sur 1 octet
enum type_c : char {rien, mur, porte, decl_b, decl_r};
enum direction : char {indefinie, nord, est, sud, ouest};
enum pos_porte : char {ouverte, p_ouverte, entrouverte, p_fermee, fermee};
enum sens_porte : char {ferme_ouvert=-1, aucun, ouvert_ferme};
//---------------------------------------------------------------------------
class bete;
class case_p;
class niveau;
class serie;
//---------------------------------------------------------------------------
class bete
 {
  public:
  int Num, x, y,
	  Decalage;
  direction Dir; // Utilisation unique de niveau::TraiteBetes()
  bete() { Decalage=Num=0; x=INDEFINI; y=INDEFINI; };
  bool EstDefinie() { return (x>INDEFINI)&&(y>INDEFINI)&&(Dir>indefinie); };
  void Definit(int x0, int y0, direction d) { x=x0; y=y0; Dir=d; };
  void Initialise(int n) { Num=n; x=INDEFINI; y=INDEFINI; Dir=indefinie; };
  void Retire() { x=INDEFINI; y=INDEFINI; Dir=indefinie; };
  void TourneADroite() { Dir=(direction)(1+(Dir%MAXDIR)); };
  void TourneAGauche() { Dir=(direction)(1+(Dir+2)%MAXDIR); };
  bool ArriveEn(int xc, int yc) { return (xc!=x)||(yc!=y); };
  void Deplace();
  bool Charge(int hfile);
  bool Sauve(int hfile);
 };
//---------------------------------------------------------------------------
class case_p
 {
  public:
  type_c Type;
  pos_porte PosPorte;
  sens_porte SensPorte;
  bete *Bete;
  case_p() { Type=rien; PosPorte=ouverte; Bete=NULL; SensPorte=aucun; };
  void Definit(type_c tc, pos_porte pp)
   {
	Type=tc; PosPorte=pp;
	SensPorte=(tc==porte)?((pp==ouverte)?ferme_ouvert:ouvert_ferme):aucun;
   };
  void Definit(type_c tc, pos_porte pp, bete *b)
   {
	Type=tc; PosPorte=pp; Bete=b;
	SensPorte=(tc==porte)?((pp==ouverte)?ferme_ouvert:ouvert_ferme):aucun;
   };
  bool EstFranchissable();
  bool Charge(int hfile, niveau *NivCrt);
  bool Sauve(int hfile);
 };
//---------------------------------------------------------------------------
class porte_en_mvt
 {
  public:
  int x, y;
  porte_en_mvt *Svt;
  porte_en_mvt(int xp, int yp) { x=xp; y=yp; Svt=NULL; };
  ~porte_en_mvt() { if (Svt) delete Svt; };
  void Ajoute(int xp, int yp)
   {
	if ((x==xp)&&(y==yp)) return; // On ne la rajoute pas deux fois !
	if (Svt)
	 Svt->Ajoute(xp, yp);
    else
     Svt=new porte_en_mvt(xp, yp);
   };
  void Retire(int xp, int yp);
 };
//---------------------------------------------------------------------------
class niveau
 {
  public:
  int Num, NbBetes, NbCrtBetes, NbBetesAFaire, NbBetesCoincees;
  bete *Bete;
  porte_en_mvt *PorteEnMvt;
  case_p c[NBX][NBY];
  long Cumul, Score, Barre, Delai, Temps, TpsRestant;
  int x0, y0, x, y, Effet0, Effet;
  bool TourEnCours, // Un tour complet se déroule (JoueTour)
       Lance, // Indique si un niveau a été lancé (jeu en cours ou en pause)
       DmdDeclPorte[NBDIR];
  niveau()
   {
    Bete=NULL; PorteEnMvt=NULL; TourEnCours=false;
    Effet=Effet0=x=y=x0=y0=NbBetes=NbCrtBetes=NbBetesAFaire=NbBetesCoincees=Num=0;
    Cumul=Score=Barre=Delai=Temps=TpsRestant=0L;
   };
  niveau(long CumulSvg)
   {
    Bete=NULL; PorteEnMvt=NULL; TourEnCours=false; Lance=false;
    Effet=Effet0=x=y=x0=y0=NbBetes=NbCrtBetes=NbBetesAFaire=NbBetesCoincees=Num=0;
    Score=Barre=Delai=Temps=TpsRestant=0L;
    Cumul=CumulSvg;
   };
  void Initialise();
  bool CreeBetes(int n);
  niveau(int n)
   {
    Bete=NULL; PorteEnMvt=NULL; TourEnCours=false; Lance=false;
    Effet=Effet0=x=y=x0=y0=NbBetes=NbCrtBetes=NbBetesAFaire=NbBetesCoincees=Num=0;
    Score=Barre=Delai=Temps=TpsRestant=0L;
    CreeBetes(n);
   };
  ~niveau()
   {
    if (Bete) delete[] Bete;
    if (PorteEnMvt) delete PorteEnMvt;
   };
  bete *AjouteBete(int x0, int y0, direction d);
  void RetireBete(int n);
  int NumImage(int x, int y, int Affichage);
  bool EstLiberable(int x, int y);
  bool EstUnMur(int x, int y, direction d, bool Bordure);
  bool EstUnePorte(int x, int y, direction d);
  bool EstUnDeclIsole(int x, int y, direction d);
  bool EstUnePorteIsolee(int x, int y);
  void ActionnePorte(int x, int y);
  void ActionneDeclencheur(int x, int y);
  bool EstTermine() { return ((Effet==Effet0)&&(Effet0<5*NbBetesAFaire))||(!TpsRestant)||(NbBetesCoincees==NbBetesAFaire); };
  void AjoutePorteEnMvt(int xp, int yp);
  void RetirePorteEnMvt(int xp, int yp);
  void DeclenchePorteADistance(direction d);
  void TraiteBerger();
  void TraiteBetes();
  void TraitePortes();
  void __fastcall JoueTour();
  bool Charge(int hfile);
  bool Sauve(int hfile);
 };
//---------------------------------------------------------------------------
extern const int dx[NBDIR], dy[NBDIR];
//---------------------------------------------------------------------------
extern niveau *Niv;
//---------------------------------------------------------------------------
extern String stRepLocalAppData();
//---------------------------------------------------------------------------
#endif
