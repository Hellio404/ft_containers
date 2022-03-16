#pragma once

#include "ft_iterator_traits.hpp"
#include "ft_type_traits.hpp"
#include <cstddef>

namespace ft
{

    template <typename _Titerator, typename _Tcontainer>
    class ft_iterator
    {

        typedef iterator_traits<_Titerator> _iterator_trait;

        _Titerator it;

    public:
        typedef _Titerator iterator_type;
        typedef typename _iterator_trait::value_type        value_type;
        typedef typename _iterator_trait::iterator_category iterator_category;
        typedef typename _iterator_trait::difference_type   difference_type;
        typedef typename _iterator_trait::pointer           pointer;
        typedef typename _iterator_trait::reference         reference;

        ft_iterator() : it(){};
        ft_iterator(iterator_type const &iter) : it(iter){};

        template <typename _TIter>
        ft_iterator(ft_iterator<_TIter, _Tcontainer> const &obj) : it(obj.base()){};

        reference operator*() const { return *it; }

        pointer operator->() const { return it; }

        ft_iterator &operator++() { ++this->it; return *this; }
        ft_iterator operator++(int) { return ft_iterator(it++); }
        ft_iterator &operator--() { --this->it; return *this; }
        ft_iterator operator--(int) { return ft_iterator(it--); }

        ft_iterator operator+(difference_type n) const { return ft_iterator(it + n); }
        ft_iterator operator-(difference_type n) const { return ft_iterator(it - n); }
        ft_iterator &operator+=(difference_type n) { this->it += n; return *this; }
        ft_iterator &operator-=(difference_type n) { this->it -= n; return *this; }

        reference operator[](difference_type n) const { return it[n]; }

        const  _Titerator& base() const { return it; }
    };

    template <typename _T1, typename _T2, typename _Tcontainer>
    bool operator==(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    { return lhs.base() == rhs.base(); }

    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator!=(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    { return lhs.base() != rhs.base(); }

    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator>(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    { return lhs.base() > rhs.base(); }

    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator<(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    { return lhs.base() < rhs.base(); }

    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator>=(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    { return lhs.base() >= rhs.base(); }


    template <typename _T1, typename _T2, typename _Tcontainer>
    bool    operator<=(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    { return lhs.base() <= rhs.base(); }


    template <typename _T1, typename _T2, typename _Tcontainer>
    typename ft_iterator<_T1, _Tcontainer>::difference_type
    operator-(const ft_iterator<_T1, _Tcontainer>& lhs, const ft_iterator<_T2, _Tcontainer>& rhs)
    { return lhs.base() - rhs.base(); }

    template <typename _T1, typename _Tcontainer>
    ft_iterator<_T1, _Tcontainer>
    operator+(typename ft_iterator<_T1, _Tcontainer>::difference_type n, const ft_iterator<_T1, _Tcontainer>& rhs)
    {  return rhs + n; }
} // namespace ft

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

        reference operator*() const { _Titerator tmp = it; return *--tmp; }
        pointer operator->() const { return &(operator*()); }

        reverse_iterator &operator++() { --this->it; return *this; }
        reverse_iterator operator++(int){ return reverse_iterator(it--); }
        reverse_iterator &operator--() { ++this->it; return *this; }
        reverse_iterator operator--(int) { return reverse_iterator(it++); }


        reverse_iterator operator+(difference_type n) const
        { return reverse_iterator(it - n); }
        reverse_iterator operator-(difference_type n) const
        {  return reverse_iterator(it + n); }
        reverse_iterator &operator+=(difference_type n)
        { this->it -= n;  return *this; }
        reverse_iterator &operator-=(difference_type n)
        { this->it += n; return *this; }

        reference operator[](difference_type n) const
        { return *(*this + n); }

        const  _Titerator& base() const { return it; }
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
        return rhs.base() - lhs.base();
    }


    template <typename _T1>
    reverse_iterator<_T1>
    operator+(typename reverse_iterator<_T1>::difference_type n, const reverse_iterator<_T1>& rhs)
    { return rhs + n; }

}
