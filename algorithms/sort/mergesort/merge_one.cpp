#include <iostream>
#include <vector>
using namespace std;

void mergeOne(vector<int>& nums, int left, int mid, int right) {
    vector<int> part1(nums.begin() + left, nums.begin() + mid + 1);
    vector<int> part2(nums.begin() + mid + 1, nums.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < part1.size() || j < part2.size()) {
        if (j == part2.size() || (i < part1.size() && part1[i] <= part2[j])) {
            nums[k++] = part1[i++];
        }
        else nums[k++] = part2[j++];
    }
}

void mergeOne1(vector<int>& nums, int left, int mid, int right) {
    vector<int> part1(nums.begin() + left, nums.begin() + mid + 1);
    vector<int> part2(nums.begin() + mid + 1, nums.begin() + right + 1);

    int i = 0, j = 0;
    while (i < part1.size() || j < part2.size()) {
        if (j == part2.size() || (i < part1.size() && part1[i] <= part2[j])) {
            nums[i + j] = part1[i];
            i++;
        }
        else {
            nums[i + j] = part2[j];
            j++;
        }
    }
}

// space optimized
void mergeOne(vector<int>& nums, vector<int>& aux, int left, int mid, int right) {
    aux = nums;
    int i = left, j = mid + 1, k = left;
    while (i <= mid || j <= right) {
        if (j > right || (i <= mid && aux[i] < aux[j]))
            nums[k++] = aux[i++];
        else
            nums[k++] = aux[j++];
    }
}

void testMergeOne() {
    vector<int> nums = {1, 3, 4, 8, 2, 6, 9};
    for (int num : nums) cout << num << " "; cout << endl;

    vector<int> aux;
    // mergeOne(nums, aux, 0, 3, 6);
    mergeOne1(nums, 0, 3, 6);
    for (int num : nums) cout << num << " "; cout << endl;
}

int main(int argc, char *argv[]) {
    testMergeOne();
    return 0;
}
