#include "graph_algorithm.hpp"
#include <queue>

using namespace std;

namespace zhaiwei
{
    void unweighted_bfs(const graph &g, const std::string &start_vtx, bfs_tree &res)
    {
            //初始化顶点状态
        vertex_color colors[g.m_headers.size()];
        for (size_t i = 0; i != g.m_headers.size(); ++i)
        {
            if (g.m_headers[i] != NULL)
            {
                colors[i] = white;
                res.insert(make_pair(g.m_map_iters[i]->first, bfs_tree_node(0, "")));
            }
        }

        queue<int> No_q;
        int curr_No, next_No;
        int curr_dist;
        string curr_name, next_name;
    
            //将起始点入队
        curr_No = g.vertex_No(start_vtx);
        No_q.push(curr_No);
        colors[curr_No-1] = gray;
    
        while (!No_q.empty())
        {
            curr_No = No_q.front();
            No_q.pop();
            curr_name = g.m_map_iters[curr_No-1]->first;
            curr_dist = res[curr_name].m_dist;
            header_vertex *hvtxptr = g.m_headers[curr_No-1];
            for (graph::edge_list_type::iterator iter = hvtxptr->begin(); iter != hvtxptr->end(); ++iter)
            {
                next_No = (*iter)->m_No;
                if (colors[next_No-1] == white)
                {
                    next_name = g.m_map_iters[next_No-1]->first;
                    res[next_name].m_dist = curr_dist + 1;
                    res[next_name].m_path = curr_name;
                    No_q.push(next_No);
                    colors[next_No-1] = gray;
                }
            }
            colors[curr_No-1] = black;
        }
    }
}
