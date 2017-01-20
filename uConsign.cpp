//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uConsign.h"
#include "dbConsign.h"
#include "uOptSelect.h"
#include "uOptionSelect.h"
#include "uProductTypes.h"
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



//---------------------------------------------------------------------------
__fastcall TfmConsign::TfmConsign(TComponent* Owner)
	: TForm(Owner)
{
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

		DM->OrderLookUp->Parameters->ParamByName("pcl")->Value =
			txtBarcodeLookup->Text ;

		DM->OrderLookUp->Open() ;

		if ( ! DM->OrderLookUp->Eof )
			{
				// we have found a match , copy the details
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
					DM->ServicesServiceID->Value;

				DM->Consignments->Post() ;

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

				Memo1->Lines->Insert(0,Now().FormatString("yyyy-mm-dd hh:nn:ss") + " Match Found for " + DM->ConsignmentsRecipientName->AsString );
			}
			else
			{
				Memo1->Lines->Insert(0,Now().FormatString("yyyy-mm-dd hh:nn:ss") + " No Match Found for barcode " + txtBarcodeLookup->Text  );
			}

		   txtBarcodeLookup->Text = "";

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
					= DM->ItemLookupCat->AsString + "/" + DM->ItemLookupOpt->AsString;
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

	DM->Consignments->Locate("ConsignmentID",DM->ConsignmentsViewConsignmentID->AsInteger , TLocateOptions() );

}
//---------------------------------------------------------------------------

void __fastcall TfmConsign::tabConsignmentsShow(TObject *Sender)
{
//	if ( ! DM->ConsignmentsView->Active ) {
//		DM->ConsignmentsView->Open() ;
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

			AnsiString rec = "";

			if ( LastKey.IsEmpty() ) {   // first time through
				ParcelSeq = 1;
			}
			else
			{
				if (LastKey == DM->ConsignmentsViewCustomerReference->AsAnsiString.Trim()    ) {
					ParcelSeq++;
				}
				else
				{
					ParcelSeq = 1;
				}
			}
			UnicodeString Phone = DM->ConsignmentsViewPrimaryTelephone->AsString ;

			Phone = StringReplace(Phone,"(" , "" , TReplaceFlags() << rfReplaceAll );
			Phone = StringReplace(Phone,")" , "" , TReplaceFlags() << rfReplaceAll );
			Phone = StringReplace(Phone," " , "" , TReplaceFlags() << rfReplaceAll );

			rec = rec.sprintf ( "%s???%s???%d???%s???%s???%s???%s???%s???%s???%s???%d???%d???%d???%d???%s???%s???%s???%s???%s???%s???%s" ,
						DM->ConsignmentsViewWarehouseCode->AsAnsiString.Trim().c_str(),
						DM->ConsignmentsViewCustomerReference->AsAnsiString.Trim().c_str(),
						ParcelSeq ,
						DM->ConsignmentsViewRecipientName->AsAnsiString.Trim().c_str(),
						DM->ConsignmentsViewRecipientAddress1->AsAnsiString.Trim().c_str(),
						DM->ConsignmentsViewRecipientAddress2->AsAnsiString.Trim().c_str(),
						DM->ConsignmentsViewRecipientAddress3->AsAnsiString.Trim().c_str(),
						DM->ConsignmentsViewRecipientAddress4->AsAnsiString.Trim().c_str(),
						DM->ConsignmentsViewRecipientPostCode->AsAnsiString.Trim().c_str(),
						( DM->ConsignmentsViewDeliveryInstructions->IsNull ? "" :
							DM->ConsignmentsViewDeliveryInstructions->AsAnsiString.Trim().c_str() ),
						DM->ConsignmentsViewWeight->AsInteger ,
						DM->ConsignmentsViewDimX->AsInteger ,
						DM->ConsignmentsViewDimY->AsInteger ,
						DM->ConsignmentsViewDimZ->AsInteger ,
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

			rec = StringReplace(rec , "," , " " , TReplaceFlags() << rfReplaceAll );
			rec = StringReplace(rec , "<" , " " , TReplaceFlags() << rfReplaceAll );
			rec = StringReplace(rec , ">" , " " , TReplaceFlags() << rfReplaceAll );
			rec = StringReplace(rec , "\r" , "" , TReplaceFlags() << rfReplaceAll );
			rec = StringReplace(rec , "\n" , "" , TReplaceFlags() << rfReplaceAll );
			rec = StringReplace(rec , "\"" , "" , TReplaceFlags() << rfReplaceAll );

			AnsiString RemoveChars = "<>,!$%^~";
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


			LastKey = DM->ConsignmentsViewCustomerReference->AsAnsiString.Trim();
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
				DM->ConsignmentsViewWarehouseCode->AsString.Length() == 0)
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

			if ( minWt > 0 || maxWt > 0 ) {
				// check the weight of the item
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
			actUpdateCSVChecked->Execute();
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

			DM->cmdUpdateCSVDate->Parameters->ParamByName("cid")->Value
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
			Memo1->Lines->Insert(0,Now().FormatString("yyyy-mm-dd hh:nn:ss") + " Parcel [" + Parcel + "]" );
			txtBarcodeLookup->Text = Parcel;

			TObject *Sender = new TObject();

			unsigned short Key = 13;
			TShiftState ss = TShiftState();

			txtBarcodeLookupKeyDown(Sender , Key , ss );
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


	PageControl1->ActivePage = tabConsignments ;


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
	TBookmark bm = DM->ConsignmentsView->GetBookmark() ;

	DM->ConsignmentsView->Requery();


	try
	{
        DM->ConsignmentsView->GotoBookmark(bm);
	}
	catch(...)
	{

    }
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
		DM->ConsignmentsWarehouseCode->Value =
			DM->SupplierServicesWarehouse->Value;

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
	UpdateConsignmentView(Sender);

}
//---------------------------------------------------------------------------


void __fastcall TfmConsign::UpdateConsignmentView(TObject *Sender)
{
	TADOQuery *Q = DM->ConsignmentsView ;
	try
	{
		Q->DisableControls() ;
		Q->Close() ;
		Q->SQL->Strings[4] = "";
		Q->SQL->Strings[5] = "";

		// cater for the show all check box
		if ( ! cbxShowAll->Checked )
		{
			Q->SQL->Strings[4] = " where Consignments.CSVCreatedOn is null";
		}

		// cater for the supplier filter box
		if ( !  CurrentMPIFilter.IsEmpty() ) {
			if ( Q->SQL->Strings[4].IsEmpty()  ) {
				DM->ConsignmentsView->SQL->Strings[4] = "where Identifier='" + CurrentMPIFilter.Trim() + "'";
			}
			else
			{
				DM->ConsignmentsView->SQL->Strings[5] = " and  Identifier='" + CurrentMPIFilter.Trim() + "'";
			}
		}

		// reopen the dataset
//		MessageDlg ( Q->SQL->Text , mtInformation , TMsgDlgButtons() << mbOK , 0 );
		Q->Open();

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
