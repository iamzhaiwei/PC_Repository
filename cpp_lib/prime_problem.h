// prime_problem.h
//
// last-edit-by: <> 
// 
// Description:
// 有关数论
//////////////////////////////////////////////////////////////////////

#ifndef PRIME_PROBLEM_H
#define PRIME_PROBLEM_H 1

#include <cstdlib>
#include <ctime>
#include <vector>

namespace zhaiwei
{

// 整数的素数和分解问题
// 歌德巴赫猜想说任何一个不小于6的偶数都可以分解为两个奇素数之和。
// 对此问题扩展，如果一个整数能够表示成两个或多个素数之和，则得到一个素数和分解式。
// 对于一个给定的整数，输出所有这种素数和分解式。
// 注意，对于同构的分解只输出一次（比如5只有一个分解2 + 3，而3 + 2是2 + 3的同构分解式）。
// 例如，对于整数8，可以作为如下三种分解：
// (1) 8 = 2 + 2 + 2 + 2
// (2) 8 = 2 + 3 + 3
// (3) 8 = 3 + 5
int decompose_int_into_sum_of_primes(int data);


// 分解质因数
// n: 要分解质因数的大整数
// m: 本次递归调用中，依次判断 m, m+1, m+2,..., 是否是n的质因数
// 初次调用时，m=2
void decompose_prime_factors(int n, int m);


// 计算不大于给定整数的所有素数
int find_all_primes_not_greater_than_int(int data, std::vector<int> &primes);


// 概率素性测试算法
int is_prime(int N);


}

#endif // MY_PRIME_H
//////////////////////////////////////////////////////////////////////
