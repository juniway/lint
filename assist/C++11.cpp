//C++11.cpp

/*	Ten c++ features Every C++ developer should use
	1. auto
	2. nullptr
	3. Range-based for-loops 
	4. Override and final
	5. Strongly-typed enums
	6. Smart pointers
	7. Lambdas
	8. non-member begin() and end()
	9. static_assert and type traits
	10. move semantics
*/

/*
 1. for each loop
 */

//C++11 provides a for each loop. The syntax is taken from Java and looks like this:

//(1)
#include<iostream>

//for( type-speciﬁer-seq simple-declarator : expression ) statement
//for ( declaration : expression ) statement
syntactically equivalent to
{
	typedef decltype(expression) C;
	auto&& __rng(( expression ));
	for( auto begin( std::For<_C>::begin(__rng) ), end( std::For<_C>::end(__rng) );
		__begin != __end; ++ begin ) {
			type-speciﬁer-seq simple-declarator ( *__begin );
			statement
	}
}

1   {
2     auto&& __range = expression;
3     for (auto __begin = begin-expression,
4               __end = end-expression;
5          __begin != __end;
6          ++__begin)
7     {
8       declaration = *__begin;
9       statement
10    }
11  }

template<typename T, size_t N>
concept map For<T[N]> {
	typedef T* iterator;
	T* begin(T (&array)[N]) { return array; }
	T* end(T (&array)[N]) { return array + N; }
}

template<Container C> 
concept map For<C> { 
	typedef C::iterator iterator ; 
	iterator begin(C& c) 
		{ return c. begin(); } 
	iterator end(C& c) 
		{ return c. end(); } 
}


int main(){
	int myint[] =  {1, 2, 3, 4, 5};
	for (int &i: myint){
		std::cout<<i<<std::endl;
	}
}

//(2)
template<class InputIterator, class Function>
  Function for_each(InputIterator first, InputIterator last, Function fn)
{
  while (first!=last) {
    fn (*first);
    ++first;
  }
  return fn; // since C++11: return std::move(fn);
}

#include