#include <iostream>
#include <vector>
#include <string>

using namespace std;

int countDecoding(string digits, int n) {
    if (n == 0 || n == 1) return 1;
    if (digits[0] == '0') return 0;

    int count = 0;
    if (digits[n - 1] > '0')
        count = countDecoding(digits, n - 1);
    if (digits[n - 2] == '1' || (digits[n - 2] == '2' && digits[n - 1] < '7'))
        count += countDecoding(digits, n - 2);

    return count;
}

int countDecodingDp(string digits, int n) {
    vector<int> count(n + 1, 0);
    count[0] = 1;
    count[1] = 1;
    if (digits[0] == '0') return 0;
    for (int i = 2; i <= n; ++i) {
        if(digits[i - 1] > '0')
            count[i] = count[i - 1];
        if(digits[i - 2] == '1' || (digits[i - 2] == '2' && digits[i - 1] < '7'))
            count[i] += count[i - 2];
    }

    return count[n];
}

int countDecodingDpO(string digits, int n) {
    if (digits[0] == '0')
        return 0;

    int count0 = 1, count1 = 1, tmp = 0, tmp1 = 0;
    for (int i = 2; i <= n; i++) {
        tmp = 0;
        tmp1 = ((int)(digits[i - 1] != '0') *  count1) +
            (int)((digits[i - 2] == '1') or (digits[i - 2] == '2' and digits[i - 1] < '7')) * count0;
        if (digits[i - 1] > '0')
            tmp = count1;
        if (digits[i - 2] == '1' || (digits[i - 2] == '2' && digits[i - 1] < '7'))
            tmp += count0;

        count0 = count1;
        count1 = tmp;
    }

    return count1;
}

void testCountDecoding() {
    string s{"100"};
    // cout << countDecoding(s, s.length()) << endl;
    // cout << countDecodingDp(s, s.length()) << endl;
    cout << countDecodingDpO(s, s.length()) << endl;
}

int main(int argc, char *argv[]) {
    testCountDecoding();
    return 0;
}
