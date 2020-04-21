//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>
#include "records_f.h"
#include "base.h"
#include "plt_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const     String stCleScore = "Score",
				 stCleNom = "Nom",
				 stCleDate = "Date",
				 stCleDelaiOuNiv[2] = {"Niveau","Delai"},
				 stCleRecords = "Records",
				 stCleSoftware = "Software",
				 stClePatquoiFr = "Patquoi.fr",
				 stClePartie = "Partie";

const     String stTitreRec[2][5]={{"Cl","Nom","Score","Niv.","Date et heure"},
                                   {"Cl","Nom","Score","Pér.","Date et heure"}};


TfrmRecords *frmRecords;
//---------------------------------------------------------------------------
__fastcall TfrmRecords::TfrmRecords(TComponent* Owner)
    : TForm(Owner)
{
}

void TfrmRecords::RafraichitRecords()
 {
  int i, j;
  String stScore, stDelaiOuNiv, stDateHeure;
  for(i=0; i<10; i++)
   {
	stNom[i]=stVide; Score[i]=0L; DelaiOuNiv[i]=(RECORD_NIVEAU())?9999L:999L; DateHeure[i]=0;
	StringGrid->Cells[0][i+1]=stVide;
    StringGrid->Cells[1][i+1]=stVide;
    StringGrid->Cells[2][i+1]=stVide;
    StringGrid->Cells[3][i+1]=stVide;
    StringGrid->Cells[4][i+1]=stVide;
   }
  if (stSerie.IsEmpty()||stNiveau.IsEmpty()) return;
  try
   {
    for(i=0; i<10; i++)
     {
      if (!i)
       for(j=0; j<5; j++)
        StringGrid->Cells[j][0]=stTitreRec[RadioGroupTypeRecord->ItemIndex][j];
      StringGrid->Cells[0][i+1]=Format("%2d", ARRAYOFCONST((i+1)));
	  if (Registry->OpenKey(stCleSoftware, true)&&
		  Registry->OpenKey(stClePatquoiFr, true)&&
          Registry->OpenKey(stCleLeBerger, true)&&
		  Registry->OpenKey(stCleRecords, true)&&
		  Registry->OpenKey(stSerie, true)&&
          Registry->OpenKey(stNiveau, true)&&
          Registry->OpenKey(IntToStr(i), true))
       {
        stScore="000000";
        stDelaiOuNiv=(RECORD_NIVEAU())?"9999":"999";
        if (Registry->ValueExists(stCleDate))
         DateHeure[i]=Registry->ReadDateTime(stCleDate);
        StringGrid->Cells[4][i+1]=((double)DateHeure[i])?FormatDateTime("dd/mm/yyyy hh:nn", DateHeure[i]):stVide;

        if (Registry->ValueExists(stCleDelaiOuNiv[RadioGroupTypeRecord->ItemIndex]))
		 DelaiOuNiv[i]=_wtol((stDelaiOuNiv=Registry->ReadString(stCleDelaiOuNiv[RadioGroupTypeRecord->ItemIndex])).c_str());
		StringGrid->Cells[3][i+1]=stDelaiOuNiv;

		if (Registry->ValueExists(stCleScore))
		 Score[i]=_wtol((stScore=Registry->ReadString(stCleScore)).c_str());
		StringGrid->Cells[2][i+1]=stScore;

		if (Registry->ValueExists(stCleNom))
		 stNom[i]=Registry->ReadString(stCleNom);
		StringGrid->Cells[1][i+1]=stNom[i];

        Registry->CloseKey();
       }
      else Registry->CloseKey();
     }
   }
  __except(true)
   {
    frmPlateau->AfficheMessage("Une erreur s'est produite lors de l'accès aux records.", MB_ICONHAND);
    return;
   }
 }

//---------------------------------------------------------------------------
void __fastcall TfrmRecords::FormShow(TObject *Sender)
 {
  int i, j, di, Index;
  long NvScore=0L, NvDelaiOuNiv=0L;
  wchar_t ws[10];
  String stScore, stDelaiOuNiv, stDateHeure;
  TStringList *slSerie, *slNiveau;

  if (!(stSerie=frmPlateau->stNomSerieNiveau).IsEmpty())
   if (RECORD_NIVEAU())
	stNiveau=Format("%3.3d", ARRAYOFCONST((Niv->Num)));
   else
	stNiveau=stClePartie;
  else
   stNiveau=stVide;

  if (!(slSerie=new TStringList))
   {
	frmPlateau->AfficheMessage("Mémoire insuffisante pour lire les séries !", MB_ICONHAND);
	return;
   }
  if (Registry->OpenKey(stCleSoftware, true)&&
	  Registry->OpenKey(stClePatquoiFr, true)&&
	  Registry->OpenKey(stCleLeBerger, true)&&
	  Registry->OpenKey(stCleRecords, true))
   {
	Registry->GetKeyNames(slSerie);
	Registry->CloseKey(); // On ferme pour libérer Registry à des fins récurrentes
	ComboBoxSerie->Clear();
	ComboBoxSerie->Items->AddStrings(slSerie);
   }
  else Registry->CloseKey();
  delete slSerie;

  if (!ComboBoxSerie->Items->Count)
   if (stSerie.IsEmpty())
    return; // Pas de série connue et pas en cours : on fait rien
   else
    Index=ComboBoxSerie->Items->Add(stSerie);
  else
   if ((Index=ComboBoxSerie->Items->IndexOf(stSerie))==INDEFINI)
    if (!stSerie.IsEmpty()) Index=ComboBoxSerie->Items->Add(stSerie);
  ComboBoxSerie->ItemIndex=Index;
  if (ComboBoxSerie->ItemIndex>INDEFINI)
   stSerie=ComboBoxSerie->Items->Strings[ComboBoxSerie->ItemIndex];
  else
   return;

  if (!(slNiveau=new TStringList))
   {
    frmPlateau->AfficheMessage("Mémoire insuffisante pour lire les niveaux !", MB_ICONHAND);
    return;
   }
  if (Registry->OpenKey(stCleSoftware, true)&&
      Registry->OpenKey(stClePatquoiFr, true)&&
      Registry->OpenKey(stCleLeBerger, true)&&
      Registry->OpenKey(stCleRecords, true)&&
      Registry->OpenKey(stSerie, true))
   {
    Registry->GetKeyNames(slNiveau);
    if ((Index=slNiveau->IndexOf(stClePartie))>INDEFINI) // On retire la clé "Partie"
     slNiveau->Delete(Index);
    Registry->CloseKey(); // On ferme pour libérer Registry à des fins récurrentes
    ComboBoxNiveau->Clear();
    ComboBoxNiveau->Items->AddStrings(slNiveau);
   }
  else Registry->CloseKey();
  delete slNiveau;

  if (!ComboBoxNiveau->Items->Count)
   if (stNiveau.IsEmpty())
    return; // Pas de série connue et pas en cours : on fait rien
   else
    Index=ComboBoxNiveau->Items->Add(stNiveau);
  else
   if ((stNiveau!=stClePartie)&&
       ((Index=ComboBoxNiveau->Items->IndexOf(stNiveau))==INDEFINI))
    {
     Index=ComboBoxNiveau->Items->Add(stNiveau);
     ComboBoxNiveau->ItemIndex=Index;
     stNiveau=ComboBoxNiveau->Items->Strings[ComboBoxNiveau->ItemIndex];
    }
  
  Pos=INDEFINI;
  for(i=0; i<10; i++) { stNom[i]=""; Score[i]=0L; DelaiOuNiv[i]=(RECORD_NIVEAU())?9999L:999L; DateHeure[i]=0; }
  if (TesterNvEntree)
   {
    NvScore=(RECORD_NIVEAU())?Niv->Score:Niv->Cumul;
    NvDelaiOuNiv=(RECORD_NIVEAU())?Niv->Delai:(long)Niv->Num;
   }
  try
   {
    for(di=i=0; i+di<10; i++)
     {
      if (!i)
       for(j=0; j<5; j++)
        StringGrid->Cells[j][0]=stTitreRec[RadioGroupTypeRecord->ItemIndex][j];
      StringGrid->Cells[0][i+di+1]=Format("%2d", ARRAYOFCONST((i+di+1)));
      if (Registry->OpenKey(stCleSoftware, true)&&
          Registry->OpenKey(stClePatquoiFr, true)&&
          Registry->OpenKey(stCleLeBerger, true)&&
          Registry->OpenKey(stCleRecords, true)&&
          Registry->OpenKey(stSerie, true)&&
          Registry->OpenKey(stNiveau, true)&&
          Registry->OpenKey(IntToStr(i+di), true))
       {
		stScore="000000";
		stDelaiOuNiv=(RECORD_NIVEAU())?"9999":"999";
        
        if (Registry->ValueExists(stCleDate))
         DateHeure[i+di]=Registry->ReadDateTime(stCleDate);
        StringGrid->Cells[4][i+di+1]=((double)DateHeure[i+di])?FormatDateTime("dd/mm/yyyy hh:nn", DateHeure[i+di]):stVide;

        if (Registry->ValueExists(stCleDelaiOuNiv[RadioGroupTypeRecord->ItemIndex]))
		 DelaiOuNiv[i+di]=_wtol((stDelaiOuNiv=Registry->ReadString(stCleDelaiOuNiv[RadioGroupTypeRecord->ItemIndex])).c_str());
		StringGrid->Cells[3][i+di+1]=stDelaiOuNiv;

		if (Registry->ValueExists(stCleScore))
		 Score[i+di]=_wtol((stScore=Registry->ReadString(stCleScore)).c_str());
        StringGrid->Cells[2][i+di+1]=stScore;

        if (Registry->ValueExists(stCleNom))
         stNom[i+di]=Registry->ReadString(stCleNom);
        StringGrid->Cells[1][i+di+1]=stNom[i+di];

        Registry->CloseKey();
        if (TesterNvEntree&&
            (i<9)&&(!di)&&
            ((NvScore>Score[i])||
             ((NvScore==Score[i])&&(NvDelaiOuNiv<DelaiOuNiv[i]))))
         {
          di=1; Pos=i;
          // On décale...
          Score[Pos+1]=Score[Pos];
		  DelaiOuNiv[Pos+1]=DelaiOuNiv[Pos];
		  stNom[Pos+1]=stNom[Pos];
          DateHeure[Pos+1]=DateHeure[Pos];

          Score[Pos]=NvScore;
          DelaiOuNiv[Pos]=NvDelaiOuNiv;
          stNom[Pos]=stVide;
          DateHeure[Pos]=Now();

          wsprintf(ws, L"%06ld", Score[Pos+1]);
          stScore=String(ws);
		  wsprintf(ws, (RECORD_NIVEAU())?L"%04ld":L"%03ld", DelaiOuNiv[Pos+1]);
          stDelaiOuNiv=String(ws);

          StringGrid->Cells[4][Pos+2]=((double)DateHeure[Pos+1])?FormatDateTime("dd/mm/yyyy hh:nn", DateHeure[Pos+1]):stVide;
		  StringGrid->Cells[3][Pos+2]=stDelaiOuNiv;
		  StringGrid->Cells[2][Pos+2]=stScore;
          StringGrid->Cells[1][Pos+2]=stNom[Pos+1];
          StringGrid->Cells[0][Pos+2]=Format("%2d", ARRAYOFCONST((Pos+2)));

		  wsprintf(ws, L"%06ld", Score[Pos]);
		  stScore=String(ws);
		  wsprintf(ws, (RECORD_NIVEAU())?L"%04ld":L"%03ld", DelaiOuNiv[Pos]);
          stDelaiOuNiv=String(ws);

		  StringGrid->Cells[4][Pos+1]=stDateHeure=FormatDateTime("dd/mm/yyyy hh:nn", DateHeure[Pos]);
		  StringGrid->Cells[3][Pos+1]=stDelaiOuNiv;
          StringGrid->Cells[2][Pos+1]=stScore;
          StringGrid->Cells[1][Pos+1]=stNom[Pos];
          LabelPos->Caption=Format("%2d", ARRAYOFCONST((Pos+1)));
          LabelScore->Caption=stScore;
		  LabelDelaiOuNiv->Caption=stDelaiOuNiv;
          LabelDateHeure->Caption=stDateHeure;
          if (frmPlateau->stNomJoueur==stVide)
           {
            EditNom->Text=stVide;
            EditNom->ReadOnly=false;
            LabelNvEntree->Caption="Votre score entre dans le top 10, entrez votre nom :";
           }
          else
           {
			EditNom->Text=frmPlateau->stNomJoueur;
            stNom[Pos]=frmPlateau->stNomJoueur;
			StringGrid->Cells[1][Pos+1]=frmPlateau->stNomJoueur;
            EditNom->ReadOnly=true;
            LabelNvEntree->Caption="Votre score entre dans le top 10 :";
           }
          PanelNvEntree->Visible=true;
          ButtonAnnuler->Enabled=true;
          ButtonAppliquer->Enabled=true;
          ComboBoxSerie->Enabled=false;
          RadioGroupTypeRecord->Enabled=false;
          ComboBoxNiveau->Enabled=false;
          ActiveControl=EditNom;
          StringGrid->Row=Pos+1;
          Timer->Enabled=true;
         }
       }
      else Registry->CloseKey();
     }
   }
  __except(true)
   {
    frmPlateau->AfficheMessage("Une erreur s'est produite lors de l'accès aux records du niveau.", MB_ICONHAND);
    return;
   }
  ComboBoxNiveau->ItemIndex=ComboBoxNiveau->Items->IndexOf(stNiveau);
 }

//---------------------------------------------------------------------------
void __fastcall TfrmRecords::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if (Timer->Enabled) Timer->Enabled=false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmRecords::EditNomChange(TObject *Sender)
{
 stNom[Pos]=EditNom->Text;
 StringGrid->Cells[1][Pos+1]=stNom[Pos];
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecords::StringGridEnter(TObject *Sender)
{
 if (Pos>INDEFINI) StringGrid->Row=Pos+1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecords::StringGridClick(TObject *Sender)
{
 if (Pos>INDEFINI) StringGrid->Row=Pos+1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecords::ButtonOkClick(TObject *Sender)
{
 int i;
 wchar_t ws[10];
 String stScore, stDelaiOuNiv;
 ButtonAnnuler->Enabled=false;
 ButtonAppliquer->Enabled=false;
 switch(RadioGroupReinitialisation->ItemIndex)
  {
   case 1:   SupprimeRecordsNiveau(stSerie, stNiveau);
             break;
   case 2:   SupprimeRecordsSerie(stSerie);
             break;
   case 3:   SupprimeRecords();
             break;
   default : break;
  }

 if ((!TesterNvEntree)||(Pos==INDEFINI))
  {
   RadioGroupReinitialisation->ItemIndex=0;
   return;
  }
 frmPlateau->stNomJoueur=EditNom->Text;
 Pos=INDEFINI;
 try
  {
   for(i=0; i<10; i++)
    {
     if (Registry->OpenKey(stCleSoftware, true)&&
         Registry->OpenKey(stClePatquoiFr, true)&&
         Registry->OpenKey(stCleLeBerger, true)&&
         Registry->OpenKey(stCleRecords, true)&&
         Registry->OpenKey(stSerie, true)&&
         Registry->OpenKey(stNiveau, true)&&
         Registry->OpenKey(IntToStr(i), true))
      {
       Registry->WriteString(stCleNom, stNom[i]);
	   wsprintf(ws, L"%06ld", Score[i]);
	   stScore=String(ws);
	   wsprintf(ws, (RECORD_NIVEAU())?L"%04ld":L"%03ld", DelaiOuNiv[i]);
	   stDelaiOuNiv=String(ws);
	   Registry->WriteString(stCleScore, stScore);
       Registry->WriteString(stCleDelaiOuNiv[RadioGroupTypeRecord->ItemIndex], stDelaiOuNiv);
       Registry->WriteDateTime(stCleDate, DateHeure[i]);
       Registry->CloseKey();
      }
     else Registry->CloseKey();
    }
  }
 __except(true)
  {
   frmPlateau->AfficheMessage("Une erreur s'est produite lors de l'accès aux records du niveau.", MB_ICONHAND);
   RadioGroupReinitialisation->ItemIndex=0;
   return;
  }
 PanelNvEntree->Visible=false;
 Timer->Enabled=false;
 ComboBoxSerie->Enabled=true;
 RadioGroupTypeRecord->Enabled=true;
 ComboBoxNiveau->Enabled=true;
 RadioGroupReinitialisation->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecords::RadioGroupReinitialisationClick(
      TObject *Sender)
{
 ButtonAnnuler->Enabled=((TesterNvEntree&&(Pos>INDEFINI))||(RadioGroupReinitialisation->ItemIndex>0));
 ButtonAppliquer->Enabled=ButtonAnnuler->Enabled;
}
//---------------------------------------------------------------------------
bool TfrmRecords::SupprimeRecordsNiveau(String stSerieASupprimer, String stNivASupprimer)
 {
  bool Ok=false;
  int i;
  String stPos;
  if (stSerieASupprimer.IsEmpty()||
      stNivASupprimer.IsEmpty()) return true;
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->OpenKey(stCleRecords, false)&&
		 Registry->OpenKey(stSerieASupprimer, false)&&
		 Registry->OpenKey(stNivASupprimer, false)))
   {
    for(i=0; Ok&&(i<10); i++)
	 if (Registry->KeyExists(stPos=IntToStr(i)))
      Ok=Registry->DeleteKey(stPos);
    Registry->CloseKey();
   }
  else Registry->CloseKey();
  if (!Ok)
   {
    RafraichitRecords();
    return false;
   }
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->OpenKey(stCleRecords, false)&&
		 Registry->OpenKey(stSerieASupprimer, false)&&
		 Registry->KeyExists(stNivASupprimer)))
   {
    Ok=Registry->DeleteKey(stNivASupprimer);
    Registry->CloseKey();
   }
  else Registry->CloseKey();

  RafraichitRecords();
  return Ok;
 }

bool TfrmRecords::SupprimeRecordsSerie(String stSerieASupprimer)
 {
  bool Ok=false;
  int i;
  TStringList *slCleNiv;
  if (stSerieASupprimer.IsEmpty()) return true;
  if (!(slCleNiv=new TStringList))
   {
    frmPlateau->AfficheMessage("Mémoire insuffisante pour supprimer les records de la série !", MB_ICONHAND);
    return false;
   }
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->OpenKey(stCleRecords, false)&&
		 Registry->OpenKey(stSerieASupprimer, false)))
   {
	Registry->GetKeyNames(slCleNiv);
	Registry->CloseKey(); // On ferme pour libérer Registry à des fins récurrentes
	for(i=0; Ok&&(i<slCleNiv->Count); i++)
	 Ok=SupprimeRecordsNiveau(stSerieASupprimer, slCleNiv->Strings[i]);
   }
  else Registry->CloseKey();

  delete slCleNiv;
  if (!Ok)
   {
    ComboBoxNiveau->Clear();
    ComboBoxSerie->Clear();
    stSerie=stVide;
    stNiveau=stVide;
    RafraichitRecords();
    return false;
   }
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->OpenKey(stCleRecords, false)&&
		 Registry->KeyExists(stSerieASupprimer)))
   {
    Ok=Registry->DeleteKey(stSerieASupprimer);
    Registry->CloseKey();
   }
  else Registry->CloseKey();

  ComboBoxNiveau->Clear();
  ComboBoxSerie->Clear();
  stSerie=stVide;
  stNiveau=stVide;
  RafraichitRecords();
  return Ok;
 }

bool TfrmRecords::SupprimeRecords()
 {
  bool Ok=false;
  int i;
  TStringList *slCleSerie;
  if (!(slCleSerie=new TStringList))
   {
    frmPlateau->AfficheMessage("Mémoire insuffisante pour supprimer tous les records !", MB_ICONHAND);
    return false;
   }
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->OpenKey(stCleRecords, false)))
   {
    Registry->GetKeyNames(slCleSerie);
    Registry->CloseKey(); // On ferme pour libérer Registry à des fins récurrentes
    for(i=0; Ok&&(i<slCleSerie->Count); i++)
     Ok=SupprimeRecordsSerie(slCleSerie->Strings[i]);
    Registry->CloseKey();
   }
  else Registry->CloseKey();

  delete slCleSerie;
  if (!Ok)
   {
    ComboBoxNiveau->Clear();
    ComboBoxSerie->Clear();
    stSerie=stVide;
    stNiveau=stVide;
    RafraichitRecords();
    return false;
   }
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->KeyExists(stCleRecords)))
   {
    Ok=Registry->DeleteKey(stCleRecords);
    Registry->CloseKey();
   }
  else Registry->CloseKey();

  ComboBoxNiveau->Clear();
  ComboBoxSerie->Clear();
  stSerie=stVide;
  stNiveau=stVide;
  RafraichitRecords();
  return Ok;
 }

void __fastcall TfrmRecords::ComboBoxNiveauChange(TObject *Sender)
{
 stNiveau=ComboBoxNiveau->Text;
 RafraichitRecords();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecords::ComboBoxSerieChange(TObject *Sender)
{
 int Index;
 stSerie=ComboBoxSerie->Text;
 stNiveau="";
 TStringList *slNiveau;
 RadioGroupTypeRecord->ItemIndex=-1;
 RafraichitRecords();
 if (!(slNiveau=new TStringList))
  {
   frmPlateau->AfficheMessage("Mémoire insuffisante pour lire les niveaux !", MB_ICONHAND);
   return;
  }
 if (Registry->OpenKey(stCleSoftware, true)&&
     Registry->OpenKey(stClePatquoiFr, true)&&
     Registry->OpenKey(stCleLeBerger, true)&&
	 Registry->OpenKey(stCleRecords, true)&&
     Registry->OpenKey(stSerie, true))
  {
   Registry->GetKeyNames(slNiveau);
   if ((Index=slNiveau->IndexOf(stClePartie))>INDEFINI) // On retire la clé "Partie"
    slNiveau->Delete(Index);
   Registry->CloseKey(); // On ferme pour libérer Registry à des fins récurrentes
   ComboBoxNiveau->Clear();
   ComboBoxNiveau->Items->AddStrings(slNiveau);
  }
 else Registry->CloseKey();
 
 delete slNiveau;
}
//---------------------------------------------------------------------------


void __fastcall TfrmRecords::TimerTimer(TObject *Sender)
{
 Timer->Tag++;
 LabelNvEntree->Visible=!((Timer->Tag)%2);
}
//---------------------------------------------------------------------------


void __fastcall TfrmRecords::RadioGroupTypeRecordClick(TObject *Sender)
{
 ComboBoxNiveau->Visible=(RECORD_NIVEAU());
 if (RECORD_NIVEAU())
  {
   stNiveau=ComboBoxNiveau->Text;
   ComboBoxNiveau->SetFocus();
  }
 else
  stNiveau=stClePartie;
 RafraichitRecords();
}
//---------------------------------------------------------------------------






void __fastcall TfrmRecords::FormDestroy(TObject *Sender)
{
 delete Registry;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecords::FormCreate(TObject *Sender)
{
 Registry=new TRegistry;   
}
//---------------------------------------------------------------------------


