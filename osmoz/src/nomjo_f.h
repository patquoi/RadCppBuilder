//---------------------------------------------------------------------------
#ifndef nomjo_fH
#define nomjo_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <System.ImageList.hpp>
//---------------------------------------------------------------------------
class TfrmNomJoueurs : public TForm
{
__published:	// Composants gérés par l'EDI
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    TEdit *Edit4;
    TEdit *Edit5;
    TEdit *Edit6;
    TCheckBox *CheckBox1A;
    TCheckBox *CheckBox2A;
    TCheckBox *CheckBox3A;
    TCheckBox *CheckBox4A;
    TCheckBox *CheckBox5A;
    TCheckBox *CheckBox6A;
    TButton *Button1;
    TButton *Button2;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TRadioGroup *RadioGroupJoueurs;
    TStatusBar *StatusBar;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TCheckBox *CheckBox1D;
    TCheckBox *CheckBox2D;
    TCheckBox *CheckBox3D;
    TCheckBox *CheckBox4D;
    TCheckBox *CheckBox5D;
    TCheckBox *CheckBox6D;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TImageList *ImageList;
    TImage *Image1;
    TImage *Image2;
    TImage *Image3;
    TImage *Image4;
    TImage *Image5;
    TImage *Image6;
  TTrackBar *TrackBar1;
  TLabel *LabelRegle;
  TTrackBar *TrackBar2;
  TTrackBar *TrackBar3;
  TTrackBar *TrackBar4;
  TTrackBar *TrackBar5;
  TTrackBar *TrackBar6;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall RadioGroupJoueursClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
  void __fastcall CheckBoxAutomateClick(TObject *Sender);
    
private:	// Déclarations de l'utilisateur
    void DessineHexagone(int x, int y, int Couleur);
public:		// Déclarations de l'utilisateur
    bool NouvellePartie, NbJoueursModifiable;
    __fastcall TfrmNomJoueurs(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNomJoueurs *frmNomJoueurs;
//---------------------------------------------------------------------------
#endif
      