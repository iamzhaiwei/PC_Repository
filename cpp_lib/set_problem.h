// set_problem.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef SET_PROBLEM_H
#define SET_PROBLEM_H 1

#include <set>
#include <string>
#include <vector>

namespace zhaiwei
{

// 给定一个字符串的集合，格式如：{aaa bbb ccc}， {bbb ddd}，{eee fff}，{ggg}，
// {ddd hhh}要求将其中交集不为空的集合合并，要求合并完成后的集合之间无交集，
// 例如上例应输出{aaa bbb ccc ddd hhh}，{eee fff}， {ggg}。
// 使用并查集
void set_union(const std::vector< std::set<std::string> > &in_sets,
               std::vector< std::set<std::string> > &out_sets);
}


#endif // SET_PROBLEM_H
//////////////////////////////////////////////////////////////////////
