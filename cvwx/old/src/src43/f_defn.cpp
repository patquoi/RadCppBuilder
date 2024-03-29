//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_defn.h"
#include "simul.h"
#include "f_simul.h"
#include "winlinux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef CV_WINDOWS
 #pragma resource "*.dfm"
#endif
#ifdef CV_LINUX
 #pragma resource "*.xfm"
#endif
//---------------------------------------------------------------------------
TfrmDefNature *frmDefNature=NULL;
//---------------------------------------------------------------------------
__fastcall TfrmDefNature::TfrmDefNature(TComponent* Owner)
  : TForm(Owner)
{
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
void __fastcall TfrmDefNature::FormResize(TObject *Sender)
{
#ifdef CV_LINUX
 static bool RedimensionnementEnCours=false;
 int l=max( LMAX(ButtonFermer,ButtonAppliquer),
            LMAX(ButtonAide,LabelRq))+LH_ESPACE,
     h=YMAX(LabelRq)+LH_ESPACE;
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
void __fastcall TfrmDefNature::FormShow(TObject *Sender)
{
#ifdef CV_LINUX
 FormResize(this);
#endif
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
