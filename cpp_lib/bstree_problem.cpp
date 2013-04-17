// bstree_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "bstree_problem.h"
#include <cstdio>
#include <boost/multi_array.hpp>
//////////////////////////////////////////////////////////////////////


namespace zhaiwei
{

// 微软面试题
// 一棵排序二叉树，令 f=(最大值+最小值)/2，
// 设计一个算法，找出距离f值最近、大于f值的结点。
// 复杂度如果是O(n2)则不得分。
// 分析：
// 若f在树中且其右子树不为空，则要找的结点是f的右子树的最小值结点
// 若f在树中但其右子树为空，或是f不在树中，则要找的结点是最后一个转向左子树的结点
btree_node<int> *bstree_find_closest_greater_than_median_node(btree_node<int> *p_tree)
{
    if (p_tree == NULL)
        return NULL;

    btree_node<int> *p_max = bstree_max(p_tree, (btree_node<int>*)NULL);
    btree_node<int> *p_min = bstree_min(p_tree, (btree_node<int>*)NULL);
    int f = (p_max->m_item + p_min->m_item) / 2;

    btree_node<int> *p_curr_node = p_tree, *p_last_lefted_node = p_tree;
    while (p_curr_node != NULL)
    {
        if (f < p_curr_node->m_item)
        {
            p_last_lefted_node = p_curr_node;
            p_curr_node = p_curr_node->mp_left;
        }
        else if (p_curr_node->m_item < f)
        {
            p_curr_node = p_curr_node->mp_right;
        }
        else
            break;
    }
    if (p_curr_node != NULL && p_curr_node->mp_right != NULL)
        return bstree_min(p_curr_node->mp_right, (btree_node<int>*)NULL);
    else 
        return p_last_lefted_node;
}


//二叉查找树转换为排序的双向列表，不新建结点，只改变指针指向
void bstree_to_dlist(btree_node<int> *p_node, btree_node<int> *&head, btree_node<int> *&tail)
{
	if (p_node == NULL)
	{
		head = tail = NULL;
		return;
	}
	
	btree_node<int> *prev = NULL, *next = NULL;
	bstree_to_dlist(p_node->mp_left, head, prev);
	bstree_to_dlist(p_node->mp_right, next, tail);

	if (head == NULL && prev == NULL)
	{
		head = p_node;
	}
	else
	{
		p_node->mp_left = prev;
		prev->mp_right = p_node;
	}

	if (next == NULL && tail == NULL)
	{
		tail = p_node;
	}
	else
	{
		p_node->mp_right = next;
		next->mp_left = p_node;
	}

	head->mp_left = NULL;
	tail->mp_right = NULL;
}
void print_bstree_to_dlist(std::ostream &ostr, btree_node<int> *p_node, int flag)
{
	btree_node<int> *curr = p_node;
	if (flag == 0)
	{
		while (curr != NULL)
		{
			ostr << curr->m_item << " ";
			curr = curr->mp_right;
		}
	}
	else if (flag == 1)
	{
		while (curr != NULL)
		{
			ostr << curr->m_item << " ";
			curr = curr->mp_left;
		}
	}
	ostr << std::endl;
}


//题目：输入一颗二元查找树，将该树转换为它的镜像.
//即在转换后的二元查找树中，左子树的结点都大于右子树的结点。
//用递归和循环两种方法完成树的镜像转换。
btree_node<int> *bstree_to_mirror_recursion(btree_node<int> *p_node)
{
	if (p_node == NULL)
		return NULL;

	btree_node<int> *pnewleft = bstree_to_mirror_recursion(p_node->mp_right);
	btree_node<int> *pnewright = bstree_to_mirror_recursion(p_node->mp_left);

	p_node->mp_left = pnewleft;
	p_node->mp_right = pnewright;
	return p_node;
}
void bstree_to_mirror_circular(btree_node<int> *p_node)
{
	if (p_node == NULL)
		return;

	std::queue< btree_node<int> *> q;
	q.push(p_node);

	btree_node<int> *pcurr, *pnewleft, *pnewright;
	while (!q.empty())
	{
		pcurr = q.front();
		q.pop();

		if (pcurr->mp_left != NULL)
			q.push(pcurr->mp_left);
		if (pcurr->mp_right != NULL)
			q.push(pcurr->mp_right);

		pnewleft = pcurr->mp_right;
		pnewright = pcurr->mp_left;
		pcurr->mp_left = pnewleft;
		pcurr->mp_right = pnewright;
	}
}


//编写一个程序，把一个有序整数数组放到二叉查找树中
btree_node<int> *build_bstree_from_ordered_array(int *array, int begin, int end)
{
	if (begin >= end)
		return NULL;

	int mid = (begin + end) / 2;
	btree_node<int> *p_node = new btree_node<int>(NULL, NULL, NULL, array[mid]);
	p_node->mp_left = build_bstree_from_ordered_array(array, begin, mid);
	p_node->mp_right = build_bstree_from_ordered_array(array, mid+1, end);
	if (p_node->mp_left != NULL)
		p_node->mp_left->mp_parent = p_node;
	if (p_node->mp_right != NULL)
		p_node->mp_right->mp_parent = p_node;

	return p_node;
}
	

// 最优二叉查找树
// 打印最优二叉查找树
static void print_optimal_bstree(const boost::multi_array<int, 2> &root, const int key_size, int i, int j)
{
    if (i == 1 && j == key_size)
    {
        fprintf(stdout, "k%d is the root\n", root[i][j]);
    }
    if (i <= j)
    {
        int r = root[i][j];
        if (i == r)
        {
            fprintf(stdout, "d%d is the left child of k%d\n", r-1, r);
        }
        else
        {
            fprintf(stdout, "k%d is the left child of k%d\n", root[i][r-1], r);
            print_optimal_bstree(root, key_size, i, r-1);
        }
        
        if (r == j)
        {
            fprintf(stdout, "d%d is the right child of k%d\n", r, r);
        }
        else
        {
            fprintf(stdout, "k%d is the right child of k%d\n", root[r+1][j], r);
            print_optimal_bstree(root, key_size, r+1, j);
        }
    }
}
// 构建一棵最优二叉查找树
// Parameter: 
// key_freq: 关键字的搜索频率数组，下标从1开始到n
// virtual_key_freq: 虚拟键的搜索频率数组，下标从0开始到n
// key_size: 关键字搜索频率的有效数目n
// Return Value:
// 最优二叉查找树的期望搜索代价，并打印出二叉树的结构
double build_optimal_bstree(double *key_freq, double *virtual_key_freq, int key_size)
{
    // expectation[i][j]记录最优子树pi...pj的期望搜索代价
    // cost[i][j]记录最优子树pi...pj的所有概率总和
    boost::multi_array<double, 2> expectation(boost::extents[key_size+2][key_size+1]),
        prob_sum(boost::extents[key_size+2][key_size+1]);

    // root[i][j]记录最优子树pi...pj的根
    boost::multi_array<int, 2> root(boost::extents[key_size+1][key_size+1]);
    
    // 只含有虚拟键的子树
    for (int i = 1; i <= key_size+1; ++i)
    {
        expectation[i][i-1] = virtual_key_freq[i-1];
        prob_sum[i][i-1] = virtual_key_freq[i-1];
    }
    for (int l = 1; l <= key_size; ++l)
    {
        for (int i = 1; i <= key_size-l+1; ++i)
        {
            int j = i + l - 1;
            prob_sum[i][j] = prob_sum[i][j-1] + key_freq[j] + virtual_key_freq[j];
            int r = i;
            double tmp_expect = expectation[i][r-1] + expectation[r+1][j] + prob_sum[i][j];
            expectation[i][j] = tmp_expect;
            root[i][j] = r;
            for (r = i+1; r <= j; ++r)
            {
                tmp_expect = expectation[i][r-1] + expectation[r+1][j] + prob_sum[i][j];
                if (tmp_expect < expectation[i][j])
                {
                    expectation[i][j] = tmp_expect;
                    root[i][j] = r;
                }
            }
        }
    }

    // 输出期望搜索代价
    fprintf(stdout, "期望搜索代价:\n");
    for (int i = 1; i <= key_size+1; ++i)
    {
        for (int j = 0; j <= key_size; ++j)
            fprintf(stdout, "%.2f ", expectation[i][j]);
        fprintf(stdout, "\n");
    }
    // 输出子树的概率总和
    fprintf(stdout, "子树的概率总和:\n");
    for (int i = 1; i <= key_size+1; ++i)
    {
        for (int j = 0; j <= key_size; ++j)
            fprintf(stdout, "%.2f ", prob_sum[i][j]);
        fprintf(stdout, "\n");
    }
    // 输出子树的根
    fprintf(stdout, "子树的根:\n");
    for (int i = 1; i <= key_size; ++i)
    {
        for (int j = 1; j <= key_size; ++j)
            fprintf(stdout, "%d ", root[i][j]);
        fprintf(stdout, "\n");
    }
    // 输出结构
    fprintf(stdout, "最优二叉查找树的结构:\n");
    print_optimal_bstree(root, key_size, 1, key_size);
    fprintf(stdout, "\n");
    return expectation[1][key_size];
}


//题目：输入一个整数数组，判断该数组是不是某二元查找树的后序遍历的结果。
//如果是返回true，否则返回false。
bool rebuild_bstree_by_postorder_traversal_sequence(int *array, int begin, int end, bstree<int> &t)
{
		//输入不正确
	if (array == NULL || begin > end)
		return false;

		//空树
	if (begin == end)
		return true;

		//只有根的树
	if (begin == end-1)
	{
		t.insert(array[begin]);
		return true;
	}
	
	int root = array[end-1];
	t.insert(root);

	int i;
	for (i = begin; i <= end-2; ++i)
	{
		if (array[i] > root)
			break;
	}

	if (rebuild_bstree_by_postorder_traversal_sequence(array, begin, i, t) == true)
		return rebuild_bstree_by_postorder_traversal_sequence(array, i, end-1, t);
	else
		return false;
}

}
