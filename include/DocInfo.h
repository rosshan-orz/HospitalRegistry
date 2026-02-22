#pragma once
class DocInfo
{
public:
	string m_doctor_id;		// 医生ID
	string m_doctor_name;	// 医生名字
	string m_depart;		// 医生所属科室
	string m_pos;			// 医生职称
	string m_Mon;			// 周一排班
	string m_Tue;			// 周二排班
	string m_Wed;			// 周三排班
	string m_Thur;			// 周四排班
	string m_Fri;			// 周五排班

	DocInfo();
	DocInfo(
		string doctor_id,
		string doctor_name,
		string depart,
		string pos,
		string Mon,
		string Tue,
		string Wed,
		string Thur,
		string Fri
	);
};

