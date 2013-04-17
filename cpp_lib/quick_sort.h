// quick_sort.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef QUICK_SORT_H
#define QUICK_SORT_H 1

namespace zhaiwei
{

// 以array[right]为主元划分数组array[left...right]，返回划分后主元的下标
int partition(int *array, int left, int right);

// 随机划分数组array[left...right], 返回划分后主元的下标
int random_partition(int *array, int left, int right);

}


#endif // QUICK_SORT_H
//////////////////////////////////////////////////////////////////////
