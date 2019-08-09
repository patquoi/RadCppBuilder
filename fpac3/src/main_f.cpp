//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "main_f.h"
#include "base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
top10 Top10;
TFormMain *FormMain;
msg_statut MsgStatut;
jeu Jeu;
//---------------------------------------------------------------------------
const zone_affichage ZoneAff[NBZONESAFFICHAGE] = {{0,4},{6,14},{16,18},{20,29},{31,34}};
const AnsiString asEnTeteTop10 = "POS ~JOUEUR~ ~NIV;DIFF~ SCORE";
const char Etoile[4]="xk*";
//---------------------------------------------------------------------------
// Classe msg_statut
//---------------------------------------------------------------------------
bool msg_statut::MessageEstEnCours()
 {
  return asMsg.Length()&&(MsgStatut.Deroulement/2<=FormMain->DrawGridMsg->ColCount);
 }
//---------------------------------------------------------------------------
void msg_statut::DerouleMessage()
 {
  if (MsgStatut.Deroulement/2<=FormMain->DrawGridMsg->ColCount)
   Deroulement++;
  else
   if (asResteMsg.Length())
    {
     asMsgPrmLigne=asMsg;
     DebutMsgPrmLigne=DebutMsg;
     asMsg=asResteMsg;
     asResteMsg="";
     DebutMsg=(FormMain->DrawGridMsg->ColCount-asMsg.Length())/2;
     Deroulement=DEBMSGSANSEFFACER;
     Ligne++;
    }
   else
    FormMain->TimerMsg->Interval=VITESSEMSG;
  if ((Deroulement==DEBMSGSANSEFFACER)&&
      ((NbLignes<2)||(!Ligne))&&
      asMsg.Length()) // On efface pas si l'on souhaite le faire avec un pacman (message vide) !!!
   FormMain->RedessineCaracteres();
  else
   {
    if (Deroulement)
     FormMain->RedessineCaractere(Deroulement/2-1, Ligne);
    if (Deroulement/2<FormMain->DrawGridMsg->ColCount)
     FormMain->RedessineCaractere(Deroulement/2, Ligne);
   }
 }
//---------------------------------------------------------------------------
void msg_statut::Affiche(const int Ligne, const AnsiString asMsg)
 {
  int PosRet=asMsg.AnsiPos("\n");
  Deroulement=DEBMSGAPRESEFFACER;
  this->Ligne=Ligne;
  if (PosRet)
   {
    this->asMsg=asMsg.SubString(1, PosRet-1);
    this->asResteMsg=asMsg.SubString(PosRet+1, asMsg.Length()-PosRet);
    this->asMsgPrmLigne="";
    this->NbLignes=2;
   }
  else
   {
    this->asMsg=asMsg;
    this->asResteMsg="";
    this->asMsgPrmLigne="";
    this->NbLignes=1;
   }
  this->DebutMsg=(FormMain->DrawGridMsg->ColCount-MsgStatut.asMsg.Length())/2;
 }
//---------------------------------------------------------------------------
msg_statut::~msg_statut()
 {
 }
//---------------------------------------------------------------------------
// Classe TFormMain
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner)
{ // On force en haut à gauche car si changement de dimensions, évite les débordements à droite et en bas
 SansDemo=false;
 Top=0; Left=0;
// DrawGridJeu->DoubleBuffered=true; // v1.2.1 : ça rafraîchissait toutes les cellules !
// DrawGridMsg->DoubleBuffered=true; // v1.2.1 : ça rafraîchissait toutes les cellules !
 ChangeAccesParametres(ACTIVER);
 ActionParamDimensions48x30->Execute();// Pour redimensionner
 DeroulementDemarrage=DEBMSGAPRESEFFACER;
 DeroulementTop10=0;
 Top10.LitParametres();
 Bienvenue();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::EffaceMessage()
 {
  MsgStatut.asMsg="";
  MsgStatut.asMsgPrmLigne="";
  MsgStatut.asResteMsg="";
  RedessineCaracteres();
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::ChangeAccesParametres(bool Activation)
 {
  for(int i=0; i<ActionList->ActionCount; i++)
   if (((TAction*)ActionList->Actions[i])->Category=="Paramètres")
    ((TAction*)ActionList->Actions[i])->Enabled=Activation;
  ActionInfosTop10->Enabled=Activation; // Consultation du top 10 désactivée en cours de partie (v1.1)
  if (Activation)
   {
    ActionParamDimensions64x40->Enabled=(Screen->Width>=1024);
    ActionParamDimensions80x50->Enabled=(Screen->Width>=1280);
    ActionParamDimensions96x60->Enabled=(Screen->Width>=1536);
    ActionParamDimensions112x70->Enabled=(Screen->Width>=1792);
   }
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::ArreteOuDemarreJeu(bool DemarreJeu)
 {
  if (DemarreJeu)
   TimerDemo->Enabled=false;
  else
   TimerJeu->Enabled=false;
  FJeuEnCours=DemarreJeu;
  ChangeAccesParametres(!DemarreJeu);
  if (DemarreJeu)
   {
    Jeu.CreeLaby();
    RedessineCases();
    EffaceMessage();
	AfficheInfosJeuDepart();
    TimerJeu->Enabled=true;
    TimerJeu->Tag=0;
   }
  else
   {
    if (!SansDemo)
     {
      RedessineInfosJeu(); // On efface les infos de jeu
      Bienvenue();
     }
   }
  if ((!DemarreJeu)&&(!SansDemo))
   {
	TimerDemo->Enabled=true;
	TimerDemo->Tag=0;
   }
 };
//---------------------------------------------------------------------------
void __fastcall TFormMain::DrawGridJeuDrawCell(TObject *Sender, int ACol,
	  int ARow, TRect &Rect, TGridDrawState State)
{
 if (Jeu.c)
  {
   int IdElement=IDMUR,
	   IdElementPacMan=IDVIDE,
	   IdElementFantome[NBMAXFANTOMES]={IDVIDE,IDVIDE,IDVIDE,IDVIDE,IDVIDE,IDVIDE,IDVIDE,IDVIDE,IDVIDE,IDVIDE};
   bool Fantome1erPlan[NBMAXFANTOMES]={false,false,false,false,false,false,false,false,false,false},
		PacManAMange=Jeu.PacMan.AMange&&(ACol==Jeu.PacMan.x)&&(ARow==Jeu.PacMan.y);
   // vCX : on affiche un fond noir d'abord
   VirtualImageListJeu->Draw(DrawGridJeu->Canvas, Rect.Left, Rect.Top, IDFONDNOIR);
   // 0. On place le bonus s'il y a
   if ((ACol==Jeu.Bonus.x)&&(ARow==Jeu.Bonus.y)) // vCX : TVirtualImageList au lieu de ImageList (HDPI)
	VirtualImageListJeu->Draw(DrawGridJeu->Canvas, Rect.Left, Rect.Top, IDBONUS+COULEURBONUS(0)+COULEURBONUS(1)+COULEURBONUS(2)+COULEURBONUS(3));
   // 1. On place le fond (pilules, pacgum, doubles flèches)
   if ((ARow==Jeu.NbY/2)&&((!ACol)||(ACol==_XMAX))) IdElement=IDGAUCHEDROITE; else
   if ((ACol==Jeu.NbX/2)&&((!ARow)||(ARow==_YMAX))) IdElement=IDHAUTBAS; else
   switch(Jeu.c[ACol][ARow])
    {
     case mur:    if (Jeu.Table[ACol][ARow]<SANS)
                   IdElement=IDPORTES+Jeu.Porte[Jeu.Table[ACol][ARow]].Pos;
                  else
                   IdElement=IDMUR;
                  break;
     case pilule: IdElement=(PacManAMange?IDVIDE:IDPILULE);
                  break;
     case pacgum: IdElement=(PacManAMange?IDVIDE:IDPACGUM);
                  break;
     case vide:   if (Jeu.Table[ACol][ARow]<SANS)
                   IdElement=IDPORTES+Jeu.Porte[Jeu.Table[ACol][ARow]].Pos;
                  else
                   IdElement=IDVIDE;
                  break;
	}
   // vCX : TVirtualImageList au lieu de ImageList (HDPI)
   VirtualImageListJeu->Draw(DrawGridJeu->Canvas, Rect.Left, Rect.Top, IdElement);

   // 2. On place les héros du jeu (fantômes et pacman)

   // 2a. Pacman
   if (Jeu.PacMan.d==indefinie) // Mort
    {
     if ((ACol==Jeu.PacMan.x)&&(ARow==Jeu.PacMan.y))
      {
       int dt=Jeu.Temps-Jeu.PacMan.TempsMort;
       if (Jeu.Temps-Jeu.PacMan.TempsMort<=TPSAVTREAPPARITION)
        IdElementPacMan=IDPCMVIEMORT+((dt<2*NBANIMATIONSMORT)?dt/2:NBANIMATIONSMORT-1);
       else
        IdElementPacMan=IDVIDE;
      }
    }
   else
    {
     bool PacManSeDeplace=_DEPLACABLE(Jeu.PacMan.x,Jeu.PacMan.y,Jeu.PacMan.d);
     if ((ACol==Jeu.PacMan.x)&&(ARow==Jeu.PacMan.y))
      if (PacManSeDeplace)
       IdElementPacMan=(!Jeu.ACheval)*(IDPCMENTIER+PacManAMange)+ // PacMan entier
                         Jeu.ACheval *(IDPCMMOITIE+ARRIERE)+ // Arrière de PacMan
					   2*Jeu.PacMan.d;           // Direction
      else
       IdElementPacMan=IDPCMENTIER+Jeu.PacMan.AMange+2*Jeu.PacMan.d;
     else
      if (Jeu.ACheval&&PacManSeDeplace&&
          (ACol==Jeu.PacMan.x+dx[Jeu.PacMan.d])&&
          (ARow==Jeu.PacMan.y+dy[Jeu.PacMan.d]))
       IdElementPacMan=IDPCMMOITIE+AVANT+2*Jeu.PacMan.d;
	 if (PacManAMange&&(!Jeu.ACheval))
      Jeu.PacMan.AMange=false;
    }
   // 2b. Fantôme(s)
   for(int i=0; i<Jeu.NbFantomes; i++)
	 if ((ACol==Jeu.Fantome[i].x)&&(ARow==Jeu.Fantome[i].y))
	  {
	   if (Jeu.Fantome[i].Etat==mange)
		IdElementFantome[i]=(!Jeu.ACheval)*IDYEUXENTIERS+ // Yeux en entier
							  Jeu.ACheval *(IDYEUXARRIERE)+ // Arrière de fantôme
							Jeu.Fantome[i].d;           // Direction
	   else
		IdElementFantome[i]=(!Jeu.ACheval)*IDFTMENTIER+ // Fantôme entier
							  Jeu.ACheval *(IDFTMARRIERE)+ // Arrière de fantôme
							NBDIRECTIONS*COULEURFANTOME(i)+ // Couleur
							Jeu.Fantome[i].d;           // Direction
	   if ((Jeu.Fantome[i].Etat==en_chasse)||(Jeu.Fantome[i].Etat==mange))
		Fantome1erPlan[i]=true;
	  }
	 else
	  if (Jeu.ACheval&&
		  (ACol==Jeu.Fantome[i].x+dx[Jeu.Fantome[i].d])&&
		  (ARow==Jeu.Fantome[i].y+dy[Jeu.Fantome[i].d]))
	   {
		if (Jeu.Fantome[i].Etat==mange)
		 IdElementFantome[i]=IDYEUXAVANT+ // Avant des yeux
							 Jeu.Fantome[i].d; // Direction
		else
		 IdElementFantome[i]=IDFTMAVANT+ // Avant du fantôme
							 NBDIRECTIONS*COULEURFANTOME(i)+ // Couleur
							 Jeu.Fantome[i].d; // Direction
	   }

   // Début vCX : TVirtualImageList au lieu de ImageList (HDPI)

   // 2c. On affiche dans l'ordre les héros suivant qui domine qui
   for(int i=0; i<Jeu.NbFantomes; i++)
	if ((IdElementFantome[i]!=IDVIDE)&&(!Fantome1erPlan[i]))
	 VirtualImageListJeu->Draw(DrawGridJeu->Canvas, Rect.Left, Rect.Top, IdElementFantome[i]); // vCX
   if (IdElementPacMan!=IDVIDE) // vCX : bug, IDVIDE affiche un carré noir !
    VirtualImageListJeu->Draw(DrawGridJeu->Canvas, Rect.Left, Rect.Top, IdElementPacMan); // vCX
   for(int i=0; i<Jeu.NbFantomes; i++)
	if (Fantome1erPlan[i]&&(IdElementFantome[i]!=IDVIDE))
	 VirtualImageListJeu->Draw(DrawGridJeu->Canvas, Rect.Left, Rect.Top, IdElementFantome[i]); // vCX

   // 3. Primes
   for(int i=Jeu.Primes.Courante; i!=Jeu.Primes.Nouvelle; i=(i+1)%NBMAXPRIMES)
	{
	 if ((Jeu.Primes.Delai[i]%2)&&(Jeu.Primes.x[i]==ACol)&&(Jeu.Primes.y[i]==ARow))
	  VirtualImageListJeu->Draw(DrawGridJeu->Canvas, Rect.Left, Rect.Top, IDPRIMES+Jeu.Primes.Valeur[i]/PRIMEFANTOME); // vCX
	}

  }
 else
  {
   if (TimerTop10->Enabled)
	{
	 // vCX : on affiche un fond noir autour du top 10
	 VirtualImageListJeu->Draw(DrawGridJeu->Canvas, Rect.Left, Rect.Top, IDFONDNOIR);
	 if ((ACol>=Top10.Col0)&&(ACol<Top10.Col0+Top10.l)&&
		 (ARow>=Top10.Row0)&&(ARow<Top10.Row0+Top10.h))
	  AfficheTop10(Rect, ACol, ARow);
	}
   else
    VirtualImageListJeu->Draw(DrawGridJeu->Canvas, Rect.Left, Rect.Top, IDMUR); // vCX
  }
  // Fin vCX : TVirtualImageList au lieu de ImageList (HDPI)
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RedessineCases()
 {
  TRect CellWRectMin=DrawGridJeu->CellRect(0, 0),
		CellWRectMax=DrawGridJeu->CellRect(DrawGridJeu->ColCount-1, DrawGridJeu->RowCount-1);
  RECT CellRect={CellWRectMin.Left, CellWRectMin.Top, CellWRectMax.Right, CellWRectMax.Bottom};
  InvalidateRect(DrawGridJeu->Handle, &CellRect, true);
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::RedessineCase(int x, int y)
 {
  TRect CellWRect=DrawGridJeu->CellRect(x, y);
  RECT CellRect={CellWRect.Left, CellWRect.Top, CellWRect.Right, CellWRect.Bottom};
  InvalidateRect(DrawGridJeu->Handle, &CellRect, true);
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::DrawGridMsgDrawCell(TObject *Sender,
	  int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
 PlaceCaractere(DrawGridMsg, Rect, 'f');
 if (MsgStatut.Deroulement==DEBMSGSANSEFFACER) return; // Efface Caracteres
 if (ARow==MsgStatut.Ligne)
  {
   if (ACol<=MsgStatut.Deroulement/2)
	{
	 // Début vCX : TVirtualImageList au lieu de ImageList (HDPI)
	 switch(ACol-MsgStatut.Deroulement/2)
	  {
	   case  0: if (MsgStatut.Deroulement%2)
				 {
				  VirtualImageListJeu->Draw(DrawGridMsg->Canvas, // vCX
											Rect.Left, Rect.Top,
											IDMSGPACENTIER+ // PacMan bouche fermée
											((ACol>=MsgStatut.DebutMsg)&& // On lui faire ouvrir la bouche s'il y a du caractère à imprimer
											 (ACol<MsgStatut.DebutMsg+MsgStatut.asMsg.Length()))*
											(!((MsgStatut.Deroulement-3)%4)));
				  break;
				 }
	   case -1: if (MsgStatut.Deroulement%2)
				 {
				  if ((ACol>=MsgStatut.DebutMsg)&&
					  (ACol<MsgStatut.DebutMsg+MsgStatut.asMsg.Length()))
				   PlaceCaractere(DrawGridMsg, Rect, MsgStatut.asMsg[1+ACol-MsgStatut.DebutMsg]);
				 }
				else
				 VirtualImageListJeu->Draw(DrawGridMsg->Canvas, Rect.Left, Rect.Top, IDMSGPACMOITIE+ACol-MsgStatut.Deroulement/2); // vCX
				break;
	   default: if ((ACol>=MsgStatut.DebutMsg)&&
					(ACol<MsgStatut.DebutMsg+MsgStatut.asMsg.Length()))
				 PlaceCaractere(DrawGridMsg, Rect, MsgStatut.asMsg[1+ACol-MsgStatut.DebutMsg]);
				break;
	  }
	 // Fin vCX : TVirtualImageList au lieu de ImageList (HDPI)
	}
  }
 else
  {
   if ((MsgStatut.Ligne==1)&&
       (MsgStatut.NbLignes==2)&&
       (MsgStatut.asMsgPrmLigne.Length())&&
       (ACol>=MsgStatut.DebutMsgPrmLigne)&&
       (ACol-MsgStatut.DebutMsgPrmLigne<MsgStatut.asMsgPrmLigne.Length()))
    PlaceCaractere(DrawGridMsg, Rect, MsgStatut.asMsgPrmLigne[1+ACol-MsgStatut.DebutMsgPrmLigne]);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RedessineCaracteres()
 {
  TRect CellWRectMin=DrawGridMsg->CellRect(0, 0),
        CellWRectMax=DrawGridMsg->CellRect(DrawGridMsg->ColCount-1, DrawGridMsg->RowCount-1);
  RECT CellRect={CellWRectMin.Left, CellWRectMin.Top, CellWRectMax.Right, CellWRectMax.Bottom};
  InvalidateRect(DrawGridMsg->Handle, &CellRect, true);
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::RedessineCaractere(int x, int y)
 {
  TRect CellWRect=DrawGridMsg->CellRect(x, y);
  RECT CellRect={CellWRect.Left, CellWRect.Top, CellWRect.Right, CellWRect.Bottom};
  InvalidateRect(DrawGridMsg->Handle, &CellRect, true);
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::PlaceCaractere(TDrawGrid *DrawGrid, TRect &Rect, const char Caractere)
{
 // Début vCX : TVirtualImageList au lieu de ImageList (HDPI)
 VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGFONDNOIR); // vCX : on met un fond noir d'abord
 if (DrawGrid==DrawGridMsg)
   VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGFOND);
 switch(Caractere)
  {
   case 'f': // vCX : on fait rien car déjà fait en début !
			 //VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGFOND);
			 break; // Fond
   case ' ': // vCX : on fait rien car IDMSGESPACE affiche un carré noir !
			 //VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGESPACE);
			 break;
   case '=': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGMUR);
			 break;
   case '@': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGVIE);
			 break; // PacMan!
   case '.': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGPACGUM);
			 break; // Pacgum!
   case '#': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGFANTOME);
			 break; // Fantôme!
   case 'm': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGTOUCHEMAJ);
			 break; // Touche Maj
   case 'c': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGTOUCHECTRL);
			 break; // Touche Ctrl
   case 'e': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGTOUCHEECHAP);
			 break; // Touche Echap
   case '(': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGTOUCHEF1);
			 break; // Touche F1
   case ')': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGTOUCHEF12);
			 break; // Touche F12
   case '[': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGTOUCHEF3);
			 break; // Touche F3
   case ']': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGTOUCHEF6);
			 break; // Touche F6
   case '+': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGFLECHES);
			 break; // Touches fléchées
   case '~': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGTILDE);
			 break; // Tilde
   case ':': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGDEUXPOINTS);
			 break; // Caractère ':'
   case '¼': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGUNQUART);
			 break; // Caractère '¼'
   case ';': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGPILULE);
			 break; // Pilule
   case '\'':VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGAPOSTROPHE);
			 break; // Apostrophe
   case '%': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGPOURCENT);
			 break; // '%'
   case 'x': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGETOILES);
			 break; // Etoile éteinte
   case 'k': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGETOILES+1);
			 break; // Etoile double-face
   case '*': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGETOILES+2);
			 break; // Etoile allumée
   case '€': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGBONUS);
			 break; // Pique
   case '£': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGBONUS+1);
			 break; // Coeur
   case '$': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGBONUS+2);
			 break; // Trèfle
   case '¥': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGBONUS+3);
			 break; // Carreau
   case 'p': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGPARAMPORTES);
			 break; // Paramètre Porte
   case '>': VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGFLECHEDROITE);
			 break; // ->
   default:  if ((Caractere>='A')&&(Caractere<='Z'))
			  VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGLETTRE+(int)(Caractere-'A'));
			 else if ((Caractere>='0')&&(Caractere<='9'))
			  VirtualImageListMsg->Draw(DrawGrid->Canvas, Rect.Left, Rect.Top, IDMSGCHIFFRE+(int)(Caractere-'0'));
			 break;
  }
 // Fin vCX : TVirtualImageList au lieu de ImageList (HDPI)
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerMsgTimer(TObject *Sender)
{
 Randomize();
 MsgStatut.DerouleMessage();
 if ((DeroulementDemarrage>DEBMSGAPRESEFFACER)&&
	 (DeroulementDemarrage<=DrawGridPts->ColCount*2))
  DerouleAffichageInfosJeu();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionDimensionsExecute(TObject *Sender)
{
 // Changement de dimensions : Tag=0,1,2 de la plus petite à la plus grande
 const int ColDim[NBTAILLES]={48,64,80,96,112},
		   RowDim[NBTAILLES]={30,40,50,60,70};
 const AnsiString asMsg[NBTAILLES]={"TAILLE 48x30 ACTIVEE", "TAILLE 64x40 ACTIVEE", "TAILLE 80x50 ACTIVEE", "TAILLE 96x60 ACTIVEE", "TAILLE 112x70 ACTIVEE"};
 int HeightDiff=ClientHeight-DrawGridJeu->Height;
 TAction *Action=(TAction*)Sender;
 Action->Checked=true;
 // 1. On change le nombre de lignes & colonnes de la grille
 DrawGridMsg->ColCount=ColDim[Action->Tag];
 DrawGridJeu->ColCount=ColDim[Action->Tag];
 DrawGridJeu->RowCount=RowDim[Action->Tag];
 // 2. On redimensionne la fenêtre
 ClientWidth=DrawGridJeu->ColCount*DrawGridJeu->DefaultColWidth;
 ClientHeight=DrawGridJeu->RowCount*DrawGridJeu->DefaultRowHeight+HeightDiff;
 Jeu.Detruit();
 RedessineCases();
 MsgStatut.Affiche(1, asMsg[Action->Tag]);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionAgressiviteExecute(TObject *Sender)
{
 const int Agressivite[NBAGRESSIVITES]={25,33,50};
 const AnsiString asMsg[NBAGRESSIVITES]={"AGRESSIVITE FIXEE A 25%", "AGRESSIVITE FIXEE A 33%", "AGRESSIVITE FIXEE A 50%"};
 TAction *Action=(TAction*)Sender;
 Action->Checked=true;
 Jeu.Agressivite=Agressivite[Action->Tag];
 MsgStatut.Affiche(1, asMsg[Action->Tag]);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Action1PGxxxPExecute(TObject *Sender)
{
 const int RapportPilulesPacgums[NBRAPPORTSPLPG]={50,100,150};
 const AnsiString asMsg[NBRAPPORTSPLPG]={"1 PILULE POUR 50 PACGUMS ACTIVEE", "1 PILULE POUR 100 PACGUMS ACTIVEE", "1 PILULE POUR 150 PACGUMS ACTIVEE"};
 TAction *Action=(TAction*)Sender;
 Action->Checked=true;
 Jeu.FrqPil=RapportPilulesPacgums[Action->Tag];
 MsgStatut.Affiche(1, asMsg[Action->Tag]);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionxxCasesExecute(TObject *Sender)
{
 const int DureeVulnerabiliteFantomes[NBVULNERABILITES]={100,50,25};
 const AnsiString asMsg[NBVULNERABILITES]={"VULNERABILITE 100 CASES ACTIVEE", "VULNERABILITE 50 CASES ACTIVEE", "VULNERABILITE 25 CASES ACTIVEE"};
 TAction *Action=(TAction*)Sender;
 Action->Checked=true;
 Jeu.Vulnerabilite=2*DureeVulnerabiliteFantomes[Action->Tag];
 MsgStatut.Affiche(1, asMsg[Action->Tag]);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionDepartFantomesExecute(TObject *Sender)
{
 const int FantomesDepart[NBDEPARTSFANTOMES]={3,4,5,6};
 const AnsiString asMsg[NBDEPARTSFANTOMES]={"DEPART AVEC 3 # ACTIVE", "DEPART AVEC 4 # ACTIVE", "DEPART AVEC 5 # ACTIVE", "DEPART AVEC 6 # ACTIVE"};
 TAction *Action=(TAction*)Sender;
 Action->Checked=true;
 Jeu.FantomesDepart=FantomesDepart[Action->Tag];
 MsgStatut.Affiche(1, asMsg[Action->Tag]);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionParamPortesNPour2LignesExecute(
      TObject *Sender)
{
 const int PortesParCase[NBRAPPORTSPORTESCASES]={150,75,50};
 const AnsiString asMsg[NBRAPPORTSPORTESCASES]={"RAPPORT 1 PORTE TOUTES LES 150 CASES ACTIVE", "RAPPORT 1 PORTE TOUTES LES 75 CASES ACTIVE", "RAPPORT 1 PORTE TOUTES LES 50 CASES ACTIVE"};
 TAction *Action=(TAction*)Sender;
 Action->Checked=true;
 Jeu.PortesParCase=PortesParCase[Action->Tag];
 MsgStatut.Affiche(1, asMsg[Action->Tag]);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionPartieJouerExecute(TObject *Sender)
{
 JeuEnCours=true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Bienvenue()
{
 MsgStatut.Affiche(0, "\
@@@@@@@@ BIENVENUE DANS FOUQUET'S PAC 3 ########\n\
JEU:cJ REGLE:mcR TOUCHES:mcC LEGENDE:mcL TOP:mcT");
 TimerDemo->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionInfosAProposExecute(TObject *Sender)
{
#ifdef _WIN64
 MsgStatut.Affiche(0, "\
== FP#@3.VERSION 1.3.0 = GPL2 @ 2008.2019 ==\n\
== PAR PATRICE FOUQUET = FP#@3~ @ 64 BITS ==");
#else
 MsgStatut.Affiche(0, "\
== FP#@3.VERSION 1.3.0 = GPL2 @ 2008.2019 ==\n\
== PAR PATRICE FOUQUET = FP#@3~ @ 32 BITS ==");
#endif
 TimerDemo->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionInfosCommandesExecute(TObject *Sender)
{
 MsgStatut.Affiche(0, "\
PARAMETRES:(~) SAUF~ 3#~6#:m[~m] . 1p~3p:c(~c[\n\
JEU:cJ ACCEL;DEFIL;:e @:+ PAUSE:P AIDE:mcC~L~R") ;
 TimerDemo->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionInfosRegleDuJeuExecute(TObject *Sender)
{
 MsgStatut.Affiche(0, "\
@ DOIT RECOLTER TOUS LES ; PAR ¼ D'ECRAN\n\
@ DOIT EVITER LES # SAUF QUAND @ MANGE .");
 TimerDemo->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionInfosLegendeExecute(TObject *Sender)
{
 MsgStatut.Affiche(0, "\
01234 @@@@    99%         xxxxk*****        €£$¥\n\
SCORE VIES ATTIRANCE NIVEAU DE DIFFICULTE  BONUS");
 TimerDemo->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormKeyPress(TObject *Sender, char &Key)
{
 switch(Key)
  {
   case 'p':
   case 'P':    if (JeuEnCours&&TimerJeu->Enabled)
				  {
				   TimerJeu->Enabled=false;
				   MsgStatut.Affiche(1, "R:REPRENDRE . A:ABANDONNER . Q:QUITTER");
				  }
				break;
   case '\x1B': // Echap
				if (MsgStatut.MessageEnCours)
				 TimerMsg->Interval=ACHEVEMSG;
				if (TimerTop10->Enabled)
				 TimerTop10->Interval=ACHEVEMSG;
				break;
   case 'r':
   case 'R':    if (JeuEnCours&&(!TimerJeu->Enabled))
				 {
				  MsgStatut.Affiche(1, "");
				  TimerJeu->Enabled=true;
				 }
				break;
   case 'a':
   case 'A':    if (JeuEnCours&&(!TimerJeu->Enabled))
				 {
				  MsgStatut.Affiche(1, "");
				  JeuEnCours=false;
				 }
				break;
   case 'q':
   case 'Q':    if (JeuEnCours&&(!TimerJeu->Enabled))
				 Close();
				break;
/*
   case '$':    Jeu.Bonus.Pris=tous;
				RedessineInfoJeu(nb_bonus);
				break;
*/
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerDemoTimer(TObject *Sender)
{
 TimerDemo->Tag=(TimerDemo->Tag+1)%3;
 if (!TimerDemo->Tag)
  Bienvenue();
 Jeu.CreeLaby();
 RedessineCases();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 if (!JeuEnCours) return;
//v1.1 : DirectionsIndefinies : empêche que l'appui prolongé sur une direction n'élimine toutes les vies !
 bool DirectionsIndefinies=(Jeu.PacMan.d==indefinie)&&(Jeu.PacMan.ds==indefinie);
 if ((!DirectionsIndefinies)||(Jeu.Temps-Jeu.PacMan.TempsMort>TPSAVTREAPPARITION))
  switch(Key)
   {
    case FLECHE_HAUT:   if ((Jeu.c[Jeu.PacMan.x+dx[nord]][Jeu.PacMan.y+dy[nord]]==mur)||Jeu.ACheval)
                         Jeu.PacMan.ds=nord;
                        else
						 Jeu.PacMan.d=nord;
                        break;
    case FLECHE_DROITE: if ((Jeu.c[Jeu.PacMan.x+dx[est]][Jeu.PacMan.y+dy[est]]==mur)||Jeu.ACheval)
                         Jeu.PacMan.ds=est;
                        else
                         Jeu.PacMan.d=est;
                        break;
    case FLECHE_BAS:    if ((Jeu.c[Jeu.PacMan.x+dx[sud]][Jeu.PacMan.y+dy[sud]]==mur)||Jeu.ACheval)
                         Jeu.PacMan.ds=sud;
                        else
                         Jeu.PacMan.d=sud;
                        break;
    case FLECHE_GAUCHE: if ((Jeu.c[Jeu.PacMan.x+dx[ouest]][Jeu.PacMan.y+dy[ouest]]==mur)||Jeu.ACheval)
                         Jeu.PacMan.ds=ouest;
                        else
                         Jeu.PacMan.d=ouest;
                        break;
   }
//v1.1 : DirectionsIndefinies : empêche que l'appui prolongé sur une direction n'élimine toutes les vies !
 if (DirectionsIndefinies&&((Jeu.PacMan.d<indefinie)||(Jeu.PacMan.ds<indefinie)))
  {
   int xp=Jeu.PacMan.x,
       yp=Jeu.PacMan.y;
   Jeu.DebloquePorte(xp, yp, par_pacman); // v1.1
   //if (_VALIDE(xp, yp)&&_PORTE(xp, yp))
   // Jeu.Porte[Jeu.Table[xp][yp]].Bloquee&=tout-par_pacman;
   Jeu.PacMan.x=Jeu.NbX/2;
   Jeu.PacMan.y=Jeu.NbY/2;
   Jeu.RetireVie();
   RedessineCase(xp, yp);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PlaceCaractereInfoJeu(TRect &Rect, int ACol)
{
 int IdElement=IDMSGFONDNOIR,  // Par défaut on affichage du noir (vCX = FONDMSGNOIR et pas ESPACE)
     Cas;
 int Info=-1;
 if (JeuEnCours&&(DeroulementDemarrage>=DEBMSGSANSEFFACER))
  Info=(1+    score)*ZoneAff[    score].Contient(ACol)+
	   (1+     vies)*ZoneAff[     vies].Contient(ACol)+
       (1+attirance)*ZoneAff[attirance].Contient(ACol)+
       (1+   niveau)*ZoneAff[   niveau].Contient(ACol)+
       (1+ nb_bonus)*ZoneAff[ nb_bonus].Contient(ACol)-1;
 switch(Info)
  {
   case score:     switch(ACol-ZoneAff[score].ColDeb)
                    {
                     case 0: IdElement=IDMSGCHIFFRE+(Jeu.Score/10000); break;
                     case 1: IdElement=IDMSGCHIFFRE+(Jeu.Score/1000)%10; break;
                     case 2: IdElement=IDMSGCHIFFRE+(Jeu.Score/100)%10; break;
                     case 3: IdElement=IDMSGCHIFFRE+(Jeu.Score/10)%10; break;
                     case 4: IdElement=IDMSGCHIFFRE+(Jeu.Score%10); break;
                    }
                   break;
   case vies:      IdElement=(Jeu.NbVies>(ACol-ZoneAff[vies].ColDeb))?IDMSGVIE:IDMSGESPACE;
                   break;
   case attirance: switch(ACol-ZoneAff[attirance].ColDeb)
                    {
                     case 0: IdElement=IDMSGCHIFFRE+(Jeu.Determinisme/10); break;
                     case 1: IdElement=IDMSGCHIFFRE+(Jeu.Determinisme%10); break;
                     case 2: IdElement=IDMSGPOURCENT; break;
                    }
                   break;
   case niveau:    Cas=Jeu.Niveau-3*(ACol-ZoneAff[niveau].ColDeb);
                   IdElement=IDMSGETOILES+(Cas==1)+2*(Cas<1);
                   break;
   case nb_bonus:  Cas=ACol-ZoneAff[nb_bonus].ColDeb;
                   if (CouleurBonus[Cas]&Jeu.Bonus.Pris)
                    IdElement=IDMSGBONUS+Cas;
                   break;
  }
 // vCX : On affiche d'abord le fond à cause de la transparence
 VirtualImageListMsg->Draw(DrawGridPts->Canvas, Rect.Left, Rect.Top, IDMSGFONDNOIR);
 // vCX : TVirtualImageList au lieu de ImageList (HDPI)
 VirtualImageListMsg->Draw(DrawGridPts->Canvas, Rect.Left, Rect.Top, IdElement);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DrawGridPtsDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
 if (ACol<=DeroulementDemarrage/2)
  {
   // Début vCX : TVirtualImageList au lieu de ImageList (HDPI)
   switch(ACol-DeroulementDemarrage/2)
	{
	 case  0: if (DeroulementDemarrage%2)
				{
				 VirtualImageListJeu->Draw(	DrawGridPts->Canvas, // vCX
											Rect.Left, Rect.Top,
											IDMSGPACENTIER+
											(!((DeroulementDemarrage-3)%4)));
				 break;
				}
	   case -1: if (DeroulementDemarrage%2)
				 PlaceCaractereInfoJeu(Rect, ACol);
				else
				 VirtualImageListJeu->Draw(DrawGridPts->Canvas, Rect.Left, Rect.Top, IDMSGPACMOITIE+ACol-DeroulementDemarrage/2); // vCX
				break;
	   default: PlaceCaractereInfoJeu(Rect, ACol);
				break;
	}
	 // Fin vCX : TVirtualImageList au lieu de ImageList (HDPI)
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RedessineInfosJeu()
 {
  TRect CellWRectMin=DrawGridPts->CellRect(0, 0),
		CellWRectMax=DrawGridPts->CellRect(DrawGridPts->ColCount-1, DrawGridPts->RowCount-1);
  RECT CellRect={CellWRectMin.Left, CellWRectMin.Top, CellWRectMax.Right, CellWRectMax.Bottom};
  InvalidateRect(DrawGridPts->Handle, &CellRect, true);
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::RedessineInfoJeu(type_zone_aff TypeZoneAff)
 {
  for(int i=ZoneAff[TypeZoneAff].ColDeb; i<=ZoneAff[TypeZoneAff].ColFin; i++)
   RedessineCaractereInfosJeu(i);
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::RedessineCaractereInfosJeu(int x)
 {
  TRect CellWRect=DrawGridPts->CellRect(x, 0);
  RECT CellRect={CellWRect.Left, CellWRect.Top, CellWRect.Right, CellWRect.Bottom};
  InvalidateRect(DrawGridPts->Handle, &CellRect, true);
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::AfficheInfosJeuDepart()
 {
  DeroulementDemarrage=DEBMSGSANSEFFACER;
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::DerouleAffichageInfosJeu()
 {
  if (DeroulementDemarrage/2<=FormMain->DrawGridPts->ColCount)
   DeroulementDemarrage++;
  if (DeroulementDemarrage)
   FormMain->RedessineCaractereInfosJeu(DeroulementDemarrage/2-1);
  if (DeroulementDemarrage/2<FormMain->DrawGridPts->ColCount)
   FormMain->RedessineCaractereInfosJeu(DeroulementDemarrage/2);
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerJeuTimer(TObject *Sender)
{
 Jeu.Deplace();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::InformeValeurElement(elmt_valeur Element)
 {
  AnsiString asMsg;
  switch(Element)
   {
    case val_ftm: asMsg="MEME . #:100 ##:300 ###:600 ####:1000 #####:1500~"; break;
    case val_pgm: asMsg=Format("1 . : %d POINTS", ARRAYOFCONST((SCOREPACGUM))); break;
    case val_bns: asMsg=Format("€ OU $ OU £ OU ¥ : %d POINTS", ARRAYOFCONST((SCOREBONUS))); break;
    case val_qrt: asMsg=Format("¼ D'ECRAN : %d POINTS; 1# ET 1@ EN PLUS", ARRAYOFCONST((SCOREQUARTVIDE))); break;
   }
  MsgStatut.Affiche(1, asMsg);
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionInfosTop10Execute(TObject *Sender)
{
 // On suspend la démo
 ActionPartieJouer->Enabled=false; // v1.1 : on empêche l'action de jouer
 SansDemo=false;
 TimerDemo->Enabled=false;
 TimerDemo->Tag=0;
 // On vide l'écran pour le TOP 10
 Jeu.Detruit();
 RedessineCases();
 // On lance l'affichage du TOP 10
 DeroulementTop10=0;
 Top10.InitialiseDepart((DrawGridJeu->ColCount-asEnTeteTop10.Length())/2,
                        (DrawGridJeu->RowCount-NBENTREESTOP-1)/2);
 TimerTop10->Interval=VITESSEMSG;
 TimerTop10->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PlaceCaractereTop10(TRect &Rect, int Col, int Row)
 {
  int Cas,
	  x=Col-Top10.Col0, y=Row-Top10.Row0;
  if ((x<0)||(x>=Top10.l)||
	  (y<0)||(y>=Top10.h)) return;
  switch(y)
   {
	case 0: PlaceCaractere(DrawGridJeu, Rect, asEnTeteTop10[x+1]); break;
	case 1: PlaceCaractere(DrawGridJeu, Rect, '~'); break; // vCX : ... au lieu de Trèfle (esthétisme)
	case NBENTREESTOP+2: PlaceCaractere(DrawGridJeu, Rect, ' '); break; // vCX pb d'affichage à la fin : on finit par des espaces
	default: switch(x)
			  {
			   case  0: if (Top10.PosDrnEntree==y-2)
						 PlaceCaractere(DrawGridJeu, Rect, '>');
						break;
			   case  1: PlaceCaractere(DrawGridJeu, Rect, IntToStr((y-1)/10)[1]); break;
			   case  2: PlaceCaractere(DrawGridJeu, Rect, IntToStr((y-1)%10)[1]); break;
			   // NOM
			   case  4:     case  5:     case  6:     case  7:     case  8:     case  9:   case 10:
			   case 11: if (Top10.asNom[y-2].Length()>=x-3)
						 PlaceCaractere(DrawGridJeu, Rect, Top10.asNom[y-2][x-3]);
						else
						 PlaceCaractere(DrawGridJeu, Rect, ' ');
						break;

			   // NIVEAU DE DIFFICULTE
			   //   case niveau:
			   case 13:     case 14:     case 15:     case 16:
			   case 17:     case 18:     case 19:     case 20:
			   case 21:
			   case 22: Cas=Top10.Niveau[y-2]-3*(x-13);
						PlaceCaractere(DrawGridJeu, Rect, Etoile[(Cas==1)+2*(Cas<1)]);
						break;
			   // SCORE
			   case 24: PlaceCaractere(DrawGridJeu, Rect, IntToStr(Top10.Score[y-2]/10000)[1]); break;
			   case 25: PlaceCaractere(DrawGridJeu, Rect, IntToStr((Top10.Score[y-2]/1000)%10)[1]); break;
			   case 26: PlaceCaractere(DrawGridJeu, Rect, IntToStr((Top10.Score[y-2]/100)%10)[1]); break;
			   case 27: PlaceCaractere(DrawGridJeu, Rect, IntToStr((Top10.Score[y-2]/10)%10)[1]); break;
			   case 28: PlaceCaractere(DrawGridJeu, Rect, IntToStr(Top10.Score[y-2]%10)[1]); break;
			   default: break;
			  }
   }
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::AfficheTop10(TRect &Rect, int Col, int Row)
 {
  int Position=POSITION;
  if ((Position>=0)&&(Position<=DeroulementTop10/2))
   {
	 // Début vCX : TVirtualImageList au lieu de ImageList (HDPI)
	 switch(Position-DeroulementTop10/2)
	  {
	   case  0: if (DeroulementTop10%2)
				 {
				  if (((DeroulementTop10+1)/2)%Top10.l)
				   VirtualImageListJeu->Draw(DrawGridJeu->Canvas, // vCX
											 Rect.Left, Rect.Top,
											 IDMSGPACENTIER+
											 (!((DeroulementTop10-3)%4)));
				  else // Fin de ligne retour à la ligne suivante
				   PlaceCaractereTop10(Rect, Col, Row);
				  break;
				 }
	   case -1: if (DeroulementTop10%2)
				 PlaceCaractereTop10(Rect, Col, Row);
				else
				 if (Position)
				  VirtualImageListJeu->Draw(DrawGridJeu->Canvas, Rect.Left, Rect.Top, IDMSGPACMOITIE+Position-DeroulementTop10/2); // vCX
				break;
	   default: PlaceCaractereTop10(Rect, Col, Row);
				break;
	  }
     // Fin vCX : TVirtualImageList au lieu de ImageList (HDPI)
	}
  }
//---------------------------------------------------------------------------
void __fastcall TFormMain::DerouleAffichageTop10()
 {
  if (DeroulementTop10<2*Top10.h*Top10.l-1)
   {
	DeroulementTop10++;
	if (DeroulementTop10)
	 FormMain->RedessineCase
	 (Top10.Col0+(DeroulementTop10/2)%Top10.l-1,
							 Top10.Row0+(DeroulementTop10/2)/Top10.l);
	if (DeroulementTop10<2*Top10.h*Top10.l)
	 FormMain->RedessineCase(Top10.Col0+(DeroulementTop10/2)%Top10.l,
							 Top10.Row0+(DeroulementTop10/2)/Top10.l);
   }
  else
   {
	TimerTop10->Enabled=false;
	DeroulementTop10=0;
	JeuEnCours=false;
	ActionPartieJouer->Enabled=true; // v1.1 : on réautorise l'action de jouer
   }
 }
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerTop10Timer(TObject *Sender)
{
 DerouleAffichageTop10();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionParamEnregistrerExecute(TObject *Sender)
{
 Top10.EnregistreParametres();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionParamRestaurerExecute(TObject *Sender)
{
 Top10.RestaureParametres();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionParamReinitialiserTop10Execute(
      TObject *Sender)
{ // Ajout v1.1
 Top10.Reinitialise();
 MsgStatut.Affiche(1, "TOP10 REINITIALISE");
 ActionInfosTop10Execute(ActionInfosTop10);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
 // vCX : TVirtualImageList au lieu de ImageList (HDPI) => On doit initialiser les propriétés non publiées
 VirtualImageListJeu->DrawingStyle=dsTransparent;
 VirtualImageListJeu->ImageType=itMask;
 VirtualImageListJeu->Masked=True;
 VirtualImageListJeu->ColorDepth=cd32Bit;
 VirtualImageListMsg->DrawingStyle=dsTransparent;
 VirtualImageListMsg->ImageType=itMask;
 VirtualImageListMsg->Masked=True;
 VirtualImageListMsg->ColorDepth=cd32Bit;
}
//---------------------------------------------------------------------------

