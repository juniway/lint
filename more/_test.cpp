#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n = 0;
void perm (int list[], int k, int m) {
    if (k >= m) {
        for (int i = 0; i <= m; ++i) {
            printf("%d ", list[i]);
        }
        printf("\n");
        ++n;
    } else {
        for (int i = k; i <= m; ++i) {
            swap(list[k], list[i]);
            perm(list, k + 1, m);
            swap(list[k], list[i]);
        }
    }
}

void combine(int a[], int n, int m, int b[], const int M){
    for(int i = n; i >= m; i--){  // 注意这里的循环范围
        b[m-1] = i - 1;
        if (m > 1) combine (a, i-1, m-1, b, M);
        else{   // m == 1, 输出一个组合
            for(int j=M-1; j>=0; j--)
              cout << a[b[j]] << " ";
            cout << endl;
        }
    }
}

int mostvalue(vector<int> A) {
    int n = (int)A.size();
    int mostKey = 0;
    int mostCounts = 0;

    int *counts = new int[n];
    memset(counts, 0, n);

    for (int i = 0; i < n; ++i) {
        counts[A[i]]++;
        if(mostCounts < counts[A[i]]) {
            mostCounts = counts[A[i]];
            mostKey = A[i];
        }
    }

    return mostKey;
}

const int MAXN = 5;
int r;
char used[MAXN];
int p[MAXN];

void permute(int pos) { 
    int i;
    // 如果已是第 r 个元素了，则可打印 r 个元素的排列
    if (pos == r) {
        for ( i = 0; i < r; i++) {
            cout << (p[i]+1);
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {     // 如果第 i 个元素未用过
            used[i]++;      // 使用第 i 个元素，作上已用标记，目的是使以后该元素不可用
            p[pos] = i;     // 保存当前搜索到的第 i 个元素
            permute(pos+1); // 递归搜索
            used[i]--;      // 恢复递归前的值，目的是使以后改元素可用
         }
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    perm(list, 0, 2); // 0, 2 表示索引范围
    printf("Total: %d \n", n);

    vector<int> a = {1, 3, 3, 2, 3, 2, 7};
    cout << "most key: " <<  mostvalue(a) << endl;
}
