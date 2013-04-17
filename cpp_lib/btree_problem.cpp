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

// �Ա������⣺����һ����ȫ��������Ҫ������нڵ����һ��pNextָ�룬ָ��ͬһ������ڽڵ㣻
// �����ǰ�ڵ��Ѿ��Ǹò�����һ���ڵ㣬��pNextָ��ָ��NULL����������ʵ�֣�������ʱ�临�ӶȺͿռ临�Ӷȡ�
void add_pointer_to_right_neighbour_node(btree_node_v2<int> *p_node)
{
    if (p_node == NULL)
        return;

    // ָ����У��洢ÿ������ָ�룬��һ����Ǹò����ұߵĽ�㣬�ý��ָ����Ӻ�
    // �����һ��NULLָ�룬��ʶ�ý�������ұߵĽ�㣬�����ھ�ָ��Ӧ��ΪNULL
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

        if (ptr_queue.front() == NULL) // �ò��ѽ�������һ��Ҳ�ѽ���
        {
            ptr_queue.push(NULL);
        }
    }
}


// �ж϶������Ƿ�ƽ�������
// ƽ��������Ķ��壺ÿ���������������ĸ߶Ȳ�С�ڵ���1.
// ������������������ƽ��������������������ĸ߶Ȳ�С�ڵ���1
static bool btree_is_balance(btree_node<int> *p_node, int &height)
{
	// ����
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


// ��֪��������ǰ�����Ϊ��- + a * b - c d / e f
// �������Ϊ��a b c d - * + e f / -
// �����������
// �ⷨ���ݹ顣
// ���Ժܺõش���Ҷ�ڵ�����������ӵĽڵ㡣����ֻ��һ�����ӣ�����ԭ�������ӻ����Һ��ӣ������ؽ������ӡ�
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


//��Ԫ������ȡ�
//����֮ǰ������parent_depth=-1
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


//��Ԫ���ĸ߶ȡ�
int btree_height(btree_node<int> *p_node)
{
	if (p_node == NULL)
		return -1;

	int left_child_height = p_node->mp_left? btree_height(p_node->mp_left): -1;
	int right_child_height = p_node->mp_right? btree_height(p_node->mp_right): -1;
	return std::max<int>(left_child_height, right_child_height) + 1;
}


//����������е�������㣬��������������������͵Ĺ�ͬ����㡣
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


//�ڶ�Ԫ�����ҳ���Ϊĳһֵ������·��
//��Ŀ������һ��������һ�ö�Ԫ���������ĸ���㿪ʼ���·���һֱ��Ҷ��������������н���γ�һ��·����
//��ӡ����������������ȵ�����·����
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
//��չ�⣺����������ſ�����͵�·����Ϊ�Ӹ��ڵ㵽Ҷ�ӽڵ�·��������������·���أ�
//�����ı�֮���Ѷ��������ӣ���ջ�й��Ŵ�root����ǰ�ڵ�ĺ���Ȼ��������Ҫ�Զ�ջ�е�Ԫ�������ı䣬
//ʹ֮��Ŷ�ջ��ǰλ�õ���ǰ�����ڵ��·����.
class stack_element
{
public:
	stack_element(btree_node<int> *p_node, int path_len):
		mp_path_begin(p_node), m_path_len(path_len)
		{}

public:
	btree_node<int> *mp_path_begin;	// ·����ʼ�ڵ�
	int m_path_len;					// ����ʼ�ڵ㵽��ǰ�ڵ�ĳ���
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


// �����е�
// ������������������ڵ�֮���������
// ������ǰѶ���������һ��ͼ�����ӽڵ�֮������߿�����˫��ģ����ǹ��Ҷ���"����"Ϊ���ڵ�֮��ߵĸ�����
// дһ��������һ�ö������������Զ�������ڵ�֮��ľ��롣
// ���ض����������������ڵ�֮��������룬ͬʱ�������ĸ߶�
static int max_distance_of_two_nodes(btree_node<int> *p_node, int &height)
{
	// ����
	if (p_node == NULL)
	{
		height = -1;
		return -1;
	}

	int left_child_max_dist, right_child_max_dist, left_child_height, right_child_height;
	// �������������������ڵ����������Լ��������ĸ߶�
	if (p_node->mp_left != NULL)
	{
		left_child_max_dist = max_distance_of_two_nodes(p_node->mp_left, left_child_height);
	}
	else
	{
		left_child_max_dist = -1;
		left_child_height = -1;
	}
	// �������������������ڵ����������Լ��������ĸ߶�
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


// �Ա�������
// ��һ���������Ͻ��Ϊ�ַ�����������������д���뽫���Ľṹ������д��һ���ļ��У�
// ����ͨ����ȡ���ļ��ָ����ṹ ��
// �Զ����Ƹ�ʽ��д�ļ�����ÿ����㣬��д������Ϊ�����ֵ�������������ļ��е�ƫ��λ��
// ���ļ��ĵ�ǰλ�ö���һ����㣬���ؽ���ָ��
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
// ����ǰ���д���ļ��ĵ�ǰλ�ã����ص�ǰλ��
static long int write_btree_to_file(btree_node<int> *p_node, FILE *pf)
{
    if (p_node == NULL || pf == NULL)
        return -1;

    long int curr_pos = ftell(pf); // ��¼��ǰ������ļ��е�ƫ��λ��
    int item = p_node->m_item;
    long int left = -1, right = -1;
    fwrite(&item, sizeof(int), 1, pf);
    fwrite(&left, sizeof(long int), 1, pf);
    fwrite(&right, sizeof(long int), 1, pf);
    left = write_btree_to_file(p_node->mp_left, pf);
    right = write_btree_to_file(p_node->mp_right, pf);

    long int new_pos = ftell(pf); // ��¼�ļ������ƫ��λ��
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
