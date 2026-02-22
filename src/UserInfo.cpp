#include "pch.h"
#include "UserInfo.h"

UserInfo::UserInfo()
{
}

UserInfo::UserInfo(string user_id, string user_name, string phone_num, string pwd)
{
	m_user_id = user_id;
	m_user_name = user_name;
	m_phone_num = phone_num;
	m_pwd = pwd;
}