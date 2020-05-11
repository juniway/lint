#include <stdio.h>

void qsort(int a[], int left, int right){
    if(left > right) return;
    int i = left, j = right;

    int tmp;
    while(i < j){
        while(a[j] >= a[left] && i < j){
            --j;
        }
        while(a[i] <= a[left] && i < j){
            ++i;
        }

        if(i < j){
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }

    tmp = a[left];
    a[left] = a[i];
    a[i] = tmp;

    qsort(a, left, i - 1);
    qsort(a, i + 1, right);

}

void print_arr(int a[], int N){
    printf("qsort:");
    int i = 0;
    for(; i < N; ++i){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(){
    #define N 10
    int a[N] = {2, 10, 4, 7, 9, 3, 11, 5, 19, 8};

    int len = sizeof(a) / sizeof(a[0]);
    printf("%d\n", len);

    qsort(a, 0, N - 1);

    print_arr(a, N);

    return 0;
}
