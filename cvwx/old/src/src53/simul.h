//---------------------------------------------------------------------------
#ifndef simulH
#define simulH
//---------------------------------------------------------------------------
#pragma warn -pia // Inhibe "Possibly Incorrect Assignment" (v5.2)
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
#define NBFEUXDEFAUT               2 // v5.1 : anciennement 30
#define NBFEUXPIETONDEFAUT         2 // v5.2
#define NBETAPESDEFAUT             2 // v5.1 : anciennement 4
#define NBVEHICULESDEFAUT        120
#define NBPIETONSDEFAUT           30 // v2.0 (25% des véhicules = 120/4 = 30)
#define NBNIVEAUXPRIORITE          3 // v2.2
#define NBMAXETAPES               32
#define NBMAXVEHICULES          9999 // v5.0.3 - Au lieu de 1000
#define NBMAXPIETONSPARCASE        2 // v2.0
#define NBMAXLIGNESBUSTRAM         9 // v3.5
#define NBMAXARRETSBUSTRAMPARLIGNE 9 // v3.5
#define NBMAXBUSTRAMPARLIGNE       3 // v3.5
#define NBMAXARRETSBUSTRAM         NBMAXLIGNESBUSTRAM*NBMAXARRETSBUSTRAMPARLIGNE // v3.5
#define NBMAXBUSTRAM               NBMAXLIGNESBUSTRAM*NBMAXBUSTRAMPARLIGNE // v3.5
#define NBSENSVOIETRAMBASE         7 // v3.5
#define NBSENSVOIETRAM             64// v3.5 (2^NBSENSVOIETRAMBASE-1=2^6=64)
#define NBTYPESVOIE                2 // v3.5
#define NBSITUATIONSTAXI           4 // v3.6
#define NBFEUXPARCASE              4 // v5.2
#define NBFEUXPIETONSPARNUMERO     2 // v5.2
//---------------------------------------------------------------------------
// valeurs de distance particulières
#define DIST_INDEFINIE  32767
//---------------------------------------------------------------------------
// Filtre pour ne donner que la nature (sans les décors) dans la propriété Nature (poids fort)
#define  NATURE(v)     ((v)->Nature&0x7FFF0000)
#define _NATURE(n)     ((n)&0x7FFF0000)
//---------------------------------------------------------------------------
// 3ème index de voie::DistParking[][][]
#define SANSPSGBUS 0
#define AVECPSGBUS 1
//---------------------------------------------------------------------------
// Index de RotPossDir
#define R90D 1
#define R180 2
#define R90G 3
//---------------------------------------------------------------------------
#define VERSION    0x530 // v3.0. La version change SSI le format de fichiers change (v5.3)
#define VERSIONMIN 0x300 // v3.0. Version minimale stockée : NE PAS MODIFIER
#define VERSIONANC 0x200 // v3.0  Version non stockée compatible : NE PAS MODIFIER
//--------------------------------------------------------------------------- Voie
#define  V(x,y,d) v[((x)+dx[d])%cv->NbX][((y)+dy[d])%cv->NbY] // en dehors de la classe centre_ville (v4.0)
#define _V(x,y,d) v[((x)+dx[d])%NbX][((y)+dy[d])%NbY] // depuis la classe centre_ville (v4.0)
#define  V_(x,y,n,d) v[((x)+(n)*dx[d])%cv->NbX][((y)+(n)*dy[d])%cv->NbY] // en dehors de la classe centre_ville (v4.0)
#define _V_(x,y,n,d) v[((x)+(n)*dx[d])%NbX][((y)+(n)*dy[d])%NbY] // depuis la classe centre_ville (v4.0)
//--------------------------------------------------------------------------- Feux Piétons (v5.2)
#define  FEUXPIETONS(v)    ((v)->NumFeuP[0]+(v)->NumFeuP[1]+(v)->NumFeuP[2]+(v)->NumFeuP[3]>0)
#define _FEUXPIETONS       (NumFeuP[0]+NumFeuP[1]+NumFeuP[2]+NumFeuP[3]>0)
#define  IFEUDIR(n,d)      (cv->FeuP[(n)-1].iFeuDir[d])
#define  IFEUOPPDIR(d)     iFeuDir[InvDir[d]-1]
//---------------------------------------------------------------------------
#define min(x,y) (((x)<(y))?(x):(y))
#define max(x,y) (((x)>(y))?(x):(y))
//---------------------------------------------------------------------------
// Pour centre_ville::PrepareCopie(...)
#define DEBUT true
#define FIN   false
//---------------------------------------------------------------------------
// Version 1.5 : Ajout de la vitesse
//  - Ajout de la propriété NbVitesses dans la classe centre_ville.
//  - Il peut y avoir de 1 à 3 vitesses différentes : 1 case/tour /2 tours ou /3 tours.

// Version 2.0 : Ajout des piétons
//  - Les piétons se déplacent en dehors des voies (endroits noirs) ou sur les passages piétons.
//  - classe pieton
//  - propriété PassagePieton, FeuOpposePietons dans la classe voie.

// Version 2.2 : Ajout des véhicules d'urgence et de police
//  - type enuméré niveau_priorite
//  - propriété niveau_priorite NivPriorite dans la classe vehicule

// Version 3.0 : Ajout des bus
//  - Classes arret_bus, ligne_bus, bus
//  - Propriétés voie::NumArretBus, centre_ville::ArretBus, centre_ville::LigneBus

// Version 3.1 : Activation des couloirs de bus
//  - Utilisation du bouton et de la rubrique Couloir Bus
//  - Utilisation de la propriété PassageBus de la classe voie

// Version 3.5 : Ajout des trams
//  - Classes arret_tram, ligne_tram, tram
//  - Propriétés voie::NumArretTram, centre_ville::ArretTram, centre_ville::LigneTram

// Version 3.6 : Ajout des taxis
//  - Classes place_taxi, file_taxi, taxi
//  - Propriétés voie::NumProchTaxi, voie::NumPlaceTaxi, centre_ville::PlaceTaxi, centre_ville::FileTaxi, centre_ville::Taxi 

// Version 3.8 : Zones délimitées en vue des décors
//  - Zones de circulation, Zones habitables, Zones piétonnes

// Version 3.9 : Premiers décors suivant les zones
//  - toitures, trottoirs, pelouses, arbres

// Version 4.0 : Dimensions de la zone modifiable

// Version 4.2 : Génération aléatoire d'un réseau (voies automobiles seulement)

// version 5.0 : - Naissance des places de parking. Les parkings deviennent des parkings (souterrains)
//               - nouvelles classes place_park, file_park

// version 5.1 : Disparition dans les paramètres du nombre de feux, parkings, arrêts de bus/tram, places de taxis/parkings.
//                 -> Ajout méthode copie et incrémentation automatique transparente.

// version 5.3 : Ajout éléments vehlib, place_vehlib
//---------------------------------------------------------------------------
// types énumérés
//---------------------------------------------------------------------------
enum priorite {a_droite, cedez_le_passage, stop, feux};
enum direction {indefinie, nord, est, sud, ouest};
enum sens {indefini, horizontal, vertical}; // v2.0. Pour les passages piétons
enum dirposs {aucune, N, E, NE, S, NS, SE, NES, O, NO, EO, NEO, SO, NSO, ESO, NESO};
enum diraprendre {gauche, devant, droite};
enum etat_feu {inactif, vert, orange, rouge};
enum dmd_vert {arrivee_vehicule, immediate};
enum psg_rouge {prm_dmd, immediat};
enum type_stats {par_nombre, par_pourcentage};
enum compatibilite {version_inf_16, version_inf_20, version_courante}; // v2.0
enum niveau_priorite {normal, urgence, police}; // v2.2
enum position_arret_bus_tram {tete, milieu, queue}; // v3.5 (ajout de "_tram" au nom du type car communs aux deux types d'arrêt)
enum sens_voie_tram {aucune_voie=0, nord_est=1, nord_sud=2, nord_ouest=4, sud_est=8, est_ouest=16, sud_ouest=32}; // v3.5
enum sens_voie_tram_base {aucune_voie_base, ne, ns, no, se, eo, so};
enum type_distance {type_indefini, parkings, arrets_bus, arrets_tram, files_taxi, files_park, files_vehlib}; // v3.5. v3.6 : Ajout de files_taxi. v5.0 : Ajout de files_park. v5.3 : Ajout de files_vehlib
enum type_voie {tvAucun, tvRoute, tvVoieTram, tvTout}; // pour la suppression des routes et voies de tram. v3.5
enum situation_taxi {stAttente, stDepart, stDepot, stRetour}; // v3.6
enum situation_vehlib {svAttente, svDepart}; // v5.3
enum nature { voies,
              trottoirs=0x10000, arbre=0x10010, pelouse=0x10020,  // Décors zone piétonne (v3.9)
              immeubles=0x20000};
enum coin {aucun_coin, haut_droite, bas_droite, bas_gauche=4, haut_gauche=8, quatre_coins=15}; // v3.8
//---------------------------------------------------------------------------
class pieton // v2.0
 {
  int Numero;
  public:
  int x, y, Dir, DemiCase,
      NumArretBus, // v3.0. Arrêt de bus d'attente (si >0). Le piéton se trouve à côté de cet arrêt (à droite de la tête de l'arrêt de bus)
      NumArretTram, // v3.5. Arrêt de tram d'attente (si >0). Le piéton se trouve à côté de cet arrêt (à droite de la tête de l'arrêt de tram)
      NumFileTaxi, // v3.6. File de taxi d'attente (si >0). Le piéton se trouve à côté de cette file (à droite de la tête de file de taxi)
      NumPlaceVehlib, // v5.3. Place vehlib d'attente (si >0). Le piéton se trouve à côté de cette place avant de monter dans le vehlib
      NumBus, // v3.0. Bus dans lequel se trouve le piéton (si >0. Dans ce cas, x=-1 et y=-1)
      NumTram, // v3.5. Tram dans lequel se trouve le piéton (si >0. Dans ce cas, x=-1 et y=-1)
      NumTaxi, // v3.6. Tram dans lequel se trouve le piéton (si >0. Dans ce cas, x=-1 et y=-1)
      NumVehlib, // v5.3/ Vehlib dans lequel se trouve le piéton (si >0. Dans ce cas, x=-1 et y=-1)
      NumFeuP, // v5.2. Feu piéton au pied duquel le piéton attend pour traverser (>0 si AttendFeuP)
      TourDrnDepl, TourDrnAff,
      TourAttBus, // v3.0. Tour à partir duquel le piéton attend le bus
      TourAttTram, // v3.5. Tour à partir duquel le piéton attend le tram
      TourAttTaxi, // v3.6. Tour à partir duquel le piéton attend le taxi
      DemiCasesParcourues; // v3.0. L'unité de longueur piétonne est la demi-case, pas la case !
  bool PsgPtTrv,
       ArretBusTrv, // v3.0. Arrêt de bus trouvé
       AttendBus,  // v3.0. Attend un bus à l'arret NumArretBus
       ArretTramTrv, // v3.5. Arrêt de tram trouvé
       AttendTram,  // v3.5. Attend un tram à l'arret NumArretTram
       AttendFeuP,  // v5.2. Attend que le feu piéton NumFeuP l'autorise à traverser la voie (tram/route).
       FileTaxiTrv, // v3.5. File de taxi trouvée
       PlaceVehlibTrv, // v5.3. Place de vehlib trouvée
       AttendTaxi,  // v3.5. Attend un taxi à la file NumFileTaxi
       AttendVehlib, // v5.3. Attend un vehlib à la file NumFileVehlib
       VeutDescendre, // v3.0. Indique qu'il veut descendre du bus, du tram ou du taxi
       Ecrase; // v4.3. Indique si ce piéton a été écrasé : Si c'est le cas les coordonnées sont l'endroit du crime 
  void Initialise()
   {
    x=-1; y=-1;
    Dir=indefinie;
    NumVehlib=NumPlaceVehlib=NumFeuP=NumTaxi=NumTram=NumBus=NumFileTaxi=NumArretTram=NumArretBus=DemiCase=0; // v3.6 (NumTaxi, NumFileTaxi), v5.2 (NumFeuP), v5.3 (vehlib)
    DemiCasesParcourues=TourDrnAff=TourDrnDepl=0L;
    Ecrase=VeutDescendre=AttendFeuP=AttendVehlib=AttendTaxi=AttendTram=AttendBus=PlaceVehlibTrv=FileTaxiTrv=ArretTramTrv=ArretBusTrv=PsgPtTrv=false; // v4.3 (Ecrase), v5.2 (AttendFeuP), v5.3 (vehlib)
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
    if (PlaceVehlibTrv) PlaceVehlibTrv=false; // v5.3
   };
  pieton(int x0, int y0, direction Dir0, int DemiCase0) { Definit(x0, y0, Dir0, DemiCase0); };
  ~pieton() {};
  void ChercheFileTaxi(); // v3.6
  bool Defini() { return (x>-1)&&(y>-1); };
  void Verifie(AnsiString &asMsgErr);
  void MonteDansBus(int b) { NumBus=b; AttendBus=false; x=-1; y=-1; }; // v3.6
  void MonteDansTram(int t) { NumTram=t; AttendTram=false; x=-1; y=-1; }; // v3.6
  void MonteDansTaxi(int t) { NumTaxi=t; AttendTaxi=false; NumFileTaxi=0; x=-1; y=-1; }; // v3.6
  void MonteDansVehlib(int v) { NumVehlib=v; AttendVehlib=false; NumPlaceVehlib=0; x=-1; y=-1; }; // v5.3
  void SeFaitEcraser() { Ecrase=true; PsgPtTrv=ArretBusTrv=ArretTramTrv=PlaceVehlibTrv=FileTaxiTrv=AttendVehlib=AttendBus=AttendTram=AttendTaxi=VeutDescendre=false; }; // v4.3. v5.3 (vehlib)
 };
//---------------------------------------------------------------------------
class feu
 {
  bool CopieEnCours; // v5.1
  int Numero; // v5.1 : devenu public
  public:
  int x, y, Dir; // Orientation. Mais il peut y avoir max. 2 feux par case;
  etat_feu Etat, ProchainEtat;
  int NbFeuxDmd, // Nbre de feux demandant le rouge
      NbFeuxAtt,// Nbre de feux devant être rouge pour que celui-ci (this) passe au vert
      NbFeuxPtn, // Nbre de feux piétons liés (v5.2). ATTENTION: défini au lancement de la simulation car le lien est établi depuis les feux de piétons.
      *NumFeuxDmd, // Liste des feux demandant le rouge
      *NumFeuxAtt, // Liste des feux devant être rouge pour que celui-ci (this) passe au vert
      *NumFeuxPtn, // Liste des feux de piétons (v5.2). ATTENTION: définie au lancement de la simulation car le lien est établi depuis les feux de piétons.
      DureeRouge, DureeVert,
      TourDrnChgEtat; // Tour du dernier changement d'état
  dmd_vert TypeDmdVert; // Type de demande du vert : dès l'arrivée d'un vehicule ou dès le passage au rouge
  psg_rouge TypePsgRouge; // Type de passage au rouge : dès la première demande ou à l'unanimité des feux demandeurs
  bool DemandeVert, // Indique qu'il demande le rouge (à ceux qui ont Numero dans FeuxDmd[])
       FeuxTousRouges, // Indique que les feux (FeuxAtt) sont tous rouges
       RougeDemande, // Indique qu'un feu demande le rouge
       ProchainVert, // Indique qu'il est autorisé à passer au vert
       VerifEnCours; // Drapeau pour Verifie()
  void Initialise()
   {
    x=-1; y=-1; Dir=indefinie; ProchainEtat=Etat=inactif;
    TypeDmdVert=arrivee_vehicule;
    TypePsgRouge=prm_dmd;
    DureeVert=DureeRouge=NbFeuxPtn=NbFeuxAtt=NbFeuxDmd=0;
    TourDrnChgEtat=0L;
    ProchainVert=RougeDemande=FeuxTousRouges=DemandeVert=false;
    VerifEnCours=false;
   };
  feu() { Numero=0; Initialise(); NumFeuxPtn=NumFeuxDmd=NumFeuxAtt=NULL; CopieEnCours=false; /*v5.1*/}; // v3.8.2 (NULL) v5.2 (NumFeuP)
  void Copie(feu *f) // v5.1
   {
    f->CopieEnCours=true;
    Numero=f->Numero;
    x=f->x;
    y=f->y;
    Dir=f->Dir;
    Etat=f->Etat;
    ProchainEtat=f->ProchainEtat;
    NbFeuxDmd=f->NbFeuxDmd;
    NbFeuxAtt=f->NbFeuxAtt;
    NbFeuxPtn=f->NbFeuxPtn; // v5.2
    NumFeuxDmd=f->NumFeuxDmd;
    NumFeuxAtt=f->NumFeuxAtt;
    NumFeuxPtn=f->NumFeuxPtn; // v5.2
    DureeRouge=f->DureeRouge;
    DureeVert=f->DureeVert;
    TourDrnChgEtat=f->TourDrnChgEtat;
    TypeDmdVert=f->TypeDmdVert;
    TypePsgRouge=f->TypePsgRouge;
    DemandeVert=f->DemandeVert;
    FeuxTousRouges=f->FeuxTousRouges;
    RougeDemande=f->RougeDemande;
    ProchainVert=f->ProchainVert;
    VerifEnCours=f->VerifEnCours;
   };
  void AffecteNumero(int Num) { Numero=Num; };
  void Definit(int x0, int y0, int Dir0) { x=x0; y=y0; Dir=Dir0; Etat=inactif; };
  ~feu()
   {
    if (!CopieEnCours) // v5.1
     {
      if (NbFeuxDmd) { delete[] NumFeuxDmd; NumFeuxDmd=NULL; }
      if (NbFeuxAtt) { delete[] NumFeuxAtt; NumFeuxAtt=NULL;}
      if (NbFeuxPtn) { delete[] NumFeuxPtn; NumFeuxPtn=NULL;} // v5.2
     }
   };
  bool Defini() { return (x>-1)&&(y>-1)&&(Dir>aucune); };
  void AjouteFeuDmd(int NumNvFeu);
  void AjouteFeuAtt(int NumNvFeu);
  void AjouteFeuPtn(int NumNvFeu); // v5.2
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
class feu_pieton // v5.2
 {
  bool CopieEnCours;
  int Numero;
  public:
  int x[NBFEUXPIETONSPARNUMERO],
      y[NBFEUXPIETONSPARNUMERO],
      Dir[NBFEUXPIETONSPARNUMERO], // Deux feux pitons sont positionnés de part et d'autre d'un passage piétons. NumFeuDir
      iFeuDir[NBDIR]; // (Arch, qu'est-ce qu'y feut dire ?) ...Permet d'avoir directement les coordonnées du feu en fonction de la direction Attention à l'accès : iFeuDir[(direction)d-1]
  etat_feu Etat, ProchainEtat;
  int NbFeux,// Nbre de feux de circulation liés
      *NumFeux, // Liste des feux de circulation liés
      DureeRouge,
      DureeVert,
      DureeTraversee, // Soit 1+2*Cases Passage piéton. Défini quand le feu opposé est placé
      TourDrnChgEtat; // Tour du dernier changement d'état
  dmd_vert TypeDmdVert; // Type de demande du vert : dès l'arrivée d'un vehicule ou dès le passage au rouge
  psg_rouge TypePsgRouge; // Type de passage au rouge : dès la première demande ou à l'unanimité des feux demandeurs
  bool DemandeVert, // Indique qu'il demande le rouge (à ceux qui ont Numero dans NumFeuxPtn[])
       FeuxTousRouges, // Indique que les feux (NumFeux) sont tous rouges
       RougeDemande, // Indique qu'un feu demande le rouge
       ProchainVert, // Indique qu'il est autorisé à passer au vert
       VerifEnCours; // Drapeau pour Verifie()
  void Initialise();
  feu_pieton() { Numero=0; Initialise(); NumFeux=NULL; CopieEnCours=false; };
  void Copie(feu_pieton *f);
  void AffecteNumero(int Num) { Numero=Num; };
  void Definit(int x0, int y0, int Dir0) { x[0]=x0; y[0]=y0; Dir[0]=Dir0; Etat=inactif; };
  void DefinitFeuOppose();
  ~feu_pieton()
   {
    if (!CopieEnCours) // v5.1
     if (NbFeux) { delete[] NumFeux; NumFeux=NULL; }
   };
  bool Defini()
   {
    return (x[0]>-1)&&(y[0]>-1)&&(Dir[0]>aucune)&&
           (x[1]>-1)&&(y[1]>-1)&&(Dir[1]>aucune);
   };
  void AjouteFeu(int NumNvFeu);
  void RetireFeu(int NumFeu);
  void ChangeEtat();
  void DefinitProchainEtat();
  bool PietonAttend();
  void Evolue();
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr, AnsiString asSource);
 };
//---------------------------------------------------------------------------
class parking
 {
  int Numero;
  public:
  int x, y;
  void Initialise() { x=-1; y=-1; };
  parking() { Numero=0; Initialise(); };
  void Copie(parking *p) // v5.1
   {
    Numero=p->Numero;
    x=p->x; y=p->y;
   };
  void AffecteNumero(int Num) { Numero=Num; };
  void Definit(int x0, int y0) { x=x0; y=y0; };
  parking(int x0, int y0) { Definit(x0, y0); };
  ~parking() {};
  bool Defini() { return (x>-1)&&(y>-1); };
  void PlaceProchainVehicule();
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
class voie; // v5.0 : utilisée en paramètre d'une méthode de vehicule
//---------------------------------------------------------------------------
class vehicule
 {
  int Numero;
  public:
  int x, y;
  direction Dir, DirDrnDepl;
  niveau_priorite NivPriorite; // v2.2
  int NumParkingDepart, NumParkingArrivee, // Index-1 de centre_ville::Parking[]
      NumFileParkDepart, NumFileParkArrivee, // v5.0. NumParking{Depart|Arrivee} exclusif avec NumFilePark{Depart|Arrivee}. Index-1 de centre_ville.FilePark[]
      TourDrnDepl, // Tour du dernier déplacement effectué
      TourDepart, // Tour pdt lequel il a été placé sur le parking de départ
      NbCasesParcourues, // Nombre de cases parcourues
      NbToursRepos; // v2.2.4 : Tours pendant lesquels le véhicule ne s'est pas déplacé du fait de la vitesse réduite
  void Initialise()
   {
    x=-1; y=-1;
    DirDrnDepl=Dir=indefinie;
    NivPriorite=normal;
    NbToursRepos/*v2.2.4*/=NbCasesParcourues=TourDepart=TourDrnDepl=0L;
    NumParkingDepart=NumParkingArrivee=0;
    NumFileParkDepart=NumFileParkArrivee=0; // v5.0
   };
  vehicule() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void Place(int x0, int y0) { x=x0; y=y0; };
  void Definit(int x0, int y0, direction Dir0,
               int NumDepart, int NumArrivee,
               int NumFileDepart, int NumFileArrivee, // v5.0
               niveau_priorite NivPriorite0); // v2.2
  ~vehicule() {};
  bool Defini() { return (x>-1)&&(y>-1); };
  bool EstDestination(const voie *v); // v5.0 : indique si v est la case destination (parking ou place de parking)
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
      NbPersonnes, // Correspond aux nombre de Pieton ayant NumBus = Numero (piétons dans le bus)
      TourDrnDepl, // Tour du dernier déplacement effectué
      TourDepart, // Tour pdt lequel il a été placé sur la case du dépot
      TourArriveDrnArret, // Tour lorsque le bus est arrêté au dernier arrêt
      TourDepartArretSvt, // Tour pour le départ vers l'arrêt suivant
      NbCasesParcourues, // Nombre de cases parcourues
      NbCasesParcouruesDepuisDrnArret, // Idem mais remis à 0 à chaque arrêt de bus
      NbToursRepos; // Tours pendant lesquels le bus ne s'est pas déplacé du fait de la vitesse réduite
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
  int x, y; // Position de la tête de l'arrêt de bus (indiquant les couleurs de lignes)
  bool Ligne[NBMAXLIGNESBUSTRAM]; // Indique si une ligne de bus passe par cet arrêt (Index-1)
  int NbLignes,
      NumLigne[NBMAXLIGNESBUSTRAM]; // Liste des lignes de bus passant par cet arrêt (Index-1)
  void Initialise();
  arret_bus() { Numero=0; Initialise(); };
  void Copie(arret_bus *a); // v5.1
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
//---------------------------------------------------------------------------
class ligne_bus // v3.0
 {
  int Numero; // Numéro de la ligne (CoulLigneBus[Numero]=Couleur de la ligne)
  public:
  int NbArrets, // Nb arrêts de la ligne
      NumArret[NBMAXARRETSBUSTRAMPARLIGNE], // Ordre des arrêts à effectuer
      NbBus, // Nb bus de la ligne
      NumBus[NBMAXBUSTRAMPARLIGNE]; // N° des bus de la ligne
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
      NbPersonnes, // Correspond aux nombre de Pieton ayant NumTram = Numero (piétons dans le tram)
      TourDrnDepl, // Tour du dernier déplacement effectué
      TourArriveDrnArret, // Tour lorsque le tram est arrêté au dernier arrêt
      TourDepartArretSvt, // Tour pour le départ vers l'arrêt suivant
      NbCasesParcourues, // Nombre de cases parcourues
      NbCasesParcouruesDepuisDrnArret, // Idem mais remis à 0 à chaque arrêt de tram
      NbToursRepos; // Tours pendant lesquels le tram ne s'est pas déplacé du fait de la vitesse réduite
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
  int x, y; // Position de la tête de l'arrêt de tram (indiquant les couleurs de lignes)
  bool Ligne[NBMAXLIGNESBUSTRAM]; // Indique si une ligne de tram passe par cet arrêt (Index-1)
  int NbLignes,
      NumLigne[NBMAXLIGNESBUSTRAM]; // Liste des lignes de tram passant par cet arrêt (Index-1)
  void Initialise();
  arret_tram() { Numero=0; Initialise(); };
  void Copie(arret_tram *a); // v5.1
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
  int Numero; // Numéro de la ligne (CoulLigneTram[Numero]=Couleur de la ligne)
  public:
  int NbArrets, // Nb arrêts de la ligne
      NumArret[NBMAXARRETSBUSTRAMPARLIGNE], // Ordre des arrêts à effectuer
      NbTrams, // Nb tram de la ligne
      NumTram[NBMAXBUSTRAMPARLIGNE]; // N° des tram de la ligne
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
  void Copie(place_taxi *p)
   {
    Numero=p->Numero;
    x=p->x; y=p->y;
    NumFile=p->NumFile;
   };
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
  direction DirPlaceSvtMemeFile(); // Retourne la direction vers laquelle il y a une place de la même file
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
      NumFile, // 0 <= NumFile < NbTaxis
      NbPersonnes,
      NbCourses,
      TourDrnDepl, // Tour du dernier déplacement effectué
      TourDepartDrnCourse, // Tour pour le départ d'une course
      TourDepotDrnCourse, // Tour lors duquel le ou les derniers clients ont été déposés
      TourRetourDrnCourse, // Tour du retour à la file (pour attente nouvelle course)
      NbCasesParcourues, // Nombre de cases parcourues
      NbCasesParcouruesDrnCourse, // Idem mais remis à 0 à chaque départ d'une course
      NbToursRepos; // Tours pendant lesquels le bus ne s'est pas déplacé du fait de la vitesse réduite
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
  int NbPietonsQuiSontMontes(); // retourne true si des piétons attendaient et sont montés
  void Verifie(AnsiString &asMsgErr);
 };
//---------------------------------------------------------------------------
class place_park // v5.0
 {
  int Numero;
  public:
  int x, y,
      NumFile; // 0 <= NumFile < NbFilesPark. -1 si non défini
  void Initialise() { x=-1; y=-1; NumFile=-1; };
  place_park() { Numero=0; Initialise(); };
  void Copie(place_park *p)
   {
    Numero=p->Numero;
    x=p->x; y=p->y;
    NumFile=p->NumFile;
   };
  void AffecteNumero(int Num) { Numero=Num; };
  bool Definie() { return (x>-1)&&(y>-1); };
  void Definit(int x0, int y0) { x=x0; y=y0; };
  void DefinitFile(int n) {NumFile=n; };
  ~place_park() {};
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
  bool EstQueueFile(); // v3.6
  bool EstTeteFile(); // v3.6
  int PlaceQueueFile(); // Retourne 1+NumPlace si elle existe, 0 sinon.
  int PlaceTeteFile(); // Retourne 1+NumPlace si elle existe, 0 sinon.
 };
//---------------------------------------------------------------------------
class file_park // v5.0
 {
  int Numero;
  public:
  int NumPlaceQueue; // 0 <= NumPlaceQueue < NbPlacesPark. -1 : Place non encore définie
  file_park() { Numero=0; NumPlaceQueue=-1; };
  void AffecteNumero(int Num) { Numero=Num; };
  void Definit(int NumPlace) { NumPlaceQueue=NumPlace; };
  ~file_park() {};
 };
//---------------------------------------------------------------------------
class place_vehlib // v5.3
 {
  int Numero;
  public:
  int x, y;
  int NumVehlibReserve; // si réservé alors > 0 et c'est le n° vehlib (+1) qui a réservé, sinon 0
  void Initialise() { x=-1; y=-1; NumVehlibReserve=0; };
  place_vehlib() { Numero=0; Initialise(); };
  void Copie(place_vehlib *p)
   {
    Numero=p->Numero;
    x=p->x; y=p->y;
    NumVehlibReserve=p->NumVehlibReserve;
   };
  void AffecteNumero(int Num) { Numero=Num; };
  bool Definie() { return (x>-1)&&(y>-1); };
  void Definit(int x0, int y0) { x=x0; y=y0; };
  ~place_vehlib() {};
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
  bool EstLibre();
 };
//---------------------------------------------------------------------------
class vehlib  // v5.3
 {
  int Numero;
  public:
  situation_vehlib Situation;
  int x, y;
  direction Dir, DirDrnDepl;
  int NumPlaceDepart,  // Place de départ. 0 = pas placé sinon index+1 de centre_ville.PlaceVehlib[].
      NumPlaceArrivee, // Place réservée. 0 = pas encore réservé sinon Index+1 de centre_ville.PlaceVehlib[].
      NbPersonnes,
      TourDrnDepl, // Tour du dernier déplacement effectué
      TourDepart, // Tour pdt lequel il a été placé sur le parking de départ
      NbCasesParcourues, // Nombre de cases parcourues
      NbToursRepos; // Tours pendant lesquels le véhicule ne s'est pas déplacé du fait de la vitesse réduite
  void Initialise()
   {
    Situation=svAttente;
    x=-1; y=-1;
    DirDrnDepl=Dir=indefinie;
    NbToursRepos=NbCasesParcourues=TourDepart=TourDrnDepl=0L;
    NumPlaceArrivee=NumPlaceDepart=0;
    NbPersonnes=0;
   };
  vehlib() { Numero=0; Initialise(); };
  void AffecteNumero(int Num) { Numero=Num; };
  void Place(int x0, int y0) { x=x0; y=y0; };
  void Place(int p); // 0 <= p < NbPlacesVehlib
  void Definit(int p) { NumPlaceDepart=p+1; }; // ATTENTION: 0 <= p < NbPlacesVehlib
  void DefinitEtPlace(int p) { Definit(p); Place(p); }; // ATTENTION: 0 <= p < NbPlacesVehlib
  ~vehlib() {};
  bool Defini() { return (x>-1)&&(y>-1); };
  bool EstDestination(const voie *v);
  void CalculeProchaineDirection();
  direction ProchaineDirectionAuCarrefour();
  bool PeutPasser();
  void FaitDescendrePietons();
  void ReservePlaceVehlibCible();
  void FaitMonterPieton(int NumPietonAFaireMonter);
  int NbPietonsQuiSontMontes(); // retourne true si des piétons attendaient et sont montés
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
  nature Nature; // v3.8. 0 = rien (fond noir), poids fort = type (voies,trottoirs,immeubles), poid faible = décors (arbre, pelouse, etc.)
  bool ToutDroit,
       PassagePietons, // v2.0. Si PassagePieton, est perpendiculaire au sens de la route
       PassageBus, // v3.0. Si PassageBus, seuls les bus peuvent franchir la case (et véhicules prioritaires)
       LigneBus[NBMAXLIGNESBUSTRAM], // v3.0. Si Ligne[i] alors la ligne n°i+1 passe par cette case (visualisation par la fiche paramètres du réseau de bus UNIQUEMENT)
       LigneTram[NBMAXLIGNESBUSTRAM]; // v3.5. Si Ligne[i] alors la ligne n°i+1 passe par cette case (visualisation par la fiche paramètres du réseau de tram UNIQUEMENT)
  int NumFeu[NBFEUXPARCASE], // >0 si feu éventuel (=index+1 de cv->Feu) (v5.2: NBFEUXPARCASE)
      NumFeuP[NBFEUXPARCASE],// v5.2. >0 si feu piéton éventuel (=index+1 de cv->FeuP)
      NumVehicule, // >0 si véhicule éventuel (=index+1 de cv->Vehicule)
      NumVehlib, // v5.3 si vehlib éventuel (=index+1 de cv->Vehlib)
      NumBus, // v3.0. >0 si bus éventuel (=index+1 de cv->Bus)
      NumTram, // v3.5. >0 si tram éventuel (=index+1 de cv->Tram)
      NumParking, // >0 si c'est un parking (=index+1 de cv->parking)
      NumProchVeh, // >0 si un véhicule doit passer sur la case lors du prochain mouvement
      NumProchVL,  // >0 si un vehlib doit passer sur la case lors du prochain mouvement
      NumProchBus, // v3.0. >0 si un bus doit passer sur la case lors du prochain mouvement
      NumProchTram, // v3.5. >0 si un tram doit passer sur la case lors du prochain mouvement
      NumProchTaxi, // v3.6. >0 si un taxi doit passer sur la case lors du prochain mouvement
      NbPietons, // v2.0. Nombre de pietons sur cette case
      NumArretBus, // v3.0. >0 si arrêt de bus (=index+1 de cv->ArretBus)
      NumArretTram, // v3.5. >0 si arrêt de tram (=index+1 de cv->ArretTram)
      NumTaxi, // v3.6. >0 si taxi (=index+1 de cv->Taxi)
      NumPlaceTaxi, // v3.6. >0 si taxi (=index+1 de cv->PlaceTaxi)
      NumPlacePark, // v5.0. >0 si place de parking (=index+1 de cv->PlacePark)
      NumPlaceVehlib, // v5.3. >0 si place de vehlib (=index+1 de cv->PlaceVehlib)
      NumSpotVehlib, // v5.3. >0 si spot vehlib (=index+1 de cv->SpotVehlib)
      NumPieton[NBMAXPIETONSPARCASE]; // v2.0. >0 si un piéton est sur la case. Max: 2 piétons/case.
  // 2 nids de pointeurs (natifs) : alloués dans voie donc détruits dans ~voie()
  int ***DistParking, // Autant de Distances (en cases) que de parkings ssi 2 DirPoss sinon NULL. Natif. v3.5
      // v2.2.7. Statistiques sur les passages de véhicules.
      // Attente[ed][ea] & Trafic[ed][ea] avec ed=ParkingDépart, ea=ParkingArrivée
      //  · Si ed=0, Stats par ParkingArrivée (toute ParkingDépart confondue)
      //  · Si ea=0, Stats par ParkingDépart  (toute ParkingArrivée confondue)
      //  · Si ed=ea=0, Stats tous véhicules.
      **Attente,   // v2.2.7. Nombre de tours pendant lesquels un véhicule est resté sur la case
      **Trafic,  // v2.2.7. Nombre de véhicules passés par la case
      **DistArretBus, // v3.0. Distance à un arrêt de bus (même principe que DistParking)
      **DistArretTram,// v3.5. Distance à un arrêt de tram (même principe que DistParking mais uniquement quand SensVoieTram>aucune_voie)
      **DistFileTaxi, // v3.6. Distance juqu'à la queue de la file de taxis.
      ***DistFilePark, // v5.0. Distance juqu'à la queue de la file parkings.
      **DistPlaceVehlib;// v5.3. Distance jusqu'à une place de vehlib (pas de notion de priorité d'où le ** au lieu de ***).
  voie();
  ~voie();
  void Initialise();
  void Initialise(type_voie TypeVoie); // v3.5
  void Definit(int x0, int y0) { x=x0; y=y0; Initialise(); };
  voie *v(direction d); // v3.0
  bool PrepareCalculDistances(); // v3.0 : inclut également celui des arrêts de bus/tram
  bool PrepareCalculAttenteTrafic(); // v2.2.7
  void CalculeProchainVehiculeOuBusOuTramOuTaxiOuVehlib(); // v3.6 (changement de nom : +OuTaxi) v5.3 (changement de nom : +OuVehlib)
  void DeplaceVehiculeOuBusOuTramOuTaxi(); // v3.6 (changement de nom : +OuTaxi)
  bool PietonPeutAller(direction DirPieton); // v2.0
  bool FaitDescendrePieton(direction DirDescente, int NumPietonAFaireDescendre); // v3.6 (taxis+DirDescente)
  bool AjoutePieton(int NumPietonAAjouter); // v2.0
  bool RetirePieton(int NumPietonARetirer); // v2.0
  void DeplacePietons(); //v2.0
  void RetireArretBus(); // v3.0
  void RetireArretTram(); // v3.5
  void RetirePlaceTaxi(); // v3.6
  void RetirePlacePark(); // v5.0
  void RetirePlaceVehlib(); // v5.3
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

  bool EstQueueFilePark(); // v5.0
  bool EstTeteFilePark(); // v5.0
  int PlaceQueueFilePark(); // v5.0. Retourne 1+NumPlace si elle existe, 0 sinon.
  int PlaceTeteFilePark(); // v5.0. Retourne 1+NumPlace si elle existe, 0 sinon.
  bool ExistePlusieursQueuesFilePark(); // v5.0
  bool ExistePlusieursTetesFilePark(); // v5.0

  bool EstQueueFileVehlibs(); // v5.3
  bool EstTeteFileVehlibs(); // v5.3
  int PlaceQueueFileVehlib(); // v5.3. Retourne 1+NumPlaceVehlib si elle existe, 0 sinon.
  int PlaceTeteFileVehlib(); // v5.3. Retourne 1+NumPlaceVehlib si elle existe, 0 sinon.
  bool ExistePlusieursQueuesFileVehlibs(); // v5.3
  bool ExistePlusieursTetesFileVehlibs(); // v5.3
  int OrientationPlaceVehlib(); // v5.3 : Permet d'orienter l'image de la place selon l'orientation de la file !

  void DefinitArretBus(int n); // v3.0
  void DefinitArretTram(int n); // v3.5
  void RedessineCasesArretBus(direction d0); // v3.0
  void RedessineCasesArretTram(direction d0); // v3.5
  bool EstDepotBus(); // v3.0

  void CalculeDistanceParking(int e, int DistSansPsgBus, int DistAvecPsgBus, direction DirOrig);
  void CalculeDistanceArretBus(int ab, int Distance, direction DirOrig); // v3.0
  void CalculeDistanceArretTram(int at, int Distance, direction DirOrig); // v3.5
  void CalculeDistanceFileTaxi(int ft, int Distance, direction DirOrig); // v3.6
  void CalculeDistanceFilePark(int fp, int DistSansPsgBus, int DistAvecPsgBus, direction DirOrig); // v5.0
  void CalculeDistancePlaceVehlib(int pv, int Distance, direction DirOrig); // v5.3
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
  void TuePietons(); // v4.3. Appelée par centre_ville::PlaceXXX (XXX = Vehicule, Bus, Tram, VehiculeTaxi ou VehiculeVehlib v5.3)
  bool FeuPietonsPossible(); //v5.2
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
       CopieEnCours; // v4.0.1 Copie en cours de la sélection dans un fichier
  TDateTime dtTop, dtTemps; // v3.9.2
  int NbX, NbY, // v4.0
      TourCrt,
      NbFeux, // Nombre de feux max. pouvant être utilisés
      NbFeuxPieton, // v5.2. Nombre de feux pietons max. pouvant être utilisés
      NbParkings, // Nombre de parkings max. pouvant être utilisés
      NbVehicules,// Nombre de véhicules générés pour la simulation
      NbVehlibs, // v5.3. Nombre de vehlib générés pour la simulation
      NbBus,// v3.0. Nombre de bus générés pour la simulation
      NbTrams, // v3.5. Nombre de trams
      NbPietons, // v2.0. Nombre de piétons générés pour la simulation
      NbArretsBus, // v3.0. Nombre d'arrêts de bus à utiliser
      NbLignesBus, // v3.0. Nombre de lignes de bus
      NbArretsTram, // v3.5. Nombre d'arrêts de tram
      NbLignesTram, // v3.5. Nombre de lignes de tram
      NbPlacesTaxi, // v3.6. Nombre de places de taxi
      NbFilesTaxi, // v3.6. Nombre de file de taxi
      NbTaxis, // v3.6. Nombre de taxis (<= Nb.Places de taxi)
      NbPlacesPark, // v5.0. Nombre de places de parking
      NbFilesPark, // v5.0. Nombre de files de parkings
      NbPlacesVehlib, // v5.3. Nombre de places de vehlib
      DureeVert, // Durée du vert PAR DEFAUT (à la création d'un feu)
      DureeOrange, // Duree de l'orange dans la simulation;
      DureeRouge, // Durée du rouge PAR DEFAUT (à la création d'un feu)
      xErr, yErr, // Coordonnées de la case concernant la dernière erreur
      NbVehiculesDeplaces,
      NbVehiculesArrives,
      NbVehiculesSortis,
      NbToursStats, // Nombre de tours soumis à la statistiques (derniers)
      NbVitesses, // v1.5. Vitesse
      NbMaxCasesDetectPsgPt, // v2.0. Maximum de cases qu'un piéton peut contrôler pour détecter un passage piéton
      ProbaDirPsgPt, // v2.0. Probabilité pour un piéton de se diriger vers un passage piéton en changeant de direction
      NbMaxCasesDetectArretBus, // v3.0. Maximum de cases qu'un piéton peut contrôler pour détecter un arret de bus
      NbMaxCasesDetectArretTram, // v3.5. Maximum de cases qu'un piéton peut contrôler pour détecter un arret de tram
      NbMaxCasesDetectFileTaxi, // v3.6. Maximum de cases qu'un piéton peut contrôler pour détecter une file de taxis
      NbMaxCasesDetectFileVehlib, // v5.3. Maximum de cases qu'un piéton peut contrôler pour détecter une file de vehlibs
      ProbaDirArretBus,  // v3.0. Probabilité pour un piéton de se diriger vers un arrêt de bus
      ProbaDirArretTram,  // v3.5. Probabilité pour un piéton de se diriger vers un arrêt de tram
      ProbaDirFileTaxi, // v3.6. Probabilité pour un piéton de se diriger vers une file de taxis
      ProbaDirFileVehlib, // v5.3. Probabilité pour un piéton de se diriger vers une file de vehlibs
      ProbaArretBusDmd, // v3.0. Probabilité pour un piéton de demander à descendre au prochain arrêt de bus
      ProbaArretTramDmd, // v3.5. Probabilité pour un piéton de demander à descendre au prochain arrêt de tram
      ProbaArretTaxiDmd, // v3.6. Probabilité pour un piéton de demander à descendre du taxi
      TauxRemplissageVehlib, // v5.3. Taux de remplissage des places de vehlib au début de la simulation (88% par défaut : 1/1 jusqu'à 4/4 puis 4/5, 5/6 pour que des places soient libres pour les premiers vehlibs pris...) 
      NbMaxPersonnesBus, // v3.0. Capacité d'un bus
      NbMaxPersonnesTram, // v3.5. Capacité d'un tram
      NbMaxPersonnesTaxi, // v3.6. Capacité d'un taxi
      NbMaxPersonnesVehlib, // v5.3. Capacité d'un vehlib
      NbToursStopArretBus, // v3.0. Arrêt obligatoire (tours) à chaque arrêt de bus
      NbToursStopArretTram, // v3.5. Arrêt obligatoire (tours) à chaque arrêt de tram
      NbMaxToursAttenteBus, // v3.0. Nombre max d'attente d'un bus à l'arrêt
      NbMaxToursAttenteTram, // v3.5. Nombre max d'attente d'un tram à l'arrêt
      NbMaxToursAttenteTaxi, // v3.6. Nombre max d'attente d'un taxi
      AttenteMaxVeh,  // Attente max d'un vehicule bloqué avant choix d'un autre trajet. AttenteMaxVeh/2 pour un piéton et 5*AttenteMaxVeh pour un bus.
      NbToursParSeconde, // Vitesse de simulation
      NbCasesParcourues, // Nb total de cases parcourues par tous les véhicules
      NbToursParcourus, // Nb Total de tours tous véhicules confondus
      Xc, Yc, NbXc, NbYc; // v4.0.1 Coordonnées et taille de la sélection à copier
// DEBUT Propriétés pour la génération aléatoire de réseau (v4.2)
  int LgrMinSgmtRoute, LgrMaxSgmtRoute, // Longueur de segment (min/max) de route dans une dir. donnée
      ProbaSortieIntersection,  // en dixième : probabilité de créer une nouvelle direction (sortie d'intersection) après chaque segment tracé
      ProbaEntreeIntersection, // en dixième : probabilité de déboucher sur une route (entrée d'intersection) après chaque segment tracé
      ProbaTraverseeRoute;      // en dixième : probabilité qu'un segment traverse une route (entrée + franchissement + sortie d'intersection)
// FIN Propriétés pour la génération aléatoire de réseau
  bool VerifOk, DistancesCalculees, QuadrillageStats;
  type_stats TypeStats;

  voie **v; // Dimensions modifiables (v4.0)
  feu *Feu; // Tableau de feux
  feu_pieton *FeuP; // v5.2 Tableau de feux piéton
  parking *Parking; // Tableau des parkings
  vehicule *Vehicule; // Tableau de voitures
  vehlib *Vehlib; // v5.3. Tableau de vehlib
  bus *Bus; // v3.0. Tableau de bus
  tram *Tram; // v3.5. Tableau de trams
  pieton *Pieton; // v2.0. Tableau de piétons
  depot_bus DepotBus; // v3.0 : Attention INSTANCE STATIQUE car Dépôt unique !
  arret_bus *ArretBus; // v3.0. Tableau d'arrêts de bus
  ligne_bus LigneBus[NBMAXLIGNESBUSTRAM]; // v3.0. Tableau (statique) de lignes de bus
  arret_tram *ArretTram; // v3.5. Tableau d'arrêts de tram
  ligne_tram LigneTram[NBMAXLIGNESBUSTRAM]; // v3.5. Tableau (statique) de lignes de tram
  taxi *Taxi; // v3.6. Tableau de taxis
  place_taxi *PlaceTaxi; // v3.6. Tableau de places de taxis
  file_taxi *FileTaxi; // v3.6. Tableau de files de taxi
  place_park *PlacePark; // v5.0. Tableau de places de parking
  file_park *FilePark; // v5.0. Tableau de files de parkings
  place_vehlib *PlaceVehlib; // v5.3. Tableau de places de vehlib
  stats *Stats; // Tableau de statistiques
  void CreeZone(); // v4.0 (allocation dynamique si NbX*NbY>0)
  centre_ville(bool NbElementsParDefaut, int NbX, int NbY); // v4.0 (NbX, NbY)
  ~centre_ville();
  int DefinitNbFeux(int n);
  int DefinitNbFeuxPietons(int n); // v5.2
  int DefinitNbParkings(int n);
  int DefinitNbVehicules(int n);
  int DefinitNbVehlibs(int n); // v5.3
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
  int DefinitFilesTaxi(); // v3.6. Renvoie le nombre de files créées. Défini à partir de PlaceTaxi.

  int DefinitNbPlacesPark(int n); // v5.0
  int DefinitNbFilesPark(int n); // v5.0
  int DefinitFilesPark(); // v5.0. Renvoie le nombre de files créées. Défini à partir de PlacePark.

  int DefinitNbPlacesVehlib(int n); // v5.3

  int NbFeuxLibres();
  int NumeroFeuLibre();
  int NumeroFeuPietonsLibre(); // v5.2
  int NumeroParkingLibre();
  int NumeroVehiculeLibre();
  int NumeroVehlibLibre(); // v5.3
  int NumeroPietonLibre(); //v2.0
  int ArretBusExistant(int x, int y); // v3.0
  int ArretTramExistant(int x, int y); // v3.5
  int NumeroArretBusLibre(int x, int y); //v3.0
  int NumeroArretTramLibre(int x, int y); //v3.5
  int NumeroPlaceTaxiLibre(); // v3.6
  int NumeroPlaceParkLibre(); // v5.0. v5.3 renommée de NumeroPlaceLibre pour ne pas confondre avec NumeroPlaceVehlibLibre()
  int NumeroPlaceVehlibLibre(); // v5.3
  int AjouteFeu(int x, int y, direction d);
  int AjouteFeuPietons(int x, int y, direction d); // v5.2
  void SupprimeFeu(int n);
  void SupprimeFeuPietons(int n); // v5.2
  void SupprimeFeuxVoie(int x, int y, type_voie TypeVoie); // v3.5 (TypeVoie)
  void SupprimeParkingVoie(int x, int y); // v3.6
  void SupprimeArretBusVoie(int x, int y); // v3.6
  void SupprimeDepotBusVoie(int x, int y); // v3.6
  void SupprimeArretTramVoie(int x, int y); // v3.6
  void SupprimePlaceTaxiVoie(int x, int y); // v3.6
  void SupprimePlaceParkVoie(int x, int y); // v5.0. v5.3 : Renommée de SupprimePlaceVoie pour ne pas confondre avec SupprimePlaceVehlibVoie(x, y)
  void SupprimePlaceVehlibVoie(int x, int y); // v5.3
  int AjouteParking(int x, int y);
  void SupprimeParking(int n);
  int AjouteArretBus(int x, int y); // v3.0
  int AjouteArretTram(int x, int y); // v3.5
  int AjoutePlaceTaxi(int x, int y); // v3.6
  int AjoutePlacePark(int x, int y); // v5.0, v5.1 : ancien nom AjoutePlace
  int AjoutePlaceVehlib(int x, int y); // v5.3
  bool ExisteCaseArretBus(int x, int y); // v3.0
  bool ExisteCaseArretTram(int x, int y); // v3.5
  void SupprimeArretBus(int x, int y); // v3.0. Supprime sur une case seulement
  void SupprimeArretBus(int n); // v3.0. Supprime complètement l'arrêt (sur TOUTES les cases)
  void SupprimeArretTram(int x, int y); // v3.5. Supprime sur une case seulement
  void SupprimeArretTram(int n); // v3.5. Supprime complètement l'arrêt (sur TOUTES les cases)
  void SupprimePlaceTaxi(int n); // v3.6
  void SupprimePlacePark(int n); // v5.0. v5.3 renommée de SupprimePlace(n) pour distinguer avec SupprimePlaceVehlib(n)
  void SupprimePlaceVehlib(int n); // v5.3
  sens SensPassagePietonsPossible(int x, int y); // v3.5
  direction CherchePassagePietons(int x, int y, sens SensRecherche); // v2.0
  direction ChercheArretBus(int x, int y, sens SensRecherche); // v3.0
  direction ChercheArretTram(int x, int y, sens SensRecherche); // v3.5
  direction CherchePlaceTaxi(int x, int y, sens SensRecherche); // v3.6
  direction CherchePlaceVehlib(int x, int y, sens SensRecherche); // v5.3
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
  bool VerifieCalculDistances(type_distance &TypeDistance); // v3.5 : inclut également celui des arrêts de bus & tram
  bool PrepareCalculDistances(); // v3.5 : inclut également celui des arrêts de bus & tram
  bool PrepareCalculAttenteTrafic(); // v2.2.7
  void PlaceVehicule(int x, int y, int NumVehicule); // v2.2.7
  bool PrepareVehicules();
  void PlaceBus(int x, int y, int NumBus); // v3.0
  void DefinitBus(int NumBus, int NumLigne); // v3.0
  bool PrepareBus(); // v3.0
  void PlaceTram(int x, int y, int NumTram); // v3.5
  void DefinitTram(int NumTram, int NumLigne); // v3.5
  void PlaceVehiculeTaxi(int x, int y, int NumTaxi); // v3.6
  void PlaceVehiculeVehlib(int x, int y, int NumVehlib); // v5.3
  bool PrepareTrams(); // v3.5
  bool PrepareTaxis(); // v3.6. Les taxis ainsi que leurs places et leurs files
  bool PrepareVehlibs(); // v5.3. Les vehlibs ainsi que leurs places et leurs files
  bool PreparePietons(); // v2.0
  void DeplacePieton(int NumPieton, int x, int y, direction d); // v2.0
  bool ChangeDirectionSiPossible(int x, int y, dirposs dp);
  void CalculeDistances();
  void RessuscitePietons(); // v4.3.1
  void PlaceVehiculesSurPlacesPark(); // v5.0
  void PlaceVehlibsSurPlaces(); // v5.3
  bool ExisteFeuPietons(int x, int y); //v5.2
  void PrepareFeuxPietons(); // v5.2
  bool FeuPietonsPossible(int x, int y, direction d); //v5.2
  bool PassagePietonFranchissable(int x, int y, direction d); // v5.2
  void __fastcall EffectueTourSimulation();
  bool Charge(int hfile);
  bool Sauve(int hfile);
  void Verifie(AnsiString &asMsgErr);
  inline bool TourDeDeplacementVehicule(int NumeroVehicule);
  inline bool TourDeDeplacementVehlib(int NumeroVehlib);
  inline bool TourDeDeplacementBus(int NumeroBus);
  inline bool TourDeDeplacementTram(int NumeroTram); // v3.5
  inline bool TourDeDeplacementTaxi(int NumeroTaxi); // v3.6
  inline void TopChrono() // v3.9.2
   {
    dtTop=Time();
   };
  inline void StopChrono() // v3.9.2
   {
    dtTemps+=(Time()-dtTop);
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
extern bool VerifierApresOuverture, VerifierAvantSimulation;
extern int dx[NBDIR+1], dy[NBDIR+1],
           VersionFichier, // v3.5
           SvgNbFeux, SvgNbParkings, SvgNbVehicules, SvgNbPietons, SvgNbArretsBus,
           SvgNbArretsTram, // v3.5
           SvgNbPlacesTaxi; // v3.6
//---------------------------------------------------------------------------
extern centre_ville *cv;
//---------------------------------------------------------------------------
extern void AppelleAuChaos();
extern template <class E> int IncrementeNombre(E **e, int &n); // v5.1
//---------------------------------------------------------------------------
#endif

