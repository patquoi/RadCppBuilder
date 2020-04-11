//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "param_f.h"
#include "base.h"
#include "main_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TFormParametres *FormParametres;
//---------------------------------------------------------------------------
__fastcall TFormParametres::TFormParametres(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormParametres::FormShow(TObject *Sender)
{
 if (P)
  {
   NbHexagonesDeCote=P->N;
   ((TRadioButton*)FindComponent("RadioButton"+IntToStr(NbHexagonesDeCote)))->Checked=true;
   RadioGroupNbCamps->ItemIndex=P->CfgDep;
   RadioGroupNbMaxLettresAPlacer->ItemIndex=P->NbMaxLettresAPlacer-5;
  }
 else
  NbHexagonesDeCote=0;
}
//---------------------------------------------------------------------------
void __fastcall TFormParametres::ButtonVuClick(TObject *Sender)
{
 String stMsg; // v1.4 : String au lieu d'AnsiString
 if (!NbHexagonesDeCote)
  stMsg="\n - la taille du plateau de jeu";
 if (RadioGroupNbCamps->ItemIndex<0)
  stMsg=stMsg+"\n - le nombre de camps";
 if (RadioGroupNbMaxLettresAPlacer->ItemIndex<0)
  stMsg=stMsg+"\n - le nombre maximum de lettres à placer";
 if (stMsg!="")
  {
   stMsg="Veuillez compléter ce qui suit avant de réessayer :"+stMsg;
   Application->MessageBox( stMsg.c_str(), L"Paramètre(s) incomplet(s)", MB_ICONEXCLAMATION);
  }
 else
  {
   if (FormMain->TimerAfficheMotsTrouves->Enabled)
    FormMain->TimerAfficheMotsTrouves->Enabled=false;
   FormMain->RichEdit->Clear(); 
   if (P) { delete P; P=NULL; }
   P=new plateau( NbHexagonesDeCote,
                  (config_depart)RadioGroupNbCamps->ItemIndex,
                  RadioGroupNbMaxLettresAPlacer->ItemIndex+6);
   for(int i=0; i<NbCamps[P->CfgDep]; i++) J[i].Initialise();
   ModalResult=mrOk;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormParametres::RadioButton7Click(TObject *Sender)
{
 NbHexagonesDeCote=((TRadioButton*)Sender)->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TFormParametres::RadioGroupNbMaxLettresAPlacerClick(
      TObject *Sender)
{
 for(int i=7; i<13; i++)
  ((TRadioButton*)FindComponent("RadioButton"+IntToStr(i)))->Enabled=(i>RadioGroupNbMaxLettresAPlacer->ItemIndex+6);
 if (NbHexagonesDeCote&&(NbHexagonesDeCote<=RadioGroupNbMaxLettresAPlacer->ItemIndex+6))
  {
   NbHexagonesDeCote=RadioGroupNbMaxLettresAPlacer->ItemIndex+7;
   ((TRadioButton*)FindComponent("RadioButton"+IntToStr(NbHexagonesDeCote)))->Checked=true;
  }
}
//---------------------------------------------------------------------------

