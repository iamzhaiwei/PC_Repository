// array_problem.h
//
// last-edit-by: <>
//
// Description:
// 数组问题
//////////////////////////////////////////////////////////////////////

#ifndef ARRAY_PROBLEM_H
#define ARRAY_PROBLEM_H 1

#include "boost/multi_array.hpp"
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{

//百度笔试：给定一个存放整数的数组，重新排列数组使得数组左边为奇数，右边为偶数。
//要求：空间复杂度 O(1)，时间复杂度为 O（n）。
void adjust_array_left_odd_right_even(int *array, int n);


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
// 2.要增加两个特例： 1）全0 算连续，2）只有一个非0算连续
bool array_is_continuous(int array[5]);


//用递归的方法判断整数组a[N]是不是升序排列
bool array_is_increasing_order_recursion(int *array, int begin, int end);


// 百度笔试题
// 数组array[begin,mid-1] 和 array[mid,end-1]，都分别升序排列。将其merge成有序数组al[0,num-1]，要求空间复杂度O(1)
void array_merge_in_place(int *array, int begin, int mid, int end);


// google面试题
// 题目：输入a1,a2,...,an,b1,b2,...,bn,
// 在O(n)的时间,O(1)的空间将这个序列顺序改为a1,b1,a2,b2,a3,b3,...,an,bn，
// 且不需要移动，通过交换完成，只需一个交换空间。
void array_rearrange(int *array, int begin, int end);


// 数组逆序
// 将数组array[0...length)中的元素逆序排列
void array_reverse(int *array, int length);
// 将数组前半部分array[begin,mid)与后半部分[mid,end)逆序，但前半部分和后半部分本身保持顺序不变
void array_reverse(int *array, int begin, int mid, int end);


// 搜狗笔试题：一个长度为n的数组a[0],a[1],...,a[n-1]。现在更新数组的名个元素，
// 即a[0]变为a[1]到a[n-1]的积，a[1]变为a[0]和a[2]到a[n-1]的积，...，
// a[n-1]为a[0]到a[n-2]的积（就是除掉当前元素，其他所有元素的积）。程序要求：
// 具有线性复杂度，且不能使用除法运算符。
// 一个辅助数组，二次遍历
void array_update_to_product(int *array, int length);
// 扩展：2012年4月67日的腾讯暑期实习生招聘笔试中，出了一道与上述21题类似的题，原题大致如下：
// 两个数组a[N]，b[N]，其中A[N]的各个元素值已知，现给b[i]赋值，b[i] = a[0]*a[1]*a[2]...*a[N-1]/a[i]
// 要求：1.不准用除法运算
// 2.除了循环计数值，a[N],b[N]外，不准再用其他任何变量（包括局部变量，全局变量等）
// 3.满足时间复杂度O（n），空间复杂度O（1）。
void array_multiply_to_product_v1(int *in_array, int *out_array, int length);
void array_multiply_to_product_v2(int *in_array, int *out_array, int length);


// 在递减序列中二分查找一个元素，若找到，返回其索引，若没有找到，返回-1.
// Parameter:
// array: 数组地址
// begin: 数组第一个元素的索引
// end: 数组最后一个元素的索引的下一个索引
// item: 要查找的元素
// Return value:
// 若找到，返回其索引，若没有找到，返回-1.
int bisearch_in_decreasing_array(int *array, int begin, int end, int item);


// 在递增序列中二分查找一个元素，若找到，返回其索引，若没有找到，返回-1.
// Parameter:
// array: 数组地址
// begin: 数组第一个元素的索引
// end: 数组最后一个元素的索引的下一个索引
// item: 要查找的元素
// Return value:
// 若找到，返回其索引，若没有找到，返回-1.
int bisearch_in_increasing_array(int *array, int begin, int end, int item);


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
int bisearch_in_lshift_decreasing_array(int *array, int begin, int end, int item);


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
int bisearch_in_lshift_increasing_array(int *array, int begin, int end, int item);


// 微软10.15笔试：对于一个数组{1,2,3}它的子数组有{1,2}，{1,3}{2,3}，{1,2,3}，元素之间可以不是连续的，
// 对于数组{5,9,1,7,2,6,3,8,10,4}，升序子序列有多少个？或者换一种表达为：数组int a[]={5,9,1,7,2,6,3,8,10,4}。
// 求其所有递增子数组(元素相对位置不变)的个数，例如：{5，9}，{5，7，8，10}，{1，2，6，8}。
int count_all_increasing_subarray_v1(int *array, int length);
int count_all_increasing_subarray_v2(int *array, int length);


// 2010年中兴面试题
// 编程求解：
// 输入两个整数 n 和 m，从数列1，2，3.......n中随意取几个数,
// 使其和等于 m ,要求将其中所有的可能组合列出来。
int find_additive_factors(int n, int m);


// 网易游戏笔试题：给一个有序数组array[n]，和一个数字m，判断m是否是这些数组里面的
// 数的和。（类似于微软面试100题2010年版第4题，即相当于给定一棵树，然后给定一个数，
// 要求把那些 相加的和等于这个数的 所有节点打印出来）。
int find_additive_factors(int *array, int length, int m);


// 在升序排列的整数数组中查找两个整数，使这两个整数的和等于给定值
bool find_two_additive_factors(int *array, int n, int sum, int &p1, int &p2);


// 在整型数组中查找出现次数超过一半的数
int find_int_appear_more_than_half(int *array, int n);


//在一个 int 数组里查找这样的数，它大于等于左侧所有数，小于等于右侧所有数。
//两个辅助数组，三次遍历
void find_int_left_less_right_greater_v1(int *array, int n, int *out, int &length);
//一个辅助数组，两次遍历
void find_int_left_less_right_greater_v2(int *array, int n, int *out, int &length);


//求随机数构成的数组中找到长度大于等于3的最长的等差数列, 输出等差数列由小到大:
//如果没有符合条件的就输出[0, 0]
int find_longest_arithmetic_sequence(int *array, int n);


//求一个数组的最长递减子序列，返回其长度
int find_longest_decreasing_subsequence(int *array, int *subsequence, int n);


//求一个数组的最长递增子序列，返回其长度
//一般方法
int find_longest_increasing_subsequence(int *array, int *subsequence, int n);
//动态规划方法
int find_longest_increasing_subsequence_dp(int *array, int *subsequence, int n);
//更快方法
int find_longest_increasing_subsequence_fast(int *array, int *subsequence, int n);


// 微软面试题：
// 有一个整数数组，请求出两两之差绝对值最小的值。
// 记住，只要得出最小值即可，不需要求出是哪两个数。
// 先对数组排序，再求相邻两数的差的绝对值的最小值
int find_min_difference(int *array, int n);


//输入n个整数，输出其中最小的k个（没写完）
void find_min_k_ints(int *array_in, int n, int *array_out, int k);


// 在排序数组中，找出给定数字的出现次数
// 比如 [1, 2, 2, 2, 3] 中2的出现次数是3次。
// Parameter:
// array: 排序数组的地址
// length: 数组长度
// item: 要查找的元素
// Return value:
// 给定数字在排序数组中的出现次数
int find_occurrence_number_in_odered_array(int *array, int length, int item);


// 找出数组中唯一的重复元素
// 1-1000放在含有1001个元素的数组中，只有唯一的一个元素值重复，其它均只出现一次．
// 每个数组元素只能访问一次，设计一个算法，将它找出来；不用辅助存储空间，
// 能否设计一个算法实现？
int find_single_duplicate_int();


//有这样一种编码：如，N=134，M=f(N)=143,N=020,M=fun(N)=101,其中N和M的位数一样，
// N,M可以均可以以0开头，N,M的各位数之和要相等，即1+3+4=1+4+3，且M是大于N中最小的一个，
// 现在求这样的序列S,N为一个定值，其中S(0)=N，S(1)=fun(N),S(2)=fun(S(1))。
void find_the_sequence(int *first_code, int length);


// 一个整型数组里除了两个数字之外，其他的数字都出现了两次。
// 请写程序找出这两个只出现一次的数字。要求时间复杂度是 O(n)，空间复杂度是 O(1)。
void find_two_ints_appear_once(int *array, int n, int &i1, int &i2);


// 一个整数数组，元素都是在[0,9]之间的数字，但未必全部包含
// 用数组中的数字(可以重复)组成一个最小的给定位数的正整数
int generate_min_int_containing_duplicate_digit(int *array, int n, int bit_num);


// Google2009华南地区笔试题
// 给定一个集合A=[0,1,3,8](该集合中的元素都是在0，9之间的数字，但未必全部包含)，
// 指定任意一个正整数K，请用A中的元素组成一个大于K的最小正整数。
// 比如，A=[1,0] K=21 那么输出结构应该为100。
int generate_min_int_greater_than_k(int *array, int n, int k);


// 阿里巴巴研究院（2009）：
// 有无序的实数列V[N]，要求求里面大小相邻的实数的差的最大值，关键是要求线性空间和线性时间
// 解法一：先排序，再计算相邻实数差的最大值
double max_difference_of_adjacent_floats_by_value_v1(double *array, int length);
// 解法二：类似桶排序
double max_difference_of_adjacent_floats_by_value_v2(double *array, int length);


// 子数组的最大和-暴力穷举法
int max_sum_of_subarray_brute_force(int *array, int n);
// 子数组的最大和-动态规划
int max_sum_of_subarray_dp(int *array, int n);
// 首尾相接的循环数组的子数组的最大和
int max_sum_of_subarray_in_circular_array(int *array, int n);
// 同时返回子数组的位置
int max_sum_of_subarray_dp_pos(int *array, int n, int &pos, int &size);


// 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
// 输入一个排好序的数组的一个旋转，输出旋转数组的最小元素。
// 例如数组{3, 4, 5, 1, 2}为{1, 2, 3, 4, 5}的一个旋转，该数组的最小值为1。
// Parameter:
// array: 数组地址
// begin: 数组第一个元素的索引
// end: 数组最后一个元素的索引的下一个索引
// Return value:
// 最小值元素
int min_from_lshifted_increasing_array(int *array, int length);


// 区间最值问题（Range Max/Min Query）
// ST（Sparse Table）算法是一个非常有名的在线处理RMQ问题的算法，它可以在O(nlogn)时间内
// 进行预处理，然后在O(1)时间内回答每个查询。
// range: 要查询的区间
// sparse_table: 简称st，记录从第i个数起连续2^j个数中的最小值
void preprocess_RMQ_ST(const std::vector<int> &range, boost::multi_array<int, 2> &sparse_table);


// 输入一个正整数数组，将它们连接起来排成一个数，输出能排出的所有数字中最小的一个。
// 例如输入数组{32, 321}，则输出这两个能排成的最小数字32132。
// 请给出解决问题的算法，并证明该算法。
void rearrange_array_to_min(unsigned int *array, int n);

}

#endif // ARRAY_PROBLEM_H
