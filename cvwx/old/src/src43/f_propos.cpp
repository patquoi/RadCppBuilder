//---------------------------------------------------------------------------
#include "vclx.h"
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
#include <shellapi.hpp>
#endif
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_propos.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
// ATTENTION : LE CHANGEMENT DE VERSION DOIT ÊTRE RÉPERCUTÉ sur :
// · Le numéro de version dans les paramètres du projet
// · Le #define VERSION en hexadécimal (simul.h) si le format de fichier a changé
// · La bitmap ici ImageVersion et la sous-version dans LabelSousVersion
// · La boîte de message pour cvx (Kylix) doit avoir la bonne version
//---------------------------------------------------------------------------
TfrmAPropos *frmAPropos;
//---------------------------------------------------------------------------
__fastcall TfrmAPropos::TfrmAPropos(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::TimerTimer(TObject *Sender)
 {
  switch((TempsEcoule++)%10)
   {
    case 0: ImageList->GetBitmap(0, Bitmap);
            LabelTexte->Font->Color=clLime;
            break;
    case 4: ImageList->GetBitmap(1, Bitmap);
            LabelTexte->Font->Color=clYellow;
            break;
    case 6: ImageList->GetBitmap(2, Bitmap);
            LabelTexte->Font->Color=clRed;
            break;
   }
  SpeedButtonOk->Glyph=Bitmap;
  if (FermetureAutomatique&&(TempsEcoule==2))
   {
    FermetureAutomatique=false;
    Close();
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormShow(TObject *Sender)
{
 TempsEcoule=0;
 Bitmap=new TBITMAP;
 ImageList->GetBitmap(0, Bitmap);
 SpeedButtonOk->Glyph=Bitmap;
 Timer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormHide(TObject *Sender)
{
 Timer->Enabled=false;
 delete Bitmap;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::LabelURLClick(TObject *Sender)
{
 #ifdef CV_WINDOWS
 ShellExecute(Application->Handle,
              NULL,
              AnsiString(LabelURL->Caption).c_str(),
              "", "",
              SW_SHOWMAXIMIZED);
 #endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::LabelEMailClick(TObject *Sender)
{
#ifdef CV_WINDOWS
 ShellExecute(Application->Handle,
              NULL,
              AnsiString("mailto:"+LabelEMail->Caption+"?subject=Centre-ville").c_str(),
              "", "",
              SW_SHOWMAXIMIZED);
 #endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormCreate(TObject *Sender)
{
 FermetureAutomatique=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::SpeedButtonOkClick(TObject *Sender)
{
 AppelleAuChaos();
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormKeyPress(TObject *Sender, char &Key)
{
 if ((Key==13)||(Key==27)) SpeedButtonOk->Click();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::LabelGPL2Click(TObject *Sender)
{
 Application->MessageBox("\
Centre-Ville est sous Licence GPL version 2.0.\n\
Copyright 1998-2003, Patrice FOUQUET\n\n\
Se reporter au fichier license.txt\n\
(traduction non officielle en français : licence.txt).\n\n\
Centre-Ville est fourni SANS AUCUNE GARANTIE.", "Licence", MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
