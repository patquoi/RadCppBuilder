//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
void TFormMain::GenereCodeAND(const String stNomFichierCur, const bool Suivant)
{
 unsigned short usiHeader[3], HotSpot[2];
 unsigned char Dimensions[2], Couleurs, Reserve;
 unsigned long Taille, Decalage;
 unsigned char EntetePNG[8];
 unsigned char EnteteCUR[40];
 unsigned char MsqXOR[128];
 unsigned char MsqAND[128];
 int f;
 if (stNomFichierCur.Length()>0)
  {
   if ((f=FileOpen(stNomFichierCur, fmOpenRead))>0)
	 {
	  String stNomCurseur=String(ExtractFileName(stNomFichierCur).SubString(1, ExtractFileName(stNomFichierCur).Length()-4)).UpperCase();
	  FileRead(f, &usiHeader, sizeof(usiHeader));
	  FileRead(f, &Dimensions, sizeof(Dimensions));
	  FileRead(f, &Couleurs, sizeof(Couleurs));
	  FileRead(f, &Reserve, sizeof(Reserve));
	  FileRead(f, &HotSpot, sizeof(HotSpot));
	  FileRead(f, &Taille, sizeof(Taille));
	  FileRead(f, &Decalage, sizeof(Decalage));
	  FileRead(f, &EntetePNG, sizeof(EntetePNG));
	  FileRead(f, &EnteteCUR, sizeof(EnteteCUR));
	  FileRead(f, &MsqXOR, sizeof(MsqXOR));
	  FileRead(f, &MsqAND, sizeof(MsqAND));
	  FileClose(f);
	  String stLigne;
	  if (Suivant)
		Memo->Lines->Add("  ,{ // Curseur "+stNomCurseur);
	  else
		Memo->Lines->Add("   { // Curseur "+stNomCurseur);
	  stLigne = "";
	  for(int i=31; i>=0; i--)
	   {
		if (i)
		  Memo->Lines->Add(Format("    0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X, // %02d",
								  ARRAYOFCONST((MsqAND[4*i+0], MsqAND[4*i+1], MsqAND[4*i+2], MsqAND[4*i+3], 32-i))));
		else
		  Memo->Lines->Add(Format("    0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X  // %02d",
								  ARRAYOFCONST((MsqAND[4*i+0], MsqAND[4*i+1], MsqAND[4*i+2], MsqAND[4*i+3], 32-i))));
	   }
	  Memo->Lines->Add("   }");
	 }
  }
}
//---------------------------------------------------------------------------
void TFormMain::GenereCodeXOR(const String stNomFichierCur, const bool Suivant)
{
 unsigned short usiHeader[3], HotSpot[2];
 unsigned char Dimensions[2], Couleurs, Reserve;
 unsigned long Taille, Decalage;
 unsigned char EntetePNG[8];
 unsigned char EnteteCUR[40];
 unsigned char MsqXOR[128];
 unsigned char MsqAND[128];
 int f;
 if (stNomFichierCur.Length()>0)
  {
   if ((f=FileOpen(stNomFichierCur, fmOpenRead))>0)
	 {
	  String stNomCurseur=String(ExtractFileName(stNomFichierCur).SubString(1, ExtractFileName(stNomFichierCur).Length()-4)).UpperCase();
	  FileRead(f, &usiHeader, sizeof(usiHeader));
	  FileRead(f, &Dimensions, sizeof(Dimensions));
	  FileRead(f, &Couleurs, sizeof(Couleurs));
	  FileRead(f, &Reserve, sizeof(Reserve));
	  FileRead(f, &HotSpot, sizeof(HotSpot));
	  FileRead(f, &Taille, sizeof(Taille));
	  FileRead(f, &Decalage, sizeof(Decalage));
	  FileRead(f, &EntetePNG, sizeof(EntetePNG));
	  FileRead(f, &EnteteCUR, sizeof(EnteteCUR));
	  FileRead(f, &MsqXOR, sizeof(MsqXOR));
	  FileRead(f, &MsqAND, sizeof(MsqAND));
	  FileClose(f);
	  String stLigne;
	  if (Suivant)
		Memo->Lines->Add("  ,{ // Curseur "+stNomCurseur);
	  else
		Memo->Lines->Add("   { // Curseur "+stNomCurseur);
	  stLigne = "";
	  for(int i=31; i>=0; i--)
	   {
		if (i)
		  Memo->Lines->Add(Format("    0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X, // %02d",
								  ARRAYOFCONST((MsqXOR[4*i+0], MsqXOR[4*i+1], MsqXOR[4*i+2], MsqXOR[4*i+3], 32-i))));
		else
		  Memo->Lines->Add(Format("    0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X  // %02d",
								  ARRAYOFCONST((MsqXOR[4*i+0], MsqXOR[4*i+1], MsqXOR[4*i+2], MsqXOR[4*i+3], 32-i))));
	   }
	  Memo->Lines->Add("   }");
	 }
  }
}
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::FormShow(TObject *Sender)
{
 bool Suivant = false;
 TSearchRec sr;
 String stFiltre=ParamStr(1);
 Memo->Lines->Add("const BYTE ANDmaskCursor[NBCURSEURS][128] = {");
 if (!FindFirst(stFiltre, faArchive, sr))
  {
   do
	{
	 if ((sr.Attr & faArchive) == sr.Attr)
	   GenereCodeAND(ExtractFilePath(stFiltre)+sr.Name, Suivant);
	 Suivant=!FindNext(sr);
	}
   while (Suivant);
   FindClose(sr);
  }
 Suivant = false;
 Memo->Lines->Add("       }");
 Memo->Lines->Add("         , ANDmaskCursor[NBCURSEURS][128] = {");
 if (!FindFirst(stFiltre, faArchive, sr))
  {
   do
	{
	 if ((sr.Attr & faArchive) == sr.Attr)
	   GenereCodeXOR(ExtractFilePath(stFiltre)+sr.Name, Suivant);
	 Suivant=!FindNext(sr);
	}
   while (Suivant);
   FindClose(sr);
  }
 Memo->Lines->Add("       };");
}
//---------------------------------------------------------------------------

