// DocOrderStateDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "DocOrderStateDlg.h"


// DocOrderStateDlg 对话框

IMPLEMENT_DYNAMIC(DocOrderStateDlg, CDialogEx)

DocOrderStateDlg::DocOrderStateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DocOrderState, pParent)
{

}

DocOrderStateDlg::~DocOrderStateDlg()
{
}

void DocOrderStateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, DocOrderState);
	DDX_Control(pDX, IDC_COMBO_Day, m_day);
}


BEGIN_MESSAGE_MAP(DocOrderStateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &DocOrderStateDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_Load, &DocOrderStateDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// DocOrderStateDlg 消息处理程序


void DocOrderStateDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}

BOOL DocOrderStateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DocOrderState.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	DocOrderState.InsertColumn(0, _T("医生ID"), LVCFMT_LEFT, 150);   //添加字符串  
	DocOrderState.InsertColumn(1, _T("医生姓名"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(2, _T("8:00-8:30"), LVCFMT_LEFT, 150);   //添加字符串  
	DocOrderState.InsertColumn(3, _T("8:30-9:00"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(4, _T("9:00-9:30"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(5, _T("9:30-10:00"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(6, _T("10:00-10:30"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(7, _T("10:30-11:00"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(8, _T("11:00-11:30"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(9, _T("11:30-12:00"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(10, _T("14:00-14:30"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(11, _T("14:30-15:00"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(12, _T("15:00-15:30"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(13, _T("15:30-16:00"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(14, _T("16:00-16:30"), LVCFMT_LEFT, 150);
	DocOrderState.InsertColumn(15, _T("16:30-17:00"), LVCFMT_LEFT, 150);

	m_day.AddString(_T("星期一"));   //添加字符串  
	m_day.AddString(_T("星期二"));
	m_day.AddString(_T("星期三"));
	m_day.AddString(_T("星期四"));
	m_day.AddString(_T("星期五"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void DocOrderStateDlg::DocOrderStateUpdateList()
{
	DocOrderState.DeleteAllItems();
	CString str;
	for (int i = 0; i < Info.size(); i++)
	{
		DocOrderState.InsertItem(i, Info[i].m_doctor_id.c_str());
		DocOrderState.SetItemText(i, 1, Info[i].m_doctor_name.c_str());
		DocOrderState.SetItemText(i, 2, Info[i].m_time_1.c_str());
		DocOrderState.SetItemText(i, 3, Info[i].m_time_2.c_str());
		DocOrderState.SetItemText(i, 4, Info[i].m_time_3.c_str());
		DocOrderState.SetItemText(i, 5, Info[i].m_time_4.c_str());
		DocOrderState.SetItemText(i, 6, Info[i].m_time_5.c_str());
		DocOrderState.SetItemText(i, 7, Info[i].m_time_6.c_str());
		DocOrderState.SetItemText(i, 8, Info[i].m_time_7.c_str());
		DocOrderState.SetItemText(i, 9, Info[i].m_time_8.c_str());
		DocOrderState.SetItemText(i, 10, Info[i].m_time_9.c_str());
		DocOrderState.SetItemText(i, 11, Info[i].m_time_10.c_str());
		DocOrderState.SetItemText(i, 12, Info[i].m_time_11.c_str());
		DocOrderState.SetItemText(i, 13, Info[i].m_time_12.c_str());
		DocOrderState.SetItemText(i, 14, Info[i].m_time_13.c_str());
		DocOrderState.SetItemText(i, 15, Info[i].m_time_14.c_str());
	}
}

void DocOrderStateDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	int index_cb1 = m_day.GetCurSel();
	switch (index_cb1)
	{
	case 0:
		select_day = "mon";
		break;
	case 1:
		select_day = "tue";
		break;
	case 2:
		select_day = "wed";
		break;
	case 3:
		select_day = "thur";
		break;
	case 4:
		select_day = "fri";
		break;
	}
	if (SQL.Connect_MySQL())
	{
		Info = SQL.Get_All_DocWorkday(select_day);
		DocOrderStateUpdateList();
		SQL.Close_MySQL();
	}
	else
	{
		SQL.Close_MySQL();
		return;
	}
}