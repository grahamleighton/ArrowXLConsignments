//---------------------------------------------------------------------------

#ifndef uOptionSelectH
#define uOptionSelectH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TfmOptSelect : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TButton *Button1;
	TButton *Button2;
	TDBGrid *DBGrid1;
private:	// User declarations
public:		// User declarations
	__fastcall TfmOptSelect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmOptSelect *fmOptSelect;
//---------------------------------------------------------------------------
#endif
