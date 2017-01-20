//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uNoMatch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmNoMatch *fmNoMatch;
//---------------------------------------------------------------------------
__fastcall TfmNoMatch::TfmNoMatch(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmNoMatch::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false;
	ModalResult = mrOk;

	Close();

}
//---------------------------------------------------------------------------
void __fastcall TfmNoMatch::FormShow(TObject *Sender)
{
	Timer1->Enabled = true;

}
//---------------------------------------------------------------------------
