//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "scores_f.h"
#include "base.h"
#include "plateau_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmScores *frmScores;
//---------------------------------------------------------------------------
__fastcall TfrmScores::TfrmScores(TComponent* Owner)
    : TForm(Owner)
{
 RafraichirTempsUniquement=false;
 // v4.5 : Prise en charge HDPI
 Top=HDPI(Top);
 Left=HDPI(Left);
}
//---------------------------------------------------------------------------
void TfrmScores::Initialise()
 {
  int i;
  for(i=0; i<6; i++)
   {
    cljo[i]=0; jocl[i]=i;
    nj[i]=np[i]=0;
   }
  NbjSvt=(nbj>=2)+(nbj>=3)+(nbj>=6);
  StringGrid->RowCount=nbj+1;
 }
//---------------------------------------------------------------------------
void TfrmScores::MajScores()
 {
  int xx, yy, i, j, n;
  double dt;
  int Row, Col, tt, h, m, s;
  for(i=0; i<6; i++)
   {
    cljo[i]=0; jocl[i]=-1;
    nj[i]=np[i]=0;
   }
  for(xx=0; xx<NBXY; xx++) // v4.0 : xx<11 remplacé par xx<15 (NBXY)
   for(yy=p.XYMin[xx]; yy<=p.XYMax[xx]; yy++)
    if ((i=p.c[xx][yy].Joueur))
     {
      nj[i-1]++;
      np[i-1]+=p.c[xx][yy].Valeur;
     }
  for(i=0; i<nbj; i++)
   for(j=0; j<nbj; j++)
    if (131072UL*(unsigned long)J[i].Score+   // v4.0 : 131072 au lieu de 131172
          1024UL*(unsigned long)nj[i]+
                 (unsigned long)np[i]<
        131072UL*(unsigned long)J[j].Score+   // v4.0 : 131072 au lieu de 131172
          1024UL*(unsigned long)nj[j]+
                 (unsigned long)np[j]) cljo[i]++;
  for(i=0; i<nbj; i++)
   {
    while(jocl[cljo[i]]!=-1) cljo[i]++;
    jocl[cljo[i]]=i;
   }
  if (!Visible)
   {
	StringGrid->RowCount=nbj+1;
	Height=HDPI(44+18*nbj); // v4.5 prise en charge HDPI
	Show();
   }
  StringGrid->Repaint();
  Caption="Scores - Tour n°"+IntToStr((int)Tour);
 }
//---------------------------------------------------------------------------

void __fastcall TfrmScores::FormShow(TObject *Sender)
{
 Initialise();
 MajScores();
}
//---------------------------------------------------------------------------
void __fastcall TfrmScores::StringGridDrawCell(TObject *Sender, int Col,
	  int Row, TRect &Rect, TGridDrawState State)
{
 int tt, m, s;
 bool TempsRafraichi=false;
 AnsiString as;
 if (StringGrid->RowCount!=nbj+1)
  {
   StringGrid->RowCount=nbj+1;
   Height=HDPI(44+18*nbj); // v4.5 prise en charge HDPI
  }

 switch(Row)
  {
   case 0: switch(Col)
            {
             case 0: as="Joueur"; break;
             case 1: as="pts"; break;
             case 2: as="jtn"; break;
             case 3: as="p-j"; break;
             case 4: as="temps"; break;
            }
            break;
   default: switch(Col)
             {
              case 0: as=J[jocl[Row-1]].stNom; break;
              case 1: as=Format("%3.3d", ARRAYOFCONST((J[jocl[Row-1]].Score))); break;
              case 2: as=Format("%2.2d", ARRAYOFCONST((nj[jocl[Row-1]]))); break;
              case 3: as=Format("%2.2d", ARRAYOFCONST((np[jocl[Row-1]]))); break;
              case 4: if (!RafraichirTempsUniquement)
                       {
                        tt=J[jocl[Row-1]].TpsEcoule+
                           ((jocl[Row-1]==Jo)&&p.TopTour)*(difftime(time(NULL), p.TopTour));
                        m=tt/60;
                        s=tt%60;
                        as=Format("%2.2d:%2.2d", ARRAYOFCONST((m,s)));
                       }
                      else
                       {
                        as=StringGrid->Cells[Col][Row];
                        TempsRafraichi=true;
                       }
                      break;
             }
  }
 StringGrid->Canvas->Brush->Color=Row?clJo[jocl[Row-1]+1][CLAIR]:clJo[0][CLAIR];
 StringGrid->Canvas->Font->Color=((!Row)||jocl[Row-1])?clBlack:clWhite;
 if (!RafraichirTempsUniquement) StringGrid->Canvas->FillRect(Rect);
 if (Col)
  StringGrid->Canvas->TextOut(Rect.Left+
                              (Rect.Right-
                               Rect.Left-
                               StringGrid->Canvas->TextWidth(as))/2,
                              Rect.Top+
                               (Rect.Bottom-
                                Rect.Top-
                                StringGrid->Canvas->TextHeight(as))/2,
                              as);
 else
  StringGrid->Canvas->TextRect(Rect, Rect.Left+2, Rect.Top+2, as);
 if (TempsRafraichi) RafraichirTempsUniquement=false;
}
//---------------------------------------------------------------------------
void TfrmScores::MajTemps()
 {
  AnsiString as;
  TRect Rect=StringGrid->CellRect(4, 1+cljo[Jo]);
  int i, tt=J[Jo].TpsEcoule+(p.TopTour>0)*difftime(time(NULL), p.TopTour),
	  m=tt/60, s=tt%60;
  if (!p.JeuEnCours) return;
  as=Format("%2.2d:%2.2d", ARRAYOFCONST((m,s)));
  if (as!=StringGrid->Cells[4][1+cljo[Jo]])
   {
	StringGrid->Cells[4][1+cljo[Jo]]=as;
	StringGrid->Canvas->Brush->Color=clJo[Jo+1][CLAIR];
	StringGrid->Canvas->Font->Color=Jo?clBlack:clWhite;
	//StringGrid->Canvas->FillRect(Rect);
	StringGrid->Canvas->TextOut(Rect.Left+
								(Rect.Right-
								 Rect.Left-
								 StringGrid->Canvas->TextWidth(as))/2,
								Rect.Top+
								 (Rect.Bottom-
								  Rect.Top-
								  StringGrid->Canvas->TextHeight(as))/2,
								as);
   }
 }
//---------------------------------------------------------------------------
void __fastcall TfrmScores::FormPaint(TObject *Sender)
{
 AnsiString as;
 int i, tt=J[Jo].TpsEcoule+(p.TopTour>0)*difftime(time(NULL), p.TopTour),
	 m=tt/60, s=tt%60;
 if (!p.JeuEnCours) return;
 as=Format("%2.2d:%2.2d", ARRAYOFCONST((m,s)));
 if (as!=StringGrid->Cells[4][1+cljo[Jo]])
  {
   RafraichirTempsUniquement=true;
   StringGrid->Cells[4][1+cljo[Jo]]=as;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmScores::TimerTimer(TObject *Sender)
{
 MajTemps();   
}
//---------------------------------------------------------------------------

