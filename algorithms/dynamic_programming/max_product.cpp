#include <iostream>
#include <vector>
using namespace std;


int maxProduct(vector<int>& nums) {
    int res = nums[0], imax = nums[0], imin = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] < 0) swap(imax, imin);
        imax = max(nums[i], imax * nums[i]);
        imin = min(nums[i], imin * nums[i]);

        res = max(res, imax);
    }

    return res;
}

void testMaxProduct() {
    vector<int> nums {2, 3, -2, 4};
    cout << maxProduct(nums) << endl;
}

int main(int argc, char *argv[]) {
    testMaxProduct();
    return 0;
}
