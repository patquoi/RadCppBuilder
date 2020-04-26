//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "base.h"
#include "param_f.h"
#include "messages_f.h"
#include "plateau_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmParametresAutomates *frmParametresAutomates;
//---------------------------------------------------------------------------
const String stSection="Automate",
			 stEntreePause="Pause",
			 stEntreeInterruption="Interruption",
			 stEntreeAutorisation="Deplacements",
			 stSectionPartie="Partie",
			 stEntreeEnregistrerMessages="EnregistrerMessages",
			 stEntreeTailleMax="TailleMax",
             stBool[2]={"N","O"};
//---------------------------------------------------------------------------
void TfrmParametresAutomates::LitParametres()
 {
  TempsPause=IniFile->ReadInteger(stSection, stEntreePause, 3);
  TailleMax=IniFile->ReadInteger(stSection, stEntreeTailleMax, 5);
  Interruption=(IniFile->ReadString(stSection, stEntreeInterruption, stBool[true])==stBool[true]);
  Autorisation=(IniFile->ReadString(stSection, stEntreeAutorisation, stBool[true])==stBool[true]);
  frmMessages->Timer->Interval=!TempsPause+1000*TempsPause;
  frmPlateau->Timer->Interval=!TempsPause+1000*TempsPause;

  TrackBar1->Position=TempsPause;
  TrackBar2->Position=TailleMax;
  CheckBoxInterruption->Checked=Interruption;
  CheckBoxAutorisation->Checked=Autorisation;
 }
//---------------------------------------------------------------------------
__fastcall TfrmParametresAutomates::TfrmParametresAutomates(TComponent* Owner)
	: TForm(Owner)
{
 IniFile=new TIniFile(stRepLocalAppData()+"Osmoz.ini");
 LitParametres();
}
//---------------------------------------------------------------------------
void __fastcall TfrmParametresAutomates::ButtonValiderClick(TObject *Sender)
{
 TempsPause=TrackBar1->Position;
 TailleMax=TrackBar2->Position;
 Interruption=CheckBoxInterruption->Checked;
 Autorisation=CheckBoxAutorisation->Checked;

 frmMessages->Timer->Interval=!TempsPause+1000*TempsPause;
 frmPlateau->Timer->Interval=!TempsPause+1000*TempsPause;
 IniFile->WriteInteger(stSection, stEntreePause, TrackBar1->Position);
 IniFile->WriteInteger(stSection, stEntreeTailleMax, TrackBar2->Position);
 IniFile->WriteString(stSection, stEntreeInterruption, stBool[CheckBoxInterruption->Checked]);
 IniFile->WriteString(stSection, stEntreeAutorisation, stBool[CheckBoxAutorisation->Checked]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmParametresAutomates::FormShow(TObject *Sender)
{
 LitParametres();
 TrackBar1->SetFocus();
}
//---------------------------------------------------------------------------


