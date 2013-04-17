// computational_geometry.h
//
// last-edit-by: <>
//
// Description:
// 计算几何问题
//
//////////////////////////////////////////////////////////////////////

#ifndef COMPUTATIONAL_GEOMETRY_H
#define COMPUTATIONAL_GEOMETRY_H 1

namespace zhaiwei
{

class point;
class two_dimension_vector;
class both_closed_interval;


// 双调欧几里德旅行商问题
double bitonic_tour_problem(point *point_array, int len);


// 计算两点间的距离
double distance(const point &lhs, const point &rhs);


// 求最大重叠区间大小。若有区间重叠，返回最大重叠区间大小，并设置相应的重叠区间索引。
double max_overlap_interval(both_closed_interval *array, int len, int &idx1, int &idx2);


// 暴力穷举法计算最近点对的距离
double min_distance_of_points_brute_force(point *point_array, int size, int &p1, int &p2);
// 分治法计算平面上最近点对的距离
// point_array, size: 点数组和点的数目
// point1, point2: 距离最近的两个点在数组中的索引
double min_distance_of_points_divide_and_conquer(point *point_array, int size, int &point1, int &point2);


// 12个工厂分布在一条东西向高速公路的两侧，工厂距离公路最西端的距离分别是0、4、5、10、12、18、27、30、 31、38、39、47.
// 在这12个工厂中选取3个原料供应厂，使得剩余工厂到最近的原料供应厂距离之和最短，问应该选哪三个厂？
int min_sum_of_distance(int *array, int length, int number);


// 微软面试题
// 平面上N个点，每两个点都确定一条直线，
// 求出斜率最大的那条直线所通过的两个点（斜率不存在的情况不考虑）。时间效率越高越好。
double find_max_slope_line(point *array, int size, int &p1, int &p2);


// 题目：输入四个点的坐标，求证四个点是不是一个矩形。若是，将四个点排成矩形的四个顶点left-top-right-bottom的顺序
bool is_rectangle(point *array, int len);


// 判断点是否在三角形内
bool point_is_in_the_triangle(point *array, int length, const point &p);


// 判断点是否在三角形边上
bool point_is_on_the_border_of_triangle(point *array, int length, const point &p);


// 二维向量的标量积
double scalar_product(const two_dimension_vector &lhs, const two_dimension_vector &rhs);

// 二维向量的矢量积
// 设i，j，k是符合右手定则的空间坐标系中沿x轴，y轴，z轴正方向的单位向量。两个二维向量在xy平面上，
// 若它们的矢量积沿正z轴方向，返回正值，否则返回负值
double vector_product(const two_dimension_vector &lhs, const two_dimension_vector &rhs);

}


#endif // COMPUTATIONAL_GEOMETRY_H
//////////////////////////////////////////////////////////////////////
