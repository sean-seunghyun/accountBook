//FindingForm.cpp
#include"FindingForm.h"
#include"AccountBookForm.h"
#include"AccountBook.h"
#include"Account.h"
#include"Income.h"
#include"Outgo.h"
#include<afxcmn.h>
#include<ATLComTime.h>
#include<afxdtctl.h>

BEGIN_MESSAGE_MAP(FindingForm,CDialog)

	ON_BN_CLICKED(IDC_BUTTON_FIND,OnFindButtonClicked)

	ON_BN_CLICKED(IDC_CHECK_DATE,OnDateButtonClicked)
	ON_BN_CLICKED(IDC_CHECK_DESCRIPTION,OnDescriptionButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_CALCULATE,OnCalculateButtonClicked)

	ON_NOTIFY(NM_DBLCLK,IDC_LIST_ACCOUNTS,OnLIstViewItemDoubleClicked)

	ON_WM_CLOSE()

END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd *parent)
	:CDialog(FindingForm::IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
	this->totalIncome = 0;
	this->totalOutgo = 0;
	this->difference = 0;
}

BOOL FindingForm::OnInitDialog() {
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DIFFERENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALINCOME_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALOUTGO_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DIFFERENCE_VALUE)->ShowWindow(SW_HIDE);


	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(0, "날짜", LVCFMT_LEFT, 75);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(1, "적요", LVCFMT_LEFT, 75);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(2, "금액(원)", LVCFMT_RIGHT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(3, "잔액(원)", LVCFMT_RIGHT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->InsertColumn(4, "비고", LVCFMT_LEFT, 50);

	GetDlgItem(IDC_DATE_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATE_END)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DESCRIPTION)->EnableWindow(FALSE);

	


	return FALSE;

}

void FindingForm::OnDateButtonClicked() {
	int checkDate;

	checkDate = ((CButton*)GetDlgItem(IDC_CHECK_DATE))->GetCheck();
	if (checkDate == BST_CHECKED) {
		GetDlgItem(IDC_DATE_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATE_END)->EnableWindow(TRUE);
	}
	else if (checkDate == BST_UNCHECKED) {
		GetDlgItem(IDC_DATE_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATE_END)->EnableWindow(FALSE);
	}
}

void FindingForm::OnDescriptionButtonClicked() {
	int checkDescription;
	checkDescription = ((CButton*)GetDlgItem(IDC_CHECK_DESCRIPTION))->GetCheck();

	if (checkDescription == BST_CHECKED) {
		GetDlgItem(IDC_EDIT_DESCRIPTION)->EnableWindow(TRUE);
	}
	else if (checkDescription == BST_UNCHECKED) {
		GetDlgItem(IDC_EDIT_DESCRIPTION)->EnableWindow(FALSE);
	}
}


void FindingForm::OnFindButtonClicked() {
	int checkDate;
	int checkDescription;
	COleDateTime startTime;
	COleDateTime endTime;
	Date startDate;
	Date endDate;
	char(*startDateChar);
	char(*endDateChar);
	AccountBookForm *accountBookForm;
	Long i = 0;
	Date date;
	CString description;
	CString amountsCString;
	Currency amounts;
	CString balanceCString;
	Currency balance;
	CString note;
	CString startDateCString;
	CString endDateCString;
	CString dateCString;
	Account *account;




	GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DIFFERENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALINCOME_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALOUTGO_VALUE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DIFFERENCE_VALUE)->ShowWindow(SW_HIDE);

	checkDate = ((CButton*)GetDlgItem(IDC_CHECK_DATE))->GetCheck();
	if (checkDate == BST_CHECKED) {
		((CDateTimeCtrl*)GetDlgItem(IDC_DATE_START))->GetTime(startTime);
		((CDateTimeCtrl*)GetDlgItem(IDC_DATE_END))->GetTime(endTime);
		startDateCString.Format("%d%02d%02d", startTime.GetYear(), startTime.GetMonth(), startTime.GetDay());
		endDateCString.Format("%d%02d%02d", endTime.GetYear(), endTime.GetMonth(), endTime.GetDay());
		startDateChar=startDateCString.GetBuffer();
		endDateChar = endDateCString.GetBuffer();
		startDate = Date(startDateChar);
		endDate = Date(endDateChar);

	}
	checkDescription = ((CButton*)GetDlgItem(IDC_CHECK_DESCRIPTION))->GetCheck();
	if (checkDescription == BST_CHECKED) {
		GetDlgItem(IDC_EDIT_DESCRIPTION)->GetWindowTextA(description);
	}
	accountBookForm = (AccountBookForm*)FindWindow("#32770", "가계부");
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	if (checkDate == BST_CHECKED && checkDescription == BST_UNCHECKED) {
		if (startDate == endDate) {
			accountBookForm->accountBook->Find(startDate, &this->indexes, &this->count);
		}
		else {
			accountBookForm->accountBook->Find(startDate, endDate, &this->indexes, &this->count);
		}
	}
	else if (checkDescription == BST_CHECKED && checkDate == BST_UNCHECKED) {
		accountBookForm->accountBook->Find((LPCTSTR)description, &this->indexes, &this->count);

	}
	else if (checkDate == BST_CHECKED && checkDescription == BST_CHECKED) {
		if (startDate == endDate) {
			accountBookForm->accountBook->Find(startDate, (LPCTSTR)description, &this->indexes, &this->count);

		}
		else {
			MessageBox("시작날짜와 끝날짜가 같아야 합니다.");
		}
	}

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->DeleteAllItems();

	while (i < this->count) {
		account = accountBookForm->accountBook->GetAt(this->indexes[i]);
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



}

void FindingForm::OnLIstViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {
	Long index;
	AccountBookForm *accountBookForm;
	Account *account;
	Date date;
	CString amounts;
	CString balance;

	index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->GetSelectionMark();
	accountBookForm = (AccountBookForm*)FindWindow("#32770", "가계부");
	account = accountBookForm->accountBook->GetAt(this->indexes[index]);
	if (dynamic_cast<Income*>(account)) {
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_CHECKED);
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
	}
	if (dynamic_cast<Outgo*>(account)) {
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	}
	date = account->GetDate();


	COleDateTime time(date.GetYear(), date.GetMonth(), date.GetDay(), 0, 0, 0);
	((CDateTimeCtrl*)accountBookForm->GetDlgItem(IDC_DATE_DATE))->SetTime(time);

	accountBookForm->GetDlgItem(IDC_EDIT_DESCRIPTION)->SetWindowTextA(CString(account->GetDescription().c_str()));
	amounts.Format("%.1f", account->GetAmounts());
	accountBookForm->GetDlgItem(IDC_EDIT_AMOUNTS)->SetWindowTextA(amounts);
	balance.Format("%.1f", account->GetBalance());
	accountBookForm->GetDlgItem(IDC_STATIC_BALANCE)->SetWindowTextA(balance);
	accountBookForm->GetDlgItem(IDC_EDIT_NOTE)->SetWindowTextA(CString(account->GetNote().c_str()));
	((CListCtrl*)accountBookForm->GetDlgItem(IDC_LIST_ACCOUNTS))->SetSelectionMark(this->indexes[index]);

	if (this->indexes != NULL) {
		delete[] this->indexes;
		
	}
	EndDialog(0);

}

void FindingForm::OnCalculateButtonClicked() {
	COleDateTime startTime;
	COleDateTime endTime;
	CString totalIncome;
	CString totalOutgo;
	CString difference;
	CString startDateCString;
	CString endDateCString;
	Long i = 0;
	Date startDate;
	Date endDate;
	char(*startDateChar);
	char(*endDateChar);
	AccountBookForm *accountBookForm;
	Account *account;
	CString amountsCString;
	Currency amounts;
	CString balanceCString;
	Currency balance;
	CString dateCString;
	Date date;

	((CDateTimeCtrl*)GetDlgItem(IDC_DATE_START))->GetTime(startTime);
	((CDateTimeCtrl*)GetDlgItem(IDC_DATE_END))->GetTime(endTime);
	startDateCString.Format("%d%02d%02d", startTime.GetYear(), startTime.GetMonth(), startTime.GetDay());
	endDateCString.Format("%d%02d%02d", endTime.GetYear(), endTime.GetMonth(), endTime.GetDay());
	startDateChar = startDateCString.GetBuffer();
	endDateChar = endDateCString.GetBuffer();
	startDate = Date(startDateChar);
	endDate = Date(endDateChar);

	accountBookForm = (AccountBookForm*)FindWindow("#32770", "가계부");
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	if(startDate!=endDate){
	accountBookForm->accountBook->Find(startDate, endDate, &this->indexes, &this->count);
	}
	else if (startDate == endDate) {
		accountBookForm->accountBook->Find(startDate, &this->indexes, &this->count);
	}

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNTS))->DeleteAllItems();

	while (i < this->count) {
		account = accountBookForm->accountBook->GetAt(this->indexes[i]);
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

	
	accountBookForm->accountBook->Calculate(startDate, endDate, &this->totalIncome, &this->totalOutgo, &this->difference);

	GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_DIFFERENCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TOTALINCOME_VALUE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TOTALOUTGO_VALUE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_DIFFERENCE_VALUE)->ShowWindow(SW_SHOW);

	totalIncome.Format("%.1f", this->totalIncome);
	totalOutgo.Format("%.1f", this->totalOutgo);
	difference.Format("%.1f", this->difference);
	GetDlgItem(IDC_STATIC_TOTALINCOME_VALUE)->SetWindowTextA(totalIncome);
	GetDlgItem(IDC_STATIC_TOTALOUTGO_VALUE)->SetWindowTextA(totalOutgo);
	GetDlgItem(IDC_STATIC_DIFFERENCE_VALUE)->SetWindowTextA(difference);
	
	
	
}

void FindingForm::OnClose() {
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	EndDialog(0);
}