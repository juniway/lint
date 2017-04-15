Merge Sort

/*
The merge sort splits the list to be sorted into two equal halves, and places them in
separate arrays. Each array is recursively sorted, and then merged back together to
form the final sorted list. Like most recursive sorts, the merge sort has an algorithmic
has an complexity of O(n log n).

Elementary implementations of the merge sort make use of three arrays - one for each half
of the data set and one to store the merged sorted list in. The below algorithm merges the arrays
in-place, so only two arrays are required. There are non-recursive versions of the merge sort,
but they don't yield any significant performance enhancement over the recursive algorithm on
most machines.


Pros: Marginally faster than the heap sort for larger sets.

Cons: At least twice the memory requirements of the other sorts; recursive.
*/

如果对Merge的每个递归调用都声明一个临时数组，那么任一时刻可能会有logN个临时数组处于活动期,这对小内存机器是致命的。
另一方面，如果Merge动态分配并释放最小量临时空间，那么由malloc占用的时间会很多。
由于Merge位于MSort的最后一行，可以在MergeSort中建立该临时数组。
因此在任一时刻只需要一个临时数组活动，而且可以使用该临时数组的任意部分；我们将使用和输入数组array相同的部分。
这样的话，该算法的空间占用为N，N是待排序的数组元素个数。

/*
tmp_array[]：辅助数组。
left_pos：数组左半部分的游标
left_end：左边数组的右界限
*/
void Merge(int array[], int tmp_array[], int left_pos, int right_pos, int right_end) {
    int i, left_end, num_elements, tmp_pos;
    left_end = right_pos - 1;
    tmp_pos = left_pos;
    num_elements = right_end - left_pos + 1;

    while (left_pos <= left_end && right_pos <= right_end)
        if (array[left_pos] <= array[right_pos])
            tmp_array[tmp_pos++] = array[left_pos++];
        else
            tmp_array[tmp_pos++] = array[right_pos++];
    while (left_pos <= left_end)
        tmp_array[tmp_pos++] = array[left_pos++];
    while (right_pos <= right_end)
        tmp_array[tmp_pos++] = array[right_pos++];
    for (i = 0; i < num_elements; i++, right_end--)
        array[right_end] = tmp_array[right_end];
}

void MSort(int array[], int tmp_array[], int left, int right) {
    int center;
    if (left < right) {
        center = (left + right) / 2;
        MSort(array, tmp_array, left, center);
        MSort(array, tmp_array, center + 1, right);
        Merge(array, tmp_array, left, center + 1, right);
    }
}

void MergeSort(int array[], int n) {
    int *tmp_array;
        //上面文字部分给出了为什么在MergeSort中建立临时数组tmp_array
        tmp_array = (int *)malloc(n * sizeof(int));
    if (tmp_array != NULL) {
        MSort(array, tmp_array, 0, n - 1);
        free(tmp_array);
    }
    else
        cout << "malloc failed" << endl;
}


#include <stdlib.h>
#include <stdio.h>

void mergeSort(int numbers[], int temp[], int array_size);
void m_sort(int numbers[], int temp[], int left, int right);
void merge(int numbers[], int temp[], int left, int mid, int right);

int numbers[10];
int temp[10];


int main(){
    int i;
    printf("Enter the numbers you want to sort");
    for(i = 0; i < 10; i++)
        scanf("%d", &numbers[i]);

    //perform merge sort on array
    mergeSort(numbers, temp, NUM_ITEMS);
    printf("Done with sort.\n");
    for (i = 0; i < NUM_ITEMS; i++)
        printf("%i\n", numbers[i]);
}

void mergeSort(int numbers[], int temp[], int array_size){
    m_sort(numbers, temp, 0, array_size - 1);
}

void m_sort(int numbers[], int temp[], int left, int right){
    int mid;

    if (left < right){
        mid = (left + right) / 2;
        m_sort(numbers, temp, left, mid);
        m_sort(numbers, temp, mid+1, right);
        merge(numbers, temp, left, mid+1, right);
    }
}

void merge(int numbers[], int temp[], int left, int mid, int right){
    int i, left_end, num_elements, tmp_pos;

    left_end = mid - 1;
    tmp_pos = left;
    num_elements = right - left + 1;

    while ((left <= left_end) && (mid <= right)){
        if (numbers[left] <= numbers[mid]){
            temp[tmp_pos] = numbers[left];
            tmp_pos = tmp_pos + 1;
            left = left +1;
        }
        else{
            temp[tmp_pos] = numbers[mid];
            tmp_pos = tmp_pos + 1;
            mid = mid + 1;
        }
    }

    while (left <= left_end){
        temp[tmp_pos] = numbers[left];
        left = left + 1;
        tmp_pos = tmp_pos + 1;
    }
    while (mid <= right){
        temp[tmp_pos] = numbers[mid];
        mid = mid + 1;
        tmp_pos = tmp_pos + 1;
    }

    for (i=0; i <= num_elements; i++){
        numbers[right] = temp[right];
        right = right - 1;
    }
}



// C program for Merge Sort
#include<stdlib.h>
#include<stdio.h>

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    // create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r){
    if (l < r){
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r-l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

/* Driver program to test above functions */
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}
