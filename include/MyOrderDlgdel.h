#pragma once
#include "afxdialogex.h"

#include "SQLInterface.h"

// MyOrderDlg 对话框

class MyOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MyOrderDlg)

public:
	MyOrderDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MyOrderDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MyOrder };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2Exit();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL OnInitDialog();
	CListCtrl MyOrderList;
	SQLInterface SQL;
	vector<User_order> OrderInfo;
	void MyOrderUpdateList();
	afx_msg void OnBnClickedButtonLoad();
	CString GlobalPhone;
	afx_msg void OnBnClickedButtonCancelorder();
	CString OrderID;
	CDateTimeCtrl m_date;
	CTime m_date_select;
};
