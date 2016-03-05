/*
* Find a duplicate in an integer array whose elements are 1 to 100 consecutive

* Input: Given an array of n elements which contains elements from 0 to n-1, 
       with any of these numbers appearing any number of times.

* Goal : To find these repeating numbers in O(n) and using only constant memory space.

*/

/* Ideas:
*   (1) C++
*   Convert the array into set, because set does not allow duplicate element, we can take advantage of this feature.
    If set size is smaller than array, then find duplicate.

*   (2) C++
*    Add every element of array into HashSet, if add(obj) returns false, then the set already contains the duplicated element.
*/

#include<iostream>
#include<algorithm>
#include<array>
#include<set>
using namespace std;

bool hasDuplicate(const int* arr, unsigned int N){ // N is the length of the array
    set<int, less<int>> myset (arr, a+N);
    /* 2. use insert
    set<int> myset;
    for(unsigned int i=0; i<len; ++i)
    	myset.insert(a[i]);
        
    // If N elements are inserted, complexity is: Nlog(size+N).
	*/
	/* 3. use emplace
	myset.emplace(a[i]);
	insert and emplace both return a pair< set<int>::iterator, bool >
	
	pair< set<int>::iterator, bool > ret;
    for(unsigned int i=0; i<len; ++i)
		if(!myset.insert(a[i]).second)
			return false;
    return true;
    */
    return myset.size()<len;
}

template <size_t N>
bool hasDuplicate(array<int, N> A){
	set<int> myset(A.begin(), A.end());
	return myset.size() < N;
}

int main(){
    //int arr[]={6, 6, 3, 9, 11, 5, 2, 2};
	
	array<int, 8> myarr={6, 6, 3, 9, 11, 5, 2, 2}; //or myarr{6, 6, 3, 9, 11, 5, 2, 2}
	
    bool b = hasDuplicate(myarr);;
    //b = hasDuplicate(arr, sizeof arr/sizeof arr[0]);
    if(b)
        cout<<"has duplicate"<<endl;
    else
        cout<<"no duplicate"<<endl;
    return 0;
}

/*

#include<iostream>
#include<array>
using namespace std;

template <size_t N>
void f(array<char, N> arr) {
    cout << "N=" << N << endl;
}

int main(){
    
    array<char, 2> arr={'a', 'b'};
    f(arr);
    return 0;
    
}

*/