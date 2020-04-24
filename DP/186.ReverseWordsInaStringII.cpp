[LeetCode 186] Reverse Words in a String II

Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.
The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?

这道题要求in-place做法，不能使用extra space, 那么，做法跟Rotate Array那道题非常相似
（1）reverse the whole array
（2）reverse each subarray seperated by ' '

class Solution {
public:
    void reverseWords(string s) {
        if (s.length == 0) return;
        std::reverse(s.begin(), s.end());
        int last = 0;
        for (int i = 0; i < s.length; i++){
            if (s[i] == ' ') {
                std::reverse(s.begin() + last, s.begin() + i-1);
                last = i + 1;
            }
        }
    }
    
    // void reverse(string s, int l, int r) {
    //     while (l <= r) {
    //         int temp = s[l];
    //         s[l] = s[r];
    //         s[r] = temp;
    //         l++;
    //         r--;
    //     }
    // }
};

