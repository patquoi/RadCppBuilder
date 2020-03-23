(******************************************************************************
CENTRE-VILLE pour Linux

Copyright (C) 2001 Patrice FOUQUET

Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le
modifier conformément aux dispositions de la Licence Publique Générale GNU,
telle que publiée par la Free Software Foundation ; version 2 de la licence,
ou encore toute version ultérieure.

Ce programme est distribué dans l'espoir qu'il sera utile,
mais SANS AUCUNE GARANTIE ; sans même la garantie implicite de COMMERCIALISATION
ou D'ADAPTATION A UN OBJET PARTICULIER. Pour plus de détail,
voir la Licence Publique Générale GNU.

Vous devez avoir reçu un exemplaire de la Licence Publique Générale GNU en même
temps que ce programme ; si ce n'est pas le cas,
écrivez à la Free Software Foundation Inc.,
675 Mass Ave, Cambridge, MA 02139, Etats-Unis.

Pour toutes informations:
mailto:fouquetp@francenet.fr
http://persoweb.francenet.fr/~fouquetp

-------------------------------------------------------------------------------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************)

unit deff_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls, QExtCtrls, QButtons, simul, QComCtrls;

type
  TfrmDefFeux = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    LabelCoordonnees: TLabel;
    LabelDirection: TLabel;
    LabelNumero: TLabel;
    RadioGroupEtat: TRadioGroup;
    RadioGroupTypeDmdVert: TRadioGroup;
    Label4: TLabel;
    LabelNbFeuxAtt: TLabel;
    SpeedButtonSelFeuxAtt: TSpeedButton;
    CheckBoxDemandeVert: TCheckBox;
    RadioGroupTypePsgRouge: TRadioGroup;
    Label5: TLabel;
    LabelNbFeuxDmd: TLabel;
    SpeedButtonSelFeuxDmd: TSpeedButton;
    CheckBoxRougeDemande: TCheckBox;
    GroupBoxDureeFeu: TGroupBox;
    Label6: TLabel;
    Label7: TLabel;
    ButtonOk: TButton;
    ButtonAnnuler: TButton;
    ButtonAppliquer: TButton;
    SpinEditDureeVert: TSpinEdit;
    SpinEditDureeRouge: TSpinEdit;
    StatusBar: TStatusBar;
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormHide(Sender: TObject);
    procedure ButtonOkClick(Sender: TObject);
    procedure ButtonAnnulerClick(Sender: TObject);
    procedure ButtonAppliquerClick(Sender: TObject);
    procedure RadioGroupEtatClick(Sender: TObject);
    procedure SpeedButtonSelFeuxDmdClick(Sender: TObject);
    procedure SpeedButtonSelFeuxAttClick(Sender: TObject);
    procedure FormResize(Sender: TObject);
  private
    Numero : Integer;
    f : pFeu;
    v : pVoie;
  public
    x, y,
    NbFeuxDmd, // Nbre de feux demandant le rouge
    NbFeuxAtt : Integer;// Nbre de feux devant être rouge pour que Numero passe au vert
    NumFeuxAtt, // Liste des feux devant être rouge pour que Numero passe au vert
    NumFeuxDmd : array of Integer; // Liste des feux demandant le rouge
    DirFeu : direction;
    procedure ControleDemandeEtPassage;
    function RafraichitInfos : Boolean;
    function AppliqueChoix : Boolean;
    procedure RafraichitInfosFeuxDmd;
    procedure RafraichitInfosFeuxAtt;
  end;

var
  frmDefFeux: TfrmDefFeux;

implementation

uses math, simul_f;

{$R *.xfm}

procedure TfrmDefFeux.FormCreate(Sender: TObject);
begin
  NbFeuxDmd:=0;
  NbFeuxAtt:=0;
end;

procedure TfrmDefFeux.ControleDemandeEtPassage;
 begin
  case RadioGroupEtat.ItemIndex of
    Integer(vert):  begin
                    CheckBoxDemandeVert.Checked:=false;
                    CheckBoxDemandeVert.Enabled:=false;
                    CheckBoxRougeDemande.Enabled:=true;
                    end;
    Integer(rouge): begin
                    CheckBoxRougeDemande.Checked:=false;
                    CheckBoxRougeDemande.Enabled:=false;
                    CheckBoxDemandeVert.Enabled:=true;
                    end;
  else
    begin
    CheckBoxDemandeVert.Enabled:=false;
    CheckBoxRougeDemande.Enabled:=false;
    end;
  end{case of};
 end;

function TfrmDefFeux.RafraichitInfos : Boolean;
var i : Integer;
    stSitFeux : String;
 begin
  v:=@(cv.v[x, y]);
  Numero:=v.NumFeu[Integer(DirFeu)-1];
  if Numero=0 then
   begin
   Numero:=cv.AjouteFeu(x, y, DirFeu);
   if Numero=0 then
    begin
     Application.MessageBox('Vous ne pouvez plus ajouter de feu :'#13#10'vous avez déjà atteint le nombre maximum. Augmentez le nombre de feux dans les paramètres.', 'Modifications impossibles', [smbOk], smsWarning);
     Result:=false;
     Exit;
    end
   else
    v.NumFeu[Integer(DirFeu)-1]:=Numero;
   end{if Numero=0};
  f:=@(cv.Feux[Numero-1]);
  LabelCoordonnees.Caption:=Format('%2.2d, %2.2d', [x, y]);
  LabelDirection.Caption:=stDir[DirFeu];
  if Numero>0 then LabelNumero.Caption:=IntToStr(Numero);
  RadioGroupEtat.ItemIndex:=Integer(f.Etat);
  RadioGroupTypeDmdVert.ItemIndex:=Integer(f.TypeDmdVert);
  CheckBoxDemandeVert.Checked:=f.DemandeVert;
  RadioGroupTypePsgRouge.ItemIndex:=Integer(f.TypePsgRouge);
  CheckBoxRougeDemande.Checked:=f.RougeDemande;
  CheckBoxDemandeVert.Enabled:=(f.Etat=rouge);
  CheckBoxRougeDemande.Enabled:=(f.Etat=vert);
  SpinEditDureeVert.Value:=f.DureeVert;
  SpinEditDureeRouge.Value:=f.DureeRouge;

  // Copie des listes de feux
  NbFeuxDmd:=f.NbFeuxDmd;
  NbFeuxAtt:=f.NbFeuxAtt;
  SetLength(NumFeuxDmd, NbFeuxDmd*sizeof(Integer));
  SetLength(NumFeuxAtt, NbFeuxAtt*sizeof(Integer));
  stSitFeux:='Dmd={';
  for i:=0 to NbFeuxDmd-1 do
   begin
   NumFeuxDmd[i]:=f.NumFeuxDmd[i];
   stSitFeux:=stSitFeux+Format('n°%d(%d,%d) ', [ NumFeuxDmd[i],
                                               cv.Feux[NumFeuxDmd[i]-1].x,
                                               cv.Feux[NumFeuxDmd[i]-1].y]);
   end;
  stSitFeux:=stSitFeux+'} Att={';
  for i:=0 to NbFeuxAtt-1 do
   begin
   NumFeuxAtt[i]:=f.NumFeuxAtt[i];
   stSitFeux:=stSitFeux+Format('n°%d(%d,%d) ', [ NumFeuxAtt[i],
                                               cv.Feux[NumFeuxAtt[i]-1].x,
                                               cv.Feux[NumFeuxAtt[i]-1].y]);
   end;
  stSitFeux:=stSitFeux+'}';
  StatusBar.SimpleText:=stSitFeux;
  // Affichage du nombre de feux de chaque liste
  LabelNbFeuxDmd.Caption:=IntToStr(NbFeuxDmd);
  LabelNbFeuxAtt.Caption:=IntToStr(NbFeuxAtt);
  Result:=true;
 end;

function TfrmDefFeux.AppliqueChoix : Boolean;
var i : Integer;
 begin
  frmSimulation.SimulModifiee:=true;
  ControleDemandeEtPassage;
  f.Etat:=etat_feu(RadioGroupEtat.ItemIndex);
  f.TypeDmdVert:=dmd_vert(RadioGroupTypeDmdVert.ItemIndex);
  f.DemandeVert:=CheckBoxDemandeVert.Checked;
  f.TypePsgRouge:=psg_rouge(RadioGroupTypePsgRouge.ItemIndex);
  f.RougeDemande:=CheckBoxRougeDemande.Checked;
  f.DureeVert:=SpinEditDureeVert.Value;
  f.DureeRouge:=SpinEditDureeRouge.Value;

  // Copie des listes de feux
  f.DefinitNbFeuxDmd(NbFeuxDmd);
  f.DefinitNbFeuxAtt(NbFeuxAtt);
  for i:=0 to NbFeuxDmd-1 do f.NumFeuxDmd[i]:=NumFeuxDmd[i];
  for i:=0 to NbFeuxAtt-1 do f.NumFeuxAtt[i]:=NumFeuxAtt[i];
  frmSimulation.RedessineCase(x, y, true);
  Result:=true;
 end;

procedure TfrmDefFeux.RafraichitInfosFeuxDmd;
 begin
  LabelNbFeuxDmd.Caption:=IntToStr(NbFeuxDmd);
 end;

procedure TfrmDefFeux.RafraichitInfosFeuxAtt;
 begin
  LabelNbFeuxAtt.Caption:=IntToStr(NbFeuxAtt);
 end;

procedure TfrmDefFeux.FormShow(Sender: TObject);
begin
 FormResize(self);
 if not RafraichitInfos then Hide else frmSimulation.RedessineCase(x, y, true);
end;


procedure TfrmDefFeux.FormHide(Sender: TObject);
var i : Integer;
begin
 frmSimulation.ToolButtonMajVoie.Enabled:=true;
 frmSimulation.RubriquePriorites.Enabled:=true;
 SpeedButtonSelFeuxDmd.Down:=false;
 SpeedButtonSelFeuxAtt.Down:=false;
 if frmSimulation.SelectionFeuxDmd then
  for i:=0 to NbFeuxDmd-1 do
   frmSimulation.RedessineCase(cv.Feux[NumFeuxDmd[i]-1].x, cv.Feux[NumFeuxDmd[i]-1].y, true);
 if frmSimulation.SelectionFeuxAtt then
  for i:=0 to NbFeuxAtt-1 do
   frmSimulation.RedessineCase(cv.Feux[NumFeuxAtt[i]-1].x, cv.Feux[NumFeuxAtt[i]-1].y, true);
 frmSimulation.SelectionFeuxDmd:=false;
 frmSimulation.SelectionFeuxAtt:=false;
 frmSimulation.RedessineCase(x, y, true);
end;

procedure TfrmDefFeux.ButtonOkClick(Sender: TObject);
begin
 AppliqueChoix;
 Hide;
end;

procedure TfrmDefFeux.ButtonAnnulerClick(Sender: TObject);
begin
 Hide;
end;


procedure TfrmDefFeux.ButtonAppliquerClick(Sender: TObject);
begin
 if not AppliqueChoix then Hide;
end;

procedure TfrmDefFeux.RadioGroupEtatClick(Sender: TObject);
begin
 ControleDemandeEtPassage;
end;


procedure TfrmDefFeux.SpeedButtonSelFeuxDmdClick(Sender: TObject);
var i : Integer;
begin
 frmSimulation.SelectionFeuxDmd:=frmSimulation.SelectionFeuxDmd xor true;
 SpeedButtonSelFeuxAtt.Enabled:=not frmSimulation.SelectionFeuxDmd;
 for i:=0 to NbFeuxDmd-1 do
  frmSimulation.RedessineCase(cv.Feux[NumFeuxDmd[i]-1].x, cv.Feux[NumFeuxDmd[i]-1].y, true);
 frmSimulation.RedessineCase(frmSimulation.DrawGridSimul.Col, frmSimulation.DrawGridSimul.Row, true);
 frmSimulation.ToolButtonMajVoie.Enabled:=not (frmSimulation.SelectionFeuxDmd or frmSimulation.SelectionFeuxAtt);
 frmSimulation.RubriquePriorites.Enabled:=frmSimulation.ToolButtonMajVoie.Enabled;
end;


procedure TfrmDefFeux.SpeedButtonSelFeuxAttClick(Sender: TObject);
var i : Integer;
begin
 frmSimulation.SelectionFeuxAtt:=frmSimulation.SelectionFeuxAtt xor true;
 SpeedButtonSelFeuxDmd.Enabled:=not frmSimulation.SelectionFeuxAtt;
 for i:=0 to NbFeuxAtt-1 do
  frmSimulation.RedessineCase(cv.Feux[NumFeuxAtt[i]-1].x, cv.Feux[NumFeuxAtt[i]-1].y, true);
 frmSimulation.RedessineCase(frmSimulation.DrawGridSimul.Col, frmSimulation.DrawGridSimul.Row, true);
 frmSimulation.ToolButtonMajVoie.Enabled:=not (frmSimulation.SelectionFeuxDmd or frmSimulation.SelectionFeuxAtt);
 frmSimulation.RubriquePriorites.Enabled:=frmSimulation.ToolButtonMajVoie.Enabled;
end;

procedure TfrmDefFeux.FormResize(Sender: TObject);
var h, w : Integer;
begin
 w:=max(max(LabelNumero.Width+LabelNumero.Left,
            max(CheckBoxDemandeVert.Width+
                CheckBoxDemandeVert.Left,
                CheckBoxRougeDemande.Width+
                CheckBoxRougeDemande.Left)),
        max(max(RadioGroupTypeDmdVert.Width+
                RadioGroupTypeDmdVert.Left,
                RadioGroupTypePsgRouge.Width+
                RadioGroupTypePsgRouge.Left),
            RadioGroupEtat.Width+RadioGroupEtat.Left))+6;
 h:=StatusBar.Height+11+
    max(max(ButtonOk.Height+ButtonOk.Top,
            ButtonAnnuler.Height+ButtonAnnuler.Top),
        ButtonAppliquer.Height+ButtonAppliquer.Top);
 if Height<>h then Height:=h;
 if Width<>w then Width:=w;
end;

end.
