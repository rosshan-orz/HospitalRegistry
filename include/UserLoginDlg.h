#pragma once
#include "afxdialogex.h"

#include "SQLInterface.h"


// UserLoginDlg 对话框

class UserLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UserLoginDlg)

public:
	UserLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UserLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UserLogin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonUserexit();
	afx_msg void OnBnClickedButtonUserreg();
	afx_msg void OnBnClickedButtonUserlogin();
	CString UserAccount;
	CString UserPwd;
	SQLInterface SQL;
	vector<UserInfo> UserLogin;
};
