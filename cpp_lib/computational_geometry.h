// computational_geometry.h
//
// last-edit-by: <>
//
// Description:
// ���㼸������
//
//////////////////////////////////////////////////////////////////////

#ifndef COMPUTATIONAL_GEOMETRY_H
#define COMPUTATIONAL_GEOMETRY_H 1

namespace zhaiwei
{

class point;
class two_dimension_vector;
class both_closed_interval;


// ˫��ŷ���������������
double bitonic_tour_problem(point *point_array, int len);


// ���������ľ���
double distance(const point &lhs, const point &rhs);


// ������ص������С�����������ص�����������ص������С����������Ӧ���ص�����������
double max_overlap_interval(both_closed_interval *array, int len, int &idx1, int &idx2);


// ������ٷ����������Եľ���
double min_distance_of_points_brute_force(point *point_array, int size, int &p1, int &p2);
// ���η�����ƽ���������Եľ���
// point_array, size: ������͵����Ŀ
// point1, point2: ����������������������е�����
double min_distance_of_points_divide_and_conquer(point *point_array, int size, int &point1, int &point2);


// 12�������ֲ���һ����������ٹ�·�����࣬�������빫·�����˵ľ���ֱ���0��4��5��10��12��18��27��30�� 31��38��39��47.
// ����12��������ѡȡ3��ԭ�Ϲ�Ӧ����ʹ��ʣ�๤���������ԭ�Ϲ�Ӧ������֮����̣���Ӧ��ѡ����������
int min_sum_of_distance(int *array, int length, int number);


// ΢��������
// ƽ����N���㣬ÿ�����㶼ȷ��һ��ֱ�ߣ�
// ���б����������ֱ����ͨ���������㣨б�ʲ����ڵ���������ǣ���ʱ��Ч��Խ��Խ�á�
double find_max_slope_line(point *array, int size, int &p1, int &p2);


// ��Ŀ�������ĸ�������꣬��֤�ĸ����ǲ���һ�����Ρ����ǣ����ĸ����ųɾ��ε��ĸ�����left-top-right-bottom��˳��
bool is_rectangle(point *array, int len);


// �жϵ��Ƿ�����������
bool point_is_in_the_triangle(point *array, int length, const point &p);


// �жϵ��Ƿ��������α���
bool point_is_on_the_border_of_triangle(point *array, int length, const point &p);


// ��ά�����ı�����
double scalar_product(const two_dimension_vector &lhs, const two_dimension_vector &rhs);

// ��ά������ʸ����
// ��i��j��k�Ƿ������ֶ���Ŀռ�����ϵ����x�ᣬy�ᣬz��������ĵ�λ������������ά������xyƽ���ϣ�
// �����ǵ�ʸ��������z�᷽�򣬷�����ֵ�����򷵻ظ�ֵ
double vector_product(const two_dimension_vector &lhs, const two_dimension_vector &rhs);

}


#endif // COMPUTATIONAL_GEOMETRY_H
//////////////////////////////////////////////////////////////////////
