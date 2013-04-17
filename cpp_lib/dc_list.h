// dc_list.h
//
// last-edit-by: <> 
//
// Description:
// 双向循环链表
//////////////////////////////////////////////////////////////////////

#ifndef DC_LIST_H
#define DC_LIST_H 1

#include <cstddef>
#include <iostream>

namespace zhaiwei
{

// 链表结点
template <typename T>
class dc_list_node
{
public:
    dc_list_node(const T &item = T(), dc_list_node<T> *p_front = NULL, dc_list_node<T> *p_next = NULL):
        m_item(item), mp_front(p_front), mp_next(p_next)
    {}
    
    T m_item;
    dc_list_node<T> *mp_front;
    dc_list_node<T> *mp_next;
private:
    dc_list_node(const dc_list_node<T> &);
    dc_list_node<T> &operator=(const dc_list_node<T> &);
};

// 链表
template <typename T>
class dc_list
{
public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &, const dc_list<U> &);
public:
    dc_list():
        mp_header(NULL), m_size(0)
    {
        mp_header = new dc_list_node<T>();
        mp_header->mp_next = mp_header;
        mp_header->mp_front = mp_header;
    }
    ~dc_list()
    {
        clear();
        delete mp_header;
    }
    dc_list(const dc_list<T> &);
    dc_list<T> &operator=(const dc_list<T> &);

    bool empty()
    {
        return m_size == 0;
    }
    int size()
    {
        return m_size;
    }
    // 在链表头部插入一新结点
    dc_list_node<T> *insert(const T &);
    // 从链表中删除给定元素值第一次出现的结点，若不存在，直接返回
    void erase(const T &);
    // 在链表中查找一给定元素值第一次出现的位置，若存在，返回其指针，若不存在，返回NULL
    dc_list_node<T> *find(const T &);
    // 清空链表
    void clear();

    // 返回表头
    dc_list_node<int> *get_head()
    {
        return mp_header;
    }
    // 返回第一个结点的指针，若链表为空，返回NULL
    dc_list_node<T> *get_first()
    {
        if (mp_header->mp_next == mp_header)
            return NULL;
        else
            return mp_header->mp_next;
    }
private:
    dc_list_node<T> *mp_header; // 链表空表头
    int m_size; // 元素数目
};

// 重载输出操作符
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const dc_list<T> &list)
{
    dc_list_node<T> *p_node = list.mp_header->mp_next;
    while (p_node != list.mp_header)
    {
        ostr << p_node->m_item << " ";
        p_node = p_node->mp_next;
    }
    return ostr;
}

// 在链表头部插入一新结点
template <typename T>
dc_list_node<T> *dc_list<T>::insert(const T &item)
{
    dc_list_node<T> *p_new_node = new dc_list_node<T>(item);
    dc_list_node<T> *p_next = mp_header->mp_next;
    p_new_node->mp_front = mp_header;
    mp_header->mp_next = p_new_node;
    p_new_node->mp_next = p_next;
    p_next->mp_front = p_new_node;
    ++m_size;
    return p_new_node;
}

// 从链表中删除给定元素值第一次出现的结点，若不存在，直接返回
template <typename T>
void dc_list<T>::erase(const T &item)
{
    dc_list_node<T> *p_node = find(item);
    if (p_node == NULL)
        return;
    dc_list_node<T> *p_next = p_node->mp_next;
    dc_list_node<T> *p_front = p_node->mp_front;
    p_front->mp_next = p_next;
    p_next->mp_front = p_front;
    delete p_node;
    --m_size;
}

// 在链表中查找一给定元素值第一次出现的位置，若存在，返回其指针，若不存在，返回NULL
template <typename T>
dc_list_node<T> *dc_list<T>::find(const T &item)
{
    dc_list_node<T> *p_curr = mp_header->mp_next;
    while (p_curr != mp_header)
    {
        if (p_curr->m_item == item)
            return p_curr;
        else
            p_curr = p_curr->mp_next;
    }
    return NULL;
}

// 清空链表
template <typename T>
void dc_list<T>::clear()
{
    dc_list_node<T> *p_node = mp_header->mp_next, *p_next;
    while (p_node != mp_header)
    {
        p_next = p_node->mp_next;
        delete p_node;
        p_node = p_next;
    }
    mp_header->mp_next = mp_header;
    mp_header->mp_front = mp_header;
    m_size = 0;
}

}

#endif // DC_LIST_H
//////////////////////////////////////////////////////////////////////
