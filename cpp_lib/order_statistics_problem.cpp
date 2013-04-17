// order_statistics_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "order_statistics_problem.h"
#include <cmath>
#include <algorithm>
#include "my_math.h"
#include "quick_sort.h"
#include "sort.h"

using namespace std;
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{
// 查找最大值
// 比较n-1次
int my_max(int *array, int n)
{
    int tmp = array[0];
    for (int i = 1; i < n; ++i)
    {
        if (tmp < array[i])
            tmp = array[i];
    }
    return tmp;
}

// 查找最小值
// 比较n-1次
int my_min(int *array, int n)
{
    int tmp = array[0];
    for (int i = 1; i < n; ++i)
    {
        if (array[i] < tmp)
            tmp = array[i];
    }
    return tmp;
}

// 同时查找最大值和最小值
// 比较(3/2)n次
void my_max_and_min(int *array, int n, int &max, int &min)
{
    int i;
    if ( is_even(n) ) // 数组有偶数个元素
    {
        if (array[0] < array[1])
        {
            max = array[1];
            min = array[0];
        }
        else
        {
            max = array[0];
            min = array[1];
        }
        i = 2;
    }
    else
    {
        max = min = array[0];
        i = 1;
    }

    int tmp_max, tmp_min;
    for (; i < n; i+=2)
    {
        if (array[i] < array[i+1])
        {
            tmp_max = array[i+1];
            tmp_min = array[i];
        }
        else
        {
            tmp_max = array[i];
            tmp_min = array[i+1];
        }
        if (max < tmp_max)
            max = tmp_max;
        if (tmp_min < min)
            min = tmp_min;
    }
}

// 返回数组array[left...right]中的第i（i>=1）小的元素
int random_select(int *array, int left, int right, int i)
{
    if (left == right)
        return array[left];
    int q = random_partition(array, left, right);
    int k = q - left + 1;
    if (i == k)
        return array[q];
    else if (i < k)
        return random_select(array, left, q-1, i);
    else
        return random_select(array, q+1, right, i-k);
}

// 返回数组array[left...right]中的第i（i>=1）小的元素
// 时间复杂度：最坏情况，O(n)
int select(int *array, int left, int right, int i)
{
    if (left == right)
        return array[right];
    
    int number_elements = right - left + 1;
    int number_subarray = ceil(double(number_elements) / 5);

    // 查找每一组的中位数
    int *median_array = new int[number_subarray];
    int index = 0;
    int j = left;
    while (j <= right && j+4 <= right)
    {
        insertion_sort(array+j, 5);
        median_array[index++] = array[j+2];
        j += 5;
    }
    if (j <= right)
    {
        insertion_sort(array+j, number_elements%5);
        median_array[index] = array[j+(number_elements%5-1)/2];
    }

    // 查找中位数的中位数
    int median_of_median = select(median_array, 0, number_subarray-1, (number_subarray+1)/2);
    delete [] median_array;

    // 以中位数的中位数划分数组
    for (j = left; j <= right; ++j)
    {
        if (array[j] == median_of_median)
            break;
    }
    swap(array[j], array[right]);
    int q = partition(array, left, right);

    // 比较
    int k = q - left + 1;
    if (i == k)
        return array[q];
    else if (i < k)
        return select(array, left, q-1, i);
    else
        return select(array, q+1, right, i-k);
    
}

}
