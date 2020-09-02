#include <iostream>
#include <limits>

int max(int a, int b, int c) {
    return std::max(std::max(a, b), c);
}

int maxCrossingSum(int a[], int low, int mid, int high) {
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = mid; i >= low; i--) {
        sum = sum + a[i];
        if (sum > left_sum)
            left_sum = sum;
    }

    sum = 0;
    int right_sum = INT_MIN;
    for (int j = mid + 1; j <= high; j++) {
        sum = sum + a[j];
        if (sum > right_sum)
            right_sum = sum;
    }
    return max(left_sum + right_sum, left_sum, right_sum);
}

int maxSubarraySum(int a[], int low, int high) {
    if (low >= high) return a[low];
    int mid = low + (high - low) / 2;
    return max(maxSubarraySum(a, low, mid),
            maxSubarraySum(a, mid + 1, high),
            maxCrossingSum(a, low, mid, high));
}

void testMaxSubarraySum() {
    int a[]{-2, -5, 6, -2, -3, 1, 5, -6};
    std::cout << maxSubarraySum(a, 0, 7) << "\n";
}

int main(int argc, char *argv[]) {
    testMaxSubarraySum();
    return 0;
}
