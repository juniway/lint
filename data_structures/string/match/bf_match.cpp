#include <iostream>
#include <string>

using namespace std;

int match1(string p, string t) {
    int m = p.length(), n = t.length();
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && t[i + j] == p[j])
            j++;
        if (j == m) return i;
    }
    return -1;
}

void testMatch() {
    cout << match1("abc", "abc") << endl;
}

int main(int argc, char *argv[]) {
    testMatch();
    return 0;
}
