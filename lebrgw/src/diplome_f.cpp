//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "diplome_f.h"
#include "plt_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmDiplome *frmDiplome;
//---------------------------------------------------------------------------
__fastcall TfrmDiplome::TfrmDiplome(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmDiplome::FormShow(TObject *Sender)
{
 int LongueurLigne;
 wchar_t wsChiffres[10];

 // 1. On recentre le titre de Diplôme au cas où la police n'est pas la même

 LabelDiplomeAvant->Top=ShapeE->Top+(ShapeE->Height-LabelDiplomeAvant->Height)/2;
 LabelDiplomeAvant->Left=(Width-LabelDiplomeAvant->Width)/2;
 LabelDiplomeArriere->Top=LabelDiplomeAvant->Top+2;
 LabelDiplomeArriere->Left=LabelDiplomeAvant->Left+2;

 // 2. On remplit les infos (Nom du joueur, série, nombre de niveaux & score)

 LabelNomJoueur->Caption=frmPlateau->stNomJoueur;
 LabelNomSerie->Caption=frmPlateau->stNomSerieNiveau;
 LabelNbNiveaux->Caption=IntToStr(Niv->Num+1);
 wsprintf(wsChiffres, L"*%06ld*", Niv->Cumul);
 LabelScore->Caption=wsChiffres;

 // 3. On centre tout ça

 LongueurLigne=Label1->Width+6+LabelNomJoueur->Width;
 Label1->Left=(Width-LongueurLigne)/2;
 LabelNomJoueur->Left=Label1->Left+Label1->Width+6;

 LongueurLigne=Label2->Width+6+LabelNbNiveaux->Width+6+Label3->Width+6+LabelNomSerie->Width;
 Label2->Left=(Width-LongueurLigne)/2;
 LabelNbNiveaux->Left=Label2->Left+Label2->Width+6;
 Label3->Left=LabelNbNiveaux->Left+LabelNbNiveaux->Width+6;
 LabelNomSerie->Left=Label3->Left+Label3->Width+6;

 LongueurLigne=Label4->Width+6+LabelScore->Width;
 Label4->Left=(Width-LongueurLigne)/2;
 LabelScore->Left=Label4->Left+Label4->Width+6;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDiplome::Fermer1Click(TObject *Sender)
{
 Close();   
}
//---------------------------------------------------------------------------
void __fastcall TfrmDiplome::RubriqueImprimerClick(TObject *Sender)
{
 Print();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDiplome::FormPaint(TObject *Sender)
{
 int i;
 for(i=0; i<64; i++) VirtualImageList->Draw(Canvas, 64*(i%8), 46*(i/8), 0);
}
//---------------------------------------------------------------------------
