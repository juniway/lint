/* Leetcode 438
 * Fine all anagrams in a string
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::string;
using std::vector;
using std::cout;

std::vector<int> findAnagrams(string s, string p) {
    vector<int> pv(128, 0), sv(128, 0), res;
    if (s.size() < p.size()) return res;

    for(int i = 0; i < p.size(); i++) {
        pv[p[i]]++;
        sv[s[i]]++;
    }

    if (pv == sv) res.push_back(0);

    for (int i = p.size(); i < s.size(); i++) {
        sv[s[i]]++;
        sv[s[i - p.size()]]--;
        if (pv == sv) res.push_back(i - p.size() + 1);
    }

    return res;
}


std::vector<int> findAnagrams1(string s, string p) {
    if (s.size() < p.size()) return {};
    vector<int> map(128, 0), res;

    for(auto a: p) map[a]++;

    int begin = 0, end = 0, count = p.size();

    while(end < s.size()) {
        if (map[s[end++]]-- > 0) count--;
        while(count == 0) {
            if (end - begin == p.size()) res.push_back(begin);
            if(map[s[begin++]]++ == 0) count++;
        }
    }

    return res;
}

// Leetcode 567
bool checkInclusion(string s1, string s2) {
    if (s1.size() > s2.size()) return false;

    vector<int> map(128, 0);
    for(auto a: s1) map[a]++;

    int begin = 0, end = 0, count = s1.size();
    while(end != s2.size()) {
        if (map[s2[end++]]-- > 0) count--;
        while(count == 0) {
            if (end - begin == s1.size()) return true;
            if (map[s2[begin++]]++ == 0) count++;
        }
    }

    return false;
}

void testAnagramInString() {
    // string s[2][2] = {
    //     {"abab", "ab"},
    //     {"cbaebabacd", "abc"},
    // };
    string s = "abab", p = "ab";
    string s1 = "cbaebabacd", p1 = "abc";

    cout << "===" << "\n";
    std::vector<int> v = findAnagrams(s, p);
    cout << "[";
    for (auto x : v) {
        cout << x << ", ";
    }
    cout << "]\n";

    cout << "===" << "\n";
    std::vector<int> v1 = findAnagrams(s1, p1);
    cout << "[";
    for (auto x : v1) {
        cout << x << ", ";
    }
    cout << "]\n";
}

// void testAnagramInString1() {
//     // string s = "abab", p = "ab";
//     // string s1 = "cbaebabacd", p1 = "abc";
//
//     string s = "baa", p = "aa";
//     findAnagrams1(s, p);
//     // findAnagrams1(s1, p1);
// }

int main(int argc, char *argv[]) {
    // testAnagramInString();
    // testAnagramInString1();
    int a, b = 1;
    cout << (a=5) << "\n";
    return 0;
}
