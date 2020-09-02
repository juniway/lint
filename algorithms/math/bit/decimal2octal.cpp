#include <iostream>
#include <string>
using namespace std;

string decToOctal(int n) {
	string res;
    while (n != 0) {
        res += (n % 8 + '0');
        n = n / 8;
    }

    reverse(res.begin(), res.end());
    return res;
}

void testDecimal2Octal() {
    cout << decToOctal(16) << endl;
}

int main(int argc, char *argv[]) {
    testDecimal2Octal();
    return 0;
}
