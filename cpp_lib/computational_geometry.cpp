// computational_geometry.cpp
//////////////////////////////////////////////////////////////////////

#include "computational_geometry.h"
#include <algorithm>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <boost/multi_array.hpp>
#include "geometry.h"
//////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;

namespace zhaiwei
{

// 输出双调旅行路径
static void print_bitonic_tour_path(const boost::multi_array<int, 2> &path, int point_size)
{
    std::stack<int> l_r_path;
    std::queue<int> r_l_path;

    int i = point_size, j = point_size;
    l_r_path.push(point_size);
    while (true)
    {
        if (i == 0 && j == 0)
            break;
        if (i > j)
        {
            l_r_path.push(path[j][i]);
            i = path[j][i];
        }
        else
        {
            r_l_path.push(path[i][j]);
            j = path[i][j];
        }
    }

    while (!l_r_path.empty())
    {
        fprintf(stdout, "%d ", l_r_path.top());
        l_r_path.pop();
    }
    while (!r_l_path.empty())
    {
        fprintf(stdout, "%d ", r_l_path.front());
        r_l_path.pop();
    }
    fprintf(stdout, "\n");
}
// 双调欧几里德旅行商问题
double bitonic_tour_problem(point *point_array, int len)
{
    // dist[i][j]记录两点Pi到Pj的距离
    // min_path_len[i][j]记录从Pi到P1再到Pj的最短路径的长度
    // i <= j
    boost::multi_array<double, 2> dist(boost::extents[len][len]),
        min_path_len(boost::extents[len][len]);

    // path[i][j]记录点Pj的前驱点
    boost::multi_array<int, 2> path(boost::extents[len][len]);

    min_path_len[0][0] = 0;
    path[0][0] = 0;

    for (int j = 1; j <= len-1; ++j)
    {
        dist[j-1][j] = distance(point_array[j-1], point_array[j]);
        for (int i = 0; i <= j-2; ++i)
        {
            min_path_len[i][j] = min_path_len[i][j-1] + dist[j-1][j];
            path[i][j] = j - 1;
        }
        for (int i = j-1; i <= j; ++i)
        {
            int k = 0;
            dist[k][j] = distance(point_array[k], point_array[j]);
            double tmp_len = min_path_len[k][i] + dist[k][j];
            min_path_len[i][j] = tmp_len;
            path[i][j] = k;
            for (k = 1; k <= i-1; ++k)
            {
                dist[k][j] = distance(point_array[k], point_array[j]);
                tmp_len = min_path_len[k][i] + dist[k][j];
                if (tmp_len < min_path_len[i][j])
                {
                    min_path_len[i][j] = tmp_len;
                    path[i][j] = k;
                }
            }
        }
    }
    // 输出最短路径长度
    for (int i = 0; i <= len-1; ++i)
    {
        for (int j = 0; j <= len-1; ++j)
            fprintf(stdout, "%.2f ", min_path_len[i][j]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    // 输出两点间距离
    for (int i = 0; i <= len-1; ++i)
    {
        for (int j = 0; j <= len-1; ++j)
            fprintf(stdout, "%.2f ", dist[i][j]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    // 输出路径
    for (int i = 0; i <= len-1; ++i)
    {
        for (int j = 0; j <= len-1; ++j)
            fprintf(stdout, "%d ", path[i][j]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");

    print_bitonic_tour_path(path, len-1);
    return min_path_len[len-1][len-1];
}


// 计算两点间的距离
double distance(const point &lhs, const point &rhs)
{
    return std::sqrt((lhs.X-rhs.X)*(lhs.X-rhs.X) + (lhs.Y-rhs.Y)*(lhs.Y-rhs.Y));
}


// 求最大重叠区间大小
double max_overlap_interval(both_closed_interval *array, int len, int &idx1, int &idx2)
{
    if (array == NULL || len < 1)
        return 0;

    // 区间索引集合
    list<int> interval_index_coll;
    for (int i = 0; i < len; ++i)
    {
        if (array[i].m_begin > array[i].m_end)
            swap(array[i].m_begin, array[i].m_end);
        interval_index_coll.push_back(i);
    }
    interval_less_function interval_less(array, len);
    interval_index_coll.sort(interval_less);
    double max_overlap_len = 0;
    list<int>::iterator curr = interval_index_coll.begin(), next;
    // 删除被包含的区间
    while (curr != interval_index_coll.end())
    {
        next = curr;
        ++next;
        if (next == interval_index_coll.end())
            break;
        if (array[*curr].m_begin == array[*next].m_begin) // next包含curr
        {
            if (array[*curr].get_length() > max_overlap_len)
            {
                max_overlap_len = array[*curr].get_length();
                idx1 = *curr;
                idx2 = *next;
            }
            interval_index_coll.erase(curr);
        }
        else if (array[*curr].m_end >= array[*next].m_end) // curr包含next
        {
            if (array[*next].get_length() > max_overlap_len)
            {
                max_overlap_len = array[*next].get_length();
                idx1 = *curr;
                idx2 = *next;
            }
            interval_index_coll.erase(next);
            next = curr;
        }
        curr = next;
    }
    // 只考虑相邻区间
    curr = interval_index_coll.begin();
    double tmp_len;
    while (curr != interval_index_coll.end())
    {
        next = curr;
        ++next;
        if (next == interval_index_coll.end())
            break;
        if (array[*curr].m_end >= array[*next].m_begin &&
            (tmp_len = array[*curr].m_end-array[*next].m_begin+1) > max_overlap_len)
        {
            max_overlap_len = tmp_len;
            idx1 = *curr;
            idx2 = *next;
        }
        curr = next;
    }
    return max_overlap_len;
}


// 暴力穷举法计算最近点对的距离
double min_distance_of_points_brute_force(point *point_array, int size, int &p1, int &p2)
{
    if (point_array == NULL || size <= 1)
        return -1;
    double min_dist = distance(point_array[0], point_array[1]);
    p1 = 0;
    p2 = 1;
    double tmp_dist;
    for (int i = 0; i <= size-2; ++i)
    {
        for (int j = i+1; j <= size-1; ++j)
        {
            tmp_dist = distance(point_array[i], point_array[j]);
            if (tmp_dist < min_dist)
            {
                min_dist = tmp_dist;
                p1 = i;
                p2 = j;
            }
        }
    }
    return min_dist;
}
// 分治法计算最近点对的距离
// point_array, size: 点数组和点的数目
// [x_first, x_last): 按x坐标排序的点数组索引的范围
// y_ordered_index: 与上述索引范围对应的按y坐标排序的点数组索引
// point1, point2: 距离最近的两个点在数组中的索引
static double min_distance_of_points_divide_and_conquer(point *point_array, int size,
                                                        std::vector<int>::iterator x_first,
                                                        std::vector<int>::iterator x_last,
                                                        std::vector<int> &y_ordered_index,
                                                        int &point1, int &point2)
{
    // 如果只有一个点或两个点
    if (x_first+1 == x_last)
        return DBL_MAX;
    if (x_first+2 == x_last)
    {
        point1 = 0;
        point2 = 1;
        return distance(point_array[*x_first], point_array[*(x_first+1)]);
    }

    // 递归计算左半部分和右半部分的最近距离
    std::vector<int>::iterator x_mid = x_first + (x_last - x_first) / 2;
    std::vector<int> y_left, y_right;
    for (std::vector<int>::iterator iter = y_ordered_index.begin(); iter != y_ordered_index.end(); ++iter)
    {
        if (point_array[*iter].X <= point_array[*x_mid].X)
            y_left.push_back(*iter);
        else
            y_right.push_back(*iter);
    }
    int left_p1, left_p2, right_p1, right_p2;
    double left_min_dist = min_distance_of_points_divide_and_conquer(point_array, size, x_first, x_mid, y_left,
                                                                     left_p1, left_p2);
    double right_min_dist = min_distance_of_points_divide_and_conquer(point_array, size, x_mid, x_last, y_right,
                                                                      right_p1, right_p2);
    double min_dist;
    if (left_min_dist < right_min_dist)
    {
        point1 = left_p1;
        point2 = left_p2;
        min_dist = left_min_dist;
    }
    else
    {
        point1 = right_p1;
        point2 = right_p2;
        min_dist = right_min_dist;
    }

    // 计算跨左右两部分的最近点对的距离
    std::vector<int> y_ordered_index_in_strip;
    for (std::vector<int>::iterator iter = y_ordered_index.begin();
         iter != y_ordered_index.end(); ++iter)
    {
        if (point_array[*iter].X >= point_array[*x_mid].X-min_dist ||
            point_array[*iter].X <= point_array[*x_mid].X+min_dist)
            y_ordered_index_in_strip.push_back(*iter);
    }
    for (std::vector<int>::iterator iter1 = y_ordered_index_in_strip.begin();
         iter1 != y_ordered_index_in_strip.end(); ++iter1)
    {
        for (std::vector<int>::iterator iter2 = iter1+1; iter2 != y_ordered_index_in_strip.end(); ++iter2)
        {
            if (point_array[*iter2].Y - point_array[*iter1].Y > min_dist)
                break;
            else
            {
                double tmp_dist = distance(point_array[*iter2], point_array[*iter1]);
                if (tmp_dist < min_dist)
                {
                    point1 = *iter1;
                    point2 = *iter2;
                    min_dist = tmp_dist;
                }
            }
        }
    }
    return min_dist;
}
// 分治法计算平面上最近点对的距离
// point_array, size: 点数组和点的数目
// point1, point2: 距离最近的两个点在数组中的索引
double min_distance_of_points_divide_and_conquer(point *point_array, int size, int &point1, int &point2)
{
    if (point_array == NULL || size <= 1)
        return -1;

    // 将所有点分别按照x坐标和y坐标排序
    // x_ordered_index与y_ordered_index分别存储按照x坐标和y坐标排序的数组索引
    std::vector<int> x_ordered_index(size, 0), y_ordered_index(size, 0);
    for (int i = 0; i != size; ++i)
    {
        x_ordered_index[i] = i;
        y_ordered_index[i] = i;
    }
    x_less x_less_instance(point_array, size);
    y_less y_less_instance(point_array, size);
    std::sort(x_ordered_index.begin(), x_ordered_index.end(), x_less_instance);
    std::sort(y_ordered_index.begin(), y_ordered_index.end(), y_less_instance);

    return min_distance_of_points_divide_and_conquer(point_array, size, x_ordered_index.begin(),
                                                     x_ordered_index.end(), y_ordered_index, point1, point2);
}


// 12个工厂分布在一条东西向高速公路的两侧，工厂距离公路最西端的距离分别是0、4、5、10、12、18、27、30、 31、38、39、47.
// 在这12个工厂中选取3个原料供应厂，使得剩余工厂到最近的原料供应厂距离之和最短，问应该选哪三个厂？
// 参考：http://blog.csdn.net/julianxiong/article/details/7381214
// 参数：
// array: 工厂距离数组，array[1...n]为有效值，array[0]置0
// length: 有效元素数目
// 求从第begin个工厂到第end个工厂设1个原料厂的最短距离
// 1<=begin<=end<=n
static int min_distance(int *array, int begin, int end)
{
    int mid = begin + (end - begin) / 2;
    int distance = 0;
    for (int i = begin; i <= end; ++i)
    {
        distance += abs(array[i]-array[mid]);
    }
    return distance;
}
// 输出从前i个工厂选择的j个原料厂
static void print_selected_factory(const multi_array<int, 2> &opt, int length, int i, int j)
{
    if (i <= j)
    {
        for (int k = 1; k <= i; ++k)
        {
            cout << k << " ";
        }
        return;
    }

    int k = opt[i][j];
    print_selected_factory(opt, length, k, j-1);
    cout << k+1 + (i-k-1)/2 << " ";
}
int min_sum_of_distance(int *array, int length, int number)
{
    if (array == NULL || length < 1)
        return 0;

    // min_distance_1[i][j]表示从第i个工厂到第j个工厂设1个原料厂的最短距离
    multi_array<int, 2> min_distance_1(extents[length+1][length+1]);
    for (int i = 0; i <= length; ++i)
        min_distance_1[i][0] = 0;
    for (int j = 1; j <= length; ++j)
        min_distance_1[0][j] = 0;
    for (int i = 1; i <= length; ++i)
        for (int j = i; j <= length; ++j)
            min_distance_1[i][j] = min_distance(array, i, j);

    // min_distance_m[i][j]表示从前i个工厂中设j个原料厂的最短距离之和
    multi_array<int, 2> min_distance_m(extents[length+1][length+1]);
    multi_array<int, 2> opt(extents[length+1][length+1]);
    for (int i = 0; i <= length; ++i)
        min_distance_m[i][0] = 0;
    for (int j = 1; j <= length; ++j)
        min_distance_m[0][j] = 0;
    for (int i = 1; i <= length; ++i)
    {
        int j = 1;
        min_distance_m[i][j] = min_distance_1[1][i];
        for (j = 2; j <= i; ++j)
        {
            min_distance_m[i][j] = INT_MAX;
            for (int k = max(1, j-1); k < i; ++k)
            {
                int tmp = min_distance_m[k][j-1] + min_distance_1[k+1][i];
                if (tmp < min_distance_m[i][j])
                {
                    min_distance_m[i][j] = tmp;
                    opt[i][j] = k;
                }
            }
        }
    }
            
    cout << "min distance: " << min_distance_m[length][number] << endl;
    print_selected_factory(opt, length, length, number);
    cout << endl;
    return min_distance_m[length][number];
}


// 微软面试题
// 平面上N个点，每两个点都确定一条直线，
// 求出斜率最大的那条直线所通过的两个点（斜率不存在的情况不考虑）。时间效率越高越好。
// 对所有点按横坐标x排序，若x相等，继续比较y。合并x相等的点，只记录y的最小值和最大值。
// 对每对相邻点x[i]和x[i+1]，使用x[i]的最小y值和x[i+1]的最大y值计算斜率，最大的斜率
// 即为要查找的那条直线。
double find_max_slope_line(point *array, int size, int &p1_idx, int &p2_idx)
{
	std::sort(array, array+size);

	double slop_max = INT_MIN;
	double slop_tmp;
	// curr_y_min和curr_y_max是有相同x坐标且有最小y坐标和最大y坐标的点的索引
	// next_y_min和next_y_max是下一个有相同x坐标且有最小y坐标和最大y坐标的点的索引
	int curr_y_min, curr_y_max, next_y_min, next_y_max;
	curr_y_max = curr_y_min = 0;
	while (curr_y_min < size)
	{
		while (curr_y_max+1 < size && array[curr_y_max+1].X == array[curr_y_max].X)
			++curr_y_max;
		if (curr_y_max+1 == size)
			break;
		next_y_max = next_y_min = curr_y_max + 1;
		while (next_y_max+1 < size && array[next_y_max+1].X == array[next_y_max].X)
			++next_y_max;
		slop_tmp = (array[next_y_max].Y-array[curr_y_min].Y) / (array[next_y_max].X-array[curr_y_min].X);
		if (slop_tmp > slop_max)
		{
			slop_max = slop_tmp;
			p1_idx = curr_y_min;
			p2_idx = next_y_max;
		}
		curr_y_min = next_y_min;
		curr_y_max = next_y_max;
	}
	return slop_max;
}


// 题目：输入四个点的坐标，求证四个点是不是一个矩形。若是，将四个点排成矩形的四个顶点left-top-right-bottom的顺序
// 解法：如果矩形的边跟坐标系不平行，查找x坐标最小的点作为left点，y坐标最大的点作为top点，x坐标最大的点作为right点，
// y坐标最小的点作为bottom点; 如果矩形的边跟坐标系平行，left点是x坐标最小且y坐标较小的点，top点是y坐标最大且x坐标
// 较小的点，right点是x坐标最大且y坐标较大的点，bottom点是y坐标最小且x坐标较大的点。
// 找到四个点后，利用向量的数量积是否为0判断矩形。
static int find_left_point(point *array, int len)
{
    int left_idx = 0;
    for (int i = 1; i < len; ++i)
    {
        if (array[i].X < array[left_idx].X)
            left_idx = i;
        else if (array[i].X == array[left_idx].X && array[i].Y < array[left_idx].Y)
            left_idx = i;
    }
    return left_idx;
}
static int find_top_point(point *array, int len)
{
    int top_idx = 0;
    for (int i = 1; i < len; ++i)
    {
        if (array[i].Y > array[top_idx].Y)
            top_idx = i;
        else if (array[i].Y == array[top_idx].Y && array[i].X < array[top_idx].Y)
            top_idx = i;
    }
    return top_idx;
}
static int find_right_point(point *array, int len)
{
    int right_idx = 0;
    for (int i = 1; i < len; ++i)
    {
        if (array[i].X > array[right_idx].X)
            right_idx = i;
        else if (array[i].X == array[right_idx].X && array[i].Y > array[right_idx].Y)
            right_idx = i;
    }
    return right_idx;
}
static int find_bottom_point(point *array, int len)
{
    int bottom_idx = 0;
    for (int i = 1; i < len; ++i)
    {
        if (array[i].Y < array[bottom_idx].Y)
            bottom_idx = i;
        else if (array[i].Y == array[bottom_idx].Y && array[i].X > array[bottom_idx].X)
            bottom_idx = i;
    }
    return bottom_idx;
}
bool is_rectangle(point *array, int len)
{
    if (array == NULL || len != 4)
        return false;
    
    int left_idx = find_left_point(array, len);
    int top_idx = find_top_point(array, len);
    if (top_idx == left_idx)
        return false;
    
    int right_idx = find_right_point(array, len);
    if (right_idx == left_idx || right_idx == top_idx)
        return false;
    
    int bottom_idx = find_bottom_point(array, len);
    if (bottom_idx == left_idx || bottom_idx == top_idx || bottom_idx == right_idx)
        return false;

    two_dimension_vector l_t(array[left_idx], array[top_idx]), t_r(array[top_idx], array[right_idx]), 
        r_b(array[right_idx], array[bottom_idx]), b_l(array[bottom_idx], array[left_idx]);

    bool flag = scalar_product(l_t, t_r) == 0 && scalar_product(t_r, r_b) == 0 &&
        scalar_product(r_b, b_l) == 0;
    if (flag == true)
    {
        point left_point = array[left_idx];
        point top_point = array[top_idx];
        point right_point = array[right_idx];
        point bottom_point = array[bottom_idx];
        array[0] = left_point;
        array[1] = top_point;
        array[2] = right_point;
        array[3] = bottom_point;
    }
    return flag;
}


// 判断点是否在三角形内
// http://blog.csdn.net/dracularking/article/details/2217180
bool point_is_in_the_triangle(point *array, int length, const point &p)
{
    if (array == NULL || length != 3)
        return false;

    // 构造向量
    two_dimension_vector pa(p, array[0]), pb(p, array[1]), pc(p, array[2]);

    // 计算矢量积
    double pa_pb = vector_product(pa, pb);
    double pb_pc = vector_product(pb, pc);
    double pc_pa = vector_product(pc, pa);

    // 若矢量积同向，点在三角形内，否则，点在三角形外
    if ( (pa_pb > 0 && pb_pc > 0 && pc_pa > 0) ||
         (pa_pb < 0 && pb_pc < 0 && pc_pa < 0) )
        return true;
    else
        return false;
}


// 判断点是否在三角形边上
bool point_is_on_the_border_of_triangle(point *array, int length, const point &p)
{
    if (array == NULL || length != 3)
        return false;

    // 构造向量
    two_dimension_vector pa(p, array[0]), pb(p, array[1]), pc(p, array[2]);

    // 计算矢量积。
    // 若任一矢量积为0, 点在三角形边上
    double pa_pb = vector_product(pa, pb);
    if (pa_pb == 0)
        return true;
    double pb_pc = vector_product(pb, pc);
    if (pb_pc == 0)
        return true;
    double pc_pa = vector_product(pc, pa);
    if (pc_pa == 0)
        return true;

    return false;
}


// 二维向量类的标量积
double scalar_product(const two_dimension_vector &lhs, const two_dimension_vector &rhs)
{
    return lhs.get_x() * rhs.get_x() + lhs.get_y() * rhs.get_y();
}

// 二维向量的矢量积
// 设i，j，k是符合右手定则的空间坐标系中沿x轴，y轴，z轴正方向的单位向量。两个二维向量在xy平面上，
// 若它们的矢量积沿正z轴方向，返回正值，否则返回负值
double vector_product(const two_dimension_vector &lhs, const two_dimension_vector &rhs)
{
    return lhs.get_x() * rhs.get_y() - lhs.get_y() * rhs.get_x();
}

}
