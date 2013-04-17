// order_statistics_problem.h
//
// last-edit-by: <> 
//
// Description:
// 中位数和顺序统计学问题
//////////////////////////////////////////////////////////////////////

#ifndef ORDER_STATISTICS_PROBLEM_H
#define ORDER_STATISTICS_PROBLEM_H 1

namespace zhaiwei
{

// 返回最大值
// 比较n-1次
int my_max(int *array, int n);

// 返回最小值
// 比较n-1次
int my_min(int *array, int n);

// 同时查找最大值和最小值
// 比较(3/2)n次
void my_max_and_min(int *array, int n, int &max, int &min);

// 返回数组array[left...right]中的第i（i>=1）小的元素
// 时间复杂度：最坏情况，O(n^2)，平均情况，O(n)
int random_select(int *array, int left, int right, int i);

// 返回数组array[left...right]中的第i（i>=1）小的元素
// 时间复杂度：最坏情况，O(n)
int select(int *array, int left, int right, int i);

}

#endif // ORDER_STATISTICS_PROBLEM_H
//////////////////////////////////////////////////////////////////////
