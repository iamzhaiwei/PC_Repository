// my_math.cpp
//////////////////////////////////////////////////////////////////////

#include "my_math.h"
#include <cstdlib>
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{

// 返回整数从右边数第i(i>=1)位的数字，个位是第一位，十位是第二位
int get_digit(int data, int i)
{
    return (data / pow(10, i-1)) % 10;
}


//返回从右边数第一个是1的bit位
unsigned int index_of_first_1_bit(int x)
{
    unsigned int idx = 0;
    while ((x & 0x01) == 0 && idx < 32)
    {
        x >>= 1;
        ++idx;
    }
    return idx;
        
}


//判断某一bit位是否是1
bool is_1_bit_at_index(int x, unsigned int idx)
{
    x >>= idx;
    return (x & 0x01) != 0;
}

    
// 把十进制数(long型)分别以二进制和十六进制形式输出，不能使用printf系列
// 十进制转换为二进制，十进制数的每1bit转换为二进制的1位数字
char *int_to_bin(unsigned long data)
{
    unsigned int bit_num = sizeof(unsigned long) * 8;
    char *p_bin = new char[bit_num+1];
    p_bin[bit_num] = '\0';
    for (unsigned int i = 0; i < bit_num; ++i)
    {
        p_bin[i] = data << i >> (bit_num-1);
        if (p_bin[i] == 0)
            p_bin[i] = '0';
        else if (p_bin[i] == 1)
            p_bin[i] = '1';
        else
            p_bin[i] = 'a';
    }
    return p_bin;
}

// 十进制转换为十六进制，十进制数的每4bit转换为十六进制的1位数字
char *int_to_hex(unsigned long data)
{
    unsigned int bit_num = sizeof(unsigned long) * 8;
    char *p_hex = new char[sizeof(unsigned long)*8/4+3];
    p_hex[0] = '0';
    p_hex[1] = 'x';
    p_hex[bit_num/4+2] = '\0';
    char *p_tmp = p_hex + 2;
    for (unsigned int i = 0; i < bit_num/4; ++i)
    {
        p_tmp[i] = data << (4*i) >> (bit_num-4);
        if (p_tmp[i] >= 0 && p_tmp[i] <= 9)
            p_tmp[i] += '0';
        else if (p_tmp[i] >= 10 && p_tmp[i] <= 15)
            p_tmp[i] = p_tmp[i] - 10 + 'A';
    }
    return p_hex;
}



}
