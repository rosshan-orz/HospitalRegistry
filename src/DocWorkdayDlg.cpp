// DocWorkdayDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "DocWorkdayDlg.h"


// DocWorkdayDlg 对话框

IMPLEMENT_DYNAMIC(DocWorkdayDlg, CDialogEx)

DocWorkdayDlg::DocWorkdayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DocWorkday, pParent)
	, DocID(_T(""))
{

}

DocWorkdayDlg::~DocWorkdayDlg()
{
}

void DocWorkdayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DocWorkday, DocWorkdayList);
	DDX_Text(pDX, IDC_EDIT_DocID, DocID);
}


BEGIN_MESSAGE_MAP(DocWorkdayDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &DocWorkdayDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_DocWorkdayOK, &DocWorkdayDlg::OnBnClickedButtonDocworkdayok)
	ON_BN_CLICKED(IDC_BUTTON_Load, &DocWorkdayDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// DocWorkdayDlg 消息处理程序

BOOL DocWorkdayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DocWorkdayList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	DocWorkdayList.InsertColumn(0, _T("医生ID"), LVCFMT_LEFT, 150);
	DocWorkdayList.InsertColumn(1, _T("医生姓名"), LVCFMT_LEFT, 150);
	DocWorkdayList.InsertColumn(2, _T("星期一"), LVCFMT_LEFT, 150);
	DocWorkdayList.InsertColumn(3, _T("星期二"), LVCFMT_LEFT, 150);
	DocWorkdayList.InsertColumn(4, _T("星期三"), LVCFMT_LEFT, 150);
	DocWorkdayList.InsertColumn(5, _T("星期四"), LVCFMT_LEFT, 150);
	DocWorkdayList.InsertColumn(6, _T("星期五"), LVCFMT_LEFT, 150);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void DocWorkdayDlg::DocWorkdayUpdateList()
{
	DocWorkdayList.DeleteAllItems();
	CString str;
	for (int i = 0; i < Info.size(); i++)
	{
		DocWorkdayList.InsertItem(i, Info[i].m_doctor_id.c_str());
		DocWorkdayList.SetItemText(i, 1, Info[i].m_doctor_name.c_str());
		DocWorkdayList.SetItemText(i, 2, Info[i].m_Mon.c_str());
		DocWorkdayList.SetItemText(i, 3, Info[i].m_Tue.c_str());
		DocWorkdayList.SetItemText(i, 4, Info[i].m_Wed.c_str());
		DocWorkdayList.SetItemText(i, 5, Info[i].m_Thur.c_str());
		DocWorkdayList.SetItemText(i, 6, Info[i].m_Fri.c_str());
	}
}

void DocWorkdayDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void DocWorkdayDlg::OnBnClickedButtonDocworkdayok()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int state_Mon = ((CButton*)GetDlgItem(IDC_CHECK_Mon))->GetCheck();
	int state_Tue = ((CButton*)GetDlgItem(IDC_CHECK_Tue))->GetCheck();
	int state_Wed = ((CButton*)GetDlgItem(IDC_CHECK_Wed))->GetCheck();
	int state_Thur = ((CButton*)GetDlgItem(IDC_CHECK_Thur))->GetCheck();
	int state_Fri = ((CButton*)GetDlgItem(IDC_CHECK_Fri))->GetCheck();

	if (!SQL.Connect_MySQL())
	{
		return;
	}
	if (SQL.Update_DocArrange(DocID, to_string(state_Mon).c_str(), to_string(state_Tue).c_str(), \
		to_string(state_Wed).c_str(), to_string(state_Thur).c_str(), to_string(state_Fri).c_str()))
	{
		MessageBox(TEXT("修改成功！"), TEXT("提示"));
		SQL.Close_MySQL();
	}
	else
	{
		MessageBox(TEXT("修改失败！"), TEXT("提示"));
		SQL.Close_MySQL();
	}
}


void DocWorkdayDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	if (SQL.Connect_MySQL())
	{
		Info = SQL.Get_All_DocInfo();
		DocWorkdayUpdateList();
		SQL.Close_MySQL();
	}
	else
	{
		SQL.Close_MySQL();
		return;
	}
}



