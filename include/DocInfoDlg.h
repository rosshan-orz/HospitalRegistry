#pragma once
#include "afxdialogex.h"

#include "SQLInterface.h"

// DocInfoDlg 对话框

class DocInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DocInfoDlg)

public:
	DocInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DocInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DocInfo };
#endif
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	CListCtrl DocInfoList;
	SQLInterface SQL;
	vector<DocInfo> Info;
	afx_msg void OnLvnItemchangedListDocinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonLoad();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboDocpos();
	afx_msg void OnCbnSelchangeComboDocdepart();
	CComboBox m_DocDepart_cb1;
	CComboBox m_DocDepart_cb2;
	void DocInfoUpdateList();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDel();
	
	afx_msg void OnEnChangeEditDocid();
	CString DocID;
	CString DocName;
};

