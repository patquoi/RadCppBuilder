//---------------------------------------------------------------------------
#ifndef f_prmtramH
#define f_prmtramH
//---------------------------------------------------------------------------
#include "CSPIN.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "base.h"
//---------------------------------------------------------------------------
class TfrmParamTram : public TForm
{
__published:	// Composants gérés par l'EDI
    TGroupBox *GroupBox1;
    TLabel *Label3;
    TLabel *Label2;
    TShape *Shape1;
    TShape *Shape2;
    TShape *Shape3;
    TShape *Shape4;
    TShape *Shape5;
    TShape *Shape6;
    TShape *Shape8;
    TShape *Shape7;
    TLabel *LabelLigne;
    TLabel *Label5;
    TLabel *Label6;
 TCSpinEdit *CSpinEdit1;
 TCSpinEdit *CSpinEdit2;
 TCSpinEdit *CSpinEdit3;
 TCSpinEdit *CSpinEdit4;
 TCSpinEdit *CSpinEdit5;
 TCSpinEdit *CSpinEdit6;
 TCSpinEdit *CSpinEdit7;
 TCSpinEdit *CSpinEdit8;
 TCSpinEdit *CSpinEdit11;
 TCSpinEdit *CSpinEdit12;
 TCSpinEdit *CSpinEdit13;
 TCSpinEdit *CSpinEdit14;
 TCSpinEdit *CSpinEdit15;
 TCSpinEdit *CSpinEdit16;
 TCSpinEdit *CSpinEdit17;
 TCSpinEdit *CSpinEdit18;
 TCSpinEdit *CSpinEdit19;
 TCSpinEdit *CSpinEdit21;
 TCSpinEdit *CSpinEdit22;
 TCSpinEdit *CSpinEdit23;
 TCSpinEdit *CSpinEdit24;
 TCSpinEdit *CSpinEdit25;
 TCSpinEdit *CSpinEdit26;
 TCSpinEdit *CSpinEdit27;
 TCSpinEdit *CSpinEdit28;
 TCSpinEdit *CSpinEdit29;
 TCSpinEdit *CSpinEdit31;
 TCSpinEdit *CSpinEdit32;
 TCSpinEdit *CSpinEdit33;
 TCSpinEdit *CSpinEdit34;
 TCSpinEdit *CSpinEdit35;
 TCSpinEdit *CSpinEdit36;
 TCSpinEdit *CSpinEdit37;
 TCSpinEdit *CSpinEdit38;
 TCSpinEdit *CSpinEdit39;
 TCSpinEdit *CSpinEdit41;
 TCSpinEdit *CSpinEdit42;
 TCSpinEdit *CSpinEdit43;
 TCSpinEdit *CSpinEdit44;
 TCSpinEdit *CSpinEdit45;
 TCSpinEdit *CSpinEdit46;
 TCSpinEdit *CSpinEdit47;
 TCSpinEdit *CSpinEdit48;
 TCSpinEdit *CSpinEdit49;
 TCSpinEdit *CSpinEdit51;
 TCSpinEdit *CSpinEdit52;
 TCSpinEdit *CSpinEdit53;
 TCSpinEdit *CSpinEdit54;
 TCSpinEdit *CSpinEdit55;
 TCSpinEdit *CSpinEdit56;
 TCSpinEdit *CSpinEdit57;
 TCSpinEdit *CSpinEdit58;
 TCSpinEdit *CSpinEdit59;
 TCSpinEdit *CSpinEdit61;
 TCSpinEdit *CSpinEdit62;
 TCSpinEdit *CSpinEdit63;
 TCSpinEdit *CSpinEdit64;
 TCSpinEdit *CSpinEdit65;
 TCSpinEdit *CSpinEdit66;
 TCSpinEdit *CSpinEdit67;
 TCSpinEdit *CSpinEdit68;
 TCSpinEdit *CSpinEdit69;
 TCSpinEdit *CSpinEdit71;
 TCSpinEdit *CSpinEdit72;
 TCSpinEdit *CSpinEdit73;
 TCSpinEdit *CSpinEdit74;
 TCSpinEdit *CSpinEdit75;
 TCSpinEdit *CSpinEdit76;
 TCSpinEdit *CSpinEdit77;
 TCSpinEdit *CSpinEdit78;
 TCSpinEdit *CSpinEdit79;
 TCSpinEdit *CSpinEdit81;
 TCSpinEdit *CSpinEdit82;
 TCSpinEdit *CSpinEdit83;
 TCSpinEdit *CSpinEdit84;
 TCSpinEdit *CSpinEdit85;
 TCSpinEdit *CSpinEdit86;
 TCSpinEdit *CSpinEdit87;
 TCSpinEdit *CSpinEdit88;
 TCSpinEdit *CSpinEdit89;
 TCSpinEdit *CSpinEdit9;
 TCSpinEdit *CSpinEdit91;
 TCSpinEdit *CSpinEdit92;
 TCSpinEdit *CSpinEdit93;
 TCSpinEdit *CSpinEdit94;
 TCSpinEdit *CSpinEdit95;
 TCSpinEdit *CSpinEdit96;
 TCSpinEdit *CSpinEdit97;
 TCSpinEdit *CSpinEdit98;
 TCSpinEdit *CSpinEdit99;
 TCSpinEdit *CSpinEditProbaArretDmd;
 TCSpinEdit *CSpinEditNbMaxPersonnesTram;
 TCSpinEdit *CSpinEditNbToursStopArretTram;
 TCSpinEdit *CSpinEditNbCasesMaxArretTram;
 TCSpinEdit *CSpinEditProbaDirArretTram;
 TCSpinEdit *CSpinEditNbMaxToursAttenteTram;
    TShape *Shape9;
    TButton *ButtonAide;
    TLabel *LabelL1;
    TLabel *LabelL2;
    TLabel *LabelL3;
    TLabel *LabelL4;
    TLabel *LabelL5;
    TLabel *LabelL6;
    TLabel *LabelL7;
    TLabel *LabelL8;
    TLabel *LabelL9;
    TBitBtn *BitBtn21;
    TBitBtn *BitBtn31;
    TBitBtn *BitBtn11;
    TBitBtn *BitBtn13;
    TBitBtn *BitBtn23;
    TBitBtn *BitBtn33;
    TBitBtn *BitBtn12;
    TBitBtn *BitBtn32;
    TPopupMenu *PopupMenu;
    TMenuItem *MenuItemHautGauche;
    TMenuItem *MenuItemHaut;
    TMenuItem *MenuItemHautDroite;
    TMenuItem *Sep1;
    TMenuItem *MenuItemGauche;
    TMenuItem *MenuItemDroite;
    TMenuItem *MenuItemZoom;
    TMenuItem *Sep2;
    TMenuItem *MenuItemBasGauche;
    TMenuItem *MenuItemBas;
    TMenuItem *MenuItemBasDroite;
    TCheckBox *CheckBoxCoins;
    TTimer *TimerClignotement;
    TButton *ButtonOk;
    TButton *ButtonAnnuler;
    TButton *ButtonAppliquer;
    TLabel *Label18;
    TGroupBox *GroupBox2;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *Label15;
    TLabel *Label16;
    TGroupBox *GroupBox3;
    TLabel *LabelNbCasesMaxPsgPtn;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label17;
    TLabel *LabelProbaPsgPt;
    TLabel *Label25;
    TLabel *Label26;
    TLabel *Label27;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
    TCheckBox *CheckBox5;
    TCheckBox *CheckBox6;
    TCheckBox *CheckBox7;
    TCheckBox *CheckBox8;
    TCheckBox *CheckBox9;
    TCheckBox *CheckBoxTout;
    TShape *ShapeT;
    TLabel *LabelT;
    TLabel *LabelNbArretsTram;
    TLabel *LabelNbMaxArretsTram;
    TLabel *LabelNbTrams;
    TLabel *LabelRqCochesLignesTram;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall CSpinEditChange(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
    void __fastcall MenuItemClick(TObject *Sender);
    void __fastcall BitBtnDirClick(TObject *Sender);
    void __fastcall TimerClignotementTimer(TObject *Sender);
    
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAppliquerClick(TObject *Sender);
    
    void __fastcall CSpinEditParametresChange(TObject *Sender);
    void __fastcall CheckBoxClick(TObject *Sender);
    
    void __fastcall CheckBoxToutClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// Déclarations de l'utilisateur
    int NbArretsTram;
    bool InitialisationEnCours;
    void RafraichitNbTrams();
    bool AppliqueChoix();
public:		// Déclarations de l'utilisateur
    int NumArretTramAMontrer;
    __fastcall TfrmParamTram(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmParamTram *frmParamTram;
//---------------------------------------------------------------------------
#endif
  