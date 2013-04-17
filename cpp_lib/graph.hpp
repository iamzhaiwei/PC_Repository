#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <iterator>
#include <string>
#include <utility>
#include <boost/unordered_map.hpp>
#include "graph_vertex.hpp"

namespace zhaiwei
{
//遍历图用的顶点的状态
    enum vertex_color {white, gray, black};

//广度优先遍历
    class bfs_tree_node;
    typedef boost::unordered_map<std::string, bfs_tree_node> bfs_tree;

//深度优先遍历
    class dfs_tree;
    typedef std::vector<dfs_tree> dfs_forest;

//有向图强连通分支
    typedef std::vector<std::string> strongly_connected_component;
    typedef std::vector< strongly_connected_component > strongly_connected_components;

//图
    class graph
    {
    public:
        typedef boost::unordered_map<std::string, int> map_type;
        typedef std::vector<map_type::iterator> map_iter_vec_type;
        typedef std::vector<header_vertex *> header_vec_type;
        typedef header_vertex::edge_list_type edge_list_type;    
        typedef boost::unordered_multimap< std::string, std::pair<int, std::string> > min_spanning_tree_type;
    public:
        friend std::ostream &operator<<(std::ostream &, const graph &);
        friend void unweighted_bfs(const graph &, const std::string &, bfs_tree &);
        friend void unweighted_directed_dfs(const graph &, dfs_forest &);
        friend void unweighted_directed_dfs_visit(const graph &, dfs_tree &, int , vertex_color *, int &);
        friend void unweighted_undirected_dfs(const graph &, dfs_forest &);
        friend void unweighted_undirected_dfs_visit(const graph &, dfs_tree &, int , vertex_color *, int &);
        friend void directed_strongly_connected_components(const graph &, strongly_connected_components &);
        friend void init_single_source(const graph &, const std::string &, bfs_tree &, int);
        friend bool bellman_ford(const graph &, const std::string &, bfs_tree &, int);
        friend void dag_shortest_path(const graph &, const std::string &, bfs_tree &, int);
        friend void dijkstra(const graph &, const std::string &, bfs_tree &, int);
    
        friend void weighted_negative(const graph &, const std::string &, bfs_tree &);
        friend void uncycled_critical_path_analysis(graph &, const std::string &, bfs_tree &);
        friend void uncycled_critical_path_analysis(graph &, const std::string &, const bfs_tree &, bfs_tree &);
        friend void undirected_prim_min_spanning_tree(const graph &, const std::string &, min_spanning_tree_type &);
        friend void undirected_kruskal_min_spanning_tree(const graph &, min_spanning_tree_type &);

    public:
        explicit graph(int max_header_size):
            m_map(max_header_size), m_map_iters(max_header_size, m_map.end()),
            m_headers(max_header_size, static_cast<header_vertex *>(NULL))
            {
                for (std::size_t i = 0; i != m_headers.size(); ++i)
                    m_avail_Nos.push(i+1);
            }
    
        ~graph()
            {
                for (std::size_t i = 0; i != m_headers.size(); ++i)
                {
                    if (m_headers[i] != NULL)
                        delete m_headers[i];
                }
            }

            //判断图是否为空，没有顶点和边
        bool empty() const
            {
                return m_headers.size() == m_avail_Nos.size();
            }
        bool full() const
            {
                return m_avail_Nos.size() == 0;
            }
            //返回图的顶点数
        std::size_t vertex_size() const
            {
                return m_headers.size() - m_avail_Nos.size();
            }
            //返回图的边数
        std::size_t edge_size()  const;
            //判断顶点是否存在
        bool vertex_exist(const std::string &name) const
            {
                return m_map.count(name) != 0;
            }
            //判断边是否存在
        bool edge_exist(const std::string &name1, const std::string &name2) const;
            //返回顶点的入度
        std::size_t indegree(const std::string &name) const
            {
                int No = vertex_No(name);
                return m_headers[No-1]->m_indegree;
            }
            //返回顶点的出度
        std::size_t outdegree(const std::string &name) const
            {
                int No = vertex_No(name);
                return m_headers[No-1]->m_outdegree;
            }
            //得到边的权重
        int get_weight(const std::string &name1, const std::string &name2) const;
            //设置边的权重
        void set_weight(const std::string &name1, const std::string &name2, int weight);

            //图反向
        void transpose(graph &g) const;
    
            //插入一条边
        void insert_edge(const std::string &name1, const std::string &name2, int weight = 1);
            //插入顶点
        void insert_vertex(const std::string &name);
            //删除边
        void erase_edge(const std::string &name1, const std::string &name2);
            //删除顶点
        void erase_vertex(const std::string &name);

        
    private:
            //存储顶点名字到编号的映射
        map_type m_map;
            //存储映射的迭代器
        map_iter_vec_type m_map_iters;
            //存储顶点的指针
        header_vec_type m_headers;
            //存储可用的编号
        std::queue<int> m_avail_Nos;
    
            //得到顶点编号
        int vertex_No(const std::string &name) const;
            //插入顶点，返回顶点编号
        int insert_vtx(const std::string &name);
            //删除顶点
        void erase_vertex(int No);
    };

    std::ostream &operator<<(std::ostream &, const graph &);
}
#endif
