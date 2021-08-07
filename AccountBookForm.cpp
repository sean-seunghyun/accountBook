//AccountBookForm.cpp
#include"AccountBookForm.h"
#include"AccountBook.h"
#include"Account.h"
#include"FindingForm.h"
#include"Income.h"
#include"Outgo.h"
#include<afxcmn.h>
#include<afxdtctl.h>
#include <atlstr.h>
#include<atltime.h>
#include<afxdb.h>

#pragma warning(disable:4996)


BEGIN_MESSAGE_MAP(AccountBookForm,CDialog)

	ON_BN_CLICKED(IDC_BUTTON_RECORD,OnRecordButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_FIND,OnFindButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_CORRECT,OnCorrectButtonClicked)

	ON_EN_KILLFOCUS(IDC_EDIT_AMOUNTS,OnAmountsFocusLost)

	ON_NOTIFY(NM_DBLCLK,IDC_LIST_ACCOUNTS,OnListViewItemDoubleClicked)

	ON_WM_CLOSE()

END_MESSAGE_MAP()


AccountBookForm::AccountBookForm(CWnd *parent)
	:CDialog(AccountBookForm::IDD, parent) {
	this->accountBook = NULL;
}



BOOL AccountBookForm::OnInitDialog() {
	CDialog::OnInitDialog();
	Long count;
	Long i = 0;

	Account *account;
	Date date;
	CString dateCString;
	Currency amounts;
	CString amountsCString;
	Currency balance;
	CString balanceCString;

	this->accountBook = new AccountBook;

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(0, "날짜",LVCFMT_LEFT, 75);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(1, "적요", LVCFMT_LEFT, 75);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(2, "금액(원)", LVCFMT_RIGHT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(3, "잔액(원)", LVCFMT_RIGHT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(4, "비고", LVCFMT_LEFT, 100);

	((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);

	count=this->Load();

	while (i < count) {

		account = this->accountBook->GetAt(i);
		date = account->GetDate();
		dateCString.Format("%04d-%02d-%02d", date.GetYear(), date.GetMonth(), date.GetDay());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertItem(i, dateCString);
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 1, CString(account->GetDescription().c_str()));
		amounts = account->GetAmounts();
		amountsCString.Format("%.1f", amounts);

		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 2, amountsCString);

		balance = account->GetBalance();
		balanceCString.Format("%.1f", balance);

		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 3, balanceCString);
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(i, 4, CString(account->GetNote().c_str()));

		i++;
	}


	return FALSE;
}


void AccountBookForm::OnRecordButtonClicked() {
	CString description;
	CString amountsCString;
	CString dateCString;
	CString balanceCString;
	char(*dateChar);
	CString note;
	COleDateTime time;
	int checkOutgo;
	Account *account;
	Long index;
	Currency amounts;
	Currency balance;
	Date date;
	
	

	checkOutgo = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
	((CDateTimeCtrl*)GetDlgItem(IDC_DATE_DATE))->GetTime(time);	
	dateCString.Format("%d%02d%02d", time.GetYear(), time.GetMonth(), time.GetDay());



	
	dateChar=dateCString.GetBuffer();
	date = Date(dateChar);



	GetDlgItem(IDC_EDIT_DESCRIPTION)->GetWindowTextA(description);
	GetDlgItem(IDC_EDIT_AMOUNTS)->GetWindowTextA(amountsCString);
	amounts = atof((LPCTSTR)amountsCString);
	if (checkOutgo == BST_CHECKED) {
		amounts *= -1;
	}
	GetDlgItem(IDC_EDIT_NOTE)->GetWindowTextA(note);

	
	

	index = this->accountBook->Record(
		date, (LPCTSTR)description, amounts, (LPCTSTR)note
	);

	this->Insert(index);

	account = this->accountBook->GetAt(index);

	date = account->GetDate();
	dateCString.Format("%04d-%02d-%02d", date.GetYear(), date.GetMonth(), date.GetDay());
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertItem(index, dateCString);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index,1, CString(account->GetDescription().c_str()));
	amounts = account->GetAmounts();
	amountsCString.Format("%.0f", amounts);

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 2, amountsCString);

	balance = account->GetBalance();
	balanceCString.Format("%.0f", balance);

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 3, balanceCString);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 4, CString(account->GetNote().c_str()));

}

void AccountBookForm::OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {
	Account *account;
	Long index;
	CString balance;
	CString amounts;
	Date date;

	index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	account = this->accountBook->GetAt(index);
	if (dynamic_cast<Income*>(account)) {
		((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
	}
	else if (dynamic_cast<Outgo*>(account)) {
		((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	}

	date = account->GetDate();
	
	COleDateTime time(date.GetYear(), date.GetMonth(), date.GetDay(), 0, 0, 0);
	((CDateTimeCtrl*)GetDlgItem(IDC_DATE_DATE))->SetTime(time);

	GetDlgItem(IDC_EDIT_DESCRIPTION)->SetWindowTextA(CString(account->GetDescription().c_str()));
	amounts.Format("%.1f", account->GetAmounts());
	GetDlgItem(IDC_EDIT_AMOUNTS)->SetWindowTextA(amounts);
	balance.Format("%.1f", account->GetBalance());
	GetDlgItem(IDC_STATIC_BALANCE)->SetWindowTextA(balance);
	GetDlgItem(IDC_EDIT_NOTE)->SetWindowTextA(CString(account->GetNote().c_str()));
}

void AccountBookForm::OnAmountsFocusLost() {
	int checkOutgo;
	Long index=-1;
	CString balanceCString;
	CString amountsCString;
	Currency amounts;
	Currency balance = 0;
	Account *account;
	Long length;
	
	
	//지출 라디오버튼이 체크되어있는지 확인한다.
	checkOutgo = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
	//금액 에디트에 있는 내용을 읽는다.
	GetDlgItem(IDC_EDIT_AMOUNTS)->GetWindowTextA(amountsCString);
	//화폐형으로 자료형을 바꾼다.
	amounts = atof((LPCTSTR)amountsCString);
	//지출 라디오 버튼으로 체크되어있으면 금액을 음수로 바꾼다.
	if (checkOutgo == BST_CHECKED) {
		amounts *= -1;
	}

	//위치를 읽는다.
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	//연결리스트에 선택된 것이 아무것도 없을떄
	if (index == -1) {
		length=this->accountBook->GetLength();
		account = this->accountBook->GetAt(length - 1);
		//가장 최근 배열의 잔액을 가져온다.
		balance = account->GetBalance();
	}
	//연결리스트에 선택이 되었을 때
	else if(index>0){
	account = this->accountBook->GetAt(index - 1);
	balance = account->GetBalance();
	}
	


	balance += amounts;
	balanceCString.Format("%.1f", balance);
	GetDlgItem(IDC_STATIC_BALANCE)->SetWindowTextA(balanceCString);
}

void AccountBookForm::OnCorrectButtonClicked() {
	CString note;
	CString amounts;
	CString balance;
	Long index;
	Account *account;
	Currency amountsForCorrect;
	GetDlgItem(IDC_EDIT_AMOUNTS)->GetWindowTextA(amounts);
	GetDlgItem(IDC_EDIT_NOTE)->GetWindowTextA(note);

	index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	amountsForCorrect = atof((LPCTSTR)amounts);
	index = this->accountBook->Correct(index, amountsForCorrect, (LPCTSTR)note);
	
	this->Modify(index);

	account = this->accountBook->GetAt(index);
	amounts.Format("%.1f", account->GetAmounts());
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 2, amounts);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 4, CString(account->GetNote().c_str()));
	while (index < this->accountBook->GetLength()) {
		account = this->accountBook->GetAt(index);
		balance.Format("%.1f", account->GetBalance());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetItemText(index, 3, balance);

		index++;
	}
}

void AccountBookForm::OnFindButtonClicked() {
	FindingForm findingForm;
	findingForm.DoModal();
}

void AccountBookForm::OnClose() {
	

	if (this->accountBook != NULL) {
		this->Save();

		delete this->accountBook;

	}
	EndDialog(0);
}

Long AccountBookForm::Load() {
	CDatabase db;
	CRecordset rs(&db);
	CString type;
	CString dateCS;
	CString descriptionCS;
	CString amountsCS;
	CString noteCS;
	Currency amounts;
	Date date;
	char(*dateChar);
	CDBVariant var;
	Long count = 0;
	CString sql = "SELECT Account.type, Account.date, Account.description, Account.amounts, Account.note FROM Account;";
	db.OpenEx("DSN=AccountBook;UID=root;PWD=a8gkdlfn");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, type);
		rs.GetFieldValue((short)1, var);
		rs.GetFieldValue((short)2, descriptionCS);
		rs.GetFieldValue((short)3, amountsCS);
		rs.GetFieldValue((short)4, noteCS);

		if (var.m_dwType = DBVT_DATE) {
			dateCS.Format("%d%02d%02d", var.m_pdate->year, var.m_pdate->month, var.m_pdate->day);
			}
		dateChar = dateCS.GetBuffer();
		date = Date(dateChar);
		amounts = atof((LPCTSTR)amountsCS);
		if (type.Compare("1") == 0) {
			amounts *= -1;
		}
		this->accountBook->Record(date, (LPCTSTR)descriptionCS, amounts, (LPCSTR)noteCS);
		count++;
		rs.MoveNext();
	}

	rs.Close();
	db.Close();

	return count;
}

CString AccountBookForm::GetCode(Date date) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	CString code;
	Long number = 0;

	db.OpenEx("DSN=AccountBook;UID=root;PWD=a8gkdlfn");
	sql.Format("SELECT Account.code FROM Account WHERE Month(date)='%d' AND Year(date)='%d';",
		date.GetMonth(), date.GetYear());

	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	while (!rs.IsEOF()) {
		number++;
		rs.MoveNext();
	}
	number++;
	code.Format("%d%02d%04d", date.GetYear(), date.GetMonth(), number);

	rs.Close();
	db.Close();

	return code;
}

void AccountBookForm::Insert(Long index) {
	CDatabase db;
	Account *account;
	Date date;
	CString sql;
	CString amountsCS;
	CString code;
	CString type = "1";
	CString dateCS;

	account = this->accountBook->GetAt(index);
	if (dynamic_cast<Income*>(account)) {
		type = "0";
	}
	date = account->GetDate();
	dateCS.Format("%d%02d%02d", date.GetYear(), date.GetMonth(), date.GetDay());
	amountsCS.Format("%.1f", account->GetAmounts());
	code = this->GetCode(date);
	sql.Format("INSERT INTO Account(type, date, description, amounts, note, code) VALUES ('%s','%s','%s','%s','%s','%s');",
		type, (LPCTSTR)dateCS, account->GetDescription().c_str(), (LPCTSTR)amountsCS, account->GetNote().c_str(), (LPCTSTR)code);

	db.OpenEx("DSN=AccountBook;UID=root;PWD=a8gkdlfn");
	db.ExecuteSQL(sql);

	db.Close();
}


void AccountBookForm::Modify(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	CString code;
	CString dateCS;
	CString descriptionCS;
	CString amountsCS;
	CString noteCS;	
	Date date;
	Account *account;

	account = this->accountBook->GetAt(index);
	date = account->GetDate();
	dateCS.Format("%d%02d%02d", date.GetYear(), date.GetMonth(), date.GetDay());
	descriptionCS = CString(account->GetDescription().c_str());
	sql.Format("SELECT Account.code FROM Account WHERE date='%s' AND description='%s';",
		(LPCTSTR)dateCS, (LPCTSTR)descriptionCS);
	db.OpenEx("DSN=AccountBook;UID=root;PWD=a8gkdlfn");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);
	}
	amountsCS.Format("%.1f", account->GetAmounts());
	noteCS = CString(account->GetNote().c_str());
	sql.Format("UPDATE Account SET amounts='%s', note='%s' WHERE code='%s';",
		(LPCTSTR)amountsCS, (LPCTSTR)noteCS, (LPCTSTR)code);
	db.ExecuteSQL(sql);

	rs.Close();
	db.Close();

}

Long AccountBookForm::Save() {

	CDatabase db;
	CRecordset rs(&db);
	Account *account;
	Date date;
	//계정으로부터 코드들만 불러온다.
	CString sql = "SELECT Account.code FROM Account;";
	CString amountsCS;
	CString dateCS;
	CString code;
	CString type;
	
	Long count = 0;
	Long i = 0;
	//연결한다
	db.OpenEx("DSN=AccountBook;UID=root;PWD=a8gkdlfn");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	//db에 있는 항목들을 모두 지운다.
	sql = "DELETE FROM Account;";
	db.ExecuteSQL(sql);

	while (i<this->accountBook->GetLength()) {
		rs.GetFieldValue((short)0, code);
		account = this->accountBook->GetAt(i);

		if (dynamic_cast<Income*>(account)) {
			type = "0";
		}
		else if (dynamic_cast<Outgo*>(account)) {
			type = "1";
		}


		date = account->GetDate();
		dateCS.Format("%d%02d%02d", date.GetYear(), date.GetMonth(), date.GetDay());
		amountsCS.Format("%.1f", account->GetAmounts());
		sql.Format("INSERT INTO Account(type, date, description, amounts, note, code) VALUES ('%s','%s','%s','%s','%s','%s');",
			type, (LPCTSTR)dateCS, account->GetDescription().c_str(), (LPCTSTR)amountsCS, account->GetNote().c_str(), (LPCTSTR)code);
		db.ExecuteSQL(sql);		
		count++;
		rs.MoveNext();
		i++;
	}
	rs.Close();
	db.Close();

	return count;
}