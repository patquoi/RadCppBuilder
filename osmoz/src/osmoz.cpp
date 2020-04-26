//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("param_f.cpp", frmParametresAutomates);
USEFORM("plateau_f.cpp", frmPlateau);
USEFORM("records_f.cpp", frmRecords);
USEFORM("scores_f.cpp", frmScores);
USEFORM("apropos_f.cpp", frmAPropos);
USEFORM("dico_f.cpp", frmDico);
USEFORM("messages_f.cpp", frmMessages);
USEFORM("nomjo_f.cpp", frmNomJoueurs);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfrmPlateau), &frmPlateau);
		Application->CreateForm(__classid(TfrmScores), &frmScores);
		Application->CreateForm(__classid(TfrmMessages), &frmMessages);
		Application->CreateForm(__classid(TfrmParametresAutomates), &frmParametresAutomates);
		Application->CreateForm(__classid(TfrmRecords), &frmRecords);
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
