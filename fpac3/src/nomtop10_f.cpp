//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "nomtop10_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TFormNomTop10 *FormNomTop10;
//---------------------------------------------------------------------------
__fastcall TFormNomTop10::TFormNomTop10(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormNomTop10::EditNomChange(TObject *Sender)
{
 ButtonOK->Enabled=EditNom->Text.Length(); 
}
//---------------------------------------------------------------------------



