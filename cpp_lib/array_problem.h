// array_problem.h
//
// last-edit-by: <>
//
// Description:
// ��������
//////////////////////////////////////////////////////////////////////

#ifndef ARRAY_PROBLEM_H
#define ARRAY_PROBLEM_H 1

#include "boost/multi_array.hpp"
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{

//�ٶȱ��ԣ�����һ��������������飬������������ʹ���������Ϊ�������ұ�Ϊż����
//Ҫ�󣺿ռ临�Ӷ� O(1)��ʱ�临�Ӷ�Ϊ O��n����
void adjust_array_left_odd_right_even(int *array, int n);


// ΢������
// һ���������У�Ԫ��ȡֵ������0~65535�е�����һ��������ͬ��ֵ�����ظ����֡�0�����⣬���Է������֡�
// �����һ���㷨������Ӹ�����������ѡȡ5����ֵ���ж���5����ֵ�Ƿ��������ڡ�
// ע�⣺
// - 5����ֵ����������ġ����磺 8 7 5 0 6
// - 0����ͨ��������ֵ�����磺8 7 5 0 6 �е�0����ͨ���9����4
// - 0���Զ�γ��֡�
// - ���Ӷ������O(n2)�򲻵÷֡�
// ����˼·��
// 1.ȡ5�����з�0�����������С����֮�����4������������������
// 2.Ҫ�������������� 1��ȫ0 ��������2��ֻ��һ����0������
bool array_is_continuous(int array[5]);


//�õݹ�ķ����ж�������a[N]�ǲ�����������
bool array_is_increasing_order_recursion(int *array, int begin, int end);


// �ٶȱ�����
// ����array[begin,mid-1] �� array[mid,end-1]�����ֱ��������С�����merge����������al[0,num-1]��Ҫ��ռ临�Ӷ�O(1)
void array_merge_in_place(int *array, int begin, int mid, int end);


// google������
// ��Ŀ������a1,a2,...,an,b1,b2,...,bn,
// ��O(n)��ʱ��,O(1)�Ŀռ佫�������˳���Ϊa1,b1,a2,b2,a3,b3,...,an,bn��
// �Ҳ���Ҫ�ƶ���ͨ��������ɣ�ֻ��һ�������ռ䡣
void array_rearrange(int *array, int begin, int end);


// ��������
// ������array[0...length)�е�Ԫ����������
void array_reverse(int *array, int length);
// ������ǰ�벿��array[begin,mid)���벿��[mid,end)���򣬵�ǰ�벿�ֺͺ�벿�ֱ�����˳�򲻱�
void array_reverse(int *array, int begin, int mid, int end);


// �ѹ������⣺һ������Ϊn������a[0],a[1],...,a[n-1]�����ڸ������������Ԫ�أ�
// ��a[0]��Ϊa[1]��a[n-1]�Ļ���a[1]��Ϊa[0]��a[2]��a[n-1]�Ļ���...��
// a[n-1]Ϊa[0]��a[n-2]�Ļ������ǳ�����ǰԪ�أ���������Ԫ�صĻ���������Ҫ��
// �������Ը��Ӷȣ��Ҳ���ʹ�ó����������
// һ���������飬���α���
void array_update_to_product(int *array, int length);
// ��չ��2012��4��67�յ���Ѷ����ʵϰ����Ƹ�����У�����һ��������21�����Ƶ��⣬ԭ��������£�
// ��������a[N]��b[N]������A[N]�ĸ���Ԫ��ֵ��֪���ָ�b[i]��ֵ��b[i] = a[0]*a[1]*a[2]...*a[N-1]/a[i]
// Ҫ��1.��׼�ó�������
// 2.����ѭ������ֵ��a[N],b[N]�⣬��׼���������κα����������ֲ�������ȫ�ֱ����ȣ�
// 3.����ʱ�临�Ӷ�O��n�����ռ临�Ӷ�O��1����
void array_multiply_to_product_v1(int *in_array, int *out_array, int length);
void array_multiply_to_product_v2(int *in_array, int *out_array, int length);


// �ڵݼ������ж��ֲ���һ��Ԫ�أ����ҵ�����������������û���ҵ�������-1.
// Parameter:
// array: �����ַ
// begin: �����һ��Ԫ�ص�����
// end: �������һ��Ԫ�ص���������һ������
// item: Ҫ���ҵ�Ԫ��
// Return value:
// ���ҵ�����������������û���ҵ�������-1.
int bisearch_in_decreasing_array(int *array, int begin, int end, int item);


// �ڵ��������ж��ֲ���һ��Ԫ�أ����ҵ�����������������û���ҵ�������-1.
// Parameter:
// array: �����ַ
// begin: �����һ��Ԫ�ص�����
// end: �������һ��Ԫ�ص���������һ������
// item: Ҫ���ҵ�Ԫ��
// Return value:
// ���ҵ�����������������û���ҵ�������-1.
int bisearch_in_increasing_array(int *array, int begin, int end, int item);


//һ����������һ���ݼ�������������λ�γɵģ�����{4��3��2��1��6��5}
//����{6��5��4��3��2��1}������λ�γɵģ������������в���ĳһ������
//���ҵ�����������������û���ҵ�������-1.
// Parameter:
// array: �����ַ
// begin: �����һ��Ԫ�ص�����
// end: �������һ��Ԫ�ص���������һ������
// item: Ҫ���ҵ�Ԫ��
// Return value:
// ���ҵ�����������������û���ҵ�������-1.
int bisearch_in_lshift_decreasing_array(int *array, int begin, int end, int item);


//һ����������һ������������������λ�γɵģ�����{3, 4, 5, 1, 2}����{1, 2, 3, 4, 5}
//������λ�γɵģ������������в���ĳһ������
//���ҵ�����������������û���ҵ�������-1.
// Parameter:
// array: �����ַ
// begin: �����һ��Ԫ�ص�����
// end: �������һ��Ԫ�ص���������һ������
// item: Ҫ���ҵ�Ԫ��
// Return value:
// ���ҵ�����������������û���ҵ�������-1.
int bisearch_in_lshift_increasing_array(int *array, int begin, int end, int item);


// ΢��10.15���ԣ�����һ������{1,2,3}������������{1,2}��{1,3}{2,3}��{1,2,3}��Ԫ��֮����Բ��������ģ�
// ��������{5,9,1,7,2,6,3,8,10,4}�������������ж��ٸ������߻�һ�ֱ��Ϊ������int a[]={5,9,1,7,2,6,3,8,10,4}��
// �������е���������(Ԫ�����λ�ò���)�ĸ��������磺{5��9}��{5��7��8��10}��{1��2��6��8}��
int count_all_increasing_subarray_v1(int *array, int length);
int count_all_increasing_subarray_v2(int *array, int length);


// 2010������������
// �����⣺
// ������������ n �� m��������1��2��3.......n������ȡ������,
// ʹ��͵��� m ,Ҫ���������еĿ�������г�����
int find_additive_factors(int n, int m);


// ������Ϸ�����⣺��һ����������array[n]����һ������m���ж�m�Ƿ�����Щ���������
// ���ĺ͡���������΢������100��2010����4�⣬���൱�ڸ���һ������Ȼ�����һ������
// Ҫ�����Щ ��ӵĺ͵���������� ���нڵ��ӡ��������
int find_additive_factors(int *array, int length, int m);


// ���������е����������в�������������ʹ�����������ĺ͵��ڸ���ֵ
bool find_two_additive_factors(int *array, int n, int sum, int &p1, int &p2);


// �����������в��ҳ��ִ�������һ�����
int find_int_appear_more_than_half(int *array, int n);


//��һ�� int ������������������������ڵ��������������С�ڵ����Ҳ���������
//�����������飬���α���
void find_int_left_less_right_greater_v1(int *array, int n, int *out, int &length);
//һ���������飬���α���
void find_int_left_less_right_greater_v2(int *array, int n, int *out, int &length);


//����������ɵ��������ҵ����ȴ��ڵ���3����ĵȲ�����, ����Ȳ�������С����:
//���û�з��������ľ����[0, 0]
int find_longest_arithmetic_sequence(int *array, int n);


//��һ���������ݼ������У������䳤��
int find_longest_decreasing_subsequence(int *array, int *subsequence, int n);


//��һ�����������������У������䳤��
//һ�㷽��
int find_longest_increasing_subsequence(int *array, int *subsequence, int n);
//��̬�滮����
int find_longest_increasing_subsequence_dp(int *array, int *subsequence, int n);
//���췽��
int find_longest_increasing_subsequence_fast(int *array, int *subsequence, int n);


// ΢�������⣺
// ��һ���������飬���������֮�����ֵ��С��ֵ��
// ��ס��ֻҪ�ó���Сֵ���ɣ�����Ҫ���������������
// �ȶ����������������������Ĳ�ľ���ֵ����Сֵ
int find_min_difference(int *array, int n);


//����n�����������������С��k����ûд�꣩
void find_min_k_ints(int *array_in, int n, int *array_out, int k);


// �����������У��ҳ��������ֵĳ��ִ���
// ���� [1, 2, 2, 2, 3] ��2�ĳ��ִ�����3�Ρ�
// Parameter:
// array: ��������ĵ�ַ
// length: ���鳤��
// item: Ҫ���ҵ�Ԫ��
// Return value:
// �������������������еĳ��ִ���
int find_occurrence_number_in_odered_array(int *array, int length, int item);


// �ҳ�������Ψһ���ظ�Ԫ��
// 1-1000���ں���1001��Ԫ�ص������У�ֻ��Ψһ��һ��Ԫ��ֵ�ظ���������ֻ����һ�Σ�
// ÿ������Ԫ��ֻ�ܷ���һ�Σ����һ���㷨�������ҳ��������ø����洢�ռ䣬
// �ܷ����һ���㷨ʵ�֣�
int find_single_duplicate_int();


//������һ�ֱ��룺�磬N=134��M=f(N)=143,N=020,M=fun(N)=101,����N��M��λ��һ����
// N,M���Ծ�������0��ͷ��N,M�ĸ�λ��֮��Ҫ��ȣ���1+3+4=1+4+3����M�Ǵ���N����С��һ����
// ����������������S,NΪһ����ֵ������S(0)=N��S(1)=fun(N),S(2)=fun(S(1))��
void find_the_sequence(int *first_code, int length);


// һ�����������������������֮�⣬���������ֶ����������Ρ�
// ��д�����ҳ�������ֻ����һ�ε����֡�Ҫ��ʱ�临�Ӷ��� O(n)���ռ临�Ӷ��� O(1)��
void find_two_ints_appear_once(int *array, int n, int &i1, int &i2);


// һ���������飬Ԫ�ض�����[0,9]֮������֣���δ��ȫ������
// �������е�����(�����ظ�)���һ����С�ĸ���λ����������
int generate_min_int_containing_duplicate_digit(int *array, int n, int bit_num);


// Google2009���ϵ���������
// ����һ������A=[0,1,3,8](�ü����е�Ԫ�ض�����0��9֮������֣���δ��ȫ������)��
// ָ������һ��������K������A�е�Ԫ�����һ������K����С��������
// ���磬A=[1,0] K=21 ��ô����ṹӦ��Ϊ100��
int generate_min_int_greater_than_k(int *array, int n, int k);


// ����Ͱ��о�Ժ��2009����
// �������ʵ����V[N]��Ҫ���������С���ڵ�ʵ���Ĳ�����ֵ���ؼ���Ҫ�����Կռ������ʱ��
// �ⷨһ���������ټ�������ʵ��������ֵ
double max_difference_of_adjacent_floats_by_value_v1(double *array, int length);
// �ⷨ��������Ͱ����
double max_difference_of_adjacent_floats_by_value_v2(double *array, int length);


// �����������-������ٷ�
int max_sum_of_subarray_brute_force(int *array, int n);
// �����������-��̬�滮
int max_sum_of_subarray_dp(int *array, int n);
// ��β��ӵ�ѭ������������������
int max_sum_of_subarray_in_circular_array(int *array, int n);
// ͬʱ�����������λ��
int max_sum_of_subarray_dp_pos(int *array, int n, int &pos, int &size);


// ��һ�������ʼ�����ɸ�Ԫ�ذᵽ�����ĩβ�����ǳ�֮Ϊ�������ת��
// ����һ���ź���������һ����ת�������ת�������СԪ�ء�
// ��������{3, 4, 5, 1, 2}Ϊ{1, 2, 3, 4, 5}��һ����ת�����������СֵΪ1��
// Parameter:
// array: �����ַ
// begin: �����һ��Ԫ�ص�����
// end: �������һ��Ԫ�ص���������һ������
// Return value:
// ��СֵԪ��
int min_from_lshifted_increasing_array(int *array, int length);


// ������ֵ���⣨Range Max/Min Query��
// ST��Sparse Table���㷨��һ���ǳ����������ߴ���RMQ������㷨����������O(nlogn)ʱ����
// ����Ԥ����Ȼ����O(1)ʱ���ڻش�ÿ����ѯ��
// range: Ҫ��ѯ������
// sparse_table: ���st����¼�ӵ�i����������2^j�����е���Сֵ
void preprocess_RMQ_ST(const std::vector<int> &range, boost::multi_array<int, 2> &sparse_table);


// ����һ�����������飬���������������ų�һ������������ų���������������С��һ����
// ������������{32, 321}����������������ųɵ���С����32132��
// ��������������㷨����֤�����㷨��
void rearrange_array_to_min(unsigned int *array, int n);

}

#endif // ARRAY_PROBLEM_H
