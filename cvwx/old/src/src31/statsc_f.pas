(******************************************************************************
CENTRE-VILLE pour Linux VERSION 2.2

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

unit statsc_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls;

type
  TfrmStatsComposition = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    LabelTotal: TLabel;
    LabelRoutes: TLabel;
    LabelEtapes: TLabel;
    LabelPriorites: TLabel;
    LabelFeux: TLabel;
    LabelClp: TLabel;
    LabelStops: TLabel;
    LabelDir: TLabel;
    LabelNord: TLabel;
    LabelEst: TLabel;
    LabelSud: TLabel;
    LabelOuest: TLabel;
    LabelTotalPC: TLabel;
    LabelRoutesPC: TLabel;
    LabelEtapesPC: TLabel;
    LabelPrioritesPC: TLabel;
    LabelFeuxPC: TLabel;
    LabelClpPC: TLabel;
    LabelStopsPC: TLabel;
    LabelDirPC: TLabel;
    LabelNordPC: TLabel;
    LabelEstPC: TLabel;
    LabelSudPC: TLabel;
    LabelOuestPC: TLabel;
    LabelEtapesMax: TLabel;
    LabelFeuxMax: TLabel;
    LabelFeuxReste: TLabel;
    LabelEtapesReste: TLabel;
    Label33: TLabel;
    Label34: TLabel;
    Label35: TLabel;
    Label36: TLabel;
    Label37: TLabel;
    Label38: TLabel;
    Label39: TLabel;
    Label40: TLabel;
    Label41: TLabel;
    Label42: TLabel;
    Label43: TLabel;
    Label44: TLabel;
    Label45: TLabel;
    Label46: TLabel;
    Label47: TLabel;
    Label48: TLabel;
    Label49: TLabel;
    Label50: TLabel;
    Label51: TLabel;
    Label52: TLabel;
    Label53: TLabel;
    Label54: TLabel;
    Label55: TLabel;
    ButtonOk: TButton;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    LabelArretsBus: TLabel;
    LabelArretsBusPC: TLabel;
    LabelArretsBusMax: TLabel;
    LabelArretsbusReste: TLabel;
    Label9: TLabel;
    procedure FormShow(Sender: TObject);
    procedure FormResize(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmStatsComposition: TfrmStatsComposition;

implementation

uses math, simul;

{$R *.xfm}

procedure TfrmStatsComposition.FormShow(Sender: TObject);
var vv : pVoie;
    i, x, y,
    Total,
    NbRoutes,
    NbPriorites,
    NbEtapes,
    NbArretsbus, // v3.0
    NbFeux,
    NbClp,
    NbStops,
    NbDirs,
    NbNord,
    NbEst,
    NbSud,
    NbOuest : Integer;
begin
 FormResize(self);
 Total:=0;
 NbRoutes:=0;
 NbPriorites:=0;
 NbEtapes:=0;
 NbArretsbus:=0; // v3.0
 NbFeux:=0;
 NbClp:=0;
 NbStops:=0;
 NbDirs:=0;
 NbNord:=0;
 NbEst:=0;
 NbSud:=0;
 NbOuest:=0;
 for i:=0 to cv.NbArretsBus-1 do // v3.0
  Inc(NbArretsbus, Ord(cv.ArretsBus[i].Defini));
 for x:=0 to NBX-1 do
  for y:=0 to NBY-1 do
   begin
    vv:=@(cv.v[x, y]);
    Inc(Total);
    Inc(NbEtapes, Ord(vv.NumEtape>0));
    if vv.DirPoss>aucune then // Route
     begin
      Inc(NbRoutes);
      Inc(NbDirs, NbDir[vv.DirPoss]);
      Inc(NbNord, Ord((Integer(vv.DirPoss) and Integer(N))>0));
      Inc(NbEst, Ord((Integer(vv.DirPoss) and Integer(E))>0));
      Inc(NbSud, Ord((Integer(vv.DirPoss) and Integer(S))>0));
      Inc(NbOuest, Ord((Integer(vv.DirPoss) and Integer(O))>0));
      for i:=0 to 3 do
       case vv.Priorites[i] of
         feux:             begin Inc(NbPriorites); Inc(NbFeux); end;
         cedez_le_passage: begin Inc(NbPriorites); Inc(NbClp); end;
         stop:             begin Inc(NbPriorites); Inc(NbStops); end;
       end{case of};
     end;
   end;
 LabelTotal.Caption:=IntToStr(Total);
 LabelRoutes.Caption:=IntToStr(NbRoutes);
 LabelRoutesPC.Caption:=Format('%6.2f', [100.0*NbRoutes/Total]);
 if NbRoutes>0 then
  begin
   LabelPriorites.Caption:=IntToStr(NbPriorites);
   LabelPrioritesPC.Caption:=Format('%6.2f', [100.0*NbPriorites/NbRoutes]);
   if NbPriorites>0 then
    begin
     LabelFeux.Caption:=IntToStr(NbFeux);
     LabelFeuxPC.Caption:=Format('%6.2f', [100.0*NbFeux/NbPriorites]);
     LabelFeuxMax.Caption:=IntToStr(cv.NbFeux);
     LabelFeuxReste.Caption:=IntToStr(cv.NbFeux-NbFeux);
     LabelClp.Caption:=IntToStr(NbClp);
     LabelClpPC.Caption:=Format('%6.2f', [100.0*NbClp/NbPriorites]);
     LabelStops.Caption:=IntToStr(NbStops);
     LabelStopsPC.Caption:=Format('%6.2f', [100.0*NbStops/NbPriorites]);
    end;
   LabelEtapes.Caption:=IntToStr(NbEtapes);
   LabelEtapesPC.Caption:=Format('%6.2f', [100.0*NbEtapes/NbRoutes]);
   LabelEtapesMax.Caption:=IntToStr(cv.NbEtapes);
   LabelEtapesReste.Caption:=IntToStr(cv.NbEtapes-NbEtapes);
   LabelDir.Caption:=IntToStr(NbDirs);
   LabelDirPC.Caption:=Format('%6.2f', [100.0*NbDirs/NbRoutes]);
   if NbDirs>0 then
    begin
     LabelNord.Caption:=IntToStr(NbNord);
     LabelNordPC.Caption:=Format('%6.2f', [100.0*NbNord/NbDirs]);
     LabelEst.Caption:=IntToStr(NbEst);
     LabelEstPC.Caption:=Format('%6.2f', [100.0*NbEst/NbDirs]);
     LabelSud.Caption:=IntToStr(NbSud);
     LabelSudPC.Caption:=Format('%6.2f', [100.0*NbSud/NbDirs]);
     LabelOuest.Caption:=IntToStr(NbOuest);
     LabelOuestPC.Caption:=Format('%6.2f', [100.0*NbOuest/NbDirs]);
    end;
  end;
 if NbArretsBus>0 then // v3.0
  begin
   LabelArretsBus.Caption:=IntToStr(NbArretsBus);
   LabelArretsBusPC.Caption:=Format('%6.2f', [100.0*NbArretsBus/NbRoutes]);
   LabelArretsBusMax.Caption:=IntToStr(cv.NbArretsBus);
   LabelArretsBusReste.Caption:=IntToStr(cv.NbArretsBus-NbArretsBus);
  end;
end;

procedure TfrmStatsComposition.FormResize(Sender: TObject);
var h, w : Integer;
begin
 h:=ButtonOk.Height+ButtonOk.Top+10;
 w:=Max( Max( Label4.Left+Label4.Width+8,
              Label7.Left+Label7.Width+14),
         Max( LabelEtapesReste.Left+LabelEtapesReste.Width+8,
              LabelFeuxReste.Left+LabelFeuxReste.Width+8));
 if Height<>h then Height:=h;
 if Width<>w then Width:=w;
end;

end.
