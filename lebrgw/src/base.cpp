//---------------------------------------------------------------------------
#include <stdlib.h>
#include <time.h>
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "plt_f.h"
#include "score_f.h"
#include "records_f.h"
#include "prt_f.h"
#include "nomjou_f.h"
#include "diplome_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const int dx[NBDIR]={0, 0, 1, 0, -1},
		  dy[NBDIR]={0, -1, 0, 1, 0};
//---------------------------------------------------------------------------
const direction InvDir[NBDIR]={indefinie,sud,ouest,nord,est};
//---------------------------------------------------------------------------
niveau *Niv=NULL;
//---------------------------------------------------------------------------
// v1.7 : Pour les fichiers créés par Le Berger (leberger.ini)
//        on utilise le chemin donné par %LocalAppData% pour Windows 7 ou plus
//        sinon le dossier de l'exécutable
//---------------------------------------------------------------------------
String stRepLocalAppData()
 {
   String stResult;
   String stExePath = ExtractFilePath(ParamStr(0));
   const String stVarLocalAppData  = "LOCALAPPDATA";
   const String stVarUserProfile  = "USERPROFILE";
   const String stRepLocAppDataLebrg = "\\Patquoi.fr\\Le Berger\\";
   stResult = GetEnvironmentVariable(stVarLocalAppData);
   if (stResult == "")
	{ // Windows 7~10
	 stResult = GetEnvironmentVariable(stVarUserProfile);
	 if (stResult == "")
	   stResult = stExePath;
	 else
	  { // Windows XP
	   stResult = stResult + "\\Local Settings\\Application Data" + stRepLocAppDataLebrg;
	   if (!DirectoryExists(stResult))
		 if (!ForceDirectories(stResult))
		   stResult = stExePath;
	  }
	}
   else
	{ // Autres
	 stResult = stResult + stRepLocAppDataLebrg;
	 if (!DirectoryExists(stResult))
	   if (!ForceDirectories(stResult))
		 stResult = stExePath;
	}
   return stResult;
 }
//---------------------------------------------------------------------------
// Méthodes de classes
//---------------------------------------------------------------------------
void porte_en_mvt::Retire(int xp, int yp)
 {
  porte_en_mvt *SvtSvg;
  if (!Svt) return;
  if ((Svt->x==xp)&&(Svt->y==yp))
   {
    SvtSvg=Svt->Svt;
    Svt->Svt=NULL;
    delete Svt;
    Svt=SvtSvg;
   }
  else Svt->Retire(xp, yp);
 }

void niveau::Initialise()
 {
  int i;
  TpsRestant=Temps; x=x0; y=y0; NbBetesCoincees=0;
  if (PorteEnMvt) delete PorteEnMvt;
  PorteEnMvt=NULL;
  for(i=0; i<NBDIR; i++) DmdDeclPorte[i]=false;
  Lance=true;
 }

bool niveau::CreeBetes(int n)
 {
  bool Ok;
  int i;
  if ((Ok=((Bete=new bete[NbBetes=n]))))
   for(i=0; i<n; i++)
    Bete[i].Initialise(i);
  return Ok;
 }

bete *niveau::AjouteBete(int x, int y, direction d)
 {
  int i;
  for(i=0; (i<NbBetes)&&Bete[i].EstDefinie(); i++);
  if (i<NbBetes)
   {
    Bete[i].Definit(x, y, d);
    NbCrtBetes++;
    return Bete+i;
   }
  else return NULL;
 }

void niveau::RetireBete(int n)
 {
  int x, y;
  if (((x=Bete[n].x)>INDEFINI)&&
      ((y=Bete[n].y)>INDEFINI)&&
      (c[x][y].Bete))
   {
    c[x][y].Bete=NULL;
    Bete[n].Retire();
    NbCrtBetes--;
   }
 }

int niveau::NumImage(int x, int y, int Affichage)
 { // Ne pas oublier : Code en fonction de la dizaine du round et des alentours
  bete *BeteCrt=c[x][y].Bete;
  bool ExisteBete=!!BeteCrt;
  int NumImageBete=I_BETE;
  if (ExisteBete)
   NumImageBete=NumIconeBete[BeteCrt->Dir][BeteCrt->Decalage][BeteCrt->ArriveEn(x,y)];
  switch(c[x][y].Type)
   {
    case rien: return ExisteBete?
                      ((Affichage&AFF_BETES)?NumImageBete:I_CHEMIN):
                      I_CHEMIN;
    case mur:  return I_MUR+  (!EstUnMur(x, y, nord, SANS_BORD))+
                            2*(!EstUnMur(x, y, est, SANS_BORD))+
                            4*(!EstUnMur(x, y, sud, SANS_BORD))+
                            8*(!EstUnMur(x, y, ouest, SANS_BORD));
    case porte: if (!c[x][y].PosPorte) // ouvert
                 return ExisteBete?
                        ((Affichage&AFF_BETES)?
                         NumImageBete:
                         ((Affichage&AFF_PORTES)?I_PORTEO:I_CHEMIN)):
                        ((Affichage&AFF_PORTES)?I_PORTEO:I_CHEMIN);
                else // Au moins presque ouvert
                 {
                  if (!(Affichage&AFF_PORTES)) return I_CHEMIN;
                  if ((EstUnMur(x, y, nord, AVEC_BORDS))&&
                      (EstUnMur(x, y, sud, AVEC_BORDS))) return I_PORTEV+c[x][y].PosPorte;
                  if ((EstUnMur(x, y, est, AVEC_BORDS))&&
                      (EstUnMur(x, y, ouest, AVEC_BORDS))) return I_PORTEH+c[x][y].PosPorte;
                  return I_CHEMIN; // Anomalie
                 }
    case decl_b: return ExisteBete?
                        ((Affichage&AFF_BETES)?
                         NumImageBete:
                         ((Affichage&AFF_DECL)?I_DECLB:I_CHEMIN)):
                        ((Affichage&AFF_DECL)?I_DECLB:I_CHEMIN);
    case decl_r: return ExisteBete?
                        ((Affichage&AFF_BETES)?
                         NumImageBete:
                         ((Affichage&AFF_DECL)?I_DECLR:I_CHEMIN)):
                        ((Affichage&AFF_DECL)?I_DECLR:I_CHEMIN);
    default: return I_CHEMIN;
   }
 };

bool niveau::EstLiberable(int x, int y)
{
 switch(c[x][y].Type)
  {
   case rien: return true;
   case mur:  if ((EstUnePorte(x,y,nord)&&EstUnMur(x+dx[nord],y+dy[nord],nord,AVEC_BORDS))||
				  (EstUnePorte(x,y,est)&&EstUnMur(x+dx[est],y+dy[est],est,AVEC_BORDS))||
				  (EstUnePorte(x,y,sud)&&EstUnMur(x+dx[sud],y+dy[sud],sud,AVEC_BORDS))||
				  (EstUnePorte(x,y,ouest)&&EstUnMur(x+dx[ouest],y+dy[ouest],ouest,AVEC_BORDS)))
			   {
				frmPlateau->AfficheMessage("Vous ne pouvez pas retirer un mur à côté d'une porte.", MB_ICONEXCLAMATION);
				return false;
			   }
			  break;
   case porte:if (EstUnDeclIsole(x,y,nord)||
				  EstUnDeclIsole(x,y,est)||
				  EstUnDeclIsole(x,y,sud)||
				  EstUnDeclIsole(x,y,ouest))
				 {
				  frmPlateau->AfficheMessage("Vous ne pouvez pas retirer une porte à côté d'un déclencheur isolé.", MB_ICONEXCLAMATION);
				  return false;
				 }
			  break;
   default:   break;
  }
 return true;
}

bool niveau::EstUnMur(int x, int y, direction d, bool Bordure)
 {
  switch(d)
   {
    case nord:  return (!y)?Bordure:EST_DE_TYPE(x,y,d,mur);
    case est:   return (x==NBX-1)?Bordure:EST_DE_TYPE(x,y,d,mur);
    case sud:   return (y==NBY-1)?Bordure:EST_DE_TYPE(x,y,d,mur);
    case ouest: return (!x)?Bordure:EST_DE_TYPE(x,y,d,mur);
    default:    return false;
   }
 }

bool niveau::EstUnePorte(int x, int y, direction d)
 {
  switch(d)
   {
    case nord:  return (y&&EST_DE_TYPE(x,y,d,porte));
    case est:   return ((x<NBX-1)&&EST_DE_TYPE(x,y,d,porte));
    case sud:   return ((y<NBY-1)&&EST_DE_TYPE(x,y,d,porte));
    case ouest: return (x&&EST_DE_TYPE(x,y,d,porte));
    default:    return false;
   }
 }

bool niveau::EstUnDeclIsole(int x, int y, direction d)
 {
  int dd,
      xx=x+dx[d],
      yy=y+dy[d];
  bool Isole=true;
  switch(d)
   {
    case nord:  if (y&&EST_UN_DECL(x,y,d))
                 {
                  for(dd=nord; Isole&&(dd<=ouest); dd++)
                   if ((xx+dx[dd]!=x)||(yy+dy[dd]!=y)) switch(dd)
                    {
                     case nord: Isole=(!yy)||(C(xx,yy,dd).Type!=porte); break;
                     case est:  Isole=(xx==NBX-1)||(C(xx,yy,dd).Type!=porte); break;
                     case sud:  Isole=(yy==NBY-1)||(C(xx,yy,dd).Type!=porte); break;
                     case ouest:Isole=(!xx)||(C(xx,yy,dd).Type!=porte); break;
                    }
                  return Isole;
                 }
                else return false;
    case est:   if ((x<NBX-1)&&EST_UN_DECL(x,y,d))
                 {
                  for(dd=nord; Isole&&(dd<=ouest); dd++)
                   if ((xx+dx[dd]!=x)||(yy+dy[dd]!=y)) switch(dd)
                    {
                     case nord: Isole=(!yy)||(C(xx,yy,dd).Type!=porte); break;
                     case est:  Isole=(xx==NBX-1)||(C(xx,yy,dd).Type!=porte); break;
                     case sud:  Isole=(yy==NBY-1)||(C(xx,yy,dd).Type!=porte); break;
                     case ouest:Isole=(!xx)||(C(xx,yy,dd).Type!=porte); break;
                    }
                  return Isole;
                 }
                else return false;
    case sud:   if ((y<NBY-1)&&EST_UN_DECL(x,y,d))
                 {
                  for(dd=nord; Isole&&(dd<=ouest); dd++)
                   if ((xx+dx[dd]!=x)||(yy+dy[dd]!=y)) switch(dd)
                    {
                     case nord: Isole=(!yy)||(C(xx,yy,dd).Type!=porte); break;
                     case est:  Isole=(xx==NBX-1)||(C(xx,yy,dd).Type!=porte); break;
                     case sud:  Isole=(yy==NBY-1)||(C(xx,yy,dd).Type!=porte); break;
                     case ouest:Isole=(!xx)||(C(xx,yy,dd).Type!=porte); break;
                    }
                  return Isole;
                 }
                else return false;
    case ouest: if (x&&EST_UN_DECL(x,y,d))
                 {
                  for(dd=nord; Isole&&(dd<=ouest); dd++)
                   if ((xx+dx[dd]!=x)||(yy+dy[dd]!=y)) switch(dd)
                    {
                     case nord: Isole=(!yy)||(C(xx,yy,dd).Type!=porte); break;
                     case est:  Isole=(xx==NBX-1)||(C(xx,yy,dd).Type!=porte); break;
                     case sud:  Isole=(yy==NBY-1)||(C(xx,yy,dd).Type!=porte); break;
                     case ouest:Isole=(!xx)||(C(xx,yy,dd).Type!=porte); break;
                    }
                  return Isole;
                 }
                else return false;
    default:    return false;
   }
 }

bool niveau::EstUnePorteIsolee(int x, int y)
 {
  int d;
  if (c[x][y].Type!=porte) return false;
  for(d=nord; (d<=ouest)&&(C(x,y,d).Type<decl_b); d++);
  return (d>ouest);
 }

void niveau::ActionnePorte(int x, int y)
 {
  if ((c[x][y].Type==porte)&&(c[x][y].SensPorte))
   {
    c[x][y].SensPorte=(sens_porte)(-c[x][y].SensPorte);
    AjoutePorteEnMvt(x, y);
   }
 }

void niveau::ActionneDeclencheur(int x, int y)
 {
  int d;
  if (c[x][y].Type==decl_r) c[x][y].Type=rien;
  for(d=nord; d<=ouest; d++)
   ActionnePorte(x+dx[d], y+dy[d]);
 }

void niveau::AjoutePorteEnMvt(int xp, int yp) // Ne fait rien si la porte est déjà dans la liste
 {
  if (PorteEnMvt)
   PorteEnMvt->Ajoute(xp, yp);
  else
   PorteEnMvt=new porte_en_mvt(xp, yp);
 }

void niveau::RetirePorteEnMvt(int xp, int yp)
 {
  porte_en_mvt *SvtSvg;
  if (!PorteEnMvt) return;
  if ((xp==PorteEnMvt->x)&&(yp==PorteEnMvt->y))
   { // C'est le premier de la liste
    if (!PorteEnMvt->Svt)
     { // ET c'est le seul...
      delete PorteEnMvt; // ALORS liste vide...
      PorteEnMvt=NULL;
     }
    else
     {  // Sinon...
      SvtSvg=PorteEnMvt->Svt; // On récupère le suivant
      PorteEnMvt->Svt=NULL; // On isole le premier
      delete PorteEnMvt; // Que l'on efface
      PorteEnMvt=SvtSvg; // Mais on repart du deuxième
     }
   }
  else // C'est pas le premier alors on le demande au premier de le chercher...
   PorteEnMvt->Retire(xp, yp);
 }

void niveau::DeclenchePorteADistance(direction d)
 {
  int dd, xx, yy;
  bool Trv=false;
  if (!d) return;
  for(dd=1; (!Trv)&&((xx=x+dd*dx[d])>=0)&&(xx<NBX)&&((yy=y+dd*dy[d])>=0)&&(yy<NBY)&&((c[xx][yy].Type==porte)||c[xx][yy].EstFranchissable()); dd++)
   if (EstUnePorteIsolee(xx, yy)) // Si porte sans déclencheur aux alentours
    {
     ActionnePorte(xx, yy); // ALORS On l'actionne
     Trv=true;
    }
   else
    Trv=(c[xx][yy].Type==porte)||(!c[xx][yy].EstFranchissable()); // On s'arrête là si porte ou case infranchissable
 }

void niveau::TraiteBerger()
 {
  int d;
  // On traite les demandes de déclenchement de portes à distance
  for(d=nord; d<=ouest; d++)
   if (DmdDeclPorte[d])
    {
     DmdDeclPorte[d]=false;
     DeclenchePorteADistance((direction)d);
    }
 }
void niveau::TraiteBetes()
 {
  int i, d, dd, Nb1er, Nb2eme, NbChxPoss,
      Ordre[NBDIR], Heur[NBDIR],
      xb, yb,
      xxb, yyb,
      dxbc, dybc; // Distances en abscisses et ordonnées Bête/Curseur
  direction DirCrt, DirChoisie, ChxDir[NBDIR];

  bete *BeteCrt;
  // On réinitialise le compteur de bêtes coincées
  NbBetesCoincees=0;
  for(i=0; i<NbBetes; i++)
   if (Bete[i].EstDefinie())
    {
     BeteCrt=&(Bete[i]);
     xb=BeteCrt->x; yb=BeteCrt->y;
     DirChoisie=DirCrt=BeteCrt->Dir;
     if (!BeteCrt->Decalage) // Pas de décalage = Direction à lui faire prendre
      {
       NbChxPoss=0;
       // 1. Calcul de l'heuristique de choix
       for(d=0; d<NBDIR; d++)
        {
         Ordre[d]=1; ChxDir[d]=indefinie;
         dxbc=abs(x-xb); dybc=abs(y-yb);
         switch(d)
          {
           case indefinie: Heur[d]=0; break;
           case nord:      Heur[d]=(yb&& // Pas en bordure ET
                                    SANS_CURSEUR(xb,yb,d)&& // pas de curseur ET
                                    (C(xb,yb,d).EstFranchissable()))* // Case franchissable ALORS
                                    ((dybc>dxbc)?(1+3*(abs(y-yb-dy[d])<dybc)):(2+(abs(y-yb-dy[d])<dybc)));
                           break;
           case est:       Heur[d]=((xb<NBX-1)&& // Pas en bordure ET
                                    SANS_CURSEUR(xb,yb,d)&& // pas de curseur ET
                                    (C(xb,yb,d).EstFranchissable()))* // Case franchissable ALORS
                                    ((dxbc>dybc)?(1+3*(abs(x-xb-dx[d])<dxbc)):(2+(abs(x-xb-dx[d])<dxbc)));
                           break;         
           case sud:       Heur[d]=((yb<NBY-1)&& // Pas en bordure ET
                                    SANS_CURSEUR(xb,yb,d)&& // pas de curseur ET
                                    (C(xb,yb,d).EstFranchissable()))* // Case franchissable ALORS
                                    ((dybc>dxbc)?(1+3*(abs(y-yb-dy[d])<dybc)):(2+(abs(y-yb-dy[d])<dybc)));
                           break;
           case ouest:     Heur[d]=(xb&& // Pas en bordure ET
                                    SANS_CURSEUR(xb,yb,d)&& // pas de curseur ET
                                    (C(xb,yb,d).EstFranchissable()))* // Case franchissable ALORS
                                    ((dxbc>dybc)?(1+3*(abs(x-xb-dx[d])<dxbc)):(2+(abs(x-xb-dx[d])<dxbc)));
                           break;
          }
         NbChxPoss+=(Heur[d]>0);
        }
       // On interdit le demi-tour si plus d'un choix possible
       if (NbChxPoss>1) Heur[InvDir[DirCrt]]=0;

       // 2. Classement
       for(d=0; d<NBDIR; d++)
        for(dd=0; dd<NBDIR; dd++)
         if (Heur[d]<Heur[dd]) Ordre[d]++;

       // 3. On évalue les cas en tête ainsi que leur nombre (Nb1er);
       for(Nb1er=d=0; d<NBDIR; d++) if (Ordre[d]==1) ChxDir[Nb1er++]=(direction)d;

       // 4. On décide duquel en fonction du nombre (Nb1er) et si on prend le meilleur choix
       if (random(Effet+1)<=5*NbBetesAFaire)
        DirChoisie=ChxDir[random(Nb1er)]; // 4.1. Meilleur choix
       else // Cas où l'effet du curseur est défaillant (deuxièmes choix)
        {
         // 4.2. On évalue les cas en deuxième ainsi que leur nombre (Nb2eme);
         for(Nb2eme=d=0; d<NBDIR; d++) if (Ordre[d]==Nb1er+1) ChxDir[Nb2eme++]=(direction)d;
         DirChoisie=ChxDir[random(Nb2eme)]; // 4.1. Meilleur choix
        }
       // 5. On regarde le score pour savoir si la bete est coincée
       if (Heur[DirChoisie]) // Elle peut se déplacer, alors on la déplace
        {
         BeteCrt->Dir=DirChoisie;
         BeteCrt->Decalage=1;
         C(xb,yb,DirChoisie).Bete=BeteCrt;

         // 6. Test d'un éventuel déclencheur
         if (C(xb,yb,DirChoisie).Type>porte)
          ActionneDeclencheur(xb+dx[DirChoisie],yb+dy[DirChoisie]);

         frmPlateau->RedessineCase(xb,yb, false);
         frmPlateau->RedessineCase(xb+dx[DirChoisie],yb+dy[DirChoisie], false);
        }
       else
        NbBetesCoincees++; // Une bête coincée de +
      }
     else // Bete entre deux cases : on poursuit
      {
       if (!(BeteCrt->Decalage=(BeteCrt->Decalage+1)%NBDECAL))
        { // Case visée atteinte entièrement
         BeteCrt->Deplace();
         c[xb][yb].Bete=NULL;
         frmPlateau->RedessineCase(xb,yb, false);
         frmPlateau->RedessineCase(xxb=BeteCrt->x,yyb=BeteCrt->y, false);

         // 7. On regarde si le curseur touche la bete
         if ((xxb-x)*(xxb-x)+(yyb-y)*(yyb-y)==1)
          Effet-=1+((xxb+dx[DirChoisie]==x)&(yyb+dy[DirChoisie]==y));
         if (Effet<Effet0) Effet=Effet0;
        }
       else
        {
         frmPlateau->RedessineCase(xb,yb, false);
         frmPlateau->RedessineCase(xb+dx[DirChoisie],yb+dy[DirChoisie], false);
        }
      }
    }
 }

void niveau::TraitePortes()
 {
  porte_en_mvt *PorteCrt=PorteEnMvt, *PorteSvt;
  int xp, yp;
  while(PorteCrt)
   {
    PorteSvt=PorteCrt->Svt; // On prend tout de suite le suivant au cas où on retire la porte
    xp=PorteCrt->x;
    yp=PorteCrt->y;

    // 1. Mouvement de porte si non bloquée (bete ou curseur)
    if (c[xp][yp].PosPorte||
        (((xp!=x)||(yp!=y))&&
         (!c[xp][yp].Bete)))
     {
      switch(c[xp][yp].PosPorte+c[xp][yp].SensPorte)
       {
        case ouverte:
        case p_ouverte:
        case entrouverte:
        case p_fermee:
        case fermee: c[xp][yp].PosPorte=(pos_porte)(c[xp][yp].PosPorte+c[xp][yp].SensPorte); break;
        default : break;
       }
      // Si porte ouverte ou fermée alors retirée des portes en mvt
      if (((c[xp][yp].PosPorte==ouverte)&&(c[xp][yp].SensPorte==ferme_ouvert))||
          ((c[xp][yp].PosPorte==fermee)&&(c[xp][yp].SensPorte==ouvert_ferme)))
       RetirePorteEnMvt(xp, yp);
      frmPlateau->RedessineCase(xp, yp, false);
     }
    PorteCrt=PorteSvt; // Au suivant !
   }
 }

void __fastcall niveau::JoueTour()
 {
  String stMsgFinDeJeu="",
		 stAncNomFichier;
  bool BarreAtteinte=false;
  int PosNumNiv;
  TourEnCours=true;
  TraiteBerger(); // On teste les demandes de déclenchement de porte (à distance ou par déclencheur)
  TraiteBetes(); // On fait avancer les betes et on agit en conséquent
  TraitePortes(); // On fait réagir les éléments en fonction de leur situation
  TpsRestant--;
  frmPlateau->RafraichitParametres(aff_tout);
  if (EstTermine())
   {
    frmPlateau->JeuEnCours=false;
    Niv->Lance=false;
    switch(frmPlateau->Mode)
     {
      case jeu:     frmPlateau->RubriqueInterrompre->Enabled=false;
                    break;
      case editeur: frmPlateau->RubriqueInterrompreNiveau->Enabled=false;
					break;
      default:      break;
     }
	stMsgFinDeJeu=   String(((Effet==Effet0)&&(Effet0<5*NbBetesAFaire))?
							 "Votre curseur n'a plus d'effet !":
							 ((!TpsRestant)?
                              "Votre temps imparti est écoulé !":
                              "Vous avez immobilisé toutes vos bêtes !"));
	if ((frmScore=new TfrmScore(frmPlateau)))
     {
      frmScore->StatusBar->SimpleText="Fin de niveau : "+stMsgFinDeJeu;
      frmScore->ShowModal();
      BarreAtteinte=frmScore->LabelBarreAtteinte->Visible;
      delete frmScore;
      frmScore=NULL;
     }
	if ((frmRecords=new TfrmRecords(frmPlateau)))
     {
      frmRecords->TesterNvEntree=true;
      frmRecords->RadioGroupTypeRecord->ItemIndex=TR_NIVEAU;
      frmRecords->ShowModal();
      delete frmRecords;
      frmRecords=NULL;
     }
    if ((frmPlateau->Mode==jeu)&&
        (frmRecords=new TfrmRecords(frmPlateau)))
     {
      frmRecords->TesterNvEntree=true;
      frmRecords->RadioGroupTypeRecord->ItemIndex=TR_PARTIE;
      frmRecords->ShowModal();
      delete frmRecords;
      frmRecords=NULL;
     }
    if (frmPlateau->Mode==editeur)
     {
      frmPlateau->RubriqueEditeur->Enabled=true;
      frmPlateau->RubriqueJeu->Enabled=true;
      frmPlateau->RubriqueChangerSerie->Enabled=true;
	  frmPlateau->RubriqueTesterNiveau->Caption=stTesterNiveau;
	  frmPlateau->Caption=stTitre[1];
	  frmPlateau->ChargeAutomatiquement();
	 }
	else
	 if (!BarreAtteinte)
	  {
	   frmPlateau->PartieEnCours=false;
	   frmParties->SupprimePartiesPrecedentes();
	   frmPlateau->RubriqueNouvelle->Caption=stNouvelle;
	   frmPlateau->RubriqueOuvrir->Enabled=true;
	   frmPlateau->RubriqueChangerSerie->Enabled=true;
	   frmPlateau->RubriqueInterrompre->Enabled=false;
	   frmPlateau->RubriqueJeu->Enabled=true;
	   frmPlateau->RubriqueEditeur->Enabled=true;
	   frmPlateau->RafraichitTitre(false);
	   frmPlateau->ChargePremierNiveau();
	  }
	 else
	  {
	   if (frmPlateau->stNomJoueur.IsEmpty()) frmNomJoueur->ShowModal();
	   frmParties->EnregistrePartie();
	   stAncNomFichier=frmPlateau->stNomFichierNiveau;
	   PosNumNiv=frmPlateau->stNomFichierNiveau.Pos(Format("%3.3d", ARRAYOFCONST((Niv->Num))));
	   frmPlateau->stNomFichierNiveau=frmPlateau->stNomFichierNiveau.SubString(1, PosNumNiv-2)+Format(".%3.3d.", ARRAYOFCONST((Niv->Num+1)))+stExtNLB;
	   if ((Niv->Num==999)||(!PosNumNiv)||(!FileExists(frmPlateau->stNomFichierNiveau)))
		{
		 frmPlateau->PartieEnCours=false;
		 frmParties->SupprimePartiesPrecedentes();
		 frmPlateau->stNomFichierNiveau=stAncNomFichier;
		 TourEnCours=false;
		 frmPlateau->AfficheMessage("Il n'y a plus de niveau !\nVous avez réussi la série !\nVous méritez un DIPLÔME de BERGER !\nUtilisez [Ctrl+I] pour imprimer, [Entrée] pour fermer.\n\nATTENTION : L'impression ne fonctionne qu'en 256 couleurs maximum uniquement.\nVeuillez changer le nombre de couleurs dans les propriétés d'affichage avant d'imprimer.", MB_ICONEXCLAMATION);

		 if ((frmDiplome=new TfrmDiplome(Application)))
		  {
		   frmDiplome->ShowModal();
		   delete frmDiplome;
		   frmDiplome=NULL;
		  }
		 frmPlateau->RubriqueNouvelle->Caption=stNouvelle;
		 frmPlateau->RubriqueOuvrir->Enabled=true;
		 frmPlateau->RubriqueChangerSerie->Enabled=true;
		 frmPlateau->RubriqueInterrompre->Enabled=false;
		 frmPlateau->RubriqueJeu->Enabled=true;
		 frmPlateau->RubriqueEditeur->Enabled=true;
		 frmPlateau->RafraichitTitre(false);
		 frmPlateau->ChargePremierNiveau();
		 return;
		}
	   frmPlateau->ChargeAutomatiquement();
	   if (frmPlateau->Mode==jeu) frmPlateau->RubriqueInterrompre->Enabled=true;
	  }
   }
  TourEnCours=false;
 }

bool niveau::Charge(int hfile)
 {
  int i, j, NumBete;
  bool Ok;
  Ok=(READ(Num)>0)&&
     (READ(NbBetes)>0)&&
     (READ(NbCrtBetes)>0);
  if (Ok)
   {
    if (Bete) delete[] Bete;
	if ((Ok=CreeBetes(NbBetes)))
	 for(i=0; Ok&&(i<NbCrtBetes); i++)
	  if ((Ok=(READ(NumBete)>0)))
	   Ok=Bete[NumBete].Charge(hfile);
   }
  if (Ok)
   for(i=0; Ok&&(i<NBX); i++)
    for(j=0; Ok&&(j<NBY); j++)
     Ok=c[i][j].Charge(hfile, this);
  if (Ok)
   Ok=(READ(NbBetesAFaire)>0)&&
      (READ(Barre)>0)&&
      (READ(Delai)>0)&&
      (READ(Temps)>0)&&
      (READ(x0)>0)&&
      (READ(y0)>0)&&
      (READ(Effet0)>0);
  if (Ok)
   {
    NbBetesCoincees=0;
    TpsRestant=Temps;
    Effet=5*NbBetesAFaire;
   }

  return Ok;
 }

bool niveau::Sauve(int hfile)
 {
  int i, j, NumBete;
  bool Ok;
  Ok=(WRITE(Num)>0)&&
     (WRITE(NbBetes)>0)&&
     (WRITE(NbCrtBetes)>0);
  if (Ok)
   for(NumBete=0; Ok&&(NumBete<NbBetes); NumBete++)
    if (Bete[NumBete].EstDefinie())
     Ok=(WRITE(NumBete)>0)&&
        Bete[NumBete].Sauve(hfile);
  if (Ok)
   for(i=0; Ok&&(i<NBX); i++)
    for(j=0; Ok&&(j<NBY); j++)
     Ok=c[i][j].Sauve(hfile);
  if (Ok)
   Ok=(WRITE(NbBetesAFaire)>0)&&
      (WRITE(Barre)>0)&&
      (WRITE(Delai)>0)&&
      (WRITE(Temps)>0)&&
      (WRITE(x0)>0)&&
      (WRITE(y0)>0)&&
      (WRITE(Effet0)>0);
  return Ok;
 }

bool case_p::EstFranchissable()
 {
  return (Type!=mur)&&
         ((Type!=porte)||
          ((PosPorte==ouverte)&&
           (SensPorte<ouvert_ferme)))&&
         (!Bete);
 }

bool case_p::Charge(int hfile, niveau *NivCrt)
 {
  bool Ok;
  int NumBete;
  if ((Ok=READ(Type)&&
		 READ(PosPorte)&&
         READ(NumBete)))
   {
    if (NumBete>INDEFINI) Bete=&(NivCrt->Bete[NumBete]);
    SensPorte=(Type==porte)?((PosPorte==ouverte)?ferme_ouvert:ouvert_ferme):aucun;
   }
  return Ok;
 }

bool case_p::Sauve(int hfile)
 {
  int NumBete=(Bete)?Bete->Num:INDEFINI;
  return WRITE(Type)&&
         WRITE(PosPorte)&&
         WRITE(NumBete);
 }

void bete::Deplace()
 {
  x+=dx[Dir];
  y+=dy[Dir];
 }

bool bete::Charge(int hfile)
 {
  return READ(x)&&READ(y)&&READ(Dir);
 }

bool bete::Sauve(int hfile)
 {
  return WRITE(x)&&WRITE(y)&&WRITE(Dir);
 }

