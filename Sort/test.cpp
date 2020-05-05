#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(const vector<int>& arr) {
    if (arr.size() == 0) return;
    for(auto &i: arr) {
        cout << i << " ";
    }
    cout << endl;
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = high;
    int i = low - 1;
    for (int k = low; k <= high - 1; ++k) {
        if (arr[k] <= arr[pivot]) {
            swap(arr[++i], arr[k]);
        }
    }
    swap(arr[i+1], arr[high]);
    print(arr);
    return i + 1;
}

int partition1(vector<int>& arr, int low, int high) {
    int pivot = low;
    int marker = low;

    for(int k = low + 1; k <= high - 1; ++k) {
        if (arr[k] <= arr[pivot]) {
            swap(arr[++marker], arr[k]);
        }
    }
    swap(arr[marker], arr[low]);
    return marker;
}

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
    swap(a[j], a[pivot]); // a[--i] 与 a[j] 等效
    return i;
}

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

    // return;
    partition3(a, low, marker);
    partition3(a, marker+1, high);
}

int gen_rand(int left, int right) {
    return left + rand()%(right-left + 1);
}

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

int findkth(vector<int>& A, int left, int right, int k) {
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
    return -1;
}

void insertion_sort(const vector<int>& A) {
    int n = A.size();
    for(int i = 0; i < n-1;) {
        for (int j = 0; j < n - i; j++) {
            
        }
    }
    
}

int main() {
    vector<int> arr = { 10, 9, 18, 5, 1, 7, 12, 8 };
    print(arr);
    partition3(arr, 0, arr.size() - 1);
    print(arr);
    cout << "kth element is: " << findkth(arr, 0, 7, 3) << endl;
}
