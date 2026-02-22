// UserInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "UserInfoDlg.h"


// UserInfoDlg 对话框

IMPLEMENT_DYNAMIC(UserInfoDlg, CDialogEx)

UserInfoDlg::UserInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UserInfo, pParent)
{

}

UserInfoDlg::~UserInfoDlg()
{
}

void UserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UserInfo, m_UserInfo);
}


BEGIN_MESSAGE_MAP(UserInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &UserInfoDlg::OnBnClickedButtonExit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &UserInfoDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON_Load, &UserInfoDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// UserInfoDlg 消息处理程序


void UserInfoDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void UserInfoDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void UserInfoDlg::UserUpdateList()
{
	m_UserInfo.DeleteAllItems();
	CString str;
	for (int i = 0; i < Info.size(); i++)
	{
		m_UserInfo.InsertItem(i, Info[i].m_user_id.c_str());
		m_UserInfo.SetItemText(i, 1, Info[i].m_user_name.c_str());
		m_UserInfo.SetItemText(i, 2, Info[i].m_phone_num.c_str());
		m_UserInfo.SetItemText(i, 3, Info[i].m_pwd.c_str());
	}
}

BOOL UserInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_UserInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);	// 整行选择、网格线
	m_UserInfo.InsertColumn(0, _T("id"), LVCFMT_LEFT, 200);	// 插入第2列的列名
	m_UserInfo.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 100);	// 插入第3列的列名
	m_UserInfo.InsertColumn(2, _T("手机号"), LVCFMT_LEFT, 200);	// 插入第4列的列名
	m_UserInfo.InsertColumn(2, _T("密码"), LVCFMT_LEFT, 150);	// 插入第4列的列名
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void UserInfoDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	if (SQL.Connect_MySQL())
	{
		Info = SQL.Get_All_UserInfo();
		UserUpdateList();
		SQL.Close_MySQL();
	}
	else
	{
		SQL.Close_MySQL();
		return;
	}
}
