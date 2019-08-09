//---------------------------------------------------------------------------
#ifndef f_defvpH
#define f_defvpH
//---------------------------------------------------------------------------
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "simul.h"
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmDefVoiePietons : public TForm
{
__published:	// Composants gérés par l'EDI
  TLabel *Label1;
  TLabel *LabelCoordonnees;
  TButton *ButtonOk;
  TButton *ButtonAnnuler;
  TButton *ButtonAppliquer;
  TButton *ButtonAide;
  TImage *ImageEE;
  TImage *ImageOO;
  TImage *ImageSS;
  TImage *ImageNN;
  TImage *ImageNE;
  TImage *ImageSE;
  TImage *ImageSO;
  TImage *ImageNO;
  TImage *ImageS;
  TImage *ImageO;
  TImage *ImageN;
  TImage *ImageE;
  TImage *Image0;
  TSpeedButton *SpeedButtonN;
  TSpeedButton *SpeedButtonE;
  TSpeedButton *SpeedButtonO;
  TSpeedButton *SpeedButtonS;
  TLabel *Label2;
  TImage *ImageAttention;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAppliquerClick(TObject *Sender);
    void __fastcall ButtonAnnulerClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall SpeedButtonClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Déclarations de l'utilisateur
    bool FeuExistant[NBDIR]; // Indique lors de l'affichage de la fenêtre, l'existence des feux. Sert à l'annulation (suppression)
    voie *v;
    int x, y, xfo[NBDIR], yfo[NBDIR];
    TSpeedButton *SpeedButton[NBDIR];
    TImage *Image[NBDIR];
    void DefinitFeu(direction Dir);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmDefVoiePietons(TComponent* Owner);
    void RafraichitInfos();
    void AppliqueChoix();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDefVoiePietons *frmDefVoiePietons;
//---------------------------------------------------------------------------
#endif
