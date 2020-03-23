//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#include <shellapi.hpp>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_propos.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
// ATTENTION : LE CHANGEMENT DE VERSION DOIT ÊTRE RÉPERCUTÉ sur :
// · Le numéro de version dans les paramètres du projet
// · Le #define VERSION en hexadécimal (simul.h) si le format de fichier a changé
// · La bitmap ici ImageVersion et la sous-version dans LabelSousVersion
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
 ShellExecute(Application->Handle,
              NULL,
              AnsiString(LabelURL->Caption).c_str(),
              "", "",
              SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::LabelEMailClick(TObject *Sender)
{
 ShellExecute(Application->Handle,
              NULL,
              AnsiString("mailto:"+LabelEMail->Caption+"?subject=Centre-ville").c_str(),
              "", "",
              SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormCreate(TObject *Sender)
{
 FermetureAutomatique=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormKeyPress(TObject *Sender, char &Key)
{
 if ((Key==13)||(Key==27)) SpeedButtonOk->Click();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::LabelClick(TObject *Sender)
{ // v5.2.3. : où que l'on clique, ça apparaît + Texte revu
 AppelleAuChaos(); // v5.2.3 : Déplacé ici
 Application->MessageBox("\
Centre-Ville est sous Licence Publique Générale version 2.0.\n\
1998-2018, Patrice FOUQUET\n\n\
Se reporter au fichier licence.txt.\n\
Centre-Ville est fourni SANS AUCUNE GARANTIE.", "Licence", MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------


