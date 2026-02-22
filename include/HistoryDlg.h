#pragma once
#include "afxdialogex.h"

#include "SQLInterface.h"

// HistoryDlg 对话框

class HistoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HistoryDlg)

public:
	HistoryDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~HistoryDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_History };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	CListCtrl HistoryList;
	virtual BOOL OnInitDialog();
	vector<User_order> HisInfo;
	SQLInterface SQL;
	void HistoryUpdateList();
	afx_msg void OnBnClickedButtonLoad();
};
