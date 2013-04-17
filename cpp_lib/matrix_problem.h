// array_problem.h
//
// last-edit-by: <> 
//
// Description:
// 矩阵问题
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX_PROBLEM_H
#define MATRIX_PROBLEM_H 1

#include <iostream>
#include <boost/multi_array.hpp>

namespace zhaiwei
{
// 对矩阵重载输出操作符
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const boost::multi_array<T, 2> &matrix);

// 逆时针生成矩阵
// 生成以下矩阵：
// 1 16 15 14 13
// 2 17 24 23 12
// 3 18 25 22 11
// 4 19 20 21 10
// 5 6  7  8  9
void generate_matrix_by_anticlockwise(int rows, int cols);

// 计算子矩阵的最大和
int max_sum_of_submatrix(const boost::multi_array<int, 2> &mat);

// 动态规划方法求矩阵链相乘的加括号顺序
// dim_array: 矩阵链的维度数组，矩阵Ai的维度为dim_array[i-1]*dim_array[i]
// size: 维度数组的长度
// 打印加括号顺序，返回矩阵链相乘需要的标量乘法次数
int matrix_chain_multiply_order(int *dim_array, int len);

// 顺时针打印矩阵
// 题目：输入一个矩阵(mxn)，按照从外向里以顺时针的顺序依次打印出每一个数字。
// 例如：如果输入如下矩阵：
// 1              2              3              4
// 5              6              7              8
// 9              10             11             12
// 13             14             15             16
// 则依次打印出数字1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10。
// 分析：包括Autodesk、EMC在内的多家公司在面试或者笔试里采用过这道题。
void print_matrix_by_clockwise(const boost::multi_array<int, 2> &mat, int m, int n);


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

// 对矩阵重载输出操作符
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
