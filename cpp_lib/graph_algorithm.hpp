#ifndef GRAPH_ALGORITHM_HPP
#define GRAPH_ALGORITHM_HPP

#include "graph.hpp"
#include "graph_adjacent_matrix.hpp"
#include <boost/heap/pairing_heap.hpp>

namespace zhaiwei
{
//广度优先搜索树结点
    class bfs_tree_node
    {
    public:
        explicit bfs_tree_node(int dist = 0, const std::string &path = "", int No = 0):
            m_dist(dist), m_path(path), m_No(No)
            {}
        int m_dist;
        std::string m_path;
        int m_No;
    };
    inline bool operator<(const bfs_tree_node &lhs, const bfs_tree_node &rhs)
    {
        return lhs.m_dist < rhs.m_dist;
    }
    inline bool operator>(const bfs_tree_node &lhs, const bfs_tree_node &rhs)
    {
        return lhs.m_dist > rhs.m_dist;
    }
//广度优先搜索树结点的最小堆
    typedef boost::heap::pairing_heap<bfs_tree_node, boost::heap::compare<std::greater<bfs_tree_node> > >
    bfs_tree_node_min_heap;

//无权广度优先搜索
    void unweighted_bfs(const graph &, const std::string &, bfs_tree &);

//深度优先搜索树结点
    class dfs_tree_node
    {
    public:
        explicit dfs_tree_node(int b = 0, int e = 0, const std::string path = ""):
            m_begin_time(b), m_end_time(e), m_path(path)
            {}
            
        int m_begin_time;
        int m_end_time;
        std::string m_path;
    };
//深度优先搜索树
    class dfs_tree
    {
    public:
        typedef boost::unordered_map<std::string, dfs_tree_node> node;
        typedef boost::unordered_multimap<std::string, std::string> edge;
    public:
        explicit dfs_tree(std::size_t vsize = 0, std::size_t esize = 0):
            m_nodes(vsize), m_tree_edges(esize), m_back_edges(esize), m_oth_edges(esize)
            {}

        void clear()
            {
                m_nodes.clear();
                m_tree_edges.clear();
                m_back_edges.clear();
                m_oth_edges.clear();
            }
        node m_nodes;
        edge m_tree_edges;
        edge m_back_edges;
        edge m_oth_edges;
    };
//无权深度优先搜索
    void unweighted_directed_dfs(const graph &, dfs_forest &);
    void unweighted_directed_dfs_visit(const graph &, dfs_tree &, int , vertex_color *, int &);
    void unweighted_undirected_dfs(const graph &, dfs_forest &);
    void unweighted_undirected_dfs_visit(const graph &, dfs_tree &, int , vertex_color *, int &);

        //深度优先搜索树结点完成时间
    class dfs_tree_node_end_time
    {
    public:
        explicit dfs_tree_node_end_time(const std::string &name = "", int t = 0):
            m_name(name), m_end_time(t)
            {}
    
        std::string m_name;
        int m_end_time;
    };
    inline bool operator<(const dfs_tree_node_end_time &lhs, const dfs_tree_node_end_time &rhs)
    {
        return lhs.m_end_time < rhs.m_end_time;
    }
    inline bool operator>(const dfs_tree_node_end_time &lhs, const dfs_tree_node_end_time &rhs)
    {
        return lhs.m_end_time > rhs.m_end_time;
    }

//拓扑排序链表
    typedef std::list<std::string> top_sort_list;
//有向无回路拓扑排序
    void dag_top_sort(const graph &, top_sort_list &);

//有向图强连通分支
    void directed_strongly_connected_components(const graph &, strongly_connected_components &);

//单源最短路径初始化
    void init_single_source(const graph &, const std::string &, bfs_tree &, int);
//边松弛，若边的结束点的最短路径减小，返回true
    bool edge_relax(const std::string &, const std::string &, int, bfs_tree &);
//带权有向图单源最短路径
    bool bellman_ford(const graph &, const std::string &, bfs_tree &, int);
//有向无环图最短路径
    void dag_shortest_path(const graph &, const std::string &, bfs_tree &, int);
//Dijkstra算法
    void dijkstra(const graph &, const std::string &, bfs_tree &, int);

//每对顶点间的最短路径
    void extend_shortest_paths(const weight_matrix &, const weight_matrix &, weight_matrix &, int);
    void slow_all_pairs_shortest_paths(const graph_adjacent_matrix &, weight_matrix &);
    void faster_all_pairs_shortest_paths(const graph_adjacent_matrix &, weight_matrix &);

//负权图
    void weighted_negative(const graph &, const std::string &, bfs_tree &);

//无圈图关键路径分析,返回最早完成时间
    void uncycled_critical_path_analysis(graph &, const std::string &, bfs_tree &);
//无圈图关键路径分析,已知最早完成时间，得到最晚完成时间
    void uncycled_critical_path_analysis(graph &, const std::string &, const bfs_tree &,
                                         bfs_tree &);
//已知最早完成时间和最晚完成时间，得到关键路径
    void uncycled_critical_path_analysis(const bfs_tree &, const bfs_tree &, bfs_tree &);

//无向图最小生成树-Prim算法
    void undirected_prim_min_spanning_tree(const graph &, const std::string &, graph::min_spanning_tree_type &);

//无向图最小生成树-Kruskal算法
    void undirected_kruskal_min_spanning_tree(const graph &, graph::min_spanning_tree_type &);

    std::ostream &operator<<(std::ostream &, const bfs_tree &);
    void print_bfs_path(std::ostream &, const std::string &, const std::string &, const bfs_tree &);
    std::ostream &operator<<(std::ostream &, const dfs_tree &);
    std::ostream &operator<<(std::ostream &, const dfs_forest &);
    std::ostream &operator<<(std::ostream &, const top_sort_list &);
    std::ostream &operator<<(std::ostream &, const strongly_connected_component &);
    std::ostream &operator<<(std::ostream &, const strongly_connected_components &);
    std::ostream &operator<<(std::ostream &, const weight_matrix &);
    
    std::ostream &operator<<(std::ostream &, const graph::min_spanning_tree_type &);
    void print_search_result(std::ostream &, const std::string &, const bfs_tree &);
}
#endif
