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

program cvx31;

uses
  QForms,
  simul_f in 'simul_f.pas' {frmSimulation},
  propos_f in 'propos_f.pas' {frmAPropos},
  simul in 'simul.pas',
  prmsim_f in 'prmsim_f.pas' {frmParamSimul},
  afdiste_f in 'afdiste_f.pas' {frmAffDistEtapes},
  afdistab_f in 'afdistab_f.pas' {frmAffDistArretsBus},
  carfours_f in 'carfours_f.pas' {frmCarrefours},
  deff_f in 'deff_f.pas' {frmDefFeux},
  defv_f in 'defv_f.pas' {frmDefVoie},
  infveh_f in 'infveh_f.pas' {frmInfosVehicule},
  infbus_f in 'infbus_f.pas' {frmInfosBus},
  infptn_f in 'infptn_f.pas' {frmInfosPieton},
  rech_f in 'rech_f.pas' {frmRecherche},
  stats_f in 'stats_f.pas' {frmStatistiques},
  statsc_f in 'statsc_f.pas' {frmStatsComposition},
  statsat_f in 'statsat_f.pas' {frmStatsAttenteTrafic},
  prmbus_f in 'prmbus_f.pas' {frmParamBus};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'Centre-Ville';
  Application.CreateForm(TfrmSimulation, frmSimulation);
  Application.CreateForm(TfrmAffDistEtapes, frmAffDistEtapes);
  Application.CreateForm(TfrmAffDistArretsBus, frmAffDistArretsBus);
  Application.CreateForm(TfrmCarrefours, frmCarrefours);
  Application.CreateForm(TfrmDefFeux, frmDefFeux);
  Application.CreateForm(TfrmDefVoie, frmDefVoie);
  Application.CreateForm(TfrmInfosVehicule, frmInfosVehicule);
  Application.CreateForm(TfrmInfosBus, frmInfosBus);
  Application.CreateForm(TfrmInfosPieton, frmInfosPieton);
  Application.CreateForm(TfrmRecherche, frmRecherche);
  Application.CreateForm(TfrmStatistiques, frmStatistiques);
  Application.CreateForm(TfrmStatsComposition, frmStatsComposition);
  Application.CreateForm(TfrmStatsAttenteTrafic, frmStatsAttenteTrafic);
  Application.Run;
end.
