#include <iostream>
#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> aux;
public:
    vector<int> countSmaller(vector<int>& nums) {
        if (nums.size() == 0) return {};

        vector<vector<int>> hold;
        for (int i = 0; i < nums.size(); i++) {
            hold.push_back({nums[i], i});
        }

        vector<int> smaller(hold.size(), 0);
        mergeSort(hold, 0, hold.size() - 1, smaller);
        return smaller;
    }

    void mergeSort(vector<vector<int>>& arr, int left, int right, vector<int>& smaller) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, smaller);
        mergeSort(arr, mid + 1, right, smaller);

        aux = arr;
        int i = left, j = mid + 1, k = left;
        while (i <= mid || j <= right) {
            if (j > right || (i <= mid && aux[i][0] <= aux[j][0])) {
                smaller[aux[i][1]] += j - mid - 1;
                arr[k++] = aux[i];
                i++;
            } else {
                arr[k++] = aux[j++];
            }
        }
    }
};

void testCountSmaller() {
    vector<int> nums = {5, 2, 6, 1};

    Solution sol;
    auto res = sol.countSmaller(nums);
    for (int v : res) cout << v << " "; cout << endl;
}

int main(int argc, char *argv[]) {
    testCountSmaller();
    return 0;
}
