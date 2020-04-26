#include <string.h>
#include <graphics.h>
#include "joueur.h"
#include "affgraph.h"
#include "mouse.h"
#include "plateau.h"

extern graphmode gm;
extern mouse m;
extern joueur J[6];
extern plateau p;

extern int nbj;

extern unsigned char Msg[480];

unsigned char EntrezNom[]="Entrez le nom du joueur %d :\n\n ",
              AutomateON[]="Automate (O/N) ?";

joueur::joueur(unsigned NumJo)
 {
  int i;
  Rang=NumJo;
  for(i=1; i<27; i++) Nombre[i]=1;
  Nombre[0]=26;
  Automate=0;
  Score=0;
  TpsEcoule=0.0;
 }

void joueur::Reinitialise(unsigned char NvNom[8], int Auto)
 {
  int i;
  strcpy(Nom, NvNom);
  for(i=1; i<27; i++) Nombre[i]=1;
  Nombre[0]=26;
  Automate=Auto;
  Score=0;
  TpsEcoule=0.0;
 }

void joueur::DefPrmCase(unsigned x, unsigned y)
 {
  CoordDeb[0]=x;
  CoordDeb[1]=y;
 }

void joueur::SaisitNom()
 {
  char Rep;
  int xx=28+64*Rang+8*((680-64*nbj)/16), yy=12, i;
  do
   {
    sprintf(Msg, EntrezNom, Rang+1);
    gm.SaisitChaine(Msg, Nom, 7, Rang+9);
   }
  while(!Nom[0]);
  Rep=gm.PoseQuestion(AutomateON, "OoNn", Rang+9);
  Automate=(Rep=='o')||(Rep=='O');
  settextstyle(0, 0, 0);
  for(i=15; i!=2*Rang+3; i-=(6-Rang))
   {
    setcolor(i-8); outtextxy(xx-8, yy-1, Nom);
    setcolor(i-6*(i==9));   outtextxy(xx-9, yy, Nom);
    delay(250);
   }
  settextstyle(0, 0, 2);
 }

void joueur::AfficheLettresDisp()
 {
  unsigned i;
  for(i=0; i<26; i++)
   {
    gm.DessineHexagone(610-30*(i%2), 17*i, 8+(Nombre[i+1]>0)*(Rang+1));
    gm.AfficheValeur(605-30*(i%2), 17*i, i+1, Nombre[i+1], 0);
   }
 }

unsigned joueur::ChoixLettre()
 {
  unsigned Lettre, Col, Lig, xm, ym, xcAnc, ycAnc, xc, yc, bg, bd, bm, g, d;
  for(Lettre=1; !Nombre[Lettre]; Lettre++);
  Lig=Lettre-1;
  Col=Lettre%2;
  xcAnc=xc=575+30*Col;
  ycAnc=yc=17*Lig;
  m.CursorOn();
  m.SetMouseCursor(0, 0, 3);
  m.MoveMouse(xc+14, yc+12);
  m.WinMouse(570, 17, 639, 441);
  m.CursorOff();
  gm.AfficheValeur(xc, yc, Lettre, Nombre[Lettre], Rang+1);
  putimage(xc-5, yc, gm.BufCurs, XOR_PUT);
  m.CursorOn();
  m.RepeatUntilNoPress();
  do
   {
    p.TesteTemps();
    m.GetMouse(&xm, &ym, &bg, &bd, &bm);
    g=bg;
    d=bd;
    Col=(xm>602);
    Lig=!(Col%2)+2*((ym-17*(!(Col%2)))/34);
    xc=575+30*(Col%2);
    yc=17*Lig;
    if (((xcAnc!=xc)||(ycAnc!=yc))&&Nombre[Lig+1])
     {
      m.CursorOff();
      gm.AfficheValeur(xcAnc, ycAnc, Lettre, Nombre[Lettre], 0);
      putimage(xcAnc-5, ycAnc, gm.BufCurs, 1);
      Lettre=Lig+1;
      gm.AfficheValeur(xc, yc, Lettre, Nombre[Lettre], Rang+1);
      putimage(xc-5, yc, gm.BufCurs, 1);
      m.CursorOn();
      xcAnc=xc;
      ycAnc=yc;
     }
    else
     {
      xc=xcAnc;
      yc=ycAnc;
     }
   }
  while((!bg)&&(!bd));
  do // On attend que tous les boutons soient lƒch‚s...
   {
    p.TesteTemps();
    m.GetButtons(&bg, &bd, &bm);
    g=g||bg;
    d=d||bd;
   }
  while(bg||bd);
  m.WinMouse(0, 0, 639, 479);
  m.CursorOff();
  if (!(g&&d))
   {
    Nombre[Lettre]--;
    Nombre[0]--;
   }
  putimage(xc-5, yc, gm.BufCurs, 1);
  gm.DessineHexagone(xc+5, yc, 8+(Nombre[Lettre]>0)*(Rang+1));
  gm.AfficheValeur(xc, yc, Lettre, Nombre[Lettre], 0);
  m.CursorOn();
  return ((!(g&&d))*Lettre);
 }

void joueur::IncrementeScore(int Points)
 {
  int xx, yy, i, j, n, cl[6], nj[6], np[6], NbjSvt=(nbj>=2)+(nbj>=3)+(nbj>=6);
  Score+=Points;
  gm.AfficheScore(Rang, Score);
  if (Points)
   {
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
    for(n=i=0; i<nbj; i++)
     for(j=0; j<nbj; j++)
      if (cl[j]==i+1)
       {
        gm.AfficheClassement(j, i+1, 15-3*(n<NbjSvt));
        if (n<3) n++;
       }
   }
 }

int joueur::Sauve(FILE *f)
 {
  int Bon;
  Bon=(fwrite(Nom, sizeof(Nom), 1, f)==1);
  if (Bon) Bon=(fwrite(CoordDeb, sizeof(CoordDeb), 1, f)==1);
  if (Bon) Bon=(fwrite(Nombre, sizeof(Nombre), 1, f)==1);
  if (Bon) Bon=(fwrite(&Automate, sizeof(Automate), 1, f)==1);
  if (Bon) Bon=(fwrite(&Score, sizeof(Score), 1, f)==1);
  if (Bon) Bon=(fwrite(&TpsEcoule, sizeof(TpsEcoule), 1, f)==1);
  return Bon;
 }

int joueur::Charge(FILE *f)
 {
  int Bon;
  Bon=(fread(Nom, sizeof(Nom), 1, f)==1);
  if (Bon) Bon=(fread(CoordDeb, sizeof(CoordDeb), 1, f)==1);
  if (Bon) Bon=(fread(Nombre, sizeof(Nombre), 1, f)==1);
  if (Bon) Bon=(fread(&Automate, sizeof(Automate), 1, f)==1);
  if (Bon) Bon=(fread(&Score, sizeof(Score), 1, f)==1);
  if (Bon) Bon=(fread(&TpsEcoule, sizeof(TpsEcoule), 1, f)==1);
  return Bon;
 }

