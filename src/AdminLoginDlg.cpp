// AdminLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "AdminLoginDlg.h"

#include "AdminRegDlg.h"
#include "DocArrangeDlg.h"


// AdminLoginDlg 对话框

IMPLEMENT_DYNAMIC(AdminLoginDlg, CDialogEx)

AdminLoginDlg::AdminLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AdminLogin, pParent)
	, AdminAccount(_T(""))
	, AdminPwd(_T(""))
{

}

AdminLoginDlg::~AdminLoginDlg()
{
}

void AdminLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AdminAccount, AdminAccount);
	DDX_Text(pDX, IDC_EDIT_AdminPwd, AdminPwd);
}


BEGIN_MESSAGE_MAP(AdminLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AdminExit, &AdminLoginDlg::OnBnClickedButtonAdminexit)
	ON_BN_CLICKED(IDC_BUTTON_AdminReg, &AdminLoginDlg::OnBnClickedButtonAdminreg)
	ON_BN_CLICKED(IDC_BUTTON_AdminLogin, &AdminLoginDlg::OnBnClickedButtonAdminlogin)
END_MESSAGE_MAP()


// AdminLoginDlg 消息处理程序


void AdminLoginDlg::OnBnClickedButtonAdminexit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}




void AdminLoginDlg::OnBnClickedButtonAdminreg()
{
	// TODO: 在此添加控件通知处理程序代码
	AdminRegDlg AdminRegDlg;
	AdminRegDlg.DoModal();
}


void AdminLoginDlg::OnBnClickedButtonAdminlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!SQL.Connect_MySQL())
	{
		return;
	}
	UpdateData(TRUE);
	if (AdminAccount == "")
	{
		MessageBox(TEXT("您的输入为空！"), TEXT("提示"));
		return;
	}
	AdminLogin = SQL.SeekAdmin(AdminAccount);
	if (AdminLogin.empty())
	{
		MessageBox(TEXT("未注册账户！"), TEXT("提示"));
		return;
	}
	CString password = CA2T(AdminLogin.front().m_pwd.c_str());
	if (AdminPwd == password)
	{
		DocArrangeDlg DocArrange;
		this->ShowWindow(SW_HIDE);
		DocArrange.DoModal();
		EndDialog(0);
		
	}
	else
	{
		AfxMessageBox(_T("密码错误"));
	}
}
