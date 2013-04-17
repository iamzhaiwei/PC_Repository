#ifndef LEFT_HEAP_HPP
#define LEFT_HEAP_HPP

template <typename T>
class left_heap_node
{
public:
    left_heap_node(const T &element = T(), left_heap_node<T> *left = NULL, left_heap_node<T> *right = NULL,
                   int npl = -1): m_element(element), m_left(left), m_right(right), m_Npl(npl)
        {}
            
    ~left_heap_node()
        {}

private:
    T m_element;
    left_heap_node<T> *m_left;
    left_heap_node<T> *m_right;
    int m_Npl;
};

template <typename T>
class left_heap
{
public:
    left_heap(left_heap_node<T> *ptr = NULL): m_root(ptr)
        {}
    
    ~left_heap()
        {}

    void merge(left_heap<T> &rhs);
private:
    left_heap_node<T> *m_root;

    left_heap_node<T> *merge(left_heap_node<T> *lhs, left_heap_node<T> *rhs);
};
#endif
