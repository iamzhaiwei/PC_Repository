#ifndef SELECTION_PROBLEM_H
#define SELECTION_PROBLEM_H

#include "sort.h"

namespace zhaiwei
{

//快速选择: 第k个最小元
template <typename T>
void qselect(T *array, int k, int left, int right)
{
    if (left + qsort_cutoff <= right)
    {
        T pivot = median3(array, left, right);
        int i = left, j = right - 1;
        for (;;)
        {
            while (array[++i] < pivot);
            while (array[--j] > pivot);
            if (i < j)
                std::swap(array[i], array[j]);
            else
                break;
        }
        std::swap(array[i], array[right-1]);

        if (k <= i)
            qselect(array, k, left, i-1);
        else if (k > i+1)
            qselect(array, k, i+1, right);            
    }
    else
        insertion_sort(array + left, right - left + 1);
}
template <typename T>
void quick_select(T *array, int k, int n)
{
    qselect(array, k, 0, n-1);
}

}

#endif
