// bstree.h
//
// last-edit-by: <>
// 2012-06-18 Ding Zhaiwei
//
// Description:
// ���������
//////////////////////////////////////////////////////////////////////

#ifndef BSTREE_OPERATION_H
#define BSTREE_OPERATION_H 1

#include "bstree.h"

namespace zhaiwei
{

//���һ�����������ڱ��ڵ�ָ��
template <typename T>
btree_node<T> *bstree_clear_r(btree_node<T> *p_tree, btree_node<T> *sentinel_node = NULL);

//��һ�����в���һ��Ԫ���Ƿ���ڣ������ڷ�����ָ�룬���򷵻�NIL���ָ�룬�ǵݹ�汾
template <typename T>
btree_node<T> *bstree_find(const T &item, btree_node<T> *p_tree, btree_node<T> *sentinel_node = NULL);

//��һ�����в���һ��Ԫ���Ƿ���ڣ������ڷ�����ָ�룬���򷵻�NIL���ָ�룬�ݹ�汾
template <typename T>
btree_node<T> *bstree_find_r(const T &item, btree_node<T> *p_tree, btree_node<T> *sentinel_node = NULL);

// ������t�����ֵ���ָ�룬���ǿ����������ڱ����ָ��
template <typename T>
btree_node<T> *bstree_max(btree_node<T> *t, btree_node<T> *sentinel_node = NULL);

// ������t����Сֵ���ָ�룬���ǿ����������ڱ����ָ��
template <typename T>
btree_node<T> *bstree_min(btree_node<T> *t, btree_node<T> *sentinel_node = NULL);

// ���ؽ��p_node�ĺ�̽�㣬��p_node�����ֵ��㣬�����ڱ����
// ����p_nodeΪ��Ч���
template <typename T>
btree_node<T> *bstree_successor(btree_node<T> *p_node, btree_node<T> *sentinel_node = NULL);

// ���ؽ��p_node��ǰ����㣬��p_node����Сֵ��㣬�����ڱ����
// ����p_nodeΪ��Ч���
template <typename T>
btree_node<T> *bstree_predecessor(btree_node<T> *p_node, btree_node<T> *sentinel_node = NULL);

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


// ���һ�����������ڱ����ָ�룬�ݹ�汾
template <typename T>
btree_node<T> *bstree_clear_r(btree_node<T> *t, btree_node<T> *sentinel_node)
{
    if (t != sentinel_node)
    {
        bstree_clear_r(t->mp_left);
        bstree_clear_r(t->mp_right);
        delete t;
    }
    return sentinel_node;
}


// ���ң������ڣ����ؽ��ָ�룬�������ڣ������ڱ����ָ�룬�ǵݹ�汾
template <typename T>
btree_node<T> *bstree_find(const T &item, btree_node<T> *t, btree_node<T> *sentinel_node)
{
    btree_node<T> *p_curr = t;
    while (p_curr != sentinel_node && p_curr->m_item != item)
    {
        if (item < p_curr->m_item)
            p_curr = p_curr->mp_left;
        else
            p_curr = p_curr->mp_right;
    }
    return p_curr;
}


// ���ң������ڣ����ؽ��ָ�룬�������ڣ������ڱ����ָ�룬�ݹ�汾
template <typename T>
btree_node<T> *bstree_find_r(const T &item, btree_node<T> *t, btree_node<T> *sentinel_node)
{
    if (t == sentinel_node || item == t->m_item)
        return t;
    else if (item < t->m_item)
        return find_r(item, t->mp_left);
    else
        return find_r(item, t->mp_right);
}


// ������t�����ֵ���ָ�룬���ǿ����������ڱ����ָ��
template <typename T>
btree_node<T> *bstree_max(btree_node<T> *t, btree_node<T> *sentinel_node)
{
    // ����
    if (t == sentinel_node)
        return t;

    btree_node<T> *p_curr = t;
    while (p_curr->mp_right != sentinel_node)
    {
        p_curr = p_curr->mp_right;
    }
    return p_curr;
}


// ������t����Сֵ���ָ�룬���ǿ����������ڱ����ָ��
template <typename T>
btree_node<T> *bstree_min(btree_node<T> *t, btree_node<T> *sentinel_node)
{
    // ����
    if (t == sentinel_node)
        return t;

    btree_node<T> *p_curr = t;
    while (p_curr->mp_left != sentinel_node)
    {
        p_curr = p_curr->mp_left;
    }
    return p_curr;
}


// ���ؽ��p_node�ĺ�̽�㣬��p_node�����ֵ��㣬�����ڱ����
// ����p_nodeΪ��Ч���
template <typename T>
btree_node<T> *bstree_successor(btree_node<T> *p_node, btree_node<T> *sentinel_node)
{
    if (p_node->mp_right != sentinel_node)
        return bstree_min(p_node->mp_right, sentinel_node);

    btree_node<T> *p_parent = p_node->mp_parent;
    while (p_parent != sentinel_node && p_node == p_parent->mp_right)
    {
        p_node = p_parent;
        p_parent = p_node->mp_parent;
    }
    return p_parent;
}

// ���ؽ��p_node��ǰ����㣬��p_node����Сֵ��㣬�����ڱ����
// ����p_nodeΪ��Ч���
template <typename T>
btree_node<T> *bstree_predecessor(btree_node<T> *p_node, btree_node<T> *sentinel_node)
{
    if (p_node->mp_left != sentinel_node)
        return bstree_max(p_node->mp_left, sentinel_node);

    btree_node<T> *p_parent = p_node->mp_parent;
    while (p_parent != sentinel_node && p_node == p_parent->mp_left)
    {
        p_node = p_parent;
        p_parent = p_node->mp_parent;
    }
    return p_parent;
}

}

#endif
