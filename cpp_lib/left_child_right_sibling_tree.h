// left_child_right_sibling_tree.h
//
// last-edit-by: <> 
//
// Description:
// 左孩子、右兄弟表示有根树
//////////////////////////////////////////////////////////////////////

#ifndef LEFT_CHILD_RIGHT_SIBLING_TREE_H
#define LEFT_CHILD_RIGHT_SIBLING_TREE_H 1

#include <iostream>

namespace zhaiwei
{

// 树的结点
template <typename T>
class lcrs_tree_node
{
public:
    explicit lcrs_tree_node(const T &item = T(), lcrs_tree_node<T> *parent = NULL, lcrs_tree_node<T> *left = NULL,
                            lcrs_tree_node<T> *right = NULL):
        m_item(item), mp_parent(parent), mp_left_child(left), mp_right_sibling(right)
    {}
    
    T m_item;
    lcrs_tree_node<T> *mp_parent;
    lcrs_tree_node<T> *mp_left_child;
    lcrs_tree_node<T> *mp_right_sibling;
};

// 树
template <typename T>
class left_child_right_sibling_tree
{
public:
    left_child_right_sibling_tree():
        mp_root(NULL), m_size(0)
    {}
    ~left_child_right_sibling_tree()
    {
        clear(mp_root);
    }

    bool empty() const
    {
        return m_size == 0;
    }
    int size() const
    {
        return m_size;
    }

    lcrs_tree_node<T> *get_root()
    {
        return mp_root;
    }
    lcrs_tree_node<T> *set_root(lcrs_tree_node<T> *p_new_root)
    {
        mp_root = clear(mp_root);
        mp_root = p_new_root;
        m_size = 1;
        return mp_root;
    }

    // 插入一个元素作为根结点，清空原来的树，返回根结点的指针
    lcrs_tree_node<T> *insert_root(const T &);
    // 插入一个元素作为给定结点的左孩子，给定结点的原左孩子成为新元素结点的右兄弟，返回新元素结点的指针
    lcrs_tree_node<T> *insert_left_child(const T &, lcrs_tree_node<T> *);
    // 插入一个元素作为给定结点的右兄弟，给定结点的原右兄弟成为新元素结点的右兄弟，返回新元素结点的指针
    lcrs_tree_node<T> *insert_right_sibling(const T &, lcrs_tree_node<T> *);
    
    // 清空树
    void clear()
    {
        mp_root = clear(mp_root);
        m_size = 0;
    }

    // 先序遍历
    void preorder_traversal(std::ostream &ostr)
    {
        preorder_traversal(ostr, mp_root);
    }
    // 中序遍历
    void inorder_traversal(std::ostream &ostr)
    {
        inorder_traversal(ostr, mp_root);
    }
    // 后序遍历
    void postorder_traversal(std::ostream &ostr)
    {
        postorder_traversal(ostr, mp_root);
    }
private:
    lcrs_tree_node<T> *mp_root;
    int m_size;

    // 清空一颗树
    lcrs_tree_node<T> *clear(lcrs_tree_node<T> *);
    // 先序遍历
    void preorder_traversal(std::ostream &, lcrs_tree_node<T> *);
    // 中序遍历
    void inorder_traversal(std::ostream &, lcrs_tree_node<T> *);
    // 后序遍历
    void postorder_traversal(std::ostream &, lcrs_tree_node<T> *);
    
    left_child_right_sibling_tree(const left_child_right_sibling_tree<T> &);
    left_child_right_sibling_tree<T> &operator=(const left_child_right_sibling_tree<T> &);
};

template <typename T>
lcrs_tree_node<T> *left_child_right_sibling_tree<T>::insert_root(const T &item)
{
    if (mp_root != NULL)
        mp_root = clear(mp_root);

    mp_root = new lcrs_tree_node<T>(item);
    m_size = 1;
    return mp_root;
}

template <typename T>
lcrs_tree_node<T> *left_child_right_sibling_tree<T>::insert_left_child(const T &item, lcrs_tree_node<T> *p_node)
{
    if (p_node == NULL)
        return NULL;
    lcrs_tree_node<T> *p_new_node = new lcrs_tree_node<T>(item, p_node, NULL, p_node->mp_left_child);
    ++m_size;
    p_node->mp_left_child = p_new_node;
    return p_new_node;
}

template <typename T>
lcrs_tree_node<T> *left_child_right_sibling_tree<T>::insert_right_sibling(const T &item, lcrs_tree_node<T> *p_node)
{
    if (p_node == NULL)
        return NULL;

    lcrs_tree_node<T> *p_new_node = new lcrs_tree_node<T>(item, p_node->mp_parent, NULL, p_node->mp_right_sibling);
    ++m_size;
    p_node->mp_right_sibling = p_new_node;
    return p_new_node;
}

template <typename T>
lcrs_tree_node<T> *left_child_right_sibling_tree<T>::clear(lcrs_tree_node<T> *p_node)
{
    if (p_node == NULL)
        return NULL;

    // 先清空左孩子，再清空右兄弟，最后清空自身
    if (p_node->mp_left_child != NULL)
    {
        p_node->mp_left_child = clear(p_node->mp_left_child);
    }
    if (p_node->mp_right_sibling != NULL)
    {
        p_node->mp_right_sibling = clear(p_node->mp_right_sibling);
    }
    delete p_node;
    return NULL;
}

template <typename T>
void left_child_right_sibling_tree<T>::preorder_traversal(std::ostream &ostr, lcrs_tree_node<T> *p_node)
{
    if (p_node == NULL)
        return;

    ostr << p_node->m_item << " ";
    preorder_traversal(ostr, p_node->mp_left_child);
    preorder_traversal(ostr, p_node->mp_right_sibling);
}

template <typename T>
void left_child_right_sibling_tree<T>::inorder_traversal(std::ostream &ostr, lcrs_tree_node<T> *p_node)
{
    if (p_node == NULL)
        return;
    
    inorder_traversal(ostr, p_node->mp_left_child);
    ostr << p_node->m_item << " ";
    inorder_traversal(ostr, p_node->mp_right_sibling);
}

template <typename T>
void left_child_right_sibling_tree<T>::postorder_traversal(std::ostream &ostr, lcrs_tree_node<T> *p_node)
{
    if (p_node == NULL)
        return;
    
    postorder_traversal(ostr, p_node->mp_left_child);
    postorder_traversal(ostr, p_node->mp_right_sibling);
    ostr << p_node->m_item << " ";
}

}



#endif // LEFT_CHILD_RIGHT_SIBLING_TREE_H
//////////////////////////////////////////////////////////////////////
