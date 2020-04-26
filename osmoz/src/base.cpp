//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#ifdef DEBUG
#include <stdio.h>
#endif
//---------------------------------------------------------------------------
#include "base.h"
#include "plateau_f.h"
#include "dico_f.h"
#include "scores_f.h"
#include "messages_f.h"
#include "records_f.h"
#include "param_f.h"
//---------------------------------------------------------------------------
#define SRC 0
#define DST 1
#define XDST 0
#define YDST 1
#define XSRC 2
#define YSRC 3
//---------------------------------------------------------------------------
#define NBMAXLDEF 5
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Convention
// Directions
//
//   1 0 5
//    \|/
//    /|\
//   2 3 4
//---------------------------------------------------------------------------
#ifdef DEBUG
  FILE *f=NULL;
#endif
//---------------------------------------------------------------------------
dico Dico;
plateau p;
joueur J[NBDIR]={{0}, {1}, {2}, {3}, {4}, {5}};
unsigned nbj=NBDIR, Jo=0, Tour=0;
//---------------------------------------------------------------------------
// Messages
const String stCouleur[NBDIR]={"BLEU", "VERT", "CIEL", "ROUGE", "MAGENTA", "JAUNE"},
			 stFrmMotForme="%-15s %2.2d %2.2d %2.2d",
			 stFrmQualifies="%-14s %3.3d %2.2d %2.2d",
			 stFrmBilanPlc="%1.1d mot(s)        %2.2d %2.2d %2.2d",
			 stDelimiteur= "------------------------",
			 stRien,
			 stFrmJoueur="%s: %s",
			 stFrmTour="Tour n°%d",
             stFinDeJeu = "Fin de jeu";
//---------------------------------------------------------------------------
const unsigned ChxPrmLtr[114]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,6,6,7,8,8,8,8,9,9,9,9,9,9,9,9,9,9,9,10,11,12,12,12,12,13,13,13,13,14,14,14,14,14,
                               15,15,15,15,15,15,15,15,16,16,18,18,18,18,18,19,19,19,19,19,19,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21,22,22,22,22,23,24,25};
//---------------------------------------------------------------------------
const int PrmCase[NBDIR][2]={{0,0},{7,0},{14,7},{14,14},{7,14},{0,7}};
//---------------------------------------------------------------------------
int max(int value1, int value2)
{
 return ((value1>value2)?value1:value2);
}
//---------------------------------------------------------------------------
int min(int value1, int value2)
{
 return((value1>value2)?value2:value1);
}
//---------------------------------------------------------------------------
// v4.5 : Pour les fichiers créés par Osmotik
//        on utilise le chemin donné par %LocalAppData% pour Windows 7 ou plus
//        sinon le dossier de l'exécutable
//---------------------------------------------------------------------------
String stRepLocalAppData()
 {
   String stResult;
   String stExePath = ExtractFilePath(Application->ExeName);
   const String stVarLocalAppData  = "LOCALAPPDATA";
   const String stVarUserProfile  = "USERPROFILE";
   const String stRepLocAppDataSmz = "\\Patquoi.fr\\Osmoz\\";
   stResult = GetEnvironmentVariable(stVarLocalAppData);
   if (stResult == "")
	{ // Windows 7~10
	 stResult = GetEnvironmentVariable(stVarUserProfile);
	 if (stResult == "")
	   stResult = stExePath;
	 else
	  { // Windows XP
	   stResult = stResult + "\\Local Settings\\Application Data" + stRepLocAppDataSmz;
	   if (!DirectoryExists(stResult))
		 if (!ForceDirectories(stResult))
		   stResult = stExePath;
	  }
	}
   else
	{ // Autres
	 stResult = stResult + stRepLocAppDataSmz;
	 if (!DirectoryExists(stResult))
	   if (!ForceDirectories(stResult))
		 stResult = stExePath;
	}
   return stResult;
 }
//---------------------------------------------------------------------------
bool Sauvegarde(String stNomFichier)
 {
  bool Bon=false;
  int i;
  int f;
  if (stNomFichier.Length()>0)
   {
	if ((f=NativeInt(FileCreate(stNomFichier)))>0)
	 {
	  Bon=(FileWrite(f, &nbj, sizeof(nbj))>0)&&
		  (FileWrite(f, &Jo, sizeof(Jo))>0)&&
		  (FileWrite(f, &Tour, sizeof(Tour))>0);
	  for(i=0; (i<nbj)&&(Bon); i++)
	   Bon=J[i].Sauve(f);
	  Bon=Bon&&p.Sauve(f);
	  FileClose(f);
	  if (!Bon)
	   frmPlateau->StatusBar->SimpleText="Erreur d'écriture dans le fichier destination.";
	 }
	else
	 frmPlateau->StatusBar->SimpleText="Impossible d'écrire dans le fichier destination.";
   }
  if (Bon)
   frmPlateau->StatusBar->SimpleText="Enregistrement effectué.";
  return Bon;
 }
//---------------------------------------------------------------------------
bool Chargement(String stNomFichier)
 {
  bool Bon=false;
  int i;
  int f;
  if (stNomFichier.Length()>0)
   {
	if ((f=FileOpen(stNomFichier, fmOpenRead))>0)
	 {
	  Bon=(FileRead(f, &nbj, sizeof(nbj))>0)&&
		  (FileRead(f, &Jo, sizeof(Jo))>0)&&
		  (FileRead(f, &Tour, sizeof(Tour))>0);
	  for(i=0; (i<nbj)&&(Bon); i++)
	   Bon=J[i].Charge(f);
	  Bon=Bon&&p.Charge(f);
	  if (!Bon)
	   frmPlateau->StatusBar->SimpleText="Erreur de lecture dans le fichier source "+stNomFichier+".";
	  FileClose(f);
	 }
	else
	 frmPlateau->StatusBar->SimpleText="Impossible de lire le fichier source "+stNomFichier+".";
   }
  if (Bon)
   {
	frmPlateau->StatusBar->SimpleText="Chargement de la partie terminée. Choisissez la rubrique \"Partie\" | \"Continuer\" ou appuyez sur Alt+C pour poursuivre le jeu.";
	frmPlateau->RubriqueContinuer->Enabled=true;
   }
  return Bon;
 }
//---------------------------------------------------------------------------
void InitialisePartie(bool JoueursCompris)
 {
  int i;
  p.Reinitialise();
  for(i=0; i<NBDIR; i++)
   if (JoueursCompris)
    J[i].Reinitialise( "Joueur "+IntToStr(i+1),
                       false,
                       frmParametresAutomates->Autorisation,
                       frmParametresAutomates->TailleMax);
   else
    J[i].Reinitialise(J[i].stNom, J[i].Automate, J[i].RechercheDeplacements, J[i].NbMaxLettres);
  Jo=0; Tour=0;
  p.AffichePlateau();
  J[Jo].AfficheLettresDisp();
  frmScores->MajScores();
 }
//---------------------------------------------------------------------------
void Qualifications()
 {
  bool AutoSvt[NBDIR]={false,false,false,false,false,false},
       RechDeplSvt[NBDIR]={false,false,false,false,false,false};
  String stNomSvt[NBDIR];
  int i, Rep, NbMaxLSvt[NBDIR]={NBMAXLDEF,NBMAXLDEF,NBMAXLDEF,NBMAXLDEF,NBMAXLDEF,NBMAXLDEF};
  int NbjSvt=(nbj>=2)+(nbj>=3)+(nbj>=NBDIR);
  bool TourSvt;
  frmPlateau->RubriqueContinuer->Enabled=false;
  frmMessages->AjouteMessage(stRien, RIEN_EFFACER);
  frmMessages->AjouteMessage("****** FIN DE JEU ******", RIEN_EFFACER);
  frmMessages->AjouteMessage(stRien, RIEN_EFFACER);
  frmMessages->AjouteMessage("JoueurQualifié Pts j. p.", RIEN_EFFACER);
  frmMessages->AjouteMessage("------------------------", RIEN_EFFACER);
  for(i=0; i<NbjSvt; i++)
   frmMessages->AjouteMessage(Format(stFrmQualifies,
                                      ARRAYOFCONST((J[frmScores->jocl[i]].stNom,
                                                    J[frmScores->jocl[i]].Score,
                                                    (int)frmScores->nj[frmScores->jocl[i]],
                                                    (int)frmScores->np[frmScores->jocl[i]]))),
                               RIEN_EFFACER);
  frmMessages->AfficheMessage("------------------------", RIEN_EFFACER);
  if (Application->MessageBox(L"Voulez-vous sauvegarder le déroulement de la fin de partie ?", stFinDeJeu.c_str(), MB_ICONQUESTION + MB_YESNO)==IDYES)
   frmMessages->SauvegardeFin();
  if (NbjSvt>1)
   {
    if (NbjSvt==3)
	 Rep=Application->MessageBox(L"Voulez-vous faire la ½ finale ?", stFinDeJeu.c_str(), MB_ICONQUESTION + MB_YESNO);
    else
	 Rep=Application->MessageBox(L"Voulez-vous faire la finale ?", stFinDeJeu.c_str(), MB_ICONQUESTION + MB_YESNO);
    TourSvt=(Rep==IDYES);
   }
  if (TourSvt)
   {
    for(i=0; i<NbjSvt; i++)
     {
      stNomSvt[i]=J[frmScores->jocl[i]].stNom;
      AutoSvt[i]=J[frmScores->jocl[i]].Automate;
      RechDeplSvt[i]=J[frmScores->jocl[i]].RechercheDeplacements;
      NbMaxLSvt[i]=J[frmScores->jocl[i]].NbMaxLettres;
     }
    p.Reinitialise();
    for(i=0; i<NbjSvt; i++)
     {
      J[i].DefPrmCase(PrmCase[NBDIR*i/NbjSvt][0], PrmCase[NBDIR*i/NbjSvt][1]);
      J[i].Reinitialise(stNomSvt[i], AutoSvt[i], RechDeplSvt[i], NbMaxLSvt[i]);
     }
    nbj=NbjSvt; Jo=0; Tour=0;
    frmMessages->Memo->Lines->Clear();
	frmPlateau->RubriquePasserSonTour->Enabled=(!J[Jo].Automate);
    p.JeuEnCours=false;
    p.AffichePlateau();
    J[Jo].AfficheLettresDisp();
    frmScores->MajScores();
	frmMessages->AjouteMessage(Format(stFrmTour, ARRAYOFCONST(((int)Tour))), RIEN_EFFACER);
	frmMessages->AjouteMessage(stRien, RIEN_EFFACER);
	frmMessages->AjouteMessage(Format(stFrmJoueur, ARRAYOFCONST((stCouleur[Jo], J[Jo].stNom))), RIEN_EFFACER);
    p.DepartChrono();
    frmPlateau->Phase=aucune_phase;
    frmPlateau->Situation=choix_lettre;
   }
 }
//---------------------------------------------------------------------------
void JoueurSuivant()
 {
  bool ToutLeMondeAPasseSonTour;
  p.FinChrono();
  if ((!p.NbCasesLibres)||
      (ToutLeMondeAPasseSonTour=(Jo+1==nbj)&&(p.NbPasseTour==nbj)))
   {
    if (ToutLeMondeAPasseSonTour)
     Application->MessageBox(L"Tous les joueurs ont passé leur tour !", stFinDeJeu.c_str(), MB_ICONINFORMATION);
    Qualifications();
    return;
   }
  Tour+=(Jo+1==nbj);
  Jo=(Jo+1)%nbj;
  frmPlateau->RubriquePasserSonTour->Enabled=(!J[Jo].Automate);
  if (!Jo)
   {
    p.NbPasseTour=0;
    frmMessages->AjouteMessage(stRien, RIEN_EFFACER);
    frmMessages->AjouteMessage(Format(stFrmTour, ARRAYOFCONST(((int)Tour))), RIEN_EFFACER);
    frmScores->MajScores();
   }
  frmMessages->AjouteMessage(stRien, RIEN_EFFACER);
  frmMessages->AjouteMessage(Format(stFrmJoueur, ARRAYOFCONST((stCouleur[Jo], J[Jo].stNom))), RIEN_EFFACER);
  J[Jo].AfficheLettresDisp();
  if (!J[Jo].Automate) p.DepartChrono();
  frmPlateau->Phase=aucune_phase;
  frmPlateau->Situation=choix_lettre;
 }
//---------------------------------------------------------------------------
plateau::plateau()
 {
  int i;
  JeuEnCours=false;
  Recherche=false;
  CalculNbCasesEnCours=false;
  NbPasseTour=0;
  NbCasesLibres=NBCASES;
  setmem(c, sizeof(c), 0);
  for(i=2; i<9; i++) ValNaiss[i]=2;                      // B…H(-E): 2
  ValNaiss[1]=ValNaiss[5]=5;                             // A,E    : 5
  ValNaiss[9]=ValNaiss[15]=ValNaiss[19]=ValNaiss[21]=4;  // I,O,S,U: 4
  ValNaiss[12]=ValNaiss[14]=ValNaiss[18]=ValNaiss[20]=3; // L,N,R,T: 3
  ValNaiss[13]=ValNaiss[16]=ValNaiss[22]=2;              // M,P,V  : 2
  ValNaiss[10]=ValNaiss[11]=ValNaiss[17]=1;              // J,K,Q  : 1
  for(i=23; i<27; i++) ValNaiss[i]=1;                    // W…Z    : 1
  dy[0]=dy[1]=dx[0]=dx[5]=-1;
  dy[5]=dy[2]=dx[4]=dx[1]=0;
  dy[3]=dy[4]=dx[3]=dx[2]=1;
  for(i=0; i<NBXY; i++)
   if (i<8) // v4.0. Avant (i<6)
    {
     XYMin[i]=0;
     XYMax[i]=7+i;// v4.0. Avant 5+i
    }
   else
    {
     XYMax[i]=14; // v4.0. Avant : 10
     XYMin[i]=i-7;// v4.0. Avant i-5
    }
  TopTour=0.0;
 }
//---------------------------------------------------------------------------
void plateau::Reinitialise()
 {
  Recherche=false;
  JeuEnCours=false;
  NbPasseTour=0;
  TopTour=0.0;
  NbCasesLibres=NBCASES;
  setmem(c, sizeof(c), 0);
 }
//---------------------------------------------------------------------------
void plateau::AffichePlateau()
 {
  int x, y;
  for(x=0; x<NBXY; x++)
   for(y=XYMin[x]; y<=XYMax[x]; y++)
    AfficheCase(x, y, clBlack);
  frmPlateau->AfficheCoordonnees();
  AfficheValNaiss();
  J[Jo].AfficheLettresDisp();
 }
//---------------------------------------------------------------------------
void plateau::AfficheCase(int x, int y, TColor Couleur)
 {  // v4.0 : Décalage = (-4,-42)
  bool LettrePresente=(c[x][y].Lettre>='A')&&(c[x][y].Lettre<='Z');
  int //Col=5+y-x,
	  Col=7+y-x,
	  // Lig=abs(5-Col)+2*(x*(Col>=5)+y*(Col<5)), // Avant
	  Lig=ABS(7-Col)+2*(x*(Col>=7)+y*(Col<7)), // v4.0
	  //xc=166+30*Col,
	  xc=100+30*Col,
	  //yc=54+17*(2*((Lig-!(Col%2))/2)+!(Col%2));
      yc=12+17*(2*((Lig-!(Col%2))/2)+!(Col%2));
  frmPlateau->DessineHexagone(xc, yc, c[x][y].Joueur, (!LettrePresente)||(!c[x][y].Joueur)||c[x][y].Valeur); // v3.3
  if (LettrePresente)
   frmPlateau->AfficheValeurs(xc, yc,
                              c[x][y].Lettre,
                              c[x][y].Valeur,
                              c[x][y].Joueur,
                              ((Couleur==clBlack)&&
                               (c[x][y].Valeur>=ValNaiss[NUM_LETTRE(c[x][y].Lettre)]))?
                               clJo[c[x][y].Joueur][0]:
                               Couleur);
 }
//---------------------------------------------------------------------------
void plateau::AfficheValNaiss()
 {
  int i;
  //setcolor(8);
  for(i=0; i<26; i++)
   {
    frmPlateau->DessineHexagone(11+30*(i%2), 12+17*i, 0, CLAIR);
    frmPlateau->AfficheValeurs(11+30*(i%2), 12+17*i, 'A'+i, ValNaiss[i+1], 0, clBlack);
   }
 }
//---------------------------------------------------------------------------
bool plateau::NouvelleLettrePossible(int x, int y)
 {
  return (c[x][y].Joueur==Jo+1)&&
         (c[x][y].Valeur>=ValNaiss[NUM_LETTRE(c[x][y].Lettre)]);
 }
//---------------------------------------------------------------------------
bool plateau::LettreDeplacable(int x, int y)
 { // Ne teste que si une case contiguë est libre. Suppose déjà que 'A'<=c[x][y].Lettre<='Z'
  int i, xx, yy;
  bool Deplacable;
  for(Deplacable=i=0; (!Deplacable)&&(i<NBDIR); i++)
   {
    xx=x+p.dx[i]; yy=y+p.dy[i];
    Deplacable= (xx>=0)&&
                (yy>=0)&&
                (xx<NBXY)&&
                (yy<NBXY)&&
                (xx>=p.XYMin[yy])&&
                (xx<=p.XYMax[yy])&&
                (yy>=p.XYMin[xx])&&
                (yy<=p.XYMax[xx])&&
                (!p.c[xx][yy].Joueur);
   }
  return Deplacable;
 }
//---------------------------------------------------------------------------
bool plateau::CaseIsolee(int x, int y)
 { // Teste si une case est isolée (c'est-à-dire n'ayant aucun jeton autour)
  int i, xx, yy;
  bool Isolee=true;
  for(i=0; Isolee&&(i<NBDIR); i++)
   {
    xx=x+p.dx[i]; yy=y+p.dy[i];
    Isolee=(xx<0)||
           (yy<0)||
           (xx>=NBXY)||
           (yy>=NBXY)||
           (xx<p.XYMin[yy])||
           (xx>p.XYMax[yy])||
           (yy<p.XYMin[xx])||
           (yy>p.XYMax[xx])||
           (!p.c[xx][yy].Joueur);
   }
  return Isolee;
 }
//---------------------------------------------------------------------------
void plateau::PrepareCalculNbCasesDeplacement(int x, int y) // (x,y) = Case destination
 {
  int i;
  CalculNbCasesEnCours=true;
  for(i=0; i<NBXY*NBXY; i++)
   {
    c[i/NBXY][i%NBXY].DejaPasse=false;
    c[i/NBXY][i%NBXY].NbCases=INDEFINI;
   }
  xDestDepl=x;
  yDestDepl=y;
 }
//---------------------------------------------------------------------------
int plateau::NbCasesDeplacement(int x, int y) // (x,y) = Case d'origine
 { // Renvoie 0 si le déplacement n'est pas possible
  int i,
      NbMinCases=NB_CASES_ASSEZ_GRAND,
      NbCasesCrt, NbCasesVoisine,
      xx, yy;
  c[x][y].DejaPasse=true;
  for(i=0; i<NBDIR; i++)
   {
    xx=x+p.dx[i]; yy=y+p.dy[i];
    if ((xx>=0)&&
        (yy>=0)&&
        (xx<NBXY)&&
        (yy<NBXY)&&
        (xx>=p.XYMin[yy])&&
        (xx<=p.XYMax[yy])&&
        (yy>=p.XYMin[xx])&&
        (yy<=p.XYMax[xx])&&
        (!p.c[xx][yy].Joueur)&&
        (!c[xx][yy].DejaPasse))
     {
      if ((xDestDepl==xx)&&
          (yDestDepl==yy))
       NbCasesCrt=1;
      else
       if (c[xx][yy].NbCases!=INDEFINI)
        if (c[xx][yy].NbCases)
         NbCasesCrt=1+c[xx][yy].NbCases;
        else
         NbCasesCrt=0; // Chemin impossible
       else
		if ((NbCasesVoisine=NbCasesDeplacement(xx, yy)))
         NbCasesCrt=1+NbCasesVoisine;
        else
         NbCasesCrt=0; // Chemin impossible
      if (NbCasesCrt&&(NbCasesCrt<NbMinCases)) NbMinCases=NbCasesCrt;
     }
   }
  c[x][y].DejaPasse=false;
  if (NbMinCases==NB_CASES_ASSEZ_GRAND) NbMinCases=0; // Chemin impossible
  if (c[x][y].NbCases==INDEFINI) c[x][y].NbCases=NbMinCases;
  return NbMinCases;
 }
//---------------------------------------------------------------------------
bool plateau::FormeMotsApresDeplacement(int x0, int y0, int x1, int y1)
 {
  bool MotsFormes;
  c[x1][y1].Lettre=c[x0][y0].Lettre;
  c[x1][y1].Valeur=c[x0][y0].Valeur;
  c[x1][y1].Joueur=c[x0][y0].Joueur;
  c[x0][y0].Lettre=0;
  c[x0][y0].Valeur=0;
  c[x0][y0].Joueur=0;
  Recherche=true;
  MotsFormes=!!ChercheMotsFormes(x1, y1);
  Recherche=false;
  c[x0][y0].Lettre=c[x1][y1].Lettre;
  c[x0][y0].Valeur=c[x1][y1].Valeur;
  c[x0][y0].Joueur=c[x1][y1].Joueur;
  c[x1][y1].Lettre=0;
  c[x1][y1].Valeur=0;
  c[x1][y1].Joueur=0;
  return MotsFormes;
 }
//---------------------------------------------------------------------------
void plateau::DeplaceLettre(int x0, int y0, int x1, int y1, int NbCases)
 {
  c[x1][y1].Lettre=c[x0][y0].Lettre;
  c[x1][y1].Valeur=c[x0][y0].Valeur-NbCases;
  c[x1][y1].Joueur=c[x0][y0].Joueur;
  c[x0][y0].Lettre=0;
  c[x0][y0].Valeur=0;
  c[x0][y0].Joueur=0;
  AfficheCase(x0, y0, clBlack);
  AfficheCase(x1, y1, clBlack);
  frmMessages->AjouteMessage("Dépl."+String((char)c[x1][y1].Lettre)+" ("+IntToStr(x0)+","+IntToStr(y0)+")",RIEN_EFFACER);
  frmMessages->AjouteMessage("     ->("+IntToStr(x1)+","+IntToStr(y1)+")", RIEN_EFFACER);
 }
//---------------------------------------------------------------------------
bool plateau::LettreUtiliseeAuDepart(char Lettre)
 {
  bool Utilisee=false;
  int i;
  for(i=0; (!Utilisee)&&(i<Jo); i++)
   Utilisee=(c[J[i].CoordDeb[0]][J[i].CoordDeb[1]].Lettre==Lettre);
  return Utilisee;
 }
//---------------------------------------------------------------------------
void plateau::PoseLettre(int x, int y, char Lettre)
 {
  c[x][y].Lettre=Lettre;
  c[x][y].Valeur=0;
  c[x][y].Joueur=Jo+1;
  NbCasesLibres--;
  AfficheCase(x, y, clBlack);
  frmMessages->AjouteMessage("Pose "+String(Lettre)+" ("+IntToStr(x)+","+IntToStr(y)+")", RIEN_EFFACER);
 }
//---------------------------------------------------------------------------
void plateau::EnleveLettre(int x, int y)
 {
  c[x][y].Lettre=0;
  c[x][y].Valeur=0;
  c[x][y].Joueur=0;
  NbCasesLibres++;
  AfficheCase(x, y, clBlack);
  frmMessages->RetireMessages(2);
 }
//---------------------------------------------------------------------------
void plateau::PlaceLettreAuto()
 { // ATTENTION, ici les lettres (variables *Ltr*) correspondent à NUM_LETTRE(Lettre)
  int i, DrnChxPlacement=INDEFINI;
  unsigned iJauge=1, Bon, SupEgal,
		   LtrChx, NumLettre, NbCases, NbChoix=0, ChxLtr[225], ChxNbCases[225];
  int x, y, xd[2], yd[2], XChx[2], YChx[2], xx, yy, ChxXY[225][4];
  unsigned long ChxPtsGagnes=0, ChxPtsPris=0, ChxLtrPrises=0, ChxTotCoefs=0;
  bool Deplacement=false;
  setmem(ChxLtr, sizeof(ChxLtr), 0);
  setmem(ChxXY, sizeof(ChxXY), 0);
  DepartChrono();
  Recherche=true;
  if (Tour)
   {
#ifdef DEBUG
    f=fopen(String(ExtractFilePath(ParamStr(0))+"osmoz.log").c_str(), "wt");
#endif
    // 1. Recherche des lettres pouvant être rechargées (v4.0 : était positionné en 4.)
    for(x=0; x<NBXY; x++)
     for(y=XYMin[x]; y<=XYMax[x]; y++)
      if (c[x][y].Joueur==Jo+1)
       if (c[x][y].Valeur>=ValNaiss[NumLettre=NUM_LETTRE(c[x][y].Lettre)]) // Assez de points pour recharger
        AjouteLettre(x, y);
    // 2. PLACEMENT D'UNE LETTRE : a. Choix de l'emplacement (v4.0 : était positionné en 1.)
    for(x=0; x<NBXY; x++)
     {
      for(y=XYMin[x]; y<=XYMax[x]; y++)
       {
		if ((Bon=!c[x][y].Joueur))
         {
          for(Bon=i=0; (!Bon)&&(i<NBDIR); i++)
           {
            xx=x+dx[i]; yy=y+dy[i];
			Bon=(xx<NBXY)&&
                (yy<NBXY)&&
                (xx>=XYMin[yy])&&
                (xx<=XYMax[yy])&&
                (yy>=XYMin[xx])&&
                (yy<=XYMax[xx])&&
                (c[xx][yy].Joueur==Jo+1);
           }
         }
        if (Bon)
         {
          NumLettre=0;
          do
           { // 2.b. Choix de la lettre (v4.0 : était positionné en 1.)
            for(NumLettre++; (NumLettre<27)&&(!J[Jo].Nombre[NumLettre]); NumLettre++);
            if (NumLettre<27)
             {
              SupEgal=0;
              c[x][y].Lettre=NumLettre+'A'-1;
              c[x][y].Joueur=Jo+1;
              /***************** Comparaison */
              if (ChercheMotsFormes(x, y))
               {
                if (PtsGagnes+PtsPris>=ChxPtsGagnes+ChxPtsPris)
                  if (!(SupEgal=(PtsGagnes+PtsPris>ChxPtsGagnes+ChxPtsPris)))
                    if (LtrPrises>=ChxLtrPrises)
                      if (!(SupEgal=(LtrPrises>ChxLtrPrises)))
                        if (TotCoefs>=ChxTotCoefs)
                          if (!(SupEgal=(TotCoefs>ChxTotCoefs)))
                            if (PtsPris>=ChxPtsPris)
                             SupEgal=(PtsPris>=ChxPtsPris)+(PtsPris==ChxPtsPris);
               }
              if (SupEgal)
               {
                NbChoix=1+NbChoix*(SupEgal==2);
                ChxLtr[NbChoix-1]=NumLettre;
                ChxXY[NbChoix-1][XDST]=x;
                ChxXY[NbChoix-1][YDST]=y;
                if (SupEgal==1)
                 {
                  ChxPtsGagnes=PtsGagnes;
                  ChxPtsPris=PtsPris;
                  ChxLtrPrises=LtrPrises;
                  ChxTotCoefs=TotCoefs;
                 }
               }
              /*******************************/
              c[x][y].Lettre=0;
              c[x][y].Joueur=0;
             }
           }
          while(NumLettre<27);
         }
		frmPlateau->StatusBar->SimpleText= Format("Recherche d'un placement (lettre+case) : %d%%", ARRAYOFCONST(((int)(0.5+(100.0*iJauge)/NBCASES)))); // v4.5 : affichage en % au lieu de barres
        frmPlateau->StatusBar->Repaint();
        iJauge++;
       }
     }

    DrnChxPlacement=NbChoix-1; iJauge=1;

    // 3. DEPLACEMENT D'UNE LETTRE (v4.0 : était positionné en 2.)
    if ((Tour>1)&&J[Jo].RechercheDeplacements)
     for(xd[DST]=0; xd[DST]<NBXY; xd[DST]++)
      { // 3.a. Choix de la case destination d'abord. Evite le recalcul des distances en interne (v4.0 : était positionné en 2.)
       for(yd[DST]=XYMin[xd[DST]]; yd[DST]<=XYMax[xd[DST]]; yd[DST]++)
        {
		 if ((Bon=(!c[xd[DST]][yd[DST]].Joueur)&&   // Case destination est libre ET
                  (!CaseIsolee(xd[DST], yd[DST])))) // pas isolée (y a un jeton autour pour faire du point
          {
           // 3.b. Choix de la case source : jeton à déplacer (v4.0 : était positionné en 2.)
           PrepareCalculNbCasesDeplacement(xd[DST],yd[DST]);
           for(xd[SRC]=0; xd[SRC]<NBXY; xd[SRC]++)
            {
             for(yd[SRC]=XYMin[xd[SRC]]; yd[SRC]<=XYMax[xd[SRC]]; yd[SRC]++)
              {
               NumLettre=c[xd[SRC]][yd[SRC]].Lettre-'A'+1;
               NbCases=NbCasesDeplacement(xd[SRC],yd[SRC]);
			   if ((Bon=(c[xd[SRC]][yd[SRC]].Joueur==Jo+1)&&    // Le jeton à déplacer est du joueur courant ET
						NbCases&&                               // il est déplaçable jusqu'à (xd[DST],yd[DST]) ET
						(NbCases<=c[xd[SRC]][yd[SRC]].Valeur))) // le nombre de cases de déplacement <= valeur du jeton
                { // Jeton en (xd[SRC],yd[SRC]) déplaçable en (xd[DST],yd[DST])
                 SupEgal=0;
                 c[xd[SRC]][yd[SRC]].Lettre=0;
                 c[xd[SRC]][yd[SRC]].Joueur=0;
                 c[xd[DST]][yd[DST]].Lettre=NumLettre+'A'-1;
                 c[xd[DST]][yd[DST]].Joueur=Jo+1;
                 /***************** Comparaison */
                 if (ChercheMotsFormes(xd[DST], yd[DST]))
                  {
                   //PtsGagnes-=NbCases;
                   if (PtsGagnes+PtsPris>=ChxPtsGagnes+ChxPtsPris)
                     if (!(SupEgal=(PtsGagnes+PtsPris>ChxPtsGagnes+ChxPtsPris)))
                       if (LtrPrises>=ChxLtrPrises)
                         if (!(SupEgal=(LtrPrises>ChxLtrPrises)))
                           if (TotCoefs>=ChxTotCoefs)
                             if (!(SupEgal=(TotCoefs>ChxTotCoefs)))
                               if (PtsPris>=ChxPtsPris)
                                SupEgal=(PtsPris>=ChxPtsPris)+(PtsPris==ChxPtsPris);
                  }
                 if (SupEgal)
                  {
                   NbChoix=1+NbChoix*(SupEgal==2);
                   if (NbChoix==1) DrnChxPlacement=INDEFINI;
                   ChxLtr[NbChoix-1]=NumLettre;
                   ChxXY[NbChoix-1][XDST]=xd[DST];
                   ChxXY[NbChoix-1][YDST]=yd[DST];
                   ChxXY[NbChoix-1][XSRC]=xd[SRC];
                   ChxXY[NbChoix-1][YSRC]=yd[SRC];
                   ChxNbCases[NbChoix-1]=NbCases;
                   if (SupEgal==1)
                    {
                     ChxPtsGagnes=PtsGagnes;
                     ChxPtsPris=PtsPris;
                     ChxLtrPrises=LtrPrises;
                     ChxTotCoefs=TotCoefs;
                    }
                  }
                 /*******************************/
                 c[xd[DST]][yd[DST]].Lettre=0;
                 c[xd[DST]][yd[DST]].Joueur=0;
                 c[xd[SRC]][yd[SRC]].Lettre=NumLettre+'A'-1;
                 c[xd[SRC]][yd[SRC]].Joueur=Jo+1;
                }
              }
            }
           CalculNbCasesEnCours=false;
          }
		 frmPlateau->StatusBar->SimpleText= Format("Recherche d'un déplacement (case+jeton)  : %d%%", ARRAYOFCONST(((int)(0.5+(100.0*iJauge)/NBCASES)))); // v4.5 : affichage en % au lieu de barres
         frmPlateau->StatusBar->Repaint();
         iJauge++;
        }
      }

    // 4. Tirage au sort parmi les solutions équivalentes trouvées (v4.0 : était positionné en 3.)
    i=(NbChoix>1)*random(NbChoix);
    XChx[DST]=ChxXY[i][XDST];
    YChx[DST]=ChxXY[i][YDST];
    if ((Deplacement=(i>DrnChxPlacement)))
     { // C'est un déplacement
      XChx[SRC]=ChxXY[i][XSRC];
      YChx[SRC]=ChxXY[i][YSRC];
      NbCases=ChxNbCases[i];
     }
    LtrChx=ChxLtr[i];
#ifdef DEBUG
    FileClose(f);
#endif
   }
  else // 1er TOUR : Choix au hasard avec probabilites de formation d'un mot de deux lettres
   {
    NbChoix=1; Deplacement=false;
    XChx[DST]=J[Jo].CoordDeb[0];
    YChx[DST]=J[Jo].CoordDeb[1];
    do // Lettre choisie différentes de celles des adversaires
     {
      LtrChx=ChxPrmLtr[random(NBPRMLTR)];
      for(i=0; (Bon=(NUM_LETTRE(c[J[i].CoordDeb[0]][J[i].CoordDeb[1]].Lettre)!=LtrChx))&&(i<Jo); i++);
     }
    while(!Bon);
   }
  // Message
  Recherche=false;
  if (NbChoix)
   {
    if (Deplacement)
     DeplaceLettre(XChx[SRC], YChx[SRC], XChx[DST], YChx[DST], NbCases);
    else
     { // Placement
      J[Jo].PrendLettre(LtrChx+'A'-1);
      PoseLettre(XChx[DST], YChx[DST], LtrChx+'A'-1);
     }
    if (Tour) ChercheMotsFormes(XChx[DST], YChx[DST]);
   }
  else NbPasseTour++;
 }
//---------------------------------------------------------------------------
int plateau::ChercheMotsFormes(int x, int y)
 {
  int NblMax=Recherche?J[Jo].NbMaxLettres:NBLMAX,
      MotCree=0, PtsPlus, PtsMoins, TotPlus=0, TotMoins=0, NbMots=0, NbLtrPrises, TotLtrPrises=0,
      Val, i, iInf, iSup, iMax, iDeb, iDebMin,
      Dir, nl, Sens, xx, yy, LgrMin, LgrMot[NBLMAX];
  unsigned NumJo=c[x][y].Joueur;
  char Mot[2][NBLMAX+1];
  String stMotLePlusLong;
  frmMessages->Memo->Hint="\"P+\"=Gain de points - \"P-\"=Perte de point(s) adverse - \"L-\"=Perte de lettre(s) adverse";

   // On évalue les mots dans les deux sens : l'un ou l'autre doit exister
  if (Recherche)
   {
    PtsGagnes=PtsPris=LtrPrises=TotCoefs=0;
   }
  else
   {
    frmMessages->AjouteMessage("Mots            P+ P- L-", RIEN_EFFACER);
	frmMessages->AjouteMessage(stDelimiteur, RIEN_EFFACER);
   }
#ifdef DEBUG
  fprintf(f, "Départ: %c(%d,%d)\n", (char)c[x][y].Lettre, x, y);
#endif
  for(Dir=0; Dir<3; Dir++)
   {
    setmem(LgrMot, sizeof(LgrMot), 0);
    switch(Dir) // Définition de l'intervalle des limites du plateau [iInf, iSup]
     { // v4.0 : 7 à la place de 5
	  case 0: iInf=x-XYMax[7+x-y]; iSup=x-XYMin[7+x-y]; break; // 15L:(7+x-y,7+x-y)
      case 1: iInf=y-XYMax[x]; iSup=y-XYMin[x]; break;
      case 2: iSup=XYMax[y]-x; iInf=XYMin[y]-x; break;
     }
#ifdef DEBUG
    fprintf(f, " Dir. %s: iInf=%d, iSup=%d, NblMax=%d\n", Dir?(Dir%2?"4h-10h":"2h-8h"):"0h-6h", iInf, iSup, NblMax);
#endif
    // On définit l'intervalle d'étude des mots
    for(iDebMin=0; (iDebMin>=-NblMax+1)&&(iDebMin>=iInf)&&(c[x+iDebMin*dx[Dir]][y+iDebMin*dy[Dir]].Lettre); iDebMin--); // 15L:(-7)
    iDebMin++;
    for(iMax=0; (iMax<=NblMax-1)&&(iMax<=iSup)&&(c[x+iMax*dx[Dir]][y+iMax*dy[Dir]].Lettre); iMax++); // 15L:(7)
    iMax--;
    // On étudie tous les cas de mots en partant des mots de 15 lettres
    // On passe au iDeb suivant dès que le mot de nl lettres existe
    // -> elimination des mots contenus
    for(iDeb=iDebMin; iDeb<=min(iMax-1, 0); iDeb++)
     {
#ifndef DEBUG
      frmScores->MajTemps();
#endif
      Sens=0;
      LgrMin=0;
      for(i=1; i<=iDeb-iDebMin; i++)
       if (LgrMin<(nl=LgrMot[iDeb-iDebMin-i]+1-i)) LgrMin=nl;
      for(nl=min(NblMax, iMax-iDeb+1); (!Sens)&&(nl>=max(max(2, LgrMin), 1-iDeb)); nl--) // 15L:(8)
       {
        for(i=0; i<nl; i++)
         Mot[1][nl-i-1]=Mot[0][i]=c[x+(iDeb+i)*dx[Dir]][y+(iDeb+i)*dy[Dir]].Lettre;
        Mot[1][nl]=Mot[0][nl]=0;
        if (!(Sens=Dico.Existe(Mot[0], nl)))
         Sens=2*Dico.Existe(Mot[1], nl);
#ifdef DEBUG
        fprintf(f, "  Forme %s/%s (%d)\n", Mot[0], Mot[1], Sens);
#endif
        // 1. Affichage des lettres du mot en blanc : AfficheCase(,,clWhite)
        // 2. Annonce du mot existant : AfficheMessage()
        // 3. (In/Dé)crémentation de la valeur des lettres du mot
        // 4. Réaffichage des lettres du mot en noir : AfficheCase(,,clBlack)
        if (Sens)
         {
          if (!MotCree) MotCree=1;
          NbMots++;
          NbLtrPrises=PtsPlus=PtsMoins=0;
          LgrMot[iDeb-iDebMin]=nl;
          for(i=0; i<nl; i++)
           {
            xx=x+(iDeb+i)*dx[Dir]; yy=y+(iDeb+i)*dy[Dir];
            if (!Recherche) AfficheCase(xx, yy, (iDeb+i)?clWhite:clLtGray);
            if (c[xx][yy].Valeur)
             {
              Val=1-2*(c[xx][yy].Joueur!=NumJo);
              if (!Recherche)
               {
                c[xx][yy].Valeur+=Val;
                J[NumJo-1].IncrementeScore(1);
               }
              else
               if (Tour>1) TotCoefs+=ValNaiss[c[xx][yy].Lettre];
              PtsPlus+=Val*(Val>0);
              PtsMoins+=-Val*(Val<0);
             }
            else
             {
              PtsPlus++;
              if (!Recherche)
               {
                NbLtrPrises+=(c[xx][yy].Joueur!=NumJo);
                c[xx][yy].Joueur=NumJo;
                c[xx][yy].Valeur=1;
                J[NumJo-1].IncrementeScore(1);
               }
              else
               if (Tour>1) TotCoefs+=ValNaiss[c[xx][yy].Lettre];
             }
           }
          TotPlus+=PtsPlus;
          TotMoins+=PtsMoins;
          TotLtrPrises+=NbLtrPrises;
          if (!Recherche)
           {
            frmMessages->AfficheMessage(Format(stFrmMotForme, ARRAYOFCONST((String(Mot[Sens-1]), PtsPlus+PtsMoins, PtsMoins, NbLtrPrises))), RIEN_EFFACER);
            if (String(Mot[Sens-1]).Length()>stMotLePlusLong.Length())
             stMotLePlusLong=String(Mot[Sens-1]);
            for(i=0; i<nl; i++)
             AfficheCase(x+(iDeb+i)*dx[Dir], y+(iDeb+i)*dy[Dir], TColor(0));
           }
         }
       }
     }
   }
  if (Recherche)
   {
    PtsGagnes=TotPlus;
    PtsPris=TotMoins;
    LtrPrises=TotLtrPrises;
   }
  if (MotCree&&(!Recherche))
   {
    frmMessages->AjouteMessage(Format(stFrmBilanPlc, ARRAYOFCONST((NbMots, TotPlus+TotMoins, TotMoins, TotLtrPrises))), RIEN_EFFACER);
    frmMessages->AjouteMessage(stDelimiteur, RIEN_EFFACER);
    frmRecords->TesteRecords(J[Jo].stNom, stMotLePlusLong, TotPlus+TotMoins, TotMoins, TotLtrPrises);
   }
  return MotCree;
 }
//---------------------------------------------------------------------------
void plateau::AjouteLettre(int x, int y)
 {
  int NumLettre=NUM_LETTRE(c[x][y].Lettre);
  J[Jo].Nombre[NumLettre]++;
  J[Jo].Nombre[0]++;
  c[x][y].Valeur-=ValNaiss[NumLettre];
  frmPlateau->Cursor=crArrow;
  frmPlateau->StatusBar->SimpleText="";
  AfficheCase(x,y,clBlack);
  J[Jo].AfficheLettresDisp();
  frmMessages->AjouteMessage("Gain "+String((char)c[x][y].Lettre)+" ("+IntToStr(x)+","+IntToStr(y)+")", RIEN_EFFACER);
  frmScores->MajScores();
 }
//---------------------------------------------------------------------------
void plateau::DepartChrono()
 {
  time(&TopTour);
  JeuEnCours=true;
 }
//---------------------------------------------------------------------------
void plateau::FinChrono()
 {
  double dt=difftime(time(NULL), TopTour);
  //int tt=J[Jo].TpsEcoule+dt, h=tt/3600, m=(tt%3600)/60, s=tt%60;
  TopTour=0;
  J[Jo].TpsEcoule+=dt;
  JeuEnCours=false;
 }
//---------------------------------------------------------------------------
int plateau::Sauve(int f)
 {
  int Bon;
  Bon=(FileWrite(f, c, sizeof(c))>0)&&
	  (FileWrite(f, &NbCasesLibres, sizeof(NbCasesLibres))>0)&&
	  (FileWrite(f, &NbPasseTour, sizeof(NbPasseTour))>0);
  return Bon;
 }
//---------------------------------------------------------------------------
int plateau::Charge(int f)
 {
  int Bon;
  Bon=(FileRead(f, c, sizeof(c))>0)&&
	  (FileRead(f, &NbCasesLibres, sizeof(NbCasesLibres))>0)&&
      (FileRead(f, &NbPasseTour, sizeof(NbPasseTour))>0);
  return Bon;
 }
//---------------------------------------------------------------------------
joueur::joueur(unsigned NumJo)
 {
  int i;
  Rang=NumJo;
  for(i=1; i<27; i++) Nombre[i]=1;
  Nombre[0]=26;
  Automate=false;
  RechercheDeplacements=true;
  NbMaxLettres=NBMAXLDEF;
  Score=0;
  TpsEcoule=0.0;
  stNom="Joueur "+IntToStr((int)(NumJo+1));
 }
//---------------------------------------------------------------------------
void joueur::Reinitialise(String stNvNom, bool Auto, bool RechDepl, int NbMaxL)
 {
  int i;
  stNom=stNvNom;
  for(i=1; i<27; i++) Nombre[i]=1;
  Nombre[0]=26;
  Automate=Auto;
  RechercheDeplacements=RechDepl;
  NbMaxLettres=NbMaxL;
  Score=0;
  TpsEcoule=0.0;
 }
//---------------------------------------------------------------------------
void joueur::IncrementeScore(int Points)
 {
  Score+=Points;
  if (Points) frmScores->MajScores();
 }
//---------------------------------------------------------------------------
void joueur::DefPrmCase(int x, int y)
 {
  CoordDeb[0]=x;
  CoordDeb[1]=y;
 }
//---------------------------------------------------------------------------
void joueur::AfficheLettresDisp()
 {
  int i, Couleur;
  for(i=0; i<26; i++)
   {
    frmPlateau->DessineHexagone(610-30*(i%2), 12+17*i, Couleur=(Nombre[i+1]>0)*(Rang+1), CLAIR);
    frmPlateau->AfficheValeurs(610-30*(i%2), 12+17*i, 'A'+i, Nombre[i+1], Couleur, clBlack);
   }
 }
//---------------------------------------------------------------------------
void joueur::PrendLettre(char Lettre)
 {
  Nombre[NUM_LETTRE(Lettre)]--;
  Nombre[0]--;
  AfficheLettresDisp();
 }
//---------------------------------------------------------------------------
void joueur::RemetLettre(char Lettre)
 {
  Nombre[NUM_LETTRE(Lettre)]++;
  Nombre[0]++;
  AfficheLettresDisp();
 }
//---------------------------------------------------------------------------
int joueur::Sauve(int f)
 {
  char szNom[9];
  int i, t=stNom.Length(), Bon;
  for(i=0; i<9; i++)
   szNom[i]=(i<t)?stNom[i+1]:0;
  szNom[8]=0;
  Bon=(FileWrite(f, szNom, 9)>0)&&
	  (FileWrite(f, CoordDeb, sizeof(CoordDeb))>0)&&
	  (FileWrite(f, Nombre, sizeof(Nombre))>0)&&
	  (FileWrite(f, &Automate, sizeof(Automate))>0)&&
	  (FileWrite(f, &RechercheDeplacements, sizeof(RechercheDeplacements))>0)&&
	  (FileWrite(f, &Score, sizeof(Score))>0)&&
	  (FileWrite(f, &NbMaxLettres, sizeof(NbMaxLettres))>0)&&
	  (FileWrite(f, &TpsEcoule, sizeof(TpsEcoule))>0);
  return Bon;
 }
//---------------------------------------------------------------------------
int joueur::Charge(int f)
 {
  int i, Bon;
  char szNom[9];
  Bon=(FileRead(f, szNom, 9)>0);
  stNom=String(szNom);
  Bon=(FileRead(f, CoordDeb, sizeof(CoordDeb))>0)&&
	  (FileRead(f, Nombre, sizeof(Nombre))>0)&&
	  (FileRead(f, &Automate, sizeof(Automate))>0)&&
	  (FileRead(f, &RechercheDeplacements, sizeof(RechercheDeplacements))>0)&&
	  (FileRead(f, &Score, sizeof(Score))>0)&&
	  (FileRead(f, &NbMaxLettres, sizeof(NbMaxLettres))>0)&&
	  (FileRead(f, &TpsEcoule, sizeof(TpsEcoule))>0);
  return Bon;
 }
//---------------------------------------------------------------------------
dico::dico()
 {
  int f=FileOpen(ExtractFilePath(Application->ExeName)+"L23456789ABCDEF", fmOpenRead);
  // v4.4 : ODS8 (v1.2 : ODS8)
  nbl[0]=162L;
  nbl[1]=1899L;
  nbl[2]=10492L;
  nbl[3]=39900L;
  nbl[4]=107946L;
  nbl[5]=225610L;
  nbl[6]=384312L;
  nbl[7]=536256L;
  nbl[8]=629540L;
  nbl[9]=635624L;
  nbl[10]=558012L;
  nbl[11]=428506L;
  nbl[12]=292404L;
  nbl[13]=181155L;
  /* // v4.3 : ODS7
  nbl[0]=160L;
  nbl[1]=1863L;
  nbl[2]=10256L;
  nbl[3]=39115L;
  nbl[4]=106086L;
  nbl[5]=221718L;
  nbl[6]=377272L;
  nbl[7]=525897L;
  nbl[8]=615870L;
  nbl[9]=621104L;
  nbl[10]=543972L;
  nbl[11]=417651L;
  nbl[12]=284998L;
  nbl[13]=176550L;
  // v4.2 : ODS6
  nbl[0]=160L;
  nbl[1]=1830L;
  nbl[2]=10036L;
  nbl[3]=38225L;
  nbl[4]=103908L;
  nbl[5]=217490L;
  nbl[6]=370632L;
  nbl[7]=517203L;
  nbl[8]=604870L;
  nbl[9]=609796L;
  nbl[10]=533616L;
  nbl[11]=409383L;
  nbl[12]=278488L;
  nbl[13]=171930L;
  // v4.1 : OSD5
  nbl[0]=154L;
  nbl[1]=1767L;
  nbl[2]=9764L;
  nbl[3]=37415L;
  nbl[4]=102210L;
  nbl[5]=214431L;
  nbl[6]=365136L;
  nbl[7]=509157L;
  nbl[8]=595260L;
  nbl[9]=598862L;
  nbl[10]=522204L;
  nbl[11]=398970L;
  nbl[12]=269906L;
  nbl[13]=165930L;
  */
  Indice[0]=0L;
  for(int i=1; i<NBLMAX; i++)
   Indice[i]=Indice[i-1]+nbl[i-1];
  frmDico=new TfrmDico(Application);
  frmDico->CGauge->MaxValue=(NTL+1)/5;
  frmDico->Show();
  if (!f)
   {
    frmDico->StatusBar->SimpleText="Fichier L23456789ABCDEF introuvable !";
    return;
   }
  int Puiss26[6]={1,26,676,17576,456976};
  for(int i=0; i<NTL/5; i++) // v4.3 (on n'a pas les deux dernières lettres dans l'ODS7)
   {
    int x;
	FileRead(f, &x, 3);
	for(int j=4; j>-1; j--)
	 {
	  Dico[5*i+j]='A'+(char)(x/Puiss26[j]);
	  x%=Puiss26[j];
	 }
	if ((i==(NTL/5))||(!(i%(NTL/500)))) // v4.3 (on n'a pas les deux dernières lettres dans l'ODS7)
	 {
	  frmDico->CGauge->Progress=i;
	  frmDico->CGauge->Repaint();
	 }
   }
  FileClose(f);
  Dico[NTL-2]='N'; // v4.3 : idem ODS7 mais parce qu'on les a pas dans le fichier ! // v4.2 : ODS6
  Dico[NTL-1]='E'; // v4.3 : idem ODS7 mais parce qu'on les a pas dans le fichier ! // v4.2 : ODS6
  frmDico->CGauge->Progress=frmDico->CGauge->MaxValue;
  frmDico->CGauge->Repaint();
  frmDico->Close();
  delete frmDico;
  frmDico=NULL;
 }
//---------------------------------------------------------------------------
int dico::Existe(char *Mot, unsigned Taille)
 {
  if ((Taille<NBLMIN)||(Taille>NBLMAX)) return 0; // v4.0
  char MotCrt[NBLMAX+1];
  int Comp;
  unsigned long iInf=0,
                iSup=nbl[Taille-2]/(unsigned long)(Taille)-1L,
                iMil=(iInf+iSup)/2;
  Comp=strncmp(Dico+Indice[Taille-2]+iMil*(unsigned long)Taille, Mot, Taille);
  MotCrt[Taille]=0;
  while(Comp&&(iSup>iInf))
   {
    if ((iSup-iInf==1)&&Comp)
     iInf=iSup;
    else
     if (Comp<=0)
      iInf=iMil;
     else iSup=iMil;
    iMil=(iInf+iSup)/2;
    strncpy(MotCrt, Dico+Indice[Taille-2]+iMil*(unsigned long)Taille, Taille);
    Comp=strncmp(Dico+Indice[Taille-2]+iMil*(unsigned long)Taille, Mot, Taille);
   }
  return (!Comp);
 }
//---------------------------------------------------------------------------
 