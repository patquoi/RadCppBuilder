//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "messages_f.h"
#include "base.h"
#include "plateau_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMessages *frmMessages;
//---------------------------------------------------------------------------
__fastcall TfrmMessages::TfrmMessages(TComponent* Owner)
    : TForm(Owner)
{
 ToutEffacer=false;
 // v4.5 : Prise en charge HDPI
 Top=HDPI(Top);
 Left=HDPI(Left);
}
//---------------------------------------------------------------------------

void TfrmMessages::AfficheMessage(AnsiString asMessage, bool ToutEffacer)
 {
  this->ToutEffacer=ToutEffacer;
  this->asMessage=asMessage;
  if (Visible) Close();
  if (ToutEffacer) Memo->Lines->Clear();
  Memo->Lines->Add(asMessage);
  Button->Enabled=true;   
  Timer->Enabled=true;   
  ShowModal();
  Show();
 }

void TfrmMessages::AjouteMessage(AnsiString asMessage, bool ToutEffacer)
 {
  if (ToutEffacer) Memo->Lines->Clear();
  Memo->Lines->Add(asMessage);
 }

void TfrmMessages::RetireMessages(int Nombre)
 {
  for(;Nombre;Nombre--) Memo->Lines->Delete(Memo->Lines->Count-2);
 }

void __fastcall TfrmMessages::TimerTimer(TObject *Sender)
{
 ModalResult=mrOk;
 Timer->Enabled=false;
 Button->Enabled=false;   
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessages::ButtonClick(TObject *Sender)
{
 Timer->Enabled=false;
 Button->Enabled=false;
}
//---------------------------------------------------------------------------

void TfrmMessages::ChargeMessages(AnsiString asNomFichier)
 {
  Memo->Lines->Clear();
  try
   {
    if (FileExists(asNomFichier))
     Memo->Lines->LoadFromFile(asNomFichier);
   }
  catch(const Exception& E)
   {
    frmPlateau->StatusBar->SimpleText=E.Message;
   }
 }

void TfrmMessages::SauveMessages(AnsiString asNomFichier)
 {
  try
   {
    Memo->Lines->SaveToFile(asNomFichier);
   }
  catch(const Exception& E)
   {
    frmPlateau->StatusBar->SimpleText=E.Message;
   }
 }

void TfrmMessages::SauvegardeFin()
 {
  try
   {
    if (SaveDialog->Execute())
     Memo->Lines->SaveToFile(SaveDialog->FileName);
   }
  catch(const Exception& E)
   {
    frmPlateau->StatusBar->SimpleText=E.Message;
   }
 }

