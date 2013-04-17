// bitmap.h
//
// last-edit-by: <>
//
// Description:
// λ����
// �洢��ʽ��
// �ֽ��������У�byte0 byte1 byte2 ...
// λ���ֽ��У�  bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
//////////////////////////////////////////////////////////////////////

#ifndef BITMAP_H
#define BITMAP_H 1

#include <cstring>
#include <iostream>

namespace zhaiwei
{

class bitmap
{
public:
	bitmap(int bit_number):	mp_buffer(NULL), m_bit_number(bit_number)
	{
		mp_buffer = new char[BYTE_NUMBER(m_bit_number)];
	}
	~bitmap()
	{
		delete [] mp_buffer;
	}

	// ����λi��ֵΪ1
	void set(int i)
	{
		mp_buffer[BYTE_INDEX(i)] |= (0x01 << BIT_INDEX(i));
	}
	// ���λi��ֵΪ0
	void clear(int i)
	{
		mp_buffer[BYTE_INDEX(i)] &= ~(0x01 << BIT_INDEX(i));
	}
	// ������е�λΪ0
	void clear()
	{
		memset(mp_buffer, 0, BYTE_NUMBER(m_bit_number));
	}
	// ����λi��ֵ�Ƿ�Ϊ1����Ϊ1������true����Ϊ0������false
	bool test(int i) const
	{
		return mp_buffer[BYTE_INDEX(i)] & (0x01 << BIT_INDEX(i));
	}
	// ����λ��Ŀ
	int bit_number() const
	{
		return m_bit_number;
	}
private:
	char *mp_buffer; 	// λ���飬���ֽ������ʾ
	int m_bit_number; 	// λ����Ŀ

	static int BITS_PER_BYTE;	// ÿ���ֽڵ�λ��Ŀ
	static int SHIFT;			// ��λ��Ŀ
	static int MASK;			// ����
	static int BYTE_NUMBER(int bit_num)	// ����λ��Ŀ����ֽ���Ŀ
	{
		return (bit_num >> SHIFT) + 1;
	}
	static int BYTE_INDEX(int i)// ����λi�����ֽڵ�����
	{
		return i >> SHIFT;
	}
	static int BIT_INDEX(int i)	// ����λi�����ֽ��е�����
	{
		return i & MASK;
	}
private:
	bitmap(const bitmap &);
	bitmap &operator=(const bitmap &);
};

int bitmap::BITS_PER_BYTE = 8;
int bitmap::SHIFT = 3;
int bitmap::MASK = 0x07;

// �������������
std::ostream &operator<<(std::ostream &ostr, const bitmap &bm)
{
	for (int i = 0; i < bm.bit_number(); ++i)
	{
		ostr << (bm.test(i)? '1': '0');
	}
	return ostr;
}

}

#endif // BITMAP_H
//////////////////////////////////////////////////////////////////////
