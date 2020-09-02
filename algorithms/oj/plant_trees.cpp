/*
 * https://ac.nowcoder.com/acm/contest/119/F?&headNav=www&headNav=acm
 * n(1≤n≤100), C(1≤C≤10^8)
 * ci(1≤ci≤10^6) and vi(1≤vi≤100)
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#define ll long long

using namespace std;

ll dp[1000005];
ll val[105], v[105];
ll T, n, C;
// n is the number of items
// C is the Capacity

int main() {
    scanf("%lld", &T);
    while(T--) {
        scanf("%lld%lld",&n, &C);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%lld%lld", &v[i], &val[i]);
            sum += val[i];
        }
    }
}

