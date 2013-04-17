// string_problem.h
//
// last-edit-by: <��լΰ 2012-05-05>
//
// Description:
// �ַ�������
//////////////////////////////////////////////////////////////////////
#ifndef DATE_TIME_H
#define DATE_TIME_H 1

namespace zhaiwei
{

// ������
struct date_t
{
	date_t(int y, int m, int d): year(y), month(m), day(d)
	{}
	
	int year;
	int month;
	int day;
};

// �������������
std::ostream &operator<<(std::ostream &ostr, const date_t &date);

// ����һ�����ڣ�����������һ��ĵڼ���
int date_to_nth_day(const date_t &date);

// �����������ڣ���������֮�������
int number_of_days_between_dates(const date_t &date1, const date_t &date2);

// ����һ�����ڣ�����ֵΪ�ܼ�
int weekday_of_date(const date_t &date);

// �����º��꣬������µ�����
void calendar_of_month(const date_t &date);

}




#endif