// bitmap.h
//
// last-edit-by: <>
//
// Description:
// 位数组
// 存储方式：
// 字节在数组中：byte0 byte1 byte2 ...
// 位在字节中：  bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
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

	// 设置位i的值为1
	void set(int i)
	{
		mp_buffer[BYTE_INDEX(i)] |= (0x01 << BIT_INDEX(i));
	}
	// 清空位i的值为0
	void clear(int i)
	{
		mp_buffer[BYTE_INDEX(i)] &= ~(0x01 << BIT_INDEX(i));
	}
	// 清空所有的位为0
	void clear()
	{
		memset(mp_buffer, 0, BYTE_NUMBER(m_bit_number));
	}
	// 测试位i的值是否为1，若为1，返回true，若为0，返回false
	bool test(int i) const
	{
		return mp_buffer[BYTE_INDEX(i)] & (0x01 << BIT_INDEX(i));
	}
	// 返回位数目
	int bit_number() const
	{
		return m_bit_number;
	}
private:
	char *mp_buffer; 	// 位数组，以字节数组表示
	int m_bit_number; 	// 位的数目

	static int BITS_PER_BYTE;	// 每个字节的位数目
	static int SHIFT;			// 移位数目
	static int MASK;			// 掩码
	static int BYTE_NUMBER(int bit_num)	// 根据位数目求出字节数目
	{
		return (bit_num >> SHIFT) + 1;
	}
	static int BYTE_INDEX(int i)// 返回位i所在字节的索引
	{
		return i >> SHIFT;
	}
	static int BIT_INDEX(int i)	// 返回位i在其字节中的索引
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

// 重载输出操作符
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
