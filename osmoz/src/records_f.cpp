//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "records_f.h"
#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmRecords *frmRecords;

const String stCleOsmoz = "Osmoz²",
			 stCleMot = "Mot",
			 stCleScore = "Score",
			 stClePointsPris = "PointsPris",
			 stCleLettresPrises = "LettresPrises",
			 stCleNom = "Nom",
			 stCleDate = "Date",
			 stCleRecords = "Records",
			 stCleRecord = "Record",
			 stCleSoftware = "Software",
			 stClePatquoiFr = "Patquoi.fr";

//---------------------------------------------------------------------------
__fastcall TfrmRecords::TfrmRecords(TComponent* Owner)
	: TForm(Owner)
{
 // v4.5 : Prise en charge HDPI
 Top=HDPI(Top);
 Left=HDPI(Left);
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecords::FormCreate(TObject *Sender)
{
 Registry=new TRegistry;
TypesRecordsBattus=trbAucun;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRecords::FormDestroy(TObject *Sender)
{
 delete Registry;
}
//---------------------------------------------------------------------------
void TfrmRecords::RafraichitRecords()
 {
   try
	{
	 if (Registry->OpenKey(stCleSoftware, true)&&
		 Registry->OpenKey(stClePatquoiFr, true)&&
		 Registry->OpenKey(stCleOsmoz, true)&&
		 Registry->OpenKey(stCleRecords, true)&&
		 Registry->OpenKey(stCleMot, true))
	  {
	   if (!Registry->ValueExists(stCleRecord))
		{
		 Registry->WriteString(stCleRecord, "");
		 Registry->WriteString(stCleNom, "");
		 Registry->WriteString(stCleDate, "");
		}
	   else
		{
		 LabelMot->Caption=Registry->ReadString(stCleRecord);
		 LabelNom1->Caption=Registry->ReadString(stCleNom);
		 LabelDate1->Caption=Registry->ReadString(stCleDate);
		}
	   Registry->CloseKey();
	  }
	 if (Registry->OpenKey(stCleSoftware, true)&&
		 Registry->OpenKey(stClePatquoiFr, true)&&
		 Registry->OpenKey(stCleOsmoz, true)&&
		 Registry->OpenKey(stCleRecords, true)&&
		 Registry->OpenKey(stCleScore, true))
	  {
	   if (!Registry->ValueExists(stCleRecord))
		{
		 Registry->WriteInteger(stCleRecord, 0);
		 Registry->WriteString(stCleNom, "");
		 Registry->WriteString(stCleDate, "");
		}
	   else
		{
		 LabelScore->Caption=IntToStr(Registry->ReadInteger(stCleRecord));
		 LabelNom2->Caption=Registry->ReadString(stCleNom);
		 LabelDate2->Caption=Registry->ReadString(stCleDate);
		}
	   Registry->CloseKey();
	  }
	 if (Registry->OpenKey(stCleSoftware, true)&&
		 Registry->OpenKey(stClePatquoiFr, true)&&
		 Registry->OpenKey(stCleOsmoz, true)&&
		 Registry->OpenKey(stCleRecords, true)&&
		 Registry->OpenKey(stClePointsPris, true))
	  {
	   if (!Registry->ValueExists(stCleRecord))
		{
		 Registry->WriteInteger(stCleRecord, 0);
		 Registry->WriteString(stCleNom, "");
		 Registry->WriteString(stCleDate, "");
		}
	   else
		{
		 LabelPointsPris->Caption=IntToStr(Registry->ReadInteger(stCleRecord));
		 LabelNom3->Caption=Registry->ReadString(stCleNom);
		 LabelDate3->Caption=Registry->ReadString(stCleDate);
        }
       Registry->CloseKey();
      }
     if (Registry->OpenKey(stCleSoftware, true)&&
         Registry->OpenKey(stClePatquoiFr, true)&&
         Registry->OpenKey(stCleOsmoz, true)&&
         Registry->OpenKey(stCleRecords, true)&&
         Registry->OpenKey(stCleLettresPrises, true))
      {
       if (!Registry->ValueExists(stCleRecord))
        {
         Registry->WriteInteger(stCleRecord, 0);
         Registry->WriteString(stCleNom, "");
         Registry->WriteString(stCleDate, "");
        }
       else
        {
         LabelLettresPrises->Caption=IntToStr(Registry->ReadInteger(stCleRecord));
         LabelNom4->Caption=Registry->ReadString(stCleNom);
         LabelDate4->Caption=Registry->ReadString(stCleDate);
        }
       Registry->CloseKey();
      }
    }
   catch(Exception &E)
   {
    Registry->CloseKey();
	Application->MessageBox(E.Message.c_str(), L"Une erreur s'est produite lors de l'accès aux records", MB_ICONHAND);
    return;
   }
 }
//---------------------------------------------------------------------------
void TfrmRecords::EnregistreRecords()
 {
   try
    {
     if ((TypesRecordsBattus&trbMot)&&
         Registry->OpenKey(stCleSoftware, true)&&
		 Registry->OpenKey(stClePatquoiFr, true)&&
         Registry->OpenKey(stCleOsmoz, true)&&
         Registry->OpenKey(stCleRecords, true)&&
         Registry->OpenKey(stCleMot, true))
      {
       Registry->WriteString(stCleRecord, LabelMot->Caption);
       Registry->WriteString(stCleNom, LabelNom1->Caption);
       Registry->WriteString(stCleDate, LabelDate1->Caption);
       Registry->CloseKey();
      }
     if ((TypesRecordsBattus&trbScore)&&
         Registry->OpenKey(stCleSoftware, true)&&
         Registry->OpenKey(stClePatquoiFr, true)&&
         Registry->OpenKey(stCleOsmoz, true)&&
         Registry->OpenKey(stCleRecords, true)&&
         Registry->OpenKey(stCleScore, true))
      {
       Registry->WriteInteger(stCleRecord, StrToInt(LabelScore->Caption));
       Registry->WriteString(stCleNom, LabelNom2->Caption);
       Registry->WriteString(stCleDate, LabelDate2->Caption);
       Registry->CloseKey();
      }
     if ((TypesRecordsBattus&trbPointsPris)&&
         Registry->OpenKey(stCleSoftware, true)&&
         Registry->OpenKey(stClePatquoiFr, true)&&
         Registry->OpenKey(stCleOsmoz, true)&&
         Registry->OpenKey(stCleRecords, true)&&
         Registry->OpenKey(stClePointsPris, true))
     {
       Registry->WriteInteger(stCleRecord, StrToInt(LabelPointsPris->Caption));
       Registry->WriteString(stCleNom, LabelNom3->Caption);
       Registry->WriteString(stCleDate, LabelDate3->Caption);
       Registry->CloseKey();
      }
     if ((TypesRecordsBattus&trbLettresPrises)&&
         Registry->OpenKey(stCleSoftware, true)&&
         Registry->OpenKey(stClePatquoiFr, true)&&
         Registry->OpenKey(stCleOsmoz, true)&&
         Registry->OpenKey(stCleRecords, true)&&
         Registry->OpenKey(stCleLettresPrises, true))
      {
       Registry->WriteInteger(stCleRecord, StrToInt(LabelLettresPrises->Caption));
       Registry->WriteString(stCleNom, LabelNom4->Caption);
	   Registry->WriteString(stCleDate, LabelDate4->Caption);
       Registry->CloseKey();
      }
    }
   catch(Exception &E)
   {
    Registry->CloseKey();
	Application->MessageBox(E.Message.c_str(), L"Une erreur s'est produite lors de l'enregistrement des records", MB_ICONHAND);
    return;
   }
 }
//---------------------------------------------------------------------------
void TfrmRecords::TesteRecords(AnsiString asNom, AnsiString asMot, int Score, int PointsPris, int LettresPrises)
 {
  AnsiString asDateHeure=FormatDateTime("dd/mm/yyyy hh:nn", Now());
  RafraichitRecords();
  TypesRecordsBattus=trbAucun;
  if (asMot.Length()>LabelMot->Caption.Length())
   {
	TypesRecordsBattus=trbMot;
	LabelMot->Caption=asMot;
	LabelNom1->Caption=asNom;
	LabelDate1->Caption=asDateHeure;
   }
  if (Score>StrToInt(LabelScore->Caption))
   {
	TypesRecordsBattus=(types_records_battus)(TypesRecordsBattus+trbScore);
	LabelScore->Caption=IntToStr(Score);
    LabelNom2->Caption=asNom;
    LabelDate2->Caption=asDateHeure;
   }
  if (PointsPris>StrToInt(LabelPointsPris->Caption))
   {
	TypesRecordsBattus=(types_records_battus)(TypesRecordsBattus+trbPointsPris);
    LabelPointsPris->Caption=IntToStr(PointsPris);
    LabelNom3->Caption=asNom;
    LabelDate3->Caption=asDateHeure;
   }
  if (LettresPrises>StrToInt(LabelLettresPrises->Caption))
   {
    TypesRecordsBattus=(types_records_battus)(TypesRecordsBattus+trbLettresPrises);
    LabelLettresPrises->Caption=IntToStr(LettresPrises);
    LabelNom4->Caption=asNom;
    LabelDate4->Caption=asDateHeure;
   }
  if (TypesRecordsBattus)
   {
    if (TypesRecordsBattus&trbMot) LabelMot->Font->Color=clRed;
    if (TypesRecordsBattus&trbScore) LabelScore->Font->Color=clRed;
    if (TypesRecordsBattus&trbPointsPris) LabelPointsPris->Font->Color=clRed;
    if (TypesRecordsBattus&trbLettresPrises) LabelLettresPrises->Font->Color=clRed;
    EnregistreRecords();
    Show();
    Timer->Enabled=true;
   }
 }

void __fastcall TfrmRecords::FormShow(TObject *Sender)
{
 RafraichitRecords();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecords::TimerTimer(TObject *Sender)
{
 TypesRecordsBattus=trbAucun;
 Timer->Enabled=false;
 LabelMot->Font->Color=clBlack;
 LabelScore->Font->Color=clBlack;
 LabelPointsPris->Font->Color=clBlack;
 LabelLettresPrises->Font->Color=clBlack;
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecords::ButtonOkClick(TObject *Sender)
{
 if (Timer->Enabled)
  {
   Timer->Enabled=false;
   LabelMot->Font->Color=clBlack;
   LabelScore->Font->Color=clBlack;
   LabelPointsPris->Font->Color=clBlack;
   LabelLettresPrises->Font->Color=clBlack;
  }
}
//---------------------------------------------------------------------------


