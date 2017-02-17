//---------------------------------------------------------------------------


#pragma hdrstop

#include "dbConsign.h"
#include <vcl.h>
#include "uConsign.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
TDM *DM;
//---------------------------------------------------------------------------
__fastcall TDM::TDM(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDM::ConsignmentItemsBeforeInsert(TDataSet *DataSet)
{
	ConsignmentItemsConsignmentID->Value =
		ConsignmentsConsignmentID->Value;
}
//---------------------------------------------------------------------------

void __fastcall TDM::ConsignmentItemsAfterPost(TDataSet *DataSet)
{
	if ( ! ConsignmentItemsHDNLProductCode->IsNull ) {
		if (! ConsignmentItemsClientProductCode->IsNull   ) {
			UnicodeString opt = ConsignmentItemsClientProductCode->Text.Trim();

			if ( opt.Length() > 2) {
				opt = opt.SubString(opt.Length()-1,2);
			}

			UnicodeString cat = ConsignmentItemsClientProductCode->Text.Trim();

			if ( cat.Length() > 6) {
				cat = cat.SubString(1,6);
			}


			cmdUpdateHDNL->Parameters->ParamByName("@hdc")->Value =
				ConsignmentItemsHDNLProductCode->AsString;
			cmdUpdateHDNL->Parameters->ParamByName("@cat")->Value = cat;
			cmdUpdateHDNL->Parameters->ParamByName("@opt")->Value = opt;

			cmdUpdateHDNL->Execute();


		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TDM::ConsignmentsNewRecord(TDataSet *DataSet)
{
	ConsignmentsWarehouseCode->AsAnsiString = "M";

}
//---------------------------------------------------------------------------


void __fastcall TDM::ConsignmentsViewAfterPost(TDataSet *DataSet)
{
	if ( Consignments->Active) {
		TBookmark bmk = Consignments->GetBookmark() ;

		Consignments->Requery();
		Consignments->GotoBookmark(bmk);
	}
}
//---------------------------------------------------------------------------

void __fastcall TDM::ConsignmentsAfterScroll(TDataSet *DataSet)
{
	fmConsign->Image3->Visible = false;
	fmConsign->Image2->Visible = false;


}
//---------------------------------------------------------------------------

