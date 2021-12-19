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
#include <memory>
#include <cstddef>

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
        };

        pointer _allocate_storage(size_type n)
        {
            return n > 0 ? _data.allocate(n) : pointer();
        }

        pointer _deallocate_storage(pointer p, size_type n)
        {
            if (p)
                _data.deallocate(p, n);
        }

        void _init_storage(size_type n)
        {
            _data._begin =  _allocate_storage(n);
            _data._finish = _data._begin;
            _data._end_of_storage = _data._begin + n;
        }
        
    public:
        /*
        _base_data :
            pointer _begin;
            pointer _finish;
            pointer _end_of_storage;
            all allocator public/protected attributes and methods
        */
        _base_data _data;

        _vector_base(): _data() {};
        _vector_base(allocator_type alloc): _data(alloc) {};
        _vector_base(size_type n, allocator_type &alloc): _data(alloc) { _init_storage(n); };

        ~_vector_base() 
        { 
            _deallocate_storage(_data._begin, size_type(_data._end_of_storage - _data._begin));
        };

    };
}