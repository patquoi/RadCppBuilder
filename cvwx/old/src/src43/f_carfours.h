//---------------------------------------------------------------------------
#ifndef f_carfoursH
#define f_carfoursH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#endif
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
    void __fastcall SpeedButtonClick(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
    
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    __fastcall TfrmCarrefours(TComponent* Owner);
    void Active(int Colonnes, int Lignes);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCarrefours *frmCarrefours;
extern int Carrefours(int Colonnes, int Lignes);
//---------------------------------------------------------------------------
#endif
