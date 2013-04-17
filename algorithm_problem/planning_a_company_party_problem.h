// planning_a_company_party_problem.h
//
// last-edit-by: <> 
//
// Description:
// 计划一个公司聚会 CLRS 15-4
//////////////////////////////////////////////////////////////////////

#ifndef PLANNING_A_COMPANY_PARTY_PROBLEM_H
#define PLANNING_A_COMPANY_PARTY_PROBLEM_H 1

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include "left_child_right_sibling_tree.h"

namespace zhaiwei
{

// 雇员类
class employee
{
public:
    employee(int id, float rank, const std::string &name):
        m_id(id), m_rank(rank), m_name(name)
    {}
    
    int m_id;
    float m_rank;
    std::string m_name;
};
// 对雇员类重载输出操作符
std::ostream &operator<<(std::ostream &ostr, const employee &e)
{
    ostr << "(" << e.m_id << "," << e.m_rank << "," << e.m_name << ")";
    return ostr;
}

static void planning_a_company_party_problem(lcrs_tree_node<employee> *p_node, std::vector<float> &opt_go,
                                      std::vector<float> &opt_no_go)
{
    if (p_node == NULL)
        return;
    
    opt_go[p_node->m_item.m_id] = p_node->m_item.m_rank;
    opt_no_go[p_node->m_item.m_id] = 0;
    lcrs_tree_node<employee> *p_child = p_node->mp_left_child;
    while (p_child != NULL)
    {
        planning_a_company_party_problem(p_child, opt_go, opt_no_go);
        opt_go[p_node->m_item.m_id] += opt_no_go[p_child->m_item.m_id];
        opt_no_go[p_node->m_item.m_id] += std::max(opt_go[p_child->m_item.m_id], opt_no_go[p_child->m_item.m_id]);
        p_child = p_child->mp_right_sibling;
    }
}

static void print_guest_list(lcrs_tree_node<employee> *p_node, const std::vector<float> &opt_go,
                             const std::vector<float> &opt_no_go, std::vector<bool> &whether_go)
{
    // 如果当前结点表示总裁或者其直接上司不参加
    if (p_node->mp_parent == NULL || whether_go[p_node->mp_parent->m_item.m_id] == false) 
    {
        if (opt_go[p_node->m_item.m_id] > opt_no_go[p_node->m_item.m_id])
        {
            whether_go[p_node->m_item.m_id] = true;
            fprintf(stdout, "%s ", p_node->m_item.m_name.c_str());
        }
        else
            whether_go[p_node->m_item.m_id] = false;
            
    }
    else // 当前结点的直接上司参加
    {
        whether_go[p_node->m_item.m_id] = false;
    }

    lcrs_tree_node<employee> *p_child = p_node->mp_left_child;
    while (p_child != NULL)
    {
        print_guest_list(p_child, opt_go, opt_no_go, whether_go);
        p_child = p_child->mp_right_sibling;
    }
}

float planning_a_company_party_problem(left_child_right_sibling_tree<employee> &company_tree)
{
    int n = company_tree.size();

    // opt_go[i]记录雇员Ai参加聚会时以Ai为根的子树的最优解
    // opt_no_go[i]记录雇员Ai不参加聚会时以Ai为根的子树的最优解
    std::vector<float> opt_go(1+n, 0), opt_no_go(1+n, 0);
    
    planning_a_company_party_problem(company_tree.get_root(), opt_go, opt_no_go);

    // 输出Ai参加时最优解
    fprintf(stdout, "Ai参加时最优解:\n");
    for (int i = 1; i <= n; ++i)
        fprintf(stdout, "%.2f ", opt_go[i]);
    fprintf(stdout, "\n\n");
    // 输出Ai不参加时最优解
    fprintf(stdout, "Ai不参加时最优解:\n");
    for (int i = 1; i <= n; ++i)
        fprintf(stdout, "%.2f ", opt_no_go[i]);
    fprintf(stdout, "\n\n");
    
    float opt = std::max(opt_go[1], opt_no_go[1]);

    std::vector<bool> whether_go(1+n, false);
    print_guest_list(company_tree.get_root(), opt_go, opt_no_go, whether_go);
    fprintf(stdout, "\n");
    
    return opt;
}

}


#endif // PLANNING_A_COMPANY_PARTY_PROBLEM_H
//////////////////////////////////////////////////////////////////////
