#ifndef DISJOINT_SETS_HPP
#define DISJOINT_SETS_HPP

#include <cstddef>
#include <iostream>

class disjoint_sets
{
public:
    typedef int set_type;
    typedef int element_type;

public:
    explicit disjoint_sets(int nsets);
    ~disjoint_sets();

    void union_set(set_type root1, set_type root2);
    void union_set_by_height(set_type root1, set_type root2);
    set_type find_set(element_type x);
    void print_detail(std::ostream &);

private:
    element_type *m_array;
    std::size_t m_nsets;
};


#endif
