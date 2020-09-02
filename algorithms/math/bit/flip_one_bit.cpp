#include <iostream>
using namespace std;

// 05.03
int flipOneBit(int num) {
    int cnt = 0, pre = 0, maxLen = 0;
    while (num) {
        if ((num & 1) == 0) {
            maxLen = max(maxLen, cnt + 1 + pre);
            pre = cnt;
            cnt = 0;
        } else {
            cnt++;
        }
        num >>= 1;
    }

    return max(maxLen, cnt + 1 + pre);
}
