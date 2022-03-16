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

#include "ft_iterator.hpp"
#include "ft_reverse_iterator.hpp"
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <deque>
#include "ft_vector.hpp"
#include "ft_utils.hpp"
#include "ft_tree.hpp"
#include "ft_map.hpp"
// #include "ft_rb_tree.hpp"
template <class T>
struct InputIterator {
    typedef std::input_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T *pointer;
    typedef const T &reference;
    InputIterator(T* current): current(current) {};
    InputIterator(InputIterator const& it): current(it.current) {};
    InputIterator& operator=(InputIterator const&it)
    {
        this->current = it.current;
        return *this;
    }
    bool operator==(InputIterator const& it)
    {
        return it.current == this->current;
    }
    
    bool    operator!=(InputIterator const& it)
    {
        return it.current != this->current;
    }

    T*    operator->()
    {
        return this->current;
    }

    T    operator*()
    {
        return *(this->current);
    }

    InputIterator&  operator++()
    {
        current = InputIterator::next;
        InputIterator::next++;
        return *this;
    }
    
    InputIterator  operator++(int)
    {
        InputIterator tmp = *this;
        current = InputIterator::next;
        InputIterator::next++;
        return tmp;
    }
    static T* next;
private:
    T*  current;
};
template <class T>
T* InputIterator<T>::next = 0;

int max_to_fail = 9999;
class test
{
private:
    /* data */
public:
    static int k;
    static int constructed_size;
    int f;
    test()
    {
        k++;
        f = k;
        std::cout << "--> TEST: Default Constructor (" << f << ")\n";
        if (k > max_to_fail)
        {
            std::cerr << "--->> ERROR HERE WHILE CONSTRUCTING TEST!!!!!\n";
            throw "LOL\n";
        }
        constructed_size++;

    }

    test(int kk)
    {
        k++;
        f = kk;
        std::cout << "--> TEST: INT Constructor (" << f << ")\n";
        if (k > max_to_fail)
        {
            std::cerr << "--->> ERROR HERE WHILE CONSTRUCTING TEST!!!!!\n";
            throw "LOL\n";
        }
        constructed_size++;
    }

    test(test const& t)
    {
        k++;
        f = k;
        std::cout << "--> TEST: copy Constructor (" << f << " from " << t.f<<")\n";
        if (k > max_to_fail)
        {
            std::cerr << "--->> ERROR HERE WHILE CONSTRUCTING TEST!!!!!\n";
            throw "LOL\n";
        }
        constructed_size++;
        

    }

    test&   operator=(test const&t)
    {
        k++;
        f = k ;
        std::cout << "--> TEST: assignement copy Constructor (" << f <<" = " << t.f<<") \n";
        if (k > max_to_fail)
        {
            std::cerr << "--->> ERROR HERE WHILE CONSTRUCTING TEST!!!!!\n";
            throw "LOL\n";
        }
        // constructed_size++;

        return *this;
    }

    ~test()
    {
        std::cout << "--> TEST: destructor (" << f << ")\n";
        constructed_size--;

    }
};

std::ostream& operator<<(std::ostream& o, test const& vl)
{
    o << vl.f;
    return o;
}
#include <limits>
template <class T> class myCustomAllocator;
template <>
class myCustomAllocator<void>
{
public:
    typedef void              value_type;
    typedef value_type*       pointer;
    typedef value_type const* const_pointer;
    typedef std::size_t       size_type;
    typedef std::ptrdiff_t    difference_type;

    template <class U>
    struct rebind
    {
        typedef myCustomAllocator<U> other;
    };
};

template <class T>
class myCustomAllocator
{
public:
    typedef T                 value_type;
    typedef value_type&       reference;
    typedef value_type const& const_reference;
    typedef value_type*       pointer;
    typedef value_type const* const_pointer;
    typedef std::size_t       size_type;
    typedef std::ptrdiff_t    difference_type;
    static size_type allocated_size ;
    static size_type k;
     size_type f;
    static size_type construct_size ;
    template <class U>
    struct rebind
    {
        typedef myCustomAllocator<U> other;
    };

    myCustomAllocator() throw() {std::cout << "Allocator: Default Constructor\n"; f = k; k++;}  // not required, unless used
    template <class U> myCustomAllocator(myCustomAllocator<U> const& u) throw() {std::cout << "Allocator: CopyConstructor\n";}

    pointer
    allocate(size_type n, myCustomAllocator<void>::const_pointer = 0)
    {
        std::cout << "Allocator: allocate Func: " << n<<"\n" ;
        allocated_size += n;
        return static_cast<pointer>(::operator new (n*sizeof(value_type)));

    }

    void
    deallocate(pointer p, size_type my_size)
    {
        std::cout << "Allocator: deallocate Func: "<< my_size << "\n";
        allocated_size -= my_size;
        // allocated_size += *(static_cast<int *>(0));
        ::operator delete(p);
    }

    void
    construct(pointer p, value_type const& val)
    {
        std::cout << "Allocator: construct Func\n";
        construct_size++;
        ::new(p) value_type(val);
    }

    void
    destroy(pointer p)
    {
        std::cout << "Allocator: destroy Func\n";
        construct_size--;
        p->~value_type();
    }

    size_type
    max_size() const throw()
    {
        std::cout << "Allocator: max_size Func\n";

        return 500000;
    }

    pointer
    address(reference x) const
    {
        std::cout << "Allocator: address Func\n";

        return &x;
    }

    const_pointer
    address(const_reference x) const
    {
        std::cout << "Allocator: const_pointer address Func\n";

        return &x;
    }
};

template <class T, class U>
bool
operator==(myCustomAllocator<T> const&, myCustomAllocator<U> const&)
{
    return true;
}

template <class T, class U>
bool
operator!=(myCustomAllocator<T> const& x, myCustomAllocator<U> const& y)
{
    return !(x == y);
}

template <typename T>
typename myCustomAllocator<T>::size_type myCustomAllocator<T>::construct_size = 0;
template <typename T>
typename myCustomAllocator<T>::size_type myCustomAllocator<T>::allocated_size = 0;
template <typename T>
typename myCustomAllocator<T>::size_type myCustomAllocator<T>::k = 0;

int test::k = 0;
int test::constructed_size = 0;



int f()
{
    std::cout << "WTF\n";
    return 0;
}
#include <iostream>
#include<stdlib.h>
#include<string.h>
#include <iostream>
#include <iterator>

#include <ctime>

struct K
{
    int operator () (int a, int b)
    {
        return a + b;
    }
};


int main()
{

    // test* ts = static_cast<test*>(operator new (5 * sizeof(test)));

    // new(ts) test(5);
    // new(ts + 1) test(689);
    // new(ts + 2) test(420);
    // new(ts + 3) test();
    // new(ts + 4) test(420);
    // max_to_fail = 102;
    // ft::cout << ac << ft::endl;

//     typedef test MyType;
//     typedef myCustomAllocator<MyType> ALLOCATOR;
// // typedef std::allocator<MyType> ALLOCATOR;

//     #define NAMESPACE ft
//     typedef NAMESPACE::vector<MyType, ALLOCATOR > VectorType;



//     try
//     {
//         MyType arr[] = {0,1,2,3,4,5,6,7,8};
//         InputIterator<MyType>::next = arr + 1;
//         InputIterator<MyType> b = arr;
//         InputIterator<MyType> e = arr + 8;
//         max_to_fail = 20;
//         VectorType vt(b, e);
       
      
//     }
//     catch(...)
//     {
//         std::cerr <<" e.what() "<< '\n';
//     }
    
    // std::vector<float, myCustomAllocator<float> > m(8,5.0, myCustomAllocator<float>()); 

//     // system("leaks test");

//     std::cout << "ALLOCATOR INFO: STILL NOT FREED: (" << myCustomAllocator<MyType>::allocated_size  << ") and STILL NOT DESTROYED: (" << MyType::constructed_size  <<")\n";
// //     ft::is_integral<std::string>::value
// //         std::vector<test>p(5);
// //     ft::is_void<myCustomAllocator<int>::lol>::value;
    // ft::vector<test, myCustomAllocator<test> > f(12, 1, myCustomAllocator<test>());
    // int arrr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    // ft::vector<int, myCustomAllocator<int> > f(arrr,arrr+12, myCustomAllocator<int>());
    // f.reserve(50);
    // test arr[] = {100,101,102,103,104,105,106,107,108};
    // std::cout << "\n\n\n";
    // std::cout << f.size() << "\n";
    
    // f.insert(f.end() , arr, arr+3);
    // std::cout << f.size() << "\n";
    // std::cout << "\n\n\n";
    // ft::vector<int, myCustomAllocator<int> >::reverse_iterator it = f.rbegin();
    // ft::vector<int, myCustomAllocator<int> >::reverse_iterator it2 = f.rbegin() + 2;

    // std::cout << (it > it2 ? "true": "false") << std::endl;
    // std::map<int , int>mp;
    // std::distance(it, it2);
    // // print the vector
    // std::cout << "Vector: ";
    // for (size_t i = 0; i < f.size(); i++)
    // {
    //     std::cout << f[i] << " ";
    // }
    // ft::vector <int> a;
    // ft::vector <int>::iterator it = a.begin();

    // ft::vector <int>::const_iterator cit = a.begin();

    // ft::vector <int>::iterator c = a.begin();

    // c.operator=(it);

    // std::cout << (it == cit) << std::endl;
    
    //  std::cout << "f size: " << f.size() << "\n";
    // std::cout << "m size: " << m.size() << "\n";

    // // print f contents using index
    // for(size_t i = 0; i < f.size(); i++)
    // {
    //     std::cout << "f[" << i << "] = " << f[i] << "\n";
    // }

    // // prsize_t m contents using index

    // for(size_t i = 0; i < m.size(); i++)
    // {
    //     std::cout << "m[" << i << "] = " << m[i] << "\n";
    // }

    // f.swap(m);
    
    // // print f and m  and their sizes
    // std::cout << "f size: " << f.size() << "\n";
    // std::cout << "m size: " << m.size() << "\n";

    // // print f contents using index
    // for(size_t i = 0; i < f.size(); i++)
    // {
    //     std::cout << "f[" << i << "] = " << f[i] << "\n";
    // }

    // // prsize_t m contents using index

    // for(size_t i = 0; i < m.size(); i++)
    // {
    //     std::cout << "m[" << i << "] = " << m[i] << "\n";
    // }

    // // f.assign(m.begin(), m.end());

    // ft::rb_tree<
    //     int, 
    //     ft::select_self< int >,
    //     std::less<int>
    // > t;

    // t._insert(69);
    // t._insert(42);
    // t._insert(1337);
    // t._insert(-42);
    // t._insert(0);
    // t._insert(55);
    // t._insert(1000);
    // t._insert(1001);
    // t._insert(1002);
    // t._insert(1003);
    // t._insert(1053);
    // t._insert(1052);
    // t._insert(1051);
    // t._insert(1050);
    // t._insert(1049);
    // // insert 50 random values
    // srand(time(NULL));
    // for(int i = 0; i < 50; i++)
    // {
    //     int k = rand() % 1000;
    //     t._insert(k);
    //     std::cout << "new Node(" << k << ")\n";
    // }
    // t.print_tree();
    // ft::rb_tree<
    //     int, 
    //     ft::select_self< int >,
    //     std::less<int>
    // >::iterator it = t.begin();

    // while (it != t.end())
    // {
    //     std::cout << *it << std::endl;
    //     it++;
    // }
    
    // ft_dev::tree_node<test> root(69);
    // ft_dev::tree_node<const test> croot(69);
    // // ft_dev::Tree<const test>::iterator ;
    // std::map <int, int> s;
    // for (int i = 1; i <=18; i++)
    //     s[i] = 100;
    // s.insert(std::pair<int, int>(1, 69));
    // s.insert(std::pair<int, int>(2, 69));
    // s.insert(std::pair<int, int>(3, 69));
    // for (std::map<int, int>::iterator it = s.begin(); it != s.end(); it++)
    // {
    //     std::cout << it->first << " " << it->second << std::endl;
    // }
    
    // generate random numbers in a vector
    std::vector<int> v;

    srand(time(NULL));
    for (int i = 0; i < 20; i++)
        v.push_back(rand() % 100);

    std::vector<ft::pair<int, int> >v1;
    for (int i = 0; i < 20; i++)
        v1.push_back(ft::pair<int, int>(v[i], i));
    
    std::vector<std::pair<int, int> >v2;
    for (int i = 0; i < 20; i++)
        v2.push_back(std::pair<int, int>(v[i], i));

    typedef   ft::map<int, int > tree;
    typedef   std::map<int, int > tree2;
    tree t(v1.begin(), v1.end());
    tree2 t2(v2.begin(), v2.end());

    tree::iterator it = t.begin();
    tree2::iterator it2 = t2.begin();

    while (it != t.end())
    {
        std::cout << it->first << " " << it->second << std::endl;
        it++;
    }
    std::cout << "\n------------------------------\n\n";
    while (it2 != t2.end())
    {
        std::cout << it2->first << " " << it2->second << std::endl;
        it2++;
    }
    std::cout << "\n------------------------------\n\n";

    std::cout << t.lower_bound(42)->first << std::endl;
    std::cout << t2.lower_bound(42)->first << std::endl;


    // for (int i = 1; i <=8; i++)
    //     t.insert_uniq(i);
    
    // tree::iterator it = t.begin();
    // while (it != t.end())
    // {
    //     std::cout << *it << std::endl;
    //     it++;
    // }
    // std::cout << "size: " << t.size() << std::endl;


    /*


        do you see this

    */




    // tree::reverse_iterator it = t.rbegin();
    // while (it != t.rend())
    // {
    //     std::cout << it->second << std::endl;
    //     it++;
    // }

    // // // t.erase_multi(1);
    // // // t.erase_multi(8);
    // ft::rb_tree<int, ft::select_self<int>, std::less<int> >::iterator it = t.begin();
    // it++;
    // it++;

    //     t.erase_iter(it, t.end());

    // t.erase_uniq(4);
    // // t.erase_uniq(2);
    // // t.erase_uniq(8);
    // // t.erase_multi(8);


    // // ft_dev::rb_tree<int, ft::select_self<int> >::node_base_ptr p = t._end_node();
    // // while (1)
    // // {
    // //     p = ft_dev::tree_prev_node(p);
    // //     std::cout << static_cast<ft_dev::tree_node<int> *>(p)->value << std::endl;
    // //     if (p == t._begin_node())
    // //         break;
    // // }
    // K()(1, 2);
    // t._print_tree(t._rb(t._root()));
    // std::cout << std::endl;
    // t.print_tree();
    // ft_dev::tree_iterator<test> it(&root);
    // ft_dev::tree_iterator<const test> cit(it);
    // std::cout << "it: " << it->f << std::endl;
    // std::cout << "it: " << cit->f << std::endl;

    // if (it == cit)
    //     std::cout << "it == cit\n";
    // else
    //     std::cout << "it != cit\n";
    
    // ft::tree_iterator<int, ft::tree_node<int> > it;
    // ft::const_tree_iterator<int, ft::tree_node<int> > cit;
    // // std::map<int,int>::iterator it;
    // // std::map<int,int>::const_iterator cit;

    // if (operator==(it, cit))
    // {
    //     std::cout << "it == cit\n";
    // }
    // else
    // {
    //     std::cout << "it != cit\n";
    // }
    // std::map<int, int *> m;
    // if (m[1])
    //     std::cout << "yep\n";
    // std::cout << m.count(1) << "\n";
}

/*

10
Allocator: construct Func
--> TEST: copy Constructor (31 from 19)
Allocator: construct Func
--> TEST: copy Constructor (32 from 20)
Allocator: construct Func
--> TEST: copy Constructor (33 from 21)
--> TEST: assignement copy Constructor (34 = 18) 
--> TEST: assignement copy Constructor (35 = 17) 
--> TEST: assignement copy Constructor (36 = 16) 
--> TEST: assignement copy Constructor (37 = 15) 
--> TEST: assignement copy Constructor (38 = 100) 
--> TEST: assignement copy Constructor (39 = 101) 
--> TEST: assignement copy Constructor (40 = 102) 
13
Vector: 12 13 14 38 39 40 37 36 35 34 31 32 33 --> TEST: destructor (108)

*/