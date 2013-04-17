// matrix_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "matrix_problem.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
//////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;

namespace zhaiwei
{

// 逆时针生成矩阵
// 生成以下矩阵：
// 1 16 15 14 13
// 2 17 24 23 12
// 3 18 25 22 11
// 4 19 20 21 10
// 5 6  7  8  9
// 逆时针生成矩阵边缘位置的元素
// [begin_row,end_row)与[begin_col,end_col)定义一个子矩阵，逆时针生成这个子矩阵最外围的元素
// init_val是初始值
static void generate_matrix_border_by_anticlockwise(boost::multi_array<int, 2> &matrix, int begin_row,
                                                    int end_row, int begin_col, int end_col, int &init_val)
{
    if (begin_row >= end_row || begin_col >= end_col)
        return;
    int i, j;
    if (begin_row+1 == end_row) // 子矩阵只有1行
    {
        i = begin_row;
        for (j = begin_col; j != end_col; ++j)
            matrix[i][j] = init_val++;
        return;
    }
    if (begin_col+1 == end_col) // 子矩阵只有1列
    {
        j = begin_col;
        for (i = begin_row; i != end_row; ++i)
            matrix[i][j] = init_val++;
        return;
    }
    // 子矩阵有多行多列
    j = begin_col;
    for (i = begin_row; i < end_row; ++i)
        matrix[i][j] = init_val++;
    i = end_row - 1;
    for (j = begin_col+1; j < end_col; ++j)
        matrix[i][j] = init_val++;
    j = end_col - 1;
    for (i = end_row-2; i >= begin_row; --i)
        matrix[i][j] = init_val++;
    i = begin_row;
    for (j = end_col-2; j >= begin_col+1; --j)
        matrix[i][j] = init_val++;
}
void generate_matrix_by_anticlockwise(int rows, int cols)
{
    boost::multi_array<int, 2> matrix(extents[rows][cols]);
    int init_val = 1;
    int begin_row = 0, end_row = rows, begin_col = 0, end_col = cols;
    while (begin_row < end_row && begin_col < end_col)
    {
        generate_matrix_border_by_anticlockwise(matrix, begin_row, end_row, begin_col, end_col, init_val);
        ++begin_row;
        --end_row;
        ++begin_col;
        --end_col;
    }
    cout << matrix << endl;
}

// 计算子矩阵的最大和
//返回一个矩阵第i_min行和第i_max行之间第j列的所有元素的和，part_sum是这个矩阵的部分和
static int rows_col_sum(const boost::multi_array<int, 2> &part_sum, int i_min, int i_max, int j)
{
    int sum = part_sum[i_max][j];
    if (i_min >= 1)
        sum -= part_sum[i_min-1][j];
    if (j >= 1)
        sum -= part_sum[i_max][j-1];
    if (i_min >= 1 && j >= 1)
        sum += part_sum[i_min-1][j-1];
    return sum;
}
int max_sum_of_submatrix(const boost::multi_array<int, 2> &mat)
{
    const boost::multi_array<int, 2>::size_type *size_ptr = mat.shape();
    int rows = size_ptr[0];
    int cols = size_ptr[1];

    //预处理部分和
    boost::multi_array<int, 2> part_sum(boost::extents[rows][cols]);
    for (int i = 0; i != rows; ++i)
    {
        for (int j = 0; j != cols; ++j)
        {
            part_sum[i][j] = mat[i][j];
            if (i >= 1)
                part_sum[i][j] += part_sum[i-1][j];
            if (j >= 1)
                part_sum[i][j] += part_sum[i][j-1];
            if (i >= 1 && j >= 1)
                part_sum[i][j] -= part_sum[i-1][j-1];
            std::cout << part_sum[i][j] << " ";
        }
        std::cout << std::endl;
    }

    int start, all;
    int max_sum = mat[0][cols-1];
    for (int i_min = 0; i_min != rows; ++i_min)
    {
        for (int i_max = i_min; i_max != rows; ++i_max)
        {
            start = rows_col_sum(part_sum, i_min, i_max, cols-1);
            all = start;
            for (int j = cols-2; j >= 0; --j)
            {
                start = std::max<int>(rows_col_sum(part_sum, i_min, i_max, j),
                                 rows_col_sum(part_sum, i_min, i_max, j)+start);
                all = std::max<int>(all, start);
            }
            if (all > max_sum)
                max_sum = all;
        }
    }
    return max_sum;
}


// 动态规划方法求矩阵链相乘的加括号顺序
// 递归打印加括号顺序
static void print_bracket_order(const boost::multi_array<int, 2> &bracket_pos, int i, int j)
{
    if (i == j)
    {
        fprintf(stdout, "A%d", i);
    }
    else
    {
        fprintf(stdout, "(");
        int k = bracket_pos[i][j];
        print_bracket_order(bracket_pos, i, k);
        print_bracket_order(bracket_pos, k+1, j);
        fprintf(stdout, ")");
    }
}
// 打印加括号顺序，返回矩阵链相乘需要的标量乘法次数
// dim_array: 矩阵链的维度数组，矩阵Ai的维度为dim_array[i-1]*dim_array[i]
// size: 维度数组的长度
int matrix_chain_multiply_order(int *dim_array, int len)
{
    // 矩阵的个数
    int num = len - 1;
    // total_number[i][j]记录矩阵链Ai...Aj相乘需要的标量乘法次数
    boost::multi_array<int, 2> total_number(boost::extents[num+1][num+1]);
    // bracket_pos[i][j]记录矩阵链Ai...Aj分开的位置
    boost::multi_array<int, 2> bracket_pos(boost::extents[num+1][num+1]);

    for (int i = 1; i<= num; ++i)
    {
        total_number[i][i] = 0;
        bracket_pos[i][i] = i;
    }
    for (int l = 2; l <= num; ++l)
    {
        for (int i = 1; i <= num-l+1; ++i)
        {
            int j = i + l - 1;
            int k = i;
            int tmp_num = total_number[i][k] + total_number[k+1][j] +
                dim_array[i-1] * dim_array[k] * dim_array[j];
            total_number[i][j] = tmp_num;
            bracket_pos[i][j] = k;
            for (k = i+1; k < j; ++k)
            {
                tmp_num = total_number[i][k] + total_number[k+1][j] +
                dim_array[i-1] * dim_array[k] * dim_array[j];
                if (tmp_num < total_number[i][j])
                {
                    total_number[i][j] = tmp_num;
                    bracket_pos[i][j] = k;
                }
            }
        }
    }
    print_bracket_order(bracket_pos, 1, num);
    fprintf(stdout, "\n");
    return total_number[1][num];
}


// 顺时针打印矩阵
// 题目：输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。
// 例如：如果输入如下矩阵：
// 1              2              3              4
// 5              6              7              8
// 9              10             11             12
// 13             14             15             16
// 则依次打印出数字1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10。
// 分析：包括Autodesk、EMC在内的多家公司在面试或者笔试里采用过这道题。
// [begin_row,end_row)与[begin_col,end_col)定义一个子矩阵，顺时针输出这个子矩阵最外围的元素
static void print_matrix_border_by_clockwise(const boost::multi_array<int, 2> &mat, int begin_row,
                                             int end_row, int begin_col, int end_col)
{
    if (begin_row >= end_row || begin_col >= end_col)
        return;
    int i, j;
    if (begin_row+1 == end_row) // 子矩阵中只有一行
    {
        i = begin_row;
        for (j = begin_col; j < end_col; ++j)
            cout << mat[i][j] << " ";
        return;
    }
    if (begin_col+1 == end_col) // 子矩阵中只有一列
    {
        j = begin_col;
        for (i = begin_row; i < end_row; ++i)
            cout << mat[i][j] << " ";
        return;
    }
    // 子矩阵有多行多列
    i = begin_row;
    for (j = begin_col; j < end_col; ++j)
        cout << mat[i][j] << " ";
    j = end_col-1;
    for (i = begin_row+1; i < end_row; ++i)
        cout << mat[i][j] << " ";
    i = end_row-1;
    for (j = end_col-2; j >= begin_col; --j)
        cout << mat[i][j] << " ";
    j = begin_col;
    for (i = end_row-2; i >= begin_row+1; --i)
        cout << mat[i][j] << " ";
}
void print_matrix_by_clockwise(const boost::multi_array<int, 2> &mat, int rows, int cols)
{
    int begin_row = 0, end_row = rows, begin_col = 0, end_col = cols;
    while (true)
    {
        if (begin_row >= end_row || begin_col >= end_col)
            break;
        print_matrix_border_by_clockwise(mat, begin_row, end_row, begin_col, end_col);
        ++begin_row;
        --end_row;
        ++begin_col;
        --end_col;
    }
}

}

