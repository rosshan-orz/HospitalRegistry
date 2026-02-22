#pragma once
#include "afxdialogex.h"

#include "SQLInterface.h"

// DocArrangeDlg 对话框

class DocArrangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DocArrangeDlg)

public:
	DocArrangeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DocArrangeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DocArrange };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDocinfo();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonDocarrange();
	afx_msg void OnBnClickedButtonDocorder();
	afx_msg void OnBnClickedButtonUserinfo();
	afx_msg void OnBnClickedButtonSum();
	SQLInterface SQL;
	vector<DocWorkday> Mon;
	vector<DocWorkday> Tue;
	vector<DocWorkday> Wed;
	vector<DocWorkday> Thur;
	vector<DocWorkday> Fri;
};
