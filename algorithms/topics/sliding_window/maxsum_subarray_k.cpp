#include <iostream>

int maxSubarrayKsum(int a[], int n) {
    int res_max = a[0];
    int cur_max = a[0];

    for (int i = 1; i < n; i++) {
        cur_max = std::max(cur_max + a[i], a[i]);
        res_max = std::max(res_max, cur_max);
    }

    return res_max;
}
