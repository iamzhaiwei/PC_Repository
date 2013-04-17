// heap_operation.h
//
// last-edit-by: <> 
//
// Description:
// 基于数组的完全二叉树最小堆操作
//////////////////////////////////////////////////////////////////////

#ifndef HEAP_OPERATION_H
#define HEAP_OPERATION_H 1

#include <cstddef>
#include <algorithm>
#include <functional>
#include <typeinfo>

namespace zhaiwei
{

// 建立堆
// array: 数组
// length: 数组长度
// comp: 比较函数对象
// 使数组[0,length-1]成为堆
template <typename T, typename Compare>
void build_heap(T *array, int length, Compare comp);


// 将一个元素压入堆
// array: 数组
// length: 数组长度
// comp: 比较函数对象
// 数组[0,length-2]已经是堆，将array[length-1]压入堆
template <typename T, typename Compare>
void push_heap(T *array, int length, Compare comp);


// 弹出堆首元素
// array: 数组
// length: 数组长度
// comp: 比较函数对象
// 数组[0,length-1]已经是堆，交换array[0]与array[length-1]，再使[0,length-2]成为堆
template <typename T, typename Compare>
void pop_heap(T *array, int length, Compare comp);


// 降低关键字的值
// array: 数组
// length: 数组长度
// position: 关键字的位置
// new_item: 关键字的新值，确保新值小于原值
// comp: 比较函数对象
// 使数组保持为堆
template <typename T, typename Compare>
void heap_decrease_key(T *array, int length, int position, const T &new_item, Compare comp);


// 增加关键字的值
// array: 数组
// length: 数组长度
// position: 关键字的位置
// new_item: 关键字的新值，确保新值大于原值
// comp: 比较函数对象
// 使数组保持为堆
template <typename T, typename Compare>
void heap_increase_key(T *array, int length, int position, const T &new_item, Compare comp);


// 下滤
// array: 数组
// length: 数组长度
// position: 关键字的位置
// comp: 比较函数对象
// 数组[0,length-1]已经是堆, array[position]破坏了堆序，使数组保持为堆
template <typename T, typename Compare>
void heap_percolate_down(T *array, int length, int position, Compare comp);


// 上滤
// array: 数组
// length: 数组长度
// position: 关键字的位置
// comp: 比较函数对象
// 数组[0,length-1]已经是堆, array[position]破坏了堆序，使数组保持为堆
template <typename T, typename Compare>
void heap_percolate_up(T *array, int length, int position, Compare comp);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

// 父结点的下标
static inline int parent(int i)
{
    return (i-1) / 2;
}
// 左儿子的下标
static inline int left(int i)
{
    return i * 2 + 1;
}
// 右儿子的下标
static inline int right(int i)
{
    return (i+1) * 2;
}

// 建立堆
// array: 数组
// length: 数组长度
// comp: 比较函数对象
// 使数组[0,length-1]成为堆
template <typename T, typename Compare>
void build_heap(T *array, int length, Compare comp)
{
    if (array == NULL || length <= 1)
        return;

    for (int i = parent(length-1); i >= 0; --i)
    {
        heap_percolate_down(array, length, i, comp);
    }
}


// 将一个元素压入堆
// array: 数组
// length: 数组长度
// comp: 比较函数对象
// 数组[0,length-2]已经是堆，将array[length-1]压入堆
template <typename T, typename Compare>
void push_heap(T *array, int length, Compare comp)
{
    if (array == NULL || length <= 1)
        return;

    heap_percolate_up(array, length, length-1, comp);
}


// 弹出堆首元素
// array: 数组
// length: 数组长度
// comp: 比较函数对象
// 数组[0,length-1]已经是堆，交换array[0]与array[length-1]，再使[0,length-2]成为堆
template <typename T, typename Compare>
void pop_heap(T *array, int length, Compare comp)
{
    if (array == NULL || length <= 1)
        return;

    std::swap(array[0], array[length-1]);
    heap_percolate_down(array, length-1, 0, comp);
}


// 降低关键字的值
// array: 数组
// length: 数组长度
// position: 关键字的位置
// new_item: 关键字的新值，确保新值小于原值
// comp: 比较函数对象
// 使数组保持为堆
template <typename T, typename Compare>
void heap_decrease_key(T *array, int length, int position, const T &new_item, Compare comp)
{
    if (array == NULL || length <= 1 || position < 0 || position >= length)
        return;

    if (!(new_item < array[position]))
        return;

    array[position] = new_item;
    if (typeid(comp) == typeid(std::less<T>)) // 最小堆
        heap_percolate_up(array, length, position, comp);
    else if (typeid(comp) == typeid(std::greater<int>)) // 最大堆
        heap_percolate_down(array, length, position, comp);
}
    

// 增加关键字的值
// array: 数组
// length: 数组长度
// position: 关键字的位置
// new_item: 关键字的新值，确保新值大于原值
// comp: 比较函数对象
// 使数组保持为堆
template <typename T, typename Compare>
void heap_increase_key(T *array, int length, int position, const T &new_item, Compare comp)
{
    if (array == NULL || length <= 1 || position < 0 || position >= length)
        return;

    if (!(array[position] < new_item))
        return;

    array[position] = new_item;
    if (typeid(comp) == typeid(std::less<T>)) // 最小堆
        heap_percolate_down(array, length, position, comp);
    else if (typeid(comp) == typeid(std::greater<int>)) // 最大堆
        heap_percolate_up(array, length, position, comp);
}

    
// 下滤
// array: 数组
// length: 数组长度
// position: 关键字的位置
// comp: 比较函数对象
// 数组[0,length-1]已经是堆, array[position]破坏了堆序，使数组保持为堆
template <typename T, typename Compare>
void heap_percolate_down(T *array, int length, int position, Compare comp)
{
    if (array == NULL || length <= 1 || position < 0 || position >= length)
        return;

    T tmp = array[position];
    int i, child;
    for (i = position; left(i) < length; i = child)
    {
        child = left(i);
        if (child+1 < length && comp(array[child+1], array[child]))
            ++child;
        if (comp(array[child], tmp))
            array[i] = array[child];
        else
            break;
    }
    array[i] = tmp;
}


// 上滤
// array: 数组
// length: 数组长度
// position: 关键字的位置
// comp: 比较函数对象
// 数组[0,length-1]已经是堆, array[position]破坏了堆序，使数组保持为堆
template <typename T, typename Compare>
void heap_percolate_up(T *array, int length, int position, Compare comp)
{
    if (array == NULL || length <= 1 || position < 0 || position >= length)
        return;

    T tmp = array[position];
    int i, p;
    for (i = position; i > 0; i = p)
    {
        p = parent(i);
        if (comp(tmp, array[p]))
            array[i] = array[p];
    }
    array[i] = tmp;
}

}


#endif // HEAP_OPERATION_H
//////////////////////////////////////////////////////////////////////
