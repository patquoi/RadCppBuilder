#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <mem.h>
#include <dos.h>
#include "affgraph.h"
#include "joueur.h"
#include "mouse.h"
#include "plateau.h"

// Contexte pour GereES()
#define CHOIX_LETTRE 0
#define PLCMT_LETTRE 1

// Interrupteur Avec ou Sans Son pour AfficheTexte
#define SANSSON      0
#define AVECSON      1

// Messages de relance systŠme pour fenetre::Relancement
#define IGNORE  0
#define RETRY   1
#define ABORT   2


extern joueur J[6];
extern mouse m;
extern plateau p;

extern unsigned char Msg[480];

extern unsigned Jo, nbj, Tour, TpsReflexion, AffMsgPartie;

unsigned Digit[10][7]={{1,1,1,1,1,0,1},
                       {0,1,0,1,0,0,0},
                       {0,1,1,0,1,1,1},
                       {0,1,0,1,1,1,1},
                       {1,1,0,1,0,1,0},
                       {1,0,0,1,1,1,1},
                       {1,0,1,1,1,1,1},
                       {0,1,0,1,1,0,0},
                       {1,1,1,1,1,1,1},
                       {1,1,0,1,1,1,1}};

unsigned XDigit[7][2]={{0,0},{2,2},{0,0},{2,2},{0,2},{0,2},{0,2}},
         YDigit[7][2]={{0,2},{0,2},{2,4},{2,4},{0,0},{2,2},{4,4}};

unsigned char RGB[48]={0,0,0,0,0,42,0,42,0,0,42,42,42,0,0,42,0,42,42,21,0,42,42,42,21,21,21,21,21,63,21,63,21,21,63,63,63,21,21,63,21,63,63,63,21,63,63,63},
              Matrice[8]={ 62, 221, 227, 221,  62, 221, 227, 221},
              MatChf[10][8]={{124, 198, 198, 198, 198, 198, 124,   0},
                             { 24,  56,  24,  24,  24,  24, 126,   0},
                             {124, 198,   6, 124, 192, 192, 254,   0},
                             {124, 198,   6,  60,   6, 198, 124,   0},
                             { 12,  28,  60, 108, 254,  12,  12,   0},
                             {254, 192, 192, 252,   6, 198, 124,   0},
                             {124, 198, 192, 252, 198, 198, 124,   0},
                             {254,   6,  12,  24,  48,  96, 192,   0},
                             {124, 198, 198, 124, 198, 198, 124,   0},
                             {124, 198, 198, 126,   6, 198, 124,   0}},
              QuestionES1[]="Voulez-vous Quitter le jeu,\nRecommencer le choix d'une lettre, Passer votre tour,\nr‚gler la Dur‚e de r‚flexion, les aFfichages,\nSauver, Charger ou Annuler (Q/R/P/D/F/S/C/A) ?",
              QuestionES2[]="Voulez-vous Quitter le jeu,\nPasser votre tour,\nr‚gler la Dur‚e de r‚flexion, les aFfichages,\nSauver, Charger ou Annuler (Q/P/D/F/S/C/A) ?",
              QstTpsReflexion[]="Temps actuel : %d mn/joueur.\nTemps … r‚partir par joueur :\n1, 2, 5 ou 10 heures (1/2/5/X) ?",
              QstAffPartie[]="Affichage actuel : %s.\nAfficher les messages pendant la partie :\nToujours, Jamais, pas pour les Automates (T/J/A) ?",
              szAffPartie[3][24]={"Jamais", "Toujours", "Pas pour les automates"},
              ImpossiblePasser[]="Vous ne pouvez pas passer le premier tour !",
              AnnulerQuitter[]="Voulez-vous Annuler ou Quitter le jeu (A/Q) ?",
              HMS[]=" :  :  ",
              ErreurSysteme[]="ERREUR SYSTEME :\n%s\nRecommencer, Ignorer ou Abandonner (R/I/A) ?",
              QuitterJeu[]="Voulez-vous quitter le jeu (O/N) ?",
              ErrSyst[17][34]={"Unit‚ prot‚g‚e contre l'‚criture",
                               "Unit‚ inconnue",
                               "Unit‚ non prˆte",
                               "Commande inconnue",
                               "Erreur de donn‚es (CRC)",
                               "Mauvaise requˆte",
                               "Erreur de recherche",
                               "Type de support inconnu",
                               "Secteur non trouv‚",
                               "L'imprimante n'a plus de papier",
                               "Erreur d'‚criture",
                               "Erreur de lecture",
                               "Echec g‚n‚ral",
                               "*** r‚serv‚ ***",
                               "*** r‚serv‚ ***",
                               "Changement de disquette invalide",
                               "Erreur de p‚riph‚rique"};


graphmode::graphmode()
 {
  long i;
  int YCirc[6]={31, 10, 1, 1, 10, 31},
      TAE[2][4]={{0,1,3,4},{0,1,2,5}},
      Epais[6]={9, 1, -1, -1, 1, 9};
  if (registerfarbgidriver(EGAVGA_driver_far)<0)
   {
    printf("\aErreur d'initialisation\n");
    exit(1);
   }
  initgraph(&pg, &mg, "");
  if ((pg!=VGA)&&(mg!=VGAHI))
   {
    printf("\aEcran VGA 640x480 16 couleurs requis\n\r");
    exit(1);
   }
  Palette(0);
  setcolor(7);
  for(i=0; i<2; i++)
   circle(320, 240, 20+40*(4-i));
  for(i=0; i<2; i++)
   line(141, 220+40*i, 499, 220+40*i);
  for(i=0; i<6; i++)
   line(220+40*i, 60+YCirc[i], 220+40*i, 420-YCirc[i]);
  setcolor(0);
  setfillstyle(0, 0);
  for(i=0; i<2; i++)
   {
    line(180+i, 221, 180+i, 259);
    line(182, 220+40*i, 219, 220+40*i);
    line(221, 220+40*i, 259, 220+40*i);
    line(261, 220+40*i, 299, 220+40*i);
    line(341, 220+40*i, 379, 220+40*i);
    line(381, 220+40*i, 419, 220+40*i);
    line(421, 220+40*i, 458, 220+40*i);
    line(460, 260, 498, 260);
    line(300+40*i, 221, 300+40*i, 259);
   }
  for(i=0; i<4; i++)
   {
    line(220+40*TAE[0][i], 61+YCirc[TAE[0][i]], 220+40*TAE[0][i], 101+YCirc[TAE[0][i]]+Epais[TAE[0][i]]);
    line(220+40*TAE[1][i], 419-YCirc[TAE[1][i]], 220+40*TAE[1][i], 379-YCirc[TAE[1][i]]-Epais[TAE[1][i]]);
   }
  for(i=0; i<2; i++)
   {
    bar(221+160*i,
        101+YCirc[0]+Epais[0],
        259+160*i,
        101+YCirc[1]+Epais[1]);
    bar(221+160*i,
        379-YCirc[1]-Epais[1],
        259+160*i,
        379-YCirc[0]-Epais[0]);
   }
  bar(341,
      379-YCirc[2]-Epais[2],
      379,
      378-YCirc[1]-Epais[1]);
  bar(421, 101+YCirc[TAE[0][0]]+Epais[TAE[0][0]], 460, 219);
  for(i=0; i<2; i++)
   bar(301, 100+279*i, 339, 101+279*i);
  setcolor(7);
  for(i=0; i<2; i++)
   line(360-80*i, 65+309*i, 360-80*i, 106+309*i);

  // Colorisation par remplissage...
  setfillstyle(6,  9); floodfill(240, 240, 7);
  setfillstyle(6, 10); floodfill(280, 240, 7);
  setfillstyle(6, 13); floodfill(320, 200, 7); floodfill(320, 280, 7);
  setfillstyle(6, 12); floodfill(400, 240, 7);

  for(i=0; i<8; i++)
   {
    setrgbpalette( 9, (RGB[27]*i)/7, (RGB[28]*i)/7,(RGB[29]*i)/7);
    delay(25);
   }
  for(i=0; i<8; i++)
   {
    setrgbpalette(10, (RGB[30]*i)/7, (RGB[31]*i)/7,(RGB[32]*i)/7);
    setrgbpalette( 9, (RGB[27]*(7-i))/7, (RGB[28]*(7-i))/7,(RGB[29]*(7-i))/7);
    delay(25);
   }
  for(i=0; i<8; i++)
   {
    setrgbpalette(13, (RGB[39]*i)/7, (RGB[40]*i)/7,(RGB[41]*i)/7);
    setrgbpalette(10, (RGB[30]*(7-i))/7, (RGB[31]*(7-i))/7,(RGB[32]*(7-i))/7);
    delay(25);
   }
  for(i=0; i<8; i++)
   {
    setrgbpalette(12, (RGB[36]*i)/7, (RGB[37]*i)/7,(RGB[38]*i)/7);
    setrgbpalette(13, (RGB[39]*(7-i))/7, (RGB[40]*(7-i))/7,(RGB[41]*(7-i))/7);
    delay(25);
   }
  for(i=7; i>-1; i--)
   {
    setrgbpalette(12, (RGB[36]*i)/7, (RGB[37]*i)/7,(RGB[38]*i)/7);
    delay(25);
   }
  for(i=0; i<19; i++)
   {
    if (i<8)
     setrgbpalette( 9, (RGB[27]*i)/7, (RGB[28]*i)/7,(RGB[29]*i)/7);
    if ((i>3)&&(i<11))
     setrgbpalette(10, (RGB[30]*(i-3))/7, (RGB[31]*(i-3))/7,(RGB[32]*(i-3))/7);
    if ((i>7)&&(i<15))
     setrgbpalette(13, (RGB[39]*(i-7))/7, (RGB[40]*(i-7))/7,(RGB[41]*(i-7))/7);
    if (i>11)
     setrgbpalette(12, (RGB[36]*(i-11))/7, (RGB[37]*(i-11))/7,(RGB[38]*(i-11))/7);
    delay(25);
   }
  delay(1000);
  for(i=7; i>-1; i--)
   {
    setrgbpalette( 9, (RGB[27]*i)/7, (RGB[28]*i)/7,(RGB[29]*i)/7);
    setrgbpalette(10, (RGB[30]*i)/7, (RGB[31]*i)/7,(RGB[32]*i)/7);
    setrgbpalette(13, (RGB[39]*i)/7, (RGB[40]*i)/7,(RGB[41]*i)/7);
    setrgbpalette(12, (RGB[36]*i)/7, (RGB[37]*i)/7,(RGB[38]*i)/7);
   }
  cleardevice();
  Palette(1);
  setactivepage(1);
  DessineHexagone(10, 0, 15);
  getimage(0, 0, 38, 32, BufCurs);
  setactivepage(0);
  settextjustify(1, 1);
  settextstyle(0, 0, 2);
  setfillpattern(Matrice, 8);
  bar(0, 0, 639, 479);
  setmem(Msg, sizeof(Msg), 0);
  Horloge=0;
 }

void graphmode::Palette(int OnOff)
 {
  int i;
  struct REGPACK r;
  if (OnOff)
   {
    r.r_ax=0x1012;
    r.r_bx=0x0000;
    r.r_cx=0x0010;
    r.r_es=(unsigned long)(RGB)/65536L;
    r.r_dx=(unsigned)(RGB);
    intr(0x10, &r);
   }
  else
   for(i=0; i<16; i++)
    {
     setrgbpalette(i, 0, 0, 0);
     setpalette(i, i);
    }
 }

void graphmode::SaisitChaine(char *Texte, char Chaine[], int LgMax, int Couleur)
 {
  int i=0, Fin=0;
  char Touche[2]=" ", Curseur[2]="Û";
  OuvreFenetre(Couleur);
  AfficheTexte(Texte, Couleur, AVECSON);
  setcolor(Couleur-6*(Couleur==9));
  setfillstyle(1, Couleur-8);
  settextstyle(0, 0, 0);
  outtextxy(96, 472, Curseur);
  Chaine[0]=0;
  do
   {
    if (!(Touche[0]=getch()))
     getch();
    strupr(Touche);
    if ((i<LgMax)&&(Touche[0]>31))
     {
      Chaine[i]=Touche[0];
      setcolor(Couleur-8); outtextxy(96+8*i, 472, Curseur);
      setcolor(Couleur-6*(Couleur==9)); outtextxy(96+8*i, 472, Touche);
      outtextxy(104+8*i, 472, Curseur);
      i++;
     }
    else
     {
      switch(Touche[0])
       {
        case 13: Chaine[i]=0; Fin=1; break;
        case 8 : if (i)
                  {
                   setcolor(Couleur-8); outtextxy(96+8*i, 472, Curseur);
                   setcolor(Couleur-6*(Couleur==9)); outtextxy(96+8*(--i), 472, Curseur);
                  }
                 break;
        case 27: Chaine[0]=0;
                 FermeFenetre();
                 Touche[0]=PoseQuestion(AnnulerQuitter, "qQaA\x1B", 12);
                 strupr(Touche);
                 FermeFenetre();
                 Fin=1;
                 if (Touche[0]=='Q')
                  {
                   textmode(3);
                   printf("\nBen pourquoi ?");
                   exit(0);
                  }
                 break;
        default: break;
       }
     }
   }
  while(!Fin);
  FermeFenetre();
  settextstyle(0, 0, 2);
 }

void graphmode::DessineHexagone(int x, int y, int c)
 {
  int i;
  int h[12]={0, 0, 18, 0, 28, 16, 18, 32, 0, 32, -10, 16};
  setcolor(c-(c==8));
  setfillstyle(c<15, (c<15)*(c-(c==8)));
  for(i=0; i<6; i++)
   {
    h[2*i]+=x;
    h[2*i+1]+=y;
   }
  fillpoly(6, h);
  setcolor(15*(c>7)+(c+8)*(c<8));
  moveto(x, y);
  for(i=1; i<4; i++)
   lineto(h[2*i], h[2*i+1]);
  setcolor(8*((c==8)||(c==15))+(c-8)*(c>8));
  for(i=4; i<6; i++)
   lineto(h[2*i], h[2*i+1]);
 }

void graphmode::DessinePlateau()
 {
  int i, j, x, y;
  char Chiffre[3]="  ";
  for(j=0; j<6; j++)
   for(i=0; i<j+1; i++)
    DessineHexagone(316+60*i-30*j, 54+17*j, 8);
  for(j=0; j<9; j++)
   for(i=0; i<5+(j%2); i++)
    DessineHexagone(196+60*i-30*(j%2), 156+17*j, 8);
  for(j=0; j<6; j++)
   for(i=0; i<6-j; i++)
    DessineHexagone(166+60*i+30*j, 309+17*j, 8);
  settextstyle(0, 0, 0);
  for(i=0; i<11; i++)
   {
    if (i==10) Chiffre[0]=49;
    Chiffre[i>9]=48+i%10;
    setcolor(1);
    outtextxy(x=305-4*(i==10)-30*((i<5)*i+5*(i>=5)), y=59+17*i+17*(i-5)*(i>5), Chiffre);
    setcolor(9); outtextxy(x+1, y-1, Chiffre);
    setcolor(4); outtextxy(657-x-8*(i==10), y, Chiffre);
    setcolor(12); outtextxy(658-x-8*(i==10), y-1, Chiffre);
   }
  settextstyle(0, 0, 2);
 }

void graphmode::AfficheValeur(unsigned x, unsigned y, unsigned l, unsigned v, unsigned Coul)
 {
  unsigned char Lettre[2]=" ";
  unsigned i, Enfonce=(Coul>0), CoulFond=getpixel(x+14, y+2);
  if (l)
   {
    Lettre[0]=64+l;
    setcolor(CoulFond);
    outtextxy(x+15-!Enfonce, y+13+!Enfonce, Lettre);
    setcolor(Coul);
    outtextxy(x+15-Enfonce, y+13+Enfonce, Lettre);
    setcolor(CoulFond);
    for(i=0; i<7; i++)
     {
      if (Digit[v/10][i])
       line(x+11+XDigit[i][0]-!Enfonce, y+23+YDigit[i][0]+!Enfonce, x+11+XDigit[i][1]-!Enfonce, y+23+YDigit[i][1]+!Enfonce);
      if (Digit[v%10][i])
       line(x+15+XDigit[i][0]-!Enfonce, y+23+YDigit[i][0]+!Enfonce, x+15+XDigit[i][1]-!Enfonce, y+23+YDigit[i][1]+!Enfonce);
     }
    setcolor(Coul);
    for(i=0; i<7; i++)
     {
      if (Digit[v/10][i])
       line(x+11+XDigit[i][0]-Enfonce, y+23+YDigit[i][0]+Enfonce, x+11+XDigit[i][1]-Enfonce, y+23+YDigit[i][1]+Enfonce);
      if (Digit[v%10][i])
       line(x+15+XDigit[i][0]-Enfonce, y+23+YDigit[i][0]+Enfonce, x+15+XDigit[i][1]-Enfonce, y+23+YDigit[i][1]+Enfonce);
     }
   }
 }

void graphmode::OuvreFenetre(int Couleur)
 {
  int i;
  setcolor(Couleur);
  setfillstyle(1, Couleur-8);
  for(i=0; i<25; i++)
   {
    bar(320-10*i, 455-i, 319+10*i, 455+i);
    delay(4);
   }
  rectangle(80, 431, 559, 479);
  nosound();
 }

void graphmode::FermeFenetre()
 {
  int i;
  setcolor(0);
  setfillpattern(Matrice, 8);
  for(i=24; i>-1; i--)
   {
    bar(320-10*i, 455-i, 319+10*i, 455-i);
    bar(320-10*i, 455+i, 319+10*i, 455+i);
    bar(320-10*i, 455-i, 319-10*(i-1), 455+i);
    bar(320+10*(i-1), 455-i, 319+10*i, 455+i);
    delay(4);
   }
 }

void graphmode::AfficheTexte(char *Texte, int Couleur, int AvecSon)
 {
  char *PtrDeb=Texte, *PtrFin=Texte;
  int PasFini=1, Ligne=0, Interligne, i=0, n=0, DerLig=0, NbCarMax=58, p2=1, MemCoupe=0;
  while(PasFini)
   {
    while(Texte[i]&&(Texte[i]!='\n')&&(i-DerLig-1<=NbCarMax))
     {
      i++;
      while(Texte[i]&&(Texte[i]!=32)&&(Texte[i]!='\n')) i++;
      if (i-DerLig-1<=NbCarMax) n=i;
     }
    PasFini=Texte[i];
    Ligne+=((!PasFini)&&(i-DerLig-1>NbCarMax));
    DerLig=n;
    PtrFin=Texte+n;
    MemCoupe+=p2*(Texte[n]=='\n'); p2*=1+(Texte[n]>0);
    Texte[n]=0;
    n++;
    i=n; Ligne++;
    if (PasFini) PtrDeb=PtrFin+1;
   }
  PtrDeb=Texte; PtrFin=Texte;
  Interligne=8+(48-8*Ligne)/(Ligne+1);
  settextstyle(0, 0, 0);
  if (AvecSon) sound(1760);
  for(i=0; i<Ligne; i++)
   {
    n=strlen(PtrFin);
    setcolor(15*(!Couleur));
    outtextxy(320, 428+(i+1)*Interligne, PtrDeb);
    setcolor(Couleur-6*(Couleur==9));
    outtextxy(321, 427+(i+1)*Interligne, PtrDeb);
    if (i<Ligne-1)
     {
      p2/=2;
      PtrFin[n]=32-22*(MemCoupe/p2>0);
      MemCoupe%=p2;
     }
    n++;
    PtrFin+=n;
    PtrDeb=PtrFin;
   }
  if (AvecSon) nosound();
  settextstyle(0, 0, 2);
 }

void graphmode::AfficheMessage(unsigned char *Texte, unsigned Couleur, unsigned Delai)
 {
  char Rep;
  int i;
  unsigned bg, bd, bm, b=0, g=0, d=0;
  OuvreFenetre(Couleur);
  AfficheTexte(Texte, Couleur, SANSSON);
  if (!Delai)
   {
    m.RepeatUntilNoPress();
    while(!m.ButtonPressed())
     if (Horloge)
      p.TesteTemps();
   }
  else
   {
    m.RepeatUntilNoPress();
    for(i=0; (!b)&&(i<Delai/100); i++)
     {
      delay(100);
      m.GetButtons(&bg, &bd, &bm);
      if (b=b||bg||bd)
       {
        while(m.ButtonPressed())
         {
          m.GetButtons(&bg, &bd, &bm);
          if (Horloge)
           p.TesteTemps();
          g=g||bg;
          d=d||bd;
         }
       }
      if (Horloge)
       p.TesteTemps();
     }
    if (g&&d)
     {
      FermeFenetre();
      Rep=PoseQuestion(QuitterJeu, "OoNn", 12);
      if ((Rep=='o')||(Rep=='O'))
       {
        textmode(3);
        printf("\nBen pourquoi ?");
        exit(0);
       }
     }
   }
  FermeFenetre();
 }

char graphmode::PoseQuestion(unsigned char *Qst, unsigned char *RepDmd, unsigned Couleur)
 {
  char Touche=0;
  int PasFini=1, i=0;
  OuvreFenetre(Couleur);
  AfficheTexte(Qst, Couleur, AVECSON);
  PasFini=1;
  while(kbhit())
   if (!getch())
    getch();
  while(PasFini)
   {
    while(!kbhit())
     if (Horloge)
      p.TesteTemps();
    if (!(Touche=getch()))
     Touche=getch();
    for(i=0; (PasFini=(Touche!=RepDmd[i]))&&(i<strlen(RepDmd)); i++);
   }
  setcolor(0);
  setfillpattern(Matrice, 8);
  for(i=24; i>-1; i--)
   {
    bar(320-10*i, 455-i, 319+10*i, 455-i);
    bar(320-10*i, 455+i, 319+10*i, 455+i);
    bar(320-10*i, 455-i, 319-10*(i-1), 455+i);
    bar(320+10*(i-1), 455-i, 319+10*i, 455+i);
    delay(4);
   }
  return Touche;
 }

void graphmode::AfficheScore(int NumJo, int Score)
 {
  int xDeb=8+64*NumJo+8*((680-64*nbj)/16), Couleur=9+NumJo-6*(!NumJo);
  setfillpattern(MatChf[Score/100], Couleur); bar(xDeb, 24, xDeb+7, 31);
  setfillpattern(MatChf[(Score%100)/10], Couleur); bar(xDeb+8, 24, xDeb+15, 31);
  setfillpattern(MatChf[Score%10], Couleur); bar(xDeb+16, 24, xDeb+23, 31);
 }

void graphmode::AfficheTemps(int h, int m, int s)
 {
  static int hs=99, ms=99, ss=99, js=9;
  int Debut=(Jo!=js), xDeb=8+64*Jo+8*((648-64*nbj)/16), Couleur=9+Jo-6*(!Jo);
  if (Debut)
   {
    setcolor(Couleur);
    settextstyle(0, 0, 0);
    outtextxy(27+xDeb, 44, HMS);
    settextstyle(0, 0, 2);
    js=Jo;
    hs=9; ms=99; ss=99;
   }
  if (h!=hs)
   {
    setfillpattern(MatChf[h%10], Couleur); bar(xDeb   , 40, xDeb+ 7, 47);
    hs=h;
   }
  if (m!=ms)
   {
    setfillpattern(MatChf[m/10], Couleur); bar(xDeb+16, 40, xDeb+23, 47);
    setfillpattern(MatChf[m%10], Couleur); bar(xDeb+24, 40, xDeb+31, 47);
    ms=m;
   }
  if (s!=ss)
   {
    setfillpattern(MatChf[s/10], Couleur); bar(xDeb+40, 40, xDeb+47, 47);
    setfillpattern(MatChf[s%10], Couleur); bar(xDeb+48, 40, xDeb+55, 47);
    ss=s;
   }
 }

void graphmode::AfficheClassement(int j, int v, int Coul)
 {
  int i, x=8*((680-64*nbj)/16)+64*j-10;
  setcolor(0);
  for(i=0; i<7; i++)
   line(x+XDigit[i][0], 25+YDigit[i][0], x+XDigit[i][1], 25+YDigit[i][1]);
  setcolor(Coul);
  for(i=0; i<7; i++)
   if (Digit[v][i])
    line(x+XDigit[i][0], 25+YDigit[i][0], x+XDigit[i][1], 25+YDigit[i][1]);
 }

char graphmode::GereES(int Contexte)
 {
  char szMsgQst[128], Rep, Bon;
  while(kbhit())
   if (!getch())
    getch();
  do
   {
    Bon=1;
    switch(Rep=PoseQuestion((Contexte==1)?QuestionES1:QuestionES2, (Contexte==1)?"QqRrPpDdSsFfCcAa\x1B":"QqPpDdSsFfCcAa\x1B", 12))
     {
      case 'q':
      case 'Q': textmode(3);
                printf("Ben pourquoi ?\n");
                exit(0);
                break;
      case 'p':
      case 'P': Bon=(Tour>0);
                if (!Bon)
                 {
                  sound(440);
                  AfficheMessage(ImpossiblePasser, 13, 0);
                 }
                break;
      case 'd':
      case 'D': sprintf(szMsgQst, QstTpsReflexion, TpsReflexion/nbj/60);
                switch(PoseQuestion(szMsgQst, "125xX\x1B", 10))
                 {
                  case '1': TpsReflexion=3600; break;
                  case '2': TpsReflexion=7200; break;
                  case '5': TpsReflexion=18000; break;
                  case 'x':
                  case 'X': TpsReflexion=36000; break;
                  case '\x1B': break;
                 }
                break;
      case 'f':
      case 'F': sprintf(szMsgQst, QstAffPartie, szAffPartie[AffMsgPartie]);
                switch(PoseQuestion(szMsgQst, "tTjJaA\x1B", 10))
                 {
                  case 't':
                  case 'T': AffMsgPartie=1; break;
                  case 'a':
                  case 'A': AffMsgPartie=2; break;
                  case 'j':
                  case 'J': AffMsgPartie=0; break;
                  case '\x1B': break;
                 }
                break;
      case '\x1B': Rep='a'; break;
      default : break;
     }
   }
  while(!Bon);
  return Rep;
 }

int graphmode::Relancement(int Erreur)
 {
  int Code=0;
  sprintf(Msg, ErreurSysteme, ErrSyst[Erreur]);
  switch(PoseQuestion(Msg, "rRiIaA", 12))
   {
    case 'r':
    case 'R': Code=RETRY; break;
    case 'i':
    case 'I': Code=IGNORE; break;
    case 'a':
    case 'A': Code=ABORT; break;
    default : break;
   }
  return Code;
 }

void graphmode::ReinitialiseEcran()
 {
  int xx, i, h, m, s;
  setfillpattern(Matrice, 8);
  bar(128, 0, 514, 52);
  for(i=0; i<nbj; i++)
   {
    xx=8*((680-64*nbj)/16)+64*i-11;
    setcolor(9+i-6*(!i));
    setfillstyle(0, 0);
    bar(xx,  5, xx+60, 17);
    bar(xx, 21, xx+60, 33);
    bar(xx, 37, xx+60, 49);
    rectangle(xx-1,  4, xx+61, 18);
    rectangle(xx-1, 20, xx+61, 34);
    rectangle(xx-1, 36, xx+61, 50);
    xx=28+64*i+8*((680-64*nbj)/16);
    settextstyle(0, 0, 0);
    setcolor(i+1); outtextxy(xx-8, 11, J[i].Nom);
    setcolor(i+9-6*(!i)); outtextxy(xx-9, 12, J[i].Nom);
    J[i].IncrementeScore(0);
    xx=J[i].TpsEcoule;
    h=xx/3600; m=(xx%3600)/60; s=xx%60;
    xx=8+64*i+8*((648-64*nbj)/16);
    setcolor(9+i-6*(!i));
    outtextxy(27+xx, 44, HMS);
    settextstyle(0, 0, 2);
    setfillpattern(MatChf[h%10], 9+i-6*(!i)); bar(xx   , 40, xx+ 7, 47);
    setfillpattern(MatChf[m/10], 9+i-6*(!i)); bar(xx+16, 40, xx+23, 47);
    setfillpattern(MatChf[m%10], 9+i-6*(!i)); bar(xx+24, 40, xx+31, 47);
    setfillpattern(MatChf[s/10], 9+i-6*(!i)); bar(xx+40, 40, xx+47, 47);
    setfillpattern(MatChf[s%10], 9+i-6*(!i)); bar(xx+48, 40, xx+55, 47);
   }
  p.AffichePlateau();
  J[Jo].AfficheLettresDisp();
 }
