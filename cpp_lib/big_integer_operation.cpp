// big_integer_operation.cpp
//////////////////////////////////////////////////////////////////////

#include "big_integer_operation.h"
#include <iostream>
//////////////////////////////////////////////////////////////////////

using namespace std;

namespace zhaiwei
{
// 大正整数比较
// lhs > rhs, 返回1
// lhs == rhs, 返回0
// lhs < rhs, 返回-1
int big_integer_compare(int *lhs, int lhs_length, int *rhs, int rhs_length)
{
    if (lhs_length > rhs_length)
        return 1;
    if (lhs_length < rhs_length)
        return -1;
    for (int i = lhs_length-1; i >= 0; --i)
    {
        if (lhs[i] > rhs[i])
            return 1;
        else if (lhs[i] < rhs[i])
            return -1;
    }
    return 0;
}

// 加法，返回表示和的整数数组地址
int *big_integer_add(int *lhs, int lhs_length, int *rhs, int rhs_length, int &new_length)
{
    int new_array_length = (lhs_length > rhs_length)? lhs_length+1: rhs_length+1;
    int *p_new_digits = new int[new_array_length];
    int i;
    for (i = 0; i < new_array_length; ++i)
        p_new_digits[i] = 0;
    for (i = 0; i < lhs_length && i < rhs_length; ++i)
        p_new_digits[i] = lhs[i] + rhs[i];
    for (; i < lhs_length; ++i)
        p_new_digits[i] = lhs[i];
    for (; i < rhs_length; ++i)
        p_new_digits[i] = rhs[i];
    big_integer_adjust(p_new_digits, new_array_length, new_length);
    return p_new_digits;
}

// 减法，第一个数大于第二个数
int *big_integer_subtract(int *lhs, int lhs_length, int *rhs, int rhs_length, int &new_length)
{
    int new_array_length = lhs_length;
    int *p_new_digits = new int[new_array_length];
    int i;
    for (i = 0; i < new_array_length; ++i)
        p_new_digits[i] = 0;
    for (i = 0; i < rhs_length; ++i)
        p_new_digits[i] = lhs[i] - rhs[i];
    for (; i < lhs_length; ++i)
        p_new_digits[i] = lhs[i];
    big_integer_adjust(p_new_digits, new_array_length, new_length);
    return p_new_digits;
}

// 乘法
int *big_integer_multiply(int *lhs, int lhs_length, int *rhs, int rhs_length, int &new_length)
{
    int new_array_length = lhs_length + rhs_length + 1;
    int *p_new_digits = new int[new_array_length];
    for (int i = 0; i < new_array_length; ++i)
        p_new_digits[i] = 0;
    for (int i = 0; i < lhs_length; ++i)
    {
        for (int j = 0; j < rhs_length; ++j)
        {
            p_new_digits[i+j] += lhs[i] * rhs[j];
        }
    }
    big_integer_adjust(p_new_digits, new_array_length, new_length);
    return p_new_digits;
}

// 调整数组使每位数字在[0,9]之间
void big_integer_adjust(int *digits_array, int digits_array_length, int &number_digits)
{
    for (int i = 0; i <= digits_array_length-2; ++i)
    {
        if (digits_array[i] >= 10)
        {
            digits_array[i+1] += digits_array[i] / 10;
            digits_array[i] %= 10;
        }
        else if (digits_array[i] < 0)
        {
            digits_array[i] += 10;
            digits_array[i+1] -= 1;
        }
    }
    for(number_digits = digits_array_length-1; number_digits >= 0; --number_digits)
    {
        if (digits_array[number_digits] > 0)
            break;
    }
    ++number_digits;
    if (number_digits == 0)
        number_digits = 1;
}

// 输出正大整数
void big_integer_print(int *digits_array, int length)
{
    for (int i = length-1; i >= 0; --i)
        cout << digits_array[i];
    cout << endl;
}

}
