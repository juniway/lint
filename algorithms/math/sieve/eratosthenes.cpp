#include <iostream>
#include <vector>
using namespace std;

void sieveOfEratosthenes(int n) {
    vector<bool> primes(n + 1, true);

    for (int p = 2; p * p <= n; p++) {
        if (primes[p]) {
            for (int i = p * p; i <= n; i += p) {
                primes[i] = false;
            }
        }
    }

    for (int i = 2; i <= n; i++)
        if (primes[i])
            cout << i << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    sieveOfEratosthenes(100);
    return 0;
}
