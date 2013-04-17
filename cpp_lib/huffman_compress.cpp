// huffman_compress.cpp
//////////////////////////////////////////////////////////////////////

#include "huffman_compress.h"
#include <iterator>
#include <queue>
#include <stdexcept>
//////////////////////////////////////////////////////////////////////

using namespace std;

static const int MAX_CHAR_NUM = 256;
namespace zhaiwei
{

huffman_compress::huffman_compress():
    m_src_file_size(0), m_dst_file_size(0), m_leaf_size(0), mp_src_file(NULL),
    mp_dst_file(NULL), m_char_freq(MAX_CHAR_NUM, 0), m_huffman_code(MAX_CHAR_NUM, ""),
    m_huffman_forest()
{
}

huffman_compress::~huffman_compress()
{
    close_file();
    
    if (!m_huffman_forest.empty())
        clear_huffman_tree(m_huffman_forest.top());
}

void huffman_compress::set_file(const std::string &src_file_name)
{
    close_file();
    open_file(src_file_name);
}

void huffman_compress::compress()
{
    analyze_char_frequency();
    build_huffman_tree();
    generate_huffman_code(m_huffman_forest.top(), "");
    for (int i = 'a'; i <= 'f'; ++i)
    {
        fprintf(stdout, "%c: %s\n", i, m_huffman_code[i].c_str());
    }
}

void huffman_compress::analyze_char_frequency()
{
    char ch;
    while (fscanf(mp_src_file, "%c", &ch) != EOF)
    {
        ++m_char_freq[(int)(unsigned char)(ch)];
        if (m_char_freq[(int)(unsigned char)(ch)] == 1)
        {
            ++m_leaf_size;
        }
        ++m_src_file_size;
    }
}

void huffman_compress::close_file()
{
    if (mp_src_file != NULL)
    {
        fclose(mp_src_file);
        mp_src_file = NULL;
    }
    if (mp_dst_file != NULL)
    {
        fclose(mp_dst_file);
        mp_dst_file = NULL;
    }
}

void huffman_compress::build_huffman_tree()
{
    for (int i = 0; i != m_char_freq.size(); ++i)
    {
        if (m_char_freq[i] != 0)
        {
            m_huffman_forest.push(new huffman_tree(i, m_char_freq[i], NULL, NULL));
        }
    }
    huffman_tree *p_tree1, *p_tree2;
    while (m_huffman_forest.size() >= 2)
    {
        p_tree1 = m_huffman_forest.top();
        m_huffman_forest.pop();
        p_tree2 = m_huffman_forest.top();
        m_huffman_forest.pop();
        m_huffman_forest.push(new huffman_tree(-1, p_tree1->m_weight+p_tree2->m_weight, p_tree1, p_tree2));
    }
}

void huffman_compress::clear_huffman_tree(huffman_tree *p_tree)
{
    if (p_tree == NULL)
        return;
    clear_huffman_tree(p_tree->mp_left);
    clear_huffman_tree(p_tree->mp_right);
    delete p_tree;
}

void huffman_compress::generate_huffman_code(huffman_tree *p_tree, const std::string &huffman_code)
{
    if (p_tree == NULL)
        return;
    if (p_tree->mp_left == NULL && p_tree->mp_right == NULL)
        m_huffman_code[(int)(unsigned char)(p_tree->m_ch)] = huffman_code;
    generate_huffman_code(p_tree->mp_left, huffman_code+"0");
    generate_huffman_code(p_tree->mp_right, huffman_code+"1");
}

void huffman_compress::open_file(const std::string &src_file_name)
{
    if ( (mp_src_file = fopen(src_file_name.c_str(), "r")) == NULL)
        throw runtime_error("huffman_compress: open source file error");
    
    string dst_file_name = src_file_name + ".huf";
    if ( (mp_dst_file = fopen(dst_file_name.c_str(), "w")) == NULL)
        throw runtime_error("huffman_compress: open dest file error");
}

void huffman_compress::write_huffman_code_to_dest_file()
{
}

}
