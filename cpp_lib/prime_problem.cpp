// prime_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "prime_problem.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include "my_algorithm.h"

using namespace std;
//////////////////////////////////////////////////////////////////////

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
// 参数：
// data: 要分解成素数和的整数
// found_primes: 已分解得到的素数和因子
// found_cnt: 素数和分解式的数目
// all_primes: 不大于data的所有素数
static void find_one_prime_sum_decomposition(int data, vector<int> &found_primes,
                                             int &found_cnt, const vector<int> &all_primes)
{
    if (data < 0)
        return;
    if (data == 0)
    {
        copy(found_primes.begin(), found_primes.end(), ostream_iterator<int>(cout, " "));
        ++found_cnt;
        return;
    }
    for (std::size_t i = 0; i != all_primes.size(); ++i)
    {
        if (data < all_primes[i] ||
            (data == all_primes[i] && found_primes.empty())) // 排除素数分解成它自身
            break;
        else
        {
            if (!found_primes.empty() && all_primes[i] < found_primes.back()) // 只选择递增的素数因子，排除同构
                continue;
            found_primes.push_back(all_primes[i]);
            find_one_prime_sum_decomposition(data-all_primes[i], found_primes, found_cnt, all_primes);
            found_primes.pop_back();
        }
    }
}
int decompose_int_into_sum_of_primes(int data)
{
    vector<int> primes; // 存储不大于data的所有素数
    find_all_primes_not_greater_than_int(data, primes);

    vector<int> found_primes; // 存储data的一个素数和分解式
    int found_cnt = 0;
    find_one_prime_sum_decomposition(data, found_primes, found_cnt, primes);
    return found_cnt;
}


// 分解质因数
// n: 要分解质因数的大整数
// m: 本次递归调用中，依次判断 m, m+1, m+2,..., 是否是n的质因数
// 初次调用时，m=2
void decompose_prime_factors(int n, int m)
{
    if (n > m)
    {
        while (n % m) // 若 n%m > 0，说明m不是n的因数
            ++m;
        n /= m;
        cout << m << " ";
        decompose_prime_factors(n, m);
    }
}


// 计算不大于给定整数的所有素数
int find_all_primes_not_greater_than_int(int data, std::vector<int> &primes)
{
    list<int> tmp_coll;
    for (int i = 2; i <= data; ++i)
    {
        tmp_coll.push_back(i);
    }
    list<int>::iterator curr, next;
    curr = tmp_coll.begin();
    while (curr != --tmp_coll.end())
    {
        next = curr;
        ++next;
        while (next != tmp_coll.end())
        {
            if (*next % *curr == 0)
                tmp_coll.erase(next++);
            else
                ++next;
        }
        ++curr;
    }
    primes.clear();
    primes.reserve(tmp_coll.size());
    for (curr = tmp_coll.begin(); curr != tmp_coll.end(); ++curr)
    {
        primes.push_back(*curr);
    }
    return primes.size();
}


// 概率素性测试算法
static int witness(int a, int i, int n)
{
    if (i == 0)
        return 1;

    int X, Y;
    X = witness(a, i/2, n);
    if (X == 0)
        return 0;
    Y = (X * X) % n;
    if (Y == 1 && X != 1 && X != n-1)
        return 0;
    if (i % 2 != 0)
        Y = (a * Y) % n;
    return Y;
}
int is_prime(int N)
{
    srand((unsigned int)time(NULL));
    int rand_num = rand() % (N-3) + 2;
    return witness(rand_num, N-1, N);
}

}
