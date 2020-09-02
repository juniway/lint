#include <iostream>
#include <vector>
using namespace std;

int query(int index) {
    cout << "Q " << index << "\n";
    cout.flush();
    int value;
    cin >> value;
    return value;
}

int solve(int N) {
    int f = query(N);
    cout << "f is: " << f << endl;
    int l = 0, r = N;
    while(r-l>1){
        int m = (r+l)/2;
        int q = query(m);
        if(q > f) l =m;
        else r = m;
    }
    return l;
}
int main() {
    int N;
    cin >> N;
    cout << "A " << solve(N) << "\n";
    cout.flush();
    return 0;
}
