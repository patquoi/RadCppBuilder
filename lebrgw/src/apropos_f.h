//---------------------------------------------------------------------------
#ifndef apropos_fH
#define apropos_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <System.ImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.VirtualImageList.hpp>
//---------------------------------------------------------------------------
class TfrmAPropos : public TForm
{
__published:	// Composants gérés par l'EDI
    TImage *Image;
    TTimer *Timer;
    TLabel *LabelURL;
    TLabel *LabelEMail;
    TLabel *LabelVersion;
    TLabel *Label1;
	TLabel *LabelAlignement;
	void __fastcall FormShow(TObject *Sender);
    void __fastcall TimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall LabelURLClick(TObject *Sender);
	void __fastcall LabelEMailClick(TObject *Sender);
	void __fastcall Label1Click(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    __fastcall TfrmAPropos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAPropos *frmAPropos;
//---------------------------------------------------------------------------
#endif
