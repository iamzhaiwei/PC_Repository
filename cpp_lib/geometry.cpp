// geometry.cpp
//////////////////////////////////////////////////////////////////////

#include "geometry.h"

using namespace std;
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{

// 重载点类的输出<<操作符
ostream &operator<<(ostream &ostr, const point &rhs)
{
    ostr << "(" << rhs.X << "," << rhs.Y << ")";
    return ostr;
}

// 重载点类的<操作符
bool operator<(const point &lhs, const point &rhs)
{
	return lhs.X < rhs.X || (lhs.X == rhs.X && lhs.Y < rhs.Y);
}

// 区间类重载输出<<操作符
std::ostream &operator<<(std::ostream &ostr, const both_closed_interval &interval)
{
    ostr << "[" << interval.m_begin << "," << interval.m_end << "]";
    return ostr;
}

// 区间类重载比较<操作符
bool operator<(const both_closed_interval &lhs, const both_closed_interval &rhs)
{
    return ( (lhs.m_begin < rhs.m_begin) ||
             (lhs.m_begin == rhs.m_begin && lhs.m_end < rhs.m_end) );
}

}
