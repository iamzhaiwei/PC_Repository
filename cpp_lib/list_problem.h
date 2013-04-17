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

// 雅虎面试题
// 有双向循环链表结点定义为：
// struct node
// { 
//   int data;
//   struct node *front,*next;
// };
// 有两个双向循环链表A，B，知道其头指针为：pHeadA,pHeadB，请写一函数将两链表中data值相同的结点删除。
void dc_list_erase_node_with_equal_value(dc_list_node<int> *&p_headA, dc_list_node<int> *&p_headB);


// 输出双向循环链表
void dc_list_print(dc_list_node<int> *p_head);


//给定链表的头指针和一个结点指针，在 O(1)时间删除该结点。
list_node<int> *erase_node(list_node<int> *h, list_node<int> *p);


//只给定单链表中某个结点 p(并非最后一个结点，即 p->next!=NULL)指针，删除该结点。
void erase_nonlast_node(list_node<int> *p);


//输入一个单向链表，输出该链表中倒数第k个结点。链表的倒数第0个结点为链表的尾指针。
list_node<int> *find_backward_kth_node(list_node<int> *h, int k);


//给定两个单链表，检测两个链表是否有交点，如果有返回第一个交点。
//假定两个单链表都没有环。
list_node<int> *find_first_common_node_of_two_intersectant_lists(list_node<int> *h1, list_node<int> *h2);


//给定单链表，如果有环的话请返回从头结点进入环的第一个节点。
list_node<int> *find_first_node_into_cycle(list_node<int> *h);


//只给定单链表中某个结点 p(非空结点)，在 p 前面插入一个结点。
void insert_before_nonnull_node(int item, list_node<int> *p);


//输入一个单链表的头结点，从尾到头反过来输出每个结点的值。
void list_backward_output(std::ostream &ostr, list_node<int> *h);


//给定单链表，检测是否有环。返回NULL，表示没有环
list_node<int> *list_has_cycle(list_node<int> *h);


//给出俩个单向链表的头指针，判断这俩个链表是否相交。
//为了简化问题，我们假设俩个链表均不带环。
bool list_intersect(list_node<int> *h1, list_node<int> *h2);


//单链表合并排序
list_node<int> *list_merge_sort(list_node<int> *h);


//单链表就地反向
list_node<int> *list_reverse(list_node<int> *p_head);


// 链表相邻元素翻转，如a->b->c->d->e->f-g，翻转后变为：b->a->d->c->f->e->g
list_node<int> *list_reverse_adjacent_node(list_node<int> *p_head);


//问题扩展：给定两个单链表，检测两个链表是否有交点，如果链表可能有环列?
bool list_with_cycle_intersect(list_node<int> *h1, list_node<int> *h2);


//合并排好序的链表
list_node<int> *merge_ordered_list(list_node<int> *h1, list_node<int> *h2);

}

#endif // LIST_PROBLEM_H
//////////////////////////////////////////////////////////////////////
