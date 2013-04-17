// string_match_problem.cpp
//////////////////////////////////////////////////////////////////////

#include "string_match_problem.h"
#include <cstring>
#include "my_math.h"
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{


// 用一种算法使通用字符串相匹配。
// 模式串中可能含有通配符。
// Parameter:
// str: 文本串
// pattern: 模式串
// Return value:
// 如果文本串与模式串相匹配，返回true，否则返回false
bool match_generic_string(char *str, char *pattern)
{
    if (*pattern == '\0')
        return true;

    if (*pattern == '*')
    {
        do
        {
            if (match_generic_string(++str, pattern+1))
                return true;
        } while (*str != '\0');
        return false;
    }

    if (*str == '\0')
        return false;
    
    if (*str == *pattern || *pattern == '?')
        return match_generic_string(str+1, pattern+1);
    else
        return false;
}


// 朴素的匹配算法
// 字符串匹配问题: 在文本text中查找模式pattern第一次出现的位置，若没有出现，返回-1
// 假设所有的字符都是ASCII字符。
// Parameter:
// text: 文本串
// pattern: 模式串
// Return value:
// 模式串在文本串第一次出现的位置的指针，或是NULL
const char *string_naive_match(const char *text, const char *pattern)
{
    if (text == NULL || pattern == NULL)
        return NULL;

    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    
    int i, j;
    for (i = 0; i <= text_len-pattern_len; ++i)
    {
        for (j = 0; j < pattern_len; ++j)
        {
            if (text[i+j] != pattern[j])
                break;
        }
        if (j == pattern_len)
            return text+i;
    }
    return NULL;
        
}


// Rabin-Karp字符串匹配算法
// Parameter:
// text: 文本串
// pattern: 模式串
// base_number: 假设每个字符都是基数为base_number的表示法中的一个数字
// prime_number: 模除用到的素数
// Return value:
// 模式串在文本串第一次出现的位置的指针，或是NULL
const char *string_rabin_karp_match(const char *text, const char *pattern, int base_number)
{
    if (text == NULL || pattern == NULL)
        return NULL;

    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    
    int p = 0, t = 0;
    for (int i = 0; i < pattern_len; ++i)
    {
        p = p * base_number + pattern[i];
        t = t * base_number + text[i];
    }

    int high = pow<int>(base_number, pattern_len-1);
    
    for (int i = 0; i <= text_len-pattern_len; ++i)
    {
        if (p == t)
            return text+i;

        if (i < text_len-pattern_len)
            t = (t - text[i] * high) * base_number + text[i+pattern_len];
    }
    return NULL;
}
const char *string_rabin_karp_match(const char *text, const char *pattern, int base_number, int prime_number)
{
    if (text == NULL || pattern == NULL)
        return NULL;

    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    
    int p = 0, t = 0;
    for (int i = 0; i < pattern_len; ++i)
    {
        p = (p * base_number + pattern[i]) % prime_number;
        t = (t * base_number + text[i]) % prime_number;
    }

    int high = 1;
    for (int i = 1; i <= pattern_len-1; ++i)
        high = high * base_number % prime_number;
    
    for (int i = 0; i <= text_len-pattern_len; ++i)
    {
        if (p == t)
        {
            int j;
            for (j = 0; j < pattern_len; ++j)
            {
                if (pattern[j] != text[i+j])
                    break;
            }
            if (j == pattern_len)
                return text+i;
        }

        if (i < text_len-pattern_len)
            t = ((t - text[i] * high) * base_number + text[i+pattern_len]) % prime_number;
        if (t < 0)
            t += prime_number;
    }
    return NULL;
}


// 字符串匹配-Sunday算法。
// 假设所有的字符都是ASCII字符。
// Parameter:
// text: 文本串
// pattern: 模式串
// Return value:
// 模式串在文本串第一次出现的位置的指针，或是NULL
const char *string_sunday_match(const char *text, const char *pattern)
{
    if (text == NULL || pattern == NULL)
        return NULL;

    int text_len = strlen(text);
    int pattern_len = strlen(pattern);

    // next[i]记录字符i到模式串末尾pattern[pattern_len]的距离。
    // 若字符i在模式串中重复出现，只记录最右边的字符。
    // 若i在模式串中没有出现，next[i] = pattern_len+1
    int next[256];
    for (int i = 0; i != 256; ++i)
        next[i] = pattern_len + 1;
    for (int i = 0; i != pattern_len; ++i)
        next[(int)(unsigned char)(pattern[i])] = pattern_len - i;

    int index = 0;
    int i, j;
    while (index <= text_len-pattern_len)
    {
        for (i = index, j = 0; j < pattern_len; ++i, ++j)
        {
            if (text[i] != pattern[j])
                break;
        }
        if (j == pattern_len)
            return text+index;
        index += next[(int)(unsigned char)(text[index+pattern_len])];
    }
    return NULL;
}


}
