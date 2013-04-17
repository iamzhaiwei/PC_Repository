// moving_on_a_checkerboard.h
//
// last-edit-by: <> 
//
// Description:
// 在棋盘上移动 CLRS 15-6
//////////////////////////////////////////////////////////////////////

#ifndef MOVING_ON_A_CHECKERBOARD_H
#define MOVING_ON_A_CHECKERBOARD_H 1

#include <climits>
#include <cstdio>
#include <boost/multi_array.hpp>

namespace zhaiwei
{
// 输出最优移动路径
static void print_opt_path(const boost::multi_array<int, 2> &path, int i, int j)
{
    if (i > 0)
        print_opt_path(path, i-1, path[i][j]);
    fprintf(stdout, "(%d,%d)", i, j);
}


// n: 棋盘的长度，方格的下标从0到n-1
// p: 从一格移动到另一格获得的钱数, 维度是n*n*3，从方格[i,j]移动到左上方、正上方、右上
// 方获得的钱数分别是p[i][j][0],p[i][j][1],p[i][j][2]
int moving_on_a_checkerboard(int n, const boost::multi_array<int, 3> &p)
{
    // money[i][j]记录棋子移动到方格[i,j]时收集到的最多的钱
    boost::multi_array<int, 2> money(boost::extents[n][n]);
    
    // path[i][j]记录棋子移动到[i,j]的路径
    boost::multi_array<int, 2> path(boost::extents[n][n]);

    int i, j, k, tmp_money;
    for (j = 0; j < n; ++j)
    {
        money[0][j] = 0;
    }
    for (i = 1; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            money[i][j] = INT_MIN;
            for (k = j-1; k <= j+1; ++k)
            {
                if ( k >= 0 && k < n && (tmp_money = money[i-1][k]+p[i-1][k][j+1-k])>money[i][j] )
                {
                    money[i][j] = tmp_money;
                    path[i][j] = k;
                }
            }
        }
    }

    int max_money = money[n-1][0];
    int opt_path = 0;
    for (j = 1; j < n; ++j)
    {
        if (money[n][j] > max_money)
        {
            max_money = money[n][j];
            opt_path = j;
        }
    }
    print_opt_path(path, n-1, opt_path);
    return max_money;
}

}


#endif // MOVING_ON_A_CHECKERBOARD_H
//////////////////////////////////////////////////////////////////////
