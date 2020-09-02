/*
 *    quick sort implementation
 */
 
 The Algorithm
Partition(A; p; r)
1: x = A[r]
2: i p  1
3: for j p to r  1 do
4: if A[j] <= x then f
5: i i + 1
6: Exchange A[i] and A[j] g
7: Exchange A[i + 1] and A[r]
8: return i + 1
During the for-loop i + 1 is the position at
which the next key that is greater than or
equal to the pivot should go to.


Pseudocode
Sort(A)
	Quicksort(A, 1, n)

Quicksort(A, low, high)
	if (low < high)
		pivot_location = Partition(A, low, high)
		Quicksort(A, low, pivot_location - 1) 
		Quicksort(A, pivot_location+1, high)
		
Partition(A, low, high)
	pivot = A[low]
	leftwall = low
	for i = low+1 to high
		if (A[i] < pivot) then
			leftwall++
			swap(A[i], A[leftwall)
	swap(A[low], A[leftwall])



#include<iostream>
using namespace std;

void quicksort(int arr[], int left, int right) {
	if(left>=right) return;

	int i = left, j = right;
	int pivot = arr[(left + right) / 2];

	// partition, i increases and j decreases, when i > j, stop partition
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			swap(arr[i], arr[j])
			i++;
			j--;
		}
	};

	// recursion sorting
	if (left < j)
		quicksort(arr, left, j);
	if (i < right)
		quicksort(arr, i, right);
}

int main(){
	int arr[]={19, 55, 28, 11, 44, 32, 13, 22, 10, 30};
	int size = sizeof arr/ sizeof arr[0];
	cout<<"Before sort:";
	for(int i=0; i<size; ++i){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	
	quicksort(arr, 0, 9); // (array, left, right)
	
	cout<<" After sort:";
	for(int i=0; i<size; ++i){
		cout<<arr[i]<<" ";
	}
	cout<<endl;

}
