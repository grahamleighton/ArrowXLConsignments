//---------------------------------------------------------------------------

#include <vcl.h>
#include <dateutils.hpp>

#pragma hdrstop

#include "uConsign.h"
#include "dbConsign.h"
#include "uOptSelect.h"
#include "uOptionSelect.h"
#include "uProductTypes.h"
#include "uNoMatch.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmConsign *fmConsign;

const int SELECTION_ALL     = 0;
const int SELECTION_NONE    = 1;
const int SELECTION_INVERT  = 2;

bool CheckedOK = false;

UnicodeString LoggedInUser = "";

UnicodeString CurrentMPIFilter = "";
UnicodeString DedicatedWarehouse = "";
UnicodeString DedicatedMPI = "";
int DedicatedServiceCode = 0;
int AddMode = 0;


#define CHEAT 1



//---------------------------------------------------------------------------
__fastcall TfmConsign::TfmConsign(TComponent* Owner)
	: TForm(Owner)
{
	if ( ParamCount() > 0 ) {
		int ac = 0;
		while ( ac < ParamCount() )
			{
				AnsiString xx =  ParamStr(ac);
				if ( ParamStr(ac).UpperCase().Trim() == "-W" )  {
					DedicatedWarehouse = ParamStr(ac+1).UpperCase().Trim();
				}
				ac++;
			}
	}

	if ( ! DedicatedWarehouse.IsEmpty() ) {
		tabSuppliers->TabVisible = false;
		tabServices->TabVisible = false;

		pnlTop->Caption = "     Consignments - " + DedicatedWarehouse ;


	}
}
//---------------------------------------------------------------------------
void __fastcall TfmConsign::tabServicesShow(TObject *Sender)
{
	if ( ! DM->SuppServices->Active ) {
		DM->SuppServices->Open() ;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmConsign::tabConsignmentShow(TObject *Sender)
{
	if ( ! DM->Services->Active ) {
		DM->Services->Open() ;
	}


	if ( ! DM->SupplierServices->Active ) {
		DM->SupplierServices->Open() ;
	}

	if ( ! DM->Consignments->Active ) {
		DM->Consignments->Open() ;
	}
	if ( ! DM->ConsignmentItems->Active ) {
		DM->ConsignmentItems->Open() ;
	}

	if ( ! DM->ProductTypes->Active ) {
		DM->ProductTypes->Open() ;
	}

	dbGridItems->Columns->Items[3]->PickList->Clear();
	DM->ProductTypes->Open() ;
	while ( ! DM->ProductTypes->Eof  )
		{

			dbGridItems->Columns->Items[3]->PickList->Add(DM->ProductTypesProductType->AsString + " " + DM->ProductTypesDescription->AsString  );
			DM->ProductTypes->Next() ;
		}
	DM->ProductTypes->First();

	if ( ! DedicatedWarehouse.IsEmpty()) {
		DM->SupplierServices->Filter = "[SupplierName]='" + DedicatedWarehouse + "'";
		DM->SupplierServices->Filtered = true;
		DM->SupplierServices->First();
		if ( DM->SupplierServices->Eof ) {
			DM->SupplierServices->Filtered = false;
			DM->SupplierServices->Filter = "";

		}

	}




}
//---------------------------------------------------------------------------
void __fastcall TfmConsign::txtBarcodeLookupKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if ( Key == 13 ) {
		txtBarcodeLookup->Text = txtBarcodeLookup->Text.Trim() ;
		if ( txtBarcodeLookup->Text.Length() != 16) {
			MessageDlg ( "Must be 16 digit number" , mtWarning , TMsgDlgButtons() << mbOK , 0 );
			txtBarcodeLookup->SetFocus();
			return;
		}

/*
		int ni = 0;
		while ( ni < 16 )
		{
			if ( txtBarcodeLookup->Text[ni+1] < '0' ||
				txtBarcodeLookup->Text[ni+1] > '9' ) {
				MessageDlg ( "Must be parcel barcode 16 digit numeric entry" , mtWarning , TMsgDlgButtons() << mbOK , 0 );
				txtBarcodeLookup->SetFocus();
				return;

			}
			ni++;
		}
*/

			if ( CreateConsignmentFrom(txtBarcodeLookup->Text) )
			{
				Memo1->Lines->Insert(0,Now().FormatString("yyyy-mm-dd hh:nn:ss") + " Match Found for " + DM->ConsignmentsRecipientName->AsString + " on barcode " + txtBarcodeLookup->Text );
				pnlConsignMain->Color = clGreen;
				Application->ProcessMessages();
				Timer2->Enabled = true;
			}
			else
			{
				Memo1->Lines->Insert(0,Now().FormatString("yyyy-mm-dd hh:nn:ss") + " No Match Found for barcode " + txtBarcodeLookup->Text  );

				pnlConsignMain->Color = clRed;
				Application->ProcessMessages();
				Timer2->Enabled = true;

			}

		   txtBarcodeLookup->Text = "";

		   Button7->Click() ;


	}
}
//---------------------------------------------------------------------------


void __fastcall TfmConsign::txtItemSearchKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if ( Key == 13 ) {


		Screen->Cursor = crHourGlass ;

		try
		{

		if ( DM->ItemLookup->Active )
			DM->ItemLookup->Close();



		DM->ItemLookup->Parameters->ParamByName("cat")->Value =
			txtItemSearch->Text ;
		DM->ItemLookup->Parameters->ParamByName("cat2")->Value = "%" +
			txtItemSearch->Text + "%";


		DM->ItemLookup->Open();

		int mr = 0;
		if ( DM->ItemLookup->RecordCount > 1) {
			TfmOptSelect *fm = new TfmOptSelect(Application);


			mr = fm->ShowModal() ;

			delete fm;
		}
		else
			mr = mrOk;






		if ( mr == mrOk && ! DM->ItemLookup->Eof  ) {



				DM->ConsignmentItems->Insert() ;

				DM->ConsignmentItemsClientProductCode->Value
					= DM->ItemLookupCat->AsString.Trim() + "/" + DM->ItemLookupOpt->AsString.Trim();
				DM->ConsignmentItemsClientProductDescription->Value
					= DM->ItemLookupDescription->Value;
				DM->ConsignmentItemsConsignmentID->Value =
					DM->ConsignmentsConsignmentID->Value;
				DM->ConsignmentItemsWeight->Value =
					DM->ItemLookupWeight->Value;
				DM->ConsignmentItemsDimX->Value =
					DM->ItemLookupDim1->Value;
				DM->ConsignmentItemsDimY->Value =
					DM->ItemLookupDim2->Value;
				DM->ConsignmentItemsDimZ->Value =
					DM->ItemLookupDim3->Value;

				if ( ! DM->ItemLookupHDNLCode->IsNull ) {
					DM->ConsignmentItemsHDNLProductCode->Value
						= DM->ItemLookupHDNLCode->Value ;
				}
				else
					MessageDlg ( "Select HDNL code"  , mtInformation , TMsgDlgButtons() << mbOK , 0 );


				DM->ConsignmentItems->Post() ;

				if ( ! DM->ItemLookupDD1Dim1->IsNull && DM->ItemLookupDD1Dim1->AsInteger > 0  ) {

					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
					= DM->ItemLookupCat->AsString.Trim() + "/" + DM->ItemLookupOpt->AsString.Trim();
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->ItemLookupDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->ItemLookupDD1Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->ItemLookupDD1Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->ItemLookupDD1Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->ItemLookupDD1Dim3->Value;

					if ( ! DM->ItemLookupHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->ItemLookupHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;

				}
				if ( ! DM->ItemLookupDD2Dim1->IsNull && DM->ItemLookupDD2Dim1->AsInteger > 0  ) {

					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
					= DM->ItemLookupCat->AsString.Trim() + "/" + DM->ItemLookupOpt->AsString.Trim();
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->ItemLookupDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->ItemLookupDD2Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->ItemLookupDD2Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->ItemLookupDD2Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->ItemLookupDD2Dim3->Value;

					if ( ! DM->ItemLookupHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->ItemLookupHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;

				}

				if ( ! DM->ItemLookupDD3Dim1->IsNull && DM->ItemLookupDD3Dim1->AsInteger > 0  ) {

					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
					= DM->ItemLookupCat->AsString.Trim() + "/" + DM->ItemLookupOpt->AsString.Trim();
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->ItemLookupDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->ItemLookupDD3Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->ItemLookupDD3Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->ItemLookupDD3Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->ItemLookupDD3Dim3->Value;

					if ( ! DM->ItemLookupHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->ItemLookupHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;

				}

				if ( ! DM->ItemLookupDD4Dim1->IsNull && DM->ItemLookupDD4Dim1->AsInteger > 0  ) {

					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
					= DM->ItemLookupCat->AsString.Trim() + "/" + DM->ItemLookupOpt->AsString.Trim();
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->ItemLookupDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->ItemLookupDD4Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->ItemLookupDD4Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->ItemLookupDD4Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->ItemLookupDD4Dim3->Value;

					if ( ! DM->ItemLookupHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->ItemLookupHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;

				}


		}



		}

		catch(Exception &E)
		{
			MessageDlg ( "Error while searching for matching items against [" + txtItemSearch->Text + "]\n\n" + E.Message
				, mtError
				, TMsgDlgButtons() << mbOK
				, 0 );
		}
		txtItemSearch->Text = "";


		Screen->Cursor = crArrow ;










	}
}
//---------------------------------------------------------------------------



void __fastcall TfmConsign::DBGrid2DblClick(TObject *Sender)
{
	tabConsignment->Show() ;
	AnsiString viewSQL = DM->Consignments->SQL->Text;

	if ( ! DM->Consignments->Locate("ConsignmentID",DM->ConsignmentsViewConsignmentID->AsInteger , TLocateOptions() ) )
	{
		DM->Consignments->Requery();
		DM->ConsignmentItems->Requery();
		DM->Consignments->Locate("ConsignmentID",DM->ConsignmentsViewConsignmentID->AsInteger , TLocateOptions() );


	}

}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::tabConsignmentsShow(TObject *Sender)
{
//	if ( ! DM->ConsignmentsView->Active ) {
//		DM->ConsignmentsView->Open() ;
		DM->DSVSuppliers->Open() ;

		if ( ! DedicatedWarehouse.IsEmpty()  ) {
			DM->DSVSuppliers->Filter = "[SupplierName]='" + DedicatedWarehouse + "'";
			DM->DSVSuppliers->Filtered = true;

			DedicatedMPI = DM->DSVSuppliersMetapackIndicator->AsString;

		}

		UpdateConsignmentView(Sender);
//	}
}
//---------------------------------------------------------------------------


void __fastcall TfmConsign::rgpSelectionClick(TObject *Sender)
{
	switch ( rgpSelection->ItemIndex  ) {
		case SELECTION_NONE :
		{
			DBGrid2->SelectedRows->Clear() ;
			DM->ConsignmentsView->First();


			break;
		}
		case SELECTION_ALL :
		{

			DM->ConsignmentsView->First();
			while ( ! DM->ConsignmentsView->Eof )
				{
					DBGrid2->SelectedRows->CurrentRowSelected = true;
					DM->ConsignmentsView->Next();
				}
			break;

		}
		case SELECTION_INVERT  :
		{
			DM->ConsignmentsView->First();
			while ( ! DM->ConsignmentsView->Eof )
				{
					DBGrid2->SelectedRows->CurrentRowSelected =
						! DBGrid2->SelectedRows->CurrentRowSelected;
					DM->ConsignmentsView->Next();
				}
			break;
			DM->ConsignmentsView->First();

			break;
		}
	default:
		;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfmConsign::cbxInvertSelectionClick(TObject *Sender)
{
	DM->ConsignmentsView->First();
			while ( ! DM->ConsignmentsView->Eof )
				{
					DBGrid2->SelectedRows->CurrentRowSelected =
						! DBGrid2->SelectedRows->CurrentRowSelected;
					DM->ConsignmentsView->Next();
				}

			DM->ConsignmentsView->First();
}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::actCreateCSVExecute(TObject *Sender)
{
	// main CSV creation routine



	CheckedOK = false;
	try
	{
		TBookmark bm = DM->ConsignmentsView->GetBookmark() ;

		DM->ConsignmentsView->Requery();

		DM->ConsignmentsView->GotoBookmark(bm);
	}
	catch(...)
	{

	}


	if ( DBGrid2->SelectedRows->Count == 0 ) {
		if ( MessageDlg ( "No items selected , do you want to process them all ?" , mtConfirmation , TMsgDlgButtons() << mbYes << mbNo , 0 ) == mrNo )
		{
			return;
		}

		rgpSelection->ItemIndex = SELECTION_ALL ;

	}
	AnsiString warehousecode = "";

	int i = 0;
	StatusBar1->Panels->Items[0]->Text = "Creating CSV for selected consignments...";
	Application->ProcessMessages();

	TADOQuery *Q = DM->ConsignmentsView ;
	TStringList *csv = new TStringList();
	csv->Clear();

	csv->Add ("Warehouse Code,Customer Reference,Parcel Sequence Nbr,Recipient Name,Recipient Address1,Recipient Address2,Recipient Address3,Recipient Address4,Recipient Postcode,Delivery Instructions,Weight,Dimension X,Dimension Y,Dimension Z,Client Product Description,Primary Telephone,Client Product Code,HDNL Product Code,Service Code,Second Telephone,E-Mail");


	int ParcelSeq = 0;
	UnicodeString LastKey = "";

	while ( i < DBGrid2->SelectedRows->Count  )
		{

			Q->GotoBookmark(DBGrid2->SelectedRows->Items[i] );

			if ( warehousecode.IsEmpty()) {
				warehousecode = DM->ConsignmentsViewWarehouseCode->AsAnsiString.SubString(1,2) ;
			}

#ifndef CHEAT
			if ( warehousecode.SubString(1,1) == "M" )
			{
				if ( warehousecode.SubString(1,1) != DM->ConsignmentsViewWarehouseCode->AsAnsiString.SubString(1,1) )
				{
						MessageDlg ( "You have more than 1 warehouse selected" , mtError , TMsgDlgButtons() << mbOK , 0 );
						delete csv;
						return;
				}
			}
			else
			{
				if ( warehousecode != DM->ConsignmentsViewWarehouseCode->AsAnsiString.SubString(1,2) )
				{
					MessageDlg ( "You have more than 1 warehouse selected" , mtError , TMsgDlgButtons() << mbOK , 0 );
					delete csv;
					return;
				}
			}
#endif

			AnsiString rec = "";

			if ( LastKey.IsEmpty() ) {   // first time through
				ParcelSeq = 1;
			}
			else
			{
				if (LastKey == DM->ConsignmentsViewCustomerReference->AsAnsiString.Trim() + DM->ConsignmentsViewClientProductCode->AsString.Trim()      ) {
					ParcelSeq++;
				}
				else
				{
					ParcelSeq = 1;
				}
			}
			AnsiString Phone = DM->ConsignmentsViewPrimaryTelephone->AsString ;

			Phone = StringReplace(Phone,"(" , "" , TReplaceFlags() << rfReplaceAll );
			Phone = StringReplace(Phone,")" , "" , TReplaceFlags() << rfReplaceAll );
			Phone = StringReplace(Phone," " , "" , TReplaceFlags() << rfReplaceAll );




			TStringList *theConsign = new TStringList();
			theConsign->Clear();
			theConsign->Add ( DM->ConsignmentsViewWarehouseCode->AsAnsiString.Trim() );
			theConsign->Add ( DM->ConsignmentsViewCustomerReference->AsAnsiString.Trim() );
			theConsign->Add ( IntToStr(ParcelSeq) );
			theConsign->Add ( DM->ConsignmentsViewRecipientName->AsAnsiString.Trim() );
			theConsign->Add ( DM->ConsignmentsViewRecipientAddress1->AsAnsiString.Trim() );
			theConsign->Add ( DM->ConsignmentsViewRecipientAddress2->AsAnsiString.Trim() );
			theConsign->Add ( ( DM->ConsignmentsViewRecipientAddress3->IsNull ? (AnsiString)"" :  DM->ConsignmentsViewRecipientAddress3->AsAnsiString.Trim() ) );
			theConsign->Add ( ( DM->ConsignmentsViewRecipientAddress4->IsNull ? (AnsiString)"" :  DM->ConsignmentsViewRecipientAddress4->AsAnsiString.Trim() ) );
			theConsign->Add ( DM->ConsignmentsViewRecipientPostCode->AsAnsiString.Trim() );
			theConsign->Add ( ( DM->ConsignmentsViewDeliveryInstructions->IsNull ? (AnsiString)"" : DM->ConsignmentsViewDeliveryInstructions->AsAnsiString.Trim() ) );
			theConsign->Add ( IntToStr(DM->ConsignmentsViewWeight->AsInteger) );
			theConsign->Add ( IntToStr(DM->ConsignmentsViewDimX->AsInteger ) );
			theConsign->Add ( IntToStr(DM->ConsignmentsViewDimY->AsInteger ) );
			theConsign->Add ( IntToStr(DM->ConsignmentsViewDimZ->AsInteger ) );
			theConsign->Add ( DM->ConsignmentsViewClientProductDescription->AsAnsiString.Trim() );
			theConsign->Add ( Phone.Trim() );
			theConsign->Add ( DM->ConsignmentsViewClientProductCode->AsAnsiString.Trim() );
			theConsign->Add ( DM->ConsignmentsViewHDNLProductCode->AsAnsiString.Trim() );
			theConsign->Add ( DM->ConsignmentsViewServiceCode_1->AsAnsiString.Trim());
			theConsign->Add ( ( DM->ConsignmentsViewSecondTelephone->IsNull ? (AnsiString)"" : DM->ConsignmentsViewSecondTelephone->AsAnsiString.Trim() ) );
			theConsign->Add ( ( DM->ConsignmentsViewEmail->IsNull ? (AnsiString)"" : DM->ConsignmentsViewEmail->AsAnsiString.Trim() ) );

			rec = rec.sprintf ( "%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s???%s" ,
						DM->ConsignmentsViewWarehouseCode->AsAnsiString.Trim().c_str(),
						DM->ConsignmentsViewCustomerReference->AsAnsiString.Trim().c_str(),
						IntToStr(ParcelSeq) ,
						DM->ConsignmentsViewRecipientName->AsAnsiString.Trim().c_str(),
						DM->ConsignmentsViewRecipientAddress1->AsAnsiString.Trim().c_str(),
						DM->ConsignmentsViewRecipientAddress2->AsAnsiString.Trim().c_str(),
						( DM->ConsignmentsViewRecipientAddress3->IsNull ? "" :  DM->ConsignmentsViewRecipientAddress3->AsAnsiString.Trim().c_str() ),
						( DM->ConsignmentsViewRecipientAddress4->IsNull ? "" :  DM->ConsignmentsViewRecipientAddress4->AsAnsiString.Trim().c_str() ),
						DM->ConsignmentsViewRecipientPostCode->AsAnsiString.Trim().c_str(),
						( DM->ConsignmentsViewDeliveryInstructions->IsNull ? "" :
							DM->ConsignmentsViewDeliveryInstructions->AsAnsiString.Trim().c_str() ),
						IntToStr(DM->ConsignmentsViewWeight->AsInteger) ,
						IntToStr(DM->ConsignmentsViewDimX->AsInteger ),
						IntToStr(DM->ConsignmentsViewDimY->AsInteger ),
						IntToStr(DM->ConsignmentsViewDimZ->AsInteger ),
						DM->ConsignmentsViewClientProductDescription->AsAnsiString.Trim().c_str() ,
						Phone.c_str() ,
						DM->ConsignmentsViewClientProductCode->AsAnsiString.Trim().c_str() ,
						DM->ConsignmentsViewHDNLProductCode->AsAnsiString.Trim().c_str() ,
						DM->ConsignmentsViewServiceCode_1->AsAnsiString.Trim().c_str() ,
						( DM->ConsignmentsViewSecondTelephone->IsNull ? "" :
							DM->ConsignmentsViewSecondTelephone->AsAnsiString.Trim().c_str() ),
						( DM->ConsignmentsViewEmail->IsNull ? "" :
							DM->ConsignmentsViewEmail->AsAnsiString.Trim().c_str() )
						);
			// now check for any invalid characters and remove them

			theConsign->Text = StringReplace(theConsign->Text , ",","",TReplaceFlags() << rfReplaceAll );
			rec = theConsign->CommaText ;

//			rec = StringReplace(rec , "," , " " , TReplaceFlags() << rfReplaceAll );
			rec = StringReplace(rec , "<" , " " , TReplaceFlags() << rfReplaceAll );
			rec = StringReplace(rec , ">" , " " , TReplaceFlags() << rfReplaceAll );
			rec = StringReplace(rec , "\r" , "" , TReplaceFlags() << rfReplaceAll );
			rec = StringReplace(rec , "\n" , "" , TReplaceFlags() << rfReplaceAll );
			rec = StringReplace(rec , "\"" , "" , TReplaceFlags() << rfReplaceAll );

			AnsiString RemoveChars = "<>!$%^~";
//			AnsiString RemoveChars = "<>,!$%^~";
			int rc = 0;
			while ( rc < RemoveChars.Length() )
				{
					rec = StringReplace(rec , (AnsiString)(RemoveChars[rc+1]) , "" , TReplaceFlags() << rfReplaceAll );

					rc++;
				}


			// now convert the ??? to commas so we have a clean CSV record

			rec = StringReplace(rec , "???" , "," , TReplaceFlags() << rfReplaceAll );

			// add the record to the CSV file

			csv->Add(rec);


			LastKey = DM->ConsignmentsViewCustomerReference->AsAnsiString.Trim() +
				DM->ConsignmentsViewClientProductCode->AsAnsiString.Trim() ;
			i++;
		}

	StatusBar1->Panels->Items[0]->Text = "";

	try
	{
		if ( FileSaveAs1->Dialog->Execute() )
		{
			csv->SaveToFile(FileSaveAs1->Dialog->FileName );
			Memo1->Lines->Insert(0,Now().FormatString("yyyy-mm-dd hh:nn:ss") + " Created CSV file in " + FileSaveAs1->Dialog->FileName  );

			CheckedOK = true;
			try
			{
				ForceDirectories("I:\\whseapps\\arrowxl\\uploads");
				AnsiString CSVFileName = "I:\\whseapps\\arrowxl\\uploads\\" + Now().FormatString("yyyymmdd_hhnnss") + "_upload.csv";
				csv->SaveToFile( CSVFileName );

			}
			catch(Exception &E)
			{
				MessageDlg ( "CSV saved ok but error occurred when creating backup copy" ,
					mtWarning ,
					TMsgDlgButtons() << mbOK , 0 );
			}
		}


	}
	catch(Exception &E)
	{
		MessageDlg ( "Error saving CSV file \n\n" + E.Message ,
			mtError , TMsgDlgButtons() << mbOK , 0 );
	}


	delete csv;


}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::actCheckDataExecute(TObject *Sender)
{
	CheckedOK = false;

	try
	{
		TBookmark bm = DM->ConsignmentsView->GetBookmark() ;

		DM->ConsignmentsView->Requery();

		DM->ConsignmentsView->GotoBookmark(bm);
	}
	catch(...)
	{

	}


	if ( DBGrid2->SelectedRows->Count == 0 ) {
		if ( MessageDlg ( "No items selected , do you want to process them all ?" , mtConfirmation , TMsgDlgButtons() << mbYes << mbNo , 0 ) == mrNo )
		{
			return;
		}

		rgpSelection->ItemIndex = SELECTION_ALL ;

	}

	int i = 0;
	StatusBar1->Panels->Items[0]->Text = "Checking selected consignments...";
	Application->ProcessMessages();


	TADOQuery *Q = DM->ConsignmentsView ;
	while ( i < DBGrid2->SelectedRows->Count  )
		{
			Q->GotoBookmark(DBGrid2->SelectedRows->Items[i] );
			// now perform any checks to make sure data is there

			if ( DM->ConsignmentsViewClientProductCode->IsNull ||
				DM->ConsignmentsViewClientProductCode->AsString.Trim().Length() == 0 )
			{
				DBGrid2DblClick(Sender);

				dbGridItems->SetFocus() ;

				MessageDlg ( "Missing product code on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( DM->ConsignmentsViewHDNLProductCode->IsNull ||
				DM->ConsignmentsViewHDNLProductCode->AsString.Trim().Length() == 0 )
			{
				DBGrid2DblClick(Sender);

				dbGridItems->SetFocus() ;

				MessageDlg ( "Missing HDNL code on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( DM->ConsignmentsViewServiceCode_1->IsNull ||
				DM->ConsignmentsViewServiceCode_1->AsString.Trim().Length() == 0 )
			{
				DBGrid2DblClick(Sender);

				DBLookupComboBox1->SetFocus();

				MessageDlg ( "Missing service code on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( DM->ConsignmentsViewClientProductDescription->IsNull ||
				DM->ConsignmentsViewClientProductDescription->AsString.Trim().Length() == 0 )
			{
				DBGrid2DblClick(Sender);

				dbGridItems->SetFocus() ;
				MessageDlg ( "Missing Client Product Description on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( DM->ConsignmentsViewCustomerReference->IsNull ||
				DM->ConsignmentsViewCustomerReference->AsString.Trim().Length() == 0 )
			{
				DBGrid2DblClick(Sender);

				DBEdit2->SetFocus() ;

				MessageDlg ( "Missing Customer Reference on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( DM->ConsignmentsViewRecipientName->IsNull ||
				DM->ConsignmentsViewRecipientName->AsString.Trim().Length() == 0 )
			{
				DBGrid2DblClick(Sender);

				DBEdit3->SetFocus() ;

				MessageDlg ( "Missing recipient name on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}
			if ( DM->ConsignmentsViewRecipientAddress1->IsNull ||
				DM->ConsignmentsViewRecipientAddress1->AsString.Trim().Length() == 0 )
			{
				DBGrid2DblClick(Sender);

				DBEdit4->SetFocus() ;

				MessageDlg ( "Missing recipient address 1 on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}
			if ( DM->ConsignmentsViewRecipientAddress2->IsNull ||
				DM->ConsignmentsViewRecipientAddress2->AsString.Trim().Length() == 0 )
			{
				DBGrid2DblClick(Sender);

				DBEdit5->SetFocus() ;

				MessageDlg ( "Missing recipient address 2 on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}
			if ( DM->ConsignmentsViewRecipientPostCode->IsNull ||
				DM->ConsignmentsViewRecipientPostCode->AsString.Trim().Length() == 0 )
			{
				DBGrid2DblClick(Sender);

				DBEdit8->SetFocus() ;

				MessageDlg ( "Missing postcode on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( DM->ConsignmentsViewPrimaryTelephone->IsNull ||
				DM->ConsignmentsViewPrimaryTelephone->AsString.Trim().Length() == 0 )
			{
				DBGrid2DblClick(Sender);

				DBEdit9->SetFocus() ;

				MessageDlg ( "Missing primary telephone on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}


			if ( DM->ConsignmentsViewWeight->IsNull ||
				DM->ConsignmentsViewWeight->Value <= 0 )
			{
				DBGrid2DblClick(Sender);

				dbGridItems->SetFocus() ;

				MessageDlg ( "Missing weight on item for consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( DM->ConsignmentsViewDimX->IsNull ||
				DM->ConsignmentsViewDimX->Value <= 0 )
			{
				DBGrid2DblClick(Sender);

				dbGridItems->SetFocus() ;

				MessageDlg ( "Missing Dim X on item for consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( DM->ConsignmentsViewDimY->IsNull ||
				DM->ConsignmentsViewDimY->Value <= 0 )
			{
				DBGrid2DblClick(Sender);

				dbGridItems->SetFocus() ;

				MessageDlg ( "Missing Dim Y on item for consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( DM->ConsignmentsViewDimZ->IsNull ||
				DM->ConsignmentsViewDimZ->Value <= 0 )
			{
				DBGrid2DblClick(Sender);

				dbGridItems->SetFocus() ;

				MessageDlg ( "Missing Dim Z on item for consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( ! DM->ConsignmentsViewEmail->IsNull &&
				DM->ConsignmentsViewEmail->AsString.Length() > 0 && DM->ConsignmentsViewEmail->AsString.Pos("@") == -1 )
			{
				DBGrid2DblClick(Sender);

				DBEdit11->SetFocus() ;

				MessageDlg ( "Invalid email on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			if ( DM->ConsignmentsViewWarehouseCode->IsNull ||
				DM->ConsignmentsViewWarehouseCode->AsString.Length() < 3)
			{
				DBGrid2DblClick(Sender);

				DBEdit1->SetFocus() ;

				MessageDlg ( "Missing warehouse code on consignment.Please correct then try again or remove it from the selection" , mtError , TMsgDlgButtons() << mbOK , 0 );

				return;
			}

			int minWt = 0;
			int maxWt = 0;

			DM->SuppServices->Open();

			if ( ! DM->SuppServices->Locate("WarehouseCodeID", DM->ConsignmentsViewWarehouseCodeID->AsInteger , TLocateOptions() ) )
			{
				MessageDlg("Something went wrong WarehouseCodeID on item is invalid", mtError, TMsgDlgButtons() << mbOK , 0);
				DBGrid2DblClick(Sender);
				return ;
			}

			if ( ! DM->SuppServicesMaxWeight->IsNull )
				maxWt  = DM->SuppServicesMaxWeight->AsInteger ;
			if ( ! DM->SuppServicesMinWeight->IsNull )
				minWt  = DM->SuppServicesMinWeight->AsInteger ;

			// get consignment weight


			int CombinedWeight = 0;

			DM->ConsignmentWeight->Parameters->ParamByName("cid")->Value =
				DM->ConsignmentsViewConsignmentID->AsInteger ;
			DM->ConsignmentWeight->Open();
			if ( !DM->ConsignmentWeight->Eof ) {
				CombinedWeight = DM->ConsignmentWeightWt->AsInteger;
			}
			DM->ConsignmentWeight->Close();


			if ( minWt > 0 || maxWt > 0 ) {
				// check the weight of the item


				if ( CombinedWeight >= minWt &&
					CombinedWeight <= maxWt  ) {
					;
				}
				else
				{
					if ( MessageDlg ( "Item " + DM->ConsignmentsViewClientProductCode->AsAnsiString + " is outside the weight category for the service selected\n\nCombined Weight is " + IntToStr(CombinedWeight) + "\n\nPlease amend service code or click No to continue" , mtWarning ,TMsgDlgButtons() << mbYes << mbNo , 0 ) == mrNo )
					{

					}
					else
					{
						DBGrid2DblClick(Sender);

						dbGridItems->SetFocus() ;
						return;
					}

				}

#if 0
				DM->ConsignmentItems->Open();



				DM->ConsignmentItems->First();


				while (! DM->ConsignmentItems->Eof )
					{
						if ( ! DM->ConsignmentItemsWeight->IsNull ) {
							int itemWt = DM->ConsignmentItemsWeight->AsInteger ;

							if ( itemWt >= minWt && itemWt <= maxWt ) {
									;
							}
							else
							{
								DBGrid2DblClick(Sender);

								dbGridItems->SetFocus() ;
								MessageDlg ( "Item " + DM->ConsignmentItemsClientProductCode->AsAnsiString + " is outside the weight category for the service selected\n\nPlease amend service code" , mtWarning ,TMsgDlgButtons() << mbOK , 0 );
								return;
							}
						}
						DM->ConsignmentItems->Next() ;
					}
#endif


			}



			i++;
		}



	StatusBar1->Panels->Items[0]->Text = "";
	CheckedOK = true;


}
//---------------------------------------------------------------------------


void __fastcall TfmConsign::Button5Click(TObject *Sender)
{
	actCheckDataExecute(Sender);

	if ( CheckedOK ) {
		MessageDlg ( "All checked OK" , mtInformation , TMsgDlgButtons() << mbOK , 0 );
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::Button6Click(TObject *Sender)
{
	actCheckData->Execute();

	if ( CheckedOK ) {
		actCreateCSV->Execute() ;
		if ( CheckedOK ) {
#ifndef CHEAT
			actUpdateCSVChecked->Execute();
#endif
			if (CheckedOK ) {

				MessageDlg ( "CSV created OK" , mtInformation , TMsgDlgButtons() << mbOK , 0 );
			}
		}

		try
		{
			TBookmark bm = DM->ConsignmentsView->GetBookmark() ;

			DM->ConsignmentsView->Requery();

			DM->ConsignmentsView->GotoBookmark(bm);
		}
		catch(...)
		{

		}


	}
}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::actUpdateCSVCheckedExecute(TObject *Sender)
{
	CheckedOK = false;

	try
	{
		TBookmark bm = DM->ConsignmentsView->GetBookmark() ;

		DM->ConsignmentsView->Requery();

		DM->ConsignmentsView->GotoBookmark(bm);
	}
	catch(...)
	{

	}


	if ( DBGrid2->SelectedRows->Count == 0 ) {
		if ( MessageDlg ( "No items selected , do you want to process them all ?" , mtConfirmation , TMsgDlgButtons() << mbYes << mbNo , 0 ) == mrNo )
		{
			return;
		}

		rgpSelection->ItemIndex = SELECTION_ALL ;

	}

	int i = 0;
	StatusBar1->Panels->Items[0]->Text = "Updating selected consignments...";
	Application->ProcessMessages();

	TADOQuery *Q = DM->ConsignmentsView ;
	while ( i < DBGrid2->SelectedRows->Count  )
		{
			Q->GotoBookmark(DBGrid2->SelectedRows->Items[i] );

			DM->cmdUpdateCSVDate->Parameters->ParamByName("@cid")->Value
				= DM->ConsignmentsViewConsignmentID->AsInteger ;
			try
			{
				DM->cmdUpdateCSVDate->Execute();
			}
			catch(Exception &E)
			{
				MessageDlg ( "Error updating CSV Checked date for consignment number " + IntToStr(DM->ConsignmentsViewConsignmentID->AsInteger ) + "\n\n" + E.Message ,
					mtError,
					TMsgDlgButtons() << mbOK ,
					0 );
			}
			i++;
		}



	StatusBar1->Panels->Items[0]->Text = "";
	CheckedOK = true;


}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::dbGridItemsEditButtonClick(TObject *Sender)
{
	if (DBGrid1->SelectedField ) {
		TfmProductTypes *fm = new TfmProductTypes(Application);

		DM->ProductTypes->Close();
		DM->ProductTypes->Open();


		int mr = fm->ShowModal() ;

		if (mr  == mrOk ) {
			if ( DM->dsConsignmentItems->State != dsEdit &&
					DM->dsConsignmentItems->State != dsInsert )
			{
				DM->ConsignmentItems->Edit() ;
			}
			DM->ConsignmentItemsHDNLProductCode->Value =
				DM->ProductTypesProductType->Value ;

		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::Timer1Timer(TObject *Sender)
{

	Timer1->Enabled = false;
	StatusBar1->Panels->Items[4]->Text  = "Initiating";
	Application->ProcessMessages();

	IdTCPServer1->Active = true;

	StatusBar1->Panels->Items[4]->Text  = "Active";
	Application->ProcessMessages();





}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::IdTCPServer1Execute(TIdContext *AContext)
{

	UnicodeString msg = AContext->Connection->IOHandler->ReadLn();

	Memo1->Lines->Insert(0,Now().FormatString("yyyy-mm-dd hh:nn:ss") + " " + msg );

	AContext->Connection->IOHandler->WriteLn("ACK");

	if ( msg.SubString(1,4) == "0100" ) {
		UnicodeString Parcel = msg.SubString(5,16);

		CreateConsignmentFrom(Parcel);

		 Button7->Click() ;
	}


}
//---------------------------------------------------------------------------




void __fastcall TfmConsign::FormShow(TObject *Sender)
{
	LPWSTR un;

	un = (wchar_t * )malloc(255);

	unsigned long len = 255;
	un[0] = 0;

	GetUserName(un,&len);

	un[len] = 0;

	LoggedInUser = un;

	free(un);

	StatusBar1->Panels->Items[6]->Text = LoggedInUser;

try
{
	UnicodeString logFileLocation = "I:\\whseapps\\arrowxl\\logs";

	ForceDirectories(logFileLocation);

	UnicodeString logFile = logFileLocation + "\\" + LoggedInUser + ".log";

	if ( FileExists(logFile,false) ) {
		Memo1->Lines->LoadFromFile(logFile);
	}

	}
	catch(...)
	{
	}

	DateTimePicker1->Date = IncDay(Date(),-2);
	PageControl1->ActivePage = tabConsignments ;


	int ci = 0;

	while ( ci < DBGrid5->Columns->Count  )
		{
			DBGrid5->Columns->Items[ci]->Title->Caption =
				StringReplace ( DBGrid5->Columns->Items[ci]->Title->Caption , "_" , " ", TReplaceFlags() << rfReplaceAll );
			ci++;
        }




}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::FormClose(TObject *Sender, TCloseAction &Action)
{
	try
	{
		UnicodeString logFileLocation = "I:\\whseapps\\arrowxl\\logs";

		ForceDirectories(logFileLocation);

		UnicodeString logFile = logFileLocation + "\\" + LoggedInUser + ".log";

		int safe = 0;
		while ( safe < 10000 && Memo1->Lines->Count > 1000 )
		{
			safe++;
			Memo1->Lines->Delete(999);
		}

		Memo1->Lines->SaveToFile(logFile);

	}
	catch(...)
	{
	}

}
//---------------------------------------------------------------------------


void __fastcall TfmConsign::Button7Click(TObject *Sender)
{
	UpdateConsignmentView(Sender);

}
//---------------------------------------------------------------------------


void __fastcall TfmConsign::actConsignmentDeleteExecute(TObject *Sender)
{
	if ( MessageDlg("Confirm Delete ?" , mtConfirmation , TMsgDlgButtons() << mbYes << mbNo , 0 ) == mrYes )  {
		{
			DM->DB->BeginTrans() ;
			DM->ConsignmentItems->First() ;
			while ( ! DM->ConsignmentItems->Eof  )
				{
					DM->ConsignmentItems->Delete() ;
				}

			DM->Consignments->Delete() ;

			try
			{
				DM->DB->CommitTrans() ;
			}
			catch(...)
			{
				DM->DB->RollbackTrans() ;
			}

		}
	}
	PageControl1->ActivePage = tabConsignments ;

}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::dbGridItemsExit(TObject *Sender)
{
	if ( DM->dsConsignmentItems->State == dsEdit ||
		DM->dsConsignmentItems->State == dsInsert) {
		try
		{
			DM->dsConsignmentItems->DataSet->Post() ;
		}
		catch(...)
		{

        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::tabSuppliersShow(TObject *Sender)
{
	DM->DSVSuppliers->Open();

}
//---------------------------------------------------------------------------


void __fastcall TfmConsign::DBLookupComboBox2CloseUp(TObject *Sender)
{
		if ( DM->Consignments->State == dsEdit
			|| DM->Consignments->State == dsInsert )
		{
			DM->ConsignmentsWarehouseCode->Value =
				DM->SupplierServicesWarehouse->Value;
		}
}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::cmbSupplierFilterCloseUp(TObject *Sender)
{
	CurrentMPIFilter  = DM->DSVSuppliersMetapackIndicator->Value ;
    UpdateConsignmentView(Sender);
  //	DM->ConsignmentsView->SQL->Strings[4] = "where  Identifier='" + MPI.Trim() + "'";



}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::Button16Click(TObject *Sender)
{
	cmbSupplierFilter->KeyValue = NULL;
	CurrentMPIFilter = "";

	UpdateConsignmentView(Sender);

}
//---------------------------------------------------------------------------


void __fastcall TfmConsign::UpdateConsignmentView(TObject *Sender)
{


	TADOQuery *Q = DM->ConsignmentsView ;
	try
	{
		bool CriteriaPresent = false;
		Q->DisableControls() ;
		Q->Close() ;
		Q->SQL->Strings[4] = "";
		Q->SQL->Strings[5] = "";
		Q->SQL->Strings[6] = "";
		Q->SQL->Strings[7] = "";



		// cater for the show all check box
		if ( ! cbxShowAll->Checked )
		{
			Q->SQL->Strings[4] = " where CSVCreatedOn is null";
			CriteriaPresent = true;
		}

		if ( ! DedicatedWarehouse.IsEmpty())
			CurrentMPIFilter = DedicatedMPI ;
		// cater for the supplier filter box
		if ( !  CurrentMPIFilter.IsEmpty() ) {
			if ( Q->SQL->Strings[4].IsEmpty()  ) {
				DM->ConsignmentsView->SQL->Strings[4] = "where Identifier like '" + CurrentMPIFilter.Trim() + "%'";
			}
			else
			{
				DM->ConsignmentsView->SQL->Strings[5] = " and  Identifier like '" + CurrentMPIFilter.Trim() + "%'";
			}
			CriteriaPresent = true;
		}

		if ( ! CriteriaPresent ) {
			Q->SQL->Strings[4] = "where ";
		}
		else
			Q->SQL->Strings[6] = " and ";

		Q->SQL->Strings[7] = " convert(char(10),[createdOn],121)>='" + DateTimePicker1->Date.FormatString("yyy-mm-dd") + "'";

		// reopen the dataset
//		MessageDlg ( Q->SQL->Text , mtInformation , TMsgDlgButtons() << mbOK , 0 );
		try
		{
			Q->Open();
		}
		catch(Exception &E)
		{
			MessageDlg ( "Error creating consigmnentview SQL\n\n" + Q->SQL->Text + "\n\nError : " + E.Message,
				mtError,
				TMsgDlgButtons() << mbOK ,
				0 );
		}

	}
	catch(Exception &E)
	{
			MessageDlg ( "Error while searching for consignments\n" + E.Message
				, mtError
				, TMsgDlgButtons() << mbOK
				, 0 );

	}
	try
	{
		Q->EnableControls();
	}
	catch(...)
	{
		try
		{
			DM->ConsignmentsView->EnableControls() ;
		}
		catch(...)
		{

		}
	}
}
void __fastcall TfmConsign::Timer2Timer(TObject *Sender)
{
	Timer2->Enabled = false;
	pnlConsignMain->Color = clCream ;

}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::Button17Click(TObject *Sender)
{
	if ( ! DM->OrderSearch->Eof ) {
			txtBarcodeLookup->Text = DM->OrderSearchParcel->AsAnsiString.Trim();
			Memo1->Lines->Insert(0,Now().FormatString("yyyy-mm-dd hh:nn:ss") + " Parcel [" + txtBarcodeLookup->Text + "]" );


			unsigned short Key = 13;
			TShiftState ss = TShiftState();

			PageControl1->ActivePage = tabConsignment ;



			txtBarcodeLookupKeyDown(Sender , Key , ss );

	}
}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::BitBtn2Click(TObject *Sender)
{
	DM->OrderSearch->Close();

	if ( LabeledEdit1->Text.IsEmpty() ) {
		MessageDlg ( "Enter an agency / account number" , mtWarning , TMsgDlgButtons() << mbOK , 0 );
		LabeledEdit1->SetFocus();
		return;
	}

	DM->OrderSearch->Parameters->ParamByName("agy")->Value =
		LabeledEdit1->Text.UpperCase();

	DM->OrderSearch->Open();


}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::LabeledEdit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if ( Key == 13 ) {
		BitBtn2->Click() ;
	}
}


bool
TfmConsign::CreateConsignmentFrom( UnicodeString parcelScan )
{
		bool error = false;


		if (! DM->SuppServices->Active ) {
			DM->SuppServices->Open();
			DM->SuppServices->Locate("Identifier",DedicatedMPI,TLocateOptions() );
		}

		int serviceCode = DM->SuppServicesWarehouseCodeID->Value;



		DM->cmdAddConsignment->Parameters->ParamByName("pcl")->Value =
			parcelScan;
		DM->cmdAddConsignment->Parameters->ParamByName("svc")->Value =
			serviceCode;

		DM->cmdAddConsignment->Execute();



		return true;







		DM->OrderLookUp->Parameters->ParamByName("pcl")->Value =
			parcelScan;

		DM->OrderLookUp->Open() ;

		if ( ! DM->OrderLookUp->Eof )
			{
				// we have found a match , copy the details

				try
				{

				DM->Consignments->Insert() ;

				DM->ConsignmentsCustomerReference->Value
					= DM->OrderLookUpAgency->AsString.Trim() + "-" +  DM->OrderLookUpInvoice->AsString.Trim();
				DM->ConsignmentsEmail->Value
					= "";
				DM->ConsignmentsPrimaryTelephone->Value
					= DM->OrderLookUpPhone->Value;
				DM->ConsignmentsRecipientName->Value
					= DM->OrderLookUpCustomerName->Value;
				DM->ConsignmentsRecipientAddress1->Value
					= DM->OrderLookUpAddress1->Value;
				DM->ConsignmentsRecipientAddress2->Value
					= DM->OrderLookUpAddress2->Value;
				DM->ConsignmentsRecipientAddress3->Value
					= DM->OrderLookUpAddress3->Value;
				DM->ConsignmentsRecipientAddress4->Value
					= DM->OrderLookUpAddress4->Value;
				DM->ConsignmentsRecipientPostCode->Value
					= DM->OrderLookUpPostcode->Value;

				DM->ConsignmentsServiceCode->Value =
					DM->ServicesWarehouseCodeID->Value;

				DM->Consignments->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignment\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );

				}
				if ( DM->ConsignmentsConsignmentID->IsNull ||
					DM->ConsignmentsConsignmentID->AsInteger < 1  ) {
					MessageDlg ( "Consignment has no ID?" , mtError , TMsgDlgButtons() << mbOK , 0 );

				}
				try
				{
				DM->ConsignmentItems->Insert() ;

				DM->ConsignmentItemsClientProductCode->Value
					= DM->OrderLookUpCat->AsString + "/" + DM->OrderLookUpOpt->AsString;
				DM->ConsignmentItemsClientProductDescription->Value
					= DM->OrderLookUpDescription->Value;
				DM->ConsignmentItemsConsignmentID->Value =
					DM->ConsignmentsConsignmentID->Value;
				DM->ConsignmentItemsWeight->Value =
					DM->OrderLookUpWeight->Value;
				DM->ConsignmentItemsDimX->Value =
					DM->OrderLookUpDim1->Value;
				DM->ConsignmentItemsDimY->Value =
					DM->OrderLookUpDim2->Value;
				DM->ConsignmentItemsDimZ->Value =
					DM->OrderLookUpDim3->Value;

				if ( ! DM->OrderLookUpHDNLCode->IsNull ) {
					DM->ConsignmentItemsHDNLProductCode->Value
						= DM->OrderLookUpHDNLCode->Value ;
				}
/*				else
					MessageDlg ( "Select HDNL code"  , mtInformation , TMsgDlgButtons() << mbOK , 0 );
*/
				DM->ConsignmentItems->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignmentitem\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
				}

				if ( ! DM->OrderLookUpDD1Dim1->IsNull && DM->OrderLookUpDD1Dim1->AsInteger > 0  ) {

					try
					{
					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
						= DM->OrderLookUpCat->AsString + "/" + DM->OrderLookUpOpt->AsString;
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->OrderLookUpDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->OrderLookUpDD1Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->OrderLookUpDD1Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->OrderLookUpDD1Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->OrderLookUpDD1Dim3->Value;

					if ( ! DM->OrderLookUpHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->OrderLookUpHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignment item 1\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
				}


				}
				if ( ! DM->OrderLookUpDD2Dim1->IsNull && DM->OrderLookUpDD2Dim1->AsInteger > 0  ) {

					try
					{
					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
						= DM->OrderLookUpCat->AsString + "/" + DM->OrderLookUpOpt->AsString;
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->OrderLookUpDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->OrderLookUpDD2Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->OrderLookUpDD2Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->OrderLookUpDD2Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->OrderLookUpDD2Dim3->Value;

					if ( ! DM->OrderLookUpHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->OrderLookUpHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignment item 2\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
				}

				}

				if ( ! DM->OrderLookUpDD3Dim1->IsNull && DM->OrderLookUpDD3Dim1->AsInteger > 0  ) {

					try
					{
					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
						= DM->OrderLookUpCat->AsString + "/" + DM->OrderLookUpOpt->AsString;
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->OrderLookUpDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->OrderLookUpDD3Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->OrderLookUpDD3Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->OrderLookUpDD3Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->OrderLookUpDD3Dim3->Value;

					if ( ! DM->OrderLookUpHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->OrderLookUpHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignment item 3\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
				}

				}

				if ( ! DM->OrderLookUpDD4Dim1->IsNull && DM->OrderLookUpDD4Dim1->AsInteger > 0  ) {

					try
					{
					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
						= DM->OrderLookUpCat->AsString + "/" + DM->OrderLookUpOpt->AsString;
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->OrderLookUpDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->OrderLookUpDD4Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->OrderLookUpDD4Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->OrderLookUpDD4Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->OrderLookUpDD4Dim3->Value;

					if ( ! DM->OrderLookUpHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->OrderLookUpHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignment item 4\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
				}

				}
#if 0
				try
				{
					DM->DB->CommitTrans() ;
				}
				catch(Exception &E)
				{
					try
					{
						DM->DB->RollbackTrans() ;
					}
					catch(...)
					{
					MessageDlg ( "Failed to add commit transaction\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
					}
				}
#endif
	 }
	 return !error;
}

//---------------------------------------------------------------------------


void __fastcall TfmConsign::Button18Click(TObject *Sender)
{
	DM->DDOrders->Close() ;

	DM->DDOrders->Parameters->ParamByName("supplier")->Value =
		DBLookupComboBox3->KeyValue ;
 //	ShowMessage ( "[" + DBLookupComboBox3->KeyValue + "]" );
	DM->DDOrders->Open();


	DM->SupplierServices->Open();
	DM->SupplierServices->Filter = "[SupplierCode]='" + DBLookupComboBox3->KeyValue  + "'";
	DM->SupplierServices->Filtered = true;





}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::Button19Click(TObject *Sender)
{

	if ( DBLookupComboBox4->KeyValue.IsNull() ) {
		MessageDlg ( "Choose service first" , mtWarning , TMsgDlgButtons() << mbOK , 0 );
		DBLookupComboBox4->SetFocus() ;
		return;
	}



	int si = 0;

	while ( si < DBGrid5->SelectedRows->Count  )
	{
		DM->DDOrders->GotoBookmark(DBGrid5->SelectedRows->Items[si]  );







	DM->OptLookUp->Close();
	DM->OptLookUp->Parameters->ParamByName("cat")->Value =
			DM->DDOrdersCATALOGUE_NUMBER->AsString.Trim();
	DM->OptLookUp->Parameters->ParamByName("opt")->Value =
			DM->DDOrdersOPTION_NUMBER->AsString.Trim();
	DM->OptLookUp->Open();

	if ( DM->OptLookUp->Eof  )
	{
		MessageDlg ( "Cannot locate item data!" , mtError , TMsgDlgButtons() << mbOK , 0 );
		DM->OptLookUp->Close();

		return;
	}


		if ( ! DM->Consignments->Active) {
			DM->Consignments->Open();
		}
		if ( ! DM->OrderLookUp->Active) {
				DM->OrderLookUp->Open();

		}

				try
				{

				DM->Consignments->Insert() ;

				DM->ConsignmentsCustomerReference->Value
					= DM->DDOrdersACCOUNT_REF_NO->AsString.Trim() + "-" +  IntToStr(DM->DDOrdersINVOICE_NO->AsInteger).Trim();
				DM->ConsignmentsEmail->Value
					= "";
				DM->ConsignmentsPrimaryTelephone->Value
					= DM->DDOrdersCONTACT_PHONE_NO->Value;
				DM->ConsignmentsRecipientName->Value
					= DM->DDOrdersDELIVERY_ADDR1->Value;
				DM->ConsignmentsRecipientAddress1->Value
					= DM->DDOrdersDELIVERY_ADDR2->Value;
				DM->ConsignmentsRecipientAddress2->Value
					= DM->DDOrdersDELIVERY_ADDR3->Value;
				DM->ConsignmentsRecipientAddress3->Value
					= DM->DDOrdersDELIVERY_ADDR4->Value;
				DM->ConsignmentsRecipientAddress4->Value
					= DM->DDOrdersDELIVERY_ADDR5->Value;
				DM->ConsignmentsRecipientPostCode->Value
					= DM->DDOrdersDELIVERY_PCODE->Value;

				DM->ConsignmentsServiceCode->Value =
					DM->SupplierServicesWarehouseCodeID->Value;
				DM->ConsignmentsWarehouseCode->Value =
					DM->SupplierServicesWarehouse->AsString.Trim();

				DM->Consignments->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignment\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );

				}

						if ( DM->ConsignmentsConsignmentID->IsNull ||
					DM->ConsignmentsConsignmentID->AsInteger < 1  ) {
					MessageDlg ( "Consignment has no ID?" , mtError , TMsgDlgButtons() << mbOK , 0 );

				}

				if ( ! DM->ConsignmentItems->Active) {
					DM->ConsignmentItems->Open();
				}

				try
				{



				DM->ConsignmentItems->Insert() ;

				DM->ConsignmentItemsClientProductCode->Value
					= DM->DDOrdersCATALOGUE_NUMBER->AsString + "/" + DM->DDOrdersOPTION_NUMBER->AsString;
				DM->ConsignmentItemsClientProductDescription->Value
					= DM->DDOrdersITEM_DESCRIPTION->Value;
				DM->ConsignmentItemsConsignmentID->Value =
					DM->ConsignmentItemsConsignmentID->Value;
				DM->ConsignmentItemsWeight->Value =
					DM->OptLookUpWeight->Value;
				DM->ConsignmentItemsDimX->Value =
					DM->OptLookUpDim1->Value;
				DM->ConsignmentItemsDimY->Value =
					DM->OptLookUpDim2->Value;
				DM->ConsignmentItemsDimZ->Value =
					DM->OptLookUpDim3->Value;

				if ( ! DM->OrderLookUpHDNLCode->IsNull ) {
					DM->ConsignmentItemsHDNLProductCode->Value
						= DM->OptLookUpHDNLCode->Value ;
				}
/*				else
					MessageDlg ( "Select HDNL code"  , mtInformation , TMsgDlgButtons() << mbOK , 0 );
*/
				DM->ConsignmentItems->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignmentitem\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
				}


			   if ( ! DM->OptLookUpDD1Dim1->IsNull && DM->OptLookUpDD1Dim1->AsInteger > 0  )
			   {

			   try
			   {
					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
						= DM->OptLookUpCat->AsString + "/" + DM->OptLookUpOpt->AsString;
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->OptLookUpDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->OptLookUpDD1Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->OptLookUpDD1Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->OptLookUpDD1Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->OptLookUpDD1Dim3->Value;

					if ( ! DM->OptLookUpHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->OptLookUpHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignment item 1\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
				}
			}

							if ( ! DM->OptLookUpDD2Dim1->IsNull && DM->OptLookUpDD2Dim1->AsInteger > 0  ) {

					try
					{
					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
						= DM->OptLookUpCat->AsString + "/" + DM->OptLookUpOpt->AsString;
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->OptLookUpDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->OptLookUpDD2Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->OptLookUpDD2Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->OptLookUpDD2Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->OptLookUpDD2Dim3->Value;

					if ( ! DM->OptLookUpHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->OptLookUpHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignment item 2\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
				}

				}

				if ( ! DM->OptLookUpDD3Dim1->IsNull && DM->OptLookUpDD3Dim1->AsInteger > 0  ) {

					try
					{
					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
						= DM->OptLookUpCat->AsString + "/" + DM->OptLookUpOpt->AsString;
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->OptLookUpDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->OptLookUpDD3Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->OptLookUpDD3Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->OptLookUpDD3Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->OptLookUpDD3Dim3->Value;

					if ( ! DM->OptLookUpHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->OptLookUpHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignment item 3\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
				}

				}

				if ( ! DM->OptLookUpDD4Dim1->IsNull && DM->OptLookUpDD4Dim1->AsInteger > 0  ) {

					try
					{
					DM->ConsignmentItems->Insert() ;

					DM->ConsignmentItemsClientProductCode->Value
						= DM->OptLookUpCat->AsString + "/" + DM->OptLookUpOpt->AsString;
					DM->ConsignmentItemsClientProductDescription->Value
						= DM->OptLookUpDescription->Value;
					DM->ConsignmentItemsConsignmentID->Value =
						DM->ConsignmentsConsignmentID->Value;
					DM->ConsignmentItemsWeight->Value =
						DM->OptLookUpDD4Weight->Value / 1000;
					DM->ConsignmentItemsDimX->Value =
						DM->OptLookUpDD4Dim1->Value;
					DM->ConsignmentItemsDimY->Value =
						DM->OptLookUpDD4Dim2->Value;
					DM->ConsignmentItemsDimZ->Value =
						DM->OptLookUpDD4Dim3->Value;

					if ( ! DM->OptLookUpHDNLCode->IsNull ) {
						DM->ConsignmentItemsHDNLProductCode->Value
							= DM->OptLookUpHDNLCode->Value ;
					}

					DM->ConsignmentItems->Post() ;
				}
				catch(Exception &E)
				{
					MessageDlg ( "Failed to add new consignment item 4\n\nError : " + E.Message,
						mtError ,
						TMsgDlgButtons() << mbOK , 0 );
				}

				}

		si++;
	}



}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::tabDDOrdersExit(TObject *Sender)
{
	DM->DDOrders->Close() ;


}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::DBGrid5TitleClick(TColumn *Column)
{
	DM->DDOrders->Close() ;

	DM->DDOrders->SQL->Strings[3] = "order by [" + Column->FieldName + "] desc";
	DM->DDOrders->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::FormCreate(TObject *Sender)
{

	LPCTSTR lptstrFilename;
	DWORD dwLen = 0;
	DWORD dwHandle;
	LPVOID lpData;

 //	strcpy ( lpstrFilename , Application->ExeName.c_str() );



//	fmConsign->Caption = "Arrow XL Metapack Consignment Management System Version : " +(AnsiString) verinfo.c_str();
	Image2->Top = Image3->Top ;
	Image2->Left = Image3->Left;

}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::Button20Click(TObject *Sender)
{
	if ( OpenDialog1->Execute()  ) {
		TStringList *imp = new TStringList();
		TStringList *rec = new TStringList();

		imp->Clear() ;
		imp->LoadFromFile(OpenDialog1->FileName );


		imp->Delimiter = ';';
		rec->Delimiter = ';';

		int i = 0;
		ListView1->Items->Clear() ;

		while ( i < imp->Count )
		{
			rec->Clear();


			rec->DelimitedText = StringReplace(imp->Strings[i], " ", "}" , TReplaceFlags() << rfReplaceAll );

			rec->Text = StringReplace(rec->Text, "}", " " , TReplaceFlags() << rfReplaceAll );

			TListItem *LI = ListView1->Items->Add() ;

			LI->Caption = rec->Strings[0];
			LI->SubItems->Add(rec->Strings[2]);
			LI->SubItems->Add(rec->Strings[3]);
			LI->SubItems->Add(rec->Strings[4]);
			LI->SubItems->Add(rec->Strings[6]);
			LI->SubItems->Add(rec->Strings[7]);


			i++;


		}
			delete imp;
			delete rec;
		Button21->Enabled = true;




	}
}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::Button21Click(TObject *Sender)
{
	int i = 0;

	while ( i < ListView1->Items->Count  )
			{
				TListItem *LI = ListView1->Items->Item[i];

				AnsiString Barcode = LI->Caption;


				DM->OrderLookUp->Parameters->ParamByName("pcl")->Value =
					Barcode;
				DM->OrderLookUp->Close();

				DM->OrderLookUp->Open();

				if ( !DM->OrderLookUp->Eof ) {
					int Parts = 1;
					LI->SubItems->Add ( "Matched");
					int Wt = DM->OrderLookUpWeight->AsInteger;

					if (! DM->OrderLookUpDD1Weight->IsNull && DM->OrderLookUpDD1Weight->AsInteger > 0  ) {
						Wt += ( DM->OrderLookUpDD1Weight->AsInteger / 1000 ) ;
						Parts++;
					}
					if (! DM->OrderLookUpDD2Weight->IsNull && DM->OrderLookUpDD2Weight->AsInteger > 0   ) {
						Wt += ( DM->OrderLookUpDD2Weight->AsInteger  / 1000 ) ;
						Parts++;
					}
					if (! DM->OrderLookUpDD3Weight->IsNull && DM->OrderLookUpDD3Weight->AsInteger > 0  ) {
						Wt += ( DM->OrderLookUpDD3Weight->AsInteger  / 1000 ) ;
						Parts++;
					}
					if (! DM->OrderLookUpDD4Weight->IsNull && DM->OrderLookUpDD4Weight->AsInteger > 0  ) {
						Wt += ( DM->OrderLookUpDD4Weight->AsInteger  / 1000 ) ;
						Parts++;
					}

					LI->SubItems->Add ( IntToStr(Wt) );
					LI->SubItems->Add ( IntToStr(Parts) );
				}
				else
				{
					LI->SubItems->Add ( "No Match");
					LI->SubItems->Add ( "0" );
					LI->SubItems->Add ( "1" );
				}

					DM->Q->SQL->Text = "select * from viewAXLConsignments where CustomerReference like '%" + LI->SubItems->Strings[1].Trim() + "%' and CustomerReference like '%" + IntToStr(LI->SubItems->Strings[2].Trim().ToInt()) + "%'";
//					ShowMessage ( DM->Q->SQL->Text );
					DM->Q->Open();
					if ( DM->Q->Eof) {
						LI->SubItems->Add ( "New");
					}
					else
					{
						LI->SubItems->Add ( "Exists");
					}
					DM->Q->Close();

				i++;
			}
	DM->OrderLookUp->Close();

	Button21->Enabled = false;


}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::Button22Click(TObject *Sender)
{

	TItemStates selected = TItemStates() << isSelected;
	TListItem *Item = ListView1->Selected;
	while (Item){

		if ( Item->SubItems->Strings[5] == "Matched" ) {
			if ( Item->SubItems->Strings[8] == "New" ) {
				int SuppID = 0;

				int Wt = 0;

				Wt = Item->SubItems->Strings[6].ToInt();

				AnsiString serCode = "Medium";


				if ( Wt < 40 ) {
					serCode = "Small";
				}
				if ( Wt > 80) {
					serCode = "Large";
				}


				int svc = 0 ;
				DM->Q->SQL->Text = "select WarehouseCodeID as WID from viewAXLSupplierServices where SupplierCode='" + Item->SubItems->Strings[0] + "' and AccountName like '%" + serCode + "%'" ;
				DM->Q->Open();
				if ( !DM->Q->Eof ) {
					Item->SubItems->Add ( IntToStr(DM->Q->FieldByName("WID")->AsInteger) );
					svc = DM->Q->FieldByName("WID")->AsInteger;
				}
				else
				{
					Item->SubItems->Add ( "0" );
					svc = 0;
				}
				DM->Q->Close();

				// ok now add the consignment
				if (AddMode) {

					DM->cmdAddConsignment->Parameters->ParamByName("pcl")->Value =
						Item->Caption ;
					DM->cmdAddConsignment->Parameters->ParamByName("svc")->Value =
						svc;

					DM->cmdAddConsignment->Execute();
					if (Item->SubItems->Count == 10 )  {
						Item->SubItems->Add ("Added");
					}
					else
					{
						Item->SubItems->Strings[10] = "Added";
					}

				}


			}
		}

		Item = ListView1->GetNextItem(Item, sdAll, selected);
	}
	AddMode = 0;







}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::Button23Click(TObject *Sender)
{
	AddMode = 1;

	Button22->Click() ;

}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::DBEdit2Exit(TObject *Sender)
{

	UnicodeString xx = "";
	Image2->Visible = false;
	Image3->Visible = false;

	xx = DBEdit2->Text ;

	if ( xx.IsEmpty() ) {
		return;
	}

	if ( xx.Pos("-") == 0) {
		MessageDlg ( "Please enter CustomerReference as CUSTOMER NUMBER-INVOICE NUMBER" , mtWarning , TMsgDlgButtons() << mbOK , 0 );
		DBEdit2->SetFocus() ;
		Image2->Visible = true;
		return;
	}

	try
	{
		UnicodeString accountno = "";
		UnicodeString invno = "";

		accountno = xx.Trim().SubString(1,xx.Pos("-") - 1);
	//	ShowMessage ( "Account = [" + accountno + "]");

		invno = xx.Trim().SubString(xx.Pos("-") + 1 , xx.Length() - xx.Pos("-"));
  //		ShowMessage ( "Invoice = [" + invno + "]");

		try
		{
			int i = invno.ToDouble() ;

		}
		catch(...)
		{
			MessageDlg ("Please only put the numeric part of the invoice number ( no letters )" , mtWarning, TMsgDlgButtons() << mbOK , 0 );
			DBEdit2->SetFocus() ;
		Image2->Visible = true;
		return;
		}


	}
	catch(Exception &E)
	{
		MessageDlg ( "Customer Reference doesn't look right , Please enter CustomerReference as CUSTOMER NUMBER-INVOICE NUMBER " , mtWarning , TMsgDlgButtons() << mbOK , 0 );
		DBEdit2->SetFocus() ;
		Image2->Visible = true;
		return;
	}
	Image3->Visible = true;

}
//---------------------------------------------------------------------------


