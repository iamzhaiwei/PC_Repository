#include "graph_algorithm.hpp"

using namespace std;

namespace zhaiwei
{
    void init_single_source(const graph &g, const std::string &start_vtx, bfs_tree &tree, int shortest_path_estimate)
    {
        string name;
        for (size_t i = 0; i != g.m_headers.size(); ++i)
        {
            if (g.m_headers[i] != NULL)
            {
                name = g.m_map_iters[i]->first;
                tree.insert(make_pair(name, bfs_tree_node(shortest_path_estimate, "", i+1)));
            }
        }
        tree[start_vtx].m_dist = 0;
    }

    bool edge_relax(const std::string &name1, const std::string &name2, int weight, bfs_tree &tree)
    {
        if (tree[name2].m_dist > tree[name1].m_dist + weight)
        {
            tree[name2].m_dist = tree[name1].m_dist + weight;
            tree[name2].m_path = name1;
            return true;
        }
        else
            return false;
    }

    bool bellman_ford(const graph &g, const std::string &start_vtx, bfs_tree &tree, int shortest_path_estimate)
    {
        init_single_source(g, start_vtx, tree, shortest_path_estimate);
        string name1, name2;
        for (size_t i = 1; i <= g.vertex_size()-1; ++i)
        {
            for (size_t j = 0; j != g.m_headers.size(); ++j)
            {
                header_vertex *hvtxptr = NULL;
                if ( (hvtxptr = g.m_headers[j]) != NULL)
                {
                    name1 = g.m_map_iters[j]->first;
                    for (graph::edge_list_type::iterator iter = hvtxptr->begin(); iter != hvtxptr->end(); ++iter)
                    {
                        name2 = g.m_map_iters[(*iter)->m_No-1]->first;
                        edge_relax(name1, name2, (*iter)->m_weight, tree);
                    }
                }
            }
        }

        for (size_t j = 0; j != g.m_headers.size(); ++j)
        {
            header_vertex *hvtxptr = NULL;
            if ( (hvtxptr = g.m_headers[j]) != NULL)
            {
                name1 = g.m_map_iters[j]->first;
                for (graph::edge_list_type::iterator iter = hvtxptr->begin(); iter != hvtxptr->end(); ++iter)
                {
                    name2 = g.m_map_iters[(*iter)->m_No-1]->first;
                    if (tree[name2].m_dist > tree[name1].m_dist + (*iter)->m_weight)
                        return false;
                }
            }
        }
        return true;
    
    }

}
