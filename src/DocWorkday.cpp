#include "pch.h"
#include "DocWorkday.h"

DocWorkday::DocWorkday()
{
}

DocWorkday::DocWorkday(string doctor_id, string doctor_name, string time_1, string time_2, string time_3, string time_4, string time_5, string time_6, string time_7, string time_8, string time_9, string time_10, string time_11, string time_12, string time_13, string time_14, string total)
{
	m_doctor_id = doctor_id;
	m_doctor_name = doctor_name;
	m_time_1 = time_1;
	m_time_2 = time_2;
	m_time_3 = time_3;
	m_time_4 = time_4;
	m_time_5 = time_5;
	m_time_6 = time_6;
	m_time_7 = time_7;
	m_time_8 = time_8;
	m_time_9 = time_9;
	m_time_10 = time_10;
	m_time_11 = time_11;
	m_time_12 = time_12;
	m_time_13 = time_13;
	m_time_14 = time_14;
	m_total = total;
}