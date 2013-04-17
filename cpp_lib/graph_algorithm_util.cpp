#include "graph_algorithm.hpp"
#include "graph_algorithm_util.hpp"

using namespace std;
using namespace boost;

namespace zhaiwei
{
    ostream &operator<<(ostream &ostr, const top_sort_list &res)
    {
        top_sort_list::const_iterator iter;
        for (iter = res.begin(); iter != res.end(); ++iter)
        {
            ostr << *iter << " ";
        }
        return ostr;
    }

    ostream &operator<<(ostream &ostr, const bfs_tree &res)
    {
        bfs_tree::const_iterator iter;
        for (iter = res.begin(); iter != res.end(); ++iter)
        {
            ostr << iter->first << ": " << iter->second.m_dist << ", " << iter->second.m_path << endl;
        }
        return ostr;
    }

    ostream &operator<<(ostream &ostr, const dfs_tree &t)
    {
        ostr << "nodes:" << endl;
        for (dfs_tree::node::const_iterator iter = t.m_nodes.begin(); iter != t.m_nodes.end(); ++iter)
            ostr << iter->first << "(" << iter->second.m_begin_time  << "," << iter->second.m_end_time << "," 
                 << iter->second.m_path << ")" << endl;

        ostr << "tree edges:" << endl;
        for (dfs_tree::edge::const_iterator iter = t.m_tree_edges.begin(); iter != t.m_tree_edges.end(); ++iter)
            ostr << "(" << iter->first << "," << iter->second << ")" << endl;

        ostr << "back edges:" << endl;
        for (dfs_tree::edge::const_iterator iter = t.m_back_edges.begin(); iter != t.m_back_edges.end(); ++iter)
            ostr << "(" << iter->first << "," << iter->second << ")" << endl;

        ostr << "other edges:" << endl;
        for (dfs_tree::edge::const_iterator iter = t.m_oth_edges.begin(); iter != t.m_oth_edges.end(); ++iter)
            ostr << "(" << iter->first << "," << iter->second << ")" << endl;

        return ostr;
    }
                   
    ostream &operator<<(ostream &ostr, const dfs_forest &f)
    {
        for (dfs_forest::const_iterator iter = f.begin(); iter != f.end(); ++iter)
        {
            ostr << *iter << endl; 
        }
        return ostr;
    }

    ostream &operator<<(ostream &ostr, const strongly_connected_component &scc)
    {
        strongly_connected_component::const_iterator iter;
        ostr << "(";
        for (iter = scc.begin(); iter != scc.end(); ++iter)
            ostr << *iter << " ";
        ostr << ")" << endl;
        return ostr;
    }

    ostream &operator<<(ostream &ostr, const strongly_connected_components &sccs)
    {
        strongly_connected_components::const_iterator iter;
        for (iter = sccs.begin(); iter != sccs.end(); ++iter)
            ostr << *iter << endl;
        return ostr;
    }

    ostream &operator<<(std::ostream &ostr, const weight_matrix &l)
    {
        const weight_matrix::size_type *sizeptr = l.shape();
        for (size_t i = 0; i != sizeptr[0]; ++i)
        {
            for (size_t j = 0; j != sizeptr[1]; ++j)
                ostr << l[i][j] << " ";
            ostr << endl;
        }
        return ostr;
    }
    
    std::ostream &operator<<(std::ostream &ostr, const graph::min_spanning_tree_type &res)
    {
        graph::min_spanning_tree_type::const_iterator iter;
        for (iter = res.begin(); iter != res.end(); ++iter)
        {
            ostr << iter->first << ": " << iter->second.first << ", " << iter->second.second << endl;
        }
        return ostr;
    }

    void print_bfs_path(std::ostream &ostr, const std::string &src, const std::string &dst, const bfs_tree &res)
    {
        if (src == dst)
        {
            ostr << dst << "(0) ";
        }
        else if (res.at(dst).m_path == "")
        {
            ostr << "no path from " << src << " to " << dst << " ";
        }
        else
        {
            print_bfs_path(ostr, src, res.at(dst).m_path, res);
            ostr << dst << "(" << res.at(dst).m_dist << ") ";
        }
    }

}
