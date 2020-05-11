/*****************************************************************************
 * Bubble sort algorithm implemented using template metaprograms
 * Author: Todd Veldhuizen        (tveldhui@seurat.uwaterloo.ca)
 *
 * This program may be redistributed in an unmodified form.  It may not be
 * sold or used in a commercial product.
 *
 * For more information on these template techniques, please see the
 * Blitz++ Numerical Library Project, at URL http://monet.uwaterloo.ca/blitz/
 */

#include <iostream.h>

// IntSwap<I,J>::swap(int* data) compares data[I] and data[J],
// and exchanges them if necessary.
template<int I, int J>
class IntSwap {

public:
    static inline void swap(int* data)
    {
        register int tmp1 = data[I];
        register int tmp2 = data[J];

        if (tmp1 > tmp2)
        {
            data[I] = tmp2;
            data[J] = tmp1;
        }
    }
};

// IntBubbleSortLoop<N,0U>::loop(p) generates code to do
//
//     IntSwap<0,1>::swap(data);
//     IntSwap<1,2>::swap(data);
//              .
//              .
//     IntSwap<N-2,N-1>::swap(data);

template<int N, int I>
class IntBubbleSortLoop {

public:
    // The 'go' enum is used as a compile-time temporary variable.  It is
    // true until the end of the loop.
    enum { go = (I+2 <= N) };

    static inline void loop(int* data)
    {
        IntSwap<I,I+1>::swap(data);
        IntBubbleSortLoop<go ? N : 0, go ? (I+1) : 0>::loop(data);
    }
};

// Base case to end the recursive loop
class IntBubbleSortLoop<0,0> {
public:
    static inline void loop(int*)
    { }
};

// Class for doing a bubble sort on an array of N integers
template<int N>
class IntBubbleSort {
public:
    static inline void sort(int* data)
    {
        IntBubbleSortLoop<N-1,0>::loop(data);
        IntBubbleSort<N-1>::sort(data);
    }
};

// Base case for the recursion
class IntBubbleSort<1> {
public:
    static inline void sort(int* data)
    { }
};

inline void swap(int& a, int& b)
{
    int temp = a;
    a=b;
    b = temp;
}

void bubbleSort(int* data, int N)
{
    for (int i=N-1; i > 0; --i)
    {
        for (int j=0; j < i; ++j)
        {
            if (data[j] > data[j+1])
                swap(data[j], data[j+1]);
        }
    }
}

int main()
{
    int data[] = { 5, 4, 3, 5, 2 };
    IntBubbleSort<5>::sort(data);
    return 0;
}
