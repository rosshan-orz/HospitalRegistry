#pragma once
#include "afxdialogex.h"

#include "SQLInterface.h"

// DocOrderStateDlg 对话框

class DocOrderStateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DocOrderStateDlg)

public:
	DocOrderStateDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DocOrderStateDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DocOrderState };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	CListCtrl DocOrderState;
	SQLInterface SQL;
	vector<DocWorkday> Info;
	afx_msg void OnBnClickedButtonLoad();
	CComboBox m_day;
	CString select_day;
	virtual BOOL OnInitDialog();
	void DocOrderStateUpdateList();
};
