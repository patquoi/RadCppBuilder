//---------------------------------------------------------------------------
#include "vclx.h"
#include <stdlib.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_simul.h"
#include "f_defv.h"
#include "simul.h"
#include "f_prmsim.h"
#include "f_prmbus.h"
#include "f_prmtram.h"
#include "f_deff.h"
#include "f_afdiste.h"
#include "f_afdistab.h"
#include "f_afdistat.h"
#include "f_afdistft.h"
#include "f_stats.h"
#include "f_statsv.h"
#include "f_infveh.h"
#include "f_infptn.h"
#include "f_infbus.h"
#include "f_inftram.h"
#include "f_inftaxi.h"
#include "f_rech.h"
#include "f_carfours.h"
#include "f_statsc.h"
#include "f_statsat.h"
#include "f_defn.h"
#include "f_dimzone.h"
#include "f_genres.h"
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include "f_propos.h"
#endif
#include "winlinux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
#define IDB_DIR         0
#define IDB_FEU         4
#define IDB_STOP       20
#define IDB_CLP        24
#define IDB_VOIE       28
#define IDB_CURSEUR    44
#define IDB_CURSERR    45
#define IDB_ETAPE      46
#define IDB_SELFEU     47
#define IDB_DIRTD      51
#define IDB_DEPLFEU    52 // v3.5
#define IDB_VEH        55
#define IDB_PSGPT     127 // v2.0
#define IDB_PIETON    129 // v2.0
#define IDB_URGENCE   153 // v2.2
#define IDB_POLICE    157 // v2.2
#define IDB_VEHPU     165 // v2.2
#define IDB_NUMETAPE  189 // v2.2
#define IDB_ARRETBUS  221 // v3.0
#define IDB_BUSTRAM   233 // v3.5 (ajout de TRAM au nom car commun avec les bus)
#define IDB_DEPOTBUS  341 // v3.0
#define IDB_PSGBUS    342 // v3.1
#define IDB_VOIETRAM  343 // v3.5
#define IDB_ARRETTRAM 349 // v3.5
#define IDB_PLCTAXI   355 // v3.6
#define IDB_VEHTAXI   356 // v3.6
#define IDB_TROTTOIR  368 // v3.8
#define IDB_TOITURE   384 // v3.8
#define IDB_COINTOIT  400 // v3.8
#define IDB_ARBRE     404 // v3.9
#define IDB_PELOUSE   408 // v3.9
#define IDB_SANG      409 // v4.3
//---------------------------------------------------------------------------
// ATTENTION, les IDB suivants
// n'existent pas en bitmap 8x8.
// Il faut les renuméroter
// de telle sorte qu'ils soient
// maintenus à la fin de ImageList8x8x2
#define IDB_COINTROT  410 // v3.8
#define IDB_DIRCARF   414 // v3.6.1.
//---------------------------------------------------------------------------
// Pour IDB_BANC
#define HORIZONTAL 0
#define VERTICAL   1
//---------------------------------------------------------------------------
// 2ème indice de NumImgBus. v3.0
#define TETE  0
#define QUEUE 1
//---------------------------------------------------------------------------
#define NBCOULDIFFV    6
#define NBCOULDIFFVPU  2
#define NBCOULDIFFP    3
#define COULEURURGENCE 1
//---------------------------------------------------------------------------
// v3.5 : calcul de la taille idéale par différence entre la fiche et le DrawGrid
//#define MAXHEIGHTFSIMUL 596
//#define MAXWIDTHFSIMUL  800
//---------------------------------------------------------------------------
#define NB_ELEMENTS_PAR_DEFAUT   true
#define AUCUN_ELEMENT_PAR_DEFAUT false
//---------------------------------------------------------------------------
#define NBELEMENTSBARREOUTILS 8 // v3.5
#define TOOLBAR  0
#define MENUITEM 1
//---------------------------------------------------------------------------
// Choix pour les éléments communs entre bus et tram
#define BUS  1
#define TRAM 2
//---------------------------------------------------------------------------
// Pour VerifieDistances
#define NBTYPESDISTANCE 4 // v3.5
//---------------------------------------------------------------------------
TfrmSimulation *frmSimulation=NULL;
//---------------------------------------------------------------------------
// v2.2 : Décalage gyrophares d{x|y}g[dorig][ddest]
//                ddest =      n   e   s   o
const int dxg[2][5][5]={{{ 0,  0,  0,  0,  0}, // ZOOMx1
                         { 0,  0,  1,  0,  0}, // dorig = nord
                         { 0,  1,  0,  1,  0}, // dorig = est
                         { 0,  0,  1,  0,  0}, // dorig = sud
                         { 0,  0,  0,  0,  0}},// dorig = ouest
                        {{ 0,  0,  0,  0,  0}, // ZOOMx2
                         { 0,  0,  1,  0, -1}, // dorig = nord
                         { 0,  1,  0,  1,  0}, // dorig = est
                         { 0,  0,  1,  0, -1}, // dorig = sud
                         { 0, -1,  0, -1,  0}}},//dorig = ouest
          dyg[2][5][5]={{{ 0,  0,  0,  0,  0},
                         { 0,  0,  0,  0,  0}, // dorig = nord
                         { 0,  0,  0,  1,  0}, // dorig = est
                         { 0,  0,  1,  0,  1}, // dorig = sud
                         { 0,  0,  0,  1,  0}},// dorig = ouest
                        {{ 0,  0,  0,  0,  0},
                         { 0,  0, -1,  0, -1}, // dorig = nord
                         { 0, -1,  0,  1,  0}, // dorig = est
                         { 0,  0,  1,  0,  1}, // dorig = sud
                         { 0, -1,  0,  1,  0}}},//dorig = ouest
            // [Dir1][Dir2][AVT|ARR] Dir2=N   ,   E   ,   S   ,   O
          NumImgBusTram[NBDIR][NBDIR][2]={{{ 1, 7},{ 2, 9},{12,12},{ 0, 5}},  // Dir1 = N // v3.5 : ajout de Tram dans le nom (nitmaps communes aux bus)
                                          {{ 3, 8},{ 4,10},{ 5, 0},{12,12}},  // Dir1 = E
                                          {{12,12},{ 6,11},{ 7, 1},{ 8, 3}},  // Dir1 = S
                                          {{11, 6},{12,12},{ 9, 2},{10, 4}}}; // Dir1 = O
//---------------------------------------------------------------------------
// v3.5 : Ajout de Tram aux constantes de Couleur
TColor CoulLigneBusTram[NBMAXLIGNESBUSTRAM]={clBlue, clRed, clLime, clYellow, clFuchsia, clAqua, clPurple, (TColor)0x00FF0080, (TColor)0x000080FF};
TColor CoulTLigneBusTram[NBMAXLIGNESBUSTRAM]={clWhite, clBlack, clBlack, clBlack, clBlack, clBlack, clWhite, clWhite, clBlack};
//---------------------------------------------------------------------------
const AnsiString asVide,
                 asFrmTitleCV = "Centre-Ville [%d]",
                 asFrmCaptionCV = "Centre-Ville - %s [%d]",
                 asTitreCV = "Centre-Ville",
                 asAsterisque[2] = {"","*"}, // v3.6
                 asSupInf[3] = {"", ">", "<"}, // v3.6. Remplacement par <,> pour Linux (v3.8). v4.3 : asSupInf remplace as12
                 asMort[2] = {"", "†"}, // v4.3. Suivant valeur de pieton::Ecrase
                 asQstEnregistrerFichier = "Voulez-vous enregistrer le fichier ",
                 asTypeVehicule[NBNIVEAUXPRIORITE]={"", "d'urgence","de police"},
                 asDebutNom[2]={"ToolBar", "MenuItem"}, // v3.5
                 asNomElementBarreOutils[NBELEMENTSBARREOUTILS]={"Menu", "Fichier", "Affichage", "EditionCase", "EditionSelection", "Simulation", "Informations", "Statistiques"}, // v3.5
                 asTypeDistance[NBTYPESDISTANCE]={"", "à une étape", "à un arrêt de bus", "à un arrêt de tram"},
                 asChargementNonEffectue="Chargement non effectué",
                 asSauvegardeNonEffectuee="Sauvegarde non effectuée",
                 asErrInattendue="Erreur inattendue",
                 asMemInsuff="Mémoire insuffisante !",
                 asFrmReseauNonConnexe[2]={"\
Le réseau n'est pas connexe : une distance %s n'a pas pu être définie !\n\
Un tableau des distances va apparaître pour vous aider à résoudre le problème.", // v3.5
                                           "\
Le réseau n'est pas connexe : une distance %s n'a pas pu être définie !\n\
Un tableau des distances va apparaître pour vous aider à résoudre le problème.\n\n\
ATTENTION ! S'il y a des zones où seuls les bus et les véhicules prioritaires peuvent passer, TOUTES CES ZONES DOIVENT ÊTRE DÉFINIES COMME PASSAGE RÉSERVÉ AUX BUS.\n\
En d'autres termes, il ne doit pas y avoir de zones non réservées aux bus isolées par des zones réservées aux bus."},
                 asSelectionIncorrecte="Sélection incorrecte",
                 asTracerEffacerPeripherique="\
Pour tracer ou effacer un périphérique,\n\
vous devez sélectionner au moins 2 lignes et 2 colonnes.",
                 asNombreLignesColonnesDifferent="Le nombre de lignes sélectionnées doit être différent du nombre de colonnes sélectionnées.",
                 asTracerEffacerRoute="\
Vous ne devez sélectionner...\n\
 - qu'1 SEULE LIGNE ou qu'1 SEULE COLONNE pour tracer ou effacer une voie À SENS UNIQUE.\n\
 - que 2 LIGNES ou 2 COLONNES pour tracer ou effacer une voie À DOUBLE SENS.",
                 asErrDsReseau="\
Une erreur a été trouvée dans le réseau !\n\n\
La cause est affichée en bas de la fenêtre et le curseur jaune clignotant sur le réseau indique l'endroit de l'erreur.\n\
Corriger puis réessayer.\n\n\
Pour plus d'informations, allez dans le sommaire de l'aide (Maj+Alt+F1) et choisissez la rubrique \"Lancement de la simulation, Messages d'erreur, Vérification du réseau\".", // v3.5
                 asAvertissement="Impossible de continuer",
                 asNbEtapesInsuff="Il manque des étapes !",
                 asCleExtCvw="\\.cvw",
                 asCleCvw="\\Cvw",
                 asCvw="Cvw",
                 asFormatCoord="(%d, %d)",
                 asFormatBilan="\
Données initiales\n\n\
 - Nombre de véhicules : %d\n\
 - Parcours minimum moyen par véhicule (cases) : %.2f\n\
 - Temps minimum moyen par véhicule (tours) : %.2f\n\
 - Temps minimum moyen d'attente de départ par véhicule : %d\n\n\
Bilan au tour n°%d\n\n\
 - Durée de la simulation : %s\n\
 - Nombre de véhicule(s) arrivé(s) : %d (%.2f%%)\n\
 - Parcours moyen effectué par véhicule (cases) : %.2f (%.2f%%)\n\
 - Attente de départ par véhicule (tours) : %.2f (%.2f%%)\n\
 - Temps moyen du parcours par véhicule (tours) : %.2f (%.2f%%) dont\n\
    · Déplacement par véhicule (tours) : %.2f (%.2f%%)\n\
    · Attente par véhicule (tours) : %.2f (%.2f%%)\n\n\
Voulez-vous voir les statistiques de fluidité et de trafic en couleurs ?",
                 asFormatBilanSansArrives="\
Données initiales\n\n\
 - Nombre de véhicules : %d\n\
 - Parcours minimum moyen par véhicule (cases) : %.2f\n\
 - Temps minimum moyen par véhicule (tours) : %.2f\n\
 - Temps minimum moyen d'attente de départ par véhicule : %d\n\n\
Bilan au tour n°%d\n\n\
 - Durée de la simulation : %s\n\
 - Aucun véhicule n'est encore arrivé.\n\n\
Voulez-vous voir les statistiques de fluidité et de trafic en couleurs ?",
                 asTypeVoie[4]={"", "routes","voies de trams", ""},
                 asTypeArret[4]={"", "de bus","de tram", ""};
//---------------------------------------------------------------------------
__fastcall TfrmSimulation::TfrmSimulation(TComponent* Owner) : TForm(Owner)
{ // Constructeur de la fiche
 yCrt=xCrt=yPrc=xPrc=-1; DirOrigVoieTram=indefinie;// v3.5
}
//---------------------------------------------------------------------------
void TfrmSimulation::RedessineCase(int x, int y, bool EffaceFond)
 {
  TRect CellWRect=DrawGridSimul->CellRect(x, y);
  RECT CellRect={CellWRect.Left, CellWRect.Top, CellWRect.Right, CellWRect.Bottom};
#ifdef CV_WINDOWS
  InvalidateRect(DrawGridSimul->Handle, &CellRect, EffaceFond);
#endif
#ifdef CV_LINUX
  ((TWidgetControl*)DrawGridSimul)->InvalidateRect(CellRect, EffaceFond);
#endif
 }
//---------------------------------------------------------------------------
void TfrmSimulation::RafraichitActionsEdition(mode_edition ModeEdition)
 {
  bool EditionCase=(ModeEdition==meCase),
       EditionSelection=(ModeEdition==meSelection);
  int i;
  for(i=0; i<ActionList->ActionCount; i++) // v3.8.3
   if (ActionList->Actions[i]->Category=="Edition (case)")
    ((TAction*)ActionList->Actions[i])->Enabled=EditionCase;
   else
    if (ActionList->Actions[i]->Category=="Edition (sélection)")
     ((TAction*)ActionList->Actions[i])->Enabled=EditionSelection;
  ToolBarEditionCase->Repaint();
  ToolBarEditionSelection->Repaint();
  MenuNatureDecors->Enabled=EditionCase;  // Le ToolButton est lié au menu (pas d'action)
  ToolButtonNatureDecors->Enabled=EditionCase;  // Le ToolButton est lié au menu (pas d'action)
  MenuRoutesCoins->Enabled=EditionSelection; // Le ToolButton est lié au menu (pas d'action)
  ToolButtonCoins->Enabled=EditionSelection; // Le ToolButton est lié au menu (pas d'action)
  MenuPeripherique->Enabled=EditionSelection; // Le ToolButton est lié au menu (pas d'action)
  ToolButtonPeripherique->Enabled=EditionSelection; // Le ToolButton est lié au menu (pas d'action)
  if (EditionCase) // Permet de rafraîchir les boutons dépendant de la case courante
   RedessineCase(DrawGridSimul->Col, DrawGridSimul->Row, true);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::DrawGridSimulDrawCell(TObject *Sender,
      int Col, int Row, TRect &Rect, TGridDrawState State)
 { // Dessin de chaque case (voie)
  int Colonnes=DrawGridSimul->Selection.Right-DrawGridSimul->Selection.Left+1,
      Lignes=DrawGridSimul->Selection.Bottom-DrawGridSimul->Selection.Top+1,
      PassPoss=0,
      BordTrottoir=0, BordToiture=0, CoinToiture=0, // v3.8
      NumPieton, // v2.0
      NivPriorite, // v2.2
      Zoom=!!ActionZoom->Checked, // v2.2
      SensVT; // v3.5
  TColor CoulTxt; // v3.0.5
  direction dorig, ddest,
            DirArretBus; // v3.0
  voie *v=&(cv->v[Col][Row]),
       *vv;
  sens Sens=cv->SensPassagePietonsPossible(Col, Row); // v2.0
  pieton *p; // v2.0
  vehicule *Veh;
  bus *Bus; // v3.0
  tram *Tram; // v3.5
  taxi *Taxi; // v3.6
  bool NordPoss, EstPoss, SudPoss, OuestPoss,
       NordPossT, EstPossT, SudPossT, OuestPossT, // v3.5
       DefFeux= frmDefFeux&&  // v3.8.1
                frmDefFeux->Visible,
       EditionAutorisee= (!DefFeux)&&
                         (!cv->TourCrt)&&
                         (!SimulationEnCours),
       ChgmtDirRoutesAutorise= (!v->PassagePietons)&& // v3.5
                               (!v->NumArretBus)&&
                               EditionAutorisee,
       ChgmtDirVoiesAutorise= (!v->PassagePietons)&& // v3.5
                              (!v->NumArretTram)&&
                              (!v->Priorite[nord-1])&&
                              (!v->Priorite[est-1])&&
                              (!v->Priorite[sud-1])&&
                              (!v->Priorite[ouest-1])&&
                              EditionAutorisee;
  TCheckBox *CheckBox; // v3.0
  AnsiString asListeLignes, asMsg="";

  // 1a. Stats Attente / Trafic
  if (StatsAttenteTrafic&&
      frmStatsAttenteTrafic&&
      (v->DirPoss>aucune)&&
      (!v->NumEtape)) // v2.2.7
   {
    DrawGridSimul->Canvas->Brush->Color=frmStatsAttenteTrafic->CouleurCase(Col, Row);
    DrawGridSimul->Canvas->FillRect(Rect);
   }
  else
   { // Calcul commun pour l'affichage du quadrillage, des routes, trottoirs et immeubles (v3.8)
    if (Affichage&(aff_voie|aff_quadr|aff_env)) // v3.8.1 (aff_env)
     { // 1. On pose le dur : Bitume des routes et trottoirs ainsi que le murs des immeubles (ou plutôt le toit !). v3.8 (trottoir et immeubles)
      for(int d=nord; d<=ouest; d++)
       { // On détermine ici les orientations pour les routes et trottoirs
        PassPoss+=(int)PossDir[d]*(((v->DirPoss&PossDir[d])==PossDir[d])||
                                   ((cv->V(Col,Row,d).DirPoss&InvPossDir[d])==InvPossDir[d]));
        BordTrottoir+=(int)PossDir[d]*((v->v((direction)d)->DirPoss>aucune)||  // v3.8
                                       (v->v((direction)d)->SensVoieTram>aucune_voie));
        BordToiture+=(int)PossDir[d]*(NATURE(v->v((direction)d))!=immeubles);
        CoinToiture+=(int)CoinDir[d]*(NATURE(v->v((direction)d)->v(ADroiteDe[(direction)d]))==immeubles); // Immeuble voisin présent en coin.. 1=NE;2=SE;4=SO;8=NO
       }
      if ((Affichage&aff_env)&& // v3.8.1 (aff_env)
          (!PassPoss)&&(!v->SensVoieTram))
       {
        // 1a. Trottoirs
        if (NATURE(v)==trottoirs) // v3.8
         if (v->Nature==pelouse) // v3.9
          ImageList8x8->Draw(DrawGridSimul->Canvas, Rect.Left, Rect.Top, IDB_PELOUSE);
         else
          {
           // D'abord le trottoir
           ImageList8x8->Draw(DrawGridSimul->Canvas, Rect.Left, Rect.Top, IDB_TROTTOIR+BordTrottoir);
           for(int d=nord; d<=ouest; d++)
            if ((!v->v((direction)d)->DirPoss)&&
                (!v->v((direction)d)->SensVoieTram)&&
                (!v->v(ADroiteDe[(direction)d])->DirPoss)&&
                (!v->v(ADroiteDe[(direction)d])->SensVoieTram)&&
                (v->v((direction)d)->v(ADroiteDe[(direction)d])->DirPoss||
                 v->v((direction)d)->v(ADroiteDe[(direction)d])->SensVoieTram))
             ImageList8x8->Draw(DrawGridSimul->Canvas, Rect.Left, Rect.Top, IDB_COINTROT+d-1);
           // Ensuite les décors (sauf pelouse)
           switch(v->Nature) // v3.9
            {
             case arbre:  ImageList8x8->Draw(DrawGridSimul->Canvas, Rect.Left, Rect.Top, IDB_ARBRE+(Col+Row)%4); break;
             default :    break;
            }
          }
        // 1b. Immeubles.
        if (NATURE(v)==immeubles) // v3.8
         {
          bool UnSeulCoinVide=false;
          if (!BordToiture)
           {
            for(int d=nord; d<=ouest; d++)
             if (CoinToiture==(int)(quatre_coins-CoinDir[d]))
              {
               UnSeulCoinVide=true;
               ImageList8x8->Draw(DrawGridSimul->Canvas, Rect.Left, Rect.Top, IDB_COINTOIT+d-1);
              }
            if (!UnSeulCoinVide)
             ImageList8x8->Draw(DrawGridSimul->Canvas, Rect.Left, Rect.Top, IDB_TOITURE);
           }
          else
           ImageList8x8->Draw(DrawGridSimul->Canvas, Rect.Left, Rect.Top, IDB_TOITURE+BordToiture);
         }
        // Si NI de voies de circulation NI immeubles NI trottoirs, ALORS c'est le néant total : tout noir (couleur du fond)
       }
      // 1c. On met le bitume. À savoir, où passe la route... Si on peut aller ou venir du nord, on pose le bitume jusqu'en haut, et ainsi de suite...
      if (Affichage&(((!PassPoss)*aff_quadr)|
                     ((!!PassPoss)*aff_voie)))
       ImageList8x8->Draw(DrawGridSimul->Canvas, Rect.Left, Rect.Top, IDB_VOIE+PassPoss);
     }
   }
  // 2. On peint la route : ligne de stop ou cédez-le-passage
  if (Affichage&aff_sign)
   {
    // 2a. On peint le passage de bus (v3.5 : déplacé en tête)
    if (v->PassageBus) // v3.1
     ImageList8x8->Draw(DrawGridSimul->Canvas,
                        Rect.Left, Rect.Top,
                        IDB_PSGBUS);
    if (v->NumPlaceTaxi) // v3.6
     ImageList8x8->Draw(DrawGridSimul->Canvas,
                        Rect.Left, Rect.Top,
                        IDB_PLCTAXI);
    // 2b. On peint les c.l.p & stops
    for(int i=0; i<4; i++)
     switch(v->Priorite[i])
      {
       case cedez_le_passage: ImageList8x8->Draw(DrawGridSimul->Canvas,
                                                 Rect.Left, Rect.Top,
                                                 IDB_CLP+i);
                              break;
       case stop:             ImageList8x8->Draw(DrawGridSimul->Canvas,
                                                 Rect.Left, Rect.Top,
                                                 IDB_STOP+i);
                              break;
       default: break;
      }
    // 2c. On peint le passage piétons
    if (v->PassagePietons&&Sens) // v2.0
     {
      ImageList8x8->Draw(DrawGridSimul->Canvas,
                         Rect.Left, Rect.Top,
                         IDB_PSGPT+Sens-1);
     }
    // 2d. On peint l'arrêt de bus
    if (v->NumArretBus&&
        (DirArretBus=cv->DirectionArretBus(Col, Row))) // v3.0
     {
      if ((!frmParamBus)||
          (!frmParamBus->Visible)||
          (frmParamBus->NumArretBusAMontrer!=v->NumArretBus)||
          frmParamBus->TimerClignotement->Tag)
       ImageList8x8->Draw(DrawGridSimul->Canvas,
                          Rect.Left, Rect.Top,
                          IDB_ARRETBUS+
                          3*(DirArretBus-1)+
                          cv->PositionArretBus(Col, Row, DirArretBus));
     }
    // 2e. Affichage des directions au carrefour (si pas d'affichage des directions possibles). v3.6.1
    if (Zoom&&(!(Affichage&aff_dir)))
     for(int d=nord; d<=ouest; d++)
      if (v->Priorite[d-1]&&(v->DirPoss&PossDir[d]))
       {
        vv=v->v((direction)d);
        ImageList8x8->Draw(DrawGridSimul->Canvas,
                           Rect.Left, Rect.Top,
                           IDB_DIRCARF-1+ // Bitmaps de flèche de direction au carrefour
                           7*(d-1)+ // Direction
                           4*((!vv->ToutDroit)&&(vv->DirPoss&PossDir[AGaucheDe[d]]))+ // à gauche
                           2*((vv->DirPoss&PossDir[d])>0)+ // Tout droit
                             ((!vv->ToutDroit)&&(vv->DirPoss&PossDir[ADroiteDe[d]]))); // à droite
       }
   }
  // 3. On met les voies de tram
  if ((Affichage&aff_voie)&&
      (!StatsAttenteTrafic))
   for(int i=0,SensVT=nord_est; SensVT<=sud_ouest; i++,SensVT*=2)
    if ((v->SensVoieTram&SensVT)&&
        ((!frmParamTram)||
         (!frmParamTram->Visible)||
         (frmParamTram->NumArretTramAMontrer!=v->NumArretTram)||
         frmParamTram->TimerClignotement->Tag))
     ImageList8x8->Draw( DrawGridSimul->Canvas,
                         Rect.Left, Rect.Top,
                         (v->NumArretTram&&(Affichage&aff_sign))?
                         IDB_ARRETTRAM+i:IDB_VOIETRAM+i);

  // 4. On met le(s) piéton(s) le(s) cas échéant(s). v2.0. (Avant les véhicules depuis v4.3 pour mode sanglant)
  if ((Affichage&aff_ptn)&&v->NbPietons&&((NATURE(v)<=trottoirs))) // v3.8 (immeubles)
   {
    // 4a. Vue de mort
    for(int i=0; i<NBMAXPIETONSPARCASE; i++)
     if (v->NumPieton[i])
      { // On décale les piétons pour qu'ils puissent entrer dans une case. On prend alors la direction du premier
       p=&(cv->Pieton[NumPieton=v->NumPieton[i]-1]);
       if (p->Ecrase) // v4.3
        ImageList8x8->Draw(DrawGridSimul->Canvas,
                           Rect.Left, Rect.Top,
                           IDB_SANG);
      }
    // 4b. Vue de vivant
    for(int i=0; i<NBMAXPIETONSPARCASE; i++)
     if (v->NumPieton[i])
      { // On décale les piétons pour qu'ils puissent entrer dans une case. On prend alors la direction du premier
       p=&(cv->Pieton[NumPieton=v->NumPieton[i]-1]);
       if (!p->Ecrase) // v4.3
        ImageList8x8->Draw(DrawGridSimul->Canvas,
                           1+Rect.Left+(2*p->DemiCase-1)*dxr[p->Dir]*((1+Rect.Right-Rect.Left)/4),
                           1+Rect.Top+ (2*p->DemiCase-1)*dyr[p->Dir]*((1+Rect.Bottom-Rect.Top)/4),
                           IDB_PIETON+                // Début image piéton
                           8*(NumPieton%NBCOULDIFFP)+ // Couleur
                           (p->TourDrnDepl<p->TourDrnAff?
                            p->Dir-1: // à l'arrêt
                            (4+p->DemiCase%2+2*(1-p->Dir%2)) // en mouvement
                           ));
       p->TourDrnAff=cv->TourCrt;
      }
   }

  if (Affichage&aff_veh&& // 5. Affichage des véhicules et bus et trams
      (!v->NumEtape)&&(!v->EstDepotBus())) // Si pas d'étape ou dépôt sur la case. v3.0
   {
    if (v->NumVehicule) // 5a. On met les véhicules le cas échéant
     {
      Veh=&(cv->Vehicule[v->NumVehicule-1]);
      dorig=(Veh->DirDrnDepl?
             InvDir[Veh->DirDrnDepl]:
             InvDir[Veh->Dir]);
      ddest=Veh->Dir;
      if (dorig==ddest) dorig=InvDir[ddest];
      switch(Veh->NivPriorite) // v2.2
       {
        case normal:  ImageList8x8->Draw(DrawGridSimul->Canvas,
                                         Rect.Left, Rect.Top,
                                         IDB_VEH+ // Numero de bitmap initiale des véhicules
                                         (v->NumVehicule-1)%NBCOULDIFFV+ // Numéro de couleur
                                         (3*(dorig-1)+ddest-1-(ddest>dorig))*NBCOULDIFFV);
                      break;
        case urgence: ImageList8x8->Draw(DrawGridSimul->Canvas,
                                         Rect.Left, Rect.Top,
                                         IDB_VEHPU+ // Numero de bitmap initiale des véhicules de police/urgence
                                         COULEURURGENCE+ // Numéro de couleur (rouge)
                                         (3*(dorig-1)+ddest-1-(ddest>dorig))*NBCOULDIFFVPU);
                       ImageList8x8->Draw(DrawGridSimul->Canvas,
                                         Rect.Left+dxg[Zoom][dorig][ddest],
                                         Rect.Top+dyg[Zoom][dorig][ddest],
                                         IDB_URGENCE+ // Numero de bitmap initiale des gyrophares
                                         2*((dorig+ddest)%2)+ // Horizontal/vertical ou en diagonale
                                         cv->TourCrt%2); // Clignotement
                      break;
        case police:  ImageList8x8->Draw(DrawGridSimul->Canvas,
                                         Rect.Left, Rect.Top,
                                         IDB_VEHPU+ // Numero de bitmap initiale des véhicules de police/urgence
                                         // Couleur Police = 1ère couleur (blanche)
                                         (3*(dorig-1)+ddest-1-(ddest>dorig))*NBCOULDIFFVPU);
                       ImageList8x8->Draw(DrawGridSimul->Canvas,
                                         Rect.Left+dxg[Zoom][dorig][ddest],
                                         Rect.Top+dyg[Zoom][dorig][ddest],
                                         IDB_POLICE+ // Numero de bitmap initiale des gyrophares
                                         2*((dorig+ddest)%NBDIR)+ // Direction
                                         cv->TourCrt%2); // Clignotement
                      break;
       }
     }
    if (v->NumBus)  // 5b. On met les bus le cas échéant. v3.0
     {
      Bus=&(cv->Bus[v->NumBus-1]);
      ImageList8x8->Draw(DrawGridSimul->Canvas,
                         Rect.Left, Rect.Top,
                         IDB_BUSTRAM+ // Numero de bitmap initiale des bus
                         12*(Bus->NumLigne-1)+ // Couleur de la ligne
                         (v->EstTeteBus()?
                          NumImgBusTram[Bus->Dir-1][Bus->DirDrnDepl-1][TETE]:
                          NumImgBusTram[Bus->DirDrnDepl-1][Bus->DirAvtDrnDepl-1][QUEUE]));
     }
    if (v->NumTram)  // 5c. On met les trams le cas échéant. v3.5
     {
      Tram=&(cv->Tram[v->NumTram-1]);
      ImageList8x8->Draw(DrawGridSimul->Canvas,
                         Rect.Left, Rect.Top,
                         IDB_BUSTRAM+ // Numero de bitmap initiale des trams
                         12*(Tram->NumLigne-1)+ // Couleur de la ligne
                         (v->EstTeteTram()?
                          NumImgBusTram[Tram->Dir-1][Tram->DirDrnDepl-1][TETE]:
                          NumImgBusTram[Tram->DirDrnDepl-1][Tram->DirAvtDrnDepl-1][QUEUE]));
     }
    if (v->NumTaxi)  // 5d. On met les taxis le cas échéant. v3.6
     {
      Taxi=&(cv->Taxi[v->NumTaxi-1]);
      dorig=(Taxi->DirDrnDepl?
             InvDir[Taxi->DirDrnDepl]:
             InvDir[Taxi->Dir]);
      ddest=Taxi->Dir;
      ImageList8x8->Draw(DrawGridSimul->Canvas,
                         Rect.Left, Rect.Top,
                         IDB_VEHTAXI+ // Numero de bitmap initiale des taxis
                         3*(dorig-1)+ddest-1-(ddest>dorig));
     }
   }
  // 6. On met le feu (ouais qu'ça pète !) de signalisation le cas échéant
  if (Affichage&aff_sign)
   for(int i=0; i<4; i++)
    if ((v->NumFeu[i])&&
        (cv->Feu[v->NumFeu[i]-1].x==Col)&&
        (cv->Feu[v->NumFeu[i]-1].y==Row)&&
        (cv->Feu[v->NumFeu[i]-1].Dir==i+1))
     ImageList8x8->Draw(DrawGridSimul->Canvas,
                        Rect.Left, Rect.Top,
                        IDB_FEU+4*i+cv->Feu[v->NumFeu[i]-1].Etat);

  // 7a. On met l'étape le cas échéant et qqsoit l'affichage
  if (v->NumEtape)
   {
    ImageList8x8->Draw(DrawGridSimul->Canvas,
                       Rect.Left, Rect.Top,
                       IDB_ETAPE);
    ImageList8x8->Draw(DrawGridSimul->Canvas, // v2.2
                       Rect.Left, Rect.Top,
                       IDB_NUMETAPE+v->NumEtape-1);
   }
  // 7b. On met le dépôt le cas échéant et qqsoit l'affichage. v3.0
  if (v->EstDepotBus())
   ImageList8x8->Draw(DrawGridSimul->Canvas,
                      Rect.Left, Rect.Top,
                      IDB_DEPOTBUS);
  // 8. Affichage des directions possibles
  if (Affichage&aff_dir)
   for(int i=0; i<4; i++)
    if (v->DirPoss&PossDir[i+1])
     ImageList8x8->Draw(DrawGridSimul->Canvas,
                        Rect.Left, Rect.Top,
                        IDB_DIR+(IDB_DIRTD*v->ToutDroit)+i);
  // 9a. Trajet des lignes de bus. v3.0
  if (frmParamBus&&frmParamBus->Visible)
   {
    CoulTxt=clTeal;
    for(int i=0; i<NBMAXLIGNESBUSTRAM; i++)
     {
      CheckBox=(TCheckBox*)frmParamBus->FindComponent("CheckBox"+IntToStr(i+1));
      if (CheckBox->Visible&&CheckBox->Checked&&v->LigneBus[i])
       {
        DrawGridSimul->Canvas->Brush->Color=CoulLigneBusTram[i];
        DrawGridSimul->Canvas->FillRect(Rect);
        CoulTxt=CoulTLigneBusTram[i];
       }
     }
    if (v->EstTeteArretBus()&&(CoulTxt!=clTeal))
     {
      DrawGridSimul->Canvas->Font=DrawGridSimul->Font;
      DrawGridSimul->Canvas->Font->Color=CoulTxt;
      DrawGridSimul->Canvas->TextOut( Rect.Left+(Rect.Right-Rect.Left+1-DrawGridSimul->Canvas->TextWidth(IntToStr(v->NumArretBus)))/2,
                                      Rect.Top+(Rect.Bottom-Rect.Top+1-DrawGridSimul->Canvas->TextHeight(IntToStr(v->NumArretBus)))/2,
                                      IntToStr(v->NumArretBus));
     }
   }
  // 9b. Trajet des lignes de tram. v3.8. Un oubli !
  if (frmParamTram&&frmParamTram->Visible)
   {
    CoulTxt=clTeal;
    for(int i=0; i<NBMAXLIGNESBUSTRAM; i++)
     {
      CheckBox=(TCheckBox*)frmParamTram->FindComponent("CheckBox"+IntToStr(i+1));
      if (CheckBox->Visible&&CheckBox->Checked&&v->LigneTram[i])
       {
        DrawGridSimul->Canvas->Brush->Color=CoulLigneBusTram[i];
        DrawGridSimul->Canvas->FillRect(Rect);
        CoulTxt=CoulTLigneBusTram[i];
       }
     }
    if (v->EstTeteArretTram()&&(CoulTxt!=clTeal))
     {
      DrawGridSimul->Canvas->Font=DrawGridSimul->Font;
      DrawGridSimul->Canvas->Font->Color=CoulTxt;
      DrawGridSimul->Canvas->TextOut( Rect.Left+(Rect.Right-Rect.Left+1-DrawGridSimul->Canvas->TextWidth(IntToStr(v->NumArretTram)))/2,
                                      Rect.Top+(Rect.Bottom-Rect.Top+1-DrawGridSimul->Canvas->TextHeight(IntToStr(v->NumArretTram)))/2,
                                      IntToStr(v->NumArretTram));
     }
   }
  // 10. Case où est le curseur : on en profite pour rafraîchir l'état des ToolButtons
  if ((DrawGridSimul->Col==Col)&&(DrawGridSimul->Row==Row))
   {
    if ((xCrt!=Col)||(yCrt!=Row))
     { xPrc=xCrt; yPrc=yCrt; xCrt=Col; yCrt=Row; }
    if (v->ToutDroit) asMsg=asMsg+"Tout droit. ";
    for(int i=0; i<4; i++)
     if ((v->NumFeu[i])&&
         (cv->Feu[v->NumFeu[i]-1].x==Col)&&
         (cv->Feu[v->NumFeu[i]-1].y==Row)&&
         (cv->Feu[v->NumFeu[i]-1].Dir==i+1))
      asMsg=asMsg+Format("Feu %s %d. ", ARRAYOFCONST((asDir[i+1], v->NumFeu[i])));
    if (v->NumEtape)
     asMsg=asMsg+Format("Etape %d. ", ARRAYOFCONST((v->NumEtape)));
    if (v->EstDepotBus()) asMsg=asMsg+"Dépôt Bus. "; // v3.0
    if (v->NumArretBus) // v3.0
     {
      asListeLignes=cv->ArretBus[v->NumArretBus-1].asListeLignesBus(); // v3.1.1
      if (asListeLignes.IsEmpty())
       asMsg=asMsg+Format( "Arrêt bus %d %s. ", // ajout de "bus" pour différencier avec "tram" (v3.5)
                           ARRAYOFCONST(( v->NumArretBus,
                                          asAsterisque[v->EstTeteArretBus()]))); // v3.1 !!!
      else
       asMsg=asMsg+Format( "Arrêt bus %d %s (%s). ", // ajout de "bus" pour différencier avec "tram" (v3.5)
                           ARRAYOFCONST(( v->NumArretBus,
                                          asAsterisque[v->EstTeteArretBus()],
                                          asListeLignes))); // v3.1 !!!
     }
    if (v->NumArretTram) // v3.5
     {
      asListeLignes=cv->ArretTram[v->NumArretTram-1].asListeLignesTram();
      if (asListeLignes.IsEmpty())
       asMsg=asMsg+Format( "Arrêt tram %d %s. ",
                           ARRAYOFCONST(( v->NumArretTram,
                                          asAsterisque[v->EstTeteArretTram()])));
      else
       asMsg=asMsg+Format( "Arrêt tram %d %s (%s). ",
                           ARRAYOFCONST(( v->NumArretTram,
                                          asAsterisque[v->EstTeteArretTram()],
                                          asListeLignes)));
     }
    if (v->NumVehicule)
     if (NivPriorite=cv->Vehicule[v->NumVehicule-1].NivPriorite)
      asMsg=asMsg+Format("Véhicule %s %d. ", ARRAYOFCONST((asTypeVehicule[NivPriorite], v->NumVehicule)));
     else
      asMsg=asMsg+Format("Véhicule %d. ", ARRAYOFCONST((v->NumVehicule)));
    if (v->PassageBus) asMsg=asMsg+"Passage bus. ";
    if (v->NumBus) // v3.0
     asMsg=asMsg+Format("Bus %d%s ligne %d. ", ARRAYOFCONST((v->NumBus, asAsterisque[v->EstTeteBus()], cv->Bus[v->NumBus-1].NumLigne)));
    if (v->NumTram) // v3.5
     asMsg=asMsg+Format("Tram %d%s ligne %d. ", ARRAYOFCONST((v->NumTram, asAsterisque[v->EstTeteTram()], cv->Tram[v->NumTram-1].NumLigne)));
    if (v->PassagePietons) asMsg=asMsg+"Passage piétons. ";
    if (v->NbPietons) // v2.0
     {
      asMsg=asMsg+"Piéton";
      if (v->NbPietons>1) asMsg=asMsg+"s";
      for(int i=0; i<NBMAXPIETONSPARCASE; i++)
       if (v->NumPieton[i])
        asMsg=asMsg+Format(" %d%s", ARRAYOFCONST(( v->NumPieton[i],
                                                   asSupInf[(!cv->Pieton[v->NumPieton[i]-1].Ecrase)*(1+cv->Pieton[v->NumPieton[i]-1].DemiCase)]+ // v4.3 (asSupInf remplace as12)
                                                   asMort[cv->Pieton[v->NumPieton[i]-1].Ecrase]))); // v4.3
      asMsg=asMsg+". ";
     }
    if (v->NumPlaceTaxi) // v3.6
     asMsg=asMsg+Format("Place Taxi %d%s%s. ", ARRAYOFCONST(( v->NumPlaceTaxi,
                                                              asSupInf[v->EstTeteFileTaxis()], // v4.3 (asSupInf remplace as12)
                                                              asSupInf[2*v->EstQueueFileTaxis()]))); // v4.3 (asSupInf remplace as12)
    if (v->NumTaxi) // v3.6
     asMsg=asMsg+Format("Véh.Taxi %d. ", ARRAYOFCONST((v->NumTaxi)));

    if (StatsAttenteTrafic&&frmStatsAttenteTrafic) // v3.0 : Affichage du détail des statistiques de fluidité det de trafic
     StatusBar->Panels->Items[0]->Text=frmStatsAttenteTrafic->asMsgDetailCase(Col, Row);
    StatusBar->Panels->Items[1]->Text=asMsg;
    StatusBar->Panels->Items[2]->Text=asDirPoss[v->DirPoss];
    StatusBar->Panels->Items[3]->Text=Format(asFormatCoord, ARRAYOFCONST((Col, Row)));
    if ((!SelectionFeuxDmd)&&(!SelectionFeuxAtt)) // Pas de curseur en sélection de feux
     ImageList8x8->Draw(DrawGridSimul->Canvas,
                        Rect.Left, Rect.Top,
                        IDB_CURSEUR);

    // Directions (Routes)
    NordPoss=((v->DirPoss&N)==N);
    EstPoss=((v->DirPoss&E)==E);
    OuestPoss=((v->DirPoss&O)==O);
    SudPoss=((v->DirPoss&S)==S);

    ActionDirectionHaut->Checked=NordPoss;
    ActionDirectionHaut->Enabled= ((!v->PassageBus)||(!NordPoss))&& // Interdit de retirer une direction si passage bus. v3.5
                                  (!v->Priorite[nord-1])&&
                                  (!(v->SensVoieTram&nord_sud))&& // Si une voie dans le même sens // v3.5
                                  ChgmtDirRoutesAutorise;
    ActionDirectionDroite->Checked=EstPoss;
    ActionDirectionDroite->Enabled= ((!v->PassageBus)||(!EstPoss))&& // Interdit de retirer une direction si passage bus. v3.5
                                    (!v->Priorite[est-1])&&
                                    (!(v->SensVoieTram&est_ouest))&&
                                    ChgmtDirRoutesAutorise;
    ActionDirectionBas->Checked=SudPoss;
    ActionDirectionBas->Enabled= ((!v->PassageBus)||(!SudPoss))&& // Interdit de retirer une direction si passage bus. v3.5
                                 (!v->Priorite[sud-1])&&
                                 (!(v->SensVoieTram&nord_sud))&&
                                 ChgmtDirRoutesAutorise;
    ActionDirectionGauche->Checked=OuestPoss;
    ActionDirectionGauche->Enabled= ((!v->PassageBus)||(!OuestPoss))&& // Interdit de retirer une direction si passage bus. v3.5
                                    (!v->Priorite[ouest-1])&&
                                    (!(v->SensVoieTram&est_ouest))&&
                                    ChgmtDirRoutesAutorise;

    ActionEffacerRoute->Enabled=ChgmtDirRoutesAutorise;

    // Directions (Voies Tram)
    ActionDirectionHautTram->Enabled=ChgmtDirVoiesAutorise&&(!(v->DirPoss&NS));
    ActionDirectionDroiteTram->Enabled=ChgmtDirVoiesAutorise&&(!(v->DirPoss&EO));
    ActionDirectionBasTram->Enabled=ChgmtDirVoiesAutorise&&(!(v->DirPoss&NS));
    ActionDirectionGaucheTram->Enabled=ChgmtDirVoiesAutorise&&(!(v->DirPoss&EO));
    ActionEffacerVoieTram->Enabled=ChgmtDirVoiesAutorise;

    // Autres Eléments
    ActionToutDroit->Checked=v->ToutDroit;

    ActionEtape->Checked=(v->NumEtape>0);
    ActionEtape->Enabled=(!v->EstDepotBus())&&
                         (!(v->Priorite[0]+v->Priorite[1]+v->Priorite[2]+v->Priorite[3]))&&
                         (NbDir[v->DirPoss]<4)&&
                         EditionAutorisee;

    // v3.0
    ActionDepotBus->Checked=v->EstDepotBus();
    ActionDepotBus->Enabled=(!v->NumEtape)&&
                            (!(v->Priorite[0]+v->Priorite[1]+v->Priorite[2]+v->Priorite[3]))&&
                            (NbDir[v->DirPoss]>0)&&
                            EditionAutorisee;

    // v2.0
    ActionPassagePietons->Checked=v->PassagePietons;
    ActionPassagePietons->Enabled=(!!Sens)&&EditionAutorisee;

    // v3.5: bouton commun entre bus et trams
    ActionArretBusTram->Checked=(v->NumArretBus>0)||(v->NumArretTram>0);
    // v3.6: Places de Taxi (exclusif avec Bus/tram)
    ActionPlaceTaxi->Checked=(v->NumPlaceTaxi>0);
    ActionPlaceTaxi->Enabled=v->DirPoss&&(!v->NumArretBus)&&(!v->NumArretTram)&&EditionAutorisee; // v3.6.1
    switch((v->NumArretBus>0)+2*(v->NumArretTram>0))
     {
      case BUS: ActionArretBusTram->Enabled=(!v->NumPlaceTaxi)&&cv->SuppressionArretBusPossible(Col, Row)&&EditionAutorisee; // v3.6
                break;
      case TRAM:ActionArretBusTram->Enabled=(!v->NumPlaceTaxi)&&cv->SuppressionArretTramPossible(Col, Row)&&EditionAutorisee; // v3.6
                break;
      default:  switch((v->DirPoss>aucune)+2*(v->SensVoieTram>aucune_voie))
                 {
                  case BUS: ActionArretBusTram->Enabled=(!v->NumPlaceTaxi)&&cv->AjoutArretBusPossible(Col, Row)&&EditionAutorisee; // v3.6
                            break;
                  case TRAM:ActionArretBusTram->Enabled=(!v->NumPlaceTaxi)&&cv->AjoutArretTramPossible(Col, Row)&&EditionAutorisee; // v3.6
                            break;
                  default:  ActionArretBusTram->Enabled=false;
                 }
     }
    // v3.1
    ActionPassageBus->Checked=v->PassageBus;
    ActionPassageBus->Enabled=(v->DirPoss>aucune)&&EditionAutorisee;
    ActionMarche->Enabled=(!DefFeux)&&(!SimulationEnCours);
    ActionPriorites->Enabled=(!v->NumEtape)&&EditionAutorisee;

    ActionSuivreVehicule->Enabled=(v->NumVehicule>0);
    ActionSuivreBus->Enabled=(v->NumBus>0); // v3.0
    ActionSuivrePieton1->Enabled=(v->NumPieton[0]>0); // v3.0
    ActionSuivrePieton2->Enabled=(v->NumPieton[1]>0); // v3.0
    ActionSuivreTram->Enabled=(v->NumTram>0); // v3.6
    ActionSuivreTaxi->Enabled=(v->NumTaxi>0); // v3.6

    ActionDistancesEtapes->Enabled=(v->DirPoss>aucune); // v3.5
    ActionDistancesArretsBus->Enabled=(v->DirPoss>aucune); // v3.5
    ActionDistancesArretsTram->Enabled=(v->SensVoieTram>aucune_voie); // v3.5
    ActionDistancesFilesTaxi->Enabled=(v->DirPoss>aucune); // v3.6
    ActionDeplacerFeuSource->Enabled= (DeplacementFeuEnCours||  // v3.5
                                      (v->Priorite[0]==feux)||
                                      (v->Priorite[1]==feux)||
                                      (v->Priorite[2]==feux)||
                                      (v->Priorite[3]==feux))&&
                                      EditionAutorisee;
    ActionDeplacerFeuDestination->Enabled=ActionDeplacerFeuSource->Enabled;
    // v3.9 (décors)
    ActionNatureTrottoir->Checked=(NATURE(v)==trottoirs);
    ActionDecorsArbre->Enabled=(NATURE(v)==trottoirs);
    ActionDecorsArbre->Checked=(v->Nature==arbre);
    ActionDecorsPelouse->Enabled=(NATURE(v)==trottoirs);
    ActionDecorsPelouse->Checked=(v->Nature==pelouse);
    ActionNatureImmeuble->Checked=(NATURE(v)==immeubles);
   }

  // 8. Case illustrée par un message
  if ((!SelectionFeuxDmd)&&(!SelectionFeuxAtt)&&
      (xErr==Col)&&(yErr==Row)&&
      TimerClignotementErreur->Enabled&&TimerClignotementErreur->Tag) // v3.5
   ImageList8x8->Draw(DrawGridSimul->Canvas,
                      Rect.Left, Rect.Top,
                      IDB_CURSERR);

  // 9. feux sélectionnés depuis la fenêtre de définition d'un feu
  if (SelectionFeuxDmd)
   for(int i=0; i<frmDefFeux->NbFeuxDmd; i++)
    if ((cv->Feu[frmDefFeux->NumFeuxDmd[i]-1].x==Col)&&
        (cv->Feu[frmDefFeux->NumFeuxDmd[i]-1].y==Row))
     ImageList8x8->Draw(DrawGridSimul->Canvas,
                        Rect.Left, Rect.Top,
                        IDB_SELFEU+cv->Feu[frmDefFeux->NumFeuxDmd[i]-1].Dir-1);
  if (SelectionFeuxAtt)
   for(int i=0; i<frmDefFeux->NbFeuxAtt; i++)
    if ((cv->Feu[frmDefFeux->NumFeuxAtt[i]-1].x==Col)&&
        (cv->Feu[frmDefFeux->NumFeuxAtt[i]-1].y==Row))
     ImageList8x8->Draw(DrawGridSimul->Canvas,
                        Rect.Left, Rect.Top,
                        IDB_SELFEU+cv->Feu[frmDefFeux->NumFeuxAtt[i]-1].Dir-1);
  if ((Colonnes>1)||(Lignes>1))
   {
    StatusBar->Panels->Items[0]->Text=Format( "Sélection en cours : %d colonne(s) et %d ligne(s)",
                                              ARRAYOFCONST((Colonnes, Lignes)));
    if (DrawGridSimul->PopupMenu==PopupMenuEditionCase) // v3.5
     {
      DrawGridSimul->PopupMenu=PopupMenuEditionSelection;
      RafraichitActionsEdition(meSelection);
     }
   }
  else
   {
    if (StatusBar->Panels->Items[0]->Text.Pos("Sélection en cours"))
     StatusBar->Panels->Items[0]->Text="";
    if (DrawGridSimul->PopupMenu==PopupMenuEditionSelection) // v3.5
     {
      DrawGridSimul->PopupMenu=PopupMenuEditionCase;
      RafraichitActionsEdition(meCase);
     }
   }
 }
//---------------------------------------------------------------------------
void TfrmSimulation::InitialiseDeplacementFeu() // v3.5
 {
  DeplacementFeuEnCours=false;
  xDeplFeu=-1; yDeplFeu=-1;
  RafraichitFonctionDeplacementFeu();
 }
//---------------------------------------------------------------------------
void TfrmSimulation::RafraichitFonctionDeplacementFeu() // v3.5
 {
  MenuItemDeplacerFeu->Action=DeplacementFeuEnCours?ActionDeplacerFeuDestination:ActionDeplacerFeuSource;
  ToolButtonDeplacerFeu->Action=DeplacementFeuEnCours?ActionDeplacerFeuDestination:ActionDeplacerFeuSource;
 }
//---------------------------------------------------------------------------
void TfrmSimulation::RedimensionneZone()
 {
  DrawGridSimul->ColCount=cv->NbX;
  DrawGridSimul->RowCount=cv->NbY;
#ifdef CV_WINDOWS
  Width=8*cv->NbX+(Width-DrawGridSimul->Width); // v4.0.1
  Height=8*cv->NbY+(Height-DrawGridSimul->Height); // v4.0.1
  DrawGridSimul->Repaint(); // v4.0.1
#endif
 }
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::FormCreate(TObject *Sender)
{ // Initialise les indicateurs et la base de registres (Windows uniquement)
#ifdef CV_WINDOWS
 ImageList8x8=ImageList8x8x1;
 TRegistry *Reg;
#endif
#ifdef CV_LINUX
 ImageList8x8=ImageList8x8x2; // ImageList8x8x1 est vide
#endif
 Affichage=(affichage)(aff_sign|aff_voie|aff_env); // v3.8.1 (aff_env)
 xErr=-1; yErr=-1;
 Pause=false; // v3.5
 SimulEnCours=false;
 SimulModifiee=false;
 EnregistrerAvant=false;
 RedimensionnementEnCours=false; // v3.5.1
 InitialiseDeplacementFeu();
#ifdef CV_WINDOWS
 // On contrôle la base de registre sur le lien avec les fichiers de simulation
 if (Reg=new TRegistry)
  {
   try
    {
     Reg->RootKey=HKEY_CLASSES_ROOT;
     if (!(Reg->KeyExists(asCleExtCvw)))
      {
       Reg->OpenKey(asCleExtCvw, true);
       Reg->WriteString(asVide, asCvw);
       Reg->CloseKey();
      }
     Reg->OpenKey(asCleCvw, true);
     Reg->WriteString(asVide, "Simulation Centre-Ville");
     Reg->OpenKey("DefaultIcon", true);
     Reg->WriteString(asVide, ParamStr(0)+",1");
     Reg->OpenKey("\\Cvw\\shell", true);
     Reg->OpenKey("open", true);
     Reg->OpenKey("command", true);
     Reg->WriteString(asVide, ParamStr(0)+AnsiString(" \"%1\""));
     Reg->CloseKey();
     Reg->CloseKey();
     Reg->CloseKey();
     Reg->CloseKey();
     Reg->CloseKey();
    }
   catch(...)
    {
     AfficheMessage("Impossible d'ouvrir et/ou de mettre à jour la base de registres", asTitreCV, tmErreur, 0, 0);
    }
   delete Reg;
  }
 else
  AfficheMessage("Mémoire insuffisante pour ouvrir la base de registres", asTitreCV, tmErreur, 0, 0);
 frmAPropos=new TfrmAPropos(this);
#endif
 cv=new centre_ville(NB_ELEMENTS_PAR_DEFAUT,NBXDEF,NBYDEF);
 // RedimensionneZone(); // Inutile ici
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::FormDestroy(TObject *Sender)
{
 if (cv) { delete cv; cv=NULL; }
#ifdef CV_WINDOWS
 if (frmAPropos) delete frmAPropos;
#endif
}
//---------------------------------------------------------------------------
bool TfrmSimulation::EnregistreModificationsAvant(operation_avant Operation)
 {
  type_reponse mrRep;
  AnsiString asMessage;
  if (!SimulationModifiee) return true; // Inutile car pas de modif
  switch(Operation)
   {
    case oaNouveau: asMessage=asQstEnregistrerFichier+
                              FILENAME(SaveDialog)+" avant de créer une nouvelle simulation ?";
                    break;
    case oaOuvrir:  asMessage=asQstEnregistrerFichier+
                              FILENAME(SaveDialog)+" avant d'ouvrir une autre simulation ?";
                    break;
    case oaQuitter: asMessage=asQstEnregistrerFichier+
                              FILENAME(SaveDialog)+" avant de quitter ?";
                    break;
   }
  mrRep=AfficheMessage( asMessage, "Confirmation", tmQuestionFacultative, 0, 2); // Défaut = Oui, Echap = Annuler
  switch(mrRep)
   {
    case trOui: EnregistrerAvant=true;
                ActionEnregistrer->Execute();
                // Enregistrement annulé : on annule la création
                if (!EnregistrerAvant) return false;
    case trNon: if (EnregistrerAvant)
                 EnregistrerAvant=false;
                return true;
    default: return false;
   }
 }
//---------------------------------------------------------------------------

bool TfrmSimulation::ModifiePassagePietonsSiNecessaire(int x, int y) // v2.0
 {
  if (cv->v[x][y].SupprimePassagePietonsInvalide()) // v3.5
   {
    SimulationModifiee=true;
    RedessineCase(x%cv->NbX, y%cv->NbY, true);
    return true;
   }
  else return false;
 }
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::DrawGridSimulDblClick(TObject *Sender)
{
 const NumSvtOrdSel[2][4]={{0,0,1,0},{1,1,1,1}};
 int x=DrawGridSimul->Col,
     y=DrawGridSimul->Row,
     i, j, NbFeux, *NumFeu,// Variables de transition
     NumFeuVoie[2]={0,0}, // Numéros de feux de la voie {Prm,Drn}
     NbFeuxListe, // Nombre de feux de la liste frmDefFeux->NumFeux...
     NbFeuxVoie=0, // Nombre de feux dans la voie v[Col][Row]
     NbNonSel, // Compteur du nombre de feux non sélectionnés
     Selection[2]={0,0}; // 0=Aucun;1=Prm;2=Drn;3=Prm+Drn (Anc,Nv)
 // Traite le clic sur la case avec des feux lors d'une sélection de feux :
 // 2 feux = passage de aucun à feu1, de feu1 à feu2,
 //                  de feu2 à feu1+feu2 et de feu1+feu2 à aucun.
 // 1 feu = passage de aucun à feu1, de feu1 à aucun
 voie *v=&(cv->v[x][y]);

 if (v->NumEtape&&ActionEtape->Enabled)
  {
   ActionEtape->Execute();
   return;
  }

 if (!(SelectionFeuxDmd||SelectionFeuxAtt))
  {
   frmDefVoie->RafraichitInfos();
   if ((!ActionPriorites->Checked)&&
       ActionPriorites->Enabled)
    frmDefVoie->Show();
   return;
  }

 // Calcul du nombre et des numéros de feux de la voie
 for(i=0; i<4; i++)
  if (v->NumFeu[i]>0) NumFeuVoie[NbFeuxVoie++]=v->NumFeu[i];

 // Attention : les listes sont exclusives à la sélection donc pas d'initialisation entre les 2

 // Calcul de la nouvelle liste NumFeuxDmd
 if (SelectionFeuxDmd)
  {
   NbFeuxListe=frmDefFeux->NbFeuxDmd;
   // Sélection courante
   for(i=0; i<NbFeuxListe; i++)
    for(j=0; j<NbFeuxVoie; j++)
     if (frmDefFeux->NumFeuxDmd[i]==NumFeuVoie[j])
      Selection[0]+=(j+1);

   // Sélection suivante selon la règle ci-dessus
   if (NbFeuxVoie)
    Selection[1]=(Selection[0]+1)%(2*NbFeuxVoie);

   // Génération de la liste                                     Selection  Nombre
   NbFeux=NbFeuxListe+(Selection[1]+1)/2-(Selection[0]+1)/2; // (0,1,2,3)->(0,1,1,2) : f(s)=(s+1)/2
   if (!(NumFeu=new int[NbFeux]))
    {
     AfficheMessage(asMemInsuff, asErrInattendue, tmErreur, 0, 0);
     RedessineCase(x, y, true);
     return;
    }
   NbNonSel=0;
   for(i=0; i<NbFeuxListe; i++) // On recopie déjà les feux de la précédente liste
    {
     NumFeu[i-NbNonSel]=frmDefFeux->NumFeuxDmd[i];
     for(j=0; j<NbFeuxVoie; j++)
      NbNonSel+=(frmDefFeux->NumFeuxDmd[i]==NumFeuVoie[j])&&(!(j&Selection[1]));
    }
   for(i=NbFeuxListe-NbNonSel; i<NbFeux; i++) // Cas de recopie d'une nouvelle sélection
    NumFeu[i]=NumFeuVoie[NumSvtOrdSel[i-NbFeuxListe+NbNonSel][Selection[1]]];

   // Changement de liste
   if (frmDefFeux->NumFeuxDmd)
    {
     delete[] frmDefFeux->NumFeuxDmd;
     frmDefFeux->NumFeuxDmd=NULL;
    }
   frmDefFeux->NumFeuxDmd=NumFeu;
   frmDefFeux->NbFeuxDmd=NbFeux;
   frmDefFeux->RafraichitInfosFeuxDmd();
   RedessineCase(x, y, true);
  }

 // Calcul de la nouvelle liste NumFeuxAtt
 if (SelectionFeuxAtt)
  {
   NbFeuxListe=frmDefFeux->NbFeuxAtt;
   // Sélection courante
   for(i=0; i<NbFeuxListe; i++)
    for(j=0; j<NbFeuxVoie; j++)
     if (frmDefFeux->NumFeuxAtt[i]==NumFeuVoie[j])
      Selection[0]+=(j+1);

   // Sélection suivante selon la règle ci-dessus
   if (NbFeuxVoie)
    Selection[1]=(Selection[0]+1)%(2*NbFeuxVoie);

   // Génération de la liste                                     Selection  Nombre
   NbFeux=NbFeuxListe+(Selection[1]+1)/2-(Selection[0]+1)/2; // (0,1,2,3)->(0,1,1,2) : f(s)=(s+1)/2
   if (!(NumFeu=new int[NbFeux]))
    {
     AfficheMessage(asMemInsuff, asErrInattendue, tmErreur, 0, 0);
     RedessineCase(x, y, true);
     return;
    }
   NbNonSel=0;
   for(i=0; i<NbFeuxListe; i++) // On recopie déjà les feux de la précédente liste
    {
     NumFeu[i-NbNonSel]=frmDefFeux->NumFeuxAtt[i];
     for(j=0; j<NbFeuxVoie; j++)
      NbNonSel+=(frmDefFeux->NumFeuxAtt[i]==NumFeuVoie[j])&&(!(j&Selection[1]));
    }
   for(i=NbFeuxListe-NbNonSel; i<NbFeux; i++) // Cas de recopie d'une nouvelle sélection
    NumFeu[i]=NumFeuVoie[NumSvtOrdSel[i-NbFeuxListe+NbNonSel][Selection[1]]];

   // Changement de liste
   if (frmDefFeux->NumFeuxAtt)
    {
     delete[] frmDefFeux->NumFeuxAtt;
     frmDefFeux->NumFeuxAtt=NULL;
    }
   frmDefFeux->NumFeuxAtt=NumFeu;
   frmDefFeux->NbFeuxAtt=NbFeux;
   frmDefFeux->RafraichitInfosFeuxAtt();
   RedessineCase(x, y, true);
  }
}
//---------------------------------------------------------------------------
bool TfrmSimulation::VerifieReseau()
 {
  bool Ok=true;
  int i, j, d,
      NbDirPossSansPsgBus, // v3.5
      NbCasesPietonPeutAller=0; // v3.8
  const AnsiString asMsgOk="Réseau correct.";
  AnsiString asMsgErr;
  dirposs dp;
  voie *v, *vv;
  cv->VerifOk=false;
  // On enleve le clignotement si actif. v3.5
  if (TimerClignotementErreur->Enabled) TimerClignotementErreur->Enabled=false;
  if ((xErr>-1)&&(yErr>-1)) RedessineCase(xErr, yErr, true);
  xErr=-1; yErr=-1;
  for(i=0; Ok&&(i<cv->NbEtapes); i++) // v3.0
   if (!(Ok=cv->Etape[i].Definie()))
    asMsgErr=Format( "L'étape n°%d n'est pas définie. Les %d étapes doivent être définies.",
                     ARRAYOFCONST((i+1, cv->NbEtapes)));
  for(i=0; Ok&&(i<NBMAXLIGNESBUSTRAM); i++)
   for(j=0; Ok&&(j<NBMAXARRETSBUSTRAMPARLIGNE); j++)
    {
     if (j<cv->LigneBus[i].NbArrets) // v3.5 : Oubli du test du nombre d'arrêts
      if (!(Ok=cv->ArretBus[cv->LigneBus[i].NumArret[j]-1].Defini()))
       {
        asMsgErr=Format( "La ligne de bus n°%d utilise l'arrêt n°%d qui n'est pas défini.",
                         ARRAYOFCONST((i+1, cv->LigneBus[i].NumArret[j])));
        break;
       }
     if (j<cv->LigneTram[i].NbArrets) // v3.5 : Oubli du test du nombre d'arrêts
      if (!(Ok=cv->ArretTram[cv->LigneTram[i].NumArret[j]-1].Defini()))
       {
        asMsgErr=Format( "La ligne de tram n°%s utilise l'arrêt n°%d qui n'est pas défini.",
                         ARRAYOFCONST((AnsiString((char)('A'+i)), cv->LigneTram[i].NumArret[j])));
        break;
       }
    }
  for(i=0; Ok&&(i<cv->NbArretsBus); i++)
   if (cv->ArretBus[i].Defini())
    if (!(Ok=(cv->v[cv->ArretBus[i].x][cv->ArretBus[i].y].NumArretBus==i+1)))
     { // v3.0.3
      xErr=cv->ArretBus[i].x; yErr=cv->ArretBus[i].y;
      asMsgErr=Format( "La tête de l'arrêt de bus n°%d n'est pas définie ou est incorrecte.",
                       ARRAYOFCONST((i+1)));
      break;
     }
  for(i=0; Ok&&(i<cv->NbArretsTram); i++)
   if (cv->ArretTram[i].Defini())
    if (!(Ok=(cv->v[cv->ArretTram[i].x][cv->ArretTram[i].y].NumArretTram==i+1)))
     { // v3.0.3
      xErr=cv->ArretTram[i].x; yErr=cv->ArretTram[i].y;
      asMsgErr=Format( "La tête de l'arrêt de tram n°%d n'est pas définie ou est incorrecte.",
                       ARRAYOFCONST((i+1)));
      break;
     }
  if (Ok&&(cv->NbArretsBus>0)&&(cv->NbLignesBus>0))  // v3.0
   if (!(Ok=cv->DepotBus.Defini()))
    asMsgErr="Si des arrêts et des lignes de bus sont définis, un dépôt de bus est obligatoire.";
   else
    {
     if (!(Ok=(cv->v[cv->DepotBus.x][cv->DepotBus.y].DirPoss>aucune)))
      {
       xErr=cv->DepotBus.x; yErr=cv->DepotBus.y;
       asMsgErr="Un dépôt de bus doit avoir au moins une direction possible vers l'extérieur.";
      }
     for(d=nord; Ok&&(d<=ouest); d++)
      if (!(Ok=!(cv->V(cv->DepotBus.x, cv->DepotBus.y, d).DirPoss&InvPossDir[d])))
       {
        xErr=(cv->DepotBus.x+dx[d])%cv->NbX; yErr=(cv->DepotBus.y+dy[d])%cv->NbY;
        asMsgErr="On ne peut diriger une case vers le dépôt de bus (il est en SORTIE SEULE).";
       }
    }
  for(i=0; Ok&&(i<cv->NbX); i++)
   for(j=0; Ok&&(j<cv->NbY); j++)
    {
     v=&(cv->v[i][j]);
     NbDirPossSansPsgBus=0; // v3.5
     for(d=nord; Ok&&(d<=ouest); d++)
      if ((v->DirPoss&PossDir[d])==PossDir[d])
       {
        vv=&(cv->V(i,j,d));
        NbDirPossSansPsgBus+=!vv->PassageBus;
        dp=vv->DirPoss;
        if (dp==InvPossDir[d])
         {
          Ok=false; xErr=i; yErr=j;
          asMsgErr=Format("Demi-tour obligé entre les cases (%d, %d) et (%d, %d).",
                          ARRAYOFCONST((i, j, (i+dx[d])%cv->NbX, (j+dy[d])%cv->NbY)));
          break;
         }
        if (!dp)
         {
          Ok=false; xErr=i; yErr=j;
          asMsgErr=Format("La case (%d, %d) pointe sur (%d, %d) qui n'a aucune direction possible.",
                          ARRAYOFCONST((i, j, (i+dx[d])%cv->NbX, (j+dy[d])%cv->NbY)));
          break;
         }
        if ((!v->PassageBus)&& // Si ce n'est pas un passage réservé aux bus ET
            v->ToutDroit&& // il y a obligation d'aller tout droit ET
            vv->PassageBus&& // la case voisine est réservée aux bus ET
            (cv->V(i,j,InvDir[d]).DirPoss&PossDir[d])&& // On peut venir de la case opposée
            (!cv->V(i,j,InvDir[d]).PassageBus)) // qui n'est pas réservé aux bus ALORS...
         { // ...Il y a possibilité de blocage. v3.5
          Ok=false; xErr=i; yErr=j;
          asMsgErr=Format("L'obligation d'aller tout droit sur la case (%d, %d) oblige à aller sur le passage bus %s.",
                          ARRAYOFCONST((i, j, asDir[d])));
          break;
         }
       }
     if (!Ok) break; // v3.5 (oubli !)
     if (v->DirPoss&&
         (!v->PassageBus)&&
         (!NbDirPossSansPsgBus)) // v3.5
      {
       Ok=false; xErr=i; yErr=j;
       asMsgErr=Format("La case (%d, %d) n'a aucune direction possible en dehors des passages de bus.",
                       ARRAYOFCONST((i, j)));
       break;
      }
     if (v->NumEtape)
      {
       if (!v->DirPoss)
        {
         Ok=false; xErr=i; yErr=j;
         asMsgErr=Format("La case (%d, %d) est une étape mais n'a aucune direction possible.",
                         ARRAYOFCONST((i, j)));
         break;
        }
       for(d=nord; (d<=ouest)&&(!(cv->V(i,j,d).DirPoss&InvPossDir[d])); d++);
       if (d>ouest)
        {
         Ok=false; xErr=i; yErr=j;
         asMsgErr=Format("La case (%d, %d) est une étape mais il est impossible d'y accéder.",
                         ARRAYOFCONST((i, j)));
         break;
       }
      }
     if (v->NumArretBus) // v3.0
      {
       for(Ok=false, d=nord; (!Ok)&&(d<=ouest); d++)
        Ok=(cv->V(i,j,d).NumArretBus==v->NumArretBus);
       if (!Ok)
        {
         xErr=i; yErr=j;
         asMsgErr=Format("L'arrêt de bus n°%d n'est défini que sur la case (%d, %d).", ARRAYOFCONST((v->NumArretBus, i, j)));
         break;
        }
      }
     if (v->NumArretTram) // v3.5
      {
       for(Ok=false, d=nord; (!Ok)&&(d<=ouest); d++)
        Ok=(cv->V(i,j,d).NumArretTram==v->NumArretTram);
       if (!Ok)
        {
         xErr=i; yErr=j;
         asMsgErr=Format("L'arrêt de tram n°%d n'est défini que sur la case (%d, %d).", ARRAYOFCONST((v->NumArretTram, i, j)));
         break;
        }
      }
     if ((v->PassagePietons)&&(!cv->SensPassagePietonsPossible(i, j)))
      {
       Ok=false; xErr=i; yErr=j;

       asMsgErr=Format("Le passage piétons sur la case (%d, %d) ne peut avoir de sens. Il a été retiré.", ARRAYOFCONST((i, j)));
       v->PassagePietons=false;
       SimulationModifiee=true;
       break;
      }
     if (v->NumPlaceTaxi&&v->ExistePlusieursQueuesFileTaxis()) // v3.6
      {
       Ok=false; xErr=i; yErr=j;
       asMsgErr=Format("Plusieurs files de taxis sont dirigées sur la place de taxi de la case (%d, %d).", ARRAYOFCONST((i, j)));
       break;
      }
     if (v->NumPlaceTaxi&&v->ExistePlusieursTetesFileTaxis()) // v3.6
      {
       Ok=false; xErr=i; yErr=j;
       asMsgErr=Format("La place de taxi de la case (%d, %d) pointe sur plus d'une file de taxis.", ARRAYOFCONST((i, j)));
       break;
      }
     // Vérification du nombre de cases potentielles avec 1 piéton par case minimum. v3.8
     for(d=nord; (!v->PietonPeutAller((direction)d))&&(d<=ouest); d++);
     NbCasesPietonPeutAller+=(d<=ouest);
    }
  if (Ok&&(NbCasesPietonPeutAller<cv->NbPietons)) // v4.2
   {
    Ok=false;
    asMsgErr=Format("Il n'y a pas assez de place pour %d piétons (%d possibles). Ajoutez des trottoirs.", ARRAYOFCONST((cv->NbPietons, NbCasesPietonPeutAller)));
   }
  StatusBar->Panels->Items[0]->Text=(cv->VerifOk=Ok)?asMsgOk:asMsgErr;
  if ((xErr>-1)&&(yErr>-1))
   TimerClignotementErreur->Enabled=true;
  Cursor=crDefault;
  return Ok;
 }
//---------------------------------------------------------------------------
void TfrmSimulation::AfficheMsgInfoNonDisp(const AnsiString asTitre) // v3.7 (char* -> const AnsiString)
 {
  AfficheMessage("Aucune information n'est disponible.", asTitre, tmAvertissement, 0, 0);
 }
//---------------------------------------------------------------------------
void TfrmSimulation::AfficheBilan()
 {
  int i, j, d, ndp, MinDist,
      xe, ye,
      ne=cv->NbEtapes, // NbEtapes
      nv=cv->NbVehicules, // NbVehicules
      nva=cv->NbVehiculesArrives, // NbVehiculesArrivés
      nvpe=nv/ne, // NbVehiculesParEtape
      ParcoursMin=0L, AttenteDepart=0L,
      ntp=cv->NbToursParcourus,
      ncp=cv->NbCasesParcourues;
  double m;
  AnsiString asMsgBilan;
  // 1. On calcule le parcours moyen
  for(i=0; i<ne; i++)
   for(j=0; j<ne; j++)
    if (i!=j)
     {
      xe=cv->Etape[i].x; ye=cv->Etape[i].y;
      MinDist=DIST_INDEFINIE; ndp=NbDir[cv->v[xe][ye].DirPoss];
      for(d=0; d<ndp; d++)
       MinDist=min(MinDist, cv->v[xe][ye].DistEtape[j][d][SANSPSGBUS]); // v3.5 (SANSPSGBUS)
      ParcoursMin+=MinDist;
     }
  m=(1.0*ParcoursMin)/ne/(ne-1);
  // 2. Calcul du temps d'attente de départ
  for(i=0; i<nv; i++)
   if (!cv->Vehicule[i].Defini())
    AttenteDepart+=cv->Vehicule[i].TourDepart-1;
  // 3. Affichage du bilan
  if (nva)
   asMsgBilan=Format( asFormatBilan,
                      ARRAYOFCONST(( nv,
                                     m, m,
                                     nvpe-3,
                                     cv->TourCrt,
                                     Format( "%s (%.2f tour(s)/s, %.2f ms/tour)",
                                             ARRAYOFCONST(( FormatDateTime("hh:nn:ss.zzz", cv->dtTemps), // v3.9.2
                                                            (double)(cv->TourCrt/(24*3600*((double)cv->dtTemps))), // v3.9.2
                                                            (double)((24L*3600000L*((double)cv->dtTemps))/cv->TourCrt)))), // v3.9.2
                                     nva, (100.0*nva)/nv,
                                     (1.0*ncp)/nva, (100.0*ncp)/nva/m,
                                     (1.0*AttenteDepart)/nva, (100.0*AttenteDepart)/nva/(nvpe-3),
                                     (1.0*ntp)/nva, (100.0*ntp)/nva/m,
                                     (1.0*ncp)/nva, (100.0*ncp)/ntp,
                                     (1.0*(ntp-ncp))/nva, (100.0*(ntp-ncp))/ntp)));
  else
   asMsgBilan=Format( asFormatBilanSansArrives,
                      ARRAYOFCONST(( nv,
                                     m, m,
                                     nvpe-3,
                                     cv->TourCrt,
                                     Format( "%s (%.2f tour(s)/s, %.2f ms/tour)",
                                             ARRAYOFCONST(( FormatDateTime("hh:nn:ss.zzz", cv->dtTemps), // v3.9.2
                                                            (double)(cv->TourCrt/(24*3600*((double)cv->dtTemps))), // v3.9.2
                                                            (double)((24L*3600000L*((double)cv->dtTemps))/cv->TourCrt))))))); // v3.9.2
  if (AfficheMessage(asMsgBilan, "Bilan", tmQuestionNecessaire, 0, 1)==trOui) // Défaut = Oui, Echap = Non
   AfficheStatsAttenteTrafic();
 }
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::FormShow(TObject *Sender)
{
 SimulEnCours=true;
 TypeDemande=tdRien;
#ifdef CV_WINDOWS
 frmAPropos->FermetureAutomatique=true;
 frmAPropos->Show();
 frmAPropos->ImageVersion->Repaint();
 frmAPropos->LabelCV2->Repaint();
 frmAPropos->LabelCV1->Repaint();
 frmAPropos->LabelAuteur2->Repaint();
 frmAPropos->LabelAuteur1->Repaint();
 frmAPropos->LabelTexte->Repaint();
 frmAPropos->LabelSousVersion->Repaint(); // v2.2.4
 frmAPropos->LabelURL->Repaint();
 frmAPropos->LabelEMail->Repaint();
#endif 
 SimulEnCours=false;
 SelectionFeuxDmd=false;
 SelectionFeuxAtt=false;
 StatsAttenteTrafic=false; // v2.2.7
 if (ParamCount()>0)
  {
   asNomFichAuto=ParamStr(1);
   SimulEnCours=true;
   ActionOuvrir->Execute();
   SimulEnCours=false;
  }
 ActionAfficherDirections->Checked=!!(Affichage&aff_dir);
 ActionAfficherSignalisation->Checked=!!(Affichage&aff_sign);
 ActionAfficherVoies->Checked=!!(Affichage&aff_voie);
 ActionAfficherVehicules->Checked=!!(Affichage&aff_veh);
 ActionAfficherPietons->Checked=!!(Affichage&aff_ptn);
 ActionAfficherEnvironnement->Checked=!!(Affichage&aff_env);
 ActionAfficherQuadrillage->Checked=!!(Affichage&aff_quadr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::DrawGridSimulClick(TObject *Sender)
{
 if ((frmDefVoie->Visible)&&
     (!(SelectionFeuxDmd||SelectionFeuxAtt)))
  frmDefVoie->RafraichitInfos();
 if (frmInfosPieton->Visible) frmInfosPieton->RafraichitInfos(); // v3.0
 if (frmInfosVehicule->Visible) frmInfosVehicule->RafraichitInfos();
 if (frmInfosBus->Visible) frmInfosBus->RafraichitInfos(); // v3.0
 if (frmInfosTram->Visible) frmInfosTram->RafraichitInfos(); // v3.5
 if (frmInfosTaxi->Visible) frmInfosTaxi->RafraichitInfos(); // v3.6
 if ((frmAffDistEtapes->Visible)&&
     (!(SelectionFeuxDmd||SelectionFeuxAtt)))
  {
   frmAffDistEtapes->EffaceInfos();
   frmAffDistEtapes->RafraichitInfos();
  }
 if ((frmAffDistArretsBus->Visible)&& // v3.0
     (!(SelectionFeuxDmd||SelectionFeuxAtt)))
  {
   frmAffDistArretsBus->EffaceInfos();
   frmAffDistArretsBus->RafraichitInfos();
  }
 if ((frmAffDistArretsTram->Visible)&& // v3.5
     (!(SelectionFeuxDmd||SelectionFeuxAtt)))
  {
   frmAffDistArretsTram->EffaceInfos();
   frmAffDistArretsTram->RafraichitInfos();
  }
 if ((frmAffDistFilesTaxi->Visible)&& // v3.6
     (!(SelectionFeuxDmd||SelectionFeuxAtt)))
  {
   frmAffDistFilesTaxi->EffaceInfos();
   frmAffDistFilesTaxi->RafraichitInfos();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::TimerSimulTimer(TObject *Sender)
{
 if (cv->TourEnCours) return;

 // On traite d'abord la demande
 switch(TypeDemande)
  {
   case tdArret:TypeDemande=tdRien;
                TimerSimul->Enabled=false;
                Pause=false; // v3.5
                SimulationEnCours=false;
                // v3.9.2 (ActionXXX->Execute() ne fonctionne pas à tous les coups) 
                if (ActionDistancesEtapes->Checked) ActionDistancesEtapesExecute(ActionDistancesEtapes);
                if (ActionDistancesArretsBus->Checked) ActionDistancesArretsBusExecute(ActionDistancesArretsBus);
                if (ActionDistancesArretsTram->Checked) ActionDistancesArretsTramExecute(ActionDistancesArretsTram);
                if (ActionDistancesFilesTaxi->Checked) ActionDistancesFilesTaxiExecute(ActionDistancesFilesTaxi);
                if (ActionEvolution->Checked) ActionEvolutionExecute(ActionEvolution);
                if (ActionAfficherVehicules->Checked) ActionAfficherVehiculesExecute(ActionAfficherVehicules);
                if (ActionStatsEtapes->Checked) ActionStatsEtapesExecute(ActionStatsEtapes); // v3.9.2
                AfficheBilan();
                StatusBar->Panels->Items[0]->Text="Arrêt de la simulation et réinitialisation du réseau en cours...";
                ActionOuvrir->Execute();
                asNomFichAuto="";
                DrawGridSimul->Options << goRangeSelect;
                DrawGridSimul->PopupMenu=PopupMenuEditionCase;
                return;
   case tdPause:TypeDemande=tdRien;
                TimerSimul->Enabled=false;
                Pause=true; // v3.5
                SimulationEnCours=false;
                AfficheBilan();
                return;
   case tdRien:
   default:     break;
  } 
 // si aucune demande, on continue la simulation...
 Application->Title = Format(asFrmTitleCV, ARRAYOFCONST(((int)(cv->TourCrt))));
 Caption = Format(asFrmCaptionCV, ARRAYOFCONST((FILENAME(SaveDialog), (int)(cv->TourCrt))));

 if (cv->NbVehiculesArrives==cv->NbVehicules)
  {
   StatusBar->Panels->Items[0]->Text=Format("Simulation terminée (%d véhicules)", ARRAYOFCONST((cv->NbVehicules)));
   TypeDemande=tdArret;
  }
 else
  {
   cv->EffectueTourSimulation();
   if (cv->NbVehiculesSortis&&(cv->NbVehiculesSortis-cv->NbVehiculesArrives))
    StatusBar->Panels->Items[0]->Text=Format("Sur %d sortis [%d%%] : %d arrivé(s) [%d%%]. Sur %d en course : %d déplacé(s) [%d%%].",
                                             ARRAYOFCONST((cv->NbVehiculesSortis, 100*cv->NbVehiculesSortis/cv->NbVehicules,
                                                           cv->NbVehiculesArrives, 100*cv->NbVehiculesArrives/cv->NbVehiculesSortis,
                                                           cv->NbVehiculesSortis-cv->NbVehiculesArrives,
                                                           cv->NbVehiculesDeplaces, 100*cv->NbVehiculesDeplaces/(cv->NbVehiculesSortis-cv->NbVehiculesArrives))));
  }
}
//---------------------------------------------------------------------------






bool TfrmSimulation::ConfirmeSuppressionFeuxUtilisesDansSelection(type_voie TypeVoie) // v3.5 (TypeVoie)
 {
  bool Abandon=false, ToutSupprimer=true;
  int i, j, d, x, y, NumFeu,
      xd=DrawGridSimul->Selection.Left,
      yd=DrawGridSimul->Selection.Top,
      xf=DrawGridSimul->Selection.Right,
      yf=DrawGridSimul->Selection.Bottom;
  for(x=xd; (!Abandon)&&(x<=xf); x++)
   for(y=yd; (!Abandon)&&(y<=yf); y++)
    for(d=0; (!Abandon)&&(d<4); d++)
     if (cv->v[x][y].ExisteVoieDansDirection(TypeVoie, (direction)d)&& // v3.5
         (NumFeu=cv->v[x][y].NumFeu[d]))
      for(i=0; (!Abandon)&&(i<cv->NbFeux); i++)
       {
        for(j=0; (!Abandon)&&(j<cv->Feu[i].NbFeuxDmd); j++)
         if (cv->Feu[i].NumFeuxDmd[j]==NumFeu)
          switch(MessageDlg( Format( "\
Le feu n°%d dépend du feu n°%d (à supprimer) :\n\
Ce dernier demande que le premier soit rouge pour passer au vert.\n\n\
Si vous continuez, le feu n°%d sera supprimé.\n\
Êtes-vous sûr de vouloir continuer ?",
                                     ARRAYOFCONST((i+1, NumFeu, NumFeu))),
                             mtConfirmation,
#ifdef CV_WINDOWS
                             TMsgDlgButtons() << mbYes << mbNo << mbYesToAll, 0))
#endif
#ifdef CV_LINUX
                             TMsgDlgButtons() << mbYes << mbNo, 0))
#endif
           {
#ifdef CV_WINDOWS
            case mrYesToAll: ToutSupprimer=true;
                             Abandon=true;
                             break;
#endif
            case mrNo:       ToutSupprimer=false;
                             Abandon=true;
            default:         break;
           }
        for(j=0; (!Abandon)&&(j<cv->Feu[i].NbFeuxAtt); j++)
         if (cv->Feu[i].NumFeuxAtt[j]==NumFeu)
          switch(MessageDlg( Format( "\
Le feu n°%d dépend du feu n°%d (à supprimer) :\n\
Ce dernier doit être rouge pour que le premier passe au vert.\n\n\
Si vous continuez, le feu n°%d sera supprimé.\n\
Êtes-vous sûr de vouloir continuer ?",
                                     ARRAYOFCONST((i+1, NumFeu, NumFeu))),
                             mtConfirmation,
#ifdef CV_WINDOWS
                             TMsgDlgButtons() << mbYes << mbNo << mbYesToAll, 0))
#endif
#ifdef CV_LINUX
                             TMsgDlgButtons() << mbYes << mbNo, 0))
#endif
           {
#ifdef CV_WINDOWS
            case mrYesToAll: ToutSupprimer=true;
                             Abandon=true;
                             break;
#endif
            case mrNo:       ToutSupprimer=false;
                             Abandon=true;
            default:         break;
           }
       }
  return ToutSupprimer;
 }
//---------------------------------------------------------------------------
void TfrmSimulation::SupprimeFeuxUtilisesDansSelection(type_voie TypeVoie)
 {
  int i, j, d, x, y, NumFeu,
      xd=DrawGridSimul->Selection.Left,
      yd=DrawGridSimul->Selection.Top,
      xf=DrawGridSimul->Selection.Right,
      yf=DrawGridSimul->Selection.Bottom;
  for(x=xd; x<=xf; x++)
   for(y=yd; y<=yf; y++)
    for(d=0; d<4; d++)
     if (cv->v[x][y].ExisteVoieDansDirection(TypeVoie, (direction)d)&& // v3.5
         (NumFeu=cv->v[x][y].NumFeu[d]))
      for(i=0; i<cv->NbFeux; i++)
       {
        for(j=0; j<cv->Feu[i].NbFeuxDmd; j++)
         if (cv->Feu[i].NumFeuxDmd[j]==NumFeu)
          cv->Feu[i].RetireFeuDmd(NumFeu);
        for(j=0; j<cv->Feu[i].NbFeuxAtt; j++)
         if (cv->Feu[i].NumFeuxAtt[j]==NumFeu)
          cv->Feu[i].RetireFeuAtt(NumFeu);
       }
 }
//---------------------------------------------------------------------------
bool TfrmSimulation::ConfirmeSuppressionArretsUtilisesDansSelection(type_voie TypeVoie) // v3.5
 {
  bool Abandon=false, ToutSupprimer=true;
  int i, j, d, x, y, NumArret,
      xd=DrawGridSimul->Selection.Left,
      yd=DrawGridSimul->Selection.Top,
      xf=DrawGridSimul->Selection.Right,
      yf=DrawGridSimul->Selection.Bottom;
  bool *ArretBusDejaVu=new bool[cv->NbArretsBus],
       *ArretTramDejaVu=new bool[cv->NbArretsTram];
  voie *v;
  type_voie TypeVoieCrt;
  for(i=0; i<cv->NbArretsBus; i++) ArretBusDejaVu[i]=false;
  for(i=0; i<cv->NbArretsTram; i++) ArretTramDejaVu[i]=false;
  for(x=xd; (!Abandon)&&(x<=xf); x++)
   for(y=yd; (!Abandon)&&(y<=yf); y++)
    {
     v=&(cv->v[x][y]); TypeVoieCrt=tvAucun;
     if (((TypeVoie&tvRoute)&&v->DirPoss&&(NumArret=v->NumArretBus)&&(TypeVoieCrt+=tvRoute))||
         ((TypeVoie&tvVoieTram)&&v->SensVoieTram&&(NumArret=v->NumArretTram)&&(TypeVoieCrt+=tvVoieTram))) // v3.5
      if (((TypeVoieCrt&tvRoute)&&(!ArretBusDejaVu[NumArret-1]))||
          ((TypeVoieCrt&tvVoieTram)&&(!ArretTramDejaVu[NumArret-1])))
       {
        switch(MessageDlg( Format( "\
L'arrêt %s n°%d est dans la sélection.\n\
Si vous continuez, il sera supprimé.\n\
Êtes-vous sûr de vouloir continuer ?",
                           ARRAYOFCONST((asTypeArret[TypeVoieCrt], NumArret))),
                           mtConfirmation,
#ifdef CV_WINDOWS
                           TMsgDlgButtons() << mbYes << mbNo << mbYesToAll, 0))
#endif
#ifdef CV_LINUX
                           TMsgDlgButtons() << mbYes << mbNo, 0))
#endif
         {
#ifdef CV_WINDOWS
          case mrYesToAll: ToutSupprimer=true;
                           Abandon=true;
                           break;
#endif
          case mrNo:       ToutSupprimer=false;
                           Abandon=true;
          default:         break;
         }
        switch(TypeVoieCrt)
         {
          case tvRoute:    ArretBusDejaVu[NumArret-1]=true; break;
          case tvVoieTram: ArretTramDejaVu[NumArret-1]=true; break;
          default: break;
         }
       }
    }
  delete[] ArretBusDejaVu;
  delete[] ArretTramDejaVu;
  return ToutSupprimer;
 }
//---------------------------------------------------------------------------
void TfrmSimulation::SupprimeArretsUtilisesDansSelection(type_voie TypeVoie)
 {
  int i, j, d, x, y, NumArret,
      xd=DrawGridSimul->Selection.Left,
      yd=DrawGridSimul->Selection.Top,
      xf=DrawGridSimul->Selection.Right,
      yf=DrawGridSimul->Selection.Bottom;
  bool *ArretBusDejaVu=new bool[cv->NbArretsBus],
       *ArretTramDejaVu=new bool[cv->NbArretsTram];
  voie *v;
  type_voie TypeVoieCrt;
  for(i=0; i<cv->NbArretsBus; i++) ArretBusDejaVu[i]=false;
  for(i=0; i<cv->NbArretsTram; i++) ArretTramDejaVu[i]=false;
  for(x=xd; (x<=xf); x++)
   for(y=yd; (y<=yf); y++)
    {
     v=&(cv->v[x][y]); TypeVoieCrt=tvAucun;
     if (((TypeVoie&tvRoute)&&v->DirPoss&&(NumArret=v->NumArretBus)&&(TypeVoieCrt+=tvRoute))||
         ((TypeVoie&tvVoieTram)&&v->SensVoieTram&&(NumArret=v->NumArretTram)&&(TypeVoieCrt+=tvVoieTram))) // v3.5
      if (((TypeVoieCrt&tvRoute)&&(!ArretBusDejaVu[NumArret]))||
          ((TypeVoieCrt&tvVoieTram)&&(!ArretTramDejaVu[NumArret])))
       {
        switch(TypeVoieCrt)
         {
          case tvRoute:    cv->SupprimeArretBus(NumArret-1); ArretBusDejaVu[NumArret-1]=true; break;
          case tvVoieTram: cv->SupprimeArretTram(NumArret-1); ArretTramDejaVu[NumArret-1]=true; break;
          default: break;
         }
       }
    }
  delete[] ArretBusDejaVu;
  delete[] ArretTramDejaVu;
 }
//---------------------------------------------------------------------------
void TfrmSimulation::ReinitialiseToutDansSelection(type_voie TypeVoie)
 {
  int x, y,
      xd=DrawGridSimul->Selection.Left,
      yd=DrawGridSimul->Selection.Top,
      xf=DrawGridSimul->Selection.Right,
      yf=DrawGridSimul->Selection.Bottom;
  for(x=xd; x<=xf; x++)
   for(y=yd; y<=yf; y++)
    {
     if (TypeVoie&tvRoute) cv->SupprimeEtapeVoie(x, y);
     if (TypeVoie&tvRoute) cv->SupprimePlaceTaxiVoie(x, y);
     if (TypeVoie&tvRoute)
      {
       cv->SupprimeDepotBusVoie(x, y);
       cv->SupprimeArretBusVoie(x, y);
      }
     if (TypeVoie&tvVoieTram) cv->SupprimeArretTramVoie(x, y);
     cv->SupprimeFeuxVoie(x, y, TypeVoie);
     cv->v[x][y].Initialise(TypeVoie);
     RedessineCase(x,y,true);
     if (y==yd) RedessineCase((x+dx[nord])%cv->NbX, (y+dy[nord])%cv->NbY, true);
     if (x==xf) RedessineCase((x+dx[est])%cv->NbX, (y+dy[est])%cv->NbY, true);
     if (y==yf) RedessineCase((x+dx[sud])%cv->NbX, (y+dy[sud])%cv->NbY, true);
     if (x==xd) RedessineCase((x+dx[ouest])%cv->NbX, (y+dy[ouest])%cv->NbY, true);
    }
 }
//---------------------------------------------------------------------------
bool TfrmSimulation::SupprimeToutDansSelection(type_voie TypeVoie)
 {
  if ((AfficheMessage( Format( "Êtes-vous bien sûr(e) de vouloir effacer les %s et supprimer tout ce qui en dépend dans la zone sélectionnée ?",
                                        ARRAYOFCONST(( asTypeVoie[TypeVoie]))),
                                "Confirmation d'effacement",
                                tmQuestionNecessaire, 1, 1)==trOui)&&
      ConfirmeSuppressionFeuxUtilisesDansSelection(TypeVoie)&&
      ConfirmeSuppressionArretsUtilisesDansSelection(TypeVoie)) // v3.5
   {
    SimulationModifiee=true;
    SupprimeFeuxUtilisesDansSelection(TypeVoie);
    SupprimeArretsUtilisesDansSelection(TypeVoie); // v3.5
    ReinitialiseToutDansSelection(TypeVoie);
    return true;
   }
  else return false;
 }
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
 CanClose=EnregistreModificationsAvant(oaQuitter);
}
//---------------------------------------------------------------------------
void TfrmSimulation::AfficheStatsAttenteTrafic() // v2.2.7
{
 affichage AffSvg=Affichage;
 if (frmStatsAttenteTrafic=new TfrmStatsAttenteTrafic(this))
  try
   {
    StatsAttenteTrafic=true;
    Affichage=aff_aucun; // Pour une meilleure visibilité
    frmStatsAttenteTrafic->ShowModal();
   }
  __finally
   {
    StatsAttenteTrafic=false;
    Affichage=AffSvg;
    DrawGridSimul->Repaint();
    frmStatsAttenteTrafic->Release();
    frmStatsAttenteTrafic=NULL;
   }
}
//---------------------------------------------------------------------------
direction TfrmSimulation::DirectionOrigineCurseur(int x, int y, direction DirDest) // v3.5
 {
  direction DirOrig=((DirOrigVoieTram>indefinie)&&(DirOrigVoieTram!=DirDest))?DirOrigVoieTram:InvDir[DirDest];
  if ((x-xPrc)*(x-xPrc)+(y-yPrc)*(y-yPrc)==1) // N,E,S ou O ?
   {
    if (xPrc-x==+1) DirOrig=est;
    if (xPrc-x==-1) DirOrig=ouest;
    if (yPrc-y==+1) DirOrig=sud;
    if (yPrc-y==-1) DirOrig=nord;
   }
  DirOrigVoieTram=DirOrig;
  return DirOrig;
 }
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::MenuItemBarreOutilsClick(TObject *Sender)
{
 TToolBar *ToolBar=(TToolBar*)FindComponent(asDebutNom[TOOLBAR]+asNomElementBarreOutils[((TMenuItem*)Sender)->Tag]);
 TMenuItem *MenuItem=(TMenuItem*)Sender;
 MenuItem->Checked^=true;
 ToolBar->Visible=MenuItem->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::PopupMenuBarreOutilsPopup(TObject *Sender)
{
 TToolBar *ToolBar; TMenuItem *MenuItem;
 for(int i=0; i<NBELEMENTSBARREOUTILS; i++)
  {
   MenuItem=(TMenuItem*)FindComponent(asDebutNom[MENUITEM]+asNomElementBarreOutils[i]);
   ToolBar=(TToolBar*)FindComponent(asDebutNom[TOOLBAR]+asNomElementBarreOutils[i]);
   MenuItem->Checked=ToolBar->Visible;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{ /* RETIRE à la version 4.1 avec la property KeyView mis à false
 TMenuItem *MenuItem;
 if ((!DrawGridSimul->PopupMenu->FindItem(ShortCut(Key, Shift), fkShortCut))&&
     (MenuItem=MainMenu->FindItem(ShortCut(Key, Shift), fkShortCut))&&
     MenuItem->Enabled)
  MenuItem->Click(); */
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::TimerClignotementErreurTimer(TObject *Sender)
{
 TimerClignotementErreur->Tag^=1; // v3.5
 cv->v[xErr][yErr].RedessineCase(false);
}
//---------------------------------------------------------------------------
void TfrmSimulation::DeplaceFeu() // v3.8.3
 {
  int d,
      xCrt=DrawGridSimul->Col,
      yCrt=DrawGridSimul->Row;
  voie *vSrc, *vDst;
  feu *FeuADeplacer;
  DeplacementFeuEnCours^=true;
  RafraichitFonctionDeplacementFeu();
  if (DeplacementFeuEnCours)
   {
    xDeplFeu=DrawGridSimul->Col;
    yDeplFeu=DrawGridSimul->Row;
    vSrc=&(cv->v[xDeplFeu][yDeplFeu]);
    if ((vSrc->Priorite[0]!=feux)&&
        (vSrc->Priorite[1]!=feux)&&
        (vSrc->Priorite[2]!=feux)&&
        (vSrc->Priorite[3]!=feux))
     {
      AfficheMessage("Il n'y a aucun feu sur cette case !", "Déplacement de feu impossible", tmAvertissement, 0, 0);
      InitialiseDeplacementFeu();
      return;
     }
   }
  else
   if ((xCrt!=xDeplFeu)||
       (yCrt!=yDeplFeu))
    {
     vSrc=&(cv->v[xDeplFeu][yDeplFeu]);
     vDst=&(cv->v[xCrt][yCrt]);
     for(d=0; d<4; d++)
      {
       if (vSrc->Priorite[d]==feux)
        {
         if (vDst->Priorite[d]==feux)
          AfficheMessage("Vous ne pouvez pas déplacer un feu sur une case où un feu de même orientation existe déjà.", "Déplacement de feu impossible", tmAvertissement, 0, 0);
         else
          if (!(vDst->DirPoss&PossDir[d+1]))
           AfficheMessage("Vous ne pouvez pas déplacer un feu sur une case qui n'a pas la même direction.", "Déplacement de feu impossible", tmAvertissement, 0, 0);
          else
           {
            FeuADeplacer=&(cv->Feu[vSrc->NumFeu[d]-1]);
            vDst->Priorite[d]=feux;
            vDst->NumFeu[d]=vSrc->NumFeu[d];
            vSrc->Priorite[d]=a_droite;
            FeuADeplacer->x=xCrt;
            FeuADeplacer->y=yCrt;
            SimulationModifiee=true;
            RedessineCase(xDeplFeu, yDeplFeu, true);
            RedessineCase(xCrt, yCrt, true);
            if (ActionPriorites->Checked) frmDefVoie->RafraichitInfos();
           }
        }
      }
     xDeplFeu=-1; yDeplFeu=-1;
    }
 }
//---------------------------------------------------------------------------
// Actions (TActionList) : v3.8.3
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionQuitterExecute(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionVerifierApresOuvertureExecute(
      TObject *Sender)
{
 ActionVerifierApresOuverture->Checked^=true;
 VerifierApresOuverture=ActionVerifierApresOuverture->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionNouveauExecute(TObject *Sender)
{
 AppelleAuChaos();
 if (EnregistreModificationsAvant(oaNouveau))
  {
   bool GenereReseauAleatoirement=false; // v4.2
   int NbX=NBXDEF, NbY=NBYDEF;
   if (cv) { NbX=cv->NbX; NbY=cv->NbY; }
   if (!DefinitDimensionsZone(NbX, NbY, GenereReseauAleatoirement)) return; // v4.2 (GenereReseauAleatoirement)
   if (cv) { delete cv; }
   cv=new centre_ville(NB_ELEMENTS_PAR_DEFAUT, NbX, NbY);
   if (GenereReseauAleatoirement) GenereReseau(); // v4.2
   RedimensionneZone();
   SimulationModifiee=false;
   asNomFichAuto="";
   SaveDialog->FileName="";
   OpenDialog->FileName="";
   Caption=asTitreCV;
   InitialiseDeplacementFeu(); // v3.5
   DrawGridSimul->Repaint();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionOuvrirExecute(TObject *Sender)
{
 AnsiString asNomFichier="";
 int hfile;
 AppelleAuChaos();
 if (asNomFichAuto.IsEmpty()&&
     (!EnregistreModificationsAvant(oaOuvrir))) return;
 if ((!asNomFichAuto.IsEmpty())||
     OpenDialog->Execute())
  {
   if (hfile=FileOpen(asNomFichier=(asNomFichAuto.IsEmpty()?FILENAME(OpenDialog):asNomFichAuto), fmOpenRead))
    {
     StatusBar->Panels->Items[0]->Text="Chargement en cours...";
     FileSeek(hfile, 0, 0);
     if (cv) { delete cv; cv=NULL; }
     cv=new centre_ville(AUCUN_ELEMENT_PAR_DEFAUT,0,0); // v non encore alloué, créé au chargement (v4.0)
     if (!cv->Charge(hfile))
      {
       if (VersionFichier>VERSION) // v3.5 : n'ouvre pas les fichier de simulation générés par une version ultérieure de la version actuelle (format de fichier)
        AfficheMessage("\
Le fichier sélectionné a été généré avec une version ultérieure à la version actuelle de Centre-Ville.\n\
Veuillez utiliser la version de Centre-Ville avec laquelle vous avez généré ce fichier.",
                                asChargementNonEffectue, tmErreur, 0, 0);
       else
        {  // v3.5 : ajout de la précision << Centre-Ville va être fermé [...] >>
         StatusBar->Panels->Items[0]->Text="Chargement non effectué.";
         AfficheMessage("Erreur de données dans le fichier.\nCentre-Ville va être fermé par précaution.", asChargementNonEffectue, tmErreur, 0, 0);
         FileClose(hfile);
         Close();
        }
      }
     else
      {
       FileClose(hfile);
       RedimensionneZone();
       SimulationModifiee=false;
       SaveDialog->FileName=asNomFichier;
       OpenDialog->FileName=asNomFichier;
       Caption="Centre-Ville - "+asNomFichier;
       InitialiseDeplacementFeu(); // v3.5
       if (VerifierApresOuverture)
        {
         StatusBar->Panels->Items[0]->Text="Contrôle d'intégrité du réseau en cours...";
         cv->Verifie(asMsgErr);
         if (asMsgErr.Length()>0)
          AfficheMessage(asMsgErr, "Erreurs d'intégrité trouvées dans le réseau", tmErreur, 0, 0);
        }
       // Mise à jour du menu Statistiques | Affichage
       MenuItemQuadrillageStatistiques->Checked=cv->QuadrillageStats;
       switch(cv->TypeStats)
        {
         case par_nombre:      MenuItemParNbVehicules->Checked=true; break;
         case par_pourcentage: MenuItemParPourcentage->Checked=true; break;
        }
       switch(cv->NbToursStats)
        {
         case 10:  MenuItem10DrnTours->Checked=true; break;
         case 20:  MenuItem20DrnTours->Checked=true; break;
         case 50:  MenuItem50DrnTours->Checked=true; break;
         case 100: MenuItem100DrnTours->Checked=true; break;
         case 200: MenuItem200DrnTours->Checked=true; break;
         case 500: MenuItem500DrnTours->Checked=true; break;
        }

       StatusBar->Panels->Items[0]->Text="Affichage du réseau en cours...";
       DrawGridSimul->Repaint();
       StatusBar->Panels->Items[0]->Text=(asMsgErr.Length()>0)?"Chargement effectué MAIS erreur(s) d'intégrité trouvée(s)":"Chargement effectué.";
      }
    }
   else
    {
     AfficheMessage("Impossible d'ouvrir le fichier", asChargementNonEffectue, tmErreur, 0, 0);
     StatusBar->Panels->Items[0]->Text="Chargement NON effectué.";
    }
   asNomFichAuto=asVide;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionEnregistrerExecute(TObject *Sender)
{
 AnsiString asNomFichier="";
 int hfile;
 AppelleAuChaos();
 if ((!FILENAME(SaveDialog).IsEmpty())||
     (!asNomFichAuto.IsEmpty())||
     SaveDialog->Execute())
  {
   StatusBar->Panels->Items[0]->Text="Enregistrement en cours...";
   if (hfile=FileCreate(asNomFichier=(asNomFichAuto.IsEmpty()?FILENAME(SaveDialog):asNomFichAuto)))
    {
     if (!cv->Sauve(hfile))
      {
       AfficheMessage("Erreur de données dans le fichier", asSauvegardeNonEffectuee, tmErreur, 0, 0);
       FileClose(hfile);
       StatusBar->Panels->Items[0]->Text="Enregistrement NON effectué.";
       if (EnregistrerAvant) EnregistrerAvant=false;
      }
     else
      {
       FileClose(hfile);
       SaveDialog->FileName=asNomFichier;
       OpenDialog->FileName=asNomFichier;
       Caption="Centre-Ville - "+asNomFichier;
       StatusBar->Panels->Items[0]->Text="Enregistrement effectué.";
       SimulationModifiee=false;
      }
    }
   else
    {
     AfficheMessage("Impossible de créer le fichier", asSauvegardeNonEffectuee, tmErreur, 0, 0);
     StatusBar->Panels->Items[0]->Text="Enregistrement non effectué.";
     if (EnregistrerAvant) EnregistrerAvant=false;
    }
  }
 else
  if (EnregistrerAvant) EnregistrerAvant=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionEnregistrerSousExecute(
      TObject *Sender)
{
 if (SaveDialog->Execute()) ActionEnregistrer->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionZoomExecute(TObject *Sender)
{
 int Col=DrawGridSimul->Col,
     Row=DrawGridSimul->Row;
#ifdef CV_LINUX
 return; // Désactivé
#endif
 ActionZoom->Checked^=true;
 if (ActionZoom->Checked)
  {
   ImageList8x8=ImageList8x8x2;
   DrawGridSimul->DefaultColWidth=16;
   DrawGridSimul->DefaultRowHeight=16;
  }
 else
  {
   ImageList8x8=ImageList8x8x1;
   DrawGridSimul->Col=0;
   DrawGridSimul->Row=0;
   DrawGridSimul->DefaultColWidth=8;
   DrawGridSimul->DefaultRowHeight=8;
   DrawGridSimul->Col=Col;
   DrawGridSimul->Row=Row;
   Width=8*cv->NbX+(Width-DrawGridSimul->Width); // v3.5
   Height=8*cv->NbY+(Height-DrawGridSimul->Height); // v3.5
   DrawGridSimul->Repaint(); // v3.5
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionAfficherDirectionsExecute(
      TObject *Sender)
{
 ActionAfficherDirections->Checked^=true;
 Affichage=(affichage)(Affichage^aff_dir);
 DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionAfficherSignalisationExecute(
      TObject *Sender)
{
 ActionAfficherSignalisation->Checked^=true;
 Affichage=(affichage)(Affichage^aff_sign);
 DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionAfficherVoiesExecute(TObject *Sender)
{
 ActionAfficherVoies->Checked^=true;
 Affichage=(affichage)(Affichage^aff_voie);
 DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionAfficherVehiculesExecute(
      TObject *Sender)
{
 ActionAfficherVehicules->Checked^=true;
 Affichage=(affichage)(Affichage^aff_veh);
 DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionAfficherPietonsExecute(
      TObject *Sender)
{
 ActionAfficherPietons->Checked^=true;
 Affichage=(affichage)(Affichage^aff_ptn);
 DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionAfficherQuadrillageExecute(TObject *Sender)
{
 ActionAfficherQuadrillage->Checked^=true;
 Affichage=(affichage)(Affichage^aff_quadr);
 DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionAfficherEnvironnementExecute(
      TObject *Sender)
{
 ActionAfficherEnvironnement->Checked^=true;
 Affichage=(affichage)(Affichage^aff_env);
 DrawGridSimul->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionParametresExecute(TObject *Sender)
{
 Parametres();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionVerifierReseauExecute(
      TObject *Sender)
{
 VerifieReseau();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionMarcheExecute(TObject *Sender)
{
 type_distance TypeDistance=type_indefini; // v3.5
 int i;
 if (frmDefFeux->Visible) frmDefFeux->Hide();
 if (frmDefVoie->Visible) frmDefVoie->Hide();
 ToolButtonArret->Enabled=true;
 MenuItemArret->Enabled=true;
 if (!Pause) // v3.5 (Remplace !cv->TourCrt)
  {
   StatusBar->Panels->Items[0]->Text="Vérification de la validité du réseau...";
   StatusBar->Repaint();
   if (!VerifieReseau())  // Il faut d'abord que le réseau soit correct
    {
     AfficheMessage(asErrDsReseau, asAvertissement, tmAvertissement, 0, 0);
     return;
    }

   for(i=0; (i<cv->NbEtapes)&&cv->Etape[i].Definie(); i++);
   if (i<cv->NbEtapes)
    {
     AfficheMessage(asNbEtapesInsuff, asAvertissement, tmAvertissement, 0, 0);
     return;
    }

   StatusBar->Panels->Items[0]->Text="Préparation du calcul des distances...";
   StatusBar->Repaint();
   cv->DefinitFilesTaxi(); // v3.6. On prépare les files de taxi pour les distances aux files de taxi
   if (!cv->PrepareCalculDistances()) // On alloue la place pour calculer les distances
    { // Si erreur alors problème de manque de mémoire
     AfficheMessage(asMemInsuff, asErrInattendue, tmErreur, 0, 0);
     return;
    }
   StatusBar->Panels->Items[0]->Text="Préparation des statistiques de fluidité et de trafic...";
   StatusBar->Repaint();
   if (!cv->PrepareCalculAttenteTrafic()) // v2.2.7 : On alloue la place pour calculer les statistiques d'attente et de trafic
    { // Si erreur alors problème de manque de mémoire
     AfficheMessage(asMemInsuff, asErrInattendue, tmErreur, 0, 0);
     return;
    }
   StatusBar->Panels->Items[0]->Text="Calcul des distances...";
   StatusBar->Repaint();
   cv->CalculeDistances(); // On calcule les distances par récurrence

   StatusBar->Panels->Items[0]->Text="Vérification du calcul des distances...";
   StatusBar->Repaint();
   if (!cv->VerifieCalculDistances(TypeDistance)) // Sont-elles toutes définies ?
    {
     StatusBar->Panels->Items[0]->Text=Format("La case (%d, %d) a une distance "+asTypeDistance[TypeDistance]+" indéfinie.",
                                              ARRAYOFCONST((xErr=cv->xErr, yErr=cv->yErr)));
     if ((xErr>-1)&&(yErr>-1)) RedessineCase(xErr, yErr, true);
     AfficheMessage(Format(asFrmReseauNonConnexe[TypeDistance==etapes],
                                    ARRAYOFCONST((asTypeDistance[TypeDistance]))),
                             asAvertissement, tmAvertissement, 0, 0);
     switch(TypeDistance) // v3.9.3
      {
       case etapes:      frmAffDistEtapes->Show(); break;
       case arrets_bus:  frmAffDistArretsBus->Show(); break;
       case arrets_tram: frmAffDistArretsTram->Show(); break;
       case files_taxi:  frmAffDistFilesTaxi->Show(); break;
      }
     return;
    }
   StatusBar->Panels->Items[0]->Text="Calcul du trajet des lignes de bus et de trams...";
   StatusBar->Repaint();
   cv->InitialiseInfosTrajetLignesBus();
   cv->CalculeTrajetLignesBus();
   cv->CalculeTrajetLignesTram(); // v3.8. Un oubli
   cv->DistancesCalculees=true;
   ActionDistancesEtapes->Enabled=true;
   ActionDistancesArretsBus->Enabled=true; // v3.0
   ActionDistancesArretsTram->Enabled=true; // v3.7
   ActionDistancesFilesTaxi->Enabled=true; // v3.7
   StatusBar->Panels->Items[0]->Text="Préparation des véhicules...";
   StatusBar->Repaint();
   if (!cv->PrepareVehicules()) // On alloue la place et on prépare les véhicules
    { // Si erreur alors problème de manque de mémoire
     AfficheMessage(asMemInsuff, asErrInattendue, tmErreur, 0, 0);
     return;
    }
   StatusBar->Panels->Items[0]->Text="Préparation des bus..."; // v3.0
   StatusBar->Repaint();
   if (!cv->PrepareBus()) // v3.0. On alloue la place et on prépare les bus. v3.0
    { // Si erreur alors problème de manque de mémoire
     AfficheMessage(asMemInsuff, asErrInattendue, tmErreur, 0, 0);
     return;
    }
   StatusBar->Panels->Items[0]->Text="Préparation des trams..."; // v3.5
   StatusBar->Repaint();
   if (!cv->PrepareTrams()) // On alloue la place et on prépare les trams que l'on place sur les arrêts. v3.5
    { // Si erreur alors problème de manque de mémoire
     AfficheMessage(asMemInsuff, asErrInattendue, tmErreur, 0, 0);
     return;
    }
   StatusBar->Panels->Items[0]->Text="Préparation des taxis..."; // v3.6
   StatusBar->Repaint();
   if (!cv->PrepareTaxis()) // On alloue la place et on prépare les taxis (1 taxi sur chaque place). v3.6
    { // Si erreur alors problème de manque de mémoire
     AfficheMessage(asMemInsuff, asErrInattendue, tmErreur, 0, 0);
     return;
    }
   StatusBar->Panels->Items[0]->Text="Préparation des piétons...";
   StatusBar->Repaint();
   if (!cv->PreparePietons()) // v2.0. On alloue la place et on prépare les piétons
    { // Si erreur alors problème de manque de mémoire
     AfficheMessage(asMemInsuff, asErrInattendue, tmErreur, 0, 0);
     return;
    }
   cv->NbVehiculesSortis=cv->NbVehiculesDeplaces=cv->NbVehiculesArrives=0;
   if (VerifierAvantSimulation)
    {
     StatusBar->Panels->Items[0]->Text="Contrôle d'intégrité du réseau...";
     StatusBar->Repaint();
     cv->Verifie(asMsgErr);
     if (asMsgErr.Length()>0)
      {
       AfficheMessage(asMsgErr, "Erreurs d'intégrité trouvées dans le réseau", tmErreur, 0, 0);
       return;
      }
    }
   asNomFichAuto=FILENAME(SaveDialog);
   EnregistrerAvant=true; // On teste si on annule l'enregistrement (j'emprunte EnregistrerAvant)
   ActionEnregistrer->Execute();
   if (!EnregistrerAvant) return; // Enregistrement Annulé
   EnregistrerAvant=false;
   if (cv->Stats=new stats[cv->NbToursStats])
    cv->Stats[0].Definit();
   else
    {
     AfficheMessage(asMemInsuff, asErrInattendue, tmErreur, 0, 0);
     return;
    }
  }
 if (!Pause) // v3.5 (Remplace !cv->TourCrt)
  {
   // On active l'affichage des véhicules
   if (!ActionAfficherVehicules->Checked) ActionAfficherVehicules->Execute();
   // v2.0. On active l'affichage des piétons
   if (!ActionAfficherPietons->Checked) ActionAfficherPietons->Execute();
  }

 // Mise en marche de la simulation : C'EST PARTI !
 Pause=false; // v3.5
 SimulationEnCours=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionInterruptionExecute(TObject *Sender)
{
 TypeDemande=tdPause;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionArretExecute(TObject *Sender)
{
 TypeDemande=tdArret;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionVerifierAvantSimulationExecute(
      TObject *Sender)
{
 ActionVerifierAvantSimulation->Checked^=true;
 VerifierAvantSimulation=ActionVerifierAvantSimulation->Checked; // v3.8.3
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionEvolutionExecute(TObject *Sender)
{
 ActionEvolution->Checked^=true;
 frmStatistiques->Visible=ActionEvolution->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionStatsAff10ToursExecute(
      TObject *Sender)
{
 ActionStatsAff10Tours->Checked=true;
 cv->NbToursStats=10;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionStatsAff20ToursExecute(
      TObject *Sender)
{
 ActionStatsAff20Tours->Checked=true;
 cv->NbToursStats=20;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionStatsAff50ToursExecute(
      TObject *Sender)
{
 ActionStatsAff50Tours->Checked=true;
 cv->NbToursStats=50;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionStatsAff100ToursExecute(
      TObject *Sender)
{
 ActionStatsAff100Tours->Checked=true;
 cv->NbToursStats=100;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionStatsAff200ToursExecute(
      TObject *Sender)
{
 ActionStatsAff200Tours->Checked=true;
 cv->NbToursStats=200;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionStatsAff500ToursExecute(
      TObject *Sender)
{
 ActionStatsAff500Tours->Checked=true;
 cv->NbToursStats=500;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionStatsAffParVehiculeExecute(
      TObject *Sender)
{
 ActionStatsAffParVehicule->Checked=true;
 cv->TypeStats=par_nombre;
 if (frmStatistiques->Visible) frmStatistiques->PaintBoxStats->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionStatsAffParPourcentExecute(
      TObject *Sender)
{
 ActionStatsAffParPourcent->Checked=true;
 cv->TypeStats=par_pourcentage;
 if (frmStatistiques->Visible) frmStatistiques->PaintBoxStats->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionStatsAffQuadrillageExecute(
      TObject *Sender)
{
 ActionStatsAffQuadrillage->Checked^=true;
 cv->QuadrillageStats=ActionStatsAffQuadrillage->Checked;
 if (frmStatistiques->Visible) frmStatistiques->PaintBoxStats->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionFluiditeTraficExecute(
      TObject *Sender)
{
 if (SimulEnCours)
  AfficheMessage("\
Vous devez interrompre ou arrêter la simulation en cours pour visualiser ces statistiques.\n\
À l'affichage du bilan, on vous demandera si vous souhaitez voir ces statistiques.",
"Statistiques de fluidité et de trafic", tmInformation, 0, 0);
 else
  AfficheStatsAttenteTrafic();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionCompositionExecute(TObject *Sender)
{
 Composition();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionStatsEtapesExecute(TObject *Sender)
{
 ActionStatsEtapes->Checked^=true;
 if (ActionStatsEtapes->Checked&&(!cv->NbVehiculesArrives))
  {
   AfficheMsgInfoNonDisp("Statistiques sur les véhicules");
   ActionStatsEtapes->Checked=false;
  }
 else
  frmStatsVehicules->Visible=ActionStatsEtapes->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionAProposExecute(TObject *Sender)
{
#ifdef CV_WINDOWS
 frmAPropos->ShowModal();
#endif
#ifdef CV_LINUX
AfficheMessage( "\
Centre-Ville pour Linux\r\n\
Version : 4.3.1\r\n\n\
Licence : GPL 2.0\r\n\n\
Idée & Programme : Patrice FOUQUET\r\n\
Copyright : 1998-2004, Patrice FOUQUET\r\n\n\
Se reporter au fichier license.txt\r\n\
(traduction non officielle en français : licence.txt).\r\n\n\
Centre-Ville est fourni SANS AUCUNE GARANTIE.\r\n\n\
Sources Linux : Kylix C++ (Kylix Delphi jusqu'à la version 3.1)\r\n\
Sources Windows : C++Builder",
                "A propos de Centre-Ville",
                tmInformation, 0, 0);
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionSommaireExecute(TObject *Sender)
{
 AfficheIndexAide(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDirectionHautExecute(TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 if (cv->ChangeDirectionSiPossible(x, y, N))
  {
   ModifiePassagePietonsSiNecessaire(x, y);
   SimulationModifiee=true;
   RedessineCase((x+dx[nord])%cv->NbX, (y+dy[nord])%cv->NbY, true);
   if (ActionPriorites->Checked) frmDefVoie->RafraichitInfos();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDirectionDroiteExecute(
      TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 if (cv->ChangeDirectionSiPossible(x, y, E))
  {
   ModifiePassagePietonsSiNecessaire(x, y);
   SimulationModifiee=true;
   RedessineCase((x+dx[est])%cv->NbX, (y+dy[est])%cv->NbY, true);
   if (ActionPriorites->Checked) frmDefVoie->RafraichitInfos();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDirectionBasExecute(TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 if (cv->ChangeDirectionSiPossible(x, y, S))
  {
   ModifiePassagePietonsSiNecessaire(x, y);
   SimulationModifiee=true;
   RedessineCase((x+dx[sud])%cv->NbX, (y+dy[sud])%cv->NbY, true);
   if (ActionPriorites->Checked) frmDefVoie->RafraichitInfos();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDirectionGaucheExecute(
      TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 if (cv->ChangeDirectionSiPossible(x, y, O))
  {
   ModifiePassagePietonsSiNecessaire(x, y);
   SimulationModifiee=true;
   RedessineCase((x+dx[ouest])%cv->NbX, (y+dy[ouest])%cv->NbY, true);
   if (ActionPriorites->Checked) frmDefVoie->RafraichitInfos();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionEffacerRouteExecute(TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 for(int d=nord; d<=ouest; d++)
  if (cv->v[x][y].DirPoss&PossDir[d])
   cv->ChangeDirectionSiPossible(x, y, PossDir[d]); // Tente de supprimer chaque direction possible
 ModifiePassagePietonsSiNecessaire(x, y);
 SimulationModifiee=true;
 for(int d=nord; d<=ouest; d++)
  RedessineCase((x+dx[d])%cv->NbX, (y+dy[d])%cv->NbY, true);
 if (ActionPriorites->Checked) frmDefVoie->RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDirectionHautTramExecute(
      TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 cv->v[x][y].ModifieSensVoieTram(DirectionOrigineCurseur(x, y, nord), nord);
 SimulationModifiee=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDirectionDroiteTramExecute(
      TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 cv->v[x][y].ModifieSensVoieTram(DirectionOrigineCurseur(x, y, est), est);
 SimulationModifiee=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDirectionBasTramExecute(
      TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 cv->v[x][y].ModifieSensVoieTram(DirectionOrigineCurseur(x, y, sud), sud);
 SimulationModifiee=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDirectionGaucheTramExecute(
      TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 cv->v[x][y].ModifieSensVoieTram(DirectionOrigineCurseur(x, y, ouest), ouest);
 SimulationModifiee=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionEffacerVoieTramExecute(
      TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 cv->v[x][y].SensVoieTram=aucune_voie;
 SimulationModifiee=true;
 RedessineCase(x, y, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionToutDroitExecute(TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 cv->v[x][y].ToutDroit^=true;
 SimulationModifiee=true;
 RedessineCase(x, y, true);
 if (ActionPriorites->Checked) frmDefVoie->RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionPrioritesExecute(TObject *Sender)
{
 ActionPriorites->Checked^=true;
 frmDefVoie->Visible=ActionPriorites->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionEtapeExecute(TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 AnsiString asMsgOp;
 int NumEtape;
 if (NumEtape=cv->v[x][y].NumEtape) // Si étape on la supprime
  {
   cv->SupprimeEtape(NumEtape-1);
   asMsgOp=Format("L'étape numéro %d a été supprimée.", ARRAYOFCONST((NumEtape)));
   SimulationModifiee=true;
  }
 else // Sinon on la crée
  {
   if (NumEtape=cv->AjouteEtape(x, y))
    {
     asMsgOp=Format("L'étape créée a le numéro %d.", ARRAYOFCONST((NumEtape)));
     SimulationModifiee=true;
    }
   else
    asMsgOp=Format("Impossible de créer une étape : il y en a déjà %d !", ARRAYOFCONST((cv->NbEtapes)));
  }
 RedessineCase(x, y, true);
 StatusBar->Panels->Items[0]->Text=asMsgOp;
 if (ActionPriorites->Checked) frmDefVoie->RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDepotBusExecute(TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row,
     xPrc=cv->DepotBus.x, yPrc=cv->DepotBus.y;
 if (cv->v[x][y].EstDepotBus()) // On supprime
  cv->DepotBus.Initialise();
 else // On le pose sur la case courante
  {
   cv->DepotBus.Definit(x,y);
   RedessineCase(xPrc, yPrc, true);
  }
 RedessineCase(x, y, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionPassagePietonsExecute(
      TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 cv->v[x][y].PassagePietons^=true;
 SimulationModifiee=true;
 RedessineCase(x, y, true);
 if (ActionPriorites->Checked) frmDefVoie->RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionArretBusTramExecute(TObject *Sender)
{
 int d, x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 AnsiString asMsgOp;
 int NumArretBus, NumArretTram;
 // OU BIEN Il y a une route OU BIEN une voie de tram
 if (!((cv->v[x][y].DirPoss>aucune)^(cv->v[x][y].SensVoieTram>aucune_voie))) return;
 if (cv->v[x][y].DirPoss)
  { // Route (arrêt de bus)
   if (NumArretBus=cv->v[x][y].NumArretBus) // Si arrêt on le supprime
    {
     cv->SupprimeArretBus(x, y);
     for(d=nord; d<=ouest; d++) // On rafraîchit les cases voisines du même arrêt
      if (NumArretBus==cv->V(x,y,d).NumArretBus)
       RedessineCase((x+dx[d])%cv->NbX, (y+dy[d])%cv->NbY, true);
     asMsgOp=Format( "La case (%d,%d) a été retirée de l'arrêt de bus %d.",
                       ARRAYOFCONST(( DrawGridSimul->Col,
                                      DrawGridSimul->Row,
                                      NumArretBus)));
     SimulationModifiee=true;
    }
   else // Sinon on le crée
    {
     if (NumArretBus=cv->AjouteArretBus(x, y))
      {
       for(d=nord; d<=ouest; d++) // On rafraîchit les cases voisines du même arrêt
        if (NumArretBus==cv->V(x,y,d).NumArretBus)
         RedessineCase((x+dx[d])%cv->NbX, (y+dy[d])%cv->NbY, true);
       asMsgOp=Format( "La case (%d,%d) a été ajoutée à l'arrêt de bus %d.",
                       ARRAYOFCONST(( DrawGridSimul->Col,
                                      DrawGridSimul->Row,
                                      NumArretBus)));
       SimulationModifiee=true;
      }
     else
      if (cv->NbArretsBus)
       asMsgOp=Format("Impossible de créer un arrêt de bus : il y en a déjà %d !", ARRAYOFCONST((cv->NbArretsBus)));
      else
       asMsgOp="Impossible de créer un arrêt de bus : vous devez d'abord en définir le nombre !";
    }
  }
 else
  { // Voie de tram (arrêt de tram)
   if (NumArretTram=cv->v[x][y].NumArretTram) // Si arrêt on le supprime
    {
     cv->SupprimeArretTram(x, y);
     for(d=nord; d<=ouest; d++) // On rafraîchit les cases voisines du même arrêt
      if (NumArretTram==cv->V(x,y,d).NumArretTram)
       RedessineCase((x+dx[d])%cv->NbX, (y+dy[d])%cv->NbY, true);
     asMsgOp=Format( "La case (%d,%d) a été retirée de l'arrêt de tram %d.",
                       ARRAYOFCONST(( DrawGridSimul->Col,
                                      DrawGridSimul->Row,
                                      NumArretTram)));
     SimulationModifiee=true;
    }
   else // Sinon on le crée
    {
     if (NumArretTram=cv->AjouteArretTram(x, y))
      {
       for(d=nord; d<=ouest; d++) // On rafraîchit les cases voisines du même arrêt
        if (NumArretTram==cv->V(x,y,d).NumArretTram)
         RedessineCase((x+dx[d])%cv->NbX, (y+dy[d])%cv->NbY, true);
       asMsgOp=Format( "La case (%d,%d) a été ajoutée à l'arrêt de tram %d.",
                       ARRAYOFCONST(( DrawGridSimul->Col,
                                      DrawGridSimul->Row,
                                      NumArretTram)));
       SimulationModifiee=true;
      }
     else
      if (cv->NbArretsTram)
       asMsgOp=Format("Impossible de créer un arrêt de tram : il y en a déjà %d !", ARRAYOFCONST((cv->NbArretsTram)));
      else
       asMsgOp="Impossible de créer un arrêt de tram : vous devez d'abord en définir le nombre !";
    }
  }
 RedessineCase(x, y, true);
 StatusBar->Panels->Items[0]->Text=asMsgOp;
 if (ActionPriorites->Checked) frmDefVoie->RafraichitInfos();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionPassageBusExecute(TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 cv->v[x][y].PassageBus^=true;
 SimulationModifiee=true;
 RedessineCase(x, y, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionPlaceTaxiExecute(TObject *Sender)
{
 int x=DrawGridSimul->Col, y=DrawGridSimul->Row;
 AnsiString asMsgOp;
 int NumPlaceTaxi;
 if (NumPlaceTaxi=cv->v[x][y].NumPlaceTaxi) // Si Place Taxi on la supprime
  {
   cv->SupprimePlaceTaxi(NumPlaceTaxi-1);
   asMsgOp=Format("La place de taxi numéro %d a été supprimée.", ARRAYOFCONST((NumPlaceTaxi)));
   SimulationModifiee=true;
  }
 else // Sinon on la crée
  {
   if (NumPlaceTaxi=cv->AjoutePlaceTaxi(x, y))
    {
     asMsgOp=Format("La place de taxi créée a le numéro %d.", ARRAYOFCONST((NumPlaceTaxi)));
     SimulationModifiee=true;
    }
   else
    asMsgOp=Format("Impossible de créer une place de taxi : il y en a déjà %d !", ARRAYOFCONST((cv->NbPlacesTaxi)));
  }
 RedessineCase(x, y, true);
 StatusBar->Panels->Items[0]->Text=asMsgOp;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDeplacerFeuSourceExecute(
      TObject *Sender)
{
 DeplaceFeu();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDeplacerFeuDestinationExecute(
      TObject *Sender)
{
 DeplaceFeu();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionSegmentRouteExecute(TObject *Sender)
{
 int i,
     Gauche=DrawGridSimul->Selection.Left,
     Droite=DrawGridSimul->Selection.Right,
     Haut=DrawGridSimul->Selection.Top,
     Bas=DrawGridSimul->Selection.Bottom,
     x0, x1, y0, y1,
     dx=abs(Droite-Gauche),
     dy=abs(Bas-Haut),
     xd=DrawGridSimul->Col,
     yd=DrawGridSimul->Row,
     xf=(xd==Gauche?Droite:Gauche),
     yf=(yd==Haut?Bas:Haut);

 if ((dx>1)&&(dy>1))
  {
   AfficheMessage(asTracerEffacerRoute, asSelectionIncorrecte, tmAvertissement, 0, 0);
   return;
  }
 if (dx==dy)
  {
   AfficheMessage(asNombreLignesColonnesDifferent, asSelectionIncorrecte, tmAvertissement, 0, 0);
   return;
  }

 SimulationModifiee=true;
 if (dx<2)
  {
   SimulationModifiee=true;
   for(i=yd; i!=yf; i+=(yf-yd)/abs(yf-yd))
    {
     cv->ChangeDirectionSiPossible(x0=yd<yf?Gauche:Droite, i, yd<yf?S:N);
     if (dx==1)
      cv->ChangeDirectionSiPossible(x1=yd<yf?Droite:Gauche, i==yd?yf:i, yd<yf?N:S);
    }
   RedessineCase(x0, yf, true);
   RedessineCase(x1, yd, true);
   return;
  }

 if (dy<2)
  {
   for(i=xd; i!=xf; i+=(xf-xd)/abs(xf-xd))
    {
     cv->ChangeDirectionSiPossible(i, y0=xd<xf?Bas:Haut, xd<xf?E:O);
     if (dy==1)
      cv->ChangeDirectionSiPossible(i==xd?xf:i, y1=xd<xf?Haut:Bas, xd<xf?O:E);
    }
   RedessineCase(xf, y0, true);
   RedessineCase(xd, y1, true);
   return;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionSegmentTramExecute(TObject *Sender)
{
 int i,
     Gauche=DrawGridSimul->Selection.Left,
     Droite=DrawGridSimul->Selection.Right,
     Haut=DrawGridSimul->Selection.Top,
     Bas=DrawGridSimul->Selection.Bottom,
     dx=abs(Droite-Gauche),
     dy=abs(Bas-Haut),
     xd=DrawGridSimul->Col,
     yd=DrawGridSimul->Row,
     xf=(xd==Gauche?Droite:Gauche),
     yf=(yd==Haut?Bas:Haut);

 if ((dx>1)&&(dy>1))
  {
   AfficheMessage(asTracerEffacerRoute, asSelectionIncorrecte, tmAvertissement, 0, 0);
   return;
  }
 if (dx==dy)
  {
   AfficheMessage(asNombreLignesColonnesDifferent, asSelectionIncorrecte, tmAvertissement, 0, 0);
   return;
  }

 SimulationModifiee=true;
 if (dx<2)
  {
   SimulationModifiee=true;
   for(i=yd; i!=yf; i+=(yf-yd)/abs(yf-yd))
    {
     cv->v[yd<yf?Gauche:Droite][i].ModifieSensVoieTram(nord, sud);
     if (dx==1)
      cv->v[yd<yf?Droite:Gauche][i==yd?yf:i].ModifieSensVoieTram(nord, sud);
    }
   return;
  }

 if (dy<2)
  {
   for(i=xd; i!=xf; i+=(xf-xd)/abs(xf-xd))
    {
     cv->v[i][xd<xf?Bas:Haut].ModifieSensVoieTram(est, ouest);
     if (dy==1)
      cv->v[i==xd?xf:i][xd<xf?Haut:Bas].ModifieSensVoieTram(est, ouest);
    }
   return;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionCoinSuperieurDroitExecute(TObject *Sender)
{
 int i,
     Gauche=DrawGridSimul->Selection.Left,
     Droite=DrawGridSimul->Selection.Right,
     Haut=DrawGridSimul->Selection.Top,
     Bas=DrawGridSimul->Selection.Bottom,
     xd=DrawGridSimul->Col,
     yd=DrawGridSimul->Row,
     xf=(xd==Gauche?Droite:Gauche),
     yf=(yd==Haut?Bas:Haut);

 SimulationModifiee=true;
 for(i=yd; i!=yf; i+=(yf-yd)/abs(yf-yd))
  cv->ChangeDirectionSiPossible(Droite, i, yd<yf?S:N);
 RedessineCase(Droite, yf, true);
 for(i=xd; i!=xf; i+=(xf-xd)/abs(xf-xd))
  cv->ChangeDirectionSiPossible(i, Haut, xd<xf?E:O);
 RedessineCase(xf, Haut, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionCoinInferieurGaucheExecute(
      TObject *Sender)
{
 int i,
     Gauche=DrawGridSimul->Selection.Left,
     Droite=DrawGridSimul->Selection.Right,
     Haut=DrawGridSimul->Selection.Top,
     Bas=DrawGridSimul->Selection.Bottom,
     xd=DrawGridSimul->Col,
     yd=DrawGridSimul->Row,
     xf=(xd==Gauche?Droite:Gauche),
     yf=(yd==Haut?Bas:Haut);

 SimulationModifiee=true;
 for(i=yd; i!=yf; i+=(yf-yd)/abs(yf-yd))
  cv->ChangeDirectionSiPossible(Gauche, i, yd<yf?S:N);
 RedessineCase(Gauche, yf, true);
 for(i=xd; i!=xf; i+=(xf-xd)/abs(xf-xd))
  cv->ChangeDirectionSiPossible(i, Bas, xd<xf?E:O);
 RedessineCase(xf, Bas, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionCoinSuperieurGaucheExecute(
      TObject *Sender)
{
 int i,
     Gauche=DrawGridSimul->Selection.Left,
     Droite=DrawGridSimul->Selection.Right,
     Haut=DrawGridSimul->Selection.Top,
     Bas=DrawGridSimul->Selection.Bottom,
     xd=DrawGridSimul->Col,
     yd=DrawGridSimul->Row,
     xf=(xd==Gauche?Droite:Gauche),
     yf=(yd==Haut?Bas:Haut);

 SimulationModifiee=true;
 for(i=yd; i!=yf; i+=(yf-yd)/abs(yf-yd))
  cv->ChangeDirectionSiPossible(Gauche, i, yd<yf?S:N);
 RedessineCase(Gauche, yf, true);
 for(i=xd; i!=xf; i+=(xf-xd)/abs(xf-xd))
  cv->ChangeDirectionSiPossible(i, Haut, xd<xf?E:O);
 RedessineCase(xf, Haut, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionCoinInferieurDroitExecute(
      TObject *Sender)
{
 int i,
     Gauche=DrawGridSimul->Selection.Left,
     Droite=DrawGridSimul->Selection.Right,
     Haut=DrawGridSimul->Selection.Top,
     Bas=DrawGridSimul->Selection.Bottom,
     xd=DrawGridSimul->Col,
     yd=DrawGridSimul->Row,
     xf=(xd==Gauche?Droite:Gauche),
     yf=(yd==Haut?Bas:Haut);

 SimulationModifiee=true;
 for(i=yd; i!=yf; i+=(yf-yd)/abs(yf-yd))
  cv->ChangeDirectionSiPossible(Droite, i, yd<yf?S:N);
 RedessineCase(Droite, yf, true);
 for(i=xd; i!=xf; i+=(xf-xd)/abs(xf-xd))
  cv->ChangeDirectionSiPossible(i, Bas, xd<xf?E:O);
 RedessineCase(xf, Bas, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionPeripheriqueExterieurExecute(
      TObject *Sender)
{
 int i,
     Gauche=DrawGridSimul->Selection.Left,
     Droite=DrawGridSimul->Selection.Right,
     Haut=DrawGridSimul->Selection.Top,
     Bas=DrawGridSimul->Selection.Bottom;

 if ((Gauche==Droite)||(Bas==Haut))
  {
   AfficheMessage(asTracerEffacerPeripherique, asSelectionIncorrecte, tmAvertissement, 0, 0);
   return;
  }

 SimulationModifiee=true;
 for(i=Gauche; i<Droite; i++) cv->ChangeDirectionSiPossible(i, Bas, E);
 for(i=Bas; i>Haut; i--) cv->ChangeDirectionSiPossible(Droite, i, N);
 for(i=Droite; i>Gauche; i--) cv->ChangeDirectionSiPossible(i, Haut, O);
 for(i=Haut; i<Bas; i++) cv->ChangeDirectionSiPossible(Gauche, i, S);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionPeripheriqueInterieurExecute(
      TObject *Sender)
{
 int i,
     Gauche=DrawGridSimul->Selection.Left,
     Droite=DrawGridSimul->Selection.Right,
     Haut=DrawGridSimul->Selection.Top,
     Bas=DrawGridSimul->Selection.Bottom;
 if ((Gauche==Droite)||(Bas==Haut))
  {
   AfficheMessage(asTracerEffacerPeripherique, asSelectionIncorrecte, tmAvertissement, 0, 0);
   return;
  }

 SimulationModifiee=true;
 for(i=Gauche; i<Droite; i++) cv->ChangeDirectionSiPossible(i, Haut, E);
 for(i=Haut; i<Bas; i++) cv->ChangeDirectionSiPossible(Droite, i, S);
 for(i=Droite; i>Gauche; i--) cv->ChangeDirectionSiPossible(i, Bas, O);
 for(i=Bas; i>Haut; i--) cv->ChangeDirectionSiPossible(Gauche, i, N);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionCarrefoursExecute(TObject *Sender)
{
 Carrefours( DrawGridSimul->Selection.Right-DrawGridSimul->Selection.Left+1,
             DrawGridSimul->Selection.Bottom-DrawGridSimul->Selection.Top+1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionEffacerRoutesExecute(
      TObject *Sender)
{
 SupprimeToutDansSelection(tvRoute);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionEffacerVoiesTramExecute(
      TObject *Sender)
{
 SupprimeToutDansSelection(tvVoieTram);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDefinirNatureExecute(TObject *Sender)
{
 ActionDefinirNature->Checked^=true;
 frmDefNature->Visible=ActionDefinirNature->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionRechercherExecute(TObject *Sender)
{
 ActionRechercher->Checked^=true;
 frmRecherche->Visible=ActionRechercher->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDetailVehiculeExecute(
      TObject *Sender)
{
 ActionDetailVehicule->Checked^=true;
 frmInfosVehicule->Visible=ActionDetailVehicule->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDetailBusExecute(TObject *Sender)
{
 ActionDetailBus->Checked^=true;
 frmInfosBus->Visible=ActionDetailBus->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDetailTramExecute(TObject *Sender)
{
 ActionDetailTram->Checked^=true;
 frmInfosTram->Visible=ActionDetailTram->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDetailPietonExecute(TObject *Sender)
{
 ActionDetailPieton->Checked^=true;
 frmInfosPieton->Visible=ActionDetailPieton->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDetailTaxiExecute(TObject *Sender)
{
 ActionDetailTaxi->Checked^=true;
 frmInfosTaxi->Visible=ActionDetailTaxi->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDistancesEtapesExecute(
      TObject *Sender)
{
 ActionDistancesEtapes->Checked^=true;
 frmAffDistEtapes->Visible=ActionDistancesEtapes->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDistancesArretsBusExecute(
      TObject *Sender)
{
 ActionDistancesArretsBus->Checked^=true;
 frmAffDistArretsBus->Visible=ActionDistancesArretsBus->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDistancesArretsTramExecute(
      TObject *Sender)
{
 ActionDistancesArretsTram->Checked^=true;
 frmAffDistArretsTram->Visible=ActionDistancesArretsTram->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSimulation::ActionDistancesFilesTaxiExecute(
      TObject *Sender)
{
 ActionDistancesFilesTaxi->Checked^=true;
 frmAffDistFilesTaxi->Visible=ActionDistancesFilesTaxi->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionSuivreVehiculeExecute(
      TObject *Sender)
{
 int NumVehicule=cv->v[DrawGridSimul->Col][DrawGridSimul->Row].NumVehicule;
 if (!NumVehicule) return;
 if (!ActionRechercher->Checked)
  ActionRechercher->Execute();
 frmRecherche->RadioButtonVehicule->Checked=true;
 frmRecherche->CSpinEditVehicule->Value=NumVehicule;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionSuivreBusExecute(TObject *Sender)
{
 int NumBus=cv->v[DrawGridSimul->Col][DrawGridSimul->Row].NumBus;
 if (!NumBus) return;
 if (!ActionRechercher->Checked)
  ActionRechercher->Execute();
 frmRecherche->RadioButtonBus->Checked=true;
 frmRecherche->CSpinEditBus->Value=NumBus;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionSuivreTramExecute(TObject *Sender)
{
 int NumTram=cv->v[DrawGridSimul->Col][DrawGridSimul->Row].NumTram;
 if (!NumTram) return;
 if (!ActionRechercher->Checked)
  ActionRechercher->Execute();
 frmRecherche->RadioButtonTram->Checked=true;
 frmRecherche->CSpinEditTram->Value=NumTram;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionSuivreTaxiExecute(TObject *Sender)
{
 int NumTaxi=cv->v[DrawGridSimul->Col][DrawGridSimul->Row].NumTaxi;
 if (!NumTaxi) return;
 if (!ActionRechercher->Checked)
  ActionRechercher->Execute();
 frmRecherche->RadioButtonTaxi->Checked=true;
 frmRecherche->CSpinEditTaxi->Value=NumTaxi;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionSuivrePieton1Execute(TObject *Sender)
{
 int NumPieton=cv->v[DrawGridSimul->Col][DrawGridSimul->Row].NumPieton[0];
 if (!NumPieton) return;
 if (!ActionRechercher->Checked)
  ActionRechercher->Execute();
 frmRecherche->RadioButtonPieton->Checked=true;
 frmRecherche->CSpinEditPieton->Value=NumPieton;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionSuivrePieton2Execute(TObject *Sender)
{
 int NumPieton=cv->v[DrawGridSimul->Col][DrawGridSimul->Row].NumPieton[1];
 if (!NumPieton) return;
 if (!ActionRechercher->Checked)
  ActionRechercher->Execute();
 frmRecherche->RadioButtonPieton->Checked=true;
 frmRecherche->CSpinEditPieton->Value=NumPieton;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDecorsArbreExecute(TObject *Sender)
{
 int x,y;
 voie *v=&(cv->v[x=DrawGridSimul->Col][y=DrawGridSimul->Row]);
 if (v->Nature==arbre) v->Nature=trottoirs; else v->Nature=arbre;
 RedessineCase(x,y,true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionDecorsPelouseExecute(TObject *Sender)
{
 int x,y;
 voie *v=&(cv->v[x=DrawGridSimul->Col][y=DrawGridSimul->Row]);
 if (v->Nature==pelouse) v->Nature=trottoirs; else v->Nature=pelouse;
 RedessineCase(x,y,true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionNatureTrottoirExecute(
      TObject *Sender)
{
 int x,y;
 voie *v=&(cv->v[x=DrawGridSimul->Col][y=DrawGridSimul->Row]);
 if (NATURE(v)!=trottoirs) v->Nature=trottoirs; else v->Nature=voies;
 RedessineCase(x,y,true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionNatureImmeubleExecute(
      TObject *Sender)
{
 int x,y;
 voie *v=&(cv->v[x=DrawGridSimul->Col][y=DrawGridSimul->Row]);
 if (NATURE(v)!=immeubles) v->Nature=immeubles; else v->Nature=voies;
 RedessineCase(x,y,true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionCopierVersExecute(TObject *Sender)
{
 int NbX=DrawGridSimul->Selection.Right-DrawGridSimul->Selection.Left+1,
     NbY=DrawGridSimul->Selection.Bottom-DrawGridSimul->Selection.Top+1;
 if (!cv) return;
 if ((NbX<8)||(NbY<8))
  {
   AfficheMessage("Les dimensions de la sélection doivent être d'au moins 8x8.", "Copie vers un fichier", tmAvertissement, 0, 0);
   return;
  }
/*
 AfficheMessage("\
Cette commande n'est pas finalisée : il n'y a pas de vérification pour prévenir les erreurs qui en résulteront.\r\n\n\
Cette commande ne doit être utilisée que pour éliminer des bordures inutilisées (dans un premier temps).\r\n\n\
Cependant les zones à exclure (zones non sélectionnées) peuvent contenir :\r\n\
 - des voies de circulation (routes & voies de tram)\r\n\
 - les marques de signalisation du type suivant : cédez-le-passage, stops, passages piétons et passages réservés aux bus\r\n\
 - les décors (bâtiments, trottoirs, arbres et pelouses).\r\n\n\
Les zones à exclure NE DOIVENT PAS contenir :\r\n\
 - des étapes\r\n\
 - le dépôt de bus\r\n\
 - des feux\r\n\
 - des arrêts de bus/tram\r\n\
 - des places de taxi.\r\n\n\
Vous devez inclure TOUS les éléments cités précédemment dans la sélection pour éviter des erreurs dans le réseau généré par la commande.\r\n\
Vous pouvez, avant d'ouvrir le fichier généré, activer l'option \"Fichier | Vérifier intégrité après ouverture\" pour savoir si le fichier contient des erreurs.\r\n\
Ce message récapitulatif sera mis à jour en fonction des contrôles ajoutés dans les versions successives. Il n'y a pas d'aide en ligne pour cette commande.",
                "Commande \"Copier vers...\"", tmAvertissement, 0, 0); // v4.2
*/
 try
  {
   cv->PrepareCopie( DEBUT,
                     DrawGridSimul->Selection.Left,
                     DrawGridSimul->Selection.Top,
                     NbX, NbY);
   if (cv->CopieValide()&& // v4.2.1
       SaveDialog->Execute())
    ActionEnregistrer->Execute();
  }
 __finally
  {
   cv->PrepareCopie(FIN, 0, 0, 0, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSimulation::ActionSanglanteExecute(TObject *Sender) // v4.3
{
 SimulationSanglante=!SimulationSanglante;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSimulation::ActionResurrectionExecute(TObject *Sender) // v4.3.1
{
 ResurrectionDemandee=true;
}
//---------------------------------------------------------------------------

