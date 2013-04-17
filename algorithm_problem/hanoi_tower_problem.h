#ifndef HANOI_TOWER_PROBLEM_H
#define HANOI_TOWER_PROBLEM_H

#include <cstdio>

namespace zhaiwei
{
// 汉诺塔问题
// 把n个盘子从柱子a移动到柱子b
// n: 盘子个数
// a, b, c: 3根柱子
void hanoi_tower(int n, char a, char b, char c)
{
    if (n == 1)
    {
        fprintf(stdout, "move disk from %c to %c\n", a, b);
        return;
    }

    hanoi_tower(n-1, a, c, b);
    hanoi_tower(1, a, b, c);
    hanoi_tower(n-1, c, b, a);
}

}




#endif // HANOI_TOWER_PROBLEM_H
