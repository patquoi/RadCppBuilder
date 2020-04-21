//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop

#include "prt_f.h"
#include "plt_f.h"
#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const     String stCleNumero = "Numero",
				 stCleScore = "Score",
				 stCleSerie = "Serie",
				 stCleChemin = "Chemin",
				 stCleDate = "Date",
				 stCleNiveau = "Niveau",
				 stCleParties = "Parties",
				 stCleSoftware = "Software",
				 stClePatquoiFr = "Patquoi.fr",
				 stTitreNum = "N°",
				 stTitreSerie = "Série",
				 stTitreNiv = "Niv",
				 stTitreDateHeure = "Date et heure";

TfrmParties *frmParties;
//---------------------------------------------------------------------------
__fastcall TfrmParties::TfrmParties(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmParties::FormShow(TObject *Sender)
{
 TStringList *slNom;
 // Initialisation des éléments visuels
 ComboBoxNom->Clear();
 StringGridParties->RowCount=11;
 StringGridParties->Cells[0][0]=stTitreNum;
 StringGridParties->Cells[1][0]=stTitreSerie;
 StringGridParties->Cells[2][0]=stTitreNiv;
 StringGridParties->Cells[3][0]=stCleScore;
 StringGridParties->Cells[4][0]=stTitreDateHeure;
 RadioGroupTypeSuppression->ItemIndex=0;
 EffaceTableauParties();
 ButtonAppliquer->Enabled=false;
 ButtonAnnuler->Enabled=false;
 if (!(slNom=new TStringList))
  {
   frmPlateau->AfficheMessage("Mémoire insuffisante pour lire les noms de joueurs !", MB_ICONHAND);
   return;
  }
 if (Registry->OpenKey(stCleSoftware, true)&&
	 Registry->OpenKey(stClePatquoiFr, true)&&
	 Registry->OpenKey(stCleLeBerger, true)&&
	 Registry->OpenKey(stCleParties, true))
  {
   Registry->GetKeyNames(slNom);
   Registry->CloseKey(); // On ferme pour libérer Registry à des fins récurrentes
   ComboBoxNom->Clear();
   ComboBoxNom->Items->AddStrings(slNom);
  }
 else Registry->CloseKey();

 delete slNom;

 ComboBoxNom->ItemIndex=ComboBoxNom->Items->IndexOf(frmPlateau->stNomJoueur);
 RafraichitParties();
 ComboBoxNom->SetFocus();
}

//---------------------------------------------------------------------------
void TfrmParties::RafraichitParties()
 {
  int i, n;
  TDateTime dt;
  TStringList *slPartie;
  EffaceTableauParties();
  if (ComboBoxNom->Text.IsEmpty()) return;
  if (!(slPartie=new TStringList))
   {
    frmPlateau->AfficheMessage("Mémoire insuffisante pour lire les informations sur les parties !", MB_ICONHAND);
    return;
   }
  if (Registry->OpenKey(stCleSoftware, true)&&
      Registry->OpenKey(stClePatquoiFr, true)&&
      Registry->OpenKey(stCleLeBerger, true)&&
      Registry->OpenKey(stCleParties, true)&&
      Registry->OpenKey(ComboBoxNom->Text, false))
   {
    Registry->GetKeyNames(slPartie);
    Registry->CloseKey(); // On ferme pour libérer Registry à des fins récurrentes
   }
  else Registry->CloseKey();

  n=slPartie->Count;
  StringGridParties->RowCount=(!n)?11:(1+n);
  StringGridParties->Cells[0][0]=stTitreNum;
  StringGridParties->Cells[1][0]=stTitreSerie;
  StringGridParties->Cells[2][0]=stTitreNiv;
  StringGridParties->Cells[3][0]=stCleScore;
  StringGridParties->Cells[4][0]=stTitreDateHeure;
  if (!n) return;

  for(i=0; i<n; i++)
   if (Registry->OpenKey(stCleSoftware, true)&&
       Registry->OpenKey(stClePatquoiFr, true)&&
       Registry->OpenKey(stCleLeBerger, true)&&
       Registry->OpenKey(stCleParties, true)&&
       Registry->OpenKey(ComboBoxNom->Text, false)&&
       Registry->OpenKey(slPartie->Strings[i], false))
    {
     StringGridParties->Cells[0][i+1]=slPartie->Strings[i];
     if (Registry->ValueExists(stCleSerie))
      StringGridParties->Cells[1][i+1]=Registry->ReadString(stCleSerie);
     if (Registry->ValueExists(stCleNiveau))
      StringGridParties->Cells[2][i+1]=Registry->ReadString(stCleNiveau);
     if (Registry->ValueExists(stCleScore))
      StringGridParties->Cells[3][i+1]=Registry->ReadString(stCleScore);
     if (Registry->ValueExists(stCleDate))
      {
       dt=Registry->ReadDateTime(stCleDate);
       StringGridParties->Cells[4][i+1]=((double)dt)?FormatDateTime("dd/mm/yyyy hh:nn", dt):stVide;
      }
     Registry->CloseKey();
    }
   else Registry->CloseKey();
    
  delete slPartie;
 }

void __fastcall TfrmParties::ComboBoxNomChange(TObject *Sender)
{
 RafraichitParties();
}
//---------------------------------------------------------------------------


void __fastcall TfrmParties::ButtonOkClick(TObject *Sender)
{
 ButtonAnnuler->Enabled=false;
 ButtonAppliquer->Enabled=false;
 switch(RadioGroupTypeSuppression->ItemIndex)
  {
   case 1: SupprimePartie(ComboBoxNom->Text, StringGridParties->Cells[0][StringGridParties->Row]);
           break;
   case 2: SupprimePartiesJoueur(ComboBoxNom->Text);
           break;
   case 3: SupprimeParties();
           break;
   default: break;
  }
 RadioGroupTypeSuppression->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmParties::RadioGroupTypeSuppressionClick(
      TObject *Sender)
{
 ButtonAnnuler->Enabled=(RadioGroupTypeSuppression->ItemIndex>0);
 ButtonAppliquer->Enabled=ButtonAnnuler->Enabled;
}
//---------------------------------------------------------------------------

void TfrmParties::EffaceTableauParties()
 {
  int i, n=StringGridParties->RowCount;
  for(i=1; i<n; i++)
   {
    StringGridParties->Cells[0][i]=stVide;
    StringGridParties->Cells[1][i]=stVide;
    StringGridParties->Cells[2][i]=stVide;
    StringGridParties->Cells[3][i]=stVide;
    StringGridParties->Cells[4][i]=stVide;
   }

 }
bool TfrmParties::SupprimePartie(String stNomJoueur, String stNumPartie)
 {
  bool Ok;
  if (stNomJoueur.IsEmpty()||
	  stNumPartie.IsEmpty()) return true;
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->OpenKey(stCleParties, false)&&
		 Registry->OpenKey(stNomJoueur, false)&&
         Registry->KeyExists(stNumPartie)))
   {
    Ok=Registry->DeleteKey(stNumPartie);
    Registry->CloseKey();
   }
  else Registry->CloseKey();
  RafraichitParties();
  return Ok;
 }

bool TfrmParties::SupprimePartiesJoueur(String stNomJoueur)
 {
  bool Ok=false;
  int i;
  TStringList *aslClePartie;
  if (stNomJoueur.IsEmpty()) return true;
  if (!(aslClePartie=new TStringList))
   {
    frmPlateau->AfficheMessage("Mémoire insuffisante pour supprimer les parties du joueur !", MB_ICONHAND);
    return false;
   }
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->OpenKey(stCleParties, false)&&
		 Registry->OpenKey(stNomJoueur, false)))
   {
    Registry->GetKeyNames(aslClePartie);
    Registry->CloseKey(); // On ferme pour libérer Registry à des fins récurrentes
    for(i=0; Ok&&(i<aslClePartie->Count); i++)
     Ok=SupprimePartie(stNomJoueur, aslClePartie->Strings[i]);
   }
  else Registry->CloseKey();
  delete aslClePartie;
  if (!Ok)
   {
    ComboBoxNom->ItemIndex=INDEFINI;
    ComboBoxNom->Items->Delete(ComboBoxNom->Items->IndexOf(stNomJoueur));
    RafraichitParties();
    return false;
   }
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->OpenKey(stCleParties, false)&&
		 Registry->KeyExists(stNomJoueur)))
   {
    Ok=Registry->DeleteKey(stNomJoueur);
    Registry->CloseKey();
   }
  else Registry->CloseKey();

  ComboBoxNom->ItemIndex=INDEFINI;
  ComboBoxNom->Items->Delete(ComboBoxNom->Items->IndexOf(stNomJoueur));
  RafraichitParties();
  return Ok;
 }

bool TfrmParties::SupprimeParties()
 {
  bool Ok=false;
  int i;
  TStringList *aslCleNomJoueur;
  if (!(aslCleNomJoueur=new TStringList))
   {
    frmPlateau->AfficheMessage("Mémoire insuffisante pour supprimer toutes les parties !", MB_ICONHAND);
    return false;
   }
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->OpenKey(stCleParties, false)))
   {
    Registry->GetKeyNames(aslCleNomJoueur);
    Registry->CloseKey(); // On ferme pour libérer Registry à des fins récurrentes
    for(i=0; Ok&&(i<aslCleNomJoueur->Count); i++)
     Ok=SupprimePartiesJoueur(aslCleNomJoueur->Strings[i]);
    Registry->CloseKey();
   }
  else Registry->CloseKey();

  delete aslCleNomJoueur;
  if (!Ok)
   {
    ComboBoxNom->Clear();
    RafraichitParties();
    return false;
   }
  if ((Ok=Registry->OpenKey(stCleSoftware, false)&&
		 Registry->OpenKey(stClePatquoiFr, false)&&
		 Registry->OpenKey(stCleLeBerger, false)&&
		 Registry->KeyExists(stCleParties)))
   {
    Ok=Registry->DeleteKey(stCleParties);
    Registry->CloseKey();
   }
  else Registry->CloseKey();
  
  ComboBoxNom->Clear();
  RafraichitParties();
  return Ok;
 }

bool TfrmParties::SupprimePartiesPrecedentes()
 {
  int i, j;
  long lNumero;
  TStringList *slNoms, *slParties;
  if (!frmPlateau->NumIdPartie) return true;
  if (!(slNoms=new TStringList))
   {
    frmPlateau->AfficheMessage("Mémoire insuffisante pour lire les infos de parties !", MB_ICONHAND);
    return false;
   }
  if (!(slParties=new TStringList))
   {
    frmPlateau->AfficheMessage("Mémoire insuffisante pour lire les infos de parties !", MB_ICONHAND);
    return false;
   }
  if (Registry->OpenKey(stCleSoftware, true)&&
      Registry->OpenKey(stClePatquoiFr, true)&&
      Registry->OpenKey(stCleLeBerger, true)&&
      Registry->OpenKey(stCleParties, true))
   {
    Registry->GetKeyNames(slNoms);
    Registry->CloseKey();
    for(i=0; i<slNoms->Count; i++)
     if (Registry->OpenKey(stCleSoftware, false)&&
         Registry->OpenKey(stClePatquoiFr, false)&&
         Registry->OpenKey(stCleLeBerger, false)&&
         Registry->OpenKey(stCleParties, false)&&
         Registry->OpenKey(slNoms->Strings[i], false))
      {
       Registry->GetKeyNames(slParties);
       Registry->CloseKey();
       for(j=0; j<slParties->Count; j++)
        if (Registry->OpenKey(stCleSoftware, false)&&
            Registry->OpenKey(stClePatquoiFr, false)&&
            Registry->OpenKey(stCleLeBerger, false)&&
            Registry->OpenKey(stCleParties, false)&&
            Registry->OpenKey(slNoms->Strings[i], false)&&
            Registry->OpenKey(slParties->Strings[j], false))
         {
          if (Registry->ValueExists(stCleNumero))
           {
            Registry->ReadBinaryData(stCleNumero, &lNumero, sizeof(lNumero));
            Registry->CloseKey();
            if ((lNumero==frmPlateau->NumIdPartie)&&
                Registry->OpenKey(stCleSoftware, false)&&
                Registry->OpenKey(stClePatquoiFr, false)&&
                Registry->OpenKey(stCleLeBerger, false)&&
                Registry->OpenKey(stCleParties, false)&&
                Registry->OpenKey(slNoms->Strings[i], false))
             {
              Registry->DeleteKey(slParties->Strings[j]);
              Registry->CloseKey();
             }
           }
         }
        else Registry->CloseKey();
      }
     else Registry->CloseKey();
   }
  else Registry->CloseKey();

  return true;
 }

void TfrmParties::EnregistrePartie()
 {
  wchar_t wsScore[10];
  int i;
  AnsiString stCleNumPartie;

  frmParties->SupprimePartiesPrecedentes();
  if (!frmPlateau->NumIdPartie)
   {
	DefinitNumIdPartie();
	frmParties->SupprimePartiesPrecedentes();
   }

  if (Registry->OpenKey(stCleSoftware, true)&&
	  Registry->OpenKey(stClePatquoiFr, true)&&
	  Registry->OpenKey(stCleLeBerger, true)&&
	  Registry->OpenKey(stCleParties, true)&&
	  Registry->OpenKey(frmPlateau->stNomJoueur, true))
   {
	for(i=0; Registry->KeyExists(stCleNumPartie=Format("%3.3d", ARRAYOFCONST((i)))); i++);
	if (Registry->OpenKey(stCleNumPartie, true))
	 {
	  Registry->WriteString(stCleSerie, frmPlateau->stNomSerieNiveau);
	  Registry->WriteString(stCleNiveau, Format("%3.3d", ARRAYOFCONST((Niv->Num))));
	  wsprintf(wsScore, L"%06ld", Niv->Cumul);
      Registry->WriteString(stCleScore, String(wsScore));
	  Registry->WriteString(stCleChemin, frmPlateau->stNomFichierNiveau);
      Registry->WriteDate(stCleDate, Now());
      Registry->WriteBinaryData(stCleNumero, &(frmPlateau->NumIdPartie), sizeof(frmPlateau->NumIdPartie));
      Registry->CloseKey();
     }
    else Registry->CloseKey();
   }
  else Registry->CloseKey();
 }

bool TfrmParties::ChargeInfosPartie(String stNomJoueur, String stNumPartie)
 {
  int Ok;
  if ((Ok=Registry->OpenKey(stCleSoftware, true)&&
		 Registry->OpenKey(stClePatquoiFr, true)&&
		 Registry->OpenKey(stCleLeBerger, true)&&
		 Registry->OpenKey(stCleParties, true)&&
		 Registry->OpenKey(stNomJoueur, false)&&
		 Registry->OpenKey(stNumPartie, false)))
   {
	frmPlateau->stNomJoueur=stNomJoueur;
	frmPlateau->stNomSerieNiveau=Registry->ReadString(stCleSerie);
    Niv->Num=StrToInt(Registry->ReadString(stCleNiveau));
    Niv->Cumul=_wtol(Registry->ReadString(stCleScore).c_str());
    frmPlateau->stNomFichierNiveau=Registry->ReadString(stCleChemin);
    Registry->ReadBinaryData(stCleNumero, &(frmPlateau->NumIdPartie), sizeof(frmPlateau->NumIdPartie));
    Registry->CloseKey();
   }
  else Registry->CloseKey();
  return Ok;
 }

void TfrmParties::DefinitNumIdPartie()
 {
  if (Registry->OpenKey(stCleSoftware, true)&&
	  Registry->OpenKey(stClePatquoiFr, true)&&
      Registry->OpenKey(stCleLeBerger, true)&&
      Registry->OpenKey(stCleParties, true))
   {
    if (Registry->ValueExists(stCleNumero)) // On prend le dernier numéro attribué.
     {
      Registry->ReadBinaryData(stCleNumero, &(frmPlateau->NumIdPartie), sizeof(frmPlateau->NumIdPartie));
      frmPlateau->NumIdPartie++;
     }
    else frmPlateau->NumIdPartie=1L; // Si pas encore de numéro attribué on prend 1.
    Registry->WriteBinaryData(stCleNumero, &(frmPlateau->NumIdPartie), sizeof(frmPlateau->NumIdPartie));
    Registry->CloseKey();
   }
  else Registry->CloseKey();
 }

void __fastcall TfrmParties::FormCreate(TObject *Sender)
{
 Registry=new TRegistry;
}
//---------------------------------------------------------------------------

void __fastcall TfrmParties::FormDestroy(TObject *Sender)
{
 delete Registry;
}
//---------------------------------------------------------------------------

void __fastcall TfrmParties::StringGridPartiesDblClick(TObject *Sender)
{
 ButtonOk->Click();   
}
//---------------------------------------------------------------------------





