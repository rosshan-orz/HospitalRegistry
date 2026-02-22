// MyOrderDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "MyOrderDlg.h"

#include "UserLoginDlg.h"

// MyOrderDlg 对话框

IMPLEMENT_DYNAMIC(MyOrderDlg, CDialogEx)

MyOrderDlg::MyOrderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MyOrder, pParent)
	, OrderID(_T(""))
{

}

MyOrderDlg::~MyOrderDlg()
{
}

void MyOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MyOrder, MyOrderList);
	DDX_Text(pDX, IDC_EDIT_OrderID, OrderID);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date);
}


BEGIN_MESSAGE_MAP(MyOrderDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2_Exit, &MyOrderDlg::OnBnClickedButton2Exit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &MyOrderDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON_Load, &MyOrderDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_CancelOrder, &MyOrderDlg::OnBnClickedButtonCancelorder)
END_MESSAGE_MAP()


// MyOrderDlg 消息处理程序


void MyOrderDlg::OnBnClickedButton2Exit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void MyOrderDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL MyOrderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	MyOrderList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);	// 整行选择、网格线
	MyOrderList.InsertColumn(0, _T("预约编号"), LVCFMT_LEFT, 100);	// 插入第1列的列名
	MyOrderList.InsertColumn(1, _T("预约日期"), LVCFMT_LEFT, 200);	// 插入第2列的列名
	MyOrderList.InsertColumn(2, _T("预约起始时间"), LVCFMT_LEFT, 200);	// 插入第3列的列名
	MyOrderList.InsertColumn(3, _T("预约结束时间"), LVCFMT_LEFT, 200);
	MyOrderList.InsertColumn(3, _T("预约医生ID"), LVCFMT_LEFT, 100);

	m_date.SetFormat(_T("yyyy-MM-dd"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void MyOrderDlg::MyOrderUpdateList()
{
	MyOrderList.DeleteAllItems();
	CString str;
	for (int i = 0; i < OrderInfo.size(); i++)
	{
		MyOrderList.InsertItem(i, OrderInfo[i].m_order_id.c_str());
		// MyOrderList.SetItemText(i, 1, OrderInfo[i].m_phone_num.c_str());
		MyOrderList.SetItemText(i, 1, OrderInfo[i].m_order_day.c_str());
		MyOrderList.SetItemText(i, 2, OrderInfo[i].m_time_begin.c_str());
		MyOrderList.SetItemText(i, 3, OrderInfo[i].m_time_over.c_str());
		MyOrderList.SetItemText(i, 4, OrderInfo[i].m_doctor_id.c_str());
	}
}


void MyOrderDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	if (SQL.Connect_MySQL())
	{
		vector<TempInfo> State;
		State = SQL.SeekTemp("1");
		CString phone = CA2T(State.front().m_phone.c_str());
		time_t now = time(0);

		OrderInfo = SQL.Get_All_Order(phone);
		MyOrderUpdateList();
		SQL.Close_MySQL();
	}
	else
	{
		SQL.Close_MySQL();
		return;
	}
}


void MyOrderDlg::OnBnClickedButtonCancelorder()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (OrderID == "")
	{
		MessageBox(TEXT("您的输入为空！"), TEXT("提示"));
		return;
	}
	if (!SQL.Connect_MySQL())
	{
		return;
	}
	vector<User_order> DelOrder;
	if (SQL.SeekOrder(OrderID).empty())
	{
		MessageBox(TEXT("无预约记录！"), TEXT("提示"));
		SQL.Close_MySQL();
		return;
	}
	else
	{
		DelOrder = SQL.SeekOrder(OrderID);
		// CString orderday = CA2T(DelOrder.front().m_order_day.c_str());

		m_date.GetTime(m_date_select);
		struct tm delDay;

		// delDay.tm_year = m_date_select.GetYear();
		// delDay.tm_mon = m_date_select.GetMonth();
		delDay.tm_wday = m_date_select.GetDayOfWeek();
		CString orderday;
		switch (delDay.tm_wday)
		{
		case 2:
			orderday = "mon";
			break;
		case 3:
			orderday = "tue";
			break;
		case 4:
			orderday = "wed";
			break;
		case 5:
			orderday = "thur";
			break;
		case 6:
			orderday = "fri";
			break;
		}

		
		CString ordertime_begin = CA2T(DelOrder.front().m_time_begin.c_str());
		CString doctorid = CA2T(DelOrder.front().m_doctor_id.c_str());
		CString ordertime;
		if (ordertime_begin == "08:00:00")
		{
			ordertime = "time1";
		}
		else if (ordertime_begin == "08:30:00")
		{
			ordertime = "time2";
		}
		else if (ordertime_begin == "09:00:00")
		{
			ordertime = "time3";
		}
		else if (ordertime_begin == "09:30:00")
		{
			ordertime = "time4";
		}
		else if (ordertime_begin == "10:00:00")
		{
			ordertime = "time5";
		}
		else if (ordertime_begin == "10:30:00")
		{
			ordertime = "time6";
		}
		else if (ordertime_begin == "11:00:00")
		{
			ordertime = "time7";
		}
		else if (ordertime_begin == "11:30:00")
		{
			ordertime = "time8";
		}
		else if (ordertime_begin == "14:00:00")
		{
			ordertime = "time9";
		}
		else if (ordertime_begin == "14:30:00")
		{
			ordertime = "time10";
		}
		else if (ordertime_begin == "15:00:00")
		{
			ordertime = "time11";
		}
		else if (ordertime_begin == "15:30:00")
		{
			ordertime = "time12";
		}
		else if (ordertime_begin == "16:00:00")
		{
			ordertime = "time13";
		}
		else if (ordertime_begin == "16:30:00")
		{
			ordertime = "time14";
		}

		SQL.Update_DelDocWorkday(orderday, ordertime, doctorid);
		SQL.Delete_User_order(OrderID);
		MessageBox(TEXT("删除成功！"), TEXT("提示"));
		SQL.Close_MySQL();
	}
}
