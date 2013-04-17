#ifndef GRAPH_ADJACENT_MATRIX_HPP
#define GRAPH_ADJACENT_MATRIX_HPP

#include <cstddef>
#include <vector>
#include <queue>
#include <iterator>
#include <string>
#include <utility>
#include <boost/multi_array.hpp>
#include <boost/unordered_map.hpp>

namespace zhaiwei
{
    typedef boost::multi_array<int, 2> weight_matrix;
    class graph_adjacent_matrix
    {
    public:
        typedef boost::unordered_map<std::string, int> map_type;
        typedef std::vector<map_type::iterator> map_iter_vec_type;
    public:
        friend std::ostream &operator<<(std::ostream &, const graph_adjacent_matrix &);
        friend void slow_all_pairs_shortest_paths(const graph_adjacent_matrix &, weight_matrix &);
        friend void faster_all_pairs_shortest_paths(const graph_adjacent_matrix &, weight_matrix &);
    public:
        graph_adjacent_matrix(std::size_t max_size, int weight_upper_bound);

            //顶点数
        const std::size_t vertex_size() const
            {
                return m_max_size - m_avail_Nos.size();
            }
        
            //插入一条边
        void insert_edge(const std::string &name1, const std::string &name2, int weight = 1);
            //插入顶点
        void insert_vertex(const std::string &name);
            //删除边
        void erase_edge(const std::string &name1, const std::string &name2);
            //删除顶点
        void erase_vertex(const std::string &name);

    private:
        std::size_t m_max_size;       //顶点最大数目
        int m_weight_upper_bound;     //代表边的权重无穷大
        map_type m_map;               //存储顶点名字到编号的映射
        map_iter_vec_type m_map_iters;//存储映射的迭代器
        std::vector<bool> m_valid_Nos;//存储编号是否有效
        std::queue<int> m_avail_Nos;  //存储可用编号
        weight_matrix m_weights;      //权重
        

            //得到顶点编号
        int vertex_No(const std::string &name) const;
            //插入顶点，返回顶点编号
        int insert_vtx(const std::string &name);
            //删除顶点
        void erase_vertex(int No);
    };

    std::ostream &operator<<(std::ostream &ostr, const graph_adjacent_matrix &g);

}
#endif
