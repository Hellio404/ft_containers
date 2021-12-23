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
#include <ft_iterator_traits.hpp>
#include <ft_iterator.hpp>
#include <ft_reverse_iterator.hpp>
#include <ft_type_traits.hpp>
#include <ft_utils.hpp>
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
        typedef typename _Talloc::template rebind<_Tv>::other   allocator_type;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        typedef size_t                                          size_type;

        struct Vector_data {
            pointer _begin;
            pointer _finish;
            pointer _end_of_storage;

            Vector_data(): _begin(), _finish(), _end_of_storage() {}

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
                this->allocator_type::deallocate(this->Vector_data::_begin,
                    size_type(this->Vector_data::_end_of_storage - this->Vector_data::_begin));
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
            return n > 0 ? _data.allocate(n) : pointer();
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
        typedef typename _Talloc::template rebind<_Tv>::other allocator_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft_iterator<pointer, vector> iterator;
        typedef ft_iterator<const_pointer, vector> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator::difference_type difference_type;
        typedef size_t size_type;

        using _base_type::_data;
        using _base_type::_allocator;

        explicit vector(const allocator_type &alloc = allocator_type())
            : _base_type(alloc) {}

        explicit vector(size_type n, const value_type &val = value_type(),
            const allocator_type &alloc = allocator_type()) : _base_type(_check_if_valid_size(n), alloc)
        {
            _data._finish = _fill_n_copy<allocator_type>(_data._begin, n, val, _allocator);
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
                _data._replace_data(pointer(), pointer(), size_type(0));
                _data._begin = x._allocator.allocate(x.size());
                _data._finish = _range_copy(x.begin(), x.end(), _data._begin, _allocator);
                _data._end_of_storage = _data._begin + x.size();
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
            return const_iterator(const_pointer(_data._finish));
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
            size_type logical_maxSize = std::numeric_limits<size_type>::max() / sizeof(_Tv);
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
            return size_type(_data._finish- _data._begin);
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
        void assign (InputIterator first, InputIterator last)
        {
            
        }

        void assign (size_type n, const value_type& val);

    private:
        void _check_if_valid_range(size_type n)
        {
            if (n >= size())
                throw std::out_of_range("ft::vector index is out of range");
        }

        size_type _check_if_valid_len(size_type n)
        {
            _check_if_valid_size(size() + n);
            size_type len = size() + ft::max(size(), n);
            return (len < size() || len > max_size()) ? max_size() : len;
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
            difference_type len = std::distance(start, end);
            _data._begin = _allocator.allocate(_check_if_valid_size(len));
            _data._end_of_storage = _data._begin + len;
            _data._finish = ft::_range_copy(start, end, _data._begin, _allocator);  
        }

        template <class InputIterator >
        void    _dispatch_fill_range(InputIterator start, InputIterator end)
        {
            _do_fill_range<InputIterator>(start, end, 
                ft::iterator_from_category<InputIterator, std::forward_iterator_tag>() );
        }

        void
        _reallocate_insert(iterator _pos, _Tv const& val)
        {
            pointer pos = ft::address_of(*_pos);
            size_type _len = _check_if_valid_len(1);

            pointer _new_begin = _allocator.allocate(_len);
            pointer _current = _new_begin;
            try
            {
                _current = _range_copy(_data._begin, pos, _new_begin, _allocator);
                _allocator.construct(ft::address_of(*_current), val);
                ++_current;
                _current = _range_copy(pos, _data._finish, _current, _allocator);
                ft::destroy(begin(), end(), _allocator);
                _data._replace_data(_new_begin, _current, _len);
            }
            catch(...)
            {
                ft::destroy(_new_begin, _current, _allocator);
                _allocator.deallocate(_new_begin, _len);
            }
        }


        

    };
}
