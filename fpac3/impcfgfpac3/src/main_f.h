//---------------------------------------------------------------------------

#ifndef main_fH
#define main_fH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// Composants gérés par l'EDI
	TImageList *ImageList;
	TImage *Image1;
	TImage *Image2;
	TLabel *Label1;
	TLabel *Label2;
	TButton *ButtonRechercher;
	TImage *Image3;
	TLabel *Label3;
	TTimer *Timer;
	TLabeledEdit *LabeledEditLocalAppData;
	TBevel *Bevel1;
	TLabeledEdit *LabeledEditDossierCourant;
	TImage *Image4;
	TImage *Image5;
	TLabel *LabelParametres;
	TButton *ButtonImporter;
	TTimer *TimerRecherche;
	TButton *Button0;
	TButton *ButtonSelectionner;
	TOpenDialog *OpenDialogFPac3Ini;
	TButton *Button1;
	TRadioGroup *RadioGroupModeImport;
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall ButtonRechercherClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button0Click(TObject *Sender);
	void __fastcall ButtonSelectionnerClick(TObject *Sender);
	void __fastcall TimerRechercheTimer(TObject *Sender);
	void __fastcall ButtonImporterClick(TObject *Sender);
private:	// Déclarations utilisateur
	void AffecteImage(const int ImageId, const bool Coche);
	bool FichierExistantEtDeTailleNonNulle(const String stNomFichier);
	bool TrouveFichierFPac3Ini(const String stChemin);
	void AnalyseDossierTrouve();
public:		// Déclarations utilisateur
	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
extern const String stFiltreFPac3Ini;
//---------------------------------------------------------------------------
#endif
