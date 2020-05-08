//---------------------------------------------------------------------------
#ifndef diplome_fH
#define diplome_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include <System.ImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.VirtualImageList.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmDiplome : public TForm
{
__published:	// Composants gérés par l'EDI
    TLabel *LabelDiplomeArriere;
    TLabel *LabelDiplomeAvant;
    TShape *Shape0;
    TShape *Shape1;
    TShape *Shape2;
    TShape *Shape3;
    TShape *Shape4;
    TShape *Shape5;
    TShape *Shape6;
    TShape *Shape7;
    TShape *Shape8;
    TShape *Shape9;
    TShape *ShapeA;
    TShape *ShapeB;
    TShape *ShapeC;
    TShape *ShapeD;
    TShape *ShapeE;
    
    TLabel *LabelNomJoueur;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *LabelNomSerie;
    TLabel *LabelNbNiveaux;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *LabelScore;
    TLabel *Label5;
    TPopupMenu *PopupMenu;
	TMenuItem *RubriqueExporter;
	TMenuItem *RubriqueFermer;
	TImageCollection *ImageCollection;
	TVirtualImageList *VirtualImageList;
	TMenuItem *RubriqueCopier;
	TSaveDialog *SaveDialogImage;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall RubriqueFermerClick(TObject *Sender);
    
    void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall RubriqueCopierClick(TObject *Sender);
	void __fastcall RubriqueExporterClick(TObject *Sender);
private:	// Déclarations de l'utilisateur
    TBitmap *bmDiplome;
public:		// Déclarations de l'utilisateur
    __fastcall TfrmDiplome(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDiplome *frmDiplome;
//---------------------------------------------------------------------------
#endif
