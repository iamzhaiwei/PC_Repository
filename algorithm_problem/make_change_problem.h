// make_change_problem.h
//
// last-edit-by: <>
//
// Description:
// 找零钱问题
// 华为面试：1分2分5分的硬币，组成1角，共有多少种组合。
//////////////////////////////////////////////////////////////////////

#ifndef MAKE_CHANGE_PROBLEM_H
#define MAKE_CHANGE_PROBLEM_H 1

#include <vector>
#include <boost/multi_array.hpp>

namespace zhaiwei
{
// 动态规划
// total_money: 要找的零钱总和
// changes: 零钱数组，已经从小到大排序，第1个元素设为0，有效元素从第2个位置即下标1开始
// kinds_change: 零钱种类
int make_change_problem(int total_money, int *changes, int kinds_change)
{
    // opt[i][j]表示用前j种零钱组成i元钱的组合数目，第j种零钱的数目可以为0
    boost::multi_array<int, 2> opt(boost::extents[total_money+1][kinds_change+1]);
	
    int i, j;
	// 组成0元钱的组合数目只有1种，即不选择任何零钱
    i = 0;
    for (j = 0; j <= kinds_change; ++j)
        opt[i][j] = 1;
	// 用0种零钱组成i(1<=i<=total_money)元钱的组合数目是0
    j = 0;
    for (i = 1; i <= total_money; ++i)
        opt[i][j] = 0;
		
    for (i = 1; i <= total_money; ++i)
    {
        for (j = 1; j <= kinds_change; ++j)
        {
            opt[i][j] = 0;
            int K = i / changes[j]; // 第j种零钱的最大数目
            for (int k = 0; k <= K; ++k)
                opt[i][j] += opt[i-k*changes[j]][j-1];
        }
    }
    return opt[total_money][kinds_change];
}

// total_money: 要找的零钱总和
// changes: 零钱数组，已经从小到大排序，第1个元素设为0，有效元素从第2个位置即下标1开始
// kinds_change: 零钱种类
int make_change_problem_v2(int total_money, int *changes, int kinds_change)
{
	// opt[i]表示i元钱的组合数目
	std::vector<int> opt(total_money+1, 0);
	
	// 组成0元钱的组合数目只有1种，即不选择任何零钱
	opt[0] = 1;
	
	// 第一个循环计算包含第i种零钱时j元钱的组合数目，第二个循环计算j(j>=changes[i])元钱的组合数目
	for (int i = 1; i <= kinds_change; ++i)
	{
		for (int j = changes[i]; j <= total_money; ++j)
		{
			opt[j] += opt[j-changes[i]];
		}
	}
	return opt[total_money];
}

}


#endif // MAKE_CHANGE_PROBLEM_H
//////////////////////////////////////////////////////////////////////
