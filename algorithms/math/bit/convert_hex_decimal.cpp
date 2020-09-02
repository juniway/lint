#include <iostream>
#include <string>
#include <stack>
using namespace std;

string decimal2hex(int n) {
    string res;
    int rem = 0;
    stack<int> st;
    while (n > 0) {
        rem = (n % 16);
        st.push(rem);
        n = n / 16;
    }

    while (!st.empty()) {
        string tmp = "";
        if (st.top() > 9)
            tmp.push_back('A' + st.top() - 10);
        else
            tmp = to_string(st.top());
        res += tmp;
        st.pop();
    }

    return res;
}

int hex2decimal(string n) {
    int i = n.length() - 1, lastdigit = 0, res = 0;
    int base = 1;
    while (i >= 0) {
        if (n[i] >= '0' && n[i] <= '9')
            lastdigit = n[i] - '0';
        else {
            lastdigit = 10 + n[i] - 'A';
        }

        res += lastdigit * base;
        base *= 16;
        i--;
    }

    return res;
}

void testDecimal2Hex() {
    cout << decimal2hex(16) << endl;
    cout << decimal2hex(15) << endl;
    cout << decimal2hex(9) << endl;
    cout << decimal2hex(32) << endl;
    cout << decimal2hex(241) << endl;
    cout << decimal2hex(2545) << endl;
}

void testHex2Decimal() {
    cout << hex2decimal("F") << endl;
    cout << hex2decimal("9") << endl;
    cout << hex2decimal("F1") << endl;
    cout << hex2decimal("9F1") << endl;
}

int main(int argc, char *argv[]) {
    testDecimal2Hex();
    cout << "==================================\n";
    testHex2Decimal();
    return 0;
}
