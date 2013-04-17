// bstree.h
//
// last-edit-by: <> 
// 2012-06-18 Ding Zhaiwei
// 
// Description:
// 二叉查找树
//////////////////////////////////////////////////////////////////////

#ifndef BSTREE_H
#define BSTREE_H 1

#include "btree.h"
#include "bstree_operation.h"

namespace zhaiwei
{
// 二叉查找树
template <typename T>
class bstree
{
public:
    // 返回哨兵结点指针
    static btree_node<T> *sentinel_node()
    {
        return NULL;
    }
public:
	// 构造函数
    bstree():mp_root(sentinel_node()), m_size(0)
    {}
	
	// 析构函数
    ~bstree()
    {
        bstree_clear_r(mp_root);
    }
	
	// 判断树是否为空
    bool empty()
    {
        return m_size == 0;
    }
	// 返回节点的数目
    std::size_t size()
    {
        return m_size;
    }
	// 返回树的根
	btree_node<T> *get_root()
    {
        return mp_root;
    }
	// 设置新根
    void set_root(btree_node<T> *proot)
    {
        mp_root = proot;
    }
	// 设置节点数目
    void set_size(std::size_t size)
    {
        m_size = size;
    }
	
	// 插入一个新元素
    // 非递归实现
    void insert(const T &item);
    // 递归实现
    void insert_r(const T &item)
    {
        mp_root = insert_r(item, mp_root);
    }
    
	// 删除一个元素
    // 非递归实现
    void erase(const T &item)
    {
        btree_node<T> *p_node = bstree_find(item);
        if (p_node != sentinel_node())
            erase(p_node);
    }
    // 递归实现
    void erase_r(const T &item)
    {
        mp_root = erase_r(item, mp_root);
    }
    // 删除结点p_node, 假设p_node为有效结点，非递归实现
    void erase(btree_node<T> *p_node);
	
	
	// 清空
    void clear_r()
    {
        mp_root = bstree_clear_r(mp_root);
        m_size = 0;
    }
    // 查找，若存在，返回结点指针，若不存在，返回哨兵结点指针
    // 非递归实现
    btree_node<T> *find(const T &item)
    {
        return bstree_find(item, mp_root);
    }
    // 递归实现
    btree_node<T> *find_r(const T &item)
    {
        return bstree_find_r(item, mp_root);
    }
    // 返回最大值结点指针，若是空树，返回哨兵结点指针
    btree_node<T> *max()
    {
        return bstree_max(mp_root);
    }
    // 返回最小值结点指针，若是空树，返回哨兵结点指针
    btree_node<T> *min()
    {
        return bstree_min(mp_root);
    }
    // 返回结点p_node的后继结点，若p_node是最大值结点，返回哨兵结点
    // 假设p_node为有效结点
    btree_node<T> *successor(btree_node<T> *p_node)
	{
		return bstree_successor(p_node);
	}
    // 返回结点p_node的前驱结点，若p_node是最小值结点，返回哨兵结点
    // 假设p_node为有效结点
    btree_node<T> *predecessor(btree_node<T> *p_node)
	{
		return bstree_predecessor(p_node);
	}

private:
    btree_node<T> *mp_root; // 树根
    std::size_t m_size; 	// 节点的数目
    
	// 创建一个新结点，返回新结点指针
    btree_node<T> *create_node(btree_node<T> *p_parent, const T &item)
    {
        return new btree_node<T>(p_parent, sentinel_node(), sentinel_node(), item);
    }
    //向一棵树插入一个新结点，返回这棵树的根
    btree_node<T> *insert_r(const T &item, btree_node<T> *p_root);
    //从一棵树中删除一个元素，返回这棵树的根，递归实现
    btree_node<T> *erase_r(const T &item, btree_node<T> *p_root);
};
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
//向一棵树插入一个新结点，返回这棵树的根
// 非递归版本
template <typename T>
void bstree<T>::insert(const T &item)
{
    btree_node<T> *p_parent = sentinel_node(), *p_curr = mp_root;
    while (p_curr != sentinel_node())
    {
        p_parent = p_curr;
        if (item == p_curr->m_item)
            return;
        else if (item < p_curr->m_item)
            p_curr = p_curr->mp_left;
        else
            p_curr = p_curr->mp_right;
    }

    ++m_size;
    btree_node<T> *p_new_node = create_node(p_parent, item);
    if (p_parent == sentinel_node())
        mp_root = p_new_node;
    else if (item < p_parent->m_item)
        p_parent->mp_left = p_new_node;
    else
        p_parent->mp_right = p_new_node;
}
// 递归版本
template <typename T>
btree_node<T> *bstree<T>::insert_r(const T &item, btree_node<T> *t)
{
    if (t == sentinel_node())
    {
        t = create_node(sentinel_node(), item);
        ++m_size;
    }
    else if (item < t->m_item)
    {
        t->mp_left = insert_r(item, t->mp_left);
        t->mp_left->mp_parent = t;
    }
    else if (t->m_item < item)
    {
        t->mp_right = insert_r(item, t->mp_right);
        t->mp_right->mp_parent = t;
    }
    return t;
}

// 删除结点p_node
// 假设p_node为有效结点
template <typename T>
void bstree<T>::erase(btree_node<T> *p_node)
{
    // 若p_node没有儿子，删除p_node
    // 若p_node只有一个儿子，将p_node的儿子与p_node的父亲相连，删除p_node
    // 若p_node有两个儿子，将p_node的后继的值赋值给p_node，删除p_node的后继
    btree_node<T> *p_erase_node;
    if (p_node->mp_left == sentinel_node() || p_node->mp_right == sentinel_node())
        p_erase_node = p_node;
    else
        p_erase_node = successor(p_node);
    
    // p_child是p_erase_node的非哨兵儿子，或p_erase_node无儿子时，被置为哨兵
    btree_node<T> *p_child;
    if (p_erase_node->mp_left != sentinel_node())
        p_child = p_erase_node->mp_left;
    else
        p_child = p_erase_node->mp_right;

    if (p_child != NULL) // 注意：不是哨兵
        p_child->mp_parent = p_erase_node->mp_parent;
    if (p_erase_node->mp_parent == sentinel_node())
        mp_root = p_child;
    else if (p_erase_node == p_erase_node->mp_parent->mp_left)
        p_erase_node->mp_parent->mp_left = p_child;
    else
        p_erase_node->mp_parent->mp_right = p_child;

    if (p_erase_node != p_node)
        p_node->m_item = p_erase_node->m_item;
    
    delete p_erase_node;
    --m_size;
}
//从一棵树中删除一个元素，返回这棵树的根
// 递归版本
template <typename T>
btree_node<T> *bstree<T>::erase_r(const T &item, btree_node<T> *t)
{
    if (t == sentinel_node())
        return sentinel_node();

    if (item < t->m_item)
    {
        t->mp_left = erase_r(item, t->mp_left);
        if (t->mp_left != NULL) // 注意：不是哨兵
            t->mp_left->mp_parent = t;
    }
    else if (t->m_item < item)
    {
        t->mp_right = erase_r(item, t->mp_right);
        if (t->mp_right != NULL) // 注意：不是哨兵
            t->mp_right->mp_parent = t;
    }
    else
    {
        erase(t);
    }
    return t;
}

}

#endif
