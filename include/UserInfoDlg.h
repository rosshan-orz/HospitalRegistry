#pragma once
#include "afxdialogex.h"
#include "SQLInterface.h"


// UserInfoDlg 对话框

class UserInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UserInfoDlg)

public:
	UserInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UserInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UserInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	CListCtrl m_UserInfo;
	SQLInterface SQL;
	vector<UserInfo> Info;
	void UserUpdateList();
	afx_msg void OnBnClickedButtonLoad();
};
