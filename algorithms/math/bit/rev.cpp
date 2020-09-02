#include <iostream>
using namespace std;

unsigned int reverseBit(unsigned int num) {
    unsigned int cnt = 31;
    unsigned int res = num;
    num >>= 1;
    while (num) {
        res <<= 1;
        res |= (num & 1);
        num >>= 1;
        cnt--;
    }
    res <<= cnt;
    return res;
}


unsigned int reverseBits(unsigned int num) {
    unsigned int count = sizeof(num) * 8 - 1;
    unsigned int reverse_num = num;

    num >>= 1;
    while(num)
    {
       reverse_num <<= 1;
       reverse_num |= num & 1;
       num >>= 1;
       count--;
    }
    reverse_num <<= count;
    return reverse_num;
}

uint32_t reverse(uint32_t n) {
    uint32_t res = 0;

    for(int i = 0; i < 32; i++, n >>= 1) {
        res = (res << 1) + (n & 1);
    }

    return res;
}

unsigned int rev1(unsigned int num) {
    unsigned int res = 0;
    for (int i = 0; i < sizeof(num) * 8; i++, num >>= 1) {
        res = (res << 1) + (num & 1);
    }

    return res;
}

unsigned int reverseBits1(unsigned int num) {
    unsigned int  NO_OF_BITS = sizeof(num) * 8;
    unsigned int reverse_num = 0;
    int i;
    for (i = 0; i < NO_OF_BITS; i++)
    {
        if((num & (1 << i)))
           reverse_num |= 1 << ((NO_OF_BITS - 1) - i);
   }
    return reverse_num;
}

uint32_t rev2(uint32_t n) {
    n = (n & 0xFFFF0000) >> 16 | (n & 0x0000FFFF) << 16;
    n = (n & 0xFF00FF00) >> 8 | (n & 0x00FF00FF) << 8;
    n = (n & 0xF0F0F0F0) >> 4 | (n & 0x0F0F0F0F) << 4;
    n = (n & 0xCCCCCCCC) >> 2 | (n & 0x33333333) << 2;
    n = (n & 0xAAAAAAAA) >> 1 | (n & 0x55555555) << 1;

    return n;
}

void testReverseBits() {
    unsigned int x = 1;
    cout << rev1(x) << endl;
    cout << rev2(x) << endl;
    cout << reverse(x) << endl;
    cout << reverseBit(x) << endl;
    cout << reverseBits(x) << endl;
    cout << reverseBits1(x) << endl;
}

int main(int argc, char *argv[]) {
    testReverseBits();
    return 0;
}
