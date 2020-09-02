/* Leetcode 159
 * Longest Substring with At Most Two Distinct Characters
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;
using std::cout;

int lengthOfLongestSubstringTwoDistinct(string s) {
    vector<int> map(128, 0);
    int begin = 0, end = 0, maxLen = INT_MIN, count = 0;

    while(end < s.length()) {
        if(map[s[end++]]++ == 0) count++;
        while (count > 2) if (map[s[begin++]]-- == 1) count--;
        maxLen = std::max(maxLen, end - begin);
    }

    return maxLen;
}

int atMostKDistinct(string s, int k) {
    vector<int> map(128, 0);
    int begin = 0, end = 0, res = 0;
    while(end != s.size()) {
        if (map[s[end++]]++ == 0) k--;
        while (k < 0) {
            if (--map[s[begin]] == 0) k++;
            begin++;
        }
        res += end - begin;
    }

    return res;
}

int atMostK(vector<int>& A, int K) {
    int i = 0, res = 0;
    unordered_map<int, int> count;
    for (int j = 0; j < A.size(); ++j) {
        if (count[A[j]]++ == 0) K--;
        while (K < 0) {
            if (--count[A[i]] == 0) K++;
            i++;
        }
        res += j - i + 1;
    }
    return res;
}

void testAtMostK() {
    string s {"12123"};
    cout << atMostKDistinct(s, 2) << "\n";
    vector<int> A{1, 2, 1, 2, 3};
    cout << atMostK(A, 2) << "\n";
}

int main(int argc, char *argv[]) {
    testAtMostK();
    return 0;
}
