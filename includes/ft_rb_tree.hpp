#pragma once
#include "ft_iterator_traits.hpp"
#include "ft_iterator.hpp"
#include "ft_type_traits.hpp"
#include "ft_utils.hpp"
#include "ft_pair.hpp"
#include "tree.hpp"
#include <memory>
#include <cstddef>
#include <limits>
#include <cstring>
#include <iostream>

namespace ft
{
    struct tree_node_base;
    template <typename _T>
    struct tree_node;

    template <typename T,
              typename NodeType,
              typename KeyOf,
              typename Compare,
              typename Alloc >
    class Tree;

    

    template <typename _T, typename KeyOf, typename _Compare = std::less<_T>, typename _Alloc = std::allocator<_T> >
    class rb_tree: public Tree<_T, rbtree_node<_T>, KeyOf, _Compare, _Alloc>
    {
    public:
        typedef  _Alloc                                                     allocator_type;
        typedef typename _Alloc::template rebind<tree_node<_T> >::other     node_allocator_type;
        typedef rbtree_node<_T>                                             rbnode_type;
        typedef rbtree_node<_T>*                                            rbnode_ptr;
        typedef rbtree_node<_T>                                              node_type;
        typedef node_type*                                                  node_ptr;
        typedef tree_node_base*                                             base_ptr;
        typedef _Compare                                                    compare_func;
        typedef _T                                                          value_type;
        typedef _T&                                                         reference;
        typedef _T*                                                         pointer;
        typedef tree_node_base*                                             node_base_ptr;

       

        
        

        

    };
} // namespace ft