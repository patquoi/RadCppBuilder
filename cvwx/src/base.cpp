//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <System.StrUtils.hpp>
#include <System.win.Registry.hpp>
//---------------------------------------------------------------------------
#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define NBTYPESMESSAGE  5
#define NBTYPESREPONSE  4
#define NBMAXBOUTONS    3
#define NBCONTEXTESAIDE 56
//---------------------------------------------------------------------------
const int Style[NBTYPESMESSAGE]={MB_ICONINFORMATION, MB_ICONEXCLAMATION, MB_ICONHAND, MB_ICONQUESTION, MB_ICONQUESTION};
const int Boutons[NBTYPESMESSAGE]={MB_OK, MB_OK, MB_OK, MB_YESNO, MB_YESNOCANCEL};
const int BoutonDefaut[NBTYPESMESSAGE][NBMAXBOUTONS]={ {MB_DEFBUTTON1,MB_DEFBUTTON1,MB_DEFBUTTON1},
                                                       {MB_DEFBUTTON1,MB_DEFBUTTON1,MB_DEFBUTTON1},
                                                       {MB_DEFBUTTON1,MB_DEFBUTTON1,MB_DEFBUTTON1},
                                                       {MB_DEFBUTTON1,MB_DEFBUTTON2,MB_DEFBUTTON1},
                                                       {MB_DEFBUTTON1,MB_DEFBUTTON2,MB_DEFBUTTON3}};
//---------------------------------------------------------------------------
const AnsiString asDebutNomSpinEdit = "CSpinEdit";
//---------------------------------------------------------------------------
const struct { int Numero; const char *szHREF; } // v5.3 : aide type HLP converti en type HTML : correspondances TForm::HelpContext en URL "html\index.html#"
      caCorresp[NBCONTEXTESAIDE] =
                      {{ 0, "ASCV"},
                       {10, "BR"},
                       {20, "EDLS"},
                       {30, "PDLI"},
                       {31, "LMP"},
                       {3101, "LMF"},
                       {3102, "LMA"},
                       {3103, "LMSI"},
                       {3104, "LMST"},
                       {3105, "LMI"},
                       {311, "PDLS"},
                       {3111, "DDDDLZDS"},
                       {3112, "GADUR"},
                       {3121, "PDRDB"},
                       {3122, "PDRDT"},
                       {3123, "PDT"},
                       {3124, "PDV"},
                       {313, "CDLS"},
                       {314, "SDLS"},
                       {315, "SSLCDR"},
                       {316, "PDLADSDE"},
                       {32, "LBDO"},
                       {33, "LZDS"},
                       {3301, "LDEDLZDS"},
                       {3302, "LMD"},
                       {34, "LBDE"},
                       {40, "CDR"},
                       {41, "DDP"},
                       {415, "DDPP"},
                       {42, "DDF"},
                       {425, "DDFDP"},
                       {431, "ODC"},
                       {4311, "OCUCS"},
                       {4312, "OCPCS"},
                       {432, "C"},
                       {44, "BDN"},
                       {45, "DDLNDUZ"},
                       {50, "LDLS"},
                       {611, "EGDLS"},
                       {612, "SDFEDT"},
                       {62, "SDVDUEAUA"},
                       {63, "ADDJAE"},
                       {641, "ADDJAADB"},
                       {642, "ADDJAADT"},
                       {643, "ADDJAFDT"},
					   {644, "ADDJAFDP"},
                       {645, "ADDJAPDV"},
					   {65, "RDUEDLS"},
                       {66, "ISUV"},
                       {671, "ISUB"},
                       {672, "ISUT"},
                       {673, "ISUVDT"},
                       {674, "ISUVL"},
                       {68, "ISUP"},
                       {69, "RC"},
                       {70, "MDE"}};
//---------------------------------------------------------------------------
// v5.4 : Pour les fichiers créés par Centre-Ville
//        on utilise le chemin donné par %LocalAppData% pour Windows 7 ou plus
//        sinon le dossier de l'exécutable
//---------------------------------------------------------------------------
String stRepLocalAppData()
 {
   String stResult;
   String stExePath = ExtractFilePath(ParamStr(0));
   const String stVarLocalAppData  = "LOCALAPPDATA";
   const String stVarUserProfile  = "USERPROFILE";
   const String stRepLocAppDataCvw = "\\Patquoi.fr\\Centre-Ville\\";
   stResult = GetEnvironmentVariable(stVarLocalAppData);
   if (stResult == "")
	{ // Windows 7~10
	 stResult = GetEnvironmentVariable(stVarUserProfile);
	 if (stResult == "")
	   stResult = stExePath;
	 else
	  { // Windows XP
	   stResult = stResult + "\\Local Settings\\Application Data" + stRepLocAppDataCvw;
	   if (!DirectoryExists(stResult))
		 if (!ForceDirectories(stResult))
		   stResult = stExePath;
	  }
    }
   else
	{ // Autres
	 stResult = stResult + stRepLocAppDataCvw;
	 if (!DirectoryExists(stResult))
	   if (!ForceDirectories(stResult))
		 stResult = stExePath;
	}
   return stResult;
 }
//---------------------------------------------------------------------------
// v5.3. S'active automatiquement au lancement de cvw.exe avec le paramètre ! et génère un fichier cvw.log où se trouve cvw.exe à la fermeture de l'application
// Usage : DebugEcrit("message");
bool Debug = false;
TStringList *slDebug = NULL;
//---------------------------------------------------------------------------
void DebugOuvre()
 {
  Debug = true;
  slDebug = new TStringList;
 }
//---------------------------------------------------------------------------
void DebugEcrit(const AnsiString asMessage)
 {
  if (Debug&&slDebug)
   slDebug->Add(asMessage);
 }
//---------------------------------------------------------------------------
void DebugFerme()
 {
  String stCheminEtFichierLog = stRepLocalAppData()+"cvw.log";
  // On vide d'un coup dans un fichier
  if (slDebug)
   {
	slDebug->SaveToFile(stCheminEtFichierLog);
	delete slDebug;
   }
  Debug = false;
 }
//---------------------------------------------------------------------------
type_reponse AfficheMessage(const AnsiString asMessage, const AnsiString asTitre, type_message Type, int OrdreBoutonDefaut, int OrdreBoutonEchap)
 {// v5.4 : Conversion BCB6>BCBX (MessageBoxW + String)
  switch(MessageBoxW(Application->Handle, String(asMessage).w_str(), String(asTitre).w_str(), Style[Type]+Boutons[Type]+BoutonDefaut[Type][OrdreBoutonDefaut]))
   {
    case IDOK :     return trOk;
    case IDCANCEL : return trAnnuler;
    case IDYES :    return trOui;
    case IDNO:      return trNon;
	default :       return trOk;
   }
 }
//---------------------------------------------------------------------------
// v5.4 : procédure privée (base.cpp) pour afficher une page HTML
//---------------------------------------------------------------------------
void AffichePageHtml(const String stURL)
 {
  String stCommandeNavUrl;
  TRegistry *Reg = new TRegistry(KEY_READ);
  STARTUPINFO si; PROCESS_INFORMATION pi;
  ZeroMemory(&si,sizeof(STARTUPINFO));
  ZeroMemory(&pi,sizeof(PROCESS_INFORMATION));
  si.cb = sizeof(STARTUPINFO);
  try
   {
	Reg->RootKey = HKEY_CLASSES_ROOT;
	if (Reg->OpenKey("http\\Shell\\Open\\Command\\", false))
	  stCommandeNavUrl = Reg->ReadString("");
	  stCommandeNavUrl = ReplaceText(stCommandeNavUrl, "%1", stURL);
	  if (CreateProcess(NULL, stCommandeNavUrl.c_str(), NULL, NULL, false, 0, NULL, NULL, &si, &pi))
	  {
	   CloseHandle(pi.hProcess);
	   CloseHandle(pi.hThread);
	  }
   }
  __finally
   {
	delete Reg;
   }
 }
//---------------------------------------------------------------------------
void AfficheAideContextuelle(TForm *Form)
 {// v5.3 : conversion HLP > HTML.
  for(int i=0; i<NBCONTEXTESAIDE; i++)
	if (caCorresp[i].Numero==Form->HelpContext) // On recherche la rubrique HelpContext dans le tableau caCorresp
	 { // v5.4 : conversion BCB6>BCBX (L"open" + String)
	  String stURL = String("file:///")+
					 ExtractFilePath(ParamStr(0))+
					 String("html\\index.html#")+
					 String(caCorresp[i].szHREF);
	  AffichePageHtml(stURL); // v5.4 : appel à CreateProcess au lieu de ShellExecute
	  break;
	 }
 }
//---------------------------------------------------------------------------
void AfficheIndexAide(TForm *Form)
 {// v5.3 : conversion HLP > HTML
  // v5.4 : Conversion BCB6>BCBX (String + L"open")
  String stURL = String("file:///")+
				 ExtractFilePath(ParamStr(0))+
				 String("html\\index.html");
  AffichePageHtml(stURL); // v5.4 : appel à CreateProcess au lieu de ShellExecute
 }
//---------------------------------------------------------------------------
void AfficheTutoriel() // v5.4 (appelée par TfrmSimulation::ActionTutorielExecute
 {
  String stURL = String("file:///")+
				 ExtractFilePath(ParamStr(0))+
				 String("tutocv\\index.html");
  AffichePageHtml(stURL);
 }
