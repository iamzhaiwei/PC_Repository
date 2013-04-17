#include "graph_algorithm.hpp"

using namespace std;

namespace zhaiwei
{
    void directed_strongly_connected_components(const graph &g, strongly_connected_components &sccs)
    {
        dfs_forest f;
        unweighted_directed_dfs(g, f);

        priority_queue<dfs_tree_node_end_time> pq;
        for (dfs_forest::iterator fiter = f.begin(); fiter != f.end(); ++fiter)
        {
            for (dfs_tree::node::iterator titer = fiter->m_nodes.begin(); titer != fiter->m_nodes.end(); ++titer)
            {
                pq.push(dfs_tree_node_end_time(titer->first, titer->second.m_end_time));
            }
        }

        graph gt(g.vertex_size());
        g.transpose(gt);

        strongly_connected_component scc;
        dfs_tree tt(gt.vertex_size(), gt.edge_size()/2);
        vertex_color colors[gt.m_headers.size()];
        for (size_t i = 0; i != gt.m_headers.size(); ++i)
            colors[i] = white;
        string name;
        int No;
        int time = 0;
        while (!pq.empty())
        {
            name = pq.top().m_name;
            pq.pop();
            No = gt.m_map[name];
            if (colors[No-1] == white)
            {
                tt.clear();
                unweighted_directed_dfs_visit(gt, tt, No-1, colors, time);
            
                scc.clear();
                for (dfs_tree::node::iterator titer = tt.m_nodes.begin(); titer != tt.m_nodes.end(); ++titer)
                    scc.push_back(titer->first);
                sccs.push_back(scc);          
            }
        }
    
    }
}
