// big_integer_operation.h
//
// last-edit-by: <> 
//
// Description:
// 正大整数四则运算
// 使用整型数组表示正大整数。
// big_int[0]表示个位数，big_int[1]表示十位数，...
// 负大整数运算转化成正大整数运算。
//////////////////////////////////////////////////////////////////////

#ifndef BIG_INTEGER_OPERATION_H
#define BIG_INTEGER_OPERATION_H 1

namespace zhaiwei
{
// 大正整数比较
// lhs > rhs, 返回1
// lhs == rhs, 返回0
// lhs < rhs, 返回-1
int big_integer_compare(int *lhs, int lhs_length, int *rhs, int rhs_length);

// 加法，返回表示和的整数数组地址
int *big_integer_add(int *lhs, int lhs_length, int *rhs, int rhs_length, int &new_length);

// 减法，第一个数大于第二个数
int *big_integer_subtract(int *lhs, int lhs_length, int *rhs, int rhs_length, int &new_length);

// 乘法
int *big_integer_multiply(int *lhs, int lhs_length, int *rhs, int rhs_length, int &new_length);

// 正大整数数组调整，使每位数字在[0,9]之间
// digits_array: 整数数组
// digits_array_length: 整数数组长度
// number_digits: 大整数位数
// 数组中大整数之后的每位以置为0
void big_integer_adjust(int *digits_array, int digits_array_length, int &number_digits);

// 输出正大整数
void big_integer_print(int *big_int, int length);
}



#endif // BIG_INTEGER_OPERATION_H
//////////////////////////////////////////////////////////////////////
