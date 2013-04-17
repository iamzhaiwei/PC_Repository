// main.cpp
//////////////////////////////////////////////////////////////////////
// 问题描述：
// 给定任务序列J1J2 ...Jn，假定只有一台处理机为这批作业服务。每件任务Ji给定一个时限di和对应利润Pi。
// 只有在规定时限之内完成作业，才会得到利润Pi。通过设计合适的算法选择和安排任务子集Ji，使得J中的
// 每个作业都能在各自的时限内完工，且使获得的利润∑Pi总和最大。
// 令d=max{di} 1≤i≤n，b=min{n,d}
// 任何最大利润的可完工子序列中的作业个数必不大于b。
//////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <algorithm>

using namespace std;

// 最大作业数目
const int N = 100005;
// 每个作业的时限和利润
int d[N], p[N];
// 每个作业按照利润排序的等级
int rank[N];
// 
int f[N];

bool cmp(int i, int j)
{
    return p[i] > p[j];
}

int find(int x)
{
    return f[x]==x ? f[x]: f[x]=find(f[x]);
}

int main(int argc, char **argv)
{
    // 作业数目
    int n;
    // 最大时限
    int maxd;
    // 利润和
    long long sum;
    
    int father;
    
    while (fscanf(stdin, "%d", &n) != EOF)
    {
        sum = 0;
        maxd = 0;
        for (int i = 0; i != n; ++i)
        {
            fscanf(stdin, "%d%d", p+i, d+i);
            rank[i] = i;
            if (d[i] > maxd)
                maxd = d[i];
        }
        sort(rank, rank+n, cmp);
        
        for (int i = 0; i <= maxd; ++i)
            f[i] = i;

        for (int i = 0; i != n; ++i)
        {
            father = find(d[rank[i]]);
            if (father != 0)
            {
                f[father] = father - 1;
                sum += p[rank[i]];
                for (int i = 0; i <= maxd; ++i)
                {
                    fprintf(stdout, "%d ", f[i]);
                }
                fprintf(stdout, "\n");
            }
        }
        for (int i = 0; i <= maxd; ++i)
        {
            fprintf(stdout, "%d ", f[i]);
        }
        fprintf(stdout, "\n");
        fprintf(stdout, "%lld\n", sum);
    }
    return 0;
}
