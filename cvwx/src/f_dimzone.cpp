//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_dimzone.h"
#include "simul.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "cspin"
//---------------------------------------------------------------------------
TfrmDimensionsZone *frmDimensionsZone;
//---------------------------------------------------------------------------
bool DefinitDimensionsZone(int &NbX, int &NbY, bool &GenereReseau)
 {
  int mrRep=mrCancel;
  if ((frmDimensionsZone=new TfrmDimensionsZone(Application)))
   try
    {
     frmDimensionsZone->NbX=NbX;
     frmDimensionsZone->NbY=NbY;
     if ((mrRep=frmDimensionsZone->ShowModal())==mrOk)
      {
       NbX=frmDimensionsZone->NbX;
       NbY=frmDimensionsZone->NbY;
       if (frmDimensionsZone->CheckBoxAfficherParametres->Checked) // v4.1
        frmSimulation->ActionParametres->Execute();
       GenereReseau=frmDimensionsZone->CheckBoxGenererReseau->Checked; // v4.2
      }
    }
   __finally
    {
     delete frmDimensionsZone;
     frmDimensionsZone=NULL;
     return (mrRep==mrOk);
    }
  else
   return false;
 }
//---------------------------------------------------------------------------
__fastcall TfrmDimensionsZone::TfrmDimensionsZone(TComponent* Owner)
  : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TfrmDimensionsZone::FormShow(TObject *Sender)
{
 CSpinEditNbX->Value=NbX;
 CSpinEditNbY->Value=NbY;
 // Autorise les modifications
 CSpinEditNbX->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDimensionsZone::ButtonCreerClick(TObject *Sender)
{
 NbX=CSpinEditNbX->Value;
 NbY=CSpinEditNbY->Value;
 if ((NbX>=NBXMIN)&&(NbY>=NBYMIN))
  ModalResult=mrOk;
 else
  AfficheMessage( Format( "Vous devez spécifier une zone d'au moins %dx%d.",
                          ARRAYOFCONST((NBXMIN, NBYMIN))),
                  "Zone insuffisante",
                  tmAvertissement, 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDimensionsZone::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------


void __fastcall TfrmDimensionsZone::FormKeyPress(TObject *Sender,
      char &Key)
{
 if (CSpinEditNbX->Focused()||CSpinEditNbY->Focused())
  switch(Key)
   {
    case '\r': ButtonCreer->Click(); break;
    case 27:   ButtonAnnuler->Click(); break;
    default: return;
   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmDimensionsZone::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

