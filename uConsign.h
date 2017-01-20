//---------------------------------------------------------------------------

#ifndef uConsignH
#define uConsignH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.DBActns.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.StdActns.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdSimpleServer.hpp>
#include <IdTCPConnection.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TfmConsign : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlTop;
	TPanel *pnlMain;
	TStatusBar *StatusBar1;
	TPageControl *PageControl1;
	TTabSheet *tabConsignment;
	TTabSheet *tabConsignments;
	TImage *Image1;
	TTabSheet *tabServices;
	TPanel *pnlServiceNav;
	TPanel *pnlServiceDetail;
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGrid1;
	TLabel *Label1;
	TDBEdit *DBEdit1;
	TLabel *Label2;
	TDBEdit *DBEdit2;
	TGroupBox *grpCustomerDetails;
	TLabel *Label3;
	TDBEdit *DBEdit3;
	TLabel *Label4;
	TDBEdit *DBEdit4;
	TDBEdit *DBEdit5;
	TDBEdit *DBEdit6;
	TDBEdit *DBEdit7;
	TDBEdit *DBEdit8;
	TLabel *Label5;
	TPanel *pnlConsignmentNav;
	TActionList *ActionList1;
	TDataSetInsert *actConsignmentInsert;
	TDataSetDelete *actConsignmentDelete;
	TDataSetEdit *actConsignmentEdit;
	TDataSetPost *actConsignmentSave;
	TDataSetCancel *actConsignmentCancel;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TDBNavigator *DBNavigator2;
	TLabel *Label6;
	TDBEdit *DBEdit9;
	TLabel *Label7;
	TDBEdit *DBEdit10;
	TLabel *Label8;
	TDBEdit *DBEdit11;
	TLabel *Label9;
	TLabel *Label10;
	TDBEdit *DBEdit13;
	TLabel *Label11;
	TDBLookupComboBox *DBLookupComboBox1;
	TPanel *pnlConsignMain;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TDBText *DBText1;
	TDBGrid *dbGridItems;
	TDBNavigator *DBNavigator3;
	TLabeledEdit *txtBarcodeLookup;
	TGroupBox *grpItems;
	TLabeledEdit *txtItemSearch;
	TPanel *pnlGroupItemsTop;
	TPanel *pnlGroupItemsNav;
	TLabel *Label15;
	TDBText *dbCSVCreated;
	TPanel *pnlConsignmentsTop;
	TPanel *pnlConsignmentsMain;
	TPanel *pnlConsignmentsBottom;
	TDBGrid *DBGrid2;
	TCheckBox *cbxShowAll;
	TRadioGroup *rgpSelection;
	TCheckBox *cbxInvertSelection;
	TButton *Button5;
	TAction *actCreateCSV;
	TAction *actCheckData;
	TButton *Button6;
	TFileSaveAs *FileSaveAs1;
	TAction *actUpdateCSVChecked;
	TTimer *Timer1;
	TIdTCPServer *IdTCPServer1;
	TTabSheet *TabSheet1;
	TMemo *Memo1;
	TButton *Button7;
	TBitBtn *BitBtn1;
	TTabSheet *tabSuppliers;
	TPanel *Panel1;
	TPanel *Panel2;
	TDBGrid *DBGrid3;
	TDataSetFirst *actDSVFirst;
	TDataSetPrior *actDSVPrev;
	TDataSetNext *actDSVNext;
	TDataSetLast *actDSVLast;
	TDataSetInsert *actDSVNew;
	TDataSetDelete *actDSVDelete;
	TDataSetEdit *actDSVEdit;
	TDataSetPost *actDSVPost;
	TDataSetCancel *actDSVCancel;
	TDataSetRefresh *actDSVRefresh;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TButton *Button15;
	TDBLookupComboBox *DBLookupComboBox2;
	TLabel *Label16;
	TDBLookupComboBox *cmbSupplierFilter;
	TLabel *Label17;
	TLabel *Label18;
	TButton *Button16;
	void __fastcall tabServicesShow(TObject *Sender);
	void __fastcall tabConsignmentShow(TObject *Sender);
	void __fastcall txtBarcodeLookupKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall txtItemSearchKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGrid2DblClick(TObject *Sender);
	void __fastcall tabConsignmentsShow(TObject *Sender);
	void __fastcall rgpSelectionClick(TObject *Sender);
	void __fastcall cbxInvertSelectionClick(TObject *Sender);
	void __fastcall actCreateCSVExecute(TObject *Sender);
	void __fastcall actCheckDataExecute(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall actUpdateCSVCheckedExecute(TObject *Sender);
	void __fastcall dbGridItemsEditButtonClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall IdTCPServer1Execute(TIdContext *AContext);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall actConsignmentDeleteExecute(TObject *Sender);
	void __fastcall dbGridItemsExit(TObject *Sender);
	void __fastcall tabSuppliersShow(TObject *Sender);
	void __fastcall DBLookupComboBox2CloseUp(TObject *Sender);
	void __fastcall cmbSupplierFilterCloseUp(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);

	void __fastcall UpdateConsignmentView(TObject *Sender);


public:	// User declarations

public:		// User declarations
	__fastcall TfmConsign(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmConsign *fmConsign;
//---------------------------------------------------------------------------
#endif
