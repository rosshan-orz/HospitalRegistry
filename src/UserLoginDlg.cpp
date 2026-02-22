// UserLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "UserLoginDlg.h"

#include "UserRegDlg.h"
#include "OrderDlg.h"
#include "MyOrderDlg.h"


// UserLoginDlg 对话框

IMPLEMENT_DYNAMIC(UserLoginDlg, CDialogEx)

UserLoginDlg::UserLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UserLogin, pParent)
	, UserAccount(_T(""))
	, UserPwd(_T(""))
{

}

UserLoginDlg::~UserLoginDlg()
{
}

void UserLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UserAccount, UserAccount);
	DDX_Text(pDX, IDC_EDIT_UserPwd, UserPwd);
}


BEGIN_MESSAGE_MAP(UserLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UserExit, &UserLoginDlg::OnBnClickedButtonUserexit)
	ON_BN_CLICKED(IDC_BUTTON_UserReg, &UserLoginDlg::OnBnClickedButtonUserreg)
	ON_BN_CLICKED(IDC_BUTTON_UserLogin, &UserLoginDlg::OnBnClickedButtonUserlogin)
END_MESSAGE_MAP()


// UserLoginDlg 消息处理程序


void UserLoginDlg::OnBnClickedButtonUserexit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void UserLoginDlg::OnBnClickedButtonUserreg()
{
	// TODO: 在此添加控件通知处理程序代码
	UserRegDlg UserRegDlg;
	UserRegDlg.DoModal();
}


void UserLoginDlg::OnBnClickedButtonUserlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (UserAccount == "")
	{
		MessageBox(TEXT("您的输入为空！"), TEXT("提示"));
		return;
	}
	if (!SQL.Connect_MySQL())
	{
		return;
	}
	UserLogin = SQL.SeekUser(UserAccount);
	if (UserLogin.empty())
	{
		MessageBox(TEXT("未注册账户！"), TEXT("提示"));
		SQL.Close_MySQL();
		return;
	}
	CString password = CA2T(UserLogin.front().m_pwd.c_str());//库中含有的密码
	if (UserPwd == password)
	{
		// AfxMessageBox(_T("成功登录！"));
		SQL.Add_Temp(TempInfo(UserAccount.GetBuffer(), "1"));

		OrderDlg Order;
		SQL.Close_MySQL();
		this->ShowWindow(SW_HIDE);
		Order.DoModal();
		EndDialog(0);
	}
	else
	{
		MessageBox(TEXT("密码错误！"), TEXT("提示"));
		SQL.Close_MySQL();
		return;
	}
}
