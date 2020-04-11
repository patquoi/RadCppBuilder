//---------------------------------------------------------------------------

#ifndef main_fH
#define main_fH
//---------------------------------------------------------------------------
#include "base.h"
#include <stdio.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <IniFiles.hpp>
#include <System.ImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.VirtualImageList.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// Composants gérés par l'EDI
  TStatusBar *StatusBar;
  TMainMenu *MainMenu;
  TMenuItem *MenuItemNouvellePartie;
  TMenuItem *MenuItemInformations;
  TPaintBox *PaintBox;
  TPopupMenu *PopupMenuPlacer;
  TMenuItem *MenuItemPlacer0h;
  TMenuItem *MenuItemPlacer2h;
  TMenuItem *MenuItemPlacer4h;
  TMenuItem *MenuItemPlacer6h;
  TMenuItem *MenuItemPlacer8h;
  TMenuItem *MenuItemPlacer10h;
  TPanel *PanelDroite;
  TRichEdit *RichEdit;
  TPanel *PanelMilieu;
  TLabel *LabelLettresAPlacer;
  TTimer *TimerAfficheMotsTrouves;
  TMenuItem *MenuItemPartie;
  TMenuItem *MenuItemOuvrir;
  TMenuItem *MenuItemEnregistrer;
  TMenuItem *MenuItemEnregistrerSous;
  TMenuItem *MenuItemQuitter;
  TOpenDialog *OpenDialog;
  TSaveDialog *SaveDialog;
  TMenuItem *MenuItemAPropos;
  TMenuItem *MenuItemAction;
  TMenuItem *MenuItemPasserSonTour;
  TMenuItem *MenuItemAide;
  TMenuItem *MenuItemOptions;
  TMenuItem *MenuItemOptionsPolice;
  TFontDialog *FontDialog;
  TMenuItem *MenuItemOptionsCouleurFond;
  TColorDialog *ColorDialog;
        TTimer *TimerReflexion;
	TImageCollection *ImageCollection;
	TVirtualImageList *VirtualImageList;
  void __fastcall PaintBoxMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
  void __fastcall PaintBoxPaint(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall PaintBoxClick(TObject *Sender);
  void __fastcall TimerAfficheMotsTrouvesTimer(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall MenuItemNLettresClick(TObject *Sender);
  void __fastcall MenuItemNouvellePartieClick(TObject *Sender);
  void __fastcall MenuItemPlacerClick(TObject *Sender);
  void __fastcall MenuItemQuitterClick(TObject *Sender);
  void __fastcall MenuItemOuvrirClick(TObject *Sender);
  void __fastcall MenuItemEnregistrerClick(TObject *Sender);
  void __fastcall MenuItemAProposClick(TObject *Sender);
  void __fastcall MenuItemPasserSonTourClick(TObject *Sender);
  void __fastcall MenuItemAideClick(TObject *Sender);
  void __fastcall MenuItemOptionsPoliceClick(TObject *Sender);
  void __fastcall MenuItemOptionsCouleurFondClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
        void __fastcall StatusBarDrawPanel(TStatusBar *StatusBar,
          TStatusPanel *Panel, const TRect &Rect);
        void __fastcall TimerReflexionTimer(TObject *Sender);
private:	// Déclarations de l'utilisateur
  TIniFile *IniFile; // v0.9.3
  TColor FBackColor; // v0.9.3
  String FFontName; // v1.4 FontName is a property now !
  void SetBackColor(const TColor NewBackColor) { FBackColor = NewBackColor; Color=NewBackColor; PaintBox->Color=NewBackColor; RichEdit->Color=NewBackColor; };
  void SetFontName(const String NewFontName) { FFontName = NewFontName; PaintBox->Font->Name=NewFontName; LabelLettresAPlacer->Font->Name=NewFontName; }; // v1.4 FontName is a property now !
  bool OuvertureAuto;
  void LitParametres(); // v0.9.3
  void EcritParametres(); // v0.9.3
  void DessineTout(bool EffaceFond);
  void PassageAuCampSuivant();
  void ComptabiliseMotsFormes();
  void AffichePoseLettres(int x, int y, direction d);
  void AfficheCapitalisation(int x, int y);
  void TireTrait(int DebutLignePrc);
  void AfficheEnTeteProprietesMotForme();
  void AfficheTotalProprietesMotsFormes();
  void AfficheProprietesMotForme(int iMot);
  void AfficheScores();
  bool Charge(int f);
  bool Sauve(int f);
  int NbLignes(); // v1.4 : décalage dans le formatage des ligne, dans SelStart, il faut retrancher 1 par retour à la ligne.
public:
  __property TColor BackColor = { read=FBackColor, write=SetBackColor, nodefault}; // v0.9.3
  __property String FontName = { read=FFontName, write=SetFontName, nodefault}; // v1.4 FontName is a property now !
  __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
