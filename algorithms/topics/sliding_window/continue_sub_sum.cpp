#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool checkSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> map;
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];
        if (k != 0) sum %= k;
        if (map.count(sum) > 0) {
            if (i - map[sum] > 1) return true;
        } else {
            map[sum] = i;
        }
    }

    return false;
}

void testCheckSubarraySum() {
    vector<int> nums {23, 2, 4, 6, 7};
    cout << boolalpha << checkSubarraySum(nums, 6) << endl;
}

int main(int argc, char *argv[]) {
    testCheckSubarraySum();
    return 0;
}
