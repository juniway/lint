#include <iostream>
#include <vector>
using namespace std;

typedef long long BigInt;

vector<BigInt> matrixMultiply(vector<BigInt>& x, vector<BigInt>& y) {
    return vector<BigInt> {
        (x[0] * y[0]) + (x[1] * y[2]),
        (x[0] * y[1]) + (x[1] * y[3]),
        (x[2] * y[0]) + (x[3] * y[2]),
        (x[2] * y[2]) + (x[3] * y[3])
    };
}

vector<BigInt> fastMatrixPow(vector<BigInt>& matrix, int n) {
    if (n < 0) throw "invalid n";
    vector<BigInt> res {1, 0, 0, 1}; // identity matrix
    while (n != 0) {
        if (n & 1)
            res = matrixMultiply(res, matrix);
        n /= 2;
        matrix = matrixMultiply(matrix, matrix);
    }
    return res;
}

BigInt fastFibonacciMatrix(int n) {
    vector<BigInt> mat = {1, 1, 1, 1};
    return fastMatrixPow(mat, n)[1];
}

void testFastFibonacciMatrix() {
    cout << fastFibonacciMatrix(10) << endl;
}

int main(int argc, char *argv[]) {
    testFastFibonacciMatrix();
    return 0;
}
