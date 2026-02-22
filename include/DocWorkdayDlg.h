#pragma once
#include "afxdialogex.h"

#include "SQLInterface.h"

// DocWorkdayDlg 对话框

class DocWorkdayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DocWorkdayDlg)

public:
	DocWorkdayDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DocWorkdayDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DocWorkday };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonDocworkdayok();
	afx_msg void OnBnClickedButtonLoad();
	virtual BOOL OnInitDialog();
	CListCtrl DocWorkdayList;
	SQLInterface SQL;
	vector<DocInfo> Info;
	void DocWorkdayUpdateList();
	CString DocID;
};
