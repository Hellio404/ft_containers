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
#include <ft_type_traits.hpp>
#include <cstddef>
#include <iterator>

namespace ft {

    template <typename T>
    struct iterator_traits {
        typedef typename T::iterator_category   iterator_category;
        typedef typename T::value_type          value_type;
        typedef typename T::difference_type     difference_type;
        typedef typename T::pointer             pointer;
        typedef typename T::reference           reference;
    };

    // specialization for pointers
    template <typename T>
    struct iterator_traits<T* > {
        typedef std::random_access_iterator_tag     iterator_category;
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
    };

    // specialization for const pointers
    template <typename T>
    struct iterator_traits<const T* > {
        typedef std::random_access_iterator_tag     iterator_category;
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef const T*                            pointer;
        typedef const T&                            reference;
    };

}
