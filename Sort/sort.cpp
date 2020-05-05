#include <stdio.h>

/* 
* Bubble Sort
* O(n^2)
*/
void bubbleSort(int a[], int n){
  for (int i = n-1; i >= 0; i--){
    for (int j = 1; j <= i; j++){
      if (a[j-1] > a[j]){
        int temp = a[j-1];
        a[j-1] = a[j];
        a[j] = temp;
      }
    }
  }
}

// selection sort
// best case:        O(n^2)
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
        j = i - 1;
        while (j > 0 && a[j] > index){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = index;
    }
}

/*
*	Heap Sort
*/
#define LeftChild(i) 2*(i)+1
#define RightChild(i) 2*(i)+2

void adjustHeap(int A[], int i, int n){ // same meaning with sift_down()
    int left = LeftChild(i);    // #define LeftChild(i) 2*(i)+1   //node i's left child
	int right = RightChild(i);	// #define RightChild(i) 2*(i)+2  //node i's right child
	int max = i;
	int temp;

	while(left < n){ // if it has left child
		if (A[max] < A[left])  // if it is less than the left child, set max to left
			max = left;

		if (right < n && A[max] < A[right])  // if it has right child and left child is less than right, set max to right
			max = right;
		
		if (i!= max){  //if the current node is not the max node, we need to swap
			temp = A[max];
			A[max] = A[i];
			A[i] = temp;

			i = max;			//new max
			left = LeftChild(i);		// #define LeftChild(i) 2*(i)+1   //node i's left child
			right = RightChild(i);		// #define RightChild(i) 2*(i)+2  //node i's right child
		}
		else
			break;
	}
}

void heap_sort(int A[], int n) {
	int i,temp;
	
	// build the heap from array
	int begin = n/2 - 1;  //the last node that has no leaf child
	for (i = begin; i >= 0; i--){
		adjustHeap(A, i, n);
	}
	
	while (n > 1){
		/*
		* remove the rightmost leaf at the deepest level and use it for the new root
		* swap root with the rightmost node at the deepest level, which means swap the first and last element of the array.
		*/
		temp = A[n-1];  
		A[n-1] = A[0];
		A[0] = temp;
		n--;        //heap size decrease by 1
		
		adjustHeap(A, 0, n);
	}
}


/*
	Driver program
*/
void print_result(int a[], int n){
    int i=0;
    for(; i<n;i++)
        printf("%d ", a[i]);
    printf("\n");
}

void test_data(void(f)(int*, int)) {
    int ilist [][10] = {
        {4, 65, 2, -31, 0, 99, 2, 83, 782, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2}
    };

    int n = sizeof ilist / sizeof ilist[0];
    for (int i = 0; i < n; i++) {
        f(ilist[i], 10);
        print_result(ilist[i], 10);
    }
}

void bubble(int a[], int n) {
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++){
            if(a[j] > a[j+1]) {
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
}


int main () {
    int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int n = sizeof a / sizeof a[0];
    insertion_sort(a, n);
    print_result(a, n);
    
    // heap_sort(a, n);
    // print_result(a, n);
    // test_data(bubbleSort);
    // test_data(bubble);
    
    return 0;
}
