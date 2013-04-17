// huffman_compress.h
//
// last-edit-by: <> 
//
// Description:
// huffman文件压缩
// 
// Parameter:
//
// Return value:
//
//////////////////////////////////////////////////////////////////////

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H 1

#include <cstdio>
#include <vector>
#include <queue>
#include <string>

namespace zhaiwei
{

class huffman_tree
{
public:
    huffman_tree(char ch = ' ', int weight = 0, huffman_tree *p_left = NULL, huffman_tree *p_right = NULL):
        m_ch(ch), m_weight(weight), mp_left(p_left), mp_right(p_right)
    {}
    
    char m_ch;
    int m_weight;
    huffman_tree *mp_left;
    huffman_tree *mp_right;
};

class huffman_tree_greater
{
public:
    bool operator()(huffman_tree *p_lhs, huffman_tree *p_rhs)
    {
        return p_lhs->m_weight > p_rhs->m_weight;
    }
};

class huffman_compress
{
public:
    huffman_compress();
    ~huffman_compress();

    // 设置源文件，打开源文件和目标文件
    void set_file(const std::string &src_file_name);
    // 压缩文件，生成目标文件
    void compress();
private:
    std::size_t m_src_file_size; // 源文件字符数目
    std::size_t m_dst_file_size; // 目标文件字符数目
    std::size_t m_leaf_size; // huffman树中树叶的数目，即不同字符的数目
    FILE *mp_src_file; // 源文件
    FILE *mp_dst_file; // 目标文件
    std::vector<int> m_char_freq; // 记录每个字符在源文件中出现的频率
    std::vector<std::string> m_huffman_code; // 以字符串的形式存储每个字符的最优前缀码
    std::priority_queue<huffman_tree *, std::vector<huffman_tree *>, huffman_tree_greater> m_huffman_forest; // huffman森林

    // 分析字符在源文件中出现的频率
    void analyze_char_frequency();
    // 构建huffman树
    void build_huffman_tree();
    // 清空huffman树
    void clear_huffman_tree(huffman_tree *p_tree);
    // 关闭源文件和目标文件
    void close_file();
    // 生成huffman编码
    void generate_huffman_code(huffman_tree *p_tree, const std::string &huffman_code);
    // 打开源文件和目标文件，若目标文件不存在，根据源文件名创建目标文件
    void open_file(const std::string &src_file_name);
    // 写huffman编码到目标文件中
    void write_huffman_code_to_dest_file();
    
};

}


#endif // HUFFMAN_COMPRESS_H
//////////////////////////////////////////////////////////////////////
