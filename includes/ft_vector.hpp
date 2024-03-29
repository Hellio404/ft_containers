// MIT License
// 
// Copyright (c) 2021 Youness Farini
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 

#pragma once
#include "ft_iterator_traits.hpp"
#include "ft_iterator.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_type_traits.hpp"
#include "ft_utils.hpp"
#include <memory>
#include <cstddef>
#include <limits>

namespace ft{

    // this is a vector base class that handles the allocation and deallocation
    // of memory, its very helpful method to prevent leaks when an exception occurred
    // on the vector main class
    template <typename _Tv, typename _Talloc = std::allocator<_Tv> >
    class _vector_base {
    private:
        typedef _Talloc                                         allocator_type;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        typedef size_t                                          size_type;

        struct Vector_data {
            pointer _begin;
            pointer _finish;
            pointer _end_of_storage;

            Vector_data(): _begin(0), _finish(0), _end_of_storage(0) {}

            Vector_data&    operator=(Vector_data const& obj)
            {
                _begin = obj._begin;
                _finish = obj._finish;
                _end_of_storage = obj._end_of_storage;
                return *this;
            }

            void _V_data_swap(Vector_data& obj)
            {
                Vector_data tmp = obj;
                obj = *this;
                *this = tmp;
            }
        };

        // this is just so we can join our allocator methods with  the struct Vector_data
        struct _base_data: public Vector_data, public allocator_type {
            _base_data(): Vector_data(), allocator_type()  {};
            _base_data(allocator_type const& _alloc): Vector_data(), allocator_type(_alloc)  {};
            ~_base_data() {};
            void    _replace_data(pointer start, pointer end, pointer end_of_storage)
            {
                size_type size = size_type(this->Vector_data::_end_of_storage - this->Vector_data::_begin);
                if (this->Vector_data::_begin)
                    this->allocator_type::deallocate(this->Vector_data::_begin, size);
                this->Vector_data::_begin = start;
                this->Vector_data::_finish = end;
                this->Vector_data::_end_of_storage = end_of_storage;
            }

            void    _replace_data(pointer start, pointer end, size_type capacity)
            {
                if (this->Vector_data::_begin)
                    this->allocator_type::deallocate(this->Vector_data::_begin,
                        size_type(this->Vector_data::_end_of_storage - this->Vector_data::_begin));
                this->Vector_data::_begin = start;
                this->Vector_data::_finish = end;
                this->Vector_data::_end_of_storage = start + capacity;
            }
        };

        pointer _allocate_storage(size_type n)
        {
            return n > 0 ? _data.allocate(n) : pointer(0);
        }


        void _init_storage(size_type n)
        {
            _data._begin =  _allocate_storage(n);
            _data._finish = _data._begin;
            _data._end_of_storage = _data._begin + n;
        }

         void    _deallocate_storage(pointer p, size_type n)
        {
            if (p)
                _data.deallocate(p, n);
        }
        
    public:
       
        _base_data _data;
        _base_data &_allocator;
        _vector_base(): _data(), _allocator(_data) {};
        _vector_base(allocator_type const& alloc): _data(alloc), _allocator(_data) {};
        _vector_base(size_type n, allocator_type const &alloc): _data(alloc), _allocator(_data)  { _init_storage(n); };

        ~_vector_base() 
        { 
            _deallocate_storage(_data._begin, size_type(_data._end_of_storage - _data._begin));
        };
    };


////////////////////////////////////////////////////////////////////////////////////
    template <typename _Tv, typename _Talloc = std::allocator<_Tv> >
    class vector: public _vector_base<_Tv, _Talloc> {
    private:
        typedef _vector_base<_Tv, _Talloc> _base_type;
    public:
        typedef _Tv value_type;
        typedef typename _Talloc::template rebind<value_type>::other allocator_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft_iterator<pointer, vector> iterator;
        typedef ft_iterator<const_pointer, vector> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator::difference_type difference_type;
        typedef size_t  size_type;

        using _base_type::_data;
        using _base_type::_allocator;

        explicit vector(const allocator_type &alloc = allocator_type())
            : _base_type(alloc) {}

        explicit vector(size_type n, const value_type &val = value_type(),
            const allocator_type &alloc = allocator_type()) : _base_type(_check_if_valid_size(n), alloc)
        {
            _data._finish = _fill_n_copy(_data._begin, n, val, _allocator);
        }

        template <class InputIterator >
        vector(InputIterator first, InputIterator last,
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, allocator_type>::type  
               const& alloc = allocator_type()): _base_type(alloc)
        {
            _dispatch_fill_range(first, last);
        }

        vector (const vector& x): _base_type(x.size(), x._allocator)
        {
            _data._finish = _range_copy(x.begin(), x.end(), _data._begin, _allocator);
            _data._end_of_storage = _data._begin + x.size();
        }

        ~vector() {
            ft::destroy(_data._begin, _data._finish, _data);
        }

         vector& operator= (const vector& x)
         {
            if (this != &x)
            {
                clear();
                _data._replace_data(pointer(0), pointer(0), size_type(0));
                _data._begin = _allocator.allocate(x.size());
                _data._end_of_storage = _data._begin + x.size();
                _data._finish = _range_copy(x.begin(), x.end(), _data._begin, _allocator);
            }
            return *this;
         }

        iterator begin() 
        { 
          return iterator(_data._begin); 
        }

        const_iterator begin() const 
        { 
            return const_iterator(_data._begin); 
            }

        iterator end()
        {
            return iterator(_data._finish);
        }

        const_iterator end() const
        {
            return const_iterator(_data._finish);
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }


        size_type max_size() const
        {
            size_type logical_maxSize = std::numeric_limits<size_type>::max() / sizeof(value_type);
            size_type allocator_maxSize = _allocator.max_size();
            return ft::min(logical_maxSize, allocator_maxSize);
        }

        bool empty() const
        {
            return (_data._begin == _data._finish);
        }

        reference operator[](size_type n)
        {
            return _data._begin[n];
        }

        const_reference operator[](size_type n) const
        {
            return _data._begin[n];
        }

        reference at(size_type n)
        {
            // this will throw out_of_range if n is invalid
            _check_if_valid_range(n);
            return (*this)[n];
        }

        const_reference at(size_type n) const
        {
            // this will throw out_of_range if n is invalid
            _check_if_valid_range(n);
            return (*this)[n];
        }

        reference front()
        {
            return (*this)[0];
        }
        
        const_reference front() const
        {
            return (*this)[0];
        }

        reference back()
        {
            return *(_data._finish - 1);
        }
        
        const_reference back() const
        {
            return *(_data._finish - 1);
        }

        size_type capacity() const
        {
            return size_type(_data._end_of_storage - _data._begin);
        }

        size_type size() const
        {
            return size_type(_data._finish - _data._begin);
        }

        void clear()
        {
            ft::destroy(_data._begin, _data._finish, _allocator);
            _data._finish = _data._begin;
        }

        void    push_back(const value_type &val)
        {
            if (_data._finish == _data._end_of_storage)
            {
               _reallocate_insert(end(), val);
            }
            else
            {
                _allocator.construct(_data._finish, val);
                ++_data._finish;
            }
        }

        void pop_back()
        {
            ft::destroy(_data._finish - 1, _data._finish, _allocator);
            _data._finish--;
        }

        void resize (size_type n, value_type val = value_type())
        {
            pointer expected_new_end = _data._begin + n;
            if (_data._finish > expected_new_end)
            {
                ft::destroy(expected_new_end, _data._finish, _allocator);
                _data._finish = expected_new_end;

            }
            else if (_data._end_of_storage >= expected_new_end)
                _data._finish = _fill_n_copy(_data._finish, n - size(), val, _allocator);
            else if (expected_new_end > _data._end_of_storage)
            {
                size_type to_allocate = _check_if_valid_len(n - size());
                pointer _p_begin_tmp = _allocator.allocate(to_allocate);
                pointer _p_finish_tmp = _p_begin_tmp;
                try
                {
                    _p_finish_tmp = _range_copy(_data._begin, _data._finish, _p_begin_tmp, _allocator);
                    _p_finish_tmp = _fill_n_copy(
                        _p_finish_tmp,
                        n - size(),
                        val,
                        _allocator
                    );
                }
                catch(...)
                {
                    ft::destroy(_p_begin_tmp, _p_finish_tmp, _allocator);
                    _allocator.deallocate(_p_begin_tmp, to_allocate);
                    throw ;
                }
                ft::destroy(_data._begin, _data._finish, _allocator);
                _data._replace_data(_p_begin_tmp, _p_finish_tmp, to_allocate);
            }
        }

        void reserve(size_type n)
        {
            if (n > capacity())
            {
                size_type len =_check_if_valid_size(n);
                pointer _p_first_tmp = _allocator.allocate(len);
                pointer _p_last_tmp;
                try
                {
                    _p_last_tmp = _range_copy(_data._begin, _data._finish, _p_first_tmp, _allocator);
                }
                catch(...)
                {
                    _allocator.deallocate(_p_first_tmp, len);
                    return ;
                }
                
                ft::destroy(_data._begin, _data._finish, _allocator);
                _data._replace_data(_p_first_tmp, _p_last_tmp, n);
            }
        }

        template <class InputIterator>
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type  // void
        assign (InputIterator first, InputIterator last)
        {
            _dispatch_fill_range(first, last);
        }

        void assign (size_type n, const value_type& val)
        {
            if (n > capacity())
            {
                // this so I can allocate max(n, 2 * capacity());
                size_type to_allocate =_check_if_valid_len(size_type(n - capacity()));
                pointer _p_begin_tmp = _allocator.allocate(to_allocate);
                pointer _p_finish_tmp = _p_begin_tmp;
                try
                {
                    _p_finish_tmp = _fill_n_copy(_p_begin_tmp, n, val, _allocator);
                }
                catch(...)
                {
                    _allocator.deallocate(_p_begin_tmp, to_allocate);
                    throw ;
                }
                ft::destroy(_data._begin, _data._finish, _allocator);
                _data._replace_data(_p_begin_tmp, _p_finish_tmp, to_allocate);
            }
            else
            {
                ft::destroy(_data._begin, _data._finish, _allocator);
                _data._finish = _data._begin;
                _data._finish = _fill_n_copy(_data._begin, n, val, _allocator);
            }
        }

        iterator erase (iterator position)
        {
            iterator position_tmp = position;
            pointer _p_pos_tmp = position.base();
            while (_p_pos_tmp + 1 != _data._finish)
            {
                *_p_pos_tmp = *(_p_pos_tmp + 1);
                ++_p_pos_tmp;
            }
            pop_back();
            return position_tmp;
        }

        iterator erase (iterator first, iterator last)
        {
            iterator position_tmp = first;

            difference_type n = last - first;
            while (last != end())
            {
                *first = *last;
                ++first;
                ++last;
            }
            ft::destroy(first, first + n, _allocator);
            _data._finish -= n;
            return position_tmp;
        }

        template <typename ForwardIterator>
        void _do_insert_range(iterator position, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
        {
            size_type n = ft::distance(first, last);
            if (n > 0)
            {
                pointer pos = position.base();

                if (_data._finish + n > _data._end_of_storage)
                {
                    size_type _len = _check_if_valid_len(n);

                    pointer _new_begin = _allocator.allocate(_len);
                    pointer _current = _new_begin;
                    try
                    {
                        _current = _range_copy(_data._begin, pos, _new_begin, _allocator);
                        _current = _range_copy(first, last, _current, _allocator);
                        _current = _range_copy(pos, _data._finish, _current, _allocator);
                        ft::destroy(begin(), end(), _allocator);
                        _data._replace_data(_new_begin, _current, _len);
                    }
                    catch(...)
                    {
                        ft::destroy(_new_begin, _current, _allocator);
                        _allocator.deallocate(_new_begin, _len);
                        throw ;
                    }
                }
                else
                {
                    if (pos + n <= _data._finish)
                    {
                        pointer _p_tmp = _data._finish - n;
                        pointer _old_finish = _data._finish ;
                        _data._finish = _range_copy(_p_tmp, _data._finish, _data._finish, _allocator);
                        --_p_tmp;
                        while (_p_tmp != pos -1)
                            *--_old_finish = *_p_tmp--;
                        pointer pos_tmp = pos + n;
                        while (pos != pos_tmp)
                            *pos++ = *first++;
                    }
                    else
                    {
                        pointer old_end = _data._finish;
                        difference_type n_back = pos + n - _data._finish;
                        ForwardIterator tmp = first;
                        for (size_type i = 0; i < n - size_type(n_back); i++)
                            tmp++;
                        _data._finish = _range_copy(tmp, last, _data._finish, _allocator);
                        _data._finish = _range_copy(pos, old_end, _data._finish, _allocator);
                        pointer pos_tmp = pos + n - n_back;
                        while (pos != pos_tmp)
                            *pos++ = *first++;
                    }
                }
            }
        }

        template <typename InputIterator>
        void _do_insert_range(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
        {

            vector tmp(first, last, _allocator);
            insert(position, tmp.begin(), tmp.end());
        }


        template <typename InputIterator>
        void insert (iterator position, InputIterator first, 
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
        {
            _do_insert_range(position, first, last, get_iterator_category<InputIterator>());
        }

        iterator insert (iterator position, const value_type& val)
        {
            difference_type dist = ft::distance(begin(), position);
            insert(position, 1, val);
            return begin() + dist;
        }

        void insert (iterator position, size_type n, const value_type& val)
        {
            value_type copy_val = val;
            if (n > 0)
            {
                if (_data._finish + n > _data._end_of_storage)
                    _reallocate_insert(position, copy_val, n);
                else
                {
                    pointer pos = position.base();
              
                    if (pos + n <= _data._finish)
                    {
                        pointer _p_tmp = _data._finish - n;
                        pointer _old_finish = _data._finish ;
                        _data._finish = _range_copy(_p_tmp, _data._finish, _data._finish, _allocator);
                        --_p_tmp;
                        while (_p_tmp != pos -1)
                            *--_old_finish = *_p_tmp--;
                        pointer pos_tmp = pos + n;
                        while (pos != pos_tmp)
                        {
                            *pos = copy_val;
                            ++pos;
                        }
                    }
                    else
                    {
                        pointer old_end = _data._finish;
                        difference_type n_back = pos + n - _data._finish;
                        _data._finish = _fill_n_copy(_data._finish, n_back, copy_val, _allocator);
                        _data._finish = _range_copy(pos, old_end, _data._finish, _allocator);
                        pointer pos_tmp = pos + n - n_back;
                        while (pos != pos_tmp)
                        {
                            *pos = copy_val;
                            ++pos;
                        }
                    }

                }
            }
        }

        

        void swap (vector& x)
        {
            _data._V_data_swap(x._data);
        }


        allocator_type get_allocator() const
        {
            return _allocator;
        }
    private:
        void _check_if_valid_range(size_type n) const
        {
            if (n >= size())
                throw std::out_of_range("ft::vector index is out of range");
        }

        size_type _check_if_valid_len(size_type n)
        {
            _check_if_valid_size(capacity() + n);
            size_type len = capacity() + ft::max(capacity(), n);
            return (len < capacity() || len > max_size()) ? max_size() : len;
        }

        size_type _check_if_valid_size(size_type n)
        {
            if (max_size() < n)
                throw std::length_error("cannot create ft::vector larger than max_size()");
            return n;
        }

        template <class InputIterator >
        void    _do_fill_range(InputIterator start, InputIterator end, false_type)
        {
            ft::destroy(_data._begin, _data._finish, _allocator);
            _data._finish = _data._begin;
            if (_data._begin)
            {
                _allocator.deallocate(_data._begin, capacity());
                _data._end_of_storage = _data._begin;
            }
            try
            {
                while (start != end)
                {
                    push_back(*start);
                    ++start;       
                }
            }
            catch(...)
            {
                ft::destroy(_data._begin, _data._finish, _allocator);
                throw ;
            }
            
        }

        template <class ForwardIterator >
        void    _do_fill_range(ForwardIterator start, ForwardIterator end, true_type)
        {
            difference_type len = ft::distance(start, end);

            ft::destroy(_data._begin, _data._finish, _allocator);
            _data._finish = _data._begin;

            if (size_type(len) > capacity())
            {
                if (_data._begin)
                {
                    _allocator.deallocate(_data._begin, capacity());
                    _data._end_of_storage = _data._begin;
                }
                _data._begin = _allocator.allocate(_check_if_valid_size(len));
                _data._end_of_storage = _data._begin + len;
            }
            _data._finish = ft::_range_copy(start, end, _data._begin, _allocator);  
        }

        template <class InputIterator >
        void    _dispatch_fill_range(InputIterator start, InputIterator end)
        {
            _do_fill_range<InputIterator>(start, end, 
                ft::iterator_from_category<InputIterator, std::forward_iterator_tag>() );
        }

        void
        _reallocate_insert(iterator _pos, value_type const& val, size_type n = 1)
        {
            pointer pos = _pos.base();
            size_type _len = _check_if_valid_len(n);

            pointer _new_begin = _allocator.allocate(_len);
            pointer _current = _new_begin;
            try
            {
                _current = _range_copy(_data._begin, pos, _new_begin, _allocator);
                _current = _fill_n_copy(_current, n, val, _allocator);
                _current = _range_copy(pos, _data._finish, _current, _allocator);
                ft::destroy(begin(), end(), _allocator);
                _data._replace_data(_new_begin, _current, _len);
            }
            catch(...)
            {
                ft::destroy(_new_begin, _current, _allocator);
                _allocator.deallocate(_new_begin, _len);
                throw ;
            }
        }


        

    };

    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }
    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(rhs < lhs);

    }
    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return rhs < lhs;
    }
    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
}



namespace std {
    template <class T, class Alloc>
    void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
    {
        x.swap(y);
    }
    
}

