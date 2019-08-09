#include "nomtop10_f.h"
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "main_f.h"
#include <math.h>
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Fonctions globales
//---------------------------------------------------------------------------
// vCX : on utilise le chemin donné par %LocalAppData% pour Windows 7 ou plus sinon le dossier de l'exécutable
String stRepLocalAppData;
//---------------------------------------------------------------------------
String InitialiseRepLocalAppData()
 {
   String stResult;
   String stExePath = ExtractFilePath(ParamStr(0));
   const String stVarLocalAppData  = "LOCALAPPDATA";
   const String stRepLocAppDataFPac3 = "\\Patquoi.fr\\FPac3";
   stResult = GetEnvironmentVariable(stVarLocalAppData);
   if (stResult == "")
	 stResult = stExePath;
   else
	{
	 stResult = stResult + stRepLocAppDataFPac3;
	 if (!DirectoryExists(stResult))
	   if (!ForceDirectories(stResult))
		 stResult = stExePath;
	}
   return stResult;
 }
//---------------------------------------------------------------------------
void top10::Reinitialise()
 {
  for(int i=0; i<NBENTREESTOP; i++)
   {
	Score[i]=0;
	asNom[i]=NOMVIDE;
	Niveau[i]=0;
   }
  Ecrit();
 }
//---------------------------------------------------------------------------
top10::top10()
 {

  PosDrnEntree=NBENTREESTOP;
  // vCX : fichier ini dans %LocalAppData%\Patquoi.fr\FPac3
  stRepLocalAppData = InitialiseRepLocalAppData();
  //IniFile = new TIniFile(ExtractFilePath(ParamStr(0))+"\\FPAC3.INI");
  IniFile = new TIniFile(stRepLocalAppData+"\\FPAC3.INI");
  Lit();
 }
//---------------------------------------------------------------------------
void top10::Lit()
 {
  for(int i=0; i<NBENTREESTOP; i++)
   {
	Score[i]=IniFile->ReadInteger(SECTIONTOP10, Format(ENTREESCORE, ARRAYOFCONST((i))), 0);
    asNom[i]=IniFile->ReadString(SECTIONTOP10, Format(ENTREENOM, ARRAYOFCONST((i))), ";;;;;;;;");
    Niveau[i]=IniFile->ReadInteger(SECTIONTOP10, Format(ENTREENIV, ARRAYOFCONST((i))), 0);
   }
 }
//---------------------------------------------------------------------------
void top10::Ecrit()
 {
  for(int i=0; i<NBENTREESTOP; i++)
   {
    IniFile->WriteInteger(SECTIONTOP10, Format(ENTREESCORE, ARRAYOFCONST((i))),  Score[i]);
    IniFile->WriteString(SECTIONTOP10, Format(ENTREENOM, ARRAYOFCONST((i))),  asNom[i]);
    IniFile->WriteInteger(SECTIONTOP10, Format(ENTREENIV, ARRAYOFCONST((i))), Niveau[i]);
   }
 }
//---------------------------------------------------------------------------
void top10::InitialiseDepart(int Col0, int Row0)
{
 this->Col0=Col0;
 this->Row0=Row0;
 this->l=asEnTeteTop10.Length();
 this->h=NBENTREESTOP+3; // Entrées + séparations + en-tête
}
//---------------------------------------------------------------------------
void top10::TesteTop()
 {
  if (EstMieuxQueLeRang(NBENTREESTOP-1)&&
      (FormNomTop10->ShowModal()==mrOk))
   AjouteAuTop(FormNomTop10->EditNom->Text);
  FormMain->ActionInfosTop10Execute(FormMain);
 }
//---------------------------------------------------------------------------
void top10::Affecte(int Rang, int Score, int Niveau, const AnsiString asNom)
 {
  this->Score[Rang]=Score;
  this->Niveau[Rang]=Niveau;
  this->asNom[Rang]=asNom;
 }
//---------------------------------------------------------------------------
void top10::AjouteAuTop(const AnsiString asNouveauNom)
 {
  for(int i=NBENTREESTOP-1; i>-1; i--)
   {
    if (EstMieuxQueLeRang(i))
     {
      if (!i)
       {
        Affecte(1, Score[0], Niveau[0], asNom[0]);
        Affecte(PosDrnEntree=0, Jeu.Score, Jeu.Niveau, asNouveauNom);
       }
      else
       if (i<NBENTREESTOP-1)
        Affecte(i+1, Score[i], Niveau[i], asNom[i]);
     }
    else
     {
      if (i<NBENTREESTOP-1)
       Affecte(PosDrnEntree=i+1, Jeu.Score, Jeu.Niveau, asNouveauNom);
      break;
     }
   }
  Ecrit();
 }
//---------------------------------------------------------------------------
void top10::LitParametres()
 {
  switch(IniFile->ReadInteger(SECTIONPARAM, ENTREEDIM, 0))
   {
    default:FormMain->ActionDimensionsExecute(FormMain->ActionParamDimensions48x30); break;
    case 1: FormMain->ActionDimensionsExecute(FormMain->ActionParamDimensions64x40); break;
    case 2: FormMain->ActionDimensionsExecute(FormMain->ActionParamDimensions80x50); break;
    case 3: FormMain->ActionDimensionsExecute(FormMain->ActionParamDimensions96x60); break;
    case 4: FormMain->ActionDimensionsExecute(FormMain->ActionParamDimensions112x70); break;
   }
  switch(IniFile->ReadInteger(SECTIONPARAM, ENTREEAGR, 0))
   {
    default:FormMain->ActionAgressiviteExecute(FormMain->ActionParamAgressivite25); break;
    case 1: FormMain->ActionAgressiviteExecute(FormMain->ActionParamAgressivite33); break;
    case 2: FormMain->ActionAgressiviteExecute(FormMain->ActionParamAgressivite50); break;
   }
  switch(IniFile->ReadInteger(SECTIONPARAM, ENTREERPP, 1))
   {
    case 0: FormMain->Action1PGxxxPExecute(FormMain->ActionParamPilulesParPacgum100); break;
    default:FormMain->Action1PGxxxPExecute(FormMain->ActionParamPilulesParPacgum100); break;
    case 2: FormMain->Action1PGxxxPExecute(FormMain->ActionParamPilulesParPacgum150); break;
   }
  switch(IniFile->ReadInteger(SECTIONPARAM, ENTREEDVF, 1))
   {
    case 0: FormMain->ActionxxCasesExecute(FormMain->ActionParamVulnerabilite100Cases); break;
    default:FormMain->ActionxxCasesExecute(FormMain->ActionParamVulnerabilite50Cases); break;
    case 2: FormMain->ActionxxCasesExecute(FormMain->ActionParamVulnerabilite25Cases); break;
   }
  switch(IniFile->ReadInteger(SECTIONPARAM, ENTREENFD, 1))
   {
    case 0: FormMain->ActionDepartFantomesExecute(FormMain->ActionParamDepartFantomes3); break;
    default:FormMain->ActionDepartFantomesExecute(FormMain->ActionParamDepartFantomes4); break;
    case 2: FormMain->ActionDepartFantomesExecute(FormMain->ActionParamDepartFantomes5); break;
    case 3: FormMain->ActionDepartFantomesExecute(FormMain->ActionParamDepartFantomes6); break;
   }
  switch(IniFile->ReadInteger(SECTIONPARAM, ENTREENBP, 1))
   {
    case 0: FormMain->ActionParamPortesNPour2LignesExecute(FormMain->ActionParamPortes1Pour150Cases); break;
    default:FormMain->ActionParamPortesNPour2LignesExecute(FormMain->ActionParamPortes1Pour75Cases); break;
    case 2: FormMain->ActionParamPortesNPour2LignesExecute(FormMain->ActionParamPortes1Pour50Cases); break;
   }
 }
//---------------------------------------------------------------------------
void top10::EnregistreParametres()
 {
  IniFile->WriteInteger(SECTIONPARAM, ENTREEDIM, 1*FormMain->ActionParamDimensions64x40->Checked+
                                                 2*FormMain->ActionParamDimensions80x50->Checked+
                                                 3*FormMain->ActionParamDimensions96x60->Checked+
                                                 4*FormMain->ActionParamDimensions112x70->Checked);

  IniFile->WriteInteger(SECTIONPARAM, ENTREEAGR, 1*FormMain->ActionParamAgressivite33->Checked+
                                                 2*FormMain->ActionParamAgressivite50->Checked);

  IniFile->WriteInteger(SECTIONPARAM, ENTREERPP, 1*FormMain->ActionParamPilulesParPacgum100->Checked+
                                                 2*FormMain->ActionParamPilulesParPacgum150->Checked);

  IniFile->WriteInteger(SECTIONPARAM, ENTREEDVF, 1*FormMain->ActionParamVulnerabilite50Cases->Checked+
                                                 2*FormMain->ActionParamVulnerabilite25Cases->Checked);

  IniFile->WriteInteger(SECTIONPARAM, ENTREENFD, 1*FormMain->ActionParamDepartFantomes4->Checked+
                                                 2*FormMain->ActionParamDepartFantomes5->Checked+
                                                 3*FormMain->ActionParamDepartFantomes6->Checked);

  IniFile->WriteInteger(SECTIONPARAM, ENTREENBP, 1*FormMain->ActionParamPortes1Pour75Cases->Checked+
                                                 2*FormMain->ActionParamPortes1Pour50Cases->Checked);
  MsgStatut.Affiche(1, "ENREGISTREMENT DES PARAMETRES EFFECTUE");
 }
//---------------------------------------------------------------------------
void top10::RestaureParametres()
 {
  FormMain->ActionDimensionsExecute(FormMain->ActionParamDimensions48x30);
  FormMain->ActionAgressiviteExecute(FormMain->ActionParamAgressivite25);
  FormMain->Action1PGxxxPExecute(FormMain->ActionParamPilulesParPacgum100);
  FormMain->ActionxxCasesExecute(FormMain->ActionParamVulnerabilite50Cases);
  FormMain->ActionDepartFantomesExecute(FormMain->ActionParamDepartFantomes4);
  FormMain->ActionParamPortesNPour2LignesExecute(FormMain->ActionParamPortes1Pour75Cases);
  MsgStatut.Affiche(1, "RESTAURATION DES PARAMETRES PAR DEFAUT EFFECTUEE");
 }
//---------------------------------------------------------------------------
bool top10::EstMieuxQueLeRang(int Rang)
 {
  return ((Jeu.Score>Score[Rang])||
          ((Jeu.Score==Score[Rang])&&
           (Jeu.Niveau>Niveau[Rang])));

 }
//---------------------------------------------------------------------------
void primes::Initialise()
 {
  Nouvelle=Courante=0;
  for(int i=0; i<NBMAXPRIMES; i++)
   x[i]=y[i]=Delai[i]=Valeur[i]=0;
 }
//---------------------------------------------------------------------------
void primes::Affiche()
 {
  for(int i=Courante; i!=Nouvelle; i=(i+1)%NBMAXPRIMES)
   {
    int x=this->x[i],
        y=this->y[i];
    if (Delai[i])
     {
      Delai[i]--;
      FormMain->RedessineCase(x, y);
     }
    else
     if (x||y)
      {
       this->x[i]=this->y[i]=0;
       Courante=(Courante+1)%NBMAXPRIMES;
       FormMain->RedessineCase(x, y);
      }
    }
 }
//---------------------------------------------------------------------------
void primes::Ajoute(int Num, int xp, int yp)
 {
  x[Nouvelle]=xp; y[Nouvelle]=yp;
  Delai[Nouvelle]=DELAIPRIME;
  Valeur[Nouvelle]=PRIMEFANTOME*Jeu.NbFantomesManges;
  Nouvelle=(Nouvelle+1)%NBMAXPRIMES;
 }
//---------------------------------------------------------------------------
void bonus::Gere()
 {
  if (Temps)
   Temps--;
  else
   {
    int xp=x, yp=y;
    Jeu.DebloquePorte(x, y, par_bonus); // v1.1
    //if (_VALIDE(x, y)&&_PORTE(x, y))
    // Jeu.Porte[Jeu.Table[x][y]].Bloquee&=tout-par_bonus;
    APrendre=CouleurBonus[RANDOM(NBBONUS)];
    do
     {
      x=1+RANDOM(_XMAX-1);
      y=1+RANDOM(_YMAX-1);
     }
    while((DIST(x-Jeu.PacMan.x, y-Jeu.PacMan.y)<DISTMINPACBONUS)||(Jeu.c[x][y]==mur));
    Jeu.BloquePorte(x, y, par_bonus); // v1.1
    //if (_VALIDE(x, y)&&_PORTE(x, y))
    // Jeu.Porte[Jeu.Table[x][y]].Bloquee|=par_bonus;
    FormMain->RedessineCase(xp, yp);
    FormMain->RedessineCase(x, y);
    Temps=TEMPSBONUS;
   }
 }
//---------------------------------------------------------------------------
void bonus::Mange()
 {
  Temps=0;
  Pris=(prise_bonus)((int)Pris|(int)APrendre); // vCX : operateur |= non supportés sur les enums.
  Jeu.IncrementeScore(SCOREBONUS); // Oups... un oubli !!! v1.1
  FormMain->RedessineInfoJeu(nb_bonus);
  FormMain->InformeValeurElement(val_bns);
  if (Pris==tous)
   MsgStatut.Affiche(1, "VOUS AVEZ LES 4 BONUS €$£¥; C'EST PORTE OUVERTE~");
 }
//---------------------------------------------------------------------------
void fantome::Lance()
 {
  int n=RANDOM(Jeu.NbBords);
  Etat=en_chasse;
  x=Jeu.Bord[n].x;
  y=Jeu.Bord[n].y;
  d=Jeu.Bord[n].d;
  FormMain->RedessineCase(x, y);
 }
//---------------------------------------------------------------------------
void fantome::CalculeNouvelleDirection()
{
 int nd=0, // Nb dir possibles
     diffmax=-INFINI, diffmin=INFINI, // Différences de distances
     ndmax=0, ndmin=0,
     diff[NBDIRECTIONS];
 bool dposs[NBDIRECTIONS]; // Dir possible ?
 nd=(dposs[nord ]=(_C(x,y,nord)<mur))+
    (dposs[est  ]=(_C(x,y,est)<mur))+
    (dposs[sud  ]=(_C(x,y,sud)<mur))+
    (dposs[ouest]=(_C(x,y,ouest)<mur));
 diffmax=-INFINI; diffmin=INFINI;
 if (nd)
  {
   if (Etat) // N'est pas mangé
    {
     for(int dd=0; dd<NBDIRECTIONS; dd++)
      {
       if ((dposs[dd])&&((nd==1)||((dd+2)%NBDIRECTIONS!=d)))
        {
         diff[dd]=DIST(x-Jeu.PacMan.x, y-Jeu.PacMan.y)-
                  DIST(x+dx[dd]-Jeu.PacMan.x-dx[Jeu.PacMan.d],
                       y+dy[dd]-Jeu.PacMan.y-dy[Jeu.PacMan.d]);
         if (diff[dd]<diffmin) diffmin=diff[dd];
         if (diff[dd]>diffmax) diffmax=diff[dd];
        }
       else diff[dd]=INFINI;
      }
     ndmax=0; ndmin=0;
     for(int dd=0; dd<NBDIRECTIONS; dd++)
      {
       if (diff[dd]==diffmax) ndmax++;
       if (diff[dd]==diffmin) ndmin++;
      }
     switch(Etat)
      {
       case en_chasse: if (RANDOM(MAXDETERMINISME)<=Jeu.Determinisme)
                        {
                         int k=RANDOM(ndmax);
                         for(int dd=0; dd<NBDIRECTIONS; dd++)
                          {
                           if (diff[dd]==diffmax)
							{
							 if (k) k--;
							 else
							  d=(direction)dd;
							}
						  }
                        }
                       else
                        do
                         d=(direction)RANDOM(NBDIRECTIONS);
                        while(diff[d]==INFINI);
                       break;
       case transition:
       case en_fuite:  if (RANDOM(MAXDETERMINISME)<=Jeu.Determinisme)
                        {
                         int k=RANDOM(ndmin);
                         for(int dd=0; dd<NBDIRECTIONS; dd++)
                          {
                           if (diff[dd]==diffmin)
							{
							 if (k) k--;
							 else d=(direction)dd;
                            }
                          }
                        }
                       else
                        do
                         d=(direction)RANDOM(NBDIRECTIONS);
                        while(diff[d]==INFINI);
					   break;
       case mange:     break; // vCX : évite l'avertissement
	  }
    }
   else // Est mangé
    {
     // Détermination de la direction adéquate jusqu'au donjon grâce à dm[x][y]
     int DistMinDonjon=INFINI;
     direction dMinDonjon=indefinie;
     for(int dd=nord; dd<=ouest; dd++)
      {
       if ((_C(x,y,dd)<mur)&& // La place est libre ET
           (((_DM(x,y,dd)<DistMinDonjon)&& // SOIT c'est plus proche du donjon que la dernière possibilité trouvée ET
             ((dMinDonjon==indefinie)|| // (c'est la première possibilité OU // v1.2
              (!DEMITOUR(dd,d))))|| // ce n'est pas la premère mais ce n'est pas un demi-tour), // v1.2
            DEMITOUR(dMinDonjon,d))) // SOIT la dernière possibilité trouvée est un demi-tour // v1.2

        {
         DistMinDonjon=_DM(x,y,dd);
         dMinDonjon=(direction)dd;
        }
      }
     if (DistMinDonjon>2) // Pas arrivé au donjon
      d=dMinDonjon;
     else // Est arrivé au donjon
      {
       xp=x; yp=y; x=y=-1;
       FormMain->RedessineCase(xp, yp); // On efface les yeux
       Lance();
      }
    }
  }
 else
  d=indefinie;
}
//---------------------------------------------------------------------------
void fantome::EvalueSituation()
 {
  // 1. Le fantome rencontre PacMan
  if (((Jeu.PacMan.x==x)&&(Jeu.PacMan.y==y))|| // 1a: Même case
      ((Jeu.PacMan.x==x-dx[d])&&(Jeu.PacMan.y==y-dy[d])&&((NBDIRECTIONS+d-Jeu.PacMan.d)%NBDIRECTIONS==NBDIRECTIONS/2))) // 1b. Ils se sont croisés à cheval !!!
   switch(Etat)
    {
     case en_chasse:  Jeu.MangePacMan();
                      break;
     case en_fuite:
     case transition: Jeu.MangeFantome(Num);
                      break;
     case mange: break; // Il est déja mangé alors on laisse le fantôme rentrer au donjon...
    }
  else // Autres cas
   if (Etat)
    {
     if (Jeu.QuartNettoye&&(Num<Jeu.NbFantomes-1))
      Etat=mange;
     else
      switch(Etat)
       {
        case transition:
        case en_fuite:   if (TpsRestantVulnerable)
                          {
                           if (TpsRestantVulnerable<=(Jeu.Vulnerabilite/RAPPORTVULNTRANS))
                            Etat=transition;
                           TpsRestantVulnerable--;
                          }
                         else
                          Etat=en_chasse;
						 break;
		case mange:
        case en_chasse:  break; // vCX : évite l'avertissement
       }
    }
 }
//---------------------------------------------------------------------------
void fantome::Deplace()
 {
  if (!Jeu.ACheval)
   CalculeNouvelleDirection();

  if (d<indefinie)
   {
    // Test déblocage porte
    Jeu.DebloquePorte(x, y, par_fantome); // v1.1
    //if (_VALIDE(x, y)&&_PORTE(x, y))
    // Jeu.Porte[Jeu.Table[x][y]].Bloquee&=tout-par_fantome;
    if (Jeu.c[x+dx[d]][y+dy[d]]<mur)
     {
      if (Jeu.ACheval)
       {
        xp=x; yp=y;
        x+=dx[d]; y+=dy[d];

        EvalueSituation();
        
        FormMain->RedessineCase(xp, yp);
        FormMain->RedessineCase(x, y);
       }
      else
       {
        FormMain->RedessineCase(x, y);
        FormMain->RedessineCase(x+dx[d], y+dy[d]);
       }
     }
    else
     FormMain->RedessineCase(x, y);
    // Test blocage porte
    Jeu.BloquePorte(x, y, par_fantome); // v1.1
    //if (_VALIDE(x, y)&&_PORTE(x, y))
    // Jeu.Porte[Jeu.Table[x][y]].Bloquee|=par_fantome;
   }
 }
//---------------------------------------------------------------------------
void fantome::RendVulnerable()
 {
  TpsRestantVulnerable=Jeu.Vulnerabilite;
  Etat=en_fuite;
 }
//---------------------------------------------------------------------------
void pacman::Deplace()
 {
  if (d==indefinie)
   {
    if (TempsMort&&
        ((Jeu.Temps-TempsMort<=2*NBANIMATIONSMORT)||
         (Jeu.Temps-TempsMort==TPSAVTREAPPARITION+1))) // v1.2
     FormMain->RedessineCase(x, y);
    if ((ds==indefinie)||
        (_C(x,y,ds)==mur)||
        Jeu.ACheval)
     return;
   }
  if ((ds<indefinie)&&
      (_C(x,y,ds)<mur)&&
      (!Jeu.ACheval))
   {
    d=ds;
    ds=indefinie;
   }
  if (d<indefinie)
   {
    // Test déblocage porte
    Jeu.DebloquePorte(x, y, par_pacman); // v1.1
    //if (_VALIDE(x, y)&&_PORTE(x, y))
    // Jeu.Porte[Jeu.Table[x][y]].Bloquee&=tout-par_pacman;
    if (Jeu.c[x+dx[d]][y+dy[d]]<mur)
     {
      if (Jeu.ACheval)
       {
        xp=x; yp=y;
        x+=dx[d]; y+=dy[d];
        switch(Jeu.c[x][y])
         {
          case vide:   Jeu.Inactivite++;
                       if (Jeu.Inactivite==INACTIVITEPARDETERMINISME)
                        Jeu.IncrementeDeterminisme();
                       break;
          case pilule: MangePilule(); break;
          case pacgum: MangePacGum(); break;
          default: break;
         }
        if ((x==Jeu.Bonus.x)&&(y==Jeu.Bonus.y))
         Jeu.Bonus.Mange();
        FormMain->RedessineCase(xp, yp);
        FormMain->RedessineCase(x, y);
       }
      else
       {
        FormMain->RedessineCase(x, y);
        FormMain->RedessineCase(x+dx[d], y+dy[d]);
       }
     }
    else
     {
      // ON regarde si ce n'est pas une transposition
      if (_TRANSPOSITION(x+dx[d], y+dy[d]))
       {
        if (Jeu.ACheval)
         {
          xp=x; yp=y;
          if (x==1) x=_XMAX-1; else
          if (x==_XMAX-1) x=1;
          if (y==1) y=_YMAX-1; else
          if (y==_YMAX-1) y=1;
          FormMain->RedessineCase(xp, yp);
          FormMain->RedessineCase(x, y);
         }
        else
         {
          if (_VALIDE(Jeu.PacMan.xp,Jeu.PacMan.yp))
           FormMain->RedessineCase(Jeu.PacMan.xp, Jeu.PacMan.yp);
          FormMain->RedessineCase(x, y);
         }
       }
      else
       FormMain->RedessineCase(x, y);
     }
    // Test blocage porte
    Jeu.BloquePorte(x, y, par_pacman); // v1.1
    //if (_VALIDE(x, y)&&_PORTE(x, y))
    // Jeu.Porte[Jeu.Table[x][y]].Bloquee|=par_pacman;
   }
 }
//---------------------------------------------------------------------------
void pacman::MangePilule()
 {
  AMange=true; // Permet d'afficher la bouche ouverte
  Jeu.IncrementeScore(SCOREPILULE);
  Jeu.c[x][y]=vide;
  int NumQuart;
  Jeu.NbPilules[NumQuart=_NUMQUART(x, y)]--;
  if (!Jeu.NbPilules[NumQuart])
   {
    Jeu.AjouteVie();
    Jeu.IncrementeScore(SCOREQUARTVIDE);
    Jeu.AjouteFantome();
    Jeu.QuartNettoye=true;
    FormMain->InformeValeurElement(val_qrt);
    // v1.1 fin de jeu déplacée en fin de cycle
   }
 }
//---------------------------------------------------------------------------
void pacman::MangePacGum()
 {
  AMange=true; // Permet d'afficher la bouche ouverte
  Jeu.IncrementeScore(SCOREPACGUM);
  Jeu.c[x][y]=vide;
  Jeu.NbFantomesManges=0;
  for(int i=0; i<Jeu.NbFantomes; i++)
   if (Jeu.Fantome[i].Etat==en_chasse)
    Jeu.Fantome[i].RendVulnerable();
  FormMain->InformeValeurElement(val_pgm);
 }
//---------------------------------------------------------------------------
void pacman::Meurt()
 {
  TempsMort=Jeu.Temps;
  d=ds=indefinie;
  FormMain->RedessineCase(x, y);
 }
//---------------------------------------------------------------------------
jeu::jeu()
 { //Paramètres par défaut
  FrqPil=PRMPARDEFPILULEPARPACGUM;
  Vulnerabilite=PRMPARDEFVULNERABILITE;
  FantomesDepart=PRMPARDEFFANTOMESDEPART;
  PortesParCase=PRMPARDEFPORTESPARCASE;
  Agressivite=PRMPARDEFAGRESSIVITE;
  c=0; Table=0; dm=0; oad=0;  // Labyrinthe (Tableaux dynamiques alloués dans Initialise au lancement du jeu)
  Porte=0;
  Temps=NbX=NbY=0; // Pas de taille
  ACheval=false;
  for(int i=0; i<NBMAXFANTOMES; i++)
   Fantome[i].Numerote(i);
 }
//---------------------------------------------------------------------------
void jeu::PosePortes()
 {
  int i, j, x, y;
  bool Ouverte;
  j=0;
  do
   {
    do
     {
      x=2+RANDOM(XMAX-3);
      y=2+RANDOM(YMAX-3);
      for(i=0; (i<j)&&((Porte[i].x-x)*(Porte[i].x-x)+(Porte[i].y-y)*(Porte[i].y-y)>1); i++);
     }
    while(i<j);
    if ((x!=NBX/2)&&(y!=NBY/2))
     {
      if ((c[x][y-1]==mur)&&(c[x][y+1]==mur)&&
          (c[x-1][y]!=mur)&&(c[x+1][y]!=mur))
       {
        Ouverte=RANDOM(2);
        Table[x][y]=j;
        Porte[j].Positionne(x, y, Ouverte, NBANIMATIONSPORTE+(NBANIMATIONSPORTE-1)*(!Ouverte));
        if (c[x][y]==pilule)
         NbPilules[NUMQUART(x,y)]--;
        j++;
       }
      if ((c[x][y-1]!=mur)&&(c[x][y+1]!=mur)&&
         (c[x-1][y]==mur)&&(c[x+1][y]==mur))
       {
        Ouverte=RANDOM(2);
        Table[x][y]=j;
        Porte[j].Positionne(x, y, Ouverte, (NBANIMATIONSPORTE-1)*(!Ouverte));
        if (c[x][y]==pilule)
         NbPilules[NUMQUART(x,y)]--;
        j++;
       }
     }
   }
  while(j<NbPortes);
  for(int k=0; k<NbPortes; k++)
   c[Porte[k].x][Porte[k].y]=(Porte[k].Pos%NBANIMATIONSPORTE)?mur:vide;
 }
//---------------------------------------------------------------------------
void jeu::AnimePortes()
 {
  int NumPorteFinCycle=(Temps%NbPortes),
      jmax=(Temps<NBANIMATIONSPORTE-1)?Temps:NBANIMATIONSPORTE-1, // On rafraîchit 4 portes par tour sauf dans les 3 premiers tours
      k=NbPortes+NumPorteFinCycle+1-jmax;
  // Zone Sésame
  if (Bonus.Pris==tous)
   {
    direction d=PacMan.d;
    if ((ACheval)&&(d<indefinie))
     {
      int x=PacMan.x+dx[d], y=PacMan.y+dy[d];
      for(int i=0; i<NbPortes; i++)
       if (oad[x][y].PosPorte[i]<NBANIMATIONSPORTE)
        {
         porte *p=Porte+i;
         if ((p->Bloquee==zone)|| // Soit la porte est déjà sous influence de Sésame
             ((!p->Bloquee)&&     // Soit elle n'est pas bloquée ET...
              (ABS(p->Pos%NBANIMATIONSPORTE-oad[x][y].PosPorte[i])<2))) // elle est dans la même position à une phase près
          {
           if (p->Bloquee!=zone)
            p->Bloquee=zone;
           p->Pos=oad[x][y].PosPorte[i]+NBANIMATIONSPORTE*((c[p->x][p->y-1]==mur)&&(c[p->x][p->y+1]==mur)&&
                                                           (c[p->x-1][p->y]!=mur)&&(c[p->x+1][p->y]!=mur));
           switch(p->Pos%NBANIMATIONSPORTE)
            {
             case 0:                   c[p->x][p->y]=vide;
                                       p->Ouverte=true;
                                       break;
             default:                  c[p->x][p->y]=mur;
                                       p->Ouverte=false;
                                        break;
            }
           FormMain->RedessineCase(p->x, p->y);
          }
        }
     }
    if (d==indefinie)
     FermePortes(); 
   }
  // Zone non (encore) Sésame
  for(int j=0; j<jmax; j++)
   {
    int i=(k+j)%NbPortes;
    porte *p=Porte+i;
    if (p->Bloquee!=zone) // Porte non bloquée par Sésame
     {
      if (i==NumPorteFinCycle)
       {
        p->Ouverte=(c[p->x][p->y]==vide);
        p->BlqEnr=p->Bloquee;
       }
      if (!p->Ouverte)
       {
        if (!p->BlqEnr)
         {
          if (p->Pos%NBANIMATIONSPORTE)
           p->Pos--;
          if (!(p->Pos%NBANIMATIONSPORTE))
           c[p->x][p->y]=vide;
          FormMain->RedessineCase(p->x, p->y);
         }
        else
         if (!j) p->BlqEnr=0;
       }
      else
       {
        if (!p->BlqEnr)
         {
          if (p->Pos%NBANIMATIONSPORTE<NBANIMATIONSPORTE-1)
           p->Pos++;
          if ((p->Pos%NBANIMATIONSPORTE)==1)
           c[p->x][p->y]=mur;
          FormMain->RedessineCase(p->x, p->y);
         }
        else
         if (!j) p->BlqEnr=0;
       }
     }
   }
 }
//---------------------------------------------------------------------------
void jeu::FermePortes()
 {
  int xp=PacMan.x,
      yp=PacMan.y;
  for(int i=0; i<NbPortes; i++)
   {
    porte *p=Porte+i;
    if ((p->Pos%NBANIMATIONSPORTE<NBANIMATIONSPORTE-1)&& // SI la porte n'est pascomplètement fermée ET
        (oad[xp][yp].PosPorte[i]<NBANIMATIONSPORTE)&& // Elle est dans la zone Sésame ET
        ((p->Bloquee|zone)==zone)) // Blocage = zone et rien d'autre. vCX : ajout parethèses pour lever avertissement
     {
      p->Pos++;
      if (p->Pos%NBANIMATIONSPORTE==1)
       {
        c[p->x][p->y]=mur;
        p->Ouverte=false;
       }
      FormMain->RedessineCase(p->x, p->y);
     }
   }
 }
//---------------------------------------------------------------------------
void jeu::Detruit()
 {
  if (c)
   {
    for(int i=0; i<NBX; i++)
     delete[] c[i];
    delete[] c;
    c=NULL;
   }
  if (Table)
   {
    for(int i=0; i<NBX; i++)
     delete[] Table[i];
    delete[] Table;
    Table=NULL;
   }
  if (dm)
   {
    for(int i=0; i<NBX; i++)
     delete[] dm[i];
    delete[] dm;
    dm=NULL;
   }
  if (oad)
   {
    for(int i=0; i<NBX; i++)
     delete[] oad[i];
    delete[] oad;
    oad=NULL;
   }
  if (Porte)
   {
    delete[] Porte;
    Porte=NULL;
   }
 }
//---------------------------------------------------------------------------
void jeu::Initialise()
 {
  Detruit();
  Temps=NbCases=0;
  for(int i=0; i<NBPLANS; i++)
   NbPilules[i]=0;
  // FrqPil, Vulnerabilite, FantomesDepart, PortesParCase ==> Paramètres déjà définis
  NbX=FormMain->DrawGridJeu->ColCount;
  NbY=FormMain->DrawGridJeu->RowCount;
  NbPortes=NbX*NbY/PortesParCase;
  XManoir=YManoir=INDEFINIE;
  Determinisme=Agressivite;
  NbVies=NBVIESDEPART;
  Niveau=DifficulteEvaluee();
  Temps=Score=NbBords=NbFantomes=NbFantomesManges=Inactivite=0;
  ACheval=QuartNettoye=false;
  Bonus.Initialise();
  for(int i=0; i<NBDIRECTIONS*NBCOTESMANOIR; i++)
   {
    Bord[i].x=Bord[i].y=INDEFINIE;
    Bord[i].d=indefinie;
   }
  for(int i=0; i<NBMAXFANTOMES; i++)
   Fantome[i].Initialise();
  PacMan.Initialise();
  Primes.Initialise();

  c=new element*[NBX];
  for(int i=0; i<NBX; i++)
   c[i]=new element[NBY];

  Table=new unsigned char*[NBX];
  for(int i=0; i<NBX; i++)
   Table[i]=new unsigned char[NBY];

  dm=new int*[NBX];
  for(int i=0; i<NBX; i++)
   dm[i]=new int[NBY];

  // Attention, utilise NbPortes à l'allocation
  oad=new ouvadist*[NBX];
  for(int i=0; i<NBX; i++)
   oad[i]=new ouvadist[NBY];

  Porte=new porte[NbPortes];
 };
//---------------------------------------------------------------------------
void jeu::InitialiseLaby()
 {
  for(int i=0; i<NBX; i++)
   for(int j=0; j<NBY; j++)
    {
     if ((i==NBX/2)||
         (j==NBY/2)||
         (!i)||(!j)||
         (i==XMAX)||
         (j==YMAX))
      c[i][j]=vide;
     else
      c[i][j]=mur;
     Table[i][j]=SANS;
     dm[i][j]=INFINI; 
    }
 }
//---------------------------------------------------------------------------
int jeu::Environnement(const int x, const int y, const direction d)
 {
  return (CXYKD(x,y-1,1,d)==mur)+
         (CXYKD(x-1,y,1,d)==mur)+
         (CXYKD(x,y+1,1,d)==mur)+
         (CXYKD(x+1,y,1,d)==mur);
 }
//---------------------------------------------------------------------------
int jeu::EnvMinimum(const int x, const int y)
 {
  int Maxi=0;
  for(int d=0; d<NBDIRECTIONS; d++)
   {
    int Env=Environnement(x, y, (direction)d);
    if ((Env>Maxi)&&(CXYKD(x, y, 1, (direction)d)==mur)) Maxi=Env;
   }
  return (Maxi>=ENVMIN);
 }
//---------------------------------------------------------------------------
void jeu::CreeLaby(const int x, const int y, const int Plan)
 {
  int j,Env,Lg;
  direction d;
  Env=Environnement(x, y, indefinie);
  if ((Env>0)&&(EnvMinimum(x,y)))
   do
    {
     do
      {
       d=(direction)(RANDOM(NBDIRECTIONS));
       Env=Environnement(x,y,d);
      }
     while((CXYKD(x,y,1,d)<mur)||(Env<ENVMIN));
     Lg=1+RANDOM(TAILLEMAXCOULOIR);
     j=1;
     do
      {
       if (CXYKD(x,y,j,d)==mur)
        {
         if (NbCases%FrqPil<FrqPil-1)
          {
           NbCases++;
           NbPilules[Plan]++;
           c[x+j*dx[d]][y+j*dy[d]]=pilule;
          }
         else
          {
           NbCases++;
           c[x+j*dx[d]][y+j*dy[d]]=pacgum;
          }
        }
       j++;
      }
     while((j<=Lg)&&(CXYKD(x,y,j,d)==mur));
     if (j>Lg)
      CreeLaby(x+Lg*dx[d], y+Lg*dy[d], Plan);
     Env=(CXYKD(x,y-1,0,indefinie)==mur)+
         (CXYKD(x-1,y,0,indefinie)==mur)+
         (CXYKD(x,y+1,0,indefinie)==mur)+
         (CXYKD(x+1,y,0,indefinie)==mur);
    }
   while ((Env>0)&&EnvMinimum(x,y));
  if (c[x][y]==mur)
   {
    NbCases++;
    NbPilules[Plan]++;
    c[x][y]=pilule;
   }
 };
//---------------------------------------------------------------------------
void jeu::CreeLaby()
 {
  // 1. Allocation en mémoire du labyrinthe
  Initialise();
  do
   {
    int NbTotalPilules, NbEntrees[NBPLANS];
    do
     {
      // 2. Initialisation du labyrinthe (délimitation des 4 plans)
      InitialiseLaby();
      // 3. Détermination du manoir des fantômes
      do
       {
        XManoir=NBX/4+RANDOM(NBX/2);
        YManoir=NBY/4+RANDOM(NBY/2);
       }
      while(DIST(XManoir-NBX/2, YManoir-NBY/2)<NBX*NBY/RAPPORTAIREDISTMIN);
      for(int k=0; k<NBCOTESMANOIR*NBCOTESMANOIR; k++)
       c[XManoir-2+k%NBCOTESMANOIR][YManoir-2+k/NBCOTESMANOIR]=vide;
      for(int k=0; k<NBPLANS; k++)
       NbPilules[k]=0;
      NbCases=0;
      CreeLaby(1+RANDOM(NBX/2-1), 1+RANDOM((NBY-1)/2), 0);
      CreeLaby(NBX/2+1+RANDOM((NBX-1)/2), 1+RANDOM((NBY-1)/2), 1);
      CreeLaby(1+RANDOM((NBX-1)/2), NBY/2+1+RANDOM((NBY-1)/2), 2);
      CreeLaby(NBX/2+1+RANDOM((NBX-1)/2), NBY/2+1+RANDOM((NBY-1)/2), 3);
      // Calcul des critères de validité
      // 1. NbTotalPilules = 40% min. NbX*NbY
      NbTotalPilules=NbPilules[0]+NbPilules[1]+NbPilules[2]+NbPilules[3];
      // 2. Au moins une entrée pour chaque quart d'écran
      NbEntrees[nord_ouest]=NbEntrees[nord_est]=NbEntrees[sud_est]=NbEntrees[sud_ouest]=0;
      for(int x=1; x<NbX-2; x++)
       {
        if (x!=NbX/2)
		 {
		  if (x<NbX/2)
		   {
			NbEntrees[nord_ouest]+=(c[x][NbY/2-1]<mur);
			NbEntrees[sud_ouest ]+=(c[x][NbY/2+1]<mur);
		   }
		  else
		   {
			NbEntrees[nord_est]+=(c[x][NbY/2-1]<mur);
			NbEntrees[sud_est ]+=(c[x][NbY/2+1]<mur);
		   }
         }
       }
      for(int y=1; y<NbY-2; y++)
       {
        if (y!=NbY/2)
		 {
		  if (y<NbY/2)
		   {
			NbEntrees[nord_ouest]+=(c[NbX/2-1][y]<mur);
			NbEntrees[nord_est  ]+=(c[NbX/2+1][y]<mur);
		   }
		  else
		   {
			NbEntrees[sud_ouest]+=(c[NbX/2-1][y]<mur);
			NbEntrees[sud_est  ]+=(c[NbX/2+1][y]<mur);
		   }
         }
       }
     }
    while((NbTotalPilules<(4*NbX*NbY)/10)||
          (!NbEntrees[nord_ouest])||
          (!NbEntrees[nord_est])||
          (!NbEntrees[sud_ouest])||
          (!NbEntrees[sud_est]));
    // On mure le tour
    for(int i=0; i<NBX; i++)
     {
      c[i][0]=mur;
      c[i][YMAX]=mur;
     }
    for(int j=0; j<NBY; j++)
     {
      c[0][j]=mur;
      c[XMAX][j]=mur;
     }
    // On calcule le chemin au manoir avant la pose des portes
    dm[XManoir][YManoir]=0;
    CalculeDistanceAuManoir(XManoir, YManoir);

    // On pose les portes
    PosePortes();

    CalculeOuverturesADistance(); // Précalcul pour la phase Sésame
    // On place Pacman

    //GenereTraceOAD();

    PacMan.Positionne(NBX/2, NBY/2, (direction)(RANDOM(NBDIRECTIONS)));
    NbBords=0;
    for(int k=0; k<NBCOTESMANOIR; k++)
     {
      if (c[Bord[NbBords].x=k+XManoir-2][Bord[NbBords].y=YManoir-3]<mur)
       {
        Bord[NbBords].d=nord;
        Bord[NbBords].y++;
        NbBords++;
       }
      if (c[Bord[NbBords].x=k+XManoir-2][Bord[NbBords].y=YManoir+3]<mur)
       {
        Bord[NbBords].d=sud;
        Bord[NbBords].y--;
        NbBords++;
       }
      if (c[Bord[NbBords].x=XManoir-3][Bord[NbBords].y=k+YManoir-2]<mur)
       {
        Bord[NbBords].d=ouest;
        Bord[NbBords].x++;
        NbBords++;
       }
      if (c[Bord[NbBords].x=XManoir+3][Bord[NbBords].y=k+YManoir-2]<mur)
       {
        Bord[NbBords].d=est;
        Bord[NbBords].x--;
        NbBords++;
       }
     }
   }
  while(!NbBords);
}
//---------------------------------------------------------------------------
void jeu::CalculeDistanceAuManoir(int x, int y)
 {
  for(int d=nord; d<=ouest; d++)
   if ((C(x,y,d)<mur)&&
       (DM(x,y,d)>dm[x][y]+1))
     {
      DM(x,y,d)=dm[x][y]+1;
      CalculeDistanceAuManoir(x+dx[d], y+dy[d]);
     }
 }
//---------------------------------------------------------------------------
int jeu::DifficulteEvaluee()
 {
  const int CoefMax=49*6*3*4*6*3,
            CoefMin= 9*3*1*1*3*1;
  int Coef= (FormMain->DrawGridJeu->ColCount*FormMain->DrawGridJeu->RowCount/160) // x9/x16/x25/x36/x49
		   *(3*Agressivite/25) // x3/x4/x6
		   *(FrqPil/50) // x1/x2/x3
		   *(200/Vulnerabilite) // x1/x2/x4
		   *FantomesDepart // x3/x4/x5/x6
		   *(150/PortesParCase); // x1/x2/x3
  double EvalSur30=Floor(30.0*(double)log(Coef/CoefMin)/(double)log(CoefMax/CoefMin));
  if (EvalSur30>29.0) EvalSur30=29.0; // Il y a trente valeurs de 0 à 29
  int Resultat = Floor(EvalSur30); // vCX FormatFloat au lieu de Format().ToInt()
  return Resultat;
 }
//---------------------------------------------------------------------------
void jeu::DeplaceFantomes()
 {
  if ((NbFantomes<FantomesDepart)&&
      (Temps==TPSAVANTLANCERFTM*(NbFantomes+1)))
   AjouteFantome();
  else
   for(int i=0; i<NbFantomes; i++)
    Fantome[i].Deplace();
 }
//---------------------------------------------------------------------------
void jeu::Deplace()
 {
  if (!FormMain->JeuEnCours) return; // v1.1
  AnimePortes();
  PacMan.Deplace();
  DeplaceFantomes();
  Primes.Affiche();
  Bonus.Gere();
  // Test des fins de jeu possibles
  if (ACheval&&QuartNettoye)
   { // v1.1. test fin de jeu
    QuartNettoye=false;
    if (Jeu.NbPilules[0]+
        Jeu.NbPilules[1]+
        Jeu.NbPilules[2]+
        Jeu.NbPilules[3]<1)
     {
      Jeu.TermineJeu(sans_pilule);
      return;
     }
   }
  if (NbVies<0)
   {
    TermineJeu(sans_vie);
    return;
   }
  // On change de phase
  Temps++;
  ACheval^=true;
 }
//---------------------------------------------------------------------------
void jeu::IncrementeScore(int Points)
 {
  Score+=Points;
  FormMain->RedessineInfoJeu(score);
 };
//---------------------------------------------------------------------------
void jeu::IncrementeDeterminisme()
 {
  Inactivite=0;
  if (Determinisme<DETERMINISMEMAX)
   Determinisme++;
  FormMain->RedessineInfoJeu(attirance);
 }
//---------------------------------------------------------------------------
void jeu::AjouteVie()
 {
  NbVies++;
  FormMain->RedessineInfoJeu(vies);
 };
//---------------------------------------------------------------------------
void jeu::RetireVie()
 {
  NbVies--;
  FormMain->RedessineInfoJeu(vies);
 };
//---------------------------------------------------------------------------
void jeu::MangeFantome(int Num)
 {
  Fantome[Num].Etat=mange;
  IncrementeScore(PRIMEFANTOME*(++NbFantomesManges));
  Primes.Ajoute(Num, PacMan.x, PacMan.y);
  FormMain->InformeValeurElement(val_ftm);
 }
//---------------------------------------------------------------------------
void jeu::TermineJeu(fin_jeu Fin)
 {
  FormMain->TimerJeu->Enabled=false;
  FormMain->ActionPartieJouer->Enabled=false; // v1.1 Action Jouer désactivée : on laisse le Top 10 se terminer
  switch(Fin)
   {
    case sans_vie:    MsgStatut.Affiche(1, "VOUS AVEZ PERDU : VOUS N'AVEZ PLUS DE VIES;;;");
                      break;
    case sans_pilule: MsgStatut.Affiche(1, "BRAVO VOUS AVEZ GAGNE : TOUT EST BIEN NETTOYE;;;");
                      break;
   }
  FormMain->SansDemo=true;
  FormMain->JeuEnCours=false;
  Top10.TesteTop();
 }
//---------------------------------------------------------------------------
void ouvadist::Initialise()
 {
  for(int i=0; i<Jeu.NbPortes; i++)
   PosPorte[i]=NBANIMATIONSPORTE;
 }
//---------------------------------------------------------------------------
void jeu::CalculeOuvADistCase(int Num, int x, int y, int Pos)
 {
  oad[x][y].PosPorte[Num]=((Pos<0)?0:Pos);
  if (Pos<NBANIMATIONSPORTE-1)
  for(int d=nord; d<=ouest; d++)
    if (((C(x,y,d)<mur)||(PORTE(x+dx[d], y+dy[d])))&&
        (OAD(x,y,d).PosPorte[Num]>Pos+1))
     CalculeOuvADistCase(Num, x+dx[d], y+dy[d], Pos+1);
 }
//---------------------------------------------------------------------------
void jeu::CalculeOuverturesADistance()
 {
  for(int i=0; i<NbPortes; i++)
   CalculeOuvADistCase(i, Porte[i].x, Porte[i].y, -1);
 }
//---------------------------------------------------------------------------
void jeu::GenereTraceOAD()
 {
  // vCX : Utilisation de la variable %LocalAppData%
  stRepLocalAppData = InitialiseRepLocalAppData();
  //FILE *f=fopen(AnsiString(ExtractFilePath(ParamStr(0))+"\\ouadist.txt").c_str(), "wt");
  FILE *f=fopen(AnsiString(stRepLocalAppData+"\\ouadist.txt").c_str(), "wt");
  for(int i=0; i<Jeu.NbPortes; i++)
   fprintf(f, "p[%d]=(%d,%d) %c\n", i, Porte[i].x, Porte[i].y, (Porte[i].Pos/NBANIMATIONSPORTE)?'|':'-');
  for(int j=0; j<NbY; j++)
   {
    for(int kj=0; kj<3; kj++)
     {
      for(int i=0; i<NbX; i++)
       if ((c[i][j]<mur)||(PORTE(i,j)))
        fprintf(f, "%d %d %d|",
                   oad[i][j].PosPorte[3*kj+0],
                   oad[i][j].PosPorte[3*kj+1],
                   oad[i][j].PosPorte[3*kj+2]);
       else
        fprintf(f, "X X X|");
       fprintf(f, "\n");
     }
    for(int i=0; i<NbX; i++)
     fprintf(f, "------");
    fprintf(f, "\n");
   }
  fclose(f);
 }
//---------------------------------------------------------------------------
void jeu::DebloquePorte(int x, int y, blocage Blocage)
 { // v1.1
  if (VALIDE(x, y)&&PORTE(x, y))
   Jeu.Porte[Jeu.Table[x][y]].Bloquee&=tout-Blocage;
 }
//---------------------------------------------------------------------------
void jeu::BloquePorte(int x, int y, blocage Blocage)
 { // v1.1 
  if (_VALIDE(x, y)&&_PORTE(x, y))
   Jeu.Porte[Jeu.Table[x][y]].Bloquee|=Blocage;
 }
