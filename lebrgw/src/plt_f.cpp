//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "plt_f.h"
#include "base.h"
#include "prmniv_f.h"
#include "apropos_f.h"
#include "records_f.h"
#include "prt_f.h"
#include "nomjou_f.h"
#include "comm_f.h"
#include "diplome_f.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmPlateau *frmPlateau;
const     String stTitre[2]={"Le Berger [PAUSE]", "Le Berger"},
				 stTesterNiveau="&Tester le niveau",
				 stArreterNiveau="&Arrêter le niveau",
				 stInterrompreNiveau="&Interrompre le niveau",
				 stContinuerNiveau="&Continuer le niveau",
				 stInterrompre="&Interrompre",
				 stContinuer="&Continuer",
				 stNouvelle="&Nouvelle",
				 stArreter="&Arrêter",
				 stRien="&Rien",
				 stTout="&Tout",
				 stVide = "",
				 stCleLeBerger = "Le Berger",
				 stExtNLB = "nlb",
				 stCleExtNLB = ".nlb",

                 stFichierIniLbrgw = "lebrgw.ini", // v1.7 : on ne reprend pas le nom de l'exécutable
				 stOpenDialogDefaultExt[2]={"nlb", "000.nlb"},
				 stOpenDialogFilter[2]={ "Niveaux Le berger (*.nlb)|*.NLB",
										 "1er niveau Le berger (*.000.nlb)|*.000.NLB"},
				 stOpenDialogFileName[2]={"serie1","original"},
				 stOpenDialogTitle[2]={"Choisissez le niveau d'une série", "Choisissez le premier niveau d'une série"},

				 stSectionParametres="Paramètres", // v1.6
				 stEntreeCommandes="Commandes",    // v1.6
				 stEntreeCouleurCurseur="CouleurCurseur",    // v1.6

				 stRaccourciClavier[3][4]={{"Haut", "Droite", "Bas", "Gauche"}, // v1.6 - Déplacé de comm_f
                                           {"Z", "S", "W", "Q"},
                                           {"8", "6", "2", "4"}};

const int NumIconeBete[NBDIR][NBDECAL][2]= {{{0,0},{0,0},{0,0},{0,0}},
                                            {{I_BEN,0},{I_FLN,I_DCN},{I_FCN,I_DCN},{I_FCN,I_DLN}},
                                            {{I_BEE,0},{I_FLE,I_DCE},{I_FCE,I_DCE},{I_FCE,I_DLE}},
                                            {{I_BES,0},{I_FLS,I_DCS},{I_FCS,I_DCS},{I_FCS,I_DLS}},
                                            {{I_BEO,0},{I_FLO,I_DCO},{I_FCO,I_DCO},{I_FCO,I_DLO}}};


//---------------------------------------------------------------------------
__fastcall TfrmPlateau::TfrmPlateau(TComponent* Owner)
    : TForm(Owner)
{
 LancementEnCours=false; // Initialisation de la propriété JeuEnCours
 PartieEnCours=false;
 IniFile=NULL;
 // 1.7 : Dossier par défaut des niveaux en lecture et en écriture
 SaveDialogNiveau->InitialDir = stRepLocalAppData();
 OpenDialogNiveau->InitialDir = ExtractFilePath(Application->ExeName)+"niv";
}

//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::FormShow(TObject *Sender)
{
 Mode=jeu;
 TypeAffMsg=boite_dialogue;
 SortieAutorisee=false;
 Charge1erNiveau=false;
 
 if ((frmAPropos=new TfrmAPropos(this)))
  {
   frmAPropos->ShowModal();
   delete frmAPropos;
  }

 // Enregistrement des liens avec les fichiers
 if (!Registry) return;

 // v1.7 : L'enregistrement de l'extension des fichiers NLB (Niveaux) est déplacée dans l'installation

 // Chargement des paramètres
 LitParametres(); //v1.6

 // Chargement à la demande
 // 1. Niveau
 if (ParamCount())
  {
   if (FileExists(ParamStr(1)))
    {
     stNomFichierNiveau=ParamStr(1);
     ChargeAutomatiquement();
     RubriqueQuadrillage->Click();
    }
   else
    Application->MessageBox(String("Le fichier \""+ParamStr(1)+"\" est introuvable !").c_str(),
                            stCleLeBerger.c_str(),
                            MB_ICONHAND);
  } 
}

void TfrmPlateau::RedessineCase(int x, int y, bool EffaceFond)
 {
  TRect CellWRect=DrawGrid->CellRect(x, y);
  RECT CellRect={CellWRect.Left, CellWRect.Top, CellWRect.Right, CellWRect.Bottom};
  InvalidateRect(DrawGrid->Handle, &CellRect, EffaceFond);
 }

//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::DrawGridDrawCell(TObject *Sender, int Col,
      int Row, TRect &Rect, TGridDrawState State)
{
 if (!AffichageAutorise) return;
  VirtualImageList->DrawingStyle=(JeuEnCours&&Niv->Lance&&
								  (Niv->x==Col)&&(Niv->y==Row))?
								 dsSelected:
								 (((DrawGrid->Col==Col)&&(DrawGrid->Row==Row))?
								  Imglist::TDrawingStyle::dsSelected:
								  Imglist::TDrawingStyle::dsNormal);
 VirtualImageList->Draw(DrawGrid->Canvas,
						Rect.Left,
						Rect.Top,
						48*((Niv->Num/10)%3)+
						Niv->NumImage(Col, Row,
									  AFF_BETES*RubriqueBetes->Checked+
									  AFF_PORTES*RubriquePortes->Checked+
									  AFF_DECL*RubriqueDeclencheurs->Checked));
 VirtualImageList->DrawingStyle=Imglist::TDrawingStyle::dsNormal;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueQuitterClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::ChangeMode(mode NvMode)
 {
  bool ModeEdit=(NvMode==editeur),
       Quadrillage=RubriqueQuadrillage->Checked;
  if (ModePrg==NvMode) return;
  if (ModeEdit)
   RubriqueEditeur->Checked=true;
  else
   {
    if (!ChargePremierNiveau())
     {
      RubriqueEditeur->Checked=true;
      NvMode=editeur;
      ModeEdit=true;
     }
    else
     RubriqueJeu->Checked=true;
   }
  if (ModeEdit&&Quadrillage)
   {
    DrawGrid->Options << goVertLine;
    DrawGrid->Options << goHorzLine;
   }
  else
   {
    DrawGrid->Options >> goVertLine;
    DrawGrid->Options >> goHorzLine;
   }
  Width+=NBX*((ModeEdit&&Quadrillage)+DrawGrid->DefaultColWidth)+4-DrawGrid->Width;
  Height+=NBY*((ModeEdit&&Quadrillage)+DrawGrid->DefaultRowHeight)+4-DrawGrid->Height;

  MenuPartie->Enabled=!ModeEdit;
  RubriqueNouvelle->Enabled=!ModeEdit;
  RubriqueOuvrir->Enabled=!ModeEdit;
  RubriqueChangerSerie->Enabled=!ModeEdit;
  
  MenuEditeur->Enabled=ModeEdit;
  RubriqueNouveauNiveau->Enabled=ModeEdit;
  RubriqueOuvrirNiveau->Enabled=ModeEdit;
  RubriqueOuvrirNiveauPrecedent->Enabled=ModeEdit;
  RubriqueOuvrirNiveauSuivant->Enabled=ModeEdit;
  RubriqueEnregistrerNiveau->Enabled=ModeEdit;
  RubriqueTesterNiveau->Enabled=ModeEdit;

  if (ModeEdit)
   RubriqueInterrompre->ShortCut=0; // Désactive le raccourci
  else
   RubriqueInterrompre->ShortCut=TextToShortCut("F5"); // Réactive le raccourci

  MenuAffEditeur->Enabled=ModeEdit;
  DrawGrid->PopupMenu=ModeEdit?PopupMenuEditeur:NULL;
  DrawGrid->Repaint();
  StatusBar->Panels->Items[0]->Width=StatusBar->Width-StatusBar->Panels->Items[1]->Width;
  RafraichitParametres(aff_tout);
  ModePrg=NvMode;
 }

void __fastcall TfrmPlateau::DemarreArreteJeu(bool LancerNiveau)
 {
  LancementEnCours=LancerNiveau; // Modification de la propriété JeuEnCours
  RafraichitTitre(!LancerNiveau);
  if (LancerNiveau)
   {
    TimerJeu->Interval=Niv->Delai;
    if (!Niv->Lance) Niv->Initialise();
	DrawGrid->PopupMenu=PopupMenuJeu;
    CmdTour = false; // v1.7 : On limite une commande par tour de jeu pour éviter la saturation des répétitions de touches
   }
  else DrawGrid->PopupMenu=(Mode==editeur)?PopupMenuEditeur:NULL;
  switch(Mode)
   {
	case jeu:     RubriqueInterrompre->Caption=(!LancerNiveau)?stContinuer:stInterrompre;
				  break;
	case editeur: RubriqueNouveauNiveau->Enabled=(!LancerNiveau);
				  RubriqueOuvrirNiveau->Enabled=(!LancerNiveau);
				  RubriqueOuvrirNiveauPrecedent->Enabled=(!LancerNiveau);
				  RubriqueOuvrirNiveauSuivant->Enabled=(!LancerNiveau);
				  RubriqueEnregistrerNiveau->Enabled=(!LancerNiveau);
				  RubriqueParametresNiveau->Enabled=(!LancerNiveau);
				  RubriqueInterrompreNiveau->Caption=(!LancerNiveau)?stContinuerNiveau:stInterrompreNiveau;
				  RubriqueInterrompreNiveau->Enabled=true;
				  break;
    default:      break;
   }
  TimerJeu->Enabled=LancerNiveau;
 }

void __fastcall TfrmPlateau::RubriqueJeuClick(TObject *Sender)
{
 Mode=jeu;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueEditeurClick(TObject *Sender)
{
 Mode=editeur;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPlateau::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
 bool JeuLance=(JeuEnCours||Niv->Lance),
      Interruption=JeuEnCours;
 if (JeuEnCours) JeuEnCours=false;
 CanClose=SortieAutorisee||(!JeuLance)||(Application->MessageBox(L"Jeu en cours...\nÊtes-vous sûr de vouloir quitter Le Berger ?", L"Confirmation", MB_ICONQUESTION+MB_YESNO)==IDYES);
 if (Interruption&&(!CanClose)) JeuEnCours=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriquePoserMurClick(TObject *Sender)
{
 int d;
 if (Niv->c[XG][YG].Type==mur) return; // Déja fait !
 if (!Niv->EstLiberable(XG, YG)) return; // Case non libérable
 if (Niv->c[XG][YG].Bete)
  {
   AfficheMessage("Vous ne pouvez pas poser de mur sur une case où il y a une bête.", MB_ICONEXCLAMATION);
   return;
  }
 Niv->c[XG][YG].Definit(mur, ouverte, NULL);
 RedessineCase(XG, YG, true);
 for(d=nord; d<=ouest; d++)
  RedessineCase(XG+dx[d], YG+dy[d], true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueLibererEspaceClick(TObject *Sender)
{
 int d;
 if (Niv->c[XG][YG].Type==rien) return; // Déja fait !
 if (!Niv->EstLiberable(XG, YG)) return; // Case non libérable
 Niv->c[XG][YG].Definit(rien, ouverte);
 RedessineCase(XG, YG, true);
 for(d=nord; d<=ouest; d++)
  RedessineCase(XG+dx[d], YG+dy[d], true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriquePoserPorteOClick(TObject *Sender)
{
 int d;
 if (Niv->c[XG][YG].Type==porte)
  {
   if (Niv->c[XG][YG].PosPorte==ouverte) return; // Déja fait !
   Niv->c[XG][YG].PosPorte=ouverte;
   Niv->c[XG][YG].SensPorte=ferme_ouvert;
  }
 else
  {
   if (!Niv->EstLiberable(XG, YG)) return; // Case non libérable
   if (((!Niv->EstUnMur(XG, YG, nord, AVEC_BORDS))||
        (!Niv->EstUnMur(XG, YG, sud, AVEC_BORDS)))&&
       ((!Niv->EstUnMur(XG, YG, est, AVEC_BORDS))||
        (!Niv->EstUnMur(XG, YG, ouest, AVEC_BORDS))))
    {
     AfficheMessage("Vous devez poser une porte ouverte entre deux murs ou entre un mur et le bord.", MB_ICONEXCLAMATION);
     return;
    }
   Niv->c[XG][YG].Type=porte;
  }
 Niv->c[XG][YG].PosPorte=ouverte;
 Niv->c[XG][YG].SensPorte=ferme_ouvert;
 RedessineCase(XG, YG, true);
 for(d=nord; d<=ouest; d++)
  RedessineCase(XG+dx[d], YG+dy[d], true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriquePoserPorteFClick(TObject *Sender)
{
 int d;
 if (Niv->c[XG][YG].Type==porte)
  {
   if (Niv->c[XG][YG].PosPorte==fermee) return; // Déja fait !
   Niv->c[XG][YG].PosPorte=fermee;
   Niv->c[XG][YG].SensPorte=ouvert_ferme;
  }
 else
  {
   if (!Niv->EstLiberable(XG, YG)) return; // Case non libérable
   if (((!Niv->EstUnMur(XG, YG, nord, AVEC_BORDS))||
        (!Niv->EstUnMur(XG, YG, sud, AVEC_BORDS)))&&
       ((!Niv->EstUnMur(XG, YG, est, AVEC_BORDS))||
        (!Niv->EstUnMur(XG, YG, ouest, AVEC_BORDS))))
    {
     AfficheMessage("Vous devez poser une porte fermée entre deux murs ou entre un mur et le bord.", MB_ICONEXCLAMATION);
     return;
    }
   Niv->c[XG][YG].Type=porte;
  }
 Niv->c[XG][YG].PosPorte=fermee;
 Niv->c[XG][YG].SensPorte=ouvert_ferme;
 RedessineCase(XG, YG, true);
 for(d=nord; d<=ouest; d++)
  RedessineCase(XG+dx[d], YG+dy[d], true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriquePoserDeclencheurBClick(TObject *Sender)
{
 int d;
 if (Niv->c[XG][YG].Type==decl_b) return; // Déja fait !
 if (!Niv->EstLiberable(XG, YG)) return; // Case non libérable
 if ((!Niv->EstUnePorte(XG,YG,nord))&&
     (!Niv->EstUnePorte(XG,YG,est))&&
     (!Niv->EstUnePorte(XG,YG,sud))&&
     (!Niv->EstUnePorte(XG,YG,ouest)))
  {
   AfficheMessage("Vous devez poser un déclencheur bleu à côté d'une porte.", MB_ICONEXCLAMATION);
   return;
  }
 Niv->c[XG][YG].Definit(decl_b, ouverte);
 RedessineCase(XG, YG, true);
 for(d=nord; d<=ouest; d++)
  RedessineCase(XG+dx[d], YG+dy[d], true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriquePoserDeclencheurRClick(TObject *Sender)
{
 int d;
 if (Niv->c[XG][YG].Type==decl_r) return; // Déja fait !
 if (!Niv->EstLiberable(XG, YG)) return; // Case non libérable
 if ((!Niv->EstUnePorte(XG,YG,nord))&&
     (!Niv->EstUnePorte(XG,YG,est))&&
     (!Niv->EstUnePorte(XG,YG,sud))&&
     (!Niv->EstUnePorte(XG,YG,ouest)))
  {
   AfficheMessage("Vous devez poser un déclencheur rouge à côté d'une porte.", MB_ICONEXCLAMATION);
   return;
  }
 Niv->c[XG][YG].Definit(decl_r, ouverte);
 RedessineCase(XG, YG, true);
 for(d=nord; d<=ouest; d++)
  RedessineCase(XG+dx[d], YG+dy[d], true);
}
//---------------------------------------------------------------------------


void __fastcall TfrmPlateau::RubriquePoserRetirerBeteClick(TObject *Sender)
{
 bool ExisteBete;
 if (!(ExisteBete=!Niv->c[XG][YG].Bete))
  Niv->RetireBete(Niv->c[XG][YG].Bete->Num);
 else
  {
   if (Niv->c[XG][YG].Type==mur)
    {
     AfficheMessage("Vous ne pouvez pas poser de bête sur un mur.", MB_ICONEXCLAMATION);
     return;
    }
   if ((Niv->c[XG][YG].Type==porte)&&
       Niv->c[XG][YG].PosPorte)
    {
     AfficheMessage("Vous ne pouvez pas poser de bête sur une porte qui n'est pas ouverte.", MB_ICONEXCLAMATION);
     return;
    }
   if (!(Niv->c[XG][YG].Bete=Niv->AjouteBete(XG, YG, nord)))
    {
     AfficheMessage("Vous ne pouvez plus ajouter de bêtes.", MB_ICONEXCLAMATION);
     return;
    }
  }
 RedessineCase(XG, YG, true);
 RubriquePoserRetirerBete->Caption=ExisteBete?"&Retirer la bête":"&Poser une bête";
 RubriqueOrienterBeteG->Enabled=ExisteBete;
 RubriqueOrienterBeteD->Enabled=ExisteBete;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueOrienterBeteGClick(TObject *Sender)
{
 if (Niv->c[XG][YG].Bete)
  {
   Niv->c[XG][YG].Bete->TourneAGauche();
   RedessineCase(XG, YG, true);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueOrienterBeteDClick(TObject *Sender)
{
 if (Niv->c[XG][YG].Bete)
  {
   Niv->c[XG][YG].Bete->TourneADroite();
   RedessineCase(XG, YG, true);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::DrawGridClick(TObject *Sender)
{
 bool ExisteBete=!!(Niv->c[XG][YG].Bete);
 RubriquePoserRetirerBete->Caption=ExisteBete?"Retirer la bête":"Poser une bête";
 RubriqueOrienterBeteG->Enabled=ExisteBete;
 RubriqueOrienterBeteD->Enabled=ExisteBete;
 switch((!DrawGrid->Tag)*((Mode==editeur)+2*((JeuEnCours)||(Niv->Lance))))
  {
   case 1:  Niv->x0=XG; Niv->y0=YG; break;
   case 2:
   case 3:  Niv->x=XG; Niv->y=YG; break;
   default: if ((Mode==jeu)||JeuEnCours||Niv->Lance)
             {
              Tag=0;
              DrawGrid->Col=(JeuEnCours||Niv->Lance)?Niv->x:Niv->x0;
              DrawGrid->Row=(JeuEnCours||Niv->Lance)?Niv->y:Niv->y0;
             }
            break; 
  }
 StatusBar->Panels->Items[1]->Text=Format("(%d,%d)", ARRAYOFCONST((XG, YG)));
}
//---------------------------------------------------------------------------



void __fastcall TfrmPlateau::RubriqueQuadrillageClick(TObject *Sender)
{
 bool Quadrillage;
 RubriqueQuadrillage->Checked=!RubriqueQuadrillage->Checked;
 if ((Quadrillage=RubriqueQuadrillage->Checked))
  {
   DrawGrid->Options << goVertLine;
   DrawGrid->Options << goHorzLine;
  }
 else
  {
   DrawGrid->Options >> goVertLine;
   DrawGrid->Options >> goHorzLine;
  }
 Width+=NBX*(Quadrillage+DrawGrid->DefaultColWidth)+4-DrawGrid->Width;
 Height+=NBY*(Quadrillage+DrawGrid->DefaultRowHeight)+4-DrawGrid->Height;
 DrawGrid->Repaint();
 StatusBar->Panels->Items[0]->Width=StatusBar->Width-StatusBar->Panels->Items[1]->Width;
 RafraichitParametres(aff_tout);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueBetesClick(TObject *Sender)
{
 RubriqueBetes->Checked=!RubriqueBetes->Checked;
 DrawGrid->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriquePortesClick(TObject *Sender)
{
 RubriquePortes->Checked=!RubriquePortes->Checked;
 DrawGrid->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueDeclencheursClick(TObject *Sender)
{
 RubriqueDeclencheurs->Checked=!RubriqueDeclencheurs->Checked;
 DrawGrid->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueToutClick(TObject *Sender)
{
 bool ToutAfficher=(RubriqueTout->Caption==stTout);
 RubriqueBetes->Checked=ToutAfficher;
 RubriquePortes->Checked=ToutAfficher;
 RubriqueDeclencheurs->Checked=ToutAfficher;
 if (ToutAfficher)
  RubriqueTout->Caption=stRien;
 else
  RubriqueTout->Caption=stTout;
 DrawGrid->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueOuvrirNiveauClick(TObject *Sender)
{
 long CumulSvg=Niv->Cumul;
 String stNomFichier="";
 int hfile;
 OpenDialogNiveau->DefaultExt=stOpenDialogDefaultExt[Charge1erNiveau];
 OpenDialogNiveau->Filter=stOpenDialogFilter[Charge1erNiveau];
 OpenDialogNiveau->FileName=stOpenDialogFileName[Charge1erNiveau];
 OpenDialogNiveau->Title=stOpenDialogTitle[Charge1erNiveau];
 if (ChargementAuto||OpenDialogNiveau->Execute())
  {
   if ((hfile=FileOpen(stNomFichier=(ChargementAuto?stNomFichierNiveau:OpenDialogNiveau->FileName), fmOpenRead)))
	{
	 //Application->MessageBox(stNomFichier.c_str(), stNomFichier.c_str(), MB_ICONINFORMATION);
	 if (stNomFichier.SubString(stNomFichier.Length()-3, 4).LowerCase()!=stCleExtNLB)
	  stNomFichier=stNomFichier+stCleExtNLB;
	 stNomSerieNiveau=ExtractFileName(stNomFichier).SubString(1, ExtractFileName(stNomFichier).Length()-8);
	 if (!ChargementAuto) stNomFichierNiveau=OpenDialogNiveau->FileName;
     AfficheMessage("Chargement en cours...", 0);
	 SaveDialogNiveau->FileName=stNomFichier;
     FileSeek(hfile, 0, 0);
     AffichageAutorise=false;
     if (Niv) { delete Niv; Niv=NULL; }
	 if ((Niv=new niveau(PartieEnCours?CumulSvg:0L)))
      {
       AffichageAutorise=true;
       if (!Niv->Charge(hfile))
        {
         AfficheMessage("Erreur de données dans le fichier. Chargement non effectué.", MB_ICONHAND);
         FileClose(hfile);
         SortieAutorisee=true;
         Close();
        }
       else
        {
         FileClose(hfile);
         AfficheMessage("Chargement effectué.", 0);
        }
      }
     else
      {
       AfficheMessage("Mémoire insuffisante !", MB_ICONHAND);
       SortieAutorisee=true;
       Close();
      }

     // On va chercher le commentaire le cas échéant
     if (IniFile) delete IniFile;
	 IniFile=new TIniFile(stNomFichier.SubString(1, stNomFichier.Length()-8)+".ini");
     if (IniFile)
	  stCommentaire=IniFile->ReadString("Commentaires", stNomFichier.SubString(stNomFichier.Length()-6, 3), "");
     else
	  stCommentaire="";
     RafraichitTitre(false);
     DrawGrid->Repaint();
     RafraichitParametres(aff_tout);
     DrawGrid->Tag=1; // Indique de ne pas mettre à jour les coordonnées (x0,y0)
     DrawGrid->Col=Niv->x0;
     DrawGrid->Row=Niv->y0;
     DrawGrid->Tag=0;
    }
   else
    {
     AfficheMessage("Impossible d'ouvrir le fichier. Chargement non effectué.", MB_ICONHAND);
	 stNomSerieNiveau=stVide;
	}
   OpenDialogNiveau->FileName=stVide;
  }
 else
  if (!ChargementAuto) stNomSerieNiveau=stVide;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueEnregistrerNiveauClick(
      TObject *Sender)
{
 String stNomFichier="";
 int hfile;
 if (!Niv->c[Niv->x0][Niv->y0].EstFranchissable())
  {
   Application->MessageBox(L"Vous devez laisser le curseur sur une case libre (position initiale du niveau).", L"Editeur de niveau", MB_ICONEXCLAMATION);
   return;
  }
 SaveDialogNiveau->FileName=((stNomSerieNiveau=="")?String("serie1"):stNomSerieNiveau)+Format(".%3.3d", ARRAYOFCONST((Niv->Num)));
 if (SaveDialogNiveau->Execute())
  {
   stNomFichierNiveau=SaveDialogNiveau->FileName;
   AfficheMessage("Enregistrement en cours...", 0);
   stNomFichier=stNomFichier=SaveDialogNiveau->FileName;
   try
    {
     StrToInt(stNomFichier.SubString(stNomFichier.Length()-6, 3));
     stNomFichier=stNomFichier.SubString(1, stNomFichier.Length()-7)+
                  Format("%3.3d", ARRAYOFCONST((Niv->Num)))+ExtractFileExt(stNomFichier);
    }
   __except(true)
    {
     stNomFichier=stNomFichier.SubString(1, stNomFichier.Length()-3)+
                  Format("%3.3d", ARRAYOFCONST((Niv->Num)))+ExtractFileExt(stNomFichier);
    }
   stNomSerieNiveau=ExtractFileName(stNomFichier).SubString(1, ExtractFileName(stNomFichier).Length()-8);
   if ((hfile=FileCreate(stNomFichier)))
    {
     if (!Niv->Sauve(hfile))
      {
       AfficheMessage("Erreur de données dans le fichier. Enregistrement non effectué.", MB_ICONHAND);
       FileClose(hfile);
      }
     else
      {
       FileClose(hfile);
       AfficheMessage("Enregistrement terminé.", 0);
       return;
      }
    }
   else AfficheMessage("Impossible de créer le fichier. Enregistrement non effectué.", MB_ICONHAND);
  }
}
//---------------------------------------------------------------------------


void __fastcall TfrmPlateau::RubriqueParametresNiveauClick(TObject *Sender)
{
 
 if (JeuEnCours) JeuEnCours=false;
 frmPrmNiveau->CheckBoxBordure->Checked=false;
 frmPrmNiveau->CheckBoxBordure->Enabled=false;
 frmPrmNiveau->ShowModal();
 DrawGrid->Repaint();
 
}
//---------------------------------------------------------------------------

void TfrmPlateau::AfficheMessage(String stMsg, int Flag)
 {
  if (TypeAffMsg&&Flag)
   Application->MessageBox(stMsg.c_str(), Application->Title.c_str(), Flag);
  else
   {
	stMsgCrt=stMsg;
    PosCrtMsg=0;
    if (!TimerMsg->Enabled) TimerMsg->Enabled=true;
   }
 }

void TfrmPlateau::RafraichitParametres(affichage Affichage)
 {
  wchar_t wsAffichage[256];
  int TaillePanneau=PanelScores->Width;
  if (Affichage==aff_tout)
   {
	LabelEffet->Left=TaillePanneau-DXAFF_NEFFET;
	LabelEffet0->Left=TaillePanneau-DXAFF_LEFFET;
	LabelReste->Left=TaillePanneau-DXAFF_NRESTE;
	LabelReste0->Left=TaillePanneau-DXAFF_LRESTE;
	LabelTemps->Left=TaillePanneau-DXAFF_NTEMPS;
	LabelTemps0->Left=TaillePanneau-DXAFF_LTEMPS;
	LabelBarre->Left=TaillePanneau-DXAFF_NBARRE;
	LabelBarre0->Left=TaillePanneau-DXAFF_LBARRE;
	LabelScore->Left=TaillePanneau-DXAFF_NSCORE;
	LabelScore0->Left=TaillePanneau-DXAFF_LSCORE;
	LabelNiveau->Left=TaillePanneau-DXAFF_NNIV;
	LabelNiveau0->Left=TaillePanneau-DXAFF_LNIV;
   }
  if (Affichage&aff_serie)
   {
	LabelSerie->Caption=stNomSerieNiveau;
	LabelSerie->Repaint();
   }
  if (Affichage&aff_niv)
   {
    LabelNiveau->Caption=Format("%3.3d", ARRAYOFCONST((Niv->Num)));
    LabelNiveau->Repaint();
   }
  if (Affichage&aff_score)
   {
	wsprintf(wsAffichage, L"%06ld", Niv->Cumul);
	LabelScore->Caption=String(wsAffichage);
	LabelScore->Repaint();
   }
  if (Affichage&aff_barre)
   {
	wsprintf(wsAffichage, L"%06ld", Niv->Barre);
	LabelBarre->Caption=String(wsAffichage);
	LabelBarre->Repaint();
   }
  if (Affichage&aff_temps)
   {
	wsprintf(wsAffichage, L"%04ld", Niv->TpsRestant);
	LabelTemps->Caption=String(wsAffichage);
	LabelTemps->Repaint();
   }
  if (Affichage&aff_reste)
   {
	LabelReste->Caption=Format("%3.3d", ARRAYOFCONST((Niv->NbBetesAFaire-Niv->NbBetesCoincees)));
	LabelReste->Repaint();
   }
  if (Affichage&aff_effet)
   {
    LabelEffet->Caption=Format("%2.2d", ARRAYOFCONST((Niv->Effet)));
    LabelEffet->Repaint();
   }

 }

void __fastcall TfrmPlateau::TimerMsgTimer(TObject *Sender)
{
 if (!PosCrtMsg) stChnAff=String::StringOfChar(' ', NBMAXCARAFF)+stMsgCrt+String::StringOfChar(' ', 90);
 StatusBar->Panels->Items[0]->Text=stChnAff.SubString(PosCrtMsg+1, NBMAXCARAFF);
 if (stChnAff.Length()-PosCrtMsg<90) TimerMsg->Enabled=false;
 PosCrtMsg++;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 TimerMsg->Enabled=false;   
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueNouveauNiveauClick(TObject *Sender)
{
 int i;
 if (JeuEnCours||Niv->Lance)
  {
   JeuEnCours=false;
   Niv->Lance=false;
  }
 RubriqueEditeur->Enabled=true;
 RubriqueJeu->Enabled=true;
 RubriqueTesterNiveau->Caption=stTesterNiveau;
 RubriqueInterrompreNiveau->Enabled=false;
 AffichageAutorise=false;
 if (Niv) delete Niv;
 Niv=new niveau;
 AffichageAutorise=true;
 stNomFichierNiveau="";
 stCommentaire="";
 RafraichitTitre(false);
 DrawGrid->Repaint();
 RafraichitParametres(aff_tout);
 frmPrmNiveau->CheckBoxBordure->Checked=false;
 frmPrmNiveau->CheckBoxBordure->Enabled=true;
 frmPrmNiveau->ShowModal();
 if (frmPrmNiveau->CheckBoxBordure->Checked)
  for(i=0; i<NBX; i++)
   {
    Niv->c[i][0].Definit(mur, ouverte, NULL);
    Niv->c[i][NBY-1].Definit(mur, ouverte, NULL);
    if (i<NBY)
     {
      Niv->c[0][i].Definit(mur, ouverte, NULL);
      Niv->c[NBX-1][i].Definit(mur, ouverte, NULL);
     }
   }
 DrawGrid->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPlateau::RubriqueTesterNiveauClick(TObject *Sender)
{
 bool BientotEnCours=(!JeuEnCours)&&(!Niv->Lance);
 if (BientotEnCours)
  {
   if (stNomFichierNiveau=="")
    {
     AfficheMessage("Vous devez enregistrer le niveau avant de le tester.", MB_ICONEXCLAMATION);
     return;
    }
   if (!Niv->c[Niv->x0][Niv->y0].EstFranchissable())
    {
     AfficheMessage("Vous devez laisser le curseur sur une case libre (position initiale du niveau).", MB_ICONEXCLAMATION);
     return;
    }
  }
 RubriqueEditeur->Enabled=!BientotEnCours;
 RubriqueJeu->Enabled=!BientotEnCours;
 if (BientotEnCours) Niv->Cumul=Niv->Score=0L;
 RubriqueTesterNiveau->Caption=BientotEnCours?stArreterNiveau:stTesterNiveau;
 RubriqueInterrompreNiveau->Enabled=BientotEnCours;
 JeuEnCours=BientotEnCours;
 RafraichitTitre(false);
 if (!BientotEnCours) ChargeAutomatiquement();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueInterrompreNiveauClick(
      TObject *Sender)
{
 JeuEnCours=!JeuEnCours;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPlateau::TimerJeuTimer(TObject *Sender)
{
 if (Niv->TourEnCours) return;
 ThreadTour=new TThreadTour(false);
 if (CmdTour) CmdTour = false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPlateau::FormCreate(TObject *Sender)
{
 ChargementAuto=false;
 ThreadTour=NULL;
 Niv=new niveau(10);
 AffichageAutorise=true;
 Registry=new TRegistry;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::FormDestroy(TObject *Sender)
{
 AffichageAutorise=false;
 if (ThreadTour) delete ThreadTour;
 if (Niv) delete Niv;
 delete Registry;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPlateau::RubriquePorteHautClick(TObject *Sender)
{
 Niv->DmdDeclPorte[nord]=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriquePorteDroiteClick(TObject *Sender)
{
 Niv->DmdDeclPorte[est]=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriquePorteBasClick(TObject *Sender)
{
 Niv->DmdDeclPorte[sud]=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriquePorteGaucheClick(TObject *Sender)
{
 Niv->DmdDeclPorte[ouest]=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueNordClick(TObject *Sender)
{
 if ((Niv->y>0)&&(Niv->C(Niv->x,Niv->y,nord).EstFranchissable()))
  {
   DrawGrid->Row=(--(Niv->y));
   if (Niv->c[Niv->x][Niv->y].Type>porte)
    Niv->ActionneDeclencheur(Niv->x, Niv->y);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueEstClick(TObject *Sender)
{
 if ((Niv->x<NBX-1)&&(Niv->C(Niv->x,Niv->y,est).EstFranchissable()))
  {
   DrawGrid->Col=(++(Niv->x));
   if (Niv->c[Niv->x][Niv->y].Type>porte)
    Niv->ActionneDeclencheur(Niv->x, Niv->y);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueSudClick(TObject *Sender)
{
 if ((Niv->y<NBY-1)&&(Niv->C(Niv->x,Niv->y,sud).EstFranchissable()))
  {
   DrawGrid->Row=(++(Niv->y));
   if (Niv->c[Niv->x][Niv->y].Type>porte)
    Niv->ActionneDeclencheur(Niv->x, Niv->y);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueOuestClick(TObject *Sender)
{
 if ((Niv->x>0)&&(Niv->C(Niv->x,Niv->y,ouest).EstFranchissable()))
  {
   DrawGrid->Col=(--(Niv->x));
   if (Niv->c[Niv->x][Niv->y].Type>porte)
    Niv->ActionneDeclencheur(Niv->x, Niv->y);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::DrawGridMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{  // Empêche l'utilisation de la souris lors du jeu
 if (JeuEnCours||Niv->Lance) DrawGrid->Tag=1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueAProposClick(TObject *Sender)
{
 
 if (JeuEnCours) JeuEnCours=false;
 if ((frmAPropos=new TfrmAPropos(this)))
  {
   frmAPropos->ShowModal();
   delete frmAPropos;
  }
 
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::DrawGridKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 //AfficheMessage(ShortCutToText(ShortCut(Key, Shift)), MB_ICONINFORMATION);   
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueRecordsClick(TObject *Sender)
{
 
 if (JeuEnCours) JeuEnCours=false;
 if ((frmRecords=new TfrmRecords(this)))
  {
   frmRecords->TesterNvEntree=false;
   frmRecords->ShowModal();
   delete frmRecords;
   frmRecords=NULL;
  }
 
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueMsgLigneStatutClick(TObject *Sender)
{
 TypeAffMsg=ligne_statut;
 RubriqueMsgLigneStatut->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueMsgBoiteDialogueClick(TObject *Sender)
{
 TypeAffMsg=boite_dialogue;
 RubriqueMsgBoiteDialogue->Checked=true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPlateau::RubriqueRDJetUTLClick(TObject *Sender)
{
 if (JeuEnCours) JeuEnCours=false;
 // v1.7 : aide en HTML
 ShellExecute(Application->Handle,
			  NULL,
			  String(ExtractFilePath(Application->ExeName)+"html/index.html").c_str(),
			  NULL, NULL,
			  SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueCouleurCurseurClick(TObject *Sender)
{
 
 if (JeuEnCours) JeuEnCours=false;
 if (ColorDialog->Execute())
  EcritParametreCouleurCurseur(ColorDialog->Color); // v1.6
 
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueOuvrirNiveauPrecedentClick(
      TObject *Sender)
{
 String stAncNomFichier=stNomFichierNiveau;
 int PosNumNiv=stNomFichierNiveau.Pos(Format("%3.3d", ARRAYOFCONST((Niv->Num))));
 if (!Niv->Num)
  {
   AfficheMessage("Il n'y a pas de niveau précédant le niveau 0.", MB_ICONEXCLAMATION);
   return;
  }
 if (!PosNumNiv)
  {
   AfficheMessage("Le nom de fichier du niveau courant doit être du type <série>.<numéro de niveau>.NLB pour pouvoir utiliser les commandes Ouvrir le niveau précédent.", MB_ICONEXCLAMATION);
   return;
  }
 stNomFichierNiveau=stNomFichierNiveau.SubString(1, PosNumNiv-2)+Format(".%3.3d.", ARRAYOFCONST((Niv->Num-1)))+stExtNLB;
 if (!FileExists(stNomFichierNiveau))
  {
   Application->MessageBox(String("Le fichier \""+stNomFichierNiveau+"\" est introuvable !").c_str(),
                           stCleLeBerger.c_str(),
                           MB_ICONEXCLAMATION);
   stNomFichierNiveau=stAncNomFichier;
   return;
  }
 ChargeAutomatiquement();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueOuvrirNiveauSuivantClick(
      TObject *Sender)
{
 String stAncNomFichier=stNomFichierNiveau;
 int PosNumNiv=stNomFichierNiveau.Pos(Format("%3.3d", ARRAYOFCONST((Niv->Num))));
 if (Niv->Num==999)
  {
   AfficheMessage("Il n'y a pas de niveau suivant le niveau 999.", MB_ICONEXCLAMATION);
   return;
  }
 if (!PosNumNiv)
  {
   AfficheMessage("Le nom de fichier du niveau courant doit être du type <série>.<numéro de niveau>.NLB pour pouvoir utiliser les commandes Ouvrir le niveau suivant.", MB_ICONEXCLAMATION);
   return;
  }
 stNomFichierNiveau=stNomFichierNiveau.SubString(1, PosNumNiv-2)+Format(".%3.3d.", ARRAYOFCONST((Niv->Num+1)))+stExtNLB;
 if ((!FileExists(stNomFichierNiveau))&&
	 (!FileExists(stNomFichierNiveau=ExtractFilePath(ParamStr(0))+ExtractFileName(stNomFichierNiveau))))
  {
   Application->MessageBox(String("Le fichier \""+stNomFichierNiveau+"\" est introuvable !").c_str(),
						   stCleLeBerger.c_str(),
                           MB_ICONEXCLAMATION);
   stNomFichierNiveau=stAncNomFichier;
   return;
  }
 ChargeAutomatiquement();
}
//---------------------------------------------------------------------------


void __fastcall TfrmPlateau::RubriqueInterrompreClick(TObject *Sender)
{
 JeuEnCours=!JeuEnCours;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueNouvelleClick(TObject *Sender)
{
 bool BientotEnCours=(!JeuEnCours)&&(!PartieEnCours);
 if (BientotEnCours)
  {
   if (stNomFichierNiveau=="")
    {
     AfficheMessage("Vous devez avoir ouvert le premier niveau d'une série avant de commencer une nouvelle partie.", MB_ICONEXCLAMATION);
     return;
    }
   if (!Niv->c[Niv->x0][Niv->y0].EstFranchissable())
    {
     AfficheMessage("Impossible de commencer une nouvelle partie : ce niveau est incorrect. Le curseur doit être sur une case libre (position initiale du niveau).", MB_ICONEXCLAMATION);
     return;
    }
  }
 RubriqueNouvelle->Caption=(BientotEnCours)?stArreter:stNouvelle;
 RubriqueOuvrir->Enabled=!BientotEnCours;
 RubriqueChangerSerie->Enabled=!BientotEnCours;
 RubriqueInterrompre->Enabled=BientotEnCours;
 RubriqueJeu->Enabled=!BientotEnCours;
 RubriqueEditeur->Enabled=!BientotEnCours;

 if (BientotEnCours) Niv->Cumul=0L;
 JeuEnCours=BientotEnCours;
 PartieEnCours=!PartieEnCours;
 if (!JeuEnCours)
  {
   RafraichitTitre(false);
   ChargePremierNiveau();
  }
}

void TfrmPlateau::ChargeAutomatiquement()
 {
  ChargementAuto=true;
  if (Mode==jeu) RubriqueOuvrirNiveau->Enabled=true;
  RubriqueOuvrirNiveau->Click();
  if (Mode==jeu) RubriqueOuvrirNiveau->Enabled=false;
  ChargementAuto=false;
 }

void TfrmPlateau::ChangeSerie()
 {
  if (Mode==jeu) RubriqueOuvrirNiveau->Enabled=true;
  Charge1erNiveau=true;
  RubriqueOuvrirNiveau->Click();
  Charge1erNiveau=false;
  if (Mode==jeu) RubriqueOuvrirNiveau->Enabled=false;
 }

//---------------------------------------------------------------------------
bool TfrmPlateau::ChargePremierNiveau()
 {
  int PosNumNiv=stNomFichierNiveau.Pos(Format("%3.3d", ARRAYOFCONST((Niv->Num))));
  // Si niveau chargé, alors on prend le premier de sa série sinon on prend le premier de la série "original"
  NumIdPartie=0L;
  stNomJoueur=stVide;
  if (!PosNumNiv)
   stNomFichierNiveau=ExtractFilePath(ParamStr(0))+"débutant.000.nlb";
  else
   stNomFichierNiveau=stNomFichierNiveau.SubString(1, PosNumNiv-2)+".000."+stExtNLB;

  if (FileExists(stNomFichierNiveau)) // Si le premier niveau existe
   ChargeAutomatiquement(); // On l'ouvre automatiquement
  else // Sinon demande à en choisir un
   ChangeSerie();

  if (stNomSerieNiveau==stVide) return false; // Echec au chargement

  if ((!Niv)||(Niv->Num)) // Même après avoir chargé un niveau .000.NLB on regarde si c'est le n°1.
   {
    AfficheMessage("Le premier niveau doit avoir le numéro 0.", MB_ICONEXCLAMATION);
    return false;
   }
  return true;
 }

void __fastcall TfrmPlateau::RubriqueOuvrirClick(TObject *Sender)
{
 if ((frmParties->ShowModal()!=mrOk)||
     (frmParties->ComboBoxNom->Text.IsEmpty())||
     (!frmParties->StringGridParties->Row)||
     (frmParties->StringGridParties->Cells[0][frmParties->StringGridParties->Row].IsEmpty()))
  return;

 if (!frmParties->ChargeInfosPartie(frmParties->ComboBoxNom->Text,
                                    frmParties->StringGridParties->Cells[0][frmParties->StringGridParties->Row]))
  {
   AfficheMessage("Impossible d'ouvrir les informations de la partie demandée !", MB_ICONHAND);
   return;
  }
 RubriqueNouvelle->Caption=stArreter;
 RubriqueOuvrir->Enabled=false;
 RubriqueChangerSerie->Enabled=false;
 RubriqueInterrompre->Caption=stContinuer;
 RubriqueInterrompre->Enabled=true;
 RubriqueJeu->Enabled=false;
 RubriqueEditeur->Enabled=false;
 PartieEnCours=true;
 ChargementAuto=true;
 if (Mode==jeu) RubriqueOuvrirNiveauSuivant->Enabled=true;
 RubriqueOuvrirNiveauSuivant->Click();
 if (Mode==jeu) RubriqueOuvrirNiveauSuivant->Enabled=false;
 ChargementAuto=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriquePartiesSauvegardeesClick(
      TObject *Sender)
{

 if (JeuEnCours) JeuEnCours=false;
 frmParties->ShowModal();

}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::RubriqueChangerSerieClick(TObject *Sender)
{
 ChangeSerie();
 ChargePremierNiveau();
}
//---------------------------------------------------------------------------
void TfrmPlateau::RafraichitTitre(bool JeuEnPause)
 {
  if (stCommentaire.IsEmpty())
   Caption=stTitre[!JeuEnPause];
  else
   Caption=stTitre[!JeuEnPause]+" - "+stCommentaire;
 }

void __fastcall TfrmPlateau::RubriqueCommandesClick(TObject *Sender)
{
 if ((frmCommandes=new TfrmCommandes(this)))
  {
   frmCommandes->ShowModal();
   frmCommandes->Release();
   frmCommandes=NULL;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::DrawGridKeyPress(TObject *Sender, char &Key)
{
 // Merci Microsoft de ne pas pouvoir mettre
 // de raccourcis sur le Pavé Numérique !
 if ((DrawGrid->PopupMenu!=PopupMenuJeu)||
     (!PopupMenuJeu->Tag)||
     (PopupMenuJeu->Tag==2)) return;
 if (IdxComm[DIR][PopupMenuJeu->Tag]==2)
  switch(Key)
   {
    case '8': RubriqueNord->Click(); break;
    case '6': RubriqueEst->Click(); break;
    case '2': RubriqueSud->Click(); break;
    case '4': RubriqueOuest->Click(); break;
   }
  else
   switch(Key)
   {
    case '8': RubriquePorteHaut->Click(); break;
    case '6': RubriquePorteDroite->Click(); break;
    case '2': RubriquePorteBas->Click(); break;
    case '4': RubriquePorteGauche->Click(); break;
   }
}
//---------------------------------------------------------------------------
void TfrmPlateau::LitParametres() // v1.6
 {
  // v1.7 : le fichier ini n'est plus là où se trouve l'exécutable et on ne reprend pas le nom de l'exécutable
  TIniFile *IniFile=new TIniFile(stRepLocalAppData()+stFichierIniLbrgw);
  try
   {
	InitialiseCommandes(IniFile->ReadInteger(stSectionParametres, stEntreeCommandes, 0));
	VirtualImageList->BlendColor=(TColor)IniFile->ReadInteger(stSectionParametres, stEntreeCouleurCurseur, (int)clFuchsia);
   }
  __finally
   {
	delete IniFile;
   }
 }
//---------------------------------------------------------------------------
void TfrmPlateau::EcritParametreCommandes(const int Commandes) // v1.6
 {
  // v1.7 : le fichier ini n'est plus là où se trouve l'exécutable et on ne reprend pas le nom de l'exécutable
  TIniFile *IniFile=new TIniFile(stRepLocalAppData()+stFichierIniLbrgw);
  try
   {
	IniFile->WriteInteger(stSectionParametres, stEntreeCommandes, Commandes);
	InitialiseCommandes(Commandes);
   }
  __finally
   {
	delete IniFile;
   }
 }
//---------------------------------------------------------------------------
void TfrmPlateau::InitialiseCommandes(const int CombinaisonCommandes) // v1.6
{
 int CommDir=IdxComm[DIR][CombinaisonCommandes],
	 CommPrt=IdxComm[PRT][CombinaisonCommandes];

 frmPlateau->PopupMenuJeu->Tag=CombinaisonCommandes;

 frmPlateau->RubriqueNord->ShortCut=TextToShortCut(stRaccourciClavier[CommDir][HAUT]);
 frmPlateau->RubriqueEst->ShortCut=TextToShortCut(stRaccourciClavier[CommDir][DROITE]);
 frmPlateau->RubriqueSud->ShortCut=TextToShortCut(stRaccourciClavier[CommDir][BAS]);
 frmPlateau->RubriqueOuest->ShortCut=TextToShortCut(stRaccourciClavier[CommDir][GAUCHE]);

 frmPlateau->RubriquePorteHaut->ShortCut=TextToShortCut(stRaccourciClavier[CommPrt][HAUT]);
 frmPlateau->RubriquePorteDroite->ShortCut=TextToShortCut(stRaccourciClavier[CommPrt][DROITE]);
 frmPlateau->RubriquePorteBas->ShortCut=TextToShortCut(stRaccourciClavier[CommPrt][BAS]);
 frmPlateau->RubriquePorteGauche->ShortCut=TextToShortCut(stRaccourciClavier[CommPrt][GAUCHE]);
}
//---------------------------------------------------------------------------
void TfrmPlateau::EcritParametreCouleurCurseur(const TColor CouleurCurseur) // v1.6
 {
  // v1.7 : le fichier ini n'est plus là où se trouve l'exécutable et on ne reprend pas le nom de l'exécutable
  TIniFile *IniFile=new TIniFile(stRepLocalAppData()+stFichierIniLbrgw);
  try
   {
    IniFile->WriteInteger(stSectionParametres, stEntreeCouleurCurseur, CouleurCurseur);
    VirtualImageList->BlendColor=CouleurCurseur;
   }
  __finally
   {
    delete IniFile;
   }
 }

void __fastcall TfrmPlateau::MenuItemDiplomeClick(TObject *Sender)
{ // v1.7 : invisible uniquement pour test
 if ((frmDiplome=new TfrmDiplome(Application)))
  {
   frmDiplome->ShowModal();
   delete frmDiplome;
   frmDiplome=NULL;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
 if ((Key>=37)&&(Key<=40)) // Touches fléchées
  {
   if (CmdTour) // v1.7 : on limite les commandes à une par tour de jeu
	 Key = 0;
   else
	 CmdTour = true;
  }
 // StatusBar->Panels->Items[0]->Text = "FormKeyDown: " + IntToStr(Key);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPlateau::FormKeyPress(TObject *Sender, System::WideChar &Key)

{
   switch(Key)
	{
	 case '2': case '4': case '6': case '8': // Directions sur pavé numérique
	 case 'z': case 'w': case 'q': case 's': // Directions sur z/s/w/q
	 case 'Z': case 'W': case 'Q': case 'S': // Directions sur Z/S/W/Q
		if (CmdTour) // v1.7 : on limite les commandes à une par tour de jeu
		  Key = '\x0';
		else
		  CmdTour = true;
	 default :
		break;
	}
 // StatusBar->Panels->Items[0]->Text = "FormKeyPress: " + Key;
}
//---------------------------------------------------------------------------

