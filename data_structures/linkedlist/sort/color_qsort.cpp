#include <cstdio>
#include <algorithm>
#include <exception>
#include <iostream>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

static const int N = 10;

void print_array(int data[], int length, int pivot_index, int left, int right){
	for(int i = 0; i < length; ++i){
		if(i == pivot_index)
			printf(ANSI_COLOR_YELLOW "%d " ANSI_COLOR_RESET, data[i]);
		else if((i == left && i != pivot_index) || i == right)
			printf(ANSI_COLOR_RED "%d " ANSI_COLOR_RESET, data[i]);
		else
			printf("%d ", data[i]);
	}
	printf("\n");
}

void quicksort(int a[], int length, int left, int right){

	printf("left = %d, right = %d \n", left, right);

	int i, j, t, pivot;
	if(left > right) return;

	pivot = a[left]; // choose the first element as the pivot
	i = left;
	j = right;

	printf("i = %d, j = %d \n", i , j);
	printf("start: ");
	print_array(a, length, left, i, j);
	while(i != j){
		// j moves first
		// 从右往左走（j--），直到找到第一个大于pivot的
		while(a[j] >= pivot && i < j)
			j--;

		// then i move
		// 从左往右走（i++），直到找到第一个小于pivot的
		while(a[i] <= pivot && i < j)
			i++;

		printf("i = %d, j = %d \n", i , j);
		// swap(a[i], a[j]);
		printf("before swap: ");
		print_array(a, length, left, i, j);

		// 确保i, j不交叉，交换a[i], a[j]
		if(i < j){
			t = a[i];
			a[i] = a[j];
			a[j] = t;

			printf("after swap:  ");
			print_array(a, length, left, i, j);
		}
	}

	// at the end of a round, i==j, we put pivot to its place
	a[left] = a[i];
	a[i] = pivot;
	printf("round: ");
	print_array(a, length, left, left, i);
	printf("\n");

	if(left < i - 1)
		quicksort(a, length, left, i - 1);
	if(i + 1 < right)
		quicksort(a, length, i + 1, right); // left is updated to i + 1
}



void Swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int Partition(int data[], int length, int start, int end){
	if(data == nullptr || length <= 0
		|| start < 0 || end >= length){
		throw new std::runtime_error("Invalid Parameters");
	}

	int small = start - 1;
	printf("start: ");
	print_array(data, length, end, start, end);
	for (int i = start; i < end; ++i) {
		if(data[i] < data[end]){
			++small;
			if(small != i){
				Swap(&data[small], &data[i]);
				printf("swap:  ");
				print_array(data, length, end, small, i);
			}
		}
	}
	++small;
	Swap(&data[small], &data[end]);
	printf("round: ");
	print_array(data, length, end, small, end);
	printf("return small = %d\n", small);
	return small;
}

void Quicksort01(int data[], int length, int start, int end){
	printf("start = %d, end = %d\n", start, end);
	if(start == end) return;
	int index = Partition(data, length, start, end);
	if(index > start)
		Quicksort01(data, length, start, index - 1);
	if(index < end)
		Quicksort01(data, length, index + 1, end);
}



int main(){
	int a[] = {2, 10, 4, 7, 9, 3, 11, 5, 19, 8};

	// printf("%c[%d;%dm%d %c[%dm\n", 27, 1, 33, 18, 27, 0);
	// printf("%s %s %s", Color_Red, "aaaa", Color_end);

	// printf(ANSI_COLOR_RED "%d" ANSI_COLOR_RESET "\n", 2000);
	// quicksort(a, N, 0, N - 1);



	Quicksort01(a, N, 0, N - 1);

	// system("bash read -p \"Press a key to continue...\" -n 1 -s");
	return 0;
}