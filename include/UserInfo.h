#pragma once

class UserInfo
{
public:
	string m_user_id;		// 用户身份证
	string m_user_name;		// 用户实名
	string m_phone_num;		// 用户手机号（账号）
	string m_pwd;			// 用户密码

	UserInfo();
	UserInfo(string user_id, string user_name, string phone_num, string pwd);
};