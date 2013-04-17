// btree_problem.h
//
// last-edit-by: <> 
//
// Description:
// ����������
//////////////////////////////////////////////////////////////////////
#ifndef BTREE_PROBLEM_H
#define BTREE_PROBLEM_H 1

#include "btree.h"
#include <iostream>

namespace zhaiwei
{
	
// ��������㣬����ָ�����ھӵ�ָ��
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
    btree_node_v2<T> *mp_left; // �����
    btree_node_v2<T> *mp_right; // �Ҷ���
    btree_node_v2<T> *mp_right_neighbour; // ���ھ�
};
// �������
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
// �Ա������⣺����һ����ȫ��������Ҫ������нڵ����һ��pNextָ�룬ָ��ͬһ������ڽڵ㣻
//�����ǰ�ڵ��Ѿ��Ǹò�����һ���ڵ㣬��pNextָ��ָ��NULL����������ʵ�֣�������ʱ�临�ӶȺͿռ临�Ӷȡ�
void add_pointer_to_right_neighbour_node(btree_node_v2<int> *p_node);


//��Ԫ������ȡ�
//����֮ǰ������parent_depth=-1
int btree_depth(btree_node<int> *p_node, int parent_depth);


//��Ԫ���ĸ߶ȡ�
int btree_height(btree_node<int> *p_node);


// �ж϶������Ƿ�ƽ�������
// ƽ��������Ķ��壺ÿ���������������ĸ߶Ȳ�С�ڵ���1.
bool btree_is_balance(btree_node<int> *p_node);


// ��֪��������ǰ�����Ϊ��- + a * b - c d / e f 
// �������Ϊ��a b c d - * + e f / -
// �����������
btree_node<char> *btree_rebuild_from_preorder_and_postorder_traversal(char *p_preorder, char *p_postorder, int length);


//����������е�������㣬��������������������͵Ĺ�ͬ����㡣
btree_node<int> *find_lowest_common_parent(btree_node<int> *p_node, btree_node<int> *p_node1, btree_node<int> *p_node2);


//�ڶ�Ԫ�����ҳ���Ϊĳһֵ������·��
//��Ŀ������һ��������һ�ö�Ԫ���������ĸ���㿪ʼ���·���һֱ��Ҷ��������������н���γ�һ��·����
//��ӡ����������������ȵ�����·����
void find_paths(btree_node<int> *p_node, const int expected_path_len);
//��չ�⣺����������ſ�����͵�·����Ϊ�Ӹ��ڵ㵽Ҷ�ӽڵ�·��������������·���أ�
void find_paths_extend(btree_node<int> *p_node, const int expected_path_len);


//������������������ڵ�֮���������
//������ǰѶ���������һ��ͼ�����ӽڵ�֮������߿�����˫��ģ����ǹ��Ҷ���"����"Ϊ���ڵ�֮��ߵĸ�����
//дһ��������һ�ö������������Զ�������ڵ�֮��ľ��롣
int max_distance_of_two_nodes(btree_node<int> *p_node);


// �Ա�������
// ��һ���������Ͻ��Ϊ�ַ�����������������д���뽫���Ľṹ������д��һ���ļ��У�
// ����ͨ����ȡ���ļ��ָ����ṹ ��
btree_node<int> *read_btree_from_file(const char *p_file_name);
void write_btree_to_file(btree_node<int> *tree, const char *p_file_name);


	
}

#endif // BTREE_PROBLEM_H
