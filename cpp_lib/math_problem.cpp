// math_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "math_problem.h"
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

using namespace std;
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{

// 计算卡塔兰数Cn(n>=0)
unsigned int catalan_number(unsigned int n)
{
    if (n == 0)
        return 1;

    unsigned int Cn = 1;
    for (unsigned int i = 1; i <= n; ++i)
    {
        Cn = Cn * (4 * i - 2) / (i + 1);
    }
    return Cn;
}


// 有两个float型的数，一个为fmax,另一个为fmin,还有一个整数n,如果 (fmax - fmin)/n 不能整除，
// 怎么改变fmax,fmin,使改变后可以整除n 。
// 解法：设a为整数，b为浮点数，b'为整数
// fmax - fmin = a * n + b 
// int(fmax - fmin) = a * n + b'
void change_two_floats(float fmax, float fmin, int n, float &new_fmax, float &new_fmin)
{
	int a = int(fmax - fmin) / n;
	float b = fmax - fmin - a * n;
	new_fmax = fmax - b;
	new_fmin = fmin;
}


// 编程实现两个正整数的除法，当然不能用除法操作符。
unsigned int div(unsigned int x, unsigned int y)
{
    unsigned int res = 0;
    for (int i = 31; i >= 0; --i) // 这里千万别把i声明为unsigned，否则就悲剧了，因为unsigned是不会小于0的，死循环
    {
        if ( (x>>i) >= y) // 比较x是否大于y的(1<<i)次方，避免将x与(y<<i)比较，因为不确定y的(1<<i)次方是否溢出
        {
            res += 1 << i;
            x -= y << i;
        }
    }
    return res;
}


// 计算斐波那契数列Fn(n>=0)
unsigned int fibonacci(unsigned int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    unsigned int curr, prev = 1, prev_prev = 0;
    for (unsigned int i = 2; i <= n; ++i)
    {
        curr = prev_prev + prev;
        prev_prev = prev;
        prev = curr;
    }
    return curr;
}


    
// 和为n连续正数序列。
// 题目：输入一个正数n，输出所有和为n连续正数序列。
// 例如输入15，由于1+2+3+4+5=4+5+6=7+8=15，所以输出3个连续序列1-5、4-6和7-8。
int find_continuous_positive_sequence_v1(unsigned int n)
{
    if (n < 3)
        return 0;

    unsigned int first, last, curr_sum;
    first = 1;
    last = 2;
    curr_sum = 3;
    while (true)
    {
        if (curr_sum < n)
        {
            curr_sum += ++last;
        }
        else if (curr_sum > n)
        {
            curr_sum -= first++;
        }
        else
            break;
    }

    unsigned int del_sum = 0;
    unsigned int k;
    int cnt = 0;
    while (first < last)
    {
        if (del_sum % (last-first+1) == 0)
        {
            k = del_sum / (last-first+1);
            first += k;
            last += k;
            del_sum = 0;
            std::cout << first << "-" << last << std::endl;
            cnt += 1;
        }
        del_sum += last--;
    }
    return cnt;
}


// 写一个C的函数，输入整数N，输出整数M，M满足：M是2的n次方，且是不大于N中最大的2的n次方。
// 例如，输入4,5,6,7，都是输出4 。
unsigned int find_power_of_2_not_greater_than_n(unsigned int n)
{
	int i;
	for (i = 31; i >= 0; --i)
	{
		if ((n >> i) & 0x01)
			break;
	}
	return (n >> i) << i;
}


// 求2或n个数的最大公约数
int gcd(int a, int b)
{
    if (a < b)
        std::swap(a, b);
    int tmp;
    while (b > 0)
    {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}
int ngcd(int *array, int length)
{
    int tmp = gcd(array[0], array[1]);
    for (int i = 2; i < length; ++i)
        tmp = gcd(tmp, array[i]);
    return tmp;
}


// 正整数序列Q中的每个元素都至少能被正整数a和b中的一个整除，现给定a和b，需要计算出Q中的前几项，
// 例如，当a=3，b=5，N=6时，序列为3，5，6，9，10，12
// (1)、设计一个函数void generate（int a,int b,int N ,int * Q）计算Q的前几项
// (2)、设计测试数据来验证函数程序在各种输入下的正确性。
void generate_front_several_items(int a, int b, int N, int *Q)
{
    int A = a, B = b;
    for (int i = 0; i < N; ++i)
    {
        if (A < B)
        {
            Q[i] = A;
            A += a;
        }
        else
        {
            Q[i] = B;
            B += b;
        }
    }
}


// 计算一个非负整数有多少位
int get_digit_number(int i)
{
	if (i == 0)
		return 1;

	int digit_number = 0;
	while (i > 0)
	{
		i /= 10;
		++digit_number;
	}
	return digit_number;
}


// 谷歌面试题
// n是正整数，n! 末尾有多少个0？
int how_many_zeros(int n)
{
    int cnt = 0;
    int num = n;
    while (num > 0)
    {
        num /= 5;
        cnt += num;
    }
    return cnt;
}


// 谷歌面试题
// 判断一个自然数是否是某个数的平方
// 若是，返回平方根(>=0)，若不是，返回-1
// 说明：当然不能使用开方运算。
int is_square_number_v1(int n)
{
    int begin = 0, end = n;
    int mid;
    while (begin <= end)
    {
        mid = begin + (end-begin)/2;
        if (mid*mid < n)
            begin = mid + 1;
        else if (mid*mid > n)
            end = mid - 1;
        else
            break;
    }
    if (begin <= end)
        return mid;
    else
        return -1;

}
// 参考：http://hi.baidu.com/mianshiti/blog/item/6b27b2edd1734b252df5348b.html
// 由于
// (n+1)^2
// =n^2 + 2n + 1，
// = ...
// = 1 + (2*1 + 1) + (2*2 + 1) + ... + (2*n + 1)
// 注意到这些项构成了等差数列（每项之间相差2）。
// 所以我们可以比较 N-1， N - 1 - 3， N - 1 - 3 - 5 ... 和0的关系。
// 如果大于0，则继续减；如果等于0，则成功退出；如果小于 0，则失败退出。
// 复杂度为O(n^0.5)。
int is_square_number_v2(int n)
{
    int square_root = 0, minus_number = 1;
    while (n > 0)
    {
        n -= minus_number;
        minus_number += 2;
        square_root += 1;
    }
    if (n == 0)
        return square_root;
    else
        return -1;
}


// 约瑟夫问题
// http://blog.csdn.net/solofancy/article/details/4211770
int josephus_problem(int n, int m)
{
    return 0;
}


// 求2或n个数的最小公倍数
int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}
int nlcm(int *array, int length)
{
    int tmp = lcm(array[0], array[1]);
    for (int i = 2; i < length; ++i)
        tmp = lcm(tmp, array[i]);
    return tmp;
}


// 腾讯
// 如何求根号2的值，并且按照我的需要列出指定小数位，比如根号2是1.141 我要列出1位小数就是1.1
// 2位就是1.14， 1000位就是1.141...... 等。
void sqrt2(int bit_num)
{
    double eps = 1.0 / pow(10, bit_num+1);
    double x1 = 1.0, x2;
    while (true)
    {
        x2 = x1 - (x1*x1-2)/(2*x1);
        if (fabs(x2-x1) <= eps)
            break;
        x1 = x2;
    }
    char fmt[10];
    snprintf(fmt, 10, "%%.%df\n\0", bit_num);
    fprintf(stdout, fmt, x2);
}


}
