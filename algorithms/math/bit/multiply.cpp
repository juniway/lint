#include <iostream>
#include <vector>

using namespace std;

// 08.05
int multiplyTwo(int a, int b) {
    if (a < b) swap(a, b);

    int res = 0, i = 0;
    while(b > 0) {
        if (b & 1){
            res += (a << i);
        }
        b >>= 1;
        i++;
    }

    return res;
}

int multiplyTwoRec(int a, int b) {
    if (a > b) swap(a, b);
    if (b == 0) return 0;
    return a + multiplyTwo(a, b - 1);
}

// 05.01
int insertBits(int N, int M, int i, int j) {
    for (int k = i; k <= j; k++) {
        N = N & ~(N >> k);
    }
    N += (M << i);
    return N;
}

// 05.04
vector<int> findClosedNumbers(int num) {
    bitset<32> small(num);
    bitset<32> big(num);

    int s = -1; // smallest bigger than num
    for (int i = 1; i < 32; i++) {
        if (small[i] == 0 && small[i - 1] == 1) {
            small[i].flip();
            small[i - 1].flip();
            int left = i - 2, right = 0;
            while(left > right) {
                while(left < right && small[left] == 0) left--;
                while(left < right && small[right] == 1) right++;
                small[left].flip();
                small[right].flip();
            }
            s = (int)small.to_ulong();
            break;
        }
    }

    int b;
    for (int i = 1; i < 32; i++) {
        if (big[i] == 1 && big[i - 1] == 0) {
            big[i].flip();
            big[i - 1].flip();
            int left = i - 2, right = 0;
            while(left < right) {
                while (left < right && big[left] == 1) left--;
                while (left < right && big[right] == 0) right++;
                big[left].flip();
                big[right].flip();
            }
            b = (int)big.to_ullong();
            break;
        }
    }

    return {s, b};
}

void testMultiply() {
    cout << multiplyTwo(6, 7) << endl;
    cout << multiplyTwoRec(6, 7) << endl;
    cout << insertBits(1024, 19, 2, 6) << endl; // expected: 1100
}

int main(int argc, char *argv[]) {
    testMultiply();
    return 0;
}
