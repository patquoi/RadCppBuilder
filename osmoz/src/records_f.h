//---------------------------------------------------------------------------
#ifndef records_fH
#define records_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Registry.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
enum types_records_battus : char {trbAucun, trbMot, trbScore, trbPointsPris=4, trbLettresPrises=8};

class TfrmRecords : public TForm
{
__published:	// Composants gérés par l'EDI
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *LabelLettresPrises;
    TLabel *LabelPointsPris;
    TLabel *LabelScore;
    TLabel *LabelMot;
    TLabel *LabelDate1;
    TLabel *LabelDate2;
    TLabel *LabelDate3;
    TLabel *LabelDate4;
    TLabel *LabelNom1;
    TLabel *LabelNom2;
    TLabel *LabelNom3;
    TLabel *LabelNom4;
    TTimer *Timer;
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall ButtonOkClick(TObject *Sender);
    
private:	// Déclarations de l'utilisateur
    TRegistry *Registry;
    types_records_battus TypesRecordsBattus;
public:		// Déclarations de l'utilisateur
    __fastcall TfrmRecords(TComponent* Owner);
    void RafraichitRecords();
    void EnregistreRecords();
    void TesteRecords(AnsiString asNom, AnsiString asMot, int Score, int PointsPris, int LettresPrises);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRecords *frmRecords;
//---------------------------------------------------------------------------
#endif
