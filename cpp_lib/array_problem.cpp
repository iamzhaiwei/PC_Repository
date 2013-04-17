// bstree_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "array_problem.h"
#include <cmath>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <boost/multi_array.hpp>
#include "my_algorithm.h"
#include "my_math.h"
#include "random_problem.h"

using namespace std;
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{

//百度笔试：给定一个存放整数的数组，重新排列数组使得数组左边为奇数，右边为偶数。
//要求：空间复杂度 O(1)，时间复杂度为 O（n）。
void adjust_array_left_odd_right_even(int *array, int n)
{
    if (array == NULL || n <= 1) return;

    int left = 0, right = n - 1;
    while (left < right)
    {
        while (is_odd(array[left]))
            ++left;
        while (is_even(array[right]))
            --right;
        if (left < right)
            std::swap<int>(array[left], array[right]);
    }
}


// 微软面试
// 一个整数数列，元素取值可能是0~65535中的任意一个数，相同数值不会重复出现。0是例外，可以反复出现。
// 请设计一个算法，当你从该数列中随意选取5个数值，判断这5个数值是否连续相邻。
// 注意：
// - 5个数值允许是乱序的。比如： 8 7 5 0 6
// - 0可以通配任意数值。比如：8 7 5 0 6 中的0可以通配成9或者4
// - 0可以多次出现。
// - 复杂度如果是O(n2)则不得分。
// 解题思路：
// 1.取5个数中非0的最大数和最小数，之差不大于4则连续，否则不连续。
// 2.要增加两个特例： 1）全0算连续，2）只有一个非0算连续
bool array_is_continuous(int array[5])
{
	int max = 0, min = 65535;
	int zero_cnt = 0;
	for (int i = 0; i < 5; ++i)
	{
		if (array[i] == 0)
			++zero_cnt;
		else
		{
			if (array[i] > max)
				max = array[i];
			else if (array[i] < min)
				min = array[i];
		}
	}
	if (zero_cnt >= 4 || max-min <= 4)
		return true;
	else
		return false;
}


//用递归的方法判断整数组a[N]是不是升序排列
bool array_is_increasing_order_recursion(int *array, int begin, int end)
{
    if (array == NULL || begin < 0 || end < 0 || begin > end)
        return false;

    if (begin == end)
        return true;

    return array[begin] <= array[begin+1] && array_is_increasing_order_recursion(array, begin+1, end);
}


// 百度笔试题
// 数组array[begin,mid-1] 和 array[mid,end-1]，都分别升序排列。将其merge成有序数组al[0,num-1]，要求空间复杂度O(1)
void array_merge_in_place(int *array, int begin, int mid, int end)
{
	if (array == NULL) return;

	int i = begin, j = mid;
	while (i < mid && j < end)
	{
		while (array[i] <= array[j]) ++i;
		++j;
		while (array[i] > array[j]) ++j;
		array_reverse(array, i, mid, j);
		i += (j-mid);
		mid = j;
	}
}


// google面试题
// 题目：输入a1,a2,...,an,b1,b2,...,bn,
// 在O(n)的时间,O(1)的空间将这个序列顺序改为a1,b1,a2,b2,a3,b3,...,an,bn，
// 且不需要移动，通过交换完成，只需一个交换空间。
// 算法不对
void array_rearrange(int *array, int begin, int end)
{
    if (array == NULL || begin+1 >= end)
        return;
    int mid = begin + (end-begin)/2;
    for (int i = begin+(mid-begin)/2+1, j = mid; i != mid && j != end; ++i, ++j)
        swap(array[i], array[j]);
    array_rearrange(array, begin, mid);
    array_rearrange(array, mid, end);
}


// 数组逆序
// 将数组array[begin...end)中的元素逆序排列
void array_reverse(int *array, int begin, int end)
{
	if (array == NULL) return;

	--end;
	for ( ; begin < end; ++begin, --end)
	{
		swap(array[begin], array[end]);
	}
}
// 将数组前半部分array[begin,mid)与后半部分[mid,end)逆序，但前半部分和后半部分本身保持顺序不变
void array_reverse(int *array, int begin, int mid, int end)
{
	array_reverse(array, begin, mid);
	array_reverse(array, mid, end);
	array_reverse(array, begin, end);
}


// 搜狗笔试题：一个长度为n的数组a[0],a[1],...,a[n-1]。现在更新数组的名个元素，
// 即a[0]变为a[1]到a[n-1]的积，a[1]变为a[0]和a[2]到a[n-1]的积，...，
// a[n-1]为a[0]到a[n-2]的积（就是除掉当前元素，其他所有元素的积）。程序要求：
// 具有线性复杂度，且不能使用除法运算符。
void array_update_to_product(int *array, int length)
{
    if (array == NULL || length <= 0)
        return;

    // tmp[i]记录array[i]左边元素的乘积
    int *left = new int[length];
    left[0] = 1;
    for (int i = 1; i != length; ++i)
    {
        left[i] = left[i-1] * array[i-1];
    }
    // right记录array[i]右边元素的乘积
    int right = 1, new_right = 1;
    for (int i = length-1; i >= 0; --i)
    {
        new_right = right * array[i];
        array[i] = left[i] * right;
        right = new_right;
    }
}
// 扩展：2012年4月67日的腾讯暑期实习生招聘笔试中，出了一道与上述21题类似的题，原题大致如下：
// 两个数组a[N]，b[N]，其中A[N]的各个元素值已知，现给b[i]赋值，b[i] = a[0]*a[1]*a[2]...*a[N-1]/a[i]；
// 要求：1.不准用除法运算
// 2.除了循环计数值，a[N],b[N]外，不准再用其他任何变量（包括局部变量，全局变量等）
// 3.满足时间复杂度O（n），空间复杂度O（1）。
void array_multiply_to_product_v1(int *in_array, int *out_array, int length)
{
    if (in_array == NULL || out_array == NULL || length <= 0)
        return;

    for (int i = 0; i != length; ++i)
        out_array[i] = 1;
    int left = 1, right = 1;
    for (int i = 0; i != length; ++i)
    {
        out_array[i] *= left;
        out_array[length-i-1] *= right;
        left *= in_array[i];
        right *= in_array[length-i-1];
    }
}
void array_multiply_to_product_v2(int *in_array, int *out_array, int length)
{
    if (in_array == NULL || out_array == NULL || length <= 0)
        return;

    out_array[0] = 1;
    for (int i = 1; i < length; ++i)
    {
        out_array[0] *= in_array[i-1];
        out_array[i] = out_array[0];
    }
    out_array[0] = 1;
    for (int i = length-2; i >= 1; --i)
    {
        out_array[0] *= in_array[i+1];
        out_array[i] *= out_array[0];
    }
    out_array[0] *= in_array[1];
}


//在递减序列中二分查找一个元素，若找到，返回其索引，若没有找到，返回-1.
// Parameter:
// array: 数组地址
// begin: 数组第一个元素的索引
// end: 数组最后一个元素的索引的下一个索引
// item: 要查找的元素
// Return value:
// 若找到，返回其索引，若没有找到，返回-1.
int bisearch_in_decreasing_array(int *array, int begin, int end, int item)
{
    if (array == NULL || begin < 0 || end < 0 || begin >= end)
        return -1;

    int mid;
    while (begin < end)
    {
        mid = begin + (end - begin) / 2;
        if (item < array[mid])
            begin = mid + 1;
        else if (array[mid] < item)
            end = mid;
        else
            return mid;
    }
    return -1;
}


// 在递增序列中二分查找一个元素，若找到，返回其索引，若没有找到，返回-1.
// Parameter:
// array: 数组地址
// begin: 数组第一个元素的索引
// end: 数组最后一个元素的索引的下一个索引
// item: 要查找的元素
// Return value:
// 若找到，返回其索引，若没有找到，返回-1.
int bisearch_in_increasing_array(int *array, int begin, int end, int item)
{
    if (array == NULL || begin < 0 || end < 0 || begin >= end)
        return -1;

    int mid;
    while (begin < end)
    {
        mid = begin + (end - begin) / 2;
        if (item < array[mid])
            end = mid;
        else if (array[mid] < item)
            begin = mid + 1;
        else
            return mid;
    }
    return -1;
}


//一个数组是由一个递减数列左移若干位形成的，比如{4，3，2，1，6，5}
//是由{6，5，4，3，2，1}左移两位形成的，在这种数组中查找某一个数。
//若找到，返回其索引，若没有找到，返回-1.
// Parameter:
// array: 数组地址
// begin: 数组第一个元素的索引
// end: 数组最后一个元素的索引的下一个索引
// item: 要查找的元素
// Return value:
// 若找到，返回其索引，若没有找到，返回-1.
int bisearch_in_lshift_decreasing_array(int *array, int begin, int end, int item)
{
    if (array == NULL || begin < 0 || end < 0 || begin >= end)
        return -1;

    int mid;
	while (begin < end)
	{
		mid = begin + (end - begin) / 2;
		if (item == array[mid])
		{
			return mid;
		}
		else if (array[begin] >= array[mid])
		{
			if (array[begin] >= item && item > array[mid])
				end = mid;
			else
				begin = mid + 1;
		}
		else
		{
			if (array[mid] > item && item >= array[end-1])
				begin = mid + 1;
			else
				end = mid;
		}
	}
	return -1;
}


//一个数组是由一个递增数列左移若干位形成的，比如{3, 4, 5, 1, 2}是由{1, 2, 3, 4, 5}
//左移两位形成的，在这种数组中查找某一个数。
//若找到，返回其索引，若没有找到，返回-1.
// Parameter:
// array: 数组地址
// begin: 数组第一个元素的索引
// end: 数组最后一个元素的索引的下一个索引
// item: 要查找的元素
// Return value:
// 若找到，返回其索引，若没有找到，返回-1.
int bisearch_in_lshift_increasing_array(int *array, int begin, int end, int item)
{
	if (array == NULL || begin < 0 || end <= 0)
		return -1;
	
	int mid;
	while (begin < end)
	{
		mid = begin + (end - begin) / 2;
		if (item == array[mid])
		{
			return mid;
		}
		else if (array[mid] <= array[end-1])
		{
			if (array[mid] < item && item <= array[end-1])
				begin = mid + 1;
			else
				end = mid;
		}
		else
		{
			if (array[begin] <= item && item < array[mid])
				end = mid;
			else
				begin = mid + 1;
		}
	}
	return -1;
}


// 微软10.15笔试：对于一个数组{1,2,3}它的子数组有{1,2}，{1,3}{2,3}，{1,2,3}，元素之间可以不是连续的，
// 对于数组{5,9,1,7,2,6,3,8,10,4}，升序子序列有多少个？或者换一种表达为：数组int a[]={5,9,1,7,2,6,3,8,10,4}。
// 求其所有递增子数组(元素相对位置不变)的个数，例如：{5，9}，{5，7，8，10}，{1，2，6，8}。
// 动态规划
int count_all_increasing_subarray_v1(int *array, int length)
{
	if (array == NULL || length <= 0)
		return 0;

	// subarray_count[i]记录以array[i]为最后一个元素的递增子数组的数目
	vector<int> subarray_count(length, 0);
	for (int i = 1; i < length; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (array[i] > array[j])
				subarray_count[i] = subarray_count[i] + subarray_count[j] + 1;
		}
	}

	int count = 0;
	for (int i = 1; i < length; ++i)
		count += subarray_count[i];
	return count;
}
// 未解决。空间和时间负载度为O(n)
// 测试用例参考：http://blog.csdn.net/julianxiong/article/details/7322665
int count_all_increasing_subarray_v2(int *array, int length)
{
	if (array == NULL || length <= 0)
		return 0;

	// subarray_count[i]记录以array[i]结尾子数组的递增子数组的数目
	vector<int> subarray_count(length, 0);
	// less_count[i]记录小于array[i]的元素的数目
	vector<int> less_count(length, 0);
	for (int i = 1; i < length; ++i)
	{
		// 第一种情况：递增子数组不包含array[i]
		subarray_count[i] = subarray_count[i-1];

		// 第二种情况：递增子数组包含array[i]
		for (int j = i-1; j >= 0; ++j)
		{
			if (array[i] > array[j])
			{
				less_count[i] = less_count[j] + 1;
				subarray_count[i] = subarray_count[i] + subarray_count[j] + less_count[i];
				break;
			}
		}
	}
	for (int i = 0; i < length; ++i)
		cout << subarray_count[i] << " ";
	cout << endl;

	for (int i = 0; i < length; ++i)
		cout << less_count[i] << " ";
	cout << endl;

	return subarray_count[length-1];
}



// 2010年中兴面试题
// 编程求解：
// 输入两个整数 n 和 m，从数列1，2，3.......n中随意取几个数,
// 使其和等于 m ,要求将其中所有的可能组合列出来。
static void find_additive_factors(int n, int m, vector<int> &factors, int &count)
{
    if (m < 0)
        return;

    if (m == 0)
    {
        for (std::size_t i = 0; i != factors.size(); ++i)
            cout << factors[i] << " ";
        cout << endl;
        ++count;
        return;
    }

    if (n <= 0)
        return;

    find_additive_factors(n-1, m, factors, count); // 不包含n

    factors.push_back(n);
    find_additive_factors(n-1, m-n, factors, count); // 包含n

    factors.pop_back();
}
int find_additive_factors(int n, int m)
{
    if (n <= 0 || m <= 0)
        return 0;

    vector<int> factors;
    int count = 0;
    find_additive_factors(n, m, factors, count);
    return count;
}


// 网易游戏笔试题：给一个有序数组array[n]，和一个数字m，判断m是否是这些数组里面的
// 数的和。（类似于微软面试100题2010年版第4题，即相当于给定一棵树，然后给定一个数，
// 要求把那些 相加的和等于这个数的 所有节点打印出来）。
// array: 升序排列的整数数组
// length: 数组长度
// m: 数字m
// factors: 已经找到的加法因子
// count: 因子组合的数目
static void find_additive_factors(int *array, int length, int m, vector<int> &factors,
                                  int &count)
{
    if (m < 0)
        return;

    if (m == 0)
    {
        ++count;
        for (std::size_t i = 0; i != factors.size(); ++i)
            cout << factors[i] << " ";
        cout << endl;
        return;
    }

    if (length == 0)
        return;

    // 数组是升序排列，array[0]是最小值。m比最小值小，若包含数组中任一元素，因子的和就超过了m的大小;
    // 若不包含任一元素，因子的和就比m小，所以数组中任一元素不可能是当前因子组合中的因子，直接返回。
    if (m < array[0])
        return;

    // 不包含array[0]
    find_additive_factors(array+1, length-1, m, factors, count);

    // 包含array[0]
    factors.push_back(array[0]);
    find_additive_factors(array+1, length-1, m-array[0], factors, count);

    factors.pop_back();
}
int find_additive_factors(int *array, int length, int m)
{
    if (array == NULL || length <= 0)
        return 0;

    vector<int> factors;
    int count = 0;
    find_additive_factors(array, length, m, factors, count);
    return count;
}


//在升序排列的整数数组中查找两个整数，使这两个整数的和等于给定值
bool find_two_additive_factors(int *array, int n, int sum, int &p1, int &p2)
{
    p1 = 0;
    p2 = n - 1;

    while (p1 < p2)
    {
        if (array[p1]+array[p2] < sum)
            ++p1;
        else if (array[p1]+array[p2] > sum)
            --p2;
        else
            break;
    }
    if (p1 < p2)
        return true;
    else
        return false;
}


// 在整型数组中查找出现次数超过一半的数
int find_int_appear_more_than_half(int *array, int n)
{
    int data;
    int cnt = 0;
    for (int i = 0; i != n; ++i)
    {
        if (cnt == 0)
        {
            data = array[i];
            cnt = 1;
        }
        else
        {
            if (data == array[i])
                ++cnt;
            else
                --cnt;
        }
    }
    return data;
}


//在一个 int 数组里查找这样的数，它大于等于左侧所有数，小于等于右侧所有数。
//两个辅助数组，三次遍历
void find_int_left_less_right_greater_v1(int *array, int n, int *out, int &length)
{
    //a[i]记录从开始到array[i]的最大值
    int *a = new int[n];
    //b[i]记录从array[i]到结尾的最小值
    int *b = new int[n];

    a[0] = array[0];
    for (int i = 1; i != n; ++i)
    {
        if (array[i] > a[i-1])
            a[i] = array[i];
        else
            a[i] = a[i-1];
    }

    b[n-1] = array[n-1];
    for (int i = n-2; i >= 0; --i)
    {
        if (array[i] < b[i+1])
            b[i] = array[i];
        else
            b[i] = b[i+1];
    }

    length = 0;
    for (int i = 0; i != n; ++i)
    {
        if (array[i] >= a[i] && array[i] <= b[i])
            out[length++] = array[i];
    }

    delete [] a;
    delete [] b;
}
//一个辅助数组，两次遍历
void find_int_left_less_right_greater_v2(int *array, int n, int *out, int &length)
{
    //b[i]记录从array[i]到结尾的最小值
    int *b = new int[n];

    b[n-1] = array[n-1];
    for (int i = n-2; i >= 0; --i)
    {
        if (array[i] < b[i+1])
            b[i] = array[i];
        else
            b[i] = b[i+1];
    }

    length = 0;
    //记录当前的最大值
    int max = array[0];
    for (int i = 0; i != n; ++i)
    {
        if (array[i] >= max)
        {
            max = array[i];
            if (array[i] <= b[i])
                out[length++] = array[i];
        }
    }

    delete [] b;
}


//求随机数构成的数组中找到长度大于等于3的最长的等差数列, 输出等差数列由小到大:
//如果没有符合条件的就输出[0, 0]
int find_longest_arithmetic_sequence(int *array, int n)
{
    if (array == NULL || n <= 3)
    {
        std::cout << "[0,0]" << std::endl;
        return -1;
    }

    std::multiset<int> mset;
    for (int i = 0; i != n; ++i)
        mset.insert(array[i]);

    // 最大的公差
    int max_diff = (*mset.rbegin() - *mset.begin()) / 3;
    int max_a1, max_d, max_len = 0, length = 0;
    int d;
    std::multiset<int>::iterator iter1, iter2;
    std::pair< std::multiset<int>::iterator, std::multiset<int>::iterator > range;
    for (iter1 = mset.begin(); iter1 != mset.end(); iter1 = mset.upper_bound(*iter1))
    {
        for (iter2 = iter1, ++iter2; iter2 != mset.end(); iter2 = mset.upper_bound(*iter2))
        {
            if ( (d = *iter2 - *iter1) > max_diff)
                break;
            if (d == 0)
            {
                length = mset.count(*iter1);
            }
            else
            {
                length = 2;
                while (true)
                {
                    range = mset.equal_range(*iter1+length*d);
                    if (range.first != range.second)
                        ++length;
                    else
                        break;
                }
            }
            if (length > max_len)
            {
                max_len = length;
                max_a1 = *iter1;
                max_d = d;
            }
        }
    }

    if (max_len >= 3)
    {
        std::cout << "[";
        for (int i = 0; i != max_len; ++i)
            std::cout << max_a1+i*max_d << " ";
        std::cout << "]";
    }
    else
        std::cout << "[0,0]";
    std::cout << std::endl;
    return max_len;
}


//求一个数组的最长递减子序列，返回其长度
static void output_lds(int *array, int *aid_array, int max_idx, int *subsequence, int max_len)
{
    int idx = max_idx, sub_idx = max_len - 1;
    while (idx >= 0 && sub_idx >= 0)
    {
        subsequence[sub_idx--] = array[idx];
        for (int i = idx-1; i >= 0; --i)
        {
            if (aid_array[i]+1 == aid_array[idx] && array[i] > array[idx])
            {
                idx = i;
                break;
            }
        }
    }
}
int find_longest_decreasing_subsequence(int *array, int *subsequence, int n)
{
    //辅助数组，aid_array[i]记录以array[i]结尾的递减序列的长度
    int *aid_array = new int[n];
    //max_v[i]记录长度为i的递减序列的最小元素的最大值
    int *max_v = new int[n+1];

    for (int i = 0; i != n; ++i)
        aid_array[i] = 1;

    int *p_max = std::max_element<int *>(array, array+n);
    max_v[0] = *p_max;
    max_v[1] = array[0];

    int max_len = 1, max_idx = 0;
    for (int i = 1; i != n; ++i)
    {
        int j = bisearch_in_decreasing_array(max_v, 0, max_len+1, array[i]);
        --j;
        aid_array[i] = j + 1;

        if (aid_array[i] > max_len)
        {
            max_len = aid_array[i];
            max_idx = i;
            max_v[max_len] = array[i];
        }
        else if (max_v[j] > array[i] && array[i] > max_v[j+1])
        {
            max_v[j+1] = array[i];
        }
    }

    output_lds(array, aid_array, max_idx, subsequence, max_len);
    delete [] aid_array;
    delete [] max_v;
    return max_len;
}


// 求一个数组的最长递增子序列，返回其长度
// 一般方法
int find_longest_increasing_subsequence(int *array, int *subsequence, int n)
{
    //最长递增子序列的长度
    int max_len = 0;
    //当前递增子序列
    int *aid_array = new int[n];
    //当前递增子序列的长度
    int length;
    for (int i = 0; i != n; ++i)
    {
        aid_array[0] = array[i];
        length = 1;
        for (int j = i+1; j != n; ++j)
        {
            if (array[j] > aid_array[length-1])
                aid_array[length++] = array[j];
        }
        if (length > max_len)
        {
            for (int k = 0; k != length; ++k)
                subsequence[k] = aid_array[k];
            max_len = length;
        }
    }
    delete [] aid_array;
    return max_len;
}
// 输出最长递增子序列
static void output_lis(int *array, int *aid_array, int max_idx, int *subsequence, int max_len)
{
    int idx = max_idx, sub_idx = max_len - 1;
    while (idx >= 0 && sub_idx >= 0)
    {
        subsequence[sub_idx--] = array[idx];
        for (int i = idx-1; i >= 0; --i)
        {
            if (aid_array[i]+1 == aid_array[idx] && array[i] < array[idx])
            {
                idx = i;
                break;
            }
        }
    }
}
// 动态规划方法
int find_longest_increasing_subsequence_dp(int *array, int *subsequence, int n)
{
    //aid_array[i]记录以array[i]结尾的最长递增子序列的长度
    int *aid_array = new int[n];
    for (int i = 0; i != n; ++i)
    {
        aid_array[i] = 1;
        for (int j = 0; j != i; ++j)
        {
            if (array[i] > array[j] && aid_array[j]+1 > aid_array[i])
            {
                aid_array[i] = aid_array[j] + 1;
            }
        }
    }

    int max_len = aid_array[0], max_idx = 0;
    for (int i = 1; i != n; ++i)
    {
        if (aid_array[i] > max_len)
        {
            max_len = aid_array[i];
            max_idx = i;
        }
    }

    output_lis(array, aid_array, max_idx, subsequence, max_len);
    delete [] aid_array;
    return max_len;
}
// 更快方法
int find_longest_increasing_subsequence_fast(int *array, int *subsequence, int n)
{
    //aid_array[i]记录以array[i]结尾的最长递增子序列的长度
    int *aid_array = new int[n];
    //max_v[i]记录长度为i的递增子序列最大元素的最小值
    int *max_v = new int[n+1];

    int *p_min = std::min_element<int *>(array, array+n);
    max_v[0] = *p_min;
    max_v[1] = array[0];

    for (int i = 0; i != n; ++i)
        aid_array[i] = 1;

    int max_len = 1, max_idx = 0;
    for (int i = 1; i != n; ++i)
    {
        int j;
        //穷举遍历
        /*
        for (j = max_len; j >= 0; --j)
        {
            if (array[i] > max_v[j])
            {
                aid_array[i] = j + 1;
                break;
            }
        }
        */
        //二分查找
        j = bisearch_in_increasing_array(max_v, 0, max_len+1, array[i]);
        --j;
        aid_array[i] = j + 1;

        if (aid_array[i] > max_len)
        {
            max_len = aid_array[i];
            max_idx = i;
            max_v[max_len] = array[i];
        }
        else if (max_v[j] < array[i] && array[i] < max_v[j+1])
        {
            max_v[j+1] = array[i];
        }
    }

    output_lis(array, aid_array, max_idx, subsequence, max_len);
    delete [] aid_array;
    delete [] max_v;
    return max_len;

}


// 微软面试题：
// 有一个整数数组，请求出两两之差绝对值最小的值。
// 记住，只要得出最小值即可，不需要求出是哪两个数。
// 先对数组排序，再求相邻两数的差的绝对值的最小值
int find_min_difference(int *array, int n)
{
    if (array == NULL || n <= 1)
        return -1;

    if (n == 2)
        return abs(array[0]-array[1]);

    std::sort<int *>(array, array+n);

    int min_diff = abs(array[0]-array[1]);
    int diff;
    for (int i = 1; i <= n-2; ++i)
    {
        diff = abs(array[i]-array[i+1]);
        if (diff < min_diff)
            min_diff = diff;
    }
    return min_diff;
}


//输入n个整数，输出其中最小的k个
void find_min_k_ints(int *array_in, int n, int *array_out, int k)
{
    if (array_in == NULL || array_out == NULL || n <= 0 || k <= 0 || k > n)
        return;

    std::priority_queue< int, std::vector<int>, std::greater<int> > pq;
    for (int i = 0; i != k; ++i)
        pq.push(array_in[i]);
    for (int i = k; i != n; ++i)
    {
    }
}


// 在排序数组中，找出给定数字的出现次数
// 比如 [1, 2, 2, 2, 3] 中2的出现次数是3次。
// Parameter:
// array: 排序数组的地址
// length: 数组长度
// item: 要查找的元素
// Return value:
// 给定数字在排序数组中的出现次数
int find_occurrence_number_in_odered_array(int *array, int length, int item)
{
    if (array == NULL || length <= 0)
        return 0;

    // 查找给定数字是否存在
    int idx = bisearch_in_increasing_array(array, 0, length, item);
    if (idx == -1 || idx == length || array[idx] != item)
        return 0;

    int begin = idx, end = idx;
    // 查找给定数字段的开始位置
    while (true)
    {
        idx = bisearch_in_increasing_array(array, 0, begin, item);
        if (idx >= 0 && idx < begin && array[idx] == item)
            begin = idx;
        else
            break;
    }
    // 查找给定数字段的结束位置
    while (true)
    {
        idx = bisearch_in_increasing_array(array, end+1, length, item);
        if (idx >= end+1 && idx < length && array[idx] == item)
            end = idx;
        else
            break;
    }
    return end-begin+1;
}


// 找出数组中唯一的重复元素
// 1-1000放在含有1001个元素的数组中，只有唯一的一个元素值重复，其它均只出现一次．
// 每个数组元素只能访问一次，设计一个算法，将它找出来；不用辅助存储空间，
// 能否设计一个算法实现？
int find_single_duplicate_int()
{
    int *array = new int[1001];
    for (int i = 0; i <= 999; ++i)
        array[i] = i + 1;
    array[1000] = random_int(1, 1000);
    cout << array[1000] << endl;
    int xor_res = 0;
    for (int i = 0; i < 1001; ++i)
        xor_res ^= array[i];
    for (int i = 1; i <= 1000; ++i)
        xor_res ^= i;
    cout << xor_res << endl;
    return xor_res;
}


//有这样一种编码：如，N=134，M=f(N)=143,N=020,M=fun(N)=101,其中N和M的位数一样，
// N,M均可以以0开头，N,M的各位数之和要相等，即1+3+4=1+4+3，且M是大于N中最小的一个，
// 现在求这样的序列S,N为一个定值，其中S(0)=N，S(1)=fun(N),S(2)=fun(S(1))。
static void print_code(int *array, int length)
{
	for (int i = 0; i < length; ++i)
		cout << array[i];
	cout << endl;
}
void find_the_sequence(int *array, int length)
{
	if (array == NULL || length <= 0)
		return;

	print_code(array, length);
	while (true)
	{
		int i, j;
		// 从最低位开始，找满足一下2个条件的数位array[i]：
		// (1) array[i] > 0
		// (2) array[i-1] < 9
		// 若只满足条件(1), 那么例如，699的下一个编码会找到798，但是实际上应该是789
		for (i = length-1; i > 0; --i)
		{
			if (array[i] > 0 && array[i-1] < 9)
				break;
		}
		if (i == 0)
			break;
		int data = array[i];
		array[i] = 0; // 当前位设为0
		array[i-1] += 1; // 前一位加1
		array[length-1] += data-1; // 剩下的值加到最后一位
		for (j = i-1; j > 0; --j)
		{
			if (array[j] >= 10)
			{
				array[j-1] += array[j]-9;
				array[j] = 9;
			}
		}
		if (array[0] >= 10)
			break;

		for (j = length-1; j > i; --j)
		{
			if (array[j] >= 10)
			{
				array[j-1] += array[j]-9;
				array[j] = 9;
			}
		}

		print_code(array, length);
	}
}


//一个整型数组里除了两个数字之外，其他的数字都出现了两次。
//请写程序找出这两个只出现一次的数字。要求时间复杂度是 O(n)，空间复杂度是 O(1)。
void find_two_ints_appear_once(int *array, int n, int &i1, int &i2)
{
    int xor_res = 0;
    for (int i = 0; i != n; ++i)
        xor_res ^= array[i];

    unsigned int idx_1 = index_of_first_1_bit(xor_res);
    i1 = i2 = 0;
    for (int i = 0; i != n; ++i)
    {
        if (is_1_bit_at_index(array[i], idx_1))
            i1 ^= array[i];
        else
            i2 ^= array[i];
    }
}


// 一个从小到大排序的整数数组，元素都是在[0,9]之间的数字，但未必全部包含
// 用数组中的数字(可以重复)组成一个最小的给定位数的正整数
int generate_min_int_containing_duplicate_digit(int *array, int n, int bit_num)
{
    // 找到最小的非零整数
    int data;
    for (int i = 0; i < n; ++i)
    {
        if (array[i] > 0)
        {
            data = array[i];
            break;
        }
    }
    for (int i = 1; i < bit_num; ++i)
    {
        data = data * 10 + array[0];
    }
    return data;
}


// Google2009华南地区笔试题
// 给定一个集合A=[0,1,3,8](该集合中的元素都是在0，9之间的数字，但未必全部包含)，
// 指定任意一个正整数K，请用A中的元素组成一个大于K的最小正整数。
// 比如，A=[1,0] K=21 那么输出结构应该为100。
int generate_min_int_greater_than_k(int *array, int n, int k)
{
    std::sort(array, array+n);
    // high_digit: k的最高位数字
    // bit_num: k的位数
    int high_digit = k, bit_num = 1;
    while (high_digit/10 > 0)
    {
        ++bit_num;
        high_digit /= 10;
    }
    // 查找数组中比k的最高位大的最小的数字
    int i;
    for (i = 0; i < n; ++i)
    {
        if (array[i] >= high_digit)
            break;
    }
    if (i == n) // 数组中的数字都比K的最高位小
    {
        return generate_min_int_containing_duplicate_digit(array, n, bit_num+1);
    }
    else if (array[i] == high_digit)// 数组中有一位数字跟K的最高位相等
    {
        int low_data = k - high_digit * pow(10, bit_num-1);
        return array[i]*pow(10, bit_num-1)+generate_min_int_greater_than_k(array, n, low_data);
    }
    else // 数组中有一位数字比k的最高位高
    {
        int data = array[i];
        for (int j = 1; j < bit_num; ++j)
        {
            data = data * 10 + array[0];
        }
        return data;
    }
    return 0;
}


// 阿里巴巴研究院（2009）：
// 有无序的实数列V[N]，要求求里面大小相邻的实数的差的最大值，关键是要求线性空间和线性时间
// 解法一：先排序，再计算相邻实数差的最大值
double max_difference_of_adjacent_floats_by_value_v1(double *array, int length)
{
    if (array == NULL || length <= 0)
        return -1;

    sort(array, array+length);
    double max_diff = 0, diff;
    for (int i = 1; i < length; ++i)
    {
        diff = array[i] - array[i-1];
        if (diff > max_diff)
            max_diff = diff;
    }
    return max_diff;
}
// 解法二：类似桶排序
double max_difference_of_adjacent_floats_by_value_v2(double *array, int length)
{
    if (array == NULL || length <= 0)
        return -1;

    // bucket_min[i]和bucket_max[i]分别记录第i个桶的最小值和最大值,
    // bucket_size[i]记录第i个桶的元素数目
    vector<double> bucket_min(length+1), bucket_max(length+1);
    vector<int> bucket_size(length+1, 0);

    // 计算桶的长度
    double *p_max = max_element(array, array+length);
    double *p_min = min_element(array, array+length);
    double bucket_diff = (*p_max - *p_min) / length;

    // 初始化第0个桶和最后一个桶
    bucket_min[0] = bucket_max[0] = *p_min;
    bucket_size[0] = 1;
    bucket_min[length] = bucket_max[length] = *p_max;
    bucket_size[length] = 1;

    // 将元素放入桶中
    for (int i = 0; i < length; ++i)
    {
        int bucket_index = (array[i] - *p_min) / bucket_diff;
        if (bucket_size[bucket_index] == 0)
        {
            bucket_min[bucket_index] = bucket_max[bucket_index] = array[i];
            bucket_size[bucket_index] = 1;
        }
        else
        {
            if (array[i] < bucket_min[bucket_index])
                bucket_min[bucket_index] = array[i];
            else if (array[i] > bucket_max[bucket_index])
                bucket_max[bucket_index] = array[i];
            ++bucket_size[bucket_index];
        }
    }

    // 查找连续的空桶，i表示第一个空桶，j表示i后第一个非空桶
    double max_diff = 0, diff;
    int i = 0, j = 0;
    while (true)
    {
        for (i = j+1; i <= length-1; ++i)
        {
            if (bucket_size[i] == 0)
                break;
        }
        if (i >= length)
            break;
        for (j = i+1; j <= length; ++j)
        {
            if (bucket_size[j] > 0)
                break;
        }
        diff = bucket_min[j] - bucket_max[i-1];
        if (diff > max_diff)
            max_diff = diff;
    }
    return max_diff;
}


//子数组的最大和-暴力穷举法
int max_sum_of_subarray_brute_force(int *array, int n)
{
    int max_sum = array[0];
    int sum;
    for (int i = 0; i != n; ++i)
    {
        sum = 0;
        for (int j = i; j != n; ++j)
        {
            sum += array[j];
            if (max_sum < sum)
                max_sum = sum;
        }
    }
    return max_sum;
}
//子数组的最大和-动态规划
int max_sum_of_subarray_dp(int *array, int n)
{
    if (n == 1)
        return array[0];

    int all = array[n-1];
    int start = array[n-1];
    for (int i = n-2; i >= 0; --i)
    {
        start = std::max<int>(array[i], array[i]+start);
        all = std::max<int>(all, start);
    }
    return all;
}
//首尾相接的循环数组的子数组的最大和
int max_sum_of_subarray_in_circular_array(int *array, int n)
{
    int max_sum = max_sum_of_subarray_dp(array, n);

    int max_sum1, max_sum2;
    int sum;
    int i, j;

    max_sum1 = array[0];
    sum = array[0];
    for (i = 1; i < n; ++i)
    {
        sum += array[i];
        if (max_sum1 < sum)
            max_sum1 = sum;
    }

    max_sum2 = array[n-1];
    sum = array[n-1];
    for (j = n-2; j >= 0; --j)
    {
        sum += array[j];
        if (max_sum2 < sum)
            max_sum2 = sum;
    }

    if (i >= j)
    {
        for (; i < n; ++i)
            max_sum1 += array[i];
    }
    else
    {
        max_sum1 += max_sum2;
    }

    return std::max<int>(max_sum, max_sum1);
}
//同时返回子数组的位置
int max_sum_of_subarray_dp_pos(int *array, int n, int &pos, int &size)
{
    if (n == 1)
    {
        pos = 0;
        size = 1;
        return array[0];
    }

    int start = array[n-1];
    int all = array[n-1];
    int pos_start = n-1, size_start = 1;
    int pos_all = n-1, size_all = 1;
    for (int i = n-2; i >= 0; --i)
    {
        if (array[i] > array[i]+start)
        {
            pos_start = i;
            size_start = 1;
            start = array[i];
        }
        else
        {
            pos_start = i;
            size_start += 1;
            start += array[i];
        }

        if (all < start)
        {
            pos_all = pos_start;
            size_all = size_start;
            all = start;
        }
    }
    pos = pos_all;
    size = size_all;
    return all;
}


//把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
//输入一个排好序的数组的一个旋转，输出旋转数组的最小元素。
//例如数组{3, 4, 5, 1, 2}为{1, 2, 3, 4, 5}的一个旋转，该数组的最小值为1。
// Parameter:
// array: 数组地址
// begin: 数组第一个元素的索引
// end: 数组最后一个元素的索引的下一个索引
// Return value:
// 最小值元素
int min_from_lshifted_increasing_array(int *array, int length)
{
	if (array == NULL || length <= 0)
		throw invalid_argument("invalid argument");
		
    if (length == 1 || array[0] < array[length-1]) //只有一个元素或是递增序列
        return array[0];

	int first = 0, last = length - 1, mid = last;
	while (array[first] >= array[last])
	{
		if (last - first == 1)
		{
			mid = last;
			break;
		}
		mid = first + (last - first) / 2;
		if (array[first] <= array[mid])
			first = mid;
		else if (array[mid] <= array[last])
			last = mid;
	}
	return array[mid];
}


// 区间最值问题（Range Max/Min Query）
// ST（Sparse Table）算法是一个非常有名的在线处理RMQ问题的算法，它可以在O(nlogn)时间内
// 进行预处理，然后在O(1)时间内回答每个查询。
// range: 要查询的区间
// sparse_table: 简称st，记录从第i个数起连续2^j个数中的最小值
void preprocess_RMQ_ST(const std::vector<int> &range, boost::multi_array<int, 2> &sparse_table)
{
	int rows = range.size();
	int cols = rows;
	sparse_table.resize(boost::extents[rows][cols]);

	for (size_t i = 0; i < range.size(); ++i)
		sparse_table[i][0] = range[i];

	for (int i = range.size()-1; i >= 0; --i)
	{
		for (int j = 1; i+(1<<(j-1))-1 < range.size(); ++j)
		{
			sparse_table[i][j] = std::min(sparse_table[i][j-1], sparse_table[i+(1<<(j-1))][j-1]);
		}
	}
}


//输入一个正整数数组，将它们连接起来排成一个数，输出能排出的所有数字中最小的一个。
//例如输入数组{32, 321}，则输出这两个能排成的最小数字32132。
//请给出解决问题的算法，并证明该算法。
class my_str_comp
{
public:
    bool operator()(const std::string &lhs, const std::string &rhs)
    {
        return lhs+rhs < rhs+lhs;
    }
};
void rearrange_array_to_min(unsigned int *array, int n)
{
    if (array == NULL || n <= 0) return;

    std::vector<std::string> strs;
    strs.reserve(n);

    std::ostringstream sstr;
    for (int i = 0; i != n; ++i)
    {
        sstr.str("");
        sstr << array[i];
        strs.push_back(sstr.str());
    }
    std::sort(strs.begin(), strs.end(), my_str_comp());
    for (int i = 0; i != n; ++i)
        std::cout << strs[i];
    std::cout << std::endl;
}

}
