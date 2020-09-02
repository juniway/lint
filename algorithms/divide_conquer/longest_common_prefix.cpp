#include <iostream>
#include <string>

using std::string;

string CommonPrefixUtil(string s1, string s2) {
    int l1 = s1.size(), l2 = s2.size();
    int n = (l1 <= l2 ? l1:l2 );
    int i = 0;

    while(i < n) {
        if (s1.at(i) != s2.at(i)) break;
        i++;
    }

    // std::cout << s1.substr(0, i) << "\n";

    return s1.substr(0, i);
}

string longestCommonPrefix(string s[], int low, int high) {
    // if (low == high) return s[low];
    // if (low + 1 == high) return CommonPrefixUtil(s[low], s[high]);
    if(low == high) return s[low];

    int mid = low + (high - low) / 2;
    string left_lcp = longestCommonPrefix(s, low, mid);
    string right_lcp = longestCommonPrefix(s, mid + 1, high);
    return CommonPrefixUtil(left_lcp, right_lcp);
}

void testLongestCommonPrefix() {
    string s[]{"geekers", "geeksforgeeks", "geeta", "geeeeeee", "geeky", "geeeoooo", "gee111"};
    std::cout << longestCommonPrefix(s, 0, 4) << "\n";
}

int main(int argc, char *argv[]) {
    testLongestCommonPrefix();
    return 0;
}
