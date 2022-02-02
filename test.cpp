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
#include <iostream>
#include <deque>
#include <ft_vector.hpp>
#include <ft_utils.hpp>
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



int main()
{

    max_to_fail = 102;
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

    ft::vector<int, myCustomAllocator<int> > f;
    for(int i = 0; i < 10; i++)
    {
        f.push_back(i);
    }

    std::cout << (*(f.begin() + 5)) << std::endl;
    std::cout << (*f.erase(f.begin() + 5))<< std::endl;

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

}