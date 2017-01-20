//---------------------------------------------------------------------------


#pragma hdrstop

#include "dbConsign.h"
#include <vcl.h>
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
void __fastcall TDM::ServicesServiceAvailableGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
	if ( ServicesServiceAvailable->IsNull || ServicesServiceAvailable->Value == 0 ) {
			Text = "No";
	}
	else
	{
        Text = "Yes";
    }
}
//---------------------------------------------------------------------------
void __fastcall TDM::ServicesServiceAvailableSetText(TField *Sender, const UnicodeString Text)

{
	ServicesServiceAvailable->Value = 0;
	if ( Text == "Yes" ) {
			ServicesServiceAvailable->Value = 1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDM::ServicesServiceCodeSetText(TField *Sender, const UnicodeString Text)

{
	ServicesServiceCode->Value = Text.UpperCase() ;

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


			cmdUpdateHDNL->Parameters->ParamByName("hdc")->Value =
				ConsignmentItemsHDNLProductCode->AsString;
			cmdUpdateHDNL->Parameters->ParamByName("cat")->Value = cat;
			cmdUpdateHDNL->Parameters->ParamByName("opt")->Value = opt;

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

