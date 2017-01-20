//---------------------------------------------------------------------------

#ifndef uProductTypesH
#define uProductTypesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TfmProductTypes : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TDBGrid *DBGrid1;
	void __fastcall DBGrid1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfmProductTypes(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmProductTypes *fmProductTypes;
//---------------------------------------------------------------------------
#endif
