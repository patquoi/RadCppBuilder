(******************************************************************************
CENTRE-VILLE pour Linux

Copyright (C) 2001 Patrice FOUQUET

Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le
modifier conformément aux dispositions de la Licence Publique Générale GNU,
telle que publiée par la Free Software Foundation ; version 2 de la licence,
ou encore toute version ultérieure.

Ce programme est distribué dans l'espoir qu'il sera utile,
mais SANS AUCUNE GARANTIE ; sans même la garantie implicite de COMMERCIALISATION
ou D'ADAPTATION A UN OBJET PARTICULIER. Pour plus de détail,
voir la Licence Publique Générale GNU.

Vous devez avoir reçu un exemplaire de la Licence Publique Générale GNU en même
temps que ce programme ; si ce n'est pas le cas,
écrivez à la Free Software Foundation Inc.,
675 Mass Ave, Cambridge, MA 02139, Etats-Unis.

Pour toutes informations:
mailto:fouquetp@francenet.fr
http://persoweb.francenet.fr/~fouquetp

-------------------------------------------------------------------------------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************)

unit simul;

interface

// Différences avec le projet cvw (C++Builder) :
// La façon d'écrire vient de l'adaptation du projet C++Builder d'origine :
// - les identificateurs EN MAJUSCULES sont d'anciens #define
// - les types en minuscules sont d'anciens enum ou des classes de la simulation
// - les types avec l'initiale en majuscule sont les types du langage (Pascal)

// Des identificateurs de propriétés de classes ont pris le pluriel car
// n'ayant pas de différence Min/Maj ils n'ont pas pu garder le même nom !
// Exemples : centre_ville.Vehicules : array of vehicule,
//            centre_ville.Pietons : array of pieton, etc.
// Idem pour la macro NBDIR -> NBDIRS pour pas confondre avec la propriété voie.NbDir

// Les tableaux dynamiques d'entités élémentaires de la simulation (véhicules,
// piétons, feux etc.) ne sont pas détruits puis alloués mais sont adaptés au
// besoin. Les types sont des tableaux dynamiques réalloués par SetLength.

// Les références temporaires d'éléments de simulation (voie*, pieton*, etc)
// sont ici des pointeurs de type ^voie, ^pieton (pVoie, pPieton), etc.
// Pour les références de voie, les macros V(x,y,d) et V_(x,y,n,d) ont été
// respectivement transformées en fonctions
// vxyd(x,y : Integer; d : direction) : pVoie et
// vxynd(x,y,n : Integer; d : direction) : pVoie.

// VERSION 3.0 : Ajout des bus
// - Classes depot_bus, arret_bus, ligne_bus & bus
// - Propriétés case.NumArretBus, centre_ville.ArretBus, centre_ville.LigneBus et centre_ville.Autobus

// ----------------------------------------------------------------------------
// MACROS #define devenues Constantes
// ----------------------------------------------------------------------------
const   VERSION=$300;    // v3.0. La version change SSI le format de fichiers change
        VERSIONMIN=$300; // v3.0. Version minimum stockée : NE PAS MODIFIER
        VERSIONANC=$200; // v3.0. Version non stockée compatible : NE PAS MODIFIER
        NBX=99;
        NBY=63;
        NBDIRS=4;

        NBFEUXDEFAUT=30;
        NBETAPESDEFAUT=4;
        NBVEHICULESDEFAUT=120;
        NBPIETONSDEFAUT=30;
        NBNIVEAUXPRIORITE=3;

        NBMAXETAPES=32;
        NBMAXVEHICULES=1000;
        NBMAXPIETONSPARCASE=2;

        NBMAXLIGNESBUS=9;         // v3.0
        NBMAXARRETSBUSPARLIGNE=9; // v3.0
        NBMAXBUSPARLIGNE=3;       // v3.0
        NBMAXARRETSBUS=NBMAXLIGNESBUS*NBMAXARRETSBUSPARLIGNE; // v3.0
        NBMAXBUS=NBMAXLIGNESBUS*NBMAXBUSPARLIGNE; // v3.0

        PEUT_ETRE_INDEFINI=true;
        DOIT_ETRE_DEFINI=false;

// valeurs de distance particulières
        DIST_INDEFINIE=32767;

//      AUCUN_FEU ((x=-1)&&(y=-1)&&(Dir=indefinie))
//      REMET_A_ZERO Definit(-1, -1, 0)

//      MIN(x,y) (((x)<(y))?(x):(y))

// RotPossDir
        R90D=1;
        R180=2;
        R90G=3;
// ----------------------------------------------------------------------------
// Types énumérés de la simulation
// ----------------------------------------------------------------------------
type priorite = (a_droite, cedez_le_passage, stop, feux);
     direction = (indefinie, nord, est, sud, ouest);
     sens = (indefini, horizontal, vertical);
     dirposs = (aucune, N, E, NE, S, NS, SE, NES, O, NO, EO, NEO, SO, NSO, ESO, NESO);
     diraprendre = (gauche, devant, droite);
     etat_feu = (inactif, vert, orange, rouge);
     dmd_vert = (arrivee_vehicule, immediate);
     psg_rouge = (prm_dmd, immediat);
     type_stats = (par_nombre, par_pourcentage);
     niveau_priorite = (normal, urgence, police);
     position_arret_bus = (tete, milieu, queue);
     pVoie = ^voie;
     pPieton = ^pieton;
     pVehicule = ^vehicule;
     pFeu = ^feu;
     pEtape = ^etape;
     pBus = ^bus; // v3.0
     pArretBus = ^arret_bus; // v3.0
     ArrayInt = array of Integer;
// ----------------------------------------------------------------------------
// Classes de la simulation
// ----------------------------------------------------------------------------
pieton = class
 private
  Numero : Integer;
 public
  x, y, DemiCase,
  NumArretBus, // v3.0. Arrêt de bus d'attente (si >0). Le piéton se trouve à côté de cet arrêt
  NumBus,      // v3.0. Bus dans lequel se trouve le piéton (si >0. Dans ce cas, x=-1 et y=-1)
  TourDrnDepl, TourDrnAff,
  TourAttBus, // v3.0. Tour à partir duquel le piéton attend le bus
  DemiCasesParcourues : Integer; // v3.0 : Unité piétonne = 1 demi-case !
  Dir : direction;
  PsgPtTrv,
  ArretBusTrv,             // v3.0. Arrêt de bus trouvé (comme PsgPtTrv)
  AttendBus,               // v3.0. Attend un bus à l'arrêt NumBus 
  VeutDescendre : Boolean; // v3.0. Indique qu'il veut descendre du bus au prochain arrêt
  procedure Initialise;
  constructor Create(Num : Integer); overload;
  procedure AffecteNumero(Num : Integer);
  procedure Place(x0, y0 : Integer);
  procedure Definit(x0, y0 : Integer; Dir0 : direction; DemiCase0 : Integer);
  procedure AnnuleRechercheEnCours; // v3.0
  destructor Destroy; override;
  function Defini : Boolean;
  procedure Verifie(var stMsgErr : String);
end{class pieton};
// ----------------------------------------------------------------------------
feu = class
 private
  Numero : Integer;
 public
  x, y : Integer; // Orientation. Mais il peut y avoir max. 2 feux par case;
  Dir : direction;
  Etat, ProchainEtat : etat_feu;
  NbFeuxDmd, // Nbre de feux demandant le rouge
  NbFeuxAtt : Integer;// Nbre de feux devant être rouge pour que celui-ci (this) passe au vert
  NumFeuxDmd, // Liste des feux demandant le rouge
  NumFeuxAtt : Array of Integer; // Liste des feux devant être rouge pour que celui-ci (this) passe au vert
  TypeDmdVert : dmd_vert; // Type de demande du vert : dès l'arrivée d'un vehicule ou dès le passage au rouge
  TypePsgRouge : psg_rouge; // Type de passage au rouge : dès la première demande ou à l'unanimité des feux demandeurs
  DureeRouge,
  DureeVert,
  TourDrnChgEtat : Integer; // Tour du dernier changement d'état
  DemandeVert, // Indique qu'il demande le rouge (à ceux qui ont Numero dans FeuxDmd[])
  FeuxTousRouges, // Indique que les feux (FeuxAtt) sont tous rouges
  RougeDemande, // Indique qu'un feu demande le rouge
  ProchainVert, // Indique qu'il est autorisé à passer au vert
  VerifEnCours : Boolean; // Drapeau pour Verifie

  procedure Initialise;
  constructor Create(Num : Integer);
  procedure AffecteNumero(Num : Integer);
  procedure Definit(x0, y0 : Integer; Dir0 : direction);
  destructor Destroy; override;
  function Defini : Boolean;
  function DefinitNbFeuxDmd(n : Integer) : Integer;
  function DefinitNbFeuxAtt(n : Integer) : Integer;
  procedure AjouteFeuDmd(NumNvFeu : Integer);
  procedure AjouteFeuAtt(NumNvFeu : Integer);
  procedure RetireFeuDmd(NumFeu : Integer);
  procedure RetireFeuAtt(NumFeu : Integer);
  procedure ChangeEtat;
  procedure DefinitProchainEtat;
  procedure Evolue;
  function Charge(hfile : Integer) : Boolean;
  function Sauve(hfile : Integer) : Boolean;
  procedure Verifie(var stMsgErr : String; stSource : String);
end{class feu};
// ----------------------------------------------------------------------------
// On gère un tableau de points de rendez-vous car la simulation va en utiliser un nombre donné
etape = class
 private
  Numero : Integer;
 public
  x, y : Integer;

  procedure Initialise;
  constructor Create(Num : Integer); overload;
  procedure AffecteNumero(Num : Integer);
  procedure Definit(x0, y0 : Integer);
  constructor Create(x0, y0 : Integer); overload;
  destructor Destroy; override;
  function Definie : Boolean;
  procedure PlaceProchainVehicule;
  function Charge(hfile : Integer) : Boolean;
  function Sauve(hfile : Integer) : Boolean;
  procedure Verifie(var stMsgErr : String);
end{class etape};
// ----------------------------------------------------------------------------
// On gère un tableau de véhicule car la simulation va en utiliser un nombre fixe
vehicule = class
 private
  Numero : Integer;
 public
  x, y : Integer;
  Dir, DirDrnDepl : direction;
  NivPriorite : niveau_priorite;
  NumEtapeDepart, NumEtapeArrivee : Integer; // Index de cv.Etape
  TourDrnDepl, // Tour du dernier déplacement effectué
  TourDepart, // Tour pdt lequel il a été placé sur l'étape de départ
  NbCasesParcourues, // Nombre de cases parcourues
  NbToursRepos : Integer; // v2.2.4 : Tours pendant lesquels le véhicule ne s'est pas déplacé du fait de la vitesse réduite

  procedure Initialise;
  constructor Create(Num : Integer);
  procedure AffecteNumero(Num : Integer);
  procedure Place(x0, y0 : Integer);
  procedure Definit(x0, y0 : Integer; Dir0 : direction; NumDepart, NumArrivee : Integer; NivPriorite0 : niveau_priorite);
  destructor Destroy; override;
  function Defini : Boolean;
  procedure CalculeProchaineDirection;
  function ProchaineDirectionAuCarrefour : direction;
  function PeutPasser : Boolean;
  procedure Verifie(var stMsgErr : String);
end{class vehicule};
// ----------------------------------------------------------------------------
depot_bus = class // v3.0. ATTENTION : il n'y en a qu'un !
 private
 public
  x, y, NumDrnBusSorti : Integer;
  procedure Initialise;
  procedure Definit(x0, y0 : Integer);
  constructor Create;
  destructor Destroy; override;
  function Defini : Boolean;
  procedure PlaceProchainBus;
  function Charge(hfile : Integer) : Boolean;
  function Sauve(hfile : Integer) : Boolean;
  procedure Verifie(var stMsgErr : String);
end{class depot_bus};
// ----------------------------------------------------------------------------
bus = class // v3.0
 private
  Numero : Integer;
 public
  x, y, NumLigne,
  NumDrnArret, NumArretSvt, // Index-1 de centre_ville.ArretBus
  NbPersonnes,  // Nombre de piétons ayant NumBus = Numero (piétons dans le bus)
  TourDrnDepl, // Tour du dernier déplacement effectué
  TourDepart,  // Tour pendant lequel il a été placé sur la case du dépôt
  TourArriveDrnArret, // Tour pendant lequel le bus est arrivé au dernier arrêt
  TourDepartArretSvt,  // Tour pour le départ vers l'arrêt suivant
  NbCasesParcourues, // Nombre de cases parcourues
  NbCasesParcouruesDepuisDrnArret, // Idem mais remis à zéro à chaque arrêt
  NbToursRepos : Integer; // Nombre de tours pendant lesquels le bus ne s'est pas déplacé du fait de sa vitesse réduite
  Dir, DirDrnDepl, DirAvtDrnDepl : direction;
  procedure Initialise;
  constructor Create(Num : Integer);
  destructor Destroy; override;
  procedure AffecteNumero(Num : Integer);
  procedure Place(x0, y0 : Integer);
  procedure Definit(NumLigne0, NumArretSvt0 : Integer);
  function Defini : Boolean;
  procedure FaitMonterPieton(NumPietonAFaireMonter : Integer);
  procedure FaitMonterEtDescendre;
  procedure CalculeProchaineDirection;                    
  function ProchaineDirectionAuCarrefour : direction;
  function PeutPasser : Boolean;
  function NumeroArretSuivant : Integer;
  procedure Verifie(var stMsgErr : String);
end{class bus};
// ----------------------------------------------------------------------------
arret_bus = class // v3.0
 private
  Numero : Integer;
 public
  x, y, NbLignes : Integer;
  Ligne : array [0..NBMAXLIGNESBUS-1] of Boolean; // Indique si une ligne passe par cet arrêt (Index-1)
  NumLigne : array [0..NBMAXLIGNESBUS-1] of Integer; // Liste des lignes passant par cet arrêt (Index-1)
  procedure Initialise;
  procedure AffecteNumero(Num : Integer);
  procedure Definit(x0, y0 : Integer);
  constructor Create(x0, y0 : Integer); overload;
  constructor Create(Num : Integer); overload;
  destructor Destroy; override;
  function Defini : Boolean;
  procedure InitialiseInfosLignesBus;
  procedure AjouteLigneBus(n : Integer);
  function stListeLignesBus : String; // v3.0.5
  function Charge(hfile : Integer) : Boolean;
  function Sauve(hfile : Integer) : Boolean;
  procedure Verifie(var stMsgErr : String);
end{class arret_bus};
// ----------------------------------------------------------------------------
ligne_bus = class // v3.0
 private
  Numero : Integer;
 public
  NbArrets, NbBus : Integer; // Nombre d'arrêts et de bus de la ligne
  NumArret : Array [0..NBMAXARRETSBUSPARLIGNE-1] of Integer; // Ordre des arrêts à effectuer
  NumBus : Array [0..NBMAXBUSPARLIGNE-1] of Integer; // N° des bus de la ligne
  procedure Initialise;
  constructor Create(Num : Integer);
  destructor Destroy; override;
  procedure AffecteNumero(Num : Integer);
  procedure AjouteBus(NumeroBus : Integer);
  function Charge(hfile : Integer) : Boolean;
  function Sauve(hfile : Integer) : Boolean;
  procedure Verifie(var stMsgErr : String);
end{class ligne_bus};
// ----------------------------------------------------------------------------
voie = class
 private
  x, y : Integer;
  DejaVenu : Boolean;
 public
  DirPoss : dirposs;
  Priorites : array [0..3] of priorite;
  ToutDroit,
  PassagePietons, // Si PassagePieton, est perpendiculaire au sens de la route
  PassageBus : Boolean; // v3.0. non-opérationnel dans cette version (false)
  LigneBus : Array [0..NBMAXLIGNESBUS-1] of Boolean; // v3.0. Si Ligne[i] alors la ligne n°i+1 passe par cette case (visualisation par fiche paramètres du réseau de bus UNIQUEMENT)

  NumFeu : array [0..3] of Integer; // >0 si feu éventuel (=index+1 de cv.Feux)
  NumVehicule, // >0 si véhicule éventuel (=index+1 de cv.Vehicules)
  NumBus, // v3.0. >0 si bus éventuel (=index+1 de cv.Autobus)
  NumEtape, // >0 si c'est une étape (=index+1 de cv.Etape)
  NumProchVeh, // >0 si un véhicule doit passer sur la case lors du prochain mouvement
  NumProchBus, // v3.0. >0 si un bus doit passer sur la case lors du prochain mouvement
  NbPietons, // Nombre de pietons sur cette case
  NumArretBus : Integer; // v3.0. >0 si arrêt de bus (=index+1 de cv.ArretsBus)
  NumPieton : array [0..NBMAXPIETONSPARCASE-1] of Integer; // >0 si un piéton est sur la case. Max. 4 piétons par case.
  // 2 nids de pointeurs (natifs) : alloués dans voie donc détruits dans ~voie
  DistEtape, // Autant de Distances (en cases) que d'étapes ssi 2 DirPoss sinon NULL. Natif.
  // v2.2.7 : Statistiques sur les passages de véhicules
  // Attente[ed,ea] & Trafic[ed,ea] avec ed=EtapeDépart;ea=EtapeArrivée
  // - Si ed=0, stats par EtapeArrivée (toute EtapeDépart confondue)
  // - Si ea=0, stats par EtapeDépart (toute EtapeArrivée confondue)
  // - Si ed=ea=0, stats tous véhicules
  DistArretBus, // v3.0. Distance à un arrêt de bus (même principe que DistEtape)
  Attente,
  Trafic    : array of ArrayInt;

  constructor Create(x0, y0 : Integer);
  destructor Destroy; override;
  procedure Initialise;
  procedure Definit(x0, y0 : Integer);
  function v(d : direction) : pVoie; // v3.0 
  function PrepareCalculDistances : Boolean; // v3.0 : inclut également celui des arrêts de bus
  function PrepareCalculAttenteTrafic : Boolean; // v2.2.7
  procedure CalculeProchainVehiculeOuBus; // v3.0 (anciennement CalculeProchainVehicule : inclut le prochain bus le cas échéant)
  procedure DeplaceVehiculeOuBus; // v3.0 (anciennement DeplaceVehicule : inclut le bus le cas échéant)
  function PietonPeutAller(DirPieton : direction) : Boolean;
  function FaitDescendrePieton(NumPietonAFaireDescendre : Integer) : Boolean; // v3.0
  function AjoutePieton(NumPietonAAjouter : Integer) : Boolean;
  function RetirePieton(NumPietonARetirer : Integer) : Boolean;
  procedure DeplacePietons;
  procedure RetireArretBus; // v3.0
  function EstTeteArretBus : Boolean; overload; // v3.0
  function EstTeteArretBus(NumeroArretBus : Integer) : Boolean; overload; // v3.0
  function EstTeteBus : Boolean;
  procedure DefinitArretBus(n : Integer); // v3.0
  procedure RedessineCasesArretBus(d0 : direction); // v3.0
  function EstDepotBus : Boolean; // v3.0
  procedure CalculeDistanceEtape(e, Distance : Integer; DirOrig : direction); // v3.0. Anciennement CalculDistance. Pour différencier Etape et Arrêts de bus
  procedure CalculeDistanceArretBus(ab, Distance : Integer; DirOrig : direction); // v3.0. Pour différencier Arrêts de bus et Etape
  procedure InitialiseInfosLignesBus; // v3.0
  procedure RedessineCase(EffaceFond : Boolean); // v3.0
  function Charge(hfile : Integer) : Boolean;
  function Sauve(hfile : Integer) : Boolean;
  procedure Verifie(var stMsgErr : String);
end{class voie};
// ----------------------------------------------------------------------------
stats = class
 public
  NbVehiculesDeplaces,
  NbVehiculesArrives,
  NbVehiculesSortis : Integer;
  constructor Create;
  procedure Definit;
end{class stats};
// ----------------------------------------------------------------------------
centre_ville = class
 private
  procedure IncrementeAttente(NumVehicule : Integer); // v2.2.7
  procedure IncrementeTrafic(NumVehicule : Integer); // v2.2.7
 public
  TourEnCours : Boolean;
  TourCrt,
  NbFeux, // Nombre de feux max. pouvant être utilisés
  NbEtapes, // Nombre d'étapes max. pouvant être utilisés
  NbVehicules,// Nombre de véhicules générés pour la simulation
  NbBus, // v3.0. Nombre de bus générés pour la simulation
  NbPietons, // Nombre de piétons générés pour la simulation
  NbArretsBus, // v3.0. Nombre d'arrêts de bus à utiliser
  NbLignesBus, // v3.0. Nombre de lignes de bus
  DureeVert, // Durée du vert PAR DEFAUT (à la création d'un feu)
  DureeOrange, // Duree de l'orange dans la simulation;
  DureeRouge, // Durée du rouge PAR DEFAUT (à la création d'un feu)
  xErr, yErr, // Coordonnées de la case concernant la dernière erreur
  NbVehiculesDeplaces,
  NbVehiculesArrives,
  NbVehiculesSortis,
  NbToursStats, // Nombre de tours soumis à la statistiques (derniers)
  NbVitesses, // Vitesse
  NbMaxCasesDetectPsgPt, // Maximum de cases qu'un piéton peut contrôler pour détecter un passage piétons
  ProbaDirPsgPt, // Probabilité pour un piéton de se diriger vers un passage piéton en changeant de direction
  NbMaxCasesDetectArretBus, // v3.0. Maximum de cases qu'un piéton peut contrôler pour détecter un arrêt de bus
  ProbaDirArretBus, // v3.0. Probabilité pour un piéton de se diriger vers un arrêt de bus en changeant de direction
  ProbaArretBusDmd, // v3.0. Probabilité pour un piéton de demander à descendre au prochain arrêt
  NbMaxPersonnesBus, // v3.0. Capacité d'un bus
  NbToursStopArretBus, // v3.0. Arrêt obligatoire (en tours) à chaque arrêt de bus
  NbMaxToursAttenteBus, // v3.0. Nombre maximum de tours pour un piéton à attendre un bus à un arrêt  
  AttenteMaxVeh,  // Attente max d'un vehicule bloqué avant choix d'un autre trajet
  NbToursParSeconde, // Vitesse de simulation
  NbCasesParcourues, // Nb total de cases parcourues par tous les véhicules
  NbToursParcourus : Integer; // Nb Total de tours tous véhicules confondus
  VerifOk, DistancesCalculees, QuadrillageStats : Boolean;
  TypeStats : type_stats;
  v : array [0..NBX-1, 0..NBY-1] of voie; // Dimensions fixées (800x600)...
  Feux : array of feu; // Tableau de feux
  Etapes : array of etape; // Tableau des etapes
  Vehicules : array of vehicule; // Tableau de voitures
  Autobus : array of bus; // v3.0. Tableau de bus
  Pietons : array of pieton; // Tableau de piétons
  DepotBus : depot_bus; // v3.0. LE Dépôt de bus
  ArretsBus : array of arret_bus; // v3.0. Tableau d'arrêts de bus
  LignesBus : array [0..NBMAXLIGNESBUS-1] of ligne_bus; // v3.0. Tableau STATIQUE de lignes de bus
  StatsCV : array of stats; // Tableau de statistiques
  constructor Create(NbElementsParDefaut : Boolean);
  destructor Destroy; override;
  function vxyd(x, y : Integer; d : direction) : pVoie;
  function vxynd(x, y, n : Integer; d : direction) : pVoie;
  function DefinitNbFeux(n : Integer) : Integer;
  function DefinitNbEtapes(n : Integer) : Integer;
  function DefinitNbVehicules(n : Integer; Prepare : Boolean) : Integer; // v3.0.4
  function DefinitNbBus(n : Integer; Prepare : Boolean) : Integer; // v3.0.4
  function DefinitNbPietons(n : Integer; Prepare : Boolean) : Integer; // v3.0.4
  function DefinitNbLignesBus(n : Integer) : Integer; // v3.0
  function DefinitNbArretsBus(n : Integer) : Integer; // v3.0
  function NbFeuxLibres : Integer;
  function NumeroFeuLibre : Integer;
  function NumeroEtapeLibre : Integer;
  function NumeroVehiculeLibre : Integer;
  function NumeroPietonLibre : Integer;
  function ArretBusExistant(x, y : Integer) : Integer; // v3.0
  function NumeroArretBusLibre(x, y : Integer) : Integer; // v3.0
  function AjouteFeu(x, y : Integer; d : direction) : Integer;
  procedure SupprimeFeu(n : Integer);
  procedure SupprimeFeuxVoie(x, y : Integer);
  function AjouteEtape(x, y : Integer) : Integer;
  procedure SupprimeEtape(n : Integer);
  function AjouteArretBus(x, y : Integer) : Integer; // v3.0
  function ExisteCaseArretBus(x, y : Integer) : Boolean; // v3.0
  procedure SupprimeArretBus(x, y : Integer); overload; // v3.0. Supprime sur une case UNIQUEMENT
  procedure SupprimeArretBus(n : Integer); overload; // v3.0. Supprime COMPLETEMENT l'arrêt de bus (TOUTES les cases)
  function SensPassagePietonsPossible(x, y : Integer) : sens;
  function CherchePassagePietons(x, y : Integer; SensRecherche : sens; var NvDir : direction) : direction;
  function ChercheArretBus(x, y : Integer; SensRecherche : sens; var NvDir : direction) : direction; // v3.0. Comme pour le passage piéton
  procedure DefinitArretBus(n, x, y : Integer); // v3.0
  function DirectionArretBus(x, y : Integer) : direction; // v3.0
  function PositionArretBus(x, y : Integer; d : direction) : position_arret_bus; // v3.0
  function ArretsBusVoisinsDifferents(x, y : Integer) : Boolean; // v3.0
  function DirArretBusVoisin(x, y : Integer) : direction; // v3.0
  function AjoutArretBusPossible(x, y : Integer) : Boolean; // v3.0
  function SuppressionArretBusPossible(x, y : Integer) : Boolean; // v3.0
  procedure InitialiseInfosLignesBus; // v3.0
  procedure InitialiseInfosTrajetLignesBus; // v3.0
  procedure CalculeTrajetLignesBus; // v3.0.3
  function VerifieCalculDistances : Boolean; // v3.0. Inclut celui des arrêts de bus
  function PrepareCalculDistances : Boolean; // v3.0. Inclut celui des arrêts de bus
  function PrepareCalculAttenteTrafic : Boolean; // v2.2.7
  procedure PlaceVehicule(x, y, NumVehicule : Integer); // v2.2.7
  function PrepareVehicules : Boolean;
  procedure PlaceBus(x, y, NumBus : Integer); // v3.0
  procedure DefinitBus(NumBus, NumLigne : Integer); // v3.0
  function PrepareBus : Boolean; // v3.0
  function PreparePietons : Boolean;
  procedure DeplacePieton(NumPieton, x, y : Integer; d : direction);
  function ChangeDirectionSiPossible(x, y : Integer; dp : dirposs) : Boolean;
  procedure CalculeDistances; // v3.0
  procedure EffectueTourSimulation;
  function Charge(hfile : Integer) : Boolean;
  function Sauve(hfile : Integer) : Boolean;
  procedure Verifie(var stMsgErr : String);
  function TourDeDeplacementVehicule(NumeroVehicule : Integer) : Boolean; // v3.0.4 (chgt de nom)
  function TourDeDeplacementBus(NumeroBus : Integer) : Boolean; // v3.0
end{class centre_ville};
// ----------------------------------------------------------------------------
// Constantes & Variables globales
// ----------------------------------------------------------------------------
const PossDir :     array [direction] of dirposs = (aucune, N, E, S, O);
      InvPossDir :  array [direction] of dirposs = (aucune, S, O, N, E);

      RotPossDir :  array [0..3, dirposs] of dirposs = // 1=+90° 2=180° 3=-90°
       ((aucune, N, E, NE, S, NS, SE, NES, O, NO, EO, NEO, SO, NSO, ESO, NESO),
        (aucune, E, S, SE, O, EO, SO, ESO, N, NE, NS, NES, NO, NEO, NSO, NESO),
        (aucune, S, O, SO, N, NS, NO, NSO, E, SE, EO, ESO, NE, NES, NEO, NESO),
        (aucune, O, N, NO, E, EO, NE, NEO, S, SO, NS, NSO, SE, ESO, NES, NESO));

      NbDir :       array [dirposs] of Integer = (0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4);
       // NumDirdp[direction, dirposs] = Ordre de direction dans dirposs
       // 0 <= NumDirdp[direction, dirposs] < NbDir[direction, dirposs]
      NumDirdp :    array [direction, dirposs] of Integer =
       ((0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0), // indefinie
        (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0), // nord
        (0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1), // est
        (0,0,0,0,0,1,1,2,0,0,0,0,0,1,1,2), // sud
        (0,0,0,0,0,0,0,0,0,1,1,2,1,2,2,3));// ouest
      dx :          array [direction] of Integer = (0, 0, 1, 0, NBX-1);
      dy :          array [direction] of Integer = (0, NBY-1, 0, 1, 0);
      dxr :         array [direction] of Integer = (0, 0, 1, 0, -1);
      dyr :         array [direction] of Integer = (0, -1, 0, 1, 0);

// SensPsgPt[dirposs] = indefini|horizontal|vertical. v2.0
      SensPsgPt :   array [dirposs] of sens =
       (indefini,   horizontal, vertical, indefini,
        horizontal, horizontal, indefini, indefini,
        vertical, indefini, vertical, indefini,
        indefini, indefini, indefini, indefini);

// (Dirdp[x, y] = (x+1)ème direction pour DirPoss=y
      Dirdp :       array [0..3, dirposs] of direction =
       ((indefinie,  nord,   est,  nord,   sud,  nord,   est,  nord,
             ouest,  nord,   est,  nord,   sud,  nord,   est,  nord),
        (indefinie,indefinie,indefinie,   est,indefinie,   sud,   sud,   est,
         indefinie,    ouest,    ouest,   est,    ouest,   sud,   sud,   est),
        (indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,   sud,
         indefinie,indefinie,indefinie,    ouest,indefinie,    ouest,    ouest,   sud),
        (indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,
         indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,indefinie,    ouest));

      InvDir :      array [direction] of direction = (indefinie, sud, ouest, nord, est);
      AGaucheDe :   array [direction] of direction = (indefinie, ouest, nord, est, sud);
      ADroiteDe :   array [direction] of direction = (indefinie, est, sud, ouest, nord);

      stDir :       array [direction] of String = ('', 'Nord', 'Est', 'Sud', 'Ouest');
      stDirPoss :   array [dirposs] of String =
       ('', 'Nord', 'Est', 'Nord+Est',
        'Sud', 'Nord+Sud', 'Est+Sud', 'Nord+Est+Sud',
        'Ouest', 'Nord+Ouest', 'Est+Ouest', 'Nord+Est+Ouest',
        'Sud+Ouest', 'Nord+Sud+Ouest', 'Est+Sud+Ouest', 'Nord+Est+Sud+Ouest');

// Constante pour PrepareNb... ( ..., Prepare : Boolean) : Integer;
    DEFINIT_ET_PREPARE : Boolean = true;
    DEFINIT_SEULEMENT : Boolean =false;

var ParamsInchanges, VerifierApresOuverture, VerifierAvantSimulation : Boolean;
    VersionFichier : Integer; // v3.0

    cv : centre_ville;

implementation


uses SysUtils, QForms, QControls, QGrids,

     simul_f, infveh_f, rech_f, stats_f, infbus_f, infptn_f;


// ----------------------------------------------------------------------------

// Passage des #define V(x,y,d) et V_(x,y,n,d) en méthodes de centre_ville
// ----------------------------------------------------------------------------
function centre_ville.vxyd(x, y : Integer; d : direction) : pVoie;
begin
 Result:=@(v[(x+dx[d]) mod NBX, ((y)+dy[d]) mod NBY]);
end;
// ----------------------------------------------------------------------------
function centre_ville.vxynd(x, y, n : Integer; d : direction) : pVoie;
begin
 Result:=@(v[(x+n*dx[d]) mod NBX, (y+n*dy[d]) mod NBY]);
end;
// ----------------------------------------------------------------------------
// Routines diverses toutes classes
// ----------------------------------------------------------------------------
procedure VerifiePosition(stMsgErr, stSource : String ; x, y : Integer; PeutEtreIndefinie : Boolean);
 begin
  if (((x<-1) and (PeutEtreIndefinie)) or
      ((x<0) and (not PeutEtreIndefinie)) or
      (x>=NBX)) then
   stMsgErr:=stMsgErr+stSource+Format(': abscisse incorrecte (%d)'#13#10'', [x]);
  if (((y<-1) and (PeutEtreIndefinie)) or
      ((y<0) and (not PeutEtreIndefinie)) or
      (y>=NBY)) then
   stMsgErr:=stMsgErr+stSource+Format(': ordonnée incorrecte (%d)'#13#10'', [y]);
 end;
// ----------------------------------------------------------------------------
procedure VerifieDirection(stMsgErr, stSource : String ; d : direction ; PeutEtreIndefinie : Boolean);
 begin
  if (((d<indefinie) and (PeutEtreIndefinie)) or
      ((d<=indefinie) and (not PeutEtreIndefinie)) or
      (d>ouest)) then
   stMsgErr:=stMsgErr+stSource+Format(': direction incorrecte (%d)'#13#10'', [Integer(d)]);
 end;
// ----------------------------------------------------------------------------
procedure VerifiePriorite(stMsgErr, stSource : String ; p : priorite);
 begin
  if ((p<a_droite) or (p>feux)) then
   stMsgErr:=stMsgErr+stSource+Format(': priorité incorrecte (%d)'#13#10'', [Integer(p)]);
 end;
// ----------------------------------------------------------------------------
procedure VerifieDirPoss(stMsgErr, stSource : String ; dp : dirposs);
 begin
  if ((dp<aucune) or (dp>NESO)) then
   stMsgErr:=stMsgErr+stSource+Format(': directions possibles incorrectes (%d)'#13#10'', [Integer(dp)]);
 end;
// ----------------------------------------------------------------------------
procedure VerifieEtat(stMsgErr, stSource : String ; e : etat_feu);
 begin
  if ((e<inactif) or (e>rouge)) then
   stMsgErr:=stMsgErr+stSource+Format(': état incorrect (%d)'#13#10'', [Integer(e)]);
 end;
// ----------------------------------------------------------------------------
procedure VerifieDmdVert(stMsgErr, stSource : String ; dv : dmd_vert);
 begin
  if ((dv<arrivee_vehicule) or (dv>immediate)) then
   stMsgErr:=stMsgErr+stSource+Format(': type de demande du vert incorrect (%d)'#13#10'', [Integer(dv)]);
 end;
// ----------------------------------------------------------------------------
procedure VerifiePsgRouge(stMsgErr, stSource : String ; pr : psg_rouge);
 begin
  if ((pr<prm_dmd) or (pr>immediat)) then
   stMsgErr:=stMsgErr+stSource+Format(': type de passage au rouge incorrect (%d)'#13#10'', [Integer(pr)]);
 end;
//-----------------------------------------------------------------------------
// Classe Piétons

// ----------------------------------------------------------------------------

procedure pieton.Initialise;

 begin
 x:=-1; y:=-1;
 Dir:=indefinie; DemiCase:=0;
 DemiCasesParcourues:=0;
 TourDrnAff:=0; TourDrnDepl:=0;
 PsgPtTrv:=false;
 end;
// ----------------------------------------------------------------------------
constructor pieton.Create(Num : Integer);
 begin
 AffecteNumero(Num);
 Initialise;
 end;
// ----------------------------------------------------------------------------
procedure pieton.AffecteNumero(Num : Integer);
 begin
 Numero:=Num;
 end;
// ----------------------------------------------------------------------------
procedure pieton.Place(x0, y0 : Integer);
 begin
 x:=x0; y:=y0;
 DemiCase:=0;
 end;
// ----------------------------------------------------------------------------
procedure pieton.Definit(x0, y0 : Integer; Dir0 : direction; DemiCase0 : Integer);
 begin
 x:=x0; y:=y0; Dir:=Dir0;
 DemiCase:=DemiCase0;
 TourDrnAff:=0; TourDrnDepl:=0;
 PsgPtTrv:=false;
 end;
// ----------------------------------------------------------------------------
procedure pieton.AnnuleRechercheEnCours;
 begin
  if PsgPtTrv then PsgPtTrv:=false;
  if ArretBusTrv then ArretBusTrv:=false;
 end;
// ----------------------------------------------------------------------------
destructor pieton.Destroy;
begin
end;
// ----------------------------------------------------------------------------
function pieton.Defini : Boolean;
 begin
 Result:=(x>-1) and (y>-1);
 end;
// ----------------------------------------------------------------------------
procedure pieton.Verifie(var stMsgErr : String);
 var  stSource : String;
 begin
 stSource:=Format('Piéton n°%d (%d,%d)', [Numero, x, y]);
 if (Numero<0) then
  stMsgErr:=stMsgErr+stSource+Format(': numéro incorrect (%d)'#13#10'', [Numero]);
  VerifiePosition(stMsgErr, stSource, x, y, DOIT_ETRE_DEFINI);
  VerifieDirection(stMsgErr, stSource, Dir, DOIT_ETRE_DEFINI);
  if ((DemiCase<0) or (DemiCase>1)) then
   stMsgErr:=stMsgErr+stSource+Format(': valeur ½ case incorrecte (%d)'#13#10'', [DemiCase]);
 end;
// ----------------------------------------------------------------------------
// Classe Feux
// ----------------------------------------------------------------------------
procedure feu.Initialise;
begin
 x:=-1; y:=-1; Dir:=indefinie;
 ProchainEtat:=inactif; Etat:=inactif;
 TypeDmdVert:=arrivee_vehicule;
 TypePsgRouge:=prm_dmd;
 DureeVert:=0; DureeRouge:=0; NbFeuxAtt:=0; NbFeuxDmd:=0;
 TourDrnChgEtat:=0;
 ProchainVert:=false; RougeDemande:=false;
 FeuxTousRouges:=false; DemandeVert:=false;
 VerifEnCours:=false;
end{feu.Initialise};
// ----------------------------------------------------------------------------
constructor feu.Create(Num : Integer);
 begin
 AffecteNumero(Num);
 Initialise;
 end;
// ----------------------------------------------------------------------------
procedure feu.AffecteNumero(Num : Integer);
 begin
 Numero:=Num;
 end;
// ----------------------------------------------------------------------------
procedure feu.Definit(x0, y0 : Integer; Dir0 : direction);
 begin
 x:=x0; y:=y0;
 Dir:=Dir0; Etat:=inactif;
 end;
// ----------------------------------------------------------------------------
destructor feu.Destroy;
begin
end;
// ----------------------------------------------------------------------------
function feu.Defini : Boolean;
 begin
 Result:=(x>-1) and (y>-1) and (Dir>indefinie);
 end;
//-----------------------------------------------------------------------------
function feu.DefinitNbFeuxDmd(n : Integer) : Integer;
 begin
 try
  SetLength(NumFeuxDmd, n*sizeof(Integer));
  NbFeuxDmd:=n;
 finally
  Result:=NbFeuxDmd;
 end{try};
 end;
//-----------------------------------------------------------------------------
function feu.DefinitNbFeuxAtt(n : Integer) : Integer;
 begin
 try
  SetLength(NumFeuxAtt, n*sizeof(Integer));
  NbFeuxAtt:=n;
 finally
  Result:=NbFeuxAtt;
 end{try};
 end;
//-----------------------------------------------------------------------------
procedure feu.AjouteFeuDmd(NumNvFeu : Integer);
 begin
  DefinitNbFeuxDmd(NbFeuxDmd+1);
  NumFeuxDmd[NbFeuxDmd-1]:=NumNvFeu;
 end;
//-----------------------------------------------------------------------------
procedure feu.AjouteFeuAtt(NumNvFeu : Integer);
 begin
  DefinitNbFeuxAtt(NbFeuxAtt+1);
  NumFeuxAtt[NbFeuxAtt-1]:=NumNvFeu;
 end;
//-----------------------------------------------------------------------------
procedure feu.RetireFeuDmd(NumFeu : Integer);
var i : Integer;
    Trv : Boolean;
 begin
 Trv:=false;
 for i:=0 to NbFeuxDmd-2 do
  begin
  if not Trv and (NumFeuxDmd[i]=NumFeu) then Trv:=true;
  if Trv then NumFeuxDmd[i]:=NumFeuxDmd[i+1];
  end;
  if not Trv and (NumFeuxDmd[NbFeuxDmd-1]=NumFeu) then Trv:=true;
  if Trv then DefinitNbFeuxDmd(NbFeuxDmd-1);
 end;
//-----------------------------------------------------------------------------
procedure feu.RetireFeuAtt(NumFeu : Integer);
var i : Integer;
    Trv : Boolean;
 begin
 Trv:=false;
 for i:=0 to NbFeuxAtt-2 do
  begin
  if not Trv and (NumFeuxAtt[i]=NumFeu) then Trv:=true;
  if Trv then NumFeuxAtt[i]:=NumFeuxAtt[i+1];
  end;
  if not Trv and (NumFeuxAtt[NbFeuxAtt-1]=NumFeu) then Trv:=true;
  if Trv then DefinitNbFeuxAtt(NbFeuxAtt-1);
 end;
//-----------------------------------------------------------------------------
procedure feu.ChangeEtat;
var ChgEtat : Boolean;
 begin
  ChgEtat:=(Etat<>ProchainEtat);
  Etat:=ProchainEtat;
  if (ChgEtat) then frmSimulation.RedessineCase(x, y, false);
 end;
//-----------------------------------------------------------------------------
procedure feu.DefinitProchainEtat;
var i : Integer;
begin
  TourDrnChgEtat:=cv.TourCrt;
  if (Etat>inactif) then ProchainEtat:=etat_feu(1+Integer(Etat) mod 3);
  case ProchainEtat of
    vert:  begin
           DemandeVert:=false;
           FeuxTousRouges:=false;
           ProchainVert:=false;
           end;
    rouge: begin
           RougeDemande:=false;
           // On informe quels sont les prochains feux à se mettre au vert
           for i:=0 to NbFeuxDmd-1 do
            if ((cv.Feux[NumFeuxDmd[i]-1].Etat=rouge) and
                (not cv.Feux[NumFeuxDmd[i]-1].ProchainVert) and
                (cv.Feux[NumFeuxDmd[i]-1].DemandeVert or
                 (cv.Feux[NumFeuxDmd[i]-1].TourDrnChgEtat<cv.TourCrt))) then 
             begin
              cv.Feux[NumFeuxDmd[i]-1].ProchainVert:=true;
              cv.Feux[NumFeuxDmd[i]-1].TourDrnChgEtat:=cv.TourCrt;
             end;
            end;
  end{case of};
 end;
//-----------------------------------------------------------------------------
procedure feu.Evolue;
var i, NumVeh, NumBus : Integer; // v3.0 (NumBus)
 begin
  if Etat=inactif then Exit;
  ProchainEtat:=Etat; // Par défaut
  NumVeh:=cv.v[x, y].NumVehicule;
  NumBus:=cv.v[x, y].NumBus;
  case Etat of
    vert:      // Si (rouge demandé ou passage immediat) et durée vert écoulée . Orange
               if (((RougeDemande and (TourDrnChgEtat<cv.TourCrt)) or
                    (TypePsgRouge=immediat)) and
                   (cv.TourCrt-TourDrnChgEtat>DureeVert)) then DefinitProchainEtat;
    orange:    if (cv.TourCrt-TourDrnChgEtat>cv.DureeOrange) then DefinitProchainEtat();
    rouge:     begin // Le vert n'est pas encore demandé
               if not DemandeVert then
                begin
                 if ((cv.TourCrt-TourDrnChgEtat>DureeRouge) and  // la durée du rouge est écoulée ET
                     ((TypeDmdVert=immediate) or  // La demande est immédiate Ou
                      ((NumVeh>0) and  // un véhicule est sur la case et
                       (cv.Vehicules[NumVeh-1].Dir=Dir)) or
                      ((NumBus>0) and  // un bus est sur la case et
                       (cv.Autobus[NumBus-1].Dir=Dir)))) then// dans la direction du feu... v3.0
                  begin // Alors...On demande le vert DES QU'UN DES FEUX (devant être rouge) EST VERT
                  i:=0;
                  while(i<NbFeuxAtt) and
                        ((cv.Feux[NumFeuxAtt[i]-1].Etat<>vert) or
                         ((cv.Feux[NumFeuxAtt[i]-1].TourDrnChgEtat=cv.TourCrt) and
                          (not cv.Feux[NumFeuxAtt[i]-1].RougeDemande))) do Inc(i);
                  DemandeVert:=(i<NbFeuxAtt);
                  if DemandeVert then TourDrnChgEtat:=cv.TourCrt;
                  end{if cv.TourCrt...};
                end{if not DmdVert};
               // Le vert est demandé...
               if DemandeVert then
                begin
                 // On le fait toujours savoir (si jamais un feu devient vert entre-temps)
                 for i:=0 to NbFeuxAtt-1 do // On parcours les feux devant être rouge
                  if ((cv.Feux[NumFeuxAtt[i]-1].Etat=vert) and  // feu opposé vert et
                      (cv.Feux[NumFeuxAtt[i]-1].TourDrnChgEtat<cv.TourCrt) and
                      (not cv.Feux[NumFeuxAtt[i]-1].RougeDemande)) then// le rouge n'a pas encore été demandé)
                   begin
                   cv.Feux[NumFeuxAtt[i]-1].RougeDemande:=true; // Ben maintenant...
                   cv.Feux[NumFeuxAtt[i]-1].TourDrnChgEtat:=cv.TourCrt; //  c'est fait
                   end;
                end{if DemandeVert};
               // On vérifie que les feux opposés ne sont pas déjà tous rouges (vert demandé ou non)
               if not FeuxTousRouges then
                begin
                i:=0;
                while (i<NbFeuxAtt) and
                      (cv.Feux[NumFeuxAtt[i]-1].Etat=rouge) and
                      (cv.Feux[NumFeuxAtt[i]-1].DemandeVert or
                       cv.Feux[NumFeuxAtt[i]-1].ProchainVert or
                       (cv.Feux[NumFeuxAtt[i]-1].TourDrnChgEtat<cv.TourCrt)) do Inc(i);
                FeuxTousRouges:=(i=NbFeuxAtt);
                if FeuxTousRouges then TourDrnChgEtat:=cv.TourCrt;
                end{if not FeuxTousRouges};
               // On passe au vert si on le demande ou on l'autorise (vert demandé ou non)
               if FeuxTousRouges and ProchainVert and (TourDrnChgEtat<cv.TourCrt) then
                DefinitProchainEtat();
               end{rouge:};
   end{case of};
 end;
//-----------------------------------------------------------------------------
function feu.Charge(hfile : Integer) : Boolean;
var i : Integer;
    Ok : Boolean;
 begin
  Ok:=(FileRead(hfile, Numero, sizeof(Numero))>0) and
      (FileRead(hfile, x, sizeof(x))>0) and
      (FileRead(hfile, y, sizeof(y))>0) and
      (FileRead(hfile, Dir, sizeof(Dir))>0) and
      (FileRead(hfile, Etat, sizeof(Etat))>0) and
      (FileRead(hfile, NbFeuxDmd, sizeof(NbFeuxDmd))>0) and
      (FileRead(hfile, NbFeuxAtt, sizeof(NbFeuxAtt))>0) and
      (FileRead(hfile, TypeDmdVert, sizeof(TypeDmdVert))>0) and
      (FileRead(hfile, TypePsgRouge, sizeof(TypePsgRouge))>0) and
      (FileRead(hfile, DureeRouge, sizeof(DureeRouge))>0) and
      (FileRead(hfile, DureeVert, sizeof(DureeVert))>0) and
      (FileRead(hfile, DemandeVert, sizeof(DemandeVert))>0) and
      (FileRead(hfile, RougeDemande, sizeof(RougeDemande))>0);

  if Ok then
   begin
    if NbFeuxDmd>0 then SetLength(NumFeuxDmd, NbFeuxDmd*sizeof(Integer));
    if NbFeuxAtt>0 then SetLength(NumFeuxAtt, NbFeuxAtt*sizeof(Integer));
   end;
  i:=0; while Ok and (i<NbFeuxDmd) do begin Ok:=FileRead(hfile, NumFeuxDmd[i], sizeof(NumFeuxDmd[i]))>0; Inc(i); end;
  i:=0; while Ok and (i<NbFeuxAtt) do begin Ok:=FileRead(hfile, NumFeuxAtt[i], sizeof(NumFeuxAtt[i]))>0; Inc(i); end;
  Result:=Ok;
 end;
//-----------------------------------------------------------------------------
function feu.Sauve(hfile : Integer) : Boolean;
var i : Integer;
    Ok : Boolean;
 begin
  Ok:=(FileWrite(hfile, Numero, sizeof(Numero))>0) and
      (FileWrite(hfile, x, sizeof(x))>0) and
      (FileWrite(hfile, y, sizeof(y))>0) and
      (FileWrite(hfile, Dir, sizeof(Dir))>0) and
      (FileWrite(hfile, Etat, sizeof(Etat))>0) and
      (FileWrite(hfile, NbFeuxDmd, sizeof(NbFeuxDmd))>0) and
      (FileWrite(hfile, NbFeuxAtt, sizeof(NbFeuxAtt))>0) and
      (FileWrite(hfile, TypeDmdVert, sizeof(TypeDmdVert))>0) and
      (FileWrite(hfile, TypePsgRouge, sizeof(TypePsgRouge))>0) and
      (FileWrite(hfile, DureeRouge, sizeof(DureeRouge))>0) and
      (FileWrite(hfile, DureeVert, sizeof(DureeVert))>0) and
      (FileWrite(hfile, DemandeVert, sizeof(DemandeVert))>0) and
      (FileWrite(hfile, RougeDemande, sizeof(RougeDemande))>0);

  i:=0; while Ok and (i<NbFeuxDmd) do begin Ok:=FileWrite(hfile, NumFeuxDmd[i], sizeof(NumFeuxDmd[i]))>0; Inc(i); end;
  i:=0; while Ok and (i<NbFeuxAtt) do begin Ok:=FileWrite(hfile, NumFeuxAtt[i], sizeof(NumFeuxAtt[i]))>0; Inc(i); end;
  Result:=Ok;
 end;
//-----------------------------------------------------------------------------
procedure feu.Verifie(var stMsgErr : String; stSource : String);
var i : Integer;
 begin
  if (Numero<0) then
   stMsgErr:=stMsgErr+stSource+Format(': numéro incorrect (%d)'#13#10'', [Numero]);
  VerifiePosition(stMsgErr, stSource, x, y, DOIT_ETRE_DEFINI);
  VerifieDirection(stMsgErr, stSource, Dir, DOIT_ETRE_DEFINI);
  VerifieEtat(stMsgErr, stSource, Etat);
  VerifieEtat(stMsgErr, stSource, ProchainEtat);

  VerifEnCours:=true; // Evite les boucles infinies dues aux pointages mutuels de références

  if ((NbFeuxDmd<0) or (NbFeuxDmd>cv.NbFeux)) then
   stMsgErr:=stMsgErr+stSource+Format(': nombre des prochains feux verts incorrect (%d)'#13#10'', [NbFeuxDmd])
  else
   for i:=0 to NbFeuxDmd-1 do
    if ((NumFeuxDmd[i]<1) or (NumFeuxDmd[i]>=cv.NbFeux)) then
     stMsgErr:=stMsgErr+stSource+Format(': numéro du %d° prochain feu vert incorrect (%d)'#13#10'', [i+1, NumFeuxDmd[i]])
    else
     if not cv.Feux[NumFeuxDmd[i]-1].VerifEnCours then
      cv.Feux[NumFeuxDmd[i]-1].Verifie(stMsgErr, Format('%d° prochain feu vert [n°%d, (%d,%d)]'#13#10'',
                                                        [i+1, NumFeuxDmd[i],
                                                         cv.Feux[NumFeuxDmd[i]-1].x,
                                                         cv.Feux[NumFeuxDmd[i]-1].y]));
  if ((NbFeuxAtt<0) or (NbFeuxAtt>cv.NbFeux)) then
   stMsgErr:=stMsgErr+stSource+Format(': nombre des feux devant être rouge incorrect (%d)'#13#10'', [NbFeuxAtt])
  else
   for i:=0 to NbFeuxAtt-1 do
    if ((NumFeuxAtt[i]<1) or (NumFeuxAtt[i]>=cv.NbFeux)) then
     stMsgErr:=stMsgErr+stSource+Format(': numéro du %d° feu devant être rouge incorrect (%d)'#13#10'', [i+1, NumFeuxAtt[i]])
    else
     if not cv.Feux[NumFeuxAtt[i]-1].VerifEnCours then
      cv.Feux[NumFeuxAtt[i]-1].Verifie(stMsgErr, Format('%d° feu devant être rouge [n°%d, (%d,%d)]'#13#10'',
                                                        [i+1, NumFeuxAtt[i],
                                                         cv.Feux[NumFeuxAtt[i]-1].x,
                                                         cv.Feux[NumFeuxAtt[i]-1].y]));
  VerifEnCours:=false;
  VerifieDmdVert(stMsgErr, stSource, TypeDmdVert);
  VerifiePsgRouge(stMsgErr, stSource, TypePsgRouge);
  if DemandeVert and (Etat<>rouge) then
   stMsgErr:=stMsgErr+stSource+': demande le vert alors qu''il n''est pas rouge'#13#10'';
  if RougeDemande and (Etat<>vert) then
   stMsgErr:=stMsgErr+stSource+': le rouge est demandé alors qu''il n''est pas vert'#13#10'';
 end{feu.Verifie};
//-----------------------------------------------------------------------------
// Classe Etapes
// ----------------------------------------------------------------------------
procedure etape.Initialise;
 begin
 x:=-1; y:=-1;
 end;
// ----------------------------------------------------------------------------
constructor etape.Create(Num : Integer);
 begin
 AffecteNumero(Num);
 Initialise;
 end;
// ----------------------------------------------------------------------------
procedure etape.AffecteNumero(Num : Integer);
 begin
 Numero:=Num;
 end;
// ----------------------------------------------------------------------------
procedure etape.Definit(x0, y0 : Integer);
 begin
 x:=x0; y:=y0;
 end;
// ----------------------------------------------------------------------------
constructor etape.Create(x0, y0 : Integer);
 begin
 Definit(x0, y0);
 end;
// ----------------------------------------------------------------------------
destructor etape.Destroy; begin end;
function etape.Definie : Boolean;
 begin
 Result:=(x>-1) and (y>-1);
 end;
// ----------------------------------------------------------------------------
procedure etape.PlaceProchainVehicule;
 var i, NumVehicule : Integer;
 begin
 NumVehicule:=0;
  if cv.v[x, y].NumVehicule=0 then
   begin
    i:=0;
    while (NumVehicule=0) and (i<cv.NbVehicules) do
     begin
     NumVehicule:=(i+1)*Ord((cv.Vehicules[i].NumEtapeDepart=Numero) and
                            (cv.Vehicules[i].x=x) and
                            (cv.Vehicules[i].y=y));
     Inc(i);
     end{while};
    if NumVehicule>0 then // Il y a encore un véhicule à sortir
     begin
      cv.v[x, y].NumVehicule:=NumVehicule;
      cv.PlaceVehicule(x, y, NumVehicule);
      cv.Vehicules[NumVehicule-1].TourDepart:=cv.TourCrt;
      Inc(cv.NbVehiculesSortis);
     end{if NumVehicule>0};
   end{cv.v[x,y].NumVeh=0};
 end{etape.PlaceProchainVehicule};
//-----------------------------------------------------------------------------
function etape.Charge(hfile : Integer) : Boolean;
 begin
  Result:=(FileRead(hfile, Numero, sizeof(Numero))>0) and
          (FileRead(hfile, x, sizeof(x))>0) and
          (FileRead(hfile, y, sizeof(y))>0);
 end;
//-----------------------------------------------------------------------------
function etape.Sauve(hfile : Integer) : Boolean;
 begin
  Result:=(FileWrite(hfile, Numero, sizeof(Numero))>0) and
          (FileWrite(hfile, x, sizeof(x))>0) and
          (FileWrite(hfile, y, sizeof(y))>0);
 end;
//-----------------------------------------------------------------------------
procedure etape.Verifie(var stMsgErr : String);
var stSource : String;
 begin
  stSource:=Format('Etape n°%d (%d,%d)', [Numero, x, y]);
  if Numero<0 then
   stMsgErr:=stMsgErr+stSource+Format(': numéro incorrect (%d)'#13#10'', [Numero]);
  VerifiePosition(stMsgErr, stSource, x, y, DOIT_ETRE_DEFINI);
 end{etape.Verifie};
//-----------------------------------------------------------------------------
// Classe Véhicules
// ----------------------------------------------------------------------------
procedure vehicule.Initialise;
begin
 x:=-1; y:=-1; DirDrnDepl:=indefinie; Dir:=indefinie;
 NivPriorite:=normal;
 NbCasesParcourues:=0; TourDepart:=0; TourDrnDepl:=0;
 NbToursRepos:=0; //v2.2.4
 NumEtapeDepart:=0; NumEtapeArrivee:=0;
end; //vehicule.Initialise
// ----------------------------------------------------------------------------
constructor vehicule.Create(Num : Integer);
 begin
 AffecteNumero(Num);
 Initialise;
 end;
// ----------------------------------------------------------------------------
procedure vehicule.AffecteNumero(Num : Integer);
 begin
 Numero:=Num;
 end;
// ----------------------------------------------------------------------------
procedure vehicule.Place(x0, y0 : Integer);
 begin
 x:=x0; y:=y0;
 end;
// ----------------------------------------------------------------------------
procedure vehicule.Definit(x0, y0 : Integer; Dir0 : direction; NumDepart, NumArrivee : Integer; NivPriorite0 : niveau_priorite);
 begin
 x:=x0; y:=y0; Dir:=Dir0;
 NumEtapeDepart:=NumDepart; NumEtapeArrivee:=NumArrivee;
 NivPriorite:=NivPriorite0;
 end;
// ----------------------------------------------------------------------------
destructor vehicule.Destroy; begin end;
function vehicule.Defini : Boolean;
 begin
 Result:=(x>-1) and (y>-1);
 end;
// ----------------------------------------------------------------------------
procedure vehicule.CalculeProchaineDirection;
 var v, Voie : pVoie;
     i, j, ndp : Integer;
     OrdreDir : array [0..3] of Integer;
     AncDir : direction; // v2.2.4
 begin
  v:=@(cv.v[x, y]);
  for i:=0 to 3 do OrdreDir[i]:=0;
  ndp:=NbDir[v.DirPoss];
  AncDir:=Dir; // v2.2.4
  Dir:=indefinie;

  // On classe les dir.poss. dans l'ordre < des distances aux étapes.
  // En cas d'égalité, c'est le hasard : (N°Veh.+Tour) Modulo Directions Possibles
  for i:=0 to ndp-1 do
   for j:=0 to ndp-1 do
    if i<>j then // On dégringole si distance supérieure.
     Inc(OrdreDir[i], Ord(((v.DistEtape[NumEtapeArrivee-1, i]>v.DistEtape[NumEtapeArrivee-1, j]) or
                           ((v.DistEtape[NumEtapeArrivee-1, i]=v.DistEtape[NumEtapeArrivee-1, j]) and
                            (Dirdp[i, v.DirPoss]<>AncDir) and // En cas d'égalité, préfère garder la direction courante : v2.2.4
                            ((i+Numero+cv.TourCrt) mod ndp>(j+Numero+cv.TourCrt) mod ndp))))); // tirage au hasard en cas d'égalité (Ici TourCrt+1)
  i:=0;
  while (Dir=indefinie) and (i<ndp) do
   begin
   j:=0;
   while (Dir=indefinie) and (j<ndp) do
    begin
    Voie:=cv.vxyd(x,y,Dirdp[j, v.DirPoss]);
    if ((OrdreDir[j]=i) and
        ((not v.ToutDroit) or     // Direction interdite si : obligation d'aller tout droit ET
         (DirDrnDepl=direction(j+1))) and  //                          pas même direction que lors du dernier déplacement
        (((Voie.NumVehicule=0) and (Voie.NumBus=0)) or // v3.0 (NumBus)
         ((Voie.NumEtape>0) and (Voie.NumEtape=NumEtapeArrivee)) or
         (cv.TourCrt<=1+TourDrnDepl+Ord(NivPriorite=normal)*cv.AttenteMaxVeh*(1+OrdreDir[j])))) then
     Dir:=Dirdp[j, v.DirPoss];
    Inc(j);
    end{while not dir and j<ndp};
   Inc(i);
   end{while not dir and i<ndp};

   // Si la direction est toujours indéfinie : on prend la meilleure direction possible
   if (Dir=indefinie) then
    begin
    i:=0;
    while (Dir=indefinie) and (i<ndp) do
     begin
     j:=0;
     while (Dir=indefinie) and (j<ndp) do
      begin
      if (OrdreDir[j]=i) then Dir:=Dirdp[j, v.DirPoss];
      Inc(j);
      end{while Dir=indefinie and j<ndp};
     Inc(i);
     end{while Dir=indefinie and i<ndp};
    end{if Dir=indefinie};
 end;
//-----------------------------------------------------------------------------
function vehicule.ProchaineDirectionAuCarrefour : direction; // ATTENTION : DIR DOIT ETRE DEFINIE
var v : pVoie;
    OrdreDir : Array [0..3] of Integer;
    i, j, ndp : Integer;
    DirAuCarrefour :  direction;
 begin
  v:=cv.vxyd(x,y,Dir); // Ici v est la prochaine case
  ndp:=NbDir[v.DirPoss];
  for i:=0 to 3 do OrdreDir[i]:=0;
  DirAuCarrefour:=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux étapes si la case est libre.
  // En cas d'égalité, c'est le hasard : (N°Veh.+Tour) Modulo Directions Possibles
  for i:=0 to ndp-1 do
   for j:=0 to ndp-1 do
    if i<>j then
     Inc(OrdreDir[i], Ord(((v.DistEtape[NumEtapeArrivee-1, i]>v.DistEtape[NumEtapeArrivee-1, j]) or
                       ((v.DistEtape[NumEtapeArrivee-1, i]=v.DistEtape[NumEtapeArrivee-1, j]) and
                        ((i+Numero+cv.TourCrt) mod ndp>(j+Numero+cv.TourCrt) mod ndp))))); // tirage au hasard en cas d'égalité (Ici TourCrt+1)
  i:=0;
  while (DirAuCarrefour=indefinie) and (i<ndp) do
   begin
   j:=0;
   while (DirAuCarrefour=indefinie) and (j<ndp) do
    begin
    if ((OrdreDir[j]=i) and
        ((not v.ToutDroit) or // Direction interdite si : obligation d'aller tout droit ET
         (DirDrnDepl=direction(j+1)))) then //                       pas même direction que lors du dernier déplacement
     DirAuCarrefour:=Dirdp[j, v.DirPoss];
    Inc(j);
    end{while Dir>indefinie and j<ndp};
   Inc(i);
   end{while Dir>indefinie and i<ndp};
  Result:=DirAuCarrefour;
 end;
//-----------------------------------------------------------------------------
function vehicule.PeutPasser : Boolean;
var v : pVoie;
    NumFeuVeh : Integer;
 begin
 v:=@(cv.v[x, y]);
 if Dir>indefinie then
  begin
  NumFeuVeh:=v.NumFeu[Integer(Dir)-1];
  Result:=(NivPriorite>normal) or
          (((v.Priorites[Integer(Dir)-1]<>stop) or
            (cv.TourCrt-TourDrnDepl>=2)) and
           ((NumFeuVeh=0) or
            (cv.Feux[NumFeuVeh-1].Etat<orange)));
  end
 else
  Result:=false;
 end;
//-----------------------------------------------------------------------------
procedure vehicule.Verifie(var stMsgErr : String);
var stSource : String;
 begin
  stSource:=Format('Véhicule n°%d (%d,%d)', [Numero, x, y]);
  if Numero<0 then
   stMsgErr:=stMsgErr+stSource+Format(': numéro incorrect (%d)'#13#10'', [Numero]);
  VerifiePosition(stMsgErr, stSource, x, y, PEUT_ETRE_INDEFINI);
  VerifieDirection(stMsgErr, stSource, Dir, PEUT_ETRE_INDEFINI);
  if (NumEtapeDepart<>0) and (NumEtapeArrivee<>0) then
   begin // On ne teste pas si Depart=Arrivee=0 (les véhicules sont préparés avant)
   if NumEtapeDepart<1 then
    stMsgErr:=stMsgErr+stSource+Format(': numéro d''étape de départ incorrect (%d)'#13#10'', [NumEtapeDepart]);
   if NumEtapeArrivee<1 then
    stMsgErr:=stMsgErr+stSource+Format(': numéro d''étape d''arrivée incorrect (%d)'#13#10'', [NumEtapeArrivee]);
   end;
 end;
//-----------------------------------------------------------------------------
// Classe Dépot de bus (v3.0)
//-----------------------------------------------------------------------------
procedure depot_bus.Initialise;
begin
x:=-1; y:=-1;
NumDrnBusSorti:=0;
end;
//-----------------------------------------------------------------------------
procedure depot_bus.Definit(x0, y0 : Integer);
begin
x:=x0; y:=y0; NumDrnBusSorti:=0;
end;
//-----------------------------------------------------------------------------
constructor depot_bus.Create;
begin
Initialise;
end;
//-----------------------------------------------------------------------------
destructor depot_bus.Destroy;
begin
end;
//-----------------------------------------------------------------------------
function depot_bus.Defini : Boolean;
begin
Result:=(x>-1) and (y>-1);
end;
//-----------------------------------------------------------------------------
procedure depot_bus.PlaceProchainBus;
var NumProchBus : Integer;
begin
if Defini and // Défini ET
   (cv.v[x,y].NumBus=0) and // pas de bus ET
   (cv.v[x,y].NumVehicule=0) and // pas de véhicule sur la case dépôt ET
   (NumDrnBusSorti<cv.NbBus) then // encore au moins un bus à sortir
 begin
 Inc(NumDrnBusSorti);
 NumProchBus:=NumDrnBusSorti;
 cv.v[x,y].NumBus:=NumProchBus;
 cv.PlaceBus(x, y, NumProchBus);
 end;
end;
//-----------------------------------------------------------------------------
function depot_bus.Charge(hfile : Integer) : Boolean;
 begin
  Result:=(FileRead(hfile, x, sizeof(x))>0) and
          (FileRead(hfile, y, sizeof(y))>0);
 end;
//-----------------------------------------------------------------------------
function depot_bus.Sauve(hfile : Integer) : Boolean;
 begin
  Result:=(FileWrite(hfile, x, sizeof(x))>0) and
          (FileWrite(hfile, y, sizeof(y))>0);
 end;
//-----------------------------------------------------------------------------
procedure depot_bus.Verifie(var stMsgErr : String); // v3.0.3
var stSource : String;
 begin
  stSource:=Format('Dépôt bus : ', [x, y]);
  VerifiePosition(stMsgErr, stSource, x, y, PEUT_ETRE_INDEFINI);
 end;
//-----------------------------------------------------------------------------
// Classe Bus (v3.0)
//-----------------------------------------------------------------------------
procedure bus.Initialise;
 begin
  x:=-1; y:=-1;
  Dir:=indefinie;
  DirDrnDepl:=indefinie;
  DirAvtDrnDepl:=indefinie;
  NbPersonnes:=0;
  NbToursRepos:=0;
  NbCasesParcouruesDepuisDrnArret:=0;
  NbCasesParcourues:=0;
  TourArriveDrnArret:=0;
  TourDepartArretSvt:=0;
  TourDepart:=0;
  TourDrnDepl:=0;
 end;
// ----------------------------------------------------------------------------
procedure bus.AffecteNumero(Num : Integer);
 begin
  Numero:=Num;
 end;
// ----------------------------------------------------------------------------
procedure bus.Place(x0, y0 : Integer);
 begin
  x:=x0; y:=y0;
 end;
// ----------------------------------------------------------------------------
procedure bus.Definit(NumLigne0, NumArretSvt0 : Integer);
 begin
  NumLigne:=NumLigne0;
  NumArretSvt:=NumArretSvt0;
 end;
// ----------------------------------------------------------------------------
constructor bus.Create(Num : Integer);
 begin
 AffecteNumero(Num);
 Initialise;
 end;
// ----------------------------------------------------------------------------
destructor bus.Destroy;
 begin
 end;
// ----------------------------------------------------------------------------
function bus.Defini : Boolean;
 begin
  Result:=(x>-1) and (y>-1);
 end;
// ----------------------------------------------------------------------------
procedure bus.FaitMonterPieton(NumPietonAFaireMonter : Integer);
var p : pPieton;
 begin
  p:=@(cv.Pietons[NumPietonAFaireMonter]);
  if NbPersonnes<cv.NbMaxPersonnesBus then
   begin
   Inc(NbPersonnes);
   cv.v[p.x, p.y].RetirePieton(NumPietonAFaireMonter);
   p.NumBus:=Numero; p.x:=-1; p.y:=-1; p.AttendBus:=false;
   frmSimulation.RedessineCase(p.x, p.y, false);
   end; 
 end;
// ----------------------------------------------------------------------------
procedure bus.FaitMonterEtDescendre;
var i : Integer;
    v : pVoie;
    p : pPieton;
 begin
  v:=cv.vxyd(x,y,direction(1+integer(Dir) mod NBDIRS));
  for i:=0 to cv.NbPietons-1 do
   begin
   p:=@(cv.Pietons[i]);
   if p.NumBus=Numero then
    begin
    if not p.VeutDescendre then
     p.VeutDescendre:=cv.ProbaArretBusDmd>Random(100);
    if p.VeutDescendre then
     v.FaitDescendrePieton(i); // Si on peut faire descendre, il descend au prochain arrêt
    end{if};
   if (p.NumArretBus=NumDrnArret) and p.AttendBus then
    FaitMonterPieton(i); // Si on ne peut pas faire monter, il montera dans le prochain bus
   end{for};
 end;
// ----------------------------------------------------------------------------
procedure bus.CalculeProchaineDirection; // v3.0
 var v, Voie : pVoie;
     i, j, ndp : Integer;
     OrdreDir : array [0..3] of Integer;
     AncDir : direction;
 begin
  v:=@(cv.v[x, y]);
  for i:=0 to 3 do OrdreDir[i]:=0;
  ndp:=NbDir[v.DirPoss];
  AncDir:=Dir; 
  Dir:=indefinie;

  // On classe les dir.poss. dans l'ordre < des distances aux arrêts de bus.
  // En cas d'égalité, c'est le hasard : (N°Bus.+Tour) Modulo Directions Possibles
  for i:=0 to ndp-1 do
   for j:=0 to ndp-1 do
    if i<>j then // On dégringole si distance supérieure.
     Inc(OrdreDir[i], Ord(((v.DistArretBus[NumArretSvt-1, i]>v.DistArretBus[NumArretSvt-1, j]) or
                           ((v.DistArretBus[NumArretSvt-1, i]=v.DistArretBus[NumArretSvt-1, j]) and
                            (Dirdp[i, v.DirPoss]<>AncDir) and // En cas d'égalité, préfère garder la direction courante : v2.2.4
                            ((i+Numero+cv.TourCrt) mod ndp>(j+Numero+cv.TourCrt) mod ndp))))); // tirage au hasard en cas d'égalité (Ici TourCrt+1)
  i:=0;
  while (Dir=indefinie) and (i<ndp) do
   begin
   j:=0;
   while (Dir=indefinie) and (j<ndp) do
    begin
    Voie:=cv.vxyd(x,y,Dirdp[j, v.DirPoss]);
    if ((OrdreDir[j]=i) and
        ((not v.ToutDroit) or     // Direction interdite si : obligation d'aller tout droit ET
         (DirDrnDepl=direction(j+1))) and  //                          pas même direction que lors du dernier déplacement
        (((Voie.NumVehicule=0) and (Voie.NumBus=0)) or
         ((Voie.NumArretBus>0) and (Voie.NumArretBus=NumArretSvt)) or
         (cv.TourCrt<=1+TourDrnDepl+5*cv.AttenteMaxVeh*(1+OrdreDir[j])))) then // AttenteMaxBus = 5*AttenteMaxVeh
     Dir:=Dirdp[j, v.DirPoss];
    Inc(j);
    end{while not dir and j<ndp};
   Inc(i);
   end{while not dir and i<ndp};

   // Si la direction est toujours indéfinie : on prend la meilleure direction possible
   if (Dir=indefinie) then
    begin
    i:=0;
    while (Dir=indefinie) and (i<ndp) do
     begin
     j:=0;
     while (Dir=indefinie) and (j<ndp) do
      begin
      if (OrdreDir[j]=i) then Dir:=Dirdp[j, v.DirPoss];
      Inc(j);
      end{while Dir=indefinie and j<ndp};
     Inc(i);
     end{while Dir=indefinie and i<ndp};
    end{if Dir=indefinie};
  if DirDrnDepl=indefinie then DirDrnDepl:=Dir;
  if DirAvtDrnDepl=indefinie then DirAvtDrnDepl:=Dir;
 end;
// ----------------------------------------------------------------------------
function bus.ProchaineDirectionAuCarrefour : direction; // v3.0
var v : pVoie;
    OrdreDir : Array [0..3] of Integer;
    i, j, ndp : Integer;
    DirAuCarrefour :  direction;
 begin
  v:=cv.vxyd(x,y,Dir); // Ici v est la prochaine case
  ndp:=NbDir[v.DirPoss];
  for i:=0 to 3 do OrdreDir[i]:=0;
  DirAuCarrefour:=indefinie;
  // On classe les dir.poss. dans l'ordre < des distances aux arrêts de bus si la case est libre.
  // En cas d'égalité, c'est le hasard : (N°Bus.+Tour) Modulo Directions Possibles
  for i:=0 to ndp-1 do
   for j:=0 to ndp-1 do
    if i<>j then
     Inc(OrdreDir[i], Ord(((v.DistArretBus[NumArretSvt-1, i]>v.DistArretBus[NumArretSvt-1, j]) or
                       ((v.DistArretBus[NumArretSvt-1, i]=v.DistArretBus[NumArretSvt-1, j]) and
                        ((i+Numero+cv.TourCrt) mod ndp>(j+Numero+cv.TourCrt) mod ndp))))); // tirage au hasard en cas d'égalité (Ici TourCrt+1)
  i:=0;
  while (DirAuCarrefour=indefinie) and (i<ndp) do
   begin
   j:=0;
   while (DirAuCarrefour=indefinie) and (j<ndp) do
    begin
    if ((OrdreDir[j]=i) and
        ((not v.ToutDroit) or // Direction interdite si : obligation d'aller tout droit ET
         (DirDrnDepl=direction(j+1)))) then //                       pas même direction que lors du dernier déplacement
     DirAuCarrefour:=Dirdp[j, v.DirPoss];
    Inc(j);
    end{while Dir>indefinie and j<ndp};
   Inc(i);
   end{while Dir>indefinie and i<ndp};
  Result:=DirAuCarrefour;
 end;
//-----------------------------------------------------------------------------
function bus.PeutPasser;
var v : pVoie;
 begin
 v:=@(cv.v[x,y]);
 Result:=(Dir>indefinie) and
         ((v.Priorites[Integer(Dir)-1]<>stop) or
          (cv.TourCrt-TourDrnDepl>=2)) and
         ((v.NumFeu[Integer(Dir)-1]=0) or
          (cv.Feux[v.NumFeu[Integer(Dir)-1]-1].Etat<orange));
 end;
// ----------------------------------------------------------------------------
function bus.NumeroArretSuivant;
var i : Integer;
 begin
 i:=0;
 while (NumArretSvt<>cv.LignesBus[NumLigne-1].NumArret[i]) and
       (i<cv.LignesBus[NumLigne-1].NbArrets) do Inc(i);
 if i<cv.LignesBus[NumLigne-1].NbArrets then
  Result:=cv.LignesBus[NumLigne-1].NumArret[(i+1) mod cv.LignesBus[NumLigne-1].NbArrets]
 else
  Result:=cv.LignesBus[NumLigne-1].NumArret[0];
 end;
// ----------------------------------------------------------------------------
procedure bus.Verifie(var stMsgErr : String); // v3.0.3
var stSource : String;
 begin
  stSource:=Format('Véhicule n°%d (%d,%d)', [Numero, x, y]);
  if Numero<0 then
   stMsgErr:=stMsgErr+stSource+Format(': numéro incorrect (%d)'#13#10'', [Numero]);
  VerifiePosition(stMsgErr, stSource, x, y, PEUT_ETRE_INDEFINI);
  VerifieDirection(stMsgErr, stSource, Dir, PEUT_ETRE_INDEFINI);
  if (NumLigne<0) or (NumLigne>=NBMAXLIGNESBUS) then
   stMsgErr:=stSource+Format(': numéro de ligne de bus incorrect (%d)'#13#10'', [NumLigne]);
 end;
// ----------------------------------------------------------------------------
// Classe Arrêt de bus (v3.0)
// ----------------------------------------------------------------------------
procedure arret_bus.Initialise;
var i : Integer;
 begin
  x:=-1; y:=-1;
  NbLignes:=0;
  for i:=0 to NBMAXLIGNESBUS-1 do
   begin
   Ligne[i]:=false;
   NumLigne[i]:=0;
   end;
 end;
// ----------------------------------------------------------------------------
procedure arret_bus.AffecteNumero(Num : Integer);
 begin
  Numero:=Num;
 end;
// ----------------------------------------------------------------------------
procedure arret_bus.Definit(x0, y0 : Integer);
 begin
  x:=x0; y:=y0;
 end;
// ----------------------------------------------------------------------------
constructor arret_bus.Create(x0, y0 : Integer);
 begin
  Definit(x0, y0);
 end;
// ----------------------------------------------------------------------------
constructor arret_bus.Create(Num : Integer);
 begin
 AffecteNumero(Num);
 Initialise;
 end;
// ----------------------------------------------------------------------------
destructor arret_bus.Destroy;
 begin
 end;
// ----------------------------------------------------------------------------
function arret_bus.Defini : Boolean;
 begin
  Result:=(x>-1) and (y>-1);
 end;
// ----------------------------------------------------------------------------
procedure arret_bus.InitialiseInfosLignesBus;
var i : Integer;
 begin
 NbLignes:=0; // v3.0.5
 for i:=0 to NBMAXLIGNESBUS-1 do
  begin
  Ligne[i]:=false;
  NumLigne[i]:=0;
  end; 
 end;
// ----------------------------------------------------------------------------
procedure arret_bus.AjouteLigneBus(n : Integer);
 begin
  NumLigne[NbLignes]:=n;
  Inc(NbLignes);
  Ligne[n-1]:=true;
 end;
// ----------------------------------------------------------------------------
function arret_bus.stListeLignesBus : String; // v3.0.5
var i : Integer;
    stListe : String;
 begin
  for i:=0 to NbLignes-1 do
   begin
    if stListe='' then
     stListe:=IntToStr(NumLigne[i])
    else
     stListe:=stListe+','+IntToStr(NumLigne[i]);
   end;
 Result:=stListe;
 end;
// ----------------------------------------------------------------------------
function arret_bus.Charge(hfile : Integer) : Boolean;
 begin
  Result:=(FileRead(hfile, Numero, sizeof(Numero))>0) and
          (FileRead(hfile, x, sizeof(x))>0) and
          (FileRead(hfile, y, sizeof(y))>0) and
          (FileRead(hfile, Ligne, sizeof(Ligne))>0) and
          (FileRead(hfile, NbLignes, sizeof(NbLignes))>0) and
          (FileRead(hfile, NumLigne, sizeof(NumLigne))>0);
 end;
// ----------------------------------------------------------------------------
function arret_bus.Sauve(hfile : Integer) : Boolean;
 begin
  Result:=(FileWrite(hfile, Numero, sizeof(Numero))>0) and
          (FileWrite(hfile, x, sizeof(x))>0) and
          (FileWrite(hfile, y, sizeof(y))>0) and
          (FileWrite(hfile, Ligne, sizeof(Ligne))>0) and
          (FileWrite(hfile, NbLignes, sizeof(NbLignes))>0) and
          (FileWrite(hfile, NumLigne, sizeof(NumLigne))>0);
 end;
// ----------------------------------------------------------------------------
procedure arret_bus.Verifie(var stMsgErr : String);
var i : Integer;
    stSource : String;
 begin
  stSource:=Format('Arrêt de bus n°%d (%d,%d)', [Numero, x, y]);
  if Numero<0 then
   stMsgErr:=stSource+Format(': numéro incorrect (%d)'#13#10, [Numero]);
  VerifiePosition(stMsgErr, stSource, x, y, PEUT_ETRE_INDEFINI);
  if (NbLignes<0) or (NbLignes>NBMAXLIGNESBUS) then
   stMsgErr:=stSource+Format(': nombre de lignes de bus incorrect (%d)'#13#10, [NbLignes]);
  for i:=0 to NbLignes-1 do
   if Ligne[i] and
      ((NumLigne[i]<0) or (NumLigne[i]>NBMAXLIGNESBUS)) then
    stMsgErr:=stSource+Format(': numéro de %d° ligne de bus incorrect (%d)'#13#10, [i+1, NbLignes]);
 end;
//-----------------------------------------------------------------------------
// Classe Ligne de bus
//-----------------------------------------------------------------------------
procedure ligne_bus.Initialise;
var i : Integer;
 begin
  NbBus:=0; NbArrets:=0;
  for i:=0 to NBMAXARRETSBUSPARLIGNE-1 do NumArret[i]:=0;
  for i:=0 to NBMAXBUSPARLIGNE-1 do NumBus[i]:=0;
 end;
//-----------------------------------------------------------------------------
constructor ligne_bus.Create(Num : Integer);
 begin
  AffecteNumero(Num);
  Initialise;
 end;
//-----------------------------------------------------------------------------
procedure ligne_bus.AffecteNumero(Num : Integer);
 begin
  Numero:=Num;
 end;
//-----------------------------------------------------------------------------
procedure ligne_bus.AjouteBus(NumeroBus : Integer);
 begin
  NumBus[NbBus]:=NumeroBus;
  Inc(NbBus);
 end;
//-----------------------------------------------------------------------------
destructor ligne_bus.Destroy;
 begin
 end;
//-----------------------------------------------------------------------------
function ligne_bus.Charge(hfile : Integer) : Boolean;
 begin // Attention : on ne stocke par le nombre et les n° de bus (calculés avant simul)
  Result:=(FileRead(hfile, Numero, sizeof(Numero))>0) and
          (FileRead(hfile, NbArrets, sizeof(NbArrets))>0) and
          (FileRead(hfile, NumArret, sizeof(NumArret))>0);
 end;
// ----------------------------------------------------------------------------
function ligne_bus.Sauve(hfile : Integer) : Boolean;
 begin
  Result:=(FileWrite(hfile, Numero, sizeof(Numero))>0) and
          (FileWrite(hfile, NbArrets, sizeof(NbArrets))>0) and
          (FileWrite(hfile, NumArret, sizeof(NumArret))>0);
 end;
// ----------------------------------------------------------------------------
procedure ligne_bus.Verifie(var stMsgErr : String);
var i : Integer;
    stSource : String;
 begin
  stSource:=Format('Ligne de bus n°%d', [Numero]);
  if Numero<0 then
   stMsgErr:=stSource+Format(': numéro incorrect (%d)'#13#10, [Numero]);
  if (NbArrets<0) or (NbArrets>NBMAXARRETSBUSPARLIGNE) then
   stMsgErr:=stSource+Format(': nombre d''arrêts de bus incorrect (%d)'#13#10, [NbArrets]);
  for i:=0 to NbArrets-1 do
   if ((NumArret[i]<0) or (NumArret[i]>cv.NbArretsBus)) then
    stMsgErr:=stSource+Format(': numéro du %d° arrêt de bus incorrect (%d)'#13#10, [i+1, NumArret[i]]);
 end;
//-----------------------------------------------------------------------------
// Classe Voie
//-----------------------------------------------------------------------------
procedure voie.Initialise;
var i : Integer;
 begin
  ToutDroit:=false;
  PassagePietons:=false;
  PassageBus:=false; // v3.0
  for i:=0 to 3 do
   begin
   Priorites[i]:=a_droite;
   NumFeu[i]:=0;
   if i<NBMAXPIETONSPARCASE then NumPieton[i]:=0;
   end;
  for i:=0 to NBMAXLIGNESBUS-1 do LigneBus[i]:=false; // v3.0.3
  DirPoss:=aucune;
  NbPietons:=0;
  NumProchVeh:=0;
  NumEtape:=0;
  NumVehicule:=0;
  NumBus:=0; // v3.0
 end{voie.Initialise};
//-----------------------------------------------------------------------------
function voie.v(d : direction) : pVoie; // v3.0
 begin
  Result:=cv.vxyd(x,y,d);
 end;
//-----------------------------------------------------------------------------
constructor voie.Create(x0, y0 : Integer);
 begin
 DejaVenu:=false;
 Definit(x0, y0);
 end;
//-----------------------------------------------------------------------------
destructor voie.Destroy;
 begin
 end;
//-----------------------------------------------------------------------------
procedure voie.Definit(x0, y0 : Integer);
 begin
 x:=x0;
 y:=y0;
 Initialise;
 end;
//-----------------------------------------------------------------------------
function voie.PrepareCalculDistances : Boolean; // v3.0 : inclut également la préparation des distances aux arrêts de bus
var i, j, nd, ne, nab : Integer;
 begin
  nd:=NbDir[DirPoss];
  ne:=cv.NbEtapes;
  nab:=cv.NbArretsBus; // v3.0
  DejaVenu:=false;
  try
    if (nd>0) then
     begin
     if (ne>0) then
      begin
      SetLength(DistEtape, ne*sizeof(ArrayInt));
      for i:=0 to ne-1 do // Puis le nombre de directions possibles
       begin
       SetLength(DistEtape[i], nd*sizeof(Integer));
       for j:=0 to nd-1 do DistEtape[i, j]:=DIST_INDEFINIE;
       end{for i};
      end{if ne>0};
     if (nab>0) then
      begin
      SetLength(DistArretBus, nab*sizeof(ArrayInt));
      for i:=0 to nab-1 do // Puis le nombre de directions possibles
       begin
       SetLength(DistArretBus[i], nd*sizeof(Integer));
       for j:=0 to nd-1 do DistArretBus[i, j]:=DIST_INDEFINIE;
       end{for i};
      end{if nab>0};
     end{if nd>0};
    Result:=true;
  except
   Result:=false;
  end{try};
end{voie.PrepareCalculDistances};
//-----------------------------------------------------------------------------
function voie.PrepareCalculAttenteTrafic : Boolean;
var i, j, ne : Integer;
 begin
  ne:=cv.NbEtapes;
  try
    if ne>0 then
     begin
     SetLength(Attente, (ne+1)*sizeof(ArrayInt));
     for i:=0 to ne do // Puis les étapes d'arrivée nombre de directions possibles
      begin
      SetLength(Attente[i], (ne+1)*sizeof(Integer));
      for j:=0 to ne do Attente[i, j]:=0;
      end{for i};
     SetLength(Trafic, (ne+1)*sizeof(ArrayInt));
     for i:=0 to ne do // Puis les étapes d'arrivée nombre de directions possibles
      begin
      SetLength(Trafic[i], (ne+1)*sizeof(Integer));
      for j:=0 to ne do Trafic[i, j]:=0;
      end{for i};
     end{if};
    Result:=true;
  except
   Result:=false;
  end{try};
 end;
//-----------------------------------------------------------------------------
procedure voie.CalculeProchainVehiculeOuBus;  // v3.0 : tient compte des bus
var invd, MaxNivP, NumVV, NumBV : Integer;
    NivPriorite : array [direction] of Integer;
    d, DirCrt, DirAuCarrefour : direction;
    v : pVoie;
 begin // Rq : Nécessite de connaître les 2 prochaines directions de chaque véhicule/bus
  MaxNivP:=0;
  for d:=indefinie to ouest do NivPriorite[d]:=0;
  NumProchVeh:=0; // Aucun par défaut;
  // 1. S'il y a un piéton, aucun ne peut arriver
  if NbPietons>0 then Exit;
  // 1bis. S'il y a déjà un véhicule et que ce n'est pas une étape, aucun ne peut arriver
  if (NumVehicule>0) and (NumEtape=0) then Exit;
  // 1ter. S'il y a déjà un bus, aucun ne peut arriver. v3.0
  if (NumBus>0) then Exit; 
  for d:=nord to ouest do
   begin
    invd:=Integer(InvDir[d])-1;
    v:=cv.vxyd(x,y,d);
    NumVV:=v.NumVehicule;
    if v.EstTeteBus then NumBV:=v.NumBus else NumBV:=0; // v3.0
    if NumVV>0 then // 1. SOIT un Vehicule voisin arrivant sur la case ? Priorité 1
     begin
     NivPriorite[d]:=Ord((cv.Vehicules[NumVV-1].Dir=InvDir[d]) and  // Qui arrive sur la case...
                         cv.TourDeDeplacementVehicule(NumVV-1) and  // Et que c'est son tour de déplacement... (multivitesse : version 1.5)
                         ((NumVehicule=0) or  // alors... Soit y a pas de véhicule sur la case,
                          ((NumEtape>0) and   // soit y en a une mais c'est une étape...
                           (cv.Vehicules[NumVV-1].NumEtapeArrivee=NumEtape)))); // et c'est l'arrivée
     if NivPriorite[d]>0 then
      begin
       if cv.Vehicules[NumVV-1].NivPriorite=normal then
        begin
         // 2. Sont-elles obligées de s'arrêter (stop non marqué ou feu non vert) ? Priorité 2
         Inc(NivPriorite[d], Ord(((v.Priorites[invd]=stop) and (cv.Vehicules[NumVV-1].TourDrnDepl>cv.TourCrt-2)) or
                                 ((v.Priorites[invd]=feux) and (cv.Feux[v.NumFeu[invd]-1].Etat>vert))));
         // 3. Doivent-elles céder le passage (clp ou stop marqué) ? Priorité 3
         Inc(NivPriorite[d], 2*Ord((v.Priorites[invd]=cedez_le_passage) or
                                   ((v.Priorites[invd]=stop) and (cv.TourCrt-cv.Vehicules[NumVV-1].TourDrnDepl>=2))));
         // 4. Véhicules sur voie à priorité à droite (ou feu inactif/vert) ? Priorité 4
         Inc(NivPriorite[d], 3*Ord((v.Priorites[invd]=a_droite) or
                                   ((v.Priorites[invd]=feux) and (cv.Feux[v.NumFeu[invd]-1].Etat<orange))));
        end{if normal}
       else // 5. Véhicule prioritaire ? Urgence : Priorité 6 ; Police : Priorité 7
        Inc(NivPriorite[d], 5+Integer(cv.Vehicules[NumVV-1].NivPriorite));
      end{if Priorite};
     end{if NumVV>0}
    else // 1bis. SOIT un Bus voisin arrivant sur la case ? Priorité 1. v3.0
     if (NumBV>0) and (NumVehicule=0) then
      begin
      NivPriorite[d]:=Ord((cv.Autobus[NumBV-1].Dir=InvDir[d]) and  // 1 Bus qui arrive sur la case...
                          cv.TourDeDeplacementBus(NumBV-1) and  // Et que c'est son tour de déplacement... (multivitesse)
                          (cv.TourCrt>=cv.Autobus[NumBV-1].TourDepartArretSvt) and // ET que c'est son tour de départ vers le prochain arrêt
                          (NumBus=0));
      if NivPriorite[d]>0 then
       begin
        // 2. Sont-elles obligées de s'arrêter (stop non marqué ou feu non vert) ? Priorité 2
        Inc(NivPriorite[d], Ord(((v.Priorites[invd]=stop) and (cv.Autobus[NumBV-1].TourDrnDepl>cv.TourCrt-2)) or
                                ((v.Priorites[invd]=feux) and (cv.Feux[v.NumFeu[invd]-1].Etat>vert))));
        // 3. Doivent-elles céder le passage (clp ou stop marqué) ? Priorité 3
        Inc(NivPriorite[d], 2*Ord((v.Priorites[invd]=cedez_le_passage) or
                                  ((v.Priorites[invd]=stop) and (cv.TourCrt-cv.Autobus[NumBV-1].TourDrnDepl>=2))));
        // 4. Véhicules sur voie à priorité à droite (ou feu inactif/vert) ? Priorité 4
        Inc(NivPriorite[d], 3*Ord((v.Priorites[invd]=a_droite) or
                                  ((v.Priorites[invd]=feux) and (cv.Feux[v.NumFeu[invd]-1].Etat<orange))));
       end{if NivPriorite}
      end{if NumBV>0}
   end{for d};

  // 5. Entre véhicules prioritaires (V.P.) :
  //    V.P. tournant à droite ? Priorité 5
  //    V.P. allant tout droit et pas de V.P. venant de droite ? Priorité 5
  //    V.P. tournant à gauche et pas de V.P. venant de la droite ou de devant ? Priorité 5
  for d:=nord to ouest do
   begin
   if NivPriorite[d]=4 then
    begin
     v:=cv.vxyd(x,y,d);
     NumVV:=v.NumVehicule;
     if v.EstTeteBus then NumBV:=v.NumBus else NumBV:=0; // v3.0
     if NumVV>0 then
      begin
      DirCrt:=cv.Vehicules[NumVV-1].Dir;
      DirAuCarrefour:=cv.Vehicules[NumVV-1].ProchaineDirectionAuCarrefour;
      end
     else
      if NumBV>0 then // v3.0
       begin
       DirCrt:=cv.Autobus[NumBV-1].Dir;
       DirAuCarrefour:=cv.Autobus[NumBV-1].ProchaineDirectionAuCarrefour;
       end
      else
       begin
       DirCrt:=indefinie;
       DirAuCarrefour:=indefinie;
       end;
     Inc(NivPriorite[d], Ord((DirAuCarrefour=ADroiteDe[DirCrt]) or
                             ((DirAuCarrefour=DirCrt) and
                              (NivPriorite[ADroiteDe[DirCrt]]<4)) or
                             ((DirAuCarrefour=AGaucheDe[DirCrt]) and
                              (NivPriorite[ADroiteDe[DirCrt]]<4) and
                              (NivPriorite[DirCrt]<4))));
    end;
   end;
  for d:=nord to ouest do
   if NivPriorite[d]>MaxNivP then
    begin
     MaxNivP:=NivPriorite[d];
     NumProchVeh:=cv.vxyd(x,y,d).NumVehicule;
     NumProchBus:=cv.vxyd(x,y,d).NumBus;
    end;
 end;
//-----------------------------------------------------------------------------
procedure voie.DeplaceVehiculeOuBus; // v3.0 : tient compte des bus
 begin
  if (NumProchVeh>0) and cv.Vehicules[NumProchVeh-1].PeutPasser then
   begin  // Si le prochain véhicule peut arriver sur la case...
    cv.v[cv.Vehicules[NumProchVeh-1].x, cv.Vehicules[NumProchVeh-1].y].NumVehicule:=0; // Effacée de la case d'origine
    frmSimulation.RedessineCase(cv.Vehicules[NumProchVeh-1].x, cv.Vehicules[NumProchVeh-1].y, false);
    if (NumEtape=0) or (NumEtape<>cv.Vehicules[NumProchVeh-1].NumEtapeArrivee) then
     begin
      cv.PlaceVehicule(x, y, NumProchVeh); // v2.2.7 : Inclut les stats d'Attente/Trafic
      NumVehicule:=NumProchVeh;
     end
    else // Etape : NumVehicule est réservé pour les véhicules qui partent de l'étape uniquement
     begin
      Inc(cv.NbToursParcourus, ( cv.TourCrt-
                                 cv.Vehicules[NumProchVeh-1].TourDepart-
                                 cv.Vehicules[NumProchVeh-1].NbToursRepos- // v2.2.4
                                 1));
      Inc(cv.NbCasesParcourues, cv.Vehicules[NumProchVeh-1].NbCasesParcourues+1);
      cv.PlaceVehicule(-1, -1, NumProchVeh); // v2.2.7 : Inclut les stats d'Attente/Trafic
      Inc(cv.NbVehiculesArrives);
     end;
    Inc(cv.NbVehiculesDeplaces);
    Inc(cv.Vehicules[NumProchVeh-1].NbCasesParcourues);
    cv.Vehicules[NumProchVeh-1].TourDrnDepl:=cv.TourCrt;
    frmSimulation.RedessineCase(x, y, false);
    cv.Vehicules[NumProchVeh-1].DirDrnDepl:=cv.Vehicules[NumProchVeh-1].Dir;
    NumProchVeh:=0;
   end;
  if (NumProchBus>0) and cv.Autobus[NumProchBus-1].PeutPasser then // v3.0
   begin // Si le prochain bus peut arriver sur la case...
   NumBus:=NumProchBus;
   cv.PlaceBus(x, y, NumProchBus);
   NumProchBus:=0;
   end;
 end;
//-----------------------------------------------------------------------------
function voie.PietonPeutAller(DirPieton : direction) : Boolean;
 begin
  Result:= (NbPietons<NBMAXPIETONSPARCASE) and
           (NumVehicule=0) and
           (NumBus=0) and // v3.0
           (PassagePietons or (DirPoss=aucune)) and
           ((NumPieton[0]=0) or
            (((cv.Pietons[NumPieton[0]-1].DemiCase>0) or
              (cv.Pietons[NumPieton[0]-1].Dir<>DirPieton)) and
             ((cv.Pietons[NumPieton[0]-1].DemiCase=0) or
              (InvDir[cv.Pietons[NumPieton[0]-1].Dir]<>DirPieton)))) and
           ((NumPieton[1]=0) or
            (((cv.Pietons[NumPieton[1]-1].DemiCase>0) or
              (cv.Pietons[NumPieton[1]-1].Dir<>DirPieton)) and
             ((cv.Pietons[NumPieton[1]-1].DemiCase=0) or
              (InvDir[cv.Pietons[NumPieton[1]-1].Dir]<>DirPieton))));
 end;
//-----------------------------------------------------------------------------
function voie.FaitDescendrePieton(NumPietonAFaireDescendre : Integer) : Boolean; // v3.0
var d : direction;
    Voie : pVoie;
    p : pPieton;
    APuDescendre : Boolean;
 begin
  if NbPietons<NBMAXPIETONSPARCASE then
   begin
    AjoutePieton(NumPietonAFaireDescendre);
    p:=@(cv.Pietons[NumPietonAFaireDescendre]);
    Dec(cv.Autobus[p.NumBus-1].NbPersonnes);
    p.x:=x; p.y:=y; p.NumBus:=0; p.VeutDescendre:=false;
    RedessineCase(false);
    Result:=true;
   end
  else
   begin
    APuDescendre:=false;
    d:=nord;
    while not APuDescendre and (d<=ouest) do
     begin
     Voie:=v(d);
     if (Voie.DirPoss=aucune) or
        (Voie.PassagePietons and
         (Voie.NumVehicule>0) and
         (Voie.NumBus>0)) then
      APuDescendre:=Voie.FaitDescendrePieton(NumPietonAFaireDescendre);   
     Inc(d);
     end;
    Result:=APuDescendre; 
   end{else};
 end;
//-----------------------------------------------------------------------------
function voie.AjoutePieton(NumPietonAAjouter : Integer) : Boolean;
var i : Integer;
 begin
  if NbPietons<NBMAXPIETONSPARCASE then
   begin
   i:=0;
   while (NumPieton[i]>0) and (i<NBMAXPIETONSPARCASE) do Inc(i);
   if (i<NBMAXPIETONSPARCASE) then
    begin
    NumPieton[i]:=NumPietonAAjouter+1;
    Inc(NbPietons);
    Result:=true;
    end
   else
    Result:=False;
   end{if NbPietons}
  else
   Result:=false;
 end;
//-----------------------------------------------------------------------------
function voie.RetirePieton(NumPietonARetirer : Integer) : Boolean;
var i : Integer;
 begin
  if NbPietons>0 then
   begin
    i:=0;
    while (NumPieton[i]<>NumPietonARetirer+1) and (i<NBMAXPIETONSPARCASE) do Inc(i);
    if i<NBMAXPIETONSPARCASE then
     begin
     NumPieton[i]:=0;
     Dec(NbPietons);
     Result:=true;
     end
    else
     Result:=false;
   end{if NbPietons>0}
  else
   Result:=false;
 end{voie.RetirePieton};
//-----------------------------------------------------------------------------
procedure voie.DeplacePietons; // v3.0 : Inclut l'attente aux arrêts de bus, la montée et la descente du bus
var DirTrv : Boolean;
    i, d, dd : Integer;
    p, pv : pPieton;
    NvDir : direction;
 begin
  for i:=0 to NBMAXPIETONSPARCASE-1 do
   if (NumPieton[i]>0) and
      (cv.Pietons[NumPieton[i]-1].NumBus=0) and // v3.0 : Ne doit pas être dans un bus
      (cv.Pietons[NumPieton[i]-1].TourDrnDepl<cv.TourCrt) then
    begin
     p:=@(cv.Pietons[NumPieton[i]-1]);
     NvDir:=indefinie;
     if p.ArretBusTrv and (cv.vxyd(x, y, p.Dir).NumArretBus>0) then // v3.0
      begin // Si arrêt de bus trouvé ET qu'il arrive dessus ALORS on attend le bus (ça bloque le piéton)
       p.ArretBusTrv:=false;
       p.NumArretBus:=cv.vxyd(x, y, p.Dir).NumArretBus;
       p.AttendBus:=true;
       p.TourAttBus:=cv.TourCrt;
      end;
     if p.AttendBus and (p.TourAttBus+cv.NbMaxToursAttenteBus<cv.TourCrt) then // v3.0
      begin // Si attente de bus tro longue (paramètre), il abandonne
       p.ArretBusTrv:=false;
       p.NumArretBus:=0;
       p.AttendBus:=false;
       p.TourAttBus:=0;
      end;
     if not p.AttendBus and // Le piéton n'attend pas de bus ET
        not p.PsgPtTrv and // il ne se dirige NI vers un passage piétons
        not p.ArretBusTrv then             // NI vers un arrêt de bus
      begin // 1. Recherche de passages piétons
       if (cv.ProbaDirPsgPt>0) and // SI Recherche de passage piétons il y a ET
          (cv.CherchePassagePietons(x, y, sens(2-Integer(p.Dir) mod 2), NvDir)>indefinie) and // Passage piéton trouvé ET
          (random(100)<cv.ProbaDirPsgPt) then // Probabilité d'y aller (paramètre) ALORS
        begin // Il va vers le passage piéton trouvé
        p.Dir:=NvDir;
        p.PsgPtTrv:=true; // Indique qu'il est en train d'aller vers un passage piéton (inhibe les futures recherches)
        end
       else // 2. v3.0 : Recherche d'arrêt de bus
        if (cv.ProbaDirArretBus>0) and // SI recherche d'arrêt de bus il y a ET
           (cv.ChercheArretBus(x, y, sens(2-Integer(p.Dir) mod 2), NvDir)>indefinie) and // Arrêt de bus trouvé ET
           (random(100)<cv.ProbaDirArretBus) then // Probabilité d'y aller (paramètre) ALORS
         begin // Il va vers le passage piéton trouvé
         p.Dir:=NvDir;
         p.ArretBusTrv:=true; // Indique qu'il est en train d'aller vers un arrêt de bus (inhibe les futures recherches)
         end
      end{if not not not};
     if (NvDir=indefinie) and not p.AttendBus then // La direction n'a pas changé et aucun bus attendu (il marche tranquillement)
      begin  // Il se déplace
       if p.DemiCase>0 then // Demi-case et même direction : il sort de la case
        if cv.vxyd(x,y,p.Dir).PietonPeutAller(p.Dir) then
         cv.DeplacePieton( NumPieton[i]-1,
                           (x+dx[p.Dir]) mod NBX,
                           (y+dy[p.Dir]) mod NBY,
                           p.Dir)
        else // Peut pas sortir : on cherche une autre direction à gauche ou à droite (au sort)
         begin
          if cv.TourCrt-cv.Pietons[NumPieton[i]-1].TourDrnDepl>1+cv.AttenteMaxVeh div 2 then
           begin // S'il a assez attendu (Paramètre AttenteVéhicule/2)
           DirTrv:=false;
           dd:=1-2*random(2);
           d:=2-dd;
           while not DirTrv and (d>0) and (d<NBDIRS) do
            begin
            NvDir:=direction(1+(Integer(p.Dir)-1+d) mod NBDIRS);
            DirTrv:=cv.vxyd(x,y,NvDir).PietonPeutAller(NvDir);
            if DirTrv then
             begin
             p.AnnuleRechercheEnCours; // v3.0 : Toute recherche est annulée car la direction a changé
             cv.DeplacePieton( NumPieton[i]-1,
                               (x+dx[NvDir]) mod NBX,
                               (y+dy[NvDir]) mod NBY,
                               NvDir);
             end;
            Inc(d, dd);
            end{while};
           end{if};
         end{else}
       else // Ben c'est la demi-case...
        begin
         // 1. On regarde si on peut passer la demi-case not
         if NumPieton[1-i]>0 then
          begin
           pv:=@(cv.Pietons[NumPieton[1-i]-1]); // pv comme piéton voisin
           if ((((pv.Dir=p.Dir) and
                 (pv.DemiCase>0)) or
                ((pv.Dir=InvDir[p.Dir]) and
                 (pv.DemiCase=0))) and
               (cv.TourCrt-cv.Pietons[NumPieton[i]-1].TourDrnDepl>1+cv.AttenteMaxVeh div 2)) then
            begin // On choisit une direction à gauche ou à droite (sûre) s'il a assez attendu
            p.AnnuleRechercheEnCours; // v3.0 : Toute recherche est annulée car la direction a changé
            p.Dir:=direction(1+(Integer(p.Dir)+1+2*random(2)) mod NBDIRS);
            end;
          end;
         Inc(p.DemiCase);
         Inc(p.DemiCasesParcourues); // v3.0
         p.TourDrnDepl:=cv.TourCrt;
        end;
      end{if NvDir=indefinie}
    end{if NumPieton>0};
  frmSimulation.RedessineCase(x, y, false);
 end;
//-----------------------------------------------------------------------------
procedure voie.RetireArretBus; // v3.0
var Numero : Integer;
    d : direction;
 begin
  Numero:=NumArretBus;
  NumArretBus:=0;
  if frmSimulation<>nil then
   frmSimulation.RedessineCase(x, y, true);
  for d:=nord to ouest do
   if cv.vxyd(x,y,d).NumArretBus=Numero then
    cv.vxyd(x,y,d).RetireArretBus;
 end;
//-----------------------------------------------------------------------------
function voie.EstTeteArretBus : Boolean; // v3.0
 begin
  Result:=(NumArretBus>0) and
          (cv.ArretsBus[NumArretBus-1].x=x) and
          (cv.ArretsBus[NumArretBus-1].y=y);
 end;
//-----------------------------------------------------------------------------
function voie.EstTeteArretBus(NumeroArretBus : Integer) : Boolean; // v3.0
 begin
  Result:=(NumArretBus=NumeroArretBus) and
          (cv.ArretsBus[NumArretBus-1].x=x) and
          (cv.ArretsBus[NumArretBus-1].y=y);
 end;
//-----------------------------------------------------------------------------
function voie.EstTeteBus : Boolean; // v3.0
 begin
  Result:=(NumBus>0) and
          (cv.Autobus[NumBus-1].x=x) and
          (cv.Autobus[NumBus-1].y=y);
 end;
//-----------------------------------------------------------------------------
procedure voie.DefinitArretBus(n : Integer); // v3.0
 begin
  cv.DefinitArretBus(n, x, y);
 end;
//-----------------------------------------------------------------------------
procedure voie.RedessineCasesArretBus(d0 : direction); // v3.0
var d : direction; 
 begin
  if frmSimulation<>nil then frmSimulation.RedessineCase(x,y,false);
  if d0>indefinie then
   begin
   if cv.vxyd(x,y,d0).NumArretBus=NumArretBus then
    cv.vxyd(x,y,d0).RedessineCasesArretBus(d0);
   end
  else
   for d:=nord to ouest do
    if cv.vxyd(x,y,d).NumArretBus=NumArretBus then
     cv.vxyd(x,y,d).RedessineCasesArretBus(d);
 end;
//-----------------------------------------------------------------------------
function voie.EstDepotBus : Boolean; // v3.0
 begin
  Result:=(x=cv.DepotBus.x) and (y=cv.DepotBus.y);
 end;
//-----------------------------------------------------------------------------
procedure voie.CalculeDistanceEtape(e, Distance : Integer; DirOrig : direction);  // 0 <= e < NbEtapes
var d : direction;
    VoieCrt : pVoie;
 begin
  if DirOrig>indefinie then
   DistEtape[e, NumDirdp[DirOrig, DirPoss]]:=Distance;
  for d:=nord to ouest do
   begin
    VoieCrt:=cv.vxyd(x,y,d);
    if ((Integer(VoieCrt.DirPoss) and
         Integer(InvPossDir[d]))=
        Integer(InvPossDir[d])) and  // Si VoieCrt pointe sur l'étape ET
       (VoieCrt.DistEtape[e, NumDirdp[InvDir[d], VoieCrt.DirPoss]]>Distance+1) then // Distance indéfinie
     VoieCrt.CalculeDistanceEtape(e, Distance+1, InvDir[d]); // On lance le calcul de distance
   end;
 end;
//-----------------------------------------------------------------------------
procedure voie.CalculeDistanceArretBus(ab, Distance : Integer; DirOrig : direction);  // 0 <= ab < NbArretsbus
var d : direction;
    VoieCrt : pVoie;
 begin
  if DirOrig>indefinie then
   DistArretBus[ab, NumDirdp[DirOrig, DirPoss]]:=Distance;
  for d:=nord to ouest do
   begin
    VoieCrt:=cv.vxyd(x,y,d);
    if ((Integer(VoieCrt.DirPoss) and
         Integer(InvPossDir[d]))=
        Integer(InvPossDir[d])) and  // Si VoieCrt pointe sur l'arrêt de bus ET
       (VoieCrt.DistArretBus[ab, NumDirdp[InvDir[d], VoieCrt.DirPoss]]>Distance+1) then // Distance indéfinie
     VoieCrt.CalculeDistanceArretBus(ab, Distance+1, InvDir[d]); // On lance le calcul de distance
   end;
 end;
//-----------------------------------------------------------------------------
procedure voie.InitialiseInfosLignesBus; // v3.0
var i : Integer;
 begin
  for i:=0 to NBMAXLIGNESBUS-1 do LigneBus[i]:=false; // v3.0.3
 end;
//-----------------------------------------------------------------------------
procedure voie.RedessineCase(EffaceFond : Boolean); // v3.0
 begin
  frmSimulation.RedessineCase(x, y, EffaceFond);
 end;
//-----------------------------------------------------------------------------
function voie.Charge(hfile : Integer) : Boolean;
var i : Integer;
    Ok : Boolean;
 begin
  Ok:=(FileRead(hfile, x, sizeof(x))>0) and
      (FileRead(hfile, y, sizeof(y))>0) and
      (FileRead(hfile, DirPoss, sizeof(DirPoss))>0) and
      (FileRead(hfile, NumEtape, sizeof(NumEtape))>0) and
      (FileRead(hfile, ToutDroit, sizeof(ToutDroit))>0) and
      (FileRead(hfile, PassagePietons, sizeof(PassagePietons))>0) and
      ((VersionFichier<$300) or // v3.0
       ((FileRead(hfile, PassageBus, sizeof(PassageBus))>0) and
        (FileRead(hfile, NumArretBus, sizeof(NumArretBus))>0)));
  i:=0;
  while Ok and (i<NBDIRS) do
   begin
   Ok:=(FileRead(hfile, Priorites[i], sizeof(Priorites[i]))>0) and
       (FileRead(hfile, NumFeu[i], sizeof(NumFeu[i]))>0);
   Inc(i);
   end;
  Result:=Ok;
 end;
//-----------------------------------------------------------------------------
function voie.Sauve(hfile : Integer) : Boolean;
var i : Integer;
    Ok : Boolean;
 begin
  Ok:=(FileWrite(hfile, x, sizeof(x))>0) and
      (FileWrite(hfile, y, sizeof(y))>0) and
      (FileWrite(hfile, DirPoss, sizeof(DirPoss))>0) and
      (FileWrite(hfile, NumEtape, sizeof(NumEtape))>0) and
      (FileWrite(hfile, ToutDroit, sizeof(ToutDroit))>0) and
      (FileWrite(hfile, PassagePietons, sizeof(PassagePietons))>0) and
      (FileWrite(hfile, PassageBus, sizeof(PassageBus))>0) and // v3.0
      (FileWrite(hfile, NumArretBus, sizeof(NumArretBus))>0); // v3.0
  i:=0;
  while Ok and (i<NBDIRS) do
   begin
   Ok:=(FileWrite(hfile, Priorites[i], sizeof(Priorites[i]))>0) and
       (FileWrite(hfile, NumFeu[i], sizeof(NumFeu[i]))>0);
   Inc(i);
   end;
  Result:=Ok;
 end;
//-----------------------------------------------------------------------------
procedure voie.Verifie(var stMsgErr : String);
var i, xx, yy : Integer;
    stSource : String;
    d : direction;
 begin
  stSource:=Format('Case (%d,%d)', [x, y]);
  VerifiePosition(stMsgErr, stSource, x, y, DOIT_ETRE_DEFINI);
  VerifieDirPoss(stMsgErr, stSource, DirPoss);
  for i:=0 to 3 do
   begin
    d:=direction(i+1); // Permet de remplacer les direction(i+1)
    VerifiePriorite(stMsgErr, stSource+' ('+stDir[d]+')', Priorites[i]);
    if (NumFeu[i]>0) and (Priorites[i]<>feux) then
     stMsgErr:=stMsgErr+stSource+Format(': numéro de feu %s mais priorité différente de Feu (%d)'#13#10'', [stDir[d], Integer(Priorites[i])]);
    if (NumFeu[i]<0) or (NumFeu[i]>=cv.NbFeux) then
     stMsgErr:=stMsgErr+stSource+Format(': numéro de feu %s incorrect (%d)'#13#10'', [stDir[d], NumFeu[i]])
    else
     if NumFeu[i]>0 then
      begin
       cv.Feux[NumFeu[i]-1].Verifie(stMsgErr, stSource+Format(' Feu %s', [stDir[d]]));
       xx:=cv.Feux[NumFeu[i]-1].x;
       yy:=cv.Feux[NumFeu[i]-1].y;
       if (x<>xx) or (y<>yy) then
        stMsgErr:=stMsgErr+stSource+Format(': coordonnées du feu %s (%d,%d) différentes des coordonnées de la case'#13#10'', [stDir[d], xx, yy]);
      end;
   end;
 end;
//-----------------------------------------------------------------------------
// Classe Statistiques
// ----------------------------------------------------------------------------
constructor stats.Create;
 begin NbVehiculesDeplaces:=0; NbVehiculesArrives:=0; NbVehiculesSortis:=0; end;
procedure stats.Definit;
 begin NbVehiculesDeplaces:=cv.NbVehiculesDeplaces; NbVehiculesArrives:=cv.NbVehiculesArrives; NbVehiculesSortis:=cv.NbVehiculesSortis; end;
// ----------------------------------------------------------------------------
// Classe Centre-Ville
// ----------------------------------------------------------------------------
constructor centre_ville.Create(NbElementsParDefaut : Boolean);
var i, j : Integer;
 begin
  TourEnCours:=false;
  NbToursParcourus:=0;
  NbCasesParcourues:=0;
  TourCrt:=0;
  NbToursParSeconde:=2;
  NbVehiculesSortis:=0;
  NbVehiculesDeplaces:=0;
  NbVehiculesArrives:=0;
  DureeOrange:=0;
  NbEtapes:=0;
  NbVehicules:=0;
  NbBus:=0; // v3.0
  NbFeux:=0;
  AttenteMaxVeh:=10;
  NbVitesses:=1;
  NbToursStats:=100;
  TypeStats:=par_nombre;
  NbMaxCasesDetectPsgPt:=5; // v3.0.5
  ProbaDirPsgPt:=50;
  NbMaxCasesDetectArretBus:=5; // v3.0.5
  ProbaDirArretBus:=50; // v3.0
  ProbaArretBusDmd:=25; // v3.0
  NbMaxPersonnesBus:=100; // v3.0
  NbToursStopArretBus:=3; // v3.0.5
  NbMaxToursAttenteBus:=25; // v3.0
  VerifOk:=false;
  DistancesCalculees:=false;
  QuadrillageStats:=false;
  for i:=0 to NBX-1 do
   for j:=0 to NBY-1 do
    v[i, j]:=voie.Create(i, j);
  for i:=0 to NBMAXLIGNESBUS-1 do // v3.0
    LignesBus[i]:=ligne_bus.Create(i+1);
  DepotBus:=depot_bus.Create; // v3.0
  // Tableaux avec nombre par défaut;
  DefinitNbFeux(NBFEUXDEFAUT);
  DefinitNbEtapes(NBETAPESDEFAUT);
  DefinitNbVehicules(NBVEHICULESDEFAUT, DEFINIT_SEULEMENT); // v3.0.4. On n'alloue pas maintenant
  DefinitNbPietons(NBPIETONSDEFAUT, DEFINIT_SEULEMENT); // v3.0.4. On n'alloue pas maintenant
 end;
//-----------------------------------------------------------------------------
destructor centre_ville.Destroy;
var i, j :Integer;
 begin
  for i:=0 to NBX-1 do for j:=0 to NBY-1 do v[i, j].Destroy;
  for i:=0 to NbFeux-1 do if Feux[i]<>nil then Feux[i].Destroy;
  for i:=0 to NbEtapes-1 do if Etapes[i]<>nil then Etapes[i].Destroy;
  for i:=0 to NbPietons-1 do
   if Pietons[i]<>nil then
    Pietons[i].Destroy;
  for i:=0 to NbVehicules-1 do
   if Vehicules[i]<>nil then
    Vehicules[i].Destroy;
  for i:=0 to NBMAXLIGNESBUS-1 do if LignesBus[i]<>nil then LignesBus[i].Destroy; // v3.0
 end;
//-----------------------------------------------------------------------------
function centre_ville.DefinitNbFeux(n : Integer) : Integer;
var i : Integer;
begin
 try
  if n<NbFeux then for i:=n to NbFeux-1 do Feux[i].Destroy;
  SetLength(Feux, n*sizeof(feu));
  if n>NbFeux then for i:=NbFeux to n-1 do Feux[i]:=feu.Create(i+1);
  NbFeux:=n;
  Result:=NbFeux;
 except
  NbFeux:=0;
  Result:=0;
 end{try};
end;
//-----------------------------------------------------------------------------
function centre_ville.DefinitNbEtapes(n : Integer) : Integer;
var i : Integer;
begin
 try
  if n<NbEtapes then for i:=n to NbEtapes-1 do Etapes[i].Destroy;
  SetLength(Etapes, n*sizeof(etape));
  if n>NbEtapes then for i:=NbEtapes to n-1 do Etapes[i]:=etape.Create(i+1);
  NbEtapes:=n;
  Result:=NbEtapes;
 except
  NbEtapes:=0;
  Result:=0;
 end{try};
end;
//-----------------------------------------------------------------------------
function centre_ville.DefinitNbVehicules(n : Integer; Prepare : Boolean) : Integer;
var i : Integer;
begin
 try
  SetLength(Vehicules, n*sizeof(vehicule));
  if n>0 then
   begin
   for i:=0 to n-1 do if Vehicules[i]<>nil then Vehicules[i].Destroy;
   if Prepare then for i:=0 to n-1 do Vehicules[i]:=vehicule.Create(i+1);
   end;
  NbVehicules:=n;
  Result:=NbVehicules;
 except
  NbVehicules:=0;
  Result:=0;
 end{try};
end;
//-----------------------------------------------------------------------------
function centre_ville.DefinitNbBus(n : Integer; Prepare : Boolean) : Integer;
var i : Integer;
begin
 try
  SetLength(Autobus, n*sizeof(bus));
  if n>0 then
   begin
    for i:=0 to n-1 do if Autobus[i]<>nil then Autobus[i].Destroy;
    if Prepare then for i:=0 to n-1 do Autobus[i]:=bus.Create(i+1);
   end;
  NbBus:=n;
  Result:=NbBus;
 except
  NbBus:=0;
  Result:=0;
 end{try};
end;
//-----------------------------------------------------------------------------
function centre_ville.DefinitNbPietons(n : Integer; Prepare : Boolean) : Integer;
var i : Integer;
begin
 try
  SetLength(Pietons, n*sizeof(pieton));
  if n>0 then
   begin
    for i:=0 to n-1 do if Pietons[i]<>nil then Pietons[i].Destroy;
    if Prepare then for i:=0 to n-1 do Pietons[i]:=pieton.Create(i+1);
   end;
  NbPietons:=n;
  Result:=NbPietons;
 except
  NbPietons:=0;
  Result:=0;
 end{try};
end;
//-----------------------------------------------------------------------------
function centre_ville.DefinitNbLignesBus(n : Integer) : Integer; // v3.0
var i : Integer;
begin
 if n>NbLignesBus then
  for i:=NbLignesBus to n-1 do LignesBus[i].Initialise
 else
  for i:=NbLignesBus-1 downto n do LignesBus[i].Initialise;
 NbLignesBus:=n;
 Result:=NbLignesBus;
end;
//-----------------------------------------------------------------------------
function centre_ville.DefinitNbArretsBus(n : Integer) : Integer; // v3.0
var i : Integer;
begin
 try
  if n<NbArretsBus then
   for i:=n to NbArretsBus-1 do ArretsBus[i].Destroy;
  SetLength(ArretsBus, n*sizeof(ArretsBus));
  if n>NbArretsBus then
   for i:=NbArretsBus to n-1 do ArretsBus[i]:=arret_bus.Create(i+1);
  NbArretsBus:=n;
  Result:=NbArretsBus;
 except
  NbArretsBus:=0;
  Result:=0;
 end{try};
end;
//-----------------------------------------------------------------------------
function centre_ville.NbFeuxLibres : Integer;
var i, n : Integer;
 begin
  n:=0;
  for i:=0 to NbFeux-1 do Inc(n, Ord(not Feux[i].Defini));
  Result:=n;
 end;
//-----------------------------------------------------------------------------
function centre_ville.NumeroFeuLibre : Integer;
var i : Integer;
 begin
  i:=0;
  while (i<NbFeux) and Feux[i].Defini do Inc(i);
  Result:=(i+1)*Ord(i<NbFeux);
 end;
//-----------------------------------------------------------------------------
function centre_ville.NumeroEtapeLibre : Integer;
var i : Integer;
 begin
  i:=0;
  while (i<NbEtapes) and Etapes[i].Definie do Inc(i);
  Result:=(i+1)*Ord(i<NbEtapes);
 end;
//-----------------------------------------------------------------------------
function centre_ville.NumeroVehiculeLibre : Integer;
var i : Integer;
 begin
  i:=0;
  while (i<NbVehicules) and Vehicules[i].Defini do Inc(i);
  Result:=(i+1)*Ord(i<NbVehicules);
 end;
//-----------------------------------------------------------------------------
function centre_ville.NumeroPietonLibre : Integer;
var i : Integer;
 begin
  i:=0;
  while (i<NbPietons) and Pietons[i].Defini do Inc(i);
  Result:=(i+1)*Ord(i<NbPietons);
 end;
//-----------------------------------------------------------------------------
function centre_ville.ArretBusExistant(x, y : Integer) : Integer; // v3.0
var i : Integer;
    d : direction;
    Voie : pVoie;
 begin
  i:=0;
  for d:=nord to ouest do
   begin
   Voie:=vxyd(x,y,d);
   if (Voie.NumArretBus>0) and
      ((Integer(v[x,y].DirPoss) and Integer(PossDir[d])>0) or // On peut aller sur la case Voie OU
       (Integer(Voie.DirPoss) and Integer(InvPossDir[d])>0)) then // venir de la case Voie
    begin
     if i=0 then
      i:=Voie.NumArretBus;
     if (Voie.NumArretBus=i) and // Si la case contiguë est un arrêt de bus ET
        (Voie.v(direction(1+(Integer(d)+2) mod NBDIRS)).DirPoss=aucune) and // il y a un trottoir à sa gauche (en regardant vers l'arrière de l'arrêt de bus) ET
        (Integer(Voie.DirPoss) and Integer(InvPossDir[d])>0) then // Si d est dans le sens du bus ALORS
      ArretsBus[i-1].Definit(x, y); // (x,y) devient la tête de l'arrêt de bus Voie.NumArret
    end{if};
   end{for};
  Result:=i; 
 end;
//-----------------------------------------------------------------------------
function centre_ville.NumeroArretBusLibre(x, y : Integer) : Integer; // v3.0
var i : Integer;
 begin
  i:=ArretBusExistant(x, y);
  if i>0 then
   Result:=i // L'arrêt existe déjà (case contiguë qui communique : va ou vient)
  else
   begin // C'est un nouvel arrêt de bus
   i:=0; while (i<NbArretsBus-1) and ArretsBus[i].Defini do Inc(i);
   Result:=(i+1)*Ord(i<NbArretsBus);
   end;
 end;
//-----------------------------------------------------------------------------
function centre_ville.AjouteFeu(x, y : Integer; d : direction) : Integer;
var i : Integer;
 begin
  i:=NumeroFeuLibre;
  if i>0 then
   begin
    Feux[i-1].Definit(x, y, d);
    v[x, y].NumFeu[Integer(d)-1]:=i;
    // Définition des durées par défaut
    Feux[i-1].DureeVert:=DureeVert;
    Feux[i-1].DureeRouge:=DureeRouge;
   end;
  Result:=i;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.SupprimeFeu(n : Integer);
 begin
  if (n>-1) and (n<NbFeux) then
   begin
    v[Feux[n].x, Feux[n].y].NumFeu[Integer(Feux[n].Dir)-1]:=0;
    Feux[n].Initialise();
   end;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.SupprimeFeuxVoie(x, y : Integer);
var Voie : pVoie;
    i : Integer;
 begin
  Voie:=@(v[x, y]);
  for i:=0 to 3 do
   if Voie.NumFeu[i]>0 then
    SupprimeFeu(Voie.NumFeu[i]-1);
 end;
//-----------------------------------------------------------------------------
function centre_ville.AjouteEtape(x, y : Integer) : Integer;
var i : Integer;
 begin
  i:=NumeroEtapeLibre;
  if i>0 then
   begin
    Etapes[i-1].Definit(x, y);
    v[x, y].NumEtape:=i;
   end;
  Result:=i;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.SupprimeEtape(n : Integer);
 begin
  if (n>-1) and (n<NbEtapes) then
   begin
    v[Etapes[n].x, Etapes[n].y].NumEtape:=0;
    Etapes[n].Initialise();
   end;
 end;
//-----------------------------------------------------------------------------
function centre_ville.AjouteArretBus(x, y : Integer) : Integer; // v3.0
var i : Integer;
 begin
  i:=NumeroArretBusLibre(x, y);
  if i>0 then
   begin
    if not ArretsBus[i-1].Defini then
     ArretsBus[i-1].Definit(x, y);
    v[x,y].NumArretBus:=i;
   end;
  Result:=i;
 end;
//-----------------------------------------------------------------------------
function centre_ville.ExisteCaseArretBus(x, y : Integer) : Boolean; // v3.0
var Existe : Boolean;
    d : direction;
    i : Integer;
    Voie : pVoie;
 begin
  Existe:=false;
  i:=v[x,y].NumArretBus;
  for d:=nord to ouest do
   begin
    Voie:=vxyd(x,y,d);
    if Voie.NumArretBus=i then
     begin // On profite pour regarder si on change de tête d'arrêt de bus
      Existe:=true;
      if v[x,y].EstTeteArretBus then // SI c'était une tête d'arrêt de bus ALORS
       Voie.DefinitArretBus(i); // sa voisine prend la place. v3.0.3
     end{if};
   end{for};
  Result:=Existe;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.SupprimeArretBus(x, y : Integer); // v3.0
var i : Integer;
 begin // Supprime l'arrêt de bus sur une case seulement
  i:=v[x,y].NumArretBus;
  if (i>0) and (i<=NbArretsBus) then
   begin
    if not ExisteCaseArretBus(x, y) then // Si l'arrêt n'a pas d'autre case ALORS
     ArretsBus[i-1].Initialise; // on supprime l'arrêt de bus
    v[x,y].NumArretBus:=0;
   end;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.SupprimeArretBus(n : Integer); // v3.0
 begin // Supprime COMPLETEMENT l'arrêt de bus (sur TOUTES les cases)
  v[ArretsBus[n].x,ArretsBus[n].y].RetireArretBus; // Retire le n° d'arrêt de bus récursivement sur toutes les cases
  ArretsBus[n].Initialise; 
 end;
//-----------------------------------------------------------------------------
function centre_ville.SensPassagePietonsPossible(x, y : Integer) : sens;
var sns : sens;
 begin
  // 1. Sens suivant DirPoss (Directions de l'intérieur vers l'extérieur)
  sns:=SensPsgPt[v[x, y].DirPoss];
  // 2. Test des cases voisines (Directions de l'extérieur vers l'intérieur)
  case sns of
    vertical:   if (((Integer(vxyd(x,y,nord).DirPoss) and Integer(S))>0) or
                    ((Integer(vxyd(x,y,sud).DirPoss) and Integer(N))>0)) then
                 begin Result:=indefini; Exit; end;
    horizontal: if (((Integer(vxyd(x,y,est).DirPoss) and Integer(O))>0) or
                    ((Integer(vxyd(x,y,ouest).DirPoss) and Integer(E))>0)) then
                 begin Result:=indefini; Exit; end;
  else
   begin Result:=indefini; Exit; end;
  end{case of};
  Result:=sns;
 end;
//-----------------------------------------------------------------------------
function centre_ville.CherchePassagePietons(x, y : Integer; SensRecherche : sens; var NvDir : direction) : direction;
var i, j : Integer;
    d : direction;
    Dist : array [0..1] of Integer;
    Dir : array [0..1] of direction;
 begin
  for i:=0 to 1 do
   begin
   Dist[i]:=0;
   Dir[i]:=direction(3+2*i-Integer(SensRecherche));
   end;
  if (NbMaxCasesDetectPsgPt=0) or  // NbMaxCasesDetectPsgPt et
     (SensRecherche=indefini) then // SensRecherche
   begin
   Result:=indefinie; //  doivent être définis (horizontal|vertical ; >0)
   NvDir:=Result;
   Exit;
   end;
  for j:=0 to 1 do
   begin
    i:=1; d:=direction(3-Integer(SensRecherche)+2*j);
    while not vxynd(x,y,i,d).PassagePietons and
          (vxynd(x,y,i,d).DirPoss=aucune) and
          (i<=NbMaxCasesDetectPsgPt) do Inc(i);
    if (i<=NbMaxCasesDetectPsgPt) and
       vxynd(x,y,i,d).PassagePietons then
     Dist[j]:=i;
   end;
  case Ord(Dist[0]>0)+2*Ord(Dist[1]>0) of
    0: Result:=indefinie;
    1: Result:=Dir[0];
    2: Result:=Dir[1];
    3: if (Dist[0]=Dist[1]) then
        Result:=Dir[random(2)]
       else
        if Dist[0]<Dist[1] then
         Result:=Dir[0]
        else
         Result:=Dir[1];
  else Result:=indefinie;
  end{case of};
  NvDir:=Result;
 end;
//-----------------------------------------------------------------------------
function centre_ville.ChercheArretBus(x, y : Integer; SensRecherche : sens; var NvDir : direction) : direction; // v3.0
var i, j : Integer;
    d : direction;
    Dist : array [0..1] of Integer;
    Dir : array [0..1] of direction;
 begin
  for i:=0 to 1 do
   begin
   Dist[i]:=0;
   Dir[i]:=direction(3+2*i-Integer(SensRecherche));
   end;
  if (NbMaxCasesDetectArretBus=0) or  // NbMaxCasesDetectArretBus et
     (SensRecherche=indefini) then // SensRecherche
   begin
   Result:=indefinie; //  doivent être définis (horizontal|vertical ; >0)
   NvDir:=Result;
   Exit;
   end;
  for j:=0 to 1 do
   begin
    i:=1; d:=direction(3-Integer(SensRecherche)+2*j);
    while (vxynd(x,y,i,d).NumArretBus=0) and
          (vxynd(x,y,i,d).DirPoss=aucune) and
          (i<=NbMaxCasesDetectArretBus) do Inc(i);
    if (i<=NbMaxCasesDetectArretBus) and
       (vxynd(x,y,i,d).NumArretBus>0) then
     Dist[j]:=i;
   end;
  case Ord(Dist[0]>0)+2*Ord(Dist[1]>0) of
    0: Result:=indefinie;
    1: Result:=Dir[0];
    2: Result:=Dir[1];
    3: if (Dist[0]=Dist[1]) then
        Result:=Dir[random(2)]
       else
        if Dist[0]<Dist[1] then
         Result:=Dir[0]
        else
         Result:=Dir[1];
  else Result:=indefinie;
  end{case of};
  NvDir:=Result;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.DefinitArretBus(n, x, y : Integer); // v3.0
 begin
  if (n>0) and (n<=NbArretsbus) then
   ArretsBus[n-1].Definit(x, y);
 end;
//-----------------------------------------------------------------------------
function centre_ville.DirectionArretBus(x, y : Integer) : direction; // v3.0
var Ambiguite : Boolean;
    d, Dir : direction;
 begin
  Ambiguite:=false;
  Dir:=indefinie;
  for d:=nord to ouest do // On prend la dernière possibilité en cas de litige
   if (Integer(v[x,y].DirPoss) and Integer(PossDir[d])=0) and // Si pas de déplacement possible vers d ET
      (vxyd(x,y,d).DirPoss=aucune) and // Mur vers d ET
      (Integer(v[x,y].DirPoss) and Integer(PossDir[direction(1+(Integer(d)+2) mod NBDIRS)])>0) then // Direction possible à gauche (dans le sens de la circulation de la voie)
    begin
     Ambiguite:=(Dir>indefinie);
     Dir:=d;
    end{if};
  if not Ambiguite then Result:=Dir else Result:=indefinie;
 end;
//-----------------------------------------------------------------------------
function centre_ville.PositionArretBus(x, y : Integer; d : direction) : position_arret_bus; // v3.0
 begin
  case   Ord(vxyd(x,y,direction(1+(Integer(d)+2) mod NBDIRS)).NumArretBus=v[x,y].NumArretBus)+
       2*Ord(vxyd(x,y,direction(1+Integer(d) mod NBDIRS)).NumArretBus=v[x,y].NumArretBus) of
   1: Result:=queue;
   2: Result:=tete;
   3: Result:=milieu;
  else Result:=tete;
  end{case of};
 end;
//-----------------------------------------------------------------------------
function centre_ville.ArretsBusVoisinsDifferents(x, y : Integer) : Boolean; // v3.0
var Voie : pVoie;
    DiffTrv : Boolean;
    d : direction;
    i : Integer;
 begin
 DiffTrv:=false; i:=0;
 for d:=nord to ouest do
  begin
  Voie:=vxyd(x,y,d);
  if (Voie.NumArretBus>0) and
     ((Integer(v[x,y].DirPoss) and Integer(PossDir[d])>0) or // On peut y aller OU
      (Integer(Voie.DirPoss) and Integer(InvPossDir[d])>0)) then // en venir
   if i=0 then i:=Voie.NumArretBus else DiffTrv:=(i<>Voie.NumArretBus);
  end{for};
 Result:=DiffTrv;
 end;
//-----------------------------------------------------------------------------
function centre_ville.DirArretBusVoisin(x, y : Integer) : direction; // v3.0
var Voie : pVoie;
    d, DirArretBusVoisin : direction;
 begin
  DirArretBusVoisin:=indefinie;
  d:=nord; while (DirArretBusVoisin=indefinie) and (d<=ouest) do
  begin
  Voie:=vxyd(x,y,d);
  if (Voie.NumArretBus>0) and
     ((Integer(v[x,y].DirPoss) and Integer(PossDir[d])>0) or // On peut y aller OU
      (Integer(Voie.DirPoss) and Integer(InvPossDir[d])>0)) then // en venir
   DirArretBusVoisin:=d;
  Inc(d);
  end{for};
 Result:=DirArretBusVoisin;
 end;
//-----------------------------------------------------------------------------
function centre_ville.AjoutArretBusPossible(x, y : Integer) : Boolean; // v3.0
var d, DirArretVoisin : direction;
    Possible : Boolean;
 begin
 Possible:=false;
  if (v[x, y].DirPoss>aucune) and // C'est de la route ET
     not ArretsBusVoisinsDifferents(x, y) then // pas 2 arrêts de bus différents voisins
   begin
    DirArretVoisin:=DirArretBusVoisin(x, y);
    d:=nord;
    while not Possible and (d<=ouest) do
     begin
     if (Integer(v[x, y].DirPoss) and Integer(PossDir[d])=0) and // Si pas de direction possible vers d ET
        (vxyd(x,y,d).DirPoss=aucune) then // il y a un mur ALORS
      Possible:=((DirArretVoisin=indefinie) or // Soit 1 seul arrêt (d'un côté ou de l'autre) soit c'est le même n+ (ou nul les 2)
                 (DirArretVoisin=direction(1+Integer(d) mod NBDIRS)) or // Il doit être dans
                 (DirArretVoisin=direction(1+(Integer(d)+2) mod NBDIRS)) and // le même sens
                ((Ord(vxyd(x,y,direction(1+(Integer(d)+1) mod NBDIRS)).NumArretBus>0)+
                  Ord(vxyd(x,y,direction(1+(Integer(d)+3) mod NBDIRS)).NumArretBus>0)=1) or
                 (vxyd(x,y,direction(1+(Integer(d)+1) mod NBDIRS)).NumArretBus=
                  vxyd(x,y,direction(1+(Integer(d)+3) mod NBDIRS)).NumArretBus)));
     Inc(d);
     end;
    Result:=Possible;
   end{if}
  else Result:=false;
 end;
//-----------------------------------------------------------------------------
function centre_ville.SuppressionArretBusPossible(x, y : Integer) : Boolean; // v3.0
var d : direction;
    i, n : Integer;
 begin
 i:=v[x,y].NumArretBus;
 n:=0;
 for d:=nord to ouest do
  Inc(n, Ord(vxyd(x,y,d).NumArretBus=i));
 Result:=(n<2);
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.InitialiseInfosLignesBus; // v3.0
var i : Integer;
 begin
  NbLignesBus:=0;
  for i:=0 to NbArretsBus-1 do
   ArretsBus[i].InitialiseInfosLignesBus;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.InitialiseInfosTrajetLignesBus; // v3.0
var i, j : Integer;
 begin
  NbLignesBus:=0;
  for i:=0 to NBX-1 do
   for j:=0 to NBY-1 do
    v[i,j].InitialiseInfosLignesBus;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.CalculeTrajetLignesBus; // v3.0.3
var i, j, dp, ndp, DistArretBus, DistCrt, NumArretSvt : Integer;
    DirSvt : direction;
    Voie : pVoie;
 begin
  for i:=0 to NBMAXLIGNESBUS-1 do
   if LignesBus[i].NbArrets>0 then
    for j:=0 to LignesBus[i].NbArrets-1 do
     begin
      Voie:=@(v[ArretsBus[LignesBus[i].NumArret[j]-1].x,
               ArretsBus[LignesBus[i].NumArret[j]-1].y]);
      Voie.LigneBus[i]:=true;
      repeat
       NumArretSvt:=LignesBus[i].NumArret[(j+1) mod LignesBus[i].NbArrets];
       DirSvt:=indefinie;
       DistArretBus:=$7FFFFFFF;
       ndp:=NbDir[Voie.DirPoss];
       for dp:=0 to ndp do
        begin
         if Integer(Voie.DirPoss) and Integer(PossDir[Dirdp[dp, Voie.DirPoss]])>0 then
          begin
           DistCrt:=Voie.DistArretBus[NumArretSvt-1, dp];
           if DistArretBus>DistCrt then
            begin
             DistArretBus:=DistCrt;
             DirSvt:=Dirdp[dp, Voie.DirPoss];
            end;
          end{if};
        end{for};
       Voie:=Voie.v(DirSvt);
       Voie.LigneBus[i]:=true;
      until Voie.EstTeteArretBus(NumArretSvt);
     end{for j};
 end;
//-----------------------------------------------------------------------------
function centre_ville.VerifieCalculDistances : Boolean; // v3.0. Inclut les distances aux arrêts de bus
var Ok : Boolean;
    i, j, d, k, ndp : Integer;
 begin
 Ok:=true;
 i:=0;
 while Ok and (i<NBX) do
  begin
  j:=0;
  while Ok and (j<NBY) do
   begin
    ndp:=NbDir[v[i, j].DirPoss];
    d:=0;
    while Ok and (d<ndp) do
     begin
     k:=0;
     while Ok and (k<NbEtapes) do
      begin
      Ok:=(v[i, j].DistEtape[k, d]<DIST_INDEFINIE);
      if not Ok then begin xErr:=i; yErr:=j; end;
      Inc(k);
      end;{while k<NbEtapes};
     Inc(d);
     k:=0;
     while Ok and (k<NbArretsbus) do  // v3.0
      begin
      Ok:=(v[i, j].DistArretBus[k, d]<DIST_INDEFINIE);
      if not Ok then begin xErr:=i; yErr:=j; end;
      Inc(k);
      end;{while k<NbArretsBus};
     Inc(d);
     end{while d<ndp};
   Inc(j);
   end{while j<NBY};
  Inc(i);
  end{while i<NBX};
  Result:=Ok;
 end;
//-----------------------------------------------------------------------------
function centre_ville.PrepareCalculDistances : Boolean; // v3.0. Inclut les distances aux arrêts de bus
var Ok : Boolean;
    i, j : Integer;
 begin
 Ok:=true;
 i:=0;
 while Ok and (i<NBX) do
  begin
  j:=0;
  while Ok and (j<NBY) do
   begin
   Ok:=v[i, j].PrepareCalculDistances;
   Inc(j);
   end;
  Inc(i);
  end;
 Result:=Ok;
 end;
//-----------------------------------------------------------------------------
function centre_ville.PrepareCalculAttenteTrafic;
var i, j : Integer;
    Ok : Boolean;
 begin
 Ok:=True; i:=0;
 while Ok and (i<NBX) do
  begin
  j:=0;
  while Ok and (j<NBY) do
   begin
   Ok:=v[i,j].PrepareCalculAttenteTrafic;
   Inc(j);
   end;
  Inc(i);
  end;
 Result:=Ok;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.IncrementeTrafic(NumVehicule : Integer);
var veh : pVehicule;
 begin
  veh:=@(Vehicules[NumVehicule-1]);
  Inc(v[veh.x,veh.y].Trafic[veh.NumEtapeDepart,veh.NumEtapeArrivee]);
  Inc(v[veh.x,veh.y].Trafic[0,veh.NumEtapeArrivee]);
  Inc(v[veh.x,veh.y].Trafic[veh.NumEtapeDepart,0]);
  Inc(v[veh.x,veh.y].Trafic[0,0]);
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.IncrementeAttente(NumVehicule : Integer);
var n : Integer;
    veh : pVehicule;
 begin
  veh:=@(Vehicules[NumVehicule-1]);
  n:=TourCrt-veh.TourDrnDepl-1;
  if n>0 then
   begin
   Inc(v[veh.x,veh.y].Attente[veh.NumEtapeDepart,veh.NumEtapeArrivee],n);
   Inc(v[veh.x,veh.y].Attente[0,veh.NumEtapeArrivee],n);
   Inc(v[veh.x,veh.y].Attente[veh.NumEtapeDepart,0],n);
   Inc(v[veh.x,veh.y].Attente[0,0],n);
   end;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.PlaceVehicule(x, y, NumVehicule : Integer);
begin
 IncrementeAttente(NumVehicule);
 Vehicules[NumVehicule-1].Place(x, y);
 if (x>-1) and (y>-1) then
  IncrementeTrafic(NumVehicule);
end;
//-----------------------------------------------------------------------------
function centre_ville.PrepareVehicules : Boolean;
var i,
    NumEtapeDepart,
    NumEtapeArrivee,
    NbVehiculesAvantCreation : Integer;
 begin
  NumEtapeDepart:=1;
  NumEtapeArrivee:=2;
  NbVehiculesAvantCreation:=NbVehicules;
  if DefinitNbVehicules(NbVehiculesAvantCreation, DEFINIT_ET_PREPARE)<>NbVehiculesAvantCreation then // v3.0.4 
   begin
   Result:=false;
   Exit;
   end;
  for i:=0 to NbVehicules-1 do
   begin
    if i mod (NbVehicules div (2*NbEtapes))>0 then
     Vehicules[i].Definit(Etapes[NumEtapeDepart-1].x, Etapes[NumEtapeDepart-1].y,
                          indefinie,
                          NumEtapeDepart, NumEtapeArrivee,
                          normal)
    else
     if i mod (NbVehicules div NbEtapes)>0 then
      Vehicules[i].Definit(Etapes[NumEtapeDepart-1].x, Etapes[NumEtapeDepart-1].y,
                           indefinie,
                           NumEtapeDepart, NumEtapeArrivee,
                           police)
     else
      Vehicules[i].Definit(Etapes[NumEtapeDepart-1].x, Etapes[NumEtapeDepart-1].y,
                           indefinie,
                           NumEtapeDepart, NumEtapeArrivee,
                           urgence);
    repeat
      NumEtapeArrivee:=1+NumEtapeArrivee mod NbEtapes;
      if NumEtapeArrivee=1 then
       begin
        NumEtapeDepart:=1+NumEtapeDepart mod NbEtapes;
        if NumEtapeDepart=1 then
         begin
         NumEtapeDepart:=1;
         NumEtapeArrivee:=2;
         end;
       end;
    until NumEtapeDepart<>NumEtapeArrivee;
   end{for};
  Result:=true;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.PlaceBus(x, y, NumBus : Integer); // v3.0
var b : pBus;
 begin
  b:=@Autobus[NumBus-1];
  if b.Defini and (b.DirDrnDepl>indefinie) then
   begin
    vxyd(b.x, b.y, InvDir[b.DirDrnDepl]).NumBus:=0; // Effacé de la case d'origine (arrière du bus)
    vxyd(b.x, b.y, InvDir[b.DirDrnDepl]).RedessineCase(false);
   end;
  b.DirAvtDrnDepl:=b.DirDrnDepl;
  b.DirDrnDepl:=b.Dir;
  b.Place(x, y);
  if (v[x,y].NumArretBus>0) and
     v[x,y].EstTeteArretBus and
     (v[x,y].NumArretBus=b.NumArretSvt) then
   begin
    b.NumDrnArret:=b.NumArretSvt;
    b.NbCasesParcouruesDepuisDrnArret:=0;
    b.TourArriveDrnArret:=TourCrt;
    b.NumArretSvt:=b.NumeroArretSuivant;
    b.TourDepartArretSvt:=TourCrt+NbToursStopArretBus;
    b.FaitMonterEtDescendre;
   end
  else
   Inc(b.NbCasesParcouruesDepuisDrnArret);
  Inc(b.NbCasesParcourues);
  b.TourDrnDepl:=TourCrt;
  vxyd(x,y,InvDir[b.DirDrnDepl]).RedessineCase(false);
  v[x,y].RedessineCase(false);
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.DefinitBus(NumBus, NumLigne : Integer); // v3.0
 begin
 Autobus[NumBus-1].Definit(NumLigne, LignesBus[NumLigne-1].NumArret[0]);
 LignesBus[NumLigne-1].AjouteBus(NumBus);
 end;
//-----------------------------------------------------------------------------
function centre_ville.PrepareBus; // v3.0
var i, NbBusADefinir, NumLigneCrt : Integer;
 begin // On définit 1 bus de 1 à 3 arrêts, 2 bus de 4 à 6 arrêts et 3 bus de 7 à 9 arrêts.
 NbBusADefinir:=0; NumLigneCrt:=0;
  for i:=0 to NBMAXLIGNESBUS-1 do
   if LignesBus[i].NbArrets>0 then
    Inc(NbBusADefinir, 1+(LignesBus[i].NbArrets-1) div 3);
  if DefinitNbBus(NbBusADefinir, DEFINIT_ET_PREPARE)<>NbBusADefinir then // v3.0.4
   Result:=false
  else
   begin
   for i:=0 to NbBus-1 do
    begin
     while (LignesBus[NumLigneCrt].NbArrets=0) or
           (LignesBus[NumLigneCrt].NbBus=1+(LignesBus[NumLigneCrt].NbArrets-1) div 3) do
      NumLigneCrt:=(NumLigneCrt+1) mod NBMAXLIGNESBUS;
     DefinitBus(i+1, NumLigneCrt+1);
     NumLigneCrt:=(NumLigneCrt+1) mod NBMAXLIGNESBUS;
    end{for};
   Result:=true;
   end{else};
 end;
//-----------------------------------------------------------------------------
function centre_ville.PreparePietons : Boolean;
var x,y,i,
    NbPietonsAvantCreation : Integer;
    Dir : direction;
 begin
  NbPietonsAvantCreation:=NbPietons;
  if DefinitNbPietons(NbPietonsAvantCreation, DEFINIT_ET_PREPARE)<>NbPietonsAvantCreation then // v3.0.4
   begin
   Result:=false;
   Exit;
   end;
  for i:=0 to NbPietons-1 do
   begin
    repeat
     x:=random(NBX);
     y:=random(NBY);
     Dir:=direction(1+random(NBDIRS));
    until v[x, y].PietonPeutAller(Dir);
    Pietons[i].Definit(x,y,Dir,0);
    v[x, y].AjoutePieton(i);
   end;
  Result:=true;
 end;
// ----------------------------------------------------------------------------
procedure centre_ville.DeplacePieton(NumPieton, x, y : Integer; d : direction);
 begin
  v[Pietons[NumPieton].x, Pietons[NumPieton].y].RetirePieton(NumPieton);
  Pietons[NumPieton].Place(x,y);
  Inc(Pietons[NumPieton].DemiCasesParcourues); // v3.0
  if Pietons[NumPieton].Dir<>d then Pietons[NumPieton].Dir:=d;
  Pietons[NumPieton].TourDrnDepl:=TourCrt;
  if Pietons[NumPieton].PsgPtTrv and   // Si le piéton se dirige vers un passage piéton ET
     v[x, y].PassagePietons then       // Si le passage piéton est trouvé ALORS
   Pietons[NumPieton].PsgPtTrv:=false; // On réactive les recherches de passages piétons
  v[x, y].AjoutePieton(NumPieton);
  frmSimulation.RedessineCase(x, y, false);
 end;
//-----------------------------------------------------------------------------
function centre_ville.ChangeDirectionSiPossible(x, y : Integer; dp : dirposs) : Boolean; // ATTENTION : dp = N|E|S|O
 begin // On change si...
  if ((v[x, y].NumEtape=0) and  // Pas d'étape sur la case
      (((Integer(cv.v[x, y].DirPoss) and Integer(dp))=0) or  // Et pas de priorité (clp, stop ou feu)
       (v[x, y].Priorites[Integer(Dirdp[0, dp])-1]=a_droite))) then // si on enlève une direction
   begin
    v[x, y].DirPoss:=dirposs(Integer(v[x, y].DirPoss) xor Integer(dp));
    frmSimulation.RedessineCase(x, y, true);
    Result:=true;
   end
  else
   Result:=false;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.CalculeDistances; // v3.0 : Inclut celles des arrêts de bus
var i : Integer;
 begin
  frmSimulation.StatusBar.Panels.Items[0].Text:='Calcul des distances aux étapes...';
  frmSimulation.StatusBar.Repaint;
  for i:=0 to NbEtapes-1 do
   begin
   frmSimulation.StatusBar.Panels.Items[3].Text:=Format('%d/%d', [i+1, NbEtapes]);
   frmSimulation.StatusBar.Repaint;
   if Etapes[i].Definie then
    v[Etapes[i].x, Etapes[i].y].CalculeDistanceEtape(i, 0, indefinie);
   end;
  frmSimulation.StatusBar.Panels.Items[0].Text:='Calcul des arrêts de bus...';
  frmSimulation.StatusBar.Repaint;
  for i:=0 to NbArretsBus-1 do
   begin
   frmSimulation.StatusBar.Panels.Items[3].Text:=Format('%d/%d', [i+1, NbArretsBus]);
   frmSimulation.StatusBar.Repaint;
   if ArretsBus[i].Defini then
    v[ArretsBus[i].x, ArretsBus[i].y].CalculeDistanceArretBus(i, 0, indefinie);
   end;
 end;
//-----------------------------------------------------------------------------
procedure centre_ville.EffectueTourSimulation;
var i, j : Integer;
 begin
  TourEnCours:=true;
  NbVehiculesDeplaces:=0;
  // 0. On déplace les piétons
  for i:=0 to NBX-1 do
   for j:=0 to NBY-1 do
    if v[i, j].NbPietons>0 then
     v[i, j].DeplacePietons;

  // 1. On calcule les priorités de passage sur chaque case de la voie
  for i:=0 to NBX-1 do
   for j:=0 to NBY-1 do
    v[i, j].CalculeProchainVehiculeOuBus;

  // 2. On déplace les véhicules
  for i:=0 to NBX-1 do
   for j:=0 to NBY-1 do
    v[i, j].DeplaceVehiculeOuBus;

  // 3. On fait tourner les feux...
  for i:=0 to NbFeux-1 do Feux[i].Evolue;
  for i:=0 to NbFeux-1 do Feux[i].ChangeEtat;

  // 4. On sort les voitures des étapes sur la voie
  for i:=0 to NbEtapes-1 do Etapes[i].PlaceProchainVehicule;
  // 4bis. Ainsi que les bus du dépôt
  DepotBus.PlaceProchainBus;

  // 5. On calcule la prochaine direction de chaque véhicule
  for i:=0 to NbVehicules-1 do
   if Vehicules[i].Defini then
    Vehicules[i].CalculeProchaineDirection; // Vehicules[i].Dir défini
  // 5bis. Ainsi que celle des bus
  for i:=0 to NbBus-1 do
   if Autobus[i].Defini then
    Autobus[i].CalculeProchaineDirection; // Bus[i].Dir défini

  // 6. On rafraîchit les véhicules (la direction a pu changer)
  for i:=0 to 2*NbEtapes-1 do
   if Vehicules[i*(NbVehicules div NbEtapes div 2)].Defini then
    frmSimulation.RedessineCase( Vehicules[i*(NbVehicules div NbEtapes div 2)].x,
                                 Vehicules[i*(NbVehicules div NbEtapes div 2)].y,
                                 false);
  // 6bis. Ainsi que les bus (la direction a pu changer). v3.0
  for i:=0 to NbBus-1 do
   if Autobus[i].Defini then
    frmSimulation.RedessineCase(Autobus[i].x, Autobus[i].y, false);
  // 7. On affiche les stats...
  StatsCV[TourCrt mod NbToursStats].Definit;
  if frmStatistiques.Visible then frmStatistiques.PaintBoxStats.Repaint;

 {if frmStatsVehicules.Visible then frmStatsVehicules.RafraichitInfos;}  // A DEFINIR
  if frmInfosVehicule.Visible then frmInfosVehicule.RafraichitInfos;
  if frmInfosBus.Visible then frmInfosBus.RafraichitInfos; // v3.0
  if frmInfosPieton.Visible then frmInfosPieton.RafraichitInfos; // v3.0
  if frmRecherche.Visible then
   begin
    if frmRecherche.RadioButtonVehicule.Checked then
     frmRecherche.SpinEditVehiculeChanged(frmRecherche.SpinEditVehicule, frmRecherche.SpinEditVehicule.Value);
    if frmRecherche.RadioButtonPieton.Checked then
     frmRecherche.SpinEditPietonChanged(frmRecherche.SpinEditPieton, frmRecherche.SpinEditPieton.Value);
    if frmRecherche.RadioButtonBus.Checked then // v3.0.
     frmRecherche.SpinEditBusChanged(frmRecherche.SpinEditBus, frmRecherche.SpinEditBus.Value);
   end;
  Inc(TourCrt, Ord(NbVehiculesArrives<NbVehicules));
  TourEnCours:=false;
 end;
//-----------------------------------------------------------------------------
function centre_ville.Charge(hfile : Integer) : Boolean;
var i, j,
    NvNbFeux,
    NvNbEtapes,
    NvNbArretsBus : Integer;
    Ok : Boolean;
begin
  NbPietons:=-1;
  Ok:=(FileRead(hfile, NvNbFeux, sizeof(NvNbFeux))>0);
  if NvNbFeux>=VERSIONMIN then // v3.0
   begin // Version stockée
    VersionFichier:=NvNbFeux;
    Ok:=(FileRead(hfile, NvNbFeux, sizeof(NvNbFeux))>0); // On relit le nombre de feux
   end
  else // Version non stockée compatible (2.0 <<= Version < 3.0)
   VersionFichier:=VERSIONANC;
  if Ok then
   Ok:=(FileRead(hfile, NvNbEtapes, sizeof(NvNbEtapes))>0) and
       (FileRead(hfile, NbVehicules, sizeof(NbVehicules))>0) and
       (FileRead(hfile, NbPietons, sizeof(NbPietons))>0) and
       ((VersionFichier<$300) or // v3.0
        ((FileRead(hfile, NvNbArretsBus, sizeof(NvNbArretsBus))>0) and
         (FileRead(hfile, NbLignesBus, sizeof(NbLignesBus))>0))) and
       (FileRead(hfile, DureeVert, sizeof(DureeVert))>0) and
       (FileRead(hfile, DureeOrange, sizeof(DureeOrange))>0) and
       (FileRead(hfile, DureeRouge, sizeof(DureeRouge))>0) and
       (FileRead(hfile, AttenteMaxVeh, sizeof(AttenteMaxVeh))>0) and
       (FileRead(hfile, NbToursParSeconde, sizeof(NbToursParSeconde))>0) and
       (FileRead(hfile, NbToursStats, sizeof(NbToursStats))>0) and
       (FileRead(hfile, QuadrillageStats, sizeof(QuadrillageStats))>0) and
       (FileRead(hfile, TypeStats, sizeof(TypeStats))>0) and
       (FileRead(hfile, NbVitesses, sizeof(NbVitesses))>0) and
       (FileRead(hfile, NbMaxCasesDetectPsgPt, sizeof(NbMaxCasesDetectPsgPt))>0) and
       (FileRead(hfile, ProbaDirPsgPt, sizeof(ProbaDirPsgPt))>0) and
       ((VersionFichier<$300) or // v3.0
        ((FileRead(hfile, NbMaxCasesDetectArretBus, sizeof(NbMaxCasesDetectArretBus))>0) and // v3.0
         (FileRead(hfile, ProbaDirArretBus, sizeof(ProbaDirArretBus))>0) and // v3.0
         (FileRead(hfile, ProbaArretBusDmd, sizeof(ProbaArretBusDmd))>0) and // v3.0
         (FileRead(hfile, NbMaxPersonnesBus, sizeof(NbMaxPersonnesBus))>0) and // v3.0
         (FileRead(hfile, NbToursStopArretBus, sizeof(NbToursStopArretBus))>0) and // v3.0
         (FileRead(hfile, NbMaxToursAttenteBus, sizeof(NbMaxToursAttenteBus))>0))); // v3.0

   if Ok then Ok:=(DefinitNbFeux(NvNbFeux)=NbFeux);
   i:=0; while Ok and (i<NbFeux) do
    begin
     Ok:=Feux[i].Charge(hfile);
     Feux[i].AffecteNumero(i+1);
     Inc(i);
    end;
   if Ok then Ok:=(DefinitNbEtapes(NvNbEtapes)=NbEtapes);
   i:=0; while Ok and (i<NbEtapes) do
    begin
     Ok:=Etapes[i].Charge(hfile);
     Etapes[i].AffecteNumero(i+1);
     Inc(i);
    end;
  if VersionFichier>=$300 then // v3.0
   begin // Dépot, Arrêts & Lignes de bus
   Ok:=DepotBus.Charge(hfile);
   if Ok then Ok:=(DefinitNbArretsBus(NvNbArretsBus)=NbArretsbus);
   i:=0; while Ok and (i<NbArretsBus) do
    begin
     Ok:=ArretsBus[i].Charge(hfile);
     Arretsbus[i].AffecteNumero(i+1);
     Inc(i);
    end;
   if Ok then
   i:=0; while Ok and (i<NBMAXLIGNESBUS) do
    begin
     Ok:=LignesBus[i].Charge(hfile);
     LignesBus[i].AffecteNumero(i+1);
     Inc(i);
    end;
   end{if VersionFichier};
  i:=0;
  while Ok and (i<NBX) do
   begin
   j:=0;
   while Ok and (j<NBY) do
    begin
    Ok:=v[i, j].Charge(hfile);
    Inc(j);
    end;
   Inc(i);
   end;
  Result:=Ok;
 end{centre_ville.Charge};
//-----------------------------------------------------------------------------
function centre_ville.Sauve(hfile : Integer) : Boolean;
var i, j, VersionCourante : Integer;
    Ok : Boolean;
begin
  VersionCourante:=VERSION; // v3.0
  Ok:=(FileWrite(hfile, VersionCourante, sizeof(VersionCourante))>0) and // v3.0
      (FileWrite(hfile, NbFeux, sizeof(NbFeux))>0) and
      (FileWrite(hfile, NbEtapes, sizeof(NbEtapes))>0) and
      (FileWrite(hfile, NbVehicules, sizeof(NbVehicules))>0) and
      (FileWrite(hfile, NbPietons, sizeof(NbPietons))>0) and
      (FileWrite(hfile, NbArretsBus, sizeof(NbArretsBus))>0) and // v3.0
      (FileWrite(hfile, NbLignesBus, sizeof(NbLignesBus))>0) and // v3.0
      (FileWrite(hfile, DureeVert, sizeof(DureeVert))>0) and
      (FileWrite(hfile, DureeOrange, sizeof(DureeOrange))>0) and
      (FileWrite(hfile, DureeRouge, sizeof(DureeRouge))>0) and
      (FileWrite(hfile, AttenteMaxVeh, sizeof(AttenteMaxVeh))>0) and
      (FileWrite(hfile, NbToursParSeconde, sizeof(NbToursParSeconde))>0) and
      (FileWrite(hfile, NbToursStats, sizeof(NbToursStats))>0) and
      (FileWrite(hfile, QuadrillageStats, sizeof(QuadrillageStats))>0) and
      (FileWrite(hfile, TypeStats, sizeof(TypeStats))>0) and
      (FileWrite(hfile, NbVitesses, sizeof(NbVitesses))>0) and
      (FileWrite(hfile, NbMaxCasesDetectPsgPt, sizeof(NbMaxCasesDetectPsgPt))>0) and
      (FileWrite(hfile, ProbaDirPsgPt, sizeof(ProbaDirPsgPt))>0) and
      (FileWrite(hfile, NbMaxCasesDetectArretBus, sizeof(NbMaxCasesDetectArretBus))>0) and // v3.0
      (FileWrite(hfile, ProbaDirArretBus, sizeof(ProbaDirArretBus))>0) and // v3.0
      (FileWrite(hfile, ProbaArretBusDmd, sizeof(ProbaArretBusDmd))>0) and // v3.0
      (FileWrite(hfile, NbMaxPersonnesBus, sizeof(NbMaxPersonnesBus))>0) and // v3.0
      (FileWrite(hfile, NbToursStopArretBus, sizeof(NbToursStopArretBus))>0) and // v3.0
      (FileWrite(hfile, NbMaxToursAttenteBus, sizeof(NbMaxToursAttenteBus))>0); // v3.0
  i:=0;
  while Ok and (i<NbFeux) do
   begin
   Ok:=Feux[i].Sauve(hfile);
   Inc(i);
   end;
  i:=0;
  while Ok and (i<NbEtapes) do
   begin
   Ok:=Etapes[i].Sauve(hfile);
   Inc(i);
   end;
  Ok:=DepotBus.Sauve(hfile); // v3.0
  i:=0;
  while Ok and (i<NbArretsBus) do
   begin
   Ok:=ArretsBus[i].Sauve(hfile);
   Inc(i);
   end; // v3.0
  i:=0;
  while Ok and (i<NBMAXLIGNESBUS) do  // v3.0. Attention : tableau statique
   begin
   Ok:=LignesBus[i].Sauve(hfile);
   Inc(i);
   end;
  i:=0;
  while Ok and (i<NBX) do
   begin
   j:=0;
   while Ok and (j<NBY) do
    begin
    Ok:=v[i, j].Sauve(hfile);
    Inc(j);
    end;
   Inc(i);
   end;
  Result:=Ok;
end{centre_ville.Sauve};
//-----------------------------------------------------------------------------
procedure centre_ville.Verifie(var stMsgErr : String);
var i, j : Integer;
 begin
  Screen.Cursor:=crHourGlass;
  stMsgErr:='';
  if NbFeux<0 then
   stMsgErr:=stMsgErr+Format('Le nombre de feux est incorrect (%d)'#13#10'', [NbFeux]);
  if NbEtapes<2 then
   stMsgErr:=stMsgErr+Format('Le nombre d''étapes est incorrect (%d)'#13#10'', [NbEtapes]);
  if NbVehicules<=0 then
   stMsgErr:=stMsgErr+Format('Le nombre de véhicules est incorrect (%d)'#13#10'', [NbVehicules])
  else
   if (NbVehicules<NBMAXVEHICULES) and
      ((NbEtapes=0) or
       (NbEtapes=1) or
       (NbVehicules mod (NbEtapes*(NbEtapes-1))>0)) then
    stMsgErr:=stMsgErr+Format('Le nombre de véhicules ne permet pas une simulation équilibrée (%d)'#13#10'', [NbVehicules]);
  if NbPietons<0 then
   stMsgErr:=stMsgErr+Format('Le nombre de piétons est incorrect (%d)'#13#10'', [NbPietons]);
  if DureeVert<0 then
   stMsgErr:=stMsgErr+Format('La durée du feu vert par défaut est incorrecte (%d)'#13#10'', [DureeOrange]);
  if DureeOrange<0 then
   stMsgErr:=stMsgErr+Format('La durée du feu orange est incorrecte (%d)'#13#10'', [DureeOrange]);
  if DureeRouge<0 then
   stMsgErr:=stMsgErr+Format('La durée du feu rouge par défaut est incorrecte (%d)'#13#10'', [DureeOrange]);
  if AttenteMaxVeh<0 then
   stMsgErr:=stMsgErr+'La durée d''attente maximale d''un véhicule est incorrecte'#13#10'';
  if NbToursParSeconde<0 then
   stMsgErr:=stMsgErr+'Le nombre de tours par seconde est incorrect'#13#10'';
  if NbToursStats<0 then
   stMsgErr:=stMsgErr+Format('Le nombre de tours soumis aux statistiques est incorrect (%d)'#13#10'', [NbToursStats]);
  if (TypeStats<par_nombre) or (TypeStats>par_pourcentage) then
   stMsgErr:=stMsgErr+Format('Le type de statistique est incorrect (%d)'#13#10'', [Integer(TypeStats)]);
  if (NbVitesses<1) or (NbVitesses>3) then
   stMsgErr:=stMsgErr+Format('Le nombre de vitesses est incorrecte (%d)'#13#10'', [NbVitesses]);
  if (NbMaxCasesDetectPsgPt<0) or (NbMaxCasesDetectPsgPt>5) then
   stMsgErr:=stMsgErr+Format('Le nombre de case maximum pour la détection de passage piétons est incorrect (%d)'#13#10'', [NbMaxCasesDetectPsgPt]);
  if (ProbaDirPsgPt<0) or (ProbaDirPsgPt>100) then
   stMsgErr:=stMsgErr+Format('La probabilité qu''un piéton se dirige vers un passage piétons détecté est incorrecte (%d)'#13#10'', [ProbaDirPsgPt]);

  for i:=0 to NBX-1 do
   for j:=0 to NBY-1 do
    v[i, j].Verifie(stMsgErr);
   for i:=0 to NbFeux-1 do
    Feux[i].Verifie(stMsgErr, Format('Feu n°%d', [i+1]));
   for i:=0 to NbEtapes-1 do
    Etapes[i].Verifie(stMsgErr);
   for i:=0 to NbVehicules-1 do
    if Vehicules[i]<>nil then // v3.0.5
     Vehicules[i].Verifie(stMsgErr);
   for i:=0 to NbPietons-1 do
    if Pietons[i]<>nil then  // v3.0.5
     Pietons[i].Verifie(stMsgErr);
   for i:=0 to NbBus-1 do
    if Autobus[i]<>nil then // v3.0.5
     Autobus[i].Verifie(stMsgErr);
   for i:=0 to NbArretsBus-1 do // v3.0
    ArretsBus[i].Verifie(stMsgErr);
   for i:=0 to NBMAXLIGNESBUS-1 do // v3.0
    LignesBus[i].Verifie(stMsgErr);
  DepotBus.Verifie(stMsgErr); // v3.0.3
  Screen.Cursor:=crDefault;
 end;
//-----------------------------------------------------------------------------
function centre_ville.TourDeDeplacementVehicule(NumeroVehicule : Integer) : Boolean; // v3.0.4 (chgt de nom)
 begin
 if Vehicules[NumeroVehicule].NivPriorite>normal then
  Result:=(TourCrt-Vehicules[NumeroVehicule].TourDepart) mod NbVitesses<=NbVitesses-1
 else
  Result:=(TourCrt-Vehicules[NumeroVehicule].TourDepart) mod NbVitesses<=NumeroVehicule mod NbVitesses;
 if not Result then Inc(Vehicules[NumeroVehicule].NbToursRepos); // v2.2.4
 end;
//-----------------------------------------------------------------------------
function centre_ville.TourDeDeplacementBus(NumeroBus : Integer) : Boolean; // v3.0
 begin
 if (TourCrt-Autobus[NumeroBus].TourDepart) mod NbVitesses=0 then
  Result:=true
 else
  begin
  Inc(Autobus[NumeroBus].NbToursRepos);
  Result:=false;
  end;
 end;
// ----------------------------------------------------------------------------
// Initialisation des variables globales
// ----------------------------------------------------------------------------
initialization
 ParamsInchanges:=false;
 VerifierApresOuverture:=false;
 VerifierAvantSimulation:=false;
 VersionFichier:=0; // v3.0
 cv:=nil;
end.

