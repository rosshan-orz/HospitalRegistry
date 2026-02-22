// UserRegDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "UserRegDlg.h"


// UserRegDlg 对话框

IMPLEMENT_DYNAMIC(UserRegDlg, CDialogEx)

UserRegDlg::UserRegDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UserReg, pParent)
	, UserAccount(_T(""))
	, UserPwd(_T(""))
	, UserID(_T(""))
	, UserName(_T(""))
{

}

UserRegDlg::~UserRegDlg()
{
}

void UserRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UserAccount, UserAccount);
	DDX_Text(pDX, IDC_EDIT_UserPwd, UserPwd);
	DDX_Text(pDX, IDC_EDIT_UserID, UserID);
	DDX_Text(pDX, IDC_EDIT_Name, UserName);
}


BEGIN_MESSAGE_MAP(UserRegDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AdminRegExit, &UserRegDlg::OnBnClickedButtonAdminregexit)
	ON_BN_CLICKED(IDC_BUTTON_AdminRegCon, &UserRegDlg::OnBnClickedButtonAdminregcon)
END_MESSAGE_MAP()


// UserRegDlg 消息处理程序


void UserRegDlg::OnBnClickedButtonAdminregexit()
{
	// TODO: 在此添加控件通知处理程序代码

	EndDialog(0);
}


void UserRegDlg::OnBnClickedButtonAdminregcon()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);
	int num = UserAccount.GetLength();//手机号位数
	CString ID_name;//库里的身份证号
	if (num != 11)
	{
		AfxMessageBox(_T("请输入有效的手机号！"));
		// SQL.Close_MySQL();
	}
	else
	{
		if (!SQL.Connect_MySQL())
		{
			return;
		}
		UserReg = SQL.SeekUserID(UserName);
		if (UserReg.empty())
		{
			MessageBox(TEXT("未注册账户！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		ID_name = CA2T(UserReg.front().m_user_name.c_str());
		if (ID_name == UserName && ID_name != TEXT(""))
		{
			if (SQL.Add_UserInfo(UserInfo(UserID.GetBuffer(), UserName.GetBuffer(), UserAccount.GetBuffer(), UserPwd.GetBuffer())))
			{
				MessageBox(TEXT("注册成功！"), TEXT("提示"));
				SQL.Close_MySQL();
			}
			else
			{
				SQL.Close_MySQL();
			}
			// AfxMessageBox(_T("注册成功"));
			EndDialog(0);
		}
		else {
			AfxMessageBox(_T("身份验证失败！"));
			SQL.Close_MySQL();
			return;
		}
		/*
		if (SQL.Add_UserInfo(UserInfo(UserID.GetBuffer(), UserName.GetBuffer(), UserAccount.GetBuffer(), UserPwd.GetBuffer())))
		{
			MessageBox(TEXT("注册成功！"), TEXT("提示"));
			SQL.Close_MySQL();
		}
		else
		{
			SQL.Close_MySQL();
		}*/
	}
	
}
