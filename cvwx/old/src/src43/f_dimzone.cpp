//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_dimzone.h"
#include "simul.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
 #pragma link "cspin"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
TfrmDimensionsZone *frmDimensionsZone;
//---------------------------------------------------------------------------
bool DefinitDimensionsZone(int &NbX, int &NbY, bool &GenereReseau)
 {
  int mrRep=mrCancel;
  if (frmDimensionsZone=new TfrmDimensionsZone(Application))
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
#ifdef CV_WINDOWS
 if (CSpinEditNbX->Focused()||CSpinEditNbY->Focused())
  switch(Key)
   {
    case '\r': ButtonCreer->Click(); break;
    case 27:   ButtonAnnuler->Click(); break;
    default: return;
   }
#endif
}
//---------------------------------------------------------------------------

void __fastcall TfrmDimensionsZone::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=max(LMAX(CSpinEditNbY, ButtonAide),
           XMAX(CheckBoxAfficherParametres))+LH_ESPACE,
     h=max(HMAX(ButtonCreer, ButtonAnnuler),
           YMAX(ButtonAide))+LH_ESPACE;
 if (!RedimensionnementEnCours)
  if ((Width!=l)||(Height!=h))
   {
    RedimensionnementEnCours=true;
    if (Width!=l) Width=l;
    if (Height!=h) Height=h;
    RedimensionnementEnCours=false;
   }
#endif
}
//---------------------------------------------------------------------------

