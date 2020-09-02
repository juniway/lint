#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int lower_bound(vector<int>& nums, int target) {
    int l = 0, h = nums.size() - 1;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (nums[mid] >= target) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << "l: " << l << ", h: " << h << endl;

    return l;
}

int upper_bound(vector<int>& nums, int target) {
    int l = 0, h = nums.size() - 1;
    while (l <= h) {
        int mid = l + (h - l + 1) / 2;
        if (nums[mid] <= target) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }

    cout << "l: " << l << ", h: " << h << endl;
    return h;
}

int smallestDifference(vector<int> a, vector<int> b) {
    sort(a.begin(), a.end());
    double ans = INT_MAX;
    for (int k = 0; k < b.size(); k++) {
        int i = 0, j = a.size() - 1;
        while (i <= j) {
            int mid = i + (j - i + 1) / 2;
            if (a[mid] <= b[k])
                i = mid + 1;
            else j = mid - 1;
        }
        ans = min(ans, (double)abs((double)a[j] - (double)b[k]));
        cout << "j: " << j << endl;
        if (j != a.size() - 1)
            ans = min(ans, (double)abs((double)a[j + 1] - (double)b[k]));
    }
    return ans;
}

void testLower() {
    vector<int> nums = {1, 2, 2, 2, 4};
    cout << lower_bound(nums, 2) << endl;
    cout << lower_bound(nums, 3) << endl;
    cout << upper_bound(nums, 2) << endl;
    cout << upper_bound(nums, 3) << endl;
    cout << upper_bound(nums, 5) << endl;
    cout << smallestDifference({9, 48}, {5}) << endl;
}

int main(int argc, char *argv[]) {
    testLower();
    return 0;
}
