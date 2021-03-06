//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
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
const struct { int Numero; char *szHREF; } // v5.3 : aide type HLP converti en type HTML : correspondances TForm::HelpContext en URL "html\index.html#"
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
// v5.3. S'active automatiquement au lancement de cvw.exe avec le param�tre ! et g�n�re un fichier cvw.log o� se trouve cvw.exe � la fermeture de l'application
// Usage : DebugEcrit("message");
bool Debug = false;
TStringList *slDebug = NULL;
AnsiString asDebugNomFichierLog;
void DebugOuvre(const AnsiString asNomFichierLog)
 {
  Debug = true;
  asDebugNomFichierLog = asNomFichierLog;
  slDebug = new TStringList;
 }
void DebugEcrit(const AnsiString asMessage)
 {
  if (Debug&&slDebug)
   slDebug->Add(asMessage);
 }
void DebugFerme()
 {
  // On vide d'un coup dans un fichier
  if (slDebug)
   {
    slDebug->SaveToFile(asDebugNomFichierLog);
    delete slDebug;
   }
  Debug = false;
 }
//---------------------------------------------------------------------------
type_reponse AfficheMessage(const AnsiString asMessage, const AnsiString asTitre, type_message Type, int OrdreBoutonDefaut, int OrdreBoutonEchap)
 {
  switch(Application->MessageBox(asMessage.c_str(), asTitre.c_str(), Style[Type]+Boutons[Type]+BoutonDefaut[Type][OrdreBoutonDefaut]))
   {
    case IDOK :     return trOk;
    case IDCANCEL : return trAnnuler;
    case IDYES :    return trOui;
    case IDNO:      return trNon;
    default :       return trOk;
   }
 }
//---------------------------------------------------------------------------
void AfficheAideContextuelle(TForm *Form)
 {// v5.3 : conversion HLP > HTML
  // WinHelp( Application->Handle, AnsiString(ExtractFilePath(ParamStr(0))+Form->HelpFile).c_str(), HELP_CONTEXT, Form->HelpContext);
  for(int i=0; i<NBCONTEXTESAIDE; i++)
    if (caCorresp[i].Numero==Form->HelpContext) // On recherche la rubrique HelpContext dans le tableau caCorresp
     {
      ShellExecute(Application->Handle,
                   NULL,
                   "explorer",
                   AnsiString(AnsiString("file:///")+
                              ExtractFilePath(ParamStr(0))+
                              "html\\index.html#"+
                              AnsiString(caCorresp[i].szHREF)).c_str(),
                   NULL,
                   SW_SHOWMAXIMIZED);
      break;
     }
 }
//---------------------------------------------------------------------------
void AfficheIndexAide(TForm *Form)
 {// v5.3 : conversion HLP > HTML
  // WinHelp( Form->Handle, AnsiString(ExtractFilePath(ParamStr(0))+Form->HelpFile).c_str(), HELP_CONTEXT, 0);
  ShellExecute(Application->Handle,
               NULL,
               "explorer",
               AnsiString(AnsiString("file:///")+
                          ExtractFilePath(ParamStr(0))+
                          "html\\index.html").c_str(),
               NULL,
               SW_SHOWMAXIMIZED);
 }
//---------------------------------------------------------------------------
