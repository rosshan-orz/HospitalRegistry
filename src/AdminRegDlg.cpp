// AdminRegDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "AdminRegDlg.h"


// AdminRegDlg 对话框

IMPLEMENT_DYNAMIC(AdminRegDlg, CDialogEx)

AdminRegDlg::AdminRegDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AdminReg, pParent)
	, AdminAccount(_T(""))
	, AdminPwd(_T(""))
	, Token(_T(""))
{

}

AdminRegDlg::~AdminRegDlg()
{
}

void AdminRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AdminAccount, AdminAccount);
	DDX_Text(pDX, IDC_EDIT_AdminPwd, AdminPwd);
	DDX_Text(pDX, IDC_EDIT_Token, Token);
	DDX_Text(pDX, IDC_EDIT_Token, Token);
}


BEGIN_MESSAGE_MAP(AdminRegDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AdminRegExit, &AdminRegDlg::OnBnClickedButtonAdminregexit)
	ON_BN_CLICKED(IDC_BUTTON_AdminRegCon, &AdminRegDlg::OnBnClickedButtonAdminregcon)
END_MESSAGE_MAP()


// AdminRegDlg 消息处理程序


void AdminRegDlg::OnBnClickedButtonAdminregexit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void AdminRegDlg::OnBnClickedButtonAdminregcon()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!SQL.Connect_MySQL())
	{
		return;
	}
	if (AdminAccount == TEXT("") || AdminPwd == TEXT(""))
	{
		AfxMessageBox(_T("账号或密码不能为空！"));
		SQL.Close_MySQL();
	}
	else if (Token == "123456")
	{
		AfxMessageBox(_T("成功注册！"));
		if (SQL.Add_AdminInfo(AdminInfo(AdminAccount.GetBuffer(), AdminPwd.GetBuffer())))
		{
			MessageBox(TEXT("注册成功！"), TEXT("提示"));
			SQL.Close_MySQL();
		}
		// EndDialog(0);
	}
	else
	{
		AfxMessageBox(_T("令牌错误！"));
		SQL.Close_MySQL();
	}
}
