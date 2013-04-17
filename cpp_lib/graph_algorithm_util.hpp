#ifndef GRAPH_ALGORITHM_UTIL_HPP
#define GRAPH_ALGORITHM_UTIL_HPP

#include <cstddef>
#include <iostream>
#include <queue>
#include <map>
#include <functional>
#include <boost/heap/pairing_heap.hpp>
#include <boost/unordered_map.hpp>

namespace zhaiwei
{
    class edge_type
    {
    public:
        edge_type(int No1, int No2, int weight):m_No1(No1), m_No2(No2), m_weight(weight)
            {}
        int m_No1;
        int m_No2;
        int m_weight;
    };
    inline bool operator<(const edge_type &lhs, const edge_type &rhs)
    {
        return lhs.m_weight < rhs.m_weight;
    }
    inline bool operator>(const edge_type &lhs, const edge_type &rhs)
    {
        return lhs.m_weight > rhs.m_weight;
    }

    typedef std::priority_queue<edge_type, std::vector<edge_type>, std::greater<edge_type> > edge_min_heap_type;
}
#endif
