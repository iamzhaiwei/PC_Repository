// quick_sort.cpp
//////////////////////////////////////////////////////////////////////

#include "quick_sort.h"
#include <algorithm>
#include "random_problem.h"

using namespace std;
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{

// 以array[right]为主元划分数组array[left...right]，返回划分后主元的下标
int partition(int *array, int left, int right)
{
    int pivot = array[right];
    int i = left - 1;
    for (int j = left; j <= right-1; ++j)
    {
        if (array[j] <= pivot)
        {
            ++i;
            swap(array[i], array[j]);
        }
    }
    ++i;
    swap(array[i], array[right]);
    return (i == right)? left+(right-left)/2: i;
}

// 随机划分数组array[left...right], 返回划分后主元的下标
int random_partition(int *array, int left, int right)
{
    int i = random_int(left, right);
    swap(array[i], array[right]);
    return partition(array, left, right);
}

}
