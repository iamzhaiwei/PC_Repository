// list_problem.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef LIST_PROBLEM_H
#define LIST_PROBLEM_H 1

#include "list.h"
#include "dc_list.h"

namespace zhaiwei
{

// �Ż�������
// ��˫��ѭ�������㶨��Ϊ��
// struct node
// { 
//   int data;
//   struct node *front,*next;
// };
// ������˫��ѭ������A��B��֪����ͷָ��Ϊ��pHeadA,pHeadB����дһ��������������dataֵ��ͬ�Ľ��ɾ����
void dc_list_erase_node_with_equal_value(dc_list_node<int> *&p_headA, dc_list_node<int> *&p_headB);


// ���˫��ѭ������
void dc_list_print(dc_list_node<int> *p_head);


//���������ͷָ���һ�����ָ�룬�� O(1)ʱ��ɾ���ý�㡣
list_node<int> *erase_node(list_node<int> *h, list_node<int> *p);


//ֻ������������ĳ����� p(�������һ����㣬�� p->next!=NULL)ָ�룬ɾ���ý�㡣
void erase_nonlast_node(list_node<int> *p);


//����һ��������������������е�����k����㡣����ĵ�����0�����Ϊ�����βָ�롣
list_node<int> *find_backward_kth_node(list_node<int> *h, int k);


//��������������������������Ƿ��н��㣬����з��ص�һ�����㡣
//�ٶ�����������û�л���
list_node<int> *find_first_common_node_of_two_intersectant_lists(list_node<int> *h1, list_node<int> *h2);


//��������������л��Ļ��뷵�ش�ͷ�����뻷�ĵ�һ���ڵ㡣
list_node<int> *find_first_node_into_cycle(list_node<int> *h);


//ֻ������������ĳ����� p(�ǿս��)���� p ǰ�����һ����㡣
void insert_before_nonnull_node(int item, list_node<int> *p);


//����һ���������ͷ��㣬��β��ͷ���������ÿ������ֵ��
void list_backward_output(std::ostream &ostr, list_node<int> *h);


//��������������Ƿ��л�������NULL����ʾû�л�
list_node<int> *list_has_cycle(list_node<int> *h);


//�����������������ͷָ�룬�ж������������Ƿ��ཻ��
//Ϊ�˼����⣬���Ǽ��������������������
bool list_intersect(list_node<int> *h1, list_node<int> *h2);


//������ϲ�����
list_node<int> *list_merge_sort(list_node<int> *h);


//������͵ط���
list_node<int> *list_reverse(list_node<int> *p_head);


// ��������Ԫ�ط�ת����a->b->c->d->e->f-g����ת���Ϊ��b->a->d->c->f->e->g
list_node<int> *list_reverse_adjacent_node(list_node<int> *p_head);


//������չ����������������������������Ƿ��н��㣬�����������л���?
bool list_with_cycle_intersect(list_node<int> *h1, list_node<int> *h2);


//�ϲ��ź��������
list_node<int> *merge_ordered_list(list_node<int> *h1, list_node<int> *h2);

}

#endif // LIST_PROBLEM_H
//////////////////////////////////////////////////////////////////////
