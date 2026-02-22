#include "pch.h"
#include "AdminInfo.h"

AdminInfo::AdminInfo()
{
}

AdminInfo::AdminInfo(string account, string pwd)
{
	m_account = account;
	m_pwd = pwd;
}