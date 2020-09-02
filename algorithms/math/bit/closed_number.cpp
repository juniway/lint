#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

vector<int> findClosedNumbers(int num) {
    bitset<32> small(num);
    bitset<32> bigger(num);

    int s = -1;
    // small, 10 转 01，1移到左侧
    for (int i = 1; i < 32; i++) {
        if (small[i] == 1 && small[i - 1] == 0) {
            small.flip(i);
            small.flip(i - 1);
            // for (int left = 0, right = i - 2; left < right;) {
            //     while (left < right && small[left] == 0) left++;
            //     while (left < right && small[right] == 1) right--;
            //     small.flip(left);
            //     small.flip(right);
            // }
            s = (int)small.to_ulong();
            break;
        }
    }

    // bigger, 01转10，1移到最右侧
    int b = -1;
    for (int i = 1; i < 32; i++) {
        if (bigger[i] == 0 && bigger[i - 1] == 1) {
            bigger.flip(i);
            bigger.flip(i - 1);

            for (int left = 0, right = i - 2; left < right;) {
                while (left < right && bigger[left] == 1) left++;
                while (left < right && bigger[right] == 0) right--;
                bigger.flip(left);
                bigger.flip(right);
            }
            b = (int)bigger.to_ulong();
            break;
        }
    }

    return {b, s};
}


void testFindClosedNumber() {
    // auto res = findClosedNumbers(1837591841);
    auto res = findClosedNumbers(9);
    cout << res[0] << ", " << res[1] << endl;
}

int main(int argc, char *argv[]) {
    testFindClosedNumber();
    return 0;
}
