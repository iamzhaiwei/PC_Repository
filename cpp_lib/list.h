#ifndef LIST_H
#define LIST_H

/*
 * 单向链表，没有空闲头结点
 */
 
#include <cstddef>
#include <iostream>

namespace zhaiwei
{

template <typename T>
class list_node
{
public:
    explicit list_node(const T &item = T(), list_node<T> *next = NULL):
        m_item(item), mp_next(next)
    {}
        
public:
    T m_item;
    list_node<T> *mp_next;  
};
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <typename T>
class list
{
public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &ostr, const list<U> &l);
public:
	// 默认构造函数
    list():mp_head(NULL), m_size(0)
    {}
	
	// 析构函数
    ~list()
    {
        clear();
    }
	
	// 复制构造函数
    list(const list<T> &rhs):mp_head(NULL), m_size(0)
    {
        mp_head = copy(rhs.mp_head);
        m_size = rhs.m_size;
    }
	
	// 赋值操作符
    list<T> &operator=(const list<T> &rhs)
    {
        list_node<T> *porig = mp_head;
        mp_head = copy(rhs.mp_head);
        m_size = rhs.m_size;
        clear(porig);
        return *this;
    } 
	
	// 判断是否为空
    bool empty() const
    {
        return m_size == 0;
    }
	
	// 返回节点数目
    std::size_t size() const
    {
        return m_size;
    }

    // 在链表头部插入一个新结点，返回新结点的指针
    list_node<T> *insert(const T &);
	
    // 从链表中删除第一个值为item的结点
    void erase(const T &);
	
    // 清空链表
    void clear();
	
    // 在链表中查找第一个值为item的结点，若存在，返回指针，否则，返回NULL
    list_node<T> *find(const T &item);

    // 返回头结点指针
    list_node<T> * get_head() const
    {
        return mp_head;
    }
	
	// 设置新的头结点
    void set_head(list_node<T> *h)
    {
        mp_head = h;
    }
private:
    list_node<T> *mp_head;
    std::size_t m_size;

private:
    list_node<T> *copy(list_node<T> *pnode);
    void clear(list_node<T> *pnode);
};
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
template <typename T>
list_node<T> *list<T>::insert(const T &item)
{
    list_node<T> *p_new_node = new list_node<T>(item, mp_head);
    mp_head = p_new_node;
    ++m_size;
    return p_new_node;
}
	
template <typename T>
void list<T>::erase(const T &item)
{
    list_node<T> *pnode = find(item);
    if (pnode == NULL)
        return;
		
    list_node<T> *tmp = NULL;
    if (pnode == mp_head)
    {
        mp_head = mp_head->mp_next;
        delete pnode;
    }
    else if (pnode->mp_next == NULL)
    {
        tmp = mp_head;
        while (tmp->mp_next != pnode)
            tmp = tmp->mp_next;
        tmp->mp_next = NULL;
        delete pnode;
    }
    else
    {
        tmp = pnode->mp_next;
        pnode->m_item = tmp->m_item;
        pnode->mp_next = tmp->mp_next;
        delete tmp;
    }
    --m_size;                    
}
    
template <typename T>
list_node<T> *list<T>::copy(list_node<T> *pnode)
{
    list_node<T> *pold = pnode, *p_new_head = NULL, *p_new_tail = NULL, *tmp = NULL;
    while (pold != NULL)
    {
        tmp = new list_node<T>(pold->m_item);
        if (p_new_head == NULL)
            p_new_head = p_new_tail = tmp;
        else
        {
            p_new_tail->mp_next = tmp;
            p_new_tail = tmp;
        }
    }
    return p_new_head;
}
			
template <typename T>
void list<T>::clear(list_node<T> *pnode)
{
    list_node<T> *pcurr = pnode, *pnext = NULL;
    while (pcurr != NULL)
    {
        pnext = pcurr->mp_next;
        delete pcurr;
        pcurr = pnext;
    }
}
	
template <typename T>
void list<T>::clear()
{
    clear(mp_head);
    mp_head = NULL;
    m_size = 0;
}
	
template <typename T>
list_node<T> *list<T>::find(const T &item)
{
    list_node<T> *pnode = mp_head;
    while (pnode != NULL)
    {
        if (pnode->m_item == item)
            break;
        else
            pnode = pnode->mp_next;
    }
    return pnode;
}

template <typename T>
void print_list(std::ostream &ostr, list_node<T> *p_node)
{
    while (p_node != NULL)
    {
        ostr << p_node->m_item << " ";
        p_node = p_node->mp_next;
    }
    ostr << std::endl;
}

template <typename T>
std::ostream &operator<<(std::ostream &ostr, const list<T> &l)
{
    print_list(ostr, l.mp_head);
    return ostr;
}
	
}




#endif
