#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

bool isValid(string s) {
    stack<char> star, left;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '*')
            star.push(i);
        else if (s[i] == '(')
            left.push(i);
        else {
            if (star.empty() || left.empty()) return false;
            if (!left.empty()) left.top();
            else star.pop();
        }
    }

    while(!left.empty() && !star.empty()) {
        if (left.top() > star.top())
            return false;
        left.pop(), star.pop();
    }

    return left.empty();
}

bool isValid1(string s) {
    int left = 0, right = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(' || s[i] == '*') left++;
        else left--;
        if (left < 0) return false;
    }
    if (left == 0) return true;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == ')' || s[i] == '*') right++;
        else right--;
        if (right < 0) return false;
    }

    return true;
}

void testMatch() {
    string s = "(*))";

    cout << boolalpha << isValid(s) << endl;
}

int main(int argc, char *argv[]) {
    testMatch();
    return 0;
}
