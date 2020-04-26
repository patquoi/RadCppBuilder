//---------------------------------------------------------------------------
#ifndef apropos_fH
#define apropos_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmAPropos : public TForm
{
__published:	// Composants gérés par l'EDI
    TTimer *Timer;
    TPanel *Panel1;
    TPanel *Panel2;
    TPanel *Panel3;
    TPopupMenu *PopupMenu;
    TMenuItem *RubriqueFermer;
    TLabel *LabelUrl;
    TLabel *LabelEMail;
        TPanel *Panel4;
	TStatusBar *StatusBar;
	TPanel *PanelAlignement;
	TPanel *PanelHDPI;
    void __fastcall TimerTimer(TObject *Sender);
    
    
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall FormPaint(TObject *Sender);
    
    void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall RubriqueFermerClick(TObject *Sender);
    void __fastcall LabelUrlClick(TObject *Sender);
    void __fastcall LabelEMailClick(TObject *Sender);
    
private:	// Déclarations de l'utilisateur
    void DessineHexagone(int x, int y, int Couleur);
	void AfficheValeurs(int x, int y, char Lettre, int Score, int Fond, TColor Couleur);
    void AfficheCase(int x, int y, char Lettre, int NumlCoul);
    void AfficheBouton(TColor clCouleur);
public:		// Déclarations de l'utilisateur
    __fastcall TfrmAPropos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAPropos *frmAPropos;
//---------------------------------------------------------------------------
#endif
