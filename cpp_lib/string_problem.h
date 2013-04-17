// string_problem.h
//
// last-edit-by: <��լΰ 2012-05-05>
//
// Description:
// �ַ�������
//////////////////////////////////////////////////////////////////////

#ifndef STRING_PROBLEM_H
#define STRING_PROBLEM_H 1

#include <cstddef>
#include <string>

namespace zhaiwei
{
// ��һ����Ϻ�������p([1,2,3]) �������[1],[2],[3],[1,2],[2,3],[1,3],[1,2,3]��
// ��ӡһ���ַ������������
// ���԰����ظ��ַ�����������ʹ��ͬ���ַ����ڡ�
void all_combination_with_duplicate_char(char *str, int length, int &count);
// �������ظ��ַ���
void all_combination_without_duplicate_char(char *str, int length, int &count);


// ��һ��ȫ���к�������p([1,2,3]) �������  [123],[132],[213],[231],[321],[323]��
// ��ӡ��һ���ַ�����ȫ���С�����û���ظ����ַ����ݹ鷽����
// Parameter:
// str: �ַ���
// begin: �ַ�����һ���ַ�������
// end: �ַ������һ���ַ�������
// count: ͳ��ȫ���е���Ŀ
// �ֵ��򷽷�������֮ǰʹ�ַ����������С����԰����ظ��ַ���
void all_permutation_by_dictionary_order(char *str, int length, int &count);
// �ַ������԰����ظ����ַ�����Ҫ���ȶ��ַ�������ʹ�ظ����ַ�����
void all_permutation_with_duplicate_char(char *str, int begin, int end, int &count);
// �ַ���û���ظ����ַ�
void all_permutation_without_duplicate_char(char *str, int begin, int end, int &count);


// ��������ַ������ַ�һ��������˳��һ��������Ϊ���ֵ��ַ������������Ѹ��ƥ���ֵ��ַ���
// ���磬bad��adb�����ֵ��ַ�������
bool brother_string_match(char *str1, char *str2);


// �Ա������⣺
// �����Ӧ�����ݽṹ���㷨��������Ч��ͳ��һƬӢ�����£��ܵ�����Ŀ������ֵ�����Ӣ�ĵ��ʣ�
// �������������״γ��ֵ�˳���ӡ����õ��ʺ����ĳ��ִ���
void count_word_in_a_text(const std::string &file_name);


// ɾ���ַ����е����ֲ�ѹ���ַ��������ַ�����abc123de4fg56��������Ϊ��abcdefg����ע��ռ��Ч�ʡ�
// ��������㷨ֻ��Ҫһ�α���������Ҫ�����¿ռ䣬ʱ�临�Ӷ�Ϊ O(N)��
void erase_digit_char(char *str);


// ��Ŀ�����������ַ������ӵ�һ�ַ�����ɾ���ڶ����ַ��������е��ַ���
// ���磬���롱They are students.���͡�aeiou���� ��ɾ��֮��ĵ�һ���ַ�����ɡ�Thy r stdnts.����
// ����������һ��΢�������⡣
void erase_specific_char(char *str1, const char *str2);


// ��һ���ַ������ҵ���һ��ֻ����һ�ε��ַ���������abaccdeff�������b��
// �������������2006��google��һ�������⡣
char find_first_single_char(const char *str);


// �����������
// ��Ŀ������ַ���һ�������ַ��������ַ����е�˳�����������һ���ַ������У����ַ���һ��֮Ϊ�ַ��������Ӵ���
// ע�⣬����Ҫ���Ӵ����ַ���һ�����ַ����������������ַ������С�
// ���дһ�����������������ַ����������ǵ�������Ӵ�������ӡ��������Ӵ���
// ���磺���������ַ���BDCABA��ABCBDAB���ַ���BCBA��BDAB���������ǵ�������Ӵ���
// ��������ǵĳ���4������ӡ����һ���Ӵ���
int find_longest_common_subsequence(const char *str1, const char *str2);


// ���ַ������ҳ�����������ִ�������������ĳ��ȷ��أ�
// �����������ִ���������һ����������outputstr��ָ�ڴ档
// ���磺"abcd12345ed125ss123456789"���׵�ַ����intputstr�󣬺���������9��
// outputstr��ָ��ֵΪ123456789
int find_longest_continuous_digit_sequence(const char *instr, char *outstr);


// ����������������ִ����硰ads3sl456789DF3456ld345AA���еġ�456789����
// �����һ����������������ִ��������䳤��
int find_longest_continuous_increasing_digit_sequence(const char *str, char *digits);


// �Գ��ַ�������󳤶ȡ�
// ��Ŀ������һ���ַ�����������ַ����жԳƵ����ַ�������󳤶ȡ����������ַ�����google����
// ���ڸ��ַ�������ĶԳ����ַ����ǡ�goog����������4��
int find_longest_symmetric_substring(const char *str);


// ��C ����ʵ�ֺ���void * memmove(void *dest,const void *src,size_t n)��
// memmove �����Ĺ����ǿ���src ��ָ���ڴ�����ǰn ���ֽڵ�dest ��ָ�ĵ�ַ�ϡ�
void *memory_move(void *dest, const void *src, size_t n);
// �Ӻ���ǰ����
void *memory_move_backward(void *dest, const void *src, size_t n);
// ��ǰ���󿽱�
void *memory_move_forward(void *dest, const void *src, size_t n);


//����һ��Ӣ�ľ��ӣ���ת�����е��ʵ�˳�򣬵��������ַ���˳�򲻱䡣�����е����Կո��������
//ʵ���ٶ���죬�ƶ����١�Ϊ������������ź���ͨ��ĸһ������
//�������롰I am a student.�����������student. a am I����
void reverse_sentence(char *sentence);


// ����һ����ʾ�������ַ������Ѹ��ַ���ת���������������
// �罫�ַ�����+123��123, ��-0123��-123, ��123CS45��123, ��123.45CS��123, ��CS123.45��0
int string_atoi(const char *str);


// �ַ����Ƚ�
// Parameter:
// str1: �ַ���
// str2: �ַ���
// Return value:
// ��ֵ, ��0, ����ֵ
int string_compare(const char *str1, const char *str2);


// �ַ���ԭ��ѹ��
// ��Ŀ������"eeeeeaaaff" ѹ��Ϊ "e5a3f2"������ʵ�֡�
void string_compress_in_place(char *str);


// ��Ѷ�����⣺
// һ���ַ���S1��ȫ���ɲ�ͬ����ĸ��ɵ��ַ����磺abcdefghijklmn
// ��һ���ַ���S2��������S1��������Ҫ��S1�̡�
// �����ǣ����һ���㷨����S2�е���ĸ�Ƿ����S1�С�
// ���Դ����Сд��ĸ
bool string_contain_by_bitmap(char *str1, char *str2);
// ���Դ����Сд��ĸ
bool string_contain_by_hashmap(char *str1, char *str2);
// ֻ�ܴ����д��ĸ��Сд��ĸ��ʵ�ֵ��Ǵ����д��ĸ
bool string_contain_by_shift_bit(char *str1, char *str2);


// ��֪һ���ַ��������� asderwsde��Ѱ�����е�һ�����ַ������� sde �ĸ��������û�з���0��
// �еĻ��������ַ����ĸ�����
int string_count_substr(const char *str, const char *substr);


// �ַ����༭�������� CLRS 15-3
// str1: Դ�ı���, ���±�1��ʼ
// str1_len: Դ�ı����ĳ���
// str2: Ŀ���ı���, ���±�1��ʼ
// str2_len: Ŀ���ı����ĳ���
// op_cost: ÿ�ֲ����Ĵ���, op_cost[0]����, op_cost[1]�滻, op_cost[2]ɾ��,
//          op_cost[3]����, op_cost[4]����, op_cost[5]����
// op_num: ��������Ŀ
// û�в���
int string_edit_distance(const char *str1, int str1_len, const char *str2, int str2_len, int *op_cost, int op_num);


// ��Ϊ������
// �ж�һ�ַ����ǲ��ǶԳƵģ��磺abccba
bool string_is_symmetric(const char *str);


// �����ַ���������ת���������ַ���ǰ������ɸ��ַ��ƶ����ַ�����β����
// ����ַ���abcdef����ת2 λ�õ��ַ���cdefab����ʵ���ַ�������ת�ĺ�����
// Ҫ��ʱ��Գ���Ϊn���ַ��������ĸ��Ӷ�ΪO(n)�������ڴ�ΪO(1)��
// Parameter:
// str: �ַ���
// n: �ַ����ĳ���
// m: ����ת���ַ���
void string_left_shift(char *str, int n, int m);


// �����κ��м������ʵ��strlen����
int string_length(const char *str);


// �ٶȱ�����
// �� C ����ʵ�ֺ��� void * memmove(void *dest, const void *src, size_t n)��
// memmove �����Ĺ����ǿ��� src ��ָ���ڴ�����ǰ n ���ֽڵ� dest ��ָ�ĵ�ַ�ϡ�
// ע��߽�������
void *string_memmove(void *dest, const void *src, size_t n);


// 2005��11�½�ɽ�����⡣�����������Ĵ�������
// �������ַ����е��ַ�'*'�Ƶ�����ǰ���֣�ǰ��ķ�'*'�ַ����ƣ������ܸı��'*'�ַ����Ⱥ�˳�򣬺�������
// �����ַ�'*'��������
// ��ԭʼ��Ϊ��ab**cd**e*12�������Ϊ*****abcde12������������ֵΪ5��
// ��Ҫ��ʹ�þ����ٵ�ʱ��͸����ռ䣩
int string_move_star_char_forward(char *str);


//�ߵ�һ���ַ������Ż��ٶȡ��Ż��ռ䡣
void string_reverse(char *str);
void string_reverse(char *str, int length);

}

#endif // STRING_PROBLEM_H
//////////////////////////////////////////////////////////////////////
