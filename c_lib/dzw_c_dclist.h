// dzw_c_dclist.h
//
// last-edit-by: <> 
//
// Description:
// 仿照Linux内核链表实现了通用型双向循环链表
//////////////////////////////////////////////////////////////////////

#ifndef DZW_C_DCLIST_H
#define DZW_C_DCLIST_H 1
    
// 表头
struct dclist_head
{
    struct dclist_head *p_prev;
    struct dclist_head *p_next;
};

// 表头初始化
#define DCLIST_HEAD_INIT(name) {&(name), &(name)}
#define DCLIST_HEAD(name) struct dclist_head name = DCLIST_HEAD_INIT(name)

// 返回结构的绝对内存地址
// // ptr: member成员的绝对内存地址
// type: 数据结构的类型名字
// member: 数据结构的成员名字
#define struct_entry(ptr, type, member)\
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

// 链表初始化
static inline void dclist_init(struct dclist_head *p_list)
{
    p_list->p_prev = p_list;
    p_list->p_next = p_list;
}

// 判断链表是否为空
static inline int dclist_empty(struct dclist_head *p_list)
{
    return p_list->p_next == p_list;
}

// 将p_new_node插入到p_node前面
static inline void dclist_insert(struct dclist_head *p_new_node, struct dclist_head *p_node)
{
    p_node->p_prev->p_next = p_new_node;
    p_new_node->p_prev = p_node->p_prev;
    p_new_node->p_next = p_node;
    p_node->p_prev = p_new_node;
}

// 将p_new_node插入到链表p_list头部
static inline void dclist_add(struct dclist_head *p_new_node, struct dclist_head *p_list)
{
    dclist_insert(p_new_node, p_list->p_next);
}

// 将p_new_node插入到链表p_list尾部
static inline void dclist_add_tail(struct dclist_head *p_new_node, struct dclist_head *p_list)
{
    dclist_insert(p_new_node, p_list);
}

// 删除p_node
static inline void dclist_del(struct dclist_head *p_node)
{
    p_node->p_prev->p_next = p_node->p_next;
    p_node->p_next->p_prev = p_node->p_prev;
    dclist_init(p_node);
}

// 将p_node从它的链表中删除，并插入到另一个链表p_list的头部
static inline void dclist_move(struct dclist_head *p_node, struct dclist_head *p_list)
{
    dclist_del(p_node);
    dclist_add(p_node, p_list);
}

// 将p_node从它的链表中删除，并插入到另一个链表p_list的尾部
static inline void dclist_move_tail(struct dclist_head *p_node, struct dclist_head *p_list)
{
    dclist_del(p_node);
    dclist_add_tail(p_node, p_list);
}

#endif // DZW_C_DCLIST_H
//////////////////////////////////////////////////////////////////////
