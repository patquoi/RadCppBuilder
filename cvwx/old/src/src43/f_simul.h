//---------------------------------------------------------------------------
#ifndef f_simulH
#define f_simulH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Dialogs.hpp>
#include <Registry.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <Classes.hpp>
#include <ActnList.hpp>
#include <QDialogs.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QDialogs.hpp>
#include <QExtCtrls.hpp>
#include <QGrids.hpp>
#include <QImgList.hpp>
#include <QMenus.hpp>
#include <QTypes.hpp>
#include <QActnList.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Dialogs.hpp>
#include <Registry.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <ActnList.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QDialogs.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QDialogs.hpp>
#include <QExtCtrls.hpp>
#include <QGrids.hpp>
#include <QImgList.hpp>
#include <QMenus.hpp>
#include <QTypes.hpp>
#include <QActnList.hpp>
#endif
//---------------------------------------------------------------------------
#include "simul.h"
//---------------------------------------------------------------------------
// pour RafraichitBoutonsEdition(...) v3.5
enum affichage {aff_aucun, aff_dir, aff_sign, aff_veh=4, aff_ptn=8, aff_voie=16, aff_quadr=32, aff_env=64}; // v3.8.1 (aff_env)
enum type_demande {tdRien, tdPause, tdArret};
enum operation_avant {oaNouveau, oaOuvrir, oaQuitter};
enum mode_edition {meAucun, meCase, meSelection}; // pour RafraichitBoutonEdition. v3.5
//---------------------------------------------------------------------------
// Utilisée dans la classe TfrmSimulation
extern const AnsiString asTitreCV;
//---------------------------------------------------------------------------
// Classe de la fiche
class TfrmSimulation : public TForm
{
__published:	// Composants gérés par l'EDI
  TStatusBar *StatusBar;
  TImageList *ImageList8x8x1;
  TImageList *ImageList16x16;
  TSaveDialog *SaveDialog;
  TOpenDialog *OpenDialog;
  TDrawGrid *DrawGridSimul;
  TMainMenu *MainMenu;
  TMenuItem *MenuFichier;
  TMenuItem *MenuItemNouveau;
  TMenuItem *MenuItemOuvrir;
  TMenuItem *MenuItemEnregistrer;
  TMenuItem *MenuItemEnregistrerSous;
  TMenuItem *MenuItemQuitter;
  TMenuItem *MenuSimulation;
  TMenuItem *MenuItemParametres;
  TTimer *TimerSimul;
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
  TImageList *ImageList8x8x2;
  TPopupMenu *PopupMenuEditionCase;
  TMenuItem *MenuStatistiques;
  TMenuItem *MenuItemEvolution;
  TMenuItem *MenuItemStatistiquesEtapes;
  TMenuItem *MenuAffichage;
  TMenuItem *MenuItemAffichageDirections;
  TMenuItem *MenuItemAffichageSignalisation;
  TMenuItem *MenuItemAffichageRoutes;
  TMenuItem *MenuItemAffichageVehicules;
  TMenuItem *MenuItemAffichageQuadrillage;
  TMenuItem *MenuItemZoom;
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
  TPopupMenu *PopupMenuSimulation;
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
  TPopupMenu *PopupMenuEditionSelection;
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
  TPopupMenu *PopupMenuBarreOutils;
  TMenuItem *MenuItemMenu;
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
  TTimer *TimerClignotementErreur;
  TMenuItem *MenuItemPlaceTaxi;
  TMenuItem *MenuItemInfosDistancesFilesTaxi;
  TMenuItem *MenuItemSuivreCeTaxi;
  TMenuItem *MenuItemInfosTaxi;
  TControlBar *ControlBar;
  TToolBar *ToolBarFichier;
  TToolButton *ToolButtonNouveau;
  TToolButton *ToolButtonOuvrir;
  TToolButton *ToolButtonEnregistrer;
  TToolBar *ToolBarAffichage;
  TToolButton *ToolButtonZoom;
  TToolButton *ToolButtonAffDir;
  TToolButton *ToolButtonAffSign;
  TToolButton *ToolButtonAffRoutes;
  TToolButton *ToolButtonAffVeh;
  TToolButton *ToolButtonAffPtn;
  TToolButton *ToolButtonAffQuadr;
  TToolBar *ToolBarInformations;
  TToolButton *ToolButtonRechercher;
  TToolButton *ToolButtonDetail;
  TToolButton *ToolButtonSuivi;
  TToolButton *ToolButtonDistances;
  TToolBar *ToolBarSimulation;
  TToolButton *ToolButtonParametres;
  TToolButton *ToolButtonVerifierReseau;
  TToolButton *ToolButtonMarche;
  TToolButton *ToolButtonPause;
  TToolButton *ToolButtonArret;
  TToolBar *ToolBarEditionCase;
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
  TToolButton *ToolButtonEtape;
  TToolButton *ToolButtonDepotBus;
  TToolButton *ToolButtonPassagePietons;
  TToolButton *ToolButtonArretBusTram;
  TToolButton *ToolButtonPassageBus;
  TToolButton *ToolButtonPlaceTaxi;
  TToolButton *ToolButtonDeplacerFeu;
  TToolBar *ToolBarStatistiques;
  TToolButton *ToolButtonComposition;
  TToolButton *ToolButtonAffStatsEtapes;
  TToolButton *ToolButtonEvolution;
  TToolButton *ToolButtonFluiditeTrafic;
  TToolBar *ToolBarEditionSelection;
  TToolButton *ToolButtonSegmentRoute;
  TToolButton *ToolButtonSegmentTram;
  TToolButton *ToolButtonCoins;
  TToolButton *ToolButtonPeripherique;
  TToolButton *ToolButtonCarrefours;
  TToolButton *ToolButtonEffacerRoutesSelection;
  TToolButton *ToolButtonEffacerVoiesTramSelection;
  TPopupMenu *PopupMenuDistances;
  TMenuItem *MenuItemDistancesArretsBus;
  TMenuItem *MenuItemDistancesArretsTram;
  TMenuItem *MenuItemDistancesFilesTaxi;
  TMenuItem *MenuItemDistancesEtapes;
  TPopupMenu *PopupMenuDetail;
  TMenuItem *MenuItemDetailVehicule;
  TMenuItem *MenuItemDetailBus;
  TMenuItem *MenuItemDetailTram;
  TMenuItem *MenuItemDetailPieton;
  TMenuItem *MenuItemDetailTaxi;
  TPopupMenu *PopupMenuSuivi;
  TMenuItem *MenuItemSuiviVehicule;
  TMenuItem *MenuItemSuiviBus;
  TMenuItem *MenuItemSuiviTram;
  TMenuItem *MenuItemSuiviTaxi;
  TMenuItem *SepZ;
  TMenuItem *MenuItemSuiviPieton1;
  TMenuItem *MenuItemSuiviPieton2;
  TPopupMenu *PopupMenuCoins;
  TMenuItem *MenuItemAngleSuperieurDroit;
  TMenuItem *MenuItemAngleInferieurGauche;
  TMenuItem *MenuItemAngleSuperieurGauche;
  TMenuItem *MenuItemAngleInferieurDroit;
  TToolButton *ToolButtonDefinirNature;
  TMenuItem *SepM;
  TMenuItem *MenuItemDefinirNature;
  TToolButton *ToolButtonAffEnv;
  TMenuItem *MenuItemAffichageEnvironnement;
  TActionList *ActionList;
  TAction *ActionNouveau;
  TAction *ActionOuvrir;
  TAction *ActionEnregistrer;
  TAction *ActionEnregistrerSous;
  TAction *ActionVerifierApresOuverture;
  TAction *ActionQuitter;
  TAction *ActionZoom;
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
  TAction *ActionStatsEtapes;
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
  TAction *ActionEtape;
  TAction *ActionDepotBus;
  TAction *ActionPassagePietons;
  TAction *ActionArretBusTram;
  TAction *ActionPassageBus;
  TAction *ActionPlaceTaxi;
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
  TAction *ActionSuivreVehicule;
  TAction *ActionSuivreBus;
  TAction *ActionSuivreTram;
  TAction *ActionSuivreTaxi;
  TAction *ActionSuivrePieton1;
  TAction *ActionSuivrePieton2;
  TAction *ActionDistancesEtapes;
  TAction *ActionDistancesArretsBus;
  TAction *ActionDistancesArretsTram;
  TAction *ActionDistancesFilesTaxi;
  TMenuItem *SepP;
  TMenuItem *MenuNatureDecors;
  TMenuItem *MenuItemArbre;
  TMenuItem *MenuItemPelouse;
  TMenuItem *SepR;
  TAction *ActionDecorsArbre;
  TAction *ActionDecorsPelouse;
  TAction *ActionNatureTrottoir;
  TMenuItem *MenuItemTrottoir;
  TMenuItem *SepQ;
  TMenuItem *MenuItemImmeuble;
  TAction *ActionNatureImmeuble;
  TMenuItem *PriphriqueExtrieur1;
  TMenuItem *PriphriqueIntrieur1;
  TToolButton *ToolButtonNatureDecors;
  TPopupMenu *PopupMenuPeripherique;
  TMenuItem *MenuItemExterieur;
  TMenuItem *MenuItemInterieur;
  TPopupMenu *PopupMenuDecors;
  TMenuItem *MenuItemDecorsTrottoir;
  TMenuItem *SepX;
  TMenuItem *MenuItemDecorsArbre;
  TMenuItem *MenuItemDecorsPelouse;
  TMenuItem *SepY;
  TMenuItem *MenuItemDecorsImmeuble;
  TAction *ActionCopierVers;
  TMenuItem *SepS;
  TMenuItem *MenuItemCopierVers;
  TAction *ActionSanglante;
  TMenuItem *Sep4;
  TMenuItem *MenuItemSanglant;
  TToolButton *ToolButtonSanglante;
  TAction *ActionResurrection;
  TMenuItem *MenuItemResurrection;
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
  void __fastcall ActionZoomExecute(TObject *Sender);
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
  void __fastcall ActionStatsEtapesExecute(TObject *Sender);
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
  void __fastcall ActionEtapeExecute(TObject *Sender);
  void __fastcall ActionDepotBusExecute(TObject *Sender);
  void __fastcall ActionPassagePietonsExecute(TObject *Sender);
  void __fastcall ActionArretBusTramExecute(TObject *Sender);
  void __fastcall ActionPassageBusExecute(TObject *Sender);
  void __fastcall ActionPlaceTaxiExecute(TObject *Sender);
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
  void __fastcall ActionDistancesEtapesExecute(TObject *Sender);
  void __fastcall ActionDistancesArretsBusExecute(TObject *Sender);
  void __fastcall ActionDistancesArretsTramExecute(TObject *Sender);
  void __fastcall ActionDistancesFilesTaxiExecute(TObject *Sender);
  void __fastcall ActionSuivreVehiculeExecute(TObject *Sender);
  void __fastcall ActionSuivreBusExecute(TObject *Sender);
  void __fastcall ActionSuivreTramExecute(TObject *Sender);
  void __fastcall ActionSuivreTaxiExecute(TObject *Sender);
  void __fastcall ActionSuivrePieton1Execute(TObject *Sender);
  void __fastcall ActionSuivrePieton2Execute(TObject *Sender);
  void __fastcall ActionDecorsArbreExecute(TObject *Sender);
  void __fastcall ActionDecorsPelouseExecute(TObject *Sender);
  void __fastcall ActionNatureTrottoirExecute(TObject *Sender);
  void __fastcall ActionNatureImmeubleExecute(TObject *Sender);
  void __fastcall ActionCopierVersExecute(TObject *Sender);
  void __fastcall ActionSanglanteExecute(TObject *Sender);
 void __fastcall ActionResurrectionExecute(TObject *Sender);
private:
  TImageList *ImageList8x8;
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
  AnsiString asNomFichAuto,
             asMsgErr;
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

    MenuDetail->Enabled=Pause||EnCours;
    MenuSuivi->Enabled=Pause||EnCours;
    MenuDistances->Enabled=Pause||EnCours;

    ActionNouveau->Enabled=!SimulEnCours;
    ActionOuvrir->Enabled=!SimulEnCours;
    ActionEnregistrer->Enabled=!SimulEnCours;
    ActionEnregistrerSous->Enabled=!SimulEnCours;
    ActionVerifierReseau->Enabled=(!Pause)&&(!EnCours);
    ActionMarche->Enabled=!EnCours;
    ActionInterruption->Enabled=EnCours;
    ActionArret->Enabled=EnCours;
    ActionEvolution->Enabled=Pause||EnCours;
    ActionFluiditeTrafic->Enabled=Pause||EnCours;
    ActionStatsEtapes->Enabled=Pause||EnCours;
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
    ActionEtape->Enabled=(!Pause)&&(!EnCours); // v3.0
    ActionDepotBus->Enabled=(!Pause)&&(!EnCours);
    ActionPassagePietons->Enabled=(!Pause)&&(!EnCours);
    ActionArretBusTram->Enabled=(!Pause)&&(!EnCours); // v3.0
    ActionPassageBus->Enabled=(!Pause)&&(!EnCours);
    ActionPlaceTaxi->Enabled=(!Pause)&&(!EnCours);
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
    __property bool SimulationEnCours = {read=SimulEstEnCours, write=MarcheArretSimul},
                    SimulationModifiee = {read=SimulEstModifiee, write=ModifieSimul},
                    SimulationSanglante = {read=SimulEstSanglante, write=ModifieModeSanglant}, // v4.3
                    ResurrectionDemandee = {read=ResurrectionEstDemandee, write=ModifieDemandeResurrection}; // v4.3.1
    bool SelectionFeuxDmd,
         SelectionFeuxAtt,
         StatsAttenteTrafic, // v2.2.7
         Pause;
    __fastcall TfrmSimulation(TComponent* Owner);
    void RedessineCase(int x, int y, bool EffaceFond);
    void AfficheBilan();
    bool SupprimeToutDansSelection(type_voie TypeVoie);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSimulation *frmSimulation;
// v3.5 : Ajout de Tram aux constantes de Couleur
extern TColor CoulLigneBusTram[NBMAXLIGNESBUSTRAM];
extern TColor CoulTLigneBusTram[NBMAXLIGNESBUSTRAM];
extern const AnsiString asMemInsuff, asErrInattendue, asFormatCoord;
//---------------------------------------------------------------------------
#endif
