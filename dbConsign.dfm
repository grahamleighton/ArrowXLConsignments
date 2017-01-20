object DM: TDM
  OldCreateOrder = False
  Height = 519
  Width = 709
  object DB: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=CityLink;Data Source=FGH-SQL02'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 40
    Top = 32
  end
  object Consignments: TADOQuery
    Connection = DB
    CursorType = ctStatic
    OnNewRecord = ConsignmentsNewRecord
    Parameters = <>
    SQL.Strings = (
      'select * from Consignments order by consignmentid desc')
    Left = 144
    Top = 32
    object ConsignmentsConsignmentID: TLargeintField
      FieldName = 'ConsignmentID'
      ReadOnly = True
    end
    object ConsignmentsWarehouseCode: TStringField
      FieldName = 'WarehouseCode'
      Size = 10
    end
    object ConsignmentsCustomerReference: TStringField
      FieldName = 'CustomerReference'
      Size = 22
    end
    object ConsignmentsRecipientName: TStringField
      FieldName = 'RecipientName'
      Size = 50
    end
    object ConsignmentsRecipientAddress1: TStringField
      FieldName = 'RecipientAddress1'
      Size = 50
    end
    object ConsignmentsRecipientAddress2: TStringField
      FieldName = 'RecipientAddress2'
      Size = 50
    end
    object ConsignmentsRecipientAddress3: TStringField
      FieldName = 'RecipientAddress3'
      Size = 50
    end
    object ConsignmentsRecipientAddress4: TStringField
      FieldName = 'RecipientAddress4'
      Size = 50
    end
    object ConsignmentsRecipientPostCode: TStringField
      FieldName = 'RecipientPostCode'
      Size = 9
    end
    object ConsignmentsDeliveryInstructions: TStringField
      FieldName = 'DeliveryInstructions'
      Size = 50
    end
    object ConsignmentsPrimaryTelephone: TStringField
      FieldName = 'PrimaryTelephone'
      Size = 16
    end
    object ConsignmentsServiceCode: TLargeintField
      FieldName = 'ServiceCode'
    end
    object ConsignmentsSecondTelephone: TStringField
      FieldName = 'SecondTelephone'
      Size = 16
    end
    object ConsignmentsEmail: TStringField
      FieldName = 'Email'
      Size = 100
    end
    object ConsignmentsCSVCreatedOn: TDateTimeField
      FieldName = 'CSVCreatedOn'
    end
    object ConsignmentsCreatedOn: TDateTimeField
      FieldName = 'CreatedOn'
    end
  end
  object Services: TADOTable
    Connection = DB
    CursorType = ctStatic
    TableName = 'Services'
    Left = 144
    Top = 96
    object ServicesServiceID: TLargeintField
      FieldName = 'ServiceID'
      ReadOnly = True
    end
    object ServicesServiceCode: TStringField
      DisplayWidth = 7
      FieldName = 'ServiceCode'
      Required = True
      OnSetText = ServicesServiceCodeSetText
      Size = 7
    end
    object ServicesServiceAvailable: TIntegerField
      FieldName = 'ServiceAvailable'
      OnGetText = ServicesServiceAvailableGetText
      OnSetText = ServicesServiceAvailableSetText
    end
    object ServicesServiceDescription: TStringField
      DisplayWidth = 20
      FieldName = 'ServiceDescription'
      Size = 150
    end
    object ServicesMinWeight: TIntegerField
      FieldName = 'MinWeight'
    end
    object ServicesMaxWeight: TIntegerField
      FieldName = 'MaxWeight'
    end
    object ServicesWarehouse: TStringField
      FieldName = 'Warehouse'
      Size = 5
    end
    object ServicesTAC: TStringField
      FieldName = 'TAC'
      Size = 4
    end
  end
  object dsServices: TDataSource
    DataSet = Services
    Left = 224
    Top = 96
  end
  object dsConsignments: TDataSource
    DataSet = Consignments
    Left = 224
    Top = 32
  end
  object ProductTypes: TADOQuery
    Connection = DB
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from ProductTypes'
      'where allowusage=1'
      'order by Description')
    Left = 144
    Top = 168
    object ProductTypesProductTypeID: TLargeintField
      FieldName = 'ProductTypeID'
      ReadOnly = True
    end
    object ProductTypesProductType: TStringField
      DisplayWidth = 3
      FieldName = 'ProductType'
      FixedChar = True
      Size = 2
    end
    object ProductTypesDescription: TStringField
      FieldName = 'Description'
      Size = 50
    end
  end
  object dsProductTypes: TDataSource
    DataSet = ProductTypes
    Left = 224
    Top = 168
  end
  object dsConsignmentItems: TDataSource
    DataSet = ConsignmentItems
    Left = 448
    Top = 32
  end
  object ConsignmentItems: TADOTable
    Connection = DB
    CursorType = ctStatic
    AfterPost = ConsignmentItemsAfterPost
    IndexFieldNames = 'ConsignmentID'
    MasterFields = 'ConsignmentID'
    MasterSource = dsConsignments
    TableName = 'ConsignmentItems'
    Left = 336
    Top = 32
    object ConsignmentItemsConsignmentItemID: TLargeintField
      FieldName = 'ConsignmentItemID'
      ReadOnly = True
    end
    object ConsignmentItemsConsignmentID: TLargeintField
      FieldName = 'ConsignmentID'
    end
    object ConsignmentItemsWeight: TIntegerField
      FieldName = 'Weight'
    end
    object ConsignmentItemsDimX: TIntegerField
      FieldName = 'DimX'
    end
    object ConsignmentItemsDimY: TIntegerField
      FieldName = 'DimY'
    end
    object ConsignmentItemsDimZ: TIntegerField
      FieldName = 'DimZ'
    end
    object ConsignmentItemsClientProductDescription: TStringField
      FieldName = 'ClientProductDescription'
    end
    object ConsignmentItemsClientProductCode: TStringField
      FieldName = 'ClientProductCode'
    end
    object ConsignmentItemsHDNLProductCode: TStringField
      FieldName = 'HDNLProductCode'
      FixedChar = True
      Size = 2
    end
  end
  object OrderLookUp: TADOQuery
    Connection = DB
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'pcl'
        Attributes = [paNullable]
        DataType = ftWideString
        NumericScale = 255
        Precision = 255
        Size = 16
        Value = Null
      end>
    SQL.Strings = (
      'select * from viewCityDetailsArrow where parcel=:pcl')
    Left = 144
    Top = 232
    object OrderLookUpAgency: TWideStringField
      FieldName = 'Agency'
      Size = 10
    end
    object OrderLookUpCustomerName: TWideStringField
      FieldName = 'CustomerName'
      Size = 32
    end
    object OrderLookUpAddress1: TWideStringField
      FieldName = 'Address1'
      Size = 32
    end
    object OrderLookUpAddress2: TWideStringField
      FieldName = 'Address2'
      Size = 32
    end
    object OrderLookUpAddress3: TWideStringField
      FieldName = 'Address3'
      Size = 32
    end
    object OrderLookUpAddress4: TWideStringField
      FieldName = 'Address4'
      Size = 32
    end
    object OrderLookUpAddress5: TWideStringField
      FieldName = 'Address5'
      Size = 32
    end
    object OrderLookUpAddress6: TWideStringField
      FieldName = 'Address6'
      Size = 32
    end
    object OrderLookUpPostcode: TWideStringField
      FieldName = 'Postcode'
      Size = 10
    end
    object OrderLookUpPhone: TWideStringField
      FieldName = 'Phone'
      Size = 15
    end
    object OrderLookUpOrderDate: TIntegerField
      FieldName = 'OrderDate'
    end
    object OrderLookUpOrderNumber: TWideStringField
      FieldName = 'OrderNumber'
      Size = 9
    end
    object OrderLookUpOrderLine: TIntegerField
      FieldName = 'OrderLine'
    end
    object OrderLookUpParcel: TWideStringField
      FieldName = 'Parcel'
      FixedChar = True
      Size = 16
    end
    object OrderLookUpInvoice: TWideStringField
      FieldName = 'Invoice'
      Size = 7
    end
    object OrderLookUpDateLoaded: TDateTimeField
      FieldName = 'DateLoaded'
    end
    object OrderLookUpCat: TStringField
      FieldName = 'Cat'
      Size = 10
    end
    object OrderLookUpOpt: TWideStringField
      FieldName = 'Opt'
      FixedChar = True
      Size = 2
    end
    object OrderLookUpDescription: TWideStringField
      FieldName = 'Description'
      FixedChar = True
    end
    object OrderLookUpPrice: TFloatField
      FieldName = 'Price'
    end
    object OrderLookUpDim1: TIntegerField
      FieldName = 'Dim1'
    end
    object OrderLookUpDim3: TIntegerField
      FieldName = 'Dim3'
    end
    object OrderLookUpDim2: TIntegerField
      FieldName = 'Dim2'
    end
    object OrderLookUpVolume: TIntegerField
      FieldName = 'Volume'
    end
    object OrderLookUpWeight: TIntegerField
      FieldName = 'Weight'
    end
    object OrderLookUpHDNLCode: TStringField
      FieldName = 'HDNLCode'
      FixedChar = True
      Size = 2
    end
  end
  object cmdUpdateHDNL: TADOCommand
    CommandText = 
      'update OptionData '#13#10'set HDNLCode=:hdc'#13#10'where Cat=:cat and [opt]=' +
      ':opt'
    Connection = DB
    Parameters = <
      item
        Name = 'hdc'
        Attributes = [paNullable]
        DataType = ftString
        NumericScale = 255
        Precision = 255
        Size = 2
        Value = Null
      end
      item
        Name = 'cat'
        DataType = ftString
        NumericScale = 255
        Precision = 255
        Size = 10
        Value = Null
      end
      item
        Name = 'opt'
        DataType = ftWideString
        NumericScale = 255
        Precision = 255
        Size = 2
        Value = Null
      end>
    Left = 336
    Top = 96
  end
  object ItemLookup: TADOQuery
    Connection = DB
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'cat'
        DataType = ftString
        NumericScale = 255
        Precision = 255
        Size = 10
        Value = 'BENCH'
      end
      item
        Name = 'cat2'
        Attributes = [paNullable]
        DataType = ftWideString
        NumericScale = 255
        Precision = 255
        Size = 20
        Value = '%BENCH%'
      end>
    SQL.Strings = (
      
        'select * from OptionData where cat=:cat or description like :cat' +
        '2')
    Left = 224
    Top = 232
    object ItemLookupCat: TStringField
      FieldName = 'Cat'
      Size = 10
    end
    object ItemLookupOpt: TWideStringField
      FieldName = 'Opt'
      FixedChar = True
      Size = 2
    end
    object ItemLookupDescription: TWideStringField
      FieldName = 'Description'
      FixedChar = True
    end
    object ItemLookupDim1: TIntegerField
      FieldName = 'Dim1'
    end
    object ItemLookupDim2: TIntegerField
      FieldName = 'Dim2'
    end
    object ItemLookupDim3: TIntegerField
      FieldName = 'Dim3'
    end
    object ItemLookupVolume: TIntegerField
      FieldName = 'Volume'
    end
    object ItemLookupWeight: TIntegerField
      FieldName = 'Weight'
    end
    object ItemLookupPrice: TFloatField
      FieldName = 'Price'
    end
    object ItemLookupOptionID: TLargeintField
      FieldName = 'OptionID'
      ReadOnly = True
    end
    object ItemLookupHDNLCode: TStringField
      FieldName = 'HDNLCode'
      FixedChar = True
      Size = 2
    end
  end
  object dsItemLookup: TDataSource
    DataSet = ItemLookup
    Left = 336
    Top = 232
  end
  object ConsignmentsView: TADOQuery
    Active = True
    Connection = DB
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * '
      'from Consignments'
      
        'inner join ConsignmentItems on Consignments.ConsignmentID = Cons' +
        'ignmentItems.ConsignmentID'
      
        'inner join dbo.WarehouseCodes on Consignments.ServiceCode = Ware' +
        'houseCodes.WarehouseCodeID'
      ''
      ''
      ''
      ''
      'order by Consignments.ConsignmentID'
      ''
      '')
    Left = 440
    Top = 96
    object ConsignmentsViewConsignmentID: TLargeintField
      FieldName = 'ConsignmentID'
      ReadOnly = True
    end
    object ConsignmentsViewWarehouseCode: TStringField
      FieldName = 'WarehouseCode'
      Size = 10
    end
    object ConsignmentsViewCustomerReference: TStringField
      FieldName = 'CustomerReference'
      Size = 22
    end
    object ConsignmentsViewRecipientName: TStringField
      FieldName = 'RecipientName'
      Size = 50
    end
    object ConsignmentsViewRecipientAddress1: TStringField
      FieldName = 'RecipientAddress1'
      Size = 50
    end
    object ConsignmentsViewRecipientAddress2: TStringField
      FieldName = 'RecipientAddress2'
      Size = 50
    end
    object ConsignmentsViewRecipientAddress3: TStringField
      FieldName = 'RecipientAddress3'
      Size = 50
    end
    object ConsignmentsViewRecipientAddress4: TStringField
      FieldName = 'RecipientAddress4'
      Size = 50
    end
    object ConsignmentsViewRecipientPostCode: TStringField
      FieldName = 'RecipientPostCode'
      Size = 9
    end
    object ConsignmentsViewDeliveryInstructions: TStringField
      FieldName = 'DeliveryInstructions'
      Size = 50
    end
    object ConsignmentsViewPrimaryTelephone: TStringField
      FieldName = 'PrimaryTelephone'
      Size = 16
    end
    object ConsignmentsViewServiceCode: TLargeintField
      FieldName = 'ServiceCode'
    end
    object ConsignmentsViewSecondTelephone: TStringField
      FieldName = 'SecondTelephone'
      Size = 16
    end
    object ConsignmentsViewEmail: TStringField
      FieldName = 'Email'
      Size = 100
    end
    object ConsignmentsViewCSVCreatedOn: TDateTimeField
      FieldName = 'CSVCreatedOn'
    end
    object ConsignmentsViewCreatedOn: TDateTimeField
      FieldName = 'CreatedOn'
    end
    object ConsignmentsViewConsignmentItemID: TLargeintField
      FieldName = 'ConsignmentItemID'
      ReadOnly = True
    end
    object ConsignmentsViewConsignmentID_1: TLargeintField
      FieldName = 'ConsignmentID_1'
    end
    object ConsignmentsViewWeight: TIntegerField
      FieldName = 'Weight'
    end
    object ConsignmentsViewDimX: TIntegerField
      FieldName = 'DimX'
    end
    object ConsignmentsViewDimY: TIntegerField
      FieldName = 'DimY'
    end
    object ConsignmentsViewDimZ: TIntegerField
      FieldName = 'DimZ'
    end
    object ConsignmentsViewClientProductDescription: TStringField
      FieldName = 'ClientProductDescription'
    end
    object ConsignmentsViewClientProductCode: TStringField
      FieldName = 'ClientProductCode'
    end
    object ConsignmentsViewHDNLProductCode: TStringField
      FieldName = 'HDNLProductCode'
      FixedChar = True
      Size = 2
    end
    object ConsignmentsViewAccount: TFloatField
      FieldName = 'Account'
    end
    object ConsignmentsViewTAC: TWideStringField
      FieldName = 'TAC'
      Size = 255
    end
    object ConsignmentsViewIdentifier: TWideStringField
      FieldName = 'Identifier'
      Size = 255
    end
    object ConsignmentsViewAccountName: TWideStringField
      FieldName = 'AccountName'
      Size = 255
    end
    object ConsignmentsViewServiceCode_1: TFloatField
      FieldName = 'ServiceCode_1'
    end
    object ConsignmentsViewWarehouse: TWideStringField
      FieldName = 'Warehouse'
      Size = 255
    end
    object ConsignmentsViewWarehouseCodeID: TLargeintField
      FieldName = 'WarehouseCodeID'
      ReadOnly = True
    end
    object ConsignmentsViewMinWeight: TIntegerField
      FieldName = 'MinWeight'
    end
    object ConsignmentsViewMaxWeight: TIntegerField
      FieldName = 'MaxWeight'
    end
  end
  object dsConsignmentsView: TDataSource
    DataSet = ConsignmentsView
    Left = 536
    Top = 104
  end
  object cmdUpdateCSVDate: TADOCommand
    CommandText = 
      'update '#13#10' Consignments'#13#10'set CSVCreatedOn=getdate()'#13#10'where Consig' +
      'nmentID=:cid'
    Connection = DB
    Parameters = <
      item
        Name = 'cid'
        Attributes = [paSigned]
        DataType = ftLargeint
        Precision = 19
        Size = 8
        Value = Null
      end>
    Left = 336
    Top = 168
  end
  object DSVSuppliers: TADOQuery
    Active = True
    Connection = DB
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from DSVSuppliers')
    Left = 144
    Top = 296
    object DSVSuppliersSupplierID: TLargeintField
      FieldName = 'SupplierID'
      ReadOnly = True
    end
    object DSVSuppliersSupplierCode: TStringField
      FieldName = 'SupplierCode'
      Size = 5
    end
    object DSVSuppliersSupplierName: TStringField
      FieldName = 'SupplierName'
      Size = 70
    end
    object DSVSuppliersMetapackIndicator: TStringField
      FieldName = 'MetapackIndicator'
      FixedChar = True
      Size = 1
    end
    object DSVSuppliersNetworkExitPoint: TStringField
      FieldName = 'NetworkExitPoint'
    end
    object DSVSuppliersContactName: TStringField
      FieldName = 'ContactName'
      Size = 50
    end
    object DSVSuppliersContactNumber: TStringField
      FieldName = 'ContactNumber'
    end
    object DSVSuppliersEmailAddress: TStringField
      FieldName = 'EmailAddress'
      Size = 50
    end
    object DSVSuppliersAddress: TStringField
      FieldName = 'Address'
      Size = 150
    end
    object DSVSuppliersPostCode: TStringField
      FieldName = 'PostCode'
      Size = 12
    end
    object DSVSuppliersCollectionDates: TStringField
      FieldName = 'CollectionDates'
      Size = 150
    end
  end
  object dsDSVSuppliers: TDataSource
    AutoEdit = False
    DataSet = DSVSuppliers
    Left = 224
    Top = 296
  end
  object SupplierServices: TADOQuery
    Connection = DB
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from viewSupplierServices'
      'order by SupplierName')
    Left = 336
    Top = 296
    object SupplierServicesSupplierCode: TStringField
      FieldName = 'SupplierCode'
      Size = 5
    end
    object SupplierServicesSupplierName: TStringField
      DisplayWidth = 15
      FieldName = 'SupplierName'
      Size = 70
    end
    object SupplierServicesMetapackIndicator: TStringField
      FieldName = 'MetapackIndicator'
      FixedChar = True
      Size = 1
    end
    object SupplierServicesAccount: TFloatField
      FieldName = 'Account'
    end
    object SupplierServicesWarehouse: TWideStringField
      FieldName = 'Warehouse'
      Size = 255
    end
    object SupplierServicesWarehouseCodeID: TLargeintField
      FieldName = 'WarehouseCodeID'
    end
    object SupplierServicesAccountName: TWideStringField
      FieldName = 'AccountName'
      Size = 255
    end
    object SupplierServicesServiceCode: TFloatField
      FieldName = 'ServiceCode'
    end
  end
  object dsSupplierServices: TDataSource
    DataSet = SupplierServices
    Left = 448
    Top = 296
  end
  object SuppServices: TADOQuery
    Connection = DB
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from WarehouseCodes'
      'order by Identifier,Warehouse')
    Left = 432
    Top = 176
    object SuppServicesAccount: TFloatField
      FieldName = 'Account'
    end
    object SuppServicesTAC: TWideStringField
      FieldName = 'TAC'
      Size = 255
    end
    object SuppServicesIdentifier: TWideStringField
      FieldName = 'Identifier'
      Size = 255
    end
    object SuppServicesAccountName: TWideStringField
      FieldName = 'AccountName'
      Size = 255
    end
    object SuppServicesServiceCode: TFloatField
      FieldName = 'ServiceCode'
    end
    object SuppServicesWarehouse: TWideStringField
      FieldName = 'Warehouse'
      Size = 255
    end
    object SuppServicesWarehouseCodeID: TLargeintField
      FieldName = 'WarehouseCodeID'
      ReadOnly = True
    end
    object SuppServicesMinWeight: TIntegerField
      FieldName = 'MinWeight'
    end
    object SuppServicesMaxWeight: TIntegerField
      FieldName = 'MaxWeight'
    end
    object SuppServicesSupplierName: TWideStringField
      FieldName = 'SupplierName'
      Size = 255
    end
  end
  object dsSuppServices: TDataSource
    DataSet = SuppServices
    Left = 536
    Top = 168
  end
end
