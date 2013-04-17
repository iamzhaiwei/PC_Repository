#include "disjoint_sets.hpp"

using namespace std;

disjoint_sets::disjoint_sets(int nsets):m_array(NULL), m_nsets(nsets)
{
    m_array = new element_type[m_nsets+1];
    for (size_t i = 0; i != m_nsets+1; ++i)
        m_array[i] = 0;
}

disjoint_sets::~disjoint_sets()
{
    delete [] m_array;
}

void disjoint_sets::union_set(set_type root1, set_type root2)
{    
    m_array[root2] = root1;
}

void disjoint_sets::union_set_by_height(set_type root1, set_type root2)
{  
    if (m_array[root2] < m_array[root1])
    {
        m_array[root1] = root2;
    }
    else
    {
        if (m_array[root1] == m_array[root2])
            --m_array[root1];
        m_array[root2] = root1;
    }
}

disjoint_sets::set_type disjoint_sets::find_set(element_type x)
{
    if (m_array[x] <= 0)
        return x;
    else
        return m_array[x] = find_set(m_array[x]);
}

void disjoint_sets::print_detail(ostream &ostr)
{
    for (size_t i = 1; i <= m_nsets; ++i)
        ostr << m_array[i] << " ";
    ostr << endl;
}
