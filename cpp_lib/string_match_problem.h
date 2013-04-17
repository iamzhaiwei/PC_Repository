// string_match_problem.h
//
// last-edit-by: <丁宅伟 2012-05-05> 
//
// Description:
// 字符串问题
//////////////////////////////////////////////////////////////////////

#ifndef STRING_MATCH_PROBLEM_H
#define STRING_MATCH_PROBLEM_H 1



namespace zhaiwei
{


// 用一种算法使通用字符串相匹配。
// 模式串中可能含有通配符。
// Parameter:
// str: 文本串
// pattern: 模式串
// Return value:
// 如果文本串与模式串相匹配，返回true，否则返回false
bool match_generic_string(char *str, char *pattern);


// 朴素的匹配算法
// 字符串匹配问题: 在文本text中查找模式pattern第一次出现的位置，若没有出现，返回-1
// 假设所有的字符都是ASCII字符。
// Parameter:
// text: 文本串
// pattern: 模式串
// Return value:
// 模式串在文本串第一次出现的位置的指针，或是NULL
const char *string_naive_match(const char *text, const char *pattern);


// Rabin-Karp字符串匹配算法
// Parameter:
// text: 文本串
// pattern: 模式串
// base_number: 假设每个字符都是基数为base_number的表示法中的一个数字
// prime_number: 模除用到的素数
// Return value:
// 模式串在文本串第一次出现的位置的指针，或是NULL
const char *string_rabin_karp_match(const char *text, const char *pattern, int base_number);
const char *string_rabin_karp_match(const char *text, const char *pattern, int base_number, int prime_number);


// 字符串匹配-Sunday算法。
// 假设所有的字符都是ASCII字符。
// Parameter:
// text: 文本串
// pattern: 模式串
// Return value:
// 模式串在文本串第一次出现的位置的指针，或是NULL
const char *string_sunday_match(const char *text, const char *pattern);



}

#endif // STRING_MATCH_PROBLEM_H
