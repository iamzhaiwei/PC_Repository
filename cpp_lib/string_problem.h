// string_problem.h
//
// last-edit-by: <丁宅伟 2012-05-05>
//
// Description:
// 字符串问题
//////////////////////////////////////////////////////////////////////

#ifndef STRING_PROBLEM_H
#define STRING_PROBLEM_H 1

#include <cstddef>
#include <string>

namespace zhaiwei
{
// 求一个组合函数：如p([1,2,3]) ，输出：[1],[2],[3],[1,2],[2,3],[1,3],[1,2,3]。
// 打印一个字符串的所有组合
// 可以包含重复字符。事先排序，使相同的字符相邻。
void all_combination_with_duplicate_char(char *str, int length, int &count);
// 不包含重复字符。
void all_combination_without_duplicate_char(char *str, int length, int &count);


// 求一个全排列函数：如p([1,2,3]) ，输出：  [123],[132],[213],[231],[321],[323]。
// 打印出一个字符串的全排列。假设没有重复的字符。递归方法。
// Parameter:
// str: 字符串
// begin: 字符串第一个字符的索引
// end: 字符串最后一个字符的索引
// count: 统计全排列的数目
// 字典序方法。调用之前使字符串升序排列。可以包含重复字符。
void all_permutation_by_dictionary_order(char *str, int length, int &count);
// 字符串可以包含重复的字符，但要事先对字符串排序，使重复的字符相邻
void all_permutation_with_duplicate_char(char *str, int begin, int end, int &count);
// 字符串没有重复的字符
void all_permutation_without_duplicate_char(char *str, int begin, int end, int &count);


// 如果两个字符串的字符一样，但是顺序不一样，被认为是兄弟字符串，问如何在迅速匹配兄弟字符串
// （如，bad和adb就是兄弟字符串）。
bool brother_string_match(char *str1, char *str2);


// 淘宝笔试题：
// 设计相应的数据结构和算法，尽量高效的统计一片英文文章（总单词数目）里出现的所有英文单词，
// 按照在文章中首次出现的顺序打印输出该单词和它的出现次数
void count_word_in_a_text(const std::string &file_name);


// 删除字符串中的数字并压缩字符串。如字符串”abc123de4fg56”处理后变为”abcdefg”。注意空间和效率。
// （下面的算法只需要一次遍历，不需要开辟新空间，时间复杂度为 O(N)）
void erase_digit_char(char *str);


// 题目：输入两个字符串，从第一字符串中删除第二个字符串中所有的字符。
// 例如，输入”They are students.”和”aeiou”， 则删除之后的第一个字符串变成”Thy r stdnts.”。
// 分析：这是一道微软面试题。
void erase_specific_char(char *str1, const char *str2);


// 在一个字符串中找到第一个只出现一次的字符。如输入abaccdeff，则输出b。
// 分析：这道题是2006年google的一道笔试题。
char find_first_single_char(const char *str);


// 最长公共子序列
// 题目：如果字符串一的所有字符按其在字符串中的顺序出现在另外一个字符串二中，则字符串一称之为字符串二的子串。
// 注意，并不要求子串（字符串一）的字符必须连续出现在字符串二中。
// 请编写一个函数，输入两个字符串，求它们的最长公共子串，并打印出最长公共子串。
// 例如：输入两个字符串BDCABA和ABCBDAB，字符串BCBA和BDAB都是是它们的最长公共子串，
// 则输出它们的长度4，并打印任意一个子串。
int find_longest_common_subsequence(const char *str1, const char *str2);


// 在字符串中找出连续最长的数字串，并把这个串的长度返回，
// 并把这个最长数字串付给其中一个函数参数outputstr所指内存。
// 例如："abcd12345ed125ss123456789"的首地址传给intputstr后，函数将返回9，
// outputstr所指的值为123456789
int find_longest_continuous_digit_sequence(const char *instr, char *outstr);


// 求最大连续递增数字串（如“ads3sl456789DF3456ld345AA”中的“456789”）
// 输出第一个最大连续递增数字串，返回其长度
int find_longest_continuous_increasing_digit_sequence(const char *str, char *digits);


// 对称字符串的最大长度。
// 题目：输入一个字符串，输出该字符串中对称的子字符串的最大长度。比如输入字符串“google”，
// 由于该字符串里最长的对称子字符串是“goog”，因此输出4。
int find_longest_symmetric_substring(const char *str);


// 用C 语言实现函数void * memmove(void *dest,const void *src,size_t n)。
// memmove 函数的功能是拷贝src 所指的内存内容前n 个字节到dest 所指的地址上。
void *memory_move(void *dest, const void *src, size_t n);
// 从后往前拷贝
void *memory_move_backward(void *dest, const void *src, size_t n);
// 从前往后拷贝
void *memory_move_forward(void *dest, const void *src, size_t n);


//输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。句子中单词以空格符隔开。
//实现速度最快，移动最少。为简单起见，标点符号和普通字母一样处理。
//例如输入“I am a student.”，则输出“student. a am I”。
void reverse_sentence(char *sentence);


// 输入一个表示整数的字符串，把该字符串转换成整数并输出。
// 如将字符串”+123”123, ”-0123”-123, “123CS45”123, “123.45CS”123, “CS123.45”0
int string_atoi(const char *str);


// 字符串比较
// Parameter:
// str1: 字符串
// str2: 字符串
// Return value:
// 负值, 或0, 或正值
int string_compare(const char *str1, const char *str2);


// 字符串原地压缩
// 题目描述："eeeeeaaaff" 压缩为 "e5a3f2"，请编程实现。
void string_compress_in_place(char *str);


// 腾讯笔试题：
// 一个字符串S1：全是由不同的字母组成的字符串如：abcdefghijklmn
// 另一个字符串S2：类似于S1，但长度要比S1短。
// 问题是，设计一种算法，求S2中的字母是否均在S1中。
// 可以处理大小写字母
bool string_contain_by_bitmap(char *str1, char *str2);
// 可以处理大小写字母
bool string_contain_by_hashmap(char *str1, char *str2);
// 只能处理大写字母或小写字母。实现的是处理大写字母
bool string_contain_by_shift_bit(char *str1, char *str2);


// 已知一个字符串，比如 asderwsde，寻找其中的一个子字符串比如 sde 的个数，如果没有返回0，
// 有的话返回子字符串的个数。
int string_count_substr(const char *str, const char *substr);


// 字符串编辑距离问题 CLRS 15-3
// str1: 源文本串, 从下标1开始
// str1_len: 源文本串的长度
// str2: 目标文本串, 从下标1开始
// str2_len: 目标文本串的长度
// op_cost: 每种操作的代价, op_cost[0]复制, op_cost[1]替换, op_cost[2]删除,
//          op_cost[3]插入, op_cost[4]交换, op_cost[5]消灭
// op_num: 操作的数目
// 没有测试
int string_edit_distance(const char *str1, int str1_len, const char *str2, int str2_len, int *op_cost, int op_num);


// 华为面试题
// 判断一字符串是不是对称的，如：abccba
bool string_is_symmetric(const char *str);


// 定义字符串的左旋转操作：把字符串前面的若干个字符移动到字符串的尾部。
// 如把字符串abcdef左旋转2 位得到字符串cdefab。请实现字符串左旋转的函数。
// 要求时间对长度为n的字符串操作的复杂度为O(n)，辅助内存为O(1)。
// Parameter:
// str: 字符串
// n: 字符串的长度
// m: 左旋转的字符数
void string_left_shift(char *str, int n, int m);


// 不用任何中间变量，实现strlen函数
int string_length(const char *str);


// 百度笔试题
// 用 C 语言实现函数 void * memmove(void *dest, const void *src, size_t n)。
// memmove 函数的功能是拷贝 src 所指的内存内容前 n 个字节到 dest 所指的地址上。
// 注意边界条件。
void *string_memmove(void *dest, const void *src, size_t n);


// 2005年11月金山笔试题。编码完成下面的处理函数。
// 函数将字符串中的字符'*'移到串的前部分，前面的非'*'字符后移，但不能改变非'*'字符的先后顺序，函数返回
// 串中字符'*'的数量。
// 如原始串为：ab**cd**e*12，处理后为*****abcde12，函数并返回值为5。
// （要求使用尽量少的时间和辅助空间）
int string_move_star_char_forward(char *str);


//颠倒一个字符串。优化速度。优化空间。
void string_reverse(char *str);
void string_reverse(char *str, int length);

}

#endif // STRING_PROBLEM_H
//////////////////////////////////////////////////////////////////////
