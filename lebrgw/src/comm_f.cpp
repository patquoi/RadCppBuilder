//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "comm_f.h"
#include "plt_f.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCommandes *frmCommandes;

const int IdxComm[2][6]={{0,0,1,1,2,2},{1,2,0,2,0,1}};

//---------------------------------------------------------------------------
__fastcall TfrmCommandes::TfrmCommandes(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCommandes::ButtonOkClick(TObject *Sender)
{
 frmPlateau->EcritParametreCommandes(RadioGroup->ItemIndex); // v1.6
}
//---------------------------------------------------------------------------

void __fastcall TfrmCommandes::FormShow(TObject *Sender)
{
 RadioGroup->ItemIndex=frmPlateau->PopupMenuJeu->Tag;
}
//---------------------------------------------------------------------------




