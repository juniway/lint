#include <iostream>
#include <vector>
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
        int mid = l + (h - l)/ 2;
        if (nums[mid] <= target) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }

    cout << "l: " << l << ", h: " << h << endl;
    return l;
}


void testLower() {
    vector<int> nums = {1, 2, 2, 2, 4};
    // cout << lower_bound(nums, 2) << endl;
    // cout << lower_bound(nums, 3) << endl;
    cout << upper_bound(nums, 2) << endl;
    cout << upper_bound(nums, 5) << endl;
}

int main(int argc, char *argv[]) {
    testLower();
    return 0;
}
