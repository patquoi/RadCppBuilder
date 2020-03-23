//---------------------------------------------------------------------------
#ifndef f_statsatH
#define f_statsatH
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
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QMenus.hpp>
#include <QStdCtrls.hpp>
#include <QTypes.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include "CSPIN.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QMenus.hpp>
#include <QStdCtrls.hpp>
#include <QTypes.hpp>
#endif
//---------------------------------------------------------------------------
#include "winlinux.h"
//---------------------------------------------------------------------------
class TfrmStatsAttenteTrafic : public TForm
{
__published:	// Composants gérés par l'EDI
    TRadioGroup *RadioGroupType;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *LabelAttenteCumulee;
    TLabel *LabelAttenteMoyenne;
    TLabel *LabelAttenteMaximale;
    TLabel *LabelTraficCumule;
    TLabel *LabelTraficMoyen;
    TLabel *LabelTraficMaximal;
    TLabel *Label8;
    TGroupBox *GroupBoxEtapes;
    TSPINEDIT *CSpinEditEtapeArrivee;
    TCheckBox *CheckBoxEtapeArrivee;
    TCheckBox *CheckBoxEtapeDepart;
    TSPINEDIT *CSpinEditEtapeDepart;
    TGroupBox *GroupBoxLegende;
    TLabel *LabelMax;
    TLabel *Label10;
    TPaintBox *PaintBox;
    TBitBtn *BitBtn21;
    TBitBtn *BitBtn31;
    TBitBtn *BitBtn11;
    TBitBtn *BitBtn13;
    TBitBtn *BitBtn23;
    TBitBtn *BitBtn33;
    TBitBtn *BitBtn12;
    TBitBtn *BitBtn32;
    TBitBtn *BitBtn22;
    TCheckBox *CheckBoxCoins;
    TPopupMenu *PopupMenu;
    TMenuItem *RubriqueHautGauche;
    TMenuItem *RubriqueHaut;
    TMenuItem *RubriqueHautDroite;
    TMenuItem *RubriqueGauche;
    TMenuItem *RubriqueDroite;
    TMenuItem *RubriqueBasGauche;
    TMenuItem *RubriqueBas;
    TMenuItem *RubriqueBasDroite;
    TMenuItem *Sep1;
    TMenuItem *Sep2;
    TMenuItem *RubriqueZoom;
    void __fastcall PaintBoxPaint(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);

    void __fastcall ParametresEtapesClick(TObject *Sender);
    void __fastcall RadioGroupTypeClick(TObject *Sender);
    void __fastcall BitBtn22Click(TObject *Sender);
    void __fastcall BitBtnDirClick(TObject *Sender);

    void __fastcall RubriqueClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// Déclarations de l'utilisateur
    int m[2];
    void RecalculeEtVisualise();

public:		// Déclarations de l'utilisateur
    __fastcall TfrmStatsAttenteTrafic(TComponent* Owner);
    TColor CouleurCase(int x, int y);
    AnsiString asMsgDetailCase(int x, int y);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStatsAttenteTrafic *frmStatsAttenteTrafic;
//---------------------------------------------------------------------------
#endif
