//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "nomjo_f.h"
#include "base.h"
#include "scores_f.h"
#include "param_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmNomJoueurs *frmNomJoueurs;
//---------------------------------------------------------------------------
const int iBmp[3][NBDIR]={{0,8,2,3,4,5},{0,6,7,3,4,5},{0,1,2,3,4,5}};
//---------------------------------------------------------------------------
__fastcall TfrmNomJoueurs::TfrmNomJoueurs(TComponent* Owner)
    : TForm(Owner)
{
 NbJoueursModifiable=true;
 NouvellePartie=true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNomJoueurs::FormShow(TObject *Sender)
{
 TCheckBox *CheckBoxAutomate;
 int i, j;
 RadioGroupJoueurs->Enabled=NbJoueursModifiable;
 switch(nbj)
  {
   case 2: RadioGroupJoueurs->ItemIndex=0; break;
   case 3: RadioGroupJoueurs->ItemIndex=1; break;
   case 6: RadioGroupJoueurs->ItemIndex=2; break;
   default: RadioGroupJoueurs->ItemIndex=2; break;
  }
 for(i=0; i<NBDIR; i++)
  {
   ((TEdit*)FindComponent("Edit"+IntToStr(i+1)))->Text=J[i].stNom;
   CheckBoxAutomate=((TCheckBox*)FindComponent("CheckBox"+IntToStr(i+1)+"A"));
   CheckBoxAutomate->Checked=J[i].Automate;
   ((TTrackBar*)FindComponent("TrackBar"+IntToStr(i+1)))->Position=(NouvellePartie?frmParametresAutomates->TailleMax:J[i].NbMaxLettres);
   ((TTrackBar*)FindComponent("TrackBar"+IntToStr(i+1)))->Enabled=CheckBoxAutomate->Checked;
   ((TCheckBox*)FindComponent("CheckBox"+IntToStr(i+1)+"D"))->Checked=(NouvellePartie?frmParametresAutomates->Autorisation:J[i].RechercheDeplacements);
   ((TCheckBox*)FindComponent("CheckBox"+IntToStr(i+1)+"D"))->Enabled=CheckBoxAutomate->Checked;
   ImageList->GetBitmap(i, ((TImage*)FindComponent("Image"+IntToStr(i+1)))->Picture->Bitmap);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmNomJoueurs::RadioGroupJoueursClick(TObject *Sender)
{
 int i, j, n=StrToInt(RadioGroupJoueurs->Items->Strings[RadioGroupJoueurs->ItemIndex]);
 bool Actif;
 TCheckBox *CheckBoxAutomate;
 TImage* Image;
 for(i=0; i<6; i++)
  {
   Actif=(i<n);
   ((TLabel*)FindComponent("Label"+IntToStr(i+1)))->Enabled=Actif;
   ((TEdit*)FindComponent("Edit"+IntToStr(i+1)))->Enabled=Actif;
   Image=(TImage*)FindComponent("Image"+IntToStr(i+1));
   ImageList->GetBitmap(iBmp[RadioGroupJoueurs->ItemIndex][i], Image->Picture->Bitmap);
   Image->Visible=Actif; if (Actif) Image->Repaint();
   CheckBoxAutomate=((TCheckBox*)FindComponent("CheckBox"+IntToStr(i+1)+"A"));
   CheckBoxAutomate->Enabled=Actif;
   ((TCheckBox*)FindComponent("CheckBox"+IntToStr(i+1)+"D"))->Enabled=Actif&&CheckBoxAutomate->Checked;
   ((TTrackBar*)FindComponent("TrackBar"+IntToStr(i+1)))->Enabled=Actif&&CheckBoxAutomate->Checked;

  }
 Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmNomJoueurs::Button1Click(TObject *Sender)
{
 int i;
 nbj=StrToInt(RadioGroupJoueurs->Items->Strings[RadioGroupJoueurs->ItemIndex]);
 for(i=0; i<nbj; i++)
  {
   J[i].stNom=((TEdit*)FindComponent("Edit"+IntToStr(i+1)))->Text;
   J[i].Automate=((TCheckBox*)FindComponent("CheckBox"+IntToStr(i+1)+"A"))->Checked;
   J[i].RechercheDeplacements=((TCheckBox*)FindComponent("CheckBox"+IntToStr(i+1)+"D"))->Checked;
   // v4.0 : 4 lignes en plus de 7 à 15 lettres correspondant aux CheckBox de 1 à 9
   J[i].NbMaxLettres= ((TTrackBar*)FindComponent("TrackBar"+IntToStr(i+1)))->Position;
   J[i].DefPrmCase(PrmCase[6*i/nbj][0], PrmCase[6*i/nbj][1]);
  }
 frmScores->MajScores(); 
}
//---------------------------------------------------------------------------




void __fastcall TfrmNomJoueurs::CheckBoxAutomateClick(TObject *Sender)
{ // v4.0
 TCheckBox *CheckBox=(TCheckBox*)Sender;
 int i=CheckBox->Tag;
 ((TTrackBar*)FindComponent("TrackBar"+IntToStr(i)))->Enabled=CheckBox->Checked;
 ((TCheckBox*)FindComponent("CheckBox"+IntToStr(i)+"D"))->Enabled=CheckBox->Checked;
}
//---------------------------------------------------------------------------

