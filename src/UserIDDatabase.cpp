#include "pch.h"
#include "UserIDDatabase.h"

UserIDDatabase::UserIDDatabase()
{
}

UserIDDatabase::UserIDDatabase(string user_id, string user_name)
{
	m_user_id = user_id;
	m_user_name = user_name;
}