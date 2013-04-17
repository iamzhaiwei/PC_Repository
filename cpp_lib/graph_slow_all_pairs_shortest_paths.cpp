#include "graph_algorithm.hpp"

using namespace std;

namespace zhaiwei
{
    
    void extend_shortest_paths(const weight_matrix &w, const weight_matrix&l1, weight_matrix &l2, int weight_upper_bound)
    {
        const weight_matrix::size_type *sizeptr = w.shape();
        for (size_t i = 0; i != sizeptr[0]; ++i)
        {
            for (size_t j = 0; j != sizeptr[0]; ++j)
            {
                l2[i][j] = weight_upper_bound;
                for (size_t k = 0; k != sizeptr[0]; ++k)
                {
                    if (l1[i][k]+w[k][j] < l2[i][j])
                        l2[i][j] = l1[i][k] + w[k][j];
                }
            }
        }
    }

    void slow_all_pairs_shortest_paths(const graph_adjacent_matrix &g, weight_matrix &l)
    {
        weight_matrix l_tmp(g.m_weights);
        for (size_t i = 2; i <= g.m_max_size-1; ++i)
        {
            extend_shortest_paths(g.m_weights, l_tmp, l, g.m_weight_upper_bound);
            l_tmp = l;
        }      
    }

    void faster_all_pairs_shortest_paths(const graph_adjacent_matrix &g, weight_matrix &l)
    {
        weight_matrix l_tmp(g.m_weights);
        for (size_t i = 1; i < g.m_max_size-1; i *= 2)
        {
            extend_shortest_paths(l_tmp, l_tmp, l, g.m_weight_upper_bound);
            l_tmp = l;
        }
    }
}
