//---------------------------------------------------------------------------
#ifndef simulH
#define simulH
//---------------------------------------------------------------------------
#include <vcl/dstring.h>
#include <systdate.h>
//---------------------------------------------------------------------------
#define NBXDEF                    99 // v4.0 (NBX->NBXDEF)
#define NBYDEF                    63 // v4.0 (NBY->NBYDEF)
#define NBXMIN                    8  // v4.0
#define NBYMIN                    8  // v4.0
//---------------------------------------------------------------------------
#define NBDIR                      4
#define NBFEUXDEFAUT              30
#define NBETAPESDEFAUT             4
#define NBVEHICULESDEFAUT        120
#define NBPIETONSDEFAUT           30 // v2.0 (25% des v�hicules = 120/4 = 30)
#define NBNIVEAUXPRIORITE          3 // v2.2
#define NBMAXETAPES               32
#define NBMAXVEHICULES          1000
#define NBMAXPIETONSPARCASE        2 // v2.0
#define NBMAXLIGNESBUSTRAM         9 // v3.5
#define NBMAXARRETSBUSTRAMPARLIGNE 9 // v3.5
#define NBMAXBUSTRAMPARLIGNE       3 // v3.5
#define NBMAXARRETSBUSTRAM         NBMAXLIGNESBUSTRAM*NBMAXARRETSBUSTRAMPARLIGNE // v3.5
#define NBMAXBUSTRAM               NBMAXLIGNESBUSTRAM*NBMAXBUSTRAMPARLIGNE // v3.5
#define NBSENSVOIETRAMBASE         7 // v3.5
#define NBSENSVOIETRAM             64// v3.5 (2^NBSENSVOIETRAMBASE-1=2^6=64)
#define NBTYPESVOIE                2 // v3.5
#define NBSITUATIONSTAXI           4 //  v3.6
//---------------------------------------------------------------------------
// valeurs de distance particuli�res
#define DIST_INDEFINIE  32767
//---------------------------------------------------------------------------
// Filtre pour ne donner que la nature (sans les d�cors) dans la propri�t� Nature (poids fort)
#define NATURE(v) ((v)->Nature&0x7FFF0000)
//---------------------------------------------------------------------------
// 3�me index de voie::DistEtape[][][]
#define SANSPSGBUS 0
#define AVECPSGBUS 1
//---------------------------------------------------------------------------
// Index de RotPossDir
#define R90D 1
#define R180 2
#define R90G 3
//---------------------------------------------------------------------------
#define VERSION    0x400 // v3.0. La version change SSI le format de fichiers change
#define VERSIONMIN 0x300 // v3.0. Version minimum stock�e : NE PAS MODIFIER
#define VERSIONANC 0x200 // v3.0  Version non stock�e compatible : NE PAS MODIFIER
//---------------------------------------------------------------------------
#define V(x,y,d) v[((x)+dx[d])%cv->NbX][((y)+dy[d])%cv->NbY] // en dehors de la classe centre_ville (v4.0)
#define _V(x,y,d) v[((x)+dx[d])%NbX][((y)+dy[d])%NbY] // depuis la classe centre_ville (v4.0)
#define V_(x,y,n,d) v[((x)+(n)*dx[d])%cv->NbX][((y)+(n)*dy[d])%cv->NbY] // en dehors de la classe centre_ville (v4.0)
#define _V_(x,y,n,d) v[((x)+(n)*dx[d])%NbX][((y)+(n)*dy[d])%NbY] // depuis la classe centre_ville (v4.0)
//---------------------------------------------------------------------------
#define min(x,y) (((x)<(y))?(x):(y))
#define max(x,y) (((x)>(y))?(x):(y))
//---------------------------------------------------------------------------
// Pour centre_ville::PrepareCopie(...)
#define DEBUT true
#define FIN   false
//---------------------------------------------------------------------------
// Version 1.5 : Ajout de la vitesse
//  - Ajout de la propri�t� NbVitesses dans la classe centre_ville.
//  - Il peut y avoir de 1 � 3 vitesses diff�rentes : 1 case/tour /2 tours ou /3 tours.

// Version 2.0 : Ajout des pi�tons
//  - Les pi�tons se d�placent en dehors des voies (endroits noirs) ou sur les passages pi�tons.
//  - classe pieton
//  - propri�t� PassagePieton, FeuOpposePietons dans la classe voie.

// Version 2.2 : Ajout des v�hicules d'urgence et de police
//  - type enum�r� niveau_priorite
//  - propri�t� niveau_priorite NivPriorite dans la classe vehicule

// Version 3.0 : Ajout des bus
//  - Classes arret_bus, ligne_bus, bus
//  - Propri�t�s voie::NumArretBus, centre_ville::ArretBus, centre_ville::LigneBus

// Version 3.1 : Activation des couloirs de bus
//  - Utilisation du bouton et de la rubrique Couloir Bus
//  - Utilisation de la propri�t� PassageBus de la classe voie

// Version 3.5 : Ajout des trams
//  - Classes arret_tram, ligne_tram, tram
//  - Propri�t�s voie::NumArretTram, centre_ville::ArretTram, centre_ville::LigneTram

// Version 3.6 : Ajout des taxis
//  - Classes place_taxi, file_taxi, taxi
//  - Propri�t�s voie::NumProchTaxi, voie::NumPlaceTaxi, centre_ville::PlaceTaxi, centre_ville::FileTaxi, centre_ville::Taxi 

// Version 3.8 : Zones d�limit�es en vue des d�cors
//  - Zones de circulation, Zones habitables, Zones pi�tonnes

// Version 3.9 : Premiers d�cors suivant les zones
//  - toitures, trottoirs, pelouses, arbres

// Version 4.0 : Dimensions de la zone modifiable

// Version 4.2 : G�n�ration al�atoire d'un r�seau (voies automobiles seulement)

//---------------------------------------------------------------------------
// types �num�r�s
//---------------------------------------------------------------------------
enum priorite {a_droite, cedez_le_passage, stop, feux};
enum direction {indefinie, nord, est, sud, ouest};
enum sens {indefini, horizontal, vertical}; // v2.0. Pour les passages pi�tons
enum dirposs {aucune, N, E, NE, S, NS, SE, NES, O, NO, EO, NEO, SO, NSO, ESO, NESO};
enum diraprendre {gauche, devant, droite};
enum etat_feu {inactif, vert, orange, rouge};
enum dmd_vert {arrivee_vehicule, immediate};
enum psg_rouge {prm_dmd, immediat};
enum type_stats {par_nombre, par_pourcentage};
enum compatibilite {version_inf_16, version_inf_20, version_courante}; // v2.0
enum niveau_priorite {normal, urgence, police}; // v2.2
enum position_arret_bus_tram {tete, milieu, queue}; // v3.5 (ajout de "_tram" au nom du type car communs aux deux types d'arr�t)
enum sens_voie_tram {aucune_voie=0, nord_est=1, nord_sud=2, nord_ouest=4, sud_est=8, est_ouest=16, sud_ouest=32}; // v3.5
enum sens_voie_tram_base {aucune_voie_base, ne, ns, no, se, eo, so};
enum type_distance {type_indefini, etapes, arrets_bus, arrets_tram, files_taxi}; // v3.5. Ajout de files_taxi : v3.6
enum type_voie {tvAucun, tvRoute, tvVoieTram, tvTout}; // pour la suppression des routes et voies de tram. v3.5
enum situation_taxi {stAttente, stDepart, stDepot, stRetour}; // v3.6
enum nature { voies,
              trottoirs=0x10000, arbre=0x10010, pelouse=0x10020,  // D�cors zone pi�tonne (v3.9)
              immeubles=0x20000};
enum coin {aucun_coin, haut_droite, bas_droite, bas_gauche=4, haut_gauche=8, quatre_coins=15}; // v3.8
//---------------------------------------------------------------------------
class pieton // v2.0
 {
  int Numero;
  public:
  int x, y, Dir, DemiCase,
      NumArretBus, // v3.0. Arr�t de bus d'attente (si >0). Le pi�ton se trouve � c�t� de cet arr�t (� droite de la t�te de l'arr�t de bus)
      NumArretTram, // v3.5. Arr�t de tram d'attente (si >0). Le pi�ton se trouve � c�t� de cet arr�t (� droite de la t�te de l'arr�t de tram)
      NumFileTaxi, // v3.6. File de taxi d'attente (si >0). Le pi�ton se trouve � c�t� de cette file (� droite de la t�te de file de taxi)
      NumBus, // v3.0. Bus dans lequel se trouve le pi�ton (si >0. Dans ce cas, x=-1 et y=-1)
      NumTram, // v3.5. Tram dans lequel se trouve le pi�ton (si >0. Dans ce cas, x=-1 et y=-1)
      NumTaxi, // v3.6. Tram dans lequel se trouve le pi�ton (si >0. Dans ce cas, x=-1 et y=-1)
      TourDrnDepl, TourDrnAff,
      TourAttBus, // v3.0. Tour � partir duquel le pi�ton attend le bus
      TourAttTram, // v3.5. Tour � partir duquel le pi�ton attend le tram
      TourAttTaxi, // v3.6. Tour � partir duquel le pi�ton attend le taxi
      DemiCasesParcourues; // v3.0. L'unit� de longueur pi�tonne est la demi-case, pas la case !
  bool PsgPtTrv,
       ArretBusTrv, // v3.0. Arr�t de bus trouv�
       AttendBus,  // v3.0. Attend un bus � l'arret NumArretBus
       ArretTramTrv, // v3.5. Arr�t de tram trouv�
       AttendTram,  // v3.5. Attend un tram � l'arret NumArretTram
       FileTaxiTrv, // v3.5. File de taxi trouv�
       AttendTaxi,  // v3.5. Attend un taxi � la file NumFileTaxi
       VeutDescendre, // v3.0. Indique qu'il veut descendre du bus, du tram ou du taxi
       Ecrase; // v4.3. Indique si ce pi�ton a �t� �cras� : Si c'est le cas les coordonn�es sont l'endroit du crime 
  void Initialise()
   {
    x=-1; y=-1;
    Dir=indefinie;
    NumTaxi=NumTram=NumBus=NumFileTaxi=NumArretTram=NumArretBus=DemiCase=0; // v3.6 (NumTaxi, NumFileTaxi)
    DemiCasesParcourues=TourDrnAff=TourDrnDepl=0L;
    Ecrase=VeutDescendre=AttendTaxi=AttendTram=AttendBus=FileTaxiTrv=ArretTramTrv=ArretBusTrv=PsgPtTrv=false; // v4.3 (Ecrase)
   };
  pieton() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void Place(int x0, int y0) { x=x0; y=y0; DemiCase=0; };
  void Definit(int x0, int y0, direction Dir0, int DemiCase0) { x=x0; y=y0; Dir=Dir0; DemiCase=DemiCase0; TourDrnAff=TourDrnDepl=0L; PsgPtTrv=false; };
  void AnnuleRechercheEnCours()
   {
    if (PsgPtTrv) PsgPtTrv=false;
    if (ArretBusTrv) ArretBusTrv=false;
    if (ArretTramTrv) ArretTramTrv=false;
    if (FileTaxiTrv) FileTaxiTrv=false; // v3.6
   };
  pieton(int x0, int y0, direction Dir0, int DemiCase0) { Definit(x0, y0, Dir0, DemiCase0); };
  ~pieton() {};
  void ChercheFileTaxis(); // v3.6
  bool Defini() { return (x>-1)&&(y>-1); };
  void Verifie(AnsiString &asMsgErr);
  void MonteDansBus(int b) { NumBus=b; AttendBus=false; x=-1; y=-1; }; // v3.6
  void MonteDansTram(int t) { NumTram=t; AttendTram=false; x=-1; y=-1; }; // v3.6
  void MonteDansTaxi(int t) { NumTaxi=t; AttendTaxi=false; NumFileTaxi=0; x=-1; y=-1; }; // v3.6
  void SeFaitEcraser() { Ecrase=true; PsgPtTrv=ArretBusTrv=AttendBus=ArretTramTrv=AttendTram=FileTaxiTrv=AttendTaxi=VeutDescendre=false; }; // v4.3
 };
//---------------------------------------------------------------------------
class feu
 {
  int Numero;
  public:
  int x, y, Dir; // Orientation. Mais il peut y avoir max. 2 feux par case;
  etat_feu Etat, ProchainEtat;
  int NbFeuxDmd, // Nbre de feux demandant le rouge
      NbFeuxAtt,// Nbre de feux devant �tre rouge pour que celui-ci (this) passe au vert
      *NumFeuxDmd, // Liste des feux demandant le rouge
      *NumFeuxAtt, // Liste des feux devant �tre rouge pour que celui-ci (this) passe au vert
      DureeRouge,
      DureeVert,
      TourDrnChgEtat; // Tour du dernier changement d'�tat
  dmd_vert TypeDmdVert; // Type de demande du vert : d�s l'arriv�e d'un vehicule ou d�s le passage au rouge
  psg_rouge TypePsgRouge; // Type de passage au rouge : d�s la premi�re demande ou � l'unanimit� des feux demandeurs
  bool DemandeVert, // Indique qu'il demande le rouge (� ceux qui ont Numero dans FeuxDmd[])
       FeuxTousRouges, // Indique que les feux (FeuxAtt) sont tous rouges
       RougeDemande, // Indique qu'un feu demande le rouge
       ProchainVert, // Indique qu'il est autoris� � passer au vert
       VerifEnCours; // Drapeau pour Verifie()
  void Initialise()
   {
    x=-1; y=-1; Dir=indefinie; ProchainEtat=Etat=inactif;
    TypeDmdVert=arrivee_vehicule;
    TypePsgRouge=prm_dmd;
    DureeVert=DureeRouge=NbFeuxAtt=NbFeuxDmd=0;
    TourDrnChgEtat=0L;
    ProchainVert=RougeDemande=FeuxTousRouges=DemandeVert=false;
    VerifEnCours=false;
   };
  feu() { Numero=0; Initialise(); NumFeuxDmd=NumFeuxAtt=NULL; }; // v3.8.2 (NULL)
  void AffecteNumero(int Num) { Numero=Num; };
  void Definit(int x0, int y0, int Dir0) { x=x0; y=y0; Dir=Dir0; Etat=inactif; };
  ~feu()
   {
    if (NbFeuxDmd) { delete[] NumFeuxDmd; NumFeuxDmd=NULL; }
    if (NbFeuxAtt) { delete[] NumFeuxAtt; NumFeuxAtt=NULL;}
   };
  bool Defini() { return (x>-1)&&(y>-1)&&(Dir>aucune); };
  int DefinitNbFeuxDmd(int n); 
  int DefinitNbFeuxAtt(int n);
  void AjouteFeuDmd(int NumNvFeu);
  void AjouteFeuAtt(int NumNvFeu);
  void RetireFeuDmd(int NumFeu);
  void RetireFeuAtt(int NumFeu);
  void ChangeEtat();
  void DefinitProchainEtat(); 
  void Evolue(); 
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr, AnsiString asSource);
 };
//---------------------------------------------------------------------------
class etape
 {
  int Numero;
  public:
  int x, y;
  void Initialise() { x=-1; y=-1; };
  etape() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void Definit(int x0, int y0) { x=x0; y=y0; };
  etape(int x0, int y0) { Definit(x0, y0); };
  ~etape() {};
  bool Definie() { return (x>-1)&&(y>-1); };
  void PlaceProchainVehicule();
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
class vehicule
 {
  int Numero;
  public:
  int x, y;
  direction Dir, DirDrnDepl;
  niveau_priorite NivPriorite; // v2.2
  int NumEtapeDepart, NumEtapeArrivee, // Index-1 de centre_ville::Etape[]
      TourDrnDepl, // Tour du dernier d�placement effectu�
      TourDepart, // Tour pdt lequel il a �t� plac� sur l'�tape de d�part
      NbCasesParcourues, // Nombre de cases parcourues
      NbToursRepos; // v2.2.4 : Tours pendant lesquels le v�hicule ne s'est pas d�plac� du fait de la vitesse r�duite
  void Initialise()
   {
    x=-1; y=-1;
    DirDrnDepl=Dir=indefinie;
    NivPriorite=normal;
    NbToursRepos/*v2.2.4*/=NbCasesParcourues=TourDepart=TourDrnDepl=0L;
    NumEtapeDepart=NumEtapeArrivee=0;
   };
  vehicule() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void Place(int x0, int y0) { x=x0; y=y0; };
  void Definit(int x0, int y0, direction Dir0, int NumDepart, int NumArrivee, niveau_priorite NivPriorite0) // v2.2
   { x=x0; y=y0; Dir=Dir0; NumEtapeDepart=NumDepart; NumEtapeArrivee=NumArrivee; NivPriorite=NivPriorite0; };
  ~vehicule() {};
  bool Defini() { return (x>-1)&&(y>-1); };
  void CalculeProchaineDirection();
  direction ProchaineDirectionAuCarrefour();
  bool PeutPasser();
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
// Classes de GESTION DES BUS
//---------------------------------------------------------------------------
class depot_bus // v3.0. ATTENTION : il n'y en a qu'un !
 {
  public:
  int x, y, NumDrnBusSorti;
  void Initialise() { x=-1; y=-1; NumDrnBusSorti=0; };
  depot_bus() { Initialise(); };
  void Definit(int x0, int y0) { x=x0; y=y0; NumDrnBusSorti=0; };
  depot_bus(int x0, int y0) { Definit(x0, y0); };
  ~depot_bus() {};
  bool Defini() { return (x>-1)&&(y>-1); };
  void PlaceProchainBus();
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
class bus // v3.0
 {
  int Numero;
  public:
  direction Dir, DirDrnDepl, DirAvtDrnDepl;
  int x, y, NumLigne,
      NumDrnArret, NumArretSvt, // Index-1 de centre_ville::ArretBus
      NbPersonnes, // Correspond aux nombre de Pieton ayant NumBus = Numero (pi�tons dans le bus)
      TourDrnDepl, // Tour du dernier d�placement effectu�
      TourDepart, // Tour pdt lequel il a �t� plac� sur la case du d�pot
      TourArriveDrnArret, // Tour lorsque le bus est arr�t� au dernier arr�t
      TourDepartArretSvt, // Tour pour le d�part vers l'arr�t suivant
      NbCasesParcourues, // Nombre de cases parcourues
      NbCasesParcouruesDepuisDrnArret, // Idem mais remis � 0 � chaque arr�t de bus
      NbToursRepos; // Tours pendant lesquels le bus ne s'est pas d�plac� du fait de la vitesse r�duite
  void Initialise()
   {
    x=-1; y=-1;
    DirAvtDrnDepl=DirDrnDepl=Dir=indefinie;
    NbPersonnes=NbToursRepos=NbCasesParcouruesDepuisDrnArret=NbCasesParcourues=TourArriveDrnArret=TourDepartArretSvt=TourDepart=TourDrnDepl=0L;
    NumDrnArret=NumArretSvt=0;
   };
  bus() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void Place(int x0, int y0) { x=x0; y=y0; };
  void Definit(int NumLigne0, int NumArretSvt0)
   { NumLigne=NumLigne0; NumArretSvt=NumArretSvt0; };
  ~bus() {};
  bool Defini() { return (x>-1)&&(y>-1); };
  void FaitMonterPieton(int NumPietonAFaireMonter);
  void FaitMonterEtDescendre(); // v3.0
  void CalculeProchaineDirection();
  direction ProchaineDirectionAuCarrefour();
  bool PeutPasser();
  int NumeroArretSuivant();
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
class arret_bus // v3.0
 {
  int Numero;
  public:
  int x, y; // Position de la t�te de l'arr�t de bus (indiquant les couleurs de lignes)
  bool Ligne[NBMAXLIGNESBUSTRAM]; // Indique si une ligne de bus passe par cet arr�t (Index-1)
  int NbLignes,
      NumLigne[NBMAXLIGNESBUSTRAM]; // Liste des lignes de bus passant par cet arr�t (Index-1)
  void Initialise();
  arret_bus() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void Definit(int x0, int y0) { x=x0; y=y0; };
  arret_bus(int x0, int y0) { Definit(x0, y0); };
  ~arret_bus() {};
  bool Defini() { return (x>-1)&&(y>-1); };
  void InitialiseInfosLignesBus();
  void AjouteLigneBus(int n);
  AnsiString asListeLignesBus(); // v3.0.5
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
 };

class ligne_bus // v3.0
 {
  int Numero; // Num�ro de la ligne (CoulLigneBus[Numero]=Couleur de la ligne)
  public:
  int NbArrets, // Nb arr�ts de la ligne
      NumArret[NBMAXARRETSBUSTRAMPARLIGNE], // Ordre des arr�ts � effectuer
      NbBus, // Nb bus de la ligne
      NumBus[NBMAXBUSTRAMPARLIGNE]; // N� des bus de la ligne
  void Initialise();
  ligne_bus() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void AjouteBus(int NumeroBus);
  ~ligne_bus() {};
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
// Classes de GESTION DES TRAMS
//---------------------------------------------------------------------------
class tram // v3.5
 {
  int Numero;
  public:
  int x, y, NumLigne;
  direction Dir, DirDrnDepl, DirAvtDrnDepl;
  int NumDrnArret, NumArretSvt, // Index-1 de centre_ville::ArretTram
      NbPersonnes, // Correspond aux nombre de Pieton ayant NumTram = Numero (pi�tons dans le tram)
      TourDrnDepl, // Tour du dernier d�placement effectu�
      TourArriveDrnArret, // Tour lorsque le tram est arr�t� au dernier arr�t
      TourDepartArretSvt, // Tour pour le d�part vers l'arr�t suivant
      NbCasesParcourues, // Nombre de cases parcourues
      NbCasesParcouruesDepuisDrnArret, // Idem mais remis � 0 � chaque arr�t de tram
      NbToursRepos; // Tours pendant lesquels le tram ne s'est pas d�plac� du fait de la vitesse r�duite
  void Initialise()
   {
    x=-1; y=-1;
    DirAvtDrnDepl=DirDrnDepl=Dir=indefinie;
    NbPersonnes=NbToursRepos=NbCasesParcouruesDepuisDrnArret=NbCasesParcourues=TourArriveDrnArret=TourDepartArretSvt=TourDrnDepl=0L;
    NumDrnArret=NumArretSvt=0;
   };
  tram() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void Place(int x0, int y0) { x=x0; y=y0; };
  void Definit(int NumLigne0, int NumArretSvt0)
   { NumLigne=NumLigne0; NumArretSvt=NumArretSvt0; };
  ~tram() {};
  bool Defini() { return (x>-1)&&(y>-1); };
  void FaitMonterPieton(int NumPietonAFaireMonter);
  void FaitMonterEtDescendre();
  void CalculeProchaineDirection();
  direction ProchaineDirectionAuCarrefour();
  bool PeutPasser();
  int NumeroArretSuivant();
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
class arret_tram // v3.5
 {
  int Numero;
  public:
  int x, y; // Position de la t�te de l'arr�t de tram (indiquant les couleurs de lignes)
  bool Ligne[NBMAXLIGNESBUSTRAM]; // Indique si une ligne de tram passe par cet arr�t (Index-1)
  int NbLignes,
      NumLigne[NBMAXLIGNESBUSTRAM]; // Liste des lignes de tram passant par cet arr�t (Index-1)
  void Initialise();
  arret_tram() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void Definit(int x0, int y0) { x=x0; y=y0; };
  arret_tram(int x0, int y0) { Definit(x0, y0); };
  ~arret_tram() {};
  bool Defini() { return (x>-1)&&(y>-1); };
  void InitialiseInfosLignesTram();
  void AjouteLigneTram(int n);
  AnsiString asListeLignesTram(); 
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
class ligne_tram // v3.5
 {
  int Numero; // Num�ro de la ligne (CoulLigneTram[Numero]=Couleur de la ligne)
  public:
  int NbArrets, // Nb arr�ts de la ligne
      NumArret[NBMAXARRETSBUSTRAMPARLIGNE], // Ordre des arr�ts � effectuer
      NbTrams, // Nb tram de la ligne
      NumTram[NBMAXBUSTRAMPARLIGNE]; // N� des tram de la ligne
  void Initialise();
  ligne_tram() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void AjouteTram(int NumeroTram);
  ~ligne_tram() {};
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
// Classes de GESTION DES TAXIS
//---------------------------------------------------------------------------
class place_taxi // v3.6
 {
  int Numero;
  public:
  int x, y,
      NumFile; // 0 <= NumFile < NbFilesTaxi
  void Initialise() { x=-1; y=-1; NumFile=-1; };
  place_taxi() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  bool Definie() { return (x>-1)&&(y>-1); };
  void Definit(int x0, int y0) { x=x0; y=y0; };
  void DefinitFile(int n) {NumFile=n; };
  ~place_taxi() {};
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
  bool EstQueueFile(); // v3.6
  bool EstTeteFile(); // v3.6
  int PlaceQueueFile(); // Retourne 1+NumPlaceTaxi si elle existe, 0 sinon.
  int PlaceTeteFile(); // Retourne 1+NumPlaceTaxi si elle existe, 0 sinon.
  direction DirPlaceSvtMemeFile(); // Retourne la direction vers laquelle il y a une place de la m�me file
 };
//---------------------------------------------------------------------------
class file_taxi // v3.6
 {
  int Numero;
  public:
  int NumPlaceQueue; // 0 <= NumPlaceQueue < NbPlacesTaxi
  file_taxi() { Numero=0; NumPlaceQueue=-1; };
  void AffecteNumero(int Num) { Numero=Num; };
  void Definit(int NumPlace) { NumPlaceQueue=NumPlace; };
  ~file_taxi() {};
 };
//---------------------------------------------------------------------------
class taxi // v3.6
 {
  int Numero;
  public:
  situation_taxi Situation;
  int x, y,
      NumFile, // 0 <= NumFile < NbFilesTaxi
      NbPersonnes,
      NbCourses,
      TourDrnDepl, // Tour du dernier d�placement effectu�
      TourDepartDrnCourse, // Tour pour le d�part d'une course
      TourDepotDrnCourse, // Tour lors duquel le ou les derniers clients ont �t� d�pos�s
      TourRetourDrnCourse, // Tour du retour � la file (pour attente nouvelle course)
      NbCasesParcourues, // Nombre de cases parcourues
      NbCasesParcouruesDrnCourse, // Idem mais remis � 0 � chaque d�part d'une course
      NbToursRepos; // Tours pendant lesquels le bus ne s'est pas d�plac� du fait de la vitesse r�duite
  direction Dir, DirDrnDepl;
  void Initialise()
   {
    NumFile=x=y=-1;
    DirDrnDepl=Dir=indefinie;
    NbCourses=NbPersonnes=0;
    Situation=stAttente;
    TourDrnDepl=TourDepartDrnCourse=TourDepotDrnCourse=TourRetourDrnCourse=
    NbCasesParcourues=NbCasesParcouruesDrnCourse=NbToursRepos=0;
   };
  taxi() { Numero=0; Initialise(); };
  ~taxi() {};
  void AffecteNumero(int Num) { Numero=Num; };
  void Definit(int f) { NumFile=f; }; // 0 <= f < NbFilesTaxi
  void Place(int x0, int y0) { x=x0; y=y0; };
  void Place(int p); // 0 <= p < NbPlacesTaxi
  void CalculeProchaineDirection();
  direction ProchaineDirectionAuCarrefour();
  bool PeutPasser();
  void DefinitEtPlace(int f, int p) { Definit(f); Place(p); };
  void FaitDescendrePietons();
  void FaitMonterPieton(int NumPietonAFaireMonter);
  int NbPietonsQuiSontMontes(); // retourne true si des pi�tons attendaient et sont mont�s
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
// Classes de GESTION GENERALE de la SIMULATION
//---------------------------------------------------------------------------
class voie
 {
  int x, y;
  public:
  dirposs DirPoss;
  sens_voie_tram SensVoieTram; // v3.5. 0 = aucune voie. Sinon 0<SensVoieTram<64.
  priorite Priorite[4];
  nature Nature; // v3.8. 0 = rien (fond noir), poids fort = type (voies,trottoirs,immeubles), poid faible = d�cors (arbre, pelouse, etc.)
  bool ToutDroit,
       PassagePietons, // v2.0. Si PassagePieton, est perpendiculaire au sens de la route
       PassageBus, // v3.0. Si PassageBus, seuls les bus peuvent franchir la case (et v�hicules prioritaires)
       LigneBus[NBMAXLIGNESBUSTRAM], // v3.0. Si Ligne[i] alors la ligne n�i+1 passe par cette case (visualisation par la fiche param�tres du r�seau de bus UNIQUEMENT)
       LigneTram[NBMAXLIGNESBUSTRAM]; // v3.5. Si Ligne[i] alors la ligne n�i+1 passe par cette case (visualisation par la fiche param�tres du r�seau de tram UNIQUEMENT)
  int NumFeu[4], // >0 si feu �ventuel (=index+1 de cv->Feu)
      NumVehicule, // >0 si v�hicule �ventuel (=index+1 de cv->Vehicule)
      NumBus, // v3.0. >0 si bus �ventuel (=index+1 de cv->Bus)
      NumTram, // v3.5. >0 si tram �ventuel (=index+1 de cv->Tram)
      NumEtape, // >0 si c'est une �tape (=index+1 de cv->etape)
      NumProchVeh, // >0 si un v�hicule doit passer sur la case lors du prochain mouvement
      NumProchBus, // v3.0. >0 si un bus doit passer sur la case lors du prochain mouvement
      NumProchTram, // v3.5. >0 si un tram doit passer sur la case lors du prochain mouvement
      NumProchTaxi, // v3.6. >0 si un taxi doit passer sur la case lors du prochain mouvement
      NbPietons, // v2.0. Nombre de pietons sur cette case
      NumArretBus, // v3.0. >0 si arr�t de bus (=index+1 de cv->ArretBus)
      NumArretTram, // v3.5. >0 si arr�t de tram (=index+1 de cv->ArretTram)
      NumTaxi, // v3.6. >0 si taxi (=index+1 de cv->Taxi)
      NumPlaceTaxi, // v3.6. >0 si taxi (=index+1 de cv->PlaceTaxi)
      NumPieton[NBMAXPIETONSPARCASE]; // v2.0. >0 si un pi�ton est sur la case. Max: 2 pi�tons/case.
  // 2 nids de pointeurs (natifs) : allou�s dans voie donc d�truits dans ~voie()
  int ***DistEtape, // Autant de Distances (en cases) que d'�tapes ssi 2 DirPoss sinon NULL. Natif. v3.5
      // v2.2.7. Statistiques sur les passages de v�hicules.
      // Attente[ed][ea] & Trafic[ed][ea] avec ed=EtapeD�part, ea=EtapeArriv�e
      //  � Si ed=0, Stats par EtapeArriv�e (toute EtapeD�part confondue)
      //  � Si ea=0, Stats par EtapeD�part  (toute EtapeArriv�e confondue)
      //  � Si ed=ea=0, Stats tous v�hicules.
      **Attente,   // v2.2.7. Nombre de tours pendant lesquels un v�hicule est rest� sur la case
      **Trafic,  // v2.2.7. Nombre de v�hicules pass�s par la case
      **DistArretBus, // v3.0. Distance � un arr�t de bus (m�me principe que DistEtape)
      **DistArretTram,// v3.5. Distance � un arr�t de tram (m�me principe que DistEtape mais uniquement quand SensVoieTram>aucune_voie)
      **DistFileTaxi; // v3.6. Distance juqu'� la queue de la file de taxis.
  voie();
  ~voie();
  void Initialise();
  void Initialise(type_voie TypeVoie); // v3.5
  void Definit(int x0, int y0) { x=x0; y=y0; Initialise(); };
  voie *v(direction d); // v3.0
  bool PrepareCalculDistances(); // v3.0 : inclut �galement celui des arr�ts de bus/tram
  bool PrepareCalculAttenteTrafic(); // v2.2.7
  void CalculeProchainVehiculeOuBusOuTramOuTaxi(); // v3.6 (changement de nom : +OuTaxi)
  void DeplaceVehiculeOuBusOuTramOuTaxi(); // v3.6 (changement de nom : +OuTaxi)
  bool PietonPeutAller(direction DirPieton); // v2.0
  bool FaitDescendrePieton(direction DirDescente, int NumPietonAFaireDescendre); // v3.6 (taxis+DirDescente)
  bool AjoutePieton(int NumPietonAAjouter); // v2.0
  bool RetirePieton(int NumPietonARetirer); // v2.0
  void DeplacePietons(); //v2.0
  void RetireArretBus(); // v3.0
  void RetireArretTram(); // v3.5
  void RetirePlaceTaxi(); // v3.6
  bool EstTeteArretBus(); // v3.0
  bool EstTeteArretBus(int NumeroArretBus); // v3.0
  bool EstTeteArretTram(); // v3.5
  bool EstTeteArretTram(int NumeroArretTram); // v3.5
  bool EstTeteBus(); // v3.0
  bool EstTeteTram(); // v3.5
  bool EstQueueFileTaxis(); // v3.6
  bool EstTeteFileTaxis(); // v3.6
  int PlaceQueueFileTaxi(); // v3.6. Retourne 1+NumPlaceTaxi si elle existe, 0 sinon.
  int PlaceTeteFileTaxi(); // v3.6. Retourne 1+NumPlaceTaxi si elle existe, 0 sinon.
  bool ExistePlusieursQueuesFileTaxis(); // v3.6
  bool ExistePlusieursTetesFileTaxis(); // v3.6
  void DefinitArretBus(int n); // v3.0
  void DefinitArretTram(int n); // v3.5
  void RedessineCasesArretBus(direction d0); // v3.0
  void RedessineCasesArretTram(direction d0); // v3.5
  bool EstDepotBus(); // v3.0
  void CalculeDistanceEtape(int e, int DistSansPsgBus, int DistAvecPsgBus, direction DirOrig);
  void CalculeDistanceArretBus(int ab, int Distance, direction DirOrig); // v3.0
  void CalculeDistanceArretTram(int at, int Distance, direction DirOrig); // v3.5
  void CalculeDistanceFileTaxi(int ft, int Distance, direction DirOrig); // v3.6
  void InitialiseInfosLignesBus(); // v3.0
  void InitialiseInfosLignesTram(); // v3.5
  void ModifieSensVoieTram(direction DirOrig, direction DirDest); // v3.5
  direction DirSensVoieTram(direction DirOrigine, int iDir); // v3.5
  bool EstDirPossSensVoieTram(direction DirOrigine, direction DirDestination); // v3.5
  int NumDirPossSensVoieTram(direction DirOrigine, direction DirDestination); // v3.5
  int NbDirPossSensVoieTram(direction DirOrigine); // v3.5
  bool SupprimePassagePietonsInvalide(); // v3.5
  inline bool ExisteVoieDansDirection(type_voie TypeVoie, direction d); // v3.5
  void DefinitNature(nature NvNature, bool Ecraser);
  void TuePietons(); // v4.3. Appel�e par centre_ville::PlaceXXX (XXX = Vehicule, Bus, Tram ou VehiculeTaxi)
  void RedessineCase(bool EffaceFond); // v3.0
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
class stats
 {
  public:
  int NbVehiculesDeplaces,
      NbVehiculesArrives,
      NbVehiculesSortis;
  stats() // v3.5 : manquait un s !!!
   { NbVehiculesDeplaces=NbVehiculesArrives=NbVehiculesSortis=0L; };
  void Definit();
 };
//---------------------------------------------------------------------------
class centre_ville
 {
  void IncrementeAttente(int NumVehicule); // v2.2.7
  void IncrementeTrafic(int NumVehicule); // v2.2.7
  public:
  bool TourEnCours,
       CopieEnCours; // v4.0.1 Copie en cours de la s�lection dans un fichier
  TDateTime dtTop, dtTemps; // v3.9.2
  int NbX, NbY, // v4.0
      TourCrt,
      NbFeux, // Nombre de feux max. pouvant �tre utilis�s
      NbEtapes, // Nombre d'�tapes max. pouvant �tre utilis�s
      NbVehicules,// Nombre de v�hicules g�n�r�s pour la simulation
      NbBus,// v3.0. Nombre de bus g�n�r�s pour la simulation
      NbTrams, // v3.5. Nombre de trams
      NbPietons, // v2.0. Nombre de pi�tons g�n�r�s pour la simulation
      NbArretsBus, // v3.0. Nombre d'arr�ts de bus � utiliser
      NbLignesBus, // v3.0. Nombre de lignes de bus
      NbArretsTram, // v3.5. Nombre d'arr�ts de tram
      NbLignesTram, // v3.5. Nombre de lignes de tram
      NbPlacesTaxi, // v3.6. Nombre de places de taxi
      NbFilesTaxi, // v3.6. Nombre de file de taxi
      NbTaxis, // v3.6. Nombre de taxis (<= Nb.Places de taxi)
      DureeVert, // Dur�e du vert PAR DEFAUT (� la cr�ation d'un feu)
      DureeOrange, // Duree de l'orange dans la simulation;
      DureeRouge, // Dur�e du rouge PAR DEFAUT (� la cr�ation d'un feu)
      xErr, yErr, // Coordonn�es de la case concernant la derni�re erreur
      NbVehiculesDeplaces,
      NbVehiculesArrives,
      NbVehiculesSortis,
      NbToursStats, // Nombre de tours soumis � la statistiques (derniers)
      NbVitesses, // v1.5. Vitesse
      NbMaxCasesDetectPsgPt, // v2.0. Maximum de cases qu'un pi�ton peut contr�ler pour d�tecter un passage pi�tons
      ProbaDirPsgPt, // v2.0. Probabilit� pour un pi�ton de se diriger vers un passage pi�ton en changeant de direction
      NbMaxCasesDetectArretBus, // v3.0. Maximum de cases qu'un pi�ton peut contr�ler pour d�tecter un arret de bus
      NbMaxCasesDetectArretTram, // v3.5. Maximum de cases qu'un pi�ton peut contr�ler pour d�tecter un arret de tram
      NbMaxCasesDetectFileTaxi, // v3.6. Maximum de cases qu'un pi�ton peut contr�ler pour d�tecter une file de taxis
      ProbaDirArretBus,  // v3.0. Probabilit� pour un pi�ton de se diriger vers un arr�t de bus
      ProbaDirArretTram,  // v3.5. Probabilit� pour un pi�ton de se diriger vers un arr�t de tram
      ProbaDirFileTaxi, // v3.6. Probabilit� pour un pi�ton de se diriger vers une file de taxis
      ProbaArretBusDmd, // v3.0. Probabilit� pour un pi�ton de demander � descendre au prochain arr�t de bus
      ProbaArretTramDmd, // v3.5. Probabilit� pour un pi�ton de demander � descendre au prochain arr�t de tram
      ProbaArretTaxiDmd, // v3.6. Probabilit� pour un pi�ton de demander � descendre du taxi
      NbMaxPersonnesBus, // v3.0. Capacit� d'un bus
      NbMaxPersonnesTram, // v3.5. Capacit� d'un tram
      NbMaxPersonnesTaxi, // v3.6. Capacit� d'un taxi
      NbToursStopArretBus, // v3.0. Arr�t obligatoire (tours) � chaque arr�t de bus
      NbToursStopArretTram, // v3.5. Arr�t obligatoire (tours) � chaque arr�t de tram
      NbMaxToursAttenteBus, // v3.0. Nombre max d'attente d'un bus � l'arr�t
      NbMaxToursAttenteTram, // v3.5. Nombre max d'attente d'un tram � l'arr�t
      NbMaxToursAttenteTaxi, // v3.6. Nombre max d'attente d'un taxi
      AttenteMaxVeh,  // Attente max d'un vehicule bloqu� avant choix d'un autre trajet. AttenteMaxVeh/2 pour un pi�ton et 5*AttenteMaxVeh pour un bus.
      NbToursParSeconde, // Vitesse de simulation
      NbCasesParcourues, // Nb total de cases parcourues par tous les v�hicules
      NbToursParcourus, // Nb Total de tours tous v�hicules confondus
      Xc, Yc, NbXc, NbYc; // v4.0.1 Coordonn�es et taille de la s�lection � copier
// DEBUT Propri�t�s pour la g�n�ration al�atoire de r�seau (v4.2)
  int LgrMinSgmtRoute, LgrMaxSgmtRoute, // Longueur de segment (min/max) de route dans une dir. donn�e
      ProbaSortieIntersection,  // en dixi�me : probabilit� de cr�er une nouvelle direction (sortie d'intersection) apr�s chaque segment trac�
      ProbaEntreeIntersection, // en dixi�me : probabilit� de d�boucher sur une route (entr�e d'intersection) apr�s chaque segment trac�
      ProbaTraverseeRoute;      // en dixi�me : probabilit� qu'un segment traverse une route (entr�e + franchissement + sortie d'intersection) 
// FIN Propri�t�s pour la g�n�ration al�atoire de r�seau 
  bool VerifOk, DistancesCalculees, QuadrillageStats;
  type_stats TypeStats;

  voie **v; // Dimensions modifiables (v4.0)
  feu *Feu; // Tableau de feux
  etape *Etape; // Tableau des etapes
  vehicule *Vehicule; // Tableau de voitures
  bus *Bus; // v3.0. Tableau de bus
  tram *Tram; // v3.5. Tableau de trams
  pieton *Pieton; // v2.0. Tableau de pi�tons
  depot_bus DepotBus; // v3.0 : Attention INSTANCE STATIQUE car D�p�t unique !
  arret_bus *ArretBus; // v3.0. Tableau d'arr�ts de bus
  ligne_bus LigneBus[NBMAXLIGNESBUSTRAM]; // v3.0. Tableau (statique) de lignes de bus
  arret_tram *ArretTram; // v3.5. Tableau d'arr�ts de tram
  ligne_tram LigneTram[NBMAXLIGNESBUSTRAM]; // v3.5. Tableau (statique) de lignes de tram
  taxi *Taxi; // v3.6. Tableau de taxis
  place_taxi *PlaceTaxi; // v3.6. Tableau de places de taxis
  file_taxi *FileTaxi; // v3.6. Tableau de files de taxis
  stats *Stats; // Tableau de statistiques
  void CreeZone(); // v4.0 (allocation dynamique si NbX*NbY>0)
  centre_ville(bool NbElementsParDefaut, int NbX, int NbY); // v4.0 (NbX, NbY)
  ~centre_ville();
  int DefinitNbFeux(int n);
  int DefinitNbEtapes(int n);
  int DefinitNbVehicules(int n);
  int DefinitNbBus(int n); // v3.0
  int DefinitNbTrams(int n); // v3.5
  int DefinitNbPietons(int n); // v2.0
  int DefinitNbLignesBus(int n); // v3.0
  int DefinitNbArretsBus(int n); // v3.0
  int DefinitNbLignesTram(int n); // v3.5
  int DefinitNbArretsTram(int n); // v3.5
  int DefinitNbPlacesTaxi(int n); // v3.6
  int DefinitNbFilesTaxi(int n); // v3.6
  int DefinitNbTaxis(int n); // v3.6
  int DefinitFilesTaxi(); // v3.6. Renvoie le nombre de files cr��es. D�fini � partir de PlaceTaxi.
  int NbFeuxLibres();
  int NumeroFeuLibre();
  int NumeroEtapeLibre();
  int NumeroVehiculeLibre();
  int NumeroPietonLibre(); //v2.0
  int ArretBusExistant(int x, int y); // v3.0
  int ArretTramExistant(int x, int y); // v3.5
  int NumeroArretBusLibre(int x, int y); //v3.0
  int NumeroArretTramLibre(int x, int y); //v3.5
  int NumeroPlaceTaxiLibre(); // v3.6
  int AjouteFeu(int x, int y, direction d);
  void SupprimeFeu(int n);
  void SupprimeFeuxVoie(int x, int y, type_voie TypeVoie); // v3.5 (TypeVoie)
  void SupprimeEtapeVoie(int x, int y); // v3.6
  void SupprimeArretBusVoie(int x, int y); // v3.6
  void SupprimeDepotBusVoie(int x, int y); // v3.6
  void SupprimeArretTramVoie(int x, int y); // v3.6
  void SupprimePlaceTaxiVoie(int x, int y); // v3.6
  int AjouteEtape(int x, int y);
  void SupprimeEtape(int n);
  int AjouteArretBus(int x, int y); // v3.0
  int AjouteArretTram(int x, int y); // v3.5
  int AjoutePlaceTaxi(int x, int y); // v3.6
  bool ExisteCaseArretBus(int x, int y); // v3.0
  bool ExisteCaseArretTram(int x, int y); // v3.5
  void SupprimeArretBus(int x, int y); // v3.0. Supprime sur une case seulement
  void SupprimeArretBus(int n); // v3.0. Supprime compl�tement l'arr�t (sur TOUTES les cases)
  void SupprimeArretTram(int x, int y); // v3.5. Supprime sur une case seulement
  void SupprimeArretTram(int n); // v3.5. Supprime compl�tement l'arr�t (sur TOUTES les cases)
  void SupprimePlaceTaxi(int n); // v3.6
  sens SensPassagePietonsPossible(int x, int y); // v3.5
  direction CherchePassagePietons(int x, int y, sens SensRecherche); // v2.0
  direction ChercheArretBus(int x, int y, sens SensRecherche); // v3.0
  direction ChercheArretTram(int x, int y, sens SensRecherche); // v3.5
  direction CherchePlaceTaxi(int x, int y, sens SensRecherche); // v3.6
  void DefinitArretBus(int n, int x, int y); // v3.0
  void DefinitArretTram(int n, int x, int y); // v3.5
  direction DirectionArretBus(int x, int y); // v3.0
  direction DirectionArretTram(int x, int y); // v3.5
  position_arret_bus_tram PositionArretBus(int x, int y, direction d); // v3.0
  position_arret_bus_tram PositionArretTram(int x, int y, direction d); // v3.5
  bool ArretsBusVoisinsDifferents(int x, int y); // v3.0
  bool ArretsTramVoisinsDifferents(int x, int y); // v3.5
  direction DirArretBusVoisin(int x, int y); // v3.0
  direction DirArretTramVoisin(int x, int y); // v3.5
  bool AjoutArretBusPossible(int x, int y); // v3.0
  bool AjoutArretTramPossible(int x, int y); // v3.5
  bool SuppressionArretBusPossible(int x, int y); // v3.0
  bool SuppressionArretTramPossible(int x, int y); // v3.5
  void InitialiseInfosLignesBus(); // v3.0
  void InitialiseInfosLignesTram(); // v3.5
  void InitialiseInfosTrajetLignesBus(); // v3.0
  void InitialiseInfosTrajetLignesTram(); // v3.5
  void CalculeTrajetLignesBus(); // v3.0
  void CalculeTrajetLignesTram(); // v3.5
  bool VerifieCalculDistances(type_distance &TypeDistance); // v3.5 : inclut �galement celui des arr�ts de bus & tram
  bool PrepareCalculDistances(); // v3.5 : inclut �galement celui des arr�ts de bus & tram
  bool PrepareCalculAttenteTrafic(); // v2.2.7
  void PlaceVehicule(int x, int y, int NumVehicule); // v2.2.7
  bool PrepareVehicules();
  void PlaceBus(int x, int y, int NumBus); // v3.0
  void DefinitBus(int NumBus, int NumLigne); // v3.0
  bool PrepareBus(); // v3.0
  void PlaceTram(int x, int y, int NumTram); // v3.5
  void DefinitTram(int NumTram, int NumLigne); // v3.5
  void PlaceVehiculeTaxi(int x, int y, int NumTaxi); // v3.6
  bool PrepareTrams(); // v3.5
  bool PrepareTaxis(); // v3.6. Les taxis ainsi que leurs places et leurs files
  bool PreparePietons(); // v2.0
  void DeplacePieton(int NumPieton, int x, int y, direction d); // v2.0
  bool ChangeDirectionSiPossible(int x, int y, dirposs dp);
  void CalculeDistances();
  void RessuscitePietons(); // v4.3.1
  void __fastcall EffectueTourSimulation();
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
  inline bool TourDeDeplacementVehicule(int NumeroVehicule);
  inline bool TourDeDeplacementBus(int NumeroBus);
  inline bool TourDeDeplacementTram(int NumeroTram); // v3.5
  inline bool TourDeDeplacementTaxi(int NumeroTaxi); // v3.6
  inline void TopChrono() // v3.9.2
   {
#ifdef CV_LINUX
    dtTop=GetTime();
#else
    dtTop=Time();
#endif
   }; 
  inline void StopChrono() // v3.9.2
   {
#ifdef CV_LINUX
    dtTemps+=(GetTime()-dtTop);
#else
    dtTemps+=(Time()-dtTop);
#endif
   };
  bool CopieValide(); // v4.2.1
  void PrepareCopie(bool EnCours, int x, int y, int NbX, int NbY) // v4.0.1
   {
    if (CopieEnCours=EnCours)
     { Xc=x; Yc=y; NbXc=NbX; NbYc=NbY; }
    else
     Xc=Yc=NbXc=NbY=0;
   };
  template <class C> bool DansSelectionEnCours(C *c) // v4.0.1
   {
    return (c->x>=Xc)&&(c->y>=Yc)&&(c->x<Xc+NbXc)&&(c->y<Yc+NbYc);
   };
  template <class C> AnsiString asCoordonnees(C *c) // v4.2.1
   {
    if ((c->x>-1)&&(c->y>-1))
     return "("+IntToStr(c->x)+", "+IntToStr(c->y)+")";
    else
     return "(?, ?)";
   };
  void PrepareGenerationAleatoire( int LgrMinSgmtRoute, int LgrMaxSgmtRoute,
                                   int ProbaSortieIntersection, int ProbaEntreeIntersection,
                                   int ProbaTraverseeRoute) // v4.2
   {
    this->LgrMinSgmtRoute=LgrMinSgmtRoute;
    this->LgrMaxSgmtRoute=LgrMaxSgmtRoute;
    this->ProbaSortieIntersection=ProbaSortieIntersection;
    this->ProbaEntreeIntersection=ProbaEntreeIntersection;
    this->ProbaTraverseeRoute=ProbaTraverseeRoute;
   };
  void Genere(int x, int y, int d); // v4.2
 };
//---------------------------------------------------------------------------
// v3.5 : remplacement des [5] par |NBDIR+1] et des [4] par [NBDIR]
extern const dirposs PossDir[NBDIR+1], InvPossDir[NBDIR+1], RotPossDir[NBDIR][16];
extern const int dxr[NBDIR+1], dyr[NBDIR+1], // v4.0 (const int->int)
                 NbDir[16],
                 NumDirdp[NBDIR+1][16];
extern const sens SensPsgPt[16];
extern const direction Dirdp[NBDIR][16],
                       InvDir[NBDIR+1],
                       AGaucheDe[NBDIR+1],
                       ADroiteDe[NBDIR+1];
extern const sens_voie_tram SensVoieTramDir[NBDIR+1][NBDIR+1]; // v3.5
extern const coin CoinDir[NBDIR+1]; // v3.8
extern const AnsiString asDir[NBDIR+1],
                        asDirPoss[16];
//---------------------------------------------------------------------------
extern bool ParamsInchanges, VerifierApresOuverture, VerifierAvantSimulation;
extern int dx[NBDIR+1], dy[NBDIR+1],
           VersionFichier, // v3.5
           SvgNbFeux, SvgNbEtapes, SvgNbVehicules, SvgNbPietons, SvgNbArretsBus,
           SvgNbArretsTram, // v3.5
           SvgNbPlacesTaxi; // v3.6
//---------------------------------------------------------------------------
extern centre_ville *cv;
//---------------------------------------------------------------------------
extern void AppelleAuChaos();
//---------------------------------------------------------------------------
#endif

