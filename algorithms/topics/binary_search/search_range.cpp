// Leetcode 34. Find First and Last Position of Element in Sorted Array

#include <iostream>
#include <vector>

using namespace std;

vector<int> searchRange(const vector<int>& nums, int target) {
    if (nums.size() == 0) return {-1, -1};
    int res[2] = {-1, -1};

    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    if (nums[left] == target)
        res[0] = left;

    right = nums.size() - 1;

    // search upper_bound of 2 in [2, 2, 2]
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= target) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    cout << "[" << nums[left] << ", " << nums[right] <<"]" << endl;
    cout << left << " " << right << endl;
    if (nums[left] == target)
        res[1] = left;

    return vector<int>(res, res + 2);
}

void testSearchRange() {
    auto res = searchRange({2, 2, 2}, 2); // {0, 2}
    cout << res[0] << ", " << res[1] << endl;
    //
    res = searchRange({1, 1, 8, 8, 9}, 8); // {2, 3}
    cout << res[0] << ", " << res[1] << endl;

    res = searchRange({1, 8, 8, 9}, 2); // {-1, -1}
    cout << res[0] << ", " << res[1] << endl;
}

int main(int argc, char *argv[]) {
    testSearchRange();
    return 0;
}
