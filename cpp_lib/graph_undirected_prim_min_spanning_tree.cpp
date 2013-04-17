#include "graph_algorithm.hpp"
#include "graph_algorithm_util.hpp"

using namespace std;

namespace zhaiwei
{
    
    void undirected_prim_min_spanning_tree(const graph &g, const std::string &start_vtx,
                                           bfs_tree &tree)
    {
            //初始化顶点状态
        vertex_stat vtxs[g.m_headers.size()];
        for (size_t i = 0; i != g.m_headers.size(); ++i)
            vtxs[i] = unqueued;
    
        bfs_vertex_min_heap_type queuing_vtx;
        bfs_vertex_min_heap_type::handle_type heap_handles[g.m_headers.size()];
        bfs_vertex_type curr_vtx(0, g.vertex_No(start_vtx), "");
        int next_No, next_dist;
        string curr_name;
            //起始顶点入队
        heap_handles[curr_vtx.m_No-1] = queuing_vtx.push(curr_vtx);
        vtxs[curr_vtx.m_No-1] = queuing;

        while (!queuing_vtx.empty())
        {
            curr_vtx = queuing_vtx.top();
            queuing_vtx.pop();
            vtxs[curr_vtx.m_No-1] = queued;
            curr_name = g.m_map_iters[curr_vtx.m_No-1]->first;        
            tree.insert(make_pair(curr_name, make_pair(curr_vtx.m_dist, curr_vtx.m_path)));
        
            header_vertex *hvtxptr = g.m_headers[curr_vtx.m_No-1];
            for (graph::edge_list_type::iterator eiter = hvtxptr->begin(); eiter != hvtxptr->end(); ++eiter)
            {
                next_No = (*eiter)->m_No;
                if (vtxs[next_No-1] == unqueued)
                {
                    next_dist = (*eiter)->m_weight;
                    heap_handles[next_No-1] = queuing_vtx.push(bfs_vertex_type(next_dist, next_No, curr_name));
                    vtxs[next_No-1] = queuing;
                }
                else if (vtxs[next_No-1] == queuing)
                {
                    for (bfs_vertex_min_heap_type::iterator qiter = queuing_vtx.begin();
                         qiter != queuing_vtx.end(); ++qiter)
                    {
                        if (qiter->m_No == next_No)
                        {
                            next_dist = (*eiter)->m_weight;
                            if (next_dist < qiter->m_dist)
                                queuing_vtx.decrease(heap_handles[next_No-1],
                                                     bfs_vertex_type(next_dist, qiter->m_No, curr_name));
                            break;
                        }
                    }
                }
            }
        }
    }
}
