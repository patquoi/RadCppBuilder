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

unit carfours_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls, QButtons;

type
  TfrmCarrefours = class(TForm)
    LabelNote: TLabel;
    GroupBox34: TGroupBox;
    SpeedButton34a1: TSpeedButton;
    SpeedButton34b1: TSpeedButton;
    SpeedButton34a2: TSpeedButton;
    SpeedButton34b2: TSpeedButton;
    SpeedButton34a3: TSpeedButton;
    SpeedButton34b3: TSpeedButton;
    GroupBox44: TGroupBox;
    SpeedButton44a: TSpeedButton;
    SpeedButton44b: TSpeedButton;
    SpeedButton44c: TSpeedButton;
    GroupBox66: TGroupBox;
    SpeedButton66a: TSpeedButton;
    SpeedButton66b: TSpeedButton;
    GroupBox43: TGroupBox;
    SpeedButton43b1: TSpeedButton;
    SpeedButton43b2: TSpeedButton;
    SpeedButton43a1: TSpeedButton;
    SpeedButton43a2: TSpeedButton;
    SpeedButton43b3: TSpeedButton;
    SpeedButton43a3: TSpeedButton;
    GroupBox88: TGroupBox;
    SpeedButton88: TSpeedButton;
    procedure SpeedButtonClick(Sender: TObject);
    procedure FormResize(Sender: TObject);
  private
  public
    procedure Active(Colonnes, Lignes : Integer);
  end;

var
  frmCarrefours: TfrmCarrefours;

// Appel de la fiche  
function Carrefours(Colonnes, Lignes : Integer) : Integer;

implementation

uses math, simul, simul_f;

{$R *.xfm}

const DirPossC4x4 : array [0..3, 0..3] of dirposs =
 ((aucune,      O,      E, aucune),
  (     S,     SO,     SE,      S),
  (     N,     NO,     NE,      N),
  (aucune,      O,      E, aucune));

      DirPossC6x6 : array [0..1, 0..5, 0..5] of dirposs =
 (((aucune, aucune,      O,      E, aucune, aucune),
   (aucune,      S,     SO,      S,      E, aucune),
   (     S,      O, aucune, aucune,     SE,      S),
   (     N,     NO, aucune, aucune,      E,      N),
   (aucune,      O,      N,     NE,      N, aucune),
   (aucune, aucune,      O,      E, aucune, aucune)),
  ((aucune, aucune,      O,      E, aucune, aucune),
   (aucune,      S,     SO,     SE,      E, aucune),
   (     S,     SO,     SO,     SE,     SE,      S),
   (     N,     NO,     NO,     NE,     NE,      N),
   (aucune,      O,     NO,     NE,      N, aucune),
   (aucune, aucune,      O,      E, aucune, aucune)));

      DirPossC8x8 : array [0..7, 0..7] of dirposs =
 ((aucune, aucune, aucune,      O,      E, aucune, aucune, aucune),
  (aucune,      S,      S,     SO,     SE,     SE,      E, aucune),
  (aucune,     SO,     SO,     SO,      S,     SE,      E, aucune),
  (     S,     SO,      O, aucune, aucune,     SE,     SE,      S),
  (     N,     NO,     NO, aucune, aucune,      E,     NE,      N),
  (aucune,      O,     NO,      N,     NE,     NE,     NE, aucune),
  (aucune,      O,     NO,     NO,     NE,      N,      N, aucune),
  (aucune, aucune, aucune,      O,      E, aucune, aucune, aucune));

      DirPossC3x4 : array [0..2, 0..3] of dirposs =
 ((     O,     SO,      O,      O),
  (     E,     SE,     NE,      E),
  (aucune,      S,      N, aucune));

      stNbFeuxLibresInsuffisant = 'Il reste moins de %d feux de libres !'#13#10'Voulez-vous augmenter le nombre de feux nécessaires ?';
      stImpossibleCreerCarrefour ='Impossible de créer le carrefour';

function Carrefours(Colonnes, Lignes : Integer) : Integer;
 begin
  frmCarrefours.Active(Colonnes, Lignes);
  Result:=frmCarrefours.ShowModal;
 end;

procedure TfrmCarrefours.Active(Colonnes, Lignes : Integer);
var i : Integer;
 begin
  for i:=0 to ComponentCount-1 do
   if Components[i].Name<>'LabelNote' then // v3.02 (version Windows)
    begin
    (Components[i] as TControl).Enabled:=
       (Components[i] is TGroupBox and
        (copy(Components[i].Name, 9, 2)=IntToStr(10*Colonnes+Lignes))) or
       (Components[i] is TSpeedButton and
        (copy(Components[i].Name, 12, 2)=IntToStr(10*Colonnes+Lignes)));
    end;
 end;

procedure TfrmCarrefours.SpeedButtonClick(Sender: TObject);
var  i, x, y, x1, y1, x2, y2, x3, y3, d1, d2, d3,
     xd, yd, xf, yf,
     mrRep,
     Dimensions, Orientation,
     TypeC : Integer;
     NumFeux : array [0..3] of Integer;
begin
 xd:=frmSimulation.DrawGridSimul.Selection.Left;
 yd:=frmSimulation.DrawGridSimul.Selection.Top;
 xf:=frmSimulation.DrawGridSimul.Selection.Right;
 yf:=frmSimulation.DrawGridSimul.Selection.Bottom;
 mrRep:=(Sender as TComponent).Tag;
 Dimensions:=mrRep div 100;
 Orientation:=(mrRep mod 100) div 10;
 TypeC:=mrRep mod 10;
 if (Dimensions<44) and (TypeC>1) and (cv.NbFeuxLibres<3) then
  begin                                          if Application.MessageBox( Format( stNbFeuxLibresInsuffisant, [3]),
                              stImpossibleCreerCarrefour,
                              [smbYes, smbNo], smsWarning, smbYes)=smbNo then
    begin
    ModalResult:=mrCancel;
    Exit;
    end
   else
    cv.DefinitNbFeux(cv.NbFeux+3-cv.NbFeuxLibres);
  end;
 if (Dimensions=44) and (TypeC>1) and (cv.NbFeuxLibres<4) then
   if Application.MessageBox( Format( stNbFeuxLibresInsuffisant, [4]),
                              stImpossibleCreerCarrefour,
                              [smbYes, smbNo], smsWarning, smbYes)=smbNo then
    begin
    ModalResult:=mrCancel;
    Exit;
    end
   else
    cv.DefinitNbFeux(cv.NbFeux+4-cv.NbFeuxLibres);
 if frmSimulation.SupprimeToutDansSelection then
  begin
   case Dimensions of
     34,
     43:  begin
          if Dimensions=34 then
           begin
            for x:=xd to xf do
             for y:=yd to yf do
              begin
               if Orientation=2 then
                cv.v[x, y].DirPoss:=RotPossDir[R90D, DirPossC3x4[xf-x, y-yd]]
               else
                cv.v[x, y].DirPoss:=RotPossDir[R90G, DirPossC3x4[x-xd, yf-y]];
               frmSimulation.RedessineCase(x,y,true);
              end;
            x1:=xd+2*(Orientation-1);
            y1:=yd+3*(Orientation-1);
            d1:=Integer(sud)-1-2*(Orientation-1);
            x2:=xd+2-2*(Orientation-1);
            y2:=yd+1+1*(Orientation-1);
            d2:=Integer(ouest)-1-2*(Orientation-1);
            x3:=xd+1;
            y3:=yd+3-3*(Orientation-1);
            d3:=Integer(nord)-1+2*(Orientation-1);
            if TypeC>1 then
             begin
             cv.v[x1, y1].Priorites[d1]:=feux;
             cv.v[x2, y2].Priorites[d2]:=feux;
             cv.v[x3, y3].Priorites[d3]:=feux;
             end
            else
             begin
             cv.v[x1, y1].Priorites[d1]:=cedez_le_passage;
             cv.v[x2, y2].Priorites[d2]:=cedez_le_passage;
             cv.v[x3, y3].Priorites[d3]:=cedez_le_passage;
             end;
           end
          else
           begin
            for x:=xd to xf do
             for y:=yd to yf do
              begin
               if Orientation=2 then
                cv.v[x, y].DirPoss:=DirPossC3x4[y-yd, x-xd]
               else
                cv.v[x, y].DirPoss:=RotPossDir[R180, DirPossC3x4[yf-y, xf-x]];
               frmSimulation.RedessineCase(x,y,true);
              end;
            x1:=xd+3*(Orientation-1);
            y1:=yd+2-2*(Orientation-1);
            d1:=Integer(est)-1+2*(Orientation-1);
            x2:=xd+1+1*(Orientation-1);
            y2:=yd+2*(Orientation-1);
            d2:=Integer(sud)-1-2*(Orientation-1);
            x3:=xd+3-3*(Orientation-1);
            y3:=yd+1;
            d3:=Integer(ouest)-1-2*(Orientation-1);
            if TypeC>1 then
             begin
             cv.v[x1, y1].Priorites[d1]:=feux;
             cv.v[x2, y2].Priorites[d2]:=feux;
             cv.v[x3, y3].Priorites[d3]:=feux;
             end
            else
             begin
             cv.v[x1, y1].Priorites[d1]:=cedez_le_passage;
             cv.v[x2, y2].Priorites[d2]:=cedez_le_passage;
             cv.v[x3, y3].Priorites[d3]:=cedez_le_passage;
             end;
           end;
          if TypeC>1 then // Avec Feux
           begin
            NumFeux[d1]:=cv.AjouteFeu(x1, y1, direction(d1+1));
            NumFeux[d2]:=cv.AjouteFeu(x2, y2, direction(d2+1));
            NumFeux[d3]:=cv.AjouteFeu(x3, y3, direction(d3+1));
            cv.Feux[NumFeux[d1]-1].AjouteFeuDmd(NumFeux[d2]);
            cv.Feux[NumFeux[d1]-1].AjouteFeuAtt(NumFeux[d2]);
            cv.Feux[NumFeux[d1]-1].Etat:=etat_feu(1+2*(TypeC mod 2));
            cv.Feux[NumFeux[d2]-1].AjouteFeuDmd(NumFeux[d1]);
            cv.Feux[NumFeux[d2]-1].AjouteFeuDmd(NumFeux[d3]);
            cv.Feux[NumFeux[d2]-1].AjouteFeuAtt(NumFeux[d1]);
            cv.Feux[NumFeux[d2]-1].AjouteFeuAtt(NumFeux[d3]);
            cv.Feux[NumFeux[d2]-1].Etat:=etat_feu(1+2*((1+TypeC) mod 2));
            cv.Feux[NumFeux[d3]-1].AjouteFeuDmd(NumFeux[d2]);
            cv.Feux[NumFeux[d3]-1].AjouteFeuAtt(NumFeux[d2]);
            cv.Feux[NumFeux[d3]-1].Etat:=etat_feu(1+2*(TypeC mod 2));
            frmSimulation.RedessineCase(x1,y1,true);
            frmSimulation.RedessineCase(x2,y2,true);
            frmSimulation.RedessineCase(x3,y3,true);
           end;
          end{34:43:};
     44: begin
         for x:=xd to xf do
          for y:=yd to yf do
           begin
            cv.v[x, y].DirPoss:=DirPossC4x4[x-xd, y-yd];
            frmSimulation.RedessineCase(x,y,true);
           end;
         if TypeC>1 then
          begin
          cv.v[xd+1, yd].Priorites[Integer(sud)-1]:=feux;
          cv.v[xd+3, yd+1].Priorites[Integer(ouest)-1]:=feux;
          cv.v[xd+2, yd+3].Priorites[Integer(nord)-1]:=feux;
          cv.v[xd, yd+2].Priorites[Integer(est)-1]:=feux;
          end
         else
          begin
          cv.v[xd+1, yd].Priorites[Integer(sud)-1]:=cedez_le_passage;
          cv.v[xd+3, yd+1].Priorites[Integer(ouest)-1]:=cedez_le_passage;
          cv.v[xd+2, yd+3].Priorites[Integer(nord)-1]:=cedez_le_passage;
          cv.v[xd, yd+2].Priorites[Integer(est)-1]:=cedez_le_passage;
          end;
         if TypeC>1 then // Avec Feux
          begin
           NumFeux[Integer(nord)-1]:=cv.AjouteFeu(xd+1, yd, sud);
           NumFeux[Integer(est)-1]:=cv.AjouteFeu(xd+3, yd+1, ouest);
           NumFeux[Integer(sud)-1]:=cv.AjouteFeu(xd+2, yd+3, nord);
           NumFeux[Integer(ouest)-1]:=cv.AjouteFeu(xd, yd+2, est);
           for i:=0 to 3 do
            begin
             cv.Feux[NumFeux[i]-1].AjouteFeuDmd(NumFeux[(i+1) mod NBDIRS]);
             cv.Feux[NumFeux[i]-1].AjouteFeuDmd(NumFeux[(i+3) mod NBDIRS]);
             cv.Feux[NumFeux[i]-1].AjouteFeuAtt(NumFeux[(i+1) mod NBDIRS]);
             cv.Feux[NumFeux[i]-1].AjouteFeuAtt(NumFeux[(i+3) mod NBDIRS]);
             cv.Feux[NumFeux[i]-1].Etat:=etat_feu(1+2*((1+TypeC+i) mod 2));
            end;
           frmSimulation.RedessineCase(xd+1,yd,true);
           frmSimulation.RedessineCase(xd+3,yd+1,true);
           frmSimulation.RedessineCase(xd+2,yd+3,true);
           frmSimulation.RedessineCase(xd,yd+2,true);
          end;
         end{44:};
     66: begin
         for x:=xd to xf do
          for y:=yd to yf do
           begin
            cv.v[x, y].DirPoss:=DirPossC6x6[TypeC-1, x-xd, y-yd];
            frmSimulation.RedessineCase(x,y,true);
           end;
         cv.v[xd+2, yd].Priorites[Integer(sud)-1]:=cedez_le_passage;
         cv.v[xd+5, yd+2].Priorites[Integer(ouest)-1]:=cedez_le_passage;
         cv.v[xd+3, yd+5].Priorites[Integer(nord)-1]:=cedez_le_passage;
         cv.v[xd, yd+3].Priorites[Integer(est)-1]:=cedez_le_passage;
         frmSimulation.RedessineCase(xd+2,yd,true);
         frmSimulation.RedessineCase(xd+5,yd+2,true);
         frmSimulation.RedessineCase(xd+3,yd+5,true);
         frmSimulation.RedessineCase(xd,yd+3,true);
         end{66:};
     88: begin
         for x:=xd to xf do
          for y:=yd to yf do
           begin
            cv.v[x, y].DirPoss:=DirPossC8x8[x-xd, y-yd];
            frmSimulation.RedessineCase(x,y,true);
           end;
         cv.v[xd+3, yd].Priorites[Integer(sud)-1]:=cedez_le_passage;
         cv.v[xd+7, yd+3].Priorites[Integer(ouest)-1]:=cedez_le_passage;
         cv.v[xd+4, yd+7].Priorites[Integer(nord)-1]:=cedez_le_passage;
         cv.v[xd, yd+4].Priorites[Integer(est)-1]:=cedez_le_passage;
         frmSimulation.RedessineCase(xd+3,yd,true);
         frmSimulation.RedessineCase(xd+7,yd+3,true);
         frmSimulation.RedessineCase(xd+4,yd+7,true);
         frmSimulation.RedessineCase(xd,yd+4,true);
         end{88:};
   end{case Dimensions of};
   ModalResult:=mrRep;
  end{if SupprimeTout...}
 else
  ModalResult:=mrCancel;
end;

procedure TfrmCarrefours.FormResize(Sender: TObject);
var h, w : Integer;
begin
 h:=Max(GroupBox88.Height+GroupBox88.Top+6,
        GroupBox43.Height+GroupBox43.Top+6);
 w:=Max(GroupBox88.Width+GroupBox88.Left+6,
    Max(GroupBox66.Width+GroupBox66.Left+6,
        GroupBox44.Width+GroupBox44.Left+6));
 if Height<>h then Height:=h;
 if Width<>w then Width:=w;
end;

end.
