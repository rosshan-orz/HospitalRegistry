#pragma once
#include "afxdialogex.h"

#include "SQLInterface.h"

// UserRegDlg 对话框

class UserRegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UserRegDlg)

public:
	UserRegDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UserRegDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UserReg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdminregexit();
	afx_msg void OnBnClickedButtonAdminregcon();
	CString UserAccount;
	CString UserPwd;
	CString UserID;
	CString UserName;
	vector<UserIDDatabase> UserReg;
	// UserInfo UserReg;
	SQLInterface SQL;
};
