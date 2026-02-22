#include "pch.h"
#include "User_order.h"

User_order::User_order()
{
}

User_order::User_order(string order_id, string phone_num, string order_day, string time_begin, string time_over, string doctor_id)
{
    m_order_id = order_id;
    m_phone_num = phone_num;
    m_order_day = order_day;
    m_time_begin = time_begin;
    m_time_over = time_over;
    m_doctor_id = doctor_id;
}