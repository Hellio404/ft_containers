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
namespace ft
{

    template <class T>
    T *address_of(T const &ptr)
    {
        return reinterpret_cast<T *>(
            &const_cast<char &>(
                reinterpret_cast<const volatile char &>(ptr)));
    }

    template <typename _TForwardIterator, typename _TAlloc>
    void destroy(_TForwardIterator start, _TForwardIterator end, _TAlloc &alloc)
    {

        for (; start != end; start++)
            alloc.destroy(address_of(*start));
    }

    template <typename _Alloc, typename _TForwardIterator, typename _Tc>
    _TForwardIterator
    _fill_n_copy(_TForwardIterator start, size_t n, _Tc &copy, _Alloc &allocator)
    {
        _TForwardIterator cur = start;
        try
        {
            for (; n > 0; --n, ++cur)
                allocator.construct(address_of(*cur), copy);
        }
        catch (...)
        {
            ft::destroy(start, cur, allocator);
            throw;
        }
        return cur;
    }

    template <typename _Alloc, typename _TForwardIterator, typename _TInputIterator>
    _TForwardIterator
    _range_copy(
        _TInputIterator start,
        _TInputIterator end,
        _TForwardIterator destination,
        _Alloc &allocator)
    {
        _TForwardIterator cur = destination;
        try
        {
            for (; start != end; start++, ++cur)
                allocator.construct(address_of(*cur), *address_of(*start));
        }
        catch (...)
        {
            ft::destroy(destination, cur, allocator);
            throw;
        }
        return cur;
    }

    template <typename _InputIterator>
    typename ft::iterator_traits<_InputIterator>::difference_type
    _do_distance(_InputIterator start, _InputIterator end, std::input_iterator_tag)
    {
        typename ft::iterator_traits<_InputIterator>::difference_type res = 0;
        while (start != end)
        {
            ++res;
            ++start;
        }
        return res;
    }

    template <typename _RandomAccessIterator>
    typename ft::iterator_traits<_RandomAccessIterator>::difference_type
    _do_distance(_RandomAccessIterator start, _RandomAccessIterator end, std::random_access_iterator_tag)
    {
        return end - start;
    }

    template <typename _InputIterator>
    typename ft::iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator start, _InputIterator end)
    {
        return (
            ft::_do_distance(start, end, get_iterator_category<_InputIterator>())
        );
    }


    template <typename T>
    void swap(T &a, T &b)
    {
        T c;

        c = a;
        a = b;
        b = c;
    }
    template <typename T>
    T min(T const &a, T const &b)
    {
        return a > b ? b : a;
    }

    template <typename T>
    T max(T const &a, T const &b)
    {
        return a < b ? b : a;
    }


    template <typename T>
    struct  select1st {
        typedef T                       argument_type;
        typedef typename T::first_type  result_type;

        result_type operator()(T const &t) const
        {
            return t.first;
        }

        const result_type &operator()(T const &t)
        {
            return t.first;
        }
    };

    template <typename T>
    struct  select2nd {
        typedef T                       argument_type;
        typedef typename T::second_type  result_type;

        result_type operator()(T const &t) const
        {
            return t.second;
        }

        const result_type &operator()(T const &t)
        {
            return t.second;
        }
    };

    template <typename T>
    struct select_self {
        typedef T                       argument_type;
        typedef T                       result_type;

        result_type operator()(T const &t) const
        {
            return t;
        }

        const result_type &operator()(T const &t)
        {
            return t;
        }
    };
    
}
