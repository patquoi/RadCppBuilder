//---------------------------------------------------------------------------
#ifndef f_afdistatH
#define f_afdistatH
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
class TfrmAffDistArretsTram : public TForm
{
__published:	// Composants gérés par l'EDI
    TStringGrid *StringGridDistances;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);


private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    __fastcall TfrmAffDistArretsTram(TComponent* Owner);
    void EffaceInfos();
    void RafraichitInfos();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAffDistArretsTram *frmAffDistArretsTram;
//---------------------------------------------------------------------------
#endif
