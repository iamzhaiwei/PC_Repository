#ifndef SORT_H
#define SORT_H

#include <cstring>
#include <algorithm>
#include <functional>
#include "heap_operation.h"
#include "my_math.h"

namespace zhaiwei
{

// 插入排序
// 稳定
// 时间复杂度：
// 最好情况是已经是升序排列，O(N),
// 最坏情况是降序排列，O(N^2),
// 平均O(N^2)
template <typename T>
void insertion_sort(T *array, int n)
{
    for (int p = 1; p < n; ++p)
    {
        int j;
        T tmp = array[p];
        for (j = p; j > 0 && array[j-1] > tmp; --j)
            array[j] = array[j-1];
        array[j] = tmp;
    }
}

// 希尔排序
// 不稳定
// 时间复杂度：
// 最好情况，O(N)
// 最坏情况，使用的增量序列不同，最坏情况下时间复杂度也不同。使用希尔增量时，是O(N^2)
// 平均情况，长期未解决
template <typename T>
void shell_sort(T *array, int n)
{
    for (int increment = n / 2; increment > 0; increment /= 2)
    {
        for (int i = increment; i < n; ++i)
        {
            T tmp = array[i];
            int j;
            for (j = i; j >= increment && array[j-increment] > tmp; j -= increment)
                array[j] = array[j-increment];
            array[j] = tmp;
        }
    }
}


// 选择排序
// 不稳定
// 时间复杂度：最好、最坏、平均情况都是O(N^2)
template <typename T>
void selection_sort(T *array, int n)
{
    if (array == NULL || n <= 1)
        return;

    for (int i = 0; i < n-1; ++i)
    {
        int min_idx = i;
        for (int j = i+1; j < n; ++j)
        {
            if (array[j] < array[min_idx])
                min_idx = j;
        }
        swap(array[i], array[min_idx]);
    }
}


// 堆排序
// 不稳定
// 时间复杂度：最好、最坏、平均情况都是O(n*log(n))
template <typename T>
void heap_sort(T *array, int n)
{
    if (array == NULL || n <= 1)
        return;

    build_heap(array, n, std::greater<T>());
    for (int i = n; i >= 1; --i)
        pop_heap(array, i, std::greater<T>());
}


// 冒泡排序
// 稳定
// 时间复杂度：最好、最坏、平均情况都是O(N^2)
template <typename T>
void bubble_sort(T *array, int n)
{
    if (array == NULL || n <= 1)
        return;

    for (int i = n-1; i >= 1; --i)
    {
        for (int j = 0; j <= i-1; ++j)
        {
            if (array[j+1] < array[j])
                std::swap(array[j+1], array[j]);
        }
    }
}
// 带交换标志的冒泡排序
// 稳定
// 时间复杂度：
// 最好，O(N)
// 最坏，O(N^2)
// 平均，O(N^2)
template <typename T>
void bubble_sort_with_Flag(T *array, int n)
{
    if (array == NULL || n <= 1)
        return;

    // 一趟冒泡过程中，最后一次交换的位置
    // 初始，假设在最后一个位置交换
    int exchange_position = n;

    while (exchange_position > 0)
    {
        // 未排序范围为[0,bound]
        int bound = exchange_position - 1;

        // 假设本次冒泡过程没有交换
        exchange_position = 0;

        for (int i = 0; i < bound; ++i)
        {
            if (array[i+1] < array[i])
            {
                std::swap(array[i+1], array[i]);
                exchange_position = i + 1;
            }
        }
    }
}

// 归并排序
// 稳定
// 时间复杂度：最好，最坏，平均都是O(N*log(N))
// 空间复杂度：O(N)
// [left,right-1]和[ritht,right_end]归并
template <typename T>
static void merge(T *array, T *tmp_array, int left, int right, int right_end)
{
    int left_end = right - 1;
    int tmp_pos = left;
    int number = right_end - left + 1;
    while (left <= left_end && right <= right_end)
    {
        if (array[left] <= array[right])
            tmp_array[tmp_pos++] = array[left++];
        else
            tmp_array[tmp_pos++] = array[right++];
    }

    while (left <= left_end)
        tmp_array[tmp_pos++] = array[left++];
    while (right <= right_end)
        tmp_array[tmp_pos++] = array[right++];

    for (int i = 0; i <number; ++i, --right_end)
        array[right_end] = tmp_array[right_end];
}
// [left,right]
template <typename T>
static void msort(T *array, T *tmp_array, int left, int right)
{
    if (left < right)
    {
        int center = left + (right - left) / 2;
        msort(array, tmp_array, left, center);
        msort(array, tmp_array, center+1, right);
        merge(array, tmp_array, left, center+1, right);
    }
}
template <typename T>
void merge_sort(T *array, int n)
{
    T *tmp_array = new T[n];
    if (tmp_array != NULL)
    {
        msort(array, tmp_array, 0, n - 1);
        delete [] tmp_array;
    }
}

// 快速排序
// 不稳定
// 时间复杂度：
// 最好，O(N*log(N))
// 最坏，O(N^2)
// 平均，O(N*log(N))
const int qsort_cutoff = 3;
// 三数中值作为枢纽元
// [left,right]
template <typename T>
static T median_of_three(T *array, int left, int right)
{
    int center = left + (right - left) / 2;
    if (array[center] < array[left])
        std::swap(array[center], array[left]);
    if (array[right] < array[left])
        std::swap(array[right], array[left]);
    if (array[right] < array[center])
        std::swap(array[right], array[center]);

    std::swap(array[center], array[right-1]);

    return array[right - 1];
}
// [left,right]
template <typename T>
static void qsort(T *array, int left, int right)
{
    if (left + qsort_cutoff <= right)
    {
        T pivot = median_of_three(array, left, right);
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

        qsort(array, left, i-1);
        qsort(array, i+1, right);
    }
    else
        insertion_sort<T>(array + left, right - left + 1);
}
template <typename T>
void quick_sort(T *array, int n)
{
    if (array == NULL || n <= 1)
        return;
    qsort(array, 0, n-1);
}


// 计数排序
// 稳定
// 时间复杂度：最好、最坏和平均情况一样，当输入的元素是 n 个 0 到 k 之间的整数时，它的运行时间是 O(n + k)
// 空间复杂度：O(n+k)
void counting_sort(int *array, int n)
{
    if (array == NULL || n <= 1)
        return;
    
    int *p_max = std::max_element(array, array+n);
    int *p_min = std::min_element(array, array+n);
    int max = *p_max, min = *p_min;
    
    int number = max - min + 1;
    int *count = new int[number];
    memset(count, 0, sizeof(int)*number);
    for (int i = 0; i < n; ++i)
        ++count[array[i]-min];
    for (int i = 1; i < n; ++i)
        count[i] += count[i-1];
    
    int *out_array = new int[n];
    for (int i = n-1; i >= 0; --i) // 倒序保证稳定性
    {
        out_array[count[array[i]-min]-1] = array[i];
        --count[array[i]-min];
    }
    for (int i = 0; i < n; ++i)
        array[i] = out_array[i];

    delete [] count;
    delete [] out_array;
}


// 桶排序
// 可对整数、浮点数等排序
// 稳定
// 时间复杂度：假设使用k个桶，复杂度为O(k)+O(n)+O(k*每个桶的平均排序时间)
// 空间复杂度：O(K)
void bucket_sort(int *array, int n)
{
    if (array == NULL || n <= 1)
        return;

    int *p_max = std::max_element(array, array+n);
    int *p_min = std::min_element(array, array+n);
    int max = *p_max, min = *p_min;

    int bucket_number = max - min + 1; // 每个整数一个桶
    int *buckets = new int[bucket_number];
    memset(buckets, 0, sizeof(int)*bucket_number);

    for (int i = 0; i < n; ++i)
        ++buckets[array[i]-min];

    int position = 0;
    for (int i = 0; i < bucket_number; ++i)
    {
        while (buckets[i] > 0)
        {
            array[position] = i + min;
            ++position;
            --buckets[i];
        }
    }
    
    delete [] buckets;
}


// 基数排序
// 对整数、浮点数、字符串等排序，见维基百科
// max_digit_number: 数组中元素的最大位数
// 稳定
// 时间复杂度：假设最大位数为k，O(k*n)，不一定优于O(n*log(n))
// 空间复杂度：O(n)
void radix_sort(int *array, int n, int max_digit_number)
{
    if (array == NULL || n <= 1)
        return;

    // 十进制
    // 对每位数字，计数排序
    int *count = new int[10];
    int *tmp_array = new int[n];
    for (int i = 1; i <= max_digit_number; ++i)
    {
        int digit;
        memset(count, 0, sizeof(int)*10);
        for (int j = 0; j < n; ++j)
        {
            digit = get_digit(array[j], i);
            ++count[digit];
        }
        for (int k = 1; k < 10; ++k)
            count[k] += count[k-1];
        for (int j = n-1; j >= 0; --j) // 必须倒序
        {
            digit = get_digit(array[j], i);
            tmp_array[count[digit]-1] = array[j];
            --count[digit];
        }
        for (int j = 0; j < n; ++j)
            array[j] = tmp_array[j];
    }

    delete [] count;
    delete [] tmp_array;
}

}

#endif
