//---------------------------------------------------------------------------
#ifndef f_simulH
#define f_simulH
//---------------------------------------------------------------------------
#include <ActnList.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <Registry.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.VirtualImageList.hpp>
//---------------------------------------------------------------------------
#include "simul.h"
//---------------------------------------------------------------------------
// v5.4 : les glyphes de TSpeedButtons sont chargées manuellement (HDPI)
//---------------------------------------------------------------------------
#define GLYPHE_DEF    0
#define GLYPHE_DEFF   1
#define GLYPHE_DEFFP  2
#define GLYPHE_SELF   3
#define GLYPHE_DEFB   4
#define GLYPHE_DEFTR  5
#define GLYPHE_DEFTX  6
#define GLYPHE_DEFVL  7
#define GLYPHE_DIR    8
//----------------------------------------------------------------------------------------------------------------------
// Types énumérés. /!\ v5.4 : le type char a été forcé pour que l'énuméré ne prenne pas la taille d'un entier (4 octets)
//----------------------------------------------------------------------------------------------------------------------
// pour RafraichitBoutonsEdition(...) v3.5
enum affichage : unsigned char {aff_aucun, aff_dir, aff_sign, aff_veh=4, aff_ptn=8, aff_voie=16, aff_quadr=32, aff_env=64, aff_infct=128}; // v3.8.1 (aff_env). v5.4.1 (unsigned + aff_infct)
enum type_demande : char {tdRien, tdPause, tdArret};
enum operation_avant : char {oaNouveau, oaOuvrir, oaQuitter};
enum mode_edition : char {meAucun, meCase, meSelection}; // pour RafraichitBoutonEdition. v3.5
//---------------------------------------------------------------------------
// Utilisée dans la classe TfrmSimulation
extern const AnsiString asTitreCV;
//---------------------------------------------------------------------------
// Classe de la fiche
class TfrmSimulation : public TForm
{
__published:	// Composants gérés par l'EDI
  TTimer *TimerSimul;
  TTimer *TimerClignotementLocalisation;
  TTimer *TimerClignotementErreur;
  TStatusBar *StatusBar;
  TSaveDialog *SaveDialog;
  TOpenDialog *OpenDialog;
  TDrawGrid *DrawGridSimul;
  TMainMenu *MainMenu;
  TPopupMenu *PopupMenuEditionCase;
  TPopupMenu *PopupMenuSimulation;
  TPopupMenu *PopupMenuEditionSelection;
  TPopupMenu *PopupMenuBarreOutils;
  TMenuItem *MenuFichier;
  TMenuItem *MenuItemNouveau;
  TMenuItem *MenuItemOuvrir;
  TMenuItem *MenuItemEnregistrer;
  TMenuItem *MenuItemEnregistrerSous;
  TMenuItem *MenuItemQuitter;
  TMenuItem *MenuSimulation;
  TMenuItem *MenuItemParametres;
  TMenuItem *MenuInformations;
  TMenuItem *MenuItemAPropos;
  TMenuItem *MenuItemAide;
  TMenuItem *MenuAffichageStatistiques;
  TMenuItem *MenuItemQuadrillageStatistiques;
  TMenuItem *MenuItem100DrnTours;
  TMenuItem *SepL;
  TMenuItem *MenuItem200DrnTours;
  TMenuItem *MenuItem50DrnTours;
  TMenuItem *MenuItem20DrnTours;
  TMenuItem *MenuItem10DrnTours;
  TMenuItem *MenuItem500DrnTours;
  TMenuItem *SepK;
  TMenuItem *MenuItemParNbVehicules;
  TMenuItem *MenuItemParPourcentage;
  TMenuItem *MenuStatistiques;
  TMenuItem *MenuItemEvolution;
  TMenuItem *MenuItemStatistiquesEtapes;
  TMenuItem *MenuAffichage;
  TMenuItem *MenuItemAffichageDirections;
  TMenuItem *MenuItemAffichageSignalisation;
  TMenuItem *MenuItemAffichageRoutes;
  TMenuItem *MenuItemAffichageVehicules;
  TMenuItem *MenuItemAffichageQuadrillage;
  TMenuItem *Sep3;
  TMenuItem *MenuItemMarche;
  TMenuItem *MenuItemPause;
  TMenuItem *MenuItemArret;
  TMenuItem *MenuItemVerifierReseau;
  TMenuItem *Sep6;
  TMenuItem *Sep7;
  TMenuItem *Sep8;
  TMenuItem *MenuItemVerifierIntegriteApresOuverture;
  TMenuItem *MenuItemVerifierIntegriteAvantSimulation;
  TMenuItem *MenuItemDirectionHaut;
  TMenuItem *MenuItemDirectionDroite;
  TMenuItem *MenuItemDirectionBas;
  TMenuItem *MenuItemDirectionGauche;
  TMenuItem *MenuItemToutDroit;
  TMenuItem *MenuItemEtape;
  TMenuItem *MenuItemPriorites;
  TMenuItem *MenuItemInfosVehicule;
  TMenuItem *MenuItemInfosDistancesEtapes;
  TMenuItem *MenuItemSuivreCeVehicule;
  TMenuItem *MenuItemComposition;
  TMenuItem *MenuItemPassagePietons;
  TMenuItem *MenuItemDeplacerFeu;
  TMenuItem *MenuItemAffichagePietons;
  TMenuItem *SepD;
  TMenuItem *MenuItemFluiditeTrafic;
  TMenuItem *MenuItemArretBusTram;
  TMenuItem *MenuItemInfosDistancesArretsBus;
  TMenuItem *SepB;
  TMenuItem *MenuItemDepotBus;
  TMenuItem *MenuItemInfosBus;
  TMenuItem *MenuItemSuivreCeBus;
  TMenuItem *MenuItemInfosPieton;
  TMenuItem *MenuItemSuivreLe1erPieton;
  TMenuItem *MenuItemSuivreLe2emePieton;
  TMenuItem *MenuItemPassageBus;
  TMenuItem *MenuItemSegmentRoute;
  TMenuItem *MenuPeripherique;
  TMenuItem *SepI;
  TMenuItem *MenuItemCarrefours;
  TMenuItem *SepJ;
  TMenuItem *MenuItemEffacerRoutes;
  TMenuItem *SepA;
  TMenuItem *SepF;
  TMenuItem *MenuItemProlongerHaut;
  TMenuItem *MenuItemProlongerDroite;
  TMenuItem *MenuItemProlongerBas;
  TMenuItem *MenuItemProlongerGauche;
  TMenuItem *MenuItemEffacerVoieTram;
  TMenuItem *MenuItemAffichage;
  TMenuItem *MenuItemStatistiques;
  TMenuItem *MenuItemEditionCase;
  TMenuItem *MenuItemSimulation;
  TMenuItem *MenuItemEditionSelection;
  TMenuItem *SepN;
  TMenuItem *SepO;
  TMenuItem *MenuItemInformations;
  TMenuItem *MenuItemInfosTram;
  TMenuItem *MenuItemSuivreCeTram;
  TMenuItem *MenuItemInfosDistancesArretsTram;
  TMenuItem *MenuItemFichier;
  TMenuItem *MenuDetail;
  TMenuItem *MenuSuivi;
  TMenuItem *MenuDistances;
  TMenuItem *MenuItemRechercher;
  TMenuItem *MenuItemSegmentVoieTram;
  TMenuItem *MenuRoutesCoins;
  TMenuItem *MenuItemRouteBordSuperieurDroit;
  TMenuItem *MenuItemRouteBordInferieurGauche;
  TMenuItem *MenuItemRouteBordSuperieurGauche;
  TMenuItem *MenuItemRouteBordInferieurDroit;
  TMenuItem *MenuItemEffacerVoiesTram;
  TMenuItem *MenuItemEffacerRoute;
  TMenuItem *MenuItemPlaceTaxi;
  TMenuItem *MenuItemPlacePark;
  TMenuItem *MenuItemPlaceVehlib;
  TMenuItem *MenuItemInfosDistancesFilesTaxi;
  TMenuItem *MenuItemInfosTaxi;
  TMenuItem *MenuItemSuivreCeTaxi;
  TMenuItem *MenuItemInfosVehlib;
  TMenuItem *MenuItemSuivreCeVehlib;
  TMenuItem *MenuItemDistancesArretsBus;
  TMenuItem *MenuItemDistancesArretsTram;
  TMenuItem *MenuItemDistancesFilesPark;
  TMenuItem *MenuItemDistancesEtapes;
  TMenuItem *MenuItemDetailVehicule;
  TMenuItem *MenuItemDetailBus;
  TMenuItem *MenuItemDetailTram;
  TMenuItem *MenuItemDetailPieton;
  TMenuItem *MenuItemDetailTaxi;
  TMenuItem *MenuItemDetailVehlib;
  TMenuItem *MenuItemSuiviVehicule;
  TMenuItem *MenuItemSuiviBus;
  TMenuItem *MenuItemSuiviTram;
  TMenuItem *MenuItemSuiviTaxi;
  TMenuItem *MenuItemSuiviVehlib;
  TMenuItem *SepZ;
  TMenuItem *MenuItemSuiviPieton1;
  TMenuItem *MenuItemSuiviPieton2;
  TMenuItem *MenuItemAngleSuperieurDroit;
  TMenuItem *MenuItemAngleInferieurGauche;
  TMenuItem *MenuItemAngleSuperieurGauche;
  TMenuItem *MenuItemAngleInferieurDroit;
  TMenuItem *SepM;
  TMenuItem *MenuItemDefinirNature;
  TMenuItem *MenuItemAffichageEnvironnement;
  TMenuItem *SepP;
  TMenuItem *MenuNatureDecors;
  TMenuItem *MenuItemArbre;
  TMenuItem *MenuItemPelouse;
  TMenuItem *SepR;
  TMenuItem *MenuItemTrottoir;
  TMenuItem *SepQ;
  TMenuItem *MenuItemImmeuble;
  TMenuItem *PriphriqueExtrieur1;
  TMenuItem *PriphriqueIntrieur1;
  TMenuItem *MenuItemExterieur;
  TMenuItem *MenuItemInterieur;
  TMenuItem *MenuItemDecorsTrottoir;
  TMenuItem *SepX;
  TMenuItem *MenuItemDecorsArbre;
  TMenuItem *MenuItemDecorsPelouse;
  TMenuItem *SepY;
  TMenuItem *MenuItemDecorsImmeuble;
  TMenuItem *SepS;
  TMenuItem *MenuItemCopierVers;
  TMenuItem *Sep4;
  TMenuItem *MenuItemSanglant;
  TMenuItem *MenuItemResurrection;
  TMenuItem *MenuItemDistancesFilesTaxi;
  TMenuItem *MenuItemInfosDistancesFilesPark;
  TMenuItem *MenuItemTutoriel;
  TMenuItem *MenuItemRafraichir;
  TMenuItem *MenuItemPrioritesPietons;
  TMenuItem *MenuItemInfosDistancesFilesVehlib;
        TMenuItem *MenuItemDistancesPlacesVehlib;
  TToolBar *ToolBarFichier;
  TToolBar *ToolBarAffichage;
  TToolBar *ToolBarInformations;
  TToolBar *ToolBarSimulation;
  TToolBar *ToolBarEditionCase;
  TToolBar *ToolBarStatistiques;
  TToolBar *ToolBarEditionSelection;
  TToolButton *ToolButtonNouveau;
  TToolButton *ToolButtonOuvrir;
  TToolButton *ToolButtonEnregistrer;
  TToolButton *ToolButtonAffDir;
  TToolButton *ToolButtonAffSign;
  TToolButton *ToolButtonAffRoutes;
  TToolButton *ToolButtonAffVeh;
  TToolButton *ToolButtonAffPtn;
  TToolButton *ToolButtonAffQuadr;
  TToolButton *ToolButtonRechercher;
  TToolButton *ToolButtonDetail;
  TToolButton *ToolButtonSuivi;
  TToolButton *ToolButtonDistances;
  TToolButton *ToolButtonParametres;
  TToolButton *ToolButtonVerifierReseau;
  TToolButton *ToolButtonMarche;
  TToolButton *ToolButtonPause;
  TToolButton *ToolButtonArret;
  TToolButton *ToolButtonNord;
  TToolButton *ToolButtonEst;
  TToolButton *ToolButtonSud;
  TToolButton *ToolButtonOuest;
  TToolButton *ToolButtonEffacerRoute;
  TToolButton *ToolButtonTramVersNord;
  TToolButton *ToolButtonTramVersEst;
  TToolButton *ToolButtonTramVersSud;
  TToolButton *ToolButtonTramVersOuest;
  TToolButton *ToolButtonEffacerVoieTram;
  TToolButton *ToolButtonToutDroit;
  TToolButton *ToolButtonPriorites;
  TToolButton *ToolButtonParking;
  TToolButton *ToolButtonDepotBus;
  TToolButton *ToolButtonPassagePietons;
  TToolButton *ToolButtonArretBusTram;
  TToolButton *ToolButtonPassageBus;
  TToolButton *ToolButtonPlaceTaxi;
  TToolButton *ToolButtonPlacePark;
  TToolButton *ToolButtonDeplacerFeu;
  TToolButton *ToolButtonComposition;
  TToolButton *ToolButtonAffStatsEtapes;
  TToolButton *ToolButtonEvolution;
  TToolButton *ToolButtonFluiditeTrafic;
  TToolButton *ToolButtonSegmentRoute;
  TToolButton *ToolButtonSegmentTram;
  TToolButton *ToolButtonCoins;
  TToolButton *ToolButtonPeripherique;
  TToolButton *ToolButtonCarrefours;
  TToolButton *ToolButtonEffacerRoutesSelection;
  TToolButton *ToolButtonEffacerVoiesTramSelection;
  TToolButton *ToolButtonDefinirNature;
  TToolButton *ToolButtonAffEnv;
  TToolButton *ToolButtonSanglante;
  TToolButton *ToolButtonNatureDecors;
  TToolButton *ToolButtonRafraichir;
  TToolButton *ToolButtonPlaceVehlib;
  TPopupMenu *PopupMenuDistances;
  TPopupMenu *PopupMenuDetail;
  TPopupMenu *PopupMenuSuivi;
  TPopupMenu *PopupMenuCoins;
  TPopupMenu *PopupMenuPeripherique;
  TPopupMenu *PopupMenuDecors;
  TActionList *ActionList;
  TAction *ActionNouveau;
  TAction *ActionOuvrir;
  TAction *ActionEnregistrer;
  TAction *ActionEnregistrerSous;
  TAction *ActionVerifierApresOuverture;
  TAction *ActionQuitter;
  TAction *ActionAfficherDirections;
  TAction *ActionAfficherSignalisation;
  TAction *ActionAfficherVoies;
  TAction *ActionAfficherVehicules;
  TAction *ActionAfficherPietons;
  TAction *ActionAfficherQuadrillage;
  TAction *ActionAfficherEnvironnement;
  TAction *ActionParametres;
  TAction *ActionVerifierReseau;
  TAction *ActionMarche;
  TAction *ActionInterruption;
  TAction *ActionArret;
  TAction *ActionVerifierAvantSimulation;
  TAction *ActionEvolution;
  TAction *ActionStatsAffQuadrillage;
  TAction *ActionStatsAffParVehicule;
  TAction *ActionStatsAffParPourcent;
  TAction *ActionStatsAff10Tours;
  TAction *ActionStatsAff20Tours;
  TAction *ActionStatsAff50Tours;
  TAction *ActionStatsAff100Tours;
  TAction *ActionStatsAff200Tours;
  TAction *ActionStatsAff500Tours;
  TAction *ActionFluiditeTrafic;
  TAction *ActionComposition;
  TAction *ActionStatsParkings;
  TAction *ActionAPropos;
  TAction *ActionSommaire;
  TAction *ActionDirectionHaut;
  TAction *ActionDirectionDroite;
  TAction *ActionDirectionBas;
  TAction *ActionDirectionGauche;
  TAction *ActionEffacerRoute;
  TAction *ActionDirectionHautTram;
  TAction *ActionDirectionBasTram;
  TAction *ActionDirectionDroiteTram;
  TAction *ActionDirectionGaucheTram;
  TAction *ActionEffacerVoieTram;
  TAction *ActionToutDroit;
  TAction *ActionPriorites;
  TAction *ActionParking;
  TAction *ActionDepotBus;
  TAction *ActionPassagePietons;
  TAction *ActionArretBusTram;
  TAction *ActionPassageBus;
  TAction *ActionPlaceTaxi;
  TAction *ActionPlacePark;
  TAction *ActionDeplacerFeuSource;
  TAction *ActionDeplacerFeuDestination;
  TAction *ActionSegmentRoute;
  TAction *ActionSegmentTram;
  TAction *ActionCoinSuperieurDroit;
  TAction *ActionCoinInferieurDroit;
  TAction *ActionCoinSuperieurGauche;
  TAction *ActionCoinInferieurGauche;
  TAction *ActionCarrefours;
  TAction *ActionEffacerRoutes;
  TAction *ActionEffacerVoiesTram;
  TAction *ActionDefinirNature;
  TAction *ActionPeripheriqueExterieur;
  TAction *ActionPeripheriqueInterieur;
  TAction *ActionRechercher;
  TAction *ActionDetailVehicule;
  TAction *ActionDetailBus;
  TAction *ActionDetailTram;
  TAction *ActionDetailPieton;
  TAction *ActionDetailTaxi;
  TAction *ActionDetailVehlib;
  TAction *ActionSuivreVehicule;
  TAction *ActionSuivreBus;
  TAction *ActionSuivreTram;
  TAction *ActionSuivreTaxi;
  TAction *ActionSuivreVehlib;
  TAction *ActionSuivrePieton1;
  TAction *ActionSuivrePieton2;
  TAction *ActionDistancesParkings;
  TAction *ActionDistancesArretsBus;
  TAction *ActionDistancesArretsTram;
  TAction *ActionDistancesFilesTaxi;
  TAction *ActionDistancesFilesPark;
  TAction *ActionDistancesPlacesVehlib;
  TAction *ActionDecorsArbre;
  TAction *ActionDecorsPelouse;
  TAction *ActionNatureTrottoir;
  TAction *ActionNatureImmeuble;
  TAction *ActionCopierVers;
  TAction *ActionSanglante;
  TAction *ActionResurrection;
  TAction *ActionTutoriel;
  TAction *ActionRafraichir;
  TAction *ActionPrioritesPietons;
  TAction *ActionPlaceVehlib;
  TImageCollection *ImageCollection; // v5.4
  TVirtualImageList *VirtualImageList16x16;
	TVirtualImageList *VirtualImageList8x8;
	TVirtualImageList *VirtualImageListGlyphes;
	TPanel *PanelHaut;
	TAction *ActionEpidemie;
	TMenuItem *Epidemie1;
	TToolButton *ToolButtonEpidemie;
	TAction *ActionAfficherInfection;
	TToolButton *ToolButtonAffInfct; // v5.4
  void __fastcall DrawGridSimulDrawCell(TObject *Sender, int Col,
		int Row, TRect &Rect, TGridDrawState State);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall DrawGridSimulDblClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall DrawGridSimulClick(TObject *Sender);
  void __fastcall TimerSimulTimer(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall MenuItemBarreOutilsClick(TObject *Sender);
  void __fastcall PopupMenuBarreOutilsPopup(TObject *Sender);
  void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall TimerClignotementErreurTimer(TObject *Sender);
  void __fastcall ActionQuitterExecute(TObject *Sender);
  void __fastcall ActionVerifierApresOuvertureExecute(TObject *Sender);
  void __fastcall ActionNouveauExecute(TObject *Sender);
  void __fastcall ActionOuvrirExecute(TObject *Sender);
  void __fastcall ActionEnregistrerExecute(TObject *Sender);
  void __fastcall ActionEnregistrerSousExecute(TObject *Sender);
  void __fastcall ActionAfficherDirectionsExecute(TObject *Sender);
  void __fastcall ActionAfficherSignalisationExecute(TObject *Sender);
  void __fastcall ActionAfficherVoiesExecute(TObject *Sender);
  void __fastcall ActionAfficherVehiculesExecute(TObject *Sender);
  void __fastcall ActionAfficherPietonsExecute(TObject *Sender);
  void __fastcall ActionAfficherQuadrillageExecute(TObject *Sender);
  void __fastcall ActionAfficherEnvironnementExecute(TObject *Sender);
  void __fastcall ActionParametresExecute(TObject *Sender);
  void __fastcall ActionVerifierReseauExecute(TObject *Sender);
  void __fastcall ActionMarcheExecute(TObject *Sender);
  void __fastcall ActionInterruptionExecute(TObject *Sender);
  void __fastcall ActionArretExecute(TObject *Sender);
  void __fastcall ActionVerifierAvantSimulationExecute(TObject *Sender);
  void __fastcall ActionEvolutionExecute(TObject *Sender);
  void __fastcall ActionStatsAff10ToursExecute(TObject *Sender);
  void __fastcall ActionStatsAff20ToursExecute(TObject *Sender);
  void __fastcall ActionStatsAff50ToursExecute(TObject *Sender);
  void __fastcall ActionStatsAff100ToursExecute(TObject *Sender);
  void __fastcall ActionStatsAff200ToursExecute(TObject *Sender);
  void __fastcall ActionStatsAff500ToursExecute(TObject *Sender);
  void __fastcall ActionStatsAffParVehiculeExecute(TObject *Sender);
  void __fastcall ActionStatsAffParPourcentExecute(TObject *Sender);
  void __fastcall ActionStatsAffQuadrillageExecute(TObject *Sender);
  void __fastcall ActionFluiditeTraficExecute(TObject *Sender);
  void __fastcall ActionCompositionExecute(TObject *Sender);
  void __fastcall ActionStatsParkingsExecute(TObject *Sender);
  void __fastcall ActionAProposExecute(TObject *Sender);
  void __fastcall ActionSommaireExecute(TObject *Sender);
  void __fastcall ActionDirectionHautExecute(TObject *Sender);
  void __fastcall ActionDirectionDroiteExecute(TObject *Sender);
  void __fastcall ActionDirectionBasExecute(TObject *Sender);
  void __fastcall ActionDirectionGaucheExecute(TObject *Sender);
  void __fastcall ActionEffacerRouteExecute(TObject *Sender);
  void __fastcall ActionDirectionHautTramExecute(TObject *Sender);
  void __fastcall ActionDirectionDroiteTramExecute(TObject *Sender);
  void __fastcall ActionDirectionBasTramExecute(TObject *Sender);
  void __fastcall ActionDirectionGaucheTramExecute(TObject *Sender);
  void __fastcall ActionEffacerVoieTramExecute(TObject *Sender);
  void __fastcall ActionToutDroitExecute(TObject *Sender);
  void __fastcall ActionPrioritesExecute(TObject *Sender);
  void __fastcall ActionParkingExecute(TObject *Sender);
  void __fastcall ActionDepotBusExecute(TObject *Sender);
  void __fastcall ActionPassagePietonsExecute(TObject *Sender);
  void __fastcall ActionArretBusTramExecute(TObject *Sender);
  void __fastcall ActionPassageBusExecute(TObject *Sender);
  void __fastcall ActionPlaceTaxiExecute(TObject *Sender);
  void __fastcall ActionPlaceParkExecute(TObject *Sender);
  void __fastcall ActionDeplacerFeuSourceExecute(TObject *Sender);
  void __fastcall ActionDeplacerFeuDestinationExecute(TObject *Sender);
  void __fastcall ActionSegmentRouteExecute(TObject *Sender);
  void __fastcall ActionSegmentTramExecute(TObject *Sender);
  void __fastcall ActionCoinSuperieurDroitExecute(TObject *Sender);
  void __fastcall ActionCoinInferieurGaucheExecute(TObject *Sender);
  void __fastcall ActionCoinSuperieurGaucheExecute(TObject *Sender);
  void __fastcall ActionCoinInferieurDroitExecute(TObject *Sender);
  void __fastcall ActionPeripheriqueExterieurExecute(TObject *Sender);
  void __fastcall ActionPeripheriqueInterieurExecute(TObject *Sender);
  void __fastcall ActionCarrefoursExecute(TObject *Sender);
  void __fastcall ActionEffacerRoutesExecute(TObject *Sender);
  void __fastcall ActionEffacerVoiesTramExecute(TObject *Sender);
  void __fastcall ActionDefinirNatureExecute(TObject *Sender);
  void __fastcall ActionRechercherExecute(TObject *Sender);
  void __fastcall ActionDetailVehiculeExecute(TObject *Sender);
  void __fastcall ActionDetailBusExecute(TObject *Sender);
  void __fastcall ActionDetailTramExecute(TObject *Sender);
  void __fastcall ActionDetailPietonExecute(TObject *Sender);
  void __fastcall ActionDetailTaxiExecute(TObject *Sender);
  void __fastcall ActionDetailVehlibExecute(TObject *Sender);
  void __fastcall ActionDistancesParkingsExecute(TObject *Sender);
  void __fastcall ActionDistancesArretsBusExecute(TObject *Sender);
  void __fastcall ActionDistancesArretsTramExecute(TObject *Sender);
  void __fastcall ActionDistancesFilesTaxiExecute(TObject *Sender);
  void __fastcall ActionSuivreVehiculeExecute(TObject *Sender);
  void __fastcall ActionSuivreBusExecute(TObject *Sender);
  void __fastcall ActionSuivreTramExecute(TObject *Sender);
  void __fastcall ActionSuivreTaxiExecute(TObject *Sender);
  void __fastcall ActionSuivreVehlibExecute(TObject *Sender);
  void __fastcall ActionSuivrePieton1Execute(TObject *Sender);
  void __fastcall ActionSuivrePieton2Execute(TObject *Sender);
  void __fastcall ActionDecorsArbreExecute(TObject *Sender);
  void __fastcall ActionDecorsPelouseExecute(TObject *Sender);
  void __fastcall ActionNatureTrottoirExecute(TObject *Sender);
  void __fastcall ActionNatureImmeubleExecute(TObject *Sender);
  void __fastcall ActionCopierVersExecute(TObject *Sender);
  void __fastcall ActionSanglanteExecute(TObject *Sender);
  void __fastcall ActionResurrectionExecute(TObject *Sender);
  void __fastcall TimerClignotementLocalisationTimer(TObject *Sender);
  void __fastcall ActionDistancesFilesParkExecute(TObject *Sender);
  void __fastcall ActionTutorielExecute(TObject *Sender);
  void __fastcall ActionRafraichirExecute(TObject *Sender);
  void __fastcall StatusBarResize(TObject *Sender);
  void __fastcall ActionPrioritesPietonsExecute(TObject *Sender);
  void __fastcall ActionPlaceVehlibExecute(TObject *Sender);
  void __fastcall ActionDistancesPlacesVehlibExecute(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall ActionEpidemieExecute(TObject *Sender);
	void __fastcall ActionAfficherInfectionExecute(TObject *Sender);
private:
  affichage Affichage;
  bool SimulEnCours,
       SimulModifiee,
       EnregistrerAvant,
       DeplacementFeuEnCours,
       RedimensionnementEnCours;
  int xErr, yErr, xDeplFeu, yDeplFeu,
      xCrt, yCrt,
      xPrc, yPrc; // Détecteurs de direction du curseur. v3.5
  direction DirOrigVoieTram; // v3.5
  // v5.4 : conversion BCB6>BCBX : (AnsiString>String)
  String asNomFichAuto;
  AnsiString asMsgErr;
  void RedimensionneZone();
  bool EnregistreModificationsAvant(operation_avant Operation);
  bool VerifieIntegrite();
  bool VerifieReseau();
  void AfficheMsgInfoNonDisp(const AnsiString asTitre); // v3.7
  // Définition de la propriété SimulEnCours
  bool __fastcall SimulEstEnCours() { return SimulEnCours; };
  void __fastcall MarcheArretSimul(bool EnCours)
   {
    SimulEnCours=EnCours;
    if (EnCours)
     cv->TopChrono();
    else
     cv->StopChrono(); // v3.9.2
    if (!EnCours) Application->Title=asTitreCV;

    if ((!Pause)&&(!EnCours))
     {
      DrawGridSimul->Options << goRangeSelect;
      DrawGridSimul->PopupMenu=PopupMenuEditionCase;
     }
    else
     {
      DrawGridSimul->Options >> goRangeSelect;
      DrawGridSimul->PopupMenu=PopupMenuSimulation;
     }

    ToolButtonDetail->Enabled=Pause||EnCours;
    ToolButtonSuivi->Enabled=Pause||EnCours;
    ToolButtonDistances->Enabled=Pause||EnCours;
    ToolButtonNatureDecors->Enabled=(!Pause)&&(!EnCours); // v5.1.1 : Oubli

    MenuDetail->Enabled=Pause||EnCours;
    MenuSuivi->Enabled=Pause||EnCours;
    MenuDistances->Enabled=Pause||EnCours;

    ActionNouveau->Enabled=(!Pause)&&(!EnCours); // v4.4.3
    ActionOuvrir->Enabled=(!Pause)&&(!EnCours); // v4.4.3
	ActionEnregistrer->Enabled=(!Pause)&&(!EnCours); // v4.4.3
	ActionEnregistrerSous->Enabled=(!Pause)&&(!EnCours); // v4.4.3
	ActionVerifierReseau->Enabled=(!Pause)&&(!EnCours);
	ActionMarche->Enabled=!EnCours;
	ActionInterruption->Enabled=EnCours;
	ActionArret->Enabled=EnCours;
	ActionEpidemie->Enabled=(!Pause)&&(!EnCours); // v5.4.2 : Action en mode interrupteur donc désactivé pendant la simulation
	ActionEvolution->Enabled=Pause||EnCours;
    ActionFluiditeTrafic->Enabled=Pause||EnCours;
    ActionStatsParkings->Enabled=Pause||EnCours;
    ActionDirectionHaut->Enabled=(!Pause)&&(!EnCours);
    ActionDirectionDroite->Enabled=(!Pause)&&(!EnCours);
    ActionDirectionBas->Enabled=(!Pause)&&(!EnCours);
    ActionDirectionGauche->Enabled=(!Pause)&&(!EnCours);
    ActionEffacerRoute->Enabled=(!Pause)&&(!EnCours);
    ActionDirectionHautTram->Enabled=(!Pause)&&(!EnCours);
    ActionDirectionDroiteTram->Enabled=(!Pause)&&(!EnCours); // v4.2.2 (Haut répété !)
    ActionDirectionBasTram->Enabled=(!Pause)&&(!EnCours);    // v4.2.2 (Haut répété !)
    ActionDirectionGaucheTram->Enabled=(!Pause)&&(!EnCours); // v4.2.2 (Haut répété !)
    ActionEffacerVoieTram->Enabled=(!Pause)&&(!EnCours);
    ActionToutDroit->Enabled=(!Pause)&&(!EnCours);
    ActionPriorites->Enabled=(!Pause)&&(!EnCours);
    ActionParking->Enabled=(!Pause)&&(!EnCours); // v3.0
    ActionDepotBus->Enabled=(!Pause)&&(!EnCours);
    ActionPassagePietons->Enabled=(!Pause)&&(!EnCours);
    ActionArretBusTram->Enabled=(!Pause)&&(!EnCours); // v3.0
    ActionPassageBus->Enabled=(!Pause)&&(!EnCours);
    ActionPlaceTaxi->Enabled=(!Pause)&&(!EnCours);
    ActionPlacePark->Enabled=(!Pause)&&(!EnCours); // v5.0
    ActionPlaceVehlib->Enabled=(!Pause)&&(!EnCours); // v5.3
    ActionDeplacerFeuSource->Enabled=(!Pause)&&(!EnCours);
    ActionDeplacerFeuDestination->Enabled=(!Pause)&&(!EnCours);
    // Changement d'échelle en abscisse désactivée pendant la simulation (v3.8.3)
    ActionStatsAff10Tours->Enabled=(!Pause)&&(!EnCours);
    ActionStatsAff20Tours->Enabled=(!Pause)&&(!EnCours);
    ActionStatsAff50Tours->Enabled=(!Pause)&&(!EnCours);
    ActionStatsAff100Tours->Enabled=(!Pause)&&(!EnCours);
	ActionStatsAff200Tours->Enabled=(!Pause)&&(!EnCours);
    ActionStatsAff500Tours->Enabled=(!Pause)&&(!EnCours);
    // Décors (v4.2.2)
    ActionNatureTrottoir->Enabled=(!Pause)&&(!EnCours);
    ActionNatureImmeuble->Enabled=(!Pause)&&(!EnCours);
    ActionDecorsArbre->Enabled=(!Pause)&&(!EnCours);
    ActionDecorsPelouse->Enabled=(!Pause)&&(!EnCours);

    if (SimulEnCours)
     {
      TypeDemande=tdRien;
      TimerSimul->Interval=(unsigned)(0.5+1000.0/(cv->NbToursParSeconde));
      TimerSimul->Enabled=true;
     }
    InitialiseDeplacementFeu(); // v3.5
   };
  bool __fastcall SimulEstModifiee() { return SimulModifiee; };
  void __fastcall ModifieSimul(bool Modifiee)
   {
    SimulModifiee=Modifiee;
    if (Modifiee)
     {
      if (Caption[Caption.Length()]!='*')
       Caption=Caption+"*";
     }
    else
     if (Caption[Caption.Length()]=='*')
      Caption=Caption.SubString(1, Caption.Length()-1);
   };
  bool __fastcall SimulEstSanglante() { return ActionSanglante->Checked; }; // v4.3
  void __fastcall ModifieModeSanglant(bool Sanglant) { ActionSanglante->Checked=Sanglant; }; // v4.3
  bool __fastcall ResurrectionEstDemandee() { return ActionResurrection->Checked; }; // v4.3.1
  void __fastcall ModifieDemandeResurrection(bool Resurrection) // v4.3.1
   {
	ActionResurrection->Checked=Resurrection;
	ActionResurrection->Enabled=!ActionResurrection->Checked;
   };
  bool __fastcall EpidemieEstActive() { return ActionEpidemie->Checked; }; // v5.4.1
  bool ConfirmeSuppressionFeuxUtilisesDansSelection(type_voie TypeVoie);
  void SupprimeFeuxUtilisesDansSelection(type_voie TypeVoie);
  bool ConfirmeSuppressionArretsUtilisesDansSelection(type_voie TypeVoie); // v3.5
  void SupprimeArretsUtilisesDansSelection(type_voie TypeVoie); // v3.5
  void ReinitialiseToutDansSelection(type_voie TypeVoie);
  bool ModifiePassagePietonsSiNecessaire(int x, int y); // v2.0
  void AfficheStatsAttenteTrafic(); // v2.2.7
  direction DirectionOrigineCurseur(int x, int y, direction DirDest); // v3.5
  void RafraichitActionsEdition(mode_edition ModeEdition); // v3.5
  void InitialiseDeplacementFeu(); // v3.5
  void RafraichitFonctionDeplacementFeu(); // v3.5
  void DeplaceFeu(); // v3.8.3
public:
    type_demande TypeDemande;
	__property bool SimulationEnCours = {read=SimulEstEnCours, write=MarcheArretSimul};
	__property bool SimulationModifiee = {read=SimulEstModifiee, write=ModifieSimul};
	__property bool SimulationSanglante = {read=SimulEstSanglante, write=ModifieModeSanglant}; // v4.3
	__property bool ResurrectionDemandee = {read=ResurrectionEstDemandee, write=ModifieDemandeResurrection}; // v4.3.1
	__property bool EpidemieActivee = {read=EpidemieEstActive}; // v5.4.1
	bool SelectionFeuxDmd,
         SelectionFeuxAtt,
         SelectionFeuxPtn, // v5.2
         StatsAttenteTrafic, // v2.2.7
         Pause;
    __fastcall TfrmSimulation(TComponent* Owner);
    void RedessineCase(int x, int y, bool EffaceFond);
    void AfficheBilan();
	bool SupprimeToutDansSelection(type_voie TypeVoie);
	void AffecteGlyphe(const int NumGlyphe, TBitmap *Glyphe)
	 { // v5.4 pour affecter les BitBtn->Glyph à partir d'une virtualImageList et supporter le HDPI
      VirtualImageListGlyphes->GetBitmap(NumGlyphe, Glyphe);
	 };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSimulation *frmSimulation;
// v3.5 : Ajout de Tram aux constantes de Couleur
extern TColor CoulLigneBusTram[NBMAXLIGNESBUSTRAM];
extern TColor CoulTLigneBusTram[NBMAXLIGNESBUSTRAM];
extern const AnsiString asMemInsuff, asErrInattendue, asFormatCoord;
//---------------------------------------------------------------------------
#endif
