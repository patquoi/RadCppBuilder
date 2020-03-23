//---------------------------------------------------------------------------
#ifndef f_proposH
#define f_proposH
//---------------------------------------------------------------------------
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "base.h"
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
    TLabel *LabelTexte;
    TSpeedButton *SpeedButtonOk;
    TLabel *LabelCV2;
    TLabel *LabelAuteur2;
    TLabel *LabelSousVersion;
  TLabel *LabelGPL1;
  TLabel *LabelGPL2;
  TImage *ImageVersion;
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall LabelURLClick(TObject *Sender);
    void __fastcall LabelEMailClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall LabelClick(TObject *Sender);
private:
    int TempsEcoule;
    TBITMAP *Bitmap;
public:		// D�clarations de l'utilisateur
    bool FermetureAutomatique;
    __fastcall TfrmAPropos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAPropos *frmAPropos;
//---------------------------------------------------------------------------
#endif
