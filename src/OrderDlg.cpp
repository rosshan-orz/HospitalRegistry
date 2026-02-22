// OrderDlg.cpp: 实现文件
//
#pragma warnign(disable : 4996)
#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "OrderDlg.h"

#include "MyOrderDlg.h"
#include "HistoryDlg.h"


// OrderDlg 对话框

IMPLEMENT_DYNAMIC(OrderDlg, CDialogEx)

OrderDlg::OrderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Order, pParent)
	, DocID(_T(""))
{

}

OrderDlg::~OrderDlg()
{
}

void OrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, OrderList);
	DDX_Control(pDX, IDC_COMBO_Time, m_Time);
	DDX_Control(pDX, IDC_COMBO_Day, m_Day);
	DDX_Text(pDX, IDC_EDIT_DocID, DocID);
}


BEGIN_MESSAGE_MAP(OrderDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MyOrder, &OrderDlg::OnBnClickedButtonMyorder)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &OrderDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_History, &OrderDlg::OnBnClickedButtonHistory)
	ON_BN_CLICKED(IDC_BUTTON_CheckDoc, &OrderDlg::OnBnClickedButtonCheckdoc)
	ON_BN_CLICKED(IDC_BUTTON_Order, &OrderDlg::OnBnClickedButtonOrder)
	ON_BN_CLICKED(IDC_BUTTON_Load, &OrderDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// OrderDlg 消息处理程序


void OrderDlg::OnBnClickedButtonMyorder()
{
	// TODO: 在此添加控件通知处理程序代码
	MyOrderDlg MyOrder;
	MyOrder.DoModal();
}


void OrderDlg::OnBnClickedButtonHistory()
{
	// TODO: 在此添加控件通知处理程序代码
	HistoryDlg History;
	History.DoModal();
}

void OrderDlg::DocUpdateList()
{
	OrderList.DeleteAllItems();
	CString str;
	for (int i = 0; i < DocInfo.size(); i++)
	{
		OrderList.InsertItem(i, DocInfo[i].m_doctor_id.c_str());
		OrderList.SetItemText(i, 1, DocInfo[i].m_doctor_name.c_str());
		OrderList.SetItemText(i, 2, DocInfo[i].m_depart.c_str());
		OrderList.SetItemText(i, 3, DocInfo[i].m_pos.c_str());
	}
}

void OrderDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	SQL.Connect_MySQL();
	SQL.Delete_TempInfo(to_string(1));
	SQL.Close_MySQL();
	EndDialog(0);
}

BOOL OrderDlg::OnInitDialog()
{
	

	CDialogEx::OnInitDialog();
	
	// TODO:  在此添加额外的初始化
	

	OrderList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);	// 整行选择、网格线
	OrderList.InsertColumn(0, _T("医生id"), LVCFMT_LEFT, 120);	// 插入第2列的列名
	OrderList.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 120);	// 插入第3列的列名
	OrderList.InsertColumn(2, _T("科室"), LVCFMT_LEFT, 120);	// 插入第4列的列名
	OrderList.InsertColumn(3, _T("职位"), LVCFMT_LEFT, 120);	// 插入第5列的列名
	
	m_Time.AddString(_T("8:00-8:30"));   //添加字符串  
	m_Time.AddString(_T("8:30-9:00"));
	m_Time.AddString(_T("9:00-9:30"));
	m_Time.AddString(_T("9:30-10:00"));
	m_Time.AddString(_T("10:00-10:30"));
	m_Time.AddString(_T("10:30-11:00"));
	m_Time.AddString(_T("11:00-11:30"));
	m_Time.AddString(_T("11:30-12:00"));
	m_Time.AddString(_T("14:00-14:30"));
	m_Time.AddString(_T("14:30-15:00"));
	m_Time.AddString(_T("15:00-15:30"));
	m_Time.AddString(_T("15:30-16:00"));
	m_Time.AddString(_T("16:00-16:30"));
	m_Time.AddString(_T("16:30-17:00"));

	m_Day.AddString(_T("星期一"));   //添加字符串  
	m_Day.AddString(_T("星期二"));
	m_Day.AddString(_T("星期三"));
	m_Day.AddString(_T("星期四"));
	m_Day.AddString(_T("星期五"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void OrderDlg::OnBnClickedButtonCheckdoc()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);    //这个函数的使用请参考数据交换UpdateData，那篇文章  
	int index_cb1 = m_Day.GetCurSel();
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
	int index_cb2 = m_Time.GetCurSel();  //这个函数用于得到用户选择的是下拉列表中的第几行，第一行的话，返回0，依次类推

	time_t now;
	time(&now);
	struct tm loctime;
	localtime_s(&loctime, &now);
	char time_now[10];
	char day_now[12];
	snprintf(time_now, 10, "%02d:%02d:%02d", loctime.tm_hour, loctime.tm_min, loctime.tm_sec);
	snprintf(day_now, 12, "%d-%02d-%02d", loctime.tm_year + 1900, loctime.tm_mon + 1, loctime.tm_mday);

	CString TIME = time_now;
	CString DAY = day_now;
	CString tep_time_1 = "08:00:00";
	CString tep_time_2 = "08:30:00";
	CString tep_time_3 = "09:00:00";
	CString tep_time_4 = "09:30:00";
	CString tep_time_5 = "10:00:00";
	CString tep_time_6 = "10:30:00";
	CString tep_time_7 = "11:00:00";
	CString tep_time_8 = "11:30:00";
	CString tep_time_9 = "14:00:00";
	CString tep_time_10 = "14:30:00";
	CString tep_time_11 = "15:00:00";
	CString tep_time_12 = "15:30:00";
	CString tep_time_13 = "16:00:00";
	CString tep_time_14 = "16:30:00";


	if (!SQL.Connect_MySQL())
	{
		return;
	}
	Check = SQL.SeekDocWorkday(select_day, DocID);
	if (Check.empty())
	{
		MessageBox(TEXT("所选医生当日不工作！"), TEXT("提示"));
		SQL.Close_MySQL();
		return;
	}
	if (loctime.tm_wday > (index_cb1 + 1))
	{
		MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
		SQL.Close_MySQL();
		return;
	}
	switch (index_cb2)
	{
	case 0:
		ordered = stoi(Check.front().m_time_1);
		if (loctime.tm_wday == (index_cb1+1) && TIME >= tep_time_1)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 1:
		ordered = stoi(Check.front().m_time_2);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_2)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 2:
		ordered = stoi(Check.front().m_time_3);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_3)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 3:
		ordered = stoi(Check.front().m_time_4);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_4)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 4:
		ordered = stoi(Check.front().m_time_5);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_5)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 5:
		ordered = stoi(Check.front().m_time_6);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_6)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 6:
		ordered = stoi(Check.front().m_time_7);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_7)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 7:
		ordered = stoi(Check.front().m_time_8);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_8)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 8:
		ordered = stoi(Check.front().m_time_9);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_9)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 9:
		ordered = stoi(Check.front().m_time_10);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_10)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 10:
		ordered = stoi(Check.front().m_time_11);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_11)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 11:
		ordered = stoi(Check.front().m_time_12);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_12)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 12:
		ordered = stoi(Check.front().m_time_13);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_13)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	case 13:
		ordered = stoi(Check.front().m_time_14);
		if (loctime.tm_wday == (index_cb1 + 1) && TIME >= tep_time_14)
		{
			MessageBox(TEXT("已过可预约时间！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		if (ordered >= 5)
		{
			MessageBox(TEXT("此时间预约已满！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
		else
		{
			MessageBox(TEXT("此时间有余号！"), TEXT("提示"));
			SQL.Close_MySQL();
			return;
		}
	}

	// SQL.Close_MySQL();
}


void OrderDlg::OnBnClickedButtonOrder()
{
	// TODO: 在此添加控件通知处理程序代码
	// UpdateData(TRUE);    //这个函数的使用请参考数据交换UpdateData，那篇文章  
	int index_cb1 = m_Day.GetCurSel();  //这个函数用于得到用户选择的是下拉列表中的第几行，第一行的话，返回0，依次类推
	int index_cb2 = m_Time.GetCurSel();

	time_t now;
	time(&now);
	struct tm loctime;
	
	localtime_s(&loctime, &now);
	// char time_order_begin[10];
	// char time_order_over[10];
	CString TIME_BEGIN;
	CString TIME_OVER;
	char day_order[12];
	/*
	snprintf(time_now, 10, "%02d:%02d:%02d", loctime.tm_hour, loctime.tm_min, loctime.tm_sec);
	snprintf(day_now, 12, "%d-%02d-%02d", loctime.tm_year+1900, loctime.tm_mon+1, loctime.tm_mday);
	*/
	// MessageBox(TEXT("%s"), TEXT("test"));
	
	// AfxMessageBox("时间" + TIME + "日期" + DAY);

	if (!SQL.Connect_MySQL())
	{
		return;
	}
	vector<TempInfo> State;
	State = SQL.SeekTemp("1");
	CString phone = CA2T(State.front().m_phone.c_str());
	SQL.Close_MySQL();
	int SELECT;

	switch (index_cb1)
	{
	case 0:
		SELECT = 1;
		select_day = "mon";
		break;
	case 1:
		SELECT = 2;
		select_day = "tue";
		break;
	case 2:
		SELECT = 3;
		select_day = "wed";
		break;
	case 3:
		SELECT = 4;
		select_day = "thur";
		break;
	case 4:
		SELECT = 5;
		select_day = "fri";
		break;
	}
	switch (index_cb2)
	{
	case 0:
		select_time = "time1";
		TIME_BEGIN = "08:00:00";
		TIME_OVER = "09:30:00";
		break;
	case 1:
		select_time = "time2";
		TIME_BEGIN = "08:30:00";
		TIME_OVER = "09:00:00";
		break;
	case 2:
		select_time = "time3";
		TIME_BEGIN = "09:00:00";
		TIME_OVER = "09:30:00";
		break;
	case 3:
		select_time = "time4";
		TIME_BEGIN = "09:30:00";
		TIME_OVER = "10:00:00";
		break;
	case 4:
		select_time = "time5";
		TIME_BEGIN = "10:00:00";
		TIME_OVER = "10:30:00";
		break;
	case 5:
		select_time = "time6";
		TIME_BEGIN = "10:30:00";
		TIME_OVER = "11:00:00";
		break;
	case 6:
		select_time = "time7";
		TIME_BEGIN = "11:00:00";
		TIME_OVER = "11:30:00";
		break;
	case 7:
		select_time = "time8";
		TIME_BEGIN = "11:30:00";
		TIME_OVER = "12:00:00";
		break; 
	case 8:
		select_time = "time9";
		TIME_BEGIN = "14:00:00";
		TIME_OVER = "14:30:00";
		break;
	case 9:
		select_time = "time10";
		TIME_BEGIN = "14:30:00";
		TIME_OVER = "15:00:00";
		break;
	case 10:
		select_time = "time11";
		TIME_BEGIN = "15:00:00";
		TIME_OVER = "15:30:00";
		break;
	case 11:
		select_time = "time12";
		TIME_BEGIN = "15:30:00";
		TIME_OVER = "16:00:00";
		break;
	case 12:
		select_time = "time13";
		TIME_BEGIN = "16:00:00";
		TIME_OVER = "16:30:00";
		break;
	case 13:
		select_time = "time14";
		TIME_BEGIN = "16:30:00";
		TIME_OVER = "17:00:00";
		break;
	}
	
	SelectTime.tm_mday = loctime.tm_mday + (SELECT - loctime.tm_wday);

	// snprintf(time_order_begin, 10, "%02d:%02d:%02d", select_time.tm_hour, select_time.tm_min, select_time.tm_sec);
	snprintf(day_order, 12, "%d-%02d-%02d", loctime.tm_year + 1900, loctime.tm_mon + 1, SelectTime.tm_mday);
	
	CString DAY = day_order;


	if (!SQL.Connect_MySQL())
	{
		return;
	}
	if (SQL.Add_User_order(User_order("", phone.GetBuffer(), DAY.GetBuffer(), TIME_BEGIN.GetBuffer(), TIME_OVER.GetBuffer(), DocID.GetBuffer())))
	{
		MessageBox(TEXT("预约成功！"), TEXT("提示"));
		SQL.Update_AddDocWorkday(select_day, select_time, DocID);
		SQL.Close_MySQL();
	}
	else
	{
		SQL.Close_MySQL();
	}
}


void OrderDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	if (SQL.Connect_MySQL())
	{
		DocInfo = SQL.Get_All_DocInfo();
		DocUpdateList();
		SQL.Close_MySQL();
	}
	else
	{
		SQL.Close_MySQL();
		return;
	}
}
