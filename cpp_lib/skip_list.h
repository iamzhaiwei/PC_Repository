// skip_list.h
//
// last-edit-by: <> 
// 2012-06-06
// Description:
// 跳跃表
//////////////////////////////////////////////////////////////////////

#ifndef SKIP_LIST_H
#define SKIP_LIST_H 1

#include <cstdlib>
#include <iostream>

namespace zhaiwei
{

// 跳跃表结点
template <typename T>
class skip_list_node
{
public:
    skip_list_node(const T &item = T(), int level = 1):
        m_item(item), m_level(level), m_forward(NULL)
    {
        m_forward = new skip_list_node*[m_level];
    }
    ~skip_list_node()
    {
        delete [] m_forward;
    }
    
    T m_item;
    int m_level; // 结点的阶数
    skip_list_node **m_forward; // 指向前项结点的指针数组
private:
    skip_list_node(const skip_list_node &);
    skip_list_node &operator=(const skip_list_node &);
};
// 对跳跃表结点重载输出操作符<<
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const skip_list_node<T> &node)
{
    ostr << node.m_item << "(" << node.m_level << ")";
    return ostr;
}

// 跳跃表
template <typename T>
class skip_list
{
public:
    template <typename Q>
    friend std::ostream &operator<<(std::ostream &, const skip_list<Q> &);
public:
    skip_list():
        mp_header(new skip_list_node<T>(T(), random_level())), m_size(0),
        m_update_node(new skip_list_node<T>*[m_max_level]), m_update_node_cnt(0)
    {}
    
    ~skip_list()
    {
        clear();
        delete mp_header;
        delete [] m_update_node;
    }

    bool empty() const
    {
        return m_size == 0;
    }
    int size() const
    {
        return m_size;
    }

    // 查找，若存在，返回其指针，若不存在，返回NULL
    skip_list_node<T> *find(const T &item);
    // 插入，若元素已存在，返回其指针，若不存在，插入新结点，返回其指针
    skip_list_node<T> *insert(const T &item);
    // 删除
    void erase(const T &item);
    // 清空
    void clear();
private:
    static double m_prob_factor; // 概率因子
    static int m_max_level; // 结点的最大阶数
    // 计算结点的随机阶数
    static int random_level();
private:
    skip_list_node<T> *mp_header; // 头结点，不包含有效元素值
    int m_size; // 有效元素的数目
    skip_list_node<T> **m_update_node; // 要更新的结点指针数组，用于insert()、erase()
    int m_update_node_cnt; // 要更新的结点数目
    
    // 查找给定元素，存在或不存在，返回给定结点应在位置的前一结点的指针，
    // 并更新结点指针数组m_update_node
    skip_list_node<T> *find_update(const T &item);
};

// 概率因子
template <typename T>
double skip_list<T>::m_prob_factor = 0.5;

// 结点的最大阶数
template <typename T>
int skip_list<T>::m_max_level = 15;

// 计算结点的随机阶数
template <typename T>
int skip_list<T>::random_level()
{
    int level = 1;
    while (rand() / double(RAND_MAX) > m_prob_factor && level < m_max_level)
        ++level;
    return level;
}

// 查找给定元素，无论存在或不存在，返回给定结点应在位置的前一结点的指针，
// 并更新结点指针数组m_update_node和m_update_node_cnt
template <typename T>
skip_list_node<T> *skip_list<T>::find_update(const T &item)
{
    skip_list_node<T> *p_node = mp_header;
    for (int i = 0; i < m_max_level; ++i)
        m_update_node[i] = NULL;
    m_update_node_cnt = 0;
    while (true)
    {
        int i;
        for (i = p_node->m_level-1; i >= 0; --i)
        {
            if (p_node->m_forward[i] == NULL || item <= p_node->m_forward[i]->m_item)
            {
                m_update_node[i] = p_node;
                ++m_update_node_cnt;
            }
            else
            {
                p_node = p_node->m_forward[i];
                break;
            }
        }
        if (i < 0)
            break;
    }
    return p_node;
}

// 查找，若存在，返回其指针，若不存在，返回NULL
template <typename T>
skip_list_node<T> *skip_list<T>::find(const T &item)
{
    skip_list_node<T> *p_node = find_update(item);
    if (p_node->m_forward[0] == NULL || p_node->m_forward[0]->m_item != item)
        return NULL;
    else
        return p_node->m_forward[0];
}

// 插入，若元素已存在，返回其指针，若不存在，插入新结点，返回其指针
template <typename T>
skip_list_node<T> *skip_list<T>::insert(const T &item)
{
    skip_list_node<T> *p_node = find_update(item);
    if (p_node->m_forward[0] == NULL || p_node->m_forward[0]->m_item != item)
    {
        skip_list_node<T> *p_new_node = new skip_list_node<T>(item, random_level());
        for (int i = 0; i < p_new_node->m_level && i < m_update_node_cnt; ++i)
        {
            p_new_node->m_forward[i] = m_update_node[i]->m_forward[i];
            m_update_node[i]->m_forward[i] = p_new_node;
        }
        ++m_size;
    }
    return p_node->m_forward[0];
}

// 删除
template <typename T>
void skip_list<T>::erase(const T &item)
{
    skip_list_node<T> *p_node = find_update(item);
    if (p_node->m_forward[0] != NULL && p_node->m_forward[0]->m_item == item)
    {
        skip_list_node<T> *p_erase_node = p_node->m_forward[0];
        for (int i = 0; i < p_erase_node->m_level && i < m_update_node_cnt; ++i)
        {
            m_update_node[i]->m_forward[i] = p_erase_node->m_forward[i];
        }
        delete p_erase_node;
        --m_size;
    }
}

// 清空
template <typename T>
void skip_list<T>::clear()
{
    skip_list_node<T> *p_curr, *p_next;
    p_curr = mp_header->m_forward[0];
    while (p_curr != NULL)
    {
        p_next = p_curr->m_forward[0];
        delete p_curr;
        p_curr = p_next;
    }
    for (int i = 0; i < mp_header->m_level; ++i)
        mp_header->m_forward[i] = NULL;
    m_size = 0;
}

// 对跳跃表重载输出操作符<<
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const skip_list<T> &l)
{
    skip_list_node<T> *p_node = l.mp_header;
    while (p_node != NULL)
    {
        ostr << *p_node << " ";
        p_node = p_node->m_forward[0];
    }
    return ostr;
}

}

#endif // SKIP_LIST_H
//////////////////////////////////////////////////////////////////////
