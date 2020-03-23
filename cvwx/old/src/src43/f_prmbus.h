//---------------------------------------------------------------------------
#ifndef f_prmbusH
#define f_prmbusH
//---------------------------------------------------------------------------
#ifdef CV_WINDOWSLINUX
#include "CSPIN.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QMenus.hpp>
#include <QStdCtrls.hpp>
#include <QComCtrls.hpp>
#include <QTypes.hpp>
#endif

#ifdef CV_WINDOWS
#include "CSPIN.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#endif

#ifdef CV_LINUX
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QMenus.hpp>
#include <QStdCtrls.hpp>
#include <QComCtrls.hpp>
#include <QTypes.hpp>
#endif

#include "winlinux.h"
//---------------------------------------------------------------------------
class TfrmParamBus : public TForm
{
__published:	// Composants gérés par l'EDI
    TGroupBox *GroupBox1;
    TLabel *LabelNbArretsBus;
    TLabel *Label3;
    TLabel *Label2;
    TLabel *LabelNbMaxArretsBus;
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
    TSPINEDIT *CSpinEdit1;
    TSPINEDIT *CSpinEdit2;
    TSPINEDIT *CSpinEdit3;
    TSPINEDIT *CSpinEdit4;
    TSPINEDIT *CSpinEdit5;
    TSPINEDIT *CSpinEdit6;
    TSPINEDIT *CSpinEdit7;
    TSPINEDIT *CSpinEdit8;
    TSPINEDIT *CSpinEdit11;
    TSPINEDIT *CSpinEdit12;
    TSPINEDIT *CSpinEdit13;
    TSPINEDIT *CSpinEdit14;
    TSPINEDIT *CSpinEdit15;
    TSPINEDIT *CSpinEdit16;
    TSPINEDIT *CSpinEdit17;
    TSPINEDIT *CSpinEdit18;
    TSPINEDIT *CSpinEdit19;
    TSPINEDIT *CSpinEdit21;
    TSPINEDIT *CSpinEdit22;
    TSPINEDIT *CSpinEdit23;
    TSPINEDIT *CSpinEdit24;
    TSPINEDIT *CSpinEdit25;
    TSPINEDIT *CSpinEdit26;
    TSPINEDIT *CSpinEdit27;
    TSPINEDIT *CSpinEdit28;
    TSPINEDIT *CSpinEdit29;
    TSPINEDIT *CSpinEdit31;
    TSPINEDIT *CSpinEdit32;
    TSPINEDIT *CSpinEdit33;
    TSPINEDIT *CSpinEdit34;
    TSPINEDIT *CSpinEdit35;
    TSPINEDIT *CSpinEdit36;
    TSPINEDIT *CSpinEdit37;
    TSPINEDIT *CSpinEdit38;
    TSPINEDIT *CSpinEdit39;
    TSPINEDIT *CSpinEdit41;
    TSPINEDIT *CSpinEdit42;
    TSPINEDIT *CSpinEdit43;
    TSPINEDIT *CSpinEdit44;
    TSPINEDIT *CSpinEdit45;
    TSPINEDIT *CSpinEdit46;
    TSPINEDIT *CSpinEdit47;
    TSPINEDIT *CSpinEdit48;
    TSPINEDIT *CSpinEdit49;
    TSPINEDIT *CSpinEdit51;
    TSPINEDIT *CSpinEdit52;
    TSPINEDIT *CSpinEdit53;
    TSPINEDIT *CSpinEdit54;
    TSPINEDIT *CSpinEdit55;
    TSPINEDIT *CSpinEdit56;
    TSPINEDIT *CSpinEdit57;
    TSPINEDIT *CSpinEdit58;
    TSPINEDIT *CSpinEdit59;
    TSPINEDIT *CSpinEdit61;
    TSPINEDIT *CSpinEdit62;
    TSPINEDIT *CSpinEdit63;
    TSPINEDIT *CSpinEdit64;
    TSPINEDIT *CSpinEdit65;
    TSPINEDIT *CSpinEdit66;
    TSPINEDIT *CSpinEdit67;
    TSPINEDIT *CSpinEdit68;
    TSPINEDIT *CSpinEdit69;
    TSPINEDIT *CSpinEdit71;
    TSPINEDIT *CSpinEdit72;
    TSPINEDIT *CSpinEdit73;
    TSPINEDIT *CSpinEdit74;
    TSPINEDIT *CSpinEdit75;
    TSPINEDIT *CSpinEdit76;
    TSPINEDIT *CSpinEdit77;
    TSPINEDIT *CSpinEdit78;
    TSPINEDIT *CSpinEdit79;
    TSPINEDIT *CSpinEdit81;
    TSPINEDIT *CSpinEdit82;
    TSPINEDIT *CSpinEdit83;
    TSPINEDIT *CSpinEdit84;
    TSPINEDIT *CSpinEdit85;
    TSPINEDIT *CSpinEdit86;
    TSPINEDIT *CSpinEdit87;
    TSPINEDIT *CSpinEdit88;
    TSPINEDIT *CSpinEdit89;
    TSPINEDIT *CSpinEdit9;
    TSPINEDIT *CSpinEdit91;
    TSPINEDIT *CSpinEdit92;
    TSPINEDIT *CSpinEdit93;
    TSPINEDIT *CSpinEdit94;
    TSPINEDIT *CSpinEdit95;
    TSPINEDIT *CSpinEdit96;
    TSPINEDIT *CSpinEdit97;
    TSPINEDIT *CSpinEdit98;
    TSPINEDIT *CSpinEdit99;
    TSPINEDIT *CSpinEditNbToursStopArretBus;
    TSPINEDIT *CSpinEditNbMaxPersonnesBus;
    TSPINEDIT *CSpinEditNbCasesMaxArretBus;
    TSPINEDIT *CSpinEditNbMaxToursAttenteBus;
    TSPINEDIT *CSpinEditProbaDirArretBus;
    TSPINEDIT *CSpinEditProbaArretDmd;
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
    TBitBtn *BitBtn22;
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
    TLabel *LabelNbBus;
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
    TLabel *LabelRqCochesLignesBus;
    TCheckBox *CheckBoxTout;
    TShape *ShapeT;
    TLabel *LabelT;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall CSpinEditChange(TObject *Sender);
    void __fastcall ButtonAideClick(TObject *Sender);
    void __fastcall MenuItemClick(TObject *Sender);
    void __fastcall BitBtnDirClick(TObject *Sender);
    void __fastcall BitBtn22Click(TObject *Sender);
    void __fastcall TimerClignotementTimer(TObject *Sender);
    
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall ButtonAppliquerClick(TObject *Sender);
    
    void __fastcall CSpinEditParametresChange(TObject *Sender);
    void __fastcall CheckBoxClick(TObject *Sender);
    
    void __fastcall CheckBoxToutClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
    int NbArretsBus;
    bool InitialisationEnCours;
    void RafraichitNbBus();
    bool AppliqueChoix();
public:		// Déclarations de l'utilisateur
    int NumArretBusAMontrer;
    __fastcall TfrmParamBus(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmParamBus *frmParamBus;
//---------------------------------------------------------------------------
#endif
  