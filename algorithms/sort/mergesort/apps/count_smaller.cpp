#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        if (nums.size() == 0) return {};

        vector<vector<int>> hold;
        for (int i = 0; i < nums.size(); i++) {
            hold.push_back({nums[i], i});
        }

        vector<int> smaller(hold.size(), 0);
        mergeSort(hold.begin(), hold.end(), smaller);
        return smaller;
    }

    typedef vector<vector<int>>::iterator Iter;
    void mergeSort(Iter left, Iter right, vector<int>& smaller) {
        if (right - left <= 1) return;

        Iter mid = left + (right - left) / 2;
        mergeSort(left, mid, smaller);
        mergeSort(mid, right, smaller);

        Iter i = left, j = mid;
        while (i != mid || j != right) {
            if (j == right || (i != mid && (*i)[0] <= (*j)[0])) {
                smaller[(*i)[1]] += j - mid;
                i++;
            } else {
                j++;
            }
        }
        inplace_merge(left, mid, right);
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
