#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

int characterReplacement(string s, int k) {
    if (s.size() < k) return 0;

    vector<int> m(128, 0);
    int begin = 0, end = 0, maxCnt = 0;
    while (end < s.length()) {
        maxCnt = std::max(maxCnt, ++m[s[end]]);
        if(maxCnt + k <= end - begin) {
            m[s[begin++]]--;
        }
        end++;
    }

    return s.length() - begin;
}
