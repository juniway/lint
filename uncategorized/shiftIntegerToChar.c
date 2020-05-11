/*
a=12345678 为int型，在内存中占4字节，共32位，即为 00000000 10111100 01100001 01001110
将a右移24位即取出前8位，第一个字节；
将a右移16位，然后位与00000000 11111111 即0xff，即可取出第二个字节；
将a右移8位，然后位与00000000 00000000 11111111 即0xff，即可取出第三个字节；
将a位与00000000 00000000 00000000 11111111 即0xff，即可取出第四个字节。
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void testShift() {
    char b[4];

    for (int i = 0; i < 10; i++) {
        int a = rand();
        b[0] = a >> 24;
        b[1] = ((a >> 16) & 0xff);
        b[2] = ((a >> 8) & 0xff);
        b[3] = a & 0xff;

        printf("%2c|%2c|%2c|%2c|\n", b[0], b[1], b[2], b[3]);
    }
}

int main(){
    srand(time(NULL));
    testShift();
	return 0;
}