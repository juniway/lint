#include <iostream>
#include <vector>
#include <string>
using namespace std;

string longesgPalindrom(string s) {
    if (s.length() <= 1) return s;
    int longestSofar = 0, starti = 0, endi = 0;
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    for (int j = 0; j < n; j++) {
        dp[j][j] = true;
        for (int i = 0; i < j; i++) {
            if(s[i] == s[j] && (j - i <= 2 || dp[i + 1][j - 1])) {
                dp[i][j] = true;
                if (j - i + 1 > longestSofar) {
                    longestSofar = j - i + 1;
                    starti = i;
                    endi = j;
                }
            }
        }
    }

    return s.substr(starti, endi - starti + 1);
}

void testLongestPalindrom() {
    cout << longesgPalindrom("ababd") << endl;
    cout << longesgPalindrom("a") << endl;
    cout << longesgPalindrom("") << endl;
    cout << longesgPalindrom("abdce") << endl;
}

int main(int argc, char *argv[]) {
    testLongestPalindrom();
    return 0;
}
