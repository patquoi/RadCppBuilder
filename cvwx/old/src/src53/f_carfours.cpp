//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "f_carfours.h"
#include "simul.h"
#include "f_simul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#include "base.h"
//---------------------------------------------------------------------------
TfrmCarrefours *frmCarrefours;
//---------------------------------------------------------------------------
const dirposs DirPossC4x4[4][4]=
 {{aucune,      O,      E, aucune},
  {     S,     SO,     SE,      S},
  {     N,     NO,     NE,      N},
  {aucune,      O,      E, aucune}},
              DirPossC6x6[2][6][6]=
 {{{aucune, aucune,      O,      E, aucune, aucune},
   {aucune,      S,     SO,      S,      E, aucune},
   {     S,      O, aucune, aucune,     SE,      S},
   {     N,     NO, aucune, aucune,      E,      N},
   {aucune,      O,      N,     NE,      N, aucune},
   {aucune, aucune,      O,      E, aucune, aucune}},
  {{aucune, aucune,      O,      E, aucune, aucune},
   {aucune,      S,     SO,     SE,      E, aucune},
   {     S,     SO,     SO,     SE,     SE,      S},
   {     N,     NO,     NO,     NE,     NE,      N},
   {aucune,      O,     NO,     NE,      N, aucune},
   {aucune, aucune,      O,      E, aucune, aucune}}},
              DirPossC8x8[8][8]=
 {{aucune, aucune, aucune,      O,      E, aucune, aucune, aucune},
  {aucune,      S,      S,     SO,     SE,     SE,      E, aucune},
  {aucune,     SO,     SO,     SO,      S,     SE,      E, aucune},
  {     S,     SO,      O, aucune, aucune,     SE,     SE,      S},
  {     N,     NO,     NO, aucune, aucune,      E,     NE,      N},
  {aucune,      O,     NO,      N,     NE,     NE,     NE, aucune},
  {aucune,      O,     NO,     NO,     NE,      N,      N, aucune},
  {aucune, aucune, aucune,      O,      E, aucune, aucune, aucune}},
              DirPossC3x4[3][4]=
 {{     O,     SO,      O,      O},
  {     E,     SE,     NE,      E},
  {aucune,      S,      N, aucune}};
//---------------------------------------------------------------------------
const AnsiString asNbFeuxLibresInsuffisant="\
Il reste moins de %d feux de libres !\n\
Il faut...\n\
 - Soit supprimer des feux existants puis réessayer,\n\
 - Soit augmenter le nombre maximum de feux puis réessayer ; Pour ce faire :\n\
   · Enregistrer le réseau actuel,\n\
   · Dans les paramètres de simulation, augmenter le nombre de feux maximum\n\
   · Cocher \"Maintenus à l'ouverture\"\n\
   · Appuyer sur Ok puis confirmer la suppression des feux\n\
   · Ouvrir à nouveau le réseau (SURTOUT NE PAS ENREGISTRER les modifications)\n\
   · Réessayer.",
                 asImpossibleCreerCarrefour="Impossible de créer le carrefour";
//---------------------------------------------------------------------------
int Carrefours(int Colonnes, int Lignes)
{
 frmCarrefours->Active(Colonnes, Lignes);
 return frmCarrefours->ShowModal();
}
//---------------------------------------------------------------------------
__fastcall TfrmCarrefours::TfrmCarrefours(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmCarrefours::Active(int Colonnes, int Lignes)
 {
  int i;
  TComponent *Component;
  AnsiString asType;
  for(i=0; i<ComponentCount; i++)
   if ((Components[i]->Name!="ButtonAide")&&
       (Components[i]->Name!="Label"))
    {
     Component=(TComponent*)Components[i];
     asType=AnsiString(Component->ClassName());
     ((TControl*)Component)->Enabled=((asType=="TGroupBox")&&
                                      (Component->Name.SubString(9, 2)==IntToStr(10*Colonnes+Lignes)))||
                                     ((asType=="TSpeedButton")&&
                                      (Component->Name.SubString(12, 2)==IntToStr(10*Colonnes+Lignes)));
    }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmCarrefours::SpeedButtonClick(TObject *Sender)
{
 int i, x, y, x1, y1, x2, y2, x3, y3, d1, d2, d3,
     xd=frmSimulation->DrawGridSimul->Selection.Left,
     yd=frmSimulation->DrawGridSimul->Selection.Top,
     xf=frmSimulation->DrawGridSimul->Selection.Right,
     yf=frmSimulation->DrawGridSimul->Selection.Bottom,
     mrRep=((TSpeedButton*)Sender)->Tag,
     Dimensions=mrRep/100,
     Orientation=(mrRep%100)/10,
     Type=mrRep%10,
     NumFeux[4];
 if ((Dimensions<44)&&(Type>1))
  while(cv->NbFeuxLibres()<3)
   IncrementeNombre(&(cv->Feu), cv->NbFeux);
 if ((Dimensions==44)&&(Type>1))
  while(cv->NbFeuxLibres()<4)
   IncrementeNombre(&(cv->Feu), cv->NbFeux);
 if (frmSimulation->SupprimeToutDansSelection(tvTout))
  {
   switch(Dimensions)
    {
     case 34:
     case 43: if (Dimensions==34)
               {
                for(x=xd; x<=xf; x++)
                 for(y=yd; y<=yf; y++)
                  {
                   if (Orientation==2)
                    cv->v[x][y].DirPoss=RotPossDir[R90D][DirPossC3x4[xf-x][y-yd]];
                   else
                    cv->v[x][y].DirPoss=RotPossDir[R90G][DirPossC3x4[x-xd][yf-y]];
                   frmSimulation->RedessineCase(x,y,true);
                  }
                cv->v[x1=xd+2*(Orientation-1)][y1=yd+3*(Orientation-1)].Priorite[d1=sud-1-2*(Orientation-1)]=(Type>1)?feux:cedez_le_passage;
                cv->v[x2=xd+2-2*(Orientation-1)][y2=yd+1+1*(Orientation-1)].Priorite[d2=ouest-1-2*(Orientation-1)]=(Type>1)?feux:cedez_le_passage;
                cv->v[x3=xd+1][y3=yd+3-3*(Orientation-1)].Priorite[d3=nord-1+2*(Orientation-1)]=(Type>1)?feux:cedez_le_passage;
               }
              else
               {
                for(x=xd; x<=xf; x++)
                 for(y=yd; y<=yf; y++)
                  {
                   if (Orientation==2)
                    cv->v[x][y].DirPoss=DirPossC3x4[y-yd][x-xd];
                   else
                    cv->v[x][y].DirPoss=RotPossDir[R180][DirPossC3x4[yf-y][xf-x]];
                   frmSimulation->RedessineCase(x,y,true);
                  }
                cv->v[x1=xd+3*(Orientation-1)][y1=yd+2-2*(Orientation-1)].Priorite[d1=est-1+2*(Orientation-1)]=(Type>1)?feux:cedez_le_passage;
                cv->v[x2=xd+1+1*(Orientation-1)][y2=yd+2*(Orientation-1)].Priorite[d2=sud-1-2*(Orientation-1)]=(Type>1)?feux:cedez_le_passage;
                cv->v[x3=xd+3-3*(Orientation-1)][y3=yd+1].Priorite[d3=ouest-1-2*(Orientation-1)]=(Type>1)?feux:cedez_le_passage;
               }
              if (Type>1) // Avec Feux
               {
                NumFeux[d1]=cv->AjouteFeu(x1, y1, (direction)(d1+1));
                NumFeux[d2]=cv->AjouteFeu(x2, y2, (direction)(d2+1));
                NumFeux[d3]=cv->AjouteFeu(x3, y3, (direction)(d3+1));
                cv->Feu[NumFeux[d1]-1].AjouteFeuDmd(NumFeux[d2]);
                cv->Feu[NumFeux[d1]-1].AjouteFeuAtt(NumFeux[d2]);
                cv->Feu[NumFeux[d1]-1].Etat=(etat_feu)(1+2*(Type%2));
                cv->Feu[NumFeux[d2]-1].AjouteFeuDmd(NumFeux[d1]);
                cv->Feu[NumFeux[d2]-1].AjouteFeuDmd(NumFeux[d3]);
                cv->Feu[NumFeux[d2]-1].AjouteFeuAtt(NumFeux[d1]);
                cv->Feu[NumFeux[d2]-1].AjouteFeuAtt(NumFeux[d3]);
                cv->Feu[NumFeux[d2]-1].Etat=(etat_feu)(1+2*((1+Type)%2));
                cv->Feu[NumFeux[d3]-1].AjouteFeuDmd(NumFeux[d2]);
                cv->Feu[NumFeux[d3]-1].AjouteFeuAtt(NumFeux[d2]);
                cv->Feu[NumFeux[d3]-1].Etat=(etat_feu)(1+2*(Type%2));
                frmSimulation->RedessineCase(x1,y1,true);
                frmSimulation->RedessineCase(x2,y2,true);
                frmSimulation->RedessineCase(x3,y3,true);
               }
              break;
     case 44: for(x=xd; x<=xf; x++)
               for(y=yd; y<=yf; y++)
                {
                 cv->v[x][y].DirPoss=DirPossC4x4[x-xd][y-yd];
                 frmSimulation->RedessineCase(x,y,true);
                }
              cv->v[xd+1][yd].Priorite[sud-1]=(Type>1)?feux:cedez_le_passage;
              cv->v[xd+3][yd+1].Priorite[ouest-1]=(Type>1)?feux:cedez_le_passage;
              cv->v[xd+2][yd+3].Priorite[nord-1]=(Type>1)?feux:cedez_le_passage;
              cv->v[xd][yd+2].Priorite[est-1]=(Type>1)?feux:cedez_le_passage;
              if (Type>1) // Avec Feux
               {
                NumFeux[nord-1]=cv->AjouteFeu(xd+1, yd, sud);
                NumFeux[est-1]=cv->AjouteFeu(xd+3, yd+1, ouest);
                NumFeux[sud-1]=cv->AjouteFeu(xd+2, yd+3, nord);
                NumFeux[ouest-1]=cv->AjouteFeu(xd, yd+2, est);
                for(i=0; i<NBDIR; i++)
                 {
                  cv->Feu[NumFeux[i]-1].AjouteFeuDmd(NumFeux[(i+1)%NBDIR]);
                  cv->Feu[NumFeux[i]-1].AjouteFeuDmd(NumFeux[(i+3)%NBDIR]);
                  cv->Feu[NumFeux[i]-1].AjouteFeuAtt(NumFeux[(i+1)%NBDIR]);
                  cv->Feu[NumFeux[i]-1].AjouteFeuAtt(NumFeux[(i+3)%NBDIR]);
                  cv->Feu[NumFeux[i]-1].Etat=(etat_feu)(1+2*((1+Type+i)%2));
                 }
                frmSimulation->RedessineCase(xd+1,yd,true);
                frmSimulation->RedessineCase(xd+3,yd+1,true);
                frmSimulation->RedessineCase(xd+2,yd+3,true);
                frmSimulation->RedessineCase(xd,yd+2,true);
               }
              break;
     case 66: for(x=xd; x<=xf; x++)
               for(y=yd; y<=yf; y++)
                {
                 cv->v[x][y].DirPoss=DirPossC6x6[Type-1][x-xd][y-yd];
                 frmSimulation->RedessineCase(x,y,true);
                }
              cv->v[xd+2][yd].Priorite[sud-1]=cedez_le_passage;
              cv->v[xd+5][yd+2].Priorite[ouest-1]=cedez_le_passage;
              cv->v[xd+3][yd+5].Priorite[nord-1]=cedez_le_passage;
              cv->v[xd][yd+3].Priorite[est-1]=cedez_le_passage;
              frmSimulation->RedessineCase(xd+2,yd,true);
              frmSimulation->RedessineCase(xd+5,yd+2,true);
              frmSimulation->RedessineCase(xd+3,yd+5,true);
              frmSimulation->RedessineCase(xd,yd+3,true);
              break;
     case 88: for(x=xd; x<=xf; x++)
               for(y=yd; y<=yf; y++)
                {
                 cv->v[x][y].DirPoss=DirPossC8x8[x-xd][y-yd];
                 frmSimulation->RedessineCase(x,y,true);
                }
              cv->v[xd+3][yd].Priorite[sud-1]=cedez_le_passage;
              cv->v[xd+7][yd+3].Priorite[ouest-1]=cedez_le_passage;
              cv->v[xd+4][yd+7].Priorite[nord-1]=cedez_le_passage;
              cv->v[xd][yd+4].Priorite[est-1]=cedez_le_passage;
              frmSimulation->RedessineCase(xd+3,yd,true);
              frmSimulation->RedessineCase(xd+7,yd+3,true);
              frmSimulation->RedessineCase(xd+4,yd+7,true);
              frmSimulation->RedessineCase(xd,yd+4,true);
              break;
    }
   ModalResult=mrRep;
  }
 else
  ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCarrefours::ButtonAideClick(TObject *Sender)
{
 AfficheAideContextuelle(this); // v3.8
}
//---------------------------------------------------------------------------

void __fastcall TfrmCarrefours::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{// v5.3 (nécessite TForm:KeyPreview à true)
 if (Key==112)
   AfficheAideContextuelle(this);
}
//---------------------------------------------------------------------------

