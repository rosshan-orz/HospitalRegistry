
// Hosp_Reg_UIDlg.h: 头文件
//
#include "SQLInterface.h"

#pragma once


// CHospRegUIDlg 对话框
class CHospRegUIDlg : public CDialogEx
{
// 构造
public:
	CHospRegUIDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSP_REG_UI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	SQLInterface SQL;

	afx_msg void OnBnClickedButtonUser();
	afx_msg void OnBnClickedButtonAdmin();
};
