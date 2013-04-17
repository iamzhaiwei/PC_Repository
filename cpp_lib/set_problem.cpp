// set_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "set_problem.h"
#include <iostream>
#include <iterator>
#include <list>
#include <utility>
#include <vector>
#include <boost/unordered_map.hpp>
//////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;

namespace zhaiwei
{
// 给定一个字符串的集合，格式如：{aaa bbb ccc}， {bbb ddd}，{eee fff}，{ggg}，
// {ddd hhh}要求将其中交集不为空的集合合并，要求合并完成后的集合之间无交集，
// 例如上例应输出{aaa bbb ccc ddd hhh}，{eee fff}， {ggg}。
// 使用并查集
// 查找集合i的父亲集合
static int find_parent(vector<int> &vec, int i)
{
    if (vec[i] == -1)
        return i;
    else
        return vec[i] = find_parent(vec, vec[i]);
}
void set_union(const vector< set<string> > &in_sets, vector< set<string> > &out_sets)
{
    // 键是集合中的字符串，值是字符串所在集合的索引链表
    unordered_map<string, list<int> > map;
    set<string>::iterator set_iter;
    unordered_map<string, list<int> >::iterator map_iter;
    list<int>::iterator list_iter, list_begin_iter;
    for (size_t i = 0; i < in_sets.size(); ++i)
    {
        for (set_iter = in_sets[i].begin(); set_iter != in_sets[i].end(); ++set_iter)
        {
            if ( (map_iter = map.find(*set_iter)) != map.end())
                map_iter->second.push_back(i);
            else
                map.insert(make_pair(*set_iter, list<int>(1, i)));
        }
    }
    // 并查集，集合i的父亲集合是vec[i]。若vec[i]=-1，i的父亲集合是其自身
    vector<int> vec(in_sets.size(), -1);
    for (map_iter = map.begin(); map_iter != map.end(); ++map_iter)
    {
        list_begin_iter = map_iter->second.begin();
        for (list_iter = list_begin_iter, ++list_iter; list_iter != map_iter->second.end(); ++list_iter)
            vec[*list_iter] = find_parent(vec, *list_begin_iter);
    }
    for (size_t i = 0; i != vec.size(); ++i)
    {
        if (vec[i] != -1)
            vec[i] = find_parent(vec, i);
    }
    // 合并集合
    out_sets.clear();
    out_sets.resize(in_sets.size());
    for (size_t i = 0; i != vec.size(); ++i)
    {
        if (vec[i] == -1)
            out_sets[i].insert(in_sets[i].begin(), in_sets[i].end());
        else
            out_sets[vec[i]].insert(in_sets[i].begin(), in_sets[i].end());
    }
    vector< set<string> >::iterator vec_iter;
    vec_iter = out_sets.begin();
    while (vec_iter != out_sets.end())
    {
        if (vec_iter->empty())
            out_sets.erase(vec_iter);
        else
            ++vec_iter;
    }
    for (vec_iter = out_sets.begin(); vec_iter != out_sets.end(); ++vec_iter)
    {
        for (set_iter = vec_iter->begin(); set_iter != vec_iter->end(); ++set_iter)
            cout << *set_iter << " ";
        cout << endl;
    }
}

}
