// [LeetCode 26] Remove Duplicates from Sorted Array

// Given a sorted array, remove the duplicates in place such that each element appear 
// only once and return the new length.
// Do not allocate extra space for another array, you must do this in place with constant memory.

// For example,
// Given input array nums = [1,1,2],
// Your function should return length = 2, with the first two elements of nums 
// being 1 and 2 respectively. 
// It doesn't matter what you leave beyond the new length.

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

void remove_duplicates(vector<int> &A){
	// auto iter = std::unique(A.begin(), A.end());
	// A.resize(std::distance(A.begin(), iter));

	// set<int> s(A.begin(), A.end());
	// A.assign(s.begin(), s.end());

    // write your code here
    const int n = A.size();
    if(n < 2) return;
    
    int end = 1;

    // end denotes the end of the new array, 
    // it is the slot that next non-duplicate number will be put in
    // end denotes  the end of the duplicates
    // for example: A{1, 1, 2, 2, 3}
    // end = 1, 3
    for(int i = 1; i < n; ++i){
        if(A[end - 1] != A[i]){
            A[end++] = A[i];
        }
    }
    A.resize(end);
}

int main(){
	std::vector<int> myvector = {100, 100, 100, 77, 77, 77, 91, 91, 91, 10, 20, 20, 20, 30, 30, 20, 20, 10, 10};
	remove_duplicates(myvector);

	for(auto& item : myvector){
		cout << item << " ";
	}
	cout << endl;
}