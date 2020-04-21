//---------------------------------------------------------------------------
#ifndef records_fH
#define records_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Registry.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#define TR_INDEFINI   -1
#define TR_PARTIE      0
#define TR_NIVEAU      1
#define RECORD_NIVEAU() RadioGroupTypeRecord->ItemIndex==1

class TfrmRecords : public TForm
{
__published:	// Composants gérés par l'EDI
    TStringGrid *StringGrid;
    TButton *ButtonOk;
    TLabel *Label1;
    TButton *ButtonAnnuler;
    TRadioGroup *RadioGroupReinitialisation;
    TComboBox *ComboBoxSerie;
    TComboBox *ComboBoxNiveau;
    TButton *ButtonAppliquer;
    TTimer *Timer;
    TPanel *PanelNvEntree;
    TLabel *LabelPos;
    TEdit *EditNom;
    TLabel *LabelScore;
    TLabel *LabelDateHeure;
    TLabel *LabelNvEntree;
    TLabel *LabelDelaiOuNiv;
    TRadioGroup *RadioGroupTypeRecord;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall EditNomChange(TObject *Sender);
    void __fastcall StringGridEnter(TObject *Sender);
    void __fastcall StringGridClick(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    void __fastcall RadioGroupReinitialisationClick(TObject *Sender);
    void __fastcall ComboBoxNiveauChange(TObject *Sender);
    void __fastcall ComboBoxSerieChange(TObject *Sender);
    
    void __fastcall TimerTimer(TObject *Sender);
    
    void __fastcall RadioGroupTypeRecordClick(TObject *Sender);
    
    
    
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    
private:	// Déclarations de l'utilisateur
    TRegistry *Registry;
    void RafraichitRecords();
	bool SupprimeRecordsNiveau(String stSerieASupprimer, String stNivASupprimer);
	bool SupprimeRecordsSerie(String stSerieASupprimer);
    bool SupprimeRecords();
public:		// Déclarations de l'utilisateur
    bool TesterNvEntree;
    int Pos;
	String stNom[10], stNiveau, stSerie;
	long Score[10], DelaiOuNiv[10];
    TDateTime DateHeure[10];
    __fastcall TfrmRecords(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRecords *frmRecords;
//---------------------------------------------------------------------------
#endif 
