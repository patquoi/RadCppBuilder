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

unit defv_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls, QButtons, QExtCtrls, simul;

type
  TfrmDefVoie = class(TForm)
    Label1: TLabel;
    LabelCoordonnees: TLabel;
    RadioGroupPrioriteNord: TRadioGroup;
    RadioGroupPrioriteOuest: TRadioGroup;
    RadioGroupPrioriteEst: TRadioGroup;
    RadioGroupPrioriteSud: TRadioGroup;
    BitBtnDefFeuO: TBitBtn;
    BitBtnDefFeuE: TBitBtn;
    BitBtnDefFeuS: TBitBtn;
    ButtonOk: TButton;
    ButtonAnnuler: TButton;
    ButtonAppliquer: TButton;
    BitBtnDefFeuN: TBitBtn;
    procedure RadioGroupPrioriteClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure BitBtnDefFeuClick(Sender: TObject);
    procedure ButtonAnnulerClick(Sender: TObject);
    procedure FormHide(Sender: TObject);
    procedure ButtonOkClick(Sender: TObject);
    procedure ButtonAppliquerClick(Sender: TObject);
    procedure FormResize(Sender: TObject);
  private
    v : pVoie;
    x, y : Integer;
    procedure DefinitFeu(Dir : direction);
  public
    procedure RafraichitInfos;
    procedure AppliqueChoix;
  end;

var
  frmDefVoie: TfrmDefVoie;

implementation

uses math, simul_f, deff_f;

{$R *.xfm}

procedure TfrmDefVoie.DefinitFeu(Dir : direction);
 begin
  frmDefFeux.DirFeu:=Dir;
  frmDefFeux.x:=x;
  frmDefFeux.y:=y;
  frmDefFeux.Show;
 end;
procedure TfrmDefVoie.RadioGroupPrioriteClick(Sender: TObject);
var n : Integer;
begin
 n:=(Sender as TComponent).Tag;
 if (Sender as TRadioGroup).ItemIndex<>Integer(v.Priorites[n]) then
  case n of
   0: BitBtnDefFeuN.Enabled:=false;
   1: BitBtnDefFeuE.Enabled:=false;
   2: BitBtnDefFeuS.Enabled:=false;
   3: BitBtnDefFeuO.Enabled:=false;
  end{case n of};
end;

procedure TfrmDefVoie.RafraichitInfos;
 begin
  if frmDefFeux.Visible then frmDefFeux.Hide;
  x:=frmSimulation.DrawGridSimul.Col;
  y:=frmSimulation.DrawGridSimul.Row;
  v:=@(cv.v[x][y]);
  LabelCoordonnees.Caption:=Format('%2.2d, %2.2d', [x, y]);
  RadioGroupPrioriteNord.Enabled:=(Integer(v.DirPoss) and Integer(N)=Integer(N)) and (v.NumEtape=0);
  RadioGroupPrioriteNord.ItemIndex:=Integer(v.Priorites[Integer(nord)-1]);
  RadioGroupPrioriteEst.Enabled:=(Integer(v.DirPoss) and Integer(E)=Integer(E)) and (v.NumEtape=0);
  RadioGroupPrioriteEst.ItemIndex:=Integer(v.Priorites[Integer(est)-1]);
  RadioGroupPrioriteSud.Enabled:=(Integer(v.DirPoss) and Integer(S)=Integer(S)) and (v.NumEtape=0);
  RadioGroupPrioriteSud.ItemIndex:=Integer(v.Priorites[Integer(sud)-1]);
  RadioGroupPrioriteOuest.Enabled:=(Integer(v.DirPoss) and Integer(O)=Integer(O)) and (v.NumEtape=0);
  RadioGroupPrioriteOuest.ItemIndex:=Integer(v.Priorites[Integer(ouest)-1]);
  BitBtnDefFeuN.Enabled:=(RadioGroupPrioriteNord.ItemIndex=3);
  BitBtnDefFeuE.Enabled:=(RadioGroupPrioriteEst.ItemIndex=3);
  BitBtnDefFeuS.Enabled:=(RadioGroupPrioriteSud.ItemIndex=3);
  BitBtnDefFeuO.Enabled:=(RadioGroupPrioriteOuest.ItemIndex=3);
 end;

procedure TfrmDefVoie.FormShow(Sender: TObject);
begin
 FormResize(self);
 frmSimulation.ToolButtonMajVoie.Down:=true;
 frmSimulation.RubriquePriorites.Checked:=true;
 RafraichitInfos;
end;

procedure TfrmDefVoie.BitBtnDefFeuClick(Sender: TObject);
begin
 DefinitFeu(direction((Sender as TComponent).Tag));
end;

procedure TfrmDefVoie.ButtonAnnulerClick(Sender: TObject);
begin
 Hide;
end;

procedure TfrmDefVoie.FormHide(Sender: TObject);
begin
 if frmDefFeux.Visible then frmDefFeux.Hide;
 frmSimulation.ToolButtonMajVoie.Down:=false;
 frmSimulation.RubriquePriorites.Checked:=false;
end;

procedure TfrmDefVoie.ButtonOkClick(Sender: TObject);
begin
 AppliqueChoix;
 Hide;
end;

procedure TfrmDefVoie.ButtonAppliquerClick(Sender: TObject);
begin
 AppliqueChoix;
end;

procedure TfrmDefVoie.AppliqueChoix;
var i, j : Integer;
    RefTrv : Boolean; 
    stMsg : String;
const stFrmMsgSuppr='Le feu %s ne peut être supprimé : le feu n°%d (%d,%d) y fait référence.'#13#10;
      stFrmMsgAjout='Le feu %s ne peut être ajouté : il y a déjà %d feux.'#13#10;
      stMAJIgnoree='Modifications de priorité ignorées';
begin
  stMsg:='';
  frmSimulation.SimulModifiee:=true;
  // 1. On suprime les feux si on change de priorité (et on ferme la fiche DefFeux)
  // - Priorité Nord
  if (v.Priorites[Integer(nord)-1]=feux) and
     (RadioGroupPrioriteNord.ItemIndex<>Integer(feux)) then
   begin
    RefTrv:=false;
    i:=0;
    while (not RefTrv) and (i<cv.NbFeux) do
     begin
     if cv.Feux[i].Defini then
      begin
       j:=0; while not RefTrv and (j<cv.Feux[i].NbFeuxAtt) do
        begin RefTrv:=(cv.Feux[i].NumFeuxAtt[j]=v.NumFeu[Integer(nord)-1]); Inc(j); end;
       j:=0; while not RefTrv and (j<cv.Feux[i].NbFeuxDmd) do
        begin RefTrv:=(cv.Feux[i].NumFeuxDmd[j]=v.NumFeu[Integer(nord)-1]); Inc(j); end;
      end;
     Inc(i);
     end{while i};
    if RefTrv then
     begin
      stMsg:=stMsg+Format(stFrmMsgSuppr, [stDir[nord], i+1, cv.Feux[i].x, cv.Feux[i].y]);
      RadioGroupPrioriteNord.ItemIndex:=Integer(feux);
     end
    else
     begin
      cv.SupprimeFeu(v.NumFeu[Integer(nord)-1]-1);
      if frmDefFeux.Visible then frmDefFeux.Hide;
     end;
   end;
  // - Priorité Est
  if (v.Priorites[Integer(est)-1]=feux) and
     (RadioGroupPrioriteEst.ItemIndex<>Integer(feux)) then
   begin
    RefTrv:=false;
    i:=0;
    while (not RefTrv) and (i<cv.NbFeux) do
     begin
     if cv.Feux[i].Defini then
      begin
       j:=0; while not RefTrv and (j<cv.Feux[i].NbFeuxAtt) do
        begin RefTrv:=(cv.Feux[i].NumFeuxAtt[j]=v.NumFeu[Integer(est)-1]); Inc(j); end;
       j:=0; while not RefTrv and (j<cv.Feux[i].NbFeuxDmd) do
        begin RefTrv:=(cv.Feux[i].NumFeuxDmd[j]=v.NumFeu[Integer(est)-1]); Inc(j); end;
      end;
     Inc(i);
     end{while i};
    if RefTrv then
     begin
      stMsg:=stMsg+Format(stFrmMsgSuppr, [stDir[est], i+1, cv.Feux[i].x, cv.Feux[i].y]);
      RadioGroupPrioriteEst.ItemIndex:=Integer(feux);
     end
    else
     begin
      cv.SupprimeFeu(v.NumFeu[Integer(est)-1]-1);
      if frmDefFeux.Visible then frmDefFeux.Hide;
     end;
   end;
  // - Priorité Sud
  if (v.Priorites[Integer(sud)-1]=feux) and
     (RadioGroupPrioriteSud.ItemIndex<>Integer(feux)) then
   begin
    RefTrv:=false;
    i:=0;
    while (not RefTrv) and (i<cv.NbFeux) do
     begin
     if cv.Feux[i].Defini then
      begin
       j:=0; while not RefTrv and (j<cv.Feux[i].NbFeuxAtt) do
        begin RefTrv:=(cv.Feux[i].NumFeuxAtt[j]=v.NumFeu[Integer(sud)-1]); Inc(j); end;
       j:=0; while not RefTrv and (j<cv.Feux[i].NbFeuxDmd) do
        begin RefTrv:=(cv.Feux[i].NumFeuxDmd[j]=v.NumFeu[Integer(sud)-1]); Inc(j); end;
      end;
     Inc(i);
     end{while i};
    if RefTrv then
     begin
      stMsg:=stMsg+Format(stFrmMsgSuppr, [stDir[sud], i+1, cv.Feux[i].x, cv.Feux[i].y]);
      RadioGroupPrioriteSud.ItemIndex:=Integer(feux);
     end
    else
     begin
      cv.SupprimeFeu(v.NumFeu[Integer(sud)-1]-1);
      if frmDefFeux.Visible then frmDefFeux.Hide;
     end;
   end;
  // - Priorité Ouest
  if (v.Priorites[Integer(ouest)-1]=feux) and
     (RadioGroupPrioriteOuest.ItemIndex<>Integer(feux)) then
   begin
    RefTrv:=false;
    i:=0;
    while (not RefTrv) and (i<cv.NbFeux) do
     begin
     if cv.Feux[i].Defini then
      begin
       j:=0; while not RefTrv and (j<cv.Feux[i].NbFeuxAtt) do
        begin RefTrv:=(cv.Feux[i].NumFeuxAtt[j]=v.NumFeu[Integer(ouest)-1]); Inc(j); end;
       j:=0; while not RefTrv and (j<cv.Feux[i].NbFeuxDmd) do
        begin RefTrv:=(cv.Feux[i].NumFeuxDmd[j]=v.NumFeu[Integer(ouest)-1]); Inc(j); end;
      end;
     Inc(i);
     end{while i};
    if RefTrv then
     begin
      stMsg:=stMsg+Format(stFrmMsgSuppr, [stDir[ouest], i+1, cv.Feux[i].x, cv.Feux[i].y]);
      RadioGroupPrioriteOuest.ItemIndex:=Integer(feux);
     end
    else
     begin
      cv.SupprimeFeu(v.NumFeu[Integer(ouest)-1]-1);
      if frmDefFeux.Visible then frmDefFeux.Hide;
     end;
   end;

  // 2. On ajoute les feux

  if (v.Priorites[Integer(nord)-1]<>feux) and
     (RadioGroupPrioriteNord.ItemIndex=Integer(feux)) and
     (cv.AjouteFeu(x, y, nord)=0) then
   begin
    stMsg:=stMsg+Format(stFrmMsgAjout, [stDir[nord], cv.NbFeux]);
    RadioGroupPrioriteNord.ItemIndex:=Integer(v.Priorites[Integer(nord)-1]);
   end;
  if (v.Priorites[Integer(est)-1]<>feux) and
     (RadioGroupPrioriteEst.ItemIndex=Integer(feux)) and
     (cv.AjouteFeu(x, y, est)=0) then
   begin
    stMsg:=stMsg+Format(stFrmMsgAjout, [stDir[est], cv.NbFeux]);
    RadioGroupPrioriteEst.ItemIndex:=Integer(v.Priorites[Integer(est)-1]);
   end;
  if (v.Priorites[Integer(sud)-1]<>feux) and
     (RadioGroupPrioriteSud.ItemIndex=Integer(feux)) and
     (cv.AjouteFeu(x, y, sud)=0) then
   begin
    stMsg:=stMsg+Format(stFrmMsgAjout, [stDir[sud], cv.NbFeux]);
    RadioGroupPrioriteSud.ItemIndex:=Integer(v.Priorites[Integer(sud)-1]);
   end;
  if (v.Priorites[Integer(ouest)-1]<>feux) and
     (RadioGroupPrioriteOuest.ItemIndex=Integer(feux)) and
     (cv.AjouteFeu(x, y, ouest)=0) then
   begin
    stMsg:=stMsg+Format(stFrmMsgAjout, [stDir[ouest], cv.NbFeux]);
    RadioGroupPrioriteOuest.ItemIndex:=Integer(v.Priorites[Integer(ouest)-1]);
   end;

  if stMsg<>'' then Application.MessageBox(stMsg, stMAJIgnoree, [smbOk], smsWarning);

  // 3. On change les priorités
  v.Priorites[Integer(nord)-1]:=priorite(RadioGroupPrioriteNord.ItemIndex);
  v.Priorites[Integer(est)-1]:=priorite(RadioGroupPrioriteEst.ItemIndex);
  v.Priorites[Integer(sud)-1]:=priorite(RadioGroupPrioriteSud.ItemIndex);
  v.Priorites[Integer(ouest)-1]:=priorite(RadioGroupPrioriteOuest.ItemIndex);

  // 4. On met à jour l'accessibilité des boutons et groupes
  BitBtnDefFeuN.Enabled:=(RadioGroupPrioriteNord.ItemIndex=3);
  BitBtnDefFeuE.Enabled:=(RadioGroupPrioriteEst.ItemIndex=3);
  BitBtnDefFeuS.Enabled:=(RadioGroupPrioriteSud.ItemIndex=3);
  BitBtnDefFeuO.Enabled:=(RadioGroupPrioriteOuest.ItemIndex=3);

  // 5. On raffraichit la scène
  frmSimulation.RedessineCase(x, y, true);
end;

procedure TfrmDefVoie.FormResize(Sender: TObject);
var h, w : Integer;
begin
 LabelCoordonnees.Left:=Label1.Width+Label1.Left+7;
 w:=max(RadioGroupPrioriteEst.Left+RadioGroupPrioriteEst.Width+9,
        ButtonAppliquer.Left+ButtonAppliquer.Width+16);
 h:=max(max(ButtonOk.Height+ButtonOk.Top,
        ButtonAnnuler.Height+ButtonAnnuler.Top),
    ButtonAppliquer.Height+ButtonAppliquer.Top)+11;
 if Height<>h then Height:=h;
 if Width<>w then Width:=w;
end;

end.
