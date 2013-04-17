// bstree.h
//
// last-edit-by: <>
// 2012-06-18 Ding Zhaiwei
//
// Description:
// 二叉查找树
//////////////////////////////////////////////////////////////////////

#ifndef BSTREE_OPERATION_H
#define BSTREE_OPERATION_H 1

#include "bstree.h"

namespace zhaiwei
{

//清空一棵树，返回哨兵节点指针
template <typename T>
btree_node<T> *bstree_clear_r(btree_node<T> *p_tree, btree_node<T> *sentinel_node = NULL);

//从一棵树中查找一个元素是否存在，若存在返回其指针，否则返回NIL结点指针，非递归版本
template <typename T>
btree_node<T> *bstree_find(const T &item, btree_node<T> *p_tree, btree_node<T> *sentinel_node = NULL);

//从一棵树中查找一个元素是否存在，若存在返回其指针，否则返回NIL结点指针，递归版本
template <typename T>
btree_node<T> *bstree_find_r(const T &item, btree_node<T> *p_tree, btree_node<T> *sentinel_node = NULL);

// 返回树t的最大值结点指针，若是空树，返回哨兵结点指针
template <typename T>
btree_node<T> *bstree_max(btree_node<T> *t, btree_node<T> *sentinel_node = NULL);

// 返回树t的最小值结点指针，若是空树，返回哨兵结点指针
template <typename T>
btree_node<T> *bstree_min(btree_node<T> *t, btree_node<T> *sentinel_node = NULL);

// 返回结点p_node的后继结点，若p_node是最大值结点，返回哨兵结点
// 假设p_node为有效结点
template <typename T>
btree_node<T> *bstree_successor(btree_node<T> *p_node, btree_node<T> *sentinel_node = NULL);

// 返回结点p_node的前驱结点，若p_node是最小值结点，返回哨兵结点
// 假设p_node为有效结点
template <typename T>
btree_node<T> *bstree_predecessor(btree_node<T> *p_node, btree_node<T> *sentinel_node = NULL);

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


// 清空一棵树，返回哨兵结点指针，递归版本
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


// 查找，若存在，返回结点指针，若不存在，返回哨兵结点指针，非递归版本
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


// 查找，若存在，返回结点指针，若不存在，返回哨兵结点指针，递归版本
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


// 返回树t的最大值结点指针，若是空树，返回哨兵结点指针
template <typename T>
btree_node<T> *bstree_max(btree_node<T> *t, btree_node<T> *sentinel_node)
{
    // 空树
    if (t == sentinel_node)
        return t;

    btree_node<T> *p_curr = t;
    while (p_curr->mp_right != sentinel_node)
    {
        p_curr = p_curr->mp_right;
    }
    return p_curr;
}


// 返回树t的最小值结点指针，若是空树，返回哨兵结点指针
template <typename T>
btree_node<T> *bstree_min(btree_node<T> *t, btree_node<T> *sentinel_node)
{
    // 空树
    if (t == sentinel_node)
        return t;

    btree_node<T> *p_curr = t;
    while (p_curr->mp_left != sentinel_node)
    {
        p_curr = p_curr->mp_left;
    }
    return p_curr;
}


// 返回结点p_node的后继结点，若p_node是最大值结点，返回哨兵结点
// 假设p_node为有效结点
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

// 返回结点p_node的前驱结点，若p_node是最小值结点，返回哨兵结点
// 假设p_node为有效结点
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
