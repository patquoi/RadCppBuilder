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
//---------------------------------------------------------------------------
enum type_message {tmInformation, tmAvertissement, tmErreur, tmQuestionNecessaire, tmQuestionFacultative};
enum type_reponse {trOk, trAnnuler, trOui, trNon};
//---------------------------------------------------------------------------
extern const AnsiString asDebutNomSpinEdit; // v5.3
//---------------------------------------------------------------------------
// v5.3: DEBOGAGE dans cvw.log 
extern bool Debug;
extern void DebugOuvre(const AnsiString asNomFichierLog);
extern void DebugEcrit(const AnsiString asMessage);
extern void DebugFerme();
//---------------------------------------------------------------------------
extern type_reponse AfficheMessage(const AnsiString asMessage, const AnsiString asTitre, type_message Type, int OrdreBoutonDefaut, int OrdreBoutonEchap);
extern void AfficheAideContextuelle(TForm *Form);
extern void AfficheIndexAide(TForm *Form);
#endif

