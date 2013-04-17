#include "graph_algorithm.hpp"

using namespace std;

namespace zhaiwei
{
    void dag_shortest_path(const graph &g, const std::string &start_vtx, bfs_tree &tree, int shortest_path_estimate)
    {
        top_sort_list list;
        dag_top_sort(g, list);

        init_single_source(g, start_vtx, tree, shortest_path_estimate);
        for (top_sort_list::iterator liter = list.begin(); liter != list.end(); ++liter)
        {
            int No = g.m_map.at(*liter);
            header_vertex *hvtxptr = g.m_headers[No-1];
            for (graph::edge_list_type::iterator eiter = hvtxptr->begin(); eiter != hvtxptr->end(); ++eiter)
                edge_relax(*liter, g.m_map_iters[(*eiter)->m_No-1]->first, (*eiter)->m_weight, tree);
        }
    }
}
