#include <cmath>

bool isPowerOfThree(int n) {
    if(n <= 0) return false;
    double a = log10(n) / log10(3) ;        // 换底
    return  a == floor(a);         // 判断换底后的log3n是否为整数，即 n 是否为3的倍数
}
