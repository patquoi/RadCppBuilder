//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "main_f.h"
#include "param_f.h"
#include <Math.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
// Pour void plateau::DessineTout(bool)
//---------------------------------------------------------------------------
#define EFFACE_FOND               true
#define RAFRAICHIT                false
// Pour TForm::TireTrait(bool)
#define DOUBLE                    0
// Pour Cursor
#define CURSEUR_PLUS_1            1
#define NUMSTATUSPANELJOUEUR      2   // v0.9.4

#define CH(x) (((ch[x]==clYellow)||(ch[x]==clLime)||(ch[x]==clAqua))?ch[(x)+NBMAXCAMPS+1]:ch[x]) // v0.9.4 : pour mieux voir sur le fond gris
//---------------------------------------------------------------------------
// v1.4 : string au lieu de AnsiString
const char stSectionOptions[] = "Options";
const char stEntreePolice[] = "Police";
const char stEntreeGras[] = "Gras"; // v1.4.1 (ajout)
const char stEntreeFond[] = "Fond"; // v0.9.3
const char stNomFichierIni[] = "Osmotik.ini"; // v1.4.1
//---------------------------------------------------------------------------
// v1.4 Définition du curseur "+1" pour CreateCursor car LoadCursor ne marche pas !!!
BYTE ANDmaskCursor[] =
{
	0xFF, 0xFF, 0xFF, 0xFF,   // 1
	0xFF, 0xFF, 0xFF, 0xFF,   // 2
	0xFF, 0xFF, 0xFF, 0xFF,   // 3
	0xFF, 0xFF, 0xFF, 0x3F,   // 4

	0xFF, 0xFF, 0xFE, 0xDF,   // 5
	0xFF, 0xFF, 0xFD, 0xDF,   // 6
	0xFF, 0xFF, 0xFB, 0xDF,   // 7
	0xFF, 0xFF, 0xF7, 0xDF,   // 8

	0xFF, 0xFF, 0xEF, 0xDF,   // 9
	0xFF, 0xFF, 0xEF, 0xDF,   // 10
	0xFF, 0x1F, 0xEF, 0xDF,   // 11
	0xFE, 0xEF, 0xF1, 0xDF,   // 12

	0xFE, 0xEF, 0xFD, 0xDF,   // 13
	0xFE, 0xEF, 0xFD, 0xDF,   // 14
	0xFE, 0xEF, 0xFD, 0xDF,   // 15
	0xE0, 0xE0, 0xFD, 0xDF,   // 16

	0xDF, 0xFF, 0x7D, 0xDF,   // 17
	0xDF, 0xFF, 0x7D, 0xDF,   // 18
	0xDF, 0xFF, 0x7D, 0xDF,   // 19
	0xE0, 0xE0, 0xFD, 0xDF,   // 20

	0xFE, 0xEF, 0xFD, 0xDF,   // 21
	0xFE, 0xEF, 0xFD, 0xDF,   // 22
	0xFE, 0xEF, 0xFD, 0xDF,   // 23
	0xFE, 0xEF, 0xFD, 0xDF,   // 24

	0xFF, 0x1F, 0xF1, 0xC7,   // 25
	0xFF, 0xFF, 0xEF, 0xFB,   // 26
	0xFF, 0xFF, 0xEF, 0xFB,   // 27
	0xFF, 0xFF, 0xEF, 0xFB,   // 28

	0xFF, 0xFF, 0xF0, 0x07,   // 29
	0xFF, 0xFF, 0xFF, 0xFF,   // 30
	0xFF, 0xFF, 0xFF, 0xFF,   // 31
	0xFF, 0xFF, 0xFF, 0xFF    // 32
},
	 XORmaskCursor[] =
{
    0x00, 0x00, 0x00, 0x00,   // 1
	0x00, 0x00, 0x00, 0x00,   // 2
	0x00, 0x00, 0x00, 0x00,   // 3
	0x00, 0x00, 0x00, 0x00,   // 4

	0x00, 0x00, 0x00, 0xC0,   // 5
	0x00, 0x00, 0x01, 0xC0,   // 6
	0x00, 0x00, 0x03, 0xC0,   // 7
	0x00, 0x00, 0x07, 0xC0,   // 8

	0x00, 0x00, 0x0F, 0xC0,   // 9
	0x00, 0x00, 0x0F, 0xC0,   // 10
	0x00, 0x00, 0x0D, 0xC0,   // 11
	0x00, 0xE0, 0x01, 0xC0,   // 12

	0x00, 0xE0, 0x01, 0xC0,   // 13
	0x00, 0xE0, 0x01, 0xC0,   // 14
	0x00, 0xE0, 0x01, 0xC0,   // 15
	0x00, 0xE0, 0x01, 0xC0,   // 16

	0x1F, 0xFF, 0x01, 0xC0,   // 17
	0x1F, 0xFF, 0x01, 0xC0,   // 18
	0x1F, 0xFF, 0x01, 0xC0,   // 19
	0x00, 0xE0, 0x01, 0xC0,   // 20

	0x00, 0xE0, 0x01, 0xC0,   // 21
	0x00, 0xE0, 0x01, 0xC0,   // 22
	0x00, 0xE0, 0x01, 0xC0,   // 23
	0x00, 0xE0, 0x01, 0xC0,   // 24

	0x00, 0x00, 0x01, 0xC0,   // 25
	0x00, 0x00, 0x0F, 0xF8,   // 26
	0x00, 0x00, 0x0F, 0xF8,   // 27
	0x00, 0x00, 0x0F, 0xF8,   // 28

	0x00, 0x00, 0x00, 0x00,   // 29
	0x00, 0x00, 0x00, 0x00,   // 30
	0x00, 0x00, 0x00, 0x00,   // 31
	0x00, 0x00, 0x00, 0x00    // 32
};

//---------------------------------------------------------------------------
TFormMain *FormMain;
//---------------------------------------------------------------------------
// Méthodes privées
//---------------------------------------------------------------------------
void TFormMain::LitParametres() // v0.9.3
 {
  if ((IniFile=new TIniFile(stRepLocalAppData()+stNomFichierIni))) // v1.4 : stRepLocalAppData au lieu de ExtractFilePath(Application->ExeName. v1.4.1 : stNomFichierIni
   {
	PaintBox->Font->Name=IniFile->ReadString(stSectionOptions, stEntreePolice, L"Comic Sans MS"); // v1.4.1 : on affecte directement PaintBox->Font

	// v1.4.1 : ajout du style de la police (gras ou non)
	PaintBox->Font->Style=TFontStyles();
	if (IniFile->ReadBool(stSectionOptions, stEntreeGras, false))
	  PaintBox->Font->Style=PaintBox->Font->Style << fsBold;
	LabelLettresAPlacer->Font=PaintBox->Font;

	PaintBox->Color=(TColor)IniFile->ReadInteger(stSectionOptions, stEntreeFond, (int)clSilver); // v1.4.1 : on affecte directement PaintBox->Color
	RichEdit->Color=PaintBox->Color;

	delete IniFile;
   }
 }
//---------------------------------------------------------------------------
void TFormMain::EcritParametres() // v0.9.3
 {
  if ((IniFile=new TIniFile(stRepLocalAppData()+stNomFichierIni))) // v1.4 : stRepLocalAppData au lieu de ExtractFilePath(Application->ExeName. v1.4.1 : stNomFichierIni
   {
	IniFile->WriteString(stSectionOptions, stEntreePolice, PaintBox->Font->Name); // v1.4.1 : on va directement voir PaintBox->Font

	// v1.4.1 : ajout du style (gras ou non) et de la taille de la police
	IniFile->WriteBool(stSectionOptions, stEntreeGras, PaintBox->Font->Style.Contains(fsBold));

	IniFile->WriteInteger(stSectionOptions, stEntreeFond, (int)PaintBox->Color); // v1.4.1 : on va directement voir PaintBox->Color
	delete IniFile;
   }
 }
//---------------------------------------------------------------------------
void TFormMain::DessineTout(bool EffaceFond)
 {
  if (EffaceFond)
   {
    PaintBox->Canvas->Brush->Color=Color;
    PaintBox->Canvas->FillRect(Rect(0,0,PaintBox->Width,PaintBox->Height));
   }
  if (P)
   {
    P->DefinitEchelle(PaintBox->Width, PaintBox->Height);
    P->DessineTout(PaintBox->Canvas);
   }
 }
//---------------------------------------------------------------------------
void TFormMain::PassageAuCampSuivant()
 {
  bool PlateauRempli=(!P->NbCasesLibres),
       Abandon=(P->NbAbandons==NbCamps[P->CfgDep]);
  LabelLettresAPlacer->Caption="";
  /*
  AnsiString asMsg=Format("Il reste %d case(s)", ARRAYOFCONST((P->NbCasesLibres)));
  RichEdit->Lines->Add(asMsg);*/
  if ((((int)P->CampCrt)==NbCamps[P->CfgDep])||
      PlateauRempli||Abandon)
   {
    if (PlateauRempli||Abandon)
     {
      int DebutLigne=RichEdit->Text.Length() - NbLignes(); // v1.4 décalage de 1 par retour à la ligne
      AnsiString asMsg="PARTIE TERMINÉE";
      RichEdit->Lines->Add(asMsg);
	  RichEdit->SelStart=DebutLigne;
      RichEdit->SelLength=asMsg.Length();
      RichEdit->SelAttributes->Style = RichEdit->SelAttributes->Style << fsBold;
      P->PartieEnCours=false;
     }
    AfficheScores();
    if (PlateauRempli||Abandon) return;
   }
  P->InitialiseTourSuivant();
  DessineTout(RAFRAICHIT);
 }
//---------------------------------------------------------------------------
void TFormMain::ComptabiliseMotsFormes()
 {
  P->iMotForme=0; // Sert à savoir à quel mot on a à faire
  TimerAfficheMotsTrouves->Enabled=true; // C'est le timer qui s'occupe de tout !
 }
//---------------------------------------------------------------------------
void TFormMain::AffichePoseLettres(int x, int y, direction d)
 {
  int DebutLigne=RichEdit->Text.Length() - NbLignes(); // v1.4 décalage de 1 par retour à la ligne
  AnsiString asMsg=Format( "%s (%d,%d) %dh",
                           ARRAYOFCONST(( LabelLettresAPlacer->Caption, x, y, 2*(int)(d-1))));
  RichEdit->Lines->Add(asMsg);
  RichEdit->SelStart=DebutLigne;
  RichEdit->SelLength=asMsg.Length();
  RichEdit->SelAttributes->Color=CH(P->CampCrt); // v0.9.4 : CH(x) au lieu de ch[x]
 }
//---------------------------------------------------------------------------
void TFormMain::AfficheCapitalisation(int x, int y)
 {
  int DebutLigne=RichEdit->Text.Length() - NbLignes(); // v1.4 décalage de 1 par retour à la ligne
  AnsiString asMsg=Format( "Capitalise %s (%d,%d)",
                           ARRAYOFCONST(( AnsiString(P->h[x][y].Lettre), x, y)));
  RichEdit->Lines->Add(asMsg);
  RichEdit->SelStart=DebutLigne;
  RichEdit->SelLength=asMsg.Length();
  RichEdit->SelAttributes->Color=CH(P->h[x][y].Camp); // v0.9.4 : CH(x) au lieu de ch[x]
 }
//---------------------------------------------------------------------------
void TFormMain::TireTrait(int DebutLignePrc)
 {
  int DebutLigne=RichEdit->Text.Length() - NbLignes(); // v1.4 décalage de 1 par retour à la ligne
  if (!DebutLignePrc)
   {
    RichEdit->Lines->Add("===========================");
	RichEdit->SelStart=DebutLigne;
	RichEdit->SelLength=27; // v1.4 : 27 au lieu de 21
    RichEdit->SelAttributes->Style = RichEdit->SelAttributes->Style << fsBold;
   }
  else
   {
	RichEdit->SelStart=DebutLignePrc;
    RichEdit->SelLength=DebutLigne-DebutLignePrc;
    RichEdit->SelAttributes->Style = RichEdit->SelAttributes->Style << fsUnderline;
   }
  RichEdit->SelStart=RichEdit->Text.Length() - NbLignes(); // v1.4 décalage de 1 par retour à la ligne
  RichEdit->SelLength=0;
 }
//---------------------------------------------------------------------------
void TFormMain::AfficheEnTeteProprietesMotForme()
 {
  int DebutLigne=RichEdit->Text.Length() - NbLignes(); // v1.4 décalage de 1 par retour à la ligne
  const AnsiString asMsg="\
Mot            Pts pa pp lp";
  RichEdit->Lines->Add(asMsg);
  TireTrait(DebutLigne);
 }
//---------------------------------------------------------------------------
void TFormMain::AfficheTotalProprietesMotsFormes()
 {
  bilan *b=&(_JCRT.BilanTour);
  int DebutLigne=RichEdit->Text.Length() - NbLignes(); // v1.4 décalage de 1 par retour à la ligne
  AnsiString asMsg=Format( "TOTAL           %2d %2d %2d %2d",
                           ARRAYOFCONST(( b->s, b->p, b->ppaa[0], b->lpaa[0])));
  RichEdit->Lines->Add(asMsg);
  RichEdit->SelStart=DebutLigne;
  RichEdit->SelLength=asMsg.Length();
  RichEdit->SelAttributes->Color=clBlack;
  RichEdit->SelAttributes->Style = RichEdit->SelAttributes->Style << fsBold;
  TireTrait(DOUBLE);
 }
//---------------------------------------------------------------------------
void TFormMain::AfficheProprietesMotForme(int iMot)
 {
  AnsiString asMot=_JCRT.slMotsFormes->Strings[iMot];
  proprietes_mot *pm=(proprietes_mot*)_JCRT.slMotsFormes->Objects[iMot];
  int DebutLigne=RichEdit->Text.Length() - NbLignes(); // v1.4 décalage de 1 par retour à la ligne
  RichEdit->Lines->Add( Format( "%-15s %2d %2d %2d %2d",
                                ARRAYOFCONST(( asMot,
                                               pm->Bilan.s, pm->Bilan.p, pm->Bilan.ppaa[0], pm->Bilan.lpaa[0]))));
  // On parfume les lettres
  for(int i=0; i<asMot.Length(); i++)
   {
	RichEdit->SelStart=DebutLigne+i;
    RichEdit->SelLength=1;
    RichEdit->SelAttributes->Color=CH(P->H(pm->x,pm->y,i,pm->d).Camp); // v0.9.4 : CH(x) au lieu de ch[x]
    if (P->LettrePosee(X(pm->x,i,pm->d), Y(pm->y,i,pm->d)))
     RichEdit->SelAttributes->Style = RichEdit->SelAttributes->Style << fsUnderline;
   }
 }
//---------------------------------------------------------------------------
void TFormMain::AfficheScores()
 {
  int nj[NBMAXCAMPS+1]={0,0,0,0,0,0,0}, // 0.8.3. Nombre de jetons
      cl[NBMAXCAMPS]={0,0,0,0,0,0},
	  DebutLigne=RichEdit->Text.Length() - NbLignes(); // v1.4 décalage de 1 par retour à la ligne
  RichEdit->Lines->Add( Format( "\
SCORES au TOUR %d\n\
Pts j paa laa ppa lpa",
								ARRAYOFCONST((P->TourCrt))));
  RichEdit->SelStart=DebutLigne;
  RichEdit->SelLength=17;
  RichEdit->SelAttributes->Style = RichEdit->SelAttributes->Style << fsBold;
  TireTrait(RichEdit->Text.Length() - NbLignes() - 23); // v1.4 décalage de 1 par retour à la ligne
  // On compte les jetons (v0.8.3)
  for(int i=0; i<2*P->N-1; i++)
   for(int j=0; j<2*P->N-1; j++)
    if (P->CoordonneesValides(i, j))
     nj[P->h[i][j].Camp]++;
  // On classe les joueurs
  for(int i=0; i<NbCamps[P->CfgDep]; i++)
   for(int j=0; j<NbCamps[P->CfgDep]; j++)
    cl[i]+= (J[i].BilanTotal.s<J[j].BilanTotal.s)||
            ((J[i].BilanTotal.s==J[j].BilanTotal.s)&&  // v0.8.3. NbJetons départage
             (nj[i+1]<nj[j+1]));
  for(int i=0; i<=NbCamps[P->CfgDep]; i++)
   for(int j=0; j<NbCamps[P->CfgDep]; j++)
    if (cl[j]==i)
     {
      AnsiString asMsg=Format( "%3d%3d%3d %3d %3d %3d",
                               ARRAYOFCONST(( J[j].BilanTotal.s,
                                              nj[j+1],
                                              J[j].BilanTotal.ppaa[0],
                                              J[j].BilanTotal.lpaa[0],
                                             -J[j].BilanTotal.pppa[0],
                                             -J[j].BilanTotal.lppa[0])));

	  DebutLigne=RichEdit->Text.Length() - NbLignes(); // v1.4 décalage de 1 par retour à la ligne
      RichEdit->Lines->Add(asMsg);
	  RichEdit->SelStart=DebutLigne;
      RichEdit->SelLength=asMsg.Length();
      RichEdit->SelAttributes->Color=CH(j+1); // v0.9.4 : CH(x) au lieu de ch[x]
      RichEdit->SelAttributes->Style = RichEdit->SelAttributes->Style << fsBold;
      RichEdit->SelStart=DebutLigne+3;
      RichEdit->SelLength=3;
      RichEdit->SelAttributes->Color=clBlack;
      RichEdit->SelAttributes->Style = RichEdit->SelAttributes->Style << fsBold;
     }
  TireTrait(DOUBLE);
 }
//---------------------------------------------------------------------------
bool TFormMain::Charge(int f) // v1.4 FileOpen/FileClose/int f au lieu de fopen/fclose/FILE *f
 {
  char szLettresAPlacer[NBLMAXMOTDICO+1]="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
  int l;
  if (P) { delete P; P=NULL; }
  P=new plateau();
  bool Ok=P&&LIT(Version)&&
		  LIT(l)&&
		  FileRead(f, szLettresAPlacer, l)&& // v1.4 FileRead au lieu de fread
		  P->Charge(f)&&
		  J[0].Charge(f)&&
		  J[1].Charge(f)&&
		  J[2].Charge(f)&&
		  J[3].Charge(f)&&
		  J[4].Charge(f)&&
		  J[5].Charge(f);
  if (Ok)
   LabelLettresAPlacer->Caption=AnsiString(szLettresAPlacer);
  return Ok;
 }
//---------------------------------------------------------------------------
bool TFormMain::Sauve(int f) // v1.4 FileOpen/FileClose/int f au lieu de fopen/fclose/FILE *f
 {
  char szLettresAPlacer[NBLMAXMOTDICO+1]="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
  int l=LabelLettresAPlacer->Caption.Length()+1;
  for(int i=1; i<l; i++) // Ici on ne peut pas se fier à AnsiString::c_str() à cause des adresses donc on recopie les lettres à la mimine
   szLettresAPlacer[i-1]=LabelLettresAPlacer->Caption[i];
  // Version=DRN_VERSION_SMT; // v0.9.4 : uniquement les nouvelles parties
  if ((double)P->TopChrono) // v0.9.4 : on comptabilise le temps écoulé si partie en cours
   {
	_JCRT.TempsEcoule+=(Now()-P->TopChrono);
	P->TopChrono=Now();
	StatusBar->Repaint();
   }
  return ECRIT(Version)&&
		 ECRIT(l)&&
		 FileWrite(f, szLettresAPlacer, l)&& // v1.4 FileRead au lieu de fread
		 P->Sauve(f)&&
		 J[0].Sauve(f)&&
		 J[1].Sauve(f)&&
		 J[2].Sauve(f)&&
		 J[3].Sauve(f)&&
		 J[4].Sauve(f)&&
		 J[5].Sauve(f);
 }
//---------------------------------------------------------------------------
int TFormMain::NbLignes() // v1.4 : décalage dans le formatage des ligne, dans SelStart, il faut retrancher 1 par retour à la ligne.
 {
  int n;
  TStringList *slText = new TStringList;
  slText->Text=RichEdit->Text;
  n=slText->Count;
  delete slText;
  return n;
 }
//---------------------------------------------------------------------------
// Evénements
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner)
{ // v1.4 : création du curseur "+1" à la volée sans passer par les ressources (LoadCursor ne marche pas)
 // HICON crPlus1=LoadCursorFromFile(String(ExtractFilePath(Application->ExeName)+"\\plus1.cur").c_str()); // Marche mais oblige à fournir le fichier .cur
 // HICON crPlus1=LoadCursor(HInstance, L"CURSOR_PLUS1"); // Ne marche pas !
 crPlus1=CreateCursor(HInstance, // app. instance
					  16, // horizontal position of hot spot
					  15, // vertical position of hot spot
					  32, // cursor width
					  32, // cursor height
					  ANDmaskCursor,     // AND mask
					  XORmaskCursor);   // XOR mask
 PaintBox->Canvas->TextFlags=ETO_OPAQUE;
 // v1.4 : on recalcul l'espace coordonnées à cause de la HDPI (au lieu de LARGEURESPACECOORDONNNEES
 StatusBar->Panels->Items[0]->Width=StatusBar->Width - StatusBar->Panels->Items[1]->Width
													 - StatusBar->Panels->Items[2]->Width
													 - StatusBar->Panels->Items[3]->Width
													 - StatusBar->Panels->Items[4]->Width
													 - StatusBar->Panels->Items[5]->Width
													 - StatusBar->Panels->Items[6]->Width
													 - StatusBar->Panels->Items[7]->Width;
 Screen->Cursors[CURSEUR_PLUS_1] = crPlus1;
 OpenDialog->InitialDir = stRepLocalAppData(); // v1.4
 SaveDialog->InitialDir = stRepLocalAppData(); // v1.4
 if ((OuvertureAuto=(ParamCount()>0)))
  {
   OpenDialog->FileName=ParamStr(1);
   MenuItemOuvrir->Click();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PaintBoxMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 if (!P) return;
 int Xs=P->Xh(X, Y),
     Ys=P->Yh(X, Y);
 if ((Xs!=P->Xs)||
	 (Ys!=P->Ys))
  {
   if (P->CoordonneesValides(Xs, Ys))
	{
	 if (P->LettreCapitalisable(Xs, Ys)&&(P->h[Xs][Ys].Camp==P->CampCrt))
	  Screen->Cursor=TCursor(CURSEUR_PLUS_1);
	 else
	  if (Screen->Cursor!=crDefault)
	   Screen->Cursor=crDefault;
	 PopupMenuPlacer->Tag= P->PartieEnCours&& // Permet l'affichage du menu Placer QUE Si partie en cours et case vide (pas de lettre)
						   (!P->FormationMotEnCours)&&
						   (!P->h[Xs][Ys].Lettre);
	 P->ChangeHexagoneCourant(PaintBox->Canvas, Xs, Ys);
	 StatusBar->Panels->Items[0]->Text=P->h[Xs][Ys].asContenu(); // v0.8.5. v0.9.4 : Affichage en tête
	 StatusBar->Panels->Items[1]->Text=Format( "(%d,%d)",
											   ARRAYOFCONST(( Xs,Ys)));
	}
   else
	{
	 if (Screen->Cursor!=crDefault)
	  Screen->Cursor=crDefault;
	 PopupMenuPlacer->Tag=0; // NE Permet PAS l'affichage du menu Placer
	 P->ChangeHexagoneCourant(PaintBox->Canvas, -1, -1);
	 StatusBar->Panels->Items[0]->Text=asVide; // v0.8.5. v0.9.4 : Affichage en tête
	 StatusBar->Panels->Items[1]->Text=asVide;
	}
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PaintBoxPaint(TObject *Sender)
{
 if (P) P->DessineTout(PaintBox->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormResize(TObject *Sender)
{
 // v1.4 : on recalcul l'espace coordonnées à cause de la HDPI (au lieu de LARGEURESPACECOORDONNNEES
 StatusBar->Panels->Items[0]->Width=StatusBar->Width - StatusBar->Panels->Items[1]->Width
													 - StatusBar->Panels->Items[2]->Width
													 - StatusBar->Panels->Items[3]->Width
													 - StatusBar->Panels->Items[4]->Width
													 - StatusBar->Panels->Items[5]->Width
													 - StatusBar->Panels->Items[6]->Width
													 - StatusBar->Panels->Items[7]->Width;
 if (P) DessineTout(RAFRAICHIT); // La fermeture de la fiche invoque FormResize, d'où le test sur P
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuItemNLettresClick(TObject *Sender)
{
 char BackSpace = '\b';
 P->NbMaxLettresAPlacer=((TMenuItem*)Sender)->Tag;
 while(LabelLettresAPlacer->Caption.Length()>P->NbMaxLettresAPlacer) // Par précaution mais en principe on ne change pas en plein mileu mais bon...
  FormKeyPress(this, BackSpace);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormKeyPress(TObject *Sender, char &Key)
{
 int l=LabelLettresAPlacer->Caption.Length();
 bool Effacement=(Key=='\b'),
      LettreSaisie=(UpperCase(Key)[1]>='A')&&(UpperCase(Key)[1]<='Z');
 if ((!P)||(!P->PartieEnCours)) return;
 // Saisie d'une lettre : réduction du capital de lettre
 if (LettreSaisie&&
     (l<P->NbMaxLettresAPlacer)&&
     (_JCRT.h[(int)(UpperCase(Key)[1]-'A')].Valeur))
  {
   LabelLettresAPlacer->Caption=LabelLettresAPlacer->Caption+UpperCase(Key);
   _JCRT.h[(int)(UpperCase(Key)[1]-'A')].Valeur--;
   P->DessineCapitalLettres(PaintBox->Canvas);
   return;
  }
 // Effacement d'une lettre : augmentation du capital de lettre
 if (Effacement&&l)
  {
   _JCRT.h[(int)(LabelLettresAPlacer->Caption[l]-'A')].Valeur++;
   LabelLettresAPlacer->Caption=LabelLettresAPlacer->Caption.SubString(1, l-1);
   P->DessineCapitalLettres(PaintBox->Canvas);
   return;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuItemNouvellePartieClick(TObject *Sender)
{
 FormParametres=new TFormParametres(Application);
 try
  {
   if (FormParametres->ShowModal()==mrOk)
    {
     Version=DRN_VERSION_SMT; //v0.9.4
     DessineTout(EFFACE_FOND);
     PassageAuCampSuivant();
    }
  }
 __finally
  {
   delete FormParametres;
   FormParametres=NULL;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuItemPlacerClick(TObject *Sender)
{
 if ((!P)||(!P->PartieEnCours)) return;
 int xd=P->Xs, yd=P->Ys, iD=0, iF=0, iFMin=0;
 if (!P->CoordonneesValides(xd, yd)) return;
 P->Xs=-1; P->Ys=-1; P->h[xd][yd].Dessine(PaintBox->Canvas); // v0.8.3. On retire la surbrillance
 direction d=(direction)((TMenuItem*)Sender)->Tag;
 if (P->LettresJouables(LabelLettresAPlacer->Caption, xd, yd, d, iFMin, iD, iF))
  {
   P->FormationMotEnCours=true; PopupMenuPlacer->Tag=0; // On n'autorise plus un deuxième choix
   P->PoseLettres(PaintBox->Canvas, LabelLettresAPlacer->Caption, xd, yd, d);
   AffichePoseLettres(xd, yd, d);
   if (P->ChercheMots(xd, yd, d, iFMin, iD, iF))
    {
     _JCRT.TempsEcoule+=(Now()-P->TopChrono); P->TopChrono=0; StatusBar->Repaint();// v0.9.4 : on arrête le chrono
     ComptabiliseMotsFormes();
    }
   else  // On retire les lettrees posées et le joueur recommence
    {
     P->RetireLettres(PaintBox->Canvas, xd, yd, d, iFMin);
     _JCRT.InitialiseTour(); // On réinitialise les calculs puisque le choix est invalide
     P->FormationMotEnCours=false;
    }
  }
 StatusBar->Repaint(); // v0.9.4 : le menu apparaît par erreur en bas 
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PaintBoxClick(TObject *Sender)
{
 if (P&&P->PartieEnCours&&PopupMenuPlacer->Tag) // Est à 1 si le placement est autorisé sinon à 0
  {
   TPoint Pt=PaintBox->ClientToScreen(TPoint(P->h[P->Xs][P->Ys].Xc(), P->h[P->Xs][P->Ys].Yc()));
   PopupMenuPlacer->Popup(Pt.x, Pt.y);
  }
 if (P&&
     P->PartieEnCours&&
     P->CoordonneesValides(P->Xs, P->Ys)&&
     P->LettreCapitalisable(P->Xs, P->Ys)&&
     P->h[P->Xs][P->Ys].Camp==P->CampCrt)
  {
   _JCRT.CapitaliseLettre(&(P->h[P->Xs][P->Ys]));
   AfficheCapitalisation(P->Xs, P->Ys);
   P->DessineCapitalLettres(PaintBox->Canvas);
   P->h[P->Xs][P->Ys].Dessine(PaintBox->Canvas);
   if (P->LettreCapitalisable(P->Xs, P->Ys)&&(P->h[P->Xs][P->Ys].Camp==P->CampCrt))
	Screen->Cursor=TCursor(CURSEUR_PLUS_1);
   else
	Screen->Cursor=crDefault;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TimerAfficheMotsTrouvesTimer(TObject *Sender)
{
 int iMot=P->iMotForme,
     iMotPrc=iMot-1;
 if (iMot>0)
  {
   P->ComptabiliseMotForme(PaintBox->Canvas, iMotPrc);
   AfficheProprietesMotForme(iMotPrc);
  }
 else
  AfficheEnTeteProprietesMotForme();
 // Dans tous les cas on met en evidence le mot formé
 if (iMot==_JCRT.slMotsFormes->Count)
  { // C'est fini !
   AfficheTotalProprietesMotsFormes();
   TimerAfficheMotsTrouves->Enabled=false;
   P->iMotForme=0;
   PassageAuCampSuivant();
   P->FormationMotEnCours=false;
  }
 else
  {
   P->DessineMot(PaintBox->Canvas, iMot);
   P->iMotForme++;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuItemQuitterClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
 CanClose=((!P)||
           (!P->PartieEnCours)||
		   (Application->MessageBox( L"Êtes-vous sûr(e) de vouloir quitter la partie en cours ?",
                                     L"Confirmation", MB_ICONQUESTION+MB_YESNO+MB_DEFBUTTON2)==IDYES));
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::MenuItemOuvrirClick(TObject *Sender)
{
 if (P&&P->FormationMotEnCours) return;
 if (P&&P->PartieEnCours&&
	 (Application->MessageBox( L"Êtes-vous sûr(e) de vouloir abandonner la partie en cours ?",
                               L"Confirmation", MB_ICONQUESTION+MB_YESNO+MB_DEFBUTTON2)==IDNO))
  return;
 if ((!OuvertureAuto)&&(!OpenDialog->Execute())) return;
 OuvertureAuto=false;
 SaveDialog->FileName=OpenDialog->FileName;
 int f=FileOpen(OpenDialog->FileName, fmOpenRead); // v1.4 FileOpen/FileClose au lieu de fopen/fclose
 if (f<=0)
  {
   Application->MessageBox(L"Impossible de lire le fichier !", L"Erreur à l'ouverture du fichier", MB_ICONHAND);
   return;
  }
 try
  {
   if (Charge(f))
    {
	 _JCRT.InitialiseTour();
     RichEdit->Clear();
     RichEdit->Lines->LoadFromFile(OpenDialog->FileName+".rtf");
     DessineTout(EFFACE_FOND);
     P->TopChrono=Now(); // v0.9.4
    }
   else
    {
	 Application->MessageBox( L"Une erreur est survenue lors de la lecture du fichier.\n\nPar précaution Osmotik va être fermé.",
                              L"Erreur lors de la lecture du fichier", MB_ICONHAND);
     Close();
    }
  }
 __finally
  {
   FileClose(f); // v1.4 FileOpen/FileClose au lieu de fopen/fclose
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuItemEnregistrerClick(TObject *Sender)
{
 bool DemandeNomFichier=((TMenuItem*)Sender)->Tag;
 if ((!P)||(!P->PartieEnCours)||P->FormationMotEnCours) return;
 if ((DemandeNomFichier||(SaveDialog->FileName==""))&&
     (!SaveDialog->Execute())) return;
 int f=FileCreate(SaveDialog->FileName); // v1.4 FileCreate au lieu de fopen("w")
 if (f<=0)
  {
   Application->MessageBox( L"Impossible de créer le fichier !\n\nFichier utilisé ? Chemin accessible ?", L"Erreur à la création du fichier", MB_ICONHAND);
   return;
  }
 try
  {
   if (!Sauve(f))
	Application->MessageBox( L"Une erreur est survenue lors de l'écriture du fichier.\n\nMerci de me le signaler (voir A Propos d'Osmotik).",
                             L"Erreur lors de l'écriture du fichier", MB_ICONHAND);
   else
    RichEdit->Lines->SaveToFile(SaveDialog->FileName+".rtf");
  }
 __finally
  {
   FileClose(f); // v1.4 FileOpen/FileClose au lieu de fopen/fclose
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuItemAProposClick(TObject *Sender)
{
 // v1.4 : Facteur HDPI + alignement 32/64 bits
 String stFacteurHDPI = FormatFloat("0.0", Screen->PixelsPerInch / 96.0);
 const String stFrmAPropos = "\
OSMOTIK 1.5 version %d bits\n\
Facteur HDPI : x%s\n\
Dictionnaire intégré : ODS9.\n\n\
GPL 2.0 - Fourni SANS AUCUNE GARANTIE que ce soit.\n\
Créé & développé par Patrice FOUQUET\n\n\
Pour toute information : patquoi.fr/#osmotik\n\
Pour informer de bogues : osmotik@patquoi.fr.",
		stTitreAPropos = "À propos d'Osmotik";
#ifdef _WIN64
 Application->MessageBox( Format(stFrmAPropos, ARRAYOFCONST((64, stFacteurHDPI))).c_str(), stTitreAPropos.c_str(), MB_ICONINFORMATION);
#else
 Application->MessageBox( Format(stFrmAPropos, ARRAYOFCONST((32, stFacteurHDPI))).c_str(), stTitreAPropos.c_str(), MB_ICONINFORMATION);
#endif
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuItemPasserSonTourClick(TObject *Sender)
{
 if (P&&P->PartieEnCours)
  {
   if (P->TourCrt)
    {
     P->NbAbandons++;
     PassageAuCampSuivant();
    }
   else
	Application->MessageBox( L"Vous ne pouvez pas passer le premier tour !",
                             L"Action impossible", MB_ICONEXCLAMATION);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
 if (P) { delete P; P=NULL; }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuItemAideClick(TObject *Sender)
{
 ShellExecute( NULL,
			   L"Open",
			   L"Osmotik.html",
			   NULL,
               String(ExtractFilePath(ParamStr(0))+"html").c_str(),
               SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuItemOptionsPoliceClick(TObject *Sender)
{
 // v1.4.1 : on va chercher directement PaintBox->Font
 FontDialog->Font->Name=PaintBox->Font->Name;
 if (PaintBox->Font->Style.Contains(fsBold)) // v1.4.1
   FontDialog->Font->Style = TFontStyles() << fsBold;

 if (FontDialog->Execute())
  {
   PaintBox->Font->Name=FontDialog->Font->Name;

   // v1.4.1 : ajout du style (gras ou non)
   PaintBox->Font->Style=TFontStyles();
   if (FontDialog->Font->Style.Contains(fsBold))
	 PaintBox->Font->Style=Font->Style << fsBold;

   LabelLettresAPlacer->Font=PaintBox->Font;
   Refresh();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{ // v0.9.3
 LitParametres();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{ // v0.9.3
 EcritParametres();
 if (crPlus1) DestroyCursor(crPlus1); // v1.4
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuItemOptionsCouleurFondClick(TObject *Sender)
{
 // v1.4.1 : on va chercher directement PaintBox->Color
 ColorDialog->Color=PaintBox->Color;
 if (ColorDialog->Execute())
  {
   PaintBox->Color=ColorDialog->Color;
   RichEdit->Color=ColorDialog->Color;
   Refresh();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::StatusBarDrawPanel(TStatusBar *StatusBar,
      TStatusPanel *Panel, const TRect &Rect)
{ // v0.9.4
 if (P&&(Panel->ID>=NUMSTATUSPANELJOUEUR)&&(Panel->ID<NUMSTATUSPANELJOUEUR+NbCamps[P->CfgDep]))
  {
   int j=Panel->ID-NUMSTATUSPANELJOUEUR;
   StatusBar->Canvas->Brush->Color=StatusBar->Color;
   StatusBar->Canvas->Font->Color=((ch[1+j]==clYellow)||(ch[1+j]==clLime)||(ch[1+j]==clAqua))?ch[j+NBMAXCAMPS+2]:ch[j+1];
   StatusBar->Canvas->TextOut(Rect.Left+(Rect.Right-Rect.Left-StatusBar->Canvas->TextWidth(Panel->Text))/2,
                              Rect.Top+(Rect.Bottom-Rect.Top-StatusBar->Canvas->TextHeight(Panel->Text))/2,
                              Panel->Text);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerReflexionTimer(TObject *Sender)
{ // v0.9.4
 TStatusPanel *StatusPanel;
 int SecondesRestantes;
 TDateTime Maintenant;
 AnsiString asTemps;
 if (P&&P->CampCrt&&(Version>=0x0940)) // Une partie a commencé
  {
   StatusPanel=StatusBar->Panels->Items[NUMSTATUSPANELJOUEUR+P->CampCrt-1];
   if ((double)P->TopChrono) // Le chrono tourne...
     Maintenant=Now();
   SecondesRestantes=(int)(24*3600*((double)_JCRT.TempsEcoule+((double)P->TopChrono?(double)(Maintenant-P->TopChrono):(double)0.0))); // v1.5.6 : Ord(p.TempsReflexion) à la place de MinutesReflexion
   asTemps=Format("%2d:%2d", ARRAYOFCONST((SecondesRestantes/60, SecondesRestantes%60)));
   if (asTemps[4]==' ') asTemps[4]='0';
   if (StatusPanel->Text!=asTemps)
    {
     StatusPanel->Text=asTemps;
     StatusBar->Repaint();
    }
  }
}
//---------------------------------------------------------------------------

