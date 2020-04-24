#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

template <typename T>
void print(const vector<T>& A){
	for(auto &i: A){
		cout << i << " ";
	}
	cout << endl;
}

// 1. recursive
void minheapify(vector<int>& A, int n, int index){
	int parent = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	if(left < n && A[parent] > A[left]) parent = left;
	if(right < n && A[parent] > A[right]) parent = right;
	if(parent != index){
		swap(A[parent], A[index]);
		print(A);
		// sleep(1);
		minheapify(A, n, parent);
	}
}

// 2. iterative
// void minheapify(vector<int>& A, int n, int index){
// 	int parent = index;
// 	int left = 2 * index + 1;
// 	int right = 2 * index + 2;
// 	while(left < n){

// 		if(right >= n){
// 			if(A[parent] > A[left]) { // if we reach here, that means we reach the last node, we STOP! and break.
// 				swap(A[parent], A[left]);
// 				break;
// 			}
// 		}
// 		if(A[parent] > left || A[parent] > A[right]){
// 			if(A[parent] > A[left]){
// 				swap(A[parent], A[left]);
// 				parent = left;
// 				// left = 2 * left + 1;
// 			}
// 			if(A[parent] > A[right]){
// 				swap(A[parent], A[right]){
// 					parent = right;
// 					// right = 2 * right + 1;
// 				}
// 			}
// 		}
// 		left = 2 * parent + 1;
// 		ritht = 2 * parent + 2;
// 	}
// }

void buildheap(vector<int>& A){
	int n = A.size();
	for(int i = (n>>1) - 1; i >= 0; --i){
		minheapify(A, n, i);
	}
}

void heapsort(vector<int>& A){
	buildheap(A);
	print(A);

	int n = A.size();
	while(n > 0){
		swap(A[0], A[n - 1]);
		--n;
		minheapify(A, n, 0);
	}
}



int main(){
	vector<int> A = {4, 7, 6, 18, 9, 3, 12, 8, 5, 11};
	heapsort(A);
	// print(A);
}