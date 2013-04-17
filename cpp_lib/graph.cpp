#include "graph.hpp"
#include <cstddef>

using namespace std;
using namespace boost;

namespace zhaiwei
{
    size_t graph::edge_size()  const
    {
        std::size_t cnt = 0;
        for (std::size_t i = 0; i != m_headers.size(); ++i)
        {
            if (m_headers[i] != NULL)
                cnt += m_headers[i]->m_indegree;
        }
        return cnt;
    }

    bool graph::edge_exist(const string &name1, const string &name2)  const
    {
        int vtx_No1, vtx_No2;
        if ( (vtx_No1 = vertex_No(name1)) <= 0)
            return false;
        if ( (vtx_No2 = vertex_No(name2)) <= 0)
            return false;
            
        header_vertex *hvtxptr = m_headers[vtx_No1-1];
        if (hvtxptr->find_evertex(vtx_No2) == hvtxptr->end())
            return false;
        else
            return true;
    }

    int graph::get_weight(const string &name1, const string &name2) const
    {
        int No1 = vertex_No(name1);
        int No2 = vertex_No(name2);
        edge_list_type::iterator iter = m_headers[No1-1]->find_evertex(No2);
        return m_headers[No1-1]->get_weight(iter);
    }

    void graph::set_weight(const string &name1, const string &name2, int weight)
    {
        int No1 = vertex_No(name1);
        int No2 = vertex_No(name2);
        edge_list_type::iterator iter = m_headers[No1-1]->find_evertex(No2);
        m_headers[No1-1]->set_weight(iter, weight);
    }

    void graph::insert_edge(const string &name1, const string &name2, int weight)
    {
        int No1, No2;
        if ( (No1 = vertex_No(name1)) <= 0)
        {
            No1 = insert_vtx(name1);
        }
        if ( (No2 = vertex_No(name2)) <= 0)
        {
            No2 = insert_vtx(name2);
        }

        if (m_headers[No1-1]->insert_evertex(new edge_vertex(No2, weight)) == true)
        {
            ++m_headers[No1-1]->m_outdegree;
            ++m_headers[No2-1]->m_indegree;
        }
    }

    void graph::insert_vertex(const string &name)
    {
        if ( vertex_No(name) <= 0)
        {
            insert_vtx(name);
        }
    }

    void graph::erase_edge(const string &name1, const string &name2)
    {
        int No1, No2;
        if ( (No1 = vertex_No(name1)) <= 0)
            return;
        if ( (No2 = vertex_No(name2)) <= 0)
            return;

        header_vertex *hvtxptr = m_headers[No1-1];
        if (hvtxptr->erase_evertex(No2) == true)
        {
            --m_headers[No1-1]->m_outdegree;
            --m_headers[No2-1]->m_indegree;
        }
    }

    void graph::erase_vertex(const string &name)
    {
        int No;
        if ( (No = vertex_No(name)) <= 0)
            return;

        erase_vertex(No);
    }

    void graph::transpose(graph &g) const//保持顶点编号不变
    {
        for (size_t i = 0; i != m_headers.size(); ++i)
        {
            header_vertex *hvtxptr = NULL;
            if ( (hvtxptr = m_headers[i]) != NULL)
            {
                g.insert_vertex(m_map_iters[i]->first);
            }
        }
        for (size_t i = 0; i != m_headers.size(); ++i)
        {
            header_vertex *hvtxptr = NULL;
            if ( (hvtxptr = m_headers[i]) != NULL)
            {
                for (edge_list_type::iterator iter = hvtxptr->begin(); iter != hvtxptr->end(); ++iter)
                {
                    g.insert_edge(m_map_iters[(*iter)->m_No-1]->first, m_map_iters[i]->first, (*iter)->m_weight);
                }
            }
        }
    }


    int graph::vertex_No(const string &name) const
    {
        if (m_map.count(name) != 0)
            return m_map.at(name);
        else
            return -1;
    }

    int graph::insert_vtx(const std::string &name)
    {
        int No = m_avail_Nos.front();
        m_avail_Nos.pop();
        pair< map_type::iterator, bool > ret = m_map.insert(make_pair(name, No));
        m_map_iters.at(No-1) = ret.first;
        m_headers.at(No-1) = new header_vertex();
        return No;
    }

    void graph::erase_vertex(int No)
    {
            //删除始于该顶点的边
        header_vertex *hvtxptr = m_headers[No-1];
        edge_list_type::iterator iter = hvtxptr->begin();
        while (iter != hvtxptr->end())
        {
            int No2 = (*iter)->m_No;
            hvtxptr->erase_evertex(iter++);
            --m_headers[No-1]->m_outdegree;
            --m_headers[No2-1]->m_indegree;
        }
            //删除终于该顶点的边
        for (size_t i = 0; i != m_headers.size(); ++i)
        {
            if (m_headers[i] != NULL)
            {
                if ( (iter = m_headers[i]->find_evertex(No)) != m_headers[i]->end())
                {
                    m_headers[i]->erase_evertex(iter);
                    --m_headers[i]->m_outdegree;
                    --m_headers[No-1]->m_indegree;
                }
            }
        }
            //删除顶点
        delete m_headers[No-1];
        m_headers[No-1] = NULL;
        m_map.erase(m_map_iters[No-1]);
        m_avail_Nos.push(No);
    }

    ostream &operator<<(ostream &ostr, const graph &g)
    {
        for (size_t i = 0; i != g.m_headers.size(); ++i)
        {
            if (g.m_headers[i] != NULL)
            {
                ostr << g.m_map_iters[i]->first
                     << "(" << g.m_headers[i]->m_indegree << ","
                     << g.m_headers[i]->m_outdegree << "): ";
                for (graph::edge_list_type::iterator iter = g.m_headers[i]->begin();
                     iter != g.m_headers[i]->end(); ++iter)
                {
                    ostr << g.m_map_iters[(*iter)->m_No-1]->first << "(" << (*iter)->m_weight << "), ";
                }
                ostr << endl;
            }
        }
        return ostr;
    }
}

