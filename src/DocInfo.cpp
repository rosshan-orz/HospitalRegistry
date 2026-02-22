#include "pch.h"
#include "DocInfo.h"

DocInfo::DocInfo()
{
}

DocInfo::DocInfo(string doctor_id, string doctor_name, string depart, string pos, string Mon, string Tue, string Wed, string Thur, string Fri)
{
	m_doctor_id = doctor_id;
	m_doctor_name = doctor_name;
	m_depart = depart;
	m_pos = pos;
	m_Mon = Mon;
	m_Tue = Tue;
	m_Wed = Wed;
	m_Thur = Thur;
	m_Fri = Fri;
}