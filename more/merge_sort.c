/*
	MergeSort(a[], l, r)
	if r > l

	1. Find the middle point to divide the array into two halves:
		middle m = (l+r) / 2
	2. Call mergesort for first half:
		mergesort(arr, 1, m);
	3. Call mergesort for second half:
		mergesort(arr, m + 1, r);
	4. Merge the two havles sorted in step 2 and step 3:
		merge(arr, l, m, r);
*/


#include <stdlib.h>
#include <stdio.h>

void merge(int *a, int n, int m){
    int *x = malloc(n * sizeof(int));

    int i = 0, j = m, k = 0;

    // for (; k < n; ++k) {
    //     x[k] = j == n      ? a[i++]
    //          : i == m      ? a[j++]
    //          : a[j] < a[i] ? a[j++]
    //          :               a[i++];
    // }
    
    // merge two sorted array
    // 0 is the start index of the first array
    // m is the start index of the second array
    // merge these two arrays
    for(; k < n; ++k){
    	if(i < m && j < n){
    		if(a[i] < a[j]){
    			x[k] = a[i++];
    		}
    		else{
    			x[k] = a[j++];
    		}
    	}
    	else if(i == m){
    		x[k] = a[j++];
    	}
    	else if(j == n){
    		x[k] = a[i++];
    	}
    }

    for (i = 0; i < n; i++) {
        a[i] = x[i];
    }
    free(x);
}

void merge_sort(int *a, int n){
    //

	if(n < 2) return;
	int m = n/2;
    printf("\n**\n");
    printf("n=%d, m=%d", n, m);
    printf("\n**\n");
	merge_sort(a, m);
	merge_sort(a + m, n - m);

	// return
	printf("n=%d, m=%d\n", n, m);
	merge(a, n, m);
}

 
int main () {
    int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int n = sizeof a / sizeof a[0];
    int i = 0;
    // for (; i < n; i++)
    //     printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
    merge_sort(a, n);
    // for (i = 0; i < n; i++)
    //     printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
    return 0;
}