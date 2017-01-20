//---------------------------------------------------------------------------

#ifndef uNoMatchH
#define uNoMatchH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfmNoMatch : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TTimer *Timer1;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfmNoMatch(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmNoMatch *fmNoMatch;
//---------------------------------------------------------------------------
#endif
