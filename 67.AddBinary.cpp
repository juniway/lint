[LeetCode 67] Add Binary
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".

Difficulty: easy


class Solution {
public:
    string addBinary(string a, string b) {
        string result;
        int i = a.size() - 1, j = b.size() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0) {
            int x = carry;
            if (i >= 0) x += a[i] - '0';
            if (j >= 0) x += b[j] - '0';
            result.push_back(x % 2 + '0');
            carry = x / 2;
            i--;
            j--;
        }

        if (carry > 0) result.push_back(carry + '0');
        reverse(result.begin(), result.end());

        return result;
    }
};