#include <iostream>
#include <vector>

using namespace std;

int merge(vector<int>& nums, int left, int mid, int right) {
    int n1 = mid + 1 - left, n2 = right - mid;
    vector<int> part1(nums.begin() + left, nums.begin() + mid + 1);
    vector<int> part2(nums.begin() + mid + 1, nums.begin() + right + 1);

    int i = 0, j = 0, k = left, inversions = 0;
    while (i < n1 || j < n2) {
        if (i == n1) nums[k++] = part2[j++];
        else if (j == n2) nums[k++] = part1[i++];
        else if (part1[i] <= part2[j]) nums[k++] = part1[i++];
        else {
            nums[k++] = part2[j++];
            int cnt = mid + 1 - (left + i);
            inversions += cnt;
        }
    }
    return inversions;
}

int divide(vector<int>& nums, int left, int right) {
    if (left >= right) return 0;
    int mid = (left + right) / 2;
    int leftInversions = divide(nums, 0, mid);
    int rightInversions = divide(nums, mid + 1, right);
    int mergedInversion = merge(nums, left, mid, right);
    return leftInversions + rightInversions + mergedInversion;
}

int countInversions(vector<int>& nums) {
    return divide(nums, 0, nums.size() - 1);
}

void testCountInversions() {
    // vector<int> a = {1, 4, 2, 3};
    vector<int> a = {5, 2, 6, 1};
    cout << countInversions(a) << endl;
}

int main(int argc, char *argv[]) {
    testCountInversions();
    return 0;
}
