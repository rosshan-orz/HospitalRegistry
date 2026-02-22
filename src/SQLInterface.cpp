#include "pch.h"
#include "SQLInterface.h"


// 数据库操作
// 连接数据库
bool SQLInterface::Connect_MySQL()
{
	mysql_init(&mysqlCon);
	//mysqlCon 数据库结构 localhost 主机名 root 用户名 "" 密码为空 mytest 数据库 3306 端口
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "[abc]3344653704", "hosp_reg", 3306, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
		return false;
	}
	else
	{
		// AfxMessageBox(_T("成功连接数据库!"));
		// 设置字符集， 使程序支持中文。
		mysql_query(&mysqlCon, "SET NAMES 'GB2312'");//解决从数据库中读取数据后汉字乱码显示的问题 
	}
	return true;
}

// 关闭库
void SQLInterface::Close_MySQL()
{
	mysql_close(&mysqlCon);
}


// 临时数据库，记录当前登录用户状态
// 添加用户登录状态
bool SQLInterface::Add_Temp(TempInfo Info)
{
	snprintf(sql, SQL_MAX, "insert into temp (phone_num,state) values('%s', '%s');", Info.m_phone.c_str(), Info.m_state.c_str());
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	// 判断查询结果
	if (ret) {
		// AfxMessageBox(_T("添加失败!"));
		return false;
	}
	return true;
}

// 查找用户登录状态
vector<TempInfo> SQLInterface::SeekTemp(CString state)
{
	vector<TempInfo> Info;
	// C语言组合字符串
	snprintf(sql, SQL_MAX, "SELECT * FROM temp where state = '%s'", state);
	// 查询数据
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	// 判断查询结果
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return Info;
	}
	// 获取结果集
	res = mysql_store_result(&mysqlCon);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		TempInfo tempinfo = TempInfo(row[0], row[1]);
		Info.push_back(tempinfo);
	};
	// 释放结果集
	mysql_free_result(res);
	return Info;
}

// 退出前删除登陆状态
bool SQLInterface::Delete_TempInfo(string state)
{
	snprintf(sql, SQL_MAX, "delete from temp where state = '%s'", state.c_str());
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("删除失败!"));
		return false;
	}
	return true;
}


// 用户信息操作
// 获取全部用户信息，用于患者信息管理
vector<UserInfo> SQLInterface::Get_All_UserInfo()
{
	vector<UserInfo> Info;
	// C语言组合字符串
	snprintf(sql, SQL_MAX, "SELECT * FROM user_info");
	// 查询数据
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	// 判断查询结果
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return Info;
	}
	// 获取结果集
	res = mysql_store_result(&mysqlCon);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		UserInfo userinfo = UserInfo(row[0], row[1], row[2], row[3]);
		Info.push_back(userinfo);
	};
	// 释放结果集
	mysql_free_result(res);
	return Info;
}

// 查找用户，用于登录
vector<UserInfo> SQLInterface::SeekUser(CString phone_num)
{
	vector<UserInfo> UserLogin;
	snprintf(sql, SQL_MAX, "select * from user_info where phone_num = '%s'", phone_num);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return UserLogin;
	}
	res = mysql_store_result(&mysqlCon);
	while ((row = mysql_fetch_row(res)) != 0)
	{
		UserInfo userlogin = UserInfo(row[0], row[1], row[2], row[3]);
		UserLogin.push_back(userlogin);
	};
	mysql_free_result(res);
	
	return UserLogin;
}

// 添加用户，用于注册
bool SQLInterface::Add_UserInfo(UserInfo Info)
{
	// C语言组合字符串
	snprintf(sql, SQL_MAX, "insert into user_info (user_id,user_name,phone_num,pwd) values('%s', '%s', '%s', '%s');", Info.m_user_id.c_str(), Info.m_user_name.c_str(), Info.m_phone_num.c_str(), Info.m_pwd.c_str());
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	// 判断查询结果
	if (ret) {
		AfxMessageBox(_T("添加失败!"));
		return false;
	}
	return true;
}

// 实名验证时的ID查询
vector<UserIDDatabase> SQLInterface::SeekUserID(CString user_name)
{
	vector<UserIDDatabase> UserID;
	snprintf(sql, SQL_MAX, "select * from user_id_database where user_name = '%s'", user_name);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return UserID;
	}
	res = mysql_store_result(&mysqlCon);
	while ((row = mysql_fetch_row(res)) != 0)
	{
		UserIDDatabase userid = UserIDDatabase(row[0], row[1]);
		UserID.push_back(userid);
	};
	mysql_free_result(res);
	return UserID;
}


// 医生信息管理
// 获取全部医生信息，挂号和医生信息管理使用
vector<DocInfo> SQLInterface::Get_All_DocInfo()
{
	vector<DocInfo> Info;
	// C语言组合字符串
	snprintf(sql, SQL_MAX, "SELECT * FROM doctor");
	// 查询数据
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	// 判断查询结果
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return Info;
	}
	// 获取结果集
	res = mysql_store_result(&mysqlCon);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		DocInfo docinfo = DocInfo(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8]);
		Info.push_back(docinfo);
	};
	// 释放结果集
	mysql_free_result(res);
	return Info;
}

// 获取某医生全部信息，并存到类中
vector<DocInfo> SQLInterface::SeekDocInfo(CString DocID)
{
	vector<DocInfo> SeekDocInfo;
	snprintf(sql, SQL_MAX, "select * from doctor where doctor_id = '%s'", DocID);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return SeekDocInfo;
	}
	res = mysql_store_result(&mysqlCon);
	while ((row = mysql_fetch_row(res)) != 0)
	{
		DocInfo docinfo = DocInfo(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8]);
		SeekDocInfo.push_back(docinfo);
	};
	mysql_free_result(res);
	return SeekDocInfo;
}

// 添加医生信息，用于医生信息管理
bool SQLInterface::Add_DocInfo(DocInfo Info)
{
	snprintf(sql, SQL_MAX, "insert into doctor (doctor_id,doctor_name,depart,pos) values('%s','%s', '%s', '%s')", Info.m_doctor_id.c_str(), Info.m_doctor_name.c_str(), Info.m_depart.c_str(), Info.m_pos.c_str());
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("添加失败!"));
		return false;
	}
	return true;
}

// 添加医生全部信息，包括排班
bool SQLInterface::Add_DocInfoAll(DocInfo Info, CString Mon, CString Tue, CString Wed, CString Thur, CString Fri)
{
	snprintf(sql, SQL_MAX, "insert into doctor (doctor_id,doctor_name,depart,pos,Mon,Tue,Wed,Thur,Fri) values('%s','%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", Info.m_doctor_id.c_str(), Info.m_doctor_name.c_str(), Info.m_depart.c_str(), Info.m_pos.c_str(), Mon, Tue, Wed, Thur, Fri);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("添加失败!"));
		return false;
	}
	return true;
}

// 删除医生信息，用于医生信息管理
bool SQLInterface::Delete_DocInfo(DocInfo Info)
{
	snprintf(sql, SQL_MAX, "delete from doctor where doctor_id = '%s'", Info.m_doctor_id.c_str());
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("删除失败!"));
		return false;
	}
	return true;
}

// 修改医生信息，用于医生信息管理
bool SQLInterface::Update_DocInfo(DocInfo Info)
{
	vector<DocInfo> Temp;
	if((SQLInterface::SeekDocInfo(Info.m_doctor_id.c_str())).empty())
	{
		return false;
	}
	else
	{
		Temp = SQLInterface::SeekDocInfo(Info.m_doctor_id.c_str());
		CString Mon_save = CA2T(Temp.front().m_Mon.c_str());
		CString Tue_save = CA2T(Temp.front().m_Tue.c_str());
		CString Wed_save = CA2T(Temp.front().m_Wed.c_str());
		CString Thur_save = CA2T(Temp.front().m_Thur.c_str());
		CString Fri_save = CA2T(Temp.front().m_Fri.c_str());
		if (!SQLInterface::Delete_DocInfo(Info))
		{
			return false;
		}
		SQLInterface::Delete_DocWorkday("mon", Info.m_doctor_id.c_str());
		SQLInterface::Delete_DocWorkday("tue", Info.m_doctor_id.c_str());
		SQLInterface::Delete_DocWorkday("wed", Info.m_doctor_id.c_str());
		SQLInterface::Delete_DocWorkday("thur", Info.m_doctor_id.c_str());
		SQLInterface::Delete_DocWorkday("fri", Info.m_doctor_id.c_str());
		if (!SQLInterface::Add_DocInfoAll(Info, Mon_save, Tue_save, Wed_save, Thur_save, Fri_save))
		{
			return false;
		}
	}
	
	return true;
}


// 医生排班系统
// 获取某日全部医生挂号信息
vector<DocWorkday> SQLInterface::Get_All_DocWorkday(CString day)
{
	vector<DocWorkday> Info;
	// C语言组合字符串
	snprintf(sql, SQL_MAX, "SELECT * FROM doctor_%s_time", day);
	// 查询数据
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	// 判断查询结果
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return Info;
	}
	// 获取结果集
	res = mysql_store_result(&mysqlCon);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		DocWorkday docinfo = DocWorkday(row[0], row[1], row[2], row[3], \
			row[4], row[5], row[6], row[7], row[8], \
			row[9], row[10], row[11], row[12], row[13], \
			row[14], row[15], row[16]);
		Info.push_back(docinfo);
	};
	// 释放结果集
	mysql_free_result(res);
	return Info;
}

// 添加医生工作安排，用于排班，作用于doctor表
bool SQLInterface::Add_DocArrange(DocInfo Info)
{
	snprintf(sql, SQL_MAX, "insert into doctor (Mon,Tue,Wed,Thur,Fri) values('%d', '%d', '%d', '%d', '%d')", Info.m_Mon, Info.m_Tue, Info.m_Wed, Info.m_Thur, Info.m_Fri);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("添加失败!"));
		return false;
	}
	return true;
}

// 修改医生工作安排，用于排班，作用于doctor表
bool SQLInterface::Update_DocArrange(CString DocID, CString Mon, CString Tue, CString Wed, CString Thur, CString Fri)
{
	snprintf(sql, SQL_MAX, "update doctor set Mon = '%s' , Tue = '%s' , Wed = '%s' , Thur = '%s' , Fri = '%s'  where doctor_id = '%s'", Mon, Tue, Wed, Thur, Fri, DocID);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("更新失败!"));
		return false;
	}
	return true;
}

// 获得医生挂号统计信息
bool SQLInterface::Sum(CString day)
{
	snprintf(sql, SQL_MAX, "update doctor_%s_time set total = time1+time2+time3+time4+time5+time6+time7+time8+time9+time10+time11+time12+time13+time14", day);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret)
	{
		AfxMessageBox(_T("求和失败！"));
		return false;
	}
	return true;
}

// 添加对应星期的医生排班空表
bool SQLInterface::Add_DocWorkday(DocWorkday Info, CString day)
{
	snprintf(sql, SQL_MAX, "insert into doc_'%s'_time values('%s', '%s', \
		'%s', '%s','%s', '%s', '%s', \
		'%s','%s', '%s', '%s', '%s', \
		'%s','%s', '%s', '%s')", \
		day, Info.m_doctor_id, Info.m_doctor_name, \
		Info.m_time_1, Info.m_time_2, Info.m_time_3, Info.m_time_4, Info.m_time_5, \
		Info.m_time_6, Info.m_time_7, Info.m_time_8, Info.m_time_9, Info.m_time_10, \
		Info.m_time_11, Info.m_time_12, Info.m_time_13, Info.m_time_14);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("添加失败!"));
		return false;
	}
	return true;
}

// 删除对应星期的医生排班表
bool SQLInterface::Delete_DocWorkday(CString day, CString DocID)
{
	snprintf(sql, SQL_MAX, "delete from doctor_%s_time where doctor_id = '%s'", day, DocID);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("删除失败!"));
		return false;
	}
	return true;
}


// 挂号操作
// 获取某日时间表
vector<DocWorkday> SQLInterface::SeekDocWorkday(CString day, CString DocID)
{
	vector<DocWorkday> Info;
	// C语言组合字符串
	snprintf(sql, SQL_MAX, "SELECT * FROM doctor_%s_time where doctor_id = '%s'", day, DocID);
	// 查询数据
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	// 判断查询结果
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return Info;
	}
	// 获取结果集
	res = mysql_store_result(&mysqlCon);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		DocWorkday docinfo = DocWorkday(row[0], row[1], row[2], row[3], \
			row[4], row[5], row[6], row[7], row[8], \
			row[9], row[10], row[11], row[12], row[13], \
			row[14], row[15], row[16]);
		Info.push_back(docinfo);
	};
	// 释放结果集
	mysql_free_result(res);
	return Info;
}

// 添加用户挂号信息，用于挂号
bool SQLInterface::Add_User_order(User_order Info)
{
	snprintf(sql, SQL_MAX, "insert into user_order (phone_num,order_day,order_time_begin,order_time_end,doctor_id) values('%s', '%s', '%s','%s', '%s');", Info.m_phone_num.c_str(), Info.m_order_day.c_str(), Info.m_time_begin.c_str(), Info.m_time_over.c_str(), Info.m_doctor_id.c_str());
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	// 判断查询结果
	if (ret) {
		AfxMessageBox(_T("添加失败!"));
		return false;
	}
	return true;
}

// 删除用户挂号信息，用于取消挂号，作用于user_order表
bool SQLInterface::Delete_User_order(CString order_id)
{
	snprintf(sql, SQL_MAX, "delete from user_order where order_id = '%s'", order_id);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("删除失败!"));
		return false;
	}
	return true;
}

// 添加挂号信息，用于doc_day_time表，用于添加挂号
bool SQLInterface::Update_AddDocWorkday(CString order_day, CString order_time, CString doctor_id)
{
	snprintf(sql, SQL_MAX, "update doctor_%s_time set %s = %s + 1 where doctor_id = '%s'", order_day, order_time, order_time, doctor_id);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("更新失败!"));
		return false;
	}
	return true;
}

// 删除挂号信息，用于doc_day_time表，用于删除挂号
bool SQLInterface::Update_DelDocWorkday(CString order_day, CString order_time, CString doctor_id)
{
	snprintf(sql, SQL_MAX, "update doctor_%s_time set %s = %s - 1 where doctor_id = '%s'", order_day, order_time, order_time, doctor_id);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("更新失败!"));
		return false;
	}
	return true;
}

/*
bool SQLInterface::Add_DocWorkday(DocWorkday Info, CString day)
{
	snprintf(sql, SQL_MAX, "insert into doc_'%s'_time values('%d', '%s', \
		'%d', '%d','%d', '%d', '%d', \
		'%d','%d', '%d', '%d', '%d', \
		'%d','%d', '%d', '%d')", \
		day, Info.m_doctor_id, Info.m_doctor_name, \
		Info.m_time_1, Info.m_time_2, Info.m_time_3, Info.m_time_4, Info.m_time_5, \
		Info.m_time_6, Info.m_time_7, Info.m_time_8, Info.m_time_9, Info.m_time_10, \
		Info.m_time_11, Info.m_time_12, Info.m_time_13, Info.m_time_14);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("添加失败!"));
		return false;
	}
	return true;
}
*/


// 查号操作
// 获取当前用户所有已成功挂号
vector<User_order> SQLInterface::Get_All_Order(CString phone_num)
{
	vector<User_order> Info;
	// C语言组合字符串
	snprintf(sql, SQL_MAX, "SELECT * FROM user_order where phone_num = '%s'", phone_num);
	// 查询数据
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	// 判断查询结果
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return Info;
	}
	// 获取结果集
	res = mysql_store_result(&mysqlCon);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		User_order userorder = User_order(row[0], row[1], row[2], row[3], row[4], row[5]);
		Info.push_back(userorder);
	};
	// 释放结果集
	mysql_free_result(res);
	return Info;
}

// 获取对应预约ID的预约信息
vector<User_order> SQLInterface::SeekOrder(CString OrderID)
{
	vector<User_order> UserOrder;
	snprintf(sql, SQL_MAX, "select * from user_order where order_id = '%s'", OrderID);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return UserOrder;
	}
	res = mysql_store_result(&mysqlCon);
	while (row = mysql_fetch_row(res))
	{
		User_order userorder = User_order(row[0], row[1], row[2], row[3], row[4], row[5]);
		UserOrder.push_back(userorder);
	};
	mysql_free_result(res);
	return UserOrder;
}


// 管理员信息操作
// 增加管理员信息，用于管理员注册
bool SQLInterface::Add_AdminInfo(AdminInfo Info)
{
	snprintf(sql, SQL_MAX, "insert into admin(account, pwd) values('%s', '%s');", Info.m_account.c_str(), Info.m_pwd.c_str());
	// 查询数据
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	// 判断查询结果
	if (ret) {
		AfxMessageBox(_T("添加失败!"));
		return false;
	}
	return true;
}

// 查找管理员信息，用于管理员登录
vector<AdminInfo> SQLInterface::SeekAdmin(CString AdminAccount)
{
	vector<AdminInfo> AdminLogin;
	snprintf(sql, SQL_MAX, "select * from admin where account = '%s'", AdminAccount);
	int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
	if (ret) {
		AfxMessageBox(_T("查询失败!"));
		return AdminLogin;
	}
	res = mysql_store_result(&mysqlCon);
	while (row = mysql_fetch_row(res))
	{
		AdminInfo adminlogin = AdminInfo(row[0], row[1]);
		AdminLogin.push_back(adminlogin);
	};
	mysql_free_result(res);
	return AdminLogin;
}