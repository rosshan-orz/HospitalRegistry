#pragma once
class User_order
{
public:
    string m_order_id;      // 用户预约ID
    string m_phone_num;     // 预约手机号（账户）
    string m_order_day;     // 预约日期
    // 预约时间
    string m_time_begin;
    string m_time_over;
    string m_doctor_id;     // 预约医生ID

    User_order();
    User_order(
        string order_id,
        string phone_num,
        string order_day,
        string time_begin,
        string time_over,
        string doctor_id
    );
};