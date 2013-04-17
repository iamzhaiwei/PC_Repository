// job_scheduling_to_max_profit.h
//
// last-edit-by: <> 
//
// Description:
// 达到最高效益的作业调度 CLRS 15-7
//////////////////////////////////////////////////////////////////////

#ifndef JOB_SCHEDULING_TO_MAX_PROFIT_H
#define JOB_SCHEDULING_TO_MAX_PROFIT_H 1

#include <algorithm>

namespace zhaiwei
{

// 将作业按照最后期限从小到大排序用到的函数对象类
class deadline_less
{
public:
    deadline_less(int *p_deadline, int n):
        mp_deadline(p_deadline), m_size(n)
    {}
        
    bool operator()(int i, int j)
    {
        return mp_deadline[i] < mp_deadline[j];
    }

private:
    int *mp_deadline;
    int m_size;
};

// proc_time: 处理时间
// profit: 效益
// deadline: 最后期限
// n: 作业数目，下标从0到n-1
int job_scheduling_to_max_profit(int *proc_time, int *profit, int *deadline, int n)
{
    // 将作业序列按最后期限从小到大排序
    // ordered_job[i]记录排在第i位的作业的索引
    std::vector<int> ordered_job(n, 0);
    for (int i = 0; i != n; ++i)
    {
        ordered_job[i] = i;
    }
    deadline_less less_instance(deadline, n);
    std::sort(ordered_job.begin(), ordered_job.end(), less_instance);

    // opt_profit[i]记录作业Ai是最后一个完成的作业时的最大收益
    // Ai是排序序列中第i个作业
    std::vector<int> opt_profit(n, 0);
    opt_profit[0] = profit[ordered_job[0]];
    for (int i = 1; i != n; ++i)
    {
        opt_profit[i] = 0;
        int tmp_profit;
        for (int j = 0; j < i; ++j)
        {
            if (deadline[ordered_job[j]] < deadline[ordered_job[i]]-proc_time[ordered_job[i]]+1 &&
                (tmp_profit = opt_profit[j]+profit[ordered_job[i]]) > opt_profit[i])
            {
                opt_profit[i] = tmp_profit;
            }
        }
    }

    int max_profit = opt_profit[0];
    for (int i = 1; i < n; ++i)
    {
        if (opt_profit[i] > max_profit)
        {
            max_profit = opt_profit[i];
        }
    }
    return max_profit;
}

}



#endif // JOB_SCHEDULING_TO_MAX_PROFIT_H
//////////////////////////////////////////////////////////////////////
