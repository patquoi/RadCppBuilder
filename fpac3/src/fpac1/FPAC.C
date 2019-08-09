#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <mem.h>
#include <math.h>

// PACMAN:

// à â  1, 3    ^ v   224, 226

// ä è  5, 9    ^ |   228, 232
// å é  6, 10   | v   229, 233

// áæç  2, 7|8  > ->  225, 230|231
//
// ãêë  4,11|12 < <-  227, 234|235

// ì    13 (pac, bouche ferm‚e) 236

// fant“mes:

// ñ (entier)

//   ^
// ò |
// ó |
//   v

// õô <-->

// Code ASCII des caractŠres red‚finis

#define MAXFANTOMES 10

#define PHAUT    224
#define PDROITE  225
#define PBAS     226
#define PGAUCHE  227
#define PHAUT1   228
#define PHAUT2   229
#define PDROITE1 230
#define PDROITE2 231
#define PBAS1    232
#define PBAS2    233
#define PGAUCHE1 234
#define PGAUCHE2 235
#define PBOULE   236
#define FENTIER  241
#define FVER1    242
#define FVER2    243
#define FHOR1    244
#define FHOR2    245

#define VERTICAL   0
#define HORIZONTAL 1

#define VIDE    0
#define GRAINE  1
#define PILULE  2
#define MUR     3

// ‚tats fant“mes
#define MANGE      0
#define ENFUITE    1
#define TRANSITION 2
#define ENCHASSE   3

#define ENVMIN  3

#define NORD     0
#define EST      1
#define SUD      2
#define OUEST    3
#define INDEFINI 4

// touches

#define GAUCHE  75
#define DROITE  77
#define HAUT    72
#define BAS     80
#define ECHAP   27

#define INFINI  32767


// Sons

#define SANSSON  0
#define SGRAINE  1
#define SPILULE  2
#define SFANTOME 3
#define SPAC     4
#define SBONUS   5

#define GOTOXY(x, y) Gotoxy((x)-1, (y)-1)

#define PORTE(x, y)  (Table[x][y]<255)


// File de portes

#define NUMERO 0
#define BUT    1

// Codes blocage

#define FANTOME  1
#define PAC      2
#define BONUS    4
#define ZONE     8

const unsigned Frq[2][5]={{220, 440, 880, 1760, 3520}, {311, 622, 1244, 2488, 4977}};
const int dx[5]={0, 1, 0, -1, 0},
          dy[5]={-1, 0, 1, 0, 0};

const unsigned ColFtm[4]={0, 3, 131, 15};
const unsigned CarFtm[4][2]={{FVER2, FVER1}, {FHOR2, FHOR1}, {FVER1, FVER2}, {FHOR1, FHOR2}};
const unsigned CarPac[4][2]={{PHAUT2, PHAUT1}, {PDROITE1, PDROITE2}, {PBAS1, PBAS2}, {PGAUCHE2, PGAUCHE1}};
const unsigned CarPac2[4]={PHAUT, PDROITE, PBAS, PGAUCHE};
const unsigned char CarPrt[10]={ 32,138,140,142,144,
                                 32,139,141,143,145};
const unsigned char CarCas[4]={' ', 'ö', '÷', 'ü'};
const unsigned ColCas[4]={0,   14,  140,  7 };
const unsigned char CarBns[4]={'ø', 'ù', 'ú', 'û'};
const unsigned ColBns[4]={13,11,13,11};

const unsigned char Mat[30][8]={{0x00,0x44,0xEE,0xFE,0xFE,0x7C,0x38,0x00},
                                {0x38,0x7C,0xF8,0xF0,0xF8,0x7C,0x38,0x00},
                                {0x00,0x38,0x7C,0xFE,0xFE,0xEE,0x44,0x00},
                                {0x1C,0x3E,0x1F,0x0F,0x1F,0x3E,0x1C,0x00},
                                {0x00,0x00,0x00,0x00,0x28,0x6C,0xFE,0xFE},
                                {0xFE,0x7C,0x38,0x00,0x00,0x00,0x00,0x00},
                                {0x03,0x07,0x0F,0x0F,0x0F,0x07,0x03,0x00},
                                {0x80,0xC0,0xE0,0x80,0xE0,0xC0,0x80,0x00},
                                {0x00,0x00,0x00,0x00,0x38,0x7C,0xFE,0xFE},
                                {0xFE,0x6C,0x28,0x00,0x00,0x00,0x00,0x00},
                                {0x03,0x07,0x0F,0x03,0x0F,0x07,0x03,0x00},
                                {0x80,0xC0,0xE0,0xE0,0xE0,0xC0,0x80,0x00},
                                {0x38,0x7C,0xFE,0xFE,0xFE,0x7C,0x38,0x00},
                                {0x00,0x38,0x7C,0xFE,0xFE,0x7C,0x38,0x00},
                                {0x00,0x00,0x10,0x7C,0xFE,0xFE,0x38,0x00},
                                {0x00,0x10,0x38,0x10,0x7C,0xFE,0x7C,0x00},
                                {0x10,0x38,0x10,0x10,0x10,0x7C,0xFE,0x00},
                                {0x38,0x54,0xD6,0xFE,0xFE,0x54,0xAA,0x00},
                                {0x00,0x00,0x00,0x00,0x38,0x54,0xD6,0xFE},
                                {0xFE,0xAA,0x54,0x00,0x00,0x00,0x00,0x00},
                                {0x80,0x40,0x60,0xE0,0xE0,0xA0,0x40,0x00},
                                {0x03,0x05,0x0D,0x0F,0x0F,0x0A,0x05,0x00},
                                {0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00},
                                {0x00,0x00,0x18,0x3C,0x3C,0x18,0x00,0x00},
                                {0x6C,0xFE,0xFE,0xFE,0x7C,0x38,0x10,0x00},
                                {0x10,0x38,0x7C,0xFE,0x7C,0x10,0x38,0x00},
                                {0x10,0x38,0x7C,0xFE,0x7C,0x38,0x10,0x00},
                                {0x38,0x38,0xD6,0xFE,0xD6,0x10,0x38,0x00},
                                {0xBF,0xBF,0x00,0xFB,0xFB,0xFB,0x00,0xBF},
                                {0x28,0x6C,0x0E,0x7C,0xE0,0x6C,0x28,0x00}};

const unsigned char Let[26][8]={{0x38,0x7C,0xC6,0xFE,0xC6,0x6C,0x28,0x00},
                                {0x38,0x7C,0xC6,0xFC,0xC6,0x7C,0x38,0x00},
                                {0x38,0x7C,0xC6,0xC0,0xC6,0x7C,0x38,0x00},
                                {0x30,0x78,0xCC,0xC6,0xCC,0x78,0x30,0x00},
                                {0x38,0x7C,0xC6,0xF0,0xC6,0x7C,0x38,0x00},
                                {0x38,0x7C,0xC6,0xF0,0xC0,0x60,0x20,0x00},
                                {0x38,0x7C,0xC0,0xDE,0xCC,0x7C,0x38,0x00},
                                {0x28,0x6C,0xC6,0xFE,0xC6,0x6C,0x28,0x00},
                                {0x38,0x7C,0xD6,0x10,0xD6,0x7C,0x38,0x00},
                                {0x38,0x3C,0x06,0x06,0xC6,0x7C,0x38,0x00},
                                {0x20,0x6C,0xC8,0xF0,0xC8,0x6C,0x20,0x00},
                                {0x20,0x60,0xC0,0xC0,0xC6,0x7C,0x38,0x00},
                                {0x38,0x7C,0xD6,0xD6,0xC6,0x6C,0x28,0x00},
                                {0x28,0x6C,0xE6,0xD6,0xCE,0x6C,0x28,0x00},
                                {0x38,0x7C,0xC6,0xC6,0xC6,0x7C,0x38,0x00},
                                {0x38,0x7C,0xC6,0xFE,0xC0,0x60,0x20,0x00},
                                {0x38,0x7C,0xC6,0xD6,0xCE,0x7C,0x3A,0x00},
                                {0x38,0x7C,0xC6,0xFC,0xC8,0x6C,0x28,0x00},
                                {0x38,0x7C,0xE6,0x10,0xCE,0x7C,0x38,0x00},
                                {0x38,0x7C,0xD6,0x10,0x10,0x38,0x38,0x00},
                                {0x28,0x6C,0xC6,0xC6,0xC6,0x7C,0x38,0x00},
                                {0x28,0x6C,0xC6,0xC6,0x6C,0x38,0x10,0x00},
                                {0x28,0x6C,0xC6,0xD6,0xFE,0x6C,0x28,0x00},
                                {0x28,0x6C,0xEE,0x10,0xEE,0x6C,0x28,0x00},
                                {0x28,0x6C,0xC6,0xFE,0x10,0x38,0x38,0x00},
                                {0x38,0x7C,0xC8,0x10,0x26,0x7C,0x38,0x00}};




const unsigned char Chf[10][8]={{0x38,0x7C,0xEE,0xEE,0xEE,0x7C,0x38,0x00},
                                {0x38,0x78,0xF8,0x38,0x38,0x38,0x38,0x00},
                                {0x38,0x7C,0x0E,0xFE,0xE0,0x7C,0x38,0x00},
                                {0x38,0x7C,0x0E,0x7E,0x0E,0x7C,0x38,0x00},
                                {0x38,0x7C,0xDC,0xFE,0x1C,0x1C,0x1C,0x00},
                                {0x38,0x7C,0xE0,0xFE,0x0E,0x7C,0x38,0x00},
                                {0x38,0x7C,0xE0,0xFE,0xEE,0x7C,0x38,0x00},
                                {0x38,0x7C,0x06,0x06,0x0E,0x1C,0x38,0x00},
                                {0x38,0x7C,0xEE,0xFE,0xEE,0x7C,0x38,0X00},
                                {0x38,0x7C,0xEE,0xFE,0x0E,0x7C,0x38,0x00}};

const unsigned char  Sco[18][8]={{0x00,0x5B,0xDB,0x5B,0x5B,0x5B,0x5B,0x00},
                                 {0x00,0xDB,0x5B,0xDB,0x9B,0x9B,0xDB,0x00},
                                 {0x00,0xDB,0x5B,0xDB,0x5B,0x5B,0xDB,0x00},
                                 {0x00,0x9B,0x9B,0xDB,0x5B,0x5B,0x5B,0x00},
                                 {0x00,0xDB,0x9B,0xDB,0x5B,0x5B,0xDB,0x00},
                                 {0x00,0xDB,0x9B,0xDB,0xDB,0xDB,0xDB,0x00},
                                 {0x00,0xDB,0x5B,0x5B,0x5B,0x5B,0x5B,0x00},
                                 {0x00,0xDB,0xDB,0x1B,0xDB,0xDB,0xDB,0x00},
                                 {0x00,0xDB,0xDB,0xDB,0x1B,0x1B,0xDB,0x00},
                                 {0x80,0x80,0x30,0x30,0x0C,0x0C,0x03,0x03},
                                 {  0, 128, 129, 193, 131, 129,   1,   0},
                                 { 62,   8,   0,   0,   0,   0,  16, 124},
                                 {  0, 128, 193,  99, 198, 131,   1,   0},
                                 { 54,  28,   8,   0,   0,  16,  56, 108},
                                 {  0,   0, 129, 118, 110, 129,   0,   0},
                                 { 36,  60,  24,  16,   8,  24,  24,  36},
                                 {  0,   0,   0, 255, 255,   0,   0,   0},
                                 { 24,  24,  24,  24,  24,  24,  24,  24}};

const unsigned char Ihsv[64][8]=
{{  0,   0,   0,   0,   0,   0,   0,   0},
 {  0,   0,   0,   3,   7,  31,  63, 127},
 {  3,  31, 255, 255, 255, 255, 255, 255},
 {255, 128, 162, 128, 136, 128, 162, 129},
 {128, 112,  62,  43, 181,  42,  53, 234},
 {  0,   1,   2, 130,  66, 178, 105, 164},
 {240,   8, 100, 132, 132, 100,   8, 240},
 {124,  96, 124,  96,  96,   0, 120, 100},
 {  0,   1,   3,   7,   7,  15,  31,  31},
 {255, 255, 255, 255, 255, 255, 255, 239},
 {240, 224, 224, 224, 224, 224, 224, 224},
 {138, 130, 162, 130, 138, 130, 162, 130},
 { 29,  10,  13,  10,  13,  10,  13,  10},
 { 98, 161,  96, 160,  96, 160,  96, 160},
 {  0,   0, 128,  64,  64,  32,  16,  16},
 {120,  96,  96,   0,  56, 100, 124, 100},
 { 63,  63,  63, 127, 127, 127, 255, 254},
 {207, 207, 143, 143,  15,  15,  15,  15},
 {224, 224, 224, 224, 224, 224, 224, 224},
 {138, 130, 162, 130, 138, 130, 162, 130},
 { 13,  10,  13,  10,  13,  10,  13,  10},
 { 96, 160,  96, 160,  96, 160,  96, 160},
 {  8,   8,   8,   4,   4,   4,   2,   2},
 {100,   0,  60,  96,  96,  96,  60,   0},
 {254, 128, 128, 128, 128, 128, 254, 254},
 { 15,  15,  15,  15,  15,  15,  15,  15},
 {224, 224, 224, 224, 224, 224, 224, 224},
 {254,   0,   0,   0,   0,   0, 254, 130},
 { 13,  10,  13,  10,  13,  10,  13,  10},
 { 96, 160,  96, 160,  96, 160,  96, 160},
 {254, 170, 214, 170, 214, 170, 214, 170},
 {  0,   0,   0,   0,   0,   0, 120, 100},
 {255, 127, 127, 127,  63,  63,  63,  31},
 { 15,  15,  15, 143, 143, 207, 207, 239},
 {224, 224, 224, 224, 224, 224, 224, 224},
 {138, 130, 162, 130, 138, 130, 162, 130},
 { 13,  10,  13,  10,  13,  10,  13,  10},
 { 97, 161,  97, 162,  99, 166, 101, 170},
 { 86, 172,  84, 172,  88, 168,  88, 176},
 {120, 100, 120,   0, 100, 100,  56,  16},
 { 31,  15,   7,   7,   3,   1,   0,   0},
 {255, 255, 255, 255, 255, 255, 255, 127},
 {224, 224, 224, 224, 224, 224, 240, 255},
 {138, 130, 162, 130, 138, 130, 162, 130},
 { 13,  10,  13,  10,  13,  10,  13,  10},
 {117, 170,  85, 170,  85, 171,  86, 172},
 { 80, 160,  64, 192, 128,   0,   0,   0},
 { 16,   0,   0,   0,   0,   0,  16,   0},
 {  0,   0,   0,   0,   0,   0,   0,   0},
 { 63,  31,   7,   3,   0,   0,   0,   0},
 {248, 248, 250, 248, 248,  24,   7,   0},
 {138,   2,  34,   2, 138,   2, 255,   0},
 { 13,  10,  13,  11,  14, 112, 128,   0},
 { 88, 176,  64, 128,   0,   0,   0,   0},
 {  0,   0,   0,   0,   0,   0,   0,   0},
 { 16,   0,  16,   0,  16,   0,  16,   0},
 {  0, 196, 170, 206, 138, 138,   0,   0},
 {  0, 236,  74,  76,  74,  74,   0,   0},
 {  0, 155, 162, 163, 162, 155,   0,   0},
 {  0, 131,   2, 131,   2, 130,   0,   0},
 {  0, 146,  42, 170,  42,  17,   0,   0},
 {  0, 146, 170, 170, 178,  25,   0,   0},
 {  0, 187, 161, 185, 161,  57,   0,   0},
 {  0, 128,   0,   0,   0,   0,   0,   0}};


const char MonNom[33]="PAT";

char ch, Nom[129]="?";

time_t time1, time2;

unsigned char Bloquee[200], Ouverte[200], BlqEnr[200];

int AvecPortes=1, jmax, QuatreAs=0;

unsigned char c[NBX][NBY], Table[NBX][NBY],
              Porte[200], BonusPris[4]={0, 0, 0, 0},
              File[50][2], Ptr=0;

unsigned char szPrs[]="FPAC v1.03 - Fouquet's Pac-Man. IHSV(c), II-MCMXCVII\n",
              szWelcome[]="%s, Bienvenu(e) dans FOUQUET's PAC-MAN...\n";

unsigned Niveau, Vies=5, TypeSon, NbCases, Son=1, Determinisme, DetermDep=50,
         Msg[10], DelaiMsg[10], XMsg[10], YMsg[10],
         xd[200], yd[200], PerPorte, NbPortes=50,
         MsgCrt=0, MsgNv=0, transposition=0, xt, yt, FrqPil, FrqPilDep=100, TextMode=TXTMODEINIT,
         XManoir, YManoir, NbGraines[4], Perdu=0, Echap, Inactivite=0,
         xp, yp, dp, nf, nfDep=4, ep, delai=100, Pts=0, // nf=nombre de fantomes
         Abandon=0, tpsbonus=100, tbonus, xs, ys, es,
         tmang[MAXFANTOMES], tpsmang=100, // temps restant pour les fantomes d'ˆtre chasseurs
         tnaiss[MAXFANTOMES], tpsnaiss=50, // temps restant avant de r‚apparaitre dans le jeu
         nfm=0, // nfm = nombre de fantomes bouff‚s avec la meme pastille
         xf[MAXFANTOMES], yf[MAXFANTOMES], df[MAXFANTOMES], ef[MAXFANTOMES], cf[MAXFANTOMES],// cf=case sous le fantome
         nbords, xb[20], yb[20], db[20]; // bords du manoir des fant“mes

FILE *f, *ff;

struct REGPACK r;

void Gotoxy(unsigned x, unsigned y)
 {
  r.r_ax=0x0200;
  r.r_bx=0x0000;
  r.r_dx=256*y+x;
  intr(0x10, &r);
 }

void printcar(unsigned char Car, unsigned char Couleur)
 {
  r.r_ax=0x0900+Car;
  r.r_bx=0x0000+Couleur;
  r.r_cx=0x0001;
  intr(0x10, &r);
 }

void ModeTexte(unsigned Mode)
 {
  r.r_ax=Mode;
  intr(0x10, &r);
 }

void ConstrEcran(unsigned Rep)
 {
  r.r_ax=0x1200+Rep;
  r.r_bx=0x0036;
  intr(0x10, &r);
 }

void InitRecords()
 {
  unsigned i, s=0;
  if (f=fopen("FPAC.RCD","wb"))
   {
    for(i=0;i<10; i++)
     {
      fwrite(MonNom, 33, 1, f);
      fwrite(&s, 2, 1, f);
      fwrite(&s, 2, 1, f);
     }
    printf("FPAC.RCD a ‚t‚ r‚initialis‚.\n");
    fclose(f);
   }
  else
   {
    perror("\aImpossible d'‚crire le fichier FPAC.RCD");
    exit(1);
   }
 }

void RecIHSV()
 {
  r.r_ax=0x1110;
  r.r_bx=0x0800;
  r.r_cx=0x001A;
  r.r_dx=0x0041;
  r.r_es=_DS;
  r.r_bp=(unsigned)(Let);
  intr(0x10, &r);
  r.r_ax=0x1110;
  r.r_bx=0x0800;
  r.r_cx=0x0040;
  r.r_dx=0x00C0;
  r.r_es=_DS;
  r.r_bp=(unsigned)(Ihsv);
  intr(0x10, &r);
  r.r_ax=0x1110;
  r.r_bx=0x0800;
  r.r_cx=0x001E;
  r.r_dx=0x00A0;
  r.r_es=_DS;
  r.r_bp=(unsigned)(Mat);
  intr(0x10, &r);
  r.r_ax=0x1110;
  r.r_bx=0x0800;
  r.r_cx=0x000A;
  r.r_dx=0x0030;
  r.r_es=_DS;
  r.r_bp=(unsigned)(Chf);
  intr(0x10, &r);
}

void AfficheLigne(unsigned x, unsigned y, char *s, unsigned Couleur, unsigned dc)
 {
  unsigned i, e=1;
  for(i=0;i<strlen(s);i++)
   {
    Gotoxy(x+i, y);
    if (e) printcar(PDROITE-dc, 14);
    else   printcar(PBOULE-dc, 14);
    delay((!Echap)*25);
    Gotoxy(x+i, y);   printcar(PDROITE1-dc, 14);
    Gotoxy(x+i+1, y); printcar(PDROITE2-dc, 14);
    delay((!Echap)*25);
    Gotoxy(x+i, y);   printcar(s[i], Couleur);
    Gotoxy(x+i+1, y);
    e=1-e;
    if (e) printcar(PDROITE-dc, 14);
    else   printcar(PBOULE-dc, 14);
    delay((!Echap)*25);
    if (kbhit())
     {
      if(!(ch=getch())) ch=getch();
      Echap=(ch==27);
     }
   }
  Gotoxy(x+i, y); printcar(32, 0);
 }

void TesteTouche(char *Touche)
 {
  time_t t1, t2;
  *Touche=0;
  time(&t1);
  do
   {
    if (kbhit())
     if (!(*Touche=getch())) *Touche=getch();
    if (*Touche==13)
     {
      ModeTexte(3);
      printf("\nA la prochaine fois !\n");
      exit(0);
     }
    time(&t2);
   }
  while((!*Touche)&&(t2-t1)<5);
 }

void TesteRecords(int Chg)
 {
  int i, j, k, ii=0, fait=0, s, l;
  char ch, n[33], ligne[40];
  ModeTexte(TextMode);
  ConstrEcran(1);
  RecIHSV();
  for(i=0;i<NBX*NBY;i++)
   {
    Gotoxy(i%NBX, i/NBX);
    printcar(192+((8+8*(i/NBX))%64+((i%NBX)%8)), 7);
   }
  ConstrEcran(0);
  _setcursortype(_NOCURSOR);
  for(i=0; i<47; i++)
   for(k=0; k<3; k++)
    for(j=0; j<i+k+1; j++)
     {
      if (k>0)
       {
        Gotoxy((NBX-49)/2+1+j, (NBY-49)/2+1+i+k);
        printcar(188, 6);
        Gotoxy((NBX-49)/2+1+i+k, (NBY-49)/2+1+j);
        printcar(188, 6);
       }
      else
       {
        Gotoxy((NBX-49)/2+1+j, (NBY-49)/2+1+i);
        printcar(32+156*((i<2)||(j<2)), 6*((i<2)||(j<2)));
        Gotoxy((NBX-49)/2+1+i, (NBY-49)/2+1+j);
        printcar(32+156*((i<2)||(j<2)), 6*((i<2)||(j<2)));
       }
     }
  do
   {
    for(i=0;i<45;i++)
     for(j=0;j<45;j++)
      {
       Gotoxy((NBX-45)/2+1+i, (NBY-45)/2+1+j);
       printcar(32, 8);
      }
    ii=0;
    Echap=0;
    AfficheLigne((NBX-26)/2+1, 6, "LES 10 MEILLEURS SCORES", 15, 64);
    AfficheLigne((NBX-26)/2+1, 10, "NIV SCORE NOMS", 14, 64);
    if ((f=fopen("FPAC.RCD","rb"))&&(!Chg||(ff=fopen("FPAC.$$$","wb"))))
     {
      for(i=0; i<10; i++)
       {
        fread(n, 33, 1, f);
        fread(&s, 2, 1, f);
        fread(&l, 2, 1, f);
        if ((Chg)&&(!fait)&&((Niveau>l)||((Niveau==l)&&(Pts>s))))
         {
          fait=1;
          sprintf(ligne, "%3d %5d %s", Niveau, Pts, Nom);
          AfficheLigne((NBX-26)/2+1, 12+3*ii, ligne, 12, 64);
          fwrite(Nom, 33, 1, ff);
          fwrite(&Pts, 2, 1, ff);
          fwrite(&Niveau, 2, 1, ff);
          ii++;
         }
        if (ii<10)
         {
          sprintf(ligne, "%3d %5d %s", l, s, n);
          AfficheLigne((NBX-26)/2+1, 13+3*ii, ligne, 10, 64);
          if (Chg)
           {
            fwrite(n, 33, 1, ff);
            fwrite(&s, 2, 1, ff);
            fwrite(&l, 2, 1, ff);
           }
          ii++;
         }
       }
      if (Chg) fclose(ff);
      fclose(f);
      if (Chg)
       {
        if (remove("FPAC.RCD"))
         {
          ModeTexte(3);
          perror("\aImpossible de supprimer FPAC.RCD");
          exit(1);
         }
        if (rename("FPAC.$$$", "FPAC.RCD"))
         {
          ModeTexte(3);
          perror("\aImpossible de renommer FPAC.$$$ en FPAC.RCD");
          exit(1);
         }
        Chg=0;
       }
      AfficheLigne((NBX-42)/2+1, 44, "ESPACE POUR JOUER OU ENTREE POUR QUITTER", 143, 64);
      Echap=0;
      TesteTouche(&ch);
      if ((ch!=32)&&(ch!=13))
       {
        delay(1000);
        for(i=0;i<45;i++)
         for(j=0;j<45;j++)
          {
           Gotoxy((NBX-45)/2+1+i, (NBY-45)/2+1+j);
           printcar(32, 4);
          }
        AfficheLigne((NBX-34)/2, 16, "FPAC PROGRAMME PAR PATRICE FOUQUET", 15, 64);
        AfficheLigne((NBX-24)/2, 18, "MEGA PAC MAN VERSION 1:03", 7, 64);
        AfficheLigne((NBX-30)/2, 23, "REMERCIEMENTS AUX TESTEURS::::", 14, 64);
        AfficheLigne((NBX-18)/2, 25, "± ROLAND MATHIEU ±", 14, 64);
        AfficheLigne((NBX-16)/2, 27, "± SAMI CEYHAN ±", 14, 64);
        AfficheLigne((NBX-24)/2, 29, "± MICHEL HARITOPOULOS ±", 14, 64);
        AfficheLigne((NBX-16)/2, 31, "± THIERRY BLIN ±", 14, 64);
        AfficheLigne((NBX-32)/2, 34, "COMMANDES AU CLAVIER DANS LE JEU", 10, 64);
        AfficheLigne((NBX-34)/2, 36, "± LES FLECHES POUR BOUGER PAC MAN ±", 10, 64);
        AfficheLigne((NBX-36)/2, 38, "± P POUR PAUSE ± ECHAP POUR QUITTER ±", 10, 64);
        AfficheLigne((NBX-42)/2+1, 44, "ESPACE POUR JOUER OU ENTREE POUR QUITTER", 143, 64);
        Echap=0;
        TesteTouche(&ch);
        if (ch==13)
         {
          ModeTexte(3);
          printf("\nA la prochaine fois !\n");
          exit(0);
         }
       }
     }
    else
     {
      ModeTexte(3);
      perror("\aImpossible de mettre … jour FPAC.RCD");
      exit(1);
     }
   }
  while(ch!=32);
 }

unsigned Dist(int x, int y)
 {
  return(x*x+y*y);
 }

int EnvMinimum(int x,int y)
 {
  int Env,d,Maxi=0;
  for(d=0; d<4; d++)
   {
    Env=(c[x+dx[d]][y+dy[d]-1]==MUR)+
        (c[x+dx[d]-1][y+dy[d]]==MUR)+
        (c[x+dx[d]+1][y+dy[d]]==MUR)+
        (c[x+dx[d]][y+dy[d]+1]==MUR);
    if ((Env>Maxi)&&(c[x+dx[d]][y+dy[d]]==MUR)) Maxi=Env;
   }
  return (Maxi>=ENVMIN);
 }

void MetPortes()
 {
  int i, j, x, y;
  j=0;
  do
   {
    do
     {
      x=1+random(XMAX-1);
      y=1+random(YMAX-1);
      for(i=0; (i<j)&&((xd[i]-x)*(xd[i]-x)+(yd[i]-y)*(yd[i]-y)>1); i++);
     }
    while(i<j);
    if ((x!=NBX/2)&&(y!=NBY/2))
     {
      if ((c[x][y-1]==MUR)&&(c[x][y+1]==MUR)&&
          (c[x-1][y]!=MUR)&&(c[x+1][y]!=MUR))
       {
        Table[x][y]=j;
        Ouverte[j]=random(2);
        Porte[j]=5+4*Ouverte[j];
        xd[j]=x;
        yd[j]=y;
        if (c[x][y]==GRAINE)
         NbGraines[(x>NBX/2)+2*(y>NBY/2)]--;
        GOTOXY(x, y); printcar(CarPrt[Porte[j]], 14);
        j++;
       }
      if ((c[x][y-1]!=MUR)&&(c[x][y+1]!=MUR)&&
         (c[x-1][y]==MUR)&&(c[x+1][y]==MUR))
       {
        Table[x][y]=j;
        Ouverte[j]=random(2);
        Porte[j]=4*Ouverte[j];
        xd[j]=x;
        yd[j]=y;
        if (c[x][y]==GRAINE)
         NbGraines[(x>NBX/2)+2*(y>NBY/2)]--;
        GOTOXY(x, y); printcar(CarPrt[Porte[j]], 14);
        j++;
       }
     }
   }
  while(j<NbPortes);
  for(j=0; j<NbPortes; j++)
   c[xd[j]][yd[j]]=MUR*(Porte[j]%5>0);
 }

void CreeLaby(int x, int y, int Plan)
 {
  int d,j,Env,Lg;

  Env=(c[x][y-1]==MUR)+
      (c[x-1][y]==MUR)+
      (c[x+1][y]==MUR)+
      (c[x][y+1]==MUR);
  if ((Env>0)&&(EnvMinimum(x,y)))
   do
    {
     do
      {
       d=random(4);
       Env=(c[x+dx[d]][y+dy[d]-1]==MUR)+
           (c[x+dx[d]-1][y+dy[d]]==MUR)+
           (c[x+dx[d]+1][y+dy[d]]==MUR)+
           (c[x+dx[d]][y+dy[d]+1]==MUR);
      }
     while((c[x+dx[d]][y+dy[d]]<MUR)||(Env<ENVMIN));
     Lg=1+random(6);
     j=1;
     do
      {
       if (c[x+j*dx[d]][y+j*dy[d]]==MUR)
        {
         if (NbCases%FrqPil<FrqPil-1)
          {
           NbCases++;
           NbGraines[Plan]++;
           c[x+j*dx[d]][y+j*dy[d]]=GRAINE;
           GOTOXY(x+j*dx[d],y+j*dy[d]); printcar('ö',14);
          }
         else
          {
           NbCases++;
           c[x+j*dx[d]][y+j*dy[d]]=PILULE;
           GOTOXY(x+j*dx[d],y+j*dy[d]); printcar('÷',140);
          }
        }
       j++;
      }
     while((j<=Lg)&&(c[x+j*dx[d]][y+j*dy[d]]==MUR));
     if (j>Lg)
      CreeLaby(x+Lg*dx[d], y+Lg*dy[d], Plan);
     Env=(c[x][y-1]==MUR)+(c[x-1][y]==MUR)+(c[x+1][y]==MUR)+(c[x][y+1]==MUR);
    }
   while ((Env>0)&&EnvMinimum(x,y));
  if (c[x][y]==MUR)
   {
    NbCases++;
    NbGraines[Plan]++;
    c[x][y]=GRAINE;
    GOTOXY(x,y);printcar('ö',14);
   }
 }


void RecMatrices()
 {
  r.r_ax=0x1110;
  r.r_bx=0x0800;
  r.r_cx=0x001A;
  r.r_dx=0x0041;
  r.r_es=_DS;
  r.r_bp=(unsigned)(Let);
  intr(0x10, &r);
  r.r_ax=0x1110;
  r.r_bx=0x0800;
  r.r_cx=0x001E;
  r.r_dx=0x00E0;
  r.r_es=_DS;
  r.r_bp=(unsigned)(Mat);
  intr(0x10, &r);
  r.r_ax=0x1110;
  r.r_bx=0x0800;
  r.r_cx=0x000A;
  r.r_dx=0x0030;
  r.r_es=_DS;
  r.r_bp=(unsigned)(Chf);
  intr(0x10, &r);
  r.r_ax=0x1110;
  r.r_bx=0x0800;
  r.r_cx=0x0012;
  r.r_dx=0x0080;
  r.r_es=_DS;
  r.r_bp=(unsigned)(Sco);
  intr(0x10, &r);
 }

void MortPac()
 {
  int i;
  for(i=MsgCrt; i!=MsgNv; i=(i+1)%10)
   if (XMsg[i]||YMsg[i])
    {
     GOTOXY(XMsg[i], YMsg[i]);
     printcar(CarCas[c[XMsg[i]][YMsg[i]]], ColCas[c[XMsg[i]][YMsg[i]]]);
    }
  for(i=0; i<5; i++)
   {
    GOTOXY(xp, yp);
    printcar(236+i, 14);
    delay(200);
   }
  GOTOXY(xp, yp);
  printcar(240, 142);
  delay(1000);
 }

void LanceFantome(int i)
 {
  int n;
  ef[i]=ENCHASSE;
  n=random(nbords);
  xf[i]=xb[n];
  yf[i]=yb[n];
  df[i]=db[n];
 }

void FaireSon()
 {
  int i;
  switch(TypeSon)
   {
    case SBONUS:   for(i=8;i<4096;i*=2)
                    {
                     sound(Son*i);
                     delay(delai/10);
                    }
                   break;
    case SGRAINE:  sound(Son*20);
                   delay(1);
                   nosound();
                   delay(delai);
                   break;
    case SPILULE:  sound(Son*1760);
                   delay(delai/2);
                   sound(Son*880);
                   delay(delai/2);
                   break;
    case SFANTOME: for(i=0; i<10; i++)
                    {
                     sound(Son*Frq[i%2][i/2]);
                     delay(delai/10);
                    }
                   break;
    case SPAC:     for(i=9; i>=0; i--)
                    {
                     sound(Son*Frq[i%2][i/2]);
                     delay(delai/10);
                    }
                   break;
    default:       delay(delai); break;
   }
  nosound();
 }

void Deplacements()
 {
  int i, j, MsgOn;
  if (tbonus) tbonus--;
  else
   {
    if PORTE(xs, ys)
     Bloquee[Table[xs][ys]]&=255-BONUS;
    GOTOXY(xs, ys);
    printcar(CarCas[c[xs][ys]], ColCas[c[xs][ys]]);
    es=random(4);
    do
     {
      xs=1+random(XMAX-1);
      ys=1+random(YMAX-1);
     }
    while((Dist(xs-xp, ys-yp)<100)||(c[xs][ys]==MUR));
    if PORTE(xs, ys)
     Bloquee[Table[xs][ys]]|=BONUS;
    GOTOXY(xs, ys); printcar(CarBns[es], ColBns[es]);
    tbonus=tpsbonus;
   }

  for(i=MsgCrt; i!=MsgNv; i=(i+1)%10)
   if (DelaiMsg[i])
    DelaiMsg[i]--;
   else
    if (XMsg[i]||YMsg[i])
     {
      GOTOXY(XMsg[i], YMsg[i]);
      printcar(CarCas[c[XMsg[i]][YMsg[i]]], ColCas[c[XMsg[i]][YMsg[i]]]);
      if PORTE(XMsg[i], YMsg[i]) printcar(CarPrt[Porte[Table[XMsg[i]][YMsg[i]]]], 14);
      XMsg[i]=0;
      YMsg[i]=0;
      MsgCrt=(MsgCrt+1)%10;
     }

  if (dp!=INDEFINI)
   {
    GOTOXY(xp, yp);printcar(CarPac[dp][0], 14);
    if (!transposition)
     GOTOXY(xp+dx[dp], yp+dy[dp]);
    else
     GOTOXY(xt, yt);
    printcar(CarPac[dp][1], 14);
   }
  for(i=0; i<nf; i++)
   {
    if (ef[i])
     {
      if ((xf[i]!=xp)||(yf[i]!=yp))
       {
        GOTOXY(xf[i], yf[i]);
        printcar(CarFtm[df[i]][0], ColFtm[ef[i]]);
       }
      GOTOXY(xf[i]+dx[df[i]], yf[i]+dy[df[i]]);
      printcar(CarFtm[df[i]][1], ColFtm[ef[i]]);
     }
   }
  delay(delai+1);
  if (dp!=INDEFINI)
   {
    MsgOn=0;
    for(i=MsgCrt; i!=MsgNv; i=(i+1)%10)
     if ((XMsg[i]==xp)&&(YMsg[i]==yp))
      {
       MsgOn=1;
       GOTOXY(xp, yp);
       printcar((unsigned)((unsigned)127+(unsigned)Msg[i]), 143);
      }
    if (!MsgOn)
     {
      GOTOXY(xp, yp); printcar(32, 14);
     }
    if (ep)
     {
      if (!transposition)
       GOTOXY(xp+dx[dp], yp+dy[dp]);
      else
       GOTOXY(xt, yt);
      printcar(CarPac2[dp] ,14);
     }
    else
     {
      if (!transposition)
       GOTOXY(xp+dx[dp], yp+dy[dp]);
      else
       GOTOXY(xt, yt);
      printcar(PBOULE,14);
     }
   }
  for(i=0; i<nf; i++)
   {
    if (ef[i])
     {
      MsgOn=0;
      for(j=MsgCrt; j!=MsgNv; j=(j+1)%10)
       if ((XMsg[j]==xf[i])&&(YMsg[j]==yf[i]))
        {
         MsgOn=1;
         GOTOXY(xf[i], yf[i]);
         printcar((unsigned)((unsigned)127+(unsigned)Msg[j]), 143);
        }
      if ((xf[i]==xs)&&(yf[i]==ys))
       {
        MsgOn=1;
        GOTOXY(xs, ys);
        printcar(CarBns[es], ColBns[es]);
       }
      if (!MsgOn)
       {
        if ((xf[i]!=xp)||(yf[i]!=yp))
         {
          GOTOXY(xf[i], yf[i]); printcar(CarCas[c[xf[i]][yf[i]]], ColCas[c[xf[i]][yf[i]]]);
         }
       }
      GOTOXY(xf[i]+dx[df[i]], yf[i]+dy[df[i]]); printcar(FENTIER, ColFtm[ef[i]]);
     }
   }
  FaireSon(TypeSon);
 }

void TesteClavier()
 {
  char ch;
  int i;
  if (kbhit())
   {
    if (!(ch=getch())) ch=getch();
    switch(ch)
     {
      case 'p':    Echap=0;
                   AfficheLigne((XMAX-24)/2, YMAX, "ESPACE POUR CONTINUER", 143, 0);
                   do if (!(ch=getch())) ch=getch(); while (ch!=32);
                   AfficheLigne((XMAX-24)/2, YMAX, "                     ", 0, 0);
                   break;

      case ECHAP:  Echap=0;
                   AfficheLigne((XMAX-28)/2, YMAX, "Q POUR QUITTER C POUR CONTINUER", 15, 0);
                   do if (!(ch=getch())) ch=getch(); while ((ch!='q')&&(ch!='c'));
                   AfficheLigne((XMAX-28)/2, YMAX, "                                ", 0, 0);
                   if (ch=='q') Perdu=3;
                   break;
      case HAUT:   if (c[xp+dx[NORD]][yp+dy[NORD]]<MUR) dp=NORD;
                   break;
      case DROITE: if (c[xp+dx[EST]][yp+dy[EST]]<MUR) dp=EST;
                   break;
      case BAS:    if (c[xp+dx[SUD]][yp+dy[SUD]]<MUR) dp=SUD;
                   break;
      case GAUCHE: if (c[xp+dx[OUEST]][yp+dy[OUEST]]<MUR) dp=OUEST;
                   break;
     }
   }
  switch(c[xp+dx[dp]][yp+dy[dp]])
   {
    case VIDE:   ep=0; Inactivite++; break;
    case PILULE: ep=1-ep; Pts+=10;
                 c[xp+dx[dp]][yp+dy[dp]]=VIDE;
                 nfm=0;
                 for(i=0; i<nf; i++)
                  if (ef[i])
                   {
                    ef[i]=ENFUITE;
                    tmang[i]=tpsmang;
                   }
                 TypeSon=SPILULE;
                 break;
    case GRAINE: ep=1-ep; Pts++;
                 c[xp+dx[dp]][yp+dy[dp]]=VIDE;
                 NbGraines[i=(xp+dx[dp]>NBX/2)+2*(yp+dy[dp]>NBY/2)]--;
                 if (!NbGraines[i])
                  {
                   Vies++;
                   Perdu=2;
                   Pts+=1000;
                   Gotoxy(6+Vies, YMAX-1);
                   printcar(PDROITE, 11);
                  }
                 TypeSon=SGRAINE;
                 break;
    case MUR:    Inactivite++;
                 if  ((((xp==1)||(xp==XMAX-1))&&(yp==NBY/2))||
                      (((yp==1)||(yp==YMAX-1))&&(xp==NBX/2)))
                  {
                   transposition=1;
                   xt=xp; yt=yp;
                   if (xp==1) xt=XMAX-1;
                   if (yp==1) yt=YMAX-1;
                   if (xp==XMAX-1) xt=1;
                   if (yp==YMAX-1) yt=1;
                  }
                 else
                  {
                   ep=1;
                   switch(dp)
                    {
                     case NORD: GOTOXY(xp, yp);printcar(PHAUT,14);
                                break;
                     case EST : GOTOXY(xp, yp);printcar(PDROITE,14);
                                break;
                     case SUD : GOTOXY(xp, yp);printcar(PBAS,14);
                                break;
                     case OUEST:GOTOXY(xp, yp);printcar(PGAUCHE,14);
                                break;
                    }
                   dp=INDEFINI;
                  }
                 break;
   }
  if (Inactivite==25)
   {
    Inactivite=0;
    if (Determinisme<99) Determinisme++;
   }
  if ((xp+dx[dp]==xs)&&(yp+dy[dp]==ys))
   {
    BonusPris[es]|=1;
    if (!QuatreAs)
     QuatreAs=(BonusPris[0]&BonusPris[1]&BonusPris[2]&BonusPris[3]);
    Gotoxy(45+es, YMAX-1); printcar(CarBns[es], ColBns[es]);
    tbonus=0;
    TypeSon=SBONUS;
    Pts+=50;
   }
 }

void TesteFantomes()
 {
  int diffmax, diffmin, d, i, j, k, nd, ndmax=0, ndmin=0, dposs[4], diff[4];
  for(i=0; i<nf; i++)
   {
    if ((xp+dx[dp]==xf[i])&&(yp+dy[dp]==yf[i]))
     switch(ef[i])
      {
       case ENCHASSE:   Perdu=1;
                        TypeSon=SPAC;
                        break;
       case ENFUITE:
       case TRANSITION: Msg[MsgNv]=nfm+1;
                        XMsg[MsgNv]=xp;
                        YMsg[MsgNv]=yp;
                        DelaiMsg[MsgNv]=16;
                        MsgNv=(MsgNv+1)%10;
                        ef[i]=MANGE;
                        TypeSon=SFANTOME;
                        tnaiss[i]=tpsnaiss;
                        nfm++; Pts+=100*nfm;
                        break;
      }
    else
     if (ef[i])
      {
       switch(ef[i])
        {
         case ENFUITE:    if (tmang[i])
                           tmang[i]--;
                          else
                           ef[i]=ENCHASSE;
                          if (tmang[i]<=(tpsmang/10))
                           ef[i]=TRANSITION;
                          break;
         case TRANSITION: if (tmang[i])
                           tmang[i]--;
                          else
                           ef[i]=ENCHASSE;
                          break;
        }
       nd=(dposs[NORD ]=(c[xf[i]+dx[NORD ]][yf[i]+dy[NORD ]]<MUR))+
          (dposs[EST  ]=(c[xf[i]+dx[EST  ]][yf[i]+dy[EST  ]]<MUR))+
          (dposs[SUD  ]=(c[xf[i]+dx[SUD  ]][yf[i]+dy[SUD  ]]<MUR))+
          (dposs[OUEST]=(c[xf[i]+dx[OUEST]][yf[i]+dy[OUEST]]<MUR));
       diffmax=-INFINI; diffmin=INFINI;
       if (nd)
        {
         for(d=0; d<4; d++)
          {
           if ((dposs[d])&&((nd==1)||((d+2)%4!=df[i])))
            {
             diff[d]=Dist((int)xf[i]-(int)xp, (int)yf[i]-(int)yp)-
                     Dist((int)xf[i]+dx[d]-(int)xp-dx[dp],
                          (int)yf[i]+dy[d]-(int)yp-dy[dp]);
             if (diff[d]<diffmin) diffmin=diff[d];
             if (diff[d]>diffmax) diffmax=diff[d];
            }
           else diff[d]=INFINI;
          }
         ndmax=0; ndmin=0;
         for(d=0; d<4; d++)
          {
           if (diff[d]==diffmax) ndmax++;
           if (diff[d]==diffmin) ndmin++;
          }
         switch(ef[i])
          {
           case ENCHASSE: if (random(100)<=Determinisme)
                           {
                            k=random(ndmax);
                            for(d=0; d<4; d++)
                             {
                              if (diff[d]==diffmax)
                               if (k) k--;
                               else df[i]=d;
                             }
                           }
                          else
                           do
                            df[i]=d=random(4);
                           while(diff[d]==INFINI);
                          break;
           case TRANSITION:
           case ENFUITE:  if (random(100)<=Determinisme)
                           {
                            k=random(ndmin);
                            for(d=0; d<4; d++)
                             {
                              if (diff[d]==diffmin)
                               if (k) k--;
                               else df[i]=d;
                             }
                           }
                          else
                           do
                            df[i]=d=random(4);
                           while(diff[d]==INFINI);
                          break;
          }
         if ((transposition&&(xt==xf[i])&&(yt==yf[i]))||((xp+dx[dp]==xf[i]+dx[df[i]])&&(yp+dy[dp]==yf[i]+dy[df[i]])))
         switch(ef[i])
          {
           case ENCHASSE:   Perdu=1;
                            TypeSon=SPAC;
                            GOTOXY(xf[i], yf[i]);printcar(CarFtm[df[i]][0], ColFtm[ef[i]]);
                            GOTOXY(xf[i]+dx[df[i]], yf[i]+dy[df[i]]);printcar(CarFtm[df[i]][1], ColFtm[ef[i]]);
                            GOTOXY(xp, yp);printcar(CarPac[dp][0], 14);
                            if (!transposition)
                             GOTOXY(xp+dx[dp], yp+dy[dp]);
                            else
                             GOTOXY(xt, yt);
                            printcar(CarPac[dp][1], 14);
                            GOTOXY(xf[i], yf[i]); printcar(CarCas[c[xf[i]][yf[i]]], ColCas[c[xf[i]][yf[i]]]);
                             GOTOXY(xf[i]+dx[df[i]], yf[i]+dy[df[i]]); printcar(FENTIER, ColFtm[ef[i]]);
                            GOTOXY(xp, yp); printcar(32, 14);
                            if (!transposition)
                             GOTOXY(xp+dx[dp], yp+dy[dp]);
                            else
                             GOTOXY(xt, yt);
                            printcar(CarPac2[dp] ,14);
                            xp+=dx[dp];
                            yp+=dy[dp];
                            break;
           case ENFUITE:
           case TRANSITION: Msg[MsgNv]=nfm+1;
                            XMsg[MsgNv]=xp;
                            YMsg[MsgNv]=yp;
                            DelaiMsg[MsgNv]=16;
                            MsgNv=(MsgNv+1)%10;
                            GOTOXY(xf[i], yf[i]);
                            printcar(CarCas[c[xf[i]][yf[i]]], ColCas[c[xf[i]][yf[i]]]);
                            ef[i]=MANGE;
                            TypeSon=SFANTOME;
                            tnaiss[i]=tpsnaiss;
                            nfm++; Pts+=100*nfm;
                            break;
          }
        }
       else
        df[i]=INDEFINI;
      }
     else
      if (tnaiss[i])
       tnaiss[i]--;
      else LanceFantome(i);
   }
 }

Dist0(int x, int y)
 {
  return(abs((int)x-(int)xp)+abs((int)y-(int)yp));
 }

DansFile(unsigned n)
 {
  int i;
  for(i=0; (File[i][NUMERO]!=n)&&(i<Ptr); i++);
  return(i<Ptr);
 }

void Enfile(unsigned n)
 {
  int p;
  File[Ptr][NUMERO]=n;
  File[Ptr][BUT]=5*(Porte[n]/5);
  Bloquee[n]|=ZONE;
  Ptr++;
 }

void Defile(unsigned n)
 {
  int i;
  Bloquee[File[n][NUMERO]]&=255-ZONE;
  for(i=n; i<Ptr-1; i++)
   {
    File[i][NUMERO]=File[i+1][NUMERO];
    File[i][BUT]=File[i+1][BUT];
   }
  Ptr--;
  File[Ptr][NUMERO]=255;
  File[Ptr][BUT]=255;
 }

void TesteFrontiere(int x, int y)
 {
  unsigned n;
  if ((x<XMAX)&&(x>0)&&(y<YMAX)&&(y>0)&&PORTE(x, y))
   {
    n=Table[x][y];
    if (!DansFile(n))
     Enfile(n);
   }
 }

void TesteFile()
 {
  int i, x, y, p;
  unsigned n;
  // test des nouvelles portes
  for(i=0; i<4; i++)
   {
    x=(int)xp+i;
    y=(int)yp-4+i;
    TesteFrontiere(x, y);
    x=(int)xp+4-i;
    y=(int)yp+i;
    TesteFrontiere(x, y);
    x=(int)xp-i;
    y=(int)yp+4-i;
    TesteFrontiere(x, y);
    x=(int)xp-4+i;
    y=(int)yp-i;
    TesteFrontiere(x, y);
   }
  for(i=0; i<Ptr; i++)
   {
    n=File[i][NUMERO];
    for(;(Dist0(xd[n], yd[n])>4)&&((Porte[n]%5)==4);)
     {
      Defile(i);
      n=File[i][NUMERO];
     }
    if (i<Ptr)
     {
      if (Dist0(xd[n], yd[n])<=4)
       File[i][BUT]=5*(Porte[n]/5);
      if (Dist0(xd[n], yd[n])>=5)
       File[i][BUT]=4+5*(Porte[n]/5);
      if ((p=File[i][BUT]-Porte[n])&&((Porte[n]%5)||!(Bloquee[n]&(255-ZONE))))
       Porte[n]+=p/abs(p);
      if (Porte[n]%5==1) c[xd[n]][yd[n]]=MUR;
      if (Porte[n]%5==0) c[xd[n]][yd[n]]=VIDE;
      if ((xp!=xd[n])||(yp!=yd[n]))
       {
        GOTOXY(xd[n], yd[n]);
        printcar(CarPrt[Porte[n]], 14);
       }
     }
   }
 }

void TestePortes()
 {
  int i, j, k;
  jmax+=(jmax<4);
  k=NbPortes+PerPorte+1-jmax;
   for(j=0; j<jmax; j++)
   {
    i=(k+j)%NbPortes;
    if (i==PerPorte)
     {
      Ouverte[i]=(c[xd[i]][yd[i]]==VIDE);
      BlqEnr[i]=Bloquee[i];
     }
    if (!Ouverte[i])
     {
      if (!BlqEnr[i])
       {
        if (Porte[i]%5==1) c[xd[i]][yd[i]]=VIDE;
        if (Porte[i]%5)
         Porte[i]--;
        GOTOXY(xd[i], yd[i]); printcar(CarPrt[Porte[i]], 14);
       }
      else
        if (!j) BlqEnr[i]=0;
     }
    else
     {
      if (!BlqEnr[i])
       {
        if (!(Porte[i]%5)) c[xd[i]][yd[i]]=MUR;
        if (Porte[i]%5<4)
         Porte[i]++;
        GOTOXY(xd[i], yd[i]); printcar(CarPrt[Porte[i]], 14);
       }
      else
       if (!j) BlqEnr[i]=0;
     }
   }
 }




void AfficheNombre(unsigned n, unsigned x, unsigned c)
 {
  Gotoxy(x  , YMAX-1);printcar(48+(n/10000), c);
  Gotoxy(x+1, YMAX-1);printcar(48+(n/1000)%10, c);
  Gotoxy(x+2, YMAX-1);printcar(48+(n/100)%10, c);
  Gotoxy(x+3, YMAX-1);printcar(48+(n/10)%10, c);
  Gotoxy(x+4, YMAX-1);printcar(48+(n%10), c);
 }

void AfficheScore()
 {
  int i;
  AfficheNombre(Pts, 0, 15);
  Gotoxy(20, YMAX-1); printcar(48+Determinisme/10, 12);
  Gotoxy(21, YMAX-1); printcar(48+Determinisme%10, 12);
 }

void AfficheVies()
 {
  Gotoxy(6+Vies, YMAX-1); printcar(' ', 0);
 }

void main(int nbarg, char *arg[])
 {
  int i, j, k;
  long lVerif1=0,lVerif2=0;
  printf(szPrs);
  if (nbarg<2)
   printf("Pas d'option s‚lectionn‚e.\n");
  else
   {
    for(i=0; i<nbarg-1; i++)
     {
      strupr(arg[1+i]);
      if (arg[1+i][1]=='=')
        switch(arg[1+i][0])
         {
          case '!': if (strlen(arg[1+i])>32) arg[1+i][32]=0;
                    strcpy(Nom, arg[1+i]+2);
                    printf(szWelcome, Nom);
                    break;

          case 'P': delai=atoi(arg[1+i]+2);
                    if ((delai<1)||(delai>1000))
                     {
                      printf("\aVitesse d'affichage incorrecte.\n");
                      exit(0);
                     }
                    printf("La vitesse d'affichage a ‚t‚ fix‚e … %d millisecondes.\n", delai);
                    break;
          case 'G': DetermDep=atoi(arg[1+i]+2);
                    if (DetermDep>99)
                     {
                      printf("\aMode de recherche des fant“mes incorrect.\n");
                      exit(0);
                     }
                    printf("Le mode de recherche des fant“mes a ‚t‚ fix‚ … %d.\n", DetermDep);
                    break;
          case 'L': FrqPilDep=atoi(arg[1+i]+2);
                    if (FrqPilDep>999)
                     {
                      printf("\aFr‚quence des PacGums invalide.\n");
                      exit(0);
                     }
                    printf("La fr‚quence des PacGums a ‚t‚ fix‚e … %d.\n", FrqPilDep);
                    break;
          case 'E': tpsmang=atoi(arg[1+i]+2);
                    if ((tpsmang<1)||(tpsmang>1000))
                     {
                      printf("\aDur‚e pendant laquelle les fant“mes sont mangeables incorrecte.\n");
                      exit(0);
                     }
                    printf("La dur‚e pendant laquelle les fant“mes sont mangeables a ‚t‚ fix‚e … %d.\n", tpsmang);
                    break;
          case 'N': nfDep=atoi(arg[1+i]+2);
                    if ((nfDep<1)||(nfDep>7))
                     {
                      printf("\aNombre de fant“mes incorrect.\n");
                      exit(0);
                     }
                    printf("Le nombre de fant“me a ‚t‚ fix‚ … %d.\n", nfDep);
                    break;
          case 'M': TextMode=atoi(arg[1+i]+2);
                    if ((nf<1)||(nf>7)) nf=5;
                    printf("Le mode texte a ‚t‚ fix‚ … %d.\n", TextMode);
                    break;
          case 'D': NbPortes=atoi(arg[1+i]+2);
                    if (NbPortes>199)
                     {
                      printf("\aNombre de portes incorrect.\n");
                      exit(0);
                     }
                    if (NbPortes)
                     printf("Le nombre de portes a ‚t‚ fix‚ … %d.\n", NbPortes);
                    else
                     {
                      printf("Jeu sans porte demand‚.\n");
                      NbPortes=100;
                      AvecPortes=0;
                     }

                    break;
          default:  printf("\aOption inconnue : %c\n%s", arg[1+i], Help);
                    exit(0);
         }
      else
       switch(arg[1+i][0])
        {
          case '?': printf("%s", Help);
                    exit(0);
                    break;
          case 'S': Son=0;
                    printf("Son d‚sactiv‚.\n");
                    break;
          case 'R': InitRecords();
                    break;
          default:  printf("\aOption incorrecte - %s\n%s", arg[1+i], Help);
                    exit(0);
       }
     }
   }
  if (!strcmp(Nom, "?"))
   {
    printf("Entrez votre nom : ");
    scanf("%s", Nom);
    strupr(Nom);
    if (strlen(Nom)>32) Nom[32]=0;
    printf("%s, Bienvenu(e) dans FOUQUET's PAC-MAN...\n",Nom);
   }
  if (!strcmp(Nom, "SESAME")) QuatreAs=1;
  printf("\nAppuyez sur [ECHAP] pour abandonner ou une autre touche pour continuer...");

  for(i=0;i<strlen(szPrs);i++)
   lVerif1+=(long unsigned)szPrs[i];
//  printf("szPrs:%ld\n", lVerif1);
  for(i=0;i<strlen(szWelcome);i++)
   lVerif2+=(long unsigned)szWelcome[i];
//  printf("szWelcome:%ld\n", lVerif2);

  if (getch()==27) exit(0);
  randomize();
  TesteRecords(0);
  //----------------- d‚but boucle -------------------
  while(1)
   {
    Vies=5;
    Determinisme=DetermDep;
    MsgCrt=0;
    MsgNv=0;
    transposition=0;
    FrqPil=FrqPilDep;
    Perdu=3*((lVerif1!=3728)||(lVerif2!=3088));
    Inactivite=0;
    Pts=0;
    Abandon=0;
    nfm=0;
    nf=nfDep;
    jmax=0;
    setmem(Bloquee, sizeof(Bloquee), 0);
    setmem(BlqEnr, sizeof(BlqEnr), 0);
    setmem(BonusPris, sizeof(BonusPris), 0);
    setmem(File, sizeof(File), 255);
    Ptr=0;
    Niveau=(unsigned)(log10((double)nf*                      // 1-7
                            (double)(1+Determinisme)*        // 1-100
                            (double)(1+FrqPil)*              // 1-1000
                            (double)(1000.0/delai)*          // 1-1000
                            (double)(1+AvecPortes*NbPortes)* // 1-200
                            (double)(1001-tpsmang))*
                      (999.99/(12.0+log10(140))));           // 1-1000 -> 140E12
    clrscr();                                                // -> log10(140)+12
    ModeTexte(TextMode);
    ConstrEcran(1);
    RecMatrices();
    for(i=0;i<NBX*NBY; i++)
     {
      GOTOXY(1+i%NBX, 1+i/NBX);
      printcar(' ', 0);
     }
    do
     {
      do
       {
        setmem(c, sizeof(c), MUR);
        for(i=0;i<NBX*(NBY-2);i++)
         {
          GOTOXY(1+i%NBX, 1+i/NBX);
          if (i%NBX<NBX-2) printcar('ü', 7);
         }
        for(i=0;i<XMAX;i++)
         {
          if (i)
           {
            GOTOXY(i, NBY/2); printcar(32, 0);
           }
          c[i][NBY/2]=VIDE;
         }
        for(i=0;i<YMAX;i++)
         {
          if (i)
           {
            GOTOXY(NBX/2, i); printcar(32, 0);
           }
          c[NBX/2][i]=VIDE;
         }
        for(i=0;i<NBX;i++)
         {
          c[i][0]=VIDE;
          c[i][YMAX]=VIDE;
         }
        for(i=0;i<NBY;i++)
         {
          c[0][i]=VIDE;
          c[XMAX][i]=VIDE;
         }
        do
         {
          XManoir=NBX/4+random(NBX/2);
          YManoir=NBY/4+random(NBY/2);
         }
        while(Dist(XManoir-NBX/2, YManoir-NBY/2)<200);
        for(k=0;k<25;k++)
         {
          c[XManoir-2+k%5][YManoir-2+k/5]=VIDE;
          GOTOXY(XManoir-2+k%5, YManoir-2+k/5);
          printcar(32, 0);
         }
        setmem(NbGraines,sizeof(NbGraines),0);
        NbCases=0;
        CreeLaby(1+random(NBX/2-1), 1+random((NBY-1)/2), 0);
        CreeLaby(NBX/2+1+random((NBX-1)/2), 1+random((NBY-1)/2), 1);
        CreeLaby(1+random((NBX-1)/2), NBY/2+1+random((NBY-1)/2), 2);
        CreeLaby(NBX/2+1+random((NBX-1)/2), NBY/2+1+random((NBY-1)/2), 3);
       }
      while((!NbGraines[0])||(!NbGraines[1])||(!NbGraines[2])||(!NbGraines[3]));
      setmem(Table, sizeof(Table), 255);
      if (AvecPortes) MetPortes();
      xp=NBX/2;
      yp=NBY/2;
      dp=random(4);
      GOTOXY(xp, yp);
      switch(dp)
       {
        case NORD : printcar(PHAUT, 14); break;
        case EST  : printcar(PDROITE, 14); break;
        case SUD  : printcar(PBAS, 14); break;
        case OUEST: printcar(PGAUCHE, 14); break;
       }
      for(i=0;i<NBX;i++)
       {
        c[i][0]=MUR;
        c[i][YMAX]=MUR;
       }
      for(i=0;i<NBY;i++)
       {
        c[0][i]=MUR;
        c[XMAX][i]=MUR;
       }
      nbords=0;
      for(i=0;i<5;i++)
       {
        if (c[xb[nbords]=i+XManoir-2][yb[nbords]=YManoir-3]<MUR)
         {
          db[nbords]=NORD;
          yb[nbords]++;
          nbords++;
         }
        if (c[xb[nbords]=i+XManoir-2][yb[nbords]=YManoir+3]<MUR)
         {
          db[nbords]=SUD;
          yb[nbords]--;
          nbords++;
         }
        if (c[xb[nbords]=XManoir-3][yb[nbords]=i+YManoir-2]<MUR)
         {
          db[nbords]=OUEST;
          xb[nbords]++;
          nbords++;
         }
        if (c[xb[nbords]=XManoir+3][yb[nbords]=i+YManoir-2]<MUR)
         {
          db[nbords]=EST;
          xb[nbords]--;
          nbords++;
         }
       }
     }
    while(!nbords);
    Gotoxy(22, YMAX-1); printcar('ý', 12); // le '%'
    Gotoxy(27, YMAX-1); printcar('N', 10);
    Gotoxy(28, YMAX-1); printcar('I', 10);
    Gotoxy(29, YMAX-1); printcar('V', 10);
    Gotoxy(30, YMAX-1); printcar(' ', 10);
    Gotoxy(31, YMAX-1); printcar(48+Niveau/100, 10);
    Gotoxy(32, YMAX-1); printcar(48+(Niveau/10)%10, 10);
    Gotoxy(33, YMAX-1); printcar(48+Niveau%10, 10);
    ConstrEcran(0);
    _setcursortype(_NOCURSOR);

// debut du jeu
    for(i=0;i<5;i++)
     {
      Gotoxy(7+i, YMAX-1);
      printcar(PDROITE, 11);
     }
    do
     {
      setmem(Msg, sizeof(Msg), 0);
      setmem(XMsg, sizeof(XMsg), 0);
      setmem(YMsg, sizeof(YMsg), 0);
      setmem(DelaiMsg, sizeof(DelaiMsg), 0);
      MsgCrt=0; MsgNv=0;
      setmem(ef, sizeof(ef),0);
      tbonus=0;
      for(i=0;i<nf;i++) tnaiss[i]=10*i;
       do
       {
        TypeSon=0;
        if (AvecPortes)
         {
          if (QuatreAs) TesteFile();
          TestePortes();
         }
        TesteClavier();
        TesteFantomes();
        AfficheScore();
        if (Perdu!=1)
         {
          Deplacements();
          if (dp!=INDEFINI)
           {
            if PORTE(xp, yp)
             Bloquee[Table[xp][yp]]&=255-PAC;
            if (!transposition)
             {
              xp+=dx[dp];
              yp+=dy[dp];
             }
            else
             {
              transposition=0;
              xp=xt; yp=yt;
             }
            if PORTE(xp, yp)
             Bloquee[Table[xp][yp]]|=PAC;
           }
          for(i=0;i<nf;i++)
           if ((ef[i])&&(df[i]!=INDEFINI))
            {
             if PORTE(xf[i], yf[i])
              Bloquee[Table[xf[i]][yf[i]]]&=255-FANTOME;
             xf[i]+=dx[df[i]];
             yf[i]+=dy[df[i]];
             if PORTE(xf[i], yf[i])
              Bloquee[Table[xf[i]][yf[i]]]|=FANTOME;
            }
         }
        else FaireSon();
        PerPorte=(PerPorte+1)%NbPortes;
       }
      while(!Perdu);
      if (Perdu==3)
       {
        ModeTexte(3);
        printf("\nPourquoi t'as quitt‚ ? Je veux jouer !\n");
        exit(0);
       }
      if (Perdu==1) MortPac();
      else
       {
        for(i=0;i<10;i++)
         {
          sound(Son*Frq[i/5][i%5]);
          delay(100);
         }
        nosound();
       }
      for(i=0;i<nf;i++)
       {
        if PORTE(xf[i], yf[i])
         Bloquee[Table[xf[i]][yf[i]]]&=255-FANTOME;
        GOTOXY(xf[i], yf[i]);
        printcar(CarCas[c[xf[i]][yf[i]]], ColCas[c[xf[i]][yf[i]]]);
       }
      if (Perdu==2)
       {
        nf++;
       }
      if (Perdu==1)
       {
        AfficheVies();
        Vies--;
       }
      Perdu=0;
     }
    while((1+Vies)&&(NbGraines[0]+NbGraines[1]+NbGraines[2]+NbGraines[3]));
    TesteRecords(1);
   }
 }
