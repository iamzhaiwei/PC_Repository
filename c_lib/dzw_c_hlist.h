// dzw_c_hlist.h
//
// last-edit-by: <> 
//
// Description:
// Linux内核哈希表链表
//////////////////////////////////////////////////////////////////////

#ifndef DZW_C_HLIST_H
#define DZW_C_HLIST_H 1

#include <stddef.h>

// 链表结点
struct hlist_node
{
    struct hlist_node *p_next;
    struct hlist_node **pp_prev;
};

// 链表表头
struct hlist_head
{
    struct hlist_node *p_first;
};

// 初始化
#define HLIST_HEAD_INIT {.p_first = NULL}
#define HLIST_HEAD(name) struct hlist_head name = {.p_first = NULL}

// 返回结构的绝对内存地址
// // ptr: member成员的绝对内存地址
// type: 数据结构的类型名字
// member: 数据结构的成员名字
#define struct_entry(ptr, type, member)\
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

// 表头初始化
static inline void hlist_head_init(struct hlist_head *p_head)
{
    p_head->p_first = NULL;
}

// 结点初始化
static inline void hlist_node_init(struct hlist_node *p_node)
{
    p_node->p_next = NULL;
    p_node->pp_prev = NULL;
}

// 判断链表是否为空
static inline int hlist_empty(struct hlist_head *p_head)
{
    return p_head->p_first == NULL;
}

// 在链表表头p_head后面添加新结点p_node
static inline void hlist_add(struct hlist_node *p_node, struct hlist_head *p_head)
{
    struct hlist_node *p_next = p_head->p_first;
    p_head->p_first = p_node;
    p_node->pp_prev = &p_head->p_first;
    p_node->p_next = p_next;
    if (p_next != NULL)
        p_next->pp_prev = &p_node->p_next;
}

// 删除结点p_node
static inline void hlist_del(struct hlist_node *p_node)
{
    struct hlist_node *p_next = p_node->p_next;
    struct hlist_node **pp_prev = p_node->pp_prev;
    *pp_prev = p_next;
    if (p_next != NULL)
        p_next->pp_prev = pp_prev;
    hlist_node_init(p_node);
}

#endif // DZW_C_HLIST_H
//////////////////////////////////////////////////////////////////////
