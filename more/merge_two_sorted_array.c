#include <stdio.h>
#include <stdlib.h>

void print_arr(int* a, int N){
	printf("after sort:");
	int i = 0;
	for(; i < N; ++i){
		printf("%d ", a[i]);
	}
	printf("\n");
}

int* merge(int *l, int m, int *r, int n){
	int *res = malloc((m+n)*sizeof(int));

	int i = 0, j = 0;
	for(int k = 0; k < m + n; ++k){
		if(i < m && j < n){
			if(l[i] < r[j]){
				res[k] = l[i];
				i++;
			}
			else{
				res[k] = r[j];
				j++;
			}
		}
		else if(i == m){
			res[k] = r[j];
			j++;
		}
		else if(j == n){
			res[k] = l[i];
			i++;
		}
	}

	return res;
}

int main () {
    int a1[] = {4, 5, 9, 11, 18};
    int a2[] = {1, 8, 13, 14, 21};

    int n1 = sizeof(a1) / sizeof(a1[0]);
    int n2 = sizeof(a2) / sizeof(a2[0]);

    int *res = merge(a1, n1, a2, n2);

    print_arr(res, n1+n2);

    free(res);

    return 0;
}