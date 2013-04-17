// dzw_c_dclist.h
//
// last-edit-by: <> 
//
// Description:
// ����Linux�ں�����ʵ����ͨ����˫��ѭ������
//////////////////////////////////////////////////////////////////////

#ifndef DZW_C_DCLIST_H
#define DZW_C_DCLIST_H 1
    
// ��ͷ
struct dclist_head
{
    struct dclist_head *p_prev;
    struct dclist_head *p_next;
};

// ��ͷ��ʼ��
#define DCLIST_HEAD_INIT(name) {&(name), &(name)}
#define DCLIST_HEAD(name) struct dclist_head name = DCLIST_HEAD_INIT(name)

// ���ؽṹ�ľ����ڴ��ַ
// // ptr: member��Ա�ľ����ڴ��ַ
// type: ���ݽṹ����������
// member: ���ݽṹ�ĳ�Ա����
#define struct_entry(ptr, type, member)\
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

// �����ʼ��
static inline void dclist_init(struct dclist_head *p_list)
{
    p_list->p_prev = p_list;
    p_list->p_next = p_list;
}

// �ж������Ƿ�Ϊ��
static inline int dclist_empty(struct dclist_head *p_list)
{
    return p_list->p_next == p_list;
}

// ��p_new_node���뵽p_nodeǰ��
static inline void dclist_insert(struct dclist_head *p_new_node, struct dclist_head *p_node)
{
    p_node->p_prev->p_next = p_new_node;
    p_new_node->p_prev = p_node->p_prev;
    p_new_node->p_next = p_node;
    p_node->p_prev = p_new_node;
}

// ��p_new_node���뵽����p_listͷ��
static inline void dclist_add(struct dclist_head *p_new_node, struct dclist_head *p_list)
{
    dclist_insert(p_new_node, p_list->p_next);
}

// ��p_new_node���뵽����p_listβ��
static inline void dclist_add_tail(struct dclist_head *p_new_node, struct dclist_head *p_list)
{
    dclist_insert(p_new_node, p_list);
}

// ɾ��p_node
static inline void dclist_del(struct dclist_head *p_node)
{
    p_node->p_prev->p_next = p_node->p_next;
    p_node->p_next->p_prev = p_node->p_prev;
    dclist_init(p_node);
}

// ��p_node������������ɾ���������뵽��һ������p_list��ͷ��
static inline void dclist_move(struct dclist_head *p_node, struct dclist_head *p_list)
{
    dclist_del(p_node);
    dclist_add(p_node, p_list);
}

// ��p_node������������ɾ���������뵽��һ������p_list��β��
static inline void dclist_move_tail(struct dclist_head *p_node, struct dclist_head *p_list)
{
    dclist_del(p_node);
    dclist_add_tail(p_node, p_list);
}

#endif // DZW_C_DCLIST_H
//////////////////////////////////////////////////////////////////////
