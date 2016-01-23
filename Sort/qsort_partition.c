
#include <stdio.h>
#include <string.h>

void Swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


void partition(int a[], int start, int end){
	if(a == NULL || start > end){
		return;
	}

	// set a[end] as the pivot
	// put elements smaller than pivot on left
	int small = start - 1;
	for (int i = start; i < end; ++i) {
		if(a[i] < a[end]){
			++small;
			if(small != i){ // not necessary
				Swap(&a[small], &a[i]);
			}
		}
	}
	++small;
	Swap(&a[small], &a[end]);

	// we can simple return small
	// return small;

	partition(a, start, small - 1);
	partition(a, small + 1, end);
}

int PartitionAroundPivot(vector<int>& nums, int left, int right, int pivot_idx) {
    int pivot_value = nums[pivot_idx];
    int new_pivot_idx = left;
    swap(nums[pivot_idx], nums[right]);
    for (int i = left; i < right; ++i) {
        if (nums[i] > pivot_value) {
            swap(nums[i], nums[new_pivot_idx++]);
        }
    }
    swap(nums[right], nums[new_pivot_idx]);
    return new_pivot_idx;
}

int partition_around_pivot(int[] A, int left, int right, int pivot_index){
	int pivot = A[pivot_index];
	int new_pivot_idx = left;
	swap(A[right], A[pivot_index]);

	for(int i = left; i < right; ++i){
		if(A[i] > pivot)
			swap(A[i], A[new_pivot_idx++]);
	}

	swap(A[new_pivot_idx], A[right]);
	return new_pivot_idx;
}

int findkth(int A[], int left, int right){

	while(left <= right){
		int index = gen(rand);
		int new_idx = partition_around_pivot(A, left, right, index);
		if(new_idx == k - 1)
			return A[new_idx];
		else if(new_idx < k - 1)
			left = new_idx + 1;
		else
			right = new_idx - 1;

	}
}

void print_arr(int* a, int N){
	printf("qsort:");
	int i = 0;
	for(; i < N; ++i){
		printf("%d ", a[i]);
	}
	printf("\n");
}



int main(){
	int a[] = {2, 10, 4, 7, 9, 3, 11, 5, 19, 8};

	int len = sizeof(a) / sizeof(a[0]);
	printf("%d\n", len);

	partition(a, 0, len - 1);

	print_arr(a, len);

	// char *s="ab\0cdef";
	// printf("sizeof:%d, strlen: %d, str=%s\n", sizeof s, strlen(s), s);

	return 0;
}

