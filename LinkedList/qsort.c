#include <cstdio>

void qsort(int *a, int N, int left, int right){
	int i = left, j = right;

	if(left > right) return;

	while(i < j){
		while(a[j] >= a[left] && j > i){
			--j;
		}
		while(a[i] <= a[left] && i < j){
			++i;
		}

		if(i < j){
			std::swap(a[i], a[j]);
		}
	}

	a[left] = a[i];
	a[i] = pivot;

	qsort(a, left, i - 1);
	qsort(a, i + 1, right);

}

void print_arr(int* a, int N){
	printf("qsort:");
	for(int i = 0; i < N; ++i){
		printf("%d ", a[i]);
	}
	printf("\n");
}


int main(){

	int a[] = {2, 10, 4, 7, 9, 3, 11, 5, 19, 8};
	int N = sizeof a / a[0];

	qsort(a, N);

	print_arr(a, N);

	return 0;
}