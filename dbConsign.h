//---------------------------------------------------------------------------

#ifndef dbConsignH
#define dbConsignH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
//---------------------------------------------------------------------------
class TDM : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *DB;
	TADOQuery *Consignments;
	TLargeintField *ConsignmentsConsignmentID;
	TStringField *ConsignmentsWarehouseCode;
	TStringField *ConsignmentsCustomerReference;
	TStringField *ConsignmentsRecipientName;
	TStringField *ConsignmentsRecipientAddress1;
	TStringField *ConsignmentsRecipientAddress2;
	TStringField *ConsignmentsRecipientAddress3;
	TStringField *ConsignmentsRecipientAddress4;
	TStringField *ConsignmentsRecipientPostCode;
	TStringField *ConsignmentsDeliveryInstructions;
	TStringField *ConsignmentsPrimaryTelephone;
	TLargeintField *ConsignmentsServiceCode;
	TStringField *ConsignmentsSecondTelephone;
	TStringField *ConsignmentsEmail;
	TADOTable *Services;
	TDataSource *dsServices;
	TDataSource *dsConsignments;
	TLargeintField *ServicesServiceID;
	TStringField *ServicesServiceCode;
	TIntegerField *ServicesServiceAvailable;
	TStringField *ServicesServiceDescription;
	TADOQuery *ProductTypes;
	TLargeintField *ProductTypesProductTypeID;
	TStringField *ProductTypesProductType;
	TStringField *ProductTypesDescription;
	TDataSource *dsProductTypes;
	TDataSource *dsConsignmentItems;
	TADOTable *ConsignmentItems;
	TADOQuery *OrderLookUp;
	TADOCommand *cmdUpdateHDNL;
	TLargeintField *ConsignmentItemsConsignmentItemID;
	TLargeintField *ConsignmentItemsConsignmentID;
	TIntegerField *ConsignmentItemsWeight;
	TIntegerField *ConsignmentItemsDimX;
	TIntegerField *ConsignmentItemsDimY;
	TIntegerField *ConsignmentItemsDimZ;
	TStringField *ConsignmentItemsClientProductDescription;
	TStringField *ConsignmentItemsClientProductCode;
	TStringField *ConsignmentItemsHDNLProductCode;
	TDateTimeField *ConsignmentsCSVCreatedOn;
	TADOQuery *ItemLookup;
	TWideStringField *OrderLookUpAgency;
	TWideStringField *OrderLookUpCustomerName;
	TWideStringField *OrderLookUpAddress1;
	TWideStringField *OrderLookUpAddress2;
	TWideStringField *OrderLookUpAddress3;
	TWideStringField *OrderLookUpAddress4;
	TWideStringField *OrderLookUpAddress5;
	TWideStringField *OrderLookUpAddress6;
	TWideStringField *OrderLookUpPostcode;
	TWideStringField *OrderLookUpPhone;
	TIntegerField *OrderLookUpOrderDate;
	TWideStringField *OrderLookUpOrderNumber;
	TIntegerField *OrderLookUpOrderLine;
	TWideStringField *OrderLookUpParcel;
	TWideStringField *OrderLookUpInvoice;
	TDateTimeField *OrderLookUpDateLoaded;
	TStringField *OrderLookUpCat;
	TWideStringField *OrderLookUpOpt;
	TWideStringField *OrderLookUpDescription;
	TFloatField *OrderLookUpPrice;
	TIntegerField *OrderLookUpDim1;
	TIntegerField *OrderLookUpDim3;
	TIntegerField *OrderLookUpDim2;
	TIntegerField *OrderLookUpVolume;
	TIntegerField *OrderLookUpWeight;
	TStringField *OrderLookUpHDNLCode;
	TStringField *ItemLookupCat;
	TWideStringField *ItemLookupOpt;
	TWideStringField *ItemLookupDescription;
	TIntegerField *ItemLookupDim1;
	TIntegerField *ItemLookupDim2;
	TIntegerField *ItemLookupDim3;
	TIntegerField *ItemLookupVolume;
	TIntegerField *ItemLookupWeight;
	TFloatField *ItemLookupPrice;
	TLargeintField *ItemLookupOptionID;
	TStringField *ItemLookupHDNLCode;
	TDataSource *dsItemLookup;
	TADOQuery *ConsignmentsView;
	TDataSource *dsConsignmentsView;
	TADOCommand *cmdUpdateCSVDate;
	TDateTimeField *ConsignmentsCreatedOn;
	TIntegerField *ServicesMinWeight;
	TIntegerField *ServicesMaxWeight;
	TADOQuery *DSVSuppliers;
	TDataSource *dsDSVSuppliers;
	TLargeintField *DSVSuppliersSupplierID;
	TStringField *DSVSuppliersSupplierCode;
	TStringField *DSVSuppliersSupplierName;
	TStringField *DSVSuppliersMetapackIndicator;
	TStringField *DSVSuppliersNetworkExitPoint;
	TStringField *DSVSuppliersContactName;
	TStringField *DSVSuppliersContactNumber;
	TStringField *DSVSuppliersEmailAddress;
	TStringField *DSVSuppliersAddress;
	TStringField *DSVSuppliersPostCode;
	TStringField *DSVSuppliersCollectionDates;
	TADOQuery *SupplierServices;
	TDataSource *dsSupplierServices;
	TStringField *ServicesWarehouse;
	TStringField *ServicesTAC;
	TStringField *SupplierServicesSupplierCode;
	TStringField *SupplierServicesSupplierName;
	TStringField *SupplierServicesMetapackIndicator;
	TFloatField *SupplierServicesAccount;
	TWideStringField *SupplierServicesWarehouse;
	TLargeintField *SupplierServicesWarehouseCodeID;
	TADOQuery *SuppServices;
	TDataSource *dsSuppServices;
	TLargeintField *ConsignmentsViewConsignmentID;
	TStringField *ConsignmentsViewWarehouseCode;
	TStringField *ConsignmentsViewCustomerReference;
	TStringField *ConsignmentsViewRecipientName;
	TStringField *ConsignmentsViewRecipientAddress1;
	TStringField *ConsignmentsViewRecipientAddress2;
	TStringField *ConsignmentsViewRecipientAddress3;
	TStringField *ConsignmentsViewRecipientAddress4;
	TStringField *ConsignmentsViewRecipientPostCode;
	TStringField *ConsignmentsViewDeliveryInstructions;
	TStringField *ConsignmentsViewPrimaryTelephone;
	TLargeintField *ConsignmentsViewServiceCode;
	TStringField *ConsignmentsViewSecondTelephone;
	TStringField *ConsignmentsViewEmail;
	TDateTimeField *ConsignmentsViewCSVCreatedOn;
	TDateTimeField *ConsignmentsViewCreatedOn;
	TLargeintField *ConsignmentsViewConsignmentItemID;
	TLargeintField *ConsignmentsViewConsignmentID_1;
	TIntegerField *ConsignmentsViewWeight;
	TIntegerField *ConsignmentsViewDimX;
	TIntegerField *ConsignmentsViewDimY;
	TIntegerField *ConsignmentsViewDimZ;
	TStringField *ConsignmentsViewClientProductDescription;
	TStringField *ConsignmentsViewClientProductCode;
	TStringField *ConsignmentsViewHDNLProductCode;
	TFloatField *ConsignmentsViewAccount;
	TWideStringField *ConsignmentsViewTAC;
	TWideStringField *ConsignmentsViewIdentifier;
	TWideStringField *ConsignmentsViewAccountName;
	TFloatField *ConsignmentsViewServiceCode_1;
	TWideStringField *ConsignmentsViewWarehouse;
	TLargeintField *ConsignmentsViewWarehouseCodeID;
	TIntegerField *ConsignmentsViewMinWeight;
	TIntegerField *ConsignmentsViewMaxWeight;
	TFloatField *SuppServicesAccount;
	TWideStringField *SuppServicesTAC;
	TWideStringField *SuppServicesIdentifier;
	TWideStringField *SuppServicesAccountName;
	TFloatField *SuppServicesServiceCode;
	TWideStringField *SuppServicesWarehouse;
	TLargeintField *SuppServicesWarehouseCodeID;
	TIntegerField *SuppServicesMinWeight;
	TIntegerField *SuppServicesMaxWeight;
	TWideStringField *SupplierServicesAccountName;
	TFloatField *SupplierServicesServiceCode;
	TWideStringField *SuppServicesSupplierName;
	void __fastcall ServicesServiceAvailableGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText);
	void __fastcall ServicesServiceAvailableSetText(TField *Sender, const UnicodeString Text);
	void __fastcall ServicesServiceCodeSetText(TField *Sender, const UnicodeString Text);
	void __fastcall ConsignmentItemsBeforeInsert(TDataSet *DataSet);
	void __fastcall ConsignmentItemsAfterPost(TDataSet *DataSet);
	void __fastcall ConsignmentsNewRecord(TDataSet *DataSet);


private:	// User declarations
public:		// User declarations
	__fastcall TDM(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDM *DM;
//---------------------------------------------------------------------------
#endif
