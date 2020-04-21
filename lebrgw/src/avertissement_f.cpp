//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "avertissement_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAvertissement *frmAvertissement;
//---------------------------------------------------------------------------
__fastcall TfrmAvertissement::TfrmAvertissement(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAvertissement::TimerTimer(TObject *Sender)
{
 if (Timer->Tag<200)
  Timer->Tag++;
 else
  Timer->Enabled=false;
 ButtonOk->Top=506-Timer->Tag;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAvertissement::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
 CanClose=!!ButtonOk->Tag;   
}
//---------------------------------------------------------------------------

void __fastcall TfrmAvertissement::ButtonOkClick(TObject *Sender)
{
 ButtonOk->Tag=1;
}
//---------------------------------------------------------------------------

