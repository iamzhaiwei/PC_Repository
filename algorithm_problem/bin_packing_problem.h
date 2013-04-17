// bin_packing_problem.h
//
// last-edit-by: <> 
//
// Description:
// 近似装箱问题
// 《数据结构与算法分析──C语言描述》第10.1.3节P270
// 
// Parameter:
//
// Return value:
//
//////////////////////////////////////////////////////////////////////

#ifndef BIN_PACKING_PROBLEM_H
#define BIN_PACKING_PROBLEM_H 1

#include <algorithm>
#include <iostream>
#include <vector>

namespace zhaiwei
{

// 箱子类
class box
{
public:
    friend std::ostream &operator<<(std::ostream &ostr, const box &rhs);
    
public:
    box(): m_remain_space(10), m_objects()
    {}

    int remain_space() const
    {
        return m_remain_space;
    }

    void add_object(int No, int space)
    {
        m_objects.push_back(No);
        m_remain_space -= space;
    }
private:
    int m_remain_space; // 箱子剩余的空间
    std::vector<int> m_objects; // 放在箱子中物体的编号
};

std::ostream &operator<<(std::ostream &ostr, const box &rhs)
{
    for (std::size_t i = 0; i != rhs.m_objects.size(); ++i)
    {
        ostr << rhs.m_objects[i] << " ";
    }
    return ostr;
}

// 联机下项适合算法
void online_next_fit_method(int *array, int size, std::vector<box> &boxs)
{
    if (array == NULL || size < 1)
        return;
    
    boxs.push_back(box());
    for (int i = 0; i != size; ++i)
    {
        if (array[i] < boxs.back().remain_space())
        {
            boxs.back().add_object(i, array[i]);
        }
        else
        {
            boxs.push_back(box());
            boxs.back().add_object(i, array[i]);
        }
    }
}

// 联机首次适合算法
void online_first_fit_method(int *array, int size, std::vector<box> &boxs)
{
    if (array == NULL || size <= 0)
        return;

    boxs.push_back(box());
    for (int i = 0; i != size; ++i)
    {
        std::size_t j;
        for (j = 0; j != boxs.size(); ++j)
        {
            if (array[i] <= boxs[j].remain_space())
            {
                boxs[j].add_object(i, array[i]);
                break;
            }
        }
        if (j == boxs.size())
        {
            boxs.push_back(box());
            boxs[j].add_object(i, array[i]);
        }
    }
}

// 函数对象类，用于将箱子按照剩余容量大小排序
class cmp_function_object
{
public:
    cmp_function_object(std::vector<box> &boxs):
        m_boxs(boxs)
    {}

    bool operator()(int i, int j)
    {
        return m_boxs[i].remain_space() < m_boxs[j].remain_space();
    }

private:
    std::vector<box> &m_boxs;
};

// 联机最佳适合算法
void online_best_fit_method(int *obj_array, int size, std::vector<box> &boxs)
{
    if (obj_array == NULL || size <= 0)
        return;

    cmp_function_object cmp(boxs);
    
    std::vector<int> box_indexs; // 将箱子按照剩余容量从小到大排序的索引序列向量
    int begin, end, mid;
    int best_index_index; // 最适合的箱子索引在索引序列向量中的索引
    
    for (int i = 0; i != size; ++i)
    {
        // 二叉查找最适合的箱子──所有箱子中能够容纳当前物体的最满的箱子
        best_index_index = -1;
        begin = 0;
        end = box_indexs.size();
        while (begin < end)
        {
            mid = begin + (end - begin) / 2;
            if (obj_array[i] < boxs[box_indexs[mid]].remain_space()) // 当前箱子适合，往前继续寻找更适合的箱子
            {
                best_index_index = mid;
                end = mid;
            }
            else if (obj_array[i] > boxs[box_indexs[mid]].remain_space()) // 当前箱子不适合，往后寻找适合的箱子
            {
                begin = mid + 1;
            }
            else // 当前箱子最适合，停止寻找
            {
                best_index_index = mid; 
                break;
            }
        }
        // 没找到适合的箱子，添加新箱子
        if (best_index_index == -1)
        {
            boxs.push_back(box());
            box_indexs.push_back(boxs.size()-1);
            best_index_index = box_indexs.size() - 1;
        }
        boxs[box_indexs[best_index_index]].add_object(i, obj_array[i]);

        // 插入排序：将当前箱子排序
        std::sort(box_indexs.begin(), box_indexs.end(), cmp);
    }
}

// 脱机首次适合递减算法，先对输入序列排序
void offline_first_fit_decreasing_method(int *obj_array, int size, std::vector<box> &boxs)
{
    online_first_fit_method(obj_array, size, boxs);
}

// 脱机首次适合递减算法，先对输入序列排序
void offline_best_fit_decreasing_method(int *obj_array, int size, std::vector<box> &boxs)
{
    online_best_fit_method(obj_array, size, boxs);
}

}


#endif // BIN_PACKING_PROBLEM_H
//////////////////////////////////////////////////////////////////////
