//---------------------------------------------------------------------------
#ifndef baseH
#define baseH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
// Propriétés de TCSpinEdit
#define MINVALUE MinValue
#define MAXVALUE MaxValue
// Propriétés de TOpen/CloseDialog
#define FILENAME(x) ((x)->FileName)
// Types
#define TBITMAP Graphics::TBitmap
#define CONTROLCOUNT ControlCount
//----------------------------------------------------------------------------------------------------------------------
// Types énumérés. /!\ v5.4 : le type char a été forcé pour que l'énuméré ne prenne pas la taille d'un entier (4 octets)
//----------------------------------------------------------------------------------------------------------------------
enum type_message : char {tmInformation, tmAvertissement, tmErreur, tmQuestionNecessaire, tmQuestionFacultative};
enum type_reponse : char {trOk, trAnnuler, trOui, trNon};
//---------------------------------------------------------------------------
// v5.3: DEBOGAGE dans cvw.log
extern bool Debug;
extern void DebugOuvre();
extern void DebugEcrit(const AnsiString asMessage);
extern void DebugFerme();
//---------------------------------------------------------------------------
extern const AnsiString asDebutNomSpinEdit; // v5.4
//---------------------------------------------------------------------------
extern String stRepLocalAppData(); // v5.4
extern type_reponse AfficheMessage(const AnsiString asMessage, const AnsiString asTitre, type_message Type, int OrdreBoutonDefaut, int OrdreBoutonEchap);
extern void AfficheAideContextuelle(TForm *Form);
extern void AfficheIndexAide(TForm *Form);
extern void AfficheTutoriel(); // v5.4 (appelée par TfrmSimulation::ActionTutorielExecute
#endif

