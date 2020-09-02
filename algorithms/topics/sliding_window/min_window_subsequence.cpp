#include <iostream>
#include <vector>
#include <string>

using namespace std;


string minWindow(string S, string T) {
    int minLen = INT_MAX;
    string result = "";
    int right = 0;
    while (right < S.length()) {
        int i = 0;
        while (right < S.length()) {
            if (S[right] == T[i]) {
                i++;
            }
            if (i == T.length()) {
                break;
            }
            right++;
        }
        if (right == S.length()) {
            break;
        }

        // use another slow pointer to traverse from right to left until find first character of T in S
        int left = right;
        i = T.length() - 1;
        while (left >= 0) {
            if (S[left] == T[i]) {
                i--;
            }
            if (i < 0) {
                break;
            }
            left--;
        }
        // if we found another subsequence with smaller length, update result
        if (right - left + 1 < minLen) {
            minLen = right - left + 1;
            result = S.substr(left, right + 1);
        }
        // WARNING: we have to move right pointer to the next position of left pointer, NOT the next position
        // of right pointer
        right = left + 1;
    }
    return result;
}

void testWindow() {
    string S = "abcdebdde", T = "bde";
    cout << minWindow(S, T) << endl;
}

int main(int argc, char *argv[]) {
    testWindow();
    return 0;
}
