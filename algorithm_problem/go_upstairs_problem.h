// go_upstairs_problem.h
//
// last-edit-by: <>
//
// Description:
// 上楼梯问题
// 上20阶楼梯，可以一次迈1，2，4步，请问有多少种上法？
//////////////////////////////////////////////////////////////////////
#ifndef GO_UPSTAIRS_PROBLEM_H
#define GO_UPSTAIRS_PROBLEM_H 1

#include <vector>

namespace zhaiwei
{
// number_stairs: 楼梯的台阶总数
// step: 一步可以走的台阶数，是个数组
// kinds_step: 数组长度
int go_upstairs_problem(int number_stairs, int *step, int kinds_step)
{
	// opt[i]表示走到第i阶台阶的走法数目
	std::vector<int> opt(number_stairs+1, 0);
	
	// 走到第0阶台阶的走法数目是1，即一步也不走
	opt[0] = 1;
	
	// 动态规划
	for (int i = 1; i <= number_stairs; ++i)
	{
		for (int j = 0; j < kinds_step; ++j)
		{
			if (i < step[j])
				break;
			opt[i] += opt[i-step[j]];
		}
	}
	return opt[number_stairs];
}

}

#endif // GO_UPSTAIRS_PROBLEM_H
//////////////////////////////////////////////////////////////////////
