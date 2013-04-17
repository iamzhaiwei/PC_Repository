// btree_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "btree_problem.h"
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

//////////////////////////////////////////////////////////////////////

using namespace std;

namespace zhaiwei
{

// 淘宝笔试题：对于一颗完全二叉树，要求给所有节点加上一个pNext指针，指向同一层的相邻节点；
// 如果当前节点已经是该层的最后一个节点，则将pNext指针指向NULL；给出程序实现，并分析时间复杂度和空间复杂度。
void add_pointer_to_right_neighbour_node(btree_node_v2<int> *p_node)
{
    if (p_node == NULL)
        return;

    // 指针队列，存储每个结点的指针，若一结点是该层最右边的结点，该结点指针入队后，
    // 再入队一个NULL指针，标识该结点是最右边的结点，其右邻居指针应设为NULL
    queue< btree_node_v2<int> * > ptr_queue;

    ptr_queue.push(p_node);
    ptr_queue.push(NULL);
    btree_node_v2<int> *p_curr;
    while (!ptr_queue.empty())
    {
        p_curr = ptr_queue.front();
        ptr_queue.pop();
        if (p_curr == NULL)
            continue;
        p_curr->mp_right_neighbour = ptr_queue.front();
        if (p_curr->mp_left != NULL)
            ptr_queue.push(p_curr->mp_left);
        if (p_curr->mp_right != NULL)
            ptr_queue.push(p_curr->mp_right);

        if (ptr_queue.front() == NULL) // 该层已结束，下一层也已结束
        {
            ptr_queue.push(NULL);
        }
    }
}


// 判断二叉树是否平衡二叉树
// 平衡二叉树的定义：每个结点的左右子树的高度差小于等于1.
// 分析：左右子树都是平衡二叉树并且左右子树的高度差小于等于1
static bool btree_is_balance(btree_node<int> *p_node, int &height)
{
	// 空树
	if (p_node == NULL)
	{
		height = -1;
		return true;
	}

	int left_child_height;
	bool left_child_balance = btree_is_balance(p_node->mp_left, left_child_height);
	if (left_child_balance == false)
		return false;
	int right_child_height;
	bool right_child_balance = btree_is_balance(p_node->mp_right, right_child_height);
	if (right_child_balance == false)
		return false;
	height = std::max(left_child_height, right_child_height) + 1;
	return abs(left_child_height-right_child_height) <= 1;
}
bool btree_is_balance(btree_node<int> *p_node)
{
	if (p_node == NULL) return true;
	int height;
	return btree_is_balance(p_node, height);
}


// 已知二叉树的前序遍历为：- + a * b - c d / e f
// 后序遍历为：a b c d - * + e f / -
// 求其中序遍历
// 解法：递归。
// 可以很好地处理叶节点和有两个孩子的节点。但若只有一个孩子，无论原来是左孩子还是右孩子，都会重建成左孩子。
btree_node<char> *btree_rebuild_from_preorder_and_postorder_traversal(char *p_preorder, char *p_postorder, int length)
{
	if (p_preorder == NULL || p_postorder == NULL || length <= 0)
		return NULL;

	btree_node<char> *p_root = new btree_node<char>(NULL, NULL, NULL, p_preorder[0]);
    if (length == 1)
        return p_root;

	char *p_left_preorder = p_preorder + 1;
	char *p_left_postorder = p_postorder;
	int left_postorder_end;
	for (left_postorder_end = 0; left_postorder_end < length-1; ++left_postorder_end)
	{
		if (p_postorder[left_postorder_end] == p_preorder[1])
			break;
	}
	int left_length = left_postorder_end + 1;

	char *p_right_preorder = p_preorder + 1 + left_length;
	char *p_right_postorder = p_postorder + left_length;
	int right_length = length - left_length - 1;

	p_root->mp_left = btree_rebuild_from_preorder_and_postorder_traversal(p_left_preorder, p_left_postorder, left_length);
	p_root->mp_right = btree_rebuild_from_preorder_and_postorder_traversal(p_right_preorder, p_right_postorder, right_length);
	return p_root;
}


//二元树的深度。
//调用之前，设置parent_depth=-1
int btree_depth(btree_node<int> *p_node, int parent_depth)
{
	if (p_node == NULL)
		return parent_depth;

	if (p_node->mp_left == NULL && p_node->mp_right == NULL)
		return parent_depth + 1;

	int left_child_depth = p_node->mp_left? btree_depth(p_node->mp_left, parent_depth+1): -1;
	int right_child_depth = p_node->mp_right? btree_depth(p_node->mp_right, parent_depth+1): -1;
	return std::max<int>(left_child_depth, right_child_depth);
}


//二元树的高度。
int btree_height(btree_node<int> *p_node)
{
	if (p_node == NULL)
		return -1;

	int left_child_height = p_node->mp_left? btree_height(p_node->mp_left): -1;
	int right_child_height = p_node->mp_right? btree_height(p_node->mp_right): -1;
	return std::max<int>(left_child_height, right_child_height) + 1;
}


//输入二叉树中的两个结点，输出这两个结点在树中最低的共同父结点。
btree_node<int> *find_lowest_common_parent(btree_node<int> *p_node, btree_node<int> *p_node1, btree_node<int> *p_node2)
{
	if (p_node == NULL)
		return NULL;

	if (p_node == p_node1 || p_node == p_node2)
		return p_node;

	btree_node<int> *pleft = find_lowest_common_parent(p_node->mp_left, p_node1, p_node2);
	btree_node<int> *pright = find_lowest_common_parent(p_node->mp_right, p_node1, p_node2);
	if (pleft == NULL)
		return pright;
	else if (pright == NULL)
		return pleft;
	else
		return p_node;
}


//在二元树中找出和为某一值的所有路径
//题目：输入一个整数和一棵二元树。从树的根结点开始往下访问一直到叶结点所经过的所有结点形成一条路径。
//打印出和与输入整数相等的所有路径。
static void find_paths(btree_node<int> *p_node, const int expected_path_len, vector<btree_node<int> *> &path, int &path_len)
{
	if (p_node == NULL)
		return;

	path.push_back(p_node);
	path_len += p_node->m_item;

	if (p_node->mp_left == NULL && p_node->mp_right == NULL && path_len == expected_path_len)
	{
		for (vector<btree_node<int> *>::iterator iter = path.begin(); iter != path.end(); ++iter)
			cout << **iter << ' ';
		cout << endl;
	}

	find_paths(p_node->mp_left, expected_path_len, path, path_len);
	find_paths(p_node->mp_right, expected_path_len, path, path_len);

	path.pop_back();
	path_len -= p_node->m_item;
}
void find_paths(btree_node<int> *p_node, const int expected_path_len)
{
	vector<btree_node<int> *> path;
	int path_len = 0;
	find_paths(p_node, expected_path_len, path, path_len);
}
//扩展题：如果将条件放宽，计算和的路径改为从根节点到叶子节点路径上任意连续子路径呢？
//条件改变之后，难度有所增加，堆栈中光存放从root到当前节点的和显然不够，需要对堆栈中的元素做出改变，
//使之存放堆栈当前位置到当前遍历节点的路径和.
class stack_element
{
public:
	stack_element(btree_node<int> *p_node, int path_len):
		mp_path_begin(p_node), m_path_len(path_len)
		{}

public:
	btree_node<int> *mp_path_begin;	// 路径起始节点
	int m_path_len;					// 从起始节点到当前节点的长度
};
static void find_paths_extend(btree_node<int> *p_node, const int expected_path_len, vector<stack_element> &path)
{
	if (p_node == NULL)
		return;

	path.push_back(stack_element(p_node, 0));
	for (vector<stack_element>::iterator iter = path.begin(); iter != path.end(); ++iter)
	{
		iter->m_path_len += p_node->m_item;
		if (iter->m_path_len == expected_path_len)
		{
			btree_node<int> *pcurr_node = iter->mp_path_begin;
			while (pcurr_node != p_node)
			{
				cout << *pcurr_node << ' ';
				if (p_node->m_item < pcurr_node->m_item)
					pcurr_node = pcurr_node->mp_left;
				else
					pcurr_node = pcurr_node->mp_right;
			}
			cout << *pcurr_node << endl;
		}
	}

	find_paths_extend(p_node->mp_left, expected_path_len, path);
	find_paths_extend(p_node->mp_right, expected_path_len, path);

	path.pop_back();
	for (vector<stack_element>::iterator iter = path.begin(); iter != path.end(); ++iter)
		iter->m_path_len -= p_node->m_item;
}
void find_paths_extend(btree_node<int> *p_node, const int expected_path_len)
{
	vector<stack_element> path;
	find_paths_extend(p_node, expected_path_len, path);
}


// 网易有道
// 求二叉树中任意两个节点之间的最大距离
// 如果我们把二叉树看成一个图，父子节点之间的连线看成是双向的，我们姑且定义"距离"为两节点之间边的个数。
// 写一个程序，求一棵二叉树中相距最远的两个节点之间的距离。
// 返回二叉树中任意两个节点之间的最大距离，同时设置树的高度
static int max_distance_of_two_nodes(btree_node<int> *p_node, int &height)
{
	// 空树
	if (p_node == NULL)
	{
		height = -1;
		return -1;
	}

	int left_child_max_dist, right_child_max_dist, left_child_height, right_child_height;
	// 求左子树中任意两个节点间的最大距离以及左子树的高度
	if (p_node->mp_left != NULL)
	{
		left_child_max_dist = max_distance_of_two_nodes(p_node->mp_left, left_child_height);
	}
	else
	{
		left_child_max_dist = -1;
		left_child_height = -1;
	}
	// 求右子树中任意两个节点间的最大距离以及右子树的高度
	if (p_node->mp_right != NULL)
	{
		right_child_max_dist = max_distance_of_two_nodes(p_node->mp_right, right_child_height);
	}
	else
	{
		right_child_max_dist = -1;
		right_child_height = -1;
	}

	height = std::max(left_child_height, right_child_height) + 1;
	return std::max(std::max(left_child_max_dist, right_child_max_dist), left_child_height+right_child_height+2);
}
int max_distance_of_two_nodes(btree_node<int> *p_node)
{
	int height;
	return max_distance_of_two_nodes(p_node, height);
}


// 淘宝笔试题
// 有一棵树（树上结点为字符串或者整数），请写代码将树的结构和数据写到一个文件中，
// 并能通过读取该文件恢复树结构 。
// 以二进制格式读写文件，对每个结点，读写的内容为：结点值，左右子树在文件中的偏移位置
// 从文件的当前位置读出一个结点，返回结点的指针
static btree_node<int> *read_btree_from_file(FILE *pf)
{
    if (pf == NULL || feof(pf))
        return NULL;

    int item;
    long int left, right;
    fread(&item, sizeof(int), 1, pf);
    fread(&left, sizeof(long int), 1, pf);
    fread(&right, sizeof(long int), 1, pf);
    btree_node<int> *p_node = new btree_node<int>(NULL, NULL, NULL, item);
    if (left != -1)
    {
        fseek(pf, left, SEEK_SET);
        p_node->mp_left = read_btree_from_file(pf);
    }
    if (right != -1)
    {
        fseek(pf, right, SEEK_SET);
        p_node->mp_right  = read_btree_from_file(pf);
    }
    return p_node;
}
btree_node<int> *read_btree_from_file(const char *p_file_name)
{
    if (p_file_name == NULL)
        return NULL;

    FILE *pf = fopen(p_file_name, "rb");
    btree_node<int> *p_node = read_btree_from_file(pf);
    fclose(pf);
    return p_node;
}
// 将当前结点写入文件的当前位置，返回当前位置
static long int write_btree_to_file(btree_node<int> *p_node, FILE *pf)
{
    if (p_node == NULL || pf == NULL)
        return -1;

    long int curr_pos = ftell(pf); // 记录当前结点在文件中的偏移位置
    int item = p_node->m_item;
    long int left = -1, right = -1;
    fwrite(&item, sizeof(int), 1, pf);
    fwrite(&left, sizeof(long int), 1, pf);
    fwrite(&right, sizeof(long int), 1, pf);
    left = write_btree_to_file(p_node->mp_left, pf);
    right = write_btree_to_file(p_node->mp_right, pf);

    long int new_pos = ftell(pf); // 记录文件的最后偏移位置
    fseek(pf, curr_pos+sizeof(int), SEEK_SET);
    fwrite(&left, sizeof(long int), 1, pf);
    fwrite(&right, sizeof(long int), 1, pf);
    fseek(pf, new_pos, SEEK_SET);
    return curr_pos;
}
void write_btree_to_file(btree_node<int> *tree, const char *p_file_name)
{
    if (tree == NULL || p_file_name == NULL)
        return;

    FILE *pf = fopen(p_file_name, "wb");
    write_btree_to_file(tree, pf);
    fclose(pf);
}

}
