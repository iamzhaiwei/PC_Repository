#include "graph_algorithm.hpp"

using namespace std;

namespace zhaiwei
{
    void dfs(const graph &g, int vtx_No, depth_first_spanning_tree_type &tree, bool *searched, int &preoeder_No)
    {
        if (searched[vtx_No-1]) return;

        searched[vtx_No-1] = true;
        string name = g.m_map_iters[vtx_No-1]->first;
        tree.m_nodes.insert(make_pair(name, make_pair(++preoeder_No, 0)));
        header_vertex *hvtxptr = g.m_headers[vtx_No-1];
        for (graph::edge_list_type::iterator iter = hvtxptr->begin(); iter != hvtxptr->end(); ++iter)
        {
            dfs(g, (*iter)->m_No, tree, searched, preoeder_No);
        }
    }

    void undirected_connected_dfs(const graph &g, const string &start_vtx, depth_first_spanning_tree_type &tree)
    {
        bool searched[g.m_headers.size()];
        for (size_t i = 0; i != g.m_headers.size(); ++i)
            searched[i] = false;

        int curr_No = g.vertex_No(start_vtx);
        int preoeder_No = 0;
        dfs(g, curr_No, tree, searched, preoeder_No);
    }
}
