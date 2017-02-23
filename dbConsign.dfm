object DM: TDM
  OldCreateOrder = False
  Height = 519
  Width = 709
  object DB: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=CityLink;Data Source=FGH-SQL01;Use Proc' +
      'edure for Prepare=1;Auto Translate=True;Packet Size=4096;Worksta' +
      'tion ID=VDIW81PERS-7;Use Encryption for Data=False;Tag with colu' +
      'mn collation when possible=False'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 40
    Top = 32
  end
  object Consignments: TADOQuery
    Connection = DB
    CursorType = ctStatic
    AfterScroll = ConsignmentsAfterScroll
    OnNewRecord = ConsignmentsNewRecord
    Parameters = <>
    SQL.Strings = (
      'select * from viewAXLConsignments order by consignmentid desc')
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
    TableDirect = True
    TableName = 'viewAXLWarehouseCodes'
    Left = 144
    Top = 96
    object ServicesAccount: TFloatField
      FieldName = 'Account'
    end
    object ServicesTAC: TWideStringField
      FieldName = 'TAC'
      Size = 255
    end
    object ServicesIdentifier: TWideStringField
      FieldName = 'Identifier'
      Size = 255
    end
    object ServicesAccountName: TWideStringField
      FieldName = 'AccountName'
      Size = 255
    end
    object ServicesServiceCode: TFloatField
      FieldName = 'ServiceCode'
    end
    object ServicesWarehouse: TWideStringField
      FieldName = 'Warehouse'
      Size = 255
    end
    object ServicesWarehouseCodeID: TLargeintField
      FieldName = 'WarehouseCodeID'
      ReadOnly = True
    end
    object ServicesMinWeight: TIntegerField
      FieldName = 'MinWeight'
    end
    object ServicesMaxWeight: TIntegerField
      FieldName = 'MaxWeight'
    end
    object ServicesSupplierName: TWideStringField
      FieldName = 'SupplierName'
      Size = 255
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
      'select * from viewAXLProductTypes'
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
    TableName = 'viewAXLConsignmentItems'
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
      'select * from viewAXLOrderDetails where parcel=:pcl')
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
    object OrderLookUpDD1Dim1: TIntegerField
      FieldName = 'DD1Dim1'
    end
    object OrderLookUpDD1Dim2: TIntegerField
      FieldName = 'DD1Dim2'
    end
    object OrderLookUpDD1Dim3: TIntegerField
      FieldName = 'DD1Dim3'
    end
    object OrderLookUpDD1Weight: TIntegerField
      FieldName = 'DD1Weight'
    end
    object OrderLookUpDD2Dim1: TIntegerField
      FieldName = 'DD2Dim1'
    end
    object OrderLookUpDD2Dim2: TIntegerField
      FieldName = 'DD2Dim2'
    end
    object OrderLookUpDD2Dim3: TIntegerField
      FieldName = 'DD2Dim3'
    end
    object OrderLookUpDD2Weight: TIntegerField
      FieldName = 'DD2Weight'
    end
    object OrderLookUpDD3Dim1: TIntegerField
      FieldName = 'DD3Dim1'
    end
    object OrderLookUpDD3Dim2: TIntegerField
      FieldName = 'DD3Dim2'
    end
    object OrderLookUpDD3Dim3: TIntegerField
      FieldName = 'DD3Dim3'
    end
    object OrderLookUpDD3Weight: TIntegerField
      FieldName = 'DD3Weight'
    end
    object OrderLookUpDD4Dim1: TIntegerField
      FieldName = 'DD4Dim1'
    end
    object OrderLookUpDD4Dim2: TIntegerField
      FieldName = 'DD4Dim2'
    end
    object OrderLookUpDD4Dim3: TIntegerField
      FieldName = 'DD4Dim3'
    end
    object OrderLookUpDD4Weight: TIntegerField
      FieldName = 'DD4Weight'
    end
  end
  object cmdUpdateHDNL: TADOCommand
    CommandText = 'AXLUpdateOptionData;1'
    CommandType = cmdStoredProc
    Connection = DB
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@cat'
        Attributes = [paNullable]
        DataType = ftString
        Size = 6
        Value = Null
      end
      item
        Name = '@opt'
        Attributes = [paNullable]
        DataType = ftString
        Size = 2
        Value = Null
      end
      item
        Name = '@hdc'
        Attributes = [paNullable]
        DataType = ftString
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
      
        'select * from viewAXLOptionData where cat=:cat or description li' +
        'ke :cat2')
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
    object ItemLookupDD1Dim1: TIntegerField
      FieldName = 'DD1Dim1'
    end
    object ItemLookupDD1Dim2: TIntegerField
      FieldName = 'DD1Dim2'
    end
    object ItemLookupDD1Dim3: TIntegerField
      FieldName = 'DD1Dim3'
    end
    object ItemLookupDD1Weight: TIntegerField
      FieldName = 'DD1Weight'
    end
    object ItemLookupDD2Dim1: TIntegerField
      FieldName = 'DD2Dim1'
    end
    object ItemLookupDD2Dim2: TIntegerField
      FieldName = 'DD2Dim2'
    end
    object ItemLookupDD2Dim3: TIntegerField
      FieldName = 'DD2Dim3'
    end
    object ItemLookupDD2Weight: TIntegerField
      FieldName = 'DD2Weight'
    end
    object ItemLookupDD3Dim1: TIntegerField
      FieldName = 'DD3Dim1'
    end
    object ItemLookupDD3Dim2: TIntegerField
      FieldName = 'DD3Dim2'
    end
    object ItemLookupDD3Dim3: TIntegerField
      FieldName = 'DD3Dim3'
    end
    object ItemLookupDD3Weight: TIntegerField
      FieldName = 'DD3Weight'
    end
    object ItemLookupDD4Dim1: TIntegerField
      FieldName = 'DD4Dim1'
    end
    object ItemLookupDD4Dim2: TIntegerField
      FieldName = 'DD4Dim2'
    end
    object ItemLookupDD4Dim3: TIntegerField
      FieldName = 'DD4Dim3'
    end
    object ItemLookupDD4Weight: TIntegerField
      FieldName = 'DD4Weight'
    end
  end
  object dsItemLookup: TDataSource
    DataSet = ItemLookup
    Left = 336
    Top = 232
  end
  object ConsignmentsView: TADOQuery
    Connection = DB
    CursorType = ctStatic
    AfterPost = ConsignmentsViewAfterPost
    Parameters = <>
    SQL.Strings = (
      'select * '
      'from viewAXLConsignmentsView'
      ''
      ''
      ''
      ''
      ''
      ''
      ''
      ''
      'order by CustomerReference,ClientProductCode'
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
    object ConsignmentsViewSupplierName: TWideStringField
      FieldName = 'SupplierName'
      Size = 255
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
  end
  object dsConsignmentsView: TDataSource
    DataSet = ConsignmentsView
    Left = 536
    Top = 104
  end
  object cmdUpdateCSVDate: TADOCommand
    CommandText = 'AXLSetConsignmentCSVCreated;1'
    CommandType = cmdStoredProc
    Connection = DB
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@cid'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 336
    Top = 168
  end
  object DSVSuppliers: TADOQuery
    Connection = DB
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from viewAXLDSVSuppliers'
      ''
      ''
      ''
      ''
      ''
      'order by SupplierName')
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
      'select * from viewAXLSupplierServices'
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
      'select * from viewAXLWarehouseCodes'
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
  object OrderSearch: TADOQuery
    Connection = DB
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'agy'
        Attributes = [paNullable]
        DataType = ftWideString
        NumericScale = 255
        Precision = 255
        Size = 10
        Value = '669253'
      end>
    SQL.Strings = (
      'select * from viewAXLOrderDetails'
      'where agency=:agy'
      ''
      'order by dateloaded desc')
    Left = 144
    Top = 368
    object OrderSearchAgency: TWideStringField
      FieldName = 'Agency'
      Size = 10
    end
    object OrderSearchCustomerName: TWideStringField
      FieldName = 'CustomerName'
      Size = 32
    end
    object OrderSearchAddress1: TWideStringField
      FieldName = 'Address1'
      Size = 32
    end
    object OrderSearchAddress2: TWideStringField
      FieldName = 'Address2'
      Size = 32
    end
    object OrderSearchAddress3: TWideStringField
      FieldName = 'Address3'
      Size = 32
    end
    object OrderSearchAddress4: TWideStringField
      FieldName = 'Address4'
      Size = 32
    end
    object OrderSearchAddress5: TWideStringField
      FieldName = 'Address5'
      Size = 32
    end
    object OrderSearchAddress6: TWideStringField
      FieldName = 'Address6'
      Size = 32
    end
    object OrderSearchPostcode: TWideStringField
      FieldName = 'Postcode'
      Size = 10
    end
    object OrderSearchPhone: TWideStringField
      FieldName = 'Phone'
      Size = 15
    end
    object OrderSearchOrderDate: TIntegerField
      FieldName = 'OrderDate'
    end
    object OrderSearchOrderNumber: TWideStringField
      FieldName = 'OrderNumber'
      Size = 9
    end
    object OrderSearchOrderLine: TIntegerField
      FieldName = 'OrderLine'
    end
    object OrderSearchParcel: TWideStringField
      FieldName = 'Parcel'
      FixedChar = True
      Size = 16
    end
    object OrderSearchInvoice: TWideStringField
      FieldName = 'Invoice'
      Size = 7
    end
    object OrderSearchDateLoaded: TDateTimeField
      FieldName = 'DateLoaded'
    end
    object OrderSearchCat: TStringField
      FieldName = 'Cat'
      Size = 10
    end
    object OrderSearchOpt: TWideStringField
      FieldName = 'Opt'
      FixedChar = True
      Size = 2
    end
    object OrderSearchDescription: TWideStringField
      FieldName = 'Description'
      FixedChar = True
    end
    object OrderSearchPrice: TFloatField
      FieldName = 'Price'
    end
    object OrderSearchDim1: TIntegerField
      FieldName = 'Dim1'
    end
    object OrderSearchDim3: TIntegerField
      FieldName = 'Dim3'
    end
    object OrderSearchDim2: TIntegerField
      FieldName = 'Dim2'
    end
    object OrderSearchVolume: TIntegerField
      FieldName = 'Volume'
    end
    object OrderSearchWeight: TIntegerField
      FieldName = 'Weight'
    end
    object OrderSearchHDNLCode: TStringField
      FieldName = 'HDNLCode'
      FixedChar = True
      Size = 2
    end
    object OrderSearchDD1Dim1: TIntegerField
      FieldName = 'DD1Dim1'
    end
    object OrderSearchDD1Dim2: TIntegerField
      FieldName = 'DD1Dim2'
    end
    object OrderSearchDD1Dim3: TIntegerField
      FieldName = 'DD1Dim3'
    end
    object OrderSearchDD1Weight: TIntegerField
      FieldName = 'DD1Weight'
    end
    object OrderSearchDD2Dim1: TIntegerField
      FieldName = 'DD2Dim1'
    end
    object OrderSearchDD2Dim2: TIntegerField
      FieldName = 'DD2Dim2'
    end
    object OrderSearchDD2Dim3: TIntegerField
      FieldName = 'DD2Dim3'
    end
    object OrderSearchDD2Weight: TIntegerField
      FieldName = 'DD2Weight'
    end
    object OrderSearchDD3Dim1: TIntegerField
      FieldName = 'DD3Dim1'
    end
    object OrderSearchDD3Dim2: TIntegerField
      FieldName = 'DD3Dim2'
    end
    object OrderSearchDD3Dim3: TIntegerField
      FieldName = 'DD3Dim3'
    end
    object OrderSearchDD3Weight: TIntegerField
      FieldName = 'DD3Weight'
    end
    object OrderSearchDD4Dim1: TIntegerField
      FieldName = 'DD4Dim1'
    end
    object OrderSearchDD4Dim2: TIntegerField
      FieldName = 'DD4Dim2'
    end
    object OrderSearchDD4Dim3: TIntegerField
      FieldName = 'DD4Dim3'
    end
    object OrderSearchDD4Weight: TIntegerField
      FieldName = 'DD4Weight'
    end
  end
  object dsOrderSearch: TDataSource
    DataSet = OrderSearch
    Left = 224
    Top = 368
  end
  object cmdAddConsignment: TADOCommand
    CommandText = 
      'declare @pcl varchar(20);'#13#10'declare @svc int;'#13#10#9#13#10#9'set @svc = :sv' +
      'c;'#13#10#9#13#10#9'set @pcl = :pcl;'#13#10#13#10#9'declare @ConsignmentID int;'#13#10#9'decla' +
      're @Warehouse varchar(10);'#13#10#13#10'select @Warehouse=Warehouse from v' +
      'iewAXLWarehouseCodes  where'#13#10'warehousecodeid=@svc'#13#10'if @@ROWCOUNT' +
      ' = 0 '#13#10'begin'#13#10'  set @Warehouse='#39'MSL'#39';'#13#10'end'#13#10'select * from viewAX' +
      'LOrderDetails where Parcel = @pcl'#13#10#9'if @@ROWCOUNT > 0  '#13#10#9'begin'#13 +
      #10#9#13#10#9#9'insert into Consignments'#13#10#9#9#9'(CustomerReference'#13#10#9#9#9',Prima' +
      'ryTelephone'#13#10#9#9#9',RecipientName'#13#10#9#9#9',RecipientAddress1 '#13#10#9#9#9',Reci' +
      'pientAddress2'#13#10#9#9#9',RecipientAddress3'#13#10#9#9#9',RecipientAddress4'#13#10#9#9#9 +
      ',RecipientPostCode '#13#10#9#9#9',ServiceCode'#13#10#9#9#9',WarehouseCode )'#13#10#9#9'('#13#10 +
      #9#9#9'select top 1'#13#10#9#9#9#9'rtrim(ltrim(v.Agency))+'#39'-'#39'+ltrim(rtrim(Invo' +
      'ice)) as CustRef'#13#10#9#9#9#9',coalesce(v.Phone,'#39#39')'#13#10#9#9#9#9',coalesce(v.Cus' +
      'tomerName,'#39#39')'#13#10#9#9#9#9',coalesce(v.Address1,'#39#39')'#13#10#9#9#9#9',coalesce(v.Add' +
      'ress2,'#39#39')'#13#10#9#9#9#9',coalesce(v.Address3,'#39#39')'#13#10#9#9#9#9',coalesce(v.Address' +
      '4,'#39#39')'#13#10#9#9#9#9',coalesce(v.Postcode,'#39#39')'#13#10#9#9#9#9',@svc'#13#10#9#9#9#9',@Warehouse'#13 +
      #10#9#9#9'   from viewAXLOrderDetails v where Parcel = @pcl'#13#10#9#9')'#13#10#9#9'if' +
      ' @@ROWCOUNT > 0 '#13#10#9#9'begin'#13#10#9#9#9'select @ConsignmentID = SCOPE_IDEN' +
      'TITY()'#13#10#9#9#9#13#10#9#9#9'insert into ConsignmentItems( ClientProductCode'#13 +
      #10#9#9#9#9#9#9#9#9#9#9#9',ClientProductDescription '#13#10#9#9#9#9#9#9#9#9#9#9#9',ConsignmentI' +
      'D'#13#10#9#9#9#9#9#9#9#9#9#9#9',Weight'#13#10#9#9#9#9#9#9#9#9#9#9#9',DimX '#13#10#9#9#9#9#9#9#9#9#9#9#9',DimY'#13#10#9#9#9#9 +
      #9#9#9#9#9#9#9',DimZ'#13#10#9#9#9#9#9#9#9#9#9#9#9',HDNLProductCode )'#13#10#9#9#9#9#9#9#9'('#13#10#9#9#9#9#9#9#9#9's' +
      'elect top 1 '#13#10#9#9#9#9#9#9#9#9#9'RTRIM(ltrim(vi.Cat+'#39'/'#39'+vi.Opt))'#13#10#9#9#9#9#9#9#9#9 +
      #9',coalesce(vi.Description ,'#39#39')'#13#10#9#9#9#9#9#9#9#9#9',@ConsignmentID '#13#10#9#9#9#9#9 +
      #9#9#9#9',coalesce(vi.Weight ,0)'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.Dim1 , 0 )'#13#10#9 +
      #9#9#9#9#9#9#9#9',coalesce(vi.Dim2 , 0 )'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.Dim3 , 0 ' +
      ')'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.HDNLCode,'#39#39') '#13#10#9#9#9#9#9#9#9#9#9'   from viewAXL' +
      'OrderDetails vi where Parcel = @pcl'#13#10#9#9#9#9#9#9#9#9#13#10#9#9#9#9#9#9#9')'#13#10#9#9#9#9#9#9#9 +
      #9#9#9#9#13#10#9#9#9'insert into ConsignmentItems( ClientProductCode'#13#10#9#9#9#9#9#9 +
      #9#9#9#9#9',ClientProductDescription '#13#10#9#9#9#9#9#9#9#9#9#9#9',ConsignmentID'#13#10#9#9#9#9 +
      #9#9#9#9#9#9#9',Weight'#13#10#9#9#9#9#9#9#9#9#9#9#9',DimX '#13#10#9#9#9#9#9#9#9#9#9#9#9',DimY'#13#10#9#9#9#9#9#9#9#9#9#9#9 +
      ',DimZ'#13#10#9#9#9#9#9#9#9#9#9#9#9',HDNLProductCode )'#13#10#9#9#9#9#9#9#9'('#13#10#9#9#9#9#9#9#9#9'select t' +
      'op 1 '#13#10#9#9#9#9#9#9#9#9#9'RTRIM(ltrim(vi.Cat+'#39'/'#39'+vi.Opt))'#13#10#9#9#9#9#9#9#9#9#9',coale' +
      'sce(vi.Description ,'#39#39')'#13#10#9#9#9#9#9#9#9#9#9',@ConsignmentID '#13#10#9#9#9#9#9#9#9#9#9',co' +
      'alesce(vi.DD1Weight ,0) / 1000'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.DD1Dim1 , ' +
      '0 )'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.DD1Dim2 , 0 )'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.' +
      'DD1Dim3 , 0 )'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.HDNLCode,'#39#39') '#13#10#9#9#9#9#9#9#9#9#9'   ' +
      'from viewAXLOrderDetails vi where Parcel = @pcl and coalesce(DD1' +
      'Dim1,0) > 0 '#13#10#9#9#9#9#9#9#9#9#13#10#9#9#9#9#9#9#9')'#13#10#9#9#9#9#9#9#9#9#9#9#9#9#9#9#13#10#9#9#9'insert into' +
      ' ConsignmentItems( ClientProductCode'#13#10#9#9#9#9#9#9#9#9#9#9#9',ClientProductD' +
      'escription '#13#10#9#9#9#9#9#9#9#9#9#9#9',ConsignmentID'#13#10#9#9#9#9#9#9#9#9#9#9#9',Weight'#13#10#9#9#9#9 +
      #9#9#9#9#9#9#9',DimX '#13#10#9#9#9#9#9#9#9#9#9#9#9',DimY'#13#10#9#9#9#9#9#9#9#9#9#9#9',DimZ'#13#10#9#9#9#9#9#9#9#9#9#9#9',H' +
      'DNLProductCode )'#13#10#9#9#9#9#9#9#9'('#13#10#9#9#9#9#9#9#9#9'select top 1 '#13#10#9#9#9#9#9#9#9#9#9'RTRI' +
      'M(ltrim(vi.Cat+'#39'/'#39'+vi.Opt))'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.Description ,' +
      #39#39')'#13#10#9#9#9#9#9#9#9#9#9',@ConsignmentID '#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.DD2Weight ' +
      ',0) / 1000'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.DD2Dim1 , 0 )'#13#10#9#9#9#9#9#9#9#9#9',coale' +
      'sce(vi.DD2Dim2 , 0 )'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.DD2Dim3 , 0 )'#13#10#9#9#9#9#9 +
      #9#9#9#9',coalesce(vi.HDNLCode,'#39#39') '#13#10#9#9#9#9#9#9#9#9#9'   from viewAXLOrderDet' +
      'ails vi where Parcel = @pcl and coalesce(DD2Dim1,0) > 0 '#13#10#9#9#9#9#9#9 +
      #9#9#13#10#9#9#9#9#9#9#9')'#13#10#9#9#9#9#9#9#9#9#9#9#9#13#10#9#9#9'insert into ConsignmentItems( Clie' +
      'ntProductCode'#13#10#9#9#9#9#9#9#9#9#9#9#9',ClientProductDescription '#13#10#9#9#9#9#9#9#9#9#9#9 +
      #9',ConsignmentID'#13#10#9#9#9#9#9#9#9#9#9#9#9',Weight'#13#10#9#9#9#9#9#9#9#9#9#9#9',DimX '#13#10#9#9#9#9#9#9#9#9 +
      #9#9#9',DimY'#13#10#9#9#9#9#9#9#9#9#9#9#9',DimZ'#13#10#9#9#9#9#9#9#9#9#9#9#9',HDNLProductCode )'#13#10#9#9#9#9#9 +
      #9#9'('#13#10#9#9#9#9#9#9#9#9'select top 1 '#13#10#9#9#9#9#9#9#9#9#9'RTRIM(ltrim(vi.Cat+'#39'/'#39'+vi.O' +
      'pt))'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.Description ,'#39#39')'#13#10#9#9#9#9#9#9#9#9#9',@Consign' +
      'mentID '#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.DD3Weight ,0) / 1000'#13#10#9#9#9#9#9#9#9#9#9',c' +
      'oalesce(vi.DD3Dim1 , 0 )'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.DD3Dim2 , 0 )'#13#10#9 +
      #9#9#9#9#9#9#9#9',coalesce(vi.DD3Dim3 , 0 )'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.HDNLCo' +
      'de,'#39#39') '#13#10#9#9#9#9#9#9#9#9#9'   from viewAXLOrderDetails vi where Parcel = ' +
      '@pcl and coalesce(DD3Dim1,0) > 0 '#13#10#9#9#9#9#9#9#9#9#13#10#9#9#9#9#9#9#9')'#13#10#13#10#9#9#9'inse' +
      'rt into ConsignmentItems( ClientProductCode'#13#10#9#9#9#9#9#9#9#9#9#9#9',ClientP' +
      'roductDescription '#13#10#9#9#9#9#9#9#9#9#9#9#9',ConsignmentID'#13#10#9#9#9#9#9#9#9#9#9#9#9',Weigh' +
      't'#13#10#9#9#9#9#9#9#9#9#9#9#9',DimX '#13#10#9#9#9#9#9#9#9#9#9#9#9',DimY'#13#10#9#9#9#9#9#9#9#9#9#9#9',DimZ'#13#10#9#9#9#9#9#9 +
      #9#9#9#9#9',HDNLProductCode )'#13#10#9#9#9#9#9#9#9'('#13#10#9#9#9#9#9#9#9#9'select top 1 '#13#10#9#9#9#9#9#9 +
      #9#9#9'RTRIM(ltrim(vi.Cat+'#39'/'#39'+vi.Opt))'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.Descri' +
      'ption ,'#39#39')'#13#10#9#9#9#9#9#9#9#9#9',@ConsignmentID '#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.DD4' +
      'Weight ,0) / 1000'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.DD4Dim1 , 0 )'#13#10#9#9#9#9#9#9#9#9 +
      #9',coalesce(vi.DD4Dim2 , 0 )'#13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.DD4Dim3 , 0 )' +
      #13#10#9#9#9#9#9#9#9#9#9',coalesce(vi.HDNLCode,'#39#39') '#13#10#9#9#9#9#9#9#9#9#9'   from viewAXLO' +
      'rderDetails vi where Parcel = @pcl and coalesce(DD4Dim1,0) > 0 '#13 +
      #10#9#9#9#9#9#9#9#9#13#10#9#9#9#9#9#9#9')'#13#10#9#9#9#13#10#9#9'end'#13#10#13#10#9#9#13#10#13#10#9#9#13#10#9'end'#13#10#9
    Connection = DB
    Parameters = <
      item
        Name = 'svc'
        DataType = ftWideString
        Size = -1
        Value = Null
      end
      item
        Name = 'pcl'
        DataType = ftWideString
        Size = 16
        Value = '9026175964034031'
      end>
    Left = 536
    Top = 240
  end
  object ConsignmentWeight: TADOQuery
    Connection = DB
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'cid'
        Attributes = [paSigned, paNullable]
        DataType = ftLargeint
        Precision = 19
        Size = 8
        Value = Null
      end>
    SQL.Strings = (
      'select sum(coalesce(weight,0)) as Wt  from ConsignmentItems'
      'where consignmentid=:cid')
    Left = 544
    Top = 328
    object ConsignmentWeightWt: TIntegerField
      FieldName = 'Wt'
      ReadOnly = True
    end
  end
  object DDOrders: TADOQuery
    Connection = DD_DB
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'supplier'
        Attributes = [paNullable]
        DataType = ftWideString
        NumericScale = 255
        Precision = 255
        Size = 4
        Value = 'A016'
      end>
    SQL.Strings = (
      'select  * from orders where dd_supplier_code=:supplier'
      'and date_of_order >dateadd(month,-3,getdate() )'
      ''
      'order by tp94_tstamp desc')
    Left = 40
    Top = 136
    object DDOrdersKEY: TWideStringField
      FieldName = 'KEY'
      Size = 15
    end
    object DDOrdersORDER_KEY: TWideStringField
      FieldName = 'ORDER_KEY'
      Size = 15
    end
    object DDOrdersPRIMARY_ITEM_IND: TWideStringField
      FieldName = 'PRIMARY_ITEM_IND'
      Size = 1
    end
    object DDOrdersDD_GROUP_SUPP_CODE: TWideStringField
      FieldName = 'DD_GROUP_SUPP_CODE'
      Size = 4
    end
    object DDOrdersDD_SUPPLIER_CODE: TWideStringField
      FieldName = 'DD_SUPPLIER_CODE'
      Size = 4
    end
    object DDOrdersSEQ_ORDER_NO: TIntegerField
      FieldName = 'SEQ_ORDER_NO'
    end
    object DDOrdersACCOUNT_REF_NO: TWideStringField
      FieldName = 'ACCOUNT_REF_NO'
      Size = 10
    end
    object DDOrdersINVOICE_NO: TIntegerField
      FieldName = 'INVOICE_NO'
    end
    object DDOrdersCOMP_CODE: TWideStringField
      FieldName = 'COMP_CODE'
      Size = 3
    end
    object DDOrdersCOMP_NAME: TWideStringField
      FieldName = 'COMP_NAME'
    end
    object DDOrdersCOMP_ADDR: TWideStringField
      FieldName = 'COMP_ADDR'
      Size = 15
    end
    object DDOrdersCOMP_RETURN_ADDR: TWideStringField
      FieldName = 'COMP_RETURN_ADDR'
      Size = 22
    end
    object DDOrdersCOMP_PCODE: TWideStringField
      FieldName = 'COMP_PCODE'
      Size = 8
    end
    object DDOrdersDATE_OF_ORDER: TDateTimeField
      FieldName = 'DATE_OF_ORDER'
    end
    object DDOrdersCATALOGUE_NUMBER: TWideStringField
      FieldName = 'CATALOGUE_NUMBER'
      Size = 6
    end
    object DDOrdersOPTION_NUMBER: TWideStringField
      FieldName = 'OPTION_NUMBER'
      Size = 2
    end
    object DDOrdersQUANTITY: TBCDField
      FieldName = 'QUANTITY'
      Precision = 5
      Size = 2
    end
    object DDOrdersWEIGHT: TBCDField
      FieldName = 'WEIGHT'
      Precision = 7
      Size = 3
    end
    object DDOrdersPRICE: TBCDField
      FieldName = 'PRICE'
      Precision = 7
      Size = 2
    end
    object DDOrdersBEK_PRICE: TBCDField
      FieldName = 'BEK_PRICE'
      Precision = 9
      Size = 3
    end
    object DDOrdersITEM_DESCRIPTION: TWideStringField
      FieldName = 'ITEM_DESCRIPTION'
    end
    object DDOrdersOPTION_DESCRIPTION: TWideStringField
      FieldName = 'OPTION_DESCRIPTION'
      Size = 10
    end
    object DDOrdersUNIT_OF_SALE_TYPE: TWideStringField
      FieldName = 'UNIT_OF_SALE_TYPE'
      Size = 1
    end
    object DDOrdersNO_OF_LABELS: TSmallintField
      FieldName = 'NO_OF_LABELS'
    end
    object DDOrdersSPEC_FORM_DETAILS: TWideStringField
      FieldName = 'SPEC_FORM_DETAILS'
      Size = 60
    end
    object DDOrdersSUPP_PRODUCT_CODE: TWideStringField
      FieldName = 'SUPP_PRODUCT_CODE'
    end
    object DDOrdersCAPED_SHROUD_IND: TWideStringField
      FieldName = 'CAPED_SHROUD_IND'
      Size = 1
    end
    object DDOrdersNO_OF_ITEMS: TSmallintField
      FieldName = 'NO_OF_ITEMS'
    end
    object DDOrdersDD_BARCODE_NO: TWideStringField
      FieldName = 'DD_BARCODE_NO'
      Size = 16
    end
    object DDOrdersLABEL_LEGEND: TWideStringField
      FieldName = 'LABEL_LEGEND'
      Size = 12
    end
    object DDOrdersLAB_PRINTED_TSTAMP: TDateTimeField
      FieldName = 'LAB_PRINTED_TSTAMP'
    end
    object DDOrdersTIMES_PRINTED: TSmallintField
      FieldName = 'TIMES_PRINTED'
    end
    object DDOrdersINTO_PROD_DATE: TDateTimeField
      FieldName = 'INTO_PROD_DATE'
    end
    object DDOrdersCOLLECTION_DATE: TDateTimeField
      FieldName = 'COLLECTION_DATE'
    end
    object DDOrdersCOLLECTION_DATE_TP: TWideStringField
      FieldName = 'COLLECTION_DATE_TP'
      Size = 2
    end
    object DDOrdersCOLLECT_DATE_TS: TDateTimeField
      FieldName = 'COLLECT_DATE_TS'
    end
    object DDOrdersMANIFEST_NUMBER: TIntegerField
      FieldName = 'MANIFEST_NUMBER'
    end
    object DDOrdersDELIVERY_ADDR1: TWideStringField
      FieldName = 'DELIVERY_ADDR1'
      Size = 40
    end
    object DDOrdersDELIVERY_ADDR2: TWideStringField
      FieldName = 'DELIVERY_ADDR2'
      Size = 35
    end
    object DDOrdersDELIVERY_ADDR3: TWideStringField
      FieldName = 'DELIVERY_ADDR3'
      Size = 35
    end
    object DDOrdersDELIVERY_ADDR4: TWideStringField
      FieldName = 'DELIVERY_ADDR4'
      Size = 35
    end
    object DDOrdersDELIVERY_ADDR5: TWideStringField
      FieldName = 'DELIVERY_ADDR5'
      Size = 35
    end
    object DDOrdersDELIVERY_ADDR6: TWideStringField
      FieldName = 'DELIVERY_ADDR6'
      Size = 35
    end
    object DDOrdersDELIVERY_PCODE: TWideStringField
      FieldName = 'DELIVERY_PCODE'
      Size = 8
    end
    object DDOrdersCONTACT_PHONE_NO: TWideStringField
      FieldName = 'CONTACT_PHONE_NO'
    end
    object DDOrdersALT_PHONE_NO: TWideStringField
      FieldName = 'ALT_PHONE_NO'
    end
    object DDOrdersDELIVERY_DATE: TDateTimeField
      FieldName = 'DELIVERY_DATE'
    end
    object DDOrdersDELIVERY_DATE_TP: TWideStringField
      FieldName = 'DELIVERY_DATE_TP'
      Size = 2
    end
    object DDOrdersDELIVERY_DATE_TS: TDateTimeField
      FieldName = 'DELIVERY_DATE_TS'
    end
    object DDOrdersAREA_CODE: TWideStringField
      FieldName = 'AREA_CODE'
      Size = 2
    end
    object DDOrdersVAN_CODE: TWideStringField
      FieldName = 'VAN_CODE'
      Size = 3
    end
    object DDOrdersFULL_CARRIER_CODE: TWideStringField
      FieldName = 'FULL_CARRIER_CODE'
      Size = 6
    end
    object DDOrdersVAN_ROUND: TWideStringField
      FieldName = 'VAN_ROUND'
      Size = 5
    end
    object DDOrdersUPLIFT_DATE: TDateTimeField
      FieldName = 'UPLIFT_DATE'
    end
    object DDOrdersUPLIFT_DATE_TP: TWideStringField
      FieldName = 'UPLIFT_DATE_TP'
      Size = 2
    end
    object DDOrdersUPLIFT_DATE_TSTAMP: TDateTimeField
      FieldName = 'UPLIFT_DATE_TSTAMP'
    end
    object DDOrdersTP91_TSTAMP: TDateTimeField
      FieldName = 'TP91_TSTAMP'
    end
    object DDOrdersLAST_TP: TWideStringField
      FieldName = 'LAST_TP'
      Size = 2
    end
    object DDOrdersTP92_TSTAMP: TDateTimeField
      FieldName = 'TP92_TSTAMP'
    end
    object DDOrdersTP92_REASON_CODE: TWideStringField
      FieldName = 'TP92_REASON_CODE'
      Size = 3
    end
    object DDOrdersTP93_TSTAMP: TDateTimeField
      FieldName = 'TP93_TSTAMP'
    end
    object DDOrdersTP93_INTOPRODDATE: TDateTimeField
      FieldName = 'TP93_INTOPRODDATE'
    end
    object DDOrdersTP94_TSTAMP: TDateTimeField
      FieldName = 'TP94_TSTAMP'
    end
    object DDOrdersTP95_TSTAMP: TDateTimeField
      FieldName = 'TP95_TSTAMP'
    end
    object DDOrdersTP96_TSTAMP: TDateTimeField
      FieldName = 'TP96_TSTAMP'
    end
    object DDOrdersTP97_TSTAMP: TDateTimeField
      FieldName = 'TP97_TSTAMP'
    end
    object DDOrdersTP97_DATE: TDateTimeField
      FieldName = 'TP97_DATE'
    end
    object DDOrdersTP97_REASON_CODE: TWideStringField
      FieldName = 'TP97_REASON_CODE'
      Size = 3
    end
    object DDOrdersTP97_SUB_CARR_CODE: TWideStringField
      FieldName = 'TP97_SUB_CARR_CODE'
      Size = 3
    end
    object DDOrdersTP97_ATTEMPTS: TSmallintField
      FieldName = 'TP97_ATTEMPTS'
    end
    object DDOrdersTP98_CARR_MANIF_TS: TDateTimeField
      FieldName = 'TP98_CARR_MANIF_TS'
    end
    object DDOrdersTP98_CARR_MANIF_NO: TWideStringField
      FieldName = 'TP98_CARR_MANIF_NO'
      Size = 6
    end
    object DDOrdersTP99_TSTAMP: TDateTimeField
      FieldName = 'TP99_TSTAMP'
    end
    object DDOrdersTP9A_TSTAMP: TDateTimeField
      FieldName = 'TP9A_TSTAMP'
    end
    object DDOrdersTP9B_TSTAMP: TDateTimeField
      FieldName = 'TP9B_TSTAMP'
    end
    object DDOrdersTP9C_TSTAMP: TDateTimeField
      FieldName = 'TP9C_TSTAMP'
    end
    object DDOrdersTP9D_TSTAMP: TDateTimeField
      FieldName = 'TP9D_TSTAMP'
    end
    object DDOrdersTP9D_REDIR_ADDR1: TWideStringField
      FieldName = 'TP9D_REDIR_ADDR1'
      Size = 40
    end
    object DDOrdersTP9D_REDIR_ADDR2: TWideStringField
      FieldName = 'TP9D_REDIR_ADDR2'
      Size = 35
    end
    object DDOrdersTP9D_REDIR_ADDR3: TWideStringField
      FieldName = 'TP9D_REDIR_ADDR3'
      Size = 35
    end
    object DDOrdersTP9D_REDIR_ADDR4: TWideStringField
      FieldName = 'TP9D_REDIR_ADDR4'
      Size = 35
    end
    object DDOrdersTP9D_REDIR_ADDR5: TWideStringField
      FieldName = 'TP9D_REDIR_ADDR5'
      Size = 35
    end
    object DDOrdersTP9D_REDIR_ADDR6: TWideStringField
      FieldName = 'TP9D_REDIR_ADDR6'
      Size = 35
    end
    object DDOrdersTP9D_PCODE: TWideStringField
      FieldName = 'TP9D_PCODE'
      Size = 8
    end
    object DDOrdersTP9E_TSTAMP: TDateTimeField
      FieldName = 'TP9E_TSTAMP'
    end
    object DDOrdersTP9F_TSTAMP: TDateTimeField
      FieldName = 'TP9F_TSTAMP'
    end
    object DDOrdersTP9G_TSTAMP: TDateTimeField
      FieldName = 'TP9G_TSTAMP'
    end
    object DDOrdersTP9G_WAIT_FLAG: TWideStringField
      FieldName = 'TP9G_WAIT_FLAG'
      Size = 1
    end
    object DDOrdersTP9G_UPLIFT_ADDR1: TWideStringField
      FieldName = 'TP9G_UPLIFT_ADDR1'
      Size = 40
    end
    object DDOrdersTP9G_UPLIFT_ADDR2: TWideStringField
      FieldName = 'TP9G_UPLIFT_ADDR2'
      Size = 35
    end
    object DDOrdersTP9G_UPLIFT_ADDR3: TWideStringField
      FieldName = 'TP9G_UPLIFT_ADDR3'
      Size = 35
    end
    object DDOrdersTP9G_UPLIFT_ADDR4: TWideStringField
      FieldName = 'TP9G_UPLIFT_ADDR4'
      Size = 35
    end
    object DDOrdersTP9G_UPLIFT_ADDR5: TWideStringField
      FieldName = 'TP9G_UPLIFT_ADDR5'
      Size = 35
    end
    object DDOrdersTP9G_UPLIFT_ADDR6: TWideStringField
      FieldName = 'TP9G_UPLIFT_ADDR6'
      Size = 35
    end
    object DDOrdersTP9G_RETURN_ADDR1: TWideStringField
      FieldName = 'TP9G_RETURN_ADDR1'
      Size = 40
    end
    object DDOrdersTP9G_RETURN_ADDR2: TWideStringField
      FieldName = 'TP9G_RETURN_ADDR2'
      Size = 35
    end
    object DDOrdersTP9G_RETURN_ADDR3: TWideStringField
      FieldName = 'TP9G_RETURN_ADDR3'
      Size = 35
    end
    object DDOrdersTP9G_RETURN_ADDR4: TWideStringField
      FieldName = 'TP9G_RETURN_ADDR4'
      Size = 35
    end
    object DDOrdersTP9G_RETURN_ADDR5: TWideStringField
      FieldName = 'TP9G_RETURN_ADDR5'
      Size = 35
    end
    object DDOrdersTP9G_RETURN_ADDR6: TWideStringField
      FieldName = 'TP9G_RETURN_ADDR6'
      Size = 35
    end
    object DDOrdersTP9G_RETURN_PCODE: TWideStringField
      FieldName = 'TP9G_RETURN_PCODE'
      Size = 8
    end
    object DDOrdersTP9H_TSTAMP: TDateTimeField
      FieldName = 'TP9H_TSTAMP'
    end
    object DDOrdersTP9I_TSTAMP: TDateTimeField
      FieldName = 'TP9I_TSTAMP'
    end
    object DDOrdersTP9J_TSTAMP: TDateTimeField
      FieldName = 'TP9J_TSTAMP'
    end
    object DDOrdersTP9J_REASON_CODE: TWideStringField
      FieldName = 'TP9J_REASON_CODE'
      Size = 2
    end
    object DDOrdersTP9J_ATTEMPTS: TSmallintField
      FieldName = 'TP9J_ATTEMPTS'
    end
    object DDOrdersDD_GROUP_CODE: TWideStringField
      FieldName = 'DD_GROUP_CODE'
      Size = 3
    end
    object DDOrdersTP9G_UPLIFT_PCODE: TWideStringField
      FieldName = 'TP9G_UPLIFT_PCODE'
      Size = 8
    end
    object DDOrdersORIG_COLLECT_DATE: TDateTimeField
      FieldName = 'ORIG_COLLECT_DATE'
    end
    object DDOrdersTP9G_UPLIFT_REASON: TWideStringField
      FieldName = 'TP9G_UPLIFT_REASON'
      Size = 30
    end
    object DDOrdersFILE_FORMAT_CAT_NO: TWideStringField
      FieldName = 'FILE_FORMAT_CAT_NO'
      Size = 6
    end
    object DDOrdersTP9K_TSTAMP: TDateTimeField
      FieldName = 'TP9K_TSTAMP'
    end
    object DDOrdersDELIVERY_ADDR7: TWideStringField
      FieldName = 'DELIVERY_ADDR7'
      Size = 35
    end
    object DDOrdersTP9D_REDIR_ADDR7: TWideStringField
      FieldName = 'TP9D_REDIR_ADDR7'
      Size = 35
    end
    object DDOrdersTP9G_UPLIFT_ADDR7: TWideStringField
      FieldName = 'TP9G_UPLIFT_ADDR7'
      Size = 35
    end
    object DDOrdersTP9G_RETURN_ADDR7: TWideStringField
      FieldName = 'TP9G_RETURN_ADDR7'
      Size = 35
    end
    object DDOrdersSPEEDLINK_NO: TWideStringField
      FieldName = 'SPEEDLINK_NO'
      Size = 12
    end
    object DDOrdersQUERY_REF_NO: TIntegerField
      FieldName = 'QUERY_REF_NO'
    end
    object DDOrdersORIG_DELIV_DATE: TDateTimeField
      FieldName = 'ORIG_DELIV_DATE'
    end
    object DDOrdersCARR_ACCOUNT_NO: TWideStringField
      FieldName = 'CARR_ACCOUNT_NO'
      Size = 8
    end
    object DDOrdersCARR_BRANCH_NO: TWideStringField
      FieldName = 'CARR_BRANCH_NO'
      Size = 8
    end
    object DDOrdersSERVICE_OFFER: TWideStringField
      FieldName = 'SERVICE_OFFER'
      Size = 8
    end
    object DDOrdersDD_PARENT_NO: TWideStringField
      FieldName = 'DD_PARENT_NO'
      Size = 50
    end
    object DDOrdersCWT: TBCDField
      FieldName = 'CWT'
      Precision = 7
      Size = 3
    end
    object DDOrdersCPC: TBCDField
      FieldName = 'CPC'
      Precision = 7
      Size = 3
    end
    object DDOrdersDD_BARCODE_ORIG: TWideStringField
      FieldName = 'DD_BARCODE_ORIG'
    end
    object DDOrdersOUT_OF_STOCK: TSmallintField
      FieldName = 'OUT_OF_STOCK'
    end
  end
  object DD_DB: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=ddtrack_daily;Data Source=FGH-SQL01'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 40
    Top = 208
  end
  object dsDDOrders: TDataSource
    DataSet = DDOrders
    Left = 96
    Top = 136
  end
  object OptLookUp: TADOQuery
    Connection = DB
    CursorType = ctStatic
    Parameters = <
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
    SQL.Strings = (
      'select * from OptionData where Cat=:cat and [opt]=:opt')
    Left = 144
    Top = 424
    object OptLookUpCat: TStringField
      FieldName = 'Cat'
      Size = 10
    end
    object OptLookUpOpt: TWideStringField
      FieldName = 'Opt'
      FixedChar = True
      Size = 2
    end
    object OptLookUpDescription: TWideStringField
      FieldName = 'Description'
      FixedChar = True
    end
    object OptLookUpDim1: TIntegerField
      FieldName = 'Dim1'
    end
    object OptLookUpDim2: TIntegerField
      FieldName = 'Dim2'
    end
    object OptLookUpDim3: TIntegerField
      FieldName = 'Dim3'
    end
    object OptLookUpVolume: TIntegerField
      FieldName = 'Volume'
    end
    object OptLookUpWeight: TIntegerField
      FieldName = 'Weight'
    end
    object OptLookUpPrice: TFloatField
      FieldName = 'Price'
    end
    object OptLookUpOptionID: TLargeintField
      FieldName = 'OptionID'
      ReadOnly = True
    end
    object OptLookUpHDNLCode: TStringField
      FieldName = 'HDNLCode'
      FixedChar = True
      Size = 2
    end
    object OptLookUpDD1Dim1: TIntegerField
      FieldName = 'DD1Dim1'
    end
    object OptLookUpDD1Dim2: TIntegerField
      FieldName = 'DD1Dim2'
    end
    object OptLookUpDD1Dim3: TIntegerField
      FieldName = 'DD1Dim3'
    end
    object OptLookUpDD1Weight: TIntegerField
      FieldName = 'DD1Weight'
    end
    object OptLookUpDD2Dim1: TIntegerField
      FieldName = 'DD2Dim1'
    end
    object OptLookUpDD2Dim2: TIntegerField
      FieldName = 'DD2Dim2'
    end
    object OptLookUpDD2Dim3: TIntegerField
      FieldName = 'DD2Dim3'
    end
    object OptLookUpDD2Weight: TIntegerField
      FieldName = 'DD2Weight'
    end
    object OptLookUpDD3Dim1: TIntegerField
      FieldName = 'DD3Dim1'
    end
    object OptLookUpDD3Dim2: TIntegerField
      FieldName = 'DD3Dim2'
    end
    object OptLookUpDD3Dim3: TIntegerField
      FieldName = 'DD3Dim3'
    end
    object OptLookUpDD3Weight: TIntegerField
      FieldName = 'DD3Weight'
    end
    object OptLookUpDD4Dim1: TIntegerField
      FieldName = 'DD4Dim1'
    end
    object OptLookUpDD4Dim2: TIntegerField
      FieldName = 'DD4Dim2'
    end
    object OptLookUpDD4Dim3: TIntegerField
      FieldName = 'DD4Dim3'
    end
    object OptLookUpDD4Weight: TIntegerField
      FieldName = 'DD4Weight'
    end
  end
  object Q: TADOQuery
    Connection = DB
    Parameters = <>
    Left = 328
    Top = 368
  end
  object DDOrderList: TADOQuery
    Connection = DD_DB
    CursorType = ctStatic
    LockType = ltReadOnly
    AfterOpen = DDOrderListAfterOpen
    Parameters = <>
    SQL.Strings = (
      'SELECT [KEY]'
      '      ,[ORDER_KEY]'
      ''
      ''
      '      ,[DD_SUPPLIER_CODE]'
      ''
      '      ,[ACCOUNT_REF_NO]'
      '      ,[INVOICE_NO]'
      ''
      ''
      '      ,[CATALOGUE_NUMBER]'
      '      ,[OPTION_NUMBER]'
      '      ,[QUANTITY]'
      '      ,[WEIGHT]'
      '      ,[PRICE]'
      '      ,[BEK_PRICE]'
      '      ,[ITEM_DESCRIPTION]'
      '      ,[OPTION_DESCRIPTION]'
      ''
      '      ,[DD_BARCODE_NO]'
      ''
      ''
      '      ,[DELIVERY_ADDR1]'
      '      ,[DELIVERY_ADDR2]'
      '      ,[DELIVERY_ADDR3]'
      '      ,[DELIVERY_ADDR4]'
      '      ,[DELIVERY_ADDR5]'
      '      ,[DELIVERY_ADDR6]'
      '      ,[DELIVERY_PCODE]'
      '      ,[CONTACT_PHONE_NO]'
      '      ,[ALT_PHONE_NO]'
      '  FROM [ddtrack_daily].[dbo].[orders]'
      '  where DATE_OF_ORDER> DATEADD(week,-26,getdate())'
      ''
      
        'and dd_supplier_code in ( '#39'A016'#39','#39'A040'#39','#39'B774'#39','#39'B914'#39','#39'C149'#39','#39'E0' +
        '11'#39','#39'G008'#39','#39'G019'#39','#39'G559'#39','#39'G586'#39','#39'H003'#39','#39'H598'#39','#39'H624'#39','#39'K001'#39','#39'L00' +
        '9'#39','#39'L027'#39','#39'M172'#39','#39'R450'#39','#39'S714'#39','#39'T601'#39','#39'U003'#39','#39'W378'#39','#39'Y153'#39' )'
      ''
      ''
      ''
      ''
      ''
      ''
      ''
      ''
      ''
      ''
      '')
    Left = 40
    Top = 296
  end
  object qrySuppList: TADOQuery
    Connection = DB
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'declare @SuppCodes as  varchar(max)'
      ''
      
        'select @SuppCodes=coalesce(@SuppCodes+'#39','#39' ,'#39#39')+QUOTENAME(Supplie' +
        'rCode)'
      'from'
      '('
      ''
      'SELECT '
      '     SupplierCode'
      '  FROM [CityLink].[dbo].[DSVSuppliers]'
      '  where coalesce(SupplierCode,'#39#39')<> '#39#39
      '  ) as aa'
      '  '
      ''
      'set @SuppCodes = REPLACE(@Suppcodes,'#39'['#39','#39#39#39#39')'
      'set @SuppCodes = REPLACE(@Suppcodes,'#39']'#39','#39#39#39#39')'
      ''
      'select @SuppCodes  as SuppList')
    Left = 408
    Top = 400
    object qrySuppListSuppList: TMemoField
      FieldName = 'SuppList'
      ReadOnly = True
      BlobType = ftMemo
    end
  end
end
