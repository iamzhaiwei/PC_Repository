//复制一棵树，返回新树的根
    btree_node<T> *copy(btree_node<T> *);

// 复制构造函数
    bstree(const bstree<T> &rhs):mp_root(NULL), m_size(0)
    {
        mp_root = copy(rhs.mp_root);
        m_size = rhs.m_size;
    }
	// 赋值操作符
    bstree<T> &operator=(const bstree<T> &rhs)
    {
        btree_node<T> *porig = mp_root;
        mp_root = copy(rhs.mp_root);
        m_size = rhs.m_size;
        clear(porig);
        return *this;
    }

//复制一棵树，返回新树的根
template <typename T>
btree_node<T> *bstree<T>::copy(btree_node<T> *t)
{
    if (t == NULL)
        return NULL;
        
    btree_node<T> *new_t = new btree_node<T>(t->m_item, NULL, NULL, NULL);
        
    new_t->mp_left = copy(t->mp_left);
    if (new_t->mp_left != NULL)
        new_t->mp_left->mp_parent = new_t;
        
    new_t->mp_right = copy(t->mp_right);
    if (new_t->mp_right != NULL)
        new_t->mp_right->mp_parent = new_t;

    return new_t;
}
