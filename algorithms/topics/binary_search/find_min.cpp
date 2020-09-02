#include <iostream>
#include <vector>

using namespace std;

int findMin(vector<int> &nums) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        if (nums[left] <= nums[right]) return nums[left];
        int mid = (left + right) / 2;
        if (nums[mid] >= nums[0])
            left = mid + 1;
        else
            right = mid;
    }
    // cout << left << " " << right << " " << mid << endl;
    return nums[left];
}

int findMin1(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (nums[left] < nums[mid])
            left = mid;
        else if (nums[left] > nums[mid])
            right = mid;
        else
            break;
    }
    return min(nums[left], min(nums[right], nums[0]));
}

void testFindMin() {
    vector<vector<int>> nums {
        {5, 6, 7, 8, 0, 1, 2},
        {2, 1},
    };
    cout << findMin(nums[0]) << endl;
    cout << findMin(nums[1]) << endl;

    cout << findMin1(nums[0]) << endl;
    cout << findMin1(nums[1]) << endl;
}

int main(int argc, char *argv[]) {
    testFindMin();
    return 0;
}
