#ifndef COMPLEX_LIST_HPP
#define COMPLEX_LIST_HPP

#include <cstddef>

/*
 * 复杂链表
 */

namespace zhaiwei
{

template <typename T>
class complex_list_node
{
public:
    complex_list_node(const T &item = T(), complex_list_node<T> *next = NULL, complex_list_node<T> *sbling = NULL):
        m_item(item), mp_next(next), mp_sbling(sbling)
    {}
public:
    T m_item;
    complex_list_node<T> *mp_next;   //指向下一个结点
    complex_list_node<T> *mp_sbling; //指向任一结点
};

template <typename T>
class complex_list
{
public:
    template <typename U>
    friend std::ostream &operator<<(std::ostream &, const complex_list<U> &);
public:
	// 默认构造函数，构造一个空链表
    complex_list(): mp_head(NULL), m_size(0)
    {}
	
	// 析构函数
    ~complex_list()
    {
        clear(mp_head);
    }
	
	// 赋值构造函数
    complex_list(const complex_list<T> &rhs):mp_head(NULL), m_size(0)
    {
        mp_head = copy(rhs.mp_head);
        m_size = rhs.m_size;
    }
	
	// 赋值运算符
    complex_list<T> &operator=(const complex_list<T> &rhs);
	
	// 判断是否为空
    bool empty() const
    {
        return m_size == 0;
    }
	
	// 返回链表中节点数目
    std::size_t size() const
    {
        return m_size;
    }

    //在链表头部插入新结点，返回其指针
    complex_list_node<T> *insert(const T &item);
	
    //设置p2为p1的兄弟
    void set_sibling(complex_list_node<T> *p1, complex_list_node<T> *p2)
    {
        if (p1 == NULL) return;
        p1->mp_sbling = p2;
    }
	
    //清空链表
    void clear()
    {
        mp_head = clear(mp_head);
        m_size = 0;
    }
private:
    complex_list_node<T> *mp_head;	// 头结点
    std::size_t m_size;				// 节点数目

    //清空链表，返回头指针
    complex_list_node<T> *clear(complex_list_node<T> *);
    //复制链表，返回新链表的头指针
    complex_list_node<T> *copy(complex_list_node<T> *);
};

// 赋值运算符
template <typename T>
complex_list<T> &complex_list<T>::operator=(const complex_list<T> &rhs)
{
    complex_list_node<T> *p_orig = mp_head;
    mp_head = copy(rhs.mp_head);
    m_size = rhs.m_size;
    clear(p_orig);
    return *this;
}

//在链表头部插入新结点，返回其指针
template <typename T>
complex_list_node<T> *complex_list<T>::insert(const T &item)
{
    complex_list_node<T> *p_new_node = new complex_list_node<T>(item, mp_head);
    mp_head = p_new_node;
    ++m_size;
    return p_new_node;
}

template <typename T> 
complex_list_node<T> *complex_list<T>::clear(complex_list_node<T> *h)
{
    complex_list_node<T> *p_curr = h, *p_next;
    while (p_curr != NULL)
    {
        p_next = p_curr->mp_next;
        delete p_curr;
        p_curr = p_next;
    }
    return p_curr;
}

template <typename T> 
complex_list_node<T> *complex_list<T>::copy(complex_list_node<T> *h)
{
    if (h == NULL) return NULL;
    
    //对于原链表的每个结点，复制其克隆结点，并将克隆结点设置为原结点的后继
    complex_list_node<T> *p_curr, *p_clone, *p_next;
    p_curr = h;
    while (p_curr != NULL)
    {
        p_next = p_curr->mp_next;
        p_clone = new complex_list_node<T>(p_curr->m_item, p_next);
        p_curr->mp_next = p_clone;
        p_curr = p_next;
    }

    //对于每个克隆结点，设置其兄弟指针
    p_curr = h;
    while (p_curr != NULL)
    {
		p_clone = p_curr->mp_next;
        p_clone->mp_sbling = (p_curr->mp_sbling? p_curr->mp_sbling->mp_next: NULL);
        p_curr = p_clone->mp_next;
    }

    //重建两个链表
    p_curr = h;
    complex_list_node<T> *p_new_head = h->mp_next;
    while (p_curr != NULL)
    {
		p_clone = p_curr->mp_next;
        p_curr->mp_next = p_clone->mp_next;
        p_curr = p_curr->mp_next;
        p_clone->mp_next = (p_curr? p_curr->mp_next: NULL);
    }
            
    return p_new_head;
}


template <typename T>
std::ostream &operator<<(std::ostream &ostr, const complex_list<T> &cl)
{
    complex_list_node<T> *p = cl.mp_head;
    while (p != NULL)
    {
        ostr << p->m_item << "(";
        p->mp_sbling? ostr << p->mp_sbling->m_item: ostr << " ";
        ostr << ") ";
        p = p->mp_next;
    }
    return ostr;   
}

}


#endif
