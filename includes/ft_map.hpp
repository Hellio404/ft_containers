#pragma once
#include "ft_tree.hpp"
#include "ft_utils.hpp"

namespace ft
{


    template <typename _iterator>
    class map_iterator: public _iterator
    {
        public:
        map_iterator(const _iterator& it): _iterator(it) {}
    };


    template <class Key,                                        // map::key_type
              class T,                                          // map::mapped_type
              class Compare = std::less<Key>,                        // map::key_compare
              class Alloc = std::allocator<ft::pair<const Key, T> >  // map::allocator_type
              >
    class map 
    {

    public:
        typedef Key                                                 key_type;
        typedef T                                                   mapped_type;
        typedef ft::pair<const key_type, mapped_type>               value_type;
        typedef Compare                                             key_compare;

        // struct  value_compare
        // {
        //     bool operator()(const value_type& lhs, const value_type& rhs) const
        //     {
        //         return key_compare()(lhs.first, rhs.first);
        //     }
        // };

        typedef Alloc                                                   allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef map_iterator<tree_iterator<value_type> >                iterator;
        typedef map_iterator<tree_const_iterator<value_type> >          const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
        typedef typename allocator_type::difference_type                difference_type; 
        typedef typename allocator_type::size_type                      size_type; 

    protected:
        typedef ft::Tree<value_type, ft::select1st<value_type> , key_type, value_type, key_compare, allocator_type> rb_tree;
        rb_tree _tree;
        
    public:
        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc) {}

        template <class InputIterator>
        map (InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()): _tree(comp, alloc)
        {
            while (first != last)
            {
                this->insert(*first);
                ++first;
            }
        }

        map (const map& x): _tree(x._tree) {}


        iterator begin()
        {
            return iterator(_tree.begin());
        }

        const_iterator begin() const
        {
            return const_iterator(_tree.begin());
        }

        iterator end()
        {
            return iterator(_tree.end());
        }

        const_iterator end() const
        {
            return const_iterator(_tree.end());
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(_tree.rbegin());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(_tree.rbegin());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(_tree.rend());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(_tree.rend());
        }

        bool empty() const
        {
            return _tree.empty();
        }

        size_type size() const
        {
            return _tree.size();
        }

        size_type max_size() const
        {
            return _tree.max_size();
        }


        mapped_type& operator[] (const key_type& k)
        {
            return _tree.insert_uniq(value_type(k, mapped_type())).first->second;
        }


        pair<iterator,bool> insert (const value_type& val)
        {
            ft::pair<typename rb_tree::iterator, bool> ret = _tree.insert_uniq(val);
            return pair<iterator, bool>(iterator(ret.first), ret.second);
        }

        iterator insert (iterator position, const value_type& val)
        {
            // todo use the hint position
            ft::pair<typename rb_tree::iterator, bool> ret = _tree.insert_uniq(val);
            return iterator(ret.first);
        }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                this->insert(*first);
                ++first;
            }
        }

        

        void clear()
        {
            _tree.clear();
        }

        iterator find (const key_type& k)
        {
            return iterator(_tree.find(k));
        }

        const_iterator find (const key_type& k) const
        {
            return const_iterator(_tree.find(k));
        }

        iterator lower_bound (const key_type& k)
        {
            return iterator(_tree.lower_bound(k));
        }

        const_iterator lower_bound (const key_type& k) const
        {
            return const_iterator(_tree.lower_bound(k));
        }

    };
} // namespace ft