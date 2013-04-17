#include "graph_adjacent_matrix.hpp"

using namespace std;
using namespace boost;

namespace zhaiwei
{
    graph_adjacent_matrix::graph_adjacent_matrix(std::size_t max_size, int weight_upper_bound):
        m_max_size(max_size), m_weight_upper_bound(weight_upper_bound),
        m_map(max_size), m_map_iters(max_size, m_map.end()), m_valid_Nos(max_size, false),
        m_weights(boost::extents[max_size][max_size])
    {
        for (std::size_t i = 1; i <= m_max_size; ++i)
            m_avail_Nos.push(i);
            
        for (std::size_t i = 0; i != m_max_size; ++i)
        {
            for (std::size_t j = 0; j != m_max_size; ++j)
            {
                if (i == j)
                    m_weights[i][j] = 0;
                else
                    m_weights[i][j] = weight_upper_bound;
            }
        }
    }

    void graph_adjacent_matrix::insert_edge(const std::string &name1, const std::string &name2, int weight)
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
        m_weights[No1-1][No2-1] = weight;
    }

    void graph_adjacent_matrix::insert_vertex(const std::string &name)
    {
        if (vertex_No(name) <= 0)
            insert_vtx(name);
    }

    void graph_adjacent_matrix::erase_edge(const std::string &name1, const std::string &name2)
    {
        int No1, No2;
        if ( (No1 = vertex_No(name1)) <= 0)
            return;
        if ( (No2 = vertex_No(name2)) <= 0)
            return;

        m_weights[No1-1][No2-1] = m_weight_upper_bound;
    }
           
    void graph_adjacent_matrix::erase_vertex(const std::string &name)
    {
        int No;
        if ( (No = vertex_No(name)) >= 1)
            erase_vertex(No);
    }

    int graph_adjacent_matrix::vertex_No(const std::string &name) const
    {
        if (m_map.count(name) != 0)
            return m_map.at(name);
        else
            return -1;
    }
    
    int graph_adjacent_matrix::insert_vtx(const std::string &name)
    {
        int No = m_avail_Nos.front();
        m_avail_Nos.pop();
        std::pair< map_type::iterator, bool > ret = m_map.insert(make_pair(name, No));
        m_map_iters.at(No-1) = ret.first;
        m_valid_Nos[No-1] = true;
        return No;
    }

    void graph_adjacent_matrix::erase_vertex(int No)
    {
        for (std::size_t i = 0; i != m_max_size; ++i)
        {
            m_weights[No-1][i] = m_weight_upper_bound;
            m_weights[i][No-1] = m_weight_upper_bound;
        }
        m_weights[No-1][No-1] = 0;
            
        m_map.erase(m_map_iters[No-1]);
        m_map_iters[No-1] = m_map.end();
        m_valid_Nos[No-1] = false;
        m_avail_Nos.push(No);
    }

    ostream &operator<<(std::ostream &ostr, const graph_adjacent_matrix &g)
    {
        for (std::size_t i = 0; i != g.m_max_size; ++i)
        {
            if (g.m_valid_Nos[i] == true)
            {
                ostr << g.m_map_iters[i]->first << ": ";
                for (std::size_t j = 0; j != g.m_max_size; ++j)
                {
                    if (g.m_valid_Nos[j] == true && g.m_weights[i][j] != 0 &&
                        g.m_weights[i][j] < g.m_weight_upper_bound)
                        ostr << g.m_map_iters[j]->first << "(" << g.m_weights[i][j] << ") ";
                }
                ostr << std::endl;
            }
        }
        return ostr;
    }
}
