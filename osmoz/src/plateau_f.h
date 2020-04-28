//---------------------------------------------------------------------------
#ifndef plateau_fH
#define plateau_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <IniFiles.hpp>
#include "curseurs.h"
//---------------------------------------------------------------------------
#define BLANC   0
#define BLEU    1
#define VERT    2
#define CIEL    3
#define ROUGE   4
#define MAGENTA 5
#define JAUNE   6
//---------------------------------------------------------------------------
#define FONCE 0
#define CLAIR 1
//---------------------------------------------------------------------------
enum situation : char {aucune_situation, choix_lettre, choix_case, decompte_points};
enum phase : char {aucune_phase, pose, deplacement}; // Se combine avec choix_lettre et choix_case pour pose et deplacement
//---------------------------------------------------------------------------
class TfrmPlateau : public TForm
{
__published:	// Composants gérés par l'EDI
    TMainMenu *MainMenu;
    TMenuItem *MenuPartie;
    TMenuItem *RubriqueNouvelle;
    TMenuItem *MenuInfos;
    TMenuItem *RubriqueAide;
    TMenuItem *RubriqueAPropos;
    TStatusBar *StatusBar;
    TMenuItem *Sep1;
    TMenuItem *RubriquePasserSonTour;
    TMenuItem *RubriqueContinuer;
    TMenuItem *RubriqueOuvrir;
    TMenuItem *RubriqueEnregistrer;
    TMenuItem *RubriqueEnregistrerSous;
    TOpenDialog *OpenDialog;
    TSaveDialog *SaveDialog;
    TMenuItem *MenuOptions;
    TMenuItem *RubriqueJoueurs;
    TMenuItem *Sep2;
    TMenuItem *Sep3;
    TMenuItem *RubriqueQuitter;
    TMenuItem *RubriqueAutomates;
    TMenuItem *Sep4;
    TMenuItem *RubriqueEnregistrerMessages;
    TTimer *Timer;
    TMenuItem *RubriqueInterrompre;
    TMenuItem *RubriqueRecords;
    TMenuItem *Sep0;
	TMenuItem *RubriquePolice;
	TFontDialog *FontDialog;
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    
    void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall RubriquePasserSonTourClick(TObject *Sender);
    void __fastcall RubriqueNouvelleClick(TObject *Sender);
    void __fastcall RubriqueContinuerClick(TObject *Sender);
    void __fastcall RubriqueOuvrirClick(TObject *Sender);
    
    void __fastcall RubriqueEnregistrerClick(TObject *Sender);
    void __fastcall RubriqueEnregistrerSousClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    
    
    
    void __fastcall RubriqueJoueursClick(TObject *Sender);
    void __fastcall RubriqueAProposClick(TObject *Sender);
    
    void __fastcall RubriqueEnregistrerMessagesClick(TObject *Sender);
    void __fastcall RubriqueQuitterClick(TObject *Sender);

    void __fastcall RubriqueAutomatesClick(TObject *Sender);
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall RubriqueInterrompreClick(TObject *Sender);
    void __fastcall RubriqueAideClick(TObject *Sender);
    void __fastcall MenuPartieClick(TObject *Sender);
    void __fastcall MenuOptionsClick(TObject *Sender);
    void __fastcall RubriqueRecordsClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall RubriquePoliceClick(TObject *Sender);
    

private:	// Déclarations de l'utilisateur
	// v4.6 : ajout d'options
	TIniFile *IniFile;

	HICON crSmz[NBCURSEURS]; // v4.5 : On crée les curseurs
	situation Sit;

	// v4.6 : ajout d'options

	// v4.6 : ajout options
	void LitParametres();
	void EcritParametres();

	void ChangeSituation(situation NvSit);
	bool EnregistrerMessages;
public:		// Déclarations de l'utilisateur
	phase Phase;
	__property situation Situation = {read=Sit, write=ChangeSituation};

	int xCrt, yCrt, // Coordonnées de la dernière case mise en évidence (curseur dessus)
        xCase, yCase, // Coordonnées de la dernière case sélectionnable (curseur dessus et case valide pour opération en cours)
        xLAD, yLAD; // Coordonnées de la lettre en cours de déplacement
    char LettreAPoser,    // Lettre courante/sélectionnée (mise en évidence sur le jeu ou à poser)
         LettreADeplacer; // Lettre courante/sélectionnée (mise en évidence sur le plateau ou à déplacer)
    __fastcall TfrmPlateau(TComponent* Owner);
    void DessineHexagone(int x, int y, int Couleur, int Contraste); // v3.3
    void AfficheValeurs(int x, int y, char Lettre, int Score, int Fond, TColor Couleur);
    void AfficheCoordonnees();
    void EffaceSelectionCouranteLettre(bool GardeLettre);
    void EffaceSelectionCouranteCase(bool GardeCase);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPlateau *frmPlateau;

extern const TColor clJo[7][2];
extern const char stNomFichierIni[]; // v4.6
//---------------------------------------------------------------------------
#endif
