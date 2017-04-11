#include <stdio.h>

/* 
* Bubble Sort
* O(n^2)
*/
void bubbleSort(int a[], int n){
  int i, j, temp;

  for (i = (n - 1); i >= 0; i--){
    for (j = 1; j <= i; j++){
      if (a[j-1] > a[j]){
        temp = a[j-1];
        a[j-1] = a[j];
        a[j] = temp;
      }
    }
  }
}

// selection sort
// best case:		O(n^2)
// avrg case:		O(n^2)
// worst case:		O(n^2)
void selection_sort(int a[], int n){
  int i, j;
  int min, temp;

  for (i = 0; i < n-1; i++){
    min = i;
    for (j = i+1; j < n; j++){
      if (a[j] < a[min])
        min = j;
    }
    temp = a[i];
    a[i] = a[min];
    a[min] = temp;
  }
}

// insertion_sort
// best case:		O(n)
// avrg case:		O(n^2)
// worst case:		O(n^2)
void insertion_sort(int a[], int n){
    int i, j, index;
    
    for (i = 1; i < n; i++){
        index = a[i];
        j = i;
        while ((j>0)&&(a[j-1] > index)){
            a[j]=a[j-1];
            j=j-1;
        }
        a[j]=index;
    }
}

/*
*	Heap Sort
	The heapsort algorithm works very much like the selection sort algorithm, 
	to understand how heapsort works is to think of it as an extension of selection sort.
	
	Typically, heap sort employs two major optimizations. 
	First, the heap is usually built up in-place inside the array by treating the array itself as a compressed representation of the heap. 
	If you look at a heapsort implementation, you will usually see unusual uses of array indices based on multiplying and dividing by two; 
	these accesses work because they are treating the array as a condensed data structure. As a result, the algorithm requires only O(1) auxiliary storage space.
*/

/*
	The algorithm follows the following main 2 steps:
	1. Heapify/build the heap.
	2. Repeatedly remove the top off the heap.
*/

void heap_sort(int a[], int n){
	int i, temp;

	for (i = (n / 2)-1; i >= 0; i--)
		sift_down(a, i, n);

	for (i = n-1; i >= 1; i--){
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		sift_down(a, 0, i-1);
	}
}

void sift_down(int a[], int root, int bottom){
	int done, maxChild, temp;

	done = 0;
	while ((root*2 <= bottom) && (!done)){
		if (root*2 == bottom)
			maxChild = root * 2;
		else if (a[root * 2] > a[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;

		if (a[root] < a[maxChild]){
			temp = a[root];
			a[root] = a[maxChild];
			a[maxChild] = temp;
			root = maxChild;
		}
		else
		done = 1;
	}
}

int main () {
    int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int n = sizeof a / sizeof a[0];
    heap_sort(a, n);
    int i=0;
    for(; i<n;i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
 