/*
 * Problem:
 * Find the longest substring without repeating characters
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::vector;
using std::string;
using std::cout;

int lengthOfLongestSubstring(string s) {
    int n = s.length();
    if (n < 1) return 1;

    std::unordered_map<char, int> um;

    int i = 0, j = 1;
    um[s.at(i)] = i + 1;
    int maxLen = 1;
    for (; i < j && j < n; ) {
        if (um[s.at(j)] > 0) { // repeat
            for (int k = i; k <= um[s.at(j)] - 1; k++) {
                um[s.at(k)] = 0;
            }
            i += 1;
        } else { // non_repeat
            maxLen = std::max(maxLen, j - i + 1);
        }
        um[s.at(j)] = j + 1;
        j++;
    }

    cout << "(" << i << ", " << j-1 << ")\n";

    return maxLen;
}

int lengthOfLongestSubstring1(string s) {
    vector<int> map(128, 0);
    int begin = 0, end = 0, count = 0, maxLen = 0;

    while(end < s.length()) {
        if(map[s[end++]]++ > 0) count++;
        while (count > 0) if(map[s[begin++]]-- > 1) count--;
        maxLen = std::max(maxLen, end - begin);
    }

    return maxLen;
}

void testLenOfLongestSubstring() {
    string s[4] = {
        {"bcabcbb"}, // 3
        {"abcdeabcbb"}, // 5
        {"aabcefb"}, // 5
        {"aaaaa"}, // 1
    };

    for (int i = 0; i < 4; i++) {
        int maxLen = lengthOfLongestSubstring(s[i]);
        cout << "maxLen: " << maxLen << "\n";
    }
}

int main(int argc, char *argv[]) {
    testLenOfLongestSubstring();
    return 0;
}
