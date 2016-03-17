
// bubble_sort
void bubble_sort(int a[], n){
	for(int i = 0; i < n - 1; ++i){
		for(int j = 0; j < n - 1 -i; ++j){
			if(a[j] < a[j + 1]){
				int tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
}

void bubbleSort(int* data, int N){
    for (int i = N - 1; i > 0; --i){
        for (int j = 0; j < i; ++j){
            if (data[j] > data[j+1])
                swap(data[j], data[j+1]);
        }
    }
}

// http://www.cs.rpi.edu/~musser/design/blitz/meta-art.html
In order to generate an inlined bubble sort such as the above,
it seems that we'll have to unwind two loops.'
We can reduce the number of loops to one,
by using a recursive version of bubble sort:
void bubbleSort(int* data, int N){
    for (int j = 0; j < N - 1; ++j){
        if (data[j] > data[j+1])
            swap(data[j], data[j+1]);
    }

    if (N > 2)
        bubbleSort(data, N-1);
}

Now the sort consists of a loop, and a recursive call to itself.
This structure is simple to implement using some template classes:

template<int N>
class IntBubbleSort {
public:
    static inline void sort(int A[]){
        IntBubbleSortLoop<N-1,0>::loop(A);
        IntBubbleSort<N-1>::sort(A);
    }
};

template<int I, int J>
class IntBubbleSortLoop{
private:
    enum(go = (J <= I - 2)};
public:
    static inline void loop(int A[]){
        IntSwap<J, J+1>::compareAndSwap(A);
        IntBubbleSortLoop<go ? I : 0, go ? (J + 1) : 0>::loop(A);
    }
};

class IntBubbleSortLoop<0, 0> {
public:
    static inline void loop(int *) {}
};

template<int I, int J>
class IntSwap{
public:
    static inline void compareAndSwap(int A[]){
        if(A[I] > A[J]) swap(A[I], A[J]);
    }
};

// optimized bubble_sort
// 如果数组已经排好序，那么bubble就可以提前结束
void bubble_sort(int A[], int n){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++){
        swapped = false;
        for (j = 0; j < n - i - 1; ++j){
            if (arr[j] > A[j + 1]){
                swap(&arr[j], &A[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped by inner loop, then break
        if (swapped == false)
            break;
   }
}
struct X { int x; typedef double Z; };
struct Y { typedef int x; double Z; };
template<typename T>
struct ZZ {
	T::Z z1;	// 1
	typename T::Z z2; // 2
	void func(T& t) { t.x = 4; } // 3
	typedef typename std::vector<T>::iterator VecIt; // 4

};


template<typename T, unsigned i> struct FixedArray { T data[i]; };
FixedArray<int, 3> a; // array of 3 integers
FixedArray<int, 1+6/3> b; // array of 3 integers
template<template<typename T, typename Allocator> class Container>
struct ContainerPair {
	Container<int, std::allocator<int>> intContainer;
	Container<std::string, std::allocator<std::string>> stringContainer;
};
ContainerPair<std::deque> deqCont; // two std::deques
ContainerPair<std::vector> vecCont; // two std::vectors

template<typename T> void func(T value) {}
template<typename T, typename U>
T func2(U value) { return T(value); }
int main() { //
T=int func(3); // T=double func(3.5); // T=int, U=double func2<int>(3.5); // T=std::vector<std::string>, U=int func2<std::vector<std::string> >(5); // specify both T and U // T=std::vector<std::string>, U=int func2<std::vector<std::string>,int>(5.7); }

int main() {
	X x;
	Y y;
	ZZX zzx; // 5
	ZZY zzy; // 6
	zzx.func(x); // 7
	zzy.func(y); // 8

}

Template instantiation involves generating a concrete class or function (instance) for a particular combination of template arguments.
Unless a template specialization has been explicitly instantiated or explicitly specialized, the compiler will generate a specialization for the template
only when it needs the definition. This is called implicit instantiation.

C++0x
The compiler does not need to generate the specialization for nonclass, noninline entities when an explicit instantiation declaration is present.
