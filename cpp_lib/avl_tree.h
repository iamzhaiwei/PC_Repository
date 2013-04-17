// avl_tree.h
//
// last-edit-by: <> 
//
// Description:
// AVL树
//////////////////////////////////////////////////////////////////////

#ifndef AVL_TREE_H
#define AVL_TREE_H 1

#include <algorithm>
#include <iostream>
#include "btree.h"
#include "bstree.h"

namespace zhaiwei
{
// AVL树结点
template <typename T>
class avl_tree_node: public btree_node<T>
{
public:
    avl_tree_node(btree_node<T> *parent, btree_node<T> *left, btree_node<T> *right,
                  const T &item, int height):
        btree_node<T>(parent, left, right, item), m_height(height)
    {}
    
    int m_height;
};

// 重载输出操作符
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const avl_tree_node<T> &node)
{
    ostr << node.m_item << "(" << node.m_height << ")";
    return ostr;
}

// AVL树
template <typename T>
class avl_tree: public bstree<T>
{
public:
    // 返回哨兵结点指针
    static btree_node<T> *sentinel_node()
    {
        return NULL;
    }
private:
    // 返回结点高度，若结点为哨兵结点，返回-1
    static int height(avl_tree_node<T> *p_node)
    {
        return (p_node)? p_node->m_height: -1;
    }
public:
    avl_tree():
        bstree<T>()
    {
        std::cout << "avl_tree ctor" << std::endl;
    }
    ~avl_tree()
    {
        std::cout << "avl_tree dtor" << std::endl;
    }
    // 插入一个新元素
    // 递归实现
    virtual void insert_r(const T &item)
    {
        bstree<T>::mp_root = insert_r(item, mp_root);
    }
private:
    // 创建一个新结点，返回新结点指针
    virtual avl_tree_node<T> *create_node(btree_node<T> *p_parent, const T &item)
    {
        return new avl_tree_node<T>(p_parent, sentinel_node(), sentinel_node(), item, 0);
    }
    //向一棵树插入一个新结点，返回这棵树的根
    virtual avl_tree_node<T> *insert_r(const T &item, btree_node<T> *p_root);
    //从一棵树中删除一个元素，返回这棵树的根，递归实现
    virtual avl_tree_node<T> *erase_r(const T &item, btree_node<T> *p_root);
    // 单右旋，只有p_node有左儿子时才可以调用，更新高度
    void single_right_rotate(avl_tree_node<T> *p_node);
    // 单左旋，只有p_node有右儿子时才可以调用，更新高度
    void single_left_rotate(avl_tree_node<T> *p_node);
    // 双右旋，更新高度
    // 对x结点的左儿子的右子树进行一次插入
    void double_right_rotate(avl_tree_node<T> *p_node)
    {
        single_left_rotate(dynamic_cast<avl_tree_node<T> *>(p_node->mp_left));
        single_right_rotate(dynamic_cast<avl_tree_node<T> *>(p_node));
    }
    // 双左旋，更新高度
    // 对x结点的右儿子的左子树进行一次插入
    void double_left_rotate(avl_tree_node<T> *p_node)
    {
        single_right_rotate(dynamic_cast<avl_tree_node<T> *>(p_node->mp_right));
        single_left_rotate(dynamic_cast<avl_tree_node<T> *>(p_node));
    }
private:
    // 插入新元素
    // 非递归实现
    virtual void insert(const T &item) {}
    // 删除元素
    // 非递归实现
    virtual void erase(const T &item) {}
    // 删除结点p_node, 假设p_node为有效结点，非递归实现
    virtual void erase(btree_node<T> *p_node) {}
};

//向一棵树插入一个新结点，返回这棵树的根
template <typename T>
avl_tree_node<T> *avl_tree<T>::insert_r(const T &item, btree_node<T> *p_btree_root)
{
    avl_tree_node<T> *p_root = dynamic_cast<avl_tree_node<T> *>(p_btree_root);
    if (p_root == sentinel_node())
    {
        p_root = create_node(sentinel_node(), item);
        ++this->m_size;
    }
    else if (item < p_root->m_item)
    {
        p_root->mp_left = insert_r(item, p_root->mp_left);
        p_root->mp_left->mp_parent = p_root;
        if (height(dynamic_cast<avl_tree_node<T> *>(p_root->mp_left)) -
            height(dynamic_cast<avl_tree_node<T> *>(p_root->mp_right)) == 2)
        {
            if (item < p_root->mp_left->m_item)
                single_right_rotate(dynamic_cast<avl_tree_node<T> *>(p_root));
            else
                double_right_rotate(dynamic_cast<avl_tree_node<T> *>(p_root));
        }
    }
    else if (p_root->m_item < item)
    {
        p_root->mp_right = insert_r(item, p_root->mp_right);
        p_root->mp_right->mp_parent = p_root;
        if (height(dynamic_cast<avl_tree_node<T> *>(p_root->mp_right)) -
            height(dynamic_cast<avl_tree_node<T> *>(p_root->mp_left)) == 2)
        {
            if (item < p_root->mp_right->m_item)
                double_left_rotate(dynamic_cast<avl_tree_node<T> *>(p_root));
            else
                single_left_rotate(dynamic_cast<avl_tree_node<T> *>(p_root));
        }
    }
    p_root->m_height = std::max(height(dynamic_cast<avl_tree_node<T> *>(p_root->mp_left)),
                                height(dynamic_cast<avl_tree_node<T> *>(p_root->mp_right))) + 1;
    return p_root;
}

//从一棵树中删除一个元素，返回这棵树的根，递归实现
template <typename T>
avl_tree_node<T> *avl_tree<T>::erase_r(const T &item, btree_node<T> *p_root)
{
    return NULL;
}

// 单右旋，只有p_node有左儿子时才可以调用，更新高度
// 对x结点的左儿子的左子树进行一次插入
template <typename T>
void avl_tree<T>::single_right_rotate(avl_tree_node<T> *p_node)
{
    avl_tree_node<T> *p_left = dynamic_cast<avl_tree_node<T> *>(p_node->mp_left);
    p_node->mp_left = p_left->mp_right;
    if (p_left->mp_right != NULL) // 注意：不是哨兵结点
        p_left->mp_right->mp_parent = p_node;
    p_left->mp_parent = p_node->mp_parent;
    if (p_node->mp_parent != NULL) // 注意：不是哨兵结点
    {
        if (p_node == p_node->mp_parent->mp_left)
            p_node->mp_parent->mp_left = p_left;
        else
            p_node->mp_parent->mp_right = p_left;
    }
    p_left->mp_right = p_node;
    p_node->mp_parent = p_left;

    p_node->m_height = std::max(height(dynamic_cast<avl_tree_node<T> *>(p_node->mp_left)),
                                height(dynamic_cast<avl_tree_node<T> *>(p_node->mp_right))) + 1;
    p_left->m_height = std::max(height(dynamic_cast<avl_tree_node<T> *>(p_left->mp_left)),
                                height(dynamic_cast<avl_tree_node<T> *>(p_left->mp_right))) + 1;
}

// 单左旋，只有p_node有右儿子时才可以调用，更新高度
// 对x结点的右儿子的右子树进行一次插入
template <typename T>
void avl_tree<T>::single_left_rotate(avl_tree_node<T> *p_node)
{
    avl_tree_node<T> *p_right = dynamic_cast<avl_tree_node<T> *>(p_node->mp_right);
    p_node->mp_right = p_right->mp_left;
    if (p_right->mp_left != NULL) // 注意：不是哨兵结点
        p_right->mp_left->mp_parent = p_node;
    p_right->mp_parent = p_node->mp_parent;
    if (p_node->mp_parent != NULL) // 注意：不是哨兵结点
    {
        if (p_node == p_node->mp_parent->mp_left)
            p_node->mp_parent->mp_left = p_right;
        else
            p_node->mp_parent->mp_right = p_right;
    }
    p_right->mp_left = p_node;
    p_node->mp_parent = p_right;

    p_node->m_height = std::max(height(dynamic_cast<avl_tree_node<T> *>(p_node->mp_left)),
                                height(dynamic_cast<avl_tree_node<T> *>(p_node->mp_right))) + 1;
    p_right->m_height = std::max(height(dynamic_cast<avl_tree_node<T> *>(p_right->mp_left)),
                                 height(dynamic_cast<avl_tree_node<T> *>(p_right->mp_right))) + 1;
}
}



#endif // AVL_TREE_H
//////////////////////////////////////////////////////////////////////
