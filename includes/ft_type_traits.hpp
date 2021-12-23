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
namespace ft {

    // this is utility so you can 'inheret' from it and give it a type and
    // a value of the same type and it will add a static member variable 
    // called value of type T and value n 
    template <typename T, T n>
    struct intergal_constant {
        static const T value = n;
    };

    // alias, instead of using intergal_constant<bool, false> you can just
    // do bool_constant<false>
    template <bool b>
    struct bool_constant : intergal_constant <bool, b> {};

    // this is a utility that you can 'inheret' from and provide it with 
    // a type and it will add a typedef called type of the  type T provided
    template <typename T>
    struct identity { typedef T type; };


    // alias for intergal_constant<bool, false>
    struct false_type   : bool_constant <false> {};
    // alias for intergal_constant<bool, false>
    struct true_type    : bool_constant <true> {};

    template <bool _cond, typename _IfTrue, typename _IfFalse>
    struct conditional: identity<_IfTrue> {};

    template <typename _IfTrue, typename _IfFalse>
    struct conditional<false, _IfTrue, _IfFalse>: identity<_IfFalse> {};

    // If B is true, ft::enable_if has a public member typedef type, equal to T; 
    // otherwise, there is no member typedef.
    template <bool B, typename T = void>
    struct enable_if : identity<T> {};
    // specialization  
    template <typename T>
    struct enable_if<false, T> {};


    template <typename T>
    struct is_pointer       : false_type {};
    // specialization  
    template <typename T>
    struct is_pointer<T*>   : true_type {};

    
    template <typename T, typename U>
    struct is_same          : false_type {};
    // specialization
    template <typename T>
    struct is_same<T, T>    : true_type {};


    template <typename T>
    struct remove_const : identity<T> {};
    // specialization
    template <typename T>
    struct remove_const<T const> : identity<T> {};


    template <typename T>
    struct remove_volatile : identity<T> {};
    // specialization
    template <typename T>
    struct remove_volatile<T volatile> : identity<T> {};


    template <typename T>
    struct remove_cv : remove_volatile<typename remove_const<T>::type> {};


    template <typename T>
    struct is_void  : is_same<typename remove_cv<T>::type, void> {};


    template <typename T>
    struct is_integral : false_type {};
    //specialization
    template <> struct is_integral<bool> :                  true_type {};
    template <> struct is_integral<char> :                  true_type {};
    template <> struct is_integral<signed char> :           true_type {};
    template <> struct is_integral<unsigned char> :         true_type {};
    template <> struct is_integral<short> :                 true_type {};
    template <> struct is_integral<unsigned short> :        true_type {};
    template <> struct is_integral<int> :                   true_type {};
    template <> struct is_integral<unsigned int> :          true_type {};
    template <> struct is_integral<long> :                  true_type {};
    template <> struct is_integral<unsigned long> :         true_type {};
    template <> struct is_integral<long long> :             true_type {};
    template <> struct is_integral<unsigned long long> :    true_type {};
}
