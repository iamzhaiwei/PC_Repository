// rb_tree.h
//
// last-edit-by: <> 
//
// Description:
// 红黑树
//////////////////////////////////////////////////////////////////////

#ifndef RB_TREE_H
#define RB_TREE_H 1

#include <cstddef>
#include <iostream>

namespace zhaiwei
{

// 结点颜色
enum color_type {RED, BLACK};

// 红黑树结点
template <typename T>
class rb_tree_node
{
public:
    rb_tree_node(color_type color = BLACK, rb_tree_node<T> *p_left = NULL,
                 rb_tree_node<T> *p_right = NULL, rb_tree_node<T> *p_parent = NULL,
                 const T &item = T()):
        m_color(color), mp_left(p_left), mp_right(p_right), mp_parent(p_parent),
        m_item(item)
    {}
    
    color_type m_color;
    rb_tree_node<T> *mp_left;
    rb_tree_node<T> *mp_right;
    rb_tree_node<T> *mp_parent;
    T m_item;
};

// 重载输出操作符
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const rb_tree_node<T> &node)
{
    ostr << node.m_item
         << ((RED==node.m_color)? "(RED)": "(BLACK)");
    return ostr;
}

// 红黑树
template <typename T>
class rb_tree:: public bstree<T>
{
private:
    // NIL结点
    static rb_tree_node<T> m_NIL;
public:
    static rb_tree_node<T> *NIL() {return &m_NIL;}
public:
    // 构造函数
    rb_tree():
        mp_root(&m_NIL), m_size(0)
    {}
    // 析构函数
    ~rb_tree() { clear(); }

    bool empty() const { return m_size == 0; }
    int size() const { return m_size; }
    rb_tree_node<T> *get_root() const { return mp_root; }
    
    // 插入
    void insert(const T &item);
    // 删除结点p_node
    // 假设p_node为有效结点
    void erase(rb_tree_node<T> *p_node);
    // 删除
    void erase(const T &item)
    {
        rb_tree_node<T> *p_node = find(item);
        if (p_node != &m_NIL)
            erase(p_node);
    }
   
private:
    rb_tree_node<T> *mp_root;
    int m_size;

    // 左旋转，假设p_node->mp_right不等于NIL
    void left_rotate(rb_tree_node<T> *p_node);
    // 右旋转，假设p_node->mp_left不等于NIL
    void right_rotate(rb_tree_node<T> *p_node);
    // 插入修正
    void insert_fixup(rb_tree_node<T> *p_node);
    // 删除修正
    void erase_fixup(rb_tree_node<T> *p_node);
};

template <typename T>
rb_tree_node<T> rb_tree<T>::m_NIL = rb_tree_node<T>();

// 插入
template <typename T>
void rb_tree<T>::insert(const T &item)
{
    rb_tree_node<T> *p_parent = &m_NIL, *p_curr = mp_root;
    while (p_curr != &m_NIL)
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
    rb_tree_node<T> *p_new_node = new rb_tree_node<T>(RED, &m_NIL, &m_NIL, p_parent, item);
    if (p_parent == &m_NIL)
        mp_root = p_new_node;
    else if (item < p_parent->m_item)
        p_parent->mp_left = p_new_node;
    else
        p_parent->mp_right = p_new_node;

    insert_fixup(p_new_node);
}

// 删除结点p_node
// 假设p_node为有效结点
template <typename T>
void rb_tree<T>::erase(rb_tree_node<T> *p_node)
{
    // 若p_node没有儿子，删除p_node
    // 若p_node只有一个儿子，将p_node的儿子与p_node的父亲相连，删除p_node
    // 若p_node有两个儿子，将p_node的后继的值赋值给p_node，删除p_node的后继
    rb_tree_node<T> *p_erase_node;
    if (p_node->mp_left == &m_NIL || p_node->mp_right == &m_NIL)
        p_erase_node = p_node;
    else
        p_erase_node = successor(p_node);
    
    // p_child是p_erase_node的非NULL儿子，或p_erase_node无儿子时，被置为NULL
    rb_tree_node<T> *p_child;
    if (p_erase_node->mp_left != &m_NIL)
        p_child = p_erase_node->mp_left;
    else
        p_child = p_erase_node->mp_right;
    
    p_child->mp_parent = p_erase_node->mp_parent;
    if (p_erase_node->mp_parent == &m_NIL)
        mp_root = p_child;
    else if (p_erase_node == p_erase_node->mp_parent->mp_left)
        p_erase_node->mp_parent->mp_left = p_child;
    else
        p_erase_node->mp_parent->mp_right = p_child;

    if (p_erase_node != p_node)
        p_node->m_item = p_erase_node->m_item;

    if (p_erase_node->m_color == BLACK)
        erase_fixup(p_child);
    delete p_erase_node;
    --m_size;
}



// 左旋转，假设x->mp_right不等于NIL
template <typename T>
void rb_tree<T>::left_rotate(rb_tree_node<T> *x)
{
    rb_tree_node<T> *y = x->mp_right;
    x->mp_right = y->mp_left;
    if (y->mp_left != &m_NIL)
        y->mp_left->mp_parent = x;
    y->mp_parent = x->mp_parent;
    if (x->mp_parent == &m_NIL)
        mp_root = y;
    else if (x->mp_parent->mp_left == x)
        x->mp_parent->mp_left = y;
    else
        x->mp_parent->mp_right = y;
    y->mp_left = x;
    x->mp_parent = y;
}

// 右旋转，假设y->mp_left不等于NIL
template <typename T>
void rb_tree<T>::right_rotate(rb_tree_node<T> *y)
{
    rb_tree_node<T> *x = y->mp_left;
    y->mp_left = x->mp_right;
    if (x->mp_right != &m_NIL)
        x->mp_right->mp_parent = y;
    x->mp_parent = y->mp_parent;
    if (y->mp_parent == &m_NIL)
        mp_root = x;
    else if (y->mp_parent->mp_left == y)
        y->mp_parent->mp_left = x;
    else
        y->mp_parent->mp_right = x;
    x->mp_right = y;
    y->mp_parent = x;
}

// 插入修正
template <typename T>
void rb_tree<T>::insert_fixup(rb_tree_node<T> *p_node)
{
    while (RED == p_node->mp_parent->m_color)
    {
        // 祖父结点
        rb_tree_node<T> *p_grandfather = p_node->mp_parent->mp_parent;
        if (p_node->mp_parent == p_grandfather->mp_left)
        {// 当前结点的父亲是当前结点的祖父的左儿子
            rb_tree_node<T> *p_uncle = p_grandfather->mp_right;
            if (RED == p_uncle->m_color)
            {// 叔叔是红色
                p_node->mp_parent->m_color = BLACK;
                p_uncle->m_color = BLACK;
                p_grandfather->m_color = RED;
                p_node = p_grandfather;
            }
            else // 叔叔是黑色
            {
                if (p_node == p_node->mp_parent->mp_right)
                {// 当前结点是右儿子
                    p_node = p_node->mp_parent;
                    p_grandfather = p_node->mp_parent->mp_parent;
                    left_rotate(p_node);
                    // 将“新”当前结点转化为左儿子
                }
                // 当前结点是左儿子
                p_node->mp_parent->m_color = BLACK;
                p_grandfather->m_color = RED;
                right_rotate(p_grandfather);
            }
        }
        else // 当前结点的父亲是当前结点的祖父的右儿子
        {
            rb_tree_node<T> *p_uncle = p_grandfather->mp_left;
            if (RED == p_uncle->m_color)
            {// 叔叔是红色
                p_node->mp_parent->m_color = BLACK;
                p_uncle->m_color = BLACK;
                p_grandfather->m_color = RED;
                p_node = p_grandfather;
            }
            else // 叔叔是黑色
            {
                if (p_node == p_node->mp_parent->mp_left)
                {// 当前结点是左儿子
                    p_node = p_node->mp_parent;
                    p_grandfather = p_node->mp_parent->mp_parent;
                    right_rotate(p_node);
                    // 将“新”当前结点转化为右儿子
                }
                // 当前结点是右儿子
                p_node->mp_parent->m_color = BLACK;
                p_grandfather->m_color = RED;
                left_rotate(p_grandfather);
            }
        }
    }
    mp_root->m_color = BLACK;
}

// 删除修正
template <typename T>
void rb_tree<T>::erase_fixup(rb_tree_node<T> *p_node)
{
    while (p_node != mp_root && p_node->m_color == BLACK)
    {
        if (p_node == p_node->mp_parent->mp_left)
        {// 当前结点是其父亲的左儿子
            rb_tree_node<T> *p_brother = p_node->mp_parent->mp_right;
            if (p_brother->m_color == RED)
            {// 兄弟是红色
                p_brother->m_color = BLACK;
                p_node->mp_parent->m_color = RED;
                left_rotate(p_node->mp_parent);
                p_brother = p_node->mp_parent->mp_right;
            }
            // 兄弟是黑色
            if (p_brother->mp_left->m_color == BLACK && p_brother->mp_right->m_color == BLACK)
            {// 兄弟的两个儿子都是黑色
                p_brother->m_color = RED;
                p_node = p_node->mp_parent;
            }
            else
            {
                if (p_brother->mp_right->m_color == BLACK)
                {// 兄弟的左儿子是红色，右儿子是黑色
                    p_brother->mp_left->m_color = BLACK;
                    p_brother->m_color = RED;
                    right_rotate(p_brother);
                    p_brother = p_node->mp_parent->mp_right;
                }
                // 兄弟的右儿子是红色
                p_brother->m_color = p_node->mp_parent->m_color;
                p_node->mp_parent->m_color = BLACK;
                p_brother->mp_right->m_color = BLACK;
                left_rotate(p_node->mp_parent);
                p_node = mp_root;
            }
        }
        else // 当前结点是其父亲的右儿子
        {
            rb_tree_node<T> *p_brother = p_node->mp_parent->mp_left;
            if (p_brother->m_color == RED)
            {// 兄弟是红色
                p_brother->m_color = BLACK;
                p_node->mp_parent->m_color = RED;
                right_rotate(p_node->mp_parent);
                p_brother = p_node->mp_parent->mp_left;
            }
            // 兄弟是黑色
            if (p_brother->mp_left->m_color == BLACK && p_brother->mp_right->m_color == BLACK)
            {// 兄弟的两个儿子都是黑色
                p_brother->m_color = RED;
                p_node = p_node->mp_parent;
            }
            else
            {
                if (p_brother->mp_left->m_color == BLACK)
                {// 兄弟的左儿子是黑色，右儿子是红色
                    p_brother->mp_right->m_color = BLACK;
                    p_brother->m_color = RED;
                    left_rotate(p_brother);
                    p_brother = p_node->mp_parent->mp_left;
                }
                // 兄弟的左儿子是红色
                p_brother->m_color = p_node->mp_parent->m_color;
                p_node->mp_parent->m_color = BLACK;
                p_brother->mp_left->m_color = BLACK;
                right_rotate(p_node->mp_parent);
                p_node = mp_root;
            }
        }
    }
    p_node->m_color = BLACK;
}

// 前序遍历
template <typename T>
void preorder_traversal(rb_tree_node<T> *p_node)
{
    if (p_node != rb_tree<T>::NIL())
    {
        std::cout << *p_node << " ";
        preorder_traversal(p_node->mp_left);
        preorder_traversal(p_node->mp_right);
    }
}

// 中序遍历
template <typename T>
void inorder_traversal(rb_tree_node<T> *p_node)
{
    if (p_node != rb_tree<T>::NIL())
    {
        inorder_traversal(p_node->mp_left);
        std::cout << *p_node << " ";
        inorder_traversal(p_node->mp_right);
    }
}

// 后序遍历
template <typename T>
void postorder_traversal(rb_tree_node<T> *p_node)
{
    if (p_node != rb_tree<T>::NIL())
    {
        postorder_traversal(p_node->mp_left);
        postorder_traversal(p_node->mp_right);
        std::cout << *p_node << " ";
    }
}

}


#endif // RB_TREE_H
//////////////////////////////////////////////////////////////////////
