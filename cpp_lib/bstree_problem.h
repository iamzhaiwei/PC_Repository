// bstree_problem.h
//
// last-edit-by: <> 
//
// Description:
// �������������
//////////////////////////////////////////////////////////////////////

#ifndef BSTREE_PROBLEM_H
#define BSTREE_PROBLEM_H 1

#include "bstree.h"

namespace zhaiwei
{

// ΢��������
// һ��������������� f=(���ֵ+��Сֵ)/2��
// ���һ���㷨���ҳ�����fֵ���������fֵ�Ľ�㡣
// ���Ӷ������O(n2)�򲻵÷֡�
btree_node<int> *bstree_find_closest_greater_than_median_node(btree_node<int> *tree);


//���������ת��Ϊ�����˫���б����½���㣬ֻ�ı�ָ��ָ��
void bstree_to_dlist(btree_node<int> *p_node, btree_node<int> *&head, btree_node<int> *&tail);
void print_bstree_to_dlist(std::ostream &ostr, btree_node<int> *p_node, int flag);


//��Ŀ������һ�Ŷ�Ԫ��������������ת��Ϊ���ľ���.
//����ת����Ķ�Ԫ�������У��������Ľ�㶼�����������Ľ�㡣
//�õݹ��ѭ�����ַ���������ľ���ת����
btree_node<int> *bstree_to_mirror_recursion(btree_node<int> *p_node);
void bstree_to_mirror_circular(btree_node<int> *p_node);


//��дһ�����򣬰�һ��������������ŵ������������
btree_node<int> *build_bstree_from_ordered_array(int *array, int begin, int end);


// ����һ�����Ŷ��������
// Parameter: 
// key_freq: �ؼ��ֵ�����Ƶ�����飬�±��1��ʼ��n
// virtual_key_freq: �����������Ƶ�����飬�±��0��ʼ��n
// key_size: �ؼ�������Ƶ�ʵ���Ч��Ŀn
// Return Value:
// ���Ŷ���������������������ۣ�����ӡ���������Ľṹ
double build_optimal_bstree(double *key_freq, double *virtual_key_freq, int key_size);


//��Ŀ������һ���������飬�жϸ������ǲ���ĳ��Ԫ�������ĺ�������Ľ����
//����Ƿ���true�����򷵻�false��
bool rebuild_bstree_by_postorder_traversal_sequence(int *array, int begin, int end, bstree<int> &t);

}




#endif // BTREE_PROBLEM_H
