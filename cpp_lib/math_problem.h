// math_problem.h
//
// last-edit-by: <> 
//
// Description:
// 数学问题
//////////////////////////////////////////////////////////////////////

#ifndef MATH_PROBLEM_H
#define MATH_PROBLEM_H 1

namespace zhaiwei
{

// 计算卡塔兰数Cn(n>=0)
unsigned int catalan_number(unsigned int n);


// 有两个float型的数，一个为fmax,另一个为fmin,还有一个整数n,如果 (fmax - fmin)/n 不能整除，
// 怎么改变fmax,fmin,使改变后可以整除n 。
void change_two_floats(float fmax, float fmin, int n, float &new_fmax, float &new_fmin);


// 编程实现两个正整数的除法，当然不能用除法操作符。
unsigned int div(unsigned int x, unsigned int y);


// 计算斐波那契数列Fn(n>=0)
unsigned int fibonacci(unsigned int n);



// 和为n连续正数序列。
// 题目：输入一个正数n，输出所有和为n连续正数序列。
// 例如输入15，由于1+2+3+4+5=4+5+6=7+8=15，所以输出3个连续序列1-5、4-6和7-8。
int find_continuous_positive_sequence_v1(unsigned int n);


// 写一个C的函数，输入整数N，输出整数M，M满足：M是2的n次方，且是不大于N中最大的2的n次方。
// 例如，输入4,5,6,7，都是输出4 。
unsigned int find_power_of_2_not_greater_than_n(unsigned int n);


// 求2或n个数的最大公约数
int gcd(int a, int b);
int ngcd(int *array, int len);


// 谷歌面试题
// 正整数序列Q中的每个元素都至少能被正整数a和b中的一个整除，现给定a和b，需要计算出Q中的前几项，
// 例如，当a=3，b=5，N=6时，序列为3，5，6，9，10，12
// (1)、设计一个函数void generate（int a,int b,int N ,int * Q）计算Q的前几项
// (2)、设计测试数据来验证函数程序在各种输入下的正确性。
void generate_front_several_items(int a, int b, int N, int *Q);


// 计算一个非负整数有多少位
int get_digit_number(int i);


// 谷歌面试题
// n是正整数，n! 末尾有多少个0？
int how_many_zeros(int n);


// 谷歌面试题
// 判断一个自然数是否是某个数的平方
// 说明：当然不能使用开方运算。
int is_square_number_v1(int n);
int is_square_number_v2(int n);

// 约瑟夫问题
// http://blog.csdn.net/solofancy/article/details/4211770
int josephus_problem(int n, int m);


// 求2或n个数的最小公倍数
int lcm(int a, int b);
int nlcm(int *array, int len);

// 腾讯
// 如何求根号2的值，并且按照我的需要列出指定小数位，比如根号2是1.141 我要列出1位小数就是1.1
// 2位就是1.14， 1000位就是1.141...... 等。
void sqrt2(int bit_num);

}


#endif // MATH_PROBLEM_H
//////////////////////////////////////////////////////////////////////
