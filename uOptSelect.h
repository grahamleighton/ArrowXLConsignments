//---------------------------------------------------------------------------

#ifndef uOptSelectH
#define uOptSelectH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TfrmOption : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TDBGrid *DBGrid1;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmOption(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOption *frmOption;
//---------------------------------------------------------------------------
#endif
