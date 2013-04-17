// five_persons_divide_fish.h
//
// last-edit-by: <> 
//
// Description:
// 创新工场面试题：abcde五人打渔，打完睡觉，a先醒来，扔掉1条鱼，把剩下的分成5分，拿一份走了；
// b再醒来，也扔掉1条，把剩下的分成5份，拿一份走了；然后cde都按上面的方法取鱼。问他们一共打了
// 多少条鱼，写程序和算法实现。提示：共打了多少条鱼的结果有很多。但求最少打的鱼的结果是3121条鱼
//////////////////////////////////////////////////////////////////////

#ifndef FIVE_PERSONS_DIVIDE_FISH_H
#define FIVE_PERSONS_DIVIDE_FISH_H 1

#include <iostream>

const int number_persons = 6;

namespace zhaiwei
{

int five_persons_divide_fish()
{
    // number_fish[i]记录第i个人分鱼之前的鱼的数目
    int number_fish[number_persons] = {0};
    number_fish[0] = 1;
    while (true)
    {
        ++number_fish[0];
        int i;
        for (i = 0; i < number_persons; ++i)
        {
            if (number_fish[i] > 1 && number_fish[i] % number_persons == 1)
            {
                if (i+1 < number_persons)
                    number_fish[i+1] = number_fish[i] / number_persons * (number_persons-1);
            }
            else
                break;
        }
        if (i == number_persons)
            break;
    }
    for (int i = 0; i < number_persons; ++i)
        std::cout << number_fish[i] << " ";
    std::cout << std::endl;
    return number_fish[0];
}

}


#endif // FIVE_PERSONS_DIVIDE_FISH_H
//////////////////////////////////////////////////////////////////////
