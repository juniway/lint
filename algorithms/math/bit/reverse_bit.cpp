// #include <cstdint>
#include <iostream>

uint32_t reverse(uint32_t n) {
    uint32_t res = 0;

    for(int i = 0; i < 32; i++, n >>= 1) {
        res = (res << 1) + (n & 1);
    }

    return res;
}

uint32_t reverse1(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; i++) {
        if ((n & (1 << i)))
            res |= (1 << (31 - i));
    }

    return res;
}

unsigned int reverseBits(unsigned int n) {
    unsigned int count = sizeof(n) * 8 - 1;
    unsigned int reverse_n = n;

    n >>= 1;
    while(n) {
       reverse_n <<= 1;
       reverse_n |= n & 1;
       n >>= 1;
       count--;
    }

    std::cout << "count: " << count << "\n";
    reverse_n <<= count;
    return reverse_n;
}

// Lookup Table
/*
tb[0]  = 0  [0000]
tb[1]  = 8  [1000]
tb[2]  = 4  [0100]
tb[3]  = 12 [1100]
tb[4]  = 2  [0010]
tb[5]  = 10 [1010]
tb[6]  = 6  [0110]
tb[7]  = 14 [1110]
tb[8]  = 1  [0001]
tb[9]  = 9  [1001]
tb[10] = 5  [0101]
tb[11] = 13 [1101]
tb[12] = 3  [0011]
tb[13] = 11 [1011]
tb[14] = 7  [0100]
tb[15] = 15 [1111]
 */
char tb[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

uint32_t reverseBits1(uint32_t n) {
    uint32_t res = 0;
    uint32_t mask = 0xF;
    for(int i = 0; i < 8; i++) {
        res = res << 4;
        res |= tb[n & mask];
        n = n >> 4;
    }
    return res;
}

uint32_t swapbits(uint32_t n) {
    return (n & 0xAAAAAAAA) >> 1 | (n & 0x55555555) << 1;
}

void testReverse() {
    uint32_t n = 1;
    std::cout << reverseBits1(n) << "\n";
    std::cout << reverse(n) << "\n";
}

int main(int argc, char *argv[]) {
    testReverse();
    std::cout << int(0xF0) << std::endl;
    std::cout <<swapbits(0x0A) << "\n";
    return 0;
}
