//---------------------------------------------------------------------------
#ifndef plt_fH
#define plt_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Registry.hpp>
#include "base.h"
#include "tourniv.h"
#include <ImgList.hpp>
#include <System.ImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.VirtualImageList.hpp>

#define XG DrawGrid->Col
#define YG DrawGrid->Row
#define NBMAXCARAFF ((StatusBar->Panels->Items[0]->Width-2)/7)

// Icônes des bêtes : (B)ête (E)ntière | (D)ébut|(F)in,(L)ong|(C)ourt
#define I_BEN 28
#define I_BEE 29
#define I_BES 30
#define I_BEO 31
#define I_DLN 32
#define I_DLE 33
#define I_DLS 34
#define I_DLO 35
#define I_FLN 36
#define I_FLE 37
#define I_FLS 38
#define I_FLO 39
#define I_DCN 40
#define I_DCE 41
#define I_DCS 42
#define I_DCO 43
#define I_FCN 44
#define I_FCE 45
#define I_FCS 46
#define I_FCO 47
// v1.7 : prise en compte du HDPI
#define DXAFF_NEFFET (int)(0.5+(33*Screen->PixelsPerInch)/96)
#define DXAFF_LEFFET (int)(0.5+(62*Screen->PixelsPerInch)/96)
#define DXAFF_NRESTE (int)(0.5+(96*Screen->PixelsPerInch)/96)
#define DXAFF_LRESTE (int)(0.5+(131*Screen->PixelsPerInch)/96)
#define DXAFF_NTEMPS (int)(0.5+(180*Screen->PixelsPerInch)/96)
#define DXAFF_LTEMPS (int)(0.5+(219*Screen->PixelsPerInch)/96)
#define DXAFF_NBARRE (int)(0.5+(282*Screen->PixelsPerInch)/96)
#define DXAFF_LBARRE (int)(0.5+(315*Screen->PixelsPerInch)/96)
#define DXAFF_NSCORE (int)(0.5+(380*Screen->PixelsPerInch)/96)
#define DXAFF_LSCORE (int)(0.5+(415*Screen->PixelsPerInch)/96)
#define DXAFF_NNIV   (int)(0.5+(453*Screen->PixelsPerInch)/96)
#define DXAFF_LNIV   (int)(0.5+(491*Screen->PixelsPerInch)/96)

//---------------------------------------------------------------------------
enum mode {neant, jeu, editeur};
enum affichage {aff_rien, aff_serie, aff_niv, aff_score=4, aff_barre=8, aff_temps=16, aff_reste=32, aff_effet=64, aff_tout=127};
enum type_aff_msg {ligne_statut, boite_dialogue};

class TfrmPlateau : public TForm
{
__published:	// Composants gérés par l'EDI
    TDrawGrid *DrawGrid;
    TMainMenu *MainMenu;
    TMenuItem *MenuPartie;
    TMenuItem *RubriqueNouvelle;
    TMenuItem *RubriqueOuvrir;
    TMenuItem *MenuAffichage;
    TMenuItem *MenuInformations;
    TMenuItem *RubriqueAPropos;
    TMenuItem *RubriqueRDJetUTL;
    TMenuItem *MenuEditeur;
    TMenuItem *RubriqueNouveauNiveau;
    TMenuItem *RubriqueOuvrirNiveau;
    TMenuItem *RubriqueEnregistrerNiveau;
    TMenuItem *MenuMode;
    TMenuItem *RubriqueJeu;
    TMenuItem *RubriqueEditeur;
    TMenuItem *RubriqueTesterNiveau;
    TPopupMenu *PopupMenuEditeur;
    TMenuItem *RubriquePoserMur;
    TMenuItem *RubriqueLibererEspace;
    TMenuItem *Sep3;
    TMenuItem *RubriquePoserPorteO;
    TMenuItem *RubriquePoserPorteF;
    TMenuItem *Sep4;
    TMenuItem *RubriquePoserDeclencheurB;
    TMenuItem *RubriquePoserDeclencheurR;
    TMenuItem *Sep6;
    TMenuItem *RubriquePoserRetirerBete;
    TMenuItem *RubriqueOrienterBeteD;
    TMenuItem *RubriqueOrienterBeteG;
    TStatusBar *StatusBar;
    TOpenDialog *OpenDialogNiveau;
    TSaveDialog *SaveDialogNiveau;
    TMenuItem *RubriqueParametresNiveau;
    TTimer *TimerMsg;
    TPanel *PanelScores;
    TLabel *LabelScore0;
    TLabel *LabelScore;
    TLabel *LabelBarre0;
    TLabel *LabelBarre;
    TLabel *LabelNiveau0;
    TLabel *Label3;
    TLabel *LabelSerie;
    TLabel *LabelNiveau;
    TLabel *LabelTemps0;
    TLabel *LabelTemps;
    TLabel *LabelReste0;
    TLabel *LabelReste;
    TLabel *LabelEffet0;
    TLabel *LabelEffet;
    TTimer *TimerJeu;
    TMenuItem *RubriqueInterrompreNiveau;
    TPopupMenu *PopupMenuJeu;
    TMenuItem *RubriquePorteDroite;
    TMenuItem *RubriquePorteHaut;
    TMenuItem *RubriquePorteBas;
    TMenuItem *RubriquePorteGauche;
    TMenuItem *RubriqueNord;
    TMenuItem *SepA;
    TMenuItem *RubriqueEst;
    TMenuItem *RubriqueSud;
    TMenuItem *RubriqueOuest;
    TMenuItem *SepB;
    TMenuItem *SepC;
    TMenuItem *SepD;
    TMenuItem *TitreMenuAction;
    TMenuItem *RubriqueRecords;
    TMenuItem *SepG;
    TMenuItem *MenuMessages;
    TMenuItem *RubriqueMsgLigneStatut;
    TMenuItem *RubriqueMsgBoiteDialogue;
    TMenuItem *MenuAffEditeur;
    TMenuItem *RubriqueQuadrillage;
    TMenuItem *Sep9;
    TMenuItem *RubriqueBetes;
    TMenuItem *RubriquePortes;
    TMenuItem *RubriqueDeclencheurs;
    TMenuItem *SepF;
    TMenuItem *RubriqueTout;
    TMenuItem *RubriqueCouleurCurseur;
    TColorDialog *ColorDialog;
    TMenuItem *RubriqueQuitter;
    TMenuItem *RubriqueOuvrirNiveauPrecedent;
    TMenuItem *RubriqueOuvrirNiveauSuivant;
    TMenuItem *Sep2;
    TMenuItem *Sep1;
    TMenuItem *RubriqueInterrompre;
    TMenuItem *Sep5;
    TMenuItem *Sep7;
    TMenuItem *Sep8;
    TMenuItem *RubriquePartiesSauvegardees;
    TMenuItem *RubriqueChangerSerie;
    TMenuItem *MenuOptions;
    TMenuItem *RubriqueCommandes;
    TMenuItem *SepH;
    TMenuItem *SepI;
    TMenuItem *SepJ;
    TMenuItem *SepK;
    TMenuItem *SepL;
    TMenuItem *SepM;
    TMenuItem *SepN;
    TMenuItem *SepO;
    TMenuItem *SepP;
    TMenuItem *SepQ;
    TMenuItem *SepR;
    TMenuItem *SepS;
	TImageCollection *ImageCollection;
	TVirtualImageList *VirtualImageList;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall DrawGridDrawCell(TObject *Sender, int Col, int Row,
          TRect &Rect, TGridDrawState State);
    void __fastcall RubriqueQuitterClick(TObject *Sender);
    void __fastcall RubriqueJeuClick(TObject *Sender);
    void __fastcall RubriqueEditeurClick(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall RubriquePoserMurClick(TObject *Sender);
    void __fastcall RubriqueLibererEspaceClick(TObject *Sender);
    void __fastcall RubriquePoserPorteOClick(TObject *Sender);
    void __fastcall RubriquePoserPorteFClick(TObject *Sender);
    void __fastcall RubriquePoserDeclencheurBClick(TObject *Sender);
    void __fastcall RubriquePoserDeclencheurRClick(TObject *Sender);
    void __fastcall RubriquePoserRetirerBeteClick(TObject *Sender);
    void __fastcall RubriqueOrienterBeteGClick(TObject *Sender);
    void __fastcall RubriqueOrienterBeteDClick(TObject *Sender);
    void __fastcall DrawGridClick(TObject *Sender);
    void __fastcall RubriqueQuadrillageClick(TObject *Sender);
    void __fastcall RubriqueBetesClick(TObject *Sender);
    void __fastcall RubriquePortesClick(TObject *Sender);
    void __fastcall RubriqueDeclencheursClick(TObject *Sender);
    void __fastcall RubriqueToutClick(TObject *Sender);
    void __fastcall RubriqueOuvrirNiveauClick(TObject *Sender);
    void __fastcall RubriqueEnregistrerNiveauClick(TObject *Sender);
    void __fastcall RubriqueParametresNiveauClick(TObject *Sender);
    void __fastcall TimerMsgTimer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    
    
    void __fastcall RubriqueNouveauNiveauClick(TObject *Sender);
    void __fastcall RubriqueTesterNiveauClick(TObject *Sender);
    void __fastcall RubriqueInterrompreNiveauClick(TObject *Sender);
    
    void __fastcall TimerJeuTimer(TObject *Sender);
    
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    
    void __fastcall RubriquePorteHautClick(TObject *Sender);
    void __fastcall RubriquePorteDroiteClick(TObject *Sender);
    void __fastcall RubriquePorteBasClick(TObject *Sender);
    void __fastcall RubriquePorteGaucheClick(TObject *Sender);
    void __fastcall RubriqueNordClick(TObject *Sender);
    void __fastcall RubriqueEstClick(TObject *Sender);
    void __fastcall RubriqueSudClick(TObject *Sender);
    void __fastcall RubriqueOuestClick(TObject *Sender);
    
    void __fastcall DrawGridMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall RubriqueAProposClick(TObject *Sender);
    void __fastcall DrawGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall RubriqueRecordsClick(TObject *Sender);
    void __fastcall RubriqueMsgLigneStatutClick(TObject *Sender);
    void __fastcall RubriqueMsgBoiteDialogueClick(TObject *Sender);
    
    void __fastcall RubriqueRDJetUTLClick(TObject *Sender);
    void __fastcall RubriqueCouleurCurseurClick(TObject *Sender);
    
    void __fastcall RubriqueOuvrirNiveauPrecedentClick(TObject *Sender);
    void __fastcall RubriqueOuvrirNiveauSuivantClick(TObject *Sender);
    
    
    void __fastcall RubriqueInterrompreClick(TObject *Sender);
    void __fastcall RubriqueNouvelleClick(TObject *Sender);
    void __fastcall RubriqueOuvrirClick(TObject *Sender);
    void __fastcall RubriquePartiesSauvegardeesClick(TObject *Sender);
    
    void __fastcall RubriqueChangerSerieClick(TObject *Sender);
    
    
    void __fastcall RubriqueCommandesClick(TObject *Sender);
    void __fastcall DrawGridKeyPress(TObject *Sender, char &Key);
private:	// Déclarations de l'utilisateur
    TRegistry *Registry;
    TIniFile *IniFile;
    mode ModePrg;
    bool LancementEnCours,
         SortieAutorisee,
         ChargementAuto,
         Charge1erNiveau;
	String stMsgCrt;
	String stChnAff;
    int PosCrtMsg;
    TThreadTour *ThreadTour;
    __fastcall mode LitMode() { return ModePrg; };
    void __fastcall ChangeMode(mode NvMode);
    __fastcall bool JeuEstEnCours() { return LancementEnCours; }; // Lecture de la propriété JeuEnCours
    void __fastcall DemarreArreteJeu(bool LancerNiveau);
public:		// Déclarations de l'utilisateur
    bool AffichageAutorise,
         PartieEnCours;
	long NumIdPartie;
	String stNomSerieNiveau,
		   stNomFichierNiveau,
		   stCommentaire,
           stNomJoueur;
    type_aff_msg TypeAffMsg;
    __property mode Mode = {read=LitMode, write=ChangeMode};
    __property bool JeuEnCours = {read=JeuEstEnCours, write=DemarreArreteJeu};
    __fastcall TfrmPlateau(TComponent* Owner);
    void RedessineCase(int x, int y, bool EffaceFond);
	void AfficheMessage(String stMsg, int Flag);
    void RafraichitParametres(affichage Affichage);
    void ChargeAutomatiquement();
    void ChangeSerie();
    bool ChargePremierNiveau();
    void RafraichitTitre(bool JeuEnPause);
    void LitParametres(); // v1.6
    void EcritParametreCommandes(const int Commandes); // v1.6
    void EcritParametreCouleurCurseur(const TColor CouleurCurseur); // v1.6
    void InitialiseCommandes(const int Commandes); // v1.6
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPlateau *frmPlateau;

extern const String stTitre[2],
				 stTesterNiveau,
                 stArreterNiveau,
                 stInterrompreNiveau,
                 stContinuerNiveau,
                 stInterrompre,
                 stContinuer,
                 stNouvelle,
                 stArreter,
                 stRien,
                 stTout,
                 stVide,
                 stCleLeBerger,
                 stCleExtNLB,

                 stExtNLB,
                 stCleTypeNLB,
                 stDesignationNLB,

                 stCleShell,
                 stCleOpen,
                 stCleCommand,
                 stCleDefaultIcon,

                 stOpenDialogDefaultExt[2],
                 stOpenDialogFilter[2],
                 stOpenDialogFileName[2],
                 stOpenDialogTitle[2];

extern const int NumIconeBete[NBDIR][NBDECAL][2];

extern String CrypteCheminFichierPartie(String stCheminFichierPartie);

//---------------------------------------------------------------------------
#endif
