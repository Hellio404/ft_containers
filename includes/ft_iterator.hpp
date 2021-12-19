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

    template <typename _Titerator, typename _Tcontainer, typename = typename ft::enable_if<ft::is_pointer<_Titerator>::value>::type>
    class ft_iterator
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

        ft_iterator() : it(){};
        ft_iterator(iterator_type const &iter) : it(iter){};

        ft_iterator(ft_iterator<_Titerator, _Tcontainer> const &obj) : it(obj.it){};

        ft_iterator &operator=(ft_iterator const &obj)
        {
            this->it = obj.it;
            return *this;
        }

        reference operator*() const
        {
            return *it;
        }

        pointer operator->() const
        {
            return it;
        }

        ft_iterator &operator++()
        {
            ++this->it;
            return *this;
        }

        ft_iterator operator++(int)
        {
            return ft_iterator(it++);
        }

        ft_iterator &operator--()
        {
            --this->it;
            return *this;
        }

        ft_iterator operator--(int)
        {
            return ft_iterator(it--);
        }


        ft_iterator operator+(difference_type n)
        {
            return ft_iterator(it + n);
        }


        ft_iterator operator-(difference_type n)
        {
            return ft_iterator(it - n);
        }

        ft_iterator &operator+=(difference_type n)
        {
            this->it += n;
            return *this;
        }

        ft_iterator &operator-=(difference_type n)
        {
            this->it -= n;
            return *this;
        }

        reference operator[](difference_type n) const
        {
            return it[n];
        }

        const  _Titerator& base() const
        {
            return it;
        }
    };

    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator==(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator!=(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator>(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator<(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator>=(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    {
        return lhs.base() >= rhs.base();
    }


    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator<=(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    {
        return lhs.base() <= rhs.base();
    }


    template <typename _T1, typename _T2, typename _Tcontainer>
    typename ft_iterator<_T1, _Tcontainer>::difference_type
    operator-(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    {
        return lhs.base() - rhs.base();
    }


    template <typename _T1, typename _Tcontainer>
    ft_iterator<_T1, _Tcontainer>   operator+(typename ft_iterator<_T1, _Tcontainer>::difference_type n, ft_iterator<_T1, _Tcontainer>& rhs)
    {
        return rhs + n;
    }


}
