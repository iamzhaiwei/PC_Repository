// an_activity_selection_problem.h
//
// last-edit-by: <> 
//
// Description:
// 活动选择问题 CLRS 16.1
//////////////////////////////////////////////////////////////////////

#ifndef AN_ACTIVITY_SELECTION_PROBLEM_H
#define AN_ACTIVITY_SELECTION_PROBLEM_H 1

#include <cstdio>
#include <boost/multi_array.hpp>

namespace zhaiwei
{

// 动态规划方法
// 输出最大活动子集
void print_optimal_activity(const boost::multi_array<int, 2> &opt, const boost::multi_array<int, 2> &act, int i, int j)
{
    if (i >= j || opt[i][j] == 0)
        return;
    print_optimal_activity(opt, act, i, act[i][j]);
    fprintf(stdout, "%d ", act[i][j]);
    print_optimal_activity(opt, act, act[i][j], j);
}
// 活动序列已按照结束时间从小到大排序
// start_time: 各个活动ai的开始时间
// finish_time: 各个活动ai的结束时间
// a(0)与a(n-1)是虚构活动，f[0]=0, s[n-1]=无穷大
int an_activity_selection_problem_dp(int *start_time, int *finish_time, int n)
{
    // opt[i][j]记录于活动ai、aj兼容的活动的个数(i<=j)
    boost::multi_array<int, 2> opt(boost::extents[n][n]);
    boost::multi_array<int, 2> act(boost::extents[n][n]);
    for (int i = 0; i != n; ++i)
    {
        opt[i][i] = 0;
    }
    for (int i = 0; i != n; ++i)
    {
        for (int j = i+1; j != n; ++j)
        {
            opt[i][j] = 0;
            int tmp;
            for (int k = i+1; k != j; ++k)
            {
                if (finish_time[i] <= start_time[k] && finish_time[k] <= start_time[j] &&
                    (tmp = opt[i][k]+opt[k][j]+1) > opt[i][j])
                {
                    opt[i][j] = tmp;
                    act[i][j] = k;
                }
            }
        }
    }
    fprintf(stdout, "最大兼容子集中的活动数：\n");
    for (int i = 0; i != n; ++i)
    {
        for (int j = 0; j != n; ++j)
            fprintf(stdout, "%d ", opt[i][j]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "最大兼容子集中的活动：\n");
    for (int i = 0; i != n; ++i)
    {
        for (int j = 0; j != n; ++j)
            fprintf(stdout, "%d ", act[i][j]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "最大兼容子集：\n");
    print_optimal_activity(opt, act, 0, n-1);
    fprintf(stdout, "\n");
    return opt[0][n-1];
}

// 贪心算法
// 活动序列已按照结束时间从小到大排序
// start_time: 各个活动ai的开始时间
// finish_time: 各个活动ai的结束时间
// 没有虚拟活动
// 递归版本
static void an_activity_selection_problem_greedy_recursion(int *start_time, int *finish_time, int i, int j,
                                                   std::vector<int> &act)
{
    int k = i + 1;
    while (k <= j && start_time[k] < finish_time[i])
        ++k;
    if (k <= j)
    {
        act.push_back(k);
        an_activity_selection_problem_greedy_recursion(start_time, finish_time, k, j, act);
    }
}
int an_activity_selection_problem_greedy_recursion(int *start_time, int *finish_time, int n)
{
    std::vector<int> act;
    act.push_back(0);
    an_activity_selection_problem_greedy_recursion(start_time, finish_time, 0, n-1, act);
    fprintf(stdout, "最大兼容子集：\n");
    for (std::size_t i = 0; i != act.size(); ++i)
        fprintf(stdout, "%d ", act[i]);
    fprintf(stdout, "\n");
    return act.size();
}
// 迭代版本
int an_activity_selection_problem_greedy_iteration(int *start_time, int *finish_time, int n)
{
    std::vector<int> act;
    int i = 0;
    act.push_back(i);
    for (int k = i+1; k < n; ++k)
    {
        if (start_time[k] >= finish_time[i])
        {
            act.push_back(k);
            i = k;
        }
    }
    fprintf(stdout, "最大兼容子集：\n");
    for (std::size_t i = 0; i != act.size(); ++i)
        fprintf(stdout, "%d ", act[i]);
    fprintf(stdout, "\n");
    return act.size();
}

}


#endif // AN_ACTIVITY_SELECTION_PROBLEM_H
//////////////////////////////////////////////////////////////////////
