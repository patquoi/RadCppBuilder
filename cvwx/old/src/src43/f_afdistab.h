//---------------------------------------------------------------------------
#ifndef f_afdistabH
#define f_afdistabH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <Classes.hpp>
#include <QControls.hpp>
#include <QGrids.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QControls.hpp>
#include <QGrids.hpp>
#endif
//---------------------------------------------------------------------------
class TfrmAffDistArretsBus : public TForm
{
__published:	// Composants g�r�s par l'EDI
    TStringGrid *StringGridDistances;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    
    
private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    __fastcall TfrmAffDistArretsBus(TComponent* Owner);
    void EffaceInfos();
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAffDistArretsBus *frmAffDistArretsBus;
//---------------------------------------------------------------------------
#endif
