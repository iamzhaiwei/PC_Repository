// btree.h
//
// last-edit-by: <>
// 2012-06-18 丁宅伟
//
// Description:
// 二叉树
//////////////////////////////////////////////////////////////////////

#ifndef BTREE_H
#define BTREE_H 1

#include <cstddef>
#include <iostream>
#include <queue>
#include <stack>

namespace zhaiwei
{

// 二叉树结点
template <typename T>
class btree_node
{
public:
    explicit btree_node(btree_node<T> *parent, btree_node<T> *left, btree_node<T> *right,
                        const T &item):
        mp_parent(parent), mp_left(left), mp_right(right), m_item(item)
    {}
    virtual ~btree_node()
    {}

    btree_node<T> *mp_parent;
    btree_node<T> *mp_left;
    btree_node<T> *mp_right;
    T m_item;
};

// 重载输出操作符
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const btree_node<T> &node)
{
    ostr << node.m_item;
    return ostr;
}

// 先序遍历
template <typename T>
void preorder_traversal(std::ostream &ostr, btree_node<T> *t, btree_node<T> *sentinel_node = NULL)
{
    if (t == sentinel_node)
        return;

    ostr << *t << ' ';
    preorder_traversal(ostr, t->mp_left, sentinel_node);
    preorder_traversal(ostr, t->mp_right, sentinel_node);
}

// 先序遍历，非递归
template <typename T>
void preorder_traversal_nonrecursion(std::ostream &ostr, btree_node<T> *t, btree_node<T> *sentinel_node = NULL)
{
    std::stack< btree_node<T> *> st;
    btree_node<T> *p_curr = t;
    while (!st.empty() || p_curr != sentinel_node)
    {
        if (p_curr != sentinel_node)
        {
            ostr << *p_curr << ' ';
            st.push(p_curr);
            p_curr = p_curr->mp_left;
        }
        else
        {
            p_curr = st.top()->mp_right;
            st.pop();
        }
    }
}

// 中序遍历
template <typename T>
void inorder_traversal(std::ostream &ostr, btree_node<T> *t, btree_node<T> *sentinel_node = NULL)
{
    if (t == sentinel_node)
        return;

    inorder_traversal(ostr, t->mp_left, sentinel_node);
    ostr << *t << ' ';
    inorder_traversal(ostr, t->mp_right, sentinel_node);
}

// 中序遍历，非递归
template <typename T>
void inorder_traversal_nonrecursion(std::ostream &ostr, btree_node<T> *t, btree_node<T> *sentinel_node = NULL)
{
	std::stack< btree_node<T> * > st;
	btree_node<T> *p_curr = t;
	while (!st.empty() || p_curr != sentinel_node)
	{
		if (p_curr != sentinel_node)
		{
			st.push(p_curr);
			p_curr = p_curr->mp_left;
		}
		else
		{
			p_curr = st.top();
			st.pop();
			ostr << *p_curr << ' ';
			p_curr = p_curr->mp_right;
		}
	}
}

// 后序遍历
template <typename T>
void postorder_traversal(std::ostream &ostr, btree_node<T> *t, btree_node<T> *sentinel_node = NULL)
{
    if (t == sentinel_node)
        return;

    postorder_traversal(ostr, t->mp_left, sentinel_node);
    postorder_traversal(ostr, t->mp_right, sentinel_node);
    ostr << *t << ' ';
}

// 标记类型，标记便利当前节点时，要遍历它的左子树还是右子树
enum tag_type {L, R};

// 后序遍历，非递归
template <typename T>
void postorder_traversal_nonrecursion(std::ostream &ostr, btree_node<T> *t, btree_node<T> *sentinel_node = NULL)
{
	std::stack< btree_node<T> * > node_st;
	std::stack<tag_type> type_st;

	btree_node<T> *p_curr = t;
	tag_type curr_type;
	while (!node_st.empty() || p_curr != sentinel_node)
	{
		if (p_curr != sentinel_node) // 第一次遍历到当前节点
		{
			node_st.push(p_curr); 	// 保存节点指针
			type_st.push(L);		// 要遍历左子树
			p_curr = p_curr->mp_left;
		}
		else
		{
			p_curr = node_st.top();
			node_st.pop();
			curr_type = type_st.top();
			type_st.pop();
			if (curr_type == L) 	// 当前节点的左子树已遍历结束，
			{
				node_st.push(p_curr);
				type_st.push(R);	// 再遍历右子树
				p_curr = p_curr->mp_right;
			}
			else if (curr_type == R)// 当前节点的右子树已遍历结束，
			{
				ostr << *p_curr << ' ';	// 最后遍历节点自身
				p_curr = sentinel_node;
			}
		}
	}
}

// 层序遍历
template <typename T>
void levelorder_traversal(std::ostream &ostr, btree_node<T> *root, btree_node<T> *sentinel_node = NULL)
{
    std::queue< btree_node<T> *> q;

    if (root != sentinel_node)
    {
        q.push(root);
        q.push(sentinel_node);
    }

    btree_node<T> *p_curr = sentinel_node;
    while (!q.empty())
    {
        p_curr = q.front();
        q.pop();

        if (p_curr != sentinel_node)
        {
            ostr << *p_curr << " ";

            if (p_curr->mp_left != sentinel_node)
                q.push(p_curr->mp_left);
            if (p_curr->mp_right != sentinel_node)
                q.push(p_curr->mp_right);

            // 当前层的结点已全部输出，下一层的结点已全部进入队列，压入sentinel_node
            if (q.front() == sentinel_node)
                q.push(sentinel_node);
        }
        else
            ostr << std::endl;
    }
}


// 从左到右输出二叉树中某一层的结点。根结点为第0层。
// 成功返回1,失败返回0
template <typename T>
int print_node_at_level(btree_node<T> *root, int level)
{
    if (root == NULL || level < 0)
        return 0;

    if (level == 0)
    {
        std::cout << *root << " ";
        return 1;
    }
    else
    {
        return print_node_at_level(root->mp_left, level-1) +
            print_node_at_level(root->mp_right, level-1);
    }
}


// 按深度从下到上，从左到右输出二叉树每层的结点
template <typename T>
void print_node_by_depth_from_left_to_right(btree_node<T> *root)
{
    if (root == NULL)
        return;

    std::queue< btree_node<T> *> q;
    std::stack< btree_node<T> *> st;
    btree_node<T> *p_curr;

    q.push(root);
    q.push(NULL);
    while (!q.empty())
    {
        p_curr = q.front();
        q.pop();
        st.push(p_curr);
        if (p_curr != NULL)
        {
            if (p_curr->mp_right != NULL)
                q.push(p_curr->mp_right);
            if (p_curr->mp_left != NULL)
                q.push(p_curr->mp_left);
            if (q.front() == NULL)
                q.push(NULL);
        }
    }

    while (!st.empty())
    {
        p_curr = st.top();
        st.pop();
        if (p_curr != NULL)
            std::cout << *p_curr << " ";
        else
            std::cout << std::endl;
    }
    std::cout << std::endl;
}


// 按深度从下到上，从右到左输出二叉树每层的结点
template <typename T>
void print_node_by_depth_from_right_to_left(btree_node<T> *root)
{
    if (root == NULL)
        return;

    std::queue< btree_node<T> *> q;
    std::stack< btree_node<T> *> st;
    btree_node<T> *p_curr;

    q.push(root);
    q.push(NULL);
    while (!q.empty())
    {
        p_curr = q.front();
        q.pop();
        st.push(p_curr);
        if (p_curr != NULL)
        {
            if (p_curr->mp_left != NULL)
                q.push(p_curr->mp_left);
            if (p_curr->mp_right != NULL)
                q.push(p_curr->mp_right);
            if (q.front() == NULL)
                q.push(NULL);
        }
    }

    while (!st.empty())
    {
        p_curr = st.top();
        st.pop();
        if (p_curr != NULL)
            std::cout << *p_curr << " ";
        else
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

}

#endif
