//---------------------------------------------------------------------------
#ifndef f_statsH
#define f_statsH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#endif
//---------------------------------------------------------------------------
class TfrmStatistiques : public TForm
{
__published:	// Composants g�r�s par l'EDI
    TPaintBox *PaintBoxStats;
    void __fastcall PaintBoxStatsPaint(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:	// D�clarations de l'utilisateur
public:		// D�clarations de l'utilisateur
    __fastcall TfrmStatistiques(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStatistiques *frmStatistiques;
//---------------------------------------------------------------------------
#endif
