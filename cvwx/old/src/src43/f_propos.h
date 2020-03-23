//---------------------------------------------------------------------------
#ifndef f_proposH
#define f_proposH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QGraphics.hpp>
#include <QImgList.hpp>
#include <QStdCtrls.hpp>
#include <QTypes.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <StdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QGraphics.hpp>
#include <QImgList.hpp>
#include <QStdCtrls.hpp>
#include <QTypes.hpp>
#endif
//---------------------------------------------------------------------------
#include "winlinux.h"
//---------------------------------------------------------------------------
class TfrmAPropos : public TForm
{
__published:
    TImageList *ImageList;
    TTimer *Timer;
    TLabel *LabelCV1;
    TLabel *LabelAuteur1;
    TLabel *LabelEMail;
    TLabel *LabelURL;
    TImage *ImageVersion;
    TLabel *LabelTexte;
    TSpeedButton *SpeedButtonOk;
    TLabel *LabelCV2;
    TLabel *LabelAuteur2;
    TLabel *LabelSousVersion;
  TLabel *LabelGPL1;
  TLabel *LabelGPL2;
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall LabelURLClick(TObject *Sender);
    void __fastcall LabelEMailClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall SpeedButtonOkClick(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall LabelGPL2Click(TObject *Sender);
private:
    int TempsEcoule;
    TBITMAP *Bitmap;
public:		// Déclarations de l'utilisateur
    bool FermetureAutomatique;
    __fastcall TfrmAPropos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAPropos *frmAPropos;
//---------------------------------------------------------------------------
#endif
