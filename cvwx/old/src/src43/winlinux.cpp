//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
#include "winlinux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define NBTYPESMESSAGE 5
#define NBTYPESREPONSE 4
#define NBMAXBOUTONS   3
//---------------------------------------------------------------------------
#ifdef CV_WINDOWS
const int Style[NBTYPESMESSAGE]={MB_ICONINFORMATION, MB_ICONEXCLAMATION, MB_ICONHAND, MB_ICONQUESTION, MB_ICONQUESTION};
const int Boutons[NBTYPESMESSAGE]={MB_OK, MB_OK, MB_OK, MB_YESNO, MB_YESNOCANCEL};
const int BoutonDefaut[NBTYPESMESSAGE][NBMAXBOUTONS]={ {MB_DEFBUTTON1,MB_DEFBUTTON1,MB_DEFBUTTON1},
                                                       {MB_DEFBUTTON1,MB_DEFBUTTON1,MB_DEFBUTTON1},
                                                       {MB_DEFBUTTON1,MB_DEFBUTTON1,MB_DEFBUTTON1},
                                                       {MB_DEFBUTTON1,MB_DEFBUTTON2,MB_DEFBUTTON1},
                                                       {MB_DEFBUTTON1,MB_DEFBUTTON2,MB_DEFBUTTON3}};
#endif
//---------------------------------------------------------------------------
#ifdef CV_LINUX
const TMessageStyle Style[NBTYPESMESSAGE]={smsInformation, smsWarning, smsCritical, smsInformation, smsInformation};
const TMessageButtons Boutons[NBTYPESMESSAGE]={ TMessageButtons() << smbOK,
                                                TMessageButtons() << smbOK,
                                                TMessageButtons() << smbOK,
                                                TMessageButtons() << smbNo << smbYes,
                                                TMessageButtons() << smbCancel << smbNo << smbYes };
const TMessageButton BoutonDefautEchap[NBTYPESMESSAGE][NBMAXBOUTONS]={ {smbOK,smbOK,smbOK},
                                                                       {smbOK,smbOK,smbOK},
                                                                       {smbOK,smbOK,smbOK},
                                                                       {smbYes,smbNo,smbYes},
                                                                       {smbYes,smbNo,smbCancel}};
#endif
//---------------------------------------------------------------------------
const AnsiString asDebutNomSpinEdit = "CSpinEdit";
//---------------------------------------------------------------------------
type_reponse AfficheMessage(const AnsiString asMessage, const AnsiString asTitre, type_message Type, int OrdreBoutonDefaut, int OrdreBoutonEchap)
 {
#ifdef CV_WINDOWS
  switch(Application->MessageBox(asMessage.c_str(), asTitre.c_str(), Style[Type]+Boutons[Type]+BoutonDefaut[Type][OrdreBoutonDefaut]))
   {
    case IDOK :     return trOk;
    case IDCANCEL : return trAnnuler;
    case IDYES :    return trOui;
    case IDNO:      return trNon;
    default :       return trOk;
   }
#endif
#ifdef CV_LINUX
  switch(Application->MessageBox( (WideString)asMessage,
                                  (WideString)asTitre,
                                  Boutons[Type],
                                  Style[Type],
                                  BoutonDefautEchap[Type][OrdreBoutonDefaut],
                                  BoutonDefautEchap[Type][OrdreBoutonEchap]))
   {
    case smbOK:     return trOk;
    case smbCancel: return trAnnuler;
    case smbYes:    return trOui;
    case smbNo:     return trNon;
    default :       return trOk;
   }
#endif
 }
//---------------------------------------------------------------------------
void AfficheAideContextuelle(TForm *Form)
 {
#ifdef CV_WINDOWS
  WinHelp( Application->Handle,
           AnsiString(ExtractFilePath(ParamStr(0))+Form->HelpFile).c_str(),
           HELP_CONTEXT,
           Form->HelpContext);
#endif
 }
//---------------------------------------------------------------------------
void AfficheIndexAide(TForm *Form)
 {
#ifdef CV_WINDOWS
  WinHelp( Form->Handle,
           AnsiString(ExtractFilePath(ParamStr(0))+Form->HelpFile).c_str(),
           HELP_CONTEXT,
           0);
#endif
 }
//---------------------------------------------------------------------------
