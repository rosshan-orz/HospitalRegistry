// DocArrangeDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "DocArrangeDlg.h"

#include "DocInfoDlg.h"
#include "DocWorkdayDlg.h"
#include "DocOrderStateDlg.h"
#include "UserInfoDlg.h"


// DocArrangeDlg 对话框

IMPLEMENT_DYNAMIC(DocArrangeDlg, CDialogEx)

DocArrangeDlg::DocArrangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DocArrange, pParent)
{

}

DocArrangeDlg::~DocArrangeDlg()
{
}

void DocArrangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DocArrangeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DocInfo, &DocArrangeDlg::OnBnClickedButtonDocinfo)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &DocArrangeDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_DocArrange, &DocArrangeDlg::OnBnClickedButtonDocarrange)
	ON_BN_CLICKED(IDC_BUTTON_DocOrder, &DocArrangeDlg::OnBnClickedButtonDocorder)
	ON_BN_CLICKED(IDC_BUTTON_UserInfo, &DocArrangeDlg::OnBnClickedButtonUserinfo)
	ON_BN_CLICKED(IDC_BUTTON_Sum, &DocArrangeDlg::OnBnClickedButtonSum)
END_MESSAGE_MAP()


// DocArrangeDlg 消息处理程序


void DocArrangeDlg::OnBnClickedButtonDocinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	DocInfoDlg DocInfoDlg;
	DocInfoDlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void DocArrangeDlg::OnBnClickedButtonDocarrange()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	DocWorkdayDlg DocWorkdayDlg;
	DocWorkdayDlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void DocArrangeDlg::OnBnClickedButtonDocorder()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	DocOrderStateDlg DocOrderStateDlg;
	DocOrderStateDlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void DocArrangeDlg::OnBnClickedButtonUserinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	UserInfoDlg UserInfoDlg;
	UserInfoDlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void DocArrangeDlg::OnBnClickedButtonSum()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!SQL.Connect_MySQL())
	{
		return;
	}
	if (SQL.Sum("mon") && SQL.Sum("tue") && SQL.Sum("wed") && SQL.Sum("thur") && SQL.Sum("fri"))
	{
		MessageBox(TEXT("求和成功，请在数据库中查看！"), TEXT("提示"));
		SQL.Close_MySQL();
	}
	else
	{
		MessageBox(TEXT("求和失败！"), TEXT("提示"));
		SQL.Close_MySQL();
	}


}


void DocArrangeDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}