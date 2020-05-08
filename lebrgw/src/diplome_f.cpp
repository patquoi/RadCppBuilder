//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <Clipbrd.hpp>
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
void __fastcall TfrmDiplome::RubriqueFermerClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDiplome::FormPaint(TObject *Sender)
{ // v1.7 : le motif de fond est "Patquoi.fr"
 int dx = VirtualImageList->Width,
	 dy = VirtualImageList->Height,
	 xMax = ClientWidth/dx,
	 yMax = ClientHeight/dy;
 for(int x=0; x<=xMax; x++)
   for(int y=0; y<=yMax; y++)
	 VirtualImageList->Draw(Canvas, x*dx, y*dy, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDiplome::FormCreate(TObject *Sender)
{ // v1.7 : on exporte en image au lieu d'imprimer
 bmDiplome = new TBitmap();
 SaveDialogImage->InitialDir = stRepLocalAppData();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDiplome::FormDestroy(TObject *Sender)
{ // v1.7 : on exporte en image au lieu d'imprimer
 delete bmDiplome;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDiplome::RubriqueCopierClick(TObject *Sender)
{ // v1.7 : on exporte en image au lieu d'imprimer
 bmDiplome = GetFormImage();
 Clipboard()->Assign(bmDiplome);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDiplome::RubriqueExporterClick(TObject *Sender)
{ // v1.7 : on exporte en image au lieu d'imprimer
 if (SaveDialogImage->Execute())
  {
   bmDiplome = GetFormImage();
   bmDiplome->SaveToFile(SaveDialogImage->FileName);
  }
}
//---------------------------------------------------------------------------

