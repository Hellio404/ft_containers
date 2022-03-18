#pragma once
#include "ft_tree.hpp"
#include "ft_utils.hpp"

namespace ft
{

    template <class Key,                                          
              class Compare = std::less<Key>,                     
              class Alloc = std::allocator<Key >
              >
    class set
    {

    public:
        

        typedef Key                                                     key_type;
        typedef key_type                                                value_type;
        typedef Compare                                                 key_compare;
        typedef Alloc                                                   allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef tree_const_iterator<value_type>                         iterator;
        typedef tree_const_iterator<value_type>                         const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type     difference_type;
        typedef size_t                                                  size_type;

        typedef key_compare                                             value_compare;

    protected:
        typedef ft::Tree<value_type, ft::select_self<value_type>, key_type, value_type, key_compare, allocator_type> rb_tree;
        rb_tree _tree;

    public:
        explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) {}

        template <class InputIterator>
        set(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : _tree(comp, alloc)
        {
            while (first != last)
            {
                this->insert(*first);
                ++first;
            }
        }

        set(const set &x) : _tree(x._tree) {}


        ~set() {}

        set &operator=(const set &x)
        {
            _tree = x._tree;
            return *this;
        }


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

        pair<iterator, bool> insert(const value_type &val)
        {
            ft::pair<typename rb_tree::iterator, bool> ret = _tree.insert_uniq(val);
            return pair<iterator, bool>(iterator(ret.first), ret.second);
        }

        iterator insert(iterator , const value_type &val)
        {
            // todo use the hint position
            ft::pair<typename rb_tree::iterator, bool> ret = _tree.insert_uniq(val);
            return iterator(ret.first);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                this->insert(*first);
                ++first;
            }
        }

        void erase(iterator position)
        {
            _tree.erase_iter(position);
        }

        size_type erase(const key_type &k)
        {
            return _tree.erase_uniq(k);
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                iterator tmp = first;
                tmp++;
                _tree.erase_iter(first);
                first = tmp;
            }
        }

        void clear()
        {
            _tree.clear();
        }

        iterator find(const key_type &k)
        {
            return iterator(_tree.find(k));
        }

        const_iterator find(const key_type &k) const
        {
            return const_iterator(_tree.find(k));
        }

        iterator lower_bound(const key_type &k)
        {
            return iterator(_tree.lower_bound(k));
        }

        const_iterator lower_bound(const key_type &k) const
        {
            return const_iterator(_tree.lower_bound(k));
        }

        iterator upper_bound(const key_type &k)
        {
            return iterator(_tree.upper_bound(k));
        }

        const_iterator upper_bound(const key_type &k) const
        {
            return const_iterator(_tree.upper_bound(k));
        }

        pair<iterator, iterator> equal_range(const key_type &k)
        {
            ft::pair<typename rb_tree::iterator, typename rb_tree::iterator> ret = _tree.equal_range(k);
            return pair<iterator, iterator>(iterator(ret.first), iterator(ret.second));
        }

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            ft::pair<typename rb_tree::const_iterator, typename rb_tree::const_iterator> ret = _tree.equal_range(k);
            return pair<const_iterator, const_iterator>(const_iterator(ret.first), const_iterator(ret.second));
        }

        size_type count(const key_type &k) const
        {
            return _tree.count(k);
        }

        value_compare value_comp() const
        {
            return value_compare(_tree._comp);
        }

        key_compare key_comp() const
        {
            return _tree._comp;
        }

        allocator_type get_allocator() const
        {
            return _tree.get_allocator();
        }

        void swap(set &x)
        {
            _tree.swap(x._tree);
        }
        
        template <class _Key, class _Compare, class _Alloc>
        friend bool operator==(const set<_Key, _Compare, _Alloc> &, const set<_Key, _Compare, _Alloc> &);

        template <class _Key, class _Compare, class _Alloc>
        friend bool operator<(const set<_Key, _Compare, _Alloc> &, const set<_Key, _Compare, _Alloc> &);

        template <class _Key, class _Compare, class _Alloc>
        friend bool operator!=(const set<_Key, _Compare, _Alloc> &, const set<_Key, _Compare, _Alloc> &);

        template <class _Key, class _Compare, class _Alloc>
        friend bool operator>(const set<_Key, _Compare, _Alloc> &, const set<_Key, _Compare, _Alloc> &);

        template <class _Key, class _Compare, class _Alloc>
        friend bool operator>=(const set<_Key, _Compare, _Alloc> &, const set<_Key, _Compare, _Alloc> &);

        template <class _Key, class _Compare, class _Alloc>
        friend bool operator<=(const set<_Key, _Compare, _Alloc> &, const set<_Key, _Compare, _Alloc> &);

    };

    template <class Key, class Compare, class Alloc>
    bool operator==(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
    {
        return x._tree == y._tree;
    }

    template <class Key, class Compare, class Alloc>
    bool operator<(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
    {
        return x._tree < y._tree;
    }

    template <class Key, class Compare, class Alloc>
    bool operator!=(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
    {
        return x._tree != y._tree;
    }

    template <class Key, class Compare, class Alloc>
    bool operator>(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
    {
        return x._tree > y._tree;
    }

    template <class Key, class Compare, class Alloc>
    bool operator>=(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
    {
        return x._tree >= y._tree;
    }

    template <class Key, class Compare, class Alloc>
    bool operator<=(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
    {
        return x._tree <= y._tree;
    }


} // namespace ft

namespace std
{
    template <class Key, class Compare, class Alloc>
    void swap(ft::set<Key, Compare, Alloc> &x, ft::set<Key, Compare, Alloc> &y)
    {
        x.swap(y);
    }
} // namespace std