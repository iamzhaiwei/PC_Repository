#ifndef GRAPH_VERTEX_HPP
#define GRAPH_VERTEX_HPP

#include <cstddef>
#include <list>

namespace zhaiwei
{
    class edge_vertex
    {
    public:
        explicit edge_vertex(int No = 0, int weight = 1):
            m_No(No), m_weight(weight)
            {}
    
        int m_No;
        int m_weight;
    };

    inline bool operator==(const edge_vertex &lhs, const edge_vertex &rhs)
    {
        return lhs.m_No == rhs.m_No && lhs.m_weight == rhs.m_weight;
    }

    class header_vertex
    {
    public:
        typedef std::list<edge_vertex *> edge_list_type;
    
    public:
        header_vertex();
        ~header_vertex();

        edge_list_type::iterator begin()
            {
                return m_edge_list_ptr->begin();
            }
        edge_list_type::const_iterator begin() const
            {
                return m_edge_list_ptr->begin();
            }
        edge_list_type::iterator end()
            {
                return m_edge_list_ptr->end();
            }
        edge_list_type::const_iterator end() const
            {
                return m_edge_list_ptr->end();
            }
    
        edge_list_type::const_iterator find_evertex(int No) const;
        edge_list_type::iterator find_evertex(int No);

        const int get_weight(edge_list_type::iterator iter) const
            {
                return (*iter)->m_weight;
            }
        void set_weight(edge_list_type::iterator iter, int weight)
            {
                (*iter)->m_weight = weight;
            }
    
        bool insert_evertex(edge_vertex *evertexptr);
        bool erase_evertex(int No);
        bool erase_evertex(edge_list_type::iterator iter);


        std::size_t m_indegree;
        std::size_t m_outdegree;
    private:
        edge_list_type *m_edge_list_ptr;
    private:
        header_vertex(const header_vertex &);
        header_vertex &operator=(const header_vertex &);
    };
}

#endif
