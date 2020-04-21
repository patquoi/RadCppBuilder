//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <shellapi.hpp>
#include "apropos_f.h"
#include "avertissement_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAPropos *frmAPropos;
//---------------------------------------------------------------------------
__fastcall TfrmAPropos::TfrmAPropos(TComponent* Owner)
    : TForm(Owner)
{ // v1.7 : ajout de l'alignement (32/64 bits)

#ifdef _WIN64
 LabelAlignement->Caption=Format(LabelAlignement->Caption, ARRAYOFCONST((64)));
#else
 LabelAlignement->Caption=Format(LabelAlignement->Caption, ARRAYOFCONST((32)));
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormShow(TObject *Sender)
{
 // v1.7 : On charge la bitmap pour s'assurer de la prise en compte du HDPI.
 Timer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::TimerTimer(TObject *Sender)
{
 Timer->Enabled=false;
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormClose(TObject *Sender,
	  TCloseAction &Action)
{
 if (Timer->Enabled) Timer->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::LabelURLClick(TObject *Sender)
{
 ShellExecute(Application->Handle,
			  NULL,
			  LabelURL->Caption.c_str(),
			  NULL, NULL,
			  SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAPropos::LabelEMailClick(TObject *Sender)
{
 ShellExecute(Application->Handle,
              NULL,
              String("mailto:"+LabelEMail->Caption+"?subject=Le berger").c_str(),
              NULL, NULL,
              SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAPropos::Label1Click(TObject *Sender)
{
 if ((frmAvertissement=new TfrmAvertissement(this)))
  {
   frmAvertissement->ShowModal();
   delete frmAvertissement;
  }
}
//---------------------------------------------------------------------------

