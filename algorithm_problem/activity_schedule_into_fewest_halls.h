// activity_schedule_into_fewest_halls.h
//
// last-edit-by: <> 
//
// Description:
// 使用尽可能少的教室来调度所有的活动。CLRS 16.1-3
// 也被称为“区间图着色”
//
// Reference:
// http://blog.sina.com.cn/s/blog_51cea4040100gpw6.html
//////////////////////////////////////////////////////////////////////

#ifndef ACTIVITY_SCHEDULE_INTO_FEWEST_HALLS_H
#define ACTIVITY_SCHEDULE_INTO_FEWEST_HALLS_H 1

#include <algorithm>
#include <cstdio>
#include <list>
#include <iostream>
#include <iterator>
#include <vector>

namespace zhaiwei
{
// 事件类型：活动开始事件/活动结束事件
enum event_type {start_event, finish_event};
// 事件类
class event
{
public:
    event(int time, event_type type, int finish_time):
        m_time(time), m_type(type), m_finish_time(finish_time)
    {}
    
    int m_time; // 事件发生的时间
    event_type m_type; // 事件类型，开始或结束
    int m_finish_time; // 若是开始事件，相应的结束时间; 若是结束事件，-1
};
// 对事件类重载<<操作符
std::ostream &operator<<(std::ostream &ostr, const event &ev)
{
    ostr << "(" << ev.m_time << ",";
    if (ev.m_type == start_event)
        ostr << "start_event,";
    else
        ostr << "finish_event,";
    ostr << ev.m_finish_time << ")";
    return ostr;
}
// 对事件按时间排序的函数对象类
class event_time_less
{
public:
    event_time_less(std::vector<event> &events): m_events(events)
    {}
    bool operator()(int i, int j)
    {
        if (m_events[i].m_time < m_events[j].m_time)
            return true;
        if (m_events[i].m_time == m_events[j].m_time && m_events[i].m_type == finish_event &&
            m_events[j].m_type == start_event)
            return true;
        return false;
    }
private:
    std::vector<event> &m_events;
};
void activity_schedule_into_fewest_halls(int *start_time, int *finish_time, int n)
{
    // 将开始事件和结束事件按照发生时间从小到大排序
    std::vector<event> events;
    events.reserve(2*n);
    std::vector<int> ordered_index;
    ordered_index.reserve(2*n);
    for (int i = 0; i != n; ++i)
    {
        events.push_back(event(start_time[i], start_event, finish_time[i]));
        ordered_index.push_back(i);
    }
    for (int i = 0; i != n; ++i)
    {
        events.push_back(event(finish_time[i], finish_event, -1));
        ordered_index.push_back(i+n);
    }
    event_time_less less_instance(events);
    std::sort(ordered_index.begin(), ordered_index.end(), less_instance);

    // 只求出需要的最少教室数
    int busy_hall_num = 0, free_hall_num = 0;
    for (std::size_t i = 0; i != ordered_index.size(); ++i)
    {
        if (events[ordered_index[i]].m_type == start_event) // 开始事件
        {
            if (free_hall_num == 0)
            {
                ++busy_hall_num;
            }
            else
            {
                --free_hall_num;
                ++busy_hall_num;
            }
        } // 结束事件
        else
        {
            ++free_hall_num;
            --busy_hall_num;
        }
    }
    fprintf(stdout, "%d\n", free_hall_num);
    
    /*
    // 求出需要的最少教室数, 哪几个活动应使用同一间教室
    // 按事件发生的顺序遍历开始事件和结束事件的集合
    std::vector<int> *p_hall; // 存储活动索引
    std::list< std::vector<int> *> busy_hall_list, free_hall_list;
    std::list< std::vector<int> *>::iterator iter;;
    for (std::size_t i = 0; i != ordered_index.size(); ++i)
    {
        if (events[ordered_index[i]].m_type == start_event) // 开始事件
        {
            if (free_hall_list.empty())
            {
                busy_hall_list.push_back(new std::vector<int>(1, ordered_index[i]));
            }
            else
            {
                p_hall = free_hall_list.front();
                free_hall_list.pop_front();
                p_hall->push_back(ordered_index[i]);
                busy_hall_list.push_back(p_hall);
            }
        }
        else // 结束事件
        {
            int idx;
            for (iter = busy_hall_list.begin(); iter != busy_hall_list.end(); ++iter)
            {
                idx = (*iter)->back();
                if (events[idx].m_finish_time == events[ordered_index[i]].m_time)
                    break;
            }
            free_hall_list.push_front(*iter);
            busy_hall_list.erase(iter);
        }
    }

    // 输出结果
    int halls = free_hall_list.size();
    fprintf(stdout, "%d\n", halls);
    for (iter = free_hall_list.begin(); iter != free_hall_list.end(); ++iter)
    {
        for (std::size_t i = 0; i != (*iter)->size(); ++i)
        {
            fprintf(stdout, "%d ", (**iter)[i]+1);
        }
        fprintf(stdout, "\n");
        delete *iter;
    }
    */
}

}


#endif // ACTIVITY_SCHEDULE_INTO_FEWEST_HALLS_H
//////////////////////////////////////////////////////////////////////
