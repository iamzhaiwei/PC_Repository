#include "graph_algorithm.hpp"
#include "graph_algorithm_util.hpp"

using namespace std;

namespace zhaiwei
{
    void uncycled_critical_path_analysis(graph &g, const std::string &start_vtx, graph::bfs_result_type &result)
    {
    
        for (size_t i = 0; i != g.m_headers.size(); ++i)
        {
            if (g.m_headers[i] != NULL)
            {
                result.insert(make_pair(g.m_map_iters[i]->first, make_pair(0, "")));
            }
        }
    
        queue<int> queue_Nos;
        int curr_No = g.vertex_No(start_vtx), next_No;
        int curr_dist, next_dist;
        string curr_name, next_name;
        queue_Nos.push(curr_No);
        while (!queue_Nos.empty())
        {
            curr_No = queue_Nos.front();
            queue_Nos.pop();
            curr_name = g.m_map_iters[curr_No-1]->first;
            curr_dist = result[curr_name].first;
        
            header_vertex *hvtxptr = g.m_headers[curr_No-1];
            for (graph::edge_list_type::iterator iter = hvtxptr->begin(); iter != hvtxptr->end(); ++iter)
            {
                next_No = (*iter)->m_No;
                next_name = g.m_map_iters[next_No-1]->first;
                next_dist = curr_dist + (*iter)->m_weight;
                if (result[next_name].first < next_dist)
                {
                    result[next_name].first = next_dist;
                    result[next_name].second = curr_name;
                }
                if (g.m_headers[next_No-1]->m_indegree == 1)
                    queue_Nos.push(next_No);
            }
            g.erase_vertex(curr_No);
        }           
    }


    void uncycled_critical_path_analysis(graph &g, const std::string &start_vtx,
                                         const graph::bfs_result_type &result_early,
                                         graph::bfs_result_type &result_late)
    {
        bool searched[g.m_headers.size()];
        for (size_t i = 0; i != g.m_headers.size(); ++i)
        {
            searched[i] = false;
        }

        for (graph::bfs_result_type::const_iterator iter = result_early.begin(); iter != result_early.end(); ++iter)
        {
                //result_late.insert(make_pair(iter->first, make_pair(iter->second.first, iter->second.second)));
            result_late.insert(*iter);
        }
    
        queue<int> queue_Nos;
        int curr_No = g.vertex_No(start_vtx), next_No;
        int curr_dist, next_dist;
        string curr_name, next_name;
        queue_Nos.push(curr_No);
        searched[curr_No-1] = true;
        while (!queue_Nos.empty())
        {
            curr_No = queue_Nos.front();
            queue_Nos.pop();
            curr_name = g.m_map_iters[curr_No-1]->first;
            curr_dist = result_late[curr_name].first;
        
            header_vertex *hvtxptr = g.m_headers[curr_No-1];
            for (graph::edge_list_type::iterator iter = hvtxptr->begin(); iter != hvtxptr->end(); ++iter)
            {
                next_No = (*iter)->m_No;
                next_name = g.m_map_iters[next_No-1]->first;
                next_dist = curr_dist - (*iter)->m_weight;
                if (searched[next_No-1] == false)
                {
                    result_late[next_name].first = next_dist;
                    searched[next_No-1] = true;
                }
                else if (searched[next_No-1] && result_late[next_name].first > next_dist)
                {
                    result_late[next_name].first = next_dist;
                }
                if (g.m_headers[next_No-1]->m_indegree == 1)
                    queue_Nos.push(next_No);
            }
            g.erase_vertex(curr_No);
        }
    }


    void uncycled_critical_path_analysis(const graph::bfs_result_type &result_early,
                                         const graph::bfs_result_type &result_late,
                                         graph::bfs_result_type &result_critical)
    {
        for (graph::bfs_result_type::const_iterator iter = result_early.begin(); iter != result_early.end(); ++iter)
        {
            string name = iter->first;
            if (result_late.at(name).first == iter->second.first)
                result_critical.insert(*iter);
        }
    }

}
