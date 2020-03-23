//---------------------------------------------------------------------------
#include "vclx.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("f_simul.cpp", frmSimulation);
USEFORM("f_defv.cpp", frmDefVoie);
USEFORM("f_prmsim.cpp", frmParamSimul);
USEFORM("f_deff.cpp", frmDefFeux);
USEFORM("f_afdiste.cpp", frmAffDistEtapes);
USEFORM("f_afdistat.cpp", frmAffDistArretsTram);
USEFORM("f_propos.cpp", frmAPropos);
USEFORM("f_stats.cpp", frmStatistiques);
USEFORM("f_statsv.cpp", frmStatsVehicules);
USEFORM("f_infveh.cpp", frmInfosVehicule);
USEFORM("f_infptn.cpp", frmInfosPieton);
USEFORM("f_inftram.cpp", frmInfosTram);
USEFORM("f_rech.cpp", frmRecherche);
USEFORM("f_carfours.cpp", frmCarrefours);
USEFORM("f_statsc.cpp", frmStatsComposition);
USEFORM("f_statsat.cpp", frmStatsAttenteTrafic);
USEFORM("f_prmtram.cpp", frmParamTram);
USEFORM("f_prmbus.cpp", frmParamBus);
USEFORM("f_inftaxi.cpp", frmInfosTaxi);
USEFORM("f_afdistft.cpp", frmAffDistFilesTaxi);
USEFORM("f_prmtaxi.cpp", frmParamTaxi);
USEFORM("f_afdistab.cpp", frmAffDistArretsBus);
USEFORM("f_infbus.cpp", frmInfosBus);
USEFORM("f_defn.cpp", frmDefNature);
USEFORM("f_dimzone.cpp", frmDimensionsZone);
USEFORM("f_genres.cpp", frmGeneration);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
 try
  {
     Application->Initialize();
     Application->Title = "Centre-Ville";
     Application->HelpFile = "Cvw.hlp";
     Application->CreateForm(__classid(TfrmSimulation), &frmSimulation);
     Application->CreateForm(__classid(TfrmDefVoie), &frmDefVoie);
     Application->CreateForm(__classid(TfrmDefFeux), &frmDefFeux);
     Application->CreateForm(__classid(TfrmAffDistEtapes), &frmAffDistEtapes);
     Application->CreateForm(__classid(TfrmAffDistArretsBus), &frmAffDistArretsBus);
     Application->CreateForm(__classid(TfrmAffDistArretsTram), &frmAffDistArretsTram);
     Application->CreateForm(__classid(TfrmAffDistFilesTaxi), &frmAffDistFilesTaxi);
     Application->CreateForm(__classid(TfrmStatistiques), &frmStatistiques);
     Application->CreateForm(__classid(TfrmStatsVehicules), &frmStatsVehicules);
     Application->CreateForm(__classid(TfrmRecherche), &frmRecherche);
     Application->CreateForm(__classid(TfrmCarrefours), &frmCarrefours);
     Application->CreateForm(__classid(TfrmInfosVehicule), &frmInfosVehicule);
     Application->CreateForm(__classid(TfrmInfosPieton), &frmInfosPieton);
     Application->CreateForm(__classid(TfrmInfosTaxi), &frmInfosTaxi);
     Application->CreateForm(__classid(TfrmInfosTram), &frmInfosTram);
     Application->CreateForm(__classid(TfrmInfosBus), &frmInfosBus);
     Application->CreateForm(__classid(TfrmDefNature), &frmDefNature);
     Application->Run();
  }
 catch (Exception &exception)
  {
   Application->ShowException(&exception);
  }
 return 0;
}
//---------------------------------------------------------------------------

