#pragma once

#include "UserInfo.h"
#include "AdminInfo.h"
#include "DocInfo.h"
#include "DocWorkday.h"
#include "User_order.h"
#include "UserIDDatabase.h"
#include "TempInfo.h"
#define SQL_MAX 1024

class SQLInterface
{
public:
	MYSQL_RES* res;	//result
	MYSQL_ROW row;
	MYSQL mysqlCon;	//Connect
	char sql[SQL_MAX];	// SQLÓï¾ä

	bool Connect_MySQL();

	bool SQLInterface::Add_Temp(TempInfo Info);
	vector<TempInfo> SeekTemp(CString state);

	bool Delete_TempInfo(string state);

	vector<UserInfo> Get_All_UserInfo();
	bool SQLInterface::Add_UserInfo(UserInfo Info);
	vector<UserInfo> SeekUser(CString phone_num);
	vector<UserIDDatabase> SeekUserID(CString user_name);

	
	bool SQLInterface::Add_User_order(User_order Info);
	bool SQLInterface::Delete_User_order(CString order_id);
	vector<User_order> SQLInterface::Get_All_Order(CString phone_num);
	vector<User_order> SQLInterface::SeekOrder(CString OrderID);
	
	vector<DocInfo> Get_All_DocInfo();
	bool SQLInterface::Add_DocInfo(DocInfo Info);
	bool SQLInterface::Add_DocInfoAll(DocInfo Info, CString Mon, CString Tue, CString Wed, CString Thur, CString Fri);
	bool SQLInterface::Delete_DocInfo(DocInfo Info);
	bool SQLInterface::Update_DocInfo(DocInfo Info);
	vector<DocInfo> SQLInterface::SeekDocInfo(CString DocID);
	
	

	bool SQLInterface::Add_DocArrange(DocInfo Info);
	bool SQLInterface::Update_DocArrange(CString DocID, CString Mon, CString Tue, CString Wed, CString Thur, CString Fri);
	
	vector<DocWorkday> Get_All_DocWorkday(CString day);
	bool SQLInterface::Sum(CString day);
	vector<DocWorkday> SQLInterface::SeekDocWorkday(CString day, CString DOcID);
	bool SQLInterface::Add_DocWorkday(DocWorkday Info, CString day);
	bool Delete_DocWorkday(CString day, CString DocID);
	bool SQLInterface::Update_AddDocWorkday(CString order_day, CString order_time, CString doctor_id);
	bool SQLInterface::Update_DelDocWorkday(CString order_day, CString order_time, CString doctor_id);

	bool SQLInterface::Add_AdminInfo(AdminInfo Info);
	vector<AdminInfo> SeekAdmin(CString adminid);

	void Close_MySQL();
};
