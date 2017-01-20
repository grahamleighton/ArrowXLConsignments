//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("uConsign.cpp", fmConsign);
USEFORM("uOptionSelect.cpp", fmOptSelect);
USEFORM("uProductTypes.cpp", fmProductTypes);
USEFORM("dbConsign.cpp", DM); /* TDataModule: File Type */
USEFORM("uNoMatch.cpp", fmNoMatch);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfmConsign), &fmConsign);
		Application->CreateForm(__classid(TDM), &DM);
		Application->CreateForm(__classid(TfmNoMatch), &fmNoMatch);
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
