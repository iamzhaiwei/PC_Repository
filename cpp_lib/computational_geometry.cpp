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

// ���˫������·��
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
// ˫��ŷ���������������
double bitonic_tour_problem(point *point_array, int len)
{
    // dist[i][j]��¼����Pi��Pj�ľ���
    // min_path_len[i][j]��¼��Pi��P1�ٵ�Pj�����·���ĳ���
    // i <= j
    boost::multi_array<double, 2> dist(boost::extents[len][len]),
        min_path_len(boost::extents[len][len]);

    // path[i][j]��¼��Pj��ǰ����
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
    // ������·������
    for (int i = 0; i <= len-1; ++i)
    {
        for (int j = 0; j <= len-1; ++j)
            fprintf(stdout, "%.2f ", min_path_len[i][j]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    // �����������
    for (int i = 0; i <= len-1; ++i)
    {
        for (int j = 0; j <= len-1; ++j)
            fprintf(stdout, "%.2f ", dist[i][j]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    // ���·��
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


// ���������ľ���
double distance(const point &lhs, const point &rhs)
{
    return std::sqrt((lhs.X-rhs.X)*(lhs.X-rhs.X) + (lhs.Y-rhs.Y)*(lhs.Y-rhs.Y));
}


// ������ص������С
double max_overlap_interval(both_closed_interval *array, int len, int &idx1, int &idx2)
{
    if (array == NULL || len < 1)
        return 0;

    // ������������
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
    // ɾ��������������
    while (curr != interval_index_coll.end())
    {
        next = curr;
        ++next;
        if (next == interval_index_coll.end())
            break;
        if (array[*curr].m_begin == array[*next].m_begin) // next����curr
        {
            if (array[*curr].get_length() > max_overlap_len)
            {
                max_overlap_len = array[*curr].get_length();
                idx1 = *curr;
                idx2 = *next;
            }
            interval_index_coll.erase(curr);
        }
        else if (array[*curr].m_end >= array[*next].m_end) // curr����next
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
    // ֻ������������
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


// ������ٷ����������Եľ���
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
// ���η����������Եľ���
// point_array, size: ������͵����Ŀ
// [x_first, x_last): ��x��������ĵ����������ķ�Χ
// y_ordered_index: ������������Χ��Ӧ�İ�y��������ĵ���������
// point1, point2: ����������������������е�����
static double min_distance_of_points_divide_and_conquer(point *point_array, int size,
                                                        std::vector<int>::iterator x_first,
                                                        std::vector<int>::iterator x_last,
                                                        std::vector<int> &y_ordered_index,
                                                        int &point1, int &point2)
{
    // ���ֻ��һ�����������
    if (x_first+1 == x_last)
        return DBL_MAX;
    if (x_first+2 == x_last)
    {
        point1 = 0;
        point2 = 1;
        return distance(point_array[*x_first], point_array[*(x_first+1)]);
    }

    // �ݹ������벿�ֺ��Ұ벿�ֵ��������
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

    // ��������������ֵ������Եľ���
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
// ���η�����ƽ���������Եľ���
// point_array, size: ������͵����Ŀ
// point1, point2: ����������������������е�����
double min_distance_of_points_divide_and_conquer(point *point_array, int size, int &point1, int &point2)
{
    if (point_array == NULL || size <= 1)
        return -1;

    // �����е�ֱ���x�����y��������
    // x_ordered_index��y_ordered_index�ֱ�洢����x�����y�����������������
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


// 12�������ֲ���һ����������ٹ�·�����࣬�������빫·�����˵ľ���ֱ���0��4��5��10��12��18��27��30�� 31��38��39��47.
// ����12��������ѡȡ3��ԭ�Ϲ�Ӧ����ʹ��ʣ�๤���������ԭ�Ϲ�Ӧ������֮����̣���Ӧ��ѡ����������
// �ο���http://blog.csdn.net/julianxiong/article/details/7381214
// ������
// array: �����������飬array[1...n]Ϊ��Чֵ��array[0]��0
// length: ��ЧԪ����Ŀ
// ��ӵ�begin����������end��������1��ԭ�ϳ�����̾���
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
// �����ǰi������ѡ���j��ԭ�ϳ�
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

    // min_distance_1[i][j]��ʾ�ӵ�i����������j��������1��ԭ�ϳ�����̾���
    multi_array<int, 2> min_distance_1(extents[length+1][length+1]);
    for (int i = 0; i <= length; ++i)
        min_distance_1[i][0] = 0;
    for (int j = 1; j <= length; ++j)
        min_distance_1[0][j] = 0;
    for (int i = 1; i <= length; ++i)
        for (int j = i; j <= length; ++j)
            min_distance_1[i][j] = min_distance(array, i, j);

    // min_distance_m[i][j]��ʾ��ǰi����������j��ԭ�ϳ�����̾���֮��
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


// ΢��������
// ƽ����N���㣬ÿ�����㶼ȷ��һ��ֱ�ߣ�
// ���б����������ֱ����ͨ���������㣨б�ʲ����ڵ���������ǣ���ʱ��Ч��Խ��Խ�á�
// �����е㰴������x������x��ȣ������Ƚ�y���ϲ�x��ȵĵ㣬ֻ��¼y����Сֵ�����ֵ��
// ��ÿ�����ڵ�x[i]��x[i+1]��ʹ��x[i]����Сyֵ��x[i+1]�����yֵ����б�ʣ�����б��
// ��ΪҪ���ҵ�����ֱ�ߡ�
double find_max_slope_line(point *array, int size, int &p1_idx, int &p2_idx)
{
	std::sort(array, array+size);

	double slop_max = INT_MIN;
	double slop_tmp;
	// curr_y_min��curr_y_max������ͬx����������Сy��������y����ĵ������
	// next_y_min��next_y_max����һ������ͬx����������Сy��������y����ĵ������
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


// ��Ŀ�������ĸ�������꣬��֤�ĸ����ǲ���һ�����Ρ����ǣ����ĸ����ųɾ��ε��ĸ�����left-top-right-bottom��˳��
// �ⷨ��������εı߸�����ϵ��ƽ�У�����x������С�ĵ���Ϊleft�㣬y�������ĵ���Ϊtop�㣬x�������ĵ���Ϊright�㣬
// y������С�ĵ���Ϊbottom��; ������εı߸�����ϵƽ�У�left����x������С��y�����С�ĵ㣬top����y���������x����
// ��С�ĵ㣬right����x���������y����ϴ�ĵ㣬bottom����y������С��x����ϴ�ĵ㡣
// �ҵ��ĸ���������������������Ƿ�Ϊ0�жϾ��Ρ�
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


// �жϵ��Ƿ�����������
// http://blog.csdn.net/dracularking/article/details/2217180
bool point_is_in_the_triangle(point *array, int length, const point &p)
{
    if (array == NULL || length != 3)
        return false;

    // ��������
    two_dimension_vector pa(p, array[0]), pb(p, array[1]), pc(p, array[2]);

    // ����ʸ����
    double pa_pb = vector_product(pa, pb);
    double pb_pc = vector_product(pb, pc);
    double pc_pa = vector_product(pc, pa);

    // ��ʸ����ͬ�򣬵����������ڣ����򣬵�����������
    if ( (pa_pb > 0 && pb_pc > 0 && pc_pa > 0) ||
         (pa_pb < 0 && pb_pc < 0 && pc_pa < 0) )
        return true;
    else
        return false;
}


// �жϵ��Ƿ��������α���
bool point_is_on_the_border_of_triangle(point *array, int length, const point &p)
{
    if (array == NULL || length != 3)
        return false;

    // ��������
    two_dimension_vector pa(p, array[0]), pb(p, array[1]), pc(p, array[2]);

    // ����ʸ������
    // ����һʸ����Ϊ0, ���������α���
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


// ��ά������ı�����
double scalar_product(const two_dimension_vector &lhs, const two_dimension_vector &rhs)
{
    return lhs.get_x() * rhs.get_x() + lhs.get_y() * rhs.get_y();
}

// ��ά������ʸ����
// ��i��j��k�Ƿ������ֶ���Ŀռ�����ϵ����x�ᣬy�ᣬz��������ĵ�λ������������ά������xyƽ���ϣ�
// �����ǵ�ʸ��������z�᷽�򣬷�����ֵ�����򷵻ظ�ֵ
double vector_product(const two_dimension_vector &lhs, const two_dimension_vector &rhs)
{
    return lhs.get_x() * rhs.get_y() - lhs.get_y() * rhs.get_x();
}

}
