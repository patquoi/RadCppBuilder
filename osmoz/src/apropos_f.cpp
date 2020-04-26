//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "apropos_f.h"
#include "plateau_f.h"
#include "base.h"
#include <ShellApi.hpp>
//---------------------------------------------------------------------------
// v4.5 : prise en charge HDPI
#define EST_SUR_LE_BOUTON (_HDPI(X)>=144)&&(_HDPI(X)<204)&&(_HDPI(Y)>=282)&&(_HDPI(Y)<314)
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmAPropos *frmAPropos;
//---------------------------------------------------------------------------
const wchar_t wsOsmoz[10]=L"  OSMOZ  ";
//---------------------------------------------------------------------------
__fastcall TfrmAPropos::TfrmAPropos(TComponent* Owner)
	: TForm(Owner)
{
#ifdef _WIN64
 PanelAlignement->Caption=Format(PanelAlignement->Caption, ARRAYOFCONST((64)));
#else
 PanelAlignement->Caption=Format(PanelAlignement->Caption, ARRAYOFCONST((32)));
#endif
 PanelHDPI->Caption=PanelHDPI->Caption+FormatFloat("0.0", Screen->PixelsPerInch/96.0);
}
//---------------------------------------------------------------------------
void TfrmAPropos::DessineHexagone(int x, int y, int Couleur)
 {
  int i;
  TPoint p[6]={Point(0, 0), Point(18, 0), Point(28, 16), Point(18, 32), Point(0, 32), Point(-10, 16)};
  Canvas->Pen->Color=clJo[Couleur][CLAIR];
  Canvas->Pen->Style=psSolid;
  Canvas->Pen->Mode=pmCopy;
  Canvas->Brush->Color=clJo[Couleur][CLAIR];
  Canvas->Brush->Style=bsSolid;
  for(i=0; i<6; i++)
   { // v4.5 : prise en charge HDPI
	p[i].x = HDPI(p[i].x+x);
	p[i].y = HDPI(p[i].y+y);
   }
  Canvas->Polygon(p, 5);
 }
//---------------------------------------------------------------------------
void TfrmAPropos::AfficheValeurs(int x, int y, char Lettre, int Valeur, int Fond, TColor Couleur)
 {
  int xc, yc, tw, th;
  wchar_t ws[3]=L" ";
  String st;
  ws[0]=Lettre;
  st=String(ws);
  Canvas->Pen->Color=clJo[Fond][CLAIR];
  Canvas->Pen->Style=psSolid;
  Canvas->Pen->Mode=pmCopy;
  Canvas->Brush->Color=clJo[Fond][CLAIR];
  Canvas->Brush->Style=bsSolid;
  Canvas->Font->Color=Couleur;
  Canvas->Font->Name="Comic Sans MS";
  Canvas->Font->Size=14;

  // v4.5 : prise en charge HDPI
  tw=_HDPI(Canvas->TextWidth(st));
  th=_HDPI(Canvas->TextHeight(st));
  xc=HDPI(x+9-tw/2);
  yc=HDPI(y+26-th);

  Canvas->TextOut(xc, yc, st);    //y+23
  st=IntToStr(Valeur);
  Canvas->Font->Name="Small Fonts";
  Canvas->Font->Size=7;

  // v4.5 : prise en charge HDPI
  tw=_HDPI(Canvas->TextWidth(st));
  th=_HDPI(Canvas->TextHeight(st));
  xc=HDPI(x+8-tw/2);
  yc=HDPI(y+32-th);

  Canvas->TextOut(xc, yc, st);
 }
//---------------------------------------------------------------------------
void TfrmAPropos::AfficheCase(int x, int y, char Lettre, int NumCoul)
 {
  int Col=5+y-x,
	  Lig=ABS(5-Col)+2*(x*(Col>=5)+y*(Col<5)),
	  xc=13+30*Col,
	  yc=17*(2*((Lig-!(Col%2))/2)+!(Col%2))-48;
  DessineHexagone(xc, yc, NumCoul);
  if ((Lettre>='A')&&(Lettre<='Z'))
   AfficheValeurs(xc, yc, Lettre,
				  p.ValNaiss[NUM_LETTRE(Lettre)],
				  NumCoul,
				  (NumCoul==1)?clWhite:clBlack);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::TimerTimer(TObject *Sender)
{
 int i=Timer->Tag%9, j=(Timer->Tag/9)%6,
	 x=4-i/2, y=(i+1)/2;
 AfficheCase(x, y, wsOsmoz[i], j+1);
 Timer->Tag++;
}
//---------------------------------------------------------------------------
void TfrmAPropos::AfficheBouton(TColor clCouleur)
 {
  DessineHexagone(155, 282, 0);
  DessineHexagone(173, 282, 0);
  AfficheValeurs(155, 282, 'V', p.ValNaiss[NUM_LETTRE('V')], 0, clCouleur);
  AfficheValeurs(173, 282, 'U', p.ValNaiss[NUM_LETTRE('U')], 0, clCouleur);
 }
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 static bool EtaitSurLeBouton=false;
 bool EstSurLeBouton=EST_SUR_LE_BOUTON;
 if (EtaitSurLeBouton!=EstSurLeBouton)
  AfficheBouton((EtaitSurLeBouton=EstSurLeBouton)?clWhite:clBlack);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormPaint(TObject *Sender)
{
 AfficheBouton(clBlack);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (EST_SUR_LE_BOUTON)
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::RubriqueFermerClick(TObject *Sender)
{
 randomize();
 ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::LabelUrlClick(TObject *Sender)
{
 ShellExecute(Handle, NULL, LabelUrl->Caption.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAPropos::LabelEMailClick(TObject *Sender)
{
 ShellExecute(Handle, NULL, String("Mailto:"+LabelEMail->Caption+"?subject=Osmoz").c_str(), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------




