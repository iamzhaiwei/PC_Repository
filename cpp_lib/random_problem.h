// random_problem.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef RANDOM_PROBLEM_H
#define RANDOM_PROBLEM_H 1


namespace zhaiwei
{

// 给你一个数组，设计一个既高效又公平的方法随机打乱这个数组（此题和洗牌算法的思想一致）
void my_random_shuffle(int *array, int length);


// 生成一个位于左闭右开区间[0,1)内的随机数
double random_double();


// 生成一个位于闭区间[i,j]内的随机数
double random_double(double i, double j);


// 生成一个位于闭区间[i,j]内的随机数
int random_int(int i, int j);


// 腾讯面试题：给你5个球，每个球被抽到的可能性为30、50、20、40、10，设计一个随机算法，
// 该算法的输出结果为本次执行的结果。输出A，B，C，D，E即可。
void random_select_a_ball(int number_selections);

// 从1....n中随机输出m个不重复的数
void random_select_m_from_n(int n, int m);

}


#endif // RANDOM_PROBLEM_H
//////////////////////////////////////////////////////////////////////
