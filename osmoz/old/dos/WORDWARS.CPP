#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <mem.h>
#include <dos.h>
#include <graphics.h>
#include "dico.h"
#include "plateau.h"
#include "joueur.h"
#include "affgraph.h"
#include "mouse.h"

#define ABORT   2


dico Dico;
joueur J[6]={{0}, {1}, {2}, {3}, {4}, {5}};
plateau p;
graphmode gm;
mouse m;

extern unsigned char Matrice[8];

// Variables globales du jeu
unsigned long lVerif1=0,lVerif2=0;

// 1. Texte
unsigned char Msg[480], NomFich[60], NomVierge[8]={0,0,0,0,0,0,0,0},
              Presentation[]="\n\
I.H.S.V. Productions pr‚sente\n\
· ÖÖÄ·ÄÄ·ÄÒ·ÿ· ÖÖÄ·ÄÄ·ÖÄ·\n\
º³ºº ºÄÒ½ ºº º³ºÇÄ¶ÄÒ½ÓÄ·\n\
ÓÁ½ÓÄ½ ÓÄÄÐ½ ÓÁ½½ Ó ÓÄÄÄ½\n",
              IHSV[]="Un jeu cr‚‚ par Patrice FOUQUET",
              CombienDeJoueurs[]="Nombre de joueurs (2, 3 ou 6) ?",
              EntrezNomFichChg[]="Entrez le nom (sans extension) du fichier … charger\n(avec chemin si n‚cessaire) :\n ",
              EntrezNomFichSvg[]="Entrez le nom (sans extension) du fichier de sauvegarde\n(avec chemin si n‚cessaire) :\n ",
              ErreurLecture[]="ERREUR DISQUE :\nErreur pendant la lecture du fichier.",
              ErreurEcriture[]="ERREUR DISQUE :\nErreur pendant l'‚criture du fichier.",
              ImpossibleLir[]="ERREUR DISQUE :\nImpossible de charger le fichier sp‚cifi‚.\nFichier inexistant ou chemin incorrect.",
              ImpossibleEcr[]="ERREUR DISQUE :\nImpossible de sauver le fichier sp‚cifi‚.\nNom de fichier ou chemin incorrect.",
              ChrgPartie[]="Voulez-vous charger une partie sauvegard‚e (O/N) ?",
              TpsImpartiEcoule[]="Le temps ‚coul‚ de %s d‚passe le temps total imparti de %d minutes.",
              SvgTerminee[]="Sauvegarde termin‚e.",
              ChrgTermine[]="Chargement termin‚.",
              LigneClassement[]="%d. %-7s avec %03d pts, %2d jetons et %03d pts-jetons",
              SuiteJeu[]="Voulez-vous commencer ou continuer une autre partie (O/N) ?",
              FaireDemiFinale[]="Voulez-vous faire la « FINALE (O/N) ?",
              FaireFinale[]="Voulez-vous faire la FINALE (O/N) ?",
              FinDeJeu[]="FIN de la GUERRE",
              Ctpa[]="\nC'est tout pour aujourd'hui.\n";

// 2. Variables d'environnement de jeu
const unsigned PrmCase[6][2]={{0,0},{5,0},{10,5},{10,10},{5,10},{0,5}};
unsigned nbj=0, Jo=0, Tour=0, Fin=0, TpsReflexion=3600, AffMsgPartie=1;

int Sauvegarde()
 {
  int Bon=0, i;
  FILE *f;
  gm.SaisitChaine(EntrezNomFichSvg, NomFich, 56, 11);
  if (NomFich[0])
   {
    strcat(NomFich, ".GDM");
    if (f=fopen(NomFich, "wb"))
     {
      Bon=(fwrite(&nbj, sizeof(nbj), 1, f)==1);
      if (Bon) Bon=(fwrite(&Jo, sizeof(nbj), 1, f)==1);
      if (Bon) Bon=(fwrite(&Tour, sizeof(nbj), 1, f)==1);
      for(i=0; (i<nbj)&&(Bon); i++)
       Bon=J[i].Sauve(f);
      if (Bon) Bon=p.Sauve(f);
      if (!Bon)
       {
        sound(440);
        gm.AfficheMessage(ErreurEcriture, 12, 0);
       }
     }
    else
     {
      sound(440);
      gm.AfficheMessage(ImpossibleEcr, 12, 0);
      Bon=0;
     }
   }
  if (Bon) Bon=(!fclose(f));
  if (Bon)
   gm.AfficheMessage(SvgTerminee, 11, 0);
  return Bon;
 }

int Chargement()
 {
  int Bon=0, i;
  FILE *f;
  gm.SaisitChaine(EntrezNomFichChg, NomFich, 56, 11);
  if (NomFich[0])
   {
    strcat(NomFich, ".GDM");
    if (f=fopen(NomFich, "rb"))
     {
      Bon=(fread(&nbj, sizeof(nbj), 1, f)==1);
      if (Bon) Bon=(fread(&Jo, sizeof(nbj), 1, f)==1);
      if (Bon) Bon=(fread(&Tour, sizeof(nbj), 1, f)==1);
      for(i=0; (i<nbj)&&(Bon); i++)
       Bon=J[i].Charge(f);
      if (Bon) Bon=p.Charge(f);
      if (!Bon)
       {
        sound(440);
        gm.AfficheMessage(ErreurLecture, 12, 0);
       }
     }
    else
     {
      sound(440);
      gm.AfficheMessage(ImpossibleLir, 12, 0);
      Bon=0;
     }
   }
  if (Bon) Bon=(!fclose(f));
  if (Bon)
   gm.AfficheMessage(ChrgTermine, 11, 0);
  return Bon;
 }

#pragma warn -par
int handler(int errval, int ax, int bp, int si)
 {
  unsigned di;
  int NumErr;
  di= _DI;
  if (ax<0)
   {
    NumErr=33; // Erreur de p‚riph‚rique
    hardretn(ABORT);
    closegraph();
   }
  NumErr=di&0x00FF;
  hardresume(gm.Relancement(NumErr));
  return ABORT;
 }
#pragma warn +par

int c_break()
 {
  textmode(3);
  printf("Ben pourquoi ?\n");
  //printf("%ld,%ld", lVerif1, lVerif2);
  return 0;
 }

void main()
 {
  char Rep, NomSvt[3][8];
  unsigned i, j, n, xx, yy, ChrgDebut, Continue=0, Finale=0, JoAuto[3], NbjSvt;
  int cl[6], nj[6], np[6];
  ctrlbrk(c_break);
  harderr(handler);
  setmem(Msg, sizeof(Msg), 0);

    for(i=0; i<strlen(Presentation);i++)
     lVerif1+=(unsigned long)Presentation[i];
    for(i=0; i<strlen(IHSV);i++)
     lVerif2+=(unsigned long)IHSV[i];

  gm.DessinePlateau();
  m.SetMouseCursor(0, 0, 0);
  gm.AfficheMessage(Presentation, 14, 2000);
  gm.AfficheMessage(IHSV, 11, 2000);
  do
   {
    if (!Finale)
     {
      Rep=gm.PoseQuestion(ChrgPartie, "OoNn", 15);
      ChrgDebut=(Rep=='o')||(Rep=='O');
      if (ChrgDebut)
       {
        if (ChrgDebut=Chargement())
         gm.ReinitialiseEcran();
       }
     }
    if ((!ChrgDebut)&&(!Finale))
     {
      nbj=gm.PoseQuestion(CombienDeJoueurs, "236", 10)-48;
      for(i=0; i<nbj; i++)
       {
        xx=8*((680-64*nbj)/16)+64*i-11;
        setfillstyle(0, 0);
        for(j=1; j<7; j++)
         {
          bar(xx+30-5*j,11-j, xx+30+5*j, 11+j);
          bar(xx+30-5*j,27-j, xx+30+5*j, 27+j);
          bar(xx+30-5*j,43-j, xx+30+5*j, 43+j);
          delay(50);
         }
        for(j=15; j!=3+2*i; j-=6-i)
         {
          setcolor(j-6*(j==9));
          rectangle(xx-1,  4, xx+61, 18);
          rectangle(xx-1, 20, xx+61, 34);
          rectangle(xx-1, 36, xx+61, 50);
          delay(100);
         }
        J[i].SaisitNom();
        J[i].IncrementeScore(0);
        nosound();
        J[i].DefPrmCase(xx=PrmCase[6*i/nbj][0], yy=PrmCase[6*i/nbj][1]);
        p.c[xx][yy].Joueur=1+i;
        p.AfficheCase(xx, yy, 0);
       }
     }
    else
     Finale=ChrgDebut=Continue=0;
    p.AfficheValNaiss();
    do
     {
      if (J[Jo].TpsEcoule<(((lVerif1==15917L)&&(lVerif2==2740L))?((double)TpsReflexion):10.0)/nbj)
       {
        J[Jo].AfficheLettresDisp();
        if (J[Jo].Automate)
         p.PlaceLettreAuto();
        else
         p.PlaceLettre();
       }
      else
       {
        sprintf(Msg, TpsImpartiEcoule, J[Jo].Nom, (int)(TpsReflexion/nbj));
        gm.AfficheMessage(Msg, 12, 3000);
        p.NbPasseTour++;
       }
      Jo=(Jo+1)%nbj;
      Fin=(!p.NbCasesLibres)||((p.NbPasseTour>=nbj-1)&&(!Jo));
      if (!Jo)
       {
        Tour++;
        p.NbPasseTour=0;
       }
     }
    while(!Fin);
    for(i=0; i<6; i++)
     {
      cl[i]=1;
      nj[i]=np[i]=0;
     }
    for(xx=0; xx<11; xx++)
     for(yy=p.XYMin[xx]; yy<=p.XYMax[xx]; yy++)
      if (i=p.c[xx][yy].Joueur)
       {
        nj[i-1]++;
        np[i-1]+=p.c[xx][yy].Valeur;
       }
    for(i=0; i<nbj; i++)
     for(j=0; j<nbj; j++)
      if (131172UL*(unsigned long)J[i].Score+
            1024UL*(unsigned long)nj[i]+
                   (unsigned long)np[i]<
          131172UL*(unsigned long)J[j].Score+
            1024UL*(unsigned long)nj[j]+
                   (unsigned long)np[j]) cl[i]++;
    sound(1760);
    gm.AfficheMessage(FinDeJeu, 15, 0);
    settextstyle(0, 0, 0);
    NbjSvt=(nbj>=2)+(nbj>=3)+(nbj>=6);
    for(n=i=0; i<nbj; i++)
     for(j=0; j<nbj; j++)
      if (cl[j]==i+1)
       {
        if (n<NbjSvt)
         {
          strcpy(NomSvt[n], J[j].Nom);
          JoAuto[n]=J[j].Automate;
         }
        sprintf(Msg, LigneClassement, i+1, J[j].Nom, J[j].Score, nj[j], np[j]);
        setcolor(7-3*(n<NbjSvt));  outtextxy(320, 434+8*i, Msg);
        setcolor(15-3*(n<NbjSvt)); outtextxy(321, 433+8*i, Msg);
        if (n<3) n++;
       }
    m.RepeatUntilNoPress();
    while(!m.ButtonPressed());
    setfillpattern(Matrice, 8);
    bar(80, 429, 559, 479);
    Continue=Finale=0;
    if (NbjSvt>1)
     {
      if (NbjSvt==3)
       Rep=gm.PoseQuestion(FaireDemiFinale, "OoNn", 15);
      else
       Rep=gm.PoseQuestion(FaireFinale, "OoNn", 15);
      Finale=(Rep=='o')||(Rep=='O');
     }
    if (!Finale)
     {
      Rep=gm.PoseQuestion(SuiteJeu, "OoNn", 11);
      if (Continue=(Rep=='O')||(Rep=='o'))
       {
        for(i=0; i<6; i++)
         J[i].Reinitialise(NomVierge, 0);
        p.Reinitialise();
        nbj=0; Jo=0; Tour=0;
        gm.ReinitialiseEcran();
       }
     }
    else
     {
      p.Reinitialise();
      for(i=0; i<NbjSvt; i++)
       {
        J[i].DefPrmCase(xx=PrmCase[6*i/NbjSvt][0], yy=PrmCase[6*i/NbjSvt][1]);
        p.c[xx][yy].Joueur=1+i;
        J[i].Reinitialise(NomSvt[i], JoAuto[i]);
       }
      nbj=NbjSvt; Jo=0; Tour=0;
      gm.ReinitialiseEcran();
     }
   }
  while(Finale||Continue);
  textmode(3);
  printf(Ctpa);
 }
