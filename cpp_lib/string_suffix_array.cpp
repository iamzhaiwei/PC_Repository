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

// �ַ����ȽϷº���
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
	const char *mp_str; // �ַ���ָ��
};


// �������ַ����������ǰ׺�ĳ���
static int length_of_common_prefix(const char *str1, const char *str2)
{
	if (str1 == NULL || str2 == NULL) return 0;

	int length = 0;
	for ( ; *str1 != '\0' && *str2 != '\0' && *str1 == *str2; ++str1, ++str2)
		++length;
	return length;
}


// ��׺����洢�ַ�����׺����ʼλ�ã�0,1,2,...,length-1�����պ�׺���ֵ�������
// һ���㷨���ַ����ĺ�׺����
// str: �ԡ�\0����β���ַ���ָ��
// length: �ַ����ĳ���
// sa: ��׺����
void string_suffix_array(const char *str, int length, vector<int> &sa)
{
	if (str == NULL || length <= 0) return;

	sa.resize(length);
	for (int i = 0; i < length; ++i)
		sa[i] = i;
	sort(sa.begin(), sa.end(), string_compare(str));
}


// ��������洢��׺�����Σ����δ�0��ʼ
// ���ݺ�׺��������������
// sa: ��׺����
// ra: ��������
void string_rank_array(const vector<int> &sa, vector<int> &ra)
{
	ra.resize(sa.size());
	for (std::size_t i = 0; i < sa.size(); ++i)
		ra[sa[i]] = i;
}


// height���飺�������ڵ�������׺�������ǰ׺
// ���ݺ�׺������height����
// str: �ַ���ָ��
// length: �ַ�������
// sa: ��׺����
// ha: height����
void string_height_array(const char *str, int length, const vector<int> &sa, vector<int> &ha)
{
	if (str == NULL || length <= 0) return;

	ha.resize(sa.size());
	for (int i = 1; i < length; ++i)
		ha[i] = length_of_common_prefix(str+sa[i], str+sa[i-1]);
}


// ����һ���ַ�����ѯ��ĳ������׺�������ǰ׺
// str: �ַ���ָ��
// length: �ַ�������
// i, j: ������׺���±�
int max_length_of_common_prefix_of_suffix(const char *str, int length, int i, int j)
{
	if (str == NULL || length <= 0) return -1;

	// ��׺���� �������� height����
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

// �����ص���ظ��Ӵ���pku1743��
// ����һ���ַ����������ظ��Ӵ��������䳤�ȣ��������Ӵ������ص���
/*
int max_length_of_nonoverlapping_repetitive_substr(char *str, int length)
{
	if (str == NULL || length <= 0) return 0;

	// ��׺���� height����
	std::vector<int> sa, ha;
	string_suffix_array(str, length, sa);
	string_height_array(str, length, sa, ha);

	// ��height��������ȥ���ظ�ֵ���� ʹ��׺�������ǰ׺�Ӵ�С����
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


// ���ص���ظ��Ӵ�
// ����һ���ַ����������ظ��Ӵ��������䳤�ȣ��������Ӵ������ص���
// ��������height��������ֵ
int max_length_of_overlapping_repetitive_substr(const char *str, int length)
{
	if (str == NULL || length <= 0) return 0;

	// ��׺���� �������� height����
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


// ������Ӵ���ural1297��
// �����Ӵ���������ַ��� L ��ĳ�����ַ��� R ������д���ԭ�����ַ��� R
// һ��������ַ��� R ���ַ��� L �Ļ����Ӵ���
// ����һ���ַ��������������Ӵ��������䳤�ȡ�
// ���������������ַ���������д��ԭ�ַ������棬�м���һ��������ַ�������
// �����Ͱ������Ϊ��������µ��ַ�����ĳ������׺�������ǰ׺��
int max_length_of_palindrome_substr(const char *str, int length)
{
	if (str == NULL || length <= 0) return 0;

	// �������ַ�������д��ԭ�ַ������棬�м���һ��������ַ�����
    int new_length = length * 2 + 1;
	char *new_str = new char[new_length+1];
	char *p = copy(str, str+length, new_str);
	*p++ = '$';
	p = reverse_copy(str, str+length, p);
	*p = '\0';

	// ��׺���� �������� height����
	vector<int> sa, ra, ha;
	string_suffix_array(new_str, new_length, sa);
	string_rank_array(sa, ra);
	string_height_array(new_str, new_length, sa, ha);
	delete [] new_str;

	int palindrome_len = 1, palindrome_center_idx = 0;
	for (int i = 1; i <= length-2; ++i)
	{
		// ���ĳ���Ϊ���������
		int tmp_len = max_length_of_common_prefix_of_suffix(ra, ha, i, new_length-i-1) * 2 - 1;
		if (tmp_len > palindrome_len)
		{
			palindrome_len = tmp_len;
			palindrome_center_idx = i;
		}
		// ���ĳ���Ϊż�������
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


// �����ظ��Ӵ�(pku2406)
// ����һ���ַ��� L����֪����ַ�������ĳ���ַ��� S �ظ� R �ζ��õ��ģ��� R �����ֵ��
int number_of_continuous_repetitive_substr(const char *str, int length)
{
	if (str == NULL || length <= 0) return 0;

	// ��׺���飬�������飬height����
	vector<int> sa, ra, ha;
	string_suffix_array(str, length, sa);
	string_rank_array(sa, ra);
	string_height_array(str, length, sa, ha);

	// ����Ӵ��ĳ���k
	for (int k = 1; k < length; ++k)
	{
		if (length % k == 0 && max_length_of_common_prefix_of_suffix(ra, ha, 0, k) == length-k)
			return length / k;
	}
	return 1;
}


// ����ͬ���Ӵ��ĸ�����spoj694,spoj705��
// ����һ���ַ���������ͬ���Ӵ��ĸ�����
// ����������ÿһ���¼ӽ����ĺ�׺ suffix(sa[k]),�������� n-sa[k] ��
// �µ�ǰ׺������������height[k]���Ǻ�ǰ����ַ�����ǰ׺����ͬ�ġ�
// ���� suffix(sa[k])�������ס��� n-sa[k]- height[k]����ͬ���Ӵ����ۼ�
// �����ԭ����Ĵ𰸡����������ʱ�临�Ӷ�Ϊ O(n)��
int number_of_different_substr(const char *str, int length)
{
	if (str == NULL || length <= 0) return 0;

	// ��׺���� height����
	std::vector<int> sa, ha;
	string_suffix_array(str, length, sa);
	string_height_array(str, length, sa, ha);

	int cnt = length - sa[0];
	for (int i = 1; i < length; ++i)
		cnt += (length - sa[i] - ha[i]);
	return cnt;
}


// �����㷨
#define max 10000
static int Rx[max], Ry[max], rx[max];

static int cmp(int *y, int a, int b, int l)
{
    return y[a] == y[b] && y[a+l] == y[b+l];
}
//���ڴ�Լ�����һλ��С�ڴ��������κ�Ԫ�ص�Ԫ�أ�����cmp��ʱ��Ͳ��õ���y[a+l]
//Խ���ˣ���Ϊy[a]= y[b]�Ͱ��������ǳ�����ȣ���û�а������һλ��
// ������
// s: �ַ���
// sa: ��׺����
void string_suffix_array_da(char *s,int *sa)
{
    int len = strlen(s), *Rank_x = Rx, *Rank_y = Ry, bar[max], *result_x = rx;
    int i, j, k, p, *t, m = 255;

	//���ַ����򲻻ᳬ��255������ʵ�����mֵ�Զ�
	//��δ����õ�Ͱ����˼�룬�����Ƚ�Ͱ���ٴӲ�ͬͰ��һ��һ�����⵹
    //sa[]�������1-ǰ׺��������Rank_x[]�������1-ǰ׺ʱ�ĸ�λ�õ�����
    for (i = 0; i <= m; i++) bar[i] = 0;
    for (i = 0; i < len; i++) bar[Rank_x[i] = s[i]]++;
    for (i = 1; i <= m; i++) bar[i] += bar[i-1];
    for (i = len-1; i >= 0; i--) sa[--bar[Rank_x[i]]] = i;

    for (k = 1,p = 1; p < len;  k *= 2, m = p)
    {
		//��δ����1-ǰ׺ʱ���ڶ��ؼ�������
        for (p = 0, i = len-k; i < len; i++) Rank_y[p++] = i;
        for (i = 0; i < len; i++)
			if (sa[i] >= k)
				Rank_y[p++] = sa[i] - k;

		//���õ���һ��Ͱ����ע����ᣬ���ڶԵڶ��ؼ����ź���������϶�
        //��һ�ؼ��ֽ���Ͱ����������µ�sa[]��result_x[]������ǹ��ڵڶ��ؼ���
        //�ź�������еĵ�һ�ؼ���������ΪͰ��������׼��
        for (i = 0; i < len; i++) result_x[i] = Rank_x[Rank_y[i]];
        for (i = 0; i <= m; i++) bar[i] = 0;
        for (i = 0; i < len; i++) bar[result_x[i]]++;
        for (i = 1; i <= m; i++) bar[i] += bar[i-1];
        for (i = len-1; i >= 0; i--) sa[--bar[result_x[i]]] = Rank_y[i];

		//���µ��������飬���Է������ο���һ���������θ���һ��ʱ�����������ʱ��
        for (t = Rank_x,Rank_x = Rank_y,Rank_y= t,p = 1,Rank_x[sa[0]]= 0,i  = 1; i <len; i++)
            Rank_x[sa[i]] =cmp(Rank_y,sa[i],sa[i-1],k)?p-1:p++;
    }
}



}
