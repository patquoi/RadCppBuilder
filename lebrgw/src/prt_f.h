//---------------------------------------------------------------------------
#ifndef prt_fH
#define prt_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Registry.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmParties : public TForm
{
__published:	// Composants gérés par l'EDI
    TComboBox *ComboBoxNom;
    TLabel *LabelNom;
    TStringGrid *StringGridParties;
    TButton *ButtonOk;
    TButton *ButtonAppliquer;
    TButton *ButtonAnnuler;
    TRadioGroup *RadioGroupTypeSuppression;
    void __fastcall FormShow(TObject *Sender);
    
    void __fastcall ComboBoxNomChange(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall RadioGroupTypeSuppressionClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    
    
    void __fastcall StringGridPartiesDblClick(TObject *Sender);
    
    
private:	// Déclarations de l'utilisateur
    TRegistry *Registry;
    void RafraichitParties();
    bool SupprimePartie(String stNomJoueur, String stNumPartie);
	bool SupprimePartiesJoueur(String stNomJoueur);
	bool SupprimeParties();
	void EffaceTableauParties();
public:		// Déclarations de l'utilisateur
	__fastcall TfrmParties(TComponent* Owner);
	bool SupprimePartiesPrecedentes();
	void EnregistrePartie();
	bool ChargeInfosPartie(String stNomJoueur, String stNumPartie);
    void DefinitNumIdPartie();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmParties *frmParties;
//---------------------------------------------------------------------------
#endif
