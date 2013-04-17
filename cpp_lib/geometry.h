// geometry.h
//
// last-edit-by: <> 
//
// Description:
// 几何元素如点、线、面等的定义
//////////////////////////////////////////////////////////////////////

#ifndef GEOMETRY_H
#define GEOMETRY_H 1

#include <iostream>

namespace zhaiwei
{

// 点类
class point
{
public:
    explicit point(double x = 0, double y = 0):
        X(x), Y(y)
    {}

    double X;
    double Y;
};

// 重载点类的输出操作符，
std::ostream &operator<<(std::ostream &ostr, const point &rhs);

// 重载点类的比较<操作符
bool operator<(const point &lhs, const point &rhs);


// 将点按照x坐标排序需要用到的函数对象类
// 对点数组的索引排序
class x_less
{
public:
    x_less(point *point_array, int size):
        m_point_array(point_array), m_size(size)
    {}

    bool operator()(int i, int j)
    {
        return m_point_array[i].X < m_point_array[j].X;
    }
private:
    point *m_point_array;
    int m_size;
};

// 将点按照y坐标排序需要用到的函数对象类
// 对点数组的索引排序
class y_less
{
public:
    y_less(point *point_array, int size):
        m_point_array(point_array), m_size(size)
    {}

    bool operator()(int i, int j)
    {
        return m_point_array[i].Y < m_point_array[j].Y;
    }
private:
    point *m_point_array;
    int m_size;
};

// 将点先按x坐标再按y坐标排序需要用到的函数对象类
// 对点数组的索引排序
class x_y_less
{
public:
	x_y_less(point point_array[], int size):
		m_point_array(point_array), m_size(size)
	{}

	bool operator()(int i, int j)
	{
		return m_point_array[i].X < m_point_array[j].X ||
			(m_point_array[i].X == m_point_array[j].X && m_point_array[i].Y < m_point_array[j].Y);

	}
private:
	point *m_point_array;
	int m_size;
};

// 二维向量
class two_dimension_vector
{
public:
    explicit two_dimension_vector(const point &begin_point = point(), const point &end_point = point()):
        m_begin_point(begin_point), m_end_point(end_point)
    {}

    double get_x() const
    {
        return m_end_point.X - m_begin_point.X;
    }

    double get_y() const
    {
        return m_end_point.Y - m_begin_point.Y;
    }
    
    point m_begin_point;
    point m_end_point;
};


// 区间类
class both_closed_interval
{
public:
    both_closed_interval(double begin = 0, double end = 0):
        m_begin(begin), m_end(end)
    {}
    
    double get_length()
    {
        return m_end - m_begin;
    }
    
    double m_begin;
    double m_end;
};

// 区间类重载输出<<操作符
std::ostream &operator<<(std::ostream &ostr, const both_closed_interval &interval);

// 区间类重载比较<操作符
bool operator<(const both_closed_interval &lhs, const both_closed_interval &rhs);


// 对区间数组的索引排序，区间比较<操作符函数对象类
class interval_less_function
{
public:
    interval_less_function(both_closed_interval *array, int length):
        m_array(array), m_length(length)
    {}
    bool operator()(int i, int j)
    {
        return m_array[i] < m_array[j];
    }
private:
    both_closed_interval *m_array;
    int m_length;
};

}

#endif // GEOMETRY_H
//////////////////////////////////////////////////////////////////////
