#pragma once
#include "afxdialogex.h"

#include "SQLInterface.h"


// AdminRegDlg 对话框

class AdminRegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AdminRegDlg)

public:
	AdminRegDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AdminRegDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AdminReg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdminregexit();
	afx_msg void OnBnClickedButtonAdminregcon();
	CString AdminAccount;
	CString AdminPwd;
	CString Token;
	SQLInterface SQL;
};
