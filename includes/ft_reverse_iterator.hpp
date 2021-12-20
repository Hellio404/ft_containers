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
#include <ft_type_traits.hpp>
#include <cstddef>
namespace ft
{

    template <typename _Titerator>
    class reverse_iterator
    {

        typedef iterator_traits<_Titerator> _iterator_trait;

        _Titerator it;

    public:
        typedef _Titerator iterator_type;
        typedef typename _iterator_trait::value_type value_type;
        typedef typename _iterator_trait::iterator_category iterator_category;
        typedef typename _iterator_trait::difference_type difference_type;
        typedef typename _iterator_trait::pointer pointer;
        typedef typename _iterator_trait::reference reference;

        reverse_iterator() : it(){};
        reverse_iterator(iterator_type const &iter) : it(iter){};

        template <typename _Titer>
        reverse_iterator(reverse_iterator<_Titer> const &obj) : it(obj.base()){};

        reverse_iterator &operator=(reverse_iterator<_Titerator> const &obj)
        {
            this->it = obj.it;
            return *this;
        }

        reference operator*() const
        {
            _Titerator tmp = it;
            return *--tmp;
        }

        pointer operator->() const
        {
            _Titerator tmp = _Titerator(it);
            return (--tmp).operator->();
        }

        reverse_iterator &operator++()
        {
            --this->it;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            return reverse_iterator(it--);
        }

        reverse_iterator &operator--()
        {
            ++this->it;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            return reverse_iterator(it++);
        }


        reverse_iterator operator+(difference_type n)
        {
            return reverse_iterator(it - n);
        }


        reverse_iterator operator-(difference_type n)
        {
            return reverse_iterator(it + n);
        }

        reverse_iterator &operator+=(difference_type n)
        {
            this->it -= n;
            return *this;
        }

        reverse_iterator &operator-=(difference_type n)
        {
            this->it += n;
            return *this;
        }

        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }

        const  _Titerator& base() const
        {
            return it;
        }
    };

    template <typename _T1, typename _T2>
    bool    operator==(const reverse_iterator<_T1>& lhs, const reverse_iterator<_T2>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename _T1, typename _T2>
    bool    operator!=(const reverse_iterator<_T1>& lhs, const reverse_iterator<_T2>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename _T1, typename _T2>
    bool    operator>(const reverse_iterator<_T1>& lhs, const reverse_iterator<_T2>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename _T1, typename _T2>
    bool    operator<(const reverse_iterator<_T1>& lhs, const reverse_iterator<_T2>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename _T1, typename _T2>
    bool    operator>=(const reverse_iterator<_T1>& lhs, const reverse_iterator<_T2>& rhs)
    {
        return lhs.base() <= rhs.base();
    }


    template <typename _T1, typename _T2>
    bool    operator<=(const reverse_iterator<_T1>& lhs, const reverse_iterator<_T2>& rhs)
    {
        return lhs.base() >= rhs.base();
    }


    template <typename _T1, typename _T2>
    typename reverse_iterator<_T1>::difference_type
    operator-(const reverse_iterator<_T1>& lhs, const reverse_iterator<_T2>& rhs)
    {
        return lhs.base() - rhs.base();
    }


    template <typename _T1, typename _T2>
    reverse_iterator<_T1>   operator+(typename reverse_iterator<_T1>::difference_type n, reverse_iterator<_T2>& rhs)
    {
        return rhs + n;
    }


}
