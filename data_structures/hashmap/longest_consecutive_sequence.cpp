// Leetcode 128. Longest Consecutive Sequence
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int longestConsecutive(vector<int>& nums) {
    unordered_map<int, int> nmap;
    int res = 0;
    for (int n : nums) {
        if (nmap.find(n) == nmap.end()) {
            int left = nmap.count(n - 1) ? nmap[n - 1] : 0;
            int right = nmap.count(n + 1) ? nmap[n + 1] : 0;
            int len = left + right + 1;
            nmap[n] = len;

            res = max(res, len);
            nmap[n - left] = len;
            nmap[n + right] = len;
        } else {
            continue;
        }
    }

    return res;
}

void testLC() {
    vector<int> nums = {1, 2, 12, 14, 13};
    cout << longestConsecutive(nums) << endl;
}

int main(int argc, char *argv[]) {
    testLC();
    return 0;
}
