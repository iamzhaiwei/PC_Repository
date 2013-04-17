// my_algorithm.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef MY_ALGORITHM_H
#define MY_ALGORITHM_H 1

#include <algorithm>
#include <iostream>
#include <boost/multi_array.hpp>

namespace zhaiwei
{
/****************************
*��������
****************************/
// ��Ѷ������
// �붨��һ���꣬�Ƚ�������a��b�Ĵ�С������ʹ�ô��ڡ�С�ڡ�if���
#define max_macro(a, b) (((a-b)&(1<<(sizeof(int)-1)))?b:a)


//��������������ֵ
template <typename T>
const T& median_of_three(const T& a, const T& b, const T& c);


// ���һ������
template <typename T>
void print_matrix(const boost::multi_array<T, 2> &mat, int rows, int cols);


// ��������е�Ԫ��ֵ
template <typename ForwardIterater>
void print_sequence(ForwardIterater begin, ForwardIterater end);
/*********************************************************************
*��������
**********************************************************************/
//��������������ֵ
template <typename T>
const T& median_of_three(const T& a, const T& b, const T& c)
{
	const T& small = std::min<T>(a, b);
	const T& big = std::max<T>(a, b);
	if (c < small)
		return small;
	else if (c < big)
		return c;
	else
		return big;
}


// ���һ������
template <typename T>
void print_matrix(const boost::multi_array<T, 2> &mat, int rows, int cols)
{
    std::cout << rows << "x" << cols << ":" << std::endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


// ��������е�Ԫ��ֵ
template <typename ForwardIterater>
void print_sequence(ForwardIterater begin, ForwardIterater end)
{
    for (; begin != end; ++begin)
    {
        std::cout << *begin << " ";
    }
    std::cout << std::endl;
}

}

#endif // MY_ALGORITHM_H
//////////////////////////////////////////////////////////////////////
