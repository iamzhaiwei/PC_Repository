// btree_problem.h
//
// last-edit-by: <> 
//
// Description:
// 二叉树问题
//////////////////////////////////////////////////////////////////////
#ifndef BTREE_PROBLEM_H
#define BTREE_PROBLEM_H 1

#include "btree.h"
#include <iostream>

namespace zhaiwei
{
	
// 二叉树结点，含有指向右邻居的指针
template <typename T>
class btree_node_v2
{
public:
    explicit btree_node_v2(const T &item = T(), btree_node_v2<T> *left = NULL, btree_node_v2<T> *right = NULL,
                           btree_node_v2<T> *right_neighbour = NULL):
        m_item(item), mp_left(left), mp_right(right), mp_right_neighbour(right_neighbour)
    {}
public:
    T m_item;
    btree_node_v2<T> *mp_left; // 左儿子
    btree_node_v2<T> *mp_right; // 右儿子
    btree_node_v2<T> *mp_right_neighbour; // 右邻居
};
// 先序遍历
template <typename T>
void preorder_traversal(btree_node_v2<T> *p_node)
{
    if (p_node == NULL)
        return;
    std::cout << p_node->m_item;
    if (p_node->mp_right_neighbour != NULL)
    {
        std::cout << "(" << p_node->mp_right_neighbour->m_item << ")";
    }
    std::cout << " ";
    preorder_traversal(p_node->mp_left);
    preorder_traversal(p_node->mp_right);
}
// 淘宝笔试题：对于一颗完全二叉树，要求给所有节点加上一个pNext指针，指向同一层的相邻节点；
//如果当前节点已经是该层的最后一个节点，则将pNext指针指向NULL；给出程序实现，并分析时间复杂度和空间复杂度。
void add_pointer_to_right_neighbour_node(btree_node_v2<int> *p_node);


//二元树的深度。
//调用之前，设置parent_depth=-1
int btree_depth(btree_node<int> *p_node, int parent_depth);


//二元树的高度。
int btree_height(btree_node<int> *p_node);


// 判断二叉树是否平衡二叉树
// 平衡二叉树的定义：每个结点的左右子树的高度差小于等于1.
bool btree_is_balance(btree_node<int> *p_node);


// 已知二叉树的前序遍历为：- + a * b - c d / e f 
// 后序遍历为：a b c d - * + e f / -
// 求其中序遍历
btree_node<char> *btree_rebuild_from_preorder_and_postorder_traversal(char *p_preorder, char *p_postorder, int length);


//输入二叉树中的两个结点，输出这两个结点在树中最低的共同父结点。
btree_node<int> *find_lowest_common_parent(btree_node<int> *p_node, btree_node<int> *p_node1, btree_node<int> *p_node2);


//在二元树中找出和为某一值的所有路径
//题目：输入一个整数和一棵二元树。从树的根结点开始往下访问一直到叶结点所经过的所有结点形成一条路径。
//打印出和与输入整数相等的所有路径。
void find_paths(btree_node<int> *p_node, const int expected_path_len);
//扩展题：如果将条件放宽，计算和的路径改为从根节点到叶子节点路径上任意连续子路径呢？
void find_paths_extend(btree_node<int> *p_node, const int expected_path_len);


//求二叉树中任意两个节点之间的最大距离
//如果我们把二叉树看成一个图，父子节点之间的连线看成是双向的，我们姑且定义"距离"为两节点之间边的个数。
//写一个程序，求一棵二叉树中相距最远的两个节点之间的距离。
int max_distance_of_two_nodes(btree_node<int> *p_node);


// 淘宝笔试题
// 有一棵树（树上结点为字符串或者整数），请写代码将树的结构和数据写到一个文件中，
// 并能通过读取该文件恢复树结构 。
btree_node<int> *read_btree_from_file(const char *p_file_name);
void write_btree_to_file(btree_node<int> *tree, const char *p_file_name);


	
}

#endif // BTREE_PROBLEM_H
