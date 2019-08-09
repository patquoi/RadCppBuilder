#define NBX         134
#define NBY          50
#define XMAX        133
#define YMAX         49
#define TXTMODEINIT  35

const char Help[]="\
\nSyntaxe : FPC14350 [Options]\n\
Options [Valeurs par d‚faut]:\n\
?          Affiche cette aide.\n\
S          Jeu sans son, [son activ‚].\n\
R          Cr‚e ou r‚initialise le top-10.\n\
!=nom      nom=Nom du joueur (32 caractŠres maximum).\n\
P=p‚riode  p‚riode=P‚riode d'affichage en millisecondes (1<p‚riode<999) [100].\n\
G=mode     Mode de recherche des fant“mes : 0=hazardeux, 99=d‚termin‚ [50].\n\
L=n        n=Nombre de pilules pour une Pac-Gum (0<=n<=999) [100].\n\
E=d        d=Dur‚e lorsque les fant“mes sont mangeables (1<=d<=1000) [100].\n\
N=n        n=Nombre de fant“mes au d‚but du jeu (0<n<8) [4].\n\
M=mode     Mode Texte 143x50 Min. avec les caractŠres 8x8 [3]\n\
D=n        n=Nombre de portes (0<=n<=199) [50]\n";

#include "fpac.c"
