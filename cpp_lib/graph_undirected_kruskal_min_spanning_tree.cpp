#include "graph_algorithm.hpp"
#include "graph_algorithm_util.hpp"
#include "disjoint_sets.hpp"

namespace zhaiwei
{
    void undirected_kruskal_min_spanning_tree(const graph &g, graph::min_spanning_tree_type &tree)
    {
            //将图的所有边读进最小优先级队列
        edge_min_heap_type edge_pq;
        for (size_t i = 0; i != g.m_headers.size(); ++i)
        {
            if (g.m_headers[i] != NULL)
            {
                graph::edge_list_type::iterator iter;
                for (iter = g.m_headers[i]->begin(); iter != g.m_headers[i]->end(); ++iter)
                    edge_pq.push(edge_type(i+1, (*iter)->m_No, (*iter)->m_weight));
            }
        }
            //并查集
        disjoint_sets sets(g.vertex_size());
        size_t edges_accepted = 0;
        while (edges_accepted < g.vertex_size()-1)
        {
            edge_type e(edge_pq.top());
            edge_pq.pop();
            disjoint_sets::set_type No1_set = sets.find_set(e.m_No1);
            disjoint_sets::set_type No2_set = sets.find_set(e.m_No2);
            if (No1_set != No2_set)
            {
                sets.union_set_by_height(No1_set, No2_set);
                tree.insert(make_pair(g.m_map_iters[e.m_No1-1]->first,
                                      make_pair(e.m_weight, g.m_map_iters[e.m_No2-1]->first)));
                ++edges_accepted;
            }
        }  
    }
}
