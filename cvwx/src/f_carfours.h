//---------------------------------------------------------------------------
#ifndef f_carfoursH
#define f_carfoursH
//---------------------------------------------------------------------------
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.VirtualImageList.hpp>
//---------------------------------------------------------------------------
class TfrmCarrefours : public TForm
{
__published:	// Composants gérés par l'EDI
    TGroupBox *GroupBox34;
    TSpeedButton *SpeedButton34b1;
    TSpeedButton *SpeedButton34b2;
    TSpeedButton *SpeedButton34b3;
    TSpeedButton *SpeedButton34a3;
    TSpeedButton *SpeedButton34a2;
    TSpeedButton *SpeedButton34a1;
    TGroupBox *GroupBox43;
    TSpeedButton *SpeedButton43b1;
    TSpeedButton *SpeedButton43b2;
    TSpeedButton *SpeedButton43b3;
    TSpeedButton *SpeedButton43a3;
    TSpeedButton *SpeedButton43a2;
    TSpeedButton *SpeedButton43a1;
    TGroupBox *GroupBox44;
    TSpeedButton *SpeedButton44b;
    TSpeedButton *SpeedButton44c;
    TSpeedButton *SpeedButton44a;
    TGroupBox *GroupBox66;
    TSpeedButton *SpeedButton66a;
    TSpeedButton *SpeedButton66b;
    TGroupBox *GroupBox88;
    TSpeedButton *SpeedButton88;
    TButton *ButtonAnnuler;
    TLabel *Label;
    TButton *ButtonAide;
	TImageCollection *ImageCollection;
	TVirtualImageList *VirtualImageList64;
	TVirtualImageList *VirtualImageList96;
	TVirtualImageList *VirtualImageList128;
    void __fastcall SpeedButtonClick(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    
private:	// Déclarations de l'utilisateur
	void AffecteGlyphe(TVirtualImageList *VirtualImageList, const int NumGlyphe, TBitmap *Glyphe)
	 { // v5.4 pour affecter les SpeedButton->Glyph à partir des virtualImageList et supporter le HDPI
	  VirtualImageList->GetBitmap(NumGlyphe, Glyphe);
	 };
public:		// Déclarations de l'utilisateur
    __fastcall TfrmCarrefours(TComponent* Owner);
    void Active(int Colonnes, int Lignes);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCarrefours *frmCarrefours;
extern int Carrefours(int Colonnes, int Lignes);
//---------------------------------------------------------------------------
#endif
