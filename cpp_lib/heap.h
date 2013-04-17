// heap.h
//
// last-edit-by: <> 
//
// Description:
// 最小二叉堆，基于数组的完全二叉树
//////////////////////////////////////////////////////////////////////

#ifndef HEAP_H
#define HEAP_H 1

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace zhaiwei
{

template <typename T>
class heap
{
public:
    heap(int capacity, const T &min_element);
    heap(int capacity, const T &min_element, const T *ptr, int size);
    heap(const heap &bh);
    ~heap();

    heap &operator=(const heap &rhs);
    
    int is_empty() const;
    int is_full() const;
    void print(const std::string &str) const;
    
    void insert(const T& x);
    T delete_min();
    T delete_element(int pos);
    void decrease_key(int pos, const T &delta);
    void increase_key(int pos, const T &delta);
private:
    T *m_array;
    int m_capacity;
    int m_size;
private:
    void percolate_down(int pos);
    void percolate_up(int pos);
};

template <typename T>
heap<T>::heap(int capacity, const T &min_element): m_capacity(capacity), m_size(0), m_array(NULL)
{
    m_array = new T[m_capacity + 1];
    m_array[0] = min_element;
}

template <typename T>
heap<T>::heap(int capacity, const T &min_element, const T *ptr, int size):m_capacity(capacity),
                                                                                        m_size(size),
                                                                                        m_array(NULL)
{
    if (m_capacity < m_size)
        throw runtime_error("the capacity of binary heap is too small");

    m_array = new T[m_capacity];
    m_array[0] = min_element;
    
    for (int i = 0; i != m_size; ++i)
        m_array[i+1] = ptr[i];
    
    for (int i = m_size / 2; i >= 1; --i)
        percolate_down(i);
}

template <typename T>
heap<T>::heap(const heap &bh):m_capacity(bh.m_capacity), m_size(bh.m_size), m_array(NULL)
{
    m_array = new T[m_capacity];
    for (int i = 0; i <= m_size; ++i)
        m_array[i] = bh.m_array[i];
}

template <typename T>
heap<T> &heap<T>::operator=(const heap &rhs)
{
    T *ptr = m_array;

    m_array = new T[rhs.m_capacity];
    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    for (int i = 0; i <= m_size; ++i)
        m_array[i] = rhs.m_array[i];
    delete [] ptr;
    return *this;
}

template <typename T>
heap<T>::~heap()
{
    delete [] m_array;
}

template <typename T>
int heap<T>::is_full() const
{
    return m_size == m_capacity;
}

template <typename T>
int heap<T>::is_empty() const
{
    return m_size == 0;
}

template <typename T>
void heap<T>::print(const std::string &str) const
{
    cout << str << endl;
    cout << "Capacity: " << m_capacity << endl;
    cout << "Size: " << m_size << endl;
    for (int i = 1; i <= m_size; ++i)
        cout << m_array[i] << ' ';
    cout << endl << endl;
}

template <typename T>
void heap<T>::insert(const T& x)
{
    if (is_full())
        throw runtime_error("binary heap is full");

    m_array[++m_size] = x;
    percolate_up(m_size);
}

template <typename T>
T heap<T>::delete_min()
{
    if (is_empty())
        throw runtime_error("binary heap is empty");

    T min_element = m_array[1];
    m_array[1] = m_array[m_size--];
    percolate_down(1);
    return min_element;
}

template <typename T>
T heap<T>::delete_element(int pos)
{
    if (pos < 1 || pos > m_size)
        throw runtime_error("the position is out of range");
    
    T del_element = m_array[pos];
    m_array[pos] = m_array[m_size--];
    percolate_down(pos);
    return del_element;
}

template <typename T>
void heap<T>::decrease_key(int pos, const T &delta)
{
    if (pos < 1 || pos > m_size)
        throw runtime_error("the position is out of range");
    
    m_array[pos] -= delta;
    percolate_up(pos);
}

template <typename T>
void heap<T>::increase_key(int pos, const T &delta)
{
    if (pos < 1 || pos > m_size)
        throw runtime_error("the position is out of range");
    
    m_array[pos] += delta;
    percolate_down(pos);
}

template <typename T>
void heap<T>::percolate_down(int pos)
{
    T element = m_array[pos];
    int i, child;
    for (i = pos; i * 2 <= m_size; i = child)
    {
        child = i * 2;
        if (child != m_size && m_array[child + 1] < m_array[child])
            ++child;

        if (m_array[child] < element)
            m_array[i] = m_array[child];
        else
            break;
    }
    m_array[i] = element;
}

template <typename T>
void heap<T>::percolate_up(int pos)
{
    T element = m_array[pos];
    int i;
    for (i = pos; m_array[i/2] > element; i /= 2)
        m_array[i] = m_array[i / 2];
    m_array[i] = element;
}

}

#endif // HEAP_H
//////////////////////////////////////////////////////////////////////
