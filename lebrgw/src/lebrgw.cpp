//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("prmniv_f.cpp", frmPrmNiveau);
USEFORM("plt_f.cpp", frmPlateau);
USEFORM("nomjou_f.cpp", frmNomJoueur);
USEFORM("prt_f.cpp", frmParties);
USEFORM("score_f.cpp", frmScore);
USEFORM("records_f.cpp", frmRecords);
USEFORM("avertissement_f.cpp", frmAvertissement);
USEFORM("apropos_f.cpp", frmAPropos);
USEFORM("comm_f.cpp", frmCommandes);
USEFORM("diplome_f.cpp", frmDiplome);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = "Le berger";
		Application->CreateForm(__classid(TfrmPlateau), &frmPlateau);
		Application->CreateForm(__classid(TfrmPrmNiveau), &frmPrmNiveau);
		Application->CreateForm(__classid(TfrmParties), &frmParties);
		Application->CreateForm(__classid(TfrmNomJoueur), &frmNomJoueur);
		Application->CreateForm(__classid(TfrmAvertissement), &frmAvertissement);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
