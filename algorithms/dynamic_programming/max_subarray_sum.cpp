#include <iostream>
#include <vector>

using namespace std;

vector<int> maxSubarraySumIJ(int a[], int n) {
    int res_max = a[0];
    int local_max = a[0];

    int start_i = 0;
    int end_i = 0;

    for (int i = 1; i < n; i++) {
        if (local_max + a[i] < a[i]) {
            local_max = a[i];
            start_i = i;
        } else {
            local_max += a[i];
        }

        if (res_max < local_max) {
            res_max = local_max;
            end_i = i;
        }

    }

    cout << res_max << "\n";

    return {start_i, end_i};
}

// kadane
int maxSubarraySum(int a[], int n) {
    assert(n > 0);
    int res_max, local_max;
    res_max = local_max = a[0];

    for (int i = 1; i < n; i++) {
        local_max = std::max(local_max + a[i], a[i]);
        res_max = std::max(res_max, local_max);
    }

    return res_max;
}

// dp
int maxSumDp(vector<int> a) {
    if (a.empty()) return 0;
    vector<int> sumAt(a.size() + 1, 0);
    // sumAt[1] = nums[0];
    sumAt[0] = a[0];
    int maxSum = a[0];
    for (int i = 1; i <= a.size(); i++) {
        sumAt[i] = max(sumAt[i-1] + a[i - 1], a[i - 1]);
        maxSum = max(maxSum, sumAt[i]);
    }

    return maxSum;
}

void testMssIJ() {
    int a[] {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    auto res = maxSubarraySumIJ(a, 9);
    cout << "{" << res[0] << ", " << res[1] << "}\n";
}

void testMss() {
    int a[] {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int res = maxSumDp(vector<int>{begin(a), end(a)});
    cout << "max sum: " << res << "\n";
}

int main(int argc, char *argv[]) {
    // testMssIJ();
    testMss();
    return 0;
}
