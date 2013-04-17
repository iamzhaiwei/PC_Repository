// the_turnpike_reconstruction_problem.h
//
// last-edit-by: <> 
// 2012-06-17 丁宅伟
// 
// Description:
// 收费公路重建问题
//////////////////////////////////////////////////////////////////////

#ifndef THE_TURNPIKE_RECONSTRUCTION_PROBLEM_H
#define THE_TURNPIKE_RECONSTRUCTION_PROBLEM_H 1

#include <cstdlib>
#include <iterator>
#include <set>
#include <vector>

namespace zhaiwei
{
// 参数说明：
// dist_set: 距离集合，初始时size>=1
// point_set: 点集合
// N: 点的数目，N>=2
// [left,right]: 本次递归调用考虑的点集合下标区间，即区间[left,right]内的点还未确定坐标值
// coordinate: left点或right点的坐标值

// 判断坐标值coordinate是否是可行的
static bool coordinate_is_feasible(std::multiset<int> &dist_set, std::vector<int> &point_set, int N,
                                   int left, int right, int coordinate);
// 删除与坐标值coordinate相关的距离
static void remove_distance_to_coordinate(std::multiset<int> &dist_set, std::vector<int> &point_set, int N,
                                          int left, int right, int coordinate);
// 插入与与坐标值coordinate相关的距离
static void add_distance_to_coordinate(std::multiset<int> &dist_set, std::vector<int> &point_set, int N,
                                       int left, int right, int coordinate);
// 重建坐标点
static bool place(std::multiset<int> &dist_set, std::vector<int> &point_set, int N, int left, int right);

// 重建坐标点，找出距离集合的所有同度点集
// cnt: 同度点集的数目，初始调用时，cnt=0
static void place_find_all_homometric(std::multiset<int> &dist_set, std::vector< std::vector<int> > &point_sets,
                                      int N, int left, int right, int &cnt);
// 问题算法
bool the_turnpike_reconstruction_problem(std::multiset<int> &dist_set, std::vector<int> &point_set, int N)
{
    point_set.resize(N);
    point_set[0] = 0;
    std::multiset<int>::iterator iter = dist_set.end();
    point_set[N-1] = *(--iter);
    dist_set.erase(iter);
    if (!dist_set.empty())
    {
        iter = dist_set.end();
        point_set[N-2] = *(--iter);
        dist_set.erase(iter);
        if ( (iter = dist_set.find(point_set[N-1]-point_set[N-2])) != dist_set.end())
        {
            dist_set.erase(iter);
            return place(dist_set, point_set, N, 1, N-3);
        }
        else
            return false;
    }
    else
        return true;
}

// 找出距离集合的所有同度点集，返回点集数目
int the_turnpike_reconstruction_problem_find_all_homometric(std::multiset<int> &dist_set,
                                                            std::vector< std::vector<int> > &point_sets, int N)
{
    int cnt = 0;
    point_sets.push_back(std::vector<int>(N));
    point_sets[cnt][0] = 0;
    std::multiset<int>::iterator iter = dist_set.end();
    point_sets[cnt][N-1] = *(--iter);
    dist_set.erase(iter);
    if (!dist_set.empty())
    {
        iter = dist_set.end();
        point_sets[cnt][N-2] = *(--iter);
        dist_set.erase(iter);
        if ( (iter = dist_set.find(point_sets[cnt][N-1]-point_sets[cnt][N-2])) != dist_set.end())
        {
            dist_set.erase(iter);
            place_find_all_homometric(dist_set, point_sets, N, 1, N-3, cnt);
        }
    }
    return cnt;
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// 判断坐标值coordinate是否是可行的
static bool coordinate_is_feasible(std::multiset<int> &dist_set, std::vector<int> &point_set, int N,
                                   int left, int right, int coordinate)
{
    // found_dist_set记录已经找到的、与coordinate相关的距离
    // 每找到一个这样的距离，先把这个距离从dist_set中删除，插入到found_dist_set中，函数返回时，再插入回来。
    // 这样做，可以避免以下情况:
    // coordinate与[0,left-1]内一点和[right+1,N-1]内一点有相同的距离值，而这个距离值只在dist_set中出现了一次
    std::multiset<int> found_dist_set;
    std::multiset<int>::iterator iter;
    for (int i = 0; i < left; ++i)
    {
        if ( (iter = dist_set.find(abs(coordinate-point_set[i]))) != dist_set.end())
        {
            found_dist_set.insert(*iter);
            dist_set.erase(iter);
        }
        else
        {
            dist_set.insert(found_dist_set.begin(), found_dist_set.end());
            return false;
        }
    }
    for (int i = right+1; i < N; ++i)
    {
        if ( (iter = dist_set.find(abs(coordinate-point_set[i]))) != dist_set.end())
        {
            found_dist_set.insert(*iter);
            dist_set.erase(iter);
        }
        else
        {
            dist_set.insert(found_dist_set.begin(), found_dist_set.end());
            return false;
        }
    }
    dist_set.insert(found_dist_set.begin(), found_dist_set.end());
    return true;
}
// 删除与坐标值coordinate相关的距离
static void remove_distance_to_coordinate(std::multiset<int> &dist_set, std::vector<int> &point_set, int N,
                                          int left, int right, int coordinate)
{
    std::multiset<int>::iterator iter;
    for (int i = 0; i < left; ++i)
    {
        iter = dist_set.find(abs(coordinate-point_set[i]));
        dist_set.erase(iter);
    }
    for (int i = right+1; i < N; ++i)
    {
        iter = dist_set.find(abs(coordinate-point_set[i]));
        dist_set.erase(iter);
    }
}
// 插入与与坐标值coordinate相关的距离
static void add_distance_to_coordinate(std::multiset<int> &dist_set, std::vector<int> &point_set, int N,
                                          int left, int right, int coordinate)
{
    std::multiset<int>::iterator iter;
    for (int i = 0; i < left; ++i)
    {
        dist_set.insert(abs(coordinate-point_set[i]));
    }
    for (int i = right+1; i < N; ++i)
    {
        dist_set.insert(abs(coordinate-point_set[i]));
    }
}
// 重建坐标点
static bool place(std::multiset<int> &dist_set, std::vector<int> &point_set, int N, int left, int right)
{
    if (dist_set.empty())
        return true;

    bool found = false;
    std::multiset<int>::iterator iter = dist_set.end();
    int max_dist = *(--iter);
    int coordinate;

    // 先放置在left点
    coordinate = point_set[N-1] - max_dist;
    if (coordinate_is_feasible(dist_set, point_set, N, left, right, coordinate))
    {
        point_set[left] = coordinate;
        remove_distance_to_coordinate(dist_set, point_set, N, left, right, coordinate);
        found = place(dist_set, point_set, N, left+1, right);
        if (found)
            return true;
        else
            add_distance_to_coordinate(dist_set, point_set, N, left, right, coordinate);
    }
    // 再放置在right点
    coordinate = max_dist;
    if (coordinate_is_feasible(dist_set, point_set, N, left, right, coordinate))
    {
        point_set[right] = coordinate;
        remove_distance_to_coordinate(dist_set, point_set, N, left, right, coordinate);
        found = place(dist_set, point_set, N, left, right-1);
        if (found)
            return true;
        else
            add_distance_to_coordinate(dist_set, point_set, N, left, right, coordinate);
    }
    return false;
}

static void place_find_all_homometric(std::multiset<int> &dist_set, std::vector< std::vector<int> > &point_sets,
                                      int N, int left, int right, int &cnt)
{
    if (dist_set.empty())
    {
        ++cnt;
        return;
    }
    
    std::multiset<int>::iterator iter = dist_set.end();
    int max_dist = *(--iter);
    int coordinate;
    // 先放置在left点
    coordinate = point_sets[point_sets.size()-1][N-1] - max_dist;
    if (coordinate_is_feasible(dist_set, point_sets[point_sets.size()-1], N, left, right, coordinate))
    {
        point_sets[point_sets.size()-1][left] = coordinate;
        remove_distance_to_coordinate(dist_set, point_sets[point_sets.size()-1], N, left, right, coordinate);
        place_find_all_homometric(dist_set, point_sets, N, left+1, right, cnt);
        add_distance_to_coordinate(dist_set, point_sets[point_sets.size()-1], N, left, right, coordinate);
    }
    // 再放置在right点
    if (cnt == point_sets.size())
        point_sets.push_back(point_sets[point_sets.size()-1]);
    coordinate = max_dist;
    if (coordinate_is_feasible(dist_set, point_sets[point_sets.size()-1], N, left, right, coordinate))
    {
        point_sets[point_sets.size()-1][right] = coordinate;
        remove_distance_to_coordinate(dist_set, point_sets[point_sets.size()-1], N, left, right, coordinate);
        place_find_all_homometric(dist_set, point_sets, N, left, right-1, cnt);
        add_distance_to_coordinate(dist_set, point_sets[point_sets.size()-1], N, left, right, coordinate);
    }
}

}

#endif // THE_TURNPIKE_RECONSTRUCTION_PROBLEM_H
//////////////////////////////////////////////////////////////////////
