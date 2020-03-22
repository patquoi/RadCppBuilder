//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "base.h"
#include "simul.h"
#include "f_simul.h"
#include "f_defn.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmDefNature *frmDefNature=NULL;
//---------------------------------------------------------------------------
__fastcall TfrmDefNature::TfrmDefNature(TComponent* Owner)
  : TForm(Owner)
{
 // v5.4 cette boîte ne s'affiche pas comme il faut en HDPI :^(
 Width=Width*Screen->PixelsPerInch/96;
 Height=Height*Screen->PixelsPerInch/96;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefNature::RadioGroupNatureClick(TObject *Sender)
{
 if (RadioGroupNature->ItemIndex==1)
  CheckBoxPelouse->Enabled=true;
 else
  {
   CheckBoxPelouse->Checked=false;
   CheckBoxPelouse->Enabled=false;
  }
 ButtonAppliquer->Enabled=(RadioGroupNature->ItemIndex>-1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefNature::ButtonAppliquerClick(TObject *Sender)
{
 bool BordGauche, BordDroit, BordHaut, BordBas;
 for(int x=frmSimulation->DrawGridSimul->Selection.Left; x<=frmSimulation->DrawGridSimul->Selection.Right; x++)
  for(int y=frmSimulation->DrawGridSimul->Selection.Top; y<=frmSimulation->DrawGridSimul->Selection.Bottom; y++)
   {
    cv->v[x][y].DefinitNature( (nature)( trottoirs*RadioGroupNature->ItemIndex+
                                         CheckBoxPelouse->Checked*(pelouse-trottoirs)),
                               CheckBoxEcraser->Checked);
    BordGauche=(x==frmSimulation->DrawGridSimul->Selection.Left);
    BordDroit=(x==frmSimulation->DrawGridSimul->Selection.Right);
    BordHaut=(y==frmSimulation->DrawGridSimul->Selection.Top);
    BordBas=(y==frmSimulation->DrawGridSimul->Selection.Bottom);
    if (BordDroit||BordHaut) cv->v[(x+BordDroit)%cv->NbX][(y+BordHaut*(cv->NbY-1))%cv->NbY].RedessineCase(true);
    if (BordDroit||BordBas) cv->v[(x+BordDroit)%cv->NbX][(y+BordBas)%cv->NbY].RedessineCase(true);
    if (BordGauche||BordBas) cv->v[(x+BordGauche*(cv->NbX-1))%cv->NbX][(y+BordBas)%cv->NbY].RedessineCase(true);
    if (BordGauche||BordHaut) cv->v[(x+BordGauche*(cv->NbX-1))%cv->NbX][(y+BordHaut*(cv->NbY-1))%cv->NbY].RedessineCase(true);
    if (BordDroit||BordBas) cv->v[(x+BordDroit)%cv->NbX][(y+BordBas)%cv->NbY].RedessineCase(true);
    if (BordDroit||BordHaut) cv->v[(x+BordDroit)%cv->NbX][(y+BordHaut*(cv->NbY-1))%cv->NbY].RedessineCase(true);
    if (BordGauche||BordBas) cv->v[(x+BordGauche*(cv->NbX-1))%cv->NbX][(y+BordBas)%cv->NbY].RedessineCase(true);
    if (BordGauche||BordHaut) cv->v[(x+BordGauche*(cv->NbX-1))%cv->NbX][(y+BordHaut*(cv->NbY-1))%cv->NbY].RedessineCase(true);
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmDefNature::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefNature::FormShow(TObject *Sender)
{
 frmSimulation->ActionDefinirNature->Checked=true;
 RadioGroupNature->ItemIndex=-1;
 CheckBoxPelouse->Enabled=false;
 CheckBoxPelouse->Checked=false;
 ButtonAppliquer->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefNature::FormHide(TObject *Sender)
{
 frmSimulation->ActionDefinirNature->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefNature::ButtonFermerClick(TObject *Sender)
{
 Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDefNature::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

