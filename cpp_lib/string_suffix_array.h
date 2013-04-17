// string_suffix_array.h
//
// last-edit-by:
//
// Description:
// 字符串后缀数组
//////////////////////////////////////////////////////////////////////

#ifndef STRING_SUFFIX_ARRAY_H
#define STRING_SUFFIX_ARRAY_H 1

#include <vector>
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{

// 一般算法求字符串的后缀数组
// str: 以‘\0’结尾的字符串指针
// length: 字符串的长度
// sa: 后缀数组
void string_suffix_array(const char *str, int length, std::vector<int> &sa);


// 名次数组存储后缀的次词
// 根据后缀数组求名次数组
// sa: 后缀数组
// ra: 名次数组
void string_rank_array(const std::vector<int> &sa, std::vector<int> &ra);


// height数组：排名相邻的两个后缀的最长公共前缀
// 根据后缀数组求height数组
// str: 字符串指针
// length: 字符串长度
// sa: 后缀数组
// ha: height数组
void string_height_array(const char *str, int length, const std::vector<int> &sa, std::vector<int> &ha);


// 给定一个字符串，询问某两个后缀的最长公共前缀
// str: 字符串指针
// length: 字符串长度
// i, j: 两个后缀的下标
int max_length_of_common_prefix_of_suffix(const char *str, int length, int i, int j);
int max_length_of_common_prefix_of_suffix(const std::vector<int> &ra, const std::vector<int> &ha, int i, int j);

// 不可重叠最长重复子串（pku1743）
// 给定一个字符串，输出最长重复子串，返回其长度，这两个子串不能重叠。
int max_length_of_nonoverlapping_repetitive_substr(const char *str, int length);


// 重复子串：字符串 R 在字符串 L 中至少出现两次，则称 R 是 L 的重复子串。
// 可重叠最长重复子串
// 给定一个字符串，输出最长重复子串，返回其长度，这两个子串可以重叠。
int max_length_of_overlapping_repetitive_substr(const char *str, int length);


// 最长回文子串（ural1297）
// 回文子串：如果将字符串 L 的某个子字符串 R 反过来写后和原来的字符串 R
// 一样，则称字符串 R 是字符串 L 的回文子串。
// 给定一个字符串，输出最长回文子串，返回其长度。
int max_length_of_palindrome_substr(const char *str, int length);


// 连续重复子串(pku2406)
// 给定一个字符串 L，已知这个字符串是由某个字符串 S 重复 R 次而得到的，求 R 的最大值。
int number_of_continuous_repetitive_substr(const char *str, int length);


// 不相同的子串的个数（spoj694,spoj705）
// 给定一个字符串，求不相同的子串的个数。
int number_of_different_substr(const char *str, int length);


// 对于串约定最后一位是小于串中其他任何元素的元素
// 参数：
// s: 字符串
// sa: 后缀数组
void string_suffix_array_da(char *s,int *sa);
}

/*

*/
#endif
