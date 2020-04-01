//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <shellapi.hpp>
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
__fastcall TfrmAPropos::TfrmAPropos(TComponent* Owner) : TForm(Owner)
 {
  #ifdef _WIN64
  LabelAlignement->Caption=Format(LabelAlignement->Caption, ARRAYOFCONST((64)));
  #else
  LabelAlignement->Caption=Format(LabelAlignement->Caption, ARRAYOFCONST((32)));
  #endif
  LabelHDPI->Caption = LabelHDPI->Caption + FormatFloat("0.0", Screen->PixelsPerInch/96.0); // v5.4.1
 }
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::TimerTimer(TObject *Sender)
 {
  switch((TempsEcoule++)%10)
   {
    case 0: VirtualImageList->GetBitmap(0, Bitmap);
            LabelTexte->Font->Color=clLime;
            break;
    case 4: VirtualImageList->GetBitmap(1, Bitmap);
            LabelTexte->Font->Color=clYellow;
            break;
    case 6: VirtualImageList->GetBitmap(2, Bitmap);
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
 VirtualImageList->GetBitmap(0, Bitmap);
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
{ // v5.4 : conversion BCB6>BCBX (string)
 ShellExecute(NULL,
			  L"open",
			  LabelURL->Caption.c_str(),
              NULL, NULL,
              SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::LabelEMailClick(TObject *Sender)
{ // v5.4 : conversion BCB6>BCBX (string)
 ShellExecute(NULL,
              L"open",
			  String("mailto:"+LabelEMail->Caption+"?subject=Centre-ville").c_str(),
			  NULL, NULL,
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
 // v5.4 : conversion BCB6>BCBX (Application-> supprimé + String)
 MessageBoxW(Application->Handle, String("\
Centre-Ville est sous Licence Publique Générale version 2.0.\n\
1998-2018, Patrice FOUQUET\n\n\
Se reporter au fichier licence.txt.\n\
Centre-Ville est fourni SANS AUCUNE GARANTIE.").w_str(), String("Licence").w_str(), MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------


