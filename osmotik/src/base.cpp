//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "base.h"
#include "dico_f.h"
#include <string.h>
#include <Forms.hpp>
#include <System.hpp>
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
#define MAX(x,y) (((x)>(y))?(x):(y))
#define MIN(x,y) (((x)<(y))?(x):(y))
#define CV(x,y,k,d) CoordonneesValides((x)+(k)*dx[(int)(d)], (y)+(k)*dy[(int)(d)])
//---------------------------------------------------------------------------
#pragma package(smart_init)
//===========================================================================
// INSTANCES des éléments principaux du jeu :
//===========================================================================
int Version=DRN_VERSION_SMT; // Sert aux ouvertures fermetures de fichiers
//---------------------------------------------------------------------------*/
dico Dico;
plateau *P=NULL;
joueur J[NBMAXCAMPS]={{cBleu}, {cRouge}, {cJaune}, {cVert}, {cMagenta}, {cCiel}};
//===========================================================================
// CONSTANTES pour le fonctionnement de l'affichage
//===========================================================================
/* Les sommets & directions sont dans l'ordreinverse trigo. Pourquoi ?
// Parce que l'ordonnée est inversée par rapport à la géométrie classique.
//       A         - Les sommets de l'hexagones sont dans l'ordre 1,2,3,4,5,6.
// F  1-----2   B  - Les directions sont A(N),B(NE),C(SE),D(S),E(SO),F(NO).
//   /       \
//  6    ·    3
//   \       /
// E  5-----4   C
//       D
//---------------------------------------------------------------------------*/
// Coordonnées des sommets de l'hexagone central d'échelle 1
const TPoint ph[NBDIR] = { TPoint(-250,-433),
                           TPoint( 250,-433),
                           TPoint( 500,   0),
                           TPoint( 250, 433),
                           TPoint(-250, 433),
                           TPoint(-500,   0)};
//---------------------------------------------------------------------------
const AnsiString asVide,
                 asCamp[NBMAXCAMPS+1]={"", "Bleu","Rouge","Jaune","Vert","Magenta","Ciel"}; // v0.8.5 (pour affichage contenu hexagone)
//---------------------------------------------------------------------------
// Mesures principales de l'hexagone  d'échelle 1
const int dc = 250,           // dépassement des côtés gauche/droite (dx entre les sommets hauts/bas et les sommets gauche/droite)
          lh = 750, hh = 433, // Largeurs et demi-hauteurs
          lq = 750, hq = 433, // Largeurs et hauteurs du quadrillage pour déterminer l'hexagone en fonction de coordonnées du Canvas
          lc = 500,           // Longueur d'un côté
          hl = 300;           // Hauteur de la lettre
//---------------------------------------------------------------------------
const double kfl = 1.2, // Sert à déterminer la hauteur nécessaire pour afficher une lettre en fonction de Font.Size :
                          // Hauteur en pixels = kf * Font.Size
             kfv = 2.0;  // Idem pour la valeur (en dessous)
//---------------------------------------------------------------------------
const TColor ch[2*(NBMAXCAMPS+1)] = { clGray,   clBlue, clRed,    clYellow, clLime,  clFuchsia, clAqua,
                                      clSilver, clNavy, clMaroon, clOlive,  clGreen, clPurple,  clTeal};
//---------------------------------------------------------------------------
// Le système de coordonnées fonctionne sur deux directions :
// 1ère coordonnée = index des //(BF) de droite/haut vers gauche/bas (chiffres)
// 2ème coordonnée = index des //(GC) de gauche/haut vers droite/bas (lettres)
/*
                                   ·  ·
                               ·  · 1A ·  ·
                           ·  · 2A ·  · 1B ·  ·
						  · 3A ·  · 2B ·  · 1C ·
						   ·  · 3B ·  · 2C ·  ·
						  · 4B ·  · 3C ·  · 2D ·
						   ·  · 4C ·  · 3D ·  ·
						  · 5C ·  · 4D ·  · 3E ·
						   ·  · 5D ·  · 4E ·  ·
							   ·  · 5E ·  ·
								   ·  ·                                     */
//---------------------------------------------------------------------------*/
// Changement de coordonnées suivant les 6 directions
const int dx[NBDIR+1]={0,-1,-1, 0, 1,1, 0},
		  dy[NBDIR+1]={0,-1, 0, 1, 1,0,-1};
const direction InvDir[NBDIR+1]={dAucune, d6h, d8h, d10h, d0h, d2h, d4h};
const String stErrPlacementIncorrect="Placement incorrect"; // v1.4 : String au lieu de char[]
//===========================================================================
// CONSTANTES pour le fonctionnement du jeu
//===========================================================================
// Score min. pour regénérer et aussi
// l'effectif au départ du jeu.   A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
const int Score0[NBLALPHABET] = { 5, 2, 2, 2, 5, 2, 2, 2, 4, 1, 1, 3, 2, 3, 4, 2, 1, 3, 4, 3, 4, 2, 1, 1, 1, 1},
		  NbCamps[NBCONFIGSDEPART]={2,3,6},
		  // ATTENTION :  X0 et X0 sont à multiplier par P->N-1 (dimensions variables du plateau)
		  X0[NBCONFIGSDEPART][NBMAXCAMPS]={{0,2,-1,-1,-1,-1},{0,1,2,-1,-1,-1},{0,0,1,2,2,1}}, // v1.4 : X0,Y0 au lieu de x0,y0 réservés
		  Y0[NBCONFIGSDEPART][NBMAXCAMPS]={{0,2,-1,-1,-1,-1},{0,2,1,-1,-1,-1},{0,1,2,2,1,0}}; // v1.4 : X0,Y0 au lieu de x0,y0 réservés
//===========================================================================
// FONCTIONS EXTERNALISABLES pour la gestion globale
//===========================================================================
//---------------------------------------------------------------------------
// v1.4 : Pour les fichiers créés par Osmotik
//        on utilise le chemin donné par %LocalAppData% pour Windows 7 ou plus
//        sinon le dossier de l'exécutable
//---------------------------------------------------------------------------
String stRepLocalAppData()
 {
   String stResult;
   String stExePath = ExtractFilePath(ParamStr(0));
   const String stVarLocalAppData  = "LOCALAPPDATA";
   const String stVarUserProfile  = "USERPROFILE";
   const String stRepLocAppDataCvw = "\\Patquoi.fr\\Osmotik\\";
   stResult = GetEnvironmentVariable(stVarLocalAppData);
   if (stResult == "")
	{ // Windows 7~10
	 stResult = GetEnvironmentVariable(stVarUserProfile);
	 if (stResult == "")
	   stResult = stExePath;
	 else
	  { // Windows XP
	   stResult = stResult + "\\Local Settings\\Application Data" + stRepLocAppDataCvw;
	   if (!DirectoryExists(stResult))
		 if (!ForceDirectories(stResult))
		   stResult = stExePath;
	  }
	}
   else
	{ // Autres
	 stResult = stResult + stRepLocAppDataCvw;
	 if (!DirectoryExists(stResult))
	   if (!ForceDirectories(stResult))
		 stResult = stExePath;
	}
   return stResult;
 }
//===========================================================================
// METHODES
//===========================================================================
// Classe BILAN
//---------------------------------------------------------------------------*/
void bilan::Initialise()
 {
  s=p=0;
  for(int i=0; i<NBMAXCAMPS+1; i++)
   ppaa[i]=lpaa[i]=pppa[i]=lppa[i]=0;
 }
//---------------------------------------------------------------------------*/
void bilan::AccumulePPAA(joueur *ja) { s++; ppaa[ja->Camp]++; ppaa[0]++; };
void bilan::AccumuleLPAA(joueur *ja) { AccumulePPAA(ja); lpaa[ja->Camp]++; lpaa[0]++; };
void bilan::EnregistrePPPA(joueur *ja) { pppa[ja->Camp]++; pppa[0]++; };
void bilan::EnregistreLPPA(joueur *ja) { lppa[ja->Camp]++; lppa[0]++; };
//---------------------------------------------------------------------------*/
// Classe HEXAGONE
//---------------------------------------------------------------------------*/
int hexagone::Xc()
 {
  double K=(Type==thPlateau)?P->K:P->Khp;
  return (int)(K*(lh*(Y-X))+0.5)+P->Xc;
 }
//---------------------------------------------------------------------------*/
int hexagone::Yc()
 {
  double K=(Type==thPlateau)?P->K:P->Khp, // On calcule K et N en fonction de la localisation
         N=(Type==thPlateau)?P->N:P->Nhp; // de l'hexagone (dans ou hors plateau)
  return (int)(K*(hh*(X+Y-2*N+2))+0.5)+P->Yc;
 }
//---------------------------------------------------------------------------*/
void hexagone::Dessine(TCanvas *Canvas)
 { // Les dimensions de l'hexagone dépendent des coordonnées (hexagone du plateau ou non)
  double K=(Type==thPlateau)?P->K:P->Khp, // On calcule K et N en fonction de la localisation
         N=(Type==thPlateau)?P->N:P->Nhp; // de l'hexagone (dans ou hors plateau)
  String stLettre=(Lettre?String(Lettre):" "), // v1.4 : String au lieu d'AnsiString
		 stValeur=(Lettre?IntToStr(Valeur):" "); // v1.4 : String au lieu d'AnsiString
  String stFontName = Canvas->Font->Name; // v1.4 : on sauvegarde avant affichage de la valeur
  TPoint p[NBDIR];
  double FacteurHDPI = Screen->PixelsPerInch / 96.0; // v1.4
  for(int i=0; i<NBDIR; i++)
   p[i]=Point( (int)(K*(ph[i].x+lh*(Y-X))+0.5)+P->Xc,
			   (int)(K*(ph[i].y+hh*(X+Y-2*N+2))+0.5)+P->Yc);
  Canvas->Pen->Color=((X==P->Xs)&&(Y==P->Ys))?clWhite:clBlack;
  Canvas->Brush->Color=MotForme?clWhite:ch[Camp+(Lettre&&(!Valeur))*(NBMAXCAMPS+1)];
  Canvas->Polygon(p, 5);
  Canvas->Font->Size = (int)(0.5+kfl*(K*hl/FacteurHDPI)); // v1.4 + FacteurHDPI
  // v0.9.4 : Ci-dessous : Lettres en noir sauf pour les bleus (en blanc)
  Canvas->Font->Color= MotForme?
					   (P&&P->LettrePosee(X,Y)?((Canvas->Brush->Color==clNavy)?clWhite:clBlack):clGray):
					   ((Type==thPlateau)?
						((P&&P->LettreCapitalisable(X, Y))?
						 ch[Camp+NBMAXCAMPS+1]:
						 (Lettre&&(Valeur>=Score0[(int)(Lettre-'A')])?clGray:((Canvas->Brush->Color==clNavy)?clWhite:clBlack))): // v0.8.1
						clBlack);
  // ATTENTION : Canvas->TextFlags doit être défini à ETO_OPAQUE;
  int x0=(int)(K*(lh*(Y-X))+0.5)+P->Xc,
	  y0=(int)(K*(hh*(X+Y-2*N+2))+0.5)+P->Yc,
	  xl=x0-Canvas->TextWidth(stLettre)/2,
	  yl=y0-Canvas->TextHeight(stLettre)/2-K*hh/6,  // v1.4.1 : On part du milieu et on retire 1/6ème de la hauteur de l'hexagone
	  tfv=(int)(0.5+kfv*(K*hl/FacteurHDPI)/4); // v1.4 + FacteurHDPI
  Canvas->TextRect( Rect(xl,yl+1,
						 xl+Canvas->TextWidth(stLettre)-1,
						 yl+Canvas->TextHeight(stLettre)-1),
					xl,yl,
					stLettre);
  Canvas->Font->Name="MS Sans Serif"; // v1.4
  Canvas->Font->Size=tfv;
  int xv=x0-Canvas->TextWidth(stValeur)/2,
	  yv=p[4].y-Canvas->TextHeight(stValeur);
  Canvas->TextOut(xv,yv, stValeur);
  Canvas->Font->Name = stFontName; // v1.4 : On restaure la police de la lettre
 }
//---------------------------------------------------------------------------*/
void hexagone::PoseLettre(TCanvas *Canvas, camp c, char l, int t)
 {
  Lettre=l;
  Camp=c;
  Valeur=0;
  Tour=t; // Permet de repérer les lettres posées pendant un tour (couleur de lettre différente lors de la visualisation des mots formés)
  Dessine(Canvas);
 }
//---------------------------------------------------------------------------*/
AnsiString hexagone::asContenu() // v0.8.5
 {
  if (Lettre)
   return Format( "Lettre %s %s Valeur %d",
                  ARRAYOFCONST(( AnsiString(Lettre),
                                 asCamp[Camp],
                                 Valeur)));
  else
   return asVide; 
 }
//---------------------------------------------------------------------------*/
// Classe PLATEAU
//---------------------------------------------------------------------------*/
plateau::plateau(int n, config_depart cd, int nl)
 {
  PartieEnCours=FormationMotEnCours=false;
  N=n;
  NbCasesLibres=3*N*(N-1)+1;
  NbAbandons=0;
  CreeHexagones();
  Xs=Ys=Xc=Yc=-1; K=0.0; CfgDep=cd; NbMaxLettresAPlacer=nl;
  Nhp=7; // Taille constante des hexagones hors plateau (référence et jeu du camp courant)
  // Propriétés de jeu
  CampCrt=cNeutre; // InitialiseTourSuivant passera à cBleu
  TourCrt=0; // Le premier tour est le tour du premier mot posé depuis la case colorée (tour=0)
  // On définit la case départ de chaque camp
  for(int i=0; i<NbCamps[CfgDep]; i++)
   h[(N-1)*X0[CfgDep][i]][(N-1)*Y0[CfgDep][i]].Camp=(camp)(i+1); // v1.4 : X0,Y0 au lieu de x0,y0 réservés
 };
//---------------------------------------------------------------------------*/
void plateau::CreeHexagones() // Et initialise aussi les hexagones de référence...
 {
  h=new hexagone*[2*N-1];
  for(int i=0; i<2*N-1; i++)
   {
    h[i]=new hexagone[2*N-1];
    for(int j=0; j<2*N-1; j++)
     h[i][j].Initialise(i, j);
   }
  // Initialisation des hexagones de référence (alphabet à gauche du plateau)
  for(int i=0; i<NBLALPHABET; i++)
   hr[i].Initialise((i+1)/2+4, i/2-4, Score0[i], (char)('A'+i));
 }
//---------------------------------------------------------------------------*/
void plateau::DetruitHexagones()
 {
  for(int i=0; i<2*N-1; i++)
   delete[] h[i];
  delete[] h;
 }
//---------------------------------------------------------------------------*/
void plateau::Dessine(TCanvas *Canvas)
 {
  for(int i=0; i<2*N-1; i++)
   for(int j=(i>=N)*(i-N+1); j<N+i-(i>=N)*(i-N+1); j++)
    h[i][j].Dessine(Canvas);
  if (CoordonneesValides(Xs, Ys))
   h[Xs][Ys].Dessine(Canvas);
  h[0][0].Dessine(Canvas); // Test car la lettre de h[0][0] se décale
 }
//---------------------------------------------------------------------------*/
void plateau::DessineReference(TCanvas *Canvas)
 {
  for(int i=0; i<NBLALPHABET; i++)
   hr[i].Dessine(Canvas);
 }
//---------------------------------------------------------------------------*/
void plateau::DessineCapitalLettres(TCanvas *Canvas) // On suppose que CampCrt>0
 {
  for(int i=0; i<NBLALPHABET; i++)
   JCRT.h[i].Dessine(Canvas);
 }
//---------------------------------------------------------------------------*/
void plateau::DefinitEchelle(int Largeur, int Hauteur) // Zone d'affichage (plateau + référence + jeu)
 {
  double Klhp=(double)(Largeur-4)/((2*Nhp)*lh+dc),
         Khhp=(double)(Hauteur-4)/(2*(2*Nhp)*hh),
         Kl=(double)(Largeur-4)/((2*N)*lh+dc),
         Kh=(double)(Hauteur-4)/(2*(2*N-1)*hh);
  K=(Kl<Kh)?Kl:Kh; Khp=(Klhp<Khhp)?Klhp:Khhp;
  Xc=Largeur/2; Yc=Hauteur/2;
 }
//---------------------------------------------------------------------------*/
int plateau::Xh(int X, int Y) // Renvoie l'abcisse de l'hexagone que le point (X,Y) sélectionne (-1 si aucun)
 {
  int x=Xq(X,Y), y=Yq(X,Y);
  return (y-x+2*(N-1)+(x%2!=y%2))/2;
 }
//---------------------------------------------------------------------------*/
int plateau::Yh(int X, int Y) // Renvoie l'ordonnée de l'hexagone que le point (X,Y) sélectionne (-1 si aucun)
 {
  int x=Xq(X,Y), y=Yq(X,Y);
  return (x+y+2*(N-1)+(x%2!=y%2))/2;
 }
//---------------------------------------------------------------------------*/
void plateau::ChangeHexagoneCourant(TCanvas *Canvas, int X, int Y)
 {
  int AncX=Xs, AncY=Ys;
  Xs=X; Ys=Y;
  if ((AncX>-1)&&(AncY>-1))
   h[AncX][AncY].Dessine(Canvas);
  if ((Xs>-1)&&(Ys>-1))
   h[Xs][Ys].Dessine(Canvas);
 }
//---------------------------------------------------------------------------*/
bool plateau::ChercheMots(int xd, int yd, direction d, int iFMin, int iD, int iF)
 {
  int iFMax=iFMin-1, NbMotsTrv=0;
  bool MotRenverse,
       PositionOk=!TourCrt; // Il faut une lettre de même camp déjà posée qui participe à au moins un mot sauf au premier tour
  char szMot[NBLMAXMOTDICO+1];
  // Tout d'abord les mots principaux (dans l'axe de la direction choisie)
  for(int i=iD; i<=0; i++)
   {
    bool Existe=false;
    for(int j=MIN(i+NBLMAXMOTDICO-1,iF); (!Existe)&&(j>=MAX(i+NBLMINMOTDICO-1,iFMax+1)); j--)
     {
      bool LettreMemeCampTrv=PositionOk;
      for(int k=i; k<=j; k++)
       {
        szMot[k-i]=H(xd,yd,k,d).Lettre;
        LettreMemeCampTrv|=LettreMemeCampDejaPosee(X(xd,k,d),Y(yd,k,d));
       }
      szMot[j-i+1]='\0';
      if ((strlen(szMot))>1)
       {
        MotRenverse=false;
        Existe=Dico.Existe(szMot, j-i+1);
        if (!Existe)
         { // Si le mot n'existe pas on regarde le mot renversé
          for(int a=0; a<(j-i+1)/2; a++)
           {
            int b=j-i-a;
            // Permutation de lettres
            szMot[a]=szMot[a]+szMot[b];
            szMot[b]=szMot[a]-szMot[b];
            szMot[a]=szMot[a]-szMot[b];
           }
          MotRenverse=true;
          Existe=Dico.Existe(szMot, j-i+1);
         }
        if (Existe)
         {
          PositionOk|=LettreMemeCampTrv;
          iFMax=MAX(iFMax,j);
          int km=(MotRenverse?j:i);
          direction dm=(MotRenverse?InvDir[(int)d]:d);
          JCRT.slMotsFormes->AddObject( AnsiString(szMot),
                                        new proprietes_mot( X(xd,km,d), Y(yd,km,d), dm));
          NbMotsTrv++;
         }
       }
     }
   }
  if (!NbMotsTrv)
   {
	Application->MessageBox(L"Les lettres placées ne permettent pas de former un mot valide.",
							 stErrPlacementIncorrect.c_str(), MB_ICONEXCLAMATION);
	return false;
   }
  if (!PositionOk)
   {
	Application->MessageBox( L"Au moins une lettre déjà placée de votre camp doit participer à la formation du mot principal.",
							 stErrPlacementIncorrect.c_str(), MB_ICONEXCLAMATION);
	return false;
   }
  // Ensuite les autres directions à partir des lettres posées uniquement
  for(int il=0; il<=iFMin; il++)
   {
    if (LettrePosee(xd+il*dx[d], yd+il*dy[d]))
     {
      int xv=X(xd,il,d),
          yv=Y(yd,il,d);
      for(int dv=(int)d0h; dv<=(int)d4h; dv++)
       if ((dv!=(int)d)&&(dv!=InvDir[(int)d])) // Direction en dehors de l'axe du mot principal
        {
         // On détermine les limites de recherche
         int iDv, iFv, iFvMax=-1;
         for( iDv=0;
              CV(xv,yv,(iDv-1),dv)&&H(xv,yv,(iDv-1),dv).Lettre&&(iDv>-NBLMAXMOTDICO);
              iDv--);
         for( iFv=0;
              CV(xv,yv,(iFv+1),dv)&&H(xv,yv,(iFv+1),dv).Lettre&&(iFv<NBLMAXMOTDICO);
              iFv++);
         for(int i=iDv; i<=0; i++)
          {
           bool Existe=false;
           for(int j=MIN(i+NBLMAXMOTDICO-1,iFv); (!Existe)&&(j>=MAX(i+NBLMINMOTDICO-1,iFvMax+1)); j--)
            {
             for(int k=i; k<=j; k++)
              szMot[k-i]=H(xv,yv,k,dv).Lettre;
             szMot[j-i+1]='\0';
             if ((strlen(szMot))>1)
              {
               MotRenverse=false;
               Existe=Dico.Existe(szMot, j-i+1);
               if (!Existe)
                { // Si le mot n'existe pas on regarde le mot renversé
                 for(int a=0; a<(j-i+1)/2; a++)
                  {
                   int b=j-i-a;
                   // Permutation de lettres
                   szMot[a]=szMot[a]+szMot[b];
                   szMot[b]=szMot[a]-szMot[b];
                   szMot[a]=szMot[a]-szMot[b];
                  }
                 MotRenverse=true;
                 Existe=Dico.Existe(szMot, j-i+1);
                }
               if (Existe)
                {
                 iFvMax=MAX(iFvMax,j);
                 int km=(MotRenverse?j:i);
                 direction dm=(MotRenverse?InvDir[dv]:((direction)dv));
                 JCRT.slMotsFormes->AddObject( AnsiString(szMot),
                                               new proprietes_mot( X(xv,km,dv), Y(yv,km,dv), dm));
                 NbMotsTrv++;
                }
              }
            }
          }
        }
     }
   }
  return true;
 }
//---------------------------------------------------------------------------*/
bool plateau::LettresJouables(const AnsiString asLettresAPlacer, int xd, int yd, direction d, int &iFMin, int &iD, int &iF)
 { // Si le mot existe id et if donnent les index des premières et dernières lettres (h[xd][yd] a l'index 0, >>> dans la d).
  int l=asLettresAPlacer.Length(),
      NbLettresDejaPlacees;
  bool PositionOk=true; // Toutes les lettres posées doivent être sur le plateau
  iFMin=0; // Index minimal de la lettre initiale du mot principal (qui est celui de la première lettre placée)
  if (!l)
   {
	Application->MessageBox( L"Vous devez spécifier les lettres à placer sur le plateau de jeu.",
							 stErrPlacementIncorrect.c_str(), MB_ICONEXCLAMATION);
	return false;
   }
  if ((!TourCrt)&&(h[xd][yd].Camp!=CampCrt)) // Si premier tour, cas initiale imposée (case colorée)
   {
	Application->MessageBox( L"La case départ doit être la case de votre couleur lors du premier tour.",
							 stErrPlacementIncorrect.c_str(), MB_ICONEXCLAMATION);
    return false;
   }
  NbLettresDejaPlacees=0;
  // On recherche d'abord la fin potentielle du mot principale (iF)
  for(int i=0; PositionOk&&(i<l); i++)
   {
    while((PositionOk=CV(xd,yd,i+NbLettresDejaPlacees,d))&&
          H(xd,yd,i+NbLettresDejaPlacees,d).Lettre)
     NbLettresDejaPlacees++;
    if (PositionOk)
     iFMin=i+NbLettresDejaPlacees;
   }
  if (!PositionOk)
   {
    Application->MessageBox( L"Il n'est pas possible de placer toutes les lettres sur le plateau depuis la case et dans la direction choisies.",
							 stErrPlacementIncorrect.c_str(), MB_ICONEXCLAMATION);
    return false;
   }
  // On recherche maintenant la fin potentielle du mot principal (iF) en avant par rapport à la dernière lettre posée
  for( iF=iFMin;
       CV(xd,yd,iF+1,d)&&H(xd,yd,iF+1,d).Lettre;
       iF++);
  // On recherche maintenant le début potentiel du mot principal (iD) en arrière par rapport à la case choisie
  for( iD=0;
       CV(xd,yd,iD-1,d)&&H(xd,yd,iD-1,d).Lettre;
       iD--);
  return true;
 }
//---------------------------------------------------------------------------*/
void plateau::ComptabiliseMotFormeLettre(int iMot, int x, int y) // +1 point si même camp, sinon -1 point
 {
  h[x][y].MotForme=false; // On ne met plus en évidence la lettre (deuxième affichage avec la valeur mise à jour
  if (h[x][y].Camp==CampCrt)
   {
    h[x][y].Valeur++;
    JCRT.AccumulePoint(iMot);
   }
  else
   {
    camp CampAdverse;
    if ((CampAdverse=h[x][y].Camp))
     {
      if (h[x][y].Valeur)
       {
        h[x][y].Valeur--;
        JCRT.AccumulePPAA(iMot, &(JC(CampAdverse)));
       }
      else
       {
        h[x][y].Camp=CampCrt; h[x][y].Valeur++;
        JCRT.AccumuleLPAA(iMot, &(JC(CampAdverse)));
       }
     }
   }
 }
//---------------------------------------------------------------------------*/
void plateau::ComptabiliseMotForme(TCanvas *Canvas, int iMot)
 {
  proprietes_mot *pm=(proprietes_mot*)(_JCRT.slMotsFormes->Objects[iMot]);
  AnsiString asMot=_JCRT.slMotsFormes->Strings[iMot];
  for(int i=0; i<asMot.Length(); i++)
   {
    ComptabiliseMotFormeLettre(iMot, X(pm->x,i,pm->d), Y(pm->y,i,pm->d));
    H(pm->x,pm->y,i,pm->d).Dessine(Canvas);
   }
 }
//---------------------------------------------------------------------------*/
void plateau::DessineMot(TCanvas *Canvas, int iMot)
 {
  proprietes_mot *pm=(proprietes_mot*)(_JCRT.slMotsFormes->Objects[iMot]);
  AnsiString asMot=_JCRT.slMotsFormes->Strings[iMot];
  for(int i=0; i<asMot.Length(); i++)
   {
    H(pm->x,pm->y,i,pm->d).MotForme=true; // On met en évidence la lettre (deuxième affichage avec la valeur mise à jour
    H(pm->x,pm->y,i,pm->d).Dessine(Canvas); // ET On rafraichit l'hexagone 
   }
 }
//---------------------------------------------------------------------------*/
void plateau::PoseLettres(TCanvas *Canvas, const AnsiString asLettresAPlacer, int xd, int yd, direction d)
 {
  int x, y,
      l=asLettresAPlacer.Length(),
      NbLettresDejaPlacees=0;
  for(int i=0; i<l; i++)
   {
    while(h[x=X(xd,i+NbLettresDejaPlacees,d)]
           [y=Y(yd,i+NbLettresDejaPlacees,d)].Lettre)
     NbLettresDejaPlacees++;
    PoseLettre(Canvas, x, y, asLettresAPlacer[i+1]);
   }
 }
//---------------------------------------------------------------------------*/
void plateau::RetireLettres(TCanvas *Canvas, int xd, int yd, int d, int iFMin)
 {
  for(int i=0; i<=iFMin; i++)
   if (P->LettrePosee(X(xd,i,d), Y(yd,i,d)))
    {
     H(xd,yd,i,d).RetireLettre(Canvas);
     NbCasesLibres++;
    }
  if (!TourCrt) h[xd][yd].Camp=CampCrt; // On remet la couleur de la case départ
 }
//---------------------------------------------------------------------------*/
bool plateau::ChargePlateau(int f) // v1.4 : int f au lieu de FILE *f et FileRead au lieu de fread
 {
  bool Ok=true;
  CreeHexagones(); // Alloue & initialise hr
  for(int i=0; Ok&&(i<2*N-1); i++)
   for(int j=0; Ok&&(j<2*N-1); j++)
	Ok=h[i][j].Charge(f);
  return Ok;
 }
//---------------------------------------------------------------------------*/
bool plateau::SauvePlateau(int f) // v1.4 : int f au lieu de FILE *f et FileRead au lieu de fread
 {
  bool Ok=true;
  for(int i=0; Ok&&(i<2*N-1); i++)
   for(int j=0; Ok&&(j<2*N-1); j++)
    Ok=h[i][j].Sauve(f);
  return Ok;
 }
//---------------------------------------------------------------------------*/
// Classe JOUEUR
//---------------------------------------------------------------------------*/
void joueur::Initialise()
 {
  for(int i=0; i<NBLALPHABET; i++)
   h[i].Initialise(thJeu, i/2-4, (i+1)/2+4, Camp, Score0[i], (char)('A'+i));
  if (slMotsFormes) delete slMotsFormes;
  slMotsFormes=new TStringList;
  BilanTotal.Initialise();
  InitialiseTour();
 }
//---------------------------------------------------------------------------*/
bool joueur::Charge(int f) // v1.4 : int f au lieu de FILE *f et FileRead au lieu de fread
   {
	return FileRead(f, &Camp, sizeof(Camp))&&
		   FileRead(f, h+ 0, sizeof(h[0]))&&
		   FileRead(f, h+ 1, sizeof(h[1]))&&
		   FileRead(f, h+ 2, sizeof(h[2]))&&
		   FileRead(f, h+ 3, sizeof(h[3]))&&
		   FileRead(f, h+ 4, sizeof(h[4]))&&
		   FileRead(f, h+ 5, sizeof(h[5]))&&
		   FileRead(f, h+ 6, sizeof(h[6]))&&
		   FileRead(f, h+ 7, sizeof(h[7]))&&
		   FileRead(f, h+ 8, sizeof(h[8]))&&
		   FileRead(f, h+ 9, sizeof(h[9]))&&
		   FileRead(f, h+10, sizeof(h[10]))&&
		   FileRead(f, h+11, sizeof(h[11]))&&
		   FileRead(f, h+12, sizeof(h[12]))&&
		   FileRead(f, h+13, sizeof(h[13]))&&
		   FileRead(f, h+14, sizeof(h[14]))&&
		   FileRead(f, h+15, sizeof(h[15]))&&
		   FileRead(f, h+16, sizeof(h[16]))&&
		   FileRead(f, h+17, sizeof(h[17]))&&
		   FileRead(f, h+18, sizeof(h[18]))&&
		   FileRead(f, h+19, sizeof(h[19]))&&
		   FileRead(f, h+20, sizeof(h[20]))&&
		   FileRead(f, h+21, sizeof(h[21]))&&
		   FileRead(f, h+22, sizeof(h[22]))&&
		   FileRead(f, h+23, sizeof(h[23]))&&
		   FileRead(f, h+24, sizeof(h[24]))&&
		   FileRead(f, h+25, sizeof(h[25]))&&
		   BilanTour.Charge(f)&&
		   BilanTotal.Charge(f)&&
		   ((Version<0x0940)||FileRead(f, &TempsEcoule, sizeof(TempsEcoule)));
   };
//---------------------------------------------------------------------------*/
bool joueur::Sauve(int f) // v1.4 : int f au lieu de FILE *f et FileRead au lieu de fread
   {
    return FileWrite(f, &Camp, sizeof(Camp))&&
           FileWrite(f, h+ 0, sizeof(h[0]))&&
           FileWrite(f, h+ 1, sizeof(h[1]))&&
           FileWrite(f, h+ 2, sizeof(h[2]))&&
           FileWrite(f, h+ 3, sizeof(h[3]))&&
		   FileWrite(f, h+ 4, sizeof(h[4]))&&
		   FileWrite(f, h+ 5, sizeof(h[5]))&&
		   FileWrite(f, h+ 6, sizeof(h[6]))&&
		   FileWrite(f, h+ 7, sizeof(h[7]))&&
		   FileWrite(f, h+ 8, sizeof(h[8]))&&
		   FileWrite(f, h+ 9, sizeof(h[9]))&&
           FileWrite(f, h+10, sizeof(h[10]))&&
           FileWrite(f, h+11, sizeof(h[11]))&&
           FileWrite(f, h+12, sizeof(h[12]))&&
           FileWrite(f, h+13, sizeof(h[13]))&&
           FileWrite(f, h+14, sizeof(h[14]))&&
           FileWrite(f, h+15, sizeof(h[15]))&&
           FileWrite(f, h+16, sizeof(h[16]))&&
           FileWrite(f, h+17, sizeof(h[17]))&&
           FileWrite(f, h+18, sizeof(h[18]))&&
           FileWrite(f, h+19, sizeof(h[19]))&&
           FileWrite(f, h+20, sizeof(h[20]))&&
           FileWrite(f, h+21, sizeof(h[21]))&&
           FileWrite(f, h+22, sizeof(h[22]))&&
           FileWrite(f, h+23, sizeof(h[23]))&&
           FileWrite(f, h+24, sizeof(h[24]))&&
           FileWrite(f, h+25, sizeof(h[25]))&&
           BilanTour.Sauve(f)&&
		   BilanTotal.Sauve(f)&&
		   ((Version<0x0940)||FileWrite(f, &TempsEcoule, sizeof(TempsEcoule)));
   }
//---------------------------------------------------------------------------
// Classe DICO
//---------------------------------------------------------------------------*/
dico::dico()
 {
  String stFichierDico = ExtractFilePath(Application->ExeName)+"L23456789ABCDEF";
  int f=FileOpen(stFichierDico, fmOpenRead); // v1.4 FileOpen au lieu de fopen
  if (f<=0) // v1.4 : on quitte tout de suite sinon la jauge reste derrière
   {
	Application->MessageBox(L"Fichier L23456789ABCDEF introuvable !", L"Impossible d'exécuter Osmotik", MB_ICONHAND);
	Application->Terminate();
    return;
   }

  // Dico[NBLDICO]=0; // v1.4
  // v1.5 : ODS9 (v1.2 : ODS8)
  nbl[0]=162L;
  nbl[1]=1917L;
  nbl[2]=10628L;
  nbl[3]=40295L;
  nbl[4]=109068L;
  nbl[5]=227885L;
  nbl[6]=388696L;
  nbl[7]=542871L;
  nbl[8]=637360L;
  nbl[9]=643764L;
  nbl[10]=564948L;
  nbl[11]=433498L;
  nbl[12]=295960L;
  nbl[13]=183420L;
  Indice[0]=0L;
  for(int i=1; i<NBLMAXMOTDICO; i++)
   Indice[i]=Indice[i-1]+nbl[i-1];

  // v1.9.2 : FormDico au lieu de frmDico (renommage)
  FormDico=new TFormDico(Application);
  FormDico->CGauge->MaxValue=(NBLDICO+1)/5;
  FormDico->Show();

  int Puiss26[6]={1,26,676,17576,456976};
  for(int i=0; i<NBLDICO/5; i++) // v1.2
   {
	int x;
	FileRead(f, &x, 3); // v1.4 : FileRead au lieu de fread
	for(int j=4; j>-1; j--)
     {
      Dico[5*i+j]='A'+(char)(x/Puiss26[j]);
      x%=Puiss26[j];
     }
    if ((i==(NBLDICO/5))||
        (!(i%(NBLDICO/500)))) // v1.2
     {
      FormDico->CGauge->Progress=i;
      FormDico->CGauge->Repaint();
     }
   }
  FileClose(f); // v1.4 FileClose(f) au lieu de fclose(f);
  Dico[NBLDICO-3]='N'; // v1.3 : ODS8
  Dico[NBLDICO-2]='N'; // v1.2 : ODS7 // v1.1 : ODS6
  Dico[NBLDICO-1]='E'; // v1.2 : ODS7 // v1.1 : ODS6
  FormDico->CGauge->Progress=FormDico->CGauge->MaxValue;
  FormDico->CGauge->Repaint();
  FormDico->Close();
  delete FormDico;
  FormDico=NULL;
 }
//---------------------------------------------------------------------------
bool dico::Existe(const char Mot[], unsigned Taille) // v1.4 : char [] au lieu de unsigned char *
 {
  char MotCrt[NBLMAXMOTDICO+1]; // v1.4 char au lieu de unsigned char
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

