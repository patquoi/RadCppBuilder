//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "nomjou_f.h"
#include "plt_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmNomJoueur *frmNomJoueur;
//---------------------------------------------------------------------------
__fastcall TfrmNomJoueur::TfrmNomJoueur(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmNomJoueur::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
 CanClose=(!EditNomJoueur->Text.IsEmpty());
}
//---------------------------------------------------------------------------
void __fastcall TfrmNomJoueur::EditNomJoueurChange(TObject *Sender)
{
 ButtonOk->Enabled=(!EditNomJoueur->Text.IsEmpty());
}
//---------------------------------------------------------------------------
void __fastcall TfrmNomJoueur::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 frmPlateau->stNomJoueur=EditNomJoueur->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNomJoueur::FormShow(TObject *Sender)
{
 EditNomJoueur->Text="";   
}
//---------------------------------------------------------------------------

