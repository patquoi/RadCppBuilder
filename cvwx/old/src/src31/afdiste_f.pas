(******************************************************************************
CENTRE-VILLE pour Linux

Copyright (C) 2001 Patrice FOUQUET

Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le
modifier conform�ment aux dispositions de la Licence Publique G�n�rale GNU,
telle que publi�e par la Free Software Foundation ; version 2 de la licence,
ou encore toute version ult�rieure.

Ce programme est distribu� dans l'espoir qu'il sera utile,
mais SANS AUCUNE GARANTIE ; sans m�me la garantie implicite de COMMERCIALISATION
ou D'ADAPTATION A UN OBJET PARTICULIER. Pour plus de d�tail,
voir la Licence Publique G�n�rale GNU.

Vous devez avoir re�u un exemplaire de la Licence Publique G�n�rale GNU en m�me
temps que ce programme ; si ce n'est pas le cas,
�crivez � la Free Software Foundation Inc.,
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

unit afdiste_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QGrids;

type
  TfrmAffDistEtapes = class(TForm)
    StringGridDistances: TStringGrid;
    procedure FormHide(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormResize(Sender: TObject);
  private
    { Private declarations }
  public
    procedure EffaceInfos;
    procedure RafraichitInfos;
  end;

var
  frmAffDistEtapes: TfrmAffDistEtapes;

implementation

uses simul_f, simul;

{$R *.xfm}

procedure TfrmAffDistEtapes.EffaceInfos;
var i, NbCol, NbLig, NbCases : Integer;
begin
 NbCol:=StringGridDistances.ColCount;
 NbLig:=StringGridDistances.RowCount;
 NbCases:=NbCol*NbLig;
 for i:=0 to NbCases-1 do
  StringGridDistances.Cells[i mod NbCol, i div NbCol]:='';
end;

procedure TfrmAffDistEtapes.RafraichitInfos;
var i, NbCases, NbX, de,
    x, y : Integer;
    v : pVoie;
begin
  x:=frmSimulation.DrawGridSimul.Col;
  y:=frmSimulation.DrawGridSimul.Row;
  v:=@(cv.v[x, y]);
  EffaceInfos;
  NbX:=1+NbDir[v.DirPoss];
  NbCases:=NbX*(1+cv.NbEtapes);
  Caption:=Format(stFormatCoord, [x, y]);
  for i:=0 to NbCases-1 do
   begin
    if i>0 then
     begin
      if i mod NbX=0 then StringGridDistances.Cells[i mod NbX, i div NbX]:=Format('%5d', [i div NbX]);
      if (i>0) and (i<NbX) then StringGridDistances.Cells[i mod NbX, i div NbX]:=stDir[Dirdp[i mod NbX-1, v.DirPoss]];
      if (i mod NbX>0) and (i>=NbX) then
       begin
       de:=v.DistEtape[i div NbX-1, i mod NbX-1];
       if de=DIST_INDEFINIE then
        StringGridDistances.Cells[i mod NbX, i div NbX]:='  N/D'
       else
        StringGridDistances.Cells[i mod NbX, i div NbX]:=Format('%5d', [de]);
       end;
     end{elsif i};
   end{for i};
end;

procedure TfrmAffDistEtapes.FormHide(Sender: TObject);
begin
 frmSimulation.ToolButtonAffDistEtapes.Down:=false;
 frmSimulation.RubriqueInfosDistancesEtapes.Checked:=false;
end;

procedure TfrmAffDistEtapes.FormShow(Sender: TObject);
begin
 FormResize(self);
 frmSimulation.ToolButtonAffDistEtapes.Down:=true;
 frmSimulation.RubriqueInfosDistancesEtapes.Checked:=true;
 StringGridDistances.RowCount:=1+cv.NbEtapes;
 if cv.NbEtapes>10 then
  Height:=213
 else
  Height:=25+21*StringGridDistances.RowCount;
  RafraichitInfos;
end;

procedure TfrmAffDistEtapes.FormResize(Sender: TObject);
var h, w : Integer;
begin
 h:=StringGridDistances.Height;
 w:=StringGridDistances.Width;
 if Height<>h then Height:=h;
 if Width<>w then Width:=w;
end;

end.
