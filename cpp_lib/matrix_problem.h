// array_problem.h
//
// last-edit-by: <> 
//
// Description:
// ��������
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX_PROBLEM_H
#define MATRIX_PROBLEM_H 1

#include <iostream>
#include <boost/multi_array.hpp>

namespace zhaiwei
{
// �Ծ����������������
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const boost::multi_array<T, 2> &matrix);

// ��ʱ�����ɾ���
// �������¾���
// 1 16 15 14 13
// 2 17 24 23 12
// 3 18 25 22 11
// 4 19 20 21 10
// 5 6  7  8  9
void generate_matrix_by_anticlockwise(int rows, int cols);

// �����Ӿ��������
int max_sum_of_submatrix(const boost::multi_array<int, 2> &mat);

// ��̬�滮�������������˵ļ�����˳��
// dim_array: ��������ά�����飬����Ai��ά��Ϊdim_array[i-1]*dim_array[i]
// size: ά������ĳ���
// ��ӡ������˳�򣬷��ؾ����������Ҫ�ı����˷�����
int matrix_chain_multiply_order(int *dim_array, int len);

// ˳ʱ���ӡ����
// ��Ŀ������һ������(mxn)�����մ���������˳ʱ���˳�����δ�ӡ��ÿһ�����֡�
// ���磺����������¾���
// 1              2              3              4
// 5              6              7              8
// 9              10             11             12
// 13             14             15             16
// �����δ�ӡ������1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10��
// ����������Autodesk��EMC���ڵĶ�ҹ�˾�����Ի��߱�������ù�����⡣
void print_matrix_by_clockwise(const boost::multi_array<int, 2> &mat, int m, int n);


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

// �Ծ����������������
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const boost::multi_array<T, 2> &matrix)
{
    const std::size_t *dimension = matrix.shape();
    int rows = dimension[0];
    int cols = dimension[1];
    for (int i = 0; i != rows; ++i)
    {
        for (int j = 0; j != cols; ++j)
        {
            ostr << matrix[i][j] << " ";
        }
        ostr << std::endl;
    }
    return ostr;
}

}

#endif // MATRIX_PROBLEM_H
