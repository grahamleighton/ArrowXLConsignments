//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uProductTypes.h"
#include "dbConsign.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmProductTypes *fmProductTypes;
//---------------------------------------------------------------------------
__fastcall TfmProductTypes::TfmProductTypes(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmProductTypes::DBGrid1DblClick(TObject *Sender)
{
	Button1->Click();
}
//---------------------------------------------------------------------------

