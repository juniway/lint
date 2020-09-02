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
