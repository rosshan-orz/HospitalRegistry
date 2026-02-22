#pragma once
#include "afxdialogex.h"
#include "SQLInterface.h"


// OrderDlg 对话框

class OrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(OrderDlg)

public:
	OrderDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~OrderDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Order };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMyorder();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonHistory();
	
	virtual BOOL OnInitDialog();
	SQLInterface SQL;
	CListCtrl OrderList;
	CComboBox m_Time;
	int ordered;
	CString select_time;
	CString select_day;
	vector<DocInfo> DocInfo;
	vector<DocWorkday> Check;
	void DocUpdateList();
	afx_msg void OnBnClickedButtonCheckdoc();
	afx_msg void OnBnClickedButtonOrder();
	afx_msg void OnBnClickedButtonLoad();
	CComboBox m_Day;
	CString DocID;
	struct tm SelectTime;
};
