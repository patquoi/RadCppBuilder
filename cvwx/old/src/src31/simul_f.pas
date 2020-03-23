(******************************************************************************
CENTRE-VILLE pour Linux

Copyright (C) 2001 Patrice FOUQUET

Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le
modifier conform�ment aux dispositions de la Licence Publique G�n�rale GNU,
telle que publi�e par la Free Software Foundation ; version 2 de la licence,
ou encore toute version ult�rieure.

Ce programme est distribu� dans l'espoir qu'il sera utile,
mais SANS AUCUNE GARANTIE ; sans m�me la garantie implicite de COMMERCIALISATION
ou D'ADAPTATION A UN OBJET PARTICULIER. Pour plus de d�tail,
voir la Licence Publique G�n�rale GNU.

Vous devez avoir re�u un exemplaire de la Licence Publique G�n�rale GNU en m�me
temps que ce programme ; si ce n'est pas le cas,
�crivez � la Free Software Foundation Inc.,
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

unit simul_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QExtCtrls, QComCtrls, QImgList, QMenus, QGrids, QTypes, QStdCtrls,
  simul;

type
  affichage = (aucun, aff_dir, aff_sign, aff_veh=4, aff_ptn=8, aff_voie=16, aff_quadr=32);
  type_demande = (rien, pause, arret);
  operation_avant = (oaNouveau, oaOuvrir, oaQuitter);
  TfrmSimulation = class(TForm)
    StatusBar: TStatusBar;
    MainMenu: TMainMenu;
    DrawGridSimul: TDrawGrid;
    MenuFichier: TMenuItem;
    MenuSimulation: TMenuItem;
    MenuStatistiques: TMenuItem;
    RubriqueInformations: TMenuItem;
    ToolBar: TToolBar;
    ImageList16x16: TImageList;
    RubriqueNouveau: TMenuItem;
    Sep0: TMenuItem;
    RubriqueOuvrir: TMenuItem;
    RubriqueVerifierIntegriteApresOuverture: TMenuItem;
    Sep2: TMenuItem;
    RubriqueEnregistrer: TMenuItem;
    RubriqueEnregistrerSous: TMenuItem;
    Sep3: TMenuItem;
    RubriqueQuitter: TMenuItem;
    RubriqueParametres: TMenuItem;
    RubriqueVerificationReseau: TMenuItem;
    Sep4: TMenuItem;
    RubriqueMarche: TMenuItem;
    RubriqueInterruption: TMenuItem;
    RubriqueArret: TMenuItem;
    RubriqueVerifierIntegriteAvantSimulation: TMenuItem;
    Sep5: TMenuItem;
    RubriqueRecherche: TMenuItem;
    Sep6: TMenuItem;
    MenuAffichageSimulation: TMenuItem;
    RubriqueDirections: TMenuItem;
    RubriqueSignalisation: TMenuItem;
    RubriqueRoutes: TMenuItem;
    RubriqueVehicules: TMenuItem;
    RubriquePietons: TMenuItem;
    RubriqueQuadrillage: TMenuItem;
    RubriqueStatistiquesEvolution: TMenuItem;
    RubriqueCompositionReseau: TMenuItem;
    MenuAffichageStatistiques: TMenuItem;
    RubriqueQuadrillageStatistiques: TMenuItem;
    Sep7: TMenuItem;
    RubriqueParNbVehicules: TMenuItem;
    RubriqueParPourcentage: TMenuItem;
    Sep8: TMenuItem;
    Rubrique10DrnTours: TMenuItem;
    Rubrique20DrnTours: TMenuItem;
    Rubrique50DrnTours: TMenuItem;
    Rubrique100DrnTours: TMenuItem;
    Rubrique200DrnTours: TMenuItem;
    Rubrique500DrnTours: TMenuItem;
    RubriqueStatistiquesEtapes: TMenuItem;
    RubriqueAPropos: TMenuItem;
    ToolButtonNord: TToolButton;
    ToolButtonEst: TToolButton;
    ToolButtonSud: TToolButton;
    ToolButtonOuest: TToolButton;
    ToolButtonToutDroit: TToolButton;
    ToolButtonEtape: TToolButton;
    ToolButtonPassagePietons: TToolButton;
    ToolButtonMajVoie: TToolButton;
    ToolButtonSep2: TToolButton;
    ToolButtonInfosVehicule: TToolButton;
    ToolButtonAffDistEtapes: TToolButton;
    ToolButtonAffStatsEtapes: TToolButton;
    ToolButtonAffStatsEvol: TToolButton;
    ToolButtonComposition: TToolButton;
    ToolButtonSep4: TToolButton;
    ToolButtonParametres: TToolButton;
    ToolButtonVerif: TToolButton;
    ToolButtonMarche: TToolButton;
    ToolButtonPause: TToolButton;
    ToolButtonArret: TToolButton;
    ToolButtonSep5: TToolButton;
    ToolButtonRecherche: TToolButton;
    ToolButtonAffDir: TToolButton;
    ToolButtonAffSign: TToolButton;
    ToolButtonAffRoutes: TToolButton;
    ToolButtonAffVeh: TToolButton;
    ToolButtonAffPtn: TToolButton;
    ToolButtonAffQuadr: TToolButton;
    ImageList8x8x2: TImageList;
    SaveDialog: TSaveDialog;
    OpenDialog: TOpenDialog;
    TimerSimul: TTimer;
    PopupMenuSimulation: TPopupMenu;
    RubriqueInfosVehicule: TMenuItem;
    RubriqueInfosDistancesEtapes: TMenuItem;
    PopupMenuEdition: TPopupMenu;
    MenuCase: TMenuItem;
    MenuSelection: TMenuItem;
    RubriqueDirectionHaut: TMenuItem;
    RubriqueDirectionDroite: TMenuItem;
    RubriqueDirectionBas: TMenuItem;
    RubriqueDirectionGauche: TMenuItem;
    SepA: TMenuItem;
    RubriqueEtape: TMenuItem;
    RubriqueToutDroit: TMenuItem;
    RubriquePassagePietons: TMenuItem;
    SepB: TMenuItem;
    RubriquePriorites: TMenuItem;
    RubriqueDeplacerFeu: TMenuItem;
    RubriqueRoute: TMenuItem;
    SepC: TMenuItem;
    RubriqueBordSuperieurDroit: TMenuItem;
    RubriqueBordInferieurGauche: TMenuItem;
    RubriqueBordSuperieurGauche: TMenuItem;
    RubriqueBordInferieurDroit: TMenuItem;
    SepD: TMenuItem;
    RubriquePeripheriqueExterieur: TMenuItem;
    RubriquePeripheriqueInferieur: TMenuItem;
    SepE: TMenuItem;
    RubriqueCarrefours: TMenuItem;
    SepF: TMenuItem;
    RubriqueEffacer: TMenuItem;
    Image16x16: TImage;
    SepG: TMenuItem;
    RubriqueAttenteTrafic: TMenuItem;
    ToolButtonDepotBus: TToolButton;
    ToolButtonArretBus: TToolButton;
    ToolButtonPassageBus: TToolButton;
    ToolButtonInfosBus: TToolButton;
    ToolButtonInfosPieton: TToolButton;
    ToolButtonAffDistArretsBus: TToolButton;
    RubriqueSuivreCeVehicule: TMenuItem;
    Sep1: TMenuItem;
    SepH: TMenuItem;
    RubriqueInfosPieton: TMenuItem;
    RubriqueSuivreLe1erPieton: TMenuItem;
    RubriqueSuivreLe2emePieton: TMenuItem;
    RubriqueInfosBus: TMenuItem;
    RubriqueSuivreCeBus: TMenuItem;
    SepI: TMenuItem;
    RubriqueInfosDistancesArretsBus: TMenuItem;
    RubriqueDepotBus: TMenuItem;
    RubriqueArretBus: TMenuItem;
    procedure RubriqueAProposClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure DrawGridSimulDrawCell(Sender: TObject; ACol, ARow: Integer;
      Rect: TRect; State: TGridDrawState);
    procedure RubriqueEnregistrerClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure RubriqueNouveauClick(Sender: TObject);
    procedure RubriqueOuvrirClick(Sender: TObject);
    procedure RubriqueEnregistrerSousClick(Sender: TObject);
    procedure ToolButtonAffichagesClick(Sender: TObject);
    procedure ToolButtonNESOClick(Sender: TObject);
    procedure ToolButtonEtapeClick(Sender: TObject);
    procedure DrawGridSimulDblClick(Sender: TObject);
    procedure ToolButtonMajVoieClick(Sender: TObject);
    procedure DrawGridSimulClick(Sender: TObject);
    procedure ToolButtonAffDistEtapesClick(Sender: TObject);
    procedure ToolButtonVerifClick(Sender: TObject);
    procedure ToolButtonPauseClick(Sender: TObject);
    procedure ToolButtonArretClick(Sender: TObject);
    procedure ToolButtonAffStatsEvolClick(Sender: TObject);
    procedure RubriqueQuadrillageStatistiquesClick(Sender: TObject);
    procedure RubriqueDrnToursClick(Sender: TObject);
    procedure RubriqueParVehPourcentClick(Sender: TObject);
    procedure ToolButtonAffStatsEtapesClick(Sender: TObject);
    procedure ToolButtonParametresClick(Sender: TObject);
    procedure ToolButtonInfosVehiculeClick(Sender: TObject);
    procedure ToolButtonRechercheClick(Sender: TObject);
    procedure RubriqueParametresClick(Sender: TObject);
    procedure RubriqueRechercheClick(Sender: TObject);
    procedure RubriqueDirectionsClick(Sender: TObject);
    procedure RubriqueSignalisationClick(Sender: TObject);
    procedure RubriqueRoutesClick(Sender: TObject);
    procedure RubriqueVehiculesClick(Sender: TObject);
    procedure RubriquePietonsClick(Sender: TObject);
    procedure RubriqueQuadrillageClick(Sender: TObject);
    procedure RubriqueMarcheClick(Sender: TObject);
    procedure RubriqueInterruptionClick(Sender: TObject);
    procedure RubriqueArretClick(Sender: TObject);
    procedure RubriqueVerificationReseauClick(Sender: TObject);
    procedure RubriqueStatistiquesEvolutionClick(Sender: TObject);
    procedure RubriqueStatistiquesEtapesClick(Sender: TObject);
    procedure RubriqueDirectionHautClick(Sender: TObject);
    procedure RubriqueDirectionDroiteClick(Sender: TObject);
    procedure RubriqueDirectionBasClick(Sender: TObject);
    procedure RubriqueDirectionGaucheClick(Sender: TObject);
    procedure RubriqueEtapeClick(Sender: TObject);
    procedure RubriquePrioritesClick(Sender: TObject);
    procedure RubriqueInfosVehiculeClick(Sender: TObject);
    procedure RubriqueInfosDistancesEtapesClick(Sender: TObject);
    procedure ToolButtonToutDroitClick(Sender: TObject);
    procedure RubriqueToutDroitClick(Sender: TObject);
    procedure RubriqueVerifierIntegriteApresOuvertureClick(
      Sender: TObject);
    procedure RubriqueVerifierIntegriteAvantSimulationClick(
      Sender: TObject);
    procedure RubriqueSuivreCeVehiculeClick(Sender: TObject);
    procedure RubriqueRouteClick(Sender: TObject);
    procedure RubriqueBordSuperieurDroitClick(Sender: TObject);
    procedure RubriqueBordInferieurGaucheClick(Sender: TObject);
    procedure RubriqueBordSuperieurGaucheClick(Sender: TObject);
    procedure RubriqueBordInferieurDroitClick(Sender: TObject);
    procedure RubriquePeripheriqueExterieurClick(Sender: TObject);
    procedure RubriquePeripheriqueInferieurClick(Sender: TObject);
    procedure RubriqueCarrefoursClick(Sender: TObject);
    procedure RubriqueEffacerClick(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure RubriquePassagePietonsClick(Sender: TObject);
    procedure ToolButtonPassagePietonsClick(Sender: TObject);
    procedure RubriqueDeplacerFeuClick(Sender: TObject);
    procedure ToolButtonCompositionClick(Sender: TObject);
    procedure RubriqueCompositionReseauClick(Sender: TObject);
    procedure TimerSimulTimer(Sender: TObject);
    procedure RubriqueQuitterClick(Sender: TObject);
    procedure ToolButtonMarcheClick(Sender: TObject);
    procedure RubriqueAttenteTraficClick(Sender: TObject);
    procedure RubriqueArretBusClick(Sender: TObject);
    procedure RubriqueDepotBusClick(Sender: TObject);
    procedure RubriqueInfosDistancesArretsBusClick(Sender: TObject);
    procedure ToolButtonArretBusClick(Sender: TObject);
    procedure ToolButtonAffDistArretsBusClick(Sender: TObject);
    procedure ToolButtonDepotBusClick(Sender: TObject);
    procedure ToolButtonInfosBusClick(Sender: TObject);
    procedure RubriqueInfosBusClick(Sender: TObject);
    procedure RubriqueSuivreCeBusClick(Sender: TObject);
    procedure RubriqueInfosPietonClick(Sender: TObject);
    procedure RubriqueSuivreLe1erPietonClick(Sender: TObject);
    procedure RubriqueSuivreLe2emePietonClick(Sender: TObject);
    procedure ToolButtonInfosPietonClick(Sender: TObject);
  private
    Affichages : affichage;
    SimulEnCours,
    EnregistrerAvant,
    DeplacementFeuEnCours : Boolean;
    xErr, yErr, xDeplFeu, yDeplFeu : Integer;
    stNomFichAuto,
    stMsgErr : String;
    function EnregistreModificationsAvant(Operation : operation_avant) : Boolean;
    function VerifieReseau : Boolean;
    procedure AfficheMsgInfoNonDisp(stTitre : String);
    function SimulEstEnCours : Boolean;
    procedure MarcheArretSimul(EnCours : Boolean);
    function ModifiePassagePietonsSiNecessaire(x, y : Integer) : Boolean;
    function ConfirmeSuppressionFeuxUtilisesDansSelection : Boolean;
    procedure SupprimeFeuxUtilisesDansSelection;
    procedure ReinitialiseToutDansSelection;
    procedure AfficheStatsAttenteTrafic; // v2.2.7
  public
    TypeDemande : type_demande;
    SimulModifiee,
    SelectionFeuxDmd,
    SelectionFeuxAtt,
    StatsAttenteTrafic : Boolean; // v2.2.7
    property SimulationEnCours : Boolean read SimulEstEnCours write MarcheArretSimul;
    procedure RedessineCase(x, y : Integer; EffaceFond : Boolean);
    procedure AfficheBilan;
    function SupprimeToutDansSelection : Boolean;
  end;

var
  frmSimulation: TfrmSimulation;

const stFormatCoord = '(%d, %d)';

// v3.0 : Couleurs des lignes de bus
      CoulLigneBus :  array [0..NBMAXLIGNESBUS-1] of TColor = (clBlue, clRed, clLime, clYellow, clFuchsia, clAqua, clPurple, $00FF0080, $000080FF);
      CoulTLigneBus : array [0..NBMAXLIGNESBUS-1] of TColor = (clWhite, clBlack, clBlack, clBlack, clBlack, clBlack, clWhite, clWhite, clBlack);

implementation

uses Math, propos_f, prmsim_f, afdiste_f, carfours_f, deff_f, defv_f,
  infveh_f, rech_f, stats_f, statsc_f, statsat_f, infbus_f, afdistab_f,
  infptn_f, prmbus_f;

{$R *.xfm}

// D�calage gyrophares d{x|y}g[dorig][ddest]
//                                             ddest =      n   e   s   o
const dxg : array [direction,direction] of Integer = (( 0,  0,  0,  0,  0), // ZOOMx2
                                                      ( 0,  0,  1,  0, -1), // dorig = nord
                                                      ( 0,  1,  0,  1,  0), // dorig = est
                                                      ( 0,  0,  1,  0, -1), // dorig = sud
                                                      ( 0, -1,  0, -1,  0));//dorig = ouest
      dyg : array [direction,direction] of Integer = (( 0,  0,  0,  0,  0),
                                                      ( 0,  0, -1,  0, -1), // dorig = nord
                                                      ( 0, -1,  0,  1,  0), // dorig = est
                                                      ( 0,  0,  1,  0,  1), // dorig = sud
                                                      ( 0, -1,  0,  1,  0));//dorig = ouest
// v3.0 : N�image de bus � partir de IDB_BUS: [Dir1,Dir2,avt|arr] Dir2 = N       E       S                Dir1
      NumImgBus : array [0..NBDIRS-1,0..NBDIRS-1,0..1] of Integer = ((( 1, 7),( 2, 9),(12,12),( 0, 5)), // N
                                                                     (( 3, 8),( 4,10),( 5, 0),(12,12)), // E
                                                                     ((12,12),( 6,11),( 7, 1),( 8, 3)), // S
                                                                     ((11, 6),(12,12),( 9, 2),(10, 4)));// O

      IDB_DIR     =  0;
      IDB_FEU     =  4;
      IDB_STOP    = 20;
      IDB_CLP     = 24;
      IDB_VOIE    = 28;
      IDB_CURSEUR = 44;
      IDB_CURSERR = 45;
      IDB_ETAPE   = 46;
      IDB_SELFEU  = 47;
      IDB_DIRTD   = 51;
      IDB_VEH     = 55;
      IDB_PSGPT   =127;
      IDB_PIETON  =129;
      IDB_URGENCE =153;
      IDB_POLICE  =157;
      IDB_VEHPU   =165;
      IDB_NUMETAPE=189;
      IDB_ARRETBUS=221; // v3.0
      IDB_BUS=     233; // v3.0
      IDB_DEPOTBUS=341; // v3.0

      // v3.0 : 2�me indice de NumImgBus
      TETE=0; QUEUE=1;

      NBCOULDIFFV   =6;
      NBCOULDIFFVPU =2;
      NBCOULDIFFP   =3;
      COULEURURGENCE=1;

      MAXHEIGHTFSIMUL=602;
      MAXWIDTHFSIMUL =800;

      NB_ELEMENTS_PAR_DEFAUT  =true;
      AUCUN_ELEMENT_PAR_DEFAUT=false;

      stCvw = 'Cvw';
      stVide = '';
      stChargementNonEffectue = 'Chargement non effectu�';
      stSauvegardeNonEffectuee = 'Sauvegarde non effectu�e';
      stMemInsuff = 'M�moire insuffisante !';
      stErrInattendue = 'Erreur inattendue';
      stErrDsReseau = 'Une erreur a �t� trouv�e dans le r�seau !';
      stAvertissement = 'Impossible de continuer';
      stReseauNonConnexe = 'Le r�seau n''est pas connexe : une distance � une �tape n''a pas pu �tre d�finie !';
      stNbEtapesInsuff = 'Il manque des �tapes !';
      stSelectionIncorrecte = 'S�lection incorrecte';
      stTracerEffacerPeripherique = 'Pour tracer ou effacer un p�riph�rique;'#13#10'vous devez s�lectionner au moins 2 lignes et 2 colonnes.';
      stNombreLignesColonnesDifferent = 'Le nombre de lignes s�lectionn�es doit �tre diff�rent du nombre de colonnes s�lectionn�es.';
      stTracerEffacerRoute = 'Vous ne devez s�lectionner...'#13#10' - qu''1 SEULE LIGNE ou qu''1 SEULE COLONNE pour tracer ou effacer une route � SENS UNIQUE.'#13#10' - que 2 LIGNES ou 2 COLONNES pour tracer ou effacer une route � DOUBLE SENS.';
      stFrmTitleCV = 'Centre-Ville [%d]';
      stFrmCaptionCV = 'Centre-Ville - %s [%d]';
      stTitreCV = 'Centre-Ville';
      stQstEnregistrerFichier = 'Voulez-vous enregistrer le fichier ';
      stFormatBilan : array [0..12] of String = ( 'Donn�es initiales'#13#10#13#10,
                                                  ' - Nombre de v�hicules : %d'#13#10,
                                                  ' - Parcours minimum moyen par v�hicule (cases) : %.2f'#13#10,
                                                  ' - Temps minimum moyen par v�hicule (tours) : %.2f'#13#10,
                                                  ' - Temps minimum moyen d''attente de d�part par v�hicule : %d'#13#10#13#10,
                                                  'Bilan au tour n�%d'#13#10#13#10,
                                                  ' - Nombre de v�hicule(s) arriv�(s) : %d (%.2f%%)'#13#10,
                                                  ' - Parcours moyen effectu� par v�hicule (cases) : %.2f (%.2f%%)'#13#10,
                                                  ' - Attente de d�part par v�hicule (tours) : %.2f (%.2f%%)'#13#10,
                                                  ' - Temps moyen du parcours par v�hicule (tours) : %.2f (%.2f%%) dont'#13#10,
                                                  '    � D�placement par v�hicule (tours) : %.2f (%.2f%%)'#13#10,
                                                  '    � Attente par v�hicule (tours) : %.2f (%.2f%%)'#13#10#13#10,
                                                  'Voulez-vous voir les statistiques de fluidit� et de trafic en couleurs ?');
      stFormatBilanSansArrives : array [0..7] of String = ( 'Donn�es initiales'#13#10#13#10,
                                                            ' - Nombre de v�hicules : %d'#13#10,
                                                            ' - Parcours minimum moyen par v�hicule (cases) : %.2f'#13#10,
                                                            ' - Temps minimum moyen par v�hicule (tours) : %.2f'#13#10,
                                                            ' - Temps minimum moyen d''attente de d�part par v�hicule : %d'#13#10#13#10,
                                                            'Bilan au tour n�%d'#13#10#13#10,
                                                            ' Aucun v�hicule n''est encore arriv�.'#13#10#13#10,
                                                            'Voulez-vous voir les statistiques de fluidit� et de trafic en couleurs ?');
      stRubriqueDeplacerFeu : array [0..1] of String = ('D�placer ce &feu', 'D�placer le &feu sur cette case');
      stTypeVehicule : array [0..NBNIVEAUXPRIORITE-1] of String = ('', 'd''urgence','de police');
//---------------------------------------------------------------------------
procedure TfrmSimulation.RedessineCase(x, y : Integer; EffaceFond : Boolean);
begin
 DrawGridSimul.InvalidateRect(DrawGridSimul.CellRect(x, y), EffaceFond);
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueAProposClick(Sender: TObject);
begin
 frmAPropos.ShowModal;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.FormCreate(Sender: TObject);
begin
 Affichages:=affichage(Integer(aff_sign) or Integer(aff_voie));
 xErr:=-1; yErr:=-1;
 SimulEnCours:=false;
 SimulModifiee:=false;
 EnregistrerAvant:=false;
 DeplacementFeuEnCours:=false;
 xDeplFeu:=-1; yDeplFeu:=-1;
 RubriqueDeplacerFeu.Caption:=stRubriqueDeplacerFeu[0];
 cv:=centre_ville.Create(NB_ELEMENTS_PAR_DEFAUT);
 frmAPropos:=TfrmAPropos.Create(self);
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.FormShow(Sender: TObject);
begin
 SimulEnCours:=true;
 TypeDemande:=rien;
 with frmAPropos do
  begin
  FermetureAutomatique:=true;
  Show;
  ImageVersion.Repaint;
  LabelCV2.Repaint;
  LabelCV1.Repaint;
  LabelAuteur2.Repaint;
  LabelAuteur1.Repaint;
  LabelTexte.Repaint;
  LabelSousVersion.Repaint; // v2.2.4
  LabelURL.Repaint;
  LabelEMail.Repaint;
  end{with};
 SimulEnCours:=false;
 SelectionFeuxDmd:=false;
 SelectionFeuxAtt:=false;
 if ParamCount>0 then
  begin
   stNomFichAuto:=AnsiString(ParamStr(1));
   SimulEnCours:=true;
   RubriqueOuvrir.Click();
   SimulEnCours:=false;
  end;
 ToolButtonAffDir.Down:=(Integer(Affichages) and Integer(aff_dir)>0);
 ToolButtonAffSign.Down:=(Integer(Affichages) and Integer(aff_sign)>0);
 ToolButtonAffRoutes.Down:=(Integer(Affichages) and Integer(aff_voie)>0);
 ToolButtonAffVeh.Down:=(Integer(Affichages) and Integer(aff_veh)>0);
 ToolButtonAffPtn.Down:=(Integer(Affichages) and Integer(aff_ptn)>0);
 RubriqueDirections.Checked:=ToolButtonAffDir.Down;
 RubriqueSignalisation.Checked:=ToolButtonAffSign.Down;
 RubriqueRoutes.Checked:=ToolButtonAffRoutes.Down;
 RubriqueVehicules.Checked:=ToolButtonAffVeh.Down;
 RubriquePietons.Checked:=ToolButtonAffPtn.Down;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.FormDestroy(Sender: TObject);
begin
 if cv<>nil then begin cv.Destroy; cv:=nil; end;
 if (frmAPropos<>nil) then
  begin
  frmAPropos.Release;
  frmAPropos:=nil;
  end;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.DrawGridSimulDrawCell(Sender: TObject; ACol,
  ARow: Integer; Rect: TRect; State: TGridDrawState);
var i,
    Colonnes,
    Lignes,
    PassPoss,
    NumPieton : Integer;
    NivPriorite : niveau_priorite;
    d, dorig, ddest,
    DirArretBus : direction; // v3.0
    v : pVoie;
    sns : sens;
    p : pPieton;
    veh : pVehicule;
    b : pBus;
    NordPoss,
    EstPoss,
    SudPoss,
    OuestPoss,
    ToutDroit,
    PassagePietons,
    DefFeux : Boolean;
    stMsg : String;
    CheckBox : TCheckBox; // v3.0
    CoulTxt : TColor; // v3.0.5

begin
  Colonnes:=DrawGridSimul.Selection.Right-DrawGridSimul.Selection.Left+1;
  Lignes:=DrawGridSimul.Selection.Bottom-DrawGridSimul.Selection.Top+1;
  PassPoss:=0;
  v:=@(cv.v[ACol][ARow]);
  sns:=cv.SensPassagePietonsPossible(ACol, ARow);
  DefFeux:=frmDefFeux.Visible;

  stMsg:='';

  // 1.a. Stats d'Attente/Trafic (v2.2.7)
  if StatsAttenteTrafic and
     (frmStatsAttenteTrafic<>nil) and
     (v.DirPoss>aucune) and
     (v.NumEtape=0) then
   begin
   DrawGridSimul.Canvas.Brush.Color:=frmStatsAttenteTrafic.CouleurCase(ACol, ARow);
   DrawGridSimul.Canvas.FillRect(Rect);
   end
  else // 1.b. On met le bitume. � savoir, o� passe la route... Si on peut aller ou venir du nord, on pose le bitume jusqu'en haut, et ainsi de suite...
   if (Integer(Affichages) and (Integer(aff_voie) or Integer(aff_quadr)))>0 then
    begin
     for d:=nord to ouest do
      Inc(PassPoss, Integer(PossDir[d])*Ord(((Integer(v.DirPoss) and
                                              Integer(PossDir[d]))=Integer(PossDir[d])) or
                                            ((Integer(cv.vxyd(ACol,ARow,d).DirPoss) and
                                              Integer(InvPossDir[d]))=Integer(InvPossDir[d]))));
     if (Integer(Affichages) and
         ((Ord(PassPoss=0)*Integer(aff_quadr)) or
          (Ord(PassPoss>0)*Integer(aff_voie))))>0 then
      ImageList8x8x2.Draw(DrawGridSimul.Canvas, Rect.Left, Rect.Top, IDB_VOIE+PassPoss);
    end;
  // 2. On peint la route : ligne de stop ou c�dez-le-passage
  if (Integer(Affichages) and Integer(aff_sign))>0 then
   begin
    for i:=0 to 3 do
     case v.Priorites[i] of
        cedez_le_passage: ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                                              Rect.Left, Rect.Top,
                                              IDB_CLP+i);
        stop:             ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                                              Rect.Left, Rect.Top,
                                              IDB_STOP+i);
     end{case of};
  // 2bis. On peint le passage pi�tons
    if v.PassagePietons and (sns>indefini) then
     begin
      ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                         Rect.Left, Rect.Top,
                         IDB_PSGPT+Integer(sns)-1);
     end;
  // 2ter. On peint l'arr�t de bus. v3.0
    if v.NumArretBus>0 then
     begin
     DirArretBus:=cv.DirectionArretBus(ACol, ARow);
     if DirArretBus>indefinie then
      if (frmParamBus=nil) or
         not frmParamBus.Visible or
         (frmParamBus.NumArretBusAMontrer<>v.NumArretBus) or
         (frmParamBus.TimerClignotement.Tag>0) then
       ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                           Rect.Left, Rect.Top,
                           IDB_ARRETBUS+
                           3*(Integer(DirArretBus)-1)+
                           Integer(cv.PositionArretBus(ACol, ARow, DirArretBus)));
     end
   end;
  // 3. On met le v�hicule le cas �ch�ant
  if ((Integer(Affichages) and
       Integer(aff_veh))>0) and
     (v.NumEtape=0) and     // v3.0. SI pas d'�tape ET
     not v.EstDepotBus then //       NI de d�p�t de bus 
   begin
    if (v.NumVehicule>0) then
     begin
      Veh:=@(cv.Vehicules[v.NumVehicule-1]);
      if Veh.DirDrnDepl>indefinie then
       dorig:=InvDir[Veh.DirDrnDepl]
      else
       dorig:=InvDir[Veh.Dir];
      ddest:=Veh.Dir;
      if dorig=ddest then dorig:=InvDir[ddest];
      case Veh.NivPriorite of
         normal:  ImageList8x8x2.Draw( DrawGridSimul.Canvas,
                                       Rect.Left, Rect.Top,
                                       IDB_VEH+ // Numero de bitmap initiale des v�hicules
                                       (v.NumVehicule-1) mod NBCOULDIFFV+ // Num�ro de couleur
                                       (3*(Integer(dorig)-1)+Integer(ddest)-1-Ord(ddest>dorig))*NBCOULDIFFV);
         urgence: begin
                  ImageList8x8x2.Draw( DrawGridSimul.Canvas,
                                       Rect.Left, Rect.Top,
                                       IDB_VEHPU+ // Numero de bitmap initiale des v�hicules de police/urgence
                                       COULEURURGENCE+ // Num�ro de couleur (rouge)
                                       (3*(Integer(dorig)-1)+Integer(ddest)-1-Ord(ddest>dorig))*NBCOULDIFFVPU);
                  ImageList8x8x2.Draw( DrawGridSimul.Canvas,
                                       Rect.Left+dxg[dorig][ddest],
                                       Rect.Top+dyg[dorig][ddest],
                                       IDB_URGENCE+ // Numero de bitmap initiale des gyrophares
                                       2*((Integer(dorig)+Integer(ddest)) mod 2)+ // Horizontal/vertical ou en diagonale
                                       cv.TourCrt mod 2); // Clignotement
                  end;
         police:  begin
                  ImageList8x8x2.Draw( DrawGridSimul.Canvas,
                                       Rect.Left, Rect.Top,
                                       IDB_VEHPU+ // Numero de bitmap initiale des v�hicules de police/urgence
                                       // Couleur Police = 1�re couleur (blanche)
                                       (3*(Integer(dorig)-1)+Integer(ddest)-1-Ord(ddest>dorig))*NBCOULDIFFVPU);
                  ImageList8x8x2.Draw( DrawGridSimul.Canvas,
                                       Rect.Left+dxg[dorig][ddest],
                                       Rect.Top+dyg[dorig][ddest],
                                       IDB_POLICE+ // Numero de bitmap initiale des gyrophares
                                       2*((Integer(dorig)+Integer(ddest)) mod NBDIRS)+ // Direction
                                       cv.TourCrt mod 2); // Clignotement
                  end;
      end{case of};
     end{if NumVehicule>0};
    // 3bis. On met une moiti� de bus le cas �ch�ant. v3.0
    if v.NumBus>0 then
     begin
      b:=@(cv.Autobus[v.NumBus-1]);
      if v.EstTeteBus then
       ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                           Rect.Left, Rect.Top,
                           IDB_BUS+ // N� de bitmap initiale des bus
                           12*(b.NumLigne-1)+ // Couleur de la ligne du bus
                           NumImgBus[Integer(b.Dir)-1, Integer(b.DirDrnDepl)-1, TETE]) // T�te de bus
      else
       ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                           Rect.Left, Rect.Top,
                           IDB_BUS+ // N� de bitmap initiale des bus
                           12*(b.NumLigne-1)+ // Couleur de la ligne du bus
                           NumImgBus[Integer(b.DirDrnDepl)-1, Integer(b.DirAvtDrnDepl)-1, QUEUE]); // Queue du bus
     end{if NumBus}
   end{if Affichages};
  // 3ter. On met le(s) pi�ton(s) le(s) cas �ch�ant(s).
  // (Oui 3bis parce que je suis fain�ant de d�caler. La prochaine fois je fais comme en Basic : de 10 en 10, na.)
  if (Integer(Affichages) and Integer(aff_ptn)>0) and (v.NbPietons>0) then
   for i:=0 to NBMAXPIETONSPARCASE-1 do
    if v.NumPieton[i]>0 then
     begin // On d�cale les pi�tons pour qu'ils puissent entrer dans une case. On prend alors la direction du premier
      NumPieton:=v.NumPieton[i]-1;
      p:=@(cv.Pietons[NumPieton]);
      if p.TourDrnDepl<p.TourDrnAff then // � l'arr�t
       ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                           1+Rect.Left+(2*p.DemiCase-1)*dxr[p.Dir]*((1+Rect.Right-Rect.Left) div 4),
                           1+Rect.Top+ (2*p.DemiCase-1)*dyr[p.Dir]*((1+Rect.Bottom-Rect.Top) div 4),
                           IDB_PIETON+                // D�but image pi�ton
                           8*(NumPieton mod NBCOULDIFFP)+ // Couleur
                           Integer(p.Dir)-1) // <-- � l'arr�t
      else // en mouvement
       ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                           1+Rect.Left+(2*p.DemiCase-1)*dxr[p.Dir]*((1+Rect.Right-Rect.Left) div 4),
                           1+Rect.Top+ (2*p.DemiCase-1)*dyr[p.Dir]*((1+Rect.Bottom-Rect.Top) div 4),
                           IDB_PIETON+                // D�but image pi�ton
                           8*(NumPieton mod NBCOULDIFFP)+ // Couleur
                           (4+p.DemiCase mod 2+2*(1-Integer(p.Dir) mod 2))); // <-- en mouvement
      p.TourDrnAff:=cv.TourCrt;
     end;
  // 4. On met le feu (ouais qu'�a p�te !) de signalisation le cas �ch�ant
  if (Integer(Affichages) and Integer(aff_sign))>0 then
   for i:=0 to 3 do
    if ((v.NumFeu[i]>0) and
        (cv.Feux[v.NumFeu[i]-1].x=ACol) and 
        (cv.Feux[v.NumFeu[i]-1].y=ARow) and 
        (Integer(cv.Feux[v.NumFeu[i]-1].Dir)=i+1)) then
     ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                         Rect.Left, Rect.Top,
                         IDB_FEU+4*i+Integer(cv.Feux[v.NumFeu[i]-1].Etat));

  // 5a. On met l'�tape le cas �ch�ant et qqsoit l'affichage
  if v.NumEtape>0 then
   begin
    ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                        Rect.Left, Rect.Top,
                        IDB_ETAPE);
    ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                        Rect.Left, Rect.Top,
                        IDB_NUMETAPE+v.NumEtape-1);
   end;
  // 5b. On met le d�p�t de bus le cas �ch�ant et qqsoit l'affichage. v3.0
  if v.EstDepotBus then
   ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                       Rect.Left, Rect.Top,
                       IDB_DEPOTBUS);
  // 6. Affichages des directions possibles
  if (Integer(Affichages) and Integer(aff_dir))>0 then
   for i:=0 to 3 do
    if (Integer(v.DirPoss) and Integer(PossDir[direction(i+1)]))>0 then
     ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                         Rect.Left, Rect.Top,
                         IDB_DIR+(IDB_DIRTD*Ord(v.ToutDroit))+i);
  // 7. Trajet des lignes de bus. v3.0
  if (frmParamBus<>nil) and frmParamBus.Visible then
   begin
    CoulTxt:=clTeal; // Couleur arbitraire (ni blanc, ni noir)
    for i:=0 to NBMAXLIGNESBUS-1 do
     begin
      CheckBox:=frmParamBus.FindComponent('CheckBox'+IntToStr(i+1)) as TCheckBox;
      if CheckBox.Visible and CheckBox.Checked and v.LigneBus[i] then
       begin
        DrawGridSimul.Canvas.Brush.Color:=CoulLigneBus[i];
        DrawGridSimul.Canvas.FillRect(Rect);
        CoulTxt:=CoulTLigneBus[i];
       end;
     end{for};
    if v.EstTeteArretBus and (CoulTxt<>clTeal) then // On �crit le num�ro de l'arr�t de bus
     begin
      DrawGridSimul.Canvas.Font:=DrawGridSimul.Font;
      DrawGridSimul.Canvas.Font.Color:=CoulTxt;
      DrawGridSimul.Canvas.TextOut( Rect.Left+(Rect.Right-Rect.Left+1-DrawGridSimul.Canvas.TextWidth(IntToStr(v.NumArretBus))) div 2,
                                    Rect.Top+(Rect.Bottom-Rect.Top+1-DrawGridSimul.Canvas.TextHeight(IntToStr(v.NumArretBus))) div 2,
                                    IntToStr(v.NumArretBus));
     end;
   end; 
  // 8. Case o� est le curseur : on en profite pour raffraichir l'�tat des ToolButtons
  if (DrawGridSimul.Col=ACol) and (DrawGridSimul.Row=ARow) then
   begin
    if v.ToutDroit then stMsg:=stMsg+'Tout droit. ';
    for i:=0 to 3 do
     begin
     d:=direction(i+1);  // Permet de remplacer les direction(i+1)
     if  (v.NumFeu[i]>0) and
         (cv.Feux[v.NumFeu[i]-1].x=ACol) and
         (cv.Feux[v.NumFeu[i]-1].y=ARow) and
         (cv.Feux[v.NumFeu[i]-1].Dir=d) then
      stMsg:=stMsg+Format('Feux %s %d. ', [stDir[d], v.NumFeu[i]]);
     end;
    if v.NumEtape>0 then
     stMsg:=stMsg+Format('Etape %d. ', [v.NumEtape]);
    if v.EstDepotBus then // v3.0
     stMsg:=stMsg+'D�p�t de bus. ';
    if v.NumArretBus>0 then // v3.0
     if v.EstTeteArretBus then
      stMsg:=stMsg+Format( 'Arr�t %d* (%s). ',
                           [ v.NumArretBus,
                             cv.ArretsBus[v.NumArretBus-1].stListeLignesBus]) // v3.0.5
     else
      stMsg:=stMsg+Format( 'Arr�t %d (%s). ',
                           [ v.NumArretBus,
                             cv.ArretsBus[v.NumArretBus-1].stListeLignesBus]); // v3.0.5
    if v.NumVehicule>0 then
     begin
     NivPriorite:=cv.Vehicules[v.NumVehicule-1].NivPriorite;
     if NivPriorite>normal then
      stMsg:=stMsg+Format('V�hicule %s %d. ', [stTypeVehicule[Integer(NivPriorite)], v.NumVehicule])
     else
      stMsg:=stMsg+Format('V�hicule %d. ', [v.NumVehicule]);
     end;
    if v.NumBus>0 then // v3.0
     if v.EstTeteBus then
      stMsg:=stMsg+Format('Bus %d*. ', [v.NumBus])
     else
      stMsg:=stMsg+Format('Bus %d. ', [v.NumBus]);
    if v.NbPietons>0 then
     begin
      stMsg:=stMsg+'Pi�ton';
      if v.NbPietons>1 then stMsg:=stMsg+'s';
      for i:=0 to NBMAXPIETONSPARCASE-1 do
       if v.NumPieton[i]>0 then
        if cv.Pietons[v.NumPieton[i]-1].DemiCase>0 then
         stMsg:=stMsg+Format('%s%d', ['`', v.NumPieton[i]])
        else
         stMsg:=stMsg+Format('%s%d', [' ', v.NumPieton[i]]);
      stMsg:=stMsg+'. ';
     end;
    // v3.0 : Affichage du d�tail des statistiques de fluidit� et de trafic pour la case courante
    if StatsAttenteTrafic and (frmStatsAttenteTrafic<>nil) then
     StatusBar.Panels.Items[0].Text:=frmStatsAttenteTrafic.stMsgDetailCase(ACol, ARow);
    StatusBar.Panels.Items[1].Text:=stMsg;
    StatusBar.Panels.Items[2].Text:=stDirPoss[v.DirPoss];
    StatusBar.Panels.Items[3].Text:=Format(stFormatCoord, [ACol, ARow]);
    if not SelectionFeuxDmd and
       not SelectionFeuxAtt then// Pas de curseur en s�lection de feux
     ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                         Rect.Left, Rect.Top,
                         IDB_CURSEUR);
    NordPoss:=((Integer(v.DirPoss) and Integer(N))=Integer(N));
    EstPoss:=((Integer(v.DirPoss) and Integer(E))=Integer(E));
    OuestPoss:=((Integer(v.DirPoss) and Integer(O))=Integer(O));
    SudPoss:=((Integer(v.DirPoss) and Integer(S))=Integer(S));
    ToutDroit:=v.ToutDroit;
    PassagePietons:=v.PassagePietons;

    ToolButtonNord.Down:=NordPoss;
    ToolButtonNord.Enabled:=(v.Priorites[Integer(nord)-1]=a_droite) and not DefFeux and (cv.TourCrt=0) and not SimulationEnCours;
    RubriqueDirectionHaut.Checked:=ToolButtonNord.Down;
    RubriqueDirectionHaut.Enabled:=ToolButtonNord.Enabled;

    ToolButtonEst.Down:=EstPoss;
    ToolButtonEst.Enabled:=(v.Priorites[Integer(est)-1]=a_droite) and not DefFeux and (cv.TourCrt=0) and not SimulationEnCours;
    RubriqueDirectionDroite.Checked:=ToolButtonEst.Down;
    RubriqueDirectionDroite.Enabled:=ToolButtonEst.Enabled;

    ToolButtonSud.Down:=SudPoss;
    ToolButtonSud.Enabled:=(v.Priorites[Integer(sud)-1]=a_droite) and not DefFeux and (cv.TourCrt=0) and not SimulationEnCours;
    RubriqueDirectionBas.Checked:=ToolButtonSud.Down;
    RubriqueDirectionBas.Enabled:=ToolButtonSud.Enabled;

    ToolButtonOuest.Down:=OuestPoss;
    ToolButtonOuest.Enabled:=(v.Priorites[Integer(ouest)-1]=a_droite) and not DefFeux and (cv.TourCrt=0) and not SimulationEnCours;
    RubriqueDirectionGauche.Checked:=ToolButtonOuest.Down;
    RubriqueDirectionGauche.Enabled:=ToolButtonOuest.Enabled;

    ToolButtonToutDroit.Down:=ToutDroit;
    RubriqueToutDroit.Checked:=ToolButtonToutDroit.Down;
    RubriqueToutDroit.Enabled:=ToolButtonToutDroit.Enabled;

    ToolButtonEtape.Down:=(v.NumEtape>0);
    ToolButtonEtape.Enabled:=(Integer(v.Priorites[0])+
                              Integer(v.Priorites[1])+
                              Integer(v.Priorites[2])+
                              Integer(v.Priorites[3])=0) and
                             not DefFeux and
                             (NbDir[v.DirPoss]<NBDIRS) and
                             (cv.TourCrt=0) and
                             not SimulationEnCours;
    RubriqueEtape.Checked:=ToolButtonEtape.Down;
    RubriqueEtape.Enabled:=ToolButtonEtape.Enabled;

    ToolButtonDepotBus.Down:=v.EstDepotBus; // v3.0
    ToolButtonDepotBus.Enabled:=(v.NumEtape=0) and
                                (Integer(v.Priorites[0])+
                                 Integer(v.Priorites[1])+
                                 Integer(v.Priorites[2])+
                                 Integer(v.Priorites[3])=0) and
                                not DefFeux and
                                (NbDir[v.DirPoss]>0) and
                                (cv.TourCrt=0) and
                                not SimulationEnCours;
    RubriqueDepotBus.Checked:=ToolButtonDepotBus.Down;
    RubriqueDepotBus.Enabled:=ToolButtonDepotBus.Enabled;

    ToolButtonPassagePietons.Down:=PassagePietons;
    RubriquePassagePietons.Checked:=ToolButtonPassagePietons.Down;
    ToolButtonPassagePietons.Enabled:=(sns>indefini);
    RubriquePassagePietons.Enabled:=ToolButtonPassagePietons.Enabled;

    ToolButtonArretBus.Down:=(v.NumArretBus>0); // v3.0
    RubriqueArretBus.Checked:=ToolButtonArretBus.Down; // v3.0
    if v.NumArretBus>0 then // v3.0
     ToolButtonArretBus.Enabled:=cv.SuppressionArretBusPossible(ACol, ARow)
    else
     ToolButtonArretBus.Enabled:=cv.AjoutArretBusPossible(ACol, ARow);
    RubriqueArretBus.Enabled:=ToolButtonArretBus.Enabled; // v3.0

    ToolButtonMajVoie.Enabled:=(v.NumEtape=0)  and not DefFeux and (cv.TourCrt=0) and not SimulationEnCours;
    RubriquePriorites.Enabled:=ToolButtonMajVoie.Enabled;

    ToolButtonMarche.Enabled:=not DefFeux and not SimulationEnCours;
    RubriqueMarche.Enabled:=ToolButtonMarche.Enabled;

    RubriqueSuivreCeVehicule.Enabled:=(v.NumVehicule>0); // v3.0
    RubriqueSuivreCeBus.Enabled:=(v.NumBus>0); // v3.0
    RubriqueSuivreLe1erPieton.Enabled:=(v.NumPieton[0]>0); // v3.0
    RubriqueSuivreLe2emePieton.Enabled:=(v.NumPieton[1]>0); // v3.0

    // Boutons d'affichage (rafra�chissement, Syst�me XWindows uniquement)
    if ToolButtonAffDir.Down<>(Integer(Affichages) and Integer(aff_dir)>0) then
     ToolButtonAffDir.Down:=not ToolButtonAffDir.Down;
    if ToolButtonAffSign.Down<>(Integer(Affichages) and Integer(aff_sign)>0) then
     ToolButtonAffSign.Down:=not ToolButtonAffSign.Down;
    if ToolButtonAffRoutes.Down<>(Integer(Affichages) and Integer(aff_voie)>0) then
     ToolButtonAffRoutes.Down:=not ToolButtonAffRoutes.Down;
    if ToolButtonAffVeh.Down<>(Integer(Affichages) and Integer(aff_veh)>0) then
     ToolButtonAffVeh.Down:=not ToolButtonAffVeh.Down;
    if ToolButtonAffPtn.Down<>(Integer(Affichages) and Integer(aff_ptn)>0) then
     ToolButtonAffPtn.Down:=not ToolButtonAffPtn.Down;
    if ToolButtonAffQuadr.Down<>(Integer(Affichages) and Integer(aff_quadr)>0) then
     ToolButtonAffQuadr.Down:=not ToolButtonAffQuadr.Down;
   end;

  // 8. Case illustr�e par un message
  if not SelectionFeuxDmd and not SelectionFeuxAtt and (xErr=ACol) and (yErr=ARow) then
   ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                       Rect.Left, Rect.Top,
                       IDB_CURSERR);

  // 9. feux s�lectionn�s depuis la fen�tre de d�finition d'un feu
  if SelectionFeuxDmd then
   for i:=0 to frmDefFeux.NbFeuxDmd-1 do
    if (cv.Feux[frmDefFeux.NumFeuxDmd[i]-1].x=ACol) and
       (cv.Feux[frmDefFeux.NumFeuxDmd[i]-1].y=ARow) then
     ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                        Rect.Left, Rect.Top,
                        IDB_SELFEU+Integer(cv.Feux[frmDefFeux.NumFeuxDmd[i]-1].Dir)-1);
  if SelectionFeuxAtt then
   for i:=0 to frmDefFeux.NbFeuxAtt-1 do
    if (cv.Feux[frmDefFeux.NumFeuxAtt[i]-1].x=ACol) and
       (cv.Feux[frmDefFeux.NumFeuxAtt[i]-1].y=ARow) then
     ImageList8x8x2.Draw(DrawGridSimul.Canvas,
                        Rect.Left, Rect.Top,
                        IDB_SELFEU+Integer(cv.Feux[frmDefFeux.NumFeuxAtt[i]-1].Dir)-1); 
  if (Colonnes>1) or (Lignes>1) then
   StatusBar.Panels.Items[0].Text:=Format( 'S�lection en cours : %d colonne(s) et %d ligne(s)',
                                           [Colonnes, Lignes])
  else
   if Pos('S�lection en cours', StatusBar.Panels.Items[0].Text)>0 then
    StatusBar.Panels.Items[0].Text:='';
end;
//---------------------------------------------------------------------------
function TfrmSimulation.EnregistreModificationsAvant(Operation : operation_avant) : Boolean;
var mrRep : TMessageButton;
    stMessage : String;
 begin
  Result:=false; // Evite le message 'Return value of function might be undefined'
  if not SimulModifiee then begin Result:=true; Exit end; // Inutile car pas de modif
  case Operation of
    oaNouveau: stMessage:=stQstEnregistrerFichier+
                              SaveDialog.FileName+' avant de cr�er une nouvelle simulation ?';
    oaOuvrir:  stMessage:=stQstEnregistrerFichier+
                              SaveDialog.FileName+' avant d''ouvrir une autre simulation ?';
    oaQuitter: stMessage:=stQstEnregistrerFichier+
                              SaveDialog.FileName+' avant de quitter ?';
   end{case of};
  mrRep:=Application.MessageBox( stMessage, 'Confirmation', [smbYes, smbNo, smbCancel], smsWarning, smbCancel);
  case mrRep of
   smbYes:    begin
              EnregistrerAvant:=true;
              RubriqueEnregistrerClick(self);
              // Enregistrement annul� : on annule la cr�ation
              if not EnregistrerAvant then Result:=false else Result:=true;
              end;
   smbNo:     begin
              if EnregistrerAvant then EnregistrerAvant:=false;
              Result:=true;
              end;
   smbCancel: Result:=false;
  end {case of};
end{function EnregistreModificationsAvant};
//---------------------------------------------------------------------------
procedure TfrmSimulation.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
 Action:=caFree;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueNouveauClick(Sender: TObject);
begin
 if EnregistreModificationsAvant(oaNouveau) then
  begin
   if cv<>nil then cv.Destroy;
   cv:=centre_ville.Create(NB_ELEMENTS_PAR_DEFAUT);
   SimulModifiee:=false;
   stNomFichAuto:='';
   SaveDialog.FileName:='';
   OpenDialog.FileName:='';
   Caption:=stTitreCV;
   DrawGridSimul.Repaint;
  end;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueOuvrirClick(Sender: TObject);
var stNomFichier : String;
    hfile : Integer;
begin
 stNomFichier:='';
 if (stNomFichAuto='') and
    not EnregistreModificationsAvant(oaOuvrir) then Exit;
 if (stNomFichAuto<>'') or OpenDialog.Execute then
  begin
   if stNomFichAuto='' then stNomFichier:=OpenDialog.FileName else stNomFichier:=stNomFichAuto;
   hfile:=FileOpen(stNomFichier, fmOpenRead);
   if hfile>0 then
    begin
     StatusBar.Panels.Items[0].Text:='Chargement en cours...';
     Screen.Cursor:=crHourGlass;
     FileSeek(hfile, 0, 0);
     if cv<>nil then begin cv.Destroy; cv:=nil; end;
     cv:=centre_ville.Create(AUCUN_ELEMENT_PAR_DEFAUT);
     if not cv.Charge(hfile) then
      begin
       Application.MessageBox('Erreur de donn�es dans le fichier', stChargementNonEffectue, [smbOk], smsCritical);
       FileClose(hfile);
       Screen.Cursor:=crDefault;
       StatusBar.Panels.Items[0].Text:='Chargement non effectu�.';
       Close;
      end
     else
      begin
       FileClose(hfile);
       SimulModifiee:=false;
       Screen.Cursor:=crDefault;
       SaveDialog.FileName:=stNomFichier;
       OpenDialog.FileName:=stNomFichier;
       Caption:='Centre-Ville - '+stNomFichier;
       if VerifierApresOuverture then
        begin
         StatusBar.Panels.Items[0].Text:='Contr�le d''int�grit� du r�seau en cours...';
         cv.Verifie(stMsgErr);
         if Length(stMsgErr)>0 then
          Application.MessageBox(stMsgErr, 'Erreurs d''int�grit� trouv�es dans le r�seau', [smbOk], smsCritical);
        end;
       // Mise � jour du menu Statistiques | Affichage
       RubriqueQuadrillageStatistiques.Checked:=cv.QuadrillageStats;
       case cv.TypeStats of
         par_nombre:      RubriqueParNbVehicules.Checked:=true;
         par_pourcentage: RubriqueParPourcentage.Checked:=true; 
       end{case of};
       case cv.NbToursStats of
         10:  Rubrique10DrnTours.Checked:=true;
         20:  Rubrique20DrnTours.Checked:=true;
         50:  Rubrique50DrnTours.Checked:=true;
         100: Rubrique100DrnTours.Checked:=true;
         200: Rubrique200DrnTours.Checked:=true;
         500: Rubrique500DrnTours.Checked:=true;
       end{case of};

       StatusBar.Panels.Items[0].Text:='Affichage du r�seau en cours...';
       DrawGridSimul.Repaint;
       if Length(stMsgErr)>0 then
        StatusBar.Panels.Items[0].Text:='Chargement effectu� mais erreur(s) d''int�grit� trouv�e(s)'
       else
        StatusBar.Panels.Items[0].Text:='Chargement termin�.';
      end;
    end
   else
    begin
     Application.MessageBox('Impossible d''ouvrir le fichier', stChargementNonEffectue, [smbOk], smsCritical);
     StatusBar.Panels.Items[0].Text:='Chargement non effectu�.';
    end;
   stNomFichAuto:='';
  end;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueEnregistrerClick(Sender: TObject);
var stNomFichier : String;
    hfile : Integer;
begin
 if (SaveDialog.FileName<>'') or
     (stNomFichAuto<>'') or
     SaveDialog.Execute then
  begin
   StatusBar.Panels.Items[0].Text:='Enregistrement en cours...';
   Screen.Cursor:=crHourGlass;
   if stNomFichAuto='' then stNomFichier:=SaveDialog.FileName else stNomFichier:=stNomFichAuto;
   hfile:=FileCreate(stNomFichier);
   if hfile>0 then
    begin
     if not cv.Sauve(hfile) then
      begin
       Application.MessageBox('Erreur de donn�es dans le fichier', stSauvegardeNonEffectuee, [smbOk], smsCritical);
       FileClose(hfile);
       Screen.Cursor:=crDefault;
       StatusBar.Panels.Items[0].Text:='Enregistrement non effectu�.';
       if EnregistrerAvant then EnregistrerAvant:=false;
      end
     else
      begin
       FileClose(hfile);
       Screen.Cursor:=crDefault;
       SaveDialog.FileName:=stNomFichier;
       OpenDialog.FileName:=stNomFichier;
       Caption:='Centre-Ville - '+stNomFichier;
       StatusBar.Panels.Items[0].Text:='Enregistrement termin�.';
       SimulModifiee:=false;
      end;
    end
   else
    begin
     Screen.Cursor:=crDefault;
     Application.MessageBox('Impossible de cr�er le fichier', stSauvegardeNonEffectuee, [smbOk], smsCritical);
     StatusBar.Panels.Items[0].Text:='Enregistrement non effectu�.';
     if EnregistrerAvant then EnregistrerAvant:=false;
    end;
  end
 else
  if EnregistrerAvant then EnregistrerAvant:=false;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueEnregistrerSousClick(Sender: TObject);
begin
 if SaveDialog.Execute then RubriqueEnregistrer.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonAffichagesClick(Sender: TObject);
var aff : affichage;
begin
 aff:=affichage((Sender as TToolButton).Tag);
 case aff of
  aff_dir:   RubriqueDirections.Checked:=ToolButtonAffDir.Down;
  aff_sign:  RubriqueSignalisation.Checked:=ToolButtonAffSign.Down;
  aff_voie:  RubriqueRoutes.Checked:=ToolButtonAffRoutes.Down;
  aff_veh:   RubriqueVehicules.Checked:=ToolButtonAffVeh.Down;
  aff_ptn:   RubriquePietons.Checked:=ToolButtonAffPtn.Down;
  aff_quadr: RubriqueQuadrillage.Checked:=ToolButtonAffQuadr.Down;
 end{case of};
 if (Integer(Affichages) and
     Integer(aff)>0) xor
    (Sender as TToolButton).Down then
  Affichages:=affichage(Integer(Affichages) xor Integer(aff));
 DrawGridSimul.Repaint;
end;
//---------------------------------------------------------------------------
function TfrmSimulation.ModifiePassagePietonsSiNecessaire(x, y : Integer) : Boolean;
var v : pVoie;
 begin
  v:=@(cv.v[x, y]);
  if v.PassagePietons and (cv.SensPassagePietonsPossible(x,y)=indefini) then
   begin
    SimulModifiee:=true;
    v.PassagePietons:=false;
    RedessineCase(x mod NBX, y mod NBY, true);
    Result:=true;
   end
  else
   Result:=false;
 end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonNESOClick(Sender: TObject);
var x, y : Integer;
    d : direction;
begin
 x:=DrawGridSimul.Col;
 y:=DrawGridSimul.Row;
 d:=direction((Sender as TToolButton).Tag);
 if cv.ChangeDirectionSiPossible(x, y, PossDir[d]) then
  begin
   ModifiePassagePietonsSiNecessaire(x, y);
   SimulModifiee:=true;
   RedessineCase((x+dx[d]) mod NBX, (y+dy[d]) mod NBY, true);
   if ToolButtonMajVoie.Down then frmDefVoie.RafraichitInfos;
  end;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonEtapeClick(Sender: TObject);
var x, y, NumEtape : Integer;
    stMsgOp : String;
begin
 x:=DrawGridSimul.Col;
 y:=DrawGridSimul.Row;
 NumEtape:=cv.v[x, y].NumEtape;
 if NumEtape>0 then // Si �tape on la supprime
  begin
   cv.SupprimeEtape(NumEtape-1);
   stMsgOp:=Format('L''�tape num�ro %d a �t� supprim�e.', [NumEtape]);
   SimulModifiee:=true;
  end
 else // Sinon on la cr�e
  begin
   NumEtape:=cv.AjouteEtape(x, y);
   if NumEtape>0 then
    begin
     stMsgOp:=Format('L''�tape cr��e a le num�ro %d.', [NumEtape]);
     SimulModifiee:=true;
    end
   else
    stMsgOp:=Format('Impossible de cr�er une �tape : il n''y en a d�j� %d !', [cv.NbEtapes]);
  end;
 RedessineCase(x, y, true);
 StatusBar.Panels.Items[0].Text:=stMsgOp;
 if ToolButtonMajVoie.Down then frmDefVoie.RafraichitInfos;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.DrawGridSimulDblClick(Sender: TObject);
const NumSvtOrdSel : array [0..1, 0..3] of Integer = ((0,0,1,0),(1,1,1,1));
var x, y, i, j, NbFeux,  // Variables de transition
     NbFeuxListe, // Nombre de feux de la liste frmDefFeux.NumFeux...
     NbFeuxVoie, // Nombre de feux dans la voie v[Col, Row]
     NbNonSel : Integer; // Compteur du nombre de feux non s�lectionn�s
    NumFeuVoie, // Num�ros de feux de la voie beginPrm,Drnend;
    Selection : array [0..1] of Integer; // 0:=Aucun;1:=Prm;2:=Drn;3:=Prm+Drn (Anc,Nv)
    NumFeu : array of Integer;
    v : pVoie;
begin
 x:=DrawGridSimul.Col;
 y:=DrawGridSimul.Row;
 NbFeuxVoie:=0;
 for i:=0 to 1 do
  begin
  NumFeuVoie[i]:=0;
  Selection[i]:=0;
  end;
 // Traite le clic sur la case avec des feux lors d'une s�lection de feux :
 // 2 feux := passage de aucun � feu1, de feu1 � feu2,
 //                  de feu2 � feu1+feu2 et de feu1+feu2 � aucun.
 // 1 feu := passage de aucun � feu1, de feu1 � aucun
 v:=@(cv.v[x, y]);

 if (v.NumEtape>0) and ToolButtonEtape.Enabled then
  begin
   ToolButtonEtape.Click;
   Exit;
  end;

 if not (SelectionFeuxDmd or SelectionFeuxAtt) then
  begin
   frmDefVoie.RafraichitInfos;
   if not ToolButtonMajVoie.Down and
          ToolButtonMajVoie.Enabled then
    frmDefVoie.Show();
   Exit;
  end;

 // Calcul du nombre et des num�ros de feux de la voie
 for i:=0 to 3 do
  if v.NumFeu[i]>0 then begin NumFeuVoie[NbFeuxVoie]:=v.NumFeu[i]; Inc(NbFeuxVoie); end;

 // Attention : les listes sont exclusives � la s�lection donc pas d'initialisation entre les 2

 // Calcul de la nouvelle liste NumFeuxDmd
 if SelectionFeuxDmd then
  begin
   NbFeuxListe:=frmDefFeux.NbFeuxDmd;
   // S�lection courante
   for i:=0 to NbFeuxListe-1 do
    for j:=0 to NbFeuxVoie-1 do
     if frmDefFeux.NumFeuxDmd[i]=NumFeuVoie[j] then
      Inc(Selection[0], j+1);

   // S�lection suivante selon la r�gle ci-dessus
   if NbFeuxVoie>0 then
    Selection[1]:=(Selection[0]+1) mod (2*NbFeuxVoie);

   // G�n�ration de la liste                                             Selection  Nombre
   NbFeux:=NbFeuxListe+(Selection[1]+1) div 2-(Selection[0]+1) div 2; // (0,1,2,3).(0,1,1,2) : f(s):=(s+1) div 2
   SetLength(NumFeu, NbFeux*sizeof(Integer));
   NbNonSel:=0;
   for i:=0 to NbFeuxListe-1 do // On recopie d�j� les feux de la pr�c�dente liste
    begin
     NumFeu[i-NbNonSel]:=frmDefFeux.NumFeuxDmd[i];
     for j:=0 to NbFeuxVoie-1 do
      Inc( NbNonSel,
           Ord( (frmDefFeux.NumFeuxDmd[i]=NumFeuVoie[j]) and
                (j and Selection[1]=0)));
    end;
   for i:=NbFeuxListe-NbNonSel to NbFeux-1 do // Cas de recopie d'une nouvelle s�lection
    NumFeu[i]:=NumFeuVoie[NumSvtOrdSel[i-NbFeuxListe+NbNonSel, Selection[1]]];

   // Changement de liste
   SetLength(frmDefFeux.NumFeuxDmd, NbFeux*sizeof(Integer));
   frmDefFeux.NbFeuxDmd:=NbFeux;
   for i:=0 to NbFeux-1 do frmDefFeux.NumFeuxDmd[i]:=NumFeu[i];
   frmDefFeux.RafraichitInfosFeuxDmd;
   RedessineCase(x, y, true);
  end;

 // Calcul de la nouvelle liste NumFeuxAtt
 if SelectionFeuxAtt then
  begin
   NbFeuxListe:=frmDefFeux.NbFeuxAtt;
   // S�lection courante
   for i:=0 to NbFeuxListe-1 do
    for j:=0 to NbFeuxVoie-1 do
     if frmDefFeux.NumFeuxAtt[i]=NumFeuVoie[j] then
      Inc(Selection[0], j+1);

   // S�lection suivante selon la r�gle ci-dessus
   if NbFeuxVoie>0 then
    Selection[1]:=(Selection[0]+1) mod (2*NbFeuxVoie);

   // G�n�ration de la liste                                             Selection  Nombre
   NbFeux:=NbFeuxListe+(Selection[1]+1) div 2-(Selection[0]+1) div 2; // (0,1,2,3).(0,1,1,2) : f(s):=(s+1) div 2
   SetLength(NumFeu, NbFeux*sizeof(Integer));
   NbNonSel:=0;
   for i:=0 to NbFeuxListe-1 do // On recopie d�j� les feux de la pr�c�dente liste
    begin
     NumFeu[i-NbNonSel]:=frmDefFeux.NumFeuxAtt[i];
     for j:=0 to NbFeuxVoie-1 do
      Inc( NbNonSel,
           Ord( (frmDefFeux.NumFeuxAtt[i]=NumFeuVoie[j]) and
                (j and Selection[1]=0)));
    end;
   for i:=NbFeuxListe-NbNonSel to NbFeux-1 do // Cas de recopie d'une nouvelle s�lection
    NumFeu[i]:=NumFeuVoie[NumSvtOrdSel[i-NbFeuxListe+NbNonSel, Selection[1]]];

   // Changement de liste
   SetLength(frmDefFeux.NumFeuxAtt, NbFeux*sizeof(Integer));
   frmDefFeux.NbFeuxAtt:=NbFeux;
   for i:=0 to NbFeux-1 do frmDefFeux.NumFeuxAtt[i]:=NumFeu[i];
   frmDefFeux.RafraichitInfosFeuxAtt;
   RedessineCase(x, y, true);
  end;
end;
//---------------------------------------------------------------------------
function TfrmSimulation.VerifieReseau : Boolean;
var Ok : Boolean;
    i, j : Integer;
    d : direction;
    stMsgErr : String;
    dp : dirposs;
const stMsgOk = 'R�seau correct.';
 begin
  Ok:=true;
  cv.VerifOk:=false;
  if (xErr>-1) and (yErr>-1) then RedessineCase(xErr, yErr, true);
  xErr:=-1; yErr:=-1;
  i:=0;
  while Ok and (i<cv.NbEtapes) do // v3.0
   begin
   Ok:=cv.Etapes[i].Definie;
   if not Ok then
    stMsgErr:=Format( 'L''�tape n�%d n''est pas d�finie. Les %d �tapes doivent �tre d�finies.',
                      [i+1, cv.NbEtapes]);
   Inc(i);
   end;
  i:=0;
  while Ok and (i<cv.NbArretsBus) do // v3.0
   begin
   Ok:=cv.ArretsBus[i].Defini;
   if not Ok then
    begin
    stMsgErr:=Format( 'L''arr�t de bus n�%d n''est pas d�fini. Les %d arr�ts de bus doivent �tre d�finis.',
                      [i+1, cv.NbArretsBus]);
    Break;
    end;
   Ok:=(cv.v[cv.ArretsBus[i].x, cv.ArretsBus[i].y].NumArretBus=i+1); // v3.0.3
   if not Ok then
    begin
    xErr:=cv.ArretsBus[i].x; yErr:=cv.ArretsBus[i].y;
    stMsgErr:=Format( 'La t�te de l''arr�t de bus n�%d n''est pas d�finie ou est incorrecte.',
                      [i+1]);
    Break;
    end;
   Inc(i);
   end;
  if Ok and (cv.NbArretsBus>0) and (cv.NbLignesBus>0) then // v3.0
   begin
   Ok:=cv.DepotBus.Defini;
   if not Ok then
    stMsgErr:='Si des arr�ts de bus et des lignes de bus sont d�finis, un d�p�t de bus est obligatoire.'
   else
    begin
    Ok:=(cv.v[cv.DepotBus.x, cv.DepotBus.y].DirPoss>aucune);
    if not Ok then
     begin
     xErr:=cv.DepotBus.x; yErr:=cv.DepotBus.y;
     stMsgErr:='Un d�p�t de bus doit avoir au moins une direction possible vers l''ext�rieur.';
     end;
    d:=nord;
    while Ok and (d<=ouest) do
     begin
     Ok:=(Integer(cv.vxyd(cv.DepotBus.x, cv.DepotBus.y, d).DirPoss) and Integer(InvPossDir[d])=0);
     if not Ok then
      begin
      xErr:=(cv.DepotBus.x+dx[d]) mod NBX; yErr:=(cv.DepotBus.y+dy[d]) mod NBY;
      stMsgErr:='On ne peut diriger une case vers le d�p�t de bus (il est en SORTIE SEULE).';
      end;
     Inc(d);
     end{while Ok};
    end{if not Ok else};
   end{if Ok and NbArretsBus and NbLignesBus};
  i:=0;
  while Ok and (i<NBX) do
   begin
   j:=0;
   while Ok and (j<NBY) do
    begin
     d:=nord;
     while Ok and (d<=ouest) do
      begin
      if (Integer(cv.v[i, j].DirPoss) and
          Integer(PossDir[d])) = Integer(PossDir[d]) then
       begin
        dp:=cv.vxyd(i,j,d).DirPoss;
        if dp=InvPossDir[d] then
         begin
          Ok:=false; xErr:=i; yErr:=j;
          stMsgErr:=Format('Demi-tour oblig� entre les cases (%d, %d) et (%d, %d).',
                          [i, j, (i+dx[d]) mod NBX, (j+dy[d]) mod NBY]);
          break;
         end;
        if dp=aucune then
         begin
          Ok:=false; xErr:=i; yErr:=j;
          stMsgErr:=Format('La case (%d, %d) pointe sur (%d, %d) qui n''a aucune direction possible.',
                           [i, j, (i+dx[d]) mod NBX, (j+dy[d]) mod NBY]);
          Break;
         end;
       end;
      d:=direction(Integer(d)+1);
      end{while d};
     if cv.v[i, j].NumEtape>0 then
      begin
       if cv.v[i, j].DirPoss=aucune then
        begin
         Ok:=false; xErr:=i; yErr:=j;
         stMsgErr:=Format('La case (%d, %d) est une �tape mais n''a aucune direction possible.',
                          [i, j]);
         Break;
        end;

       d:=nord;
       while (d<=ouest) and
             ((Integer(cv.vxyd(i,j,d).DirPoss) and
               Integer(InvPossDir[d]))=0) do d:=direction(Integer(d)+1);
       if d>ouest then
        begin
         Ok:=false; xErr:=i; yErr:=j;
         stMsgErr:=Format('La case (%d, %d) est une �tape mais il est impossible d''y acc�der.',
                          [i, j]);
         Break;
        end;
      end{if NumEtape};
     if cv.v[i,j].NumArretBus>0 then // v3.0
      begin
      d:=nord; Ok:=false;
      while not Ok and (d<=ouest) do
       begin
       Ok:=(cv.vxyd(i,j,d).NumArretBus=cv.v[i,j].NumArretBus);
       Inc(d);
       end;
      if not Ok then
       begin
       xErr:=i; yErr:=j;
       stMsgErr:=Format( 'L''arr�t de bus n�%d n''est d�fini que sur la case (%d, %d).',
                         [cv.v[i,j].NumArretBus, i, j]);
       Break;
       end{if not Ok};
      end{if NumArretBus};
     Inc(j);
    end{while j};
   Inc(i);
   end{while i};
  cv.VerifOk:=Ok;
  if Ok then
   StatusBar.Panels.Items[0].Text:=stMsgOk
  else
   StatusBar.Panels.Items[0].Text:=stMsgErr;
  if (xErr>-1) and (yErr>-1) then RedessineCase(xErr, yErr, true);
  Cursor:=crDefault;
  Result:=Ok;
 end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.AfficheMsgInfoNonDisp(stTitre : String);
 begin
  Application.MessageBox('Aucune information n''est disponible.', stTitre, [smbOk], smsWarning);
 end;
//---------------------------------------------------------------------------
function TfrmSimulation.SimulEstEnCours : Boolean;
 begin
  Result:=SimulEnCours;
 end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.AfficheBilan;
var i, j, d, ndp, MinDist,
    xe, ye,
    ne, nv,
    nva, // NbVehiculesArriv�s
    nvpe, // NbVehiculesParEtape
    ParcoursMin,
    AttenteDepart,
    ntp, ncp : Integer;
    m : Double;
    stMsgBilan : String;

 begin
  ne:=cv.NbEtapes; // NbEtapes
  nv:=cv.NbVehicules; // NbVehicules
  nva:=cv.NbVehiculesArrives; // NbVehiculesArriv�s
  nvpe:=nv div ne; // NbVehiculesParEtape
  ParcoursMin:=0;
  AttenteDepart:=0;
  ntp:=cv.NbToursParcourus;
  ncp:=cv.NbCasesParcourues;
  // 1. On calcule le parcours moyen
  for i:=0 to ne-1 do
   for j:=0 to ne-1 do
    if i<>j then
     begin
      xe:=cv.Etapes[i].x; ye:=cv.Etapes[i].y;
      MinDist:=DIST_INDEFINIE;
      ndp:=NbDir[cv.v[xe, ye].DirPoss];
      for d:=0 to ndp-1 do
       MinDist:=min(MinDist, cv.v[xe, ye].DistEtape[j, d]);
      Inc(ParcoursMin, MinDist);
     end;
  m:=(1.0*ParcoursMin)/ne/(ne-1);
  // 2. Calcul du temps d'attente de d�part
  for i:=0 to nv-1 do
   if not cv.Vehicules[i].Defini then
    Inc(AttenteDepart, cv.Vehicules[i].TourDepart-1);
  // 3. Affichage du bilan
  if nva>0 then
   stMsgBilan:= stFormatBilan[0]+
                Format(stFormatBilan[1], [nv])+
                Format(stFormatBilan[2], [m])+
                Format(stFormatBilan[3], [m])+
                Format(stFormatBilan[4], [nvpe-3])+
                Format(stFormatBilan[5], [cv.TourCrt])+
                Format(stFormatBilan[6], [nva, (100.0*nva)/nv])+
                Format(stFormatBilan[7], [(1.0*ncp)/nva, (100.0*ncp)/nva/m])+
                Format(stFormatBilan[8], [(1.0*AttenteDepart)/nva,
                                          (100.0*AttenteDepart)/nva/(nvpe-3)])+
                Format(stFormatBilan[9], [(1.0*ntp)/nva,
                                          (100.0*ntp)/nva/m])+
                Format(stFormatBilan[10], [(1.0*ncp)/nva,
                                           (100.0*ncp)/ntp])+
                Format(stFormatBilan[11], [(1.0*(ntp-ncp))/nva,
                                           (100.0*(ntp-ncp))/ntp])+
                stFormatBilan[12]
  else
   stMsgBilan:= stFormatBilanSansArrives[0]+
                Format(stFormatBilanSansArrives[1], [nv])+
                Format(stFormatBilanSansArrives[2], [m])+
                Format(stFormatBilanSansArrives[3], [m])+
                Format(stFormatBilanSansArrives[4], [nvpe-3])+
                Format(stFormatBilanSansArrives[5], [cv.TourCrt])+
                stFormatBilanSansArrives[6]+
                stFormatBilanSansArrives[7];
  if Application.MessageBox(stMsgBilan, 'Bilan', [smbYes, smbNo], smsInformation, smbYes)=smbYes then
   AfficheStatsAttenteTrafic;
 end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonMajVoieClick(Sender: TObject);
begin
 frmDefVoie.Visible:=ToolButtonMajVoie.Down;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.DrawGridSimulClick(Sender: TObject);
begin
 if frmDefVoie.Visible and
    not (SelectionFeuxDmd or SelectionFeuxAtt) then
  frmDefVoie.RafraichitInfos;
 if frmInfosVehicule.Visible then frmInfosVehicule.RafraichitInfos;
 if frmInfosBus.Visible then frmInfosBus.RafraichitInfos; // v3.0
 if frmInfosPieton.Visible then frmInfosPieton.RafraichitInfos; // v3.0
 if frmAffDistEtapes.Visible and
    not (SelectionFeuxDmd or SelectionFeuxAtt) then
  begin
   frmAffDistEtapes.EffaceInfos;
   frmAffDistEtapes.RafraichitInfos;
  end;
 if frmAffDistArretsBus.Visible and
    not (SelectionFeuxDmd or SelectionFeuxAtt) then // v3.0
  begin
  frmAffDistArretsBus.EffaceInfos;
  frmAffDistArretsBus.RafraichitInfos;
  end;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonAffDistEtapesClick(Sender: TObject);
begin // v3.0. changement de nom suite aux distances aux arr�ts de bus
 frmAffDistEtapes.Visible:=ToolButtonAffDistEtapes.Down;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonVerifClick(Sender: TObject);
begin
 VerifieReseau;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonPauseClick(Sender: TObject);
begin
 TypeDemande:=pause;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonArretClick(Sender: TObject);
begin
 TypeDemande:=arret;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonAffStatsEvolClick(Sender: TObject);
begin
 frmStatistiques.Visible:=ToolButtonAffStatsEvol.Down;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueQuadrillageStatistiquesClick(
  Sender: TObject);
begin
 RubriqueQuadrillageStatistiques.Checked:=RubriqueQuadrillageStatistiques.Checked xor true;
 cv.QuadrillageStats:=RubriqueQuadrillageStatistiques.Checked;
 if frmStatistiques.Visible then frmStatistiques.PaintBoxStats.Repaint;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueDrnToursClick(Sender: TObject);
begin
 (Sender as TMenuItem).Checked:=true;
 cv.NbToursStats:=(Sender as TMenuItem).Tag;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueParVehPourcentClick(Sender: TObject);
begin
 (Sender as TMenuItem).Checked:=true;
 cv.TypeStats:=type_stats((Sender as TMenuItem).Tag);
 if frmStatistiques.Visible then frmStatistiques.PaintBoxStats.Repaint;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonAffStatsEtapesClick(
  Sender: TObject);
begin
  if ToolButtonAffStatsEtapes.Down and (cv.NbVehiculesArrives=0) then
   begin
    AfficheMsgInfoNonDisp('Statistiques sur les v�hicules');
    ToolButtonAffStatsEtapes.Down:=false;
    RubriqueStatistiquesEtapes.Checked:=false;
   end{ // A DEFINIR
 else
  frmStatsVehicules.Visible:=ToolButtonAffStatsEtapes.Down};
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonParametresClick(Sender: TObject);
begin
 Parametres;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonInfosVehiculeClick(Sender: TObject);
begin
 frmInfosVehicule.Visible:=ToolButtonInfosVehicule.Down;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonRechercheClick(Sender: TObject);
begin
 frmRecherche.Visible:=ToolButtonRecherche.Down;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueParametresClick(Sender: TObject);
begin
 ToolButtonParametres.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueRechercheClick(Sender: TObject);
begin
 ToolButtonRecherche.Down:=ToolButtonRecherche.Down xor true;
 ToolButtonRecherche.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueDirectionsClick(Sender: TObject);
begin
 ToolButtonAffDir.Down:=ToolButtonAffDir.Down xor true;
 ToolButtonAffDir.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueSignalisationClick(Sender: TObject);
begin
 ToolButtonAffSign.Down:=ToolButtonAffSign.Down xor true;
 ToolButtonAffSign.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueRoutesClick(Sender: TObject);
begin
 ToolButtonAffRoutes.Down:=ToolButtonAffRoutes.Down xor true;
 ToolButtonAffRoutes.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueVehiculesClick(Sender: TObject);
begin
 ToolButtonAffVeh.Down:=ToolButtonAffVeh.Down xor true;
 ToolButtonAffVeh.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriquePietonsClick(Sender: TObject);
begin
 ToolButtonAffPtn.Down:=ToolButtonAffPtn.Down xor true;
 ToolButtonAffPtn.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueQuadrillageClick(Sender: TObject);
begin
 ToolButtonAffQuadr.Down:=ToolButtonAffQuadr.Down xor true;
 ToolButtonAffQuadr.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueMarcheClick(Sender: TObject);
begin
 ToolButtonMarche.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueInterruptionClick(Sender: TObject);
begin
 ToolButtonPause.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueArretClick(Sender: TObject);
begin
 ToolButtonArret.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueVerificationReseauClick(Sender: TObject);
begin
 ToolButtonVerif.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueStatistiquesEvolutionClick(
  Sender: TObject);
begin
 ToolButtonAffStatsEvol.Down:=ToolButtonAffStatsEvol.Down xor true;
 ToolButtonAffStatsEvol.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueStatistiquesEtapesClick(Sender: TObject);
begin
 ToolButtonAffStatsEtapes.Down:=ToolButtonAffStatsEtapes.Down xor true;
 ToolButtonAffStatsEtapes.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueDirectionHautClick(Sender: TObject);
begin
 ToolButtonNord.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueDirectionDroiteClick(Sender: TObject);
begin
 ToolButtonEst.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueDirectionBasClick(Sender: TObject);
begin
 ToolButtonSud.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueDirectionGaucheClick(Sender: TObject);
begin
 ToolButtonOuest.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueEtapeClick(Sender: TObject);
begin
 ToolButtonEtape.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriquePrioritesClick(Sender: TObject);
begin
 ToolButtonMajVoie.Down:=ToolButtonMajVoie.Down xor true;
 ToolButtonMajVoie.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueInfosVehiculeClick(Sender: TObject);
begin
 ToolButtonInfosVehicule.Down:=ToolButtonInfosVehicule.Down xor true;
 ToolButtonInfosVehicule.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueInfosDistancesEtapesClick(Sender: TObject);
begin
 ToolButtonAffDistEtapes.Down:=ToolButtonAffDistEtapes.Down xor true;
 ToolButtonAffDistEtapes.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonToutDroitClick(Sender: TObject);
var x, y : Integer;
begin
 x:=DrawGridSimul.Col;
 y:=DrawGridSimul.Row;
 cv.v[x, y].ToutDroit:=cv.v[x, y].ToutDroit xor true;
 SimulModifiee:=true;
 RedessineCase(x, y, true);
 if ToolButtonMajVoie.Down then frmDefVoie.RafraichitInfos;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueToutDroitClick(Sender: TObject);
begin
 ToolButtonToutDroit.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueVerifierIntegriteApresOuvertureClick(
  Sender: TObject);
begin
 RubriqueVerifierIntegriteApresOuverture.Checked:=RubriqueVerifierIntegriteApresOuverture.Checked xor true;
 VerifierApresOuverture:=RubriqueVerifierIntegriteApresOuverture.Checked;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueVerifierIntegriteAvantSimulationClick(
  Sender: TObject);
begin
 RubriqueVerifierIntegriteAvantSimulation.Checked:=RubriqueVerifierIntegriteAvantSimulation.Checked xor true;
 VerifierAvantSimulation:=RubriqueVerifierIntegriteAvantSimulation.Checked;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueSuivreCeVehiculeClick(Sender: TObject);
var NumVehicule : Integer;
begin
 NumVehicule:=cv.v[DrawGridSimul.Col, DrawGridSimul.Row].NumVehicule;
 if NumVehicule=0 then Exit;
 if not ToolButtonRecherche.Down then
  begin
   ToolButtonRecherche.Down:=ToolButtonRecherche.Down xor true;
   ToolButtonRecherche.Click;
  end;
 frmRecherche.RadioButtonVehicule.Checked:=true;
 frmRecherche.SpinEditVehicule.Value:=NumVehicule;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueEffacerClick(Sender: TObject);
begin
 SupprimeToutDansSelection;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.FormCloseQuery(Sender: TObject;
  var CanClose: Boolean);
begin
 CanClose:=EnregistreModificationsAvant(oaQuitter);
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriquePassagePietonsClick(Sender: TObject);
begin
 ToolButtonPassagePietons.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonPassagePietonsClick(Sender: TObject);
var x, y : Integer;
begin
 x:=DrawGridSimul.Col;
 y:=DrawGridSimul.Row;
 cv.v[x, y].PassagePietons:=cv.v[x, y].PassagePietons xor true;
 SimulModifiee:=true;
 RedessineCase(x, y, true);
 if ToolButtonMajVoie.Down then frmDefVoie.RafraichitInfos;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonCompositionClick(Sender: TObject);
begin
 frmStatsComposition:=TfrmStatsComposition.Create(Application);
  try
   frmStatsComposition.ShowModal;
  finally
    frmStatsComposition.Release;
    frmStatsComposition:=nil;
  end;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueCompositionReseauClick(Sender: TObject);
begin
 ToolButtonComposition.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueRouteClick(Sender: TObject);
var  i,
     Gauche,
     Droite,
     Haut,
     Bas,
     x0, x1, y0, y1,
     dx,
     dy,
     xd,
     yd,
     xf,
     yf : Integer;

begin
 Gauche:=DrawGridSimul.Selection.Left;
 Droite:=DrawGridSimul.Selection.Right;
 Haut:=DrawGridSimul.Selection.Top;
 Bas:=DrawGridSimul.Selection.Bottom;
 dx:=abs(Droite-Gauche);
 dy:=abs(Bas-Haut);
 xd:=DrawGridSimul.Col;
 yd:=DrawGridSimul.Row;
 if xd=Gauche then xf:=Droite else xf:=Gauche;
 if yd=Haut then yf:=Bas else yf:=Haut;
 x0:=0; y0:=0; x1:=0; y1:=0; // Evite l'avertissement 'Might not have been initialized' 
 if (dx>1) and (dy>1) then
  begin
   Application.MessageBox(stTracerEffacerRoute, stSelectionIncorrecte,
                          [smbOk], smsWarning);
   Exit;
  end;
 if dx=dy then
  begin
   Application.MessageBox(stNombreLignesColonnesDifferent, stSelectionIncorrecte,
                          [smbOk], smsWarning);
   Exit;
  end;

 SimulModifiee:=true;
 if dx<2 then
  begin
   SimulModifiee:=true;
   i:=yd;
   while i<>yf do
    begin
     if yd<yf then
      begin
      x0:=Gauche;
      cv.ChangeDirectionSiPossible(x0, i, S);
      if dx=1 then
       begin
       x1:=Droite;
       if i=yd then
        cv.ChangeDirectionSiPossible(x1, yf, N)
       else
        cv.ChangeDirectionSiPossible(x1, i, N);
       end;
      end
     else
      begin
      x0:=Droite;
      cv.ChangeDirectionSiPossible(x0, i, N);
      if dx=1 then
       begin
       x1:=Gauche;
       if i=yd then
        cv.ChangeDirectionSiPossible(x1, yf, S)
       else
        cv.ChangeDirectionSiPossible(x1, i, S);
       end;
      end;
    Inc(i, (yf-yd) div abs(yf-yd));
    end{while i=yf};
   RedessineCase(x0, yf, true);
   RedessineCase(x1, yd, true);
   Exit;
  end;

 if dy<2 then
  begin
   i:=xd;
   while i<>xf do
    begin
     if xd<xf then
      begin
      y0:=Bas;
      cv.ChangeDirectionSiPossible(i, y0, E);
      if dy=1 then
       begin
       y1:=Haut;
       if i=xd then
        cv.ChangeDirectionSiPossible(xf, y1, O)
       else
        cv.ChangeDirectionSiPossible(i, y1, O);
       end;
      end
     else
      begin
      y0:=Haut;
      cv.ChangeDirectionSiPossible(i, y0, O);
      if dy=1 then
       begin
       y1:=Bas;
       if i=xd then
        cv.ChangeDirectionSiPossible(xf, y1, E)
       else
        cv.ChangeDirectionSiPossible(i, y1, E);
       end;
      end;
    Inc(i, (xf-xd) div abs(xf-xd));
    end{while i=xf};
   RedessineCase(xf, y0, true);
   RedessineCase(xd, y1, true);
   Exit;
  end;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueBordSuperieurDroitClick(Sender: TObject);
var  i,
     Gauche, Droite, Haut, Bas,
     xd, yd, xf, yf : Integer;
begin
 Gauche:=DrawGridSimul.Selection.Left;
 Droite:=DrawGridSimul.Selection.Right;
 Haut:=DrawGridSimul.Selection.Top;
 Bas:=DrawGridSimul.Selection.Bottom;
 xd:=DrawGridSimul.Col;
 yd:=DrawGridSimul.Row;
 if xd=Gauche then xf:=Droite else xf:=Gauche;
 if yd=Haut then yf:=Bas else yf:=Haut;
 SimulModifiee:=true;
 i:=yd;
 while i<>yf do
  begin
  if yd<yf then
   cv.ChangeDirectionSiPossible(Droite, i, S)
  else
   cv.ChangeDirectionSiPossible(Droite, i, N);
  Inc(i, (yf-yd) div abs(yf-yd));
  end;
 RedessineCase(Droite, yf, true);
 i:=xd;
 while i<>xf do
  begin
  if xd<xf then
   cv.ChangeDirectionSiPossible(i, Haut, E)
  else
   cv.ChangeDirectionSiPossible(i, Haut, O);
  Inc(i, (xf-xd) div abs(xf-xd));
  end;
 RedessineCase(xf, Haut, true);
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueBordInferieurGaucheClick(Sender: TObject);
var  i,
     Gauche, Droite, Haut, Bas,
     xd, yd, xf, yf : Integer;
begin
 Gauche:=DrawGridSimul.Selection.Left;
 Droite:=DrawGridSimul.Selection.Right;
 Haut:=DrawGridSimul.Selection.Top;
 Bas:=DrawGridSimul.Selection.Bottom;
 xd:=DrawGridSimul.Col;
 yd:=DrawGridSimul.Row;
 if xd=Gauche then xf:=Droite else xf:=Gauche;
 if yd=Haut then yf:=Bas else yf:=Haut;
 SimulModifiee:=true;
 i:=yd;
 while i<>yf do
  begin
  if yd<yf then
   cv.ChangeDirectionSiPossible(Gauche, i, S)
  else
   cv.ChangeDirectionSiPossible(Gauche, i, N);
  Inc(i, (yf-yd) div abs(yf-yd));
  end;
 RedessineCase(Gauche, yf, true);
 i:=xd;
 while i<>xf do
  begin
  if xd<xf then
   cv.ChangeDirectionSiPossible(i, Bas, E)
  else
   cv.ChangeDirectionSiPossible(i, Bas, O);
  Inc(i, (xf-xd) div abs(xf-xd));
  end;
 RedessineCase(xf, Bas, true);
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueBordSuperieurGaucheClick(Sender: TObject);
var  i,
     Gauche, Droite, Haut, Bas,
     xd, yd, xf, yf : Integer;
begin
 Gauche:=DrawGridSimul.Selection.Left;
 Droite:=DrawGridSimul.Selection.Right;
 Haut:=DrawGridSimul.Selection.Top;
 Bas:=DrawGridSimul.Selection.Bottom;
 xd:=DrawGridSimul.Col;
 yd:=DrawGridSimul.Row;
 if xd=Gauche then xf:=Droite else xf:=Gauche;
 if yd=Haut then yf:=Bas else yf:=Haut;
 SimulModifiee:=true;
 i:=yd;
 while i<>yf do
  begin
  if yd<yf then
   cv.ChangeDirectionSiPossible(Gauche, i, S)
  else
   cv.ChangeDirectionSiPossible(Gauche, i, N);
  Inc(i, (yf-yd) div abs(yf-yd));
  end;
 RedessineCase(Gauche, yf, true);
 i:=xd;
 while i<>xf do
  begin
  if xd<xf then
   cv.ChangeDirectionSiPossible(i, Haut, E)
  else
   cv.ChangeDirectionSiPossible(i, Haut, O);
  Inc(i, (xf-xd) div abs(xf-xd));
  end;
 RedessineCase(xf, Haut, true);
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueBordInferieurDroitClick(Sender: TObject);
var  i,
     Gauche, Droite, Haut, Bas,
     xd, yd, xf, yf : Integer;
begin
 Gauche:=DrawGridSimul.Selection.Left;
 Droite:=DrawGridSimul.Selection.Right;
 Haut:=DrawGridSimul.Selection.Top;
 Bas:=DrawGridSimul.Selection.Bottom;
 xd:=DrawGridSimul.Col;
 yd:=DrawGridSimul.Row;
 if xd=Gauche then xf:=Droite else xf:=Gauche;
 if yd=Haut then yf:=Bas else yf:=Haut;
 SimulModifiee:=true;
 i:=yd;
 while i<>yf do
  begin
  if yd<yf then
   cv.ChangeDirectionSiPossible(Droite, i, S)
  else
   cv.ChangeDirectionSiPossible(Droite, i, N);
  Inc(i, (yf-yd) div abs(yf-yd));
  end;
 RedessineCase(Droite, yf, true);
 i:=xd;
 while i<>xf do
  begin
  if xd<xf then
   cv.ChangeDirectionSiPossible(i, Bas, E)
  else
   cv.ChangeDirectionSiPossible(i, Bas, O);
  Inc(i, (xf-xd) div abs(xf-xd));
  end;
 RedessineCase(xf, Bas, true);
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriquePeripheriqueExterieurClick(
  Sender: TObject);
var  i,
     Gauche, Droite,
     Haut, Bas : Integer;
begin
 Gauche:=DrawGridSimul.Selection.Left;
 Droite:=DrawGridSimul.Selection.Right;
 Haut:=DrawGridSimul.Selection.Top;
 Bas:=DrawGridSimul.Selection.Bottom;
 if (Gauche=Droite) or (Bas=Haut) then
  begin
   Application.MessageBox(stTracerEffacerPeripherique,
                          stSelectionIncorrecte,
                          [smbOk], smsWarning);
   Exit;
  end;

 SimulModifiee:=true;
 for i:=Gauche to Droite-1 do cv.ChangeDirectionSiPossible(i, Bas, E);
 for i:=Bas downto Haut+1 do cv.ChangeDirectionSiPossible(Droite, i, N);
 for i:=Droite downto Gauche+1 do cv.ChangeDirectionSiPossible(i, Haut, O);
 for i:=Haut to Bas-1 do cv.ChangeDirectionSiPossible(Gauche, i, S);
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriquePeripheriqueInferieurClick(
  Sender: TObject);
var  i,
     Gauche, Droite,
     Haut, Bas : Integer;
begin
 Gauche:=DrawGridSimul.Selection.Left;
 Droite:=DrawGridSimul.Selection.Right;
 Haut:=DrawGridSimul.Selection.Top;
 Bas:=DrawGridSimul.Selection.Bottom;
 if (Gauche=Droite) or (Bas=Haut) then
  begin
   Application.MessageBox(stTracerEffacerPeripherique,
                           stSelectionIncorrecte,
                           [smbOk], smsWarning);
   Exit;
  end;

 SimulModifiee:=true;
 for i:=Gauche to Droite-1 do cv.ChangeDirectionSiPossible(i, Haut, E);
 for i:=Haut to Bas-1 do cv.ChangeDirectionSiPossible(Droite, i, S);
 for i:=Droite downto Gauche+1 do cv.ChangeDirectionSiPossible(i, Bas, O);
 for i:=Bas downto Haut+1 do cv.ChangeDirectionSiPossible(Gauche, i, N);
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueCarrefoursClick(Sender: TObject);
begin
 Carrefours( DrawGridSimul.Selection.Right-DrawGridSimul.Selection.Left+1,
             DrawGridSimul.Selection.Bottom-DrawGridSimul.Selection.Top+1);
end;
//---------------------------------------------------------------------------
function TfrmSimulation.ConfirmeSuppressionFeuxUtilisesDansSelection : Boolean;
var Abandon,
    ToutSupprimer : Boolean;
    i, j, d, x, y, NumFeu,
    xd, yd, xf, yf : Integer;
 begin
  Abandon:=false;
  ToutSupprimer:=true;
  xd:=DrawGridSimul.Selection.Left;
  yd:=DrawGridSimul.Selection.Top;
  xf:=DrawGridSimul.Selection.Right;
  yf:=DrawGridSimul.Selection.Bottom;
  x:=xd; 
  while not Abandon and (x<=xf) do
   begin
   y:=yd;
   while not Abandon and (y<=yf) do
    begin
    d:=0;
    while not Abandon and (d<NBDIRS) do
     begin
     NumFeu:=cv.v[x, y].NumFeu[d];
     if NumFeu>0 then
      begin
      i:=0;
      while not Abandon and (i<cv.NbFeux) do
       begin
       j:=0;
       while not Abandon and (j<cv.Feux[i].NbFeuxDmd) do
        begin
        if cv.Feux[i].NumFeuxDmd[j]=NumFeu then
         case MessageDlg( Format( 'Le feu n�%d d�pend du feu n�%d (� supprimer) :'#13#10+
                                  'Ce dernier demande que le premier soit rouge pour passer au vert.'#13#10#13#10+
                                  'Le feu n�%d sera-t-il � supprimer ?',
                                  [i+1, NumFeu, NumFeu]),
                            mtConfirmation,
                            [mbYes, mbNo, mbIgnore], 0, mbNo) of
           mrIgnore:   begin
                       ToutSupprimer:=true;
                       Abandon:=true;
                       end;
           mrNo:       begin
                       ToutSupprimer:=false;
                       Abandon:=true;
                       end;
         end{case of};
        Inc(j);
        end{while j};
       j:=0;
       while not Abandon and (j<cv.Feux[i].NbFeuxAtt) do
        begin
        if cv.Feux[i].NumFeuxAtt[j]=NumFeu then
         case MessageDlg( Format( 'Le feu n�%d d�pend du feu n�%d (� supprimer) :'#13#10+
                                  'Ce dernier doit �tre rouge pour que le premier passe au vert.'#13#10#13#10+
                                  'Le feu n�%d sera-t-il � supprimer ?',
                                  [i+1, NumFeu, NumFeu]),
                          mtConfirmation,
                          [mbYes, mbNo, mbIgnore], 0, mbNo) of
           mrIgnore:   begin
                       ToutSupprimer:=true;
                       Abandon:=true;
                       end;
           mrNo:       begin
                       ToutSupprimer:=false;
                       Abandon:=true;
                       end;
         end{case of};
        Inc(j);
        end{while j};
       Inc(i);
       end{while i};
      end{if NumFeu>0};
     Inc(d);
     end{while d};
    Inc(y);
    end{while y};
   Inc(x);
   end{while x};
  Result:=ToutSupprimer;
 end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.SupprimeFeuxUtilisesDansSelection;
var i, j, d, x, y, NumFeu,
    xd, yd, xf, yf : Integer;
 begin
 xd:=DrawGridSimul.Selection.Left;
 yd:=DrawGridSimul.Selection.Top;
 xf:=DrawGridSimul.Selection.Right;
 yf:=DrawGridSimul.Selection.Bottom;
  for x:=xd to xf do
   for y:=yd to yf do
    for d:=0 to NBDIRS-1 do
     begin
     NumFeu:=cv.v[x, y].NumFeu[d];
     for i:=0 to cv.NbFeux-1 do
      begin
      for j:=0 to cv.Feux[i].NbFeuxDmd-1 do
       if cv.Feux[i].NumFeuxDmd[j]=NumFeu then
        cv.Feux[i].RetireFeuDmd(NumFeu);
      for j:=0 to cv.Feux[i].NbFeuxAtt-1 do
       if cv.Feux[i].NumFeuxAtt[j]=NumFeu then
        cv.Feux[i].RetireFeuAtt(NumFeu);
      end;
     end;
 end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ReinitialiseToutDansSelection;
var x, y,
    xd, yd, xf, yf : Integer;
 begin
  xd:=DrawGridSimul.Selection.Left;
  yd:=DrawGridSimul.Selection.Top;
  xf:=DrawGridSimul.Selection.Right;
  yf:=DrawGridSimul.Selection.Bottom;
  for x:=xd to xf do
   for y:=yd to yf do
    begin
     cv.SupprimeFeuxVoie(x,y);
     cv.v[x, y].Initialise;
     RedessineCase(x,y,true);
     if y=yd then RedessineCase((x+dx[nord]) mod NBX, (y+dy[nord]) mod NBY, true);
     if x=xf then RedessineCase((x+dx[est]) mod NBX, (y+dy[est]) mod NBY, true);
     if y=yf then RedessineCase((x+dx[sud]) mod NBX, (y+dy[sud]) mod NBY, true);
     if x=xd then RedessineCase((x+dx[ouest]) mod NBX, (y+dy[ouest]) mod NBY, true);
    end;
 end;
//---------------------------------------------------------------------------
function TfrmSimulation.SupprimeToutDansSelection : Boolean;
 begin
  if (Application.MessageBox( '�tes-vous bien s�r de vouloir effacer les routes, supprimer les priorit�s, feux et �tapes dans la zone s�lectionn�e ?',
                              'Confirmation d''effacement',
                              [smbYes, smbNo], smsWarning,  smbNo)=smbYes) and
     ConfirmeSuppressionFeuxUtilisesDansSelection then
   begin
    SimulModifiee:=true;
    SupprimeFeuxUtilisesDansSelection;
    ReinitialiseToutDansSelection;
    Result:=true;
   end
  else
   Result:=false;
 end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueDeplacerFeuClick(Sender: TObject);
var d : direction;
    i, xCrt, yCrt : Integer;
    vSrc, vDst : pVoie ;
    FeuADeplacer : pFeu;
begin
 xCrt:=DrawGridSimul.Col;
 yCrt:=DrawGridSimul.Row;
 DeplacementFeuEnCours:=DeplacementFeuEnCours xor true;
 RubriqueDeplacerFeu.Caption:=stRubriqueDeplacerFeu[Ord(DeplacementFeuEnCours)];
 if DeplacementFeuEnCours then
  begin
   xDeplFeu:=DrawGridSimul.Col;
   yDeplFeu:=DrawGridSimul.Row;
   vSrc:=@(cv.v[xDeplFeu, yDeplFeu]);
   if (vSrc.Priorites[0]<>feux) and
      (vSrc.Priorites[1]<>feux) and
      (vSrc.Priorites[2]<>feux) and
      (vSrc.Priorites[3]<>feux) then
    begin
     Application.MessageBox('Il n''y a aucun feu sur cette case not ', 'D�placement de feu impossible', [smbOk], smsWarning);
     DeplacementFeuEnCours:=false;
     RubriqueDeplacerFeu.Caption:=stRubriqueDeplacerFeu[0];
     xDeplFeu:=-1; yDeplFeu:=-1;
     Exit;
    end;
  end
 else
  if (xCrt<>xDeplFeu) or
     (yCrt<>yDeplFeu) then
   begin
    vSrc:=@(cv.v[xDeplFeu, yDeplFeu]);
    vDst:=@(cv.v[xCrt, yCrt]);
    for i:=0 to 3 do
     begin
     d:=direction(i+1); // Permet de remplacer les direction(i+1)
      if vSrc.Priorites[i]=feux then
       begin
        if vDst.Priorites[i]=feux then
         Application.MessageBox('Vous ne pouvez pas i+1�placer un feu sur une case o� un feu de m�me orientation existe d�j�.', 'D�placement de feu impossible', [smbOk], smsWarning)
        else
         if (Integer(vDst.DirPoss) and Integer(PossDir[d]))=0 then
          Application.MessageBox('Vous ne pouvez pas d�placer un feu sur une case qui n''a pas la m�me direction.', 'D�placement de feu impossible', [smbOk], smsWarning)
         else
          begin
           FeuADeplacer:=@(cv.Feux[vSrc.NumFeu[i]-1]);
           vDst.Priorites[i]:=feux;
           vDst.NumFeu[i]:=vSrc.NumFeu[i];
           vSrc.Priorites[i]:=a_droite;
           FeuADeplacer.x:=xCrt;
           FeuADeplacer.y:=yCrt;
           SimulModifiee:=true;
           RedessineCase(xDeplFeu, yDeplFeu, true);
           RedessineCase(xCrt, yCrt, true);
           if ToolButtonMajVoie.Down then frmDefVoie.RafraichitInfos;
          end;
       end;
     end;
    xDeplFeu:=-1; yDeplFeu:=-1;
   end;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.MarcheArretSimul(EnCours : Boolean);
 begin
  SimulEnCours:=EnCours;
  if not EnCours then Application.Title:=stTitreCV;

  if (cv.TourCrt=0) and not EnCours then
   begin
    DrawGridSimul.Options:=DrawGridSimul.Options+[goRangeSelect];
    DrawGridSimul.PopupMenu:=PopupMenuEdition;
   end
  else
   begin
    DrawGridSimul.Options:=DrawGridSimul.Options-[goRangeSelect];
    DrawGridSimul.PopupMenu:=PopupMenuSimulation;
   end;

  ToolButtonNord.Enabled:=(cv.TourCrt=0) and not EnCours;
  ToolButtonEst.Enabled:=(cv.TourCrt=0) and not EnCours;
  ToolButtonSud.Enabled:=(cv.TourCrt=0) and not EnCours;
  ToolButtonOuest.Enabled:=(cv.TourCrt=0) and not EnCours;
  ToolButtonToutDroit.Enabled:=(cv.TourCrt=0) and not EnCours;
  ToolButtonEtape.Enabled:=(cv.TourCrt=0) and not EnCours;
  ToolButtonDepotBus.Enabled:=(cv.TourCrt=0) and not EnCours; // v3.0
  ToolButtonMajVoie.Enabled:=(cv.TourCrt=0) and not EnCours;
  ToolButtonVerif.Enabled:=(cv.TourCrt=0) and not EnCours;
  ToolButtonAffStatsEvol.Enabled:=(cv.TourCrt>0) or EnCours;
  ToolButtonAffStatsEtapes.Enabled:=(cv.TourCrt>0) or EnCours;

  ToolButtonMarche.Enabled:=not EnCours;
  ToolButtonPause.Enabled:=EnCours;

  if not EnCours then RubriqueSuivreCeVehicule.Enabled:=false;
  if not EnCours then RubriqueSuivreCeBus.Enabled:=false; // v3.0
  if not EnCours then RubriqueSuivreLe1erPieton.Enabled:=false; // v3.0
  if not EnCours then RubriqueSuivreLe2emePieton.Enabled:=false; // v3.0
  RubriqueVerificationReseau.Enabled:=ToolButtonVerif.Enabled;
  RubriqueStatistiquesEvolution.Enabled:=ToolButtonAffStatsEvol.Enabled;
  RubriqueStatistiquesEtapes.Enabled:=ToolButtonAffStatsEtapes.Enabled;
  RubriqueMarche.Enabled:=ToolButtonMarche.Enabled;
  RubriqueInterruption.Enabled:=ToolButtonPause.Enabled;

  RubriqueNouveau.Enabled:=not SimulEnCours;
  RubriqueOuvrir.Enabled:=not SimulEnCours;
  RubriqueEnregistrer.Enabled:=not SimulEnCours;
  RubriqueEnregistrerSous.Enabled:=not SimulEnCours;
  Rubrique10DrnTours.Enabled:=not SimulEnCours;
  Rubrique20DrnTours.Enabled:=not SimulEnCours;
  Rubrique50DrnTours.Enabled:=not SimulEnCours;
  Rubrique100DrnTours.Enabled:=not SimulEnCours;
  Rubrique200DrnTours.Enabled:=not SimulEnCours;
  Rubrique500DrnTours.Enabled:=not SimulEnCours;

  if SimulEnCours then
   begin
    TypeDemande:=rien;
    TimerSimul.Interval:=Round(1000.0/(cv.NbToursParSeconde));
    TimerSimul.Enabled:=true;
   end;
  DeplacementFeuEnCours:=false;
  xDeplFeu:=-1; yDeplFeu:=-1;
  RubriqueDeplacerFeu.Caption:=stRubriqueDeplacerFeu[0];
 end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.TimerSimulTimer(Sender: TObject);
begin
 if cv.TourEnCours then Exit;

 // On traite d'abord la demande
 case TypeDemande of
   arret:  begin
           TypeDemande:=rien;
           TimerSimul.Enabled:=false;
           SimulationEnCours:=false;
           ToolButtonArret.Enabled:=false;
           RubriqueArret.Enabled:=false;
           ToolButtonVerif.Enabled:=true;
           ToolButtonToutDroit.Enabled:=true;
           if ToolButtonAffDistEtapes.Down then
            begin
             ToolButtonAffDistEtapes.Down:=false;
             RubriqueInfosDistancesEtapes.Checked:=false;
             ToolButtonAffDistEtapes.Click;
            end;
           ToolButtonAffDistEtapes.Enabled:=false;
           RubriqueInfosDistancesEtapes.Enabled:=false;
           if ToolButtonAffDistArretsBus.Down then // v3.0
            begin
             ToolButtonAffDistArretsBus.Down:=false;
             RubriqueInfosDistancesArretsBus.Checked:=false;
             ToolButtonAffDistArretsBus.Click;
            end;
           ToolButtonAffDistArretsBus.Enabled:=false; // v3.0
           RubriqueInfosDistancesArretsBus.Enabled:=false; // v3.0
           if ToolButtonAffStatsEvol.Down then
            begin
             ToolButtonAffStatsEvol.Down:=false;
             RubriqueStatistiquesEvolution.Checked:=false;
             ToolButtonAffStatsEvol.Click;
            end;
           ToolButtonAffStatsEvol.Enabled:=false;
           RubriqueStatistiquesEvolution.Enabled:=false;
           if ToolButtonAffVeh.Down then
            begin
             ToolButtonAffVeh.Down:=false;
             RubriqueInfosVehicule.Checked:=false;
             ToolButtonAffVeh.Click;
            end;
           ToolButtonAffStatsEtapes.Enabled:=false;
           RubriqueStatistiquesEtapes.Enabled:=false;
           RubriqueSuivreCeVehicule.Enabled:=false;
           RubriqueSuivreCeBus.Enabled:=false; // v3.0
           RubriqueSuivreLe1erPieton.Enabled:=false; // v3.0
           RubriqueSuivreLe2emePieton.Enabled:=false; // v3.0
           AfficheBilan;
           StatusBar.Panels.Items[0].Text:='Arr�t de la simulation et r�initialisation du r�seau en cours...';
           RubriqueOuvrirClick(self);
           stNomFichAuto:='';

           DrawGridSimul.Options:=DrawGridSimul.Options+[goRangeSelect];
           DrawGridSimul.PopupMenu:=PopupMenuEdition;
           Exit;
           end;
   pause:  begin
           TypeDemande:=rien;
           TimerSimul.Enabled:=false;
           SimulationEnCours:=false;
           AfficheBilan;
           Exit;
           end;
 end{case of};
 // si aucune demande, on continue la simulation...
 Application.Title := Format(stFrmTitleCV, [cv.TourCrt]);
 Caption := Format(stFrmCaptionCV, [SaveDialog.FileName, cv.TourCrt]);

 if cv.NbVehiculesArrives=cv.NbVehicules then
  begin
   StatusBar.Panels.Items[0].Text:=Format('Simulation termin�e (%d v�hicules)', [cv.NbVehicules]);
   TypeDemande:=arret;
  end
 else
  begin
// TourSimulThread:=new TTourSimulThread(false); // Avec TThread A DEFINIR
  cv.EffectueTourSimulation; // Sans thread
  if (cv.NbVehiculesSortis>0) and (cv.NbVehiculesSortis-cv.NbVehiculesArrives>0) then
   StatusBar.Panels.Items[0].Text:=Format('Sur %d sortis [%d%%] : %d arriv�(s) [%d%%]. Sur %d en course : %d d�plac�(s) [%d%%].',
                                            [cv.NbVehiculesSortis, 100*cv.NbVehiculesSortis div cv.NbVehicules,
                                                          cv.NbVehiculesArrives, 100*cv.NbVehiculesArrives div cv.NbVehiculesSortis,
                                                          cv.NbVehiculesSortis-cv.NbVehiculesArrives,
                                                          cv.NbVehiculesDeplaces, 100*cv.NbVehiculesDeplaces div (cv.NbVehiculesSortis-cv.NbVehiculesArrives)]);
  end;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueQuitterClick(Sender: TObject);
begin
 Close;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonMarcheClick(Sender: TObject);
var i : Integer;
begin
 if frmDefFeux.Visible then frmDefFeux.Hide;
 if frmDefVoie.Visible then frmDefVoie.Hide;
 ToolButtonArret.Enabled:=true;
 RubriqueArret.Enabled:=true;
 if cv.TourCrt=0 then // Pas de simulation en pause
  begin
   StatusBar.Panels.Items[0].Text:='V�rification de la validit� du r�seau...';
   StatusBar.Repaint;
   if not VerifieReseau then  // Il faut d'abord que le r�seau soit correct
    begin
     Application.MessageBox(stErrDsReseau, stAvertissement, [smbOk], smsWarning);
     Exit;
    end;

   i:=0; while (i<cv.NbEtapes) and cv.Etapes[i].Definie do Inc(i);
   if i<cv.NbEtapes then
    begin
     Application.MessageBox(stNbEtapesInsuff, stAvertissement, [smbOk], smsWarning);
     Exit;
    end;

   StatusBar.Panels.Items[0].Text:='Pr�paration du calcul des distances aux �tapes...';
   StatusBar.Repaint;
   if not cv.PrepareCalculDistances then // On alloue la place pour calculer les distances
    begin // Si erreur alors probl�me de manque de m�moire
     Application.MessageBox(stMemInsuff, stErrInattendue, [smbOk], smsCritical);
     Exit;
    end;
   StatusBar.Panels.Items[0].Text:='Pr�paration des statistiques de fluidit� et de trafic...';
   StatusBar.Repaint;
   if not cv.PrepareCalculAttenteTrafic then // v2.2.7 : On alloue la place pour calculer les stats
    begin // Si erreur alors probl�me de manque de m�moire
     Application.MessageBox(stMemInsuff, stErrInattendue, [smbOk], smsCritical);
     Exit;
    end;
   StatusBar.Panels.Items[0].Text:='Calcul des distances aux �tapes...';
   StatusBar.Repaint;
   cv.CalculeDistances; // On calcule les distances par r�currence

   StatusBar.Panels.Items[0].Text:='V�rification du calcul des distances aux �tapes...';
   StatusBar.Repaint;
   if not cv.VerifieCalculDistances then // Sont-elles toutes d�finies ?
    begin
     xErr:=cv.xErr; yErr:=cv.yErr;
     StatusBar.Panels.Items[0].Text:=Format('La case (%d, %d) a une distance ind�finie.',
                                              [xErr, yErr]);
     if (xErr>-1) and (yErr>-1) then RedessineCase(xErr, yErr, true);
     Application.MessageBox(stReseauNonConnexe, stAvertissement, [smbOk], smsWarning);
     Exit;
    end;
   StatusBar.Panels.Items[0].Text:='Calcul des informations de trajet des lignes de bus...';
   StatusBar.Repaint;
   cv.InitialiseInfosTrajetLignesBus;
   cv.CalculeTrajetLignesBus; // v3.0
   cv.DistancesCalculees:=true;
   ToolButtonAffDistEtapes.Enabled:=true;
   RubriqueInfosDistancesEtapes.Enabled:=true;
   ToolButtonAffDistArretsBus.Enabled:=true; // v3.0
   RubriqueInfosDistancesArretsBus.Enabled:=true; // v3.0
   StatusBar.Panels.Items[0].Text:='Pr�paration des v�hicules...';
   StatusBar.Repaint;
   if not cv.PrepareVehicules then // On alloue la place et on pr�pare les v�hicules
    begin // Si erreur alors probl�me de manque de m�moire
     Application.MessageBox(stMemInsuff, stErrInattendue, [smbOk], smsCritical);
     Exit;
    end;
   StatusBar.Panels.Items[0].Text:='Pr�paration des bus...'; // v3.0
   StatusBar.Repaint;
   if not cv.PrepareBus then // On alloue la place et on pr�pare les bus. v3.0
    begin // Si erreur alors probl�me de manque de m�moire
     Application.MessageBox(stMemInsuff, stErrInattendue, [smbOk], smsCritical);
     Exit;
    end;
   StatusBar.Panels.Items[0].Text:='Pr�paration des pi�tons...';
   StatusBar.Repaint;
   if not cv.PreparePietons then // On alloue la place et on pr�pare les pi�tons
    begin // Si erreur alors probl�me de manque de m�moire
     Application.MessageBox(stMemInsuff, stErrInattendue, [smbOk], smsCritical);
     Exit;
    end;
   cv.NbVehiculesSortis:=0;
   cv.NbVehiculesDeplaces:=0;
   cv.NbVehiculesArrives:=0;
   if VerifierAvantSimulation then
    begin
     StatusBar.Panels.Items[0].Text:='Contr�le d''int�grit� du r�seau...';
     StatusBar.Repaint;
     cv.Verifie(stMsgErr);
     if Length(stMsgErr)>0 then
      begin
       Application.MessageBox(stMsgErr, 'Erreurs d''int�grit� trouv�es dans le r�seau', [smbOk], smsCritical);
       Exit;
      end;
    end;
   stNomFichAuto:=SaveDialog.FileName;
   EnregistrerAvant:=true; // On teste si on annule l'enregistrement (j'emprunte EnregistrerAvant)
   RubriqueEnregistrerClick(RubriqueEnregistrer);
   if not EnregistrerAvant then Exit; // Enregistrement Annul�
   EnregistrerAvant:=false;
   SetLength(cv.StatsCV, cv.NbToursStats*sizeof(stats));
   for i:=0 to cv.NbToursStats-1 do cv.StatsCV[i]:=stats.Create;
   cv.StatsCV[0].Definit;
  end;
 if cv.TourCrt=0 then
  begin
   // On active l'affichage des v�hicules
   if not ToolButtonAffVeh.Down then
    begin
     ToolButtonAffVeh.Down:=true;
     RubriqueVehicules.Checked:=true;
     ToolButtonAffVeh.Click;
    end;
   // On active l'affichage des pi�tons
   if not ToolButtonAffPtn.Down then
    begin
     ToolButtonAffPtn.Down:=true;
     RubriquePietons.Checked:=true;
     ToolButtonAffPtn.Click;
    end;
  end;
 // Mise en marche de la simulation : C'EST PARTI !
 SimulationEnCours:=true;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.AfficheStatsAttenteTrafic; // v2.2.7
var AffSvg : affichage;
begin
 AffSvg:=Affichages;
 frmStatsAttenteTrafic:=TfrmStatsAttenteTrafic.Create(self);
 try
  StatsAttenteTrafic:=True;
  Affichages:=aucun; // Pour une meilleure lisibilit�
  frmStatsAttenteTrafic.ShowModal;
 finally
  StatsAttenteTrafic:=False;
  Affichages:=AffSvg;
  DrawGridSimul.Repaint;
  frmStatsAttenteTrafic.Release;
  frmStatsAttenteTrafic:=nil;
 end;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueAttenteTraficClick(Sender: TObject);
begin
if SimulEnCours then
 Application.MessageBox( 'Vous devez interrompre ou arr�ter la simulation en cours pour visualiser ces statistiques.'#13#10+
                         'A l''affichage du bilan, on vous demandera si vous souhaitez voir ces statistiques.',
                         'Statistiques de fluidit� et de trafic')
else
 AfficheStatsAttenteTrafic;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueArretBusClick(Sender: TObject);
begin // v3.0
 ToolButtonArretBus.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueInfosDistancesArretsBusClick(
  Sender: TObject);
begin // v3.0
 ToolButtonAffDistArretsBus.Down:=not ToolButtonAffDistArretsBus.Down;
 ToolButtonAffDistArretsBus.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonArretBusClick(Sender: TObject);
var x, y, NumArretBus : Integer;
    d : direction;
    stMsgOp : String;
begin // v3.0
 x:=DrawGridSimul.Col;
 y:=DrawGridSimul.Row;
 NumArretBus:=cv.v[x, y].NumArretBus;
 if NumArretBus>0 then // SI arr�t de bus
  begin // on le SUPPRIME
   cv.SupprimeArretBus(x, y);
   for d:=nord to ouest do // On rafra�chit les cases voisines du m�me arr�t
    if NumArretBus=cv.vxyd(x,y,d).NumArretBus then
     RedessineCase((x+dx[d]) mod NBX, (y+dy[d]) mod NBY, true);
   stMsgOp:=Format( 'La case (%d,%d) a �t� retir�e de l''arr�t de bus %d.',
                    [DrawGridSimul.Col, DrawGridSimul.Row, NumArretBus]);
   SimulModifiee:=true;
  end{if NumArretBus}
 else // SINON
  begin // on le CREE
   NumArretBus:=cv.AjouteArretBus(x, y);
   if NumArretBus>0 then
    begin
     for d:=nord to ouest do
      if NumArretBus=cv.vxyd(x,y,d).NumArretBus then
       RedessineCase((x+dx[d]) mod NBX, (y+dy[d]) mod NBY, true);
     stMsgOp:=Format( 'La case (%d,%d) a �t� ajout�e � l''arr�t de bus %d.',
                      [DrawGridSimul.Col, DrawGridSimul.Row, NumArretBus]);
     SimulModifiee:=true;
    end{if NumArretBus}
   else
    if cv.NbArretsBus>0 then
     stMsgOp:=Format( 'Impossible de cr�er un arr�t de bus : il y en a d�j� %d !',
                      [cv.NbArretsBus])
    else
     stMsgOp:='Impossible de cr�er un arr�t de bus : vous devez d�j� en d�finir le nombre !';
  end{else};
 RedessineCase(x, y, true);
 StatusBar.Panels.Items[0].Text:=stMsgOp;
 if ToolButtonMajVoie.Down then frmDefVoie.RafraichitInfos;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonAffDistArretsBusClick(Sender: TObject);
begin // v3.0
 frmAffDistArretsBus.Visible:=ToolButtonAffDistArretsBus.Down;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonDepotBusClick(Sender: TObject);
var x, y, xPrc, yPrc : Integer;
begin // v3.0
 x:=DrawGridSimul.Col;
 y:=DrawGridSimul.Row;
 xPrc:=cv.DepotBus.x;
 yPrc:=cv.DepotBus.y;
 if cv.v[x, y].EstDepotBus then // On supprime
  cv.DepotBus.Initialise
 else // On le pose sur la case courante
  begin
   cv.DepotBus.Definit(x, y);
   RedessineCase(xPrc, yPrc, true);
  end;
 RedessineCase(x, y, true);
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueDepotBusClick(Sender: TObject);
begin
 ToolButtonDepotBus.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.ToolButtonInfosBusClick(Sender: TObject);
begin // v3.0
 frmInfosBus.Visible:=ToolButtonInfosBus.Down;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueInfosBusClick(Sender: TObject);
begin
 ToolButtonInfosBus.Down:=not ToolButtonInfosBus.Down;
 ToolButtonInfosBus.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueSuivreCeBusClick(Sender: TObject);
var NumBus : Integer;
begin // v3.0
 NumBus:=cv.v[DrawGridSimul.Col, DrawGridSimul.Row].NumBus;
 if NumBus=0 then Exit;
 if not ToolButtonRecherche.Down then
  begin
   ToolButtonRecherche.Down:=true;
   ToolButtonRecherche.Click;
  end; 
 frmRecherche.RadioButtonBus.Checked:=true;
 frmRecherche.SpinEditBus.Value:=NumBus;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueInfosPietonClick(Sender: TObject);
begin // v3.0
 ToolButtonInfosPieton.Down:=not ToolButtonInfosPieton.Down;
 ToolButtonInfosPieton.Click;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueSuivreLe1erPietonClick(Sender: TObject);
var NumPieton : Integer;
begin
 NumPieton:=cv.v[DrawGridSimul.Col, DrawGridSimul.Row].NumPieton[0];
 if NumPieton=0 then Exit;
 if not ToolButtonRecherche.Down then
  begin
   ToolButtonRecherche.Down:=true;
   ToolButtonRecherche.Click;
  end; 
 frmRecherche.RadioButtonPieton.Checked:=true;
 frmRecherche.SpinEditPieton.Value:=NumPieton;
end;
//---------------------------------------------------------------------------
procedure TfrmSimulation.RubriqueSuivreLe2emePietonClick(Sender: TObject);
var NumPieton : Integer;
begin
 NumPieton:=cv.v[DrawGridSimul.Col, DrawGridSimul.Row].NumPieton[0];
 if NumPieton=0 then Exit;
 if not ToolButtonRecherche.Down then
  begin
   ToolButtonRecherche.Down:=true;
   ToolButtonRecherche.Click;
  end;
 frmRecherche.RadioButtonPieton.Checked:=true;
 frmRecherche.SpinEditPieton.Value:=NumPieton;
end;

procedure TfrmSimulation.ToolButtonInfosPietonClick(Sender: TObject);
begin
 frmInfosPieton.Visible:=ToolButtonInfosPieton.Down;
end;

end.
