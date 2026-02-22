#pragma once
class UserIDDatabase
{
public:
	string m_user_id;
	string m_user_name;

	UserIDDatabase();
	UserIDDatabase(
		string user_id,
		string user_name
	);
};

