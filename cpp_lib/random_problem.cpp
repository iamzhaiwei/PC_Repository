// random_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "random_problem.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
//////////////////////////////////////////////////////////////////////

using namespace std;

namespace zhaiwei
{

// 给你一个数组，设计一个既高效又公平的方法随机打乱这个数组（此题和洗牌算法的思想一致）
void my_random_shuffle(int *array, int length)
{
    if (array == NULL || length <= 1)
        return;

    for (int i = length-1; i >= 1; --i)
        swap(array[rand()%(i+1)], array[i]);
}


// 生成一个位于左闭右开区间[0,1)内的随机数
double random_double()
{
    int i = rand() % 100;
    return i / double(100);
}


// 生成一个位于闭区间[i,j]内的随机数
double random_double(double i, double j)
{
    int a = random_int(i, j);
    return (double)(a-i) / ((int)j-(int)i) * (j-i) + i;
}


// 生成一个位于闭区间[i,j]内的随机数
int random_int(int i, int j)
{
    return rand() % (j-i+1) + i;
}


// 腾讯面试题：给你5个球，每个球被抽到的可能性为30、50、20、40、10，设计一个随机算法，
// 该算法的输出结果为本次执行的结果。输出A，B，C，D，E即可。
void random_select_a_ball(int number_selections)
{
    // prob[i]表示第i球被选中的概率
    int prob[5] = {30, 50, 20, 40, 10};
    for (int i = 1; i < 5; ++i)
        prob[i] += prob[i-1];

    // 每个球被选中的次数
    int number_selected[5];
    for (int i = 0; i < 5; ++i)
        number_selected[i] = 0;
    
    srand(time(NULL));
    int rand_number;
    for (int i = 0; i < number_selections; ++i)
    {
        rand_number = rand() % prob[4];
        for (int j = 0; j < 5; ++j)
        {
            if (rand_number < prob[j])
            {
                ++number_selected[j];
                break;
            }
        }
    }
    for (int i = 0; i < 5; ++i)
        cout << number_selected[i]/(double)number_selections << " ";
    cout << endl;
}

// 从1....n中随机输出m个不重复的数
void random_select_m_from_n(int n, int m)
{
    srand(time(NULL));
    for (int i = 0; i < n; ++i)
    {
        if (rand()%(n-i) < m)
        {
            cout << i+1 << " ";
            --m;
        }
    }
}

}
