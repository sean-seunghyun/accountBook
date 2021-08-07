//AccountBookForm.h
#ifndef _ACCOUNTBOOKFORM_H
#define _ACCOUNTBOOKFORM_H
#include"resource.h"
#include"Date.h"
#include<afxwin.h>
typedef signed long int Long;

class AccountBook;
class AccountBookForm :public CDialog {
public:
	enum { IDD = IDD_ACCOUNTBOOKFORM };
public:
	AccountBookForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
	Long Load();
	Long Save();
	void Insert(Long index);
	void Modify(Long index);
	CString GetCode(Date date);


public:
	AccountBook *accountBook;

protected:
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnAmountsFocusLost();
	afx_msg void OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // !_ACCOUNTBOOKFORM_H
