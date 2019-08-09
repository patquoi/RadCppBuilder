//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <IniFiles.hpp>
#include "dtlcfg_f.h"
#include "main_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TFormDetailConfig *FormDetailConfig;
//---------------------------------------------------------------------------
const String stSectionParametres = "Paramètres";
const String stEntreeParametres[NBENTREES] = {"Dimensions","Agressivité","RapportPilulesPacGums","DuréeVulnerabilité","NombreFantomesDepart","NombrePortes"};
//---------------------------------------------------------------------------
void TFormDetailConfig::LitParametres()
{
  TIniFile *IniFile = new TIniFile(LabeledEditFichierIni->Text);
  try
   {
	 int Dimensions = IniFile->ReadInteger(stSectionParametres, stEntreeParametres[DIMENSIONS], 0);
	 int Agressivite = IniFile->ReadInteger(stSectionParametres, stEntreeParametres[AGRESSIVITE], 0);
	 int RapportPPG = IniFile->ReadInteger(stSectionParametres, stEntreeParametres[RAPPORTPPG], 1);
	 int Vulnerabilite = IniFile->ReadInteger(stSectionParametres, stEntreeParametres[VULNERABILITE], 0);
	 int Fantomes = IniFile->ReadInteger(stSectionParametres, stEntreeParametres[FANTOMES], 1);
	 int Portes = IniFile->ReadInteger(stSectionParametres, stEntreeParametres[PORTES], 1);
	 for(int i=0; i<TreeView->Items->Count; i++)
	  {
	   TTreeNode *TreeNode = TreeView->Items->Item[i];
	   // Dimensions
	   if ((TreeNode->Text == "48 x 30") && (Dimensions == 0))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "64 x 40") && (Dimensions == 1))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "80 x 50") && (Dimensions == 2))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "96 x 60") && (Dimensions == 3))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "112 x 70") && (Dimensions == 4))
		{ TreeNode->ImageIndex = 1; continue; }

	   // Agressivité
	   if ((TreeNode->Text == "25%") && (Agressivite == 0))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "33%") && (Agressivite == 1))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "50%") && (Agressivite == 2))
		{ TreeNode->ImageIndex = 1; continue; }

	   // Rapport Pilules/Pacgums
	   if ((TreeNode->Text == "1/50") && (RapportPPG == 0))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "1/100") && (RapportPPG == 1))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "1/150") && (RapportPPG == 2))
		{ TreeNode->ImageIndex = 1; continue; }

	   // Vulnérabilité
	   if ((TreeNode->Text == "100 cases") && (Vulnerabilite == 0))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "50 cases") && (Vulnerabilite == 1))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "25 cases") && (Vulnerabilite == 2))
		{ TreeNode->ImageIndex = 1; continue; }

	   // Fantômes
	   if ((TreeNode->Text == "3") && (Fantomes == 0))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "4") && (Fantomes == 1))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "5") && (Fantomes == 2))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "6") && (Fantomes == 3))
		{ TreeNode->ImageIndex = 1; continue; }

	   // Portes
	   if ((TreeNode->Text == "1/150 cases") && (Portes == 0))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "1/75 cases") && (Portes == 1))
		{ TreeNode->ImageIndex = 1; continue; }
	   if ((TreeNode->Text == "1/50 cases") && (Portes == 2))
		{ TreeNode->ImageIndex = 1; continue; }
	  }
   }
  __finally
   {
	 delete IniFile;
   }
}
//---------------------------------------------------------------------------
__fastcall TFormDetailConfig::TFormDetailConfig(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormDetailConfig::FormShow(TObject *Sender)
{
 TSearchRec sr;
 LabeledEditFichierIni->Text = FormMain->LabeledEditDossierCourant->Text + stFiltreFPac3Ini;
 if (!FindFirst(LabeledEditFichierIni->Text, faNormal, sr))
   LabeledEditDateHeureModification->Text = DateTimeToStr(sr.TimeStamp);
 FindClose(sr);
 TreeView->FullExpand();
 LitParametres();
}
//---------------------------------------------------------------------------

