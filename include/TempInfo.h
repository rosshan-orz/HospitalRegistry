#pragma once
class TempInfo
{
public:
	string m_phone;		// 临时数据库，用户手机号
	string m_state;		// 用户登录状态

	TempInfo();
	TempInfo(string phone, string state);
};

