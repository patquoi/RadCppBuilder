#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "dico.h"

#define NTL 130522L

#define DICO(x) (((x)<65260L)?(Dico1+x):(Dico2+(x-65260L)))

extern unsigned char Dico1[65261L];
extern unsigned char Dico2[65263L];

dico::dico()
 {
  FILE *f=fopen("L23456", "rb");
  unsigned long i, j, t, k, XJauge=0, MoinsUn[5]={0, 0, 1, 1, 0};
  unsigned Code, m26;
  unsigned char Triple[4]="   ";
  Dico1[65260L]=0;
  Dico2[65262L]=0;
  nbl[0]=144L;
  nbl[1]=1467L;
  nbl[2]=8144L;
  nbl[3]=32075L;
  nbl[4]=88692L;
  Indice[0]=0L;
  for(i=1; i<6; i++)
   Indice[i]=Indice[i-1]+nbl[i-1];
  printf("Chargement du dictionnaire - veuillez patienter, SVP...\n\r±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±\r");
  gotoxy(wherex(), wherey()-1);
  _setcursortype(_NOCURSOR);
  if (!f)
   {
    printf("\n\r\aFichier L23456 introuvable\n\r");
    exit(1);
   }
  for(i=0; i<5; i++)
   {
    t=(nbl[i]/3)+MoinsUn[i];
    for(j=0; j<t; j++)
     {
      if (fread(&Code, 2, 1, f)==1)
       {
        m26=676;
        if ((i==3)&&(j==t-2))
         m26=676;
        for(k=0; k<3; k++)
         {
          Triple[k]='A'+Code/m26;
          Code%=m26;
          m26/=26;
         }
        if ((k=Indice[i]+3L*j)<65260L)
         strncpy(Dico1+k, Triple, 3);
        else
         strncpy(Dico2+(k-65260L), Triple, 3);
        if ((80L*k)/NTL>XJauge)
         {
          printf("²");
          XJauge++;
         }
       }
      else
       {
        printf("\n\r\aErreur de lecture\n\r");
        exit(1);
       }
     }
   }
  printf("²");
  _setcursortype(_NORMALCURSOR);
 }

dico::Existe(unsigned char *Mot, unsigned Taille)
 {
  char MotCrt[7];
  int Comp;
  unsigned long iInf=0,
                iSup=nbl[Taille-2]/(unsigned long)(Taille)-1L,
                iMil=(iInf+iSup)/2;
  Comp=strncmp(DICO(Indice[Taille-2]+iMil*(unsigned long)Taille), Mot, Taille);
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
    strncpy(MotCrt, DICO(Indice[Taille-2]+iMil*(unsigned long)Taille), Taille);
    Comp=strncmp(DICO(Indice[Taille-2]+iMil*(unsigned long)Taille), Mot, Taille);
   }
  return (!Comp);
 }
