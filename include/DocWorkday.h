#pragma once
class DocWorkday
{
public:
	string m_doctor_id;		// 医生ID
	string m_doctor_name;	// 医生姓名
	// 14段预约时间
	string m_time_1;
	string m_time_2;
	string m_time_3;
	string m_time_4;
	string m_time_5;
	string m_time_6;
	string m_time_7;
	string m_time_8;
	string m_time_9;
	string m_time_10;
	string m_time_11;
	string m_time_12;
	string m_time_13;
	string m_time_14;
	string m_total;

	DocWorkday();
	DocWorkday(
		string doctor_id,
		string doctor_name,
		string time_1,
		string time_2,
		string time_3,
		string time_4,
		string time_5,
		string time_6,
		string time_7,
		string time_8,
		string time_9,
		string time_10,
		string time_11,
		string time_12,
		string time_13,
		string time_14,
		string m_total
	);
};

