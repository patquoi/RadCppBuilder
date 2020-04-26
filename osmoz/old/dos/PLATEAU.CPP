#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <mem.h>
#include <graphics.h>
#include "plateau.h"
#include "dico.h"
#include "affgraph.h"
#include "mouse.h"
#include "joueur.h"


// Contextes pour GereES()
#define CHOIX_LETTRE 0
#define PLCMT_LETTRE 1

#define NBPRMLTR     114

// Convention
// Directions
//
//   1 0 5
//    \³/
//    /³\
//   2 3 4


extern dico Dico;
extern graphmode gm;
extern mouse m;
extern joueur J[6];
extern unsigned nbj, Jo, Tour, TpsReflexion, AffMsgPartie;
extern unsigned char Msg[480];

extern int Sauvegarde();  // de WORDWARS.CPP
extern int Chargement();  //    ------------

// Messages
char TourDeJeu[]="C'est … %s de jouer.",
     CaseIncContigue[]="CASE INCORRECTE ! Elle doit ˆtre vide et contigu‰ … une case occup‚e par une de vos lettres.\nRecommencez votre choix.",
     CaseIncPrmCase[]="CASE INCORRECTE ! Elle doit ˆtre la case initiale de coordonn‚es (%d, %d).\nRecommencez votre choix.",
     CaseIncLettreAppart[]="CASE INCORRECTE ! Elle doit ˆtre occup‚e par une de vos lettres.\nRecommencez votre choix.",
     ValeurCreationInsuf[]="VALEUR DE CREATION INSUFFISANTE ! La lettre choisie n'a pas le nombre suffisant de points pour g‚n‚rer une lettre suppl‚mentaire. Reportez-vous … la colonne situ‚e … gauche du plateau pour connaŒtre la valeur minimale.",
     MotForme[]="Vous formez le mot \"%s\".\nVous obtenez %d points.\nVous retirez %d point(s) et prenez %d lettre(s) … vos adversaires.",
     BilanPlacemt[]="Au total, vous avez\nform‚ %d mot(s),\nobtenu %d points,\nretir‚ %d point(s) et pris %d lettre(s) … vos adversaires.",
     LettreIncIdent[]="LETTRE INCORRECTE ! Vous devez choisir une lettre diff‚rente de celles choisies par vos adversaires. Recommencez votre choix.",
     LettreMorte[]="LETTRE MORTE ! Les lettres Q et Z ne permettent de former aucun mot de deux lettres. Choisissez une autre lettre.",
     CaseIncMotCree[]="CASE INCORRECTE ! Elle ne permet la cr‚ation d'au moins un mot.\nRecommencez votre choix.",
     ChoixAutreLtrImp[]="CHOIX D'UNE AUTRE LETTRE IMPOSSIBLE ! Vous avez effectu‚ une cr‚ation de lettre.",
     AutomatePlaceLtr[]="L'automate %s place la lettre %c en (%d, %d).",
     AutomatePasseTour[]="L'automate %s passe son tour.",
     OpIgnoreeTpsEcoule[]="Votre temps total de jeu d‚passe le temps total imparti de %d minutes. Votre op‚ration est ignor‚e.";

const unsigned ChxPrmLtr[114]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,6,6,7,8,8,8,8,9,9,9,9,9,9,9,9,9,9,9,10,11,12,12,12,12,13,13,13,13,14,14,14,14,14,
                               15,15,15,15,15,15,15,15,16,16,18,18,18,18,18,19,19,19,19,19,19,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21,22,22,22,22,23,24,25};

int max(int value1, int value2)
{
 return ((value1>value2)?value1:value2);
}

int min(int value1, int value2)
{
 return((value1>value2)?value2:value1);
}

plateau::plateau()
 {
  unsigned i;
  NbPasseTour=Recherche=SauvePos=0;
  NbCasesLibres=91;
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
  for(i=0; i<11; i++)
   if (i<6)
    {
     XYMin[i]=0;
     XYMax[i]=5+i;
    }
   else
    {
     XYMax[i]=10;
     XYMin[i]=i-5;
    }
 }

void plateau::Reinitialise()
 {
  NbPasseTour=Recherche=SauvePos=0;
  NbCasesLibres=91;
  setmem(c, sizeof(c), 0);
 }

void plateau::AffichePlateau()
 {
  int x, y;
  for(x=0; x<11; x++)
   for(y=XYMin[x]; y<=XYMax[x]; y++)
    AfficheCase(x, y, 0);
 }

void plateau::ChoixCase(unsigned *x, unsigned *y, unsigned *b)
 {
  int Lig, Col, Contigu=0;
  unsigned i, CursLettre=m.NumCurs, Val, xAnc=5, yAnc=5, xm=320, ym=240,
           xcAnc=311, ycAnc=224, xc=311, yc=224, xx, yy, bg, bd, bm, g=0, d=0;
  static unsigned xms=320, yms=200, xs=5, ys=5, xcs=311, ycs=224, ncs=0;
  *x=5; *y=5;
  m.WinMouse(156, 55, 484, 426);
  m.CursorOn();
  if (!SauvePos)
   {
    m.MoveMouse(320, 240);
    m.SetMouseCursor(0, 0, 0);
   }
  else
   {
    m.MoveMouse(xm=xms, ym=yms);
    m.SetMouseCursor(8-8*((!ncs)||(ncs==3)), 8-8*((!ncs)||(ncs==3))-(ncs>4), ncs);
    if (ncs<5)
     {
      if ((c[*x][*y].Joueur==Jo+1)&&(c[*x][*y].Valeur))
       {
        if (c[*x][*y].Valeur>=ValNaiss[c[*x][*y].Lettre])
         {
          if (m.NumCurs!=1)
           m.SetMouseCursor(8, 8, 1);
         }
        else
         {
          if (m.NumCurs!=3)
           m.SetMouseCursor(0, 0, 3);
         }
       }
      else
       {
        if (m.NumCurs)
         m.SetMouseCursor(0, 0, 0);
       }
     }
    *x=xs; *y=ys;
    xc=xcs; yc=ycs;
    xAnc=*x;
    yAnc=*y;
    xcAnc=xc;
    ycAnc=yc;
   }
  m.CursorOff();
  if (Val=c[*x][*y].Joueur)
   gm.AfficheValeur(xc, yc, c[*x][*y].Lettre, c[*x][*y].Valeur, Val);
  putimage(xc-5, yc, gm.BufCurs, 1);
  m.RepeatUntilNoPress();
  m.CursorOn();
  do
   {
    TesteTemps();
    m.GetMouse(&xm, &ym, &bg, &bd, &bm);
    g=bg;
    d=bd;
    if ((xm>160)&&(xm<479)&&(ym>53)&&(ym<426))
     {
      Col=(xm-161)/30;
      Lig=(ym-54)/17;
      if ((Lig>=abs(Col-5))&&(Lig<=21-abs(Col-5)))
       {
        if (xc!=(Val=161+30*Col)) xc=Val;
        if (yc!=(Val=54+17*(2*((Lig-!(Col%2))/2)+!(Col%2)))) yc=Val;
        Val=(Lig-abs(5-Col))/2;
        *x=Val+(Col<5)*(5-Col);
        *y=Val+(Col>5)*(Col-5);
        // sauvegarde des donn‚es xym, *xy, xyc, nc
        xms=xm; yms=ym;
        xs=*x; ys=*y;
        xcs=xc; ycs=yc;
        ncs=m.NumCurs;
        if ((xAnc!=*x)||(yAnc!=*y))
         {
          m.CursorOff();
          if (c[xAnc][yAnc].Joueur) gm.AfficheValeur(xcAnc, ycAnc, c[xAnc][yAnc].Lettre, c[xAnc][yAnc].Valeur, 0);
          putimage(xcAnc-5, ycAnc, gm.BufCurs, 1);
          if (Val=c[*x][*y].Joueur) gm.AfficheValeur(xc, yc, c[*x][*y].Lettre, c[*x][*y].Valeur, Val);
          putimage(xc-5, yc, gm.BufCurs, 1);
          m.CursorOn();
          if (Tour)
           {
            if (Contigu=(!c[*x][*y].Joueur))
             {
              for(Contigu=i=0; (!Contigu)&&(i<6); i++)
               {
                xx=(*x)+dx[i]; yy=(*y)+dy[i];
                Contigu=(xx<11)&&
                    (yy<11)&&
                    (xx>=XYMin[yy])&&
                    (xx<=XYMax[yy])&&
                    (yy>=XYMin[xx])&&
                    (yy<=XYMax[xx])&&
                    (c[xx][yy].Joueur==Jo+1);
               }
             }
           }
          else
           Contigu=(*x==J[Jo].CoordDeb[0])&&(*y==J[Jo].CoordDeb[1]);
          if (Contigu)
           {
            if (m.NumCurs!=CursLettre)
             m.SetMouseCursor(8, 7, CursLettre);
           }
          else
           {
            if ((c[*x][*y].Joueur==Jo+1)&&(c[*x][*y].Valeur))
             {
              if (c[*x][*y].Valeur>=ValNaiss[c[*x][*y].Lettre])
               {
                if (m.NumCurs!=1)
                 m.SetMouseCursor(8, 8, 1);
               }
              else
               {
                if (m.NumCurs!=3)
                 m.SetMouseCursor(0, 0, 3);
               }
             }
            else
             {
              if (m.NumCurs)
               m.SetMouseCursor(0, 0, 0);
             }
           }
          xAnc=*x;
          yAnc=*y;
          xcAnc=xc;
          ycAnc=yc;
         }
       }
     }
   }
  while((!g)&&(!d));
  do // On attend que tous les boutons soient lƒch‚s...
   {
    randomize();
    TesteTemps();
    m.GetButtons(&bg, &bd, &bm);
    g=g||bg;
    d=d||bd;
   }
  while(bg||bd);
  *b=(g>0)+2*(d>0);
  m.CursorOff();
  if (c[*x][*y].Joueur) gm.AfficheValeur(xc, yc, c[*x][*y].Lettre, c[*x][*y].Valeur, 0);
  putimage(xc-5, yc, gm.BufCurs, 1);
  m.WinMouse(0, 0, 639, 479);
 }

void plateau::AfficheCase(unsigned x, unsigned y, unsigned CoulTxt)
 {
  unsigned Col=5+y-x,
           Lig=abs(5-Col)+2*(x*(Col>=5)+y*(Col<5)),
           xc=161+30*Col,
           yc=54+17*(2*((Lig-!(Col%2))/2)+!(Col%2));
  if (c[x][y].Joueur)
   gm.DessineHexagone(xc+5, yc, c[x][y].Joueur+8);
  else
   gm.DessineHexagone(xc+5, yc, 8);
  gm.AfficheValeur(xc, yc, c[x][y].Lettre, c[x][y].Valeur, CoulTxt);
 }

void plateau::AfficheValNaiss()
 {
  unsigned i;
  setcolor(8);
  for(i=0; i<26; i++)
   {
    gm.DessineHexagone(11+30*(i%2), 17*i, 8);
    gm.AfficheValeur(6+30*(i%2), 17*i, i+1, ValNaiss[i+1], 0);
   }
 }

void plateau::PlaceLettre()
 {
  unsigned i, Lettre, xl, yl, xx, yy, Btn, Bon=1,
           PionPose=0, Passe=0, NvChoix=0, Creation=0;
  unsigned char Rep;
  DepartChrono();
  gm.Horloge=1;
  sprintf(Msg, TourDeJeu, J[Jo].Nom);
  if (AFFICHAGE) gm.AfficheMessage(Msg, 9+Jo, 0);
  do
   {
    SauvePos=Passe=NvChoix=0;
    do
     {
      Lettre=J[Jo].ChoixLettre();
      m.CursorOff();
      if (!Lettre)
       {
        Rep=gm.GereES(CHOIX_LETTRE);
        switch(Rep)
         {
          case 'p':
          case 'P': Passe=1;
                    NbPasseTour++;
                    break;
          case 's':
          case 'S': gm.Horloge=0;
                    Sauvegarde();
                    gm.Horloge=1;
                    break;
          case 'c':
          case 'C': gm.Horloge=0;
                    if (Chargement())
                     {
                      gm.ReinitialiseEcran();
                      DepartChrono();
                     }
                    gm.Horloge=1;
                    break;
          default : break;
         }
        Bon=0;
       }
      else
       {
        if (!Tour)
         {
          for(i=0; (Bon=(c[J[i].CoordDeb[0]][J[i].CoordDeb[1]].Lettre!=Lettre))&&(i<Jo); i++);
          if (!Bon)
           {
            sound(440);
            gm.AfficheMessage(LettreIncIdent, 12, 0);
            J[Jo].Nombre[Lettre]++;
            J[Jo].Nombre[0]++;
            gm.DessineHexagone(580+30*(Lettre%2), 17*(Lettre-1), 9+Jo);
            gm.AfficheValeur(575+30*(Lettre%2), 17*(Lettre-1), Lettre, 1, 0);
           }
          else
           {
            if (!(Bon=(Lettre!=17)&&(Lettre!=26)))
             {
              sound(440);
              gm.AfficheMessage(LettreMorte, 12, 0);
              J[Jo].Nombre[Lettre]++;
              J[Jo].Nombre[0]++;
              gm.DessineHexagone(580+30*(Lettre%2), 17*(Lettre-1), 9+Jo);
              gm.AfficheValeur(575+30*(Lettre%2), 17*(Lettre-1), Lettre, 1, 0);
             }
           }
         }
        else
         Bon=1;
       }
     }
    while((!Bon)&&(!Passe));
    PionPose=SauvePos=0;
    if (!Passe) do
     {
      do
       {
        m.NumCurs=Lettre+4;
        ChoixCase(&xl, &yl, &Btn);
        switch(Btn)
         {
          case 2:
          case 1: if (Tour)
                   {
                    if (!c[xl][yl].Joueur)
                     {
                      for(Bon=i=0; (!Bon)&&(i<6); i++)
                       {
                        xx=xl+dx[i]; yy=yl+dy[i];
                        Bon=(xx<11)&&
                            (yy<11)&&
                            (xx>=XYMin[yy])&&
                            (xx<=XYMax[yy])&&
                            (yy>=XYMin[xx])&&
                            (yy<=XYMax[xx])&&
                            (c[xx][yy].Joueur==Jo+1);
                       }
                      if (!Bon)
                       {
                        sound(440);
                        gm.AfficheMessage(CaseIncContigue, 12, 0);
                       }
                      else
                       PionPose=1;
                     }
                    else
                     {
                      if ((c[xl][yl].Joueur==Jo+1)&&(i=c[xl][yl].Lettre))
                       {
                        if (c[xl][yl].Valeur>=ValNaiss[i])
                         {
                          Creation=1;
                          J[Jo].Nombre[i]++;
                          J[Jo].Nombre[0]++;
                          c[xl][yl].Valeur-=ValNaiss[i];
                          AfficheCase(xl, yl, 0);
                          gm.DessineHexagone(580+30*(i%2), 17*(i-1), 9+Jo);
                          gm.AfficheValeur(575+30*(i%2), 17*(i-1), i, J[Jo].Nombre[i], 0);
                         }
                        else
                         {
                          sound(440);
                          gm.AfficheMessage(ValeurCreationInsuf, 12, 0);
                         }
                       }
                      else
                       {
                        sound(440);
                        gm.AfficheMessage(CaseIncLettreAppart, 12, 0);
                       }
                     }
                   }
                  else
                   {
                    if ((xl!=J[Jo].CoordDeb[0])||(yl!=J[Jo].CoordDeb[1]))
                     {
                      sprintf(Msg, CaseIncPrmCase, J[Jo].CoordDeb[0], J[Jo].CoordDeb[1]);
                      sound(440);
                      gm.AfficheMessage(Msg, 12, 0);
                     }
                    else
                     PionPose=1;
                   }
                  break;
          case 3: Rep=gm.GereES(PLCMT_LETTRE);
                  switch(Rep)
                   {
                    case 'p':
                    case 'P': NbPasseTour+=(Passe=(Rep=='p')||(Rep=='P'));
                    case 'r':
                    case 'R': NvChoix=((Rep=='r')||(Rep=='R'))&&(!Creation);
                              J[Jo].Nombre[Lettre]++;
                              J[Jo].Nombre[0]++;
                              gm.DessineHexagone(580+30*(Lettre%2), 17*(Lettre-1), 9+Jo);
                              gm.AfficheValeur(575+30*(Lettre%2), 17*(Lettre-1), Lettre, J[Jo].Nombre[Lettre], 0);
                              if (((Rep=='r')||(Rep=='R'))&&(Creation))
                               {
                                sound(440);
                                gm.AfficheMessage(ChoixAutreLtrImp, 13, 0);
                               }
                    case 's':
                    case 'S': if ((Rep=='s')||(Rep=='S'))
                               {
                                gm.Horloge=0;
                                Sauvegarde();
                                gm.Horloge=1;
                               }
                    case 'c':
                    case 'C': if ((Rep=='c')||(Rep=='C'))
                               {
                                gm.Horloge=0;
                                if (Chargement())
                                 {
                                  gm.ReinitialiseEcran();
                                  DepartChrono();
                                  NvChoix=1;
                                 }
                                gm.Horloge=1;
                               }
                    default : break;
                   }
                  break;
         }
        SauvePos=(!PionPose)&&(!Passe)&&(!NvChoix);
       }
      while(SauvePos);
      if ((!Passe)&&(!NvChoix))
       {
        if (J[Jo].TpsEcoule+difftime(time(NULL), TopTour)<((double)TpsReflexion)/nbj)
         {
          c[xl][yl].Lettre=Lettre;
          c[xl][yl].Valeur=0;
          c[xl][yl].Joueur=Jo+1;
          NbCasesLibres--;
          AfficheCase(xl, yl, 0);
          if (Tour)
           Bon=ChercheMotsFormes(xl, yl);
          SauvePos=(!Bon);
          if (!Bon)
           {
            sound(440);
            gm.AfficheMessage(CaseIncMotCree, 12, 0);
            c[xl][yl].Lettre=0;
            c[xl][yl].Valeur=0;
            c[xl][yl].Joueur=0;
            AfficheCase(xl, yl, 0);
           }
         }
        else
         {
          sprintf(Msg, OpIgnoreeTpsEcoule, TpsReflexion/60/nbj);
          sound(440);
          gm.AfficheMessage(Msg, 15, 0);
         }
       }
      SauvePos=(!Bon)&&(!Passe)&&(!NvChoix);
     }
    while(SauvePos);
   }
  while(NvChoix);
  SauvePos=0;
  gm.Horloge=0;
  FinChrono();
 }

void plateau::PlaceLettreAuto()
 {
  int Lig, Col;
  unsigned i, Bon, SupEgal, x, y, XChx=0, YChx=0, LtrChx=0, xx, yy, Lettre, NbChoix=0, ChxLtr[225], ChxXY[225][2];
  unsigned long ChxPtsGagnes=0, ChxPtsPris=0, ChxLtrPrises=0, ChxTotCoefs=0;
  setmem(ChxLtr, sizeof(ChxLtr), 0);
  setmem(ChxXY, sizeof(ChxXY), 0);
  DepartChrono();
  gm.Horloge=1;
  sprintf(Msg, TourDeJeu, J[Jo].Nom);
  if (AFFICHAGE) gm.AfficheMessage(Msg, 9+Jo, 1000);
  Recherche=1;
  if (Tour)
   {
    // 1. Choix de la lettre et de l'emplacement
    for(x=0; x<11; x++)
     {
      for(y=XYMin[x]; y<=XYMax[x]; y++)
       {
        if (Bon=!c[x][y].Joueur)
         {
          for(Bon=i=0; (!Bon)&&(i<6); i++)
           {
            xx=x+dx[i]; yy=y+dy[i];
            Bon=(xx<11)&&
                (yy<11)&&
                (xx>=XYMin[yy])&&
                (xx<=XYMax[yy])&&
                (yy>=XYMin[xx])&&
                (yy<=XYMax[xx])&&
                (c[xx][yy].Joueur==Jo+1);
           }
         }
        if (Bon)
         {
          Lettre=0;
          do
           {
            for(Lettre++; (Lettre<27)&&(!J[Jo].Nombre[Lettre]); Lettre++);
            if (Lettre<27)
             {
              SupEgal=0;
              c[x][y].Lettre=Lettre;
              c[x][y].Joueur=Jo+1;
              /***************** Comparaison */
              if (ChercheMotsFormes(x, y))
               {
                if (PtsGagnes+PtsPris>=ChxPtsGagnes+PtsPris)
                  if (!(SupEgal=(PtsGagnes+PtsPris>ChxPtsGagnes+PtsPris)))
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
                ChxLtr[NbChoix-1]=Lettre;
                ChxXY[NbChoix-1][0]=x;
                ChxXY[NbChoix-1][1]=y;
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
          while(Lettre<27);
         }
       }
     }
    // 2. Recherche des lettres pouvant faire naitre des lettres
    for(x=0; x<11; x++)
     {
      for(y=XYMin[x]; y<=XYMax[x]; y++)
       {
        if (c[x][y].Joueur==Jo+1)
         {
          if (c[x][y].Valeur>=ValNaiss[Lettre=c[x][y].Lettre])
           {
            // m. … j. et affichages
            J[Jo].Nombre[Lettre]++;
            J[Jo].Nombre[0]++;
            c[x][y].Valeur-=ValNaiss[Lettre];
            Col=5+y-x;
            Lig=abs(5-Col)+2*(x*(Col>=5)+y*(Col<5));
            xx=156+30*Col;
            yy=54+17*(2*((Lig-!(Col%2))/2)+!(Col%2));
            putimage(xx, yy, gm.BufCurs, 1);
            AfficheCase(x, y, 15);
            delay(500);
            putimage(xx, yy, gm.BufCurs, 1);
            AfficheCase(x, y, 0);
            gm.DessineHexagone(580+30*(Lettre%2), 17*(Lettre-1), 8+(J[Jo].Nombre[Lettre]>0)*(Jo+1));;
            gm.AfficheValeur(575+30*(Lettre%2), 17*(Lettre-1), Lettre, J[Jo].Nombre[Lettre], 0);
           }
         }
       }
     }
    // Tirage au sort parmi les solutions ‚quivalentes trouv‚es
    i=(NbChoix>1)*random(NbChoix);
    XChx=ChxXY[i][0];
    YChx=ChxXY[i][1];
    LtrChx=ChxLtr[i];
   }
  else // Choix au hasard avec probabilites de formation d'un mot de deux lettres
   {
    NbChoix=1;
    XChx=J[Jo].CoordDeb[0];
    YChx=J[Jo].CoordDeb[1];
    do // Lettre choisie diff‚rentes de celles des adversaires
     {
      LtrChx=ChxPrmLtr[random(NBPRMLTR)];
      for(i=0; (Bon=(c[J[i].CoordDeb[0]][J[i].CoordDeb[1]].Lettre!=LtrChx))&&(i<Jo); i++);
     }
    while(!Bon);
   }
  // Message
  Recherche=0;
  if (NbChoix)
   {
    sprintf(Msg, AutomatePlaceLtr, J[Jo].Nom, LtrChx+64, XChx, YChx);
    if (AFFICHAGE) gm.AfficheMessage(Msg, 9+Jo, 1000); else delay(500);
    // Mise … jour du plateau
    c[XChx][YChx].Lettre=LtrChx;
    c[XChx][YChx].Valeur=0;
    c[XChx][YChx].Joueur=Jo+1;
    NbCasesLibres--;
    J[Jo].Nombre[LtrChx]--;
    J[Jo].Nombre[0]--;
    gm.DessineHexagone(580+30*(LtrChx%2), 17*(LtrChx-1), 8+(J[Jo].Nombre[LtrChx]>0)*(Jo+1));
    gm.AfficheValeur(575+30*(LtrChx%2), 17*(LtrChx-1), LtrChx, J[Jo].Nombre[LtrChx], 0);
    // Affichage de la lettre;
    AfficheCase(XChx, YChx, 0);
    if (Tour)
     ChercheMotsFormes(XChx, YChx);
   }
  else
   {
    sprintf(Msg, AutomatePasseTour, J[Jo].Nom);
    if (AFFICHAGE) gm.AfficheMessage(Msg, 9+Jo, 1000);
    NbPasseTour++;
   }
  gm.Horloge=0;
  FinChrono();
 }

int plateau::ChercheMotsFormes(int x, int y)
 {
  int MotCree=0, PtsPlus, PtsMoins, TotPlus=0, TotMoins=0, NbMots=0, NbLtrPrises=0, TotLtrPrises=0,
      Val, i, iInf, iSup, iMax, iDeb, iDebMin,
      Dir, nl, Sens, xx, yy, LgrMin, LgrMot[6];
  unsigned NumJo=c[x][y].Joueur;
  unsigned char Mot[2][7];
   // On ‚value les mots dans les deux sens : l'un ou l'autre doit exister
  if (Recherche)
   {
    randomize();
    TesteTemps();
    PtsGagnes=PtsPris=LtrPrises=TotCoefs=0;
   }
  for(Dir=0; Dir<3; Dir++)
   {
    setmem(LgrMot, sizeof(LgrMot), 0);
    switch(Dir) // D‚finition de l'intervalle des limites du plateau [iInf, iSup]
     {
      case 0: iInf=x-XYMax[5+x-y]; iSup=x-XYMin[5+x-y]; break;
      case 1: iInf=y-XYMax[x]; iSup=y-XYMin[x]; break;
      case 2: iSup=XYMax[y]-x; iInf=XYMin[y]-x; break;
     }
    // On d‚finit l'intervalle d'‚tude des mots
    for(iDebMin=0; (iDebMin>=-5)&&(iDebMin>=iInf)&&(c[x+iDebMin*dx[Dir]][y+iDebMin*dy[Dir]].Lettre); iDebMin--);
    iDebMin++;
    for(iMax=0; (iMax<=5)&&(iMax<=iSup)&&(c[x+iMax*dx[Dir]][y+iMax*dy[Dir]].Lettre); iMax++);
    iMax--;
    // On ‚tudie tous les cas de mots en partant des mots de 6 lettres
    // On passe au iDeb suivant dŠs que le mot de nl lettres existe
    // -> elimination des mots contenu
    for(iDeb=iDebMin; iDeb<=min(iMax-1, 0); iDeb++)
     {
      Sens=0;
      LgrMin=0;
      for(i=1; i<=iDeb-iDebMin; i++)
       if (LgrMin<(nl=LgrMot[iDeb-iDebMin-i]+1-i)) LgrMin=nl;
      for(nl=min(6, iMax-iDeb+1); (!Sens)&&(nl>=max(max(2, LgrMin), 1-iDeb)); nl--)
       {
        for(i=0; i<nl; i++)
         Mot[1][nl-i-1]=Mot[0][i]=c[x+(iDeb+i)*dx[Dir]][y+(iDeb+i)*dy[Dir]].Lettre+64;
        Mot[1][nl]=Mot[0][nl]=0;
        if (!(Sens=Dico.Existe(Mot[0], nl)))
         Sens=2*Dico.Existe(Mot[1], nl);
        // 1. Affichage des lettres du mot en blanc : AfficheCase(,,15)
        // 2. Annonce du mot existant : AfficheMessage()
        // 3. (In/D‚)cr‚mentation de la valeur des lettres du mot
        // 4. R‚affichage des lettres du mot en noir : AfficheCase(,,0)
        if (Sens)
         {
          if (!MotCree) MotCree=1;
          NbMots++;
          NbLtrPrises=PtsPlus=PtsMoins=0;
          LgrMot[iDeb-iDebMin]=nl;
          for(i=0; i<nl; i++)
           {
            xx=x+(iDeb+i)*dx[Dir]; yy=y+(iDeb+i)*dy[Dir];
            if (!Recherche) AfficheCase(xx, yy, 15-8*(!(iDeb+i)));
            if (c[xx][yy].Valeur)
             {
              Val=1-2*(c[xx][yy].Joueur!=NumJo);
              if (!Recherche)
               {
                c[xx][yy].Valeur+=Val;
                J[NumJo-1].IncrementeScore(1);
               }
              else
               TotCoefs+=ValNaiss[c[xx][yy].Lettre];
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
               TotCoefs+=ValNaiss[c[xx][yy].Lettre];
             }
           }
          TotPlus+=PtsPlus;
          TotMoins+=PtsMoins;
          TotLtrPrises+=NbLtrPrises;
          if (!Recherche)
           {
            sprintf(Msg, MotForme, Mot[Sens-1], PtsPlus+PtsMoins, PtsMoins, NbLtrPrises);
            if (AFFICHAGE) gm.AfficheMessage(Msg, 15, 1000*J[Jo].Automate); else delay(500);
            for(i=0; i<nl; i++)
             AfficheCase(x+(iDeb+i)*dx[Dir], y+(iDeb+i)*dy[Dir], 0);
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
    sprintf(Msg, BilanPlacemt, NbMots, TotPlus+TotMoins, TotMoins, TotLtrPrises);
    if (AFFICHAGE) gm.AfficheMessage(Msg, 11, 3000-2000*J[Jo].Automate); else delay(500);
   }
  return MotCree;
 }

void plateau::TesteTemps()
 {
  double dt=difftime(time(NULL), TopTour);
  int tt=J[Jo].TpsEcoule+dt, h=tt/3600, m=(tt%3600)/60, s=tt%60;
  gm.AfficheTemps(h, m, s);
 }

void plateau::DepartChrono()
 {
  time(&TopTour);
 }

void plateau::FinChrono()
 {
  double dt=difftime(time(NULL), TopTour);
  int tt=J[Jo].TpsEcoule+dt, h=tt/3600, m=(tt%3600)/60, s=tt%60;
  gm.AfficheTemps(h, m, s);
  J[Jo].TpsEcoule+=dt;
 }

int plateau::Sauve(FILE *f)
 {
  int Bon;
  Bon=(fwrite(c, sizeof(c), 1, f)==1);
  if (Bon) Bon=(fwrite(&NbCasesLibres, sizeof(NbCasesLibres), 1, f)==1);
  if (Bon) Bon=(fwrite(&NbPasseTour, sizeof(NbPasseTour), 1, f)==1);
  return Bon;
 }

int plateau::Charge(FILE *f)
 {
  int Bon;
  Bon=(fread(c, sizeof(c), 1, f)==1);
  if (Bon) Bon=(fread(&NbCasesLibres, sizeof(NbCasesLibres), 1, f)==1);
  if (Bon) Bon=(fread(&NbPasseTour, sizeof(NbPasseTour), 1, f)==1);
  return Bon;
 }
