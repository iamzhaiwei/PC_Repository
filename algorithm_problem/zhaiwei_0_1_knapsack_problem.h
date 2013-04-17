// zhaiwei_0_1_knapsack_problem.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef ZHAIWEI_0_1_KNAPSACK_PROBLEM_H
#define ZHAIWEI_0_1_KNAPSACK_PROBLEM_H 1

#include <cstdio>
#include <boost/multi_array.hpp>

namespace zhaiwei
{
// 输出选择的物品
void print_selected_items(const boost::multi_array<int, 2> &opt, int *weight, int i, int w)
{
    if (i == 0 || weight == 0)
        return;
    if (opt[i][w] == opt[i-1][w]) // 没有包含物品i
    {
        print_selected_items(opt, weight, i-1, w);
    }
    else //包含物品i
    {
        print_selected_items(opt, weight, i-1, w-weight[i]);
        fprintf(stdout, "%d ", i);
    }
}
// 下标从1开始
// value: 物品的价值
// weight: 物品的重量
// n: 物品的数目
// W: 背包的最大负重
// 在数组value和weight前添加一个虚拟物品，value[0]=0, weight[0]=0
// 但n还是实际物品的数目
void zhaiwei_0_1_knapsack_problem(int *value, int *weight, int n, int W)
{
    // opt[i][w]记录从前i件物品中拿最多w磅重的物品的最大价值
    boost::multi_array<int, 2> opt(boost::extents[n+1][W+1]);

    int i, w;
    for (w = 0; w <= W; ++w)
    {
        opt[0][w] = 0;
    }
    for (i = 0; i <= n; ++i)
    {
        opt[i][0] = 0;
    }
    for (i = 1; i <= n; ++i)
    {
        for (w = 1; w <= W; ++w)
        {
            if (weight[i] > w)
            {
                opt[i][w] = opt[i-1][w];
            }
            else
            {
                // 包括物品i
                opt[i][w] = value[i] + opt[i-1][w-weight[i]];
                // 不包括物品i
                if (opt[i-1][w] > opt[i][w])
                    opt[i][w] = opt[i-1][w];
            }

        }
    }

    fprintf(stdout, "最优子结构:\n");
    for (i = 0; i <= n; ++i)
    {
        for (w = 0; w <= W; ++w)
            fprintf(stdout, "%d ", opt[i][w]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "%d\n", opt[n][W]);
    print_selected_items(opt, weight, n, W);
    fprintf(stdout, "\n");
}

}


#endif // ZHAIWEI_0_1_KNAPSACK_PROBLEM_H
//////////////////////////////////////////////////////////////////////
