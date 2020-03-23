//---------------------------------------------------------------------------
#ifndef winlinuxH
#define winlinuxH
//---------------------------------------------------------------------------
#include "vclx.h"
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
// Propriétés de TCSpinEdit
#define MINVALUE MinValue
#define MAXVALUE MaxValue
// Propriétés de TOpen/CloseDialog
#define FILENAME(x) ((x)->FileName)
// Types
#define TBITMAP Graphics::TBitmap
#define TSPINEDIT TCSpinEdit
#define CONTROLCOUNT ControlCount
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
// Hauteur/Largeur de l'espace entre les objets/bord
// Pour les mesures automatiques de taille de fenêtre (OnResize)
#define LH_ESPACE 8
#define XMAX(x) ((x)->Left+(x)->Width)
#define YMAX(y) ((y)->Top+(y)->Height)
#define LMAX(x,y) (max(XMAX(x),XMAX(y)))
#define HMAX(x,y) (max(YMAX(x),YMAX(y)))

// Propriétés de TSpinEdit
#define MINVALUE Min
#define MAXVALUE Max
// Propriétés de TOpen/CloseDialog
#define FILENAME(x) ((AnsiString)((x)->FileName))
// Type TBitMap
#define TBITMAP TBitmap
#define TSPINEDIT TSpinEdit
#define CONTROLCOUNT ControlCount()
#endif
//---------------------------------------------------------------------------
enum type_message {tmInformation, tmAvertissement, tmErreur, tmQuestionNecessaire, tmQuestionFacultative};
enum type_reponse {trOk, trAnnuler, trOui, trNon};
//---------------------------------------------------------------------------
extern const AnsiString asDebutNomSpinEdit;
//---------------------------------------------------------------------------
extern type_reponse AfficheMessage(const AnsiString asMessage, const AnsiString asTitre, type_message Type, int OrdreBoutonDefaut, int OrdreBoutonEchap);
extern void AfficheAideContextuelle(TForm *Form);
extern void AfficheIndexAide(TForm *Form);
//---------------------------------------------------------------------------
#endif
