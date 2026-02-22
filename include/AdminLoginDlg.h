#pragma once
#include "afxdialogex.h"

#include "SQLInterface.h"


// AdminLoginDlg 对话框

class AdminLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AdminLoginDlg)

public:
	AdminLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AdminLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AdminLogin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdminexit();
	afx_msg void OnBnClickedButtonAdminreg();
	afx_msg void OnBnClickedButtonAdminlogin();
	CString AdminAccount;
	CString AdminPwd;
	SQLInterface SQL;
	vector<AdminInfo> AdminLogin;
};
