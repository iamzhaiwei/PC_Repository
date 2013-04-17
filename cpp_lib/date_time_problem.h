// string_problem.h
//
// last-edit-by: <丁宅伟 2012-05-05>
//
// Description:
// 字符串问题
//////////////////////////////////////////////////////////////////////
#ifndef DATE_TIME_H
#define DATE_TIME_H 1

namespace zhaiwei
{

// 日期类
struct date_t
{
	date_t(int y, int m, int d): year(y), month(m), day(d)
	{}
	
	int year;
	int month;
	int day;
};

// 重载输出操作符
std::ostream &operator<<(std::ostream &ostr, const date_t &date);

// 给定一个日期，返回它是这一年的第几天
int date_to_nth_day(const date_t &date);

// 给定两个日期，返回两者之间的天数
int number_of_days_between_dates(const date_t &date1, const date_t &date2);

// 给定一个日期，返回值为周几
int weekday_of_date(const date_t &date);

// 给定月和年，输出该月的日历
void calendar_of_month(const date_t &date);

}




#endif