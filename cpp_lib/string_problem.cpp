// string_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "string_problem.h"
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>
#include <vector>
#include <boost/multi_array.hpp>
#include <boost/unordered_map.hpp>
#include "bitmap.h"
#include "string_match_problem.h"
//////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;

namespace zhaiwei
{

// 求一个组合函数：如p([1,2,3]) ，输出：[1],[2],[3],[1,2],[2,3],[1,3],[1,2,3]。
// 打印一个字符串的所有组合
// 参数：
// str: 字符串
// length: 字符串长度
// combination: 已获得的字符组合
// combination_length: 本次递归调用要获得的字符组合的长度
// count: 已获得的字符组合的数目
// 可以包含重复字符。事先排序，使相同的字符相邻。
static void all_combination_with_duplicate_char(char *str, int length, vector<char> &combination,
                                                int combination_length, int &count)
{
	if (combination_length == 0)
	{
		for (std::size_t i = 0; i != combination.size(); ++i)
			cout << combination[i];
		cout << endl;
		++count;
		return;
	}
	
	if (length == 0)
		return;
	
	combination.push_back(str[0]);
	int i;
	for (i = 1; i < length; ++i)
	{
		if (str[i] != str[0])
			break;
	}
	all_combination_with_duplicate_char(str+i, length-i, combination, combination_length-1, count);
	combination.pop_back();
	all_combination_with_duplicate_char(str+i, length-i, combination, combination_length, count);
}
void all_combination_with_duplicate_char(char *str, int length, int &count)
{
	if (str == NULL || length <= 0)
		return;

	vector<char> combination;
	combination.reserve(length);
	count = 0;
	for (int combination_length = 1; combination_length <= length-1; ++combination_length)
	{
		all_combination_with_duplicate_char(str, length, combination, combination_length, count);
	}
	++count;
	cout << str << endl;
}
// 不包含重复字符。
static void all_combination_without_duplicate_char(char *str, int length, vector<char> &combination,
                                                   int combination_length, int &count)
{
	if (combination_length == 0)
	{
		for (std::size_t i = 0; i != combination.size(); ++i)
			cout << combination[i];
		cout << endl;
		++count;
		return;
	}
	
	if (length == 0)
		return;
	
	combination.push_back(str[0]);
	all_combination_without_duplicate_char(str+1, length-1, combination, combination_length-1, count);
	combination.pop_back();
	all_combination_without_duplicate_char(str+1, length-1, combination, combination_length, count);
}
void all_combination_without_duplicate_char(char *str, int length, int &count)
{
	if (str == NULL || length <= 0)
		return;

	vector<char> combination;
	combination.reserve(length);
	count = 0;
	for (int combination_length = 1; combination_length <= length; ++combination_length)
	{
		all_combination_without_duplicate_char(str, length, combination, combination_length, count);
	}
}


// 求一个全排列函数：如p([1,2,3]) ，输出：  [123],[132],[213],[231],[321],[323]。
// 打印出一个字符串的全排列。假设没有重复的字符。递归方法。
// Parameter:
// str: 字符串
// begin: 字符串第一个字符的索引
// end: 字符串最后一个字符的索引
// count: 统计全排列的数目，调用之前赋值为0
// 字符串没有重复的字符
void all_permutation_without_duplicate_char(char *str, int begin, int end, int &count)
{
    if (begin >= end)
    {
        cout << str << endl;
        ++count;
        return;
    }
    
    for (int i = begin; i <= end; ++i)
    {
        std::swap(str[begin], str[i]);
        all_permutation_without_duplicate_char(str, begin+1, end, count);
        std::swap(str[begin], str[i]);
    }
}
// 字符串可以包含重复的字符，但要事先对字符串排序，使重复的字符相邻
void all_permutation_with_duplicate_char(char *str, int begin, int end, int &count)
{
    if (begin >= end)
    {
        cout << str << endl;
        ++count;
        return;
    }

    all_permutation_with_duplicate_char(str, begin+1, end, count);
    int i = begin + 1;
    while (i <= end)
    {
        if (str[begin] != str[i])
        {
            std::swap(str[begin], str[i]);
            all_permutation_with_duplicate_char(str, begin+1, end, count);
            std::swap(str[begin], str[i]);

            while (str[i] == str[i+1])
                ++i;
        }
        ++i;
    }
}
// 字典序方法。调用之前使字符串升序排列。可以包含重复字符。
void all_permutation_by_dictionary_order(char *str, int length, int &count)
{
	if (str == NULL || length <= 0)
		return;

	cout << str << endl;
	++count;

	while (true)
	{
		int i;
		for (i = length-2; i >= 0; --i)
		{
			if (str[i] < str[i+1])
				break;
		}
		if (i <= -1)
			break;
		for (int j = length-1; j > i; --j)
		{
			if (str[i] < str[j])
			{
				swap(str[i], str[j]);
				string_reverse(&str[i+1]);
				break;
			}
		}
		cout << str << endl;
		++count;
	}
}


// 如果两个字符串的字符一样，但是顺序不一样，被认为是兄弟字符串，问如何在迅速匹配兄弟字符串
// （如，bad和adb就是兄弟字符串）。
bool brother_string_match(char *str1, char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return false;

    vector<int> count(256, 0);
    char *p = str1;
    while (*p != '\0')
    {
        ++count[(int)(unsigned char)*p];
        ++p;
    }
    p = str2;
    while (*p != '\0')
    {
        if (count[(int)(unsigned char)*p] == 0)
            return false;
        --count[(int)(unsigned char)*p];
        ++p;
    }
    for (int i = 0; i != 256; ++i)
    {
        if (count[i] != 0)
            return false;
    }
    return true;
}


// 淘宝笔试题：
// 设计相应的数据结构和算法，尽量高效的统计一片英文文章（总单词数目）里出现的所有英文单词，
// 按照在文章中首次出现的顺序打印输出该单词和它的出现次数
void count_word_in_a_text(const string &file_name)
{
	// 按照单词在文章中首次出现的顺序保存单词
	list<string> words;
	// 记录单词出现的次数
	unordered_map<string, int> word_count;
	unordered_map<string, int>::iterator word_count_iter;

	ifstream in_file(file_name.c_str());
	string word;
	int last_pos;
	while (in_file >> word)
	{
		if (isupper(word[0]))
			word[0] = tolower(word[0]);
		last_pos = word.length() - 1;
		if (word[last_pos] == ',' || word[last_pos] == '.')
			word.erase(last_pos, 1);
		if ( (word_count_iter = word_count.find(word)) == word_count.end()) // 单词第一次出现
		{
			word_count.insert(make_pair(word, 1));
			words.push_back(word);
		}
		else // 单词又一次出现
		{
			++word_count_iter->second;
		}
	}
	for (list<string>::iterator iter = words.begin(); iter != words.end(); ++iter)
	{
		word_count_iter = word_count.find(*iter);
		cout << *iter << ": " << word_count_iter->second << endl;
	}
}


// 删除字符串中的数字并压缩字符串。如字符串”abc123de4fg56”处理后变为”abcdefg”。注意空间和效率。
// （下面的算法只需要一次遍历，不需要开辟新空间，时间复杂度为 O(N)）
void erase_digit_char(char *str)
{
    if (str == NULL)
        return;

    char *p_digit, *p;
    p_digit = p = str;
    while (*p != '\0')
    {
        if (!isdigit(*p))
        {
            std::swap(*p_digit, *p);
            ++p_digit;
            ++p;
        }
        else
        {
            ++p;
        }
    }
    *p_digit = '\0';
}


// 题目：输入两个字符串，从第一字符串中删除第二个字符串中所有的字符。
// 例如，输入”They are students.”和”aeiou”， 则删除之后的第一个字符串变成”Thy r stdnts.”。
// 分析：这是一道微软面试题。
void erase_specific_char(char *str1, const char *str2)
{
    char array[256];
    memset(array, 0, sizeof(array)/sizeof(char));

    int len2 = strlen(str2);
    for (int i = 0; i != len2; ++i)
        ++array[(int)(unsigned char)(str2[i])];

    char *p1 = str1, *p2 = str1;
    while (*p2 != '\0')
    {
        if (array[(int)(unsigned char)(*p2)] == 0)
        {
            *p1++ = *p2++;
        }
        else
        {
            ++p2;
        }
    }
    *p1 = '\0';
}


// 在一个字符串中找到第一个只出现一次的字符。如输入abaccdeff，则输出b。
// 分析：这道题是2006年google的一道笔试题。
char find_first_single_char(const char *str)
{
    int count[256];
    memset(count, 0, sizeof(int)*256);

    const char *p = str;
    while (*p != '\0')
    {
        ++count[(int)(unsigned char)(*p)];
        ++p;
    }

    p = str;
    while (*p !='\0')
    {
        if (count[(int)(unsigned char)(*p)] == 1)
            return *p;
        ++p;
    }

    return '\0';
}


// 最长公共子序列
// 题目：如果字符串一的所有字符按其在字符串中的顺序出现在另外一个字符串二中，则字符串一称之为字符串二的子串。
// 注意，并不要求子串（字符串一）的字符必须连续出现在字符串二中。
// 请编写一个函数，输入两个字符串，求它们的最长公共子串，并打印出最长公共子串。
// 例如：输入两个字符串BDCABA和ABCBDAB，字符串BCBA和BDAB都是是它们的最长公共子串，
// 则输出它们的长度4，并打印任意一个子串。
// 利用路径表和字符串1输出最长公共子序列
static void print_longest_common_subsequence_using_path_table(boost::multi_array<int, 2> &path_table,
                                             const char *str1, int i, int j)
{
    if (i == 0 || j == 0)
        return;

    if (path_table[i][j] == 0)
    {
        print_longest_common_subsequence_using_path_table(path_table, str1, i-1, j-1);
        std::cout << str1[i-1];
    }
    else if (path_table[i][j] == 1)
    {
        print_longest_common_subsequence_using_path_table(path_table, str1, i-1, j);
    }
    else
    {
        print_longest_common_subsequence_using_path_table(path_table, str1, i, j-1);
    }
}
// 利用长度表和字符串1输出最长公共子序列
static void print_longest_common_subsequence_using_length_table(boost::multi_array<int, 2> &length_table,
                                             const char *str1, int i, int j)
{
    if (i == 0 || j == 0)
        return;

    if (length_table[i][j] == length_table[i-1][j-1]+1)
    {
        print_longest_common_subsequence_using_length_table(length_table, str1, i-1, j-1);
        std::cout << str1[i-1];
    }
    else if (length_table[i][j] == length_table[i-1][j])
    {
        print_longest_common_subsequence_using_length_table(length_table, str1, i-1, j);
    }
    else if (length_table[i][j] == length_table[i][j-1])
    {
        print_longest_common_subsequence_using_length_table(length_table, str1, i, j-1);
    }
}
// 查找最长公共子序列，返回长度
int find_longest_common_subsequence(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return 0;

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // length_table[i][j]表示str1[i-1]与str2[j-1]的最长公共子串长度
    boost::multi_array<int, 2> length_table(boost::extents[len1+1][len2+1]);
    // path_table[i][j] = 0, 往左上方走, = 1, 往上方走，= 2, 往左方走
    boost::multi_array<int, 2> path_table(boost::extents[len1+1][len2+1]);

    for (int i = 0; i <= len1; ++i)
        length_table[i][0] = 0;
    for (int j = 0; j <= len2; ++j)
        length_table[0][j] = 0;
    for (int i = 1; i <= len1; ++i)
    {
        for (int j = 1; j <= len2; ++j)
        {
            if (str1[i-1] == str2[j-1])
            {
                length_table[i][j] = length_table[i-1][j-1] + 1;
                path_table[i][j] = 0;
            }
            else if (length_table[i-1][j] > length_table[i][j-1])
            {
                length_table[i][j] = length_table[i-1][j];
                path_table[i][j] = 1;
            }
            else
            {
                length_table[i][j] = length_table[i][j-1];
                path_table[i][j] = 2;
            }
        }
    }

    print_longest_common_subsequence_using_path_table(path_table, str1, len1, len2);
    std::cout << std::endl;

    print_longest_common_subsequence_using_length_table(length_table, str1, len1, len2);
    std::cout << std::endl;

    return length_table[len1][len2];
}


// 在字符串中找出连续最长的数字串，并把这个串的长度返回，
// 并把这个最长数字串付给其中一个函数参数outputstr所指内存。
// 例如："abcd12345ed125ss123456789"的首地址传给intputstr后，函数将返回9，
// outputstr所指的值为123456789
int find_longest_continuous_digit_sequence(const char *instr, char *outstr)
{
    if (instr == NULL)
        return 0;

    int max_len = 0;
    const char *p_max_begin = NULL;
    int length;
    while (*instr != '\0')
    {
        length = 0;
        while (*instr >= '0' && *instr <= '9')
        {
            ++length;
            ++instr;
        }

        if (length > max_len)
        {
            max_len = length;
            p_max_begin = instr - max_len;
        }

        ++instr;
    }

    for (int i = 0; i != max_len; ++i)
    {
        outstr[i] = p_max_begin[i];
    }
    return max_len;
}


// 求最大连续递增数字串（如“ads3sl456789DF3456ld345AA”中的“456789”）
// 输出第一个最大连续递增数字串，返回其长度
int find_longest_continuous_increasing_digit_sequence(const char *str, char *digits)
{
    if (str == NULL)
    {
        digits[0] = '\0';
        return 0;
    }

    int str_len = strlen(str);

    int max_begin = 0, max_len = 0;
    int i = 0, curr_len = 0;
    while (i < str_len)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            if (curr_len == 0 || str[i] > str[i-1]) // 新的数字串开始，或是当前的递增数字串继续增长
            {
                ++curr_len;
            }
            else // 当前的递增数字串结束，新的数字串开始
            {
                if (curr_len > max_len)
                {
                    max_len = curr_len;
                    max_begin = i - curr_len;
                }
                curr_len = 1;
            }
        }
        else // 当前的递增数字串结束
        {
            if (curr_len > max_len)
                {
                    max_len = curr_len;
                    max_begin = i - curr_len;
                }
                curr_len = 0;
        }
        ++i;
    }

    for (int j = 0; j < max_len; ++j)
    {
        digits[j] = str[max_begin+j];
    }
    digits[max_len] = '\0';
    return max_len;
}


// 对称字符串的最大长度。
// 题目：输入一个字符串，输出该字符串中对称的子字符串的最大长度。比如输入字符串“google”，
// 由于该字符串里最长的对称子字符串是“goog”，因此输出4。
// 查找以index为中心的最长回文
static int find_longest_palindrain_middle(const char *str, int length, int index)
{
    int max_len = 1;
    for (int i = 1; i <= index && i <= length-index-1; ++i)
    {
        if (str[index-i] == str[index+i])
            max_len += 2;
        else
            break;
    }
    return max_len;
}
// 查找以index和index+1为中心的最长回文
static int find_longest_palindrain_mirror(const char *str, int length, int index)
{
    int max_len = 0;
    for (int i = 0, j = 1; i >= 0 && i <= index && j >= 1 && j <= length-index-1; ++i, ++j)
    {
        if (str[index-i] == str[index+j])
            max_len += 2;
        else
            break;
    }
    return max_len;
}
int find_longest_symmetric_substring(const char *str)
{
    int length = strlen(str);

    int len1, len2, max_len = 0;
    for (int i = 0; i != length; ++i)
    {
        len1 = find_longest_palindrain_middle(str, length, i);
        len2 = find_longest_palindrain_mirror(str, length, i);
        if (len2 > len1)
            len1 = len2;
        if (len1 > max_len)
            max_len = len1;
    }
    return max_len;
}


// 用C 语言实现函数void * memmove(void *dest,const void *src,size_t n)。
// memmove 函数的功能是拷贝src 所指的内存内容前n 个字节到dest 所指的地址上。
void *memory_move(void *dest, const void *src, size_t n)
{
	assert(dest != NULL && src != NULL);
	
	char *p_dest = (char *)dest;
	const char *p_src = (const char *)src;
	if (p_dest >= p_src && p_dest < p_src+n)
		return memory_move_backward(dest, src, n);
	else
		return memory_move_forward(dest, src, n);
}

// 从后往前拷贝
void *memory_move_backward(void *dest, const void *src, size_t n)
{
	assert(dest != NULL && src != NULL);
	
	char *p_dest = (char *)dest;
	const char *p_src = (const char *)src;
	p_dest += (n - 1);
	p_src += (n - 1);
	for (size_t i = 0; i < n; ++i)
	{
		*p_dest-- = *p_src--;
	}
	return dest;
}
// 从前往后拷贝
void *memory_move_forward(void *dest, const void *src, size_t n)
{
	assert(dest != NULL && src != NULL);
	
	char *p_dest = (char *)dest;
	const char *p_src = (const char *)src;
	for (size_t i = 0; i < n; ++i)
	{
		*p_dest++ = *p_src++;
	}
	return dest;
}


//输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。句子中单词以空格符隔开。
//实现速度最快，移动最少。为简单起见，标点符号和普通字母一样处理。
//例如输入“I am a student.”，则输出“student. a am I”。
void reverse_sentence(char *sentence)
{
    int length = strlen(sentence);
    string_reverse(sentence, length);

    int i;
    char *p = sentence;
    char *word;
    while (true)
    {
        while (*p != '\0' && *p == ' ')
            ++p;

        i = 0;
        word = p;
        while (*p != '\0' && *p != ' ')
        {
            ++p;
            ++i;
        }
        string_reverse(word, i);

        if (*p == '\0')
            break;
        ++p;
    }
}


// 输入一个表示整数的字符串，把该字符串转换成整数并输出。
// 如将字符串”+123”123, ”-0123”-123, “123CS45”123, “123.45CS”123, “CS123.45”0
int string_atoi(const char *str)
{
    while (isspace((int)(unsigned char)(*str)))
        ++str;

    int sign = (*str == '-'? -1: 1);

    if (*str == '-' || *str == '+')
        ++str;

    int c;
    int data = 0;
    while (*str != '\0')
    {
        c = (int)(unsigned char)(*str++);
        if (isdigit(c))
            data = data * 10 + c - '0';
        else
            break;
    }
    data *= sign;

    return data;
}


// 字符串比较
// Parameter:
// str1: 字符串
// str2: 字符串
// Return value:
// 负值, 或0, 或正值
int string_compare(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
    {
        ++str1;
        ++str2;
    }
    return *str1 - *str2;
}


// 字符串原地压缩
// 题目描述："eeeeeaaaff" 压缩为 "e5a3f2"，请编程实现。
void string_compress_in_place(char *str)
{
    char *p_curr = str, *p_next = str;
    int count = 1;
    while (*p_curr != '\0' && *p_next != '\0')
    {
        ++p_next;
        if (*p_curr == *p_next)
        {
            ++count;
        }
        else
        {
            ++p_curr;
            *p_curr = count + '0';
            ++p_curr;
            *p_curr = *p_next;
            count = 1;
        }
    }
}

// 腾讯笔试题：
// 一个字符串S1：全是由不同的字母组成的字符串如：abcdefghijklmn
// 另一个字符串S2：类似于S1，但长度要比S1短。
// 问题是，设计一种算法，求S2中的字母是否均在S1中。
// http://blog.csdn.net/v_JULY_v/article/details/6347454
// 解法：在bitmap和hashmap中大写字母排在小写字母前面
// 返回字母的hash值，也就是它的索引
static int index(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c - 'A';
	else if (c >= 'a' && c <= 'z')
		return 26 + c - 'a';
	else
		return -1;
}
// 可以处理大小写字母
bool string_contain_by_bitmap(char *str1, char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return false;
		
	bitmap bm(52);
	while (*str1 != '\0')
	{
		bm.set(index(*str1));
		++str1;
	}
	while (*str2 != '\0')
	{
		if (bm.bit(index(*str2)) == 0)
			return false;
		++str2;
	}
	return true;
}
// 可以处理大小写字母
// 可以使用与bitmap方法相同的计数方法，但这里使用另一种
bool string_contain_by_hashmap(char *str1, char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return false;

    int str2_count = 0; // 记录str2中不同字母的数目
    int count[52] = {0};
    int idx;
    while (*str2 != '\0')
    {
        idx = index(*str2);
        if (count[idx] == 0)
        {
            count[idx] = 1;
            ++str2_count;
        }
        ++str2;
    }
    while (*str1 != '\0')
    {
        idx = index(*str1);
        if (count[idx] > 0)
        {
            --count[idx];
            --str2_count;
            if (str2_count == 0)
                return true;
        }
        ++str1;
    }
    return false;
}
// 只能处理大写字母或小写字母。实现的是处理大写字母
bool string_contain_by_shift_bit(char *str1, char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return false;
    
    unsigned int str1_data = 0, str2_data = 0;
    while (*str1 != '\0')
    {
        str1_data |= (1 << (*str1-'A'));
        ++str1;
    }
    while (*str2 != '\0')
    {
        str2_data |= (1 << (*str2-'A'));
        ++str2;
    }
    return (str1_data|str2_data) == str1_data;
}


// 已知一个字符串，比如 asderwsde，寻找其中的一个子字符串比如 sde 的个数，如果没有返回0，
// 有的话返回子字符串的个数。
int string_count_substr(const char *str, const char *substr)
{
    if (str == NULL || substr == NULL)
        return 0;

    int count = 0;
    const char *pos = str;
    while (true)
    {
        pos = string_sunday_match(pos, substr);
        if (pos == NULL)
            break;
        ++count;
        pos += 1;
    }
    return count;
}


// 字符串编辑距离问题 CLRS 15-3
// 输出最优操作序列
void print_optimal_op_sequence(const boost::multi_array<int, 2> &op, int i, int j)
{
    if (i == 0 && j == 0)
        return;

    int op_id = op[i][j];
    if (op_id == 0 || op_id == 1)
    {
        i -= 1;
        j -= 1;
    }
    else if (op_id == 2)
    {
        i -= 1;
    }
    else if (op_id == 3)
    {
        j -= 1;
    }
    else if (op_id == 4)
    {
        i -= 2;
        j -= 2;
    }
    else
    {
        i = -op_id;
    }
    print_optimal_op_sequence(op, i, j);
    fprintf(stdout, "%d ", op_id);
}
// str1: 源文本串, 从下标1开始
// str1_len: 源文本串的长度
// str2: 目标文本串, 从下标1开始
// str2_len: 目标文本串的长度
// op_cost: 每种操作的代价, op_cost[0]复制, op_cost[1]替换, op_cost[2]删除,
//          op_cost[3]插入, op_cost[4]交换, op_cost[5]消灭
// op_num: 操作的数目
int string_edit_distance(const char *str1, int str1_len, const char *str2, int str2_len, int *op_cost, int op_num)
{
    // cost[i][j]记录将字符串str1[1...i]转换为str2[1...j]的代价
    boost::multi_array<int, 2> cost(boost::extents[1+str1_len][1+str2_len]);
    // op[i][j]记录str1[i]->str2[j]的操作
    // op[i][j] = 0, 1, 2, 3, 4, -i
    boost::multi_array<int, 2> op(boost::extents[1+str1_len][1+str2_len]);
    // str1是空串
    for (int j = 0; j <= str2_len; ++j)
    {
        cost[0][j] = j * op_cost[3];
        op[0][j] = 3;
    }
    // str2是空串
    for (int i = 0; i <= str1_len; ++i)
    {
        cost[i][0] = i * op_cost[2];
        op[i][0] = 2;
    }
    int tmp_cost;
    for (int i = 1; i <= str1_len; ++i)
    {
        for (int j = 1; j <= str2_len; ++j)
        {
            // 复制
            if (str1[i] == str2[j])
            {
                cost[i][j] = cost[i-1][j-1] + op_cost[0];
                op[i][j] = 0;
            }
            else // 替换
            {
                cost[i][j] = cost[i-1][j-1] + op_cost[1];
                op[i][j] = 1;
            }
            // 删除
            if ( (tmp_cost = cost[i-1][j] + op_cost[2]) < cost[i][j])
            {
                cost[i][j] = tmp_cost;
                op[i][j] = 2;
            }
            // 插入
            if ( (tmp_cost = cost[i][j-1] + op_cost[3]) < cost[i][j])
            {
                cost[i][j] = tmp_cost;
                op[i][j] = 3;
            }
            // 交换
            if (i >= 2 && j >= 2 && str1[i-1] == str2[j] && str1[i] == str2[j-1] &&
                (tmp_cost = cost[i-2][j-2] + op_cost[4]) < cost[i][j])
            {
                cost[i][j] = tmp_cost;
                op[i][j] = 4;
            }
        }
    }
    // 消灭
    for (int i = 0; i <= str1_len-1; ++i)
    {
        if ( (tmp_cost = cost[i][str2_len] + op_cost[5]) < cost[str1_len][str2_len])
        {
            cost[str1_len][str2_len] = tmp_cost;
            op[str1_len][str2_len] = -i;
        }
    }

    fprintf(stdout, "代价表:\n");
    for (int i = 0; i <= str1_len; ++i)
    {
        for (int j = 0; j <= str2_len; ++j)
            fprintf(stdout, "%d ", cost[i][j]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "操作表:\n");
    for (int i = 0; i <= str1_len; ++i)
    {
        for (int j = 0; j <= str2_len; ++j)
            fprintf(stdout, "%d ", op[i][j]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    print_optimal_op_sequence(op, str1_len, str2_len);
    fprintf(stdout, "\n");
    return cost[str1_len][str2_len];
}


// 华为面试题
// 判断一字符串是不是对称的，如：abccba
bool string_is_symmetric(const char *str)
{
    if (str == NULL)
        return false;

    int length = strlen(str);
    int first = 0, last = length - 1;
    while (first <= last)
    {
        if (str[first] != str[last])
            break;
        ++first;
        --last;
    }
    if (first > last)
        return true;
    else
        return false;
}


// 定义字符串的左旋转操作：把字符串前面的若干个字符移动到字符串的尾部。
// 如把字符串abcdef左旋转2 位得到字符串cdefab。请实现字符串左旋转的函数。
// 要求时间对长度为n的字符串操作的复杂度为O(n)，辅助内存为O(1)。
// Parameter:
// str: 字符串
// n: 字符串的长度
// m: 左旋转的字符数
void string_left_shift(char *str, int n, int m)
{
    if (str == NULL)
        return;

    if (n < m)
        m %= n;

    string_reverse(str, n);
    string_reverse(str, n-m);
    string_reverse(str+n-m, m);
}


// 不用任何中间变量，实现strlen函数
int string_length(const char *str)
{
    if (str == NULL || *str == '\0')
        return 0;
    return string_length(str+1) + 1;
}


// 百度笔试题
// 用 C 语言实现函数 void * memmove(void *dest, const void *src, size_t n)。
// memmove 函数的功能是拷贝 src 所指的内存内容前 n 个字节到 dest 所指的地址上。
// 注意边界条件。
void *string_memmove(void *dest, const void *src, size_t n)
{
    assert(dest);
    assert(src);

    unsigned char *p_dest = (unsigned char *)dest;
    const unsigned char *p_src = (const unsigned char *)src;
    int step = 1;
    if (p_dest < p_src+n)
    {
        p_dest = p_dest + n - 1;
        p_src = p_src + n - 1;
        step = -1;
    }

    for (size_t i = 0; i < n; ++i)
    {
        *p_dest = *p_src;
        p_dest += step;
        p_src += step;
    }
    return dest;
}


// 2005年11月金山笔试题。编码完成下面的处理函数。
// 函数将字符串中的字符'*'移到串的前部分，前面的非'*'字符后移，但不能改变非'*'字符的先后顺序，函数返回
// 串中字符'*'的数量。
// 如原始串为：ab**cd**e*12，处理后为*****abcde12，函数并返回值为5。
// （要求使用尽量少的时间和辅助空间）
int string_move_star_char_forward(char *str)
{
    if (str == NULL)
        return 0;

    int count = 0;
    int length = strlen(str);
    char *p_star, *p;
    p_star = p = str + length - 1;
    while (p >= str)
    {
        if (*p != '*')
        {
            std::swap(*p, *p_star);
            --p;
            --p_star;
        }
        else
        {
            ++count;
            --p;
        }
    }
    return count;
}


//颠倒一个字符串。优化速度。优化空间。
void string_reverse(char *str)
{
    int length = strlen(str);
    string_reverse(str, length);
}
void string_reverse(char *str, int length)
{
    char ch;
    for (char *i = str, *j = str + length - 1; i < j; ++i, --j)
    {
        ch = *i;
        *i = *j;
        *j = ch;
    }
}


}
