//---------------------------------------------------------------------------

#ifndef dtlcfg_fH
#define dtlcfg_fH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
#define NBENTREES		6

#define DIMENSIONS		0
#define AGRESSIVITE		1
#define RAPPORTPPG		2
#define VULNERABILITE	3
#define	FANTOMES		4
#define PORTES          5
//---------------------------------------------------------------------------
class TFormDetailConfig : public TForm
{
__published: // Composants gérés par l'EDI
	TImageList *ImageList;
	TLabeledEdit *LabeledEditFichierIni;
	TLabeledEdit *LabeledEditDateHeureModification;
	TTreeView *TreeView;
	void __fastcall FormShow(TObject *Sender);
private:
	void LitParametres();
public:
	__fastcall TFormDetailConfig(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDetailConfig *FormDetailConfig;
//---------------------------------------------------------------------------
#endif
