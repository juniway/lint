#include <iostream>
#include <string>
#include <vector>
using namespace std;

string DeleteDigits(string &num, int k) {
    string ans = "";
    for (char c : num) {
        while(ans.length() > 0 && ans.back() > c && k > 0) {
            ans.pop_back();
            k--;
        }
        if (ans.length() > 0 || c != '0') ans.push_back(c);
    }

    while(ans.length() > 0 && k--) {
        ans.pop_back();
    }
    return ans.empty()? "0" : ans;
}

void testDeleteDigits() {
    string s = "178542";
    cout << DeleteDigits(s, 4) << endl;
}

int main(int argc, char *argv[]) {
    testDeleteDigits();
    return 0;
}
