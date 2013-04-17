// printing_neatly_problem.h
//
// last-edit-by: <> 
//
// Description:
// CLRS 15-2 整齐打印问题
//////////////////////////////////////////////////////////////////////

#ifndef PRINTING_NEATLY_PROBLEM_H
#define PRINTING_NEATLY_PROBLEM_H 1

#include <cmath>
#include <boost/multi_array.hpp>

namespace zhaiwei
{

int printing_neatly_problem(int char_num, int *word_len_array, int word_num)
{
    // remain[i][j]记录将单词Wi到Wj放入一行后该行剩余的空格个数
    // i <= j
    boost::multi_array<int, 2> remain(boost::extents[word_num+1][word_num+1]);
    // opt[i]记录将单词W0到Wi打印出来消耗的“代价”
    std::vector<int> opt(word_num+1, 0);
    // words_len[i]记录单词W0到Wi的长度之和
    std::vector<int> words_len(word_num+1, 0);
    
    for (int i = 1; i <= word_num; ++i)
    {
        words_len[i] = words_len[i-1] + word_len_array[i];
    }

    for (int j = 1; j != word_num; ++j)
    {
        for (int i = 1; i <= j; ++i)
        {
            remain[i][j] = char_num - j + i - (words_len[j]-words_len[i-1]);
        }
    }
    
    for (int i = 1; i <= word_num; ++i)
    {
        int tmp_opt;
        int k = 1;
        if (remain[k][i] < 0)
                break;
        tmp_opt = opt[k-1] + std::pow(remain[k][i], 3);
        opt[i] = tmp_opt;
        for (k = 2; k <= i; ++k)
        {
            if (remain[k][i] < 0)
                break;
            tmp_opt = opt[k-1] + std::pow(remain[k][i], 3);
            if (tmp_opt < opt[i])
            {
                opt[i] = tmp_opt;
            }
        }
    }
    return opt[word_num];
}


}



#endif // PRINTING_NEATLY_PROBLEM_H
//////////////////////////////////////////////////////////////////////
