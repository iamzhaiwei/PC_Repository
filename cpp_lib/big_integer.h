// big_integer.h
//
// last-edit-by: <> 
//
// Description:
// 大数问题
//////////////////////////////////////////////////////////////////////

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H 1

#include <iostream>

namespace zhaiwei
{

class big_integer
{
public:
    friend std::ostream &operator<<(std::ostream &ostr, const big_integer &integer);
    friend big_integer operator+(const big_integer &lhs, const big_integer &rhs);
    friend big_integer operator-(const big_integer &lhs, const big_integer &rhs);
    friend big_integer operator*(const big_integer &lhs, const big_integer &rhs);
    friend big_integer operator/(const big_integer &lhs, const big_integer &rhs);
public:
    big_integer(const char *p_digits = NULL);
    ~big_integer();
    big_integer(const big_integer &other);
    big_integer &operator=(const big_integer &other);
    
    // 设置大整数
    void set_integer(const char *p_digits);
    
    big_integer &operator+=(const big_integer &rhs);
    big_integer &operator-=(const big_integer &rhs);
    big_integer &operator*=(const big_integer &rhs);
    big_integer &operator/=(const big_integer &rhs);
private:
    int m_sign; // 正负号，1表示正数，-1表示负数。大整数0的符号设为1
    int *m_digits; // 数字数组，m_digits[0]表示各位，m_digits[1]表示十位，... ，最后一位是'\0'
    int m_number_digits; // 数字位数

    // 清空
    void clear();
    // 调整数组使每位数字在[0,9]之间
    void adjust_digits_array(int *digits_array, int &number_digits, int digits_array_length);
};

}



#endif // BIG_INTEGER_H
//////////////////////////////////////////////////////////////////////
