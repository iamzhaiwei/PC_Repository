#include "graph_algorithm.hpp"

using namespace std;
using namespace boost;
using namespace boost::heap;

namespace zhaiwei
{
    void dijkstra(const graph &g, const std::string &start_vtx, bfs_tree &tree, int shortest_path_estimate)
    {
        init_single_source(g, start_vtx, tree, shortest_path_estimate);

        bfs_tree_node_min_heap min_heap;
        bfs_tree_node_min_heap::handle_type handles[g.m_headers.size()];
        for (size_t i = 0; i != g.m_headers.size(); ++i)
        {
            if (g.m_headers[i] != NULL)
                handles[i] = min_heap.push(bfs_tree_node(shortest_path_estimate, "", i+1));
        }
        int curr_No = g.m_map.at(start_vtx);
        bfs_tree_node curr_node(0, "", curr_No);
        string curr_name;
        int next_No;
        string next_name;
        min_heap.decrease(handles[curr_No-1], curr_node);
    
        while (!min_heap.empty())
        {
            curr_node = min_heap.top();
            min_heap.pop();
            curr_No = curr_node.m_No;
            curr_name = g.m_map_iters[curr_No-1]->first;
            tree[curr_name].m_dist = curr_node.m_dist;
            tree[curr_name].m_path = curr_node.m_path;

            header_vertex *hvtxptr = g.m_headers[curr_No-1];
            for (graph::edge_list_type::iterator iter = hvtxptr->begin(); iter != hvtxptr->end(); ++iter)
            {
                next_No = (*iter)->m_No;
                next_name = g.m_map_iters[next_No-1]->first;
                if (edge_relax(curr_name, next_name, (*iter)->m_weight, tree))
                    min_heap.decrease(handles[next_No-1], tree[next_name]);
            }
        }
    }

}
