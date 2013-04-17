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

//�ٶȱ��ԣ�����һ��������������飬������������ʹ���������Ϊ�������ұ�Ϊż����
//Ҫ�󣺿ռ临�Ӷ� O(1)��ʱ�临�Ӷ�Ϊ O��n����
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


// ΢������
// һ���������У�Ԫ��ȡֵ������0~65535�е�����һ��������ͬ��ֵ�����ظ����֡�0�����⣬���Է������֡�
// �����һ���㷨������Ӹ�����������ѡȡ5����ֵ���ж���5����ֵ�Ƿ��������ڡ�
// ע�⣺
// - 5����ֵ����������ġ����磺 8 7 5 0 6
// - 0����ͨ��������ֵ�����磺8 7 5 0 6 �е�0����ͨ���9����4
// - 0���Զ�γ��֡�
// - ���Ӷ������O(n2)�򲻵÷֡�
// ����˼·��
// 1.ȡ5�����з�0�����������С����֮�����4������������������
// 2.Ҫ�������������� 1��ȫ0��������2��ֻ��һ����0������
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


//�õݹ�ķ����ж�������a[N]�ǲ�����������
bool array_is_increasing_order_recursion(int *array, int begin, int end)
{
    if (array == NULL || begin < 0 || end < 0 || begin > end)
        return false;

    if (begin == end)
        return true;

    return array[begin] <= array[begin+1] && array_is_increasing_order_recursion(array, begin+1, end);
}


// �ٶȱ�����
// ����array[begin,mid-1] �� array[mid,end-1]�����ֱ��������С�����merge����������al[0,num-1]��Ҫ��ռ临�Ӷ�O(1)
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


// google������
// ��Ŀ������a1,a2,...,an,b1,b2,...,bn,
// ��O(n)��ʱ��,O(1)�Ŀռ佫�������˳���Ϊa1,b1,a2,b2,a3,b3,...,an,bn��
// �Ҳ���Ҫ�ƶ���ͨ��������ɣ�ֻ��һ�������ռ䡣
// �㷨����
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


// ��������
// ������array[begin...end)�е�Ԫ����������
void array_reverse(int *array, int begin, int end)
{
	if (array == NULL) return;

	--end;
	for ( ; begin < end; ++begin, --end)
	{
		swap(array[begin], array[end]);
	}
}
// ������ǰ�벿��array[begin,mid)���벿��[mid,end)���򣬵�ǰ�벿�ֺͺ�벿�ֱ�����˳�򲻱�
void array_reverse(int *array, int begin, int mid, int end)
{
	array_reverse(array, begin, mid);
	array_reverse(array, mid, end);
	array_reverse(array, begin, end);
}


// �ѹ������⣺һ������Ϊn������a[0],a[1],...,a[n-1]�����ڸ������������Ԫ�أ�
// ��a[0]��Ϊa[1]��a[n-1]�Ļ���a[1]��Ϊa[0]��a[2]��a[n-1]�Ļ���...��
// a[n-1]Ϊa[0]��a[n-2]�Ļ������ǳ�����ǰԪ�أ���������Ԫ�صĻ���������Ҫ��
// �������Ը��Ӷȣ��Ҳ���ʹ�ó����������
void array_update_to_product(int *array, int length)
{
    if (array == NULL || length <= 0)
        return;

    // tmp[i]��¼array[i]���Ԫ�صĳ˻�
    int *left = new int[length];
    left[0] = 1;
    for (int i = 1; i != length; ++i)
    {
        left[i] = left[i-1] * array[i-1];
    }
    // right��¼array[i]�ұ�Ԫ�صĳ˻�
    int right = 1, new_right = 1;
    for (int i = length-1; i >= 0; --i)
    {
        new_right = right * array[i];
        array[i] = left[i] * right;
        right = new_right;
    }
}
// ��չ��2012��4��67�յ���Ѷ����ʵϰ����Ƹ�����У�����һ��������21�����Ƶ��⣬ԭ��������£�
// ��������a[N]��b[N]������A[N]�ĸ���Ԫ��ֵ��֪���ָ�b[i]��ֵ��b[i] = a[0]*a[1]*a[2]...*a[N-1]/a[i]��
// Ҫ��1.��׼�ó�������
// 2.����ѭ������ֵ��a[N],b[N]�⣬��׼���������κα����������ֲ�������ȫ�ֱ����ȣ�
// 3.����ʱ�临�Ӷ�O��n�����ռ临�Ӷ�O��1����
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


//�ڵݼ������ж��ֲ���һ��Ԫ�أ����ҵ�����������������û���ҵ�������-1.
// Parameter:
// array: �����ַ
// begin: �����һ��Ԫ�ص�����
// end: �������һ��Ԫ�ص���������һ������
// item: Ҫ���ҵ�Ԫ��
// Return value:
// ���ҵ�����������������û���ҵ�������-1.
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


// �ڵ��������ж��ֲ���һ��Ԫ�أ����ҵ�����������������û���ҵ�������-1.
// Parameter:
// array: �����ַ
// begin: �����һ��Ԫ�ص�����
// end: �������һ��Ԫ�ص���������һ������
// item: Ҫ���ҵ�Ԫ��
// Return value:
// ���ҵ�����������������û���ҵ�������-1.
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


//һ����������һ���ݼ�������������λ�γɵģ�����{4��3��2��1��6��5}
//����{6��5��4��3��2��1}������λ�γɵģ������������в���ĳһ������
//���ҵ�����������������û���ҵ�������-1.
// Parameter:
// array: �����ַ
// begin: �����һ��Ԫ�ص�����
// end: �������һ��Ԫ�ص���������һ������
// item: Ҫ���ҵ�Ԫ��
// Return value:
// ���ҵ�����������������û���ҵ�������-1.
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


//һ����������һ������������������λ�γɵģ�����{3, 4, 5, 1, 2}����{1, 2, 3, 4, 5}
//������λ�γɵģ������������в���ĳһ������
//���ҵ�����������������û���ҵ�������-1.
// Parameter:
// array: �����ַ
// begin: �����һ��Ԫ�ص�����
// end: �������һ��Ԫ�ص���������һ������
// item: Ҫ���ҵ�Ԫ��
// Return value:
// ���ҵ�����������������û���ҵ�������-1.
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


// ΢��10.15���ԣ�����һ������{1,2,3}������������{1,2}��{1,3}{2,3}��{1,2,3}��Ԫ��֮����Բ��������ģ�
// ��������{5,9,1,7,2,6,3,8,10,4}�������������ж��ٸ������߻�һ�ֱ��Ϊ������int a[]={5,9,1,7,2,6,3,8,10,4}��
// �������е���������(Ԫ�����λ�ò���)�ĸ��������磺{5��9}��{5��7��8��10}��{1��2��6��8}��
// ��̬�滮
int count_all_increasing_subarray_v1(int *array, int length)
{
	if (array == NULL || length <= 0)
		return 0;

	// subarray_count[i]��¼��array[i]Ϊ���һ��Ԫ�صĵ������������Ŀ
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
// δ������ռ��ʱ�为�ض�ΪO(n)
// ���������ο���http://blog.csdn.net/julianxiong/article/details/7322665
int count_all_increasing_subarray_v2(int *array, int length)
{
	if (array == NULL || length <= 0)
		return 0;

	// subarray_count[i]��¼��array[i]��β������ĵ������������Ŀ
	vector<int> subarray_count(length, 0);
	// less_count[i]��¼С��array[i]��Ԫ�ص���Ŀ
	vector<int> less_count(length, 0);
	for (int i = 1; i < length; ++i)
	{
		// ��һ����������������鲻����array[i]
		subarray_count[i] = subarray_count[i-1];

		// �ڶ���������������������array[i]
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



// 2010������������
// �����⣺
// ������������ n �� m��������1��2��3.......n������ȡ������,
// ʹ��͵��� m ,Ҫ���������еĿ�������г�����
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

    find_additive_factors(n-1, m, factors, count); // ������n

    factors.push_back(n);
    find_additive_factors(n-1, m-n, factors, count); // ����n

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


// ������Ϸ�����⣺��һ����������array[n]����һ������m���ж�m�Ƿ�����Щ���������
// ���ĺ͡���������΢������100��2010����4�⣬���൱�ڸ���һ������Ȼ�����һ������
// Ҫ�����Щ ��ӵĺ͵���������� ���нڵ��ӡ��������
// array: �������е���������
// length: ���鳤��
// m: ����m
// factors: �Ѿ��ҵ��ļӷ�����
// count: ������ϵ���Ŀ
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

    // �������������У�array[0]����Сֵ��m����СֵС����������������һԪ�أ����ӵĺ;ͳ�����m�Ĵ�С;
    // ����������һԪ�أ����ӵĺ;ͱ�mС��������������һԪ�ز������ǵ�ǰ��������е����ӣ�ֱ�ӷ��ء�
    if (m < array[0])
        return;

    // ������array[0]
    find_additive_factors(array+1, length-1, m, factors, count);

    // ����array[0]
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


//���������е����������в�������������ʹ�����������ĺ͵��ڸ���ֵ
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


// �����������в��ҳ��ִ�������һ�����
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


//��һ�� int ������������������������ڵ��������������С�ڵ����Ҳ���������
//�����������飬���α���
void find_int_left_less_right_greater_v1(int *array, int n, int *out, int &length)
{
    //a[i]��¼�ӿ�ʼ��array[i]�����ֵ
    int *a = new int[n];
    //b[i]��¼��array[i]����β����Сֵ
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
//һ���������飬���α���
void find_int_left_less_right_greater_v2(int *array, int n, int *out, int &length)
{
    //b[i]��¼��array[i]����β����Сֵ
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
    //��¼��ǰ�����ֵ
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


//����������ɵ��������ҵ����ȴ��ڵ���3����ĵȲ�����, ����Ȳ�������С����:
//���û�з��������ľ����[0, 0]
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

    // ���Ĺ���
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


//��һ���������ݼ������У������䳤��
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
    //�������飬aid_array[i]��¼��array[i]��β�ĵݼ����еĳ���
    int *aid_array = new int[n];
    //max_v[i]��¼����Ϊi�ĵݼ����е���СԪ�ص����ֵ
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


// ��һ�����������������У������䳤��
// һ�㷽��
int find_longest_increasing_subsequence(int *array, int *subsequence, int n)
{
    //����������еĳ���
    int max_len = 0;
    //��ǰ����������
    int *aid_array = new int[n];
    //��ǰ���������еĳ���
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
// ��������������
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
// ��̬�滮����
int find_longest_increasing_subsequence_dp(int *array, int *subsequence, int n)
{
    //aid_array[i]��¼��array[i]��β������������еĳ���
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
// ���췽��
int find_longest_increasing_subsequence_fast(int *array, int *subsequence, int n)
{
    //aid_array[i]��¼��array[i]��β������������еĳ���
    int *aid_array = new int[n];
    //max_v[i]��¼����Ϊi�ĵ������������Ԫ�ص���Сֵ
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
        //��ٱ���
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
        //���ֲ���
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


// ΢�������⣺
// ��һ���������飬���������֮�����ֵ��С��ֵ��
// ��ס��ֻҪ�ó���Сֵ���ɣ�����Ҫ���������������
// �ȶ����������������������Ĳ�ľ���ֵ����Сֵ
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


//����n�����������������С��k��
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


// �����������У��ҳ��������ֵĳ��ִ���
// ���� [1, 2, 2, 2, 3] ��2�ĳ��ִ�����3�Ρ�
// Parameter:
// array: ��������ĵ�ַ
// length: ���鳤��
// item: Ҫ���ҵ�Ԫ��
// Return value:
// �������������������еĳ��ִ���
int find_occurrence_number_in_odered_array(int *array, int length, int item)
{
    if (array == NULL || length <= 0)
        return 0;

    // ���Ҹ��������Ƿ����
    int idx = bisearch_in_increasing_array(array, 0, length, item);
    if (idx == -1 || idx == length || array[idx] != item)
        return 0;

    int begin = idx, end = idx;
    // ���Ҹ������ֶεĿ�ʼλ��
    while (true)
    {
        idx = bisearch_in_increasing_array(array, 0, begin, item);
        if (idx >= 0 && idx < begin && array[idx] == item)
            begin = idx;
        else
            break;
    }
    // ���Ҹ������ֶεĽ���λ��
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


// �ҳ�������Ψһ���ظ�Ԫ��
// 1-1000���ں���1001��Ԫ�ص������У�ֻ��Ψһ��һ��Ԫ��ֵ�ظ���������ֻ����һ�Σ�
// ÿ������Ԫ��ֻ�ܷ���һ�Σ����һ���㷨�������ҳ��������ø����洢�ռ䣬
// �ܷ����һ���㷨ʵ�֣�
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


//������һ�ֱ��룺�磬N=134��M=f(N)=143,N=020,M=fun(N)=101,����N��M��λ��һ����
// N,M��������0��ͷ��N,M�ĸ�λ��֮��Ҫ��ȣ���1+3+4=1+4+3����M�Ǵ���N����С��һ����
// ����������������S,NΪһ����ֵ������S(0)=N��S(1)=fun(N),S(2)=fun(S(1))��
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
		// �����λ��ʼ��������һ��2����������λarray[i]��
		// (1) array[i] > 0
		// (2) array[i-1] < 9
		// ��ֻ��������(1), ��ô���磬699����һ��������ҵ�798������ʵ����Ӧ����789
		for (i = length-1; i > 0; --i)
		{
			if (array[i] > 0 && array[i-1] < 9)
				break;
		}
		if (i == 0)
			break;
		int data = array[i];
		array[i] = 0; // ��ǰλ��Ϊ0
		array[i-1] += 1; // ǰһλ��1
		array[length-1] += data-1; // ʣ�µ�ֵ�ӵ����һλ
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


//һ�����������������������֮�⣬���������ֶ����������Ρ�
//��д�����ҳ�������ֻ����һ�ε����֡�Ҫ��ʱ�临�Ӷ��� O(n)���ռ临�Ӷ��� O(1)��
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


// һ����С����������������飬Ԫ�ض�����[0,9]֮������֣���δ��ȫ������
// �������е�����(�����ظ�)���һ����С�ĸ���λ����������
int generate_min_int_containing_duplicate_digit(int *array, int n, int bit_num)
{
    // �ҵ���С�ķ�������
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


// Google2009���ϵ���������
// ����һ������A=[0,1,3,8](�ü����е�Ԫ�ض�����0��9֮������֣���δ��ȫ������)��
// ָ������һ��������K������A�е�Ԫ�����һ������K����С��������
// ���磬A=[1,0] K=21 ��ô����ṹӦ��Ϊ100��
int generate_min_int_greater_than_k(int *array, int n, int k)
{
    std::sort(array, array+n);
    // high_digit: k�����λ����
    // bit_num: k��λ��
    int high_digit = k, bit_num = 1;
    while (high_digit/10 > 0)
    {
        ++bit_num;
        high_digit /= 10;
    }
    // ���������б�k�����λ�����С������
    int i;
    for (i = 0; i < n; ++i)
    {
        if (array[i] >= high_digit)
            break;
    }
    if (i == n) // �����е����ֶ���K�����λС
    {
        return generate_min_int_containing_duplicate_digit(array, n, bit_num+1);
    }
    else if (array[i] == high_digit)// ��������һλ���ָ�K�����λ���
    {
        int low_data = k - high_digit * pow(10, bit_num-1);
        return array[i]*pow(10, bit_num-1)+generate_min_int_greater_than_k(array, n, low_data);
    }
    else // ��������һλ���ֱ�k�����λ��
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


// ����Ͱ��о�Ժ��2009����
// �������ʵ����V[N]��Ҫ���������С���ڵ�ʵ���Ĳ�����ֵ���ؼ���Ҫ�����Կռ������ʱ��
// �ⷨһ���������ټ�������ʵ��������ֵ
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
// �ⷨ��������Ͱ����
double max_difference_of_adjacent_floats_by_value_v2(double *array, int length)
{
    if (array == NULL || length <= 0)
        return -1;

    // bucket_min[i]��bucket_max[i]�ֱ��¼��i��Ͱ����Сֵ�����ֵ,
    // bucket_size[i]��¼��i��Ͱ��Ԫ����Ŀ
    vector<double> bucket_min(length+1), bucket_max(length+1);
    vector<int> bucket_size(length+1, 0);

    // ����Ͱ�ĳ���
    double *p_max = max_element(array, array+length);
    double *p_min = min_element(array, array+length);
    double bucket_diff = (*p_max - *p_min) / length;

    // ��ʼ����0��Ͱ�����һ��Ͱ
    bucket_min[0] = bucket_max[0] = *p_min;
    bucket_size[0] = 1;
    bucket_min[length] = bucket_max[length] = *p_max;
    bucket_size[length] = 1;

    // ��Ԫ�ط���Ͱ��
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

    // ���������Ŀ�Ͱ��i��ʾ��һ����Ͱ��j��ʾi���һ���ǿ�Ͱ
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


//�����������-������ٷ�
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
//�����������-��̬�滮
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
//��β��ӵ�ѭ������������������
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
//ͬʱ�����������λ��
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


//��һ�������ʼ�����ɸ�Ԫ�ذᵽ�����ĩβ�����ǳ�֮Ϊ�������ת��
//����һ���ź���������һ����ת�������ת�������СԪ�ء�
//��������{3, 4, 5, 1, 2}Ϊ{1, 2, 3, 4, 5}��һ����ת�����������СֵΪ1��
// Parameter:
// array: �����ַ
// begin: �����һ��Ԫ�ص�����
// end: �������һ��Ԫ�ص���������һ������
// Return value:
// ��СֵԪ��
int min_from_lshifted_increasing_array(int *array, int length)
{
	if (array == NULL || length <= 0)
		throw invalid_argument("invalid argument");
		
    if (length == 1 || array[0] < array[length-1]) //ֻ��һ��Ԫ�ػ��ǵ�������
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


// ������ֵ���⣨Range Max/Min Query��
// ST��Sparse Table���㷨��һ���ǳ����������ߴ���RMQ������㷨����������O(nlogn)ʱ����
// ����Ԥ����Ȼ����O(1)ʱ���ڻش�ÿ����ѯ��
// range: Ҫ��ѯ������
// sparse_table: ���st����¼�ӵ�i����������2^j�����е���Сֵ
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


//����һ�����������飬���������������ų�һ������������ų���������������С��һ����
//������������{32, 321}����������������ųɵ���С����32132��
//��������������㷨����֤�����㷨��
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
