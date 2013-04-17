// my_math.h
//
// last-edit-by: <丁宅伟 2012-05-05> 
//
// Description:
// 通用的数学函数
//////////////////////////////////////////////////////////////////////

#ifndef MY_MATH_H
#define MY_MATH_H 1

#include <cstdlib>

namespace zhaiwei
{

// 返回整数从右边数第i(i>=1)位的数字，个位是第一位，十位是第二位
int get_digit(int data, int i);


//返回从右边数第一个是1的bit位
unsigned int index_of_first_1_bit(int x);


//判断某一bit位是否是1
bool is_1_bit_at_index(int x, unsigned int idx);


// 把十进制数(long型)分别以二进制和十六进制形式输出，不能使用printf系列
// 十进制转换为二进制，十进制数的每1bit转换为二进制的1位数字
char *int_to_bin(unsigned long data);


// 十进制转换为十六进制，十进制数的每4bit转换为十六进制的1位数字
char *int_to_hex(unsigned long data);


//是否为偶数
inline bool is_even(int x)
{
    return !(x & 0x01);
}

//是否为奇数
inline bool is_odd(int x)
{
    return x & 0x01;
}

// 幂
template <typename T>
T pow(T base, unsigned int exp)
{
    if (exp == 0)
        return 1;
    
    if (exp == 1)
        return base;
    
    if (is_even(exp))
        return pow(base*base, exp>>1);
    else
        return pow(base*base, exp>>1) * base;
}

}


#endif // MY_MATH_H
//////////////////////////////////////////////////////////////////////
