// string_suffix_array.cpp
/////////////////////////////////////////////////////////////////////

#include "string_suffix_array.h"
#include <cstring>
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
/////////////////////////////////////////////////////////////////////

namespace zhaiwei
{

// 字符串比较仿函数
class string_compare: public binary_function<int, int, bool>
{
public:
	string_compare(const char *str): mp_str(str)
	{}

	bool operator()(int i, int j)
	{
		return strcmp(mp_str+i, mp_str+j) < 0;
	}

private:
	const char *mp_str; // 字符串指针
};


// 求两个字符串的最长公共前缀的长度
static int length_of_common_prefix(const char *str1, const char *str2)
{
	if (str1 == NULL || str2 == NULL) return 0;

	int length = 0;
	for ( ; *str1 != '\0' && *str2 != '\0' && *str1 == *str2; ++str1, ++str2)
		++length;
	return length;
}


// 后缀数组存储字符串后缀的起始位置：0,1,2,...,length-1，按照后缀的字典序排列
// 一般算法求字符串的后缀数组
// str: 以‘\0’结尾的字符串指针
// length: 字符串的长度
// sa: 后缀数组
void string_suffix_array(const char *str, int length, vector<int> &sa)
{
	if (str == NULL || length <= 0) return;

	sa.resize(length);
	for (int i = 0; i < length; ++i)
		sa[i] = i;
	sort(sa.begin(), sa.end(), string_compare(str));
}


// 名次数组存储后缀的名次，名次从0开始
// 根据后缀数组求名次数组
// sa: 后缀数组
// ra: 名次数组
void string_rank_array(const vector<int> &sa, vector<int> &ra)
{
	ra.resize(sa.size());
	for (std::size_t i = 0; i < sa.size(); ++i)
		ra[sa[i]] = i;
}


// height数组：排名相邻的两个后缀的最长公共前缀
// 根据后缀数组求height数组
// str: 字符串指针
// length: 字符串长度
// sa: 后缀数组
// ha: height数组
void string_height_array(const char *str, int length, const vector<int> &sa, vector<int> &ha)
{
	if (str == NULL || length <= 0) return;

	ha.resize(sa.size());
	for (int i = 1; i < length; ++i)
		ha[i] = length_of_common_prefix(str+sa[i], str+sa[i-1]);
}


// 给定一个字符串，询问某两个后缀的最长公共前缀
// str: 字符串指针
// length: 字符串长度
// i, j: 两个后缀的下标
int max_length_of_common_prefix_of_suffix(const char *str, int length, int i, int j)
{
	if (str == NULL || length <= 0) return -1;

	// 后缀数组 名次数组 height数组
	vector<int> sa, ra, ha;
	string_suffix_array(str, length, sa);
	string_rank_array(sa, ra);
	string_height_array(str, length, sa, ha);

	return max_length_of_common_prefix_of_suffix(ra, ha, i, j);
}
int max_length_of_common_prefix_of_suffix(const vector<int> &ra, const vector<int> &ha, int i, int j)
{
	int less_rank = min(ra[i], ra[j]);
	int greater_rank = max(ra[i], ra[j]);
	vector<int> ha_copy;
	for (int rank = less_rank; rank < greater_rank; ++rank)
		ha_copy.push_back(ha[rank+1]);
	return *min_element(ha_copy.begin(), ha_copy.end());
}

// 不可重叠最长重复子串（pku1743）
// 给定一个字符串，输出最长重复子串，返回其长度，这两个子串不能重叠。
/*
int max_length_of_nonoverlapping_repetitive_substr(char *str, int length)
{
	if (str == NULL || length <= 0) return 0;

	// 后缀数组 height数组
	std::vector<int> sa, ha;
	string_suffix_array(str, length, sa);
	string_height_array(str, length, sa, ha);

	// 将height数组排序，去除重复值，即 使后缀的最长公共前缀从大到小排序
	std::vector<int> ha_copy(ha);
	std::sort(ha_copy.begin()+1, ha_copy.end());
	std::unique(ha_copy.begin()+1, ha_copy.end());

	for (std::vector<int>::iterator ha_cp_iter = ha_copy.begin()+1; ha_cp_iter != ha_copy.end(); ++ha_cp_iter)
	{
		std::vector<int>::iterator ha_iter = ha.begin() + 1;
		while (ha_iter != ha.end())
		{
			while (*ha_iter < *ha_cp_iter) ++ha_iter;
			std::vector<int>::iterator ha_iter1 = ha_iter;
			while (*ha_iter >= *ha_cp_iter) ++ha_iter;
			std::vector<int>::iterator ha_iter2 = ha_iter;
			int idx1 = ha_iter1 - ha.begin() - 1;
			int idx2 = ha_iter2 - ha.begin();
			std::vector<int>::iterator sa_iter_min, sa_iter_max;
			sa_iter_min = std::min_element(sa.begin()+idx1, sa.begin()+idx2);
			sa_iter_max = std::max_element(sa.begin()+idx1, sa.begin()+idx2);
			if (*sa_iter_max - *sa_iter_min >= *ha_cp_iter)
				return *ha_cp_iter;
		}
	}
	return 0;
}
*/


// 可重叠最长重复子串
// 给定一个字符串，输出最长重复子串，返回其长度，这两个子串可以重叠。
// 分析：即height数组的最大值
int max_length_of_overlapping_repetitive_substr(const char *str, int length)
{
	if (str == NULL || length <= 0) return 0;

	// 后缀数组 名次数组 height数组
	std::vector<int> sa, ha;
	string_suffix_array(str, length, sa);
	string_height_array(str, length, sa, ha);

	std::vector<int>::iterator iter_max = std::max_element(ha.begin()+1, ha.end());
	int index = iter_max - ha.begin();
	for (int i = sa[index]; i < sa[index]+*iter_max; ++i)
		std::cout << str[i];
	std::cout << std::endl;
	return *iter_max;
}


// 最长回文子串（ural1297）
// 回文子串：如果将字符串 L 的某个子字符串 R 反过来写后和原来的字符串 R
// 一样，则称字符串 R 是字符串 L 的回文子串。
// 给定一个字符串，输出最长回文子串，返回其长度。
// 分析：：将整个字符串反过来写在原字符串后面，中间用一个特殊的字符隔开。
// 这样就把问题变为了求这个新的字符串的某两个后缀的最长公共前缀。
int max_length_of_palindrome_substr(const char *str, int length)
{
	if (str == NULL || length <= 0) return 0;

	// 将整个字符串逆序写在原字符串后面，中间用一个特殊的字符隔开
    int new_length = length * 2 + 1;
	char *new_str = new char[new_length+1];
	char *p = copy(str, str+length, new_str);
	*p++ = '$';
	p = reverse_copy(str, str+length, p);
	*p = '\0';

	// 后缀数组 名次数组 height数组
	vector<int> sa, ra, ha;
	string_suffix_array(new_str, new_length, sa);
	string_rank_array(sa, ra);
	string_height_array(new_str, new_length, sa, ha);
	delete [] new_str;

	int palindrome_len = 1, palindrome_center_idx = 0;
	for (int i = 1; i <= length-2; ++i)
	{
		// 回文长度为奇数的情况
		int tmp_len = max_length_of_common_prefix_of_suffix(ra, ha, i, new_length-i-1) * 2 - 1;
		if (tmp_len > palindrome_len)
		{
			palindrome_len = tmp_len;
			palindrome_center_idx = i;
		}
		// 回文长度为偶数的情况
		tmp_len = max_length_of_common_prefix_of_suffix(ra, ha, i, new_length-i) * 2;
		if (tmp_len > palindrome_len)
		{
			palindrome_len = tmp_len;
			palindrome_center_idx = i;
		}
	}

	int begin = palindrome_center_idx - palindrome_len / 2;
	for (int i = 0; i < palindrome_len; ++i)
		cout << str[begin+i];
	cout << endl;

	return palindrome_len;
}


// 连续重复子串(pku2406)
// 给定一个字符串 L，已知这个字符串是由某个字符串 S 重复 R 次而得到的，求 R 的最大值。
int number_of_continuous_repetitive_substr(const char *str, int length)
{
	if (str == NULL || length <= 0) return 0;

	// 后缀数组，名次数组，height数组
	vector<int> sa, ra, ha;
	string_suffix_array(str, length, sa);
	string_rank_array(sa, ra);
	string_height_array(str, length, sa, ha);

	// 穷举子串的长度k
	for (int k = 1; k < length; ++k)
	{
		if (length % k == 0 && max_length_of_common_prefix_of_suffix(ra, ha, 0, k) == length-k)
			return length / k;
	}
	return 1;
}


// 不相同的子串的个数（spoj694,spoj705）
// 给定一个字符串，求不相同的子串的个数。
// 分析：对于每一次新加进来的后缀 suffix(sa[k]),它将产生 n-sa[k] 个
// 新的前缀。但是其中有height[k]个是和前面的字符串的前缀是相同的。
// 所以 suffix(sa[k])将“贡献”出 n-sa[k]- height[k]个不同的子串。累加
// 后便是原问题的答案。这个做法的时间复杂度为 O(n)。
int number_of_different_substr(const char *str, int length)
{
	if (str == NULL || length <= 0) return 0;

	// 后缀数组 height数组
	std::vector<int> sa, ha;
	string_suffix_array(str, length, sa);
	string_height_array(str, length, sa, ha);

	int cnt = length - sa[0];
	for (int i = 1; i < length; ++i)
		cnt += (length - sa[i] - ha[i]);
	return cnt;
}


// 倍增算法
#define max 10000
static int Rx[max], Ry[max], rx[max];

static int cmp(int *y, int a, int b, int l)
{
    return y[a] == y[b] && y[a+l] == y[b+l];
}
//对于串约定最后一位是小于串中其他任何元素的元素，这样cmp的时候就不用担心y[a+l]
//越界了，因为y[a]= y[b]就暗含了他们长度相等，都没有包含最后一位。
// 参数：
// s: 字符串
// sa: 后缀数组
void string_suffix_array_da(char *s,int *sa)
{
    int len = strlen(s), *Rank_x = Rx, *Rank_y = Ry, bar[max], *result_x = rx;
    int i, j, k, p, *t, m = 255;

	//对字符排序不会超过255，根据实际情况m值自定
	//这段代码用到桶排序思想，就是先进桶，再从不同桶里一个一个往外倒
    //sa[]保存的是1-前缀排序结果，Rank_x[]保存的是1-前缀时的各位置的排名
    for (i = 0; i <= m; i++) bar[i] = 0;
    for (i = 0; i < len; i++) bar[Rank_x[i] = s[i]]++;
    for (i = 1; i <= m; i++) bar[i] += bar[i-1];
    for (i = len-1; i >= 0; i--) sa[--bar[Rank_x[i]]] = i;

    for (k = 1,p = 1; p < len;  k *= 2, m = p)
    {
		//这段代码对1-前缀时做第二关键字排序
        for (p = 0, i = len-k; i < len; i++) Rank_y[p++] = i;
        for (i = 0; i < len; i++)
			if (sa[i] >= k)
				Rank_y[p++] = sa[i] - k;

		//又用到了一次桶排序，注意体会，是在对第二关键字排好序的序列上对
        //第一关键字进行桶排序求得了新的sa[]，result_x[]保存的是关于第二关键字
        //排好序的序列的第一关键字排名，为桶排序做好准备
        for (i = 0; i < len; i++) result_x[i] = Rank_x[Rank_y[i]];
        for (i = 0; i <= m; i++) bar[i] = 0;
        for (i = 0; i < len; i++) bar[result_x[i]]++;
        for (i = 1; i <= m; i++) bar[i] += bar[i-1];
        for (i = len-1; i >= 0; i--) sa[--bar[result_x[i]]] = Rank_y[i];

		//求新的名次数组，可以发现名次可能一样，当名次各不一样时就是排序完成时。
        for (t = Rank_x,Rank_x = Rank_y,Rank_y= t,p = 1,Rank_x[sa[0]]= 0,i  = 1; i <len; i++)
            Rank_x[sa[i]] =cmp(Rank_y,sa[i],sa[i-1],k)?p-1:p++;
    }
}



}
