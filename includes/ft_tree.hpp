#pragma once
#include <iostream>
#include "ft_type_traits.hpp"
#include "ft_iterator_traits.hpp"
#include <iterator>
#include "ft_iterator.hpp"
#include "ft_pair.hpp"
#include "ft_utils.hpp"
namespace ft
{
    template <typename Ptr>
    struct tree_end_node {

        Ptr     left;
        tree_end_node() : left(0) {}
    };

    struct tree_node_base: public tree_end_node<tree_node_base *>
    {
        typedef tree_node_base       *base_ptr;
        typedef const tree_node_base *const_base_ptr;

        base_ptr right;
        base_ptr parent;
        tree_node_base() : tree_end_node(), right(0), parent(0) {}

    };

    template <typename _T>
    struct tree_node : public tree_node_base
    {
        _T value;

        tree_node() : value() {}
        tree_node(const _T &_value) :tree_node_base(), value(_value) {}
    };


    enum node_color { color_red = 0, color_black = 1 };

    template <typename _T>
    struct rbtree_node: public tree_node<_T>
    {
        node_color color;
        rbtree_node(const _T& value): tree_node<_T>(value), color(color_red) {}
    };

    tree_node_base *tree_minimum(tree_node_base *node);
    tree_node_base *tree_maximum(tree_node_base *node);
    bool tree_is_left_node(tree_node_base *node);
    bool tree_is_right_node(tree_node_base *node);
    tree_node_base *tree_next_node(tree_node_base *node);
    tree_node_base *tree_prev_node(tree_node_base *node);
    tree_node_base *_left_rotate(tree_node_base *a);
    tree_node_base *_right_rotate(tree_node_base *a);


    
    template <typename _T>
    class tree_iterator
    {
    public:
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef ptrdiff_t                           difference_type;
        typedef _T                                  value_type;
        typedef _T*                                 pointer;
        typedef _T&                                 reference;
        typedef tree_iterator<_T>                   iterator;
        typedef tree_node<_T>                       node_type;
        typedef node_type*                          node_ptr;
        typedef tree_node_base                      node_base_type;
        typedef node_base_type*                     node_base_ptr;

        node_base_ptr _node;


        tree_iterator() : _node(0) {}
        explicit tree_iterator(node_base_ptr node) : _node(node) {}

        reference operator*() const { return static_cast<node_ptr>(_node)->value; }
        pointer operator->() const { return ft::address_of(static_cast<node_ptr>(_node)->value); }

        iterator &operator++() 
        { 
            _node = tree_next_node(_node);
            return *this;
        }

        iterator operator++(int) 
        { 
            iterator tmp = *this;
            ++*this;
            return tmp;
        }

        iterator &operator--()
        {
            _node = tree_prev_node(_node);
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            --*this;
            return tmp;
        }
        
        node_base_ptr get_node() const { return _node; }

        bool operator==(const iterator &other) const { return _node == other._node; }
        bool operator!=(const iterator &other) const { return _node != other._node; }
        

    };


    template <typename _T>
    class tree_const_iterator
    {
    public:
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef ptrdiff_t                           difference_type;
        typedef size_t                              size_type;
        typedef _T                                  value_type;
        typedef const _T*                           pointer;
        typedef const _T&                           reference;
        typedef tree_const_iterator<_T>             iterator;
        typedef tree_node<_T>                       node_type;
        typedef node_type*                          node_ptr;
        typedef tree_node_base                      node_base_type;
        typedef node_base_type*                     node_base_ptr;
        typedef tree_iterator<_T>                   non_tree_const_iterator;
        node_base_ptr _node;

        tree_const_iterator() : _node(0) {}
        explicit tree_const_iterator(node_base_ptr node) : _node(node) {}

        tree_const_iterator(const non_tree_const_iterator &other) : _node(other._node) {}

        reference operator*() const { return static_cast<node_ptr>(_node)->value; }
        pointer operator->() const { return ft::address_of(static_cast<node_ptr>(_node)->value); }

        iterator &operator++() 
        { 
            _node = tree_next_node(_node);
            return *this;
        }

        iterator operator++(int) 
        { 
            iterator tmp = *this;
            ++*this;
            return tmp;
        }

        iterator &operator--()
        {
            _node = tree_prev_node(_node);
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            --*this;
            return tmp;
        }
        
        node_base_ptr get_node() const { return _node; }

        bool operator==(const tree_const_iterator &rhs) { return _node == rhs._node; }

        bool operator!=(const tree_const_iterator &rhs) { return _node != rhs._node; }

    };

   











    template <typename T,
              typename KeyOf,
              typename KeyType = T,
              typename ValueType = T,
              typename Compare = std::less<T>,
              typename Alloc = std::allocator<T> >
    class Tree
    {
    public:
        typedef KeyType                                             key_type;
        typedef ValueType                                           value_type;
        typedef rbtree_node<T>                                      node_t;
        typedef Compare                                             key_compare;
        typedef Compare                                             value_compare;
        typedef typename Alloc::template rebind<node_t>::other      allocator_type;
        typedef T&                                                  reference;
        typedef const T&                                            const_reference;
        typedef T*                                                  pointer;
        typedef const T*                                            const_pointer;
        typedef KeyOf                                               key_of_value;
        typedef tree_iterator<T>                                    iterator;
        typedef tree_const_iterator<T>                              const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
        typedef size_t                                              size_type;
        typedef node_t*                                             node_ptr;
        typedef tree_node_base                                      node_base_t;
        typedef tree_node_base*                                     node_base_ptr;
        typedef tree_end_node<node_base_ptr>                        end_node_t;
        typedef tree_end_node<node_base_ptr>*                       end_node_ptr;

        
        node_base_ptr                                   begin_node;
        end_node_t                                      end_node;
        key_compare                                     _comp;
        allocator_type                                  allocator;
        size_type                                       _size;


        node_base_ptr                       _end_node() { return static_cast<tree_node_base*>(&end_node); };
        node_base_ptr&                      _begin_node() { return begin_node; };
        const node_base_ptr&                _begin_node() const { return begin_node; };
        node_base_ptr                       _root() { return _end_node()->left; };


        iterator                            begin() { return iterator(_begin_node()); };
        iterator                            end() { return iterator(_end_node()); };
        const_iterator                      begin() const { return const_iterator(_begin_node()); };
        const_iterator                      end() const { return const_iterator(_end_node()); };
        reverse_iterator                    rbegin() { return reverse_iterator(end()); };
        reverse_iterator                    rend() { return reverse_iterator(begin()); };
        const_reverse_iterator              rbegin() const { return const_reverse_iterator(end()); };
        const_reverse_iterator              rend() const { return const_reverse_iterator(begin()); };


        bool empty() const { return _size == 0; }
        size_type size() const { return _size;  }
        size_type max_size() const{ return size_type(-1); } // TODO}


        Tree(const Compare &comp = Compare(), const allocator_type &alloc = allocator_type()) : end_node(), _comp(comp), allocator(alloc), _size(0)
        {
            begin_node = _end_node();
        }

        Tree(const Tree &other) : end_node(), _comp(other._comp), allocator(other.allocator), _size(0)
        {
            begin_node = _end_node();
            // todo use iterators to copy
        }


        node_base_ptr& find_unique_position(const key_type& key, node_base_ptr &parent)
        {
            parent = _end_node();
            node_base_ptr* _node_ptr = &(parent->left);
            while (*_node_ptr)
            {
                if (_comp(key, key_of_value()(static_cast<node_ptr>(*_node_ptr)->value)))
                {
                    parent = *_node_ptr;
                    _node_ptr = &(parent->left);
                }
                else if (_comp(key_of_value()(static_cast<node_ptr>(*_node_ptr)->value), key))
                {
                    parent = *_node_ptr;
                    _node_ptr = &(parent->right);
                }
                else
                {
                    while ((*_node_ptr)->left && !_comp(key_of_value()(static_cast<node_ptr>((*_node_ptr)->left)->value), key))
                    {
                        parent = *_node_ptr;
                        _node_ptr = &(parent->left);
                    }
                    return *_node_ptr;
                }
            }
            return *_node_ptr;
        }


        node_base_ptr& find_position(const key_type& key, node_base_ptr &parent)
        {
            parent = _end_node();
            node_base_ptr* _node_ptr = &(parent->left);
            while (*_node_ptr)
            {
                if (_comp(key, key_of_value()(static_cast<node_ptr>(*_node_ptr)->value)))
                {
                    parent = *_node_ptr;
                    _node_ptr = &(parent->left);
                }
                else
                {
                    parent = *_node_ptr;
                    _node_ptr = &(parent->right);
                }
            }
            return *_node_ptr;
        }


        node_base_ptr   erase(node_base_ptr node, node_base_ptr parent)
        {
            if (node == this->_begin_node())
                this->_begin_node() = tree_next_node(node);
            node_base_ptr x;
            node_base_ptr y = node;
            node_base_ptr x_parent;
            node_color y_original_color = _color(_rb(y));
            if (node->left && node->right)
            {
                y = tree_minimum(node->right);
                y_original_color = _color(_rb(y));
                x = y->right;
                if (y->parent != node)
                    x_parent = y->parent;
                else
                    x_parent = y;
                _rb(y)->color = _rb(node)->color;
                if (tree_is_left_node(y))
                    y->parent->left = y->right;
                else
                    y->parent->right = y->right;
                y->left = node->left;
                y->right = node->right;
                if (node->left)
                    node->left->parent = y;
                if (node->right)
                    node->right->parent = y;
                y->parent = parent;
                if (tree_is_left_node(node))
                    parent->left = y;
                else
                    parent->right = y;
            }
            else
            {
                x = node->left ? node->left : node->right;
                x_parent = node->parent;
                if (x)
                    x->parent = parent;
                if (tree_is_left_node(node))
                    parent->left = x;
                else
                    parent->right = x;
            }
            this->allocator.destroy(static_cast<node_ptr>(node));
            this->allocator.deallocate(static_cast<node_ptr>(node), 1);
            if (y_original_color != color_black)
                return x;
            while (x != this->_root() && _color(_rb(x)) == color_black)
            {
                if (x == x_parent->left)
                {
                    node_base_ptr   w = x_parent->right;
                    if (_color(_rb(w)) == color_red)
                    {
                        _rb(w)->color = color_black;
                        _rb(x_parent)->color = color_red;
                        _left_rotate(x_parent);
                        w = x_parent->right;
                    }
                    if (_color(_rb(w->left)) == color_black && _color(_rb(w->right)) == color_black)
                    {
                        _rb(w)->color = color_red;
                        x = x ? x->parent : x_parent;
                        x_parent = x->parent;
                    }
                    else
                    {
                        if (_color(_rb(w->right)) == color_black)
                        {
                            _rb(w->left)->color = color_black;
                            _rb(w)->color = color_red;
                            _right_rotate(w);
                            w = x_parent->right;
                        }
                        _rb(w)->color = _rb(x_parent)->color;
                        _rb(x_parent)->color = color_black;
                        _rb(w->right)->color = color_black;
                        _left_rotate(x_parent);
                        x = this->_root();
                    }
                }
                else
                {
                    node_base_ptr   w = x_parent->left;
                    if (_color(w) == color_red)
                    {
                        _rb(w)->color = color_black;
                        _rb(x_parent)->color = color_red;
                        _right_rotate(x_parent);
                        w = x_parent->left;
                    }
                    if (_color(_rb(w->right)) == color_black && _color(_rb(w)->left) == color_black)
                    {
                        _rb(w)->color = color_red;
                        x = x ? x->parent : x_parent;
                        x_parent = _rb(x->parent);
                    }
                    else
                    {
                        if (_color(_rb(w)->left) == color_black)
                        {
                            _rb(w->right)->color = color_black;
                            _rb(w)->color = color_red;
                            _left_rotate(w);
                            w = x_parent->left;
                        }
                        _rb(w)->color = _rb(x_parent)->color;
                        _rb(x_parent)->color = color_black;
                        _rb(w->left)->color = color_black;
                        _right_rotate(x_parent);
                        x = this->_root();
                    }
                }
            }
            if (x)
                _rb(x)->color = color_black;
            return x;
        }

        node_base_ptr   erase(node_base_ptr node)
        {
            return this->erase(node, node->parent);
        }


        void    erase_iter(iterator node)
        {
            this->erase(node.get_node(), node.get_node()->parent);
        }

        void    erase_iter(iterator first, iterator end)
        {
            while (first != end)
                this->erase_iter(first++);
        }

        size_type                       erase_uniq(const key_type& key)
        {
            node_base_ptr parent;
            node_base_ptr node = find_unique_position(key, parent);
            if (node == NULL)
                return 0;
            erase(node, parent);
            --_size;
            return 1;
        }

        size_type                       erase_multi(const key_type& key)
        {
            size_type count = 0;
            node_base_ptr parent;
            node_base_ptr node = find_unique_position(key, parent);
            if (node == NULL)
                return 0;
            while(!_comp(key, key_of_value()(static_cast<node_ptr>(node)->value)))
            {
                node_base_ptr next = tree_next_node(node);
                erase(node, parent);
                node = next;
                if (node == _end_node())
                    break;
                else
                    parent = node->parent;
                ++count;
                --_size;
            }
            return count;
        }


        ft::pair<iterator, bool>   insert_uniq(const_reference val)
        {
            node_base_ptr parent;
            node_base_ptr& node = find_unique_position(key_of_value()(val), parent);
            if (node)
                return ft::make_pair(iterator(node), false);
            else
            {
                node = allocator.allocate(1);
                try
                {
                    allocator.construct(static_cast<node_ptr>(node), val);
                }
                catch (...)
                {
                    allocator.deallocate(static_cast<node_ptr>(node), 1);
                    throw;
                }
                node->parent = parent;
                if (_begin_node()->left)
                    _begin_node() = _begin_node()->left;
                _rebalance_after_insert(static_cast<node_ptr>(node));
                ++_size;
                return ft::make_pair(iterator(node), true);
            }
        }

        ft::pair<iterator, bool> insert_multi(const_reference val)
        {
            node_base_ptr parent;
            node_base_ptr& node = find_position(key_of_value()(val), parent);
            node = allocator.allocate(1);
            try
            {
                allocator.construct(static_cast<node_ptr>(node), val);
            }
            catch (...)
            {
                allocator.deallocate(static_cast<node_ptr>(node), 1);
                throw;
            }
            node->parent = parent;
            _rebalance_after_insert(static_cast<node_ptr>(node));
            ++_size;
            return ft::make_pair(iterator(node), true);
        }

        node_ptr  _rb(node_base_ptr node)
        {
            return static_cast<node_ptr>(node);
        }
        
        node_color  _color(node_base_ptr node)
        {
            return node ? _rb(node)->color : color_black;
        }


        void    _print_tree(node_ptr node)
        {
            if (node)
            {
                printf("{ \"data\": \"%d\", \"color\": \"%d\", \"left\":", KeyOf()(node->value), _rb(node)->color);
                _print_tree(_rb(node->left));
                printf(", \"right\": ");
                _print_tree(_rb(node->right));
                printf("}");
            }
            else
                std::cout << "0";
        }



        node_ptr   _rebalance_after_insert(node_ptr node)
        {
            _rb(node)->color = color_red;
            node_ptr parent = _rb(node->parent);
            while (parent != this->_end_node() && _color(parent) == color_red)
            {
                node_ptr grand_parent = _rb(parent->parent);
                if (parent == grand_parent->left)
                {
                    node_ptr uncle = _rb(grand_parent->right);
                    if (_color(uncle) == color_red)
                    {
                        _rb(parent)->color = color_black;
                        _rb(uncle)->color = color_black;
                        _rb(grand_parent)->color = color_red;
                        node = grand_parent;
                        parent = _rb(node->parent);
                    }
                    else
                    {
                        if (node == parent->right)
                        {
                            node = parent;
                            _left_rotate(node);
                            parent = _rb(node->parent);
                            grand_parent = _rb(parent->parent);
                        }
                        _rb(parent)->color = color_black;
                        _rb(grand_parent)->color = color_red;
                        _right_rotate(grand_parent);
                    }
                }
                else
                {
                    node_ptr uncle = _rb(grand_parent->left);
                    if (_color(uncle) == color_red)
                    {
                        _rb(parent)->color = color_black;
                        _rb(uncle)->color = color_black;
                        _rb(grand_parent)->color = color_red;
                        node = grand_parent;
                        parent = _rb(node->parent);
                    }
                    else
                    {
                        if (node == parent->left)
                        {
                            node = parent;
                            _right_rotate(node);
                            parent = _rb(node->parent);
                            grand_parent = _rb(parent->parent);
                        }
                        _rb(parent)->color = color_black;
                        _rb(grand_parent)->color = color_red;
                        _left_rotate(grand_parent);
                    }
                }
            }
            static_cast<node_ptr>(this->_root())->color = color_black;
            return node;
        }

        void clear()
        {
            erase_iter(begin(), end());
        }

        iterator find (const key_type& k)
        {
            node_base_ptr parent;
            node_base_ptr node = find_unique_position(k, parent);
            return node ? iterator(node) : end();
        }

        const_iterator find (const key_type& k) const
        {
            node_base_ptr parent;
            node_base_ptr node = find_unique_position(k, parent);
            return node ? const_iterator(node) : end();
        }

        iterator lower_bound (const key_type& k)
        {

            node_base_ptr parent;
            node_base_ptr node = find_unique_position(k, parent);
            if (node || !_comp(key_of_value()(static_cast<node_ptr>(parent)->value), k))
                return iterator(parent);
            else
                return ++iterator(parent);
        }

    }; // class Tree

} // namespace ft_dev



