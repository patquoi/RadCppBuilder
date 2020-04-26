//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "plateau_f.h"
#include "base.h"
#include "nomjo_f.h"
#include "scores_f.h"
#include "messages_f.h"
#include <dir.h>
#include <Registry.hpp>
#include <ShellApi.hpp>
#include "apropos_f.h"
#include "param_f.h"
#include "records_f.h"
#include "curseurs.h"

#define NBLETTRES    26

#define AJOUTABLE            1
#define DEPLACABLE           2
#define AJOUTABLE_DEPLACABLE 3

#define GARDE  true
#define LAISSE false

#define SELECTION_CASE ((xCrt>=0)&&(xCrt<NBXY)&&(yCrt>=0)&&(yCrt<NBXY))      // v4.0 : <=10 remplacé par <NBXY
#define CHOIX_CASE     ((xCase>=0)&&(xCase<NBXY)&&(yCase>=0)&&(yCase<NBXY))  // v4.0 : <=10 remplacé par <NBXY

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmPlateau *frmPlateau;
const TColor clJo[7][2]={{clGray, clLtGray},
                         {clNavy, clBlue},
                         {clGreen, clLime},
                         {clTeal, clAqua},
                         {clMaroon, clRed},
                         {clPurple, clFuchsia},
                         {clOlive, clYellow}};
const String stInterrompre="Choisissez la rubrique \"Partie\" | \"Interrompre\" ou appuyez sur Alt+I pour faire une pause.",
			 stContinuer=  "Choisissez la rubrique \"Partie\" | \"Continuer\" ou appuyez sur Alt+C pour poursuivre le jeu.",
			 stTitre="Osmoz²",
			 stTitrePause="Osmoz² [PAUSE]",
			 stCommentChoisirLaLettreAPlacer="Cliquez gauche sur la lettre à placer sur le plateau de jeu.",
			 stCommentChoisirLaLettreAPlacerAuDebut="Vous devez placer une lettre au sommet du plateau correspondant à votre couleur.",
			 stCommentChoisirLaLettreADeplacer="Cliquez gauche sur la lettre à déplacer sur le plateau de jeu.",
			 stCommentPoserLaLettreSurLePlateau="Cliquez gauche sur la case où vous souhaitez placer la lettre ou cliquez droit pour annuler (choisir une autre lettre).",
			 stCommentChoisirLaLettreSurLePlateau="Cliquez gauche sur la lettre à déplacer ou cliquez droit sur la lettre pour incrémenter son compte dans votre jeu (curseur +1).",
             stDecompteDesPoints="Décompte des points : appuyez sur le bouton Continuer de la boîte de dialogue sous les scores pour continuer...";
//---------------------------------------------------------------------------
__fastcall TfrmPlateau::TfrmPlateau(TComponent* Owner)
    : TForm(Owner)
{
 int i;
 for(i=0; i<NBCURSEURS; i++)
  { // v4.5 : On crée les curseurs
   crSmz[i]=CreateCursor(HInstance, // app. instance
						 16, // horizontal position of hot spot
						 16, // vertical position of hot spot
						 32, // cursor width
						 32, // cursor height
						 ANDmaskCursor[i],     // AND mask
						 XORmaskCursor[i]);   // XOR mask
   Screen->Cursors[i+1]=crSmz[i];
  }
 xCrt=yCrt=xCase=yCase=xLAD=yLAD=INDEFINI;
 EnregistrerMessages=true;
 OpenDialog->InitialDir=stRepLocalAppData();
 SaveDialog->InitialDir=stRepLocalAppData();
}
//---------------------------------------------------------------------------
void TfrmPlateau::ChangeSituation(situation NvSit)
 {
  switch(NvSit)
   {
    case choix_lettre:    if (J[Jo].Automate)
                           {
                            if (p.JeuEnCours)
                             {
                              StatusBar->SimpleText="";
                              p.PlaceLettreAuto();
                              JoueurSuivant();
                             }
                            else
                             {
                              RubriqueContinuer->Enabled=true;
                              if (!frmParametresAutomates->Interruption)
                               {
                                RubriqueInterrompre->Enabled=true;
								StatusBar->SimpleText=stInterrompre;
                                StatusBar->Repaint();
                                Timer->Enabled=true;
                               }
                              else
                               {
								Caption=stTitre;
								StatusBar->SimpleText=stContinuer;
                               }
                             }
                           }
                          else
                           {
                            LettreAPoser=LettreADeplacer=0;
                            xCrt=yCrt=xCase=yCase=xLAD=yLAD=INDEFINI;
							StatusBar->SimpleText=stCommentChoisirLaLettreAPlacer;
                           }
                          break;
	case choix_case:      StatusBar->SimpleText=stCommentPoserLaLettreSurLePlateau;
                          switch(Phase)
                           {
							case pose:        Cursor=CUR_LAP; break;
							case deplacement: Cursor=CUR_LAD; break;
                            default:          break;
                           }
                          break;
    case decompte_points: StatusBar->SimpleText=stDecompteDesPoints;
                          Cursor=crArrow; break;
    default: break;
   }
  switch(Sit)
   {
    case choix_lettre: EffaceSelectionCouranteLettre(GARDE); break;
    case choix_case:   Cursor=crArrow; break;
    default : break;
   }
  Sit=NvSit;
 }
//---------------------------------------------------------------------------
void TfrmPlateau::DessineHexagone(int x, int y, int Couleur, int Contraste) // v3.3
 {
  int i;
  TPoint p[NBDIR]={Point(0, 0), Point(18, 0), Point(28, 16), Point(18, 32), Point(0, 32), Point(-10, 16)};
  Canvas->Pen->Color=clJo[Couleur][Contraste]; // v3.3 (Contraste)
  Canvas->Pen->Style=psSolid;
  Canvas->Pen->Mode=pmCopy;
  Canvas->Brush->Color=clJo[Couleur][Contraste]; // v3.3 (Contraste)
  Canvas->Brush->Style=bsSolid;
  for(i=0; i<NBDIR; i++)
   { // v4.5 : prise en charge HDPI
	p[i].x=HDPI(p[i].x+x);
	p[i].y=HDPI(p[i].y+y);
   }
  Canvas->Polygon(p, 5);
 }
//---------------------------------------------------------------------------
void TfrmPlateau::AfficheValeurs(int x, int y, char Lettre, int Score, int Fond, TColor Couleur)
 {
  int xc, yc, tw, th;
  bool FondTropFonce=(Fond==1)&&(!Score)&&(Couleur==clBlack);
  wchar_t ws[3]=L" ", wsScore;
  String st;
  ws[0]=Lettre;
  st=String(ws);
  Canvas->Pen->Color=clJo[Fond][((!Fond)||Score)?CLAIR:FONCE]; // v3.3
  Canvas->Pen->Style=psSolid;
  Canvas->Pen->Mode=pmCopy;
  Canvas->Brush->Color=clJo[Fond][((!Fond)||Score)?CLAIR:FONCE]; // v3.3
  Canvas->Brush->Style=bsSolid;
  Canvas->Font->Color=FondTropFonce?clGray:Couleur;
  Canvas->Font->Name="Comic Sans MS";
  Canvas->Font->Size=14;

  // v4.5 : prise en charge HDPI
  tw=_HDPI(Canvas->TextWidth(st));
  th=_HDPI(Canvas->TextHeight(st));
  xc=HDPI(x+9-tw/2);
  yc=HDPI(y+26-th);

  Canvas->TextOut(xc, yc, st);    //y+23
  st=IntToStr(Score);
  Canvas->Font->Name="Small Fonts";
 Canvas->Font->Size=7;

  // v4.5 : prise en charge HDPI
  tw=_HDPI(Canvas->TextWidth(st));
  th=_HDPI(Canvas->TextHeight(st));
  xc=HDPI(x+8-tw/2);
  yc=HDPI(y+32-th);

  Canvas->TextOut(xc, yc, st);
 }
//---------------------------------------------------------------------------
void TfrmPlateau::AfficheCoordonnees()
 {
  int i, x, y;
  String stChiffre;
  Canvas->Pen->Color=clGray;
  Canvas->Pen->Style=psSolid;
  Canvas->Pen->Mode=pmCopy;
  Canvas->Brush->Color=clGray;
  Canvas->Brush->Style=bsSolid;
  Canvas->Font->Name="Small Fonts";
  Canvas->Font->Size=7;
  for(i=0; i<NBXY; i++)
   {
	stChiffre=IntToStr(i);
    // v4.5 : prise en charge HDPI
	x=HDPI(293-30*((i<8)*i+7*(i>=8)));
	y=HDPI(11+17*i+(17*(i-7))*(i>=8));
	Canvas->Font->Color=clBlue; Canvas->TextOut(x, y, stChiffre); // v4.0
	Canvas->Font->Color=clMaroon; Canvas->TextOut(HDPI(633)-x, y, stChiffre); // v4.0
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::FormPaint(TObject *Sender)
{
 p.AffichePlateau();
}
//---------------------------------------------------------------------------
void TfrmPlateau::EffaceSelectionCouranteLettre(bool GardeLettre)
 {
  int iCrt=(int)(LettreAPoser-'A'), Couleur;
  if ((iCrt>=0)&&(iCrt<=25))
   {
    DessineHexagone(610-30*(iCrt%2), 12+17*iCrt, Couleur=(J[Jo].Nombre[iCrt+1]>0)*(Jo+1), CLAIR);
    AfficheValeurs(610-30*(iCrt%2), 12+17*iCrt, 'A'+iCrt, J[Jo].Nombre[iCrt+1], Couleur, clBlack);
   }
  if (!GardeLettre) LettreAPoser=0;
 }
//---------------------------------------------------------------------------
void TfrmPlateau::EffaceSelectionCouranteCase(bool GardeCase)
 {
  if (SELECTION_CASE) p.AfficheCase(xCrt, yCrt, clBlack);
  if (!GardeCase)
   {
    xCrt=yCrt=xCase=yCase=INDEFINI;
    switch(Situation)
     {
      case choix_lettre: if (Cursor!=crArrow) Cursor=crArrow; break;
	  case choix_case:   if (Cursor!=CUR_LAD) Cursor=CUR_LAD; break;
      default: break;
     }
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 bool CaseDepot=false;
 int i, j, Couleur, NbCases, Cas,
     Col, Lig, xh, yh, h, xc, yc, xx, yy;
 if (J[Jo].Automate) return;

 // v4.5 : prise en charge HDPI
 X=_HDPI(X);
 Y=_HDPI(Y);

 switch(Situation)
  {
   case choix_lettre: // v4.5 : prise en charge HDPI
					  if ((X>=575)&&(X<=634)&&(Y>=12+17*(X<605))&&(Y<=453+17*(X<605)))
                       { // Le curseur est sur le jeu en situation de choix d'une lettre
						StatusBar->SimpleText=stCommentChoisirLaLettreAPlacer;
                        i=(X<605)+2*((Y-12-17*(X<605))/34);
                        if (i!=(int)(LettreAPoser-'A'))
						 {
						  if (J[Jo].Nombre[i+1]&&(Tour||(!p.LettreUtiliseeAuDepart(i+'A')&&(i!=16)&&(i!=25))))
						   {
							EffaceSelectionCouranteLettre(LAISSE);
							AfficheValeurs(610-30*(i%2), 12+17*i, 'A'+i, J[Jo].Nombre[i+1], Jo+1, clLtGray);
							LettreAPoser=(char)(i+'A'); LettreADeplacer=0;
						   }
						  else // Le curseur est sur une lettre indisponible : on efface la sélection courante
						   EffaceSelectionCouranteLettre(LAISSE);
                         }
                       }
                      else // Le curseur est en dehors de la zone de sélection : on efface la sélection courante
                       {
						StatusBar->SimpleText=Tour?stCommentChoisirLaLettreADeplacer:stCommentChoisirLaLettreAPlacerAuDebut;
                        EffaceSelectionCouranteLettre(LAISSE);

						// v4.5 : prise en charge HDPI
						if// ((X>160)&&(X<491)&&(Y>53)&&(Y<426))
                             ((X>94)&&(X<545)&&(Y>11)&&(Y<520)) // v4.0
                         {  // Zone du plateau de jeu : on regarde si la lettre sous le curseur est déplaçable ou ajoutable
                          Col=(X-95)/30; // v4.0 : 161 remplacé par 95
                          Lig=(Y-12)/17; // v4.0 : 54 remplacé par 12
                          // v4.0 : remplacement de 5*Col par 7*Col et Col*5 par Col*7  (* étant un opérateur)
                          if ((Lig>=abs(Col-7))&&(Lig<=29-abs(Col-7))) // v4.0 : 29 à la place de 21
                           {
                            // xh=166+30*Col;
                            xh=100+30*Col; // v4.0
                            // yh=54+17*(2*((Lig-!(Col%2))/2)+!(Col%2));
                            yh=12+17*(2*((Lig-!(Col%2))/2)+!(Col%2));
                            h=(Lig-abs(7-Col))/2;
                            xc=h+(Col<7)*(7-Col);
                            yc=h+(Col>7)*(Col-7);
                            if ((xc>=0)&&(xc<NBXY)&& // v4.0 xc<=10 remplacé par xc<=14
                                ((xc!=xCrt)||(yc!=yCrt))&&
                                (xc<NBXY)&&
                                (yc<NBXY)&&
                                (xc>=p.XYMin[yc])&&
                                (xc<=p.XYMax[yc])&&
                                (yc>=p.XYMin[xc])&&
                                (yc<=p.XYMax[xc])&&
                                (p.c[xc][yc].Joueur==Jo+1)&&
                                (p.c[xc][yc].Valeur>0))
                             {
                              Cas=  p.NouvelleLettrePossible(xc, yc)+
                                  2*p.LettreDeplacable(xc, yc);
                              if (Cas)
                               {
                                if (Cursor!=(TCursor)(Cas+NBLETTRES)) Cursor=(TCursor)(Cas+NBLETTRES);
                                xCrt=xc; yCrt=yc;
                                if (Cas&DEPLACABLE)
                                 {
                                  LettreADeplacer=(char)p.c[xc][yc].Lettre;
                                  LettreAPoser=0;
                                 }
                               }
                              else // Ni ajoutable ni déplaçable -> Curseur Flèche
                               EffaceSelectionCouranteCase(LAISSE);
							  StatusBar->SimpleText=stCommentChoisirLaLettreSurLePlateau;
                             }
                            else
                             if ((xc!=xCrt)||(yc!=yCrt))
                              EffaceSelectionCouranteCase(LAISSE);
                           }
                          else
                           EffaceSelectionCouranteCase(LAISSE);
                         }
                        else
                         EffaceSelectionCouranteCase(LAISSE);
                       }
                      break;
   case choix_case:   // v4.5 : prise en charge HDPI
					  if// ((X>160)&&(X<491)&&(Y>53)&&(Y<426))
                           ((X>94)&&(X<545)&&(Y>11)&&(Y<520)) // v4.0
                       {  // Zone du plateau de jeu : on regarde si la lettre sous le curseur est déplaçable ou ajoutable
                        Col=(X-95)/30; // v4.0 : 161 remplacé par 95
                        Lig=(Y-12)/17; // v4.0 : 54 remplacé par 12
                        // v4.0 : remplacement de 5*Col par 7*Col et Col*5 par Col*7  (* étant un opérateur)
                        if ((Lig>=abs(Col-7))&&(Lig<=29-abs(Col-7))) // v4.0 : 29 à la place de 21
                         {
                          // xh=166+30*Col;
                          xh=100+30*Col; // v4.0
                          // yh=54+17*(2*((Lig-!(Col%2))/2)+!(Col%2));
                          yh=12+17*(2*((Lig-!(Col%2))/2)+!(Col%2));
                          h=(Lig-abs(7-Col))/2;
                          xc=h+(Col<7)*(7-Col);
                          yc=h+(Col>7)*(Col-7);
                          if ((xc>=0)&&(xc<NBXY)&&((xc!=xCrt)||(yc!=yCrt))) // v4.0 : 10 remplacé par 14
                           { // Mise en évidence d'une nouvelle case du plateau
                            EffaceSelectionCouranteCase(GARDE);
							switch(Phase)
                             {
                              case pose:         // Est-ce une case dépôt (pose) ?
                                                 // Recherche : - si la case est contiguë à une case du joueur ou
                                                 //             - si c'est une case départ
                                                 if (Tour)
                                                  {
                                                   if ((CaseDepot=(!p.c[xc][yc].Joueur)))
                                                    {
                                                     for(CaseDepot=i=0; (!CaseDepot)&&(i<NBDIR); i++)
                                                      {
                                                       xx=xc+p.dx[i]; yy=yc+p.dy[i];
                                                       CaseDepot= (xx>=0)&&
                                                                  (yy>=0)&&
                                                                  (xx<NBXY)&&
                                                                  (yy<NBXY)&&
                                                                  (xx>=p.XYMin[yy])&&
                                                                  (xx<=p.XYMax[yy])&&
                                                                  (yy>=p.XYMin[xx])&&
                                                                  (yy<=p.XYMax[xx])&&
                                                                  (p.c[xx][yy].Joueur==Jo+1);
                                                      }
                                                    }
                                                  }
                                                 else
                                                  CaseDepot=(xc==J[Jo].CoordDeb[0])&&(yc==J[Jo].CoordDeb[1]);
                                                 if (CaseDepot)
                                                  { // C'est bien ou case dépôt : on met en évidence que s'en est une
                                                   xCase=xc; yCase=yc;
                                                   DessineHexagone(xh, yh, Jo+1, CLAIR);
                                                   // 1. Case Dépot -> Curseur = LETTRE
                                                   if (Cursor!=CUR_LAP) Cursor=CUR_LAP;
                                                  }
                                                 else xCase=yCase=INDEFINI;
                                                 // 2. Nouvelle lettre possible (prioritaire) -> Curseur = +1
                                                 if (p.NouvelleLettrePossible(xc, yc))
                                                  {
                                                   if (Cursor!=CUR_PLUS_1) Cursor=CUR_PLUS_1;
                                                   StatusBar->SimpleText=stCommentChoisirLaLettreSurLePlateau;
                                                  }
                                                 else // 3. Ce n'est pas une CaseDepot -> Curseur Flèche
                                                  if (!CaseDepot)
                                                   {
													StatusBar->SimpleText=stCommentPoserLaLettreSurLePlateau;
													if (Cursor!=crArrow) Cursor=crArrow;
												   }
												 break;
							  case deplacement:  // Est-ce une case dépôt (déplacement)
												 if (!p.CalculNbCasesEnCours)
												  {
												   p.PrepareCalculNbCasesDeplacement(xc, yc);
												   if ((NbCases=p.NbCasesDeplacement(xLAD, yLAD))&&
													   (p.c[xLAD][yLAD].Valeur>=NbCases))
													{ // C'est bien ou case dépôt : on met en évidence que s'en est une
													 CaseDepot=true;
													 xCase=xc; yCase=yc;
													 DessineHexagone(xh, yh, Jo+1, CLAIR);
													 // 1. Case Dépot -> Curseur = LETTRE
													 if (Cursor!=CUR_LAD) Cursor=CUR_LAD;
													}
												   else xCase=yCase=INDEFINI;
												   p.CalculNbCasesEnCours=false;
												  }
												 else xCase=yCase=INDEFINI;
												 // 2. Nouvelle lettre possible (prioritaire) -> Curseur = +1
												 if (p.NouvelleLettrePossible(xc, yc))
												  {
												   if (Cursor!=CUR_PLUS_1) Cursor=CUR_PLUS_1;
												   StatusBar->SimpleText=stCommentChoisirLaLettreSurLePlateau;
												  }
												 else // 3. Ce n'est pas une CaseDepot -> Curseur Flèche
												  if (!CaseDepot)
												   {
													StatusBar->SimpleText=stCommentPoserLaLettreSurLePlateau;
													if (Cursor!=crArrow) Cursor=crArrow;
												   }
												 break;
                              default:           break;
							 }
							xCrt=xc; yCrt=yc;
						   }
						 }
						else
						 EffaceSelectionCouranteCase(LAISSE);
					   }
					  else
					   {
						EffaceSelectionCouranteCase(LAISSE);
						// Le curseur est en dehors de la zone du plateau : on montre la lettre à poser le cas échéant
						if (Phase==pose)
						 {
						  // Message à mettre ici (StatusBar)
						  if (Cursor!=CUR_LAP) Cursor=CUR_LAP;
						 }
					   }
					  break;
   default: break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::FormMouseUp(TObject *Sender,
	  TMouseButton Button, TShiftState Shift, int X, int Y)
{
 int NbCases;
 if (J[Jo].Automate) return;
 switch(Situation)
  {
   case choix_lettre: if ((LettreAPoser>='A')&&(LettreAPoser<='Z')&&J[Jo].Nombre[LettreAPoser-'A'+1])
					   {
						J[Jo].PrendLettre(LettreAPoser);
						Phase=pose;
						Situation=choix_case;
						break;
					   }
					  if (SELECTION_CASE)
					   {
						switch(Button)
						 {
						  case mbLeft:  if (p.LettreDeplacable(xCrt, yCrt))
										 {
										  xCase=xLAD=xCrt;
										  yCase=yLAD=yCrt;
										  Phase=deplacement;
										  Situation=choix_case;
										 }
										break;
						  case mbRight: if (p.NouvelleLettrePossible(xCrt, yCrt))
										 {
                                          p.AjouteLettre(xCrt, yCrt);
                                          xCrt=yCrt=INDEFINI;
                                         }
										break;
                          default:      break;
                         }
                        break;
                       }
   case choix_case:   switch(Button)
                       {
                        case mbLeft:  if (CHOIX_CASE)
                                       {
                                        switch(Phase)
                                         {
                                          case pose:        p.PoseLettre(xCase, yCase, LettreAPoser);
                                                            if ((!Tour)||p.ChercheMotsFormes(xCase, yCase))
                                                             {
                                                              Phase=aucune_phase;
                                                              Situation=decompte_points;
                                                              JoueurSuivant();
                                                             }
                                                            else
                                                             {
                                                              p.EnleveLettre(xCase, yCase);
                                                              xCrt=xCase=yCrt=yCase=INDEFINI;
                                                              J[Jo].AfficheLettresDisp();
                                                             }
                                                            break;
                                          case deplacement: if (!p.CalculNbCasesEnCours)
                                                             {
                                                              p.PrepareCalculNbCasesDeplacement(xCase, yCase);
                                                              if ((NbCases=p.NbCasesDeplacement(xLAD, yLAD))&&
                                                                  (p.c[xLAD][yLAD].Valeur>=NbCases)&&
                                                                   p.FormeMotsApresDeplacement(xLAD, yLAD, xCase, yCase))
                                                               {
                                                                p.CalculNbCasesEnCours=false;
                                                                p.DeplaceLettre(xLAD, yLAD, xCase, yCase, NbCases);
                                                                p.ChercheMotsFormes(xCase, yCase);
                                                                Phase=aucune_phase;
                                                                Situation=decompte_points;
                                                                JoueurSuivant();
                                                               }
                                                              else
                                                               p.CalculNbCasesEnCours=false;
                                                             }
															break;
                                          default:          break;
                                         }
                                       }
                                      break;
                        case mbRight: if (SELECTION_CASE&&p.NouvelleLettrePossible(xCrt, yCrt))
                                       { // Si lettre ajoutable (curseur +1) : on effectue l'opération (prioritaire)
                                        p.AjouteLettre(xCrt, yCrt);
                                        if ((xLAD==xCrt)&&
                                            (yLAD==yCrt)&&
                                            (Phase==deplacement))
                                         { // On annule le déplacement si c'est la lettre ajoutable qui devait être déplacé
                                          p.AfficheCase(xCrt, yCrt, clBlack);
                                          Phase=aucune_phase;
                                          Situation=choix_lettre;
                                         }
                                        xCrt=yCrt=INDEFINI;
                                        break;
                                       }
                                      else
                                       { // Annulation de la pose ou du déplacement
                                        switch(Phase)
                                         {
                                          case pose:        if ((xCrt!=INDEFINI)&&(yCrt!=INDEFINI))
                                                             p.AfficheCase(xCrt, yCrt, clBlack);
                                                            J[Jo].RemetLettre(LettreAPoser);
                                                            Phase=aucune_phase;
                                                            Situation=choix_lettre;
                                                            break;
                                          case deplacement: if ((xCrt!=INDEFINI)&&(yCrt!=INDEFINI))
                                                             p.AfficheCase(xCrt, yCrt, clBlack);
                                                            Phase=aucune_phase;
                                                            Situation=choix_lettre;
                                                            break;
                                          default:          break;
                                         }
                                       }
                                      break;
                        default: break;
                       }
                      break;
   default : break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriquePasserSonTourClick(TObject *Sender)
{
 if ((!Tour)||(J[Jo].Automate)) return;
 LettreAPoser=LettreADeplacer=0;
 p.NbPasseTour++;
 JoueurSuivant();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueNouvelleClick(TObject *Sender)
{
 int mrRep;
 randomize();
 if ((frmNomJoueurs=new TfrmNomJoueurs(this)))
  {
   mrRep=frmNomJoueurs->ShowModal();
   frmNomJoueurs->Release();
   frmNomJoueurs=NULL;
  }
 else Close();
 if (mrRep!=mrOk) return;
 InitialisePartie(SANS_JOUEURS);
 frmPlateau->RubriquePasserSonTour->Enabled=(!J[Jo].Automate);
 frmMessages->AjouteMessage(Format(stFrmTour, ARRAYOFCONST(((int)Tour))), RIEN_EFFACER);
 frmMessages->AjouteMessage(stRien, RIEN_EFFACER);
 frmMessages->AjouteMessage(Format(stFrmJoueur, ARRAYOFCONST((stCouleur[Jo], J[Jo].stNom))), RIEN_EFFACER);
 p.DepartChrono();
 Phase=aucune_phase;
 Situation=choix_lettre;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueContinuerClick(TObject *Sender)
{
 Caption=stTitre;
 p.DepartChrono();
 Phase=aucune_phase;
 Situation=choix_lettre;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueOuvrirClick(TObject *Sender)
{
 if (OpenDialog->Execute())
  {
   if (Chargement(OpenDialog->FileName))
	{
	 frmMessages->ChargeMessages(OpenDialog->FileName+".txt");
	 frmPlateau->RubriquePasserSonTour->Enabled=(!J[Jo].Automate);
	 p.JeuEnCours=false;
	 p.AffichePlateau();
	 J[Jo].AfficheLettresDisp();
	 frmScores->MajScores();
	}
   else Close();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueEnregistrerClick(TObject *Sender)
{
 if (SaveDialog->FileName.IsEmpty())
  RubriqueEnregistrerSous->Click();
 else
  {
   Sauvegarde(SaveDialog->FileName.c_str());
   if (EnregistrerMessages)
    frmMessages->SauveMessages(SaveDialog->FileName+".txt");
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueEnregistrerSousClick(TObject *Sender)
{
 if (SaveDialog->Execute())
  RubriqueEnregistrer->Click();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::FormCreate(TObject *Sender)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::FormShow(TObject *Sender)
{
 int n;
 EnregistrerMessages=(frmParametresAutomates->IniFile->ReadString(stSectionPartie, stEntreeEnregistrerMessages, stBool[true])==stBool[true]);
 RubriqueEnregistrerMessages->Checked=EnregistrerMessages;
 if (!ParamStr(1).IsEmpty())
  {
   if (Chargement(ParamStr(1)))
    {
     frmMessages->ChargeMessages(ParamStr(1)+".txt");
     frmPlateau->RubriquePasserSonTour->Enabled=(!J[Jo].Automate);
     p.JeuEnCours=false;
     p.AffichePlateau();
     J[Jo].AfficheLettresDisp();
     frmScores->MajScores();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueJoueursClick(TObject *Sender)
{
 if ((frmNomJoueurs=new TfrmNomJoueurs(this)))
  {
   frmNomJoueurs->NouvellePartie=false;
   frmNomJoueurs->NbJoueursModifiable=false;
   frmNomJoueurs->ShowModal();
   frmNomJoueurs->Release();
   frmNomJoueurs=NULL;
  }
 else Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueAProposClick(TObject *Sender)
{
 if ((frmAPropos=new TfrmAPropos(this)))
  {
   frmAPropos->ShowModal();
   frmAPropos->Release();
   frmAPropos=NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueEnregistrerMessagesClick(
      TObject *Sender)
{
 RubriqueEnregistrerMessages->Checked^=true;
 EnregistrerMessages=RubriqueEnregistrerMessages->Checked;
 frmParametresAutomates->IniFile->WriteString(stSectionPartie, stEntreeEnregistrerMessages, stBool[EnregistrerMessages]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueQuitterClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueAutomatesClick(TObject *Sender)
{
 frmParametresAutomates->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::TimerTimer(TObject *Sender)
{
 int k;
 Timer->Enabled=false;
 while((k=random(100))>=50) k=random(100);
 RubriqueContinuer->Click();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueInterrompreClick(TObject *Sender)
{
 Caption=stTitrePause;
 Timer->Enabled=false;
 RubriqueInterrompre->Enabled=false;
 StatusBar->SimpleText=stContinuer;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueAideClick(TObject *Sender)
{
 ShellExecute(NULL,
			  L"Open",
			  L"osmoz.html",
			  NULL,
			  String(ExtractFilePath(Application->ExeName)+"html").c_str(),
			  SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::MenuPartieClick(TObject *Sender)
{
 if (Timer->Enabled)
  {
   RubriqueInterrompre->Enabled=true;
   RubriqueInterrompre->Click();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::MenuOptionsClick(TObject *Sender)
{
 if (Timer->Enabled)
  {
   RubriqueInterrompre->Enabled=true;
   RubriqueInterrompre->Click();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueRecordsClick(TObject *Sender)
{
 frmRecords->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::FormDestroy(TObject *Sender)
{
 for(int i=0; i<NBCURSEURS; i++)
   DestroyCursor(crSmz[i]);
}
//---------------------------------------------------------------------------

