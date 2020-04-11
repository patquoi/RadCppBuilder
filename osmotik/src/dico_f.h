//---------------------------------------------------------------------------
#ifndef dico_fH
#define dico_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cgauges.h"
#include <ComCtrls.hpp>
#include "CGAUGES.h"
//---------------------------------------------------------------------------
class TFormDico : public TForm
{
__published:	// Composants gérés par l'EDI
    TCGauge *CGauge;
    TStatusBar *StatusBar;
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    __fastcall TFormDico(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDico *FormDico;
//---------------------------------------------------------------------------
#endif
