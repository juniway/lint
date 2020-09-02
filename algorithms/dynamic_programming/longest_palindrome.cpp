#include <iostream>
#include <vector>
#include <string>
using namespace std;

string longestPalindrome(string s) {
    int len = s.length();
    if (len == 0) return "";
    int longestSoFar = 0, startIndex = 0, endIndex = 0;
    vector<vector<bool>> palindrom(len, vector<bool>(len, false));
    for (int j = 0; j < len; j++) {
        palindrom[j][j] = true;
        for (int i = 0; i < j; i++) {
            if(s[i] == s[j] && (j-i <= 2 || palindrom[i+1][j-1])) {
                palindrom[i][j] = true;
                if (j - i + 1 > longestSoFar) {
                    longestSoFar = j - i + 1;
                    startIndex = i;
                    endIndex = j;
                }
            }
        }
    }

    return s.substr(startIndex, endIndex - startIndex + 1);
}

string longestPalindrome1(string s) {
    int n = s.length();
    if (n == 0) return "";
    vector<vector<bool>> isPalindrom(n, vector<bool> (n, false));
    string res = "";

    for (int len = 1; len < n + 1; len++) {
        for (int begin = 0; begin < n; begin++) {
            int end = begin + len - 1;
            if (end >= n) break;
            if (len == 1)
                isPalindrom[begin][end] = true;
            else if (len == 2)
                isPalindrom[begin][end] = s[begin] == s[end];
            else isPalindrom[begin][end] = (s[begin] == s[end] && isPalindrom[begin+1][end-1]);

            if(isPalindrom[begin][end])
                res = s.substr(begin, end - begin + 1);
        }
    }
    return res;
}

void testLongestPalindrome() {
    string s = "abba";
    string s1 = "aba";
    string s2 = "a";
    cout << longestPalindrome(s) << endl;
    cout << longestPalindrome(s1) << endl;
    cout << longestPalindrome(s2) << endl;
    cout << longestPalindrome1(s2) << endl;
}

int main(int argc, char *argv[]) {
    testLongestPalindrome();
    return 0;
}
