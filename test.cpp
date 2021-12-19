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

#include <ft_iterator.hpp>
#include <ft_reverse_iterator.hpp>
#include <vector>
#include <bits/stl_iterator.h>
#include <iostream>
#include <stack>
struct test
{
   int b;
   test(): b(96) {}

};





int main()
{
    int a[] = {0,1,2,3,4,5,6};
    std::vector<int> v(a, a+7);

    // typedef ft::ft_iterator<int *, std::vector<int> >  normal_it;
    // normal_it start(a);
    // normal_it end(a + 7);


 
    ft::reverse_iterator<std::vector<int>::iterator> rstart(v.end());
    ft::reverse_iterator<std::vector<int>::const_iterator> rend(v.begin());

    std::cout << (rstart <= rend) <<std::endl;
    // while (rstart != rend)
    // {
    //     std::cout << *rstart << std::endl;
    //     ++rstart;
    // }

    // int af;
    // typedef __gnu_cxx::__normal_iterator< test *, std::vector<test> > myType;
    // typedef __gnu_cxx::__normal_iterator< int *, std::vector<test> > myType2;

    // myType  f1(&a);
    // myType2  f2(&af);
    // std::reverse_iterator<myType> c(f1);
    // std::reverse_iterator<myType2 > c2(f2);
    
    
    // test &tp = c[0];

    // std::cout << c.base();

    // std::cout << c.base().base() <<"\n"<< (c - 2).base().base()  << std::endl;
   
    // ft::is_same<typename std::vector<int>::pointer, typename ft::ft_iterator<char *, std::vector<int> >::iterator_type>::value;
}