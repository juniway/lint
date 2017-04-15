
#include <stdio.h>
#include <string.h>

// partition
// 分析：
// 先选定一个元素作为中枢轴 Pivot，默认通常选取数组头或者数组尾，即使是其他 Index 也把其与数组头或尾交换位置。

// 方法一
// pivot 取第一个元素的下标，遍历元素（2个游标 indexer）从第二个元素开始，

// 具体算法：
// 一个指针 k 用于遍历，一个指针 marker 只要 k 位置当前的元素小于 a[pivot] 的值，++marker，
// 否则 marker 不动直到 k 遇到下一个小于 pivot 的值，交换 a[++marker] 和 a[k]
// 遍历结束条件是 k 移动到数组末尾，此时，交换 a[pivot] 和 a[marker]
// partition 过程结束后： marker 位置左边都是小于 a[marker] 的元素，右边的都是大于 a[marker] 的元素

// 方法二
// pivot 取第一个元素，遍历元素时，两个游标，如：游标 i 从第二个元素往右移动，游标 j 从数组尾向左移动
// 具体算法：
//

// 方法一与方法二比较分析：
// 方法一
// 交换次数：元素交换次数稍多，因为移动范围小
// 游标移动：游标移动较少，因为大部分是 k 在移动，而 marker 移动较少
// 方法二
// 交换次数：元素交换较少，因为一次性移动到末尾了
// 游标移动：两个游标每个移动一半，也比方法一要少

// method 1
int partition1(vector<int>& a, int low, int high) {
	int pivot = low;
	int marker = low;
	for (int k = low + 1; k <= high - 1; ++k) {
		if (a[k] <= a[pivot]) {
			swap(a[++marker], a[pivot]);
		}
	}
	swap(a[pivot], a[marker]);
	return marker;
}

// method 2
int partition2(vector<int>& a, int low, int high) {
	int i = low, j = high;
	if (low >= high) return -1;
	int pivot = low, P = a[pivot];
	while (true) {
		while (a[++i] <= P) {
			if (i >= j) break;
		}
		while(a[--j] >= P) {
			if (i >= j) break;
		}
		if (i >= j) break;
		swap(a[i], a[j]);
	}
	swap(a[--i], a[pivot]); // a[--i] 与 a[j] 等效
	return i;
}

// 直接使用 partition 分治处理得到 sort 结果
// 这里注意，由于分开的两部分需要在中间收敛，所以需要采取两端闭合的区间（也即 [low, high]）！这点非常重要！
void partition3(vector<int>& a, int low, int high){
    if(low >= high){
        return;
    }

    int marker = low;
    for (int i = low + 1; i <= high; ++i) {
        if(a[i] < a[low]){
            swap(a[++marker], a[i]);
        }
    }
    swap(a[marker], a[low]);

    partition3(a, low, marker);
    partition3(a, marker+1, high);
}

// given a pivot index, partition the input array
int partition_around_pivot(vector<int>& nums, int left, int right, int pivot_idx) {
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

// quick sort
void quickSort(vector<int>& arr, int left, int right) {
      int index = partition(arr, left, right);
      if (left < index - 1)
            quickSort(arr, left, index - 1);
      if (index < right)
            quickSort(arr, index, right);
}

// 找到第 k 大的元素，注意顺序，第 k 大的意思是从大到小排列的。
// 先找 pivot 下标 idx，如果下标 idx == k，即找到
// 如果 idx < k，在 [idx + 1, end) 继续找 idx_1
// 如果 idx > k, 在 [0, idx-1] 继续找 idx_2
int findkth(int A[], int left, int right, int k) {
	srand(static_cast<unsigned int>(time(0)));
	while(left <= right) {
		int index = gen_rand(left, right);
		int new_idx = partition_around_pivot(A, left, right, index);
		if(new_idx == k - 1)
			return A[new_idx];
		else if(new_idx < k - 1)
			left = new_idx + 1;
		else
			right = new_idx - 1;
	}
}

int gen_rand(left, right) {
	return min + rand()%(right-left + 1);
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

