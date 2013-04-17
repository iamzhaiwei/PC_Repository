// string_suffix_array.h
//
// last-edit-by:
//
// Description:
// �ַ�����׺����
//////////////////////////////////////////////////////////////////////

#ifndef STRING_SUFFIX_ARRAY_H
#define STRING_SUFFIX_ARRAY_H 1

#include <vector>
//////////////////////////////////////////////////////////////////////

namespace zhaiwei
{

// һ���㷨���ַ����ĺ�׺����
// str: �ԡ�\0����β���ַ���ָ��
// length: �ַ����ĳ���
// sa: ��׺����
void string_suffix_array(const char *str, int length, std::vector<int> &sa);


// ��������洢��׺�Ĵδ�
// ���ݺ�׺��������������
// sa: ��׺����
// ra: ��������
void string_rank_array(const std::vector<int> &sa, std::vector<int> &ra);


// height���飺�������ڵ�������׺�������ǰ׺
// ���ݺ�׺������height����
// str: �ַ���ָ��
// length: �ַ�������
// sa: ��׺����
// ha: height����
void string_height_array(const char *str, int length, const std::vector<int> &sa, std::vector<int> &ha);


// ����һ���ַ�����ѯ��ĳ������׺�������ǰ׺
// str: �ַ���ָ��
// length: �ַ�������
// i, j: ������׺���±�
int max_length_of_common_prefix_of_suffix(const char *str, int length, int i, int j);
int max_length_of_common_prefix_of_suffix(const std::vector<int> &ra, const std::vector<int> &ha, int i, int j);

// �����ص���ظ��Ӵ���pku1743��
// ����һ���ַ����������ظ��Ӵ��������䳤�ȣ��������Ӵ������ص���
int max_length_of_nonoverlapping_repetitive_substr(const char *str, int length);


// �ظ��Ӵ����ַ��� R ���ַ��� L �����ٳ������Σ���� R �� L ���ظ��Ӵ���
// ���ص���ظ��Ӵ�
// ����һ���ַ����������ظ��Ӵ��������䳤�ȣ��������Ӵ������ص���
int max_length_of_overlapping_repetitive_substr(const char *str, int length);


// ������Ӵ���ural1297��
// �����Ӵ���������ַ��� L ��ĳ�����ַ��� R ������д���ԭ�����ַ��� R
// һ��������ַ��� R ���ַ��� L �Ļ����Ӵ���
// ����һ���ַ��������������Ӵ��������䳤�ȡ�
int max_length_of_palindrome_substr(const char *str, int length);


// �����ظ��Ӵ�(pku2406)
// ����һ���ַ��� L����֪����ַ�������ĳ���ַ��� S �ظ� R �ζ��õ��ģ��� R �����ֵ��
int number_of_continuous_repetitive_substr(const char *str, int length);


// ����ͬ���Ӵ��ĸ�����spoj694,spoj705��
// ����һ���ַ���������ͬ���Ӵ��ĸ�����
int number_of_different_substr(const char *str, int length);


// ���ڴ�Լ�����һλ��С�ڴ��������κ�Ԫ�ص�Ԫ��
// ������
// s: �ַ���
// sa: ��׺����
void string_suffix_array_da(char *s,int *sa);
}

/*

*/
#endif
