#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

string lockin, lockout;

int L1[35], L2[35], L3[35];

int main(int argc, char *argv[]) {
    int num1 = 0, num2 = 0;
    cin >> lockin >> lockout;
    int len = lockin.length();
    for(int i = 0; i < len; i++){
        L1[i] = (int)(lockin[i] - '0');
        L3[i] = L1[i];
        L2[i] = (int)(lockout[i] - '0');
    }

    // 不按第一把锁
    for(int i = 1; i < len; i++){
        if(L1[i-1] != L2[i-1]){
            num1++;
            L1[i-1] ^= 1;
            L1[i] ^= 1;
            L1[i+1] ^= 1;
        }
    }

    // 按第一把锁
    L3[0] ^= 1;
    L3[1] ^= 1;
    num2++;
    for(int i = 1; i < len; i++){
        if(L3[i-1] != L2[i-1]){
            num2++;
            L3[i-1] ^= 1;
            L3[i] ^= 1;
            L3[i+1] ^= 1;
        }
    }

    int flag1 = 1,flag2 = 1;
    for(int i = 0; i < len; i++){
        if(L1[i] != L2[i]){
            flag1 = -1;
        }
        if(L3[i] != L2[i]){
            flag2 = -1;
        }
    }

    if(flag1 == -1 && flag2 == -1){
        cout<<"impossible"<<endl;
    }
    else if(flag1 == 1 && flag2 == 1){
        int num = min(num1, num2);
        cout << num << endl;
    }
    else {
        if(flag1 == 1) cout<< num1 << endl;
        if(flag2 == 1) cout<< num2 << endl;
    }

    return 0;
}
