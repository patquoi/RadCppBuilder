//---------------------------------------------------------------------------
#ifndef dico_fH
#define dico_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "CGAUGES.h"
//---------------------------------------------------------------------------
class TfrmDico : public TForm
{
__published:	// Composants g�r�s par l'EDI
    TCGauge *CGauge;
    TStatusBar *StatusBar;
private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    __fastcall TfrmDico(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDico *frmDico;
//---------------------------------------------------------------------------
#endif
