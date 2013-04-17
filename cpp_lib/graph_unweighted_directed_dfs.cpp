#include "graph_algorithm.hpp"

using namespace std;

namespace zhaiwei
{
    
    void unweighted_directed_dfs_visit(const graph &g, dfs_tree &tree, int root_idx, vertex_color colors[], int &time)
    {
        colors[root_idx] = gray;
        string root_name = g.m_map_iters[root_idx]->first;
        tree.m_nodes.insert(make_pair(root_name, dfs_tree_node(++time)));
        graph::edge_list_type::iterator iter;
        int No;
        string name;
        for (iter = g.m_headers[root_idx]->begin(); iter != g.m_headers[root_idx]->end(); ++iter)
        {
            No = (*iter)->m_No;
            name = g.m_map_iters[No-1]->first;
            if (colors[No-1] == black)
                tree.m_oth_edges.insert(make_pair(root_name, name));
            else if (colors[No-1] == gray)
                tree.m_back_edges.insert(make_pair(root_name, name));
            else
            {
                tree.m_tree_edges.insert(make_pair(root_name, name));
                unweighted_directed_dfs_visit(g, tree, No-1, colors, time);
                tree.m_nodes[name].m_path = root_name;
            }
        }
        colors[root_idx] = black;
        tree.m_nodes[root_name].m_end_time = ++time;
    }

    void unweighted_directed_dfs(const graph &g, dfs_forest &forest)
    {
        vertex_color colors[g.m_headers.size()];
        for (size_t i = 0; i != g.m_headers.size(); ++i)
            colors[i] = white;

        dfs_tree tree(g.vertex_size(), g.edge_size()/2);
        int time = 0;
        for (size_t i = 0; i != g.m_headers.size(); ++i)
        {
            if (g.m_headers[i] != NULL && colors[i] == white)
            {
                unweighted_directed_dfs_visit(g, tree, i, colors, time);
                forest.push_back(tree);
                tree.clear();
            }
        }
    }
}
