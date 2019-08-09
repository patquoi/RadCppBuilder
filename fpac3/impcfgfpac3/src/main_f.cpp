//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_f.h"
#include "dtlcfg_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
const String stFiltreFPac3Ini 	= "FPac3.ini";
const String stTitreMessage 	= "Import de configuration FPac 3";
const String stFiltreDossiers   = "*.*";
//---------------------------------------------------------------------------
String GetLocalAppDataFPac3Folder()
 {
   const String stVarLocalAppData  = "LOCALAPPDATA";
   const String stRepLocAppDataFPac3 = "\\Patquoi.fr\\FPac3";
   String stResult;
   String stExePath = ExtractFilePath(ParamStr(0));
   stResult = GetEnvironmentVariable(stVarLocalAppData);
   if (stResult != "")
	{
	 stResult = stResult + stRepLocAppDataFPac3;
	 if (!DirectoryExists(stResult))
	   if (!ForceDirectories(stResult))
		 stResult = "";
	   else
		 stResult = stResult + "\\";
	 else
	   stResult = stResult + "\\";
	}
   return stResult;
 }
//---------------------------------------------------------------------------
TFormMain *FormMain;
//---------------------------------------------------------------------------
String	stLecteurCourant,
		stCheminCibleInstall; // Transmis en paramètres via Insfpac3
TStringList	*slCheminsTrv;
//---------------------------------------------------------------------------
void TFormMain::AffecteImage(const int ImageId, const bool Coche)
 {
  TImage *Image = (TImage*)FindComponent("Image" + IntToStr(ImageId));
  Image->Picture->Bitmap = NULL;
  if (Coche) ImageList->GetBitmap(1, Image->Picture->Bitmap);
  if (ImageId == 5)
   {
	Button0->Enabled = Coche; // Bouton Détails
	Button1->Enabled = Coche; // Bouton Voir
   }
 }
//---------------------------------------------------------------------------
bool TFormMain::FichierExistantEtDeTailleNonNulle(const String stNomFichier)
 {
  TSearchRec sr;
  bool bResult = false; // Pessimiste
  if (FileExists(stNomFichier))
	if (!FindFirst(stNomFichier, faNormal, sr))
	 {
	  bResult = (sr.Size>0); // Si taille nulle, on renvoie False
	  FindClose(sr);
	 }
   return bResult;
 }
//---------------------------------------------------------------------------
bool TFormMain::TrouveFichierFPac3Ini(const String stChemin)
 {
  TSearchRec sr;
  bool bResult;
  if (stChemin == "") // Lancement depuis le bouton Rechercher (appel initial)
   {
	// On part de zéro... On balaie les lecteurs fixes
	for(char i='A'; i<='Z'; i++) // On scrute les lecteurs fixes (disques durs)
	 {
	  stLecteurCourant[1] = i;
	  if (GetDriveType(stLecteurCourant.c_str()) == DRIVE_FIXED)
	   {
		bResult = TrouveFichierFPac3Ini(stLecteurCourant + "\\");
		if (bResult) return true; // On trouve on sort sinon on continue...
	   }
	 }
   }
  else // On a un chemin : on recherche FPac3.ini
   {
	LabeledEditDossierCourant->Text = stChemin;
	LabeledEditDossierCourant->Repaint();
	if (slCheminsTrv->IndexOf(stChemin) == -1) // Pas déjà trouvé
	 {
	  if (!FindFirst(stChemin+stFiltreFPac3Ini, faNormal, sr))
	   { // On a trouvé : on sort avec le chemin dans stDrnCheminTrv
		slCheminsTrv->Add(stChemin);
		FindClose(sr);
		return true;
	   }
	  else
		FindClose(sr);
     }
    // On recherche ensuite en profondeur
	if (!FindFirst(stChemin + stFiltreDossiers, faDirectory + faHidden, sr))
	 do
	  {
	   if ((sr.Name != ".") && (sr.Name != "..") &&
		   ((sr.Attr & faDirectory) == faDirectory))
		{
		 bResult = TrouveFichierFPac3Ini(stChemin + sr.Name + "\\");
		 if (bResult)
		  {
		   FindClose(sr);
		   return true; // On trouve on sort sinon on continue...
		  }
		}
	  }
	while(!FindNext(sr));
    FindClose(sr);
   }
  return false;
 }
//---------------------------------------------------------------------------
void TFormMain::AnalyseDossierTrouve()
 {
  AffecteImage(5, FichierExistantEtDeTailleNonNulle(slCheminsTrv->Strings[slCheminsTrv->Count-1] + stFiltreFPac3Ini));
  ButtonImporter->Enabled = true;
  RadioGroupModeImport->Enabled = true;
 }
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
 {
  stLecteurCourant=" :";
  stCheminCibleInstall=ParamStr(1)+"\\";
  slCheminsTrv = new TStringList();
  slCheminsTrv->Sorted=false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
 delete slCheminsTrv;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerTimer(TObject *Sender)
{
 if (!Tag) // Not busy
  {
   switch(Timer->Tag)
	{
	  case 0:	// 1. EXISTENCE DE %LocalAppData% ?
				Tag = 1;
				LabeledEditLocalAppData->Text = GetLocalAppDataFPac3Folder();
				if (LabeledEditLocalAppData->Text == "")
				 {
				  AffecteImage(1, false);
				  // Finalement on remplace %LocalAppData par le chemin cible de l'installation
				  LabeledEditLocalAppData->Text = stCheminCibleInstall;
				  Timer->Tag = Timer->Tag + 1;
				 }
				else
				 {
				  AffecteImage(1, true);
				  Timer->Tag = Timer->Tag + 1;
				 }
				Tag = 0; // Ready
				break;
	  case 1:   // 2. EXISTENCE de FPac3.ini dans %LocalAppData% ?
				Tag = 1; // Busy
				if (FichierExistantEtDeTailleNonNulle(LabeledEditLocalAppData->Text + "\\" + stFiltreFPac3Ini))
				 {
				  AffecteImage(2, false);
				  Timer->Enabled = false;
				  Application->MessageBox(String("\
Vous avez déjà une configuration FPac 3 dans votre dossier cible des données d'application.\n\n\
Elle sera donc prise en compte automatiquement après installation de la nouvelle version.").c_str(), stTitreMessage.c_str(), MB_ICONINFORMATION);
				  Application->Terminate();
				 }
				else
				 {
				  AffecteImage(2, true);
				  Timer->Tag = Timer->Tag + 1;
				 }
				Tag = 0; // Ready
				break;
	  case 2:   Tag = 1; // Busy
				AffecteImage(3, true);
				ButtonRechercher->Enabled = true;
				ButtonSelectionner->Enabled = true;
				Timer->Enabled = false;
				Application->MessageBox(String("\
Vous n'avez pas de configuration FPac 3 dans votre dossier cible des données d'application.\n\n\
Si vous avez déjà installé FPac 3 dans un autre dossier, vous pouvez importer la configuration en lançant une recherche ou en sélectionnant vous même le fichier de configuration.").c_str(), stTitreMessage.c_str(), MB_ICONINFORMATION);
				Tag = 0; // Ready
				break;
	}
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonRechercherClick(TObject *Sender)
 {
  TImage *ImageIni;
  // Initialisation
  Image4->Picture->Bitmap = NULL;
  Image5->Picture->Bitmap = NULL;
  Button0->Enabled = false;
  Button1->Enabled = false;
  LabeledEditDossierCourant->Text = "";
  ButtonRechercher->Enabled = false;
  ButtonSelectionner->Enabled = false;
  ButtonImporter->Enabled = false;
  RadioGroupModeImport->Enabled = false;
  // On lance la recherche via un timer pour rafraîchir la page
  TimerRecherche->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button1Click(TObject *Sender)
 {
  String stCheminEtNomFichierAVoir;
  stCheminEtNomFichierAVoir = LabeledEditDossierCourant->Text + stFiltreFPac3Ini;
  ShellExecute( NULL,
				String("Open").c_str(),
				ExtractFileName(stCheminEtNomFichierAVoir).c_str(),
				NULL,
				ExtractFilePath(stCheminEtNomFichierAVoir).c_str(),
				SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button0Click(TObject *Sender)
 {
  FormDetailConfig = new TFormDetailConfig(this);
  try
	{
	 FormDetailConfig->ShowModal();
	}
  __finally
	{
	 FormDetailConfig->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonSelectionnerClick(TObject *Sender)
{
 if (OpenDialogFPac3Ini->Execute())
  {
   LabeledEditDossierCourant->Text = ExtractFilePath(OpenDialogFPac3Ini->FileName);
   slCheminsTrv->Add(LabeledEditDossierCourant->Text);
   AnalyseDossierTrouve();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerRechercheTimer(TObject *Sender)
 {
  TimerRecherche->Enabled = false;
  if (TrouveFichierFPac3Ini(""))
   {
	AffecteImage(4, true);
	AnalyseDossierTrouve();
   }
  else
   {
	AffecteImage(4, false);
	LabeledEditDossierCourant->Text = "";
   }
  ButtonRechercher->Enabled = true;
  ButtonSelectionner->Enabled = true;
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonImporterClick(TObject *Sender)
 {
  int i, n=0;
  String stSource, stCible, stMsg;
  // On copie d'abord le fichier FPac3.ini...
  stSource = LabeledEditDossierCourant->Text + stFiltreFPac3Ini;
  stCible = LabeledEditLocalAppData->Text + stFiltreFPac3Ini;
  if (!CopyFile(stSource.c_str(), stCible.c_str(), false))
   {
	stMsg = Format("Impossible de copier '%s' dans '%s' !", ARRAYOFCONST((stSource, LabeledEditLocalAppData->Text)));
	Application->MessageBox(stMsg.c_str(), String("L'import a échoué !").c_str(), MB_ICONHAND);
	return;
   }
  else
   n = 1;
  if (RadioGroupModeImport->ItemIndex == 1) /* Déplacer */
   {
	// On supprime à la source le cas échéant...
	if (!DeleteFile(stSource))
	 {
	  stMsg = Format("Impossible de supprimer '%s' !", ARRAYOFCONST((stSource)));
	  Application->MessageBox(stMsg.c_str(), String("Import impossible").c_str(), MB_ICONHAND);
	 }
   }
  stMsg = Format("%d fichier(s) ont été %s(s) !", ARRAYOFCONST((n, (RadioGroupModeImport->ItemIndex==0)?"copié":"déplacé")));
  Application->MessageBox(stMsg.c_str(), String("L'import a réussi !").c_str(), MB_ICONINFORMATION);
  Application->Terminate();
 }
//---------------------------------------------------------------------------

