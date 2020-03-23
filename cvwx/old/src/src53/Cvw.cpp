//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("f_simul.cpp", frmSimulation);
USEFORM("f_defvp.cpp", frmDefVoiePietons);
USEFORM("f_prmsim.cpp", frmParamSimul);
USEFORM("f_deffp.cpp", frmDefFeuxPietons);
USEFORM("f_afdistp.cpp", frmAffDistParkings);
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
USEFORM("f_afdistfp.cpp", frmAffDistFilesPark);
USEFORM("f_prmtaxi.cpp", frmParamTaxi);
USEFORM("f_afdistab.cpp", frmAffDistArretsBus);
USEFORM("f_infbus.cpp", frmInfosBus);
USEFORM("f_defn.cpp", frmDefNature);
USEFORM("f_dimzone.cpp", frmDimensionsZone);
USEFORM("f_genres.cpp", frmGeneration);
USEFORM("f_afdistft.cpp", frmAffDistFilesTaxi);
USEFORM("f_deff.cpp", frmDefFeux);
USEFORM("f_defv.cpp", frmDefVoie);
USEFORM("f_afdistpv.cpp", frmAffDistPlacesVehlib);
USEFORM("f_infvehlib.cpp", frmInfosVehlib);
USEFORM("f_prmvehlib.cpp", frmParamVehlib);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
 try
  {
     Application->Initialize();
     Application->Title = "Centre-Ville";
     //Application->HelpFile = "Cvw.hlp"; // v5.3 (HLP>HTML)
     Application->CreateForm(__classid(TfrmSimulation), &frmSimulation);
     Application->CreateForm(__classid(TfrmDefVoie), &frmDefVoie);
     Application->CreateForm(__classid(TfrmDefVoiePietons), &frmDefVoiePietons);
     Application->CreateForm(__classid(TfrmDefFeux), &frmDefFeux);
     Application->CreateForm(__classid(TfrmDefFeuxPietons), &frmDefFeuxPietons);
     Application->CreateForm(__classid(TfrmAffDistParkings), &frmAffDistParkings);
     Application->CreateForm(__classid(TfrmAffDistArretsBus), &frmAffDistArretsBus);
     Application->CreateForm(__classid(TfrmAffDistArretsTram), &frmAffDistArretsTram);
     Application->CreateForm(__classid(TfrmAffDistFilesTaxi), &frmAffDistFilesTaxi);
     Application->CreateForm(__classid(TfrmAffDistFilesPark), &frmAffDistFilesPark);
     Application->CreateForm(__classid(TfrmAffDistPlacesVehlib), &frmAffDistPlacesVehlib);
     Application->CreateForm(__classid(TfrmStatistiques), &frmStatistiques);
     Application->CreateForm(__classid(TfrmStatsVehicules), &frmStatsVehicules);
     Application->CreateForm(__classid(TfrmRecherche), &frmRecherche);
     Application->CreateForm(__classid(TfrmCarrefours), &frmCarrefours);
     Application->CreateForm(__classid(TfrmInfosVehicule), &frmInfosVehicule);
     Application->CreateForm(__classid(TfrmInfosPieton), &frmInfosPieton);
     Application->CreateForm(__classid(TfrmInfosTaxi), &frmInfosTaxi);
     Application->CreateForm(__classid(TfrmInfosTram), &frmInfosTram);
     Application->CreateForm(__classid(TfrmInfosBus), &frmInfosBus);
     Application->CreateForm(__classid(TfrmInfosVehlib), &frmInfosVehlib);
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

