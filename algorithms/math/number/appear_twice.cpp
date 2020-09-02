// three different number appear once, others all appear twice
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

void find2AppearOnce(vector<int>& nums, int n,  vector<int>& res) {
    int ab = accumulate(nums.begin(), nums.begin() + n, 0, bit_xor<int>());

    ab &= -ab;
    int seta = 0, setb = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] & ab) seta ^= nums[i];
        else setb ^= nums[i];
    }

    res.push_back(seta);
    res.push_back(setb);
}

vector<int> find3AppearOnce(vector<int>& nums) {
    if (nums.size() < 3) return {};
    int abc = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());

    int bit = abc & (-abc);
    int uniqueNum = 0;
    for (int num : nums) {
        if (bit & num) uniqueNum ^= num;
    }

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == uniqueNum) {
            swap(nums[i], nums[nums.size() - 1]);
            break;
        }
    }

    for (auto x : nums) cout << x << " "; cout << endl;

    vector<int> res;
    res.push_back(uniqueNum);
    cout << uniqueNum << endl;

    find2AppearOnce(nums, nums.size() - 1, res);
    return res;
}


void testFind3AppearOnce() {
    vector<int> a{2, 2, 3, 4, 7, 7, 8, 8, 9};

    auto res = find3AppearOnce(a);
    for(int v : res) cout << v << " "; cout << endl;
}

int main(int argc, char *argv[]) {
    testFind3AppearOnce();
    return 0;
}

