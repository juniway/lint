[LeetCode 20] Valid Parentheses


Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid 
but "(]" and "([)]" are not.

[解题思路]
经典的栈匹配。一个栈，左符号入栈，右符号出栈。最后检查栈是否为空。

Related:
[LeetCode 32] Longest Valid Parentheses


class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(int i = 0; i < s.length(); ++i){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
                st.push(s[i]);
            }
            else{
                if(st.empty()) return false;
                if(s[i] == ')' && st.top() != '(')
                    return false;
                else if(s[i] == ']' && st.top() != '[')
                    return false;
                else if(s[i] == '}' && st.top() != '{')
                    return false;
                else
                    st.pop();
            }
        }
        return st.empty();
    }
};