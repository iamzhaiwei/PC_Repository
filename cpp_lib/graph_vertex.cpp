#include "graph_vertex.hpp"

using namespace std;

namespace zhaiwei
{
    header_vertex::header_vertex():
        m_indegree(0), m_outdegree(0), m_edge_list_ptr(NULL)
    {
        m_edge_list_ptr = new edge_list_type();
    }

    header_vertex::~header_vertex()
    {
        if (m_edge_list_ptr != NULL)
        {
            for (edge_list_type::iterator iter = m_edge_list_ptr->begin();
                 iter != m_edge_list_ptr->end(); ++iter)
            {
                delete *iter;
                *iter = NULL;
            }
            delete m_edge_list_ptr;
            m_edge_list_ptr = NULL;
        }
    }

    header_vertex::edge_list_type::const_iterator header_vertex::find_evertex(int No) const
    {
        edge_list_type::const_iterator iter;
        for (iter = m_edge_list_ptr->begin(); iter != m_edge_list_ptr->end(); ++iter)
        {
            if ((*iter)->m_No == No)
                break;
        }
        return iter;
    }

    header_vertex::edge_list_type::iterator header_vertex::find_evertex(int No)
    {
        edge_list_type::iterator iter;
        for (iter = m_edge_list_ptr->begin(); iter != m_edge_list_ptr->end(); ++iter)
        {
            if ((*iter)->m_No == No)
                break;
        }
        return iter;
    }

    bool header_vertex::insert_evertex(edge_vertex *evertexptr)
    {
        if (find_evertex(evertexptr->m_No) == m_edge_list_ptr->end())
        {
            m_edge_list_ptr->push_back(evertexptr);
            return true;
        }
        else
            return false;
    }
    bool header_vertex::erase_evertex(int No)
    {
        edge_list_type::iterator iter = find_evertex(No);
        return erase_evertex(iter);
    }
    bool header_vertex::erase_evertex(edge_list_type::iterator iter)
    {
        if (iter != m_edge_list_ptr->end())
        {
            delete *iter;
            m_edge_list_ptr->erase(iter);
            return true;
        }
        else
            return false;
    }
}
