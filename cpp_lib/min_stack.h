#ifndef MIN_STACK_HPP
#define MIN_STACK_HPP

#include <stack>

namespace zhaiwei
{
    template <typename T>
    class min_stack
    {
    public:
        min_stack() {}

        void push(const T &item)
            {
                m_items.push(item);
                if (m_items.size() == 1)
                {                   
                    m_min_items.push(item);
                }
                else
                {
                    if (item < m_min_items.top())
                        m_min_items.push(item);
                    else
                        m_min_items.push(m_min_items.top());
                }
            }
        void pop()
            {
                m_items.pop();
                m_min_items.pop();
            }
        T &top()
            {
                return m_items.top();
            }
        const T &top() const
            {
                return m_items.top();
            }
        T &min()
            {
                return m_min_items.top();
            }
        const T &min() const
            {
                return m_min_items.top();
            }
    private:
        std::stack<T> m_items;
        std::stack<T> m_min_items;
    };
}


#endif
