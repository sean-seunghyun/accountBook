//FindingForm.h
#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include<afxwin.h>
#include "resource.h"
typedef signed long int Long;
typedef double Currency;

class FindingForm :public CDialog {
public:
	enum{IDD=IDD_FINDINGFORM};
public:
	FindingForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnFindButtonClicked();
	afx_msg void OnDateButtonClicked();
	afx_msg void OnDescriptionButtonClicked();
	afx_msg void OnCalculateButtonClicked();
	afx_msg void OnLIstViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

private:
	Long(*indexes);
	Long count;
	Currency totalIncome;
	Currency totalOutgo;
	Currency difference;
};

#endif // !_FINDINGFORM_H
