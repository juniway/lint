[LeetCode] Valid Palindrome
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.
Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.
For the purpose of this problem, we define empty string as valid palindrome.
思路：
回文必定是左右对称。所以双指针left/right分别向中间扫描比较。遇到非数字字母的字符则跳过。直到left/right对应的数字字母不同，返回false；或left/right相遇，返回true。
corner case: 空字符串，或字符串中没有数字字母。

class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size();
        int i = 0, j = n - 1;
        while(i < j){
            while(!isalnum(s[i]) && i < j) ++i;
            while(!isalnum(s[j]) && i < j) --j;
            if(tolower(s[i]) != tolower(s[j]))
                return false;
            ++i, --j;
        }
        return true;
    }
};