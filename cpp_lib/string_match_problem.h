// string_match_problem.h
//
// last-edit-by: <��լΰ 2012-05-05> 
//
// Description:
// �ַ�������
//////////////////////////////////////////////////////////////////////

#ifndef STRING_MATCH_PROBLEM_H
#define STRING_MATCH_PROBLEM_H 1



namespace zhaiwei
{


// ��һ���㷨ʹͨ���ַ�����ƥ�䡣
// ģʽ���п��ܺ���ͨ�����
// Parameter:
// str: �ı���
// pattern: ģʽ��
// Return value:
// ����ı�����ģʽ����ƥ�䣬����true�����򷵻�false
bool match_generic_string(char *str, char *pattern);


// ���ص�ƥ���㷨
// �ַ���ƥ������: ���ı�text�в���ģʽpattern��һ�γ��ֵ�λ�ã���û�г��֣�����-1
// �������е��ַ�����ASCII�ַ���
// Parameter:
// text: �ı���
// pattern: ģʽ��
// Return value:
// ģʽ�����ı�����һ�γ��ֵ�λ�õ�ָ�룬����NULL
const char *string_naive_match(const char *text, const char *pattern);


// Rabin-Karp�ַ���ƥ���㷨
// Parameter:
// text: �ı���
// pattern: ģʽ��
// base_number: ����ÿ���ַ����ǻ���Ϊbase_number�ı�ʾ���е�һ������
// prime_number: ģ���õ�������
// Return value:
// ģʽ�����ı�����һ�γ��ֵ�λ�õ�ָ�룬����NULL
const char *string_rabin_karp_match(const char *text, const char *pattern, int base_number);
const char *string_rabin_karp_match(const char *text, const char *pattern, int base_number, int prime_number);


// �ַ���ƥ��-Sunday�㷨��
// �������е��ַ�����ASCII�ַ���
// Parameter:
// text: �ı���
// pattern: ģʽ��
// Return value:
// ģʽ�����ı�����һ�γ��ֵ�λ�õ�ָ�룬����NULL
const char *string_sunday_match(const char *text, const char *pattern);



}

#endif // STRING_MATCH_PROBLEM_H
