// bstree_problem.h
//
// last-edit-by: <> 
//
// Description:
// 二叉查找树问题
//////////////////////////////////////////////////////////////////////

#ifndef BSTREE_PROBLEM_H
#define BSTREE_PROBLEM_H 1

#include "bstree.h"

namespace zhaiwei
{

// 微软面试题
// 一棵排序二叉树，令 f=(最大值+最小值)/2，
// 设计一个算法，找出距离f值最近、大于f值的结点。
// 复杂度如果是O(n2)则不得分。
btree_node<int> *bstree_find_closest_greater_than_median_node(btree_node<int> *tree);


//二叉查找树转换为排序的双向列表，不新建结点，只改变指针指向
void bstree_to_dlist(btree_node<int> *p_node, btree_node<int> *&head, btree_node<int> *&tail);
void print_bstree_to_dlist(std::ostream &ostr, btree_node<int> *p_node, int flag);


//题目：输入一颗二元查找树，将该树转换为它的镜像.
//即在转换后的二元查找树中，左子树的结点都大于右子树的结点。
//用递归和循环两种方法完成树的镜像转换。
btree_node<int> *bstree_to_mirror_recursion(btree_node<int> *p_node);
void bstree_to_mirror_circular(btree_node<int> *p_node);


//编写一个程序，把一个有序整数数组放到二叉查找树中
btree_node<int> *build_bstree_from_ordered_array(int *array, int begin, int end);


// 构建一棵最优二叉查找树
// Parameter: 
// key_freq: 关键字的搜索频率数组，下标从1开始到n
// virtual_key_freq: 虚拟键的搜索频率数组，下标从0开始到n
// key_size: 关键字搜索频率的有效数目n
// Return Value:
// 最优二叉查找树的期望搜索代价，并打印出二叉树的结构
double build_optimal_bstree(double *key_freq, double *virtual_key_freq, int key_size);


//题目：输入一个整数数组，判断该数组是不是某二元查找树的后序遍历的结果。
//如果是返回true，否则返回false。
bool rebuild_bstree_by_postorder_traversal_sequence(int *array, int begin, int end, bstree<int> &t);

}




#endif // BTREE_PROBLEM_H
