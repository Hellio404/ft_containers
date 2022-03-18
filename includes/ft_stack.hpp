#pragma once
#include "ft_vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> > class stack
    {
        public:
            typedef  T                              value_type;
            typedef  Container                      container_type;
            typedef typename Container::size_type   size_type;

        protected:
            container_type c;
        public:
            explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}
            ~stack () {}


            stack &operator=(stack const &other) { c = other.c; return *this; }

            void push(T const &val) { c.push_back(val); }
            void pop() { c.pop_back(); }
            const value_type &top() const { return c.back(); }
            value_type& top() { return c.back(); }
            bool empty() const { return c.empty(); }
            size_type size() const { return c.size(); }


            template <class _T, class _Container>
            friend bool operator==(stack<_T, _Container> const &lhs, stack<_T, _Container> const &rhs);
            template <class _T, class _Container>
            friend bool operator<(stack<_T, _Container> const &lhs, stack<_T, _Container> const &rhs);
    };

    template <class T, class Container>
    bool operator==(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
    {
        return lhs.c == rhs.c;
    }

    template <class T, class Container>
    bool operator<(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
    {
        return lhs.c < rhs.c;
    }

    template <class T, class Container>
    bool operator!=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Container>
    bool operator>(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Container>
    bool operator<=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Container>
    bool operator>=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
    {
        return !(lhs < rhs);
    }
} // namespace ft
