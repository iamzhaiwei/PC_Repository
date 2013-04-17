// big_integer.cpp
//////////////////////////////////////////////////////////////////////

#include "big_integer.h"
#include <cstring>
#include "big_integer_operation.h"
//////////////////////////////////////////////////////////////////////

using namespace std;

namespace zhaiwei
{

big_integer::big_integer(const char *p_digits):
    m_sign(0), m_digits(NULL), m_number_digits(0)
{
    set_integer(p_digits);
}

big_integer::~big_integer()
{
    clear();
}

big_integer::big_integer(const big_integer &other):
    m_sign(other.m_sign), m_digits(NULL), m_number_digits(other.m_number_digits)
{
    m_digits = new int[m_number_digits];
    memcpy(m_digits, other.m_digits, m_number_digits*sizeof(int));   
}

big_integer &big_integer::operator=(const big_integer &other)
{
    int *p_new_digits = new int[other.m_number_digits];
    memcpy(p_new_digits, other.m_digits, other.m_number_digits*sizeof(int));
    delete [] m_digits;
    m_digits = p_new_digits;
    m_sign = other.m_sign;
    m_number_digits = other.m_number_digits;
    return *this;
}

void big_integer::set_integer(const char *p_digits)
{
    if (p_digits == NULL)
        return;
    clear();
    if (p_digits[0] == '-')
    {
        m_sign = -1;
        ++p_digits;
    }
    else if (p_digits[0] == '+')
    {
        m_sign = 1;
        ++p_digits;
    }
    else
    {
        m_sign = 1;
    }
    m_number_digits = strlen(p_digits);
    m_digits = new int[m_number_digits];
    for (int i = 0; i < m_number_digits; ++i)
        m_digits[i] = p_digits[m_number_digits-i-1] - '0';
}

big_integer &big_integer::operator+=(const big_integer &rhs)
{
    int new_sign, *p_new_digits, new_number_digits;
    if (m_sign == rhs.m_sign) // 同号
    {
        new_sign = m_sign;
        p_new_digits = big_integer_add(m_digits, m_number_digits, rhs.m_digits, rhs.m_number_digits,
                                       new_number_digits);
    }
    else // 异号，转换成减法，先确定结果的符号，再用大绝对值减去小绝对值
    {
        int result = big_integer_compare(m_digits, m_number_digits, rhs.m_digits, rhs.m_number_digits);
        if (result > 0)
        {
            new_sign = m_sign; 
            p_new_digits = big_integer_subtract(m_digits, m_number_digits, rhs.m_digits, rhs.m_number_digits,
                                                new_number_digits);
        }
        else if (result < 0)
        {
            new_sign = rhs.m_sign;
            p_new_digits = big_integer_subtract(rhs.m_digits, rhs.m_number_digits, m_digits, m_number_digits,
                                                new_number_digits);
        }
        else
        {
            new_sign = 1;
            new_number_digits = 1;
            p_new_digits = new int[1];
            p_new_digits[0] = 0;
        }
    }
    clear();
    m_sign = new_sign;
    m_number_digits = new_number_digits;
    m_digits = p_new_digits;
    return *this;
}

big_integer &big_integer::operator-=(const big_integer &rhs)
{
    int new_sign, *p_new_digits, new_number_digits;
    if (m_sign != rhs.m_sign) // 异号，正减负，或负减正，结果的符号跟第一个数相同
    {
        new_sign = m_sign;
        p_new_digits = big_integer_add(m_digits, m_number_digits, rhs.m_digits, rhs.m_number_digits,
                                       new_number_digits);
    }
    else // 同号
    {
        int result = big_integer_compare(m_digits, m_number_digits, rhs.m_digits, rhs.m_number_digits);
        if (result > 0) // 大正数减小正数，或小负数减大负数，结果的符号跟第一个数相同
        {
            new_sign = m_sign;
            p_new_digits = big_integer_subtract(m_digits, m_number_digits, rhs.m_digits, rhs.m_number_digits,
                                                new_number_digits);
        }
        else if (result < 0) // 小正数减大正数，或大负数减小负数，结果的符号跟第一个数相反
        {
            new_sign = -m_sign;
            p_new_digits = big_integer_subtract(rhs.m_digits, rhs.m_number_digits, m_digits, m_number_digits, 
                                                new_number_digits);
        }
        else
        {
            new_sign = 1;
            new_number_digits = 1;
            p_new_digits = new int[1];
            p_new_digits[0] = 0;
        }
    }
    clear();
    m_sign = new_sign;
    m_number_digits = new_number_digits;
    m_digits = p_new_digits;
    return *this;
}
big_integer &big_integer::operator*=(const big_integer &rhs)
{
    int new_sign, *p_new_digits, new_number_digits;
    if (m_sign != rhs.m_sign) // 异号
    {
        new_sign = -1;
        p_new_digits = big_integer_multiply(m_digits, m_number_digits, rhs.m_digits, rhs.m_number_digits,
                                            new_number_digits);
        // 乘积是0的情况
        if (new_number_digits == 1 && p_new_digits[0] == 0)
            new_sign = 1;
    }
    else // 同号
    {
        new_sign = 1;
        p_new_digits = big_integer_multiply(m_digits, m_number_digits, rhs.m_digits, rhs.m_number_digits,
                                            new_number_digits);
    }
    clear();
    m_sign = new_sign;
    m_number_digits = new_number_digits;
    m_digits = p_new_digits;
    return *this;
}
big_integer &big_integer::operator/=(const big_integer &rhs)
{
    return *this;
}

void big_integer::clear()
{
    if (m_digits != NULL)
    {
        delete [] m_digits;
        m_digits = NULL;
    }
    m_sign = 0;
    m_number_digits = 0;
}

ostream &operator<<(ostream &ostr, const big_integer &integer)
{
    if (integer.m_sign == -1)
        ostr << '-';
    for (int i = integer.m_number_digits-1; i >= 0; --i)
        ostr << integer.m_digits[i];
    return ostr;
}
big_integer operator+(const big_integer &lhs, const big_integer &rhs)
{
    big_integer result(lhs);
    result += rhs;
    return result;
}

big_integer operator-(const big_integer &lhs, const big_integer &rhs)
{
    big_integer result(lhs);
    result -= rhs;
    return result;
}

big_integer operator*(const big_integer &lhs, const big_integer &rhs)
{
    big_integer result(lhs);
    result *= rhs;
    return result;
}

big_integer operator/(const big_integer &lhs, const big_integer &rhs)
{
    big_integer result(lhs);
    result /= rhs;
    return result;
}

}
