// DocInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "Hosp_Reg_UI.h"
#include "afxdialogex.h"
#include "DocInfoDlg.h"
#include "DocInfo.h"
#include "SQLInterface.h"


// DocInfoDlg 对话框

IMPLEMENT_DYNAMIC(DocInfoDlg, CDialogEx)

DocInfoDlg::DocInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DocInfo, pParent)
	, DocID(_T(""))
	, DocName(_T(""))
{
	// AfxMessageBox(_T("hi"));
	/*if (SQL.Connect_MySQL())
	{
		Info = SQL.Get_All_DocInfo();
		// UpdateList();
	}
	else
	{
		return;
	}*/
	
}

DocInfoDlg::~DocInfoDlg()
{
}

void DocInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DocInfo, DocInfoList);
	DDX_Control(pDX, IDC_COMBO_DocDepart, m_DocDepart_cb1);
	DDX_Control(pDX, IDC_COMBO_DocPos, m_DocDepart_cb2);
	DDX_Text(pDX, IDC_EDIT_DocID, DocID);
	DDX_Text(pDX, IDC_EDIT_DocName, DocName);
}


BEGIN_MESSAGE_MAP(DocInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &DocInfoDlg::OnBnClickedButtonExit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DocInfo, &DocInfoDlg::OnLvnItemchangedListDocinfo)
	ON_BN_CLICKED(IDC_BUTTON_Load, &DocInfoDlg::OnBnClickedButtonLoad)
	ON_CBN_SELCHANGE(IDC_COMBO_DocPos, &DocInfoDlg::OnCbnSelchangeComboDocpos)
	ON_CBN_SELCHANGE(IDC_COMBO_DocDepart, &DocInfoDlg::OnCbnSelchangeComboDocdepart)
	ON_BN_CLICKED(IDC_BUTTON_Add, &DocInfoDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Change, &DocInfoDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_Del, &DocInfoDlg::OnBnClickedButtonDel)
	ON_EN_CHANGE(IDC_EDIT_DocID, &DocInfoDlg::OnEnChangeEditDocid)
END_MESSAGE_MAP()


// DocInfoDlg 消息处理程序

BOOL DocInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DocInfoList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	DocInfoList.InsertColumn(0, _T("医生ID"), LVCFMT_LEFT, 150);
	DocInfoList.InsertColumn(1, _T("医生姓名"), LVCFMT_LEFT, 150);
	DocInfoList.InsertColumn(2, _T("科室"), LVCFMT_LEFT, 150);
	DocInfoList.InsertColumn(3, _T("职称"), LVCFMT_LEFT, 150);


	m_DocDepart_cb1.AddString(_T("内科"));   //添加字符串  
	m_DocDepart_cb1.AddString(_T("外科"));
	m_DocDepart_cb1.AddString(_T("儿科"));
	m_DocDepart_cb1.AddString(_T("妇科"));
	m_DocDepart_cb1.AddString(_T("脑科"));

	m_DocDepart_cb1.SetCurSel(0);   //默认选择第一个

	m_DocDepart_cb2.AddString(_T("实习医师"));//添加字符串
	m_DocDepart_cb2.AddString(_T("医师"));     
	m_DocDepart_cb2.AddString(_T("主治医师"));
	m_DocDepart_cb2.AddString(_T("副主任医师"));
	m_DocDepart_cb2.AddString(_T("主任医师"));

	m_DocDepart_cb2.SetCurSel(0);   //默认选择第一个

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void DocInfoDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void DocInfoDlg::OnLvnItemchangedListDocinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void DocInfoDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	if (SQL.Connect_MySQL())
	{
		Info = SQL.Get_All_DocInfo();
		DocInfoUpdateList();
		SQL.Close_MySQL();
	}
	else
	{
		SQL.Close_MySQL();
		return;
	}
}




void DocInfoDlg::OnCbnSelchangeComboDocpos()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void DocInfoDlg::OnCbnSelchangeComboDocdepart()
{
	// TODO: 在此添加控件通知处理程序代码
}


void DocInfoDlg::DocInfoUpdateList()
{
	DocInfoList.DeleteAllItems();
	CString str;
	for (int i = 0; i < Info.size(); i++)
	{
		DocInfoList.InsertItem(i, Info[i].m_doctor_id.c_str());
		DocInfoList.SetItemText(i, 1, Info[i].m_doctor_name.c_str());
		DocInfoList.SetItemText(i, 2, Info[i].m_depart.c_str());
		DocInfoList.SetItemText(i, 3, Info[i].m_pos.c_str());
	}
}

void DocInfoDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);    //这个函数的使用请参考数据交换UpdateData，那篇文章  
	int index_cb1 = m_DocDepart_cb1.GetCurSel();  //这个函数用于得到用户选择的是下拉列表中的第几行，第一行的话，返回0，依次类推
	int index_cb2 = m_DocDepart_cb2.GetCurSel();  //这个函数用于得到用户选择的是下拉列表中的第几行，第一行的话，返回0，依次类推
	
	CString DocDepart;
	CString DocPos;
	switch (index_cb1)
	{
	case 0: DocDepart = "内科"; break;
	case 1: DocDepart = "外科"; break;
	case 2: DocDepart = "儿科"; break;
	case 3: DocDepart = "妇科"; break;
	case 4: DocDepart = "脑科"; break;
	}
	switch (index_cb2)
	{
	case 0: DocPos = "实习医师"; break;
	case 1: DocPos = "医师"; break;
	case 2: DocPos = "主治医师"; break;
	case 3: DocPos = "副主任医师"; break;
	case 4: DocPos = "主任医师"; break;

	}
	
	if (!SQL.Connect_MySQL())
	{
		return;
	}
	if (SQL.Add_DocInfo(DocInfo(DocID.GetBuffer(), DocName.GetBuffer(), DocDepart.GetBuffer(), DocPos.GetBuffer(), "", "", "", "", "")))
	{
		MessageBox(TEXT("添加成功！"), TEXT("提示"));
		// DocInfoUpdateList();
		SQL.Close_MySQL();
	}
	else
	{
		MessageBox(TEXT("添加失败！"), TEXT("提示"));
		// DocInfoUpdateList();
		SQL.Close_MySQL();
	}
}


void DocInfoDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);    //这个函数的使用请参考数据交换UpdateData，那篇文章  
	int index_cb1 = m_DocDepart_cb1.GetCurSel();  //这个函数用于得到用户选择的是下拉列表中的第几行，第一行的话，返回0，依次类推
	int index_cb2 = m_DocDepart_cb2.GetCurSel();  //这个函数用于得到用户选择的是下拉列表中的第几行，第一行的话，返回0，依次类推

	CString DocDepart;
	CString DocPos;
	switch (index_cb1)
	{
	case 0: DocDepart = "内科"; break;
	case 1: DocDepart = "外科"; break;
	case 2: DocDepart = "儿科"; break;
	case 3: DocDepart = "妇科"; break;
	case 4: DocDepart = "脑科"; break;
	}
	switch (index_cb2)
	{
	case 0: DocPos = "实习医师"; break;
	case 1: DocPos = "医师"; break;
	case 2: DocPos = "主治医师"; break;
	case 3: DocPos = "副主任医师"; break;
	case 4: DocPos = "主任医师"; break;
	}

	if (!SQL.Connect_MySQL())
	{
		return;
	}
	if (SQL.Update_DocInfo(DocInfo(DocID.GetBuffer(), DocName.GetBuffer(), DocDepart.GetBuffer(), DocPos.GetBuffer(), "", "", "", "", "")))
	{
		MessageBox(TEXT("修改成功！"), TEXT("提示"));
		// DocInfoUpdateList();
		SQL.Close_MySQL();
	}
	else
	{
		MessageBox(TEXT("修改失败！"), TEXT("提示"));
		// DocInfoUpdateList();
		SQL.Close_MySQL();
	}
}


void DocInfoDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);    //这个函数的使用请参考数据交换UpdateData，那篇文章  
	int index_cb1 = m_DocDepart_cb1.GetCurSel();  //这个函数用于得到用户选择的是下拉列表中的第几行，第一行的话，返回0，依次类推
	int index_cb2 = m_DocDepart_cb2.GetCurSel();  //这个函数用于得到用户选择的是下拉列表中的第几行，第一行的话，返回0，依次类推
	
	if (!SQL.Connect_MySQL())
	{
		return;
	}
	if (SQL.Delete_DocInfo(DocInfo(DocID.GetBuffer(), "", "", "", "", "", "", "", "")))
	{
		MessageBox(TEXT("删除成功！"), TEXT("提示"));
		SQL.Delete_DocWorkday("mon", DocID.GetBuffer());
		SQL.Delete_DocWorkday("tue", DocID.GetBuffer());
		SQL.Delete_DocWorkday("wed", DocID.GetBuffer());
		SQL.Delete_DocWorkday("thur", DocID.GetBuffer());
		SQL.Delete_DocWorkday("fri", DocID.GetBuffer());
		// DocInfoUpdateList();
		SQL.Close_MySQL();
	}
	else
	{
		MessageBox(TEXT("删除失败！"), TEXT("提示"));
		// DocInfoUpdateList();
		SQL.Close_MySQL();
	}
}


void DocInfoDlg::OnEnChangeEditDocid()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
