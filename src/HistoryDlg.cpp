// HistoryDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "HistoryDlg.h"


// HistoryDlg 对话框

IMPLEMENT_DYNAMIC(HistoryDlg, CDialogEx)

HistoryDlg::HistoryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_History, pParent)
{

}

HistoryDlg::~HistoryDlg()
{
}

void HistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_History, HistoryList);
}


BEGIN_MESSAGE_MAP(HistoryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &HistoryDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_Load, &HistoryDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// HistoryDlg 消息处理程序


void HistoryDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


BOOL HistoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HistoryList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);	// 整行选择、网格线
	HistoryList.InsertColumn(0, _T("预约编号"), LVCFMT_LEFT, 100);	// 插入第1列的列名
	HistoryList.InsertColumn(1, _T("预约日期"), LVCFMT_LEFT, 200);	// 插入第2列的列名
	HistoryList.InsertColumn(2, _T("预约开始时间"), LVCFMT_LEFT, 200);	// 插入第3列的列名
	HistoryList.InsertColumn(3, _T("预约结束时间"), LVCFMT_LEFT, 200);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void HistoryDlg::HistoryUpdateList()
{
	HistoryList.DeleteAllItems();
	CString str;
	for (int i = 0; i < HisInfo.size(); i++)
	{
		HistoryList.InsertItem(i, HisInfo[i].m_order_id.c_str());
		HistoryList.SetItemText(i, 1, HisInfo[i].m_order_day.c_str());
		HistoryList.SetItemText(i, 2, HisInfo[i].m_time_begin.c_str());
		HistoryList.SetItemText(i, 3, HisInfo[i].m_time_over.c_str());
	}
}




void HistoryDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	if (SQL.Connect_MySQL())
	{
		vector<TempInfo> State;
		State = SQL.SeekTemp("1");
		CString phone = CA2T(State.front().m_phone.c_str());
		HisInfo = SQL.Get_All_Order(phone);
		HistoryUpdateList();
		SQL.Close_MySQL();
	}
	else
	{
		SQL.Close_MySQL();
		return;
	}
}
