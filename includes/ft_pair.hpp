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

namespace ft
{
    template <typename T1, typename T2>
    class pair
    {
    public:
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;

        pair() : first(T1()), second(T2()){};

        pair(const T1 &a, const T2 &b) : first(a), second(b){};

        template <typename U1, typename U2>
        pair(const pair<U1, U2> &pr) : first(pr.first), second(pr.second){};

        pair &operator=(const pair<T1, T2> &pr)
        {
            this->first = pr.first;
            this->second = pr.second;
            return *this;
        }
    };

    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y)
    {
        return x.first == y.first && x.second == y.second;
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &x, const pair<T1, T2> &y)
    {
        return !(x == y);
    }

    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &x, const pair<T1, T2> &y)
    {
        return x.first < y.first || (x.first == y.first && x.second < y.second);
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &x, const pair<T1, T2> &y)
    {
        return !(y < x);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &x, const pair<T1, T2> &y)
    {
        return y < x;
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &x, const pair<T1, T2> &y)
    {
        return !(x < y);
    }


    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return pair<T1, T2>(x, y);
    }
}
