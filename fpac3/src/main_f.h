//---------------------------------------------------------------------------

#ifndef main_fH
#define main_fH
//---------------------------------------------------------------------------
#include <Math.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
#include "base.h"
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.VirtualImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
//---------------------------------------------------------------------------
#define NBTAILLES              5
#define NBAGRESSIVITES         3
#define NBRAPPORTSPLPG         3
#define NBVULNERABILITES       3
#define NBDEPARTSFANTOMES      4
#define NBRAPPORTSPORTESCASES  3

#define NBDIRECTIONS           4
#define NBCOULEURSFTM          6

#define VITESSEMSG         25
#define ACHEVEMSG           1 // vCX : Au lieu de 5
#define DEBMSGAPRESEFFACER -2 // Code pour Deroulement
#define DEBMSGSANSEFFACER  -1 // Code après effacement

#define IDPILULE         0
#define IDPACGUM         1
#define IDMUR            2
#define IDPCMENTIER      3
#define IDPCMMOITIE     11
#define IDPCMVIEMORT   130
#define IDFTMENTIER     19
#define IDFTMARRIERE    43
#define IDFTMAVANT      67
#define IDYEUXENTIERS  118
#define IDYEUXARRIERE  122
#define IDYEUXAVANT    126
#define IDPRIMES        90
#define IDHAUTBAS      101
#define IDGAUCHEDROITE 102
#define IDVIDE         103
#define IDBONUS        104
#define IDPORTES       108
#define IDFONDNOIR     134 // vCX

#define IDMSGPACENTIER     5
#define IDMSGPACMOITIE    14

#define IDMSGCHIFFRE       0
#define IDMSGESPACE       10
#define IDMSGLETTRE       11
#define IDMSGVIE          37
#define IDMSGMUR          38
#define IDMSGPACGUM       39
#define IDMSGFANTOME      40
#define IDMSGTOUCHECTRL   41
#define IDMSGTOUCHEMAJ    42
#define IDMSGTOUCHEF1     43
#define IDMSGTOUCHEF3     44
#define IDMSGTOUCHEF6     45
#define IDMSGTOUCHEF12    46
#define IDMSGFLECHES      47
#define IDMSGTILDE        48
#define IDMSGDEUXPOINTS   49
#define IDMSGUNQUART      50
#define IDMSGPILULE       51
#define IDMSGAPOSTROPHE   52
#define IDMSGFOND         53
#define IDMSGTOUCHEECHAP  54
#define IDMSGPOURCENT     55
#define IDMSGETOILES      56
#define IDMSGBONUS        59
#define IDMSGPARAMPORTES  63
#define IDMSGFLECHEDROITE 64
#define IDMSGFONDNOIR     65 // vCX

#define ARRIERE           0
#define AVANT             1

// Codes géo de touches
#define FLECHE_GAUCHE    37
#define FLECHE_HAUT      38
#define FLECHE_DROITE    39
#define FLECHE_BAS       40

#define TPSAVTREAPPARITION 25
 
#define NBZONESAFFICHAGE  5
#define NBCOULEURSFANTOME 5 // gris exclu réservé pour la fuite

#define ACTIVER           true // paramètre pour ChangeAccesParametres(bool)

#define COULEURFANTOME(i) ((Jeu.Fantome[i].Etat==en_fuite)?gris:((Jeu.Fantome[i].Etat==transition)?(Jeu.ACheval?gris:(i%NBCOULEURSFANTOME)):(i%NBCOULEURSFANTOME)))
#define COULEURBONUS(i)   (i*(Jeu.Bonus.APrendre==CouleurBonus[i]))

#define POSITION (Col-Top10.Col0+(Row-Top10.Row0)*asEnTeteTop10.Length())
//---------------------------------------------------------------------------
enum type_zone_aff {score, vies, attirance, niveau, nb_bonus};
enum couleur_ftm {bleu, ciel, magenta, rouge, vert, gris};
enum elmt_valeur {val_ftm, val_pgm, val_bns, val_qrt};
//---------------------------------------------------------------------------
typedef struct
{
 int ColDeb, ColFin;
 bool Contient(const int Col) const { return (Col>=ColDeb)&&(Col<=ColFin); };
} zone_affichage;
//---------------------------------------------------------------------------
class msg_statut
{
 private:
  bool MessageEstEnCours();
 public:
  int Deroulement, DebutMsg, Ligne, NbLignes, DebutMsgPrmLigne;
  AnsiString asMsg, asResteMsg, asMsgPrmLigne;
  msg_statut() { Deroulement=DEBMSGSANSEFFACER; asMsg=""; }; // Pas de message à dérouler = -1
  ~msg_statut();
  void Affiche(const int Ligne, const AnsiString asMsg);
  void DerouleMessage();
  __property bool MessageEnCours = {read=MessageEstEnCours};
};
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// Composants gérés par l'EDI
  TTimer *TimerJeu;
  TTimer *TimerMsg;
  TDrawGrid *DrawGridJeu;
  TDrawGrid *DrawGridMsg;
  TMainMenu *MainMenu;
  TMenuItem *MenuItemPartie;
  TMenuItem *MenuItemJouer;
  TMenuItem *MenuItemParametres;
  TMenuItem *MenuItemDimensions;
  TMenuItem *MenuItemDimensions3;
  TMenuItem *MenuItemDimensions2;
  TMenuItem *MenuItemDimensions1;
  TMenuItem *MenuItemAgressivite;
  TMenuItem *MenuItemVitesse1;
  TMenuItem *MenuItemVitesse2;
  TMenuItem *MenuItemVitesse3;
  TMenuItem *MenuItemNbPilules;
  TMenuItem *MenuItem50Pilules;
  TMenuItem *MenuItem100Pilules;
  TMenuItem *MenuItem200Pilules;
  TMenuItem *MenuItemVulnerabilite;
  TMenuItem *MenuItemVulnerabilite1;
  TMenuItem *MenuItemVulnerabilite2;
  TMenuItem *MenuItemVulnerabilite3;
  TMenuItem *MenuItemFantomesDepart;
  TMenuItem *MenuItemFantomesDepart3;
  TMenuItem *MenuItemFantomesDepart4;
  TMenuItem *MenuItemFantomesDepart6;
  TMenuItem *MenuItemFantomesDepart5;
  TMenuItem *MenuItemNbPortes;
  TMenuItem *MenuItem1PortesPour2lignes;
  TMenuItem *MenuItem2PortesPour2lignes;
  TMenuItem *MenuItem3PortesPour2lignes;
  TMenuItem *MenuItemInfo;
  TMenuItem *MenuItemAPropos;
  TMenuItem *MenuItemCommandes;
  TActionList *ActionList;
  TAction *ActionPartieJouer;
  TAction *ActionParamDimensions80x50;
  TAction *ActionParamDimensions64x40;
  TAction *ActionParamDimensions48x30;
  TAction *ActionParamAgressivite50;
  TAction *ActionParamAgressivite33;
  TAction *ActionParamAgressivite25;
  TAction *ActionParamPilulesParPacgum100;
  TAction *ActionParamPilulesParPacgum150;
  TAction *ActionParamPilulesParPacgum50;
  TAction *ActionParamVulnerabilite25Cases;
  TAction *ActionParamVulnerabilite50Cases;
  TAction *ActionParamVulnerabilite100Cases;
  TAction *ActionParamDepartFantomes3;
  TAction *ActionParamDepartFantomes4;
  TAction *ActionParamDepartFantomes5;
  TAction *ActionParamDepartFantomes6;
  TAction *ActionParamPortes1Pour150Cases;
  TAction *ActionParamPortes1Pour75Cases;
  TAction *ActionParamPortes1Pour50Cases;
  TAction *ActionInfosAPropos;
  TAction *ActionInfosCommandes;
  TDrawGrid *DrawGridPts;
  TAction *ActionInfosRegleDuJeu;
  TMenuItem *Rgledujeu1;
  TAction *ActionInfosLegende;
  TMenuItem *Lgende1;
  TTimer *TimerDemo;
  TAction *ActionParamDimensions96x60;
  TMenuItem *MenuItemDimensions4;
  TAction *ActionParamDimensions112x70;
  TMenuItem *MenuItemDimensions5;
  TAction *ActionInfosTop10;
  TTimer *TimerTop10;
  TMenuItem *Top101;
  TMenuItem *MenuItemSeparatorA;
  TAction *ActionParamEnregistrer;
  TMenuItem *ActionParamEnregistrer1;
  TAction *ActionParamRestaurer;
  TMenuItem *Restaurerlesparamtrespardfaut1;
  TAction *ActionParamReinitialiserTop10;
  TMenuItem *RinitialiserleTop101;
	TVirtualImageList *VirtualImageListJeu;
	TImageCollection *ImageCollection;
	TVirtualImageList *VirtualImageListMsg;
  void __fastcall ActionDimensionsExecute(TObject *Sender);
  void __fastcall DrawGridMsgDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
  void __fastcall TimerMsgTimer(TObject *Sender);
  void __fastcall ActionInfosAProposExecute(TObject *Sender);
  void __fastcall ActionAgressiviteExecute(TObject *Sender);
  void __fastcall Action1PGxxxPExecute(TObject *Sender);
  void __fastcall ActionxxCasesExecute(TObject *Sender);
  void __fastcall ActionDepartFantomesExecute(TObject *Sender);
  void __fastcall DrawGridJeuDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
  void __fastcall ActionPartieJouerExecute(TObject *Sender);
  void __fastcall ActionInfosCommandesExecute(TObject *Sender);
  void __fastcall ActionParamPortesNPour2LignesExecute(TObject *Sender);
  void __fastcall ActionInfosRegleDuJeuExecute(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall ActionInfosLegendeExecute(TObject *Sender);
  void __fastcall TimerDemoTimer(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall DrawGridPtsDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
  void __fastcall TimerJeuTimer(TObject *Sender);
  void __fastcall RedessineInfoJeu(type_zone_aff TypeZoneAff);
  void __fastcall ActionInfosTop10Execute(TObject *Sender);
  void __fastcall TimerTop10Timer(TObject *Sender);
  void __fastcall ActionParamEnregistrerExecute(TObject *Sender);
  void __fastcall ActionParamRestaurerExecute(TObject *Sender);
  void __fastcall ActionParamReinitialiserTop10Execute(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// Déclarations de l'utilisateur
  int DeroulementDemarrage, DeroulementTop10;
  bool FJeuEnCours;
  void __fastcall Bienvenue();
  void __fastcall EffaceMessage();
  void __fastcall ChangeAccesParametres(bool Activation);
  void __fastcall PlaceCaractere(TDrawGrid *DrawGrid, TRect &Rect, const char Caractere);
  void __fastcall PlaceCaractereInfoJeu(TRect &Rect, int ACol);
  void __fastcall RedessineInfosJeu();
  void __fastcall RedessineCaractereInfosJeu(int x);
  void __fastcall AfficheInfosJeuDepart();
  void __fastcall DerouleAffichageInfosJeu();
  void __fastcall RedessineCaractereTop10(int x);
  void __fastcall DerouleAffichageTop10();
protected:
  void __fastcall ArreteOuDemarreJeu(bool DemarreJeu);
  bool __fastcall IndiqueSiJeuEnCours() { return FJeuEnCours; };
public:		// Déclarations de l'utilisateur
  bool SansDemo;
  __fastcall TFormMain(TComponent* Owner);
  void __fastcall RedessineCases();
  void __fastcall RedessineCase(int x, int y);
  void __fastcall RedessineCase(int x, int y, int id);
  void __fastcall RedessineCaracteres();
  void __fastcall RedessineCaractere(int x, int y);
  void __fastcall InformeValeurElement(elmt_valeur Element);
  void __fastcall PlaceCaractereTop10(TRect &Rect, int Col, int Row);
  void __fastcall AfficheTop10(TRect &Rect, int Col, int Row);
  void __fastcall EnregistreParametres();
  __property bool JeuEnCours = {read=IndiqueSiJeuEnCours, write=ArreteOuDemarreJeu, default=false};
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
extern msg_statut MsgStatut;
extern top10 Top10;
extern const AnsiString asEnTeteTop10;
//---------------------------------------------------------------------------
#endif
