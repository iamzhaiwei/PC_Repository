// list_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "list_problem.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include "my_algorithm.h"
//////////////////////////////////////////////////////////////////////

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
void dc_list_erase_node_with_equal_value(dc_list_node<int> *&p_headA, dc_list_node<int> *&p_headB)
{
    if (p_headA == NULL || p_headB == NULL)
        return;
    // A_vec存储链表A的元素值，B_vec存储链表B的元素值
    std::vector<int> A_vec, B_vec, common_vec;
    dc_list_node<int> *p_node;
    A_vec.push_back(p_headA->m_item);
    p_node = p_headA->mp_next;
    while (p_node != p_headA)
    {
        A_vec.push_back(p_node->m_item);
        p_node = p_node->mp_next;
    }
    B_vec.push_back(p_headB->m_item);
    p_node = p_headB->mp_next;
    while (p_node != p_headB)
    {
        B_vec.push_back(p_node->m_item);
        p_node = p_node->mp_next;
    }
    // 将A_vec和B_vec排序
    std::sort(A_vec.begin(), A_vec.end());
    std::sort(B_vec.begin(), B_vec.end());
    // 合并A_vec和B_vec相同的元素值到common_vec
    std::size_t i = 0, j = 0;
    while (i < A_vec.size() && j < B_vec.size())
    {
        if (A_vec[i] < B_vec[j])
            ++i;
        else if (A_vec[i] > B_vec[j])
            ++j;
        else
        {
            common_vec.push_back(A_vec[i]);
            ++i;
            ++j;
        }
    }
    // 分别遍历链表A和B，删除在元素值common_vec中的结点
    p_node = p_headA;
    for (i = 0; i < A_vec.size(); ++i)
    {
        if (std::binary_search(common_vec.begin(), common_vec.end(), p_node->m_item)) // 当前结点是值相同的结点
        {
            if (p_node == p_headA && p_node->mp_next == p_headA) // 链表中只有头结点一个结点
            {
                delete p_headA;
                p_headA = NULL;
                break;
            }
            else if (p_node == p_headA) // 当前结点是头结点
            {
                p_headA = p_node->mp_next;
                p_headA->mp_front = p_node->mp_front;
                p_node->mp_front->mp_next = p_headA;
                p_node = p_headA;
            }
            else
            {
                dc_list_node<int> *p_next = p_node->mp_next, *p_front = p_node->mp_front;
                p_next->mp_front = p_front;
                p_front->mp_next = p_next;
                delete p_node;
                p_node = p_next;
            }
        }
        else
            p_node = p_node->mp_next;
    }
    p_node = p_headB;
    for (i = 0; i < B_vec.size(); ++i)
    {
        if (std::binary_search(common_vec.begin(), common_vec.end(), p_node->m_item)) // 当前结点是值相同的结点
        {
            if (p_node == p_headB && p_node->mp_next == p_headB) // 链表中只有头结点一个结点
            {
                delete p_headB;
                p_headB = NULL;
                break;
            }
            else if (p_node == p_headB) // 当前结点是头结点
            {
                p_headB = p_node->mp_next;
                p_headB->mp_front = p_node->mp_front;
                p_node->mp_front->mp_next = p_headB;
                p_node = p_headB;
            }
            else
            {
                dc_list_node<int> *p_next = p_node->mp_next, *p_front = p_node->mp_front;
                p_next->mp_front = p_front;
                p_front->mp_next = p_next;
                delete p_node;
                p_node = p_next;
            }
        }
        else
            p_node = p_node->mp_next;
    }
}


// 输出双向循环链表
void dc_list_print(dc_list_node<int> *p_head)
{
    if (p_head == NULL)
        return;
    fprintf(stdout, "%d ", p_head->m_item);
    dc_list_node<int> *p_node = p_head->mp_next;
    while (p_node != p_head)
    {
        fprintf(stdout, "%d ", p_node->m_item);
        p_node = p_node->mp_next;
    }
    fprintf(stdout, "\n");
}


//给定链表的头指针和一个结点指针，在 O(1)时间删除该结点。
list_node<int> *erase_node(list_node<int> *h, list_node<int> *p)
{
    if (h == NULL || p == NULL) return h;

    list_node<int> *tmp;
    if (p->mp_next != NULL) //p不是最后一个结点
    {
        tmp = p->mp_next;
        p->m_item = tmp->m_item;
        p->mp_next = tmp->mp_next;
        delete tmp;
    }
    else if (p == h) //p是最后一个结点，同时也是头结点
    {
        delete h;
        h = NULL;
    }
    else
    {
        tmp = h;
        while (tmp->mp_next != p)
            tmp = tmp->mp_next;
        tmp->mp_next = NULL;
        delete p;
    }

    return h;
}


//只给定单链表中某个结点 p(并非最后一个结点，即 p->next!=NULL)指针，删除该结点。
void erase_nonlast_node(list_node<int> *p)
{
    list_node<int> *p_next = p->mp_next;
    p->m_item = p_next->m_item;
    p->mp_next = p_next->mp_next;
    delete p_next;
}


//输入一个单向链表，输出该链表中倒数第k个结点。链表的倒数第0个结点为链表的尾指针。
list_node<int> *find_backward_kth_node(list_node<int> *h, int k)
{
    if (h == NULL || k <= 0)
        return NULL;

    list_node<int> *p = h, *pk = h;
    while (--k > 0)
    {
        if (pk != NULL)
            pk = pk->mp_next;
        else
            return NULL;
    }

    while (pk->mp_next != NULL)
    {
        p = p->mp_next;
        pk = pk->mp_next;
    }

    return p;
}


//给定两个单链表，检测两个链表是否有交点，如果有返回第一个交点。
//假定两个单链表都没有环。
list_node<int> *find_first_common_node_of_two_intersectant_lists(list_node<int> *h1, list_node<int> *h2)
{
    if (h1 == NULL || h2 == NULL) return NULL;

    if (h1 == h2) return h1;

    int len1 = 0, len2 = 0;
    list_node<int> *p1 = h1, *p2 = h2;
    while (p1 != NULL)
    {
        ++len1;
        p1 = p1->mp_next;
    }
    while (p2 != NULL)
    {
        ++len2;
        p2 = p2->mp_next;
    }

    p1 = h1;
    p2 = h2;
    if (len1 > len2)
    {
        int k = len1 - len2;
        while (k-- > 0)
            p1 = p1->mp_next;
    }
    else
    {
        int k = len2 - len1;
        while (k-- > 0)
            p2 = p2->mp_next;
    }

    while (p1 != p2)
    {
        p1 = p1->mp_next;
        p2 = p2->mp_next;
    }
    return p1;
}


//给定单链表，如果有环的话请返回从头结点进入环的第一个节点。
list_node<int> *find_first_node_into_cycle(list_node<int> *h)
{
    list_node<int> *p_node = list_has_cycle(h);
    if (p_node == NULL)
        return NULL;

    list_node<int> *p_new_head = p_node->mp_next;
    p_node->mp_next = NULL;

    list_node<int> *p_first_node = find_first_common_node_of_two_intersectant_lists(h, p_new_head);

    p_node->mp_next = p_new_head;
    return p_first_node;
}


//只给定单链表中某个结点 p(非空结点)，在 p 前面插入一个结点。
void insert_before_nonnull_node(int item, list_node<int> *p)
{
    list_node<int> *p_new_node = new list_node<int>(p->m_item);
    p_new_node->mp_next = p->mp_next;
    p->mp_next = p_new_node;
    p->m_item = item;
}


//输入一个单链表的头结点，从尾到头反过来输出每个结点的值。
void list_backward_output(std::ostream &ostr, list_node<int> *h)
{
    if (h == NULL)
        return;

    list_backward_output(ostr, h->mp_next);
    ostr << h->m_item << " ";
}


//给定单链表，检测是否有环。
list_node<int> *list_has_cycle(list_node<int> *h)
{
    if (h == NULL) return NULL;

    list_node<int> *p1 = h, *p2 = h->mp_next;
    while (p2 != NULL)
    {
        if (p1 == p2)
            break;
        
        p1 = p1->mp_next;
        p2 = p2->mp_next;
        if (p2 != NULL)
            p2 = p2->mp_next;
        else
            break;
    }
    return p2;
}


//给出俩个单向链表的头指针，判断这俩个链表是否相交。
//为了简化问题，我们假设俩个链表均不带环。
bool list_intersect(list_node<int> *h1, list_node<int> *h2)
{
    if (h1 == NULL || h2 == NULL) return NULL;

    if (h1 == h2) return h1;

    list_node<int> *p1 = h1, *p2 = h2;
    while (p1->mp_next != NULL)
        p1 = p1->mp_next;
    while (p2->mp_next != NULL)
        p2 = p2->mp_next;

    if (p1 == p2)
        return true;
    else
        return false;
}

//单链表合并排序
list_node<int> *list_msort(list_node<int> *h, int len)
{
    if (h == NULL) return NULL;
    
    if (len == 1)
    {
        h->mp_next = NULL;
        return h;
    }

    list_node<int> *p_mid = h;
    for (int i = 0; i != len/2; ++i)
        p_mid = p_mid->mp_next;
    list_node<int> *p1 = list_msort(h, len/2);
    list_node<int> *p2 = list_msort(p_mid, len-len/2);
    return merge_ordered_list(p1, p2);
}
list_node<int> *list_merge_sort(list_node<int> *h)
{
    if (h == NULL) return NULL;
    
    int len = 0;
    list_node<int> *p = h;
    while (p != NULL)
    {
        ++len;
        p = p->mp_next;
    }

    return list_msort(h, len);
}

//问题扩展：给定两个单链表，检测两个链表是否有交点，如果链表可能有环列?
bool list_with_cycle_intersect(list_node<int> *h1, list_node<int> *h2)
{
    if (h1 == NULL || h2 == NULL) return false;
    if (h1 == h2) return true;

    list_node<int> *p1_in_cycle = list_has_cycle(h1);
    list_node<int> *p2_in_cycle = list_has_cycle(h2);

    bool flag;
    if (p1_in_cycle == NULL && p2_in_cycle == NULL) //h1和h2都没有环
        flag = list_intersect(h1, h2);
    else if ( (p1_in_cycle == NULL && p2_in_cycle != NULL) || //一个有环，一个没环
              (p1_in_cycle != NULL && p2_in_cycle == NULL) )
        flag = false;
    else 
    {
        //h1和h2都有环。断开h1的环，若h2和h1相交，h2也将无环，否则，h2的环已然存在。
        list_node<int> *p1_in_cycle_next = p1_in_cycle->mp_next;
        p1_in_cycle->mp_next = NULL;
        if (list_has_cycle(h2) != NULL)
            flag = false;
        else
            flag = true;
        p1_in_cycle->mp_next = p1_in_cycle_next;
    }
    return flag;
}

//单链表就地反向
list_node<int> *list_reverse(list_node<int> *p_head)
{
    list_node<int> *p_prev = NULL, *p_curr = NULL, *p_next = NULL;

    p_curr = p_head;
    while (p_curr != NULL)
    {
        p_next = p_curr->mp_next;
        p_curr->mp_next = p_prev;
        p_prev = p_curr;
        p_curr = p_next;
    }
    return p_prev;
}

// 链表相邻元素翻转，如a->b->c->d->e->f-g，翻转后变为：b->a->d->c->f->e->g
list_node<int> *list_reverse_adjacent_node(list_node<int> *p_head)
{
	list_node<int> *p_prev, *p_curr_first, *p_curr_second, *p_next, *p_new_head;
	
	p_prev = NULL;
	p_curr_first = p_head;
	p_new_head = p_head;
	while (p_curr_first != NULL && p_curr_first->mp_next != NULL)
	{
		p_curr_second = p_curr_first->mp_next;
		p_next = p_curr_second->mp_next;
		p_curr_first->mp_next = p_next;
		p_curr_second->mp_next = p_curr_first;
		if (p_prev != NULL)
			p_prev->mp_next = p_curr_second;
		else
			p_new_head = p_curr_second;
		p_prev = p_curr_first;
		p_curr_first = p_next;
	}
	return p_new_head;
}

//合并排好序的链表
list_node<int> *merge_ordered_list(list_node<int> *h1, list_node<int> *h2)
{
	if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;

    list_node<int> *p_head = NULL;
    if (h1->m_item < h2->m_item)
    {
        p_head = h1;
        h1 = h1->mp_next;
    }
    else
    {
        p_head = h2;
        h2 = h2->mp_next;
    }
  
    list_node<int> *p_curr = p_head;
    while (h1 != NULL || h2 != NULL)
    {
        if (h1 == NULL || (h2 != NULL && h2->m_item < h1->m_item))
        {
            p_curr->mp_next = h2;
            p_curr = p_curr->mp_next;
            h2 = h2->mp_next;
        }
        else
        {
            p_curr->mp_next = h1;
            p_curr = p_curr->mp_next;
            h1 = h1->mp_next;
        }
    }
    return p_head;
}

}
